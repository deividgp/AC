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
#pragma ident "@(#)$RCSfile: if_tra_data.c,v $ $Revision: 1.1.23.2 $ (DEC) $Date: 1995/10/25 19:58:32 $"
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
#include <netinet/if_trn.h>
#include <net/ether_driver.h>
#include <hal/cpuconf.h>
#include <io/common/devdriver.h>
#include <io/dec/uba/ubavar.h>
#include <io/dec/tc/tc.h>
#include <io/dec/eisa/eisa.h>
#include <io/dec/pci/pci.h>

#include <kern/thread.h>
#include <kern/sched_prim.h>

#include <io/dec/netif/if_trareg.h>


#define TRAIOSYNC()	mb()

/*
 * This the maximum number of transmit and receive parameter lists that are
 * preallocated.
 */
#define XMITSZ	32
#define RCVSZ	16

/*
 * For the OPEN command.
 *	The board has 512K of RAM of which 392K is useable
 *	for receive and transmit.
 */
#define BUFFER_SIZE	2048
#define XMIT_BMIN_CNT	10
#define XMIT_BMAX_CNT	20

#define	TRA_SCB_BUF_SIZE	8	/* roundoff from 6 -> 8 */
#define	TRA_SSB_BUF_SIZE	8

#define TRA_PID_BUF_SIZE	20	/* roundoff from 18 -> 20 */

#define TRA_OPEN_PB_SIZE	sizeof(OPEN_PARM_BLOCK)
#define	TRA_ERR_LOG_SIZE	sizeof(ERROR_LOG)

#define	TRA_XMT_RING_SIZE	(sizeof(XMIT_PARM_LIST) * (XMITSZ))
#define	TRA_RCV_RING_SIZE	(sizeof(RCV_PARM_LIST) * (RCVSZ))

/*
 * The error log table.
 * Used to maintain the counts by the driver.
 */

struct error_log_table {
    u_int	line_error;
    u_int	burst_error;
    u_int	ari_fci_error;
    u_int	lost_frame_error;
    u_int	rcv_congestion_error;		/* receive overrun */
    u_int	frame_copied_error;
    u_int	token_error;
    u_int	dma_bus_error;
    u_int	dma_parity_error;
};

struct tra_counts {
    u_short	ring_poll_error;
    u_short	transmit_timeout;
    u_short	board_reset;
    u_short	small_packet;
    u_short	access_pri_error;
    u_short	unenabled_mac_frame;
    u_short	illegal_frame_format;
    u_short	no_sysbuffers;
    u_short	signal_loss;
    u_short	hard_error;
    u_short	soft_error;
    u_short	xmit_beacon;
    u_short	xmit_fail;
    u_short	lobe_wire_fault;
    u_short	auto_rem_error;
    u_short	remove_received;
    u_short	counter_overflow;
    u_short	single_station;
    u_short	ring_recovery;
    u_short	dio_parity;
    u_short	read_timeout_abort;
    u_short	read_parity_error_abort;
    u_short	read_bus_error_abort;
    u_short	write_timeout_abort;
    u_short	write_parity_error_abort;
    u_short	write_bus_error_abort;
    u_short	illegal_opcode;
    u_short	parity_error;
    u_short	ram_data_error;
    u_short	ram_parity_error;
    u_short	ring_underrun;
    u_short	invalid_internal_interrupt;
    u_short	invalid_error_interrupt;
    u_short	invalid_xop_request;
    u_short	fatal_error;
    u_short	selftest_fail;
};

struct trastat {
    u_long  tra_bytercvd;           /* bytes received */
    u_long  tra_bytesent;           /* bytes sent */
    u_long  tra_pdurcvd;            /* data blocks received */
    u_long  tra_pdusent;            /* data blocks sent */
    u_long  tra_mbytercvd;          /* multicast bytes received */
    u_long  tra_mpdurcvd;           /* multicast blocks received */
    u_long  tra_mbytesent;          /* multicast bytes sent */
    u_long  tra_mpdusent;           /* multicast blocks sent */
    u_long  tra_pduunrecog;	    /* frame unrecognized */
};

