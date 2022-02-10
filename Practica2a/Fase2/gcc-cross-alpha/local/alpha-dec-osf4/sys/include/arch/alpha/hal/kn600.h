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
#pragma ident "@(#)$RCSfile: kn600.h,v $ $Revision: 1.1.9.6 $ (DEC) $Date: 1999/03/16 21:52:49 $"

#ifndef __ARCH_ALPHA_HAL_KN600_H 
#define __ARCH_ALPHA_HAL_KN600_H 
#include <arch/alpha/hal/common_ev6_mcheck_hdr.h>

/* 
 * Define high temperature operating threshold for 
 * environmental monitoring 
 */
#define KN600_HIGH_TEMP_THRESHOLD       40
#define KN600_HIGH_TEMP_CLIPPER         50
#define KN600_HIGH_TEMP_GOLDRUSH        55

#define KN600_GET_HIGH_TEMP_THRESHOLD( member_id, data_ptr ) {  \
   switch( member_id ) {                                        \
   case KN600_MEMBER_CLIPPER:                                   \
      *data_ptr = KN600_HIGH_TEMP_CLIPPER;                      \
      break;                                                    \
   case KN600_MEMBER_GOLDRUSH:                                  \
   case KN600_MEMBER_WEBBRICK:                                  \
      *data_ptr = KN600_HIGH_TEMP_GOLDRUSH;                     \
      break;                                                    \
   default:                                                     \
      *data_ptr = KN600_HIGH_TEMP_THRESHOLD;                    \
   }                                                            \
}

/*
 * Define for the number of seconds it might take the Clipper
 * RMC/SPC to respond to a software powerdown request.
 */
#define KN600_CLIPPER_OS_POWERDOWN       60

/* bit defines for Server Management Control Register */
#define KN600_SMCR_MASK                 0xbf
#define KN600_SMCR_SOFT_PWRDN   	0x80
#define KN600_SMCR_RESERVED_1	        0x40
#define KN600_SMCR_WATCH_BISC	        0x20
#define KN600_SMCR_WATCH_ENA	        0x10
#define KN600_SMCR_CPU3_PWRDN	        0x08
#define KN600_SMCR_CPU2_PWRDN	        0x04
#define KN600_SMCR_CPU1_PWRDN	        0x02
#define KN600_SMCR_CPU0_PWRDN	        0x01

/* bit defines for Server Management Information Register */
#define KN600_SMIR_MASK                 0xff
#define KN600_SMIR_SYS_RST_L	        0x80
#define KN600_SMIR_PCI1_RST_L	        0x40
#define KN600_SMIR_PCI0_RST_L	        0x20
#define KN600_SMIR_TEMP_FAIL	        0x10
#define KN600_SMIR_TEMP_WARN	        0x08
#define KN600_SMIR_SYS_DC_FAIL          0x04
#define KN600_SMIR_RMC_HALT_L	        0x02
#define KN600_SMIR_SYS_PS_FAIL	        0x01

/* bit defines for CPU Information Register */
#define KN600_CPUIR_MASK                0xff
#define KN600_CPUIR_CPU_FAIL_MASK       0xf0
#define KN600_CPUIR_CPU3_REG_FAIL	0x80
#define KN600_CPUIR_CPU2_REG_FAIL	0x40
#define KN600_CPUIR_CPU1_REG_FAIL	0x20
#define KN600_CPUIR_CPU0_REG_FAIL	0x10
#define KN600_CPUIR_CPU3_REG_ENA        0x08
#define KN600_CPUIR_CPU2_REG_ENA        0x04
#define KN600_CPUIR_CPU1_REG_ENA        0x02
#define KN600_CPUIR_CPU0_REG_ENA        0x01

/* bit defines for Power Supply Information Register */
#define KN600_PSIR_FAIL_MASK            0x70
#define KN600_PSIR_ENABLE_MASK          0x07
#define KN600_PSIR_PS2_FAIL     	0x40
#define KN600_PSIR_PS1_FAIL     	0x20
#define KN600_PSIR_PS0_FAIL     	0x10
#define KN600_PSIR_PS2_ENA     	        0x04
#define KN600_PSIR_PS1_ENA     	        0x02
#define KN600_PSIR_PS0_ENA           	0x01

