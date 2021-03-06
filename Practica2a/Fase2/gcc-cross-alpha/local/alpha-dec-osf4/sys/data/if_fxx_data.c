/*
 * *****************************************************************
 * *                                                               *
 * *    Copyright (c) Digital Equipment Corporation, 1991, 1999    *
 * *                                                               *
 * *   All Rights Reserved.  Unpublished rights  reserved  under   *
 * *   the copyright laws of the United States.                    *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Digital   *
 * *   Equipment Corporation.  Possession, use,  duplication  or   *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Digital Equipment  *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */
/*
#pragma ident "@(#)$RCSfile: if_fxx_data.c,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1994/11/08 17:23:52 $"
 */

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>  
#include <vm/vm_kern.h>  
#include <sys/syslog.h>  
#include <dec/binlog/errlog.h>

#include <net/if.h>
#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/in_systm.h>
#include <netinet/if_ether.h>
#include <netinet/if_fddi.h>
#include <net/ether_driver.h>
#include <hal/cpuconf.h>
#include <io/common/devdriver.h>
#include <io/dec/uba/ubavar.h>
#include <io/dec/tc/tc.h>

#include <kern/thread.h>
#include <kern/sched_prim.h>

#include <io/dec/netif/if_pdqreg.h>
#ifdef VFAA
#include <io/dec/mbox/mbox.h>
#endif

/*
 * For this release we have a hack for getting aligned, contiguous memory.
 */
#ifdef mips
#define FTAIOSYNC()	wbflush()
#define FTAREGWR(csr,v) (*(csr)) = (v)
#define FTAREGRD(csr) (*(csr))
#define PAGESZ	4096
#ifdef OSF
#define PDQ_VM_HACK
#endif OSF
#else 
#ifdef __alpha
#define FTAIOSYNC()	mb()
#ifdef VFTA
#define FTAREGWR(csr, value)	(*(csr)) = ((unsigned long)((0x0FL<<32)|((unsigned long)(value))));
#define FTAREGRD(csr) (*(volatile unsigned int *)(csr))
#endif
#ifdef VFAA
#define FTAREGWR(csr, value) (WRTCSRS(LONG_32, sc->ctlr, csr, value))
#define FTAREGRD(csr) (RDCSR(LONG_32, sc->ctlr, csr))
#endif
#define PAGESZ	8192
#endif /* __alpha */
#endif /* mips */
/*
 * To identify the different receive Q's
 */
#define RCV_Q 		0
#define UNSOL_Q		1
#define CMDRSP_Q	2
#define SMT_Q		3
/*
 * The number of transmit and receive descriptors
 * we will be using. The maximum number of XMT and RCV
 * descriptors is 256 each. 
 * NOTE: We have to use all 256 descriptors. The number 
 *	 is not programmable
 */
#define NPDQRCV		256
#define NPDQRCV_MASK	0xFF
#define NPDQXMT		256
#define NPDQXMT_MASK	0xFF
/*
 * The number of Command Request, Command Response, Unsolicited
 * responses and Host SMT descriptors used.
 * 	Command Request: 	16
 *	Command Response:	16
 *	Unsolicited:		16
 *	Host SMT:		16
 */
#define NPDQCREQ	16
#define NPDQCREQ_MASK	0x0F
#define NPDQCRSP	16
#define NPDQCRSP_MASK	0x0F
#define NPDQUNSOL	16
#define NPDQUNSOL_MASK	0x0F
#define NPDQHSMT	64
#define NPDQHSMT_MASK	0x3F

/*
 * The default buffer sizes we allocate for each of the receive queues.
 */
#define RSP_BUFSIZ	512
#define UNSOL_BUFSIZ	512
#ifdef __alpha
/*
 * NOTE: Even though we allocate a cluster mbuf (size == 8192) we 
 * specify the BUFSIZ to be 4608 bytes. FDDIMAX is 4495.
 * The maximum receive buffer length on the adapter is 8064 bytes. This is 
 * what you get if you set the seg_len field in the receive descriptor 
 * (bits 28:23,  corresponding to seg_len[12:7]) to all ones. If you try 
 * to specify a length of 8192 , by setting bit 29 of the descriptor to one and 
 * bits 28:23 to zero, the PDQ will see the length as zero and stop because 
 * you specified a zero length buffer.
 */