struct scb_wait_q {
    SYSTEM_COMMAND_BLOCK       	*scb;
    struct scb_wait_q 		*next;
};

struct ssb_wait_q {
    SYSTEM_STATUS_BLOCK       	*ssb;
    struct ssb_wait_q 		*next;
};

struct xmit_list {
    XMIT_PARM_LIST	*list;		/* The xmit list seen by the adapter */
    u_int		physaddr;	/* The physical address of "*list" */
    struct xmit_list	*next_list;	/* next pointer - used by driver. */
    struct mbuf		*xmit_mbuf;	/* The address of the data buffer */
    sglist_t		tsglp[3];	/* SG-List pointers for this PARM */
    u_int		unload[3];	/* Whether or not to unload on intr */
};

#define XMIT_LIST struct xmit_list

struct rcv_list {
    RCV_PARM_LIST	*list;		/* The rcv list seen by adapter */
    u_int		physaddr;	/* lower portion of param phys. addr */
    struct rcv_list	*next_list;	/* next pointer */
    struct mbuf		*rcv_mbuf[3];	/* Addresses of mbufs used */
    sglist_t		rsglp[3];	/* SG-List pointers for above mbufs */
};

#define RCV_LIST struct rcv_list
#define TRN_MAC_HDR_SIZE 32	/* Size of mac header 14 + rif(18) */
/*
 * The following union is used for making our life easier in using the 
 * TMS380 chip which needs things in terms of 16 bits and in the network
 * byte order for which we use htons() whereever required. This ain't an 
 * chip designed to keep you sane ;-).
 * For example: ABCDEF01 will be broken into:
 *	value = ABCDEF01
 *	lo_short = htons(ABCD);
 *	hi_short = htons(EF01);
 *	
 */
union converter {
    struct {
	u_short lo_bytes;
	u_short	hi_bytes;
    } segment;
    u_int	value_int;
};

/*
 * This macro converts a host 32 bit value to the TMS format of 2 16
 * bit values.
 */
#define HOST_TO_TMS(value, hi, lo){\
        union converter convert;\
	convert.value_int = value;\
	lo = htons(convert.segment.lo_bytes);\
	hi = htons(convert.segment.hi_bytes);\
}

/*
 * This macro converts a TMS two 16 bit values to the HOST format of 32
 * bit value.
 */
#define TMS_TO_HOST(value, hi, lo){\
        union converter convert;\
	convert.segment.lo_bytes = ntohs(lo);\
	convert.segment.hi_bytes = ntohs(hi);\
	value = convert.value_int;\
}

#define MAXCMD	16
#define TRA_NMULTI 512

struct tra_multi {
    u_char  tra_multi_char[6];
};

/*
 * Token Ring software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * ds_if, which the routing code uses to locate the interface.
 */
