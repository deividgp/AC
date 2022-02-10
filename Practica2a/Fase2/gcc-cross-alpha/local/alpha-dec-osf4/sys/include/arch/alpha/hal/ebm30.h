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
 * @(#)$RCSfile: ebm30.h,v $ $Revision: 1.1.2.5 $ (DEC) $Date: 1999/03/16 21:55:14 $
 */

#ifndef __ARCH_ALPHA_HAL_EBM30_H
#define __ARCH_ALPHA_HAL_EBM30_H
#include <arch/alpha/hal/common_ev6_mcheck_hdr.h>

#include <hal/ebm10.h>
#undef	IS_AN_ISA_DEVICE

/*
 * EIGER can support upto 16 PCI slots and has upto 8 misc servermanagement
 * interrupts 
 */
#define EIGER_TOTAL_PCI_INTRS	((16 * 4) + 8)

/* 
 * Define high temperature operating threshold for 
 * environmental monitoring 
 */
#define EIGER_HIGH_TEMP_THRESHOLD 50
#define EIGER_TEMP_GREEN	45
#define EIGER_TEMP_YELLOW	48

/*
 * Server management related definitions
 */
#define	EBM30_SRVMGMT_CTR   0xc0000002	/* Server Management Register.	*/
#define EBM30_SRVMGMT_SR0   0xc0000004	/* Server Management status reg 0 */
#define EBM30_SRVMGMT_SR1   0xc0000005	/* Server Management status reg 1 */
#define EBM30_SRVMGMT_ESR   0xc0000006  /* Environment status register */
#define	EBM30_SRVMGMT_CLRDC 0xc0000012  /* Clear Detect SYS DC Bad */
#define	EBM30_SRVMGMT_CLRTW 0xc0000013  /* Clear Detect Temp Warning */
#define	EBM30_SRVMGMT_CLRTF 0xc0000014   /* Clear Detect Temp Failure */

/* bit defines for Server management Control register */
#define EBM30_SMCR_SOFT_PWRDN	0x80
#define EBM30_SMCR_RESERVED_1	0x40
#define EBM30_SMCR_WATCH_BISC	0x20
#define EBM30_SMCR_WATCH_ENA	0x10
#define EBM30_SMCR_CPU3_PWRDN	0x08
#define EBM30_SMCR_CPU2_PWRDN	0x04
#define EBM30_SMCR_CPU1_PWRDN	0x02
#define EBM30_SMCR_CPU0_PWRDN	0x01


/* bit defines for Server management status register 0 */
#define EBM30_SMR0_CPU3_DCENA	0x8
#define EBM30_SMR0_CPU2_DCENA	0x4
#define EBM30_SMR0_CPU1_DCENA	0x2
#define EBM30_SMR0_CPU0_DCENA	0x1

/* bit defines for Server management status register 1 */
#define EBM30_SMR1_PS1_PRES	0x80
#define EBM30_SMR1_PS0_PRES	0x40
#define EBM30_SMR1_PS1_DCENA	0x20
#define EBM30_SMR1_PS0_DCENA	0x10
#define EBM30_SMR1_DET_NODC	0x8
#define EBM30_SMR1_DET_SYSPWR	0x4
#define EBM30_SMR1_DET_OCPHLT	0x2
#define EBM30_SMR1_SYS_RESET	0x1

/* bit defines for Environment Status Register */
#define EBM30_SMESR_CPU3_FAIL	0x80
#define EBM30_SMESR_CPU2_FAIL	0x40
#define EBM30_SMESR_CPU1_FAIL	0x20
#define EBM30_SMESR_CPU0_FAIL	0x10
#define EBM30_SMESR_DET_TMPFL	0x8
#define EBM30_SMESR_DET_TMPWN	0x4
#define EBM30_SMESR_PS1_FAIL	0x2
#define EBM30_SMESR_PS0_FAIL	0x1


/* 
 * Machine check structures, defines 
 */

/*
 * System Specific Machine Check Error Codes
 */
#define EBM30_MCHK_SYS_UNCORR	0x202
#define EBM30_MCHK_SYS_CORERR	0x204
#define EBM30_MCHK_SYS_EVENT	0x206
/*
 * Per-cpu data structure for tracking machine check error handing
 */
struct ebm30_error_counters {	/* this is a copy of elr_error_counters, */
				/* so that errlog.h doesn't need to be   */
				/* included here. */
    char error_counters[96];
};

/*
 * Error software flags struct
 *	-- indicates which error packets are attached 
 *	   to a binary error log
 */
struct ebm30_elr_soft_flags {
    int		packet_revision;	/* Packet Revision, bits 0->31	*/
    int		rsvd;			/* Reserve 32 bits		*/
    u_long	error_flags;		/* 64-bits of Error flags	*/
};

/*
 * Defines for error_flags in ebm30_elr_soft_flags struct
 */
#define EBM30_ELR_SWFLAG_SYS_ENV_PRES		(1L<<10)
#define EBM30_ELR_SWFLAG_MEM_SUBPACKET_PRES	(1L<<11)
/* CChip & Dchip Subpacket Present flags	*/
/* -- bit 8 for Cchip; bits 23:16 for 8 possible Dchips	*/
#define EBM30_ELR_SWFLAG_CCHIP_SUBPACKET_PRES	(1L<<8) 
#define EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE	(1L<<16) 

/* OR of 8 possible DChip subpacket flags	*/
#define EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_PRES \
	(EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE | \
	 (EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 1) | \
	 (EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 2) | \
	 (EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 3) | \
	 (EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 4) | \
	 (EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 5) | \
	 (EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 6) | \
	 (EBM30_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 7) )

/* bits 33:32 are for PChip1:0, respectively.	*/
/* note: PPlus version considered a Pchip	*/
#define EBM30_ELR_SWFLAG_PCHIP_SUBPACKET_BASE	(1L<<32)

/* OR of 2 possible PChip subpacket flags	*/
#define EBM30_ELR_SWFLAG_PCHIP_SUBPACKET_PRES \
	(EBM30_ELR_SWFLAG_PCHIP_SUBPACKET_BASE | \
	 (EBM30_ELR_SWFLAG_PCHIP_SUBPACKET_BASE << 1) )


/* bits 36->39 are for PCI0->PCI3, respectively. */
#define EBM30_ELR_SWFLAG_PCI_SNAPSHOT_BASE	(1L<<36)

/* OR of 4 possible PCI bus subpacket flags */
#define EBM30_ELR_SWFLAG_PCI_SNAPSHOT_PRES \
	(EBM30_ELR_SWFLAG_PCI_SNAPSHOT_BASE | \
	 (EBM30_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 1) | \
	 (EBM30_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 2) | \
	 (EBM30_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 3) )


/* 
 * Cypress, multi-function chip subpacket; contains:
 *	- ISA (SIO)
 *	- IDE 0
 *	- IDE 1
 *	- USB
 *	- Sys. Mgmt
 *	- Pwr. Mgmt
 *	- tbd
 *	- tbd
 *	- tbd
 */
#define EBM30_ELR_SWFLAG_CYPRESS_SUBPACKET_PRES	(1L<<40)


/*
 *  COMMON EV6-TSUNAMI Module logout area.
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
 * |                     RSVD2                     |               | :20
 * +-------------------------------+-------------------------------+
 * |          SYSTEM_REV           |       DISABLE_RESOURCE        | :28
 * +-------------------------------+-------------------------------+
 */

#define _EBM30_SYS_SN_SIZE 10
#define _EBM30_SYS_RSVD1_SIZE 6
#define _EBM30_SYS_RSVD2_SIZE 6

struct ebm30_elr_sys_common_header {
    int 	active_cpus;		/* OS active CPU bit mask	*/
    int 	hw_rev;			/* HWRPB per cpu offset tbs	*/
    char 	sys_sn[_EBM30_SYS_SN_SIZE]; /* HWRPB per cpu offset tbs	*/
    char 	rsvd1[_EBM30_SYS_RSVD1_SIZE];
    char 	mod_sn[_EBM30_SYS_SN_SIZE]; /* HWRPB offset 64		*/
    char 	rsvd2[_EBM30_SYS_RSVD2_SIZE];
    int		disable_resource;	/* tbd				*/
    int		system_rev;		/* HWRPB offset 96		*/
};


#ifdef KERNEL
/* A per-cpu data structure for handling, tracking machine checks */
struct ebm30_mcheck_control {

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
    struct ebm30_mchk_logout *mctl_pmchkf_va;	
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
    struct ebm30_error_counters error_670_counters;
    struct ebm30_error_counters error_660_counters;
    struct ebm30_error_counters error_630_counters;
    struct ebm30_error_counters error_620_counters;

};
#endif

/* Bits 31:16 are EBM30's 660,670 machine-check reason mask */
#define EBM30_MCHECK_REASON_MASK 0x000000000000FF00L

/* 
 * TSUNAMI, EBM30 Machine Check Logout Frames
 */
#define EBM30_MCHK_SUMM_P0ERR	0x1
#define EBM30_MCHK_SUMM_P1ERR	0x2
#define EBM30_MCHK_SUMM_MEMERR	0x4


/*
 * Tsunami specific portion of the machine check logout 
 * frame. This is used for both correctable and 
 * uncorrectable errors
 */
struct elf_dc104x_error_data {
        u_long  syserr_summary_flag;
        u_long	syserr_dir;
	u_long	syserr_misc;
	u_long	syserr_p0_perror;
	u_long	syserr_p1_perror;
};


/*
 * Eiger specific data fields tacked on at the end of Tsunami fields
 */
struct elf_eiger_specific_data {
    u_long	sys_ia_conf;	/* Interrupt Accelerator Configuration */
    u_long	sys_ia_intreg1;	/* Interrupt Accelerator Register 1 */
    u_long	sys_ia_intreg2;
    u_long	sys_ia_intreg3;
    u_long	sys_ia_intreg4;
    u_long	sys_lm78_stat;	/* LM78 Register */
    u_long	sys_wd_sm_reg;	/* Watchdog & server manager register */
};

/* 
 * Tsunami Specific structure for logout frame on 
 * system events
 */ 
struct el_ebm30_680_logout_frame {
        struct	elf_common_ev6_logout_header	hdr;
        u_long  sysevt_summary_flag;
        u_long  sysevt_dir;
/****	Eiger does not have following registers
        u_long  sysevt_smir;
        u_long  sysevt_cpuir;
        u_long  sysevt_psir;
        u_long  sysevt_reserved[6];
****/
	u_long	sysevt_lm78_stat;
	u_long	sysevt_wd_sm_reg;  /* Watchdog & server manager register */
};


/* EBM30 Un-corrected error log data structures
 */
struct el_ebm30_660_670_logout_frame {
  	struct	elf_common_ev6_logout_header	hdr;
	struct  elf_common_ev6_uncorr_data 	procdata;
	struct	elf_dc104x_error_data 		elfmc_sysdata;
	struct	elf_eiger_specific_data		elfmc_eigerdata;
};

/* EBM30 corrected error log data structures
 */

/*  TSUNAMI 630/620 correctable logout frame. This is the PAL's
 * 	logout frame, which becomes a piece of the correctable
 *	errorlog packet.
 */

struct el_ebm30_620_630_logout_frame {
  	struct	elf_common_ev6_logout_header	hdr;
	struct  elf_common_ev6_corr_data 	procdata;
	struct	elf_dc104x_error_data 		elfcc_sysdata;
	struct	elf_eiger_specific_data		elfcc_eigerdata;
};

/*
 * Structures related to extended error packets 
 * that need to be logged for DECanalyze
 */

#define	EBM30_EL_TSUNAMI_CLASS	12
struct el_ebm30_packet_hdr {
  short	packt_length;
  short	packt_class;
  short	packt_type;
  short packt_rev;
};

#define	EBM30_EL_BLKMEM_LNGTH	0x10
#define	EBM30_EL_BLKMEM_TYPE	4
#define	EBM30_EL_BLKMEM_REV	1


struct el_ebm30_block_mem_packet {
  struct el_ebm30_packet_hdr hdr;
  u_char 	dpr80[8];
};

#define	EBM30_EL_TSUMEM_LNGTH	0x38
#define	EBM30_EL_TSUMEM_TYPE	7
#define	EBM30_EL_TSUMEM_REV	1

struct el_ebm30_tsunami_mem_packet {
  struct el_ebm30_packet_hdr hdr;
  u_long	aar0;
  u_long	aar1;
  u_long	aar2;
  u_long	aar3;
  u_long	p0_pctl;
  u_long	p1_pctl;
};

#define	EBM30_EL_PCHIP_LNGTH	0x78
#define	EBM30_EL_PCHIP_CLASS	12
#define	EBM30_EL_PCHIP0_TYPE	5
#define	EBM30_EL_PCHIP1_TYPE	6
#define	EBM30_EL_PCHIP2_TYPE	8
#define	EBM30_EL_PCHIP3_TYPE	9
#define	EBM30_EL_PCHIP_REV	1

struct el_ebm30_pchip_packet {
  struct el_ebm30_packet_hdr hdr;
  u_long	pctl;
  u_long	perrmask;
  u_long	wsba0;
  u_long	wsba1;
  u_long	wsba2;
  u_long	wsba3;
  u_long	wsm0;
  u_long	wsm1;
  u_long	wsm2;
  u_long	wsm3;
  u_long	tba0;
  u_long	tba1;
  u_long	tba2;
  u_long	tba3;
};

/* definitions needed for Termination packet */
#define	EBM30_EL_TERM_LNGTH	8
#define EBM30_EL_TERM_CLASS	0
#define	EBM30_EL_TERM_TYPE	0
#define	EBM30_EL_TERM_REV	1


/*
 * Known members of the Tsunami/Typhoon family
 */
#define	EBM30_MEMBER_DP264	1
#define	EBM30_MEMBER_WARHOL	2
#define	EBM30_MEMBER_WINDJAMMER	3
#define	EBM30_MEMBER_MONET	4
#define	EBM30_MEMBER_CLIPPER	5
#define EBM30_MEMBER_GOLDRUSH	6

#define MEMBER_ID_SHIFT 10
#define MEMBER_ID 0xfc00L

/*
 * Server management definitions needed for Goldrush
 */
#define EBM30_I2C_BASE_ADDR_OFFSET 		0xFFF80000
#define EBM30_ESC_BASE_ADDR			0x80
/*
 * Server Management definitions needed for Clipper
 */
#define EBM30_DPRAM_INDEX		0x40
#define	EBM30_DUAL_PORT_RAM_ADDR	0x80140000000L
/* Base Address of memory config info */
#define EBM30_DPRAM_MEM_CONFIG			(0x80*0x40)


/* power supply status registers */
#define	EBM30_DPRAM_BLK0_PS_STATUS		(0x90*0x40)
#define	EBM30_DPRAM_BLK1_PS_STATUS		(0x91*0x40)
#define	EBM30_DPRAM_BLK2_PS_STATUS		(0x92*0x40)

/* cpu regulator status registers */
#define	EBM30_DPRAM_CPU0_PS_STATUS		(0x94*0x40)
#define	EBM30_DPRAM_CPU1_PS_STATUS		(0x95*0x40)
#define	EBM30_DPRAM_CPU2_PS_STATUS		(0x96*0x40)
#define	EBM30_DPRAM_CPU3_PS_STATUS		(0x97*0x40)

#define EBM30_DPRAM_FAN_STATUS			(0xa0*0x40)

/* Temperature for CPU's */
#define	EBM30_DPRAM_CPU0_TEMP			(0x98*0x40)
#define	EBM30_DPRAM_CPU1_TEMP			(0x99*0x40)
#define	EBM30_DPRAM_CPU2_TEMP			(0x9a*0x40)
#define	EBM30_DPRAM_CPU3_TEMP			(0x9b*0x40)

/* Temperature for Zones */
#define	EBM30_DPRAM_ZONE0_TEMP			(0x9c*0x40)
#define	EBM30_DPRAM_ZONE1_TEMP			(0x9d*0x40)
#define	EBM30_DPRAM_ZONE2_TEMP			(0x9e*0x40)
#define	EBM30_DPRAM_ZONE3_TEMP			(0x9f*0x40)


#endif /* __ARCH_ALPHA_HAL_EBM30_H */