#define RCV_BUFSIZ	4608
#define SMT_BUFSIZ	4608
#else
#define RCV_BUFSIZ	MCLBYTES /* 4096 for mips */
#define SMT_BUFSIZ	MCLBYTES
#endif /* __alpha */

/*
 * The number of descriptors to produce initially
 * NOTE: This means that we produce 32 descriptors for
 *	 alpha and 24 pairs of descriptors for mips.
 */
#ifdef __alpha
#define RCV_DESCR_PROD 		32	/* till index 31 */
#else
#define RCV_DESCR_PROD 		48	/* till index 47 */
#endif /* __alpha */
#define UNSOL_DESCR_PROD    	16	/* till index 15 */
#define SMT_DESCR_PROD		16	/* i.e. till index 15 */
/*
 * The number of segments we need.
 * In case of the receive data queue we use 2 segments,
 * in all other cases we use only one segment.
 */
#define PDQ_HOST_SEG_VALUE_1	0x0000
#define PDQ_HOST_SEG_VALUE_2	0x0001

/*
 * To delete and add addresses to the CAM
 */
#define PDQ_DEL_ADDR	0
#define PDQ_ADD_ADDR	1

/*
 * The thresholds for knowing when to transmit packets.
 * NOT USED.
 */
#define XMT_THRESH	15

/*
 * The threshold for enabling the xmt done interrupt.
 * NOT USED.
 */
#define DESCR_THRESH	32

/*
 * The producer threshold is used for writing out the producer index
 * out onto the adapter. If the driver has not produced the number of
 * descriptors required this value is not written out until we have finished
 * processing all the packets.
 * NOT USED.
 */
#define PROD_THRESH	12	/* 6 packets */

/*
 * This threshold defines the number of packets that are received at one
 * time, after which the transmit routine is called to transmit ONE packet.
 * This is used to acheive some degree of fairness between receive and 
 * the transmit sides.
 */
#define PKTS_RCVD_THRESH	30
/*
 * The receive descriptors used. The default value for this
 * is 8 and is user settable to a maximum of 128 with dbx.
 * In the event of the driver being made promicuous this
 * value increases to 32 (if less than 32) or a value set by
 * the user, if it is greater than 32.
 */
extern short recv_descr;

#ifdef PDQ_VM_HACK
/*
 * For the descriptor block.
 */
struct queue_info {
    PI_RCV_DESCR  *rcv_data;
    PI_XMT_DESCR  *xmt_data;
    PI_RCV_DESCR  *smt_host;
    PI_RCV_DESCR  *unsol;
    PI_RCV_DESCR  *cmd_rsp;
    PI_XMT_DESCR  *cmd_req;
    u_long phys_descr_blk;		/* the physical address	     */
    PI_CONSUMER_BLOCK *cons_blk;	/* has to be 64 byte aligned */
    u_long phys_cons_blk;		/* the physical address	     */
    PORT_REGS regs;
};
#else
struct queue_info {
	PI_DESCR_BLOCK *descr_blk;	/* has to be 8K aligned      */
	u_long phys_descr_blk;		/* the physical address	     */
	PI_CONSUMER_BLOCK *cons_blk;	/* has to be 64 byte aligned */
	u_long phys_cons_blk;		/* the physical address	     */
	PORT_REGS regs;
};
#endif
/*
 * The following structure stores the settable characteristic values
 * in the adapter. These values are:
 * req_trt, tvx, restricted_token, ring_purger, counter_interval,
 * LEM_Threshold_0, LEM_Threshold_1 (not applicable for a SAS) and
 * Loopback_Mode.
 *	The values in this structure are then used to restore the status
 * values in case of a reset.
 */
struct char_values {
    short valid;	/* if valid == 0 information is incorrect. don't use */
    u_int treq;
    u_int tvx;
    u_int rtoken;
    u_int ring_purger;
    u_int cnt_interval;
    u_int lem0;	/* Only LEM 0; LEM 1 has no value for us */
    u_int loopback;
    u_short full_duplex_mode;
};


/*
 * Structure for keeping track of rcv. dma queue.
 */
struct rmbuf {
	struct mbuf *rmbuf;
	u_long	phymbuf;		/* data area of the mbuf */
	char  *mdata;			/* the virtual address for the data */
};

