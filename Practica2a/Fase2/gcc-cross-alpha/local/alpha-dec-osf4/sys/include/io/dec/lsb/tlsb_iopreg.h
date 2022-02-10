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
 * Modification history: lsb_iopreg.h
 * Revision 1.2.8.3  1993/09/21  20:50:12  Randall_Brown
 * 	Merge of Maint + Sterling HW Support to Gold
 * 	[1993/09/18  22:24:59  Randall_Brown]
 *
 * Revision 1.2.8.2  1993/06/14  14:55:37  Stuart_Hollander
 * 	copied from AGOSMAINT_BL4
 * 	[1993/06/03  22:46:18  Stuart_Hollander]
 * 
 * Revision 1.2.6.2  1993/04/23  20:44:24  Stuart_Hollander
 * 	Added FLAG id value.
 * 	[1993/04/22  03:32:34  Stuart_Hollander]
 * 
 * Revision 1.2.6.2  1993/04/23  20:44:24  Stuart_Hollander
 * 	Added FLAG id value.
 * 	[1993/04/22  03:32:34  Stuart_Hollander]
 * 
 * Revision 1.2.2.4  1992/09/09  16:55:54  Ronald_Hegli
 * 	Added a define for MAX_HOSE, for convenience.
 * 	[92/09/09  16:12:22  Ronald_Hegli]
 * 
 * Revision 1.2.2.3  92/08/20  12:55:32  Peter_Schulter
 * 	Code cleanup: Changed Ruby to DEC7000 and Cobra to DEC4000.
 * 	[92/08/20  10:23:09  Peter_Schulter]
 * 
 * Revision 1.2.2.2  92/02/11  14:25:31  Joseph_Amato
 * 	comment and #ifdef cleanup
 * 	[92/02/11  14:16:39  Joseph_Amato]
 * 
 * Revision 1.2  92/01/15  01:45:34  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 1.1.2.4  92/01/13  08:50:52  Joseph_Amato
 * 	bug fixes
 * 	[92/01/09  07:53:36  Joseph_Amato]
 * 
 * Revision 1.1.2.3  91/12/31  12:16:06  Joseph_Amato
 * 	Added ipchst bit defs
 * 	Moved nHOSES here
 * 	[91/12/31  08:31:39  Joseph_Amato]
 * 
 * Revision 1.1.2.2  91/12/06  18:02:39  David_Snow
 * 	"Initial version.  File copied from TIN-based Alpha pool."
 * 
 * Revision 1.1.1.2  91/12/06  16:13:39  David_Snow
 * 	Initial version.  File copied from TIN-based Alpha pool.
 * 
 */
/*	"@(#)lsb_iopreg.h	9.2	(ULTRIX/OSF)	10/23/91" */

#ifndef LSB_IOPREG_H
#define LSB_IOPREG_H


#define bus_node private[1]

#define nHOSES 4
#define MAX_HOSE (nHOSES - 1)

/* remote adapters */
#define	LAMB    0x102a
#define FLAG	0x2f00
#define LAVA    0x7700
#define PCIA    0xef00	

