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
#pragma ident "@(#)$RCSfile: if_fta_data.c,v $ $Revision: 1.1.68.2 $ (DEC) $Date: 1998/10/09 20:25:50 $"
*/
/* -----------------------------------------------------------------------
 *
 * Modification history:
 *
 * 27-Mar-92	Uttam Shikarpur	
 *	Submitted into SILVER pool.
 *
 *---------------------------------------------------------------------- */
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
#include <io/dec/eisa/eisa.h>
#include <io/dec/pci/pci.h>

#include <kern/thread.h>
#include <kern/sched_prim.h>

#include <io/dec/netif/if_pdqreg.h>

#define FTAIOSYNC()	mb()
#define PAGESZ	8192

/*
 * Some defines for DEFPA
 */
#define	PFI_MODE	0x40	/* offset for PFI mode register */
#define	PFI_STATUS	0x44	/* offset for PFI status register */

#define	PFI_MODE_DMA_ENABLE	0x01	/* DMA Enable */
#define	PFI_MODE_PFI_PCI_INTR	0x02	/* PFI-to-PCI Interrupt Enable */
#define	PFI_MODE_PDQ_PCI_INTR	0x04	/* PDQ-to-PCI Interrupt Enable */

#define	PFI_STATUS_PDQ_INTR	0x10	/* PDQ Interrupt received */
#define	PFI_STATUS_DMA_ABORT	0x08	/* PDQ DMA Abort asserted */

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
#define REQ_BUFSIZ	512
#define RSP_BUFSIZ	512
#define UNSOL_BUFSIZ	512
#define CONSR_BUFSIZ	512
#define DESCR_BUFSIZ	(512*10)

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

/*
 * The number of descriptors to produce initially
 */
#define RCV_DESCR_PROD 		32	/* till index 31 */
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
 * The producer threshold is used for writing out the producer index
 * out onto the adapter. If the driver has not produced the number of
 * descriptors required this value is not written out until we have finished
 * processing all the packets.
 */
#define XMT_PROD_THRESH	6	
#define RCV_PROD_THRESH	8

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

struct queue_info {
	PI_DESCR_BLOCK *descr_blk;	/* has to be 8K aligned      */
	u_long phys_descr_blk;		/* the physical address	     */
	PI_CONSUMER_BLOCK *cons_blk;	/* has to be 64 byte aligned */
	u_long phys_cons_blk;		/* the physical address	     */
	PORT_REGS regs;
};
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
	sglist_t rsglp;			/* dma mapping sg-list ptr for mdata */
};

struct unsolbuf {
	void *bufaddr;			/* buffer address:UNSOL_BUFSIZ buffer */
	u_int phyaddr;			/* 32-bit physical address of above */
}; 

/*
 * Array to keep track of the virtual addresses that
 * we have allocated while transmitting mbuf's.
 */
struct xmtvaddr {
	struct mbuf *vaddr;
	sglist_t    tsglp;		/* dma mapping sg-list ptr for mbuf */
};

/*
 * For the commands.
 */
struct ftadebug {
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
	u_int  	ftareset;
        u_int  	ftaundrop;
        u_int  	ftasmtrcvd;
        u_int  	ftanombuf;
	u_int  	ftasmtdrop;
	u_int  	ftalarge;
	u_int  	ftasmall;
	u_int  	ftamiddle;
	u_int  	ftaxmtdone;
	u_int  	ftafairness;
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
 *
 * This data structure is arranged in an attempt to keep locks in their
 * own cache lines and not to mix up writeable objects with ones which 
 * are predominately read only.  Wherever things are rarely used, I used
 * them to pad between often referenced items in a feeble attempt to 
 * keep cache thrashing down to a minimum.
 */
struct	fta_softc {
	struct	    ether_driver is_ed;		/* FDDI driver */
#define	is_ac	    is_ed.ess_ac		/* FDDI common part */
#define	ztime	    is_ed.ess_ztime		/* Time since last zeroed */
#define	is_if	    is_ac.ac_if			/* network-visible interface */
#define	is_addr	    is_ac.ac_enaddr		/* hardware FDDI address */
#define is_ctrblk   is_ed.ess_ctrblk		/* counter block */