/*
 * Array to keep track of the virtual addresses that
 * we have allocated while transmitting mbuf's.
 */
struct xmtvaddr {
	struct mbuf *vaddr;
};

/*
 * For the commands.
 */
struct cmd_buf {
	u_long *req_buf;
	u_long *rsp_buf;
	short  timeout;
	struct cmd_buf *next;
};

struct fxxdebug {
	struct cmdcnt {
		u_short	start;
		u_short set_filter_set;
		u_short read_filters;
		u_short set_char;
		u_short read_char;
		u_short set_addr_filter;
		u_short read_addr_filter;
		u_int	read_counters;
		u_int	clear_error_log;
		u_int	read_error_log;
	} cmdcnt;
	struct 	fstat fstat;
	u_int  	fxxreset;
        u_int  	fxxundrop;
        u_int  	fxxsmtrcvd;
        u_int  	fxxnombuf;
	u_int  	fxxsmtdrop;
	u_int  	fxxlarge;
	u_int  	fxxsmall;
	u_int  	fxxmiddle;
	u_int  	fxxxmtdone;
	u_int  	fxxfairness;
	short	driver_state;			/* The state of the driver */
	short   prev_state;			/* Previous state of driver */
	short	ifq_maxlen_seen;		/* The maximum ifqlen len the
						 * driver observed.
						 */
}; 

/*
 * This structure contains information about the source address
 * of the directed beacon received and the address of the upstream
 * neighbor.
 */
struct dbeacon_info {
	u_char db_srcaddr[6];
	u_char db_unaddr[6];
};
/*
 * The following are used to index into the different
 * filters. We maintain a copy of the filters set on the
 * adapter in a structure in the softc - "filters".
 */
#define IND_GROUP	0
#define GROUP		1
#define BROADCAST	2
#define SMT_PROM	3
#define SMT_USER	4
#define RESERVED	5
#define IMPLEMENTOR	6
#define EOL		7


/*
 * FDDI software status per interface.
 * The FDDI network interface structure is based on ethernet interface 
 * structure.
 *
 * Each interface is referenced by a network interface structure,
 * ds_if, which the routing code uses to locate the interface.
 */
struct	fxx_softc {
	struct	   ether_driver is_ed;		/* FDDI driver */
#define	is_ac	is_ed.ess_ac			/* FDDI common part */
#define	ztime	is_ed.ess_ztime			/* Time since last zeroed */
#define	is_if	is_ac.ac_if			/* network-visible interface */
#define	is_addr	is_ac.ac_enaddr			/* hardware FDDI address */
#define is_ctrblk  is_ed.ess_ctrblk		/* counter block */
	vm_offset_t basereg;			/* base register  */
	struct     queue_info q_info;           /* contains info. about 
						 * descr_blk, cons_blk and
						 * registers.
						 */
	char	    is_multi[62][8];		/* multicast buffer */
	int	    is_muse[62];		/* number of entrys/slot */
	short	    is_inuse;			/* # of slots being used*/
	PI_ITEM_LIST filters[PI_CMD_FILTERS_SET_K_ITEMS_MAX];/*filters*/
	struct char_values char_val;		/* default charecteristics */
	PI_CNTR_BLK  *ctrblk;		        /* Per-unit line counters */
	PI_CMD_STATUS_CHARS_GET_RSP *fxx_status;/* Per-unit status info */
	PI_CMD_DEC_EXT_MIB_GET_RSP *dec_ext;	/* Per-unit status info */
	struct	    pdqsw *pdqsw;		/* bus specific information */
	u_char	    is_dpaddr[6];		/* Default phys. address */
 	u_long 	    *rsp_buf[NPDQCRSP]; 	/* allocated response buffers */
	struct cmd_buf *q_first;		/* first in the request q */
	struct cmd_buf *q_last;			/* last in the request q */

	decl_simple_lock_data(,lk_interrupt_level)
	lock_data_t lk_thread_level;

