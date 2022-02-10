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
/*
 * HISTORY
 */
#pragma ident "@(#)$RCSfile: common_ev6_mcheck_hdr.h,v $ $Revision: 1.1.2.6 $ (DEC) $Date: 1998/04/23 12:47:15 $"
#ifndef __ARCH_ALPHA_HAL_EV6_MCHECK 
#define __ARCH_ALPHA_HAL_EV6_MCHECK

/*
 * Common header portion for machine check logout frame
 */
struct  elf_common_ev6_logout_header {
	u_int	elfl_size;		/* size in bytes of logout area. */
	int	elfl_sbz1:30;		/* Should Be Zero		 */
	int	elfl_2nd_error:1;	/* 1 for second error occured	 */
	int	elfl_retry:1;		/* Retry flag. 			 */
        u_int	elfl_procoffset;	/* Processor-specific offset.	 */
	u_int	elfl_sysoffset;		/* Offset of system-specific. 	 */
        u_long  elfl_mcheck_code;	/* machine check code 		 */
};

/*
 * EV6 specific portion of uncorrectable logout frame
 */
struct  elf_common_ev6_uncorr_data {
	u_long ev6err_i_stat;
	u_long ev6err_dc_stat;
	u_long ev6err_c_addr;
	u_long ev6err_dc1_syndrome;
	u_long ev6err_dc0_syndrome;
	u_long ev6err_c_stat;
	u_long ev6err_c_sts;
	u_long ev6err_mm_stat;
	u_long ev6err_exc_addr;
	u_long ev6err_ier_cm;
	u_long ev6err_isum;
	u_long ev6err_reserved_1;
	u_long ev6err_pal_base;
	u_long ev6err_i_ctl;
	u_long ev6err_pctx;
	u_long ev6err_reserved_2;
	u_long ev6err_reserved_3;
};

struct elf_common_ev6_uncorr_frame {
  	struct	elf_common_ev6_logout_header	hdr;
	struct  elf_common_ev6_uncorr_data 	procdata;
};


/*
 * EV6 specific portion of correctable logout frame
 */
struct  elf_common_ev6_corr_data {
	u_long ev6err_i_stat;
	u_long ev6err_dc_stat;
	u_long ev6err_c_addr;
	u_long ev6err_dc1_syndrome;
	u_long ev6err_dc0_syndrome;
	u_long ev6err_c_stat;
	u_long ev6err_c_sts;
	u_long ev6err_mm_stat;
};

/*
 * data structure that defines the common portion of the 
 * correctable logout frame
 */
struct elf_common_ev6_corr_frame {
  	struct	elf_common_ev6_logout_header	hdr;
	struct  elf_common_ev6_corr_data 	procdata;
};

/* Error bits in EV6 ISTAT IPR */
#define	EV6_ISTAT_DPE		0x40000000	/* Icache data parity */
#define	EV6_ISTAT_TPE		0x20000000	/* Icache tag parity */

/* Error bits in EV6 DCSTAT IPR */
#define	EV6_DCSTAT_SEO		0x00000010	/* Second error occurred */
#define	EV6_DCSTAT_ECC_ERR_LD	0x00000008	/* ECC on load */
#define	EV6_DCSTAT_ECC_ERR_ST	0x00000004	/* ECC on store */
#define	EV6_DCSTAT_TPERR_P1	0x00000002	/* Tag parity pipeline 1 */
#define	EV6_DCSTAT_TPERR_P0	0x00000001	/* Tag parity pipeline 0 */

/* Error bits in EV6 CSTAT IPR */
#define	EV6_CSTAT_MASK		0x0000001f	/* only bits <4:0> */
#define	EV6_CSTAT_BC_PERR	0x00000001	/* Bcache parity error */
#define	EV6_CSTAT_DC_PERR	0x00000002	/* Dcache parity error */
#define	EV6_CSTAT_DS_MEM_ERR	0x00000003	/* Dstream memory error */
#define	EV6_CSTAT_DS_BC_ERR	0x00000004	/* Dstream Bcache error */
#define	EV6_CSTAT_DS_DC_ERR	0x00000005	/* Dstream Dcache error */
#define	EV6_CSTAT_IS_MEM_ERR	0x0000000b	/* Istream memory error */
#define	EV6_CSTAT_IS_BC_ERR	0x0000000c	/* Istream Bcache error */
#define	EV6_CSTAT_DBFE		0x00000010	/* Double bit fill error */


/*
 * Machine Check Error codes for EV6 detected errors
 */
#define	EV6_MCHK_SDC_ECCER	0x81
#define	EV6_MCHK_DC_ECCER	0x82
#define	EV6_MCHK_DCTAG_PERR	0x83
#define	EV6_MCHK_IC_PERR	0x84
#define	EV6_MCHK_DCVR_ECCER	0x85
#define	EV6_MCHK_BC_ECCER	0x86
#define	EV6_MCHK_MEM_ECCER	0x87
#define	EV6_MCHK_PAL_BUGCK	0x8E
#define	EV6_MCHK_SDC_LDIS	0x91
#define	EV6_MCHK_DDC_TPE	0x93
#define	EV6_MCHK_DBIT_ECCER	0x96
#define	EV6_MCHK_PROBE_DERR	0x97
#define	EV6_MCHK_PROC_MCHK	0x98
#define	EV6_MCHK_BC_TPE		0x9A
#define EV6_MCHK_DC_TPE		0x9E

/*
 * functional prototypes for common EV6 functions
 */
void	ev6_logout_frame_consprint(struct elf_common_ev6_uncorr_frame *cmcf);



#endif /* __ARCH_ALPHA_HAL_EV6_MCHECK */