struct iopreg {
        /* LASER required registers */
        unsigned int ldev;             /* device type */
        char         pad_1[60];   /* 60 byte pad 0x04-40 */
        unsigned int lber;             /* bus error */
        char         pad_2[60];   /* 60 byte pad 0x44-80 */
        unsigned int lcnr;             /* config reg */
        char         pad_3[0x17c];/* 380 byte pad 0x84-200 */
        unsigned int lmmr0;            /* Memory mapping register (0-7) */
        char         pad_4[60];   /* 60 byte pad 0x204-240 */
        unsigned int lmmr1;
        char         pad_5[60];   /* 60 byte pad 0x244-280 */
        unsigned int lmmr2;
        char         pad_6[60];   /* 60 byte pad 0x284-2c0 */
        unsigned int lmmr3;
        char         pad_7[60];   /* 60 byte pad 0x2c4-300 */
        unsigned int lmmr4;
        char         pad_8[60];   /* 60 byte pad 0x304-340 */
        unsigned int lmmr5;
        char         pad_9[60];   /* 60 byte pad 0x344-380 */
        unsigned int lmmr6;
        char         pad_10[60];   /* 60 byte pad 0x384-3c0 */
        unsigned int lmmr7;
        char         pad_11[0x23c];   /* 572 byte pad 0x3c4-600 */
        unsigned int lfadr0;           /* Failing address reg (0-1)*/
        char         pad_12[60];   /* 60 byte pad 0x604-644 */
        unsigned int lfadr1;
        char         pad_13[60];   /* 60 byte pad 0x644-680 */
        unsigned int lbesr0;           /* bus ecc error syndrome (0-3) */
        char         pad_14[60];   /* 60 byte pad 0x684-6c0 */
        unsigned int lbesr1;
        char         pad_15[60];   /* 60 byte pad 0x6c4-700 */
        unsigned int lbesr2;
        char         pad_16[60];   /* 60 byte pad 0x704-740 */
        unsigned int lbesr3;
        char         pad_17[0x2bc];   /* 700 byte pad 0x744-A00 */
        unsigned int lild0;             /* int level 0 ident */
        char         pad_18[60];   /* 60 byte pad 0xa04-a40 */
        unsigned int lild1;             /* int level 1 ident */
        char         pad_19[60];   /* 60 byte pad 0xa44-a80 */
        unsigned int lild2;             /* int level 2 ident */
        char         pad_20[60];   /* 60 byte pad 0xa84-ac0 */
        unsigned int lild3;             /* int level 3 ident */
        char         pad_21[60];   /* 60 byte pad 0xac4-b00 */
        unsigned int lcpumask;          /* cpu int mask */
        char         pad_22[0xfc];   /* 252 byte pad 0xb04-c00 */
        long lmbpr;                     /* mailbox */
        char         pad_23[0x13f8]; /* 5112 byte pad 0xc08-2000 */
        /* IOP specific registers */
        unsigned int iccmsr;            /* Control Chip Mode Select     */
        char         pad_24[60];   /* 60 byte pad 0x2004-2040 */
        unsigned int iccnse;            /* Node Specific Error Reg      */
        char         pad_25[60];   /* 60 byte pad 0x2044-2080 */
        unsigned int iccdr;             /* Control chip Diag            */
        char         pad_26[60];   /* 60 byte pad 0x2084-20c0 */
        unsigned int iccmtr;            /* Control Chip Mailbox Transaction */
        char         pad_27[60];   /* 60 byte pad 0x20c4-2100 */
        unsigned int iccwtr;        /* Control Chip Window Space Transaction */
        char         pad_27a[60];  /* 60 byte pad 0x2104-2140 */
        unsigned int idpnse1;          /* Node Specific Data Path Error Reg 1*/
        char         pad_28[60];    /* 60 byte pad 0x2144-2180 */
        unsigned int idpdr1;            /* I/O Data Path Diag 1         */
        char         pad_29[0xbc];  /* 188 byte pad 0x2184-2240 */
        unsigned int idpnse2;          /* Node Specific Data Path Error Reg 2*/
        char         pad_30[60];    /* 60 byte pad 0x2244-2280 */
        unsigned int idpdr2;            /* I/O Data Path Diag 2         */
        char         pad_31[0xbc];  /* 188 byte pad 0x2284-2340 */
        unsigned int idpnse3;          /* Node Specific Data Path Error Reg 3*/
        char         pad_32[60];    /* 60 byte pad 0x2344-2380 */
        unsigned int idpdr3;            /* I/O Data Path Diag 3         */
        char         pad_33[0x6bc]; /* 1724 byte pad 0x2384-2A40 */
        unsigned int idpnse0;          /* Node Specific Data Path Error Reg 0*/
        char         pad_34[60];    /* 60 byte pad 0x2a44-2a80 */
        unsigned int idpdr0;            /* I/O Data Path Diag 0         */
        char         pad_35[0xbc];  /* 188 byte pad 0x2a84-2b40 */
        unsigned int idpvr;             /* I/O Data Path Vector         */
        char         pad_36[60];    /* 60 byte pad 0x2b44-2b80 */
        unsigned int idpmsr;            /* I/O Data Path Mode Select    */
        char         pad_37[60];    /* 60 byte pad 0x2b44-2bc0 */
        unsigned int ibr;               /* Information Base Repair      */
        char         pad_38[0xd43c];    /* 54322 byte pad 0x2bc4 - 10000  */
      };

/* ipcnse register bit definitions */
#define INTR_NSES       0x80000000
#define TLSB_WND_OFLO	0x20000000
#define ICC_CSR_BUS_PE	0x10000000
#define ICC_IE		0x08000000
#define UP_VRTX_ERR     0x06000000	
#define UP_VRTX_ERR1    0x04000000	/* Detects errors on Up Turbo-Vortex-B
					   (Hose <3:2>) */
#define UP_VRTX_ERR0    0x02000000	/* Detects errors on Up Turbo-Vortex-A
					   (Hose <1:0>) */
#define DN_VRTX_ERR     0x01800000	
#define DN_VRTX_ERR1    0x01000000	/* Detects errors on Down Turbo-Vortex-B
                                           (Hose <3:2>) */
#define DN_VRTX_ERR0    0x00800000	/* Detects errors on Down Turbo-Vortex-A
                                           (Hose <1:0>) */

#define MULT_INTR_ERR   0x00400000
#define UP_HDP_IE       0x00300000
#define UP_HDP_IE1      0x00200000
#define UP_HDP_IE0      0x00100000
#define UP_HOSE_PAR_ERR 0x000f0000
#define UP_HOSE_PKT_ERR 0x0000f000
#define UP_HOSE_OFLO    0x00000f00
#define UN_MBX_STAT     0x000000f0

/* some ipcnse bit pos shifts */
#define UP_HOSE_PAR_SHFT     16
#define UP_HOSE_PKT_SHFT     12
#define UP_HOSE_OFLO_SHFT    8
#define UN_MBX_STAT_SHFT     4

/* ipchst register bit definitions */
#define IDPNSE_HOSE_STAT  0xF
#define IDPNSE_HOSE_RESET 0x80000000
#define IDP_IE		  0x08000000

/* hose status bits */
#define IDPNSE_PWROKT    0x8           /* power ok transitioned */
#define IDPNSE_CBLOK     0x4           /* cblok current */
#define IDPNSE_PWROKC    0x2           /* power ok current */
#define IDPNSE_ERROR     0x1           /* error transitioned */

#endif /* LSB_IOPREG_H */