	vm_offset_t basereg;			/* base register  */
	vm_offset_t pfi_status;			/* handle for PFI Status reg */
	vm_offset_t pci_status;			/* handle for PCI Status reg */
	struct controller *ctlr;		/* back ref to ctlr struct */

	/* Info about registers, descriptor block, and consumer block */
	u_short     flags;			/* see below */
	struct      queue_info q_info;          

	/* Command request indicies and buffers */
	u_int	    l_cmdreqcompl_index;
	u_int	    l_cmdreqprod_index;
	void	    *cmd_req_buf;
	vm_offset_t cmd_req_phys;

	/* Command response indicies and buffers */
	u_int	    l_cmdrspcompl_index;
	u_int	    l_cmdrspprod_index;
	void	    *cmd_rsp_buf;
	vm_offset_t cmd_rsp_phys;

	/* Transmit buffers and indicies */
	simple_lock_data_t lk_fta_xmit;        	/* SMP lock for transmits only */
	u_int	    l_xmtprod_index;
	u_int	    l_xmtcompl_index;		
	struct 	    xmtvaddr xmt_vaddr[NPDQXMT];

	/* SMT indicies and buffers */
	u_int	    l_hostsmtcompl_index;	/* local copy of compl. index */
	u_int	    l_hostsmtprod_index;	/* local copy of prod. index */
	struct      rmbuf smtmbuf[NPDQHSMT];	/* SMT receive mbuf chain */

	/* Receive buffers and indicies */
	u_int	    l_rcvprod_index;
	u_int	    l_rcvcompl_index;
	struct      rmbuf rcvmbuf[NPDQRCV];	

	/* Unsolicted message queue indicies and buffers */
	u_int	    l_unsolcompl_index;
	u_int	    l_unsolprod_index;
	struct unsolbuf cntr_update;		/* used while updating cntrs */
	struct unsolbuf unsol_buf[NPDQUNSOL];	

/* Information which follows is rarely referenced */

	/* Bus specific setup information */
	struct	    pdqsw *pdqsw;		/* Turbo channel only */
	ihandler_id_t *hid;	           	/* handle from registering intr */

	/* Driver parameters */
	short	    rcv_mbufs_allocated;	/* mbufs allocated    */
	short	    rcv_mbufs_required;		/* required mbufs */
	short	    unsol_bufs_allocated;	/* unsol bufs allocated    */
	short	    unsol_bufs_required;	/* unsol bufs required */
	short	    error_recovery_flag;	/* flag to wake up a process */
	int	    halt_count;			/* # of times halted */
#define MAX_HALTS   20 

	/* Adapter specific information */
	int	    pdq_revision;		/* for book-keeping */
	u_char	    is_dpaddr[6];		/* Default phys. address */
	struct 	    char_values char_val;	/* default charecteristics */

	simple_lock_data_t lk_fta_softc;        /* SMP lock for driver/softc */

	/* Multicast address support */
	char	    is_multi[62][8];		/* multicast buffer */
	int	    is_muse[62];		/* number of entrys/slot */
	short	    is_inuse;			/* # of slots being used*/

	simple_lock_data_t lk_fta_regs; 	/* SMP lock for critical regs */   
	u_int	    index_val;	  		/* Value last written to type2prod reg */

	/* Address filters (multicast, unique, broadcast) */
	PI_ITEM_LIST filters[PI_CMD_FILTERS_SET_K_ITEMS_MAX];

	/* Error and other statistical counters */
	PI_CNTR_BLK                 	*ctrblk;	
	PI_CMD_SMT_MIB_GET_RSP      	*smt_mib_rsp;
	PI_CMD_FDDI_MIB_GET_RSP     	*fddi_mib_rsp;
	PI_CMD_STATUS_CHARS_GET_RSP 	*fta_status;
	PI_CMD_DEC_EXT_MIB_GET_RSP  	*dec_ext;	
	int	    fta_status_valid;
	int	    dec_ext_valid;
	struct	    dbeacon_info  dbeacon;