/* bit defines for System_Doors */
#define KN600_SYSDOORS_MASK             0x0e
#define KN600_SYSDOORS_PCI              0x08
#define KN600_SYSDOORS_FAN              0x04
#define KN600_SYSDOORS_CPU              0x02

/* bit defines for System_Temperature_Warning */
#define KN600_SYSTEMP_MASK              0x7f
#define KN600_SYSTEMP_ZONE_2            0x40
#define KN600_SYSTEMP_ZONE_1            0x20
#define KN600_SYSTEMP_ZONE_0            0x10
#define KN600_SYSTEMP_CPU3              0x08
#define KN600_SYSTEMP_CPU2              0x04
#define KN600_SYSTEMP_CPU1              0x02
#define KN600_SYSTEMP_CPU0              0x01

/* bit defines for System_Fan_Control_Fault */
#define KN600_SYSFAN_MASK               0xf3f
#define KN600_SYSFAN_PCI_REDUCE         0x800
#define KN600_SYSFAN_PCI_MAX_SPIN       0x400
#define KN600_SYSFAN_CPU_REDUCE         0x200
#define KN600_SYSFAN_CPU_MAX_SPIN       0x100
#define KN600_SYSFAN_6_CTL_FAULT        0x020
#define KN600_SYSFAN_5_CTL_FAULT        0x010
#define KN600_SYSFAN_4_CTL_FAULT        0x008
#define KN600_SYSFAN_3_CTL_FAULT        0x004
#define KN600_SYSFAN_2_CTL_FAULT        0x002
#define KN600_SYSFAN_1_CTL_FAULT        0x001

/* bit defines for System_Power_Supply/Temp/Fan_Fault LM78_ISR */
#define KN600_LM78_MASK                 0xdf00df04ffL
#define KN600_LM78_FAN_FAIL_MASK        0xc000c000c0L
#define KN600_LM78_PS_FAIL_MASK         0x0f000f040fL
#define KN600_LM78_SYSFAN_6_FAIL        0x8000000000L   /* bit 39 */
#define KN600_LM78_SYSFAN_3_FAIL        0x4000000000L   /* bit 38 */
#define KN600_LM78_TEMP_ZONE_2_FAIL     0x1000000000L   /* bit 36 */
#define KN600_LM78_CPU3_VIO_1_5         0x0800000000L   /* bit 35 */
#define KN600_LM78_CPU3_VCORE_2         0x0400000000L   /* bit 34 */
#define KN600_LM78_CPU2_VIO_1_5         0x0200000000L   /* bit 33 */
#define KN600_LM78_CPU2_VCORE_2         0x0100000000L   /* bit 32 */
#define KN600_LM78_SYSFAN_5_FAIL        0x0000800000L   /* bit 23 */
#define KN600_LM78_SYSFAN_4_FAIL        0x0000400000L   /* bit 22 */
#define KN600_LM78_TEMP_ZONE_1_FAIL     0x0000100000L   /* bit 20 */
#define KN600_LM78_CPU1_VIO_1_5         0x0000080000L   /* bit 19 */
#define KN600_LM78_CPU1_VCORE_2         0x0000040000L   /* bit 18 */
#define KN600_LM78_CPU0_VIO_1_5         0x0000020000L   /* bit 17 */
#define KN600_LM78_CPU0_VCORE_2         0x0000010000L   /* bit 16 */
#define KN600_LM78_12V_TOLERANCE        0x0000000400L   /* bit 10 */
#define KN600_LM78_SYSFAN_2_FAIL        0x0000000080L   /* bit 7  */
#define KN600_LM78_SYSFAN_1_FAIL        0x0000000040L   /* bit 6  */
#define KN600_LM78_CPU_TEMP_FAIL        0x0000000020L   /* bit 5  */
#define KN600_LM78_TEMP_ZONE_0_FAIL     0x0000000010L   /* bit 4  */
#define KN600_LM78_VTERM_TOLERANCE      0x0000000008L   /* bit 3  */
#define KN600_LM78_PS_12V_TOLERANCE     0x0000000004L   /* bit 2  */
#define KN600_LM78_PS_5V_TOLERANCE      0x0000000002L   /* bit 1  */
#define KN600_LM78_PS_3_3V_TOLERANCE    0x0000000001L   /* bit 0  */