	thread_t    rcv_mbuf_alloc_thread;	/* thread to alloc mbufs */
	thread_t    cmd_rsp_thread;		/* thread to alloc mbufs */
	short	    rsp_thread_started;		/* rsp thread running?   */
	short 	    reinit_thread_started;	/* reinit thread running? */
	u_long	    *unsol_buf[NPDQUNSOL];	/* unsolicited q buffers  */
	u_long	    *cntr_update;		/* used while updating cntrs */
	short	    error_recovery_flag;	/* flag to wake up a process */
	short	    mbuf_alloc_flag;		/* flag to wake up a process */
	struct      rmbuf rcvmbuf[NPDQRCV];	/* receive mbuf chain */
	struct 	    xmtvaddr xmt_vaddr[NPDQXMT];/* Transmit buffer info. */
	u_int	    t_max;			/* value = 167.77224ms */
        int         ndbr;                       /* # of direct beacon recv*/
	struct	    dbeacon_info  dbeacon;
	int	    halt_count;			/* # of times halted */
#define MAX_HALTS	20			/* local copies of indexes */
	int	    l_xmtcompl_index;		/* on the adapter.	   */
	int	    l_rcvcompl_index;
	short	    l_xmtprod_index;
	short	    l_rcvprod_index;
	short	    l_unsolcompl_index;
	short	    l_unsolprod_index;
	short	    l_cmdreqcompl_index;
	short	    l_cmdreqprod_index;
	short	    l_cmdrspcompl_index;
	short	    l_cmdrspprod_index;
	struct      rmbuf smtmbuf[NPDQHSMT];	/* SMT receive mbuf chain */
	short	    l_hostsmtcompl_index;	/* local copy of compl. index */
	short	    l_hostsmtprod_index;	/* local copy of prod. index */
	short	    rcv_mbufs_allocated;	/* mbufs allocated    */
	short	    rcv_mbufs_required;		/* required mbufs */
	struct      fxxdebug  fxx_debug;	/* debug counter/info */
	struct      controller *ctlr;		/* needed by RDCSR/WRTCSR macros to get mbox */
#ifdef VFAA
/* These should eventually be moved into netif/if_pdqreg.h */
	volatile unsigned int	*error_hi;
	volatile unsigned int	*error_lo;
	volatile unsigned int	*faddr_hi;
	volatile unsigned int	*faddr_lo;
	volatile unsigned int	*bytelane;
	volatile unsigned int	*intr_addr;
	volatile unsigned int	*intr_data;
#endif /* VFAA */
};

#ifdef VFAA
/* These should eventually be moved into netif/if_pdqreg.h */
#define addr_error_hi		error_hi
#define addr_error_lo		error_lo
#define addr_faddr_hi		faddr_hi
#define addr_faddr_lo		faddr_lo
#define addr_bytelane		bytelane
#define addr_intr_addr		intr_addr
#define addr_intr_data		intr_data

#define BI_KR_ERROR_HI		    (0x0180)	/* from base of registers */
#define BI_KR_ERROR_LO		    (0x0184)	/* from base of registers */
#define BI_KR_FADDR_HI		    (0x0188)	/* from base of registers */
#define BI_KR_FADDR_LO		    (0x018C)	/* from base of registers */
#define BI_KR_BYTELANE		    (0x0190)	/* from base of registers */
#define BI_KR_INTR_ADDR		    (0x0400)
#define BI_KR_INTR_DATA		    (0x0408)
 /* note that for fbus, the regs are 4bytes apart */
#endif /* VFAA */

/*
 * Defines to make accessing the copies of the local pointers easier.
 */
#define xmt_cindex	sc->l_xmtcompl_index
#define rcv_cindex	sc->l_rcvcompl_index
#define xmt_pindex	sc->l_xmtprod_index
#define rcv_pindex	sc->l_rcvprod_index
#define unsol_cindex	sc->l_unsolcompl_index
#define unsol_pindex	sc->l_unsolprod_index
#define cmdreq_cindex	sc->l_cmdreqcompl_index
#define cmdreq_pindex	sc->l_cmdreqprod_index
#define cmdrsp_cindex	sc->l_cmdrspcompl_index
#define cmdrsp_pindex	sc->l_cmdrspprod_index
#define smt_cindex	sc->l_hostsmtcompl_index
#define smt_pindex	sc->l_hostsmtprod_index
/*
 * The firmware and hardware revision numbers.
 */
#define mod_rev		fxx_status->module_rev
#define firm_rev	fxx_status->firmware_rev
/*
 * The states.
 */
#define driver_state		fxx_debug.driver_state
#define prev_state		fxx_debug.prev_state

