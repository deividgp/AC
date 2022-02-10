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
 * @(#)$RCSfile: kn300.h,v $ $Revision: 1.1.11.2 $ (DEC) $Date: 1997/06/27 17:26:35 $
 */
#ifndef _KN300_H 
#define _KN300_H 

#include <hal/cpuconf.h>	/* for memtest_t def.	*/
#include <machine/machparam.h>	/* for NPBG		*/

/* Define high temperature operating threshold for environmental monitoring */
#define KN300_HIGH_TEMP_THRESHOLD 40

/* 
 * Machine check structures, defines 
 */

/*
 * this is a per-cpu data structure for tracking machine check error handing
 */
struct kn300_error_counters {	/* this is a copy of elr_error_counters, */
				/* so that errlog.h doesn't need to be   */
				/* included here. */
    char error_counters[96];
};

/*
 * Error software flags struct
 *	-- indicates which error packets are attached 
 *	   to a binary error log
 */
struct kn300_elr_soft_flags {
    int		packet_revision;	/* Packet Revision, bits 0->31	*/
    int		rsvd;			/* Reserve 32 bits		*/
    u_long	error_flags;		/* 64-bits of Error flags	*/
};

/*
 * Defines for error_flags in kn300_elr_soft_flags struct
 */
#define KN300_ELR_SWFLAG_SYS_ENV_PRES		(1L<<10)

/* bits 32->35 are for IOD0->IOD3, respectively. */
#define KN300_ELR_SWFLAG_IOD_SUBPACKET_BASE	(1L<<32)
/* OR of 4 possible IOD subpacket flags */
#define KN300_ELR_SWFLAG_IOD_SUBPACKET_PRES \
	(KN300_ELR_SWFLAG_IOD_SUBPACKET_BASE | \
	 (KN300_ELR_SWFLAG_IOD_SUBPACKET_BASE << 1) | \
	 (KN300_ELR_SWFLAG_IOD_SUBPACKET_BASE << 2) | \
	 (KN300_ELR_SWFLAG_IOD_SUBPACKET_BASE << 3) )

/* bits 36->39 are for PCI0->PCI3, respectively. */
#define KN300_ELR_SWFLAG_PCI_SNAPSHOT_BASE	(1L<<36)
/* OR of 4 possible PCI bus subpacket flags */
#define KN300_ELR_SWFLAG_PCI_SNAPSHOT_PRES \
	(KN300_ELR_SWFLAG_PCI_SNAPSHOT_BASE | \
	 (KN300_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 1) | \
	 (KN300_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 2) | \
	 (KN300_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 3) )

#define KN300_ELR_SWFLAG_ESC_SUBPACKET_PRES	(1L<<40)


/*
 *  COMMON RAWHIDE CUD Module logout area.
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |          HW_REVISION          |          ACTIVE_CPUS          | :00
 * +-------------------------------+-------------------------------+
 * |                      SYSTEM_SERIAL_NUMBER (10 bytes)          | :08
 * +-------------------------------+---------------+               +
 * |                     RSVD                      |               | :10
 * +-------------------------------+-------------------------------+
 * |                      MODULE_SERIAL_NUMBER (10 bytes)          | :18
 * +-------------------------------+---------------+               +
 * |            RSVD               |    MOD_TYPE   |               | :20
 * +-------------------------------+-------------------------------+
 * |          SYSTEM_REV           |       DISABLE_RESOURCE        | :28
 * +-------------------------------+-------------------------------+
 */

#define _RCUD_SN_SIZE 10
#define _RCUD_RSVD1_SIZE 6
#define _RCUD_RSVD2_SIZE 6

struct kn300_elr_rcud_common_header {
    int 	active_cpus;		/* OS active CPU bit mask	*/
    int 	hw_rev;			/* HWRPB per cpu offset tbs	*/
    char 	sys_sn[_RCUD_SN_SIZE];	/* HWRPB per cpu offset	tbs	*/
    char 	rsvd1[_RCUD_RSVD1_SIZE];
    char 	mod_sn[_RCUD_SN_SIZE];	/* HWRPB offset 64		*/
    char 	rsvd2[_RCUD_RSVD2_SIZE];
    int		disable_resource;	/* tbd				*/
    int		system_rev;		/* HWRPB offset 96		*/
};

struct kn300_elr_iodsnap_hdr {
    u_long	base_addr;	/* base address of bridge, physical	*/
    u_int	whami;		/* WHOAMI reg.				*/
    u_int	rsvd0;
    u_int	pci_rev;	/* PCI rev. reg.			*/
    u_int	cap_ctrl;
    u_int	hae_mem;
    u_int	hae_io;
    u_int	int_ctl;
    u_int	int_reg;
    u_int	int_mask0;
    u_int	int_mask1;
    u_int	mc_err0;
    u_int	mc_err1;
    u_int	cap_err;
    u_int	sys_env;
    u_int	pci_err1;
    u_int	mdpa_stat;
    u_int	mdpa_syn;
    u_int	mdpb_stat;
    u_int	mdpb_syn;
    u_int	rsvd2;
    u_int	rsvd3;
    u_int	rsvd4;
};


/* A per-cpu data structure for handling, tracking machine checks */
struct kn300_mcheck_control {

    /* The following set of structure elements are used for		*/
    /* intentional machine checks, such as those caused by BADADDR IO	*/
    /* probing, probing memory (testpage code).				*/
    u_int 	mcheck_expected;	/* flag: we're probing.		*/
    u_int 	mcheck_occurred;	/* Number of mchecks during probe.  */
    u_int 	mcheck_action; 		/* Action to take with this mcheck: */
					/* recover, crash, retry	    */
    u_int	mcheck_retry;	/* Logout frames retry bit		*/
    long 	mcheck_return;	/* return to this PC expected mchecks	*/
    memtest_t 	mcheck_tp_active;	/* flag: testpage in progress	*/
    long  	mcheck_page;	/* page we're testing.			*/
    u_long 	mctl_probe_va;	/* VA being probed. 			*/

    /* This next set of elements are used to describe the machine 	*/
    /* check frame, built by PAL, and used in error parsing.		*/
    struct kn300_mchk_logout *mctl_pmchkf_va;	
				/* VA of PAL's mcheck logout area	*/
    u_long	mctl_pmchkf_pa;	/* PA ... 				*/
    u_long	mctl_pmchkf_len;/* size of logout area 			*/
    u_long	mctl_vector;	/* SCB Vector from PAL.			*/
    u_long	*mctl_regs;	/* ptr to registers saved by _XentInt	*/
				/* before calling machine check routine. */

    /* The next set of elements are used to maintain a running	*/
    /* count of error flags found set in the elr_soft_flags 	*/
    /* structure returned from each error parse. These values 	*/
    /* start at 0 at system boot time. 				*/
    struct kn300_error_counters error_670_counters;
    struct kn300_error_counters error_660_counters;
    struct kn300_error_counters error_630_counters;
    struct kn300_error_counters error_620_counters;

#ifdef KN300_ERRLOG_SCRATCH_BUF
    /* Fields for maintaining error logger scratch buffer.	*/
    struct kn300_mcheck_control_elbuf {
	char        elctl_buf[NBPG];	/* Error logging scratch buffer. */
	u_long      elctl_len;		/* Length of scratch buffer.	 */
	caddr_t     elctl_ptr;		/* Pointer to first free in	 */
					/* scratch buffer		 */
	u_long      elctl_rmng;		/* Remaining room in scratch buf */
    } mctl_elctl;
#endif

};

/* MACRO to get ptr to per-cpu mcheck_control struct */
#define KN300_MCHECK_CONTROL(cpu_id) kn300_mcheck_control[cpu_id]

/* Machine check code looked at in consprint routine */
#define EV5_corrected		0x00000086L

/* Bits 31:16 are KN300's 660,670 machine-check reason mask */
#define KN300_MCHECK_REASON_MASK 0x000000000000FF00L

/* 
 * RAWHIDE, KN300 Machine Check Logout Frames
 */

/* KN300 Un-corrected error log data structures
 */
struct el_kn300_uncorrected_frame_mcheck {
	struct el_common_EV5_logout_header elfmc_hdr;
	struct el_common_EV5_uncorrectable_mcheck elfmc_procdata;
};

/* KN300 corrected error log data structures
 */

/* RAWHIDE 630/620 Correctable Error Logout Frame 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |R|S|D|C|                                       | Frame Size    | :00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |      System area offset       |    CPU area offset            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |        MCHK Frame Rev         |  MCHK Reason mask             |
 * |-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           EI__STAT                            | 
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           EI__ADDR                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                            FIL_SYN                            | 
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                              ISR                              |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |        Sys. Env. registers    |             WHAMI		   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |             	Base Address of Bridge		           |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |             MCERR0		   |            PCI_REV	   	   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |            CAP_ERR	    	   |         	 MCERR1		   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |            MDPA_SYM	   |           MDPA_STAT	   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |            MDPB_SYM	   |           MDPB_STAT	   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |            reserved	   |            reserved	   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */

/*  RAWHIDE 630/620 correctable logout frame. This is the PAL's
 * 	logout frame, which becomes a piece of the correctable
 *	errorlog packet.
 */

struct el_kn300_620_630_sysdata {

/* Common area */
/* struct el_common_EV5_logout_header */
/* CPU specific area 
 * -- currently, a juggle of struct el_common_EV5_correctable_mcheck
 */
        u_long	ei_stat;    
        u_long	ei_addr;    
        u_long	fil_syn;    
        u_long	isr;        
/* System specific area */
	u_int	whami;
        u_int	sys_env;
	u_long	mcpcia_regs;
        u_int	pci_rev;      
        u_int	mcerr0;      
        u_int	mcerr1;     
        u_int	cap_err;     
        u_int	mdpa_stat;     
        u_int	mdpa_syn;     
        u_int	mdpb_stat;     
        u_int	mdpb_syn;     
        u_long	end_rsvd;     
};

struct el_kn300_620_630_logout_frame {
	struct el_common_EV5_logout_header elfcc_hdr;
/*	struct el_common_EV5_correctable_mcheck elfcc_procdata; */
	struct el_kn300_620_630_sysdata elfcc_sysdata;
};

#endif /* _KN300_H */