/* 
 * Machine check structures, defines 
 */

/*
 * System Specific Machine Check Error Codes
 */
#define KN600_MCHK_SYS_UNCORR	0x202
#define KN600_MCHK_SYS_CORERR	0x204
#define KN600_MCHK_SYS_EVENT	0x206
/*
 * Per-cpu data structure for tracking machine check error handing
 */
struct kn600_error_counters {	/* this is a copy of elr_error_counters, */
				/* so that errlog.h doesn't need to be   */
				/* included here. */
    char error_counters[96];
};

/*
 * Error software flags struct
 *	-- indicates which error packets are attached 
 *	   to a binary error log
 */
struct kn600_elr_soft_flags {
    int		packet_revision;	/* Packet Revision, bits 0->31	*/
    int		rsvd;			/* Reserve 32 bits		*/
    u_long	error_flags;		/* 64-bits of Error flags	*/
};

/*
 * Defines for error_flags in kn600_elr_soft_flags struct
 */
#define KN600_ELR_SWFLAG_SYS_ENV_PRES		(1L<<10)
#define KN600_ELR_SWFLAG_MEM_SUBPACKET_PRES	(1L<<11)
/* CChip & Dchip Subpacket Present flags	*/
/* -- bit 8 for Cchip; bits 23:16 for 8 possible Dchips	*/
#define KN600_ELR_SWFLAG_CCHIP_SUBPACKET_PRES	(1L<<8) 
#define KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE	(1L<<16) 

/* OR of 8 possible DChip subpacket flags	*/
#define KN600_ELR_SWFLAG_DCHIP_SUBPACKET_PRES \
	(KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE | \
	 (KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 1) | \
	 (KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 2) | \
	 (KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 3) | \
	 (KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 4) | \
	 (KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 5) | \
	 (KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 6) | \
	 (KN600_ELR_SWFLAG_DCHIP_SUBPACKET_BASE << 7) )

/* bits 33:32 are for PChip1:0, respectively.	*/
/* note: PPlus version considered a Pchip	*/
#define KN600_ELR_SWFLAG_PCHIP_SUBPACKET_BASE	(1L<<32)

/* OR of 2 possible PChip subpacket flags	*/
#define KN600_ELR_SWFLAG_PCHIP_SUBPACKET_PRES \
	(KN600_ELR_SWFLAG_PCHIP_SUBPACKET_BASE | \
	 (KN600_ELR_SWFLAG_PCHIP_SUBPACKET_BASE << 1) )


/* bits 36->39 are for PCI0->PCI3, respectively. */
#define KN600_ELR_SWFLAG_PCI_SNAPSHOT_BASE	(1L<<36)

/* OR of 4 possible PCI bus subpacket flags */
#define KN600_ELR_SWFLAG_PCI_SNAPSHOT_PRES \
	(KN600_ELR_SWFLAG_PCI_SNAPSHOT_BASE | \
	 (KN600_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 1) | \
	 (KN600_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 2) | \
	 (KN600_ELR_SWFLAG_PCI_SNAPSHOT_BASE << 3) )


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
#define KN600_ELR_SWFLAG_CYPRESS_SUBPACKET_PRES	(1L<<40)


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

#define _KN600_SYS_SN_SIZE 10
#define _KN600_SYS_RSVD1_SIZE 6
#define _KN600_SYS_RSVD2_SIZE 6

