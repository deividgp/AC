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
 * @(#)ka_ruby.h	9.3  (ULTRIX)        10/29/91
 */

/*
 * Modification History: machine/alpha/ka_ruby.h
 *
 *      14-Jan-92       prm
 *         - Add gbus structure definition for Watch's csrb. Modify csra
 *           definitions to avoid conflict with csrb. Fix gbus_watch offsets.
 *
 *      28-oct-91       prm
 *         - Add more gbus structure definitions, including BB_WATCH (toy).
 *         - Change mchk_logout to ruby_mchk_logout, since it will not be the
 *           same across platforms.
 *
 *      13-Sep-91       prm (Peter Mott) 
 *           Add definitions for Gbus uart support.
 *
 *	12-sep-91	jac	Added lots of register definitions...
 *
 * Jun-91	jac: created this file for processor support of Laser/Ruby
 *
 */

#ifndef __KN7AA_H__
#define __KN7AA_H__
#include <sys/types.h>	/* included to define type u_long for */
			/* el_ruby_mcheck_data structure */
#include <hal/dc21064.h>

/*
 * Ruby register definitions
*/

struct ruby_reg {
	unsigned int  	lep_ldev;	/* Laser device register	*/
	char		lep_pad0[0x3c];	/* 60 byte pad			*/
	unsigned int  	lep_lber;	/* Laser bus error register	*/
	char		lep_pad1[0x3c];	/* 60 byte pad			*/
	unsigned int	lep_lcnr;	/* Laser configuration register	*/
	char		lep_pad2[0x17c]; /* 380 byte pad		*/
	unsigned int	lep_lmmr0;	/* Laser memory mapping Reg 0	*/
	char		lep_pad3[0x3c];	/* 60 byte pad			*/
	unsigned int	lep_lmmr1;	/* Laser memory mapping Reg 1	*/
	char		lep_pad4[0x3c];	/* 60 byte pad			*/
	unsigned int	lep_lmmr2;	/* Laser memory mapping Reg 2	*/
	char		lep_pad5[0x3c];	/* 60 byte pad			*/
	unsigned int	lep_lmmr3;	/* Laser memory mapping Reg 3	*/
	char		lep_pad6[0x3c];	/* 60 byte pad			*/
	unsigned int	lep_lmmr4;	/* Laser memory mapping Reg 4	*/
	char		lep_pad7[0x3c];	/* 60 byte pad			*/
	unsigned int	lep_lmmr5;	/* Laser memory mapping Reg 5	*/
	char		lep_pad8[0x3c];	/* 60 byte pad			*/
	unsigned int	lep_lmmr6;	/* Laser memory mapping Reg 6	*/
	char		lep_pad9[0x3c];	/* 60 byte pad			*/
	unsigned int	lep_lmmr7;	/* Laser memory mapping Reg 7	*/
	char		lep_pad10[0x23c]; /* 572 byte pad		*/
	unsigned int	lep_lbesr0;	/* Laser bus error syndrome R0	*/
	char		lep_pad11[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lbesr1;	/* Laser bus error syndrome R1	*/
	char		lep_pad12[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lbesr2;	/* Laser bus error syndrome R2	*/
	char		lep_pad13[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lbesr3;	/* Laser bus error syndrome R3	*/
	char		lep_pad14[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lbecr0;	/* Laser bus error command R0	*/
	char		lep_pad15[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lbecr1;	/* Laser bus error command R1	*/
	char		lep_pad16[0x4bc]; /* 1212 byte pad		*/
	unsigned int	lep_ldiag;	/* LEP diagnostic control reg	*/
	char		lep_pad17[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lmerr;	/* LEP module error reg		*/
	char		lep_pad18[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_ltaga;	/* LEP tag address reg		*/
	char		lep_pad19[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_ltagw;	/* LEP tag write data reg	*/
	char		lep_pad20[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_ltagr;	/* LEP tag read data reg	*/
	char		lep_pad21[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_llock;	/* LEP lock address reg		*/
	char		lep_pad22[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lwpend;	/* LEP write pending address reg*/
	char		lep_pad23[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lvict;	/* LEP victum address reg	*/
	char		lep_pad24[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lcon0;	/* LEP console communication reg*/
	char		lep_pad25[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lcon1;	/* LEP console communication reg*/
	char		lep_pad26[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lmode;	/* LEP mode reg			*/
	char		lep_pad27[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_ledto;	/* LEP EDAL timeout reg		*/
	char		lep_pad28[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_liointr;	/* IO interrupt reg		*/
	char		lep_pad29[0x3c]; /* 60 byte pad			*/
	unsigned int	lep_lipintr;	/* IP interrupt reg		*/
};


/* GBUS addresses of UART base registers et. al. */
#define GBUS_LOC_BASE 	0x3F4000000
#define GBUS_PS_BASE 	0x3F4800000
#define GBUS_P_BASE 	0x3F5000000

#define GBUS_DUART0 	0x3F4000000
#define GBUS_DUART1 	0x3F4800000
#define GBUS_DUART2 	0x3F5000000
#define GBUS_WATCH 	0x3F6000000
#define GBUS_MISC 	0x3F7000000

/*
 * System variation numbers used to differenciate between laser and blazer
*/

#define DEC7000_SYSVAR	0L
#define DEC10000_SYSVAR	1L



#define PRM_NEW_MCHECK_FRAME

struct ruby_mchk_logout {
#ifndef PRM_NEW_MCHECK_FRAME
#define KN7AA_MCHECK_FRAME_PA 0x6010	/* This is setup because the */
					/* RPD doesn't have it, and we */
					/* need it */
        long    retry;		/* +6010 */
	long	unused1;
	int	proc_off;	/* +6020 */
	int	sys_off;	/* */
	long	unused2;
	long	das_tag;	/* +6030 */
	long	unused3;
	long	pal_temps[32*2];/* +6040 */
	long	exc_addr;	/* +6240 */
	long	unused4;
        long    exc_sum;	/* +6250 */
	long	unused5;
	long	iccsr;		/* +6260 */
	long	unused6;
/*        long    msk; */
        long    pal_base;	/* +6270 */
	long	unused7;
        long    hier;		/* +6280 */
	long	unused8;
        long    hirr;		/* +6290 */
	long	unused9;
        long    mm_csr;		/* +62A0 */
	long	unused10;
        long    dc_stat;	/* +62B0 */
	long	unused11;
        long    dc_addr;	/* +62C0 */
	long	unused12;
	long	abox_ctl;	/* +62D0 */
	long	unused13;
        long    biu_stat;	/* +62E0 */
	long	unused14;
        long    biu_addr;	/* +62F0 */
	long	unused15;
	long	biu_ctl;	/* +6300 */
	long	unused16;
        long    fill_syndrome;	/* +6310 */
	long	unused17;
        long    fill_addr;	/* +6320 */
	long	unused18;
        long    va;		/* +6330 */
	long	unused19;
        long    bc_tag;		/* +6340 */
	long	unused20;
	u_long lep_gbus;	/* +6350 */
	long	unused21;
	u_long lep_lmode;	/* +6360 */
	long	unused22;
	u_long lep_lmerr;	/* +6370 */
	long	unused23;
	u_long lep_llock;	/* +6380 */
	long	unused24;
	u_long lep_lber;	/* +6390 */
	long	unused25;
	u_long lep_lcnr;	/* +63A0 */
	long	unused26;
	u_long lep_ldev;	/* +63B0 */
	long	unused27;
	u_long lep_lbesr0;	/* +63C0 */
	long	unused28;
	u_long lep_lbesr1;	/* +63D0 */
	long	unused29;
	u_long lep_lbesr2;	/* +63E0 */
	long	unused30;
	u_long lep_lbesr3;	/* +63F0 */
	long	unused31;
	u_long lep_lbecr0;	/* +6400 */
	long	unused32;
        u_long lep_lbecr1;	/* +6410 */
	long	unused33;
#else /* not PRM_NEW_MCHECK_FRAME */
#define KN7AA_MCHECK_FRAME_PA 0x6010	/* This is setup because the */
					/* RPD doesn't have it, and we */
					/* need it */

 /* these are a part of the console's structure, but preceed the */
 /* pointer address passed to osf from pal */
 /* removed	long	flags; */
 /* removed	long	dasdebug; */

				/* the following offset are describe */
				/* from the base of the console's data */
				/* structure as seen with a 'mchk' cmd */
				/* from the console prompt. Subtract */
				/* 10 for offsets from the base of the */
				/* frame address passed to osf bt the */
				/* pal code */

/*	long	osfmces;	/* +010 */
/*	long	osfvers;	/* +018 */

        long    retry;		/* +020 ; known as byte count to PAL */
				/* <63> - retry; <15:0> byte count */

	int	proc_off;	/* +028 ; these two int's, together */
				/* are known as 'offsets' to the pal */
	int	sys_off;	/* +02C */

        long    pal_temps[32];		/* PAL temporary locations - 30->128		*/

	long	exc_addr;	/* +130 */
        long    exc_sum;	/* +138 */
	long	exc_mask;	/* +140 */
	long	iccsr;		/* +148 */
	long	pal_base;	/* +150 */
	long	hier;		/* +158 */
	long	hirr;		/* +160 */
	long	mm_csr;		/* +168 */
	long	dc_stat;	/* +170 */
	long	dc_addr;	/* +178	*/
	long	abox_ctl;	/* +180	*/
	long	biu_stat;	/* +188 */
	long	biu_addr;	/* +190 */
	long	biu_ctl;	/* +198 */
	long	fill_syndrome;	/* +1A0 */
	long	fill_addr;	/* +1A8	*/
	long	va;		/* +1B0 */
 	long	bc_tag;		/* +1B8 */

 	long	lep_gbus;	/* +1C0	*/
 	int	lep_ldev;	/* +1C8 */
 	int	lep_lber;	/* +1CC */
 	int	lep_lcnr;	/* +1D0	 */
 	int	lep_lmerr;	/* +1D4	 */
 	int	lep_lbesr0;	/* +1D8	 */
 	int	lep_lbesr1;	/* +1DC */
 	int	lep_lbesr2;	/* +1E0	 */
 	int	lep_lbesr3;	/* +1E4 */
 	int	lep_lbecr0;	/* +1E8 */
 	int	lep_lbecr1;	/* +1EC */
 	int	lep_lmode;	/* +1F0	 */
 	int	lep_llock;	/* +1F4	 */

/*
 * End official frame - add IOP for console display only 
 */
	int	iop_lber;	/* +1F8	*/
	int	iop_lbecr0;	/* +1FC	*/
	int	iop_lbecr1;	/* +200	*/
	int	iop_ipcnse;	/* +204	*/
	int	iop_ipchst;	/* +208*/
	int	mem_lber;	/* +20C	*/
	int	mem_lbecr0;	/* +210	*/
	int	mem_lbecr1;	/* +214	*/
	int	mem_erra;	/* +218	*/
	int	mem_errb;	/* +21C */

#endif /* PRM_NEW_MCHECK_FRAME */
};



/*
 * Processor (630) correctable error frame fields
 */
struct kn7aa_proccorr_logout {
        long    retry;		/* +000 ; known as byte count to PAL */
				/* <63> - retry; <15:0> byte count */

	int	proc_off;	/* +008 ; these two int's, together */
				/* are known as 'offsets' to the pal */
	int	sys_off;	/* +00C */
	long	crd_code;
 	long	crd_biu_stat;	/* +010 */
	long	crd_biu_addr;	/* +018		(unlocks biu_stat) */
	long	crd_biu_ctl;	/* +020		(for interest) */
 	long	crd_fill_syndrome;/*+028 */
	long	crd_fill_addr;	/* +030		(unlocks fill syn) */
	long	crd_bc_tag;	/* +038		(one bit at a time!) */
	long	crd_dc_stat;    	/* +040		 */
	long	crd_dc_addr;	/* +048		(unlocks dc_stat) */
};


#endif /* __KA_RUBY_H__ */