/*
 * The register addresses on the adapter.
 */
#define addr_portctrl		q_info.regs.port_ctrl
#define addr_portdataA		q_info.regs.port_data_A
#define addr_portdataB		q_info.regs.port_data_B
#define addr_intenbX		q_info.regs.int_enb_X
#define addr_portreset		q_info.regs.port_reset
#define addr_type2prod		q_info.regs.type2_prod
#define addr_portstatus		q_info.regs.port_status
#define addr_unsolprod		q_info.regs.unsol_prod
#define addr_cmdreqprod		q_info.regs.cmdreq_prod
#define addr_cmdrspprod 	q_info.regs.cmdrsp_prod
#define addr_hostsmtprod	q_info.regs.hostsmt_prod 
#define addr_hostdata		q_info.regs.host_data 
#define addr_intrtype0		q_info.regs.intr_type0 

/*
 * Consumer Indexes from the the adapter
 */
#define cons_req_index		q_info.cons_blk->cmd_req
#define cons_rsp_index		q_info.cons_blk->cmd_rsp
#define cons_unsol_index	q_info.cons_blk->unsol
#define cons_hostsmt_index	q_info.cons_blk->smt_host
#define cons_rcv_index		q_info.cons_blk->xmt_rcv_data
#define cons_xmt_index		q_info.cons_blk->xmt_rcv_data

/*
 * The descriptor blocks
 */
#ifdef PDQ_VM_HACK
#define rcv_data_blk		q_info.rcv_data
#define xmt_data_blk		q_info.xmt_data
#define smt_data_blk		q_info.smt_host
#define unsol_blk		q_info.unsol
#define cmd_rsp_blk		q_info.cmd_rsp
#define cmd_req_blk		q_info.cmd_req
#else
#define rcv_data_blk		q_info.descr_blk->rcv_data
#define xmt_data_blk		q_info.descr_blk->xmt_data
#define smt_data_blk		q_info.descr_blk->smt_host
#define unsol_blk		q_info.descr_blk->unsol
#define cmd_rsp_blk		q_info.descr_blk->cmd_rsp
#define cmd_req_blk		q_info.descr_blk->cmd_req
#endif

