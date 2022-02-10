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
 * Modification history: tlaser.h
 * Revision 1.1.2.4  1994/11/07  21:09:12  Mark_Bozen
 * 	bmerge before submit
 * 	[1994/11/07  21:03:38  Mark_Bozen]
 *
 * 	Remove conflict of multiple definitions of ruby_mcheck_control structure
 * 	bewteen Ruby and Turbolaser
 * 	[1994/11/03  20:34:50  Mark_Bozen]
 *
 * 	Move ELMACH_DECTLASER definition to errlog.h
 * 	[1994/10/21  19:28:22  Mark_Bozen]
 *
 * Revision 1.1.2.3  1994/08/29  21:17:04  Mark_Bozen
 * 	bmerge before submit
 * 	[1994/08/29  21:16:21  Mark_Bozen]
 * 
 * 	Added temporary Tlaser processor type for errorlog header field
 * 	[1994/08/25  18:58:54  Mark_Bozen]
 * 
 * 	Initial machine check and correctable errorlog support
 * 	[1994/08/24  19:24:49  Mark_Bozen]
 * 
 * Revision 1.1.2.2  1994/04/15  14:55:37  Naresh_Dharnidharka
 * 	Added Turbolaser System variation defines.
 * 	[1994/04/12  16:30:36  Naresh_Dharnidharka]
 * 
 * 	Moved the watch chip and uart stuff to ruby_common.h.
 * 	[1994/04/11  18:43:43  Naresh_Dharnidharka]
 * 
 * 	Moved the mcheck control structure to ruby_common.h
 * 	[1994/04/06  19:46:29  Naresh_Dharnidharka]
 * 
 * 	Added back the GBUS addresses of the UART registers.
 * 	[1994/03/30  16:10:39  Naresh_Dharnidharka]
 * 
 * 	Moved all UART defines to ruby_uart.h
 * 	[1994/03/29  17:08:54  Naresh_Dharnidharka]
 * 
 * 	Bug fix.
 * 	[1994/03/02  20:08:38  Naresh_Dharnidharka]
 * 
 * 	More changes.
 * 	[1994/02/24  15:47:56  Naresh_Dharnidharka]
 * 
 * 	Iniital changes for Turbolaser.
 * 	[1994/02/09  18:26:06  Naresh_Dharnidharka]
 * 
 * Prtial Modification history: kn7aa.h
 * Revision 1.1.9.3  1993/09/21  20:36:07  Randall_Brown
 * 	Merge of Maint + Sterling HW Support to Gold
 * 	[1993/09/18  22:08:42  Randall_Brown]
 *
 * Revision 1.1.9.2  1993/05/26  21:52:08  Paula_Long
 * 	submitting the SMP project
 * 	[1993/05/26  05:34:09  Paula_Long]
 * 
 */
/*
 * @(#)$RCSfile: kn8ae.h,v $ $Revision: 1.1.13.2 $ (DEC) $Date: 1999/02/09 17:31:45 $
 */

#ifndef __KN8AE_H__
#define __KN8AE_H__
#include <sys/types.h>	/* included to define type u_long for */
			/* el_ruby_mcheck_data structure */
#include <hal/dc21064.h>
#include <hal/cpuconf.h>	/* memtest_t for kn8ae_mcheck_control struct */


/*
 * Turbolaser TLEP register definitions =
 *  TLSB required regs + TLEP module specific regs + CPU specific regs 
 *
 *  Three TLEP versions: EV5, EV56, & EV6. As noted below, not all
 *  registers exist on all versions and there are some conflicts.
 */