struct kn600_elr_sys_common_header {
    int 	active_cpus;		/* OS active CPU bit mask	*/
    int 	hw_rev;			/* HWRPB per cpu offset tbs	*/
    char 	sys_sn[_KN600_SYS_SN_SIZE]; /* HWRPB per cpu offset tbs	*/
    char 	rsvd1[_KN600_SYS_RSVD1_SIZE];
    char 	mod_sn[_KN600_SYS_SN_SIZE]; /* HWRPB offset 64		*/
    char 	rsvd2[_KN600_SYS_RSVD2_SIZE];
    int		disable_resource;	/* tbd				*/
    int		system_rev;		/* HWRPB offset 96		*/
};


#ifdef KERNEL
/* A per-cpu data structure for handling, tracking machine checks */
struct kn600_mcheck_control {

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
    struct kn600_mchk_logout *mctl_pmchkf_va;	
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
    struct kn600_error_counters error_670_counters;
    struct kn600_error_counters error_660_counters;
    struct kn600_error_counters error_630_counters;
    struct kn600_error_counters error_620_counters;

};
#endif

/* Bits 31:16 are KN600's 660,670 machine-check reason mask */
#define KN600_MCHECK_REASON_MASK 0x000000000000FF00L

/* 
 * TSUNAMI, KN600 Machine Check Logout Frames
 */
#define KN600_MCHK_SUMM_P0ERR	0x1
#define KN600_MCHK_SUMM_P1ERR	0x2
#define KN600_MCHK_SUMM_MEMERR	0x4


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
 * Tsunami Specific structure for logout frame on 
 * system environmental events
 */ 
struct el_kn600_680_logout_frame {

        struct	elf_common_ev6_logout_header	hdr;

        /*
         * NOTE: It is very important that all elements
         *       of this union define structures of the
         *       same size (otherwise error logging will
         *       break). There must be 11 u_long's.
         */
        union {

            struct {
                u_long  swerr_summary_flags;
                u_long  cchip_dir;
                u_long  tig_smir;
                u_long  tig_cpuir;
                u_long  tig_psir;
                u_long  lm78_isr;
                u_long  sys_doors;
                u_long  sys_temp_warning;
                u_long  sys_fan_fault;
                u_long  reserved[2];
            } clipper;

            struct {
                u_long  swerr_summary_flags;
                u_long  cchip_dir;
                u_long  fan_temp_ps_func;
                u_long  fan_fail_ps;
                u_long  reserved[7];
            } goldrush_webbrick;

        } sysevt; /* union */
};

/*
 * Goldrush/WebBrick environmental event logout frame bit defines
 */
#define KN600_ENV_FUNC_TEMP_OK          0x01
#define KN600_ENV_FUNC_SYSFAN_OK        0x02
#define KN600_ENV_FUNC_CPUFANS_OK       0x08
#define KN600_ENV_FUNC_FAN_TRAY_FAIL    0x10
#define KN600_ENV_FUNC_PS0_OK           0x20
#define KN600_ENV_FUNC_PS1_OK           0x40

#define KN600_ENV_FAIL_CSFAN1           0x02
#define KN600_ENV_FAIL_PS1_PRESENT      0x10
#define KN600_ENV_FAIL_CSFAN0           0x20
#define KN600_ENV_FAIL_PS0_PRESENT      0x80

/*
 * KN600 Un-corrected error log data structures
 */
struct el_kn600_660_670_logout_frame {
  	struct	elf_common_ev6_logout_header	hdr;
	struct  elf_common_ev6_uncorr_data 	procdata;
	struct	elf_dc104x_error_data 		elfmc_sysdata;
};

/* KN600 corrected error log data structures
 */

/*  TSUNAMI 630/620 correctable logout frame. This is the PAL's
 * 	logout frame, which becomes a piece of the correctable
 *	errorlog packet.
 */

struct el_kn600_620_630_logout_frame {
  	struct	elf_common_ev6_logout_header	hdr;
	struct  elf_common_ev6_corr_data 	procdata;
	struct	elf_dc104x_error_data 		elfcc_sysdata;
};

/*
 * Structures related to extended error packets 
 * that need to be logged for DECanalyze
 */

#define	KN600_EL_TSUNAMI_CLASS	12

/* definitions needed for Termination packet */
#define	KN600_EL_TERM_LNGTH	8
#define KN600_EL_TERM_CLASS	0
#define	KN600_EL_TERM_TYPE	0
#define	KN600_EL_TERM_REV	1