#define fstc_second 	sc->fxx_debug.fstat.fst_second
#define fstc_frame 	sc->fxx_debug.fstat.fst_frame
#define fst_station_id 		sc->fxx_debug.fxx_status.fst_station_id
#define fst_station_type 	sc->fxx_debug.fstat.fxx_status_station_type
#define fstc_error 	sc->fxx_debug.fstat.fst_error
#define fstc_lost 	sc->fxx_debug.fstat.fst_lost
#define fstc_bytercvd 	sc->fxx_debug.fstat.fst_bytercvd
#define fstc_bytesent 	sc->fxx_debug.fstat.fst_bytesent
#define fstc_pdurcvd 	sc->fxx_debug.fstat.fst_pdurcvd
#define fstc_pdusent 	sc->fxx_debug.fstat.fst_pdusent
#define fstc_underrun 	sc->fxx_debug.fstat.fst_underrun
#define fstc_sendfail 	sc->fxx_debug.fstat.fst_sendfail
#define fstc_fcserror 	sc->fxx_debug.fstat.fst_fcserror
#define fstc_fseerror 	sc->fxx_debug.fstat.fst_fseerror
#define fstc_pdualig 	sc->fxx_debug.fstat.fst_pdualig
#define fstc_pdulen 	sc->fxx_debug.fstat.fst_pdulen
#define fstc_pduunrecog sc->fxx_debug.fstat.fst_pduunrecog
#define fstc_overrun 	sc->fxx_debug.fstat.fst_overrun
#define fstc_sysbuf 	sc->fxx_debug.fstat.fst_sysbuf
#define fstc_userbuf 	sc->fxx_debug.fstat.fst_userbuf
#define fstc_ringinit 	sc->fxx_debug.fstat.fst_ringinit
#define fstc_ringinitrcv sc->fxx_debug.fstat.fst_ringinitrcv
#define fstc_ringbeacon sc->fxx_debug.fstat.fst_ringbeacon
#define fstc_dupaddfail sc->fxx_debug.fstat.fst_dupaddfail
#define fstc_duptoken   sc->fxx_debug.fstat.fst_duptoken
#define fstc_ringpurge 	sc->fxx_debug.fstat.fst_ringpurge
#define fstc_bridgestrip sc->fxx_debug.fstat.fst_bridgestrip
#define fstc_traceinit 	sc->fxx_debug.fstat.fst_traceinit
#define fstc_tracerecv 	sc->fxx_debug.fstat.fst_tracerecv
#define fstc_selftest 	sc->fxx_debug.fstat.fst_selftest
#define fstc_mbytesent 	sc->fxx_debug.fstat.fst_mbytesent
#define fstc_mpdusent 	sc->fxx_debug.fstat.fst_mpdusent
#define fstc_mbytercvd 	sc->fxx_debug.fstat.fst_mbytercvd
#define fstc_mpdurcvd 	sc->fxx_debug.fstat.fst_mpdurcvd
#define fstc_mpduunrecog sc->fxx_debug.fstat.fst_mpduunrecog
#define fstc_connection sc->fxx_debug.fstat.fst_connection
#define fstc_tne_exp_rej sc->fxx_debug.fstat.fst_tne_exp_rej
#define fstc_lct_rej  	sc->fxx_debug.fstat.fst_lct_rej
#define fstc_lem_rej  	sc->fxx_debug.fstat.fst_lem_rej
#define fstc_lem_events	sc->fxx_debug.fstat.fst_lem_events
#define fstc_ebf_error  sc->fxx_debug.fstat.fst_ebf_error
#define fxxnreset	sc->fxx_debug.fxxreset	
#define fxxnundrop	sc->fxx_debug.fxxundrop
#define fxxnsmtrcvd	sc->fxx_debug.fxxsmtrcvd
#define fxxnsmtdrop	sc->fxx_debug.fxxsmtdrop
#define fxxnnombuf	sc->fxx_debug.fxxnombuf
#define fxxnlarge	sc->fxx_debug.fxxlarge
#define fxxnmiddle	sc->fxx_debug.fxxmiddle
#define fxxnsmall	sc->fxx_debug.fxxsmall
#define fxxconcat	sc->fxx_debug.fxxconcat
#define fxxxmtdone	sc->fxx_debug.fxxxmtdone
#define fxxfairness	sc->fxx_debug.fxxfairness
#define ifqmaxlen_seen	sc->fxx_debug.ifq_maxlen_seen

/*
 * The driver states
 */
#define PI_DRIVERINIT		1
#define PI_PORTINIT		2
#define PI_OPERATIONAL		3
#define PI_UPGRADE		4
#define PI_BROKEN		5
#define PI_FLUSH		6

/*
 * The following is the switch table for the the different adapters
 * that might come out using the port spec. At this time (9/25;8:00 AM :-))
 * it is unclear what the structure should contain. But, the need for this
 * may exist.
 */
struct pdqsw {		/* The port interface switch */
	char *intf_name;
	u_long mode_base;
};
#ifdef BINARY
#ifdef VFTA
extern	struct 	fxx_softc fta_softc[];
extern	struct	controller *ftainfo[];
extern struct pdqsw turbosw[];
#endif
#ifdef VFAA
extern	struct 	fxx_softc faa_softc[];
extern	struct	controller *faainfo[];
extern struct pdqsw fbussw[];
#endif
#else BINARY

#ifdef VFTA
#include "fta.h"
#endif
#ifdef VFAA
#include "faa.h"
#endif

/* For the Turbochannel */
#ifdef VFTA
struct pdqsw turbosw [] = {
	"fta", TURBO_MODE_BASE 
};
#if NFTA > 0
struct 	fxx_softc fta_softc[NFTA];
struct	controller *ftainfo[NFTA];
#else 
struct 	fxx_softc *fta_softc;
struct	controller *ftainfo;
#endif	/* NFTA > 0 */
#endif	/* VFTA */

/* For the Futurebus */
#ifdef VFAA
struct pdqsw fbussw [] = {
	"faa", FBUS_MODE1_BASE 
};
#if NFAA > 0
struct 	fxx_softc faa_softc[NFAA];
struct	controller *faainfo[NFAA];
#else 
struct 	fxx_softc *faa_softc;
struct	controller *faainfo;
#endif	/* NFAA > 0 */
#endif	/* VFAA */

#endif	BINARY