struct lsb_lep_reg 
{
				   /* Begin Node Space registers	*/
    u_int	lep_ldev;	   /* 0000: TLaser device register	*/
    char	lep_pad0[0x3c];	   /*   60 byte pad			*/
    u_int	lep_lber;	   /* 0040: TLaser bus error register	*/
    char	lep_pad1[0x3c];    /*   60 byte pad			*/
    u_int	lep_lcnr;	   /* 0080: TL configuration register	*/
    char	lep_pad2[0x3c];    /*   60 byte pad			*/
    u_int	lep_lvid;	   /* 00c0: TLaser Virutal ID register	*/
    char	lep_pad3[0x13c];   /*  316 byte pad			*/
    u_int	lep_lmmr0;	   /* 0200: TL memory mapping Reg 0	*/
    char	lep_pad4[0x3c];    /*   60 byte pad			*/
    u_int	lep_lmmr1;	   /* 0240: TL memory mapping Reg 1	*/
    char	lep_pad5[0x3c];    /*  60 byte pad			*/
    u_int	lep_lmmr2;	   /* 0280: TL memory mapping Reg 2	*/
    char	lep_pad6[0x3c];    /*  60 byte pad			*/
    u_int	lep_lmmr3;	   /* 02c0: TL memory mapping Reg 3	*/
    char	lep_pad7[0x3c];    /*  60 byte pad			*/
    u_int	lep_lmmr4;	   /* 0300: TL memory mapping Reg 4	*/
    char	lep_pad8[0x3c];    /*  60 byte pad			*/
    u_int	lep_lmmr5;	   /* 0340: TL memory mapping Reg 5	*/
    char	lep_pad9[0x3c];    /*   60 byte pad			*/
    u_int	lep_lmmr6;	   /* 0380: TL memory mapping Reg 6	*/
    char	lep_pad10[0x3c];   /*   60 byte pad			*/
    u_int	lep_lmmr7;	   /* 03c0: TL memory mapping Reg 7	*/
    char	lep_pad11[0x23c];  /*  572 byte pad			*/
    u_int	lep_lfadr0;	   /* 0600: TL failing address Reg 0	*/
    char	lep_pad12[0x3c];   /*   60 byte pad			*/
    u_int	lep_lfadr1;	   /* 0640: TL failing address Reg 1	*/
    char	lep_pad13[0x3c];   /*   60 byte pad			*/
    u_int	lep_lbesr0;	   /* 0680: TL bus error syndrome R0	*/
    char	lep_pad14[0x3c];   /*   60 byte pad			*/
    u_int	lep_lbesr1;	   /* 06c0: TL bus error syndrome R1	*/
    char	lep_pad15[0x3c];   /*   60 byte pad			*/
    u_int	lep_lbesr2;	   /* 0700: TL bus error syndrome R2	*/
    char	lep_pad16[0x3c];   /*   60 byte pad			*/
    u_int	lep_lbesr3;	   /* 0740: TL bus error syndrome R3	*/
    char	lep_pad17[0x8bc];  /* 2236 byte pad			*/
				   /* Begin Module Specific Registers	*/
    u_int	lep_ldiag;	   /* 1000: TLEP Diagnostic setup reg	*/
				   /*       TL-6 Module Config Register	*/
    char	lep_pad18[0x3c];   /*	60 byte pad			*/
    u_int	lep_ldtagdata;     /* 1040: TLEP DTAG data reg		*/
				   /*       TL-6 DTAG Data Test Reg	*/
    char	lep_pad19[0x3c];   /*	60 byte pad			*/
    u_int	lep_ldtagstat;     /* 1080: TLEP DTAG stat reg		*/
				   /*       TL-6 DTAG Address Reg	*/
    char	lep_pad20[0x3c];   /*	60 byte pad			*/
    u_int	lep_lmodconfig;    /* 10c0: Module Configuration reg	*/
    char	lep_pad21[0x3c];   /*	60 byte pad			*/
    u_int	lep_lintrmask0;    /* 1100: Interrupt Mask reg for Cpu0 */
    char	lep_pad22[0x3c];   /*	60 byte pad			*/
    u_int	lep_lintrmask1;    /* 1140: Interrupt Mask reg for Cpu1 */
    char	lep_pad23[0x3c];   /*	60 byte pad			*/
    u_int	lep_lintrsum0;     /* 1180: Interrupt Source reg for Cpu0 */
    char	lep_pad24[0x3c];   /*	60 byte pad			*/
    u_int	lep_lintrsum1;     /* 11c0: Interrupt Source reg for Cpu1 */
    char	lep_pad25[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon00; 	   /* 1200: Console Comm. reg0 for Cpu0	*/
    char	lep_pad26[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon00a; 	   /* 1240: DIGA Comm. test reg0 for DIGA1 */
    char	lep_pad27[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon00b; 	   /* 1280: DIGA Comm. test reg0 for DIGA2 */
    char	lep_pad28[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon00c; 	   /* 12c0: DIGA Comm. test reg0 for DIGA3 */
    char	lep_pad29[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon10; 	   /* 1300: Console Comm. reg0 for Cpu1	*/
    char	lep_pad30[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon10a; 	   /* 1340: DIGA Comm. test reg1 for DIGA1 */
    char	lep_pad31[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon10b; 	   /* 1380: DIGA Comm. test reg1 for DIGA2 */
    char	lep_pad32[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon10c; 	   /* 13c0: DIGA Comm. test reg1 for DIGA3 */
    char	lep_pad33[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon01; 	   /* 1400: Console Comm. reg1 for Cpu0	*/
    char	lep_pad34[0x3c];   /*	60 byte pad			*/
    u_int	lep_lcon11; 	   /* 1440: Console Comm. reg1 for Cpu1	*/
    char	lep_pad35[0xbc];   /*  188 byte pad			*/
    u_int	lep_aerr; 	   /* 1500: ADG Error register		*/
				   /*	    TL-6 TCC Error Register	*/
    char	lep_pad36[0x3c];   /*	60 byte pad			*/
    u_int	lep_derr; 	   /* 1540: DIGA Error register		*/
				   /*	    TL-6 TDI Error Register	*/
    char	lep_pad37[0x3c];   /*	60 byte pad			*/
    u_int	lep_merr; 	   /* 1580: MMG Error register		*/
				   /*	    TL-6 unused			*/
    char	lep_pad38[0x3c];   /*	60 byte pad			*/
    u_int	lep_vmg; 	   /* 15c0: Voltage Margining register	*/
    char	lep_pad39[0x3c];   /*	60 byte pad			*/
    u_int	lep_wserr;	   /* 1600: TL-6 Window Space Error Reg	*/
				   /*       TL-5 1st Data Mover reg	*/
				   /*	    TL-56 not used		*/
    char	lep_pad40[0x1fc];  /*  508 byte pad			*/

				   /* Nuked Data Mover registers. Only exist
				      on TL-EV5 & never used by the OS.     */

    u_int	lep_tlpm_cmd;	   /* 1800: Perf. monitor command reg	*/
				   /*	    TL-6 DTAG test execute reg	*/
    char	lep_pad46[0x3c];   /*	60 byte pad			*/
				   /* Note: TL-6 NO Perf. Monitor regs	*/
    u_int	lep_tlpm_total_cycles;	/* 1840: Total number of cycles */
    					/*       since start bit set	*/
    char	lep_pad47[0x3c];	/*   60 byte pad		*/
    u_int	lep_tlpm_ev5_latency;	/* 1880: Total average read latency */
    char	lep_pad48[0x3c];	/*   60 byte pad		*/
    u_int	lep_tlpm_read_latency;	/* 18c0: average latency for	*/
    					/*       individual reads	*/
    char	lep_pad49[0x3c];	/*   60 byte pad		*/
    u_int	lep_tlpm_sys_owner; /* 1900: No. of cycles system owned */
    				    /*       the command bus		*/
    char	lep_pad50[0x3c];   /*    60 byte pad		*/
    u_int	lep_tlpm_cmd_silo; /* 1940: CMD silo			*/
    char	lep_pad51[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_lock;	   /* 1980: No. of lock cmds acked 	*/
    char	lep_pad52[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_mb;	   /* 19c0: No. of MBs acked		*/
    char	lep_pad53[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_sd_total; /* 1a00: No. of Set Dirtys issued by EV5 */
    char	lep_pad54[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_sd_acked; /* 1a40: No. of Set Dirtys acked 	*/
    char	lep_pad55[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_rd_csr;   /* 1a80: No of CSR read cmds 	*/
    char	lep_pad56[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_rd;       /* 1ac0: No. of mem space read miss cmds */
    char	lep_pad57[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_rd_mod;   /* 1b00: No. of Read miss mod cmds	*/
    char	lep_pad58[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_rd_stc;   /* 1b40: No of read miss stxc cmds	*/
    char	lep_pad59[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_victim;   /* 1b80: No of Bcache victims	*/
    char	lep_pad60[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_wr_csr;   /* 1bc0: No of csr write cmds	*/
    char	lep_pad61[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_wr; 	   /* 1c00: No of Write Block cmds acked */
    char	lep_pad62[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_wr_lock;  /* 1c40: No of Write Block Lock cmds acked */
    char	lep_pad63[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_inval;    /* 1c80: No of invals from system 	*/
    char	lep_pad64[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_set_shrd; /* 1cc0: No of set shareds from system */
    char	lep_pad65[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_rd_dirty; /* 1d00: No of Read dirtys from system */
    char	lep_pad66[0x3c];   /*   60 byte pad			*/
    u_int	lep_tlpm_adr_silo; /* 1d40: Address silo reg		*/
    char	lep_pad67[0xbc];   /*  188 byte pad			*/
    u_int	lep_rm_rang_reg0a; /* 1e00: RM range reg for chan 0	*/
				   /*	    Note: TL-6 no RM registers	*/
    char	lep_pad68[0x3c];   /*   60 byte pad			*/
    u_int	lep_rm_rang_reg0b; /* 1e40: RM range reg for chan 0	*/
    char	lep_pad69[0x3c];   /*   60 byte pad			*/
    u_int	lep_rm_rang_reg1a; /* 1e80: RM range reg for chan 1	*/
    char	lep_pad70[0x3c];   /*   60 byte pad			*/
    u_int	lep_rm_rang_reg1b; /* 1ec0: RM range reg for chan 1	*/
    char	fill[0x10000-0x1ec4];
};

/*
 * Define EV6 TurboLaser registers so the code can
 * reference them by their correct names.
 */
#define	lep_lmodconfig0	lep_ldiag		/* TLMODCONFIG0 (1000) */
#define	lep_lmodconfig1	lep_lmodconfig		/* TLMODCONFIG1 (10c0) */
#define	lep_tccerr	lep_aerr		/* TCCERR (1500) */
#define	lep_tdierr	lep_derr		/* TDIERR (1540) */


/*
 * Turbolaser Registers - Broadcast Space
 *   Base Address = 0xff8e000000
 */

struct tlaser_reg {
    u_int	tlprivate;	/* 0000: Reserved for Private transactions */
    char	pad0[0x3c];	/*   60 byte pad			*/
    u_int	tlipintr;	/* 0040: TLEP IP Interrupt Reg		*/
    char	pad1[0xbc];	/*  188 byte pad			*/
    u_int	tliointr4;	/* 0100: IO interrupt reg		*/
    char	pad2[0x3c];	/*   60 byte pad			*/
    u_int	tliointr5;	/* 0140: IO interrupt reg		*/
    char	pad3[0x3c];	/*   60 byte pad			*/
    u_int	tliointr6;	/* 0180: IO interrupt reg		*/
    char	pad4[0x3c];	/*   60 byte pad			*/
    u_int	tliointr7;	/* 01c0: IO interrupt reg		*/
    char	pad5[0x3c];	/*   60 byte pad			*/
    u_int	tliointr8;	/* 0200: TO interrupt reg		*/
    char	pad6[0x1fc];	/*  508 byte pad			*/
    u_int	tlwsdqr4;	/* 0400: Window space DEC count 4	*/
    char	pad7[0x3c];	/*   60 byte pad			*/
    u_int	tlwsdqr5;	/* 0440: Window space DEC count 5	*/
    char	pad8[0x3c];	/*   60 byte pad			*/
    u_int	tlwsdqr6;	/* 0480: Window space DEC count 6	*/
    char	pad9[0x3c];	/*   60 byte pad			*/
    u_int	tlwsdqr7;	/* 04c0: Window space DEC count 7	*/
    char	pad10[0x3c];	/*   60 byte pad			*/
    u_int	tlwsdqr8;	/* 0500: Window space DEC count 8	*/
    char	pad11[0xfc];	/*  252 byte pad			*/
    u_int	tlrmdqrx;	/* 0600: Reflective Memory DEC count x	*/
    char	pad12[0x3c];	/*   60 byte pad			*/
    u_int	tlrmdqr8;	/* 0640: Reflective Memory DEC count 8	*/
    char	pad13[0x1bc];	/*  444 byte pad			*/
    u_int	tlrdrd;		/* 0800: Window space Read Data Data Reg */
    char	pad14[0x3c];	/*   60 byte pad			*/
    u_int	tlrdre;		/* 0840: Window space Read Data Error Reg */
};


/* GBUS addresses of UART base registers */

#define GBUS_DUART0     0xFFA0000000
#define GBUS_DUART1     0xFFA1000000
#define GBUS_WATCH      0xFFB0000000
#define GBUS_MISC       0xFFC0000000
#define GBUS_TLSBRST	0xFFC6000000

/*
 * System variation numbers used to differenciate between laser and blazer
*/

#define DEC21000_800	0L	/* Turbolaser Rackmount cabinet (800 MP) */
#define DEC21000_900	1L	/* Turbolaser NEP cabinet (900 MP) */

#define	KN8AE_NCPUS	18	/* Maximum number of processors on TruboLaser */
				/* Note: 9 TLSB slots; max CPU number is 17 */

struct	kn8ae_mcheck_control {	/* kn8ae machine check control structure */

	/* The following set of structure elements are used for intentional
	 * machine checks, such as those caused by BADADDR, for bus probing.
	 */
	u_int mcheck_expected;		/* flag: we're probing. */
	u_int mcheck_occured;		/* Number of mchecks during probe. */
	u_int mcheck_action;		/* What action to take with this mcheck,
					   recover, crash, retry */
	u_int mcheck_retry;		/* Logout frames retry bit */	
	memtest_t mcheck_tp_active;	/* flag: testpage in progress */
	long  mcheck_return;		/* return to this PC expected mchecks */
	long  mcheck_page;		/* page we're testing. */
};

#define	KN8AE_MCHECK_CONTROL(cpu_id) &kn8ae_mcheck_control[cpu_id]

#endif /* __KN8AE_H__ */