struct el_kn600_packet_hdr {
  short	packt_length;
  short	packt_class;
  short	packt_type;
  short packt_rev;
};

#define	KN600_EL_BLKMEM_LNGTH	0x10
#define	KN600_EL_BLKMEM_TYPE	4
#define	KN600_EL_BLKMEM_REV	1


struct el_kn600_block_mem_packet {
  struct el_kn600_packet_hdr hdr;
  u_char 	dpr80[8];
};

#define	KN600_EL_TSUMEM_LNGTH	0x38
#define	KN600_EL_TSUMEM_TYPE	7
#define	KN600_EL_TSUMEM_REV	1

struct el_kn600_tsunami_mem_packet {
  struct el_kn600_packet_hdr hdr;
  u_long	aar0;
  u_long	aar1;
  u_long	aar2;
  u_long	aar3;
  u_long	p0_pctl;
  u_long	p1_pctl;
};

#define	KN600_EL_PCHIP_LNGTH	0x78
#define	KN600_EL_PCHIP_CLASS	12
#define	KN600_EL_PCHIP0_TYPE	5
#define	KN600_EL_PCHIP1_TYPE	6
#define	KN600_EL_PCHIP2_TYPE	8
#define	KN600_EL_PCHIP3_TYPE	9
#define	KN600_EL_PCHIP_REV	1

struct el_kn600_pchip_packet {
  struct el_kn600_packet_hdr hdr;
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

/* definitions needed for Throttle packet */
#define KN600_EL_THROTTLE_LNGTH 24
#define KN600_EL_THROTTLE_CLASS 9
#define	KN600_EL_THROTTLE_TYPE	1
#define	KN600_EL_THROTTLE_REV	1

struct el_kn600_throttle_packet {
  struct el_kn600_packet_hdr hdr;
  long          cpuid;
  long          mces;
};

#define KN600_FORCE_CRD_DATA    0xdc10135700000000L
/* definition for crd testing */
struct kn600_crd {
    int hosenum;                        /* read-only member */
    int crd_count;                      /* modifiable */
    int iterations;                     /* read-only member */
    int loop_count;                     /* modifiable */
};

/*
 * Known members of the Tsunami/Typhoon family
 */
#define	KN600_MEMBER_DP264	1
#define	KN600_MEMBER_WARHOL	2
#define	KN600_MEMBER_WINDJAMMER	3
#define	KN600_MEMBER_MONET	4
#define	KN600_MEMBER_CLIPPER	5
#define KN600_MEMBER_GOLDRUSH	6
#define KN600_MEMBER_WEBBRICK   7


#define MEMBER_ID_SHIFT 10
#define MEMBER_ID 0xfc00L

/*
 * Server management definitions needed for Goldrush
 * and WebBrick
 *
 *      I2C-Based Server Management
 *
 *      The I2C base address and esc address.
 */
#define KN600_I2C_BASE_ADDR_WEBBRICK 		0x000e0000
#define KN600_I2C_BASE_ADDR_GOLDRUSH 		0xfff80000
#define KN600_ESC_BASE_ADDR			0x80

#define KN600_GET_I2C_BASE_ADDR( member_id, data_ptr )       {  \
   switch( member_id ) {                                        \
   case KN600_MEMBER_DP264:                                     \
   case KN600_MEMBER_GOLDRUSH:                                  \
      *data_ptr = KN600_I2C_BASE_ADDR_GOLDRUSH;                 \
      break;                                                    \
   case KN600_MEMBER_WEBBRICK:                                  \
      *data_ptr = KN600_I2C_BASE_ADDR_WEBBRICK;                 \
      break;                                                    \
   default:                                                     \
      *data_ptr = KN600_I2C_BASE_ADDR_WEBBRICK;                 \
   }                                                            \
}