	struct      ftadebug  fta_debug;	/* debug counter/info */
};

/* Definitions for flags field in fta_softc */

#define DEFEA			0x0001
#define DEFPA			0x0002
#define TLASER			0x0004
#define CRE_MODULE		0x0008
#define BAD_CRE_MODULE		0x0010	
#define ATTACH_DONE		0x0020

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
#define mod_rev		fta_status->module_rev
#define firm_rev	fta_status->firmware_rev
/*
 * The states.
 */
#define driver_state		fta_debug.driver_state
#define prev_state		fta_debug.prev_state

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
#define rcv_data_blk		q_info.descr_blk->rcv_data
#define xmt_data_blk		q_info.descr_blk->xmt_data
#define smt_data_blk		q_info.descr_blk->smt_host
#define unsol_blk		q_info.descr_blk->unsol
#define cmd_rsp_blk		q_info.descr_blk->cmd_rsp
#define cmd_req_blk		q_info.descr_blk->cmd_req

#define einfo			unsol_report->info.report

#define fstc_second 	sc->fta_debug.fstat.fst_second
#define fstc_frame 	sc->fta_debug.fstat.fst_frame
#define fst_station_id 		sc->fta_debug.fta_status.fst_station_id
#define fst_station_type 	sc->fta_debug.fstat.fta_status_station_type
#define fstc_error 	sc->fta_debug.fstat.fst_error
#define fstc_lost 	sc->fta_debug.fstat.fst_lost
#define fstc_bytercvd 	sc->fta_debug.fstat.fst_bytercvd
#define fstc_bytesent 	sc->fta_debug.fstat.fst_bytesent
#define fstc_pdurcvd 	sc->fta_debug.fstat.fst_pdurcvd
#define fstc_pdusent 	sc->fta_debug.fstat.fst_pdusent
#define fstc_underrun 	sc->fta_debug.fstat.fst_underrun
#define fstc_sendfail 	sc->fta_debug.fstat.fst_sendfail
#define fstc_fcserror 	sc->fta_debug.fstat.fst_fcserror
#define fstc_fseerror 	sc->fta_debug.fstat.fst_fseerror
#define fstc_pdualig 	sc->fta_debug.fstat.fst_pdualig
#define fstc_pdulen 	sc->fta_debug.fstat.fst_pdulen
#define fstc_pduunrecog sc->fta_debug.fstat.fst_pduunrecog
#define fstc_overrun 	sc->fta_debug.fstat.fst_overrun
#define fstc_sysbuf 	sc->fta_debug.fstat.fst_sysbuf
#define fstc_userbuf 	sc->fta_debug.fstat.fst_userbuf
#define fstc_ringinit 	sc->fta_debug.fstat.fst_ringinit
#define fstc_ringinitrcv sc->fta_debug.fstat.fst_ringinitrcv
#define fstc_ringbeacon sc->fta_debug.fstat.fst_ringbeacon
#define fstc_dupaddfail sc->fta_debug.fstat.fst_dupaddfail
#define fstc_duptoken   sc->fta_debug.fstat.fst_duptoken
#define fstc_ringpurge 	sc->fta_debug.fstat.fst_ringpurge
#define fstc_bridgestrip sc->fta_debug.fstat.fst_bridgestrip
#define fstc_traceinit 	sc->fta_debug.fstat.fst_traceinit
#define fstc_tracerecv 	sc->fta_debug.fstat.fst_tracerecv
#define fstc_selftest 	sc->fta_debug.fstat.fst_selftest
#define fstc_mbytesent 	sc->fta_debug.fstat.fst_mbytesent
#define fstc_mpdusent 	sc->fta_debug.fstat.fst_mpdusent
#define fstc_mbytercvd 	sc->fta_debug.fstat.fst_mbytercvd
#define fstc_mpdurcvd 	sc->fta_debug.fstat.fst_mpdurcvd
#define fstc_mpduunrecog sc->fta_debug.fstat.fst_mpduunrecog
#define fstc_connection sc->fta_debug.fstat.fst_connection
#define fstc_tne_exp_rej sc->fta_debug.fstat.fst_tne_exp_rej
#define fstc_lct_rej  	sc->fta_debug.fstat.fst_lct_rej
#define fstc_lem_rej  	sc->fta_debug.fstat.fst_lem_rej
#define fstc_lem_events	sc->fta_debug.fstat.fst_lem_events
#define fstc_ebf_error  sc->fta_debug.fstat.fst_ebf_error
#define ftanreset	sc->fta_debug.ftareset	
#define ftanundrop	sc->fta_debug.ftaundrop
#define ftansmtrcvd	sc->fta_debug.ftasmtrcvd
#define ftansmtdrop	sc->fta_debug.ftasmtdrop
#define ftannombuf	sc->fta_debug.ftanombuf
#define ftanlarge	sc->fta_debug.ftalarge
#define ftanmiddle	sc->fta_debug.ftamiddle
#define ftansmall	sc->fta_debug.ftasmall
#define ftaconcat	sc->fta_debug.ftaconcat
#define ftaxmtdone	sc->fta_debug.ftaxmtdone
#define ftafairness	sc->fta_debug.ftafairness
#define ifqmaxlen_seen	sc->fta_debug.ifq_maxlen_seen

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
 * Defines for controlling number of packets transmitted
 */
#define UNLIM_PKTS		0
#define	ONE_PKT			1

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

extern	struct 	fta_softc fta_softc[];
extern	struct	controller *ftainfo[];
extern  struct pdqsw turbosw[];
extern char *fta_adapter_states[];
extern char *fta_halt_reasons[];
extern char *fta_unsol_station_events[];
extern char *fta_comp_status[];
extern char *fta_unsol_phy_events[];
extern char *fta_unsol_link_events[];

#else BINARY

#include "fta.h"

/*
 * For the Turbochannel.
 */
struct pdqsw turbosw [] = {
	"fta", TURBO_MODE_BASE 
};

char *fta_adapter_states[] = {
	"Reset",
	"Upgrade",
	"DMA Unavailable",
	"DMA Available",
	"Link Available",
	"Link Unavailable",
	"Halted",
	"Ring Member",
	"Unknown adapter state"
};

char *fta_comp_status[] = {
	"Success",
	"Failure",
	"Warning",
	"Loopback Mode Invalid",
	"Bad Item Code",
	"Invalid TVX Given",
	"Invalid TREQ Given",
	"Invalid Token",
	"Reason Unknown",
	"Reason Unknown",
	"Reason Unknown",
	"Reason Unknown",
	"No EOL Given",
	"Invalid Filter State",
	"Invalid Command Type",
	"Invalid Adapter State",
	"Invalid Ring Purger",
	"Invalid LEM Threshold A",
	"Loopback not supported",
	"Bad Flush Time",
	"Not Implemented",
	"Bad Configuration Policy",
	"Bad Station Action",
	"Bad MAC Action",
	"Bad Connection Policy",
	"MAC Loop Time Bad",
	"TB Max Bad",
	"LER Cuttoff Bad",
	"LER Alarm Bad",
	"MAC Paths Request Bad",
	"MAC T Request Bad",
	"Ring Purger Bad",
	"Token Time Bad",
	"No Such Entry",
	"T Notify Bad",
	"TR Max EXP Bad",
	"MAC Frame Error Thresh Bad",
	"MAX T Req Bad",
	"Full Duplex Enb/Dis Bad",
	"Response timed out",
	"Reason unknown"
};

char *fta_halt_reasons[] = {
	"Self Test Timeout",
	"Host bus parity error",
	"Host Directed Halt",
	"Firmware Fault",
	"Network Hardware Fault",
	"PC Trace",
	"DMA Error",
	"Image CRC Error",
	"Unknown"
};

char *fta_unsol_station_events[] = {
	"Self test failed",
	"PC Trace received",
	"Configuration change",
	"Event unknown"
};

char *fta_unsol_phy_events[] = {
	"LEM error monitor reject",
	"Elasticity buffer error",
	"LCT rejects",
	"Event unknown"
};

char *fta_unsol_link_events[] = {
	"Link transmit underrun",
	"Link transmit failure",
	"Block check error",
	"Frame status error",
	"Length error",
	"Bad destination",
	"Bad multicast destination",
	"Receive Overrun",
	"No link buffer",
	"No user buffer",
	"Link initialization initiated",
	"Ring initialized",
	"Ring beacon initiated",
	"Duplicate address failure",
	"Duplicate token found",
	"Ring purge error",
	"FCI strip error",
	"PC Trace initiated",
	"Directed beacon received",
	"Event unknown"
};

#if NFTA > 0
struct 	fta_softc fta_softc[NFTA];
struct	controller *ftainfo[NFTA];
#else 
struct 	fta_softc *fta_softc;
struct	controller *ftainfo;
#endif	
#endif	BINARY