struct	tra_softc {
	struct	   ether_driver is_ed;		/* driver */
#define	is_ac	is_ed.ess_ac			/* common part */
#define	ztime	is_ed.ess_ztime			/* Time since last zeroed */
#define	is_if	is_ac.ac_if			/* network-visible interface */
#define	is_addr	is_ac.ac_enaddr			/* hardware address */
	u_char	is_dpaddr[6];			/* default physical address */
	vm_offset_t basereg;			/* base register  */
	INIT_PARM_BLOCK   init_block;           /* initialization options */
	SYSTEM_COMMAND_BLOCK 	*scb;		/* system command block */
	SYSTEM_STATUS_BLOCK	*ssb;		/* system status block */
	SYSTEM_STATUS_BLOCK	ssb_copy;	/* copy of the ssb */
	XMIT_LIST		xmitlist[XMITSZ];/* The xmit list */
	XMIT_LIST		*xmit_ptr;	/* buffer avail. for xmit */
	XMIT_LIST		*xmit_done_ptr; /* buffer thats been xmitted */
	RCV_LIST		rcvlist[RCVSZ];/* The rcv. list */
	RCV_LIST		*rcv_ptr;	/* rcv buffer to process */
	OPEN_PARM_BLOCK		*open_block;	/* The open parm. block ptr */
	u_int			open_block_physaddr;	/* And its physaddr */
	ERROR_LOG		*error_log;	/* The error log ptr */
	u_int			error_log_physaddr;	/* And its physaddr */
	u_short			time_init_flag; 
	u_short			mac_open;	/* 1 == open; 0 == close */
	u_short			alloc_index;
	u_char			*product_id;	/* The product ID bufr ptr */
	u_int 			product_id_physaddr;	/* And its physaddr */
	u_int			grp_addr;	
	u_int			func_addr;	/* Functional address	*/
	u_short			ring_speed;	/* The current ring speed */
	u_short			last_speed;	/* The last ring speed */
	u_short			ring_status;	/* Ring status */
	u_short			ring_state;	/* Ring state */
	u_short			open_status;	/* Open status */
	u_short			etr;	  /* Early Token Release true/false */
	u_short			mon_cntd; /* Monitor Contender: true/false */
	u_short			pad_rif;	/* pad routing field */
	struct error_log_table	error_cnts;	/* The error log counters */
	struct tra_counts	count;		/* some local counts */
	struct trastat		tracount;	/* packet counters */
        thread_t                thread1;        /*  Error_log thread */
        thread_t                thread2;        /*  Error_recovery thread */
	vm_offset_t		error_log_read_flag;
	vm_offset_t		error_recovery_flag;
	u_int			error_recovery_init;
	u_int			ring_recovery_active;
	u_short			rcv_ring_size;
	decl_simple_lock_data(,	scb_clear_lock)
	u_short			scb_clear_flag;	/* Is SCB available? */
	struct scb_wait_q	*scb_q;
	struct ssb_wait_q	ssb_q[MAXCMD];
	u_long		 	tms_sifdat;
	u_long		 	tms_sifdat_inc;
	u_long		 	tms_sifadr1;
	u_long		 	tms_sifcmd_sts;
	u_long		 	tms_sifacl;
	u_long		 	tms_sifadr2;
	u_long		 	tms_sifadx;
	u_long		 	tms_dmalen;
	u_long		 	detra_csr0;
	u_long		 	detra_csr1;
	u_long			detra_csr2;
	u_long		 	detra_csr3;
	u_long			dw110_pcsr;
	u_long			dw110_intdma;
	u_long			dw300_cfg1;
	u_long                  racal_cfg;
	io_handle_t             racal_rom;
	u_char                  racal_bia[6];
	u_long                  tc_idcfg;
	u_long                  tc_csr;
	u_long                  tc_csrval;
	u_long                  tc_armval;
	u_long                  pci_misc;
	u_long                  pci_miscval;
	ihandler_id_t           *hid;
	u_int			*mac_location;
	u_int			mac_size;
	u_int			*ace_location;
	u_int			ace_size;
	u_int			*speed_location;
	u_int			speed_size;
	u_int			*error_location;
	u_int			error_size;
	ADAP_INTERNAL_POINTERS	adap_ptr;
	char                    *microcode_type;
	char                    *device_type;
	u_char                  si_rev[3];
	u_char                  micro_level[4];
	u_char			dev_type;
	u_int			dma_flags;
	u_int			maxmtu;
        struct tra_multi	is_multi[TRA_NMULTI];
        u_char                  is_muse[TRA_NMULTI];
    	u_int                   is_nmulti;
};

#ifdef BINARY
extern	struct 	tra_softc tra_softc[];
extern	struct	controller *trainfo[];
#else BINARY
#include "tra.h"
#if NTRA > 0
struct 	tra_softc tra_softc[NTRA];
struct	controller *trainfo[NTRA];
#else 
struct 	tra_softc *tra_softc;
struct	controller *trainfo;
#endif	
#endif	BINARY