/*
 * Server Management Definitions SPECIFIC TO CLIPPER
 *
 *      Dual-Ported RAM Based Server Management
 *
 *      Note that this will eventually be migrated to
 *      be based upon the FRU 5.0 Table definition, once
 *      it has been completed and is robust enough to 
 *      provide Clipper Server Management. Until then,
 *      we will access the dual-ported RAM directly
 *      for environmental monitoring (instead of
 *      traversing the V5.0 FRU Table to obtain DPR
 *      offsets).
 */
#define KN600_DPR_INDEX                         0x40
#define KN600_DPR_SIZE                          0x100

/* Base Address of memory config info */
#define KN600_DPR_MEM_CONFIG			(0x80 * KN600_DPR_INDEX)


/* Power Supply Status */
#define	KN600_DPR_PS_CPU_PRESENT		(0x90 * KN600_DPR_INDEX)
#define	KN600_DPR_PS_POK_BITS		        (0x91 * KN600_DPR_INDEX)
#define	KN600_DPR_PS_AC_INPUT    		(0x92 * KN600_DPR_INDEX)

/* Temperature for CPU's */
#define	KN600_DPR_CPU0_TEMP			(0x93 * KN600_DPR_INDEX)
#define	KN600_DPR_CPU1_TEMP			(0x94 * KN600_DPR_INDEX)
#define	KN600_DPR_CPU2_TEMP			(0x95 * KN600_DPR_INDEX)
#define	KN600_DPR_CPU3_TEMP			(0x96 * KN600_DPR_INDEX)

/* Temperature for PCI Zones */
#define	KN600_DPR_PCI_ZONE1_TEMP		(0x97 * KN600_DPR_INDEX)
#define	KN600_DPR_PCI_ZONE2_TEMP		(0x98 * KN600_DPR_INDEX)
#define	KN600_DPR_PCI_ZONE3_TEMP		(0x99 * KN600_DPR_INDEX)

/* Raw Fan Speeds */
#define KN600_DPR_FAN1_SPEED                    (0x9a * KN600_DPR_INDEX)
#define KN600_DPR_FAN2_SPEED                    (0x9b * KN600_DPR_INDEX)
#define KN600_DPR_FAN3_SPEED                    (0x9c * KN600_DPR_INDEX)
#define KN600_DPR_FAN4_SPEED                    (0x9d * KN600_DPR_INDEX)
#define KN600_DPR_FAN5_SPEED                    (0x9e * KN600_DPR_INDEX)
#define KN600_DPR_FAN6_SPEED                    (0x9f * KN600_DPR_INDEX)

/* Fan Status Mask */
#define KN600_DPR_FAN_OK_MASK                   (0xaa * KN600_DPR_INDEX)

/* Per-Power Supply Detail */
#define KN600_DPR_PS0_ID                        (0xdb * KN600_DPR_INDEX)
#define KN600_DPR_PS0_AC_INPUT                  (0xdc * KN600_DPR_INDEX)
#define KN600_DPR_PS0_INTERNAL_TEMP             (0xdd * KN600_DPR_INDEX)
#define KN600_DPR_PS0_INLET_TEMP                (0xde * KN600_DPR_INDEX)
#define KN600_DPR_PS0_3V_CURRENT                (0xe0 * KN600_DPR_INDEX)
#define KN600_DPR_PS0_5V_CURRENT                (0xe1 * KN600_DPR_INDEX)
#define KN600_DPR_PS0_12V_CURRENT               (0xe2 * KN600_DPR_INDEX)
#define KN600_DPR_PS0_FAN_SPEED                 (0xd3 * KN600_DPR_INDEX)

#define KN600_DPR_PS1_ID                        (0xe4 * KN600_DPR_INDEX)
#define KN600_DPR_PS1_AC_INPUT                  (0xe5 * KN600_DPR_INDEX)
#define KN600_DPR_PS1_INTERNAL_TEMP             (0xe6 * KN600_DPR_INDEX)
#define KN600_DPR_PS1_INLET_TEMP                (0xe7 * KN600_DPR_INDEX)
#define KN600_DPR_PS1_3V_CURRENT                (0xe9 * KN600_DPR_INDEX)
#define KN600_DPR_PS1_5V_CURRENT                (0xea * KN600_DPR_INDEX)
#define KN600_DPR_PS1_12V_CURRENT               (0xeb * KN600_DPR_INDEX)
#define KN600_DPR_PS1_FAN_SPEED                 (0xec * KN600_DPR_INDEX)

#define KN600_DPR_PS2_ID                        (0xed * KN600_DPR_INDEX)
#define KN600_DPR_PS2_AC_INPUT                  (0xee * KN600_DPR_INDEX)
#define KN600_DPR_PS2_INTERNAL_TEMP             (0xef * KN600_DPR_INDEX)
#define KN600_DPR_PS2_INLET_TEMP                (0xf0 * KN600_DPR_INDEX)
#define KN600_DPR_PS2_3V_CURRENT                (0xf2 * KN600_DPR_INDEX)
#define KN600_DPR_PS2_5V_CURRENT                (0xf3 * KN600_DPR_INDEX)
#define KN600_DPR_PS2_12V_CURRENT               (0xf4 * KN600_DPR_INDEX)
#define KN600_DPR_PS2_FAN_SPEED                 (0xf5 * KN600_DPR_INDEX)

/*
 * Bit-Level Masks for Dual-Ported RAM Fields
 */

/* DPR Location 0x90 - Power Supply & CPU Present */
#define KN600_DPRMASK_CPU_PRESENT		0xf0
#define KN600_DPRMASK_CPU0_PRESENT		0x10
#define KN600_DPRMASK_CPU1_PRESENT		0x20
#define KN600_DPRMASK_CPU2_PRESENT		0x40
#define KN600_DPRMASK_CPU3_PRESENT		0x80
#define KN600_DPRMASK_PS_PRESENT		0x07
#define KN600_DPRMASK_PS0_PRESENT		0x01
#define KN600_DPRMASK_PS1_PRESENT		0x02
#define KN600_DPRMASK_PS2_PRESENT		0x04

/* DPR Location 0x91 - Power Supply Info */
#define	KN600_DPRMASK_PS_POK		        0xff
#define	KN600_DPRMASK_PS0_POK		        0x01
#define	KN600_DPRMASK_PS1_POK		        0x02
#define	KN600_DPRMASK_PS2_POK		        0x04
#define	KN600_DPRMASK_VTERM_POK		        0x08
#define KN600_DPRMASK_CPU0_POK                  0x10
#define KN600_DPRMASK_CPU1_POK                  0x20
#define KN600_DPRMASK_CPU2_POK                  0x40
#define KN600_DPRMASK_CPU3_POK                  0x80

/* DPR Location 0x92 - Power Supply AC Input */
#define KN600_DPRMASK_PS_AC_INPUT               0x07
#define KN600_DPRMASK_PS0_AC_INPUT              0x01
#define KN600_DPRMASK_PS1_AC_INPUT              0x02
#define KN600_DPRMASK_PS2_AC_INPUT              0x04

/* DPR Location 0xaa - Fan Status Mask */
#define KN600_DPRMASK_FAN_OK                    0x3f
#define KN600_DPRMASK_FAN1_OK                   0x01
#define KN600_DPRMASK_FAN2_OK                   0x02
#define KN600_DPRMASK_FAN3_OK                   0x04
#define KN600_DPRMASK_FAN4_OK                   0x08
#define KN600_DPRMASK_FAN5_OK                   0x10
#define KN600_DPRMASK_FAN6_OK                   0x20


/* DPR Location 0x92 - Power Supply AC Input */
#define	KN600_DPRMASK_PS_AC_INPUT    		0x07
#define	KN600_DPRMASK_PS0_AC_INPUT    		0x01
#define	KN600_DPRMASK_PS1_AC_INPUT    		0x02
#define	KN600_DPRMASK_PS2_AC_INPUT    		0x04

/* DPR Locations db:e3, e4:ec and ed:f5 - Per-Power Supply Detail */
#define KN600_DPRMASK_PS_ID                     0x03
#define KN600_DPRMASK_PS_THERMAL_SHUTDOWN       0x08

#endif /* __ARCH_ALPHA_HAL_KN600_H */


















