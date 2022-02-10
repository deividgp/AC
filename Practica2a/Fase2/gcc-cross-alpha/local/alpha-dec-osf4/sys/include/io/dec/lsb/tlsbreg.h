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
 * @(#)$RCSfile: tlsbreg.h,v $ $Revision: 1.1.16.2 $ (DEC) $Date: 1999/02/09 17:31:51 $
 *
 * Revision 1.2.10.5  1993/12/03  20:46:37  Mark_Bozen
 * 	bmerge prior to submit
 * 	[1993/12/03  20:46:05  Mark_Bozen]
 *
 * 	Add definitions for presto RAM battery replacement date eeprom
 * 	address and string length
 * 	[1993/11/30  19:12:51  Mark_Bozen]
 *
 * Revision 1.2.10.4  1993/11/09  02:32:17  Randall_Brown
 * 	merge of Sterling BL7 changes
 * 	[1993/11/08  23:52:10  Randall_Brown]
 * 
 * Revision 1.2.10.3  1993/09/21  20:50:21  Randall_Brown
 * 	Changed LSBCR1_CID_SHIFT back to gold value of 10 from minor version
 * 	of 11. The minor version is correct but leave as 10 till firmware
 * 	figures out why we are getting this mcheck.
 * 	[1993/09/21  01:36:56  Randall_Brown]
 * 
 * 	Merge of Maint + Sterling HW Support to Gold
 * 	[1993/09/18  22:25:18  Randall_Brown]
 * 
 * Revision 1.2.10.2  1993/05/26  21:58:15  Paula_Long
 * 	submitting the SMP project
 * 	[1993/05/26  05:51:48  Paula_Long]
 * 
 * Revision 1.2.8.2  1993/05/24  19:01:58  Bryan_Panner
 * 	Changed the defined value for a LEP to 0x8001 which is the proper value
 * 	[1993/05/24  18:23:04  Bryan_Panner]
 * 
 * Revision 1.2.13.4  1993/10/06  13:51:19  Peter_S_Thompson
 * 	Make #endif statements ANSI compliant
 * 	[1993/09/30  17:19:09  Peter_S_Thompson]
 * 
 * Revision 1.2.13.3  1993/08/13  20:23:54  Naresh_Dharnidharka
 * 	The lsb_lma_reg struct now includes the MERB, MSYNDB registers.
 * 	[1993/08/09  17:35:28  Naresh_Dharnidharka]
 * 
 * Revision 1.2.13.2  1993/07/13  17:39:12  SJ_Lee
 * 	add #ifndef _LSBREG_H_ to avoid multiple inclusion.
 * 	[1993/06/30  15:01:24  SJ_Lee]
 * 
 * Revision 1.2.6.5  1993/05/11  21:31:53  Jim_Campbell
 * 	LBECR1_CID_SHIFT value is wrong - this incorrectly ignores LSB bystander
 * 	errors.
 * 	[1993/05/11  21:21:39  Jim_Campbell]
 * 
 * Revision 1.2.6.4  1993/05/03  17:42:12  Jim_Campbell
 * 	Add presto RAM battery power switch definition
 * 	[1993/05/03  17:41:17  Jim_Campbell]
 * 
 * Revision 1.2.6.3  1993/04/09  23:27:06  Jim_Campbell
 * 	Move NVram size to here from lsbinit.c
 * 	[1993/04/09  22:55:16  Jim_Campbell]
 * 
 * Revision 1.2.6.2  93/02/16  16:07:05  Jim_Campbell
 * 	Change NVram status bit definitions, correct LEP devtype,
 * 	add ms7bb devtype.
 * 	[93/02/16  16:01:58  Jim_Campbell]
 * 
 * Revision 1.2.2.10  1992/12/14  17:52:18  Ernie_Petrides
 * 	Convert callers of pmap_map_io to use kseg space.
 * 	[92/12/14  16:40:40  Ernie_Petrides]
 * 
 * Revision 1.2.2.9  92/08/25  15:22:24  Jim_Campbell
 * 	Add presto and lsb_eeprom defines
 * 	[92/08/25  15:06:06  Jim_Campbell]
 * 
 * Revision 1.2.2.8  92/08/21  16:27:37  Peter_Mott
 * 	merge with submit branch
 * 	[92/08/21  16:22:41  Peter_Mott]
 * 
 * 	Add node space register and bit definitions needed for parsing errors
 * 	[92/08/21  05:06:44  Peter_Mott]
 * 
 * Revision 1.2.2.7  92/08/20  12:55:52  Peter_Schulter
 * 	Code cleanup: Changed Ruby to DEC7000 and Cobra to DEC4000.
 * 	[92/08/20  10:25:32  Peter_Schulter]
 * 
 * Revision 1.2.2.6  92/06/18  16:06:50  Peter_Mott
 * 	Add LSB register space definitions for LMA.
 * 	[92/06/18  16:06:01  Peter_Mott]
 * 
 * Revision 1.2.2.5  92/02/10  18:31:37  Jim_Campbell
 * 	Fix general bmerge bedlam
 * 	[92/02/10  18:29:50  Jim_Campbell]
 * 
 * Revision 1.2.2.4  92/02/10  17:22:26  Jim_Campbell
 * 	Fix broken comment
 * 	[92/02/10  17:19:49  Jim_Campbell]
 * 
 * Revision 1.2.2.3  92/02/10  16:19:33  Jim_Campbell
 * 	Fixed a broken comment...
 * 	[92/02/10  16:15:33  Jim_Campbell]
 * 
 * Revision 1.2.2.2  92/02/10  13:40:58  Jim_Campbell
 * 	General cleanup, added some comments.
 * 	[92/02/10  13:35:39  Jim_Campbell]
 * 
 * Revision 1.2  92/01/15  01:45:45  devbld_gsf
 * 	Baselevel alpha_bl002
 * 
 * Revision 1.1.2.2  91/12/06  18:02:54  David_Snow
 * 	"Initial version.  File copied from TIN-based Alpha pool."
 * 
 * Revision 1.1.1.2  91/12/06  16:13:58  David_Snow
 * 	Initial version.  File copied from TIN-based Alpha pool.
 * 
 * $EndLog$
 * $EndLog$
 */
/*	"@(#)lsbreg.h	9.3	(ULTRIX/OSF)	10/28/91" */

/************************************************************************
 *									*
 *			Copyright (c) 1991 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any	other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or	reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

/*
 * Revision History: ./dec/io/lsb/lsbreg.h
 *	June-1991 jac:	created this file for the Laser system bus (lsb)
 *
 *
 *************************************************************************/

#ifndef _LSBREG_H_
#define _LSBREG_H_

/* These are the 3 important LSB required registers.
 * The size of this structure is arbitary - but Joe A. has cast
 * iopreg on top of this, so any change in size must
 * be cordinated across all users.
*/
struct lsb_reg {
	unsigned int  	lsb_ldev;	/* Laser device register	*/
	char		lsb_pad0[0x3c];	/* 60 byte pad 04-40		*/
	unsigned int  	lsb_lber;	/* Laser bus error register	*/
	char		lsb_pad1[0x3c];	/* 60 byte pad 44-80		*/
	unsigned int	lsb_lcnr;	/* Laser configuration register	*/
	char		lsb_pad3[0x5fc];/* 1532 byte pad      84-680    */
	unsigned int	lsb_lbesr0;	/* Error Syndrome register	*/
	char		lsb_pad4[0x3c];	/* 60 byte pad      684-6C0     */
	unsigned int	lsb_lbesr1;	/* Error Syndrome register	*/
	char		lsb_pad5[0x3c];	/* 60 byte pad      6C4-700     */
	unsigned int	lsb_lbesr2;	/* Error Syndrome register	*/
	char		lsb_pad6[0x3c];	/* 60 byte pad      704-740     */
	unsigned int	lsb_lbesr3;	/* Error Syndrome register	*/
	char		lsb_pad7[0xf8bc];/* pad    744 - 10000		*/
};

#define LSB_REG_SIZE sizeof(struct lsb_reg) /* 16Kb per node		*/

struct lsb_lma_reg {
	unsigned int  	lma_ldev;	/* Laser device register	*/
	char		lma_pad0[0x3c];	/* 60 byte pad	    04-40	*/
	unsigned int  	lma_lber;	/* Laser bus error register	*/
	char		lma_pad1[0x3c];	/* 60 byte pad	    44-80	*/
	unsigned int	lma_lcnr;	/* Laser configuration register	*/
	char		lma_pad2[0x3c];	/* 60 byte pad	    84-C0	*/
	unsigned int	lma_lvid;	/* Virtual ID register		*/
	char		lma_pad3[0x53c];/* xx byte pad      C4-600      */
	unsigned int 	lma_fadr0;	/* Failing address Reg 0	*/
	char		lma_pad4[0x3c];	/* 60 byte pad	    604-640	*/
	unsigned int 	lma_fadr1;	/* Failing address Reg 1	*/
	char		lma_pad5[0x3c];	/* 60 byte pad	    644-680	*/
	unsigned int	lma_lbesr0;	/* Error Syndrome register	*/
	char		lma_pad6[0x3c];	/* 60 byte pad      684-6C0     */
	unsigned int	lma_lbesr1;	/* Error Syndrome register	*/
	char		lma_pad7[0x3c];	/* 60 byte pad      6C4-700     */
	unsigned int	lma_lbesr2;	/* Error Syndrome register	*/
	char		lma_pad8[0x3c];	/* 60 byte pad      704-740     */
	unsigned int	lma_lbesr3;	/* Error Syndrome register	*/
	char		lma_pad9[0x3c]; /* 60 byte pad      744-780     */
	unsigned int	lma_rsvd;	/* Reserved TLSB CSR Space 	*/
	char		lma_pad10[0x107c];/* xx byte pad    784-1800    */
	unsigned int	lma_secr;	/* Serial EEPROM Control/Data reg*/
	char		lma_pad11[0x3c];/* 60 byte pad      1804-1840   */
	unsigned int	lma_mir;	/* Memory Interleave register 	*/
	char		lma_pad12[0x3c];/* 60 byte pad      1844-1880   */
	unsigned int	lma_mcr;	/* Memory Config. register      */
	char		lma_pad13[0x3c];/* 60 byte pad      2004-2040   */
	unsigned int	lma_stair;	/* Self-Test Address Isolation  */
	char		lma_pad14[0x3c];/* 60 byte pad      2044-2080   */
      	unsigned int	lma_ster;	/* Selftest Error Register 	*/
	char		lma_pad15[0x3c];/* 60 byte pad      2084-20C0   */
	unsigned int	lma_mer;	/* Memory Error Register 	*/
	char		lma_pad16[0x3c];/* 60 byte pad      20C4-2100   */
	unsigned int	lma_mdra;	/* Memory diag Register	A	*/
	char		lma_pad17[0x3c];/* 60 byte pad      2104-2140   */
	unsigned int	lma_mdrb;	/* Memory diag Reg. B		*/
        char            lma_pad18[0x10140-0x19C4]; /* fill   19C4-10140 */
        unsigned int    lma_ddr0;       /* Data Diagnostic reg 0 10140-10144 */
        char            lma_pad19[0x3ffc];          /*  fill  10144-14140 */
        unsigned int    lma_ddr1;       /* Data Diagnostic reg 1 14140-14144 */
        char            lma_pad20[0x3ffc];         /*  fill  14144-18140 */
        unsigned int    lma_ddr2;       /* Data Diagnostic reg 2 18140-18144 */
        char            lma_pad21[0x3ffc];         /*  fill  18144-1C140 */
        unsigned int    lma_ddr3;       /* Data Diagnostic reg 3 1C140-1C144 */
        char            lma_pad22[0x1ffc0-0x1c144];/*  fill  1C144-1FFC0 */
};

#define LSB_LMA_REG_SIZE sizeof(struct lsb_lma_reg) /* 64Kb per node	*/

#ifdef	KERNEL
extern struct lsb_reg lsbnode[];
#endif /*  KERNEL */

/* IOP Node address is absolute for RUBY */
#define LSB_IOP_NODE 8


#define LSB_WINDOW4_BASE 0x8000000000L
#define LSB_WINDOW_OFFSET 0x1000000000L

/* LSB flags (taken from xmireg...)	*/
#define LSBF_SST 0x1		/* do node reset before call init	*/
#define LSBF_DEVICE 0x4		/* is a device in the config file	*/
#define LSBF_CONTROLLER 0x8	/* is a controller in config file	*/
#define LSBF_ADAPTER  0x10	/* adapters...uba's etc			*/
#define LSBF_NOCONF 0x1000	/* Isn't config'd			*/

/* LSB device register */

#define	LSB_IOP_LDEV	0x00002000	/* LSB IOP device */
#define	LSBLDEV_TYPE	0x0000ffff	/* LSB device type field */
#define	LSBLDEV_REV	0xffff0000	/* LSB device revision field */
#define	TLSB_ITIOP_LDEV	0x00002020	/* TLSB ITIOP device */

/* LSB device types defined */

#define LSB_PROCESSOR	0x8000		/* generic processor type 	*/
#define	LSB_LEP		0x8010		/* 1 EV5 processor, 1M Cache	*/
#define	LSB_LEP_4	0x8011		/* 1 EV5 processor, 4M Cache	*/
#define	LSB_LEP_16	0x8012		/* 1 EV5 processor, 16M Cache	*/
#define	LSB_TLEP	0x8013		/* 2 EV5 processors, 1M Cache	*/
#define	LSB_TLEP_4	0x8014		/* 2 EV5 processors, 4M Cache	*/
#define	LSB_TLEP_16	0x8015		/* 2 EV5 processors, 16M Cache	*/
#define LSB_LEP6_4	0x8024		/* 1 EV6 processors, 4M Cache	*/
#define LSB_TLEP6_4	0x8025		/* 2 EV6 processors, 4M Cache	*/
#define	LSB_IOP		0x2000		/* Laser I/O module		*/
#define	TLSB_ITIOP	0x2020		/* Laser I/O module		*/
#define	LSB_MEM		0x4000		/* Laser memory module		*/
#define	LSB_BBMEM	0x4002		/* Laser Battery backed up memory*/
#define	TLSB_MEM	0x5000		/* TurboLaser memory module	*/

/*
 * Laser System Bus error definitions (LBER)
 * (these lousy abbrevations are what is used in the LSB spec...
*/
#define TLSB_ATCE	0x00000001	/* Address Transmit Check Error	*/
#define TLSB_APE	0x00000002	/* Address Parity Error 	*/
#define TLSB_BBE	0x00000004	/* Bank Busy Violation 		*/
#define TLSB_LKTO	0x00000008	/* Bank Lock Timeout		*/
#define TLSB_NAE	0x00000010	/* No Acknowledge Error		*/
#define TLSB_RTCE	0x00000020	/* Request Transmit Check Error	*/
#define TLSB_ACKTCE	0x00000040	/* Acknowledge Transmit Check Error */
#define TLSB_MMRE	0x00000080	/* Mem. Mapping Register Error	*/
#define TLSB_FNAE	0x00000100	/* Fatal No Ack. Error		*/
#define TLSB_REQDE	0x00000200	/* Request Deassertion Error	*/
#define TLSB_ATDE	0x00000400	/* Address Transmitter during Error */
#define TLSB_UDE	0x00010000	/* Uncorrectable Data Error 	*/
#define TLSB_CWDE	0x00020000	/* Correctable Write Data Error	*/
#define TLSB_CRDE	0x00040000	/* Correctable Read Data Error	*/
#define TLSB_CWDE2	0x00080000	/* 2nd Correctable Write Data Error */
#define TLSB_DTDE	0x01000000	/* Data Transmitter during Error */
#define TLSB_FDTCE	0x02000000	/* Fata Data Transmit check Error */
#define TLSB_UACKE	0x04000000	/* Unexpected Ack 		*/
#define TLSB_ABTCE	0x08000000	/* Address Bus Transmit Check Error */
#define TLSB_DCTCE	0x10000000	/* Data Control Transmit Check Error */
#define TLSB_SEQE	0x20000000	/* Sequence Error 		*/
#define TLSB_DSE	0x40000000	/* Data status Error 		*/
#define TLSB_DTO	0x80000000	/* Data Timeout Error 		*/
/* Need new defines for TL - NBD */

/* TLBER register definitions for Turbolaser error parsing */
#define TLBER_ATCE      0x00000001      /* Address Transmit Check Error */
#define TLBER_APE       0x00000002      /* Address Parity Error         */
#define TLBER_BBE       0x00000004      /* Bank Busy Violation          */
#define TLBER_LKTO      0x00000008      /* Bank Lock Timeout            */
#define TLBER_NAE       0x00000010      /* No Acknowledge Error         */
#define TLBER_RTCE      0x00000020      /* Request Transmit Check Error */
#define TLBER_ACKTCE    0x00000040      /* Acknowledge Transmit Check Error */
#define TLBER_MMRE      0x00000080      /* Mem. Mapping Register Error  */
#define TLBER_FNAE      0x00000100      /* Fatal No Ack. Error          */
#define TLBER_REQDE     0x00000200      /* Request Deassertion Error    */
#define TLBER_ATDE      0x00000400      /* Address Transmitter during Error */
#define TLBER_DE_MASK   0x000f0000	/* Data error bits mask */
#define TLBER_UDE       0x00010000      /* Uncorrectable Data Error     */
#define TLBER_CWDE      0x00020000      /* Correctable Write Data Error */
#define TLBER_CRDE      0x00040000      /* Correctable Read Data Error  */
#define TLBER_CWDE2     0x00080000      /* 2nd Correctable Write Data Error */
/*
 * Data Syndrome Bits - A status bit set when register TLESR? contains
 * status relative to the current data error.
 */
#define TLBER_DS_MASK	0x00f00000	/* Data Syndrome bits mask	*/
#define TLBER_DS0	0x00100000	/* Data Syndrome 0		*/
#define TLBER_DS1	0x00200000	/* Data Syndrome 1		*/
#define TLBER_DS2	0x00400000	/* Data Syndrome 2		*/
#define TLBER_DS3	0x00800000	/* Data Syndrome 3		*/

#define TLBER_DTDE      0x01000000      /* Data Transmitter during Error */
#define TLBER_FDTCE     0x02000000      /* Fata Data Transmit check Error */
#define TLBER_UACKE     0x04000000      /* Unexpected Ack               */
#define TLBER_ABTCE     0x08000000      /* Address Bus Transmit Check Error */
#define TLBER_DCTCE     0x10000000      /* Data Control Transmit Check Error */
#define TLBER_SEQE      0x20000000      /* Sequence Error               */
#define TLBER_DSE       0x40000000      /* Data status Error            */
#define TLBER_DTO       0x80000000      /* Data Timeout Error           */
#define TLBER_FAULT	0xfe0003e7	/* Bits which assert TLSB FAULT */

#define TLESR_TCE	0x00020000

#define	TCCERR_FAULT	0x00000100	/* TCCERR TLSB fault asserted   */
#define	TCCERR_SYSFAULT	0x00000020	/* TCCERR TLSB sysfault		*/

#define	TLAERR_SYSFAULT	0x00000100	/* TL5/TL56 AERR SYSFAULT bit	*/

#define TLFADR_ADRV	0x01000000	/* TLFADR Address Valid		*/
#define TLFADR_CMD	0x00070000	/* TLFADR command mask <18:16>	*/
#define TLFADR_READ	0x00020000	/* READ				*/
#define TLFADR_WRITE	0x00030000	/* WRITE			*/
#define TLFADR_RD_LOCK	0x00040000	/* READ LOCK			*/
#define	TLFADR_WRT_LOCK	0x00050000	/* WRITE LOCK			*/

#define LSB_E		0x00000001	/* Error line is asserted	*/
#define LSB_UCE		0x00000002	/* Uncorrectable data error	*/
#define LSB_UCE2	0x00000004	/* 2nd uncorrectable data error	*/
#define LSB_CE		0x00000008	/* Correctable data error	*/
#define LSB_CE2		0x00000010	/* 2nd correctable data error	*/
#define LSB_CPE		0x00000020	/* Command parity error		*/
#define LSB_CPE2	0x00000040	/* 2nd command parity error	*/
#define LSB_CDPE	0x00000080	/* CSR data parity error	*/
#define LSB_CDPE2	0x00000100	/* 2nd CSR data parity error	*/
#define LSB_TDE		0x00000200	/* transmitter during error (?)	*/
#define LSB_STE		0x00000400	/* STALL error			*/
#define LSB_CNFE	0x00000800	/* CNF error			*/
#define LSB_NXAE	0x00001000	/* Non-existent address error	*/
#define LSB_CAE		0x00002000	/* CA error			*/
#define LSB_SHE		0x00004000	/* SHARED error			*/
#define LSB_DIE		0x00008000	/* DIRTY error			*/
#define LSB_DTCE	0x00010000	/* Data transmit check error	*/
#define LSB_CTCE	0x00020000	/* Control transmit check error	*/
#define LSB_NSES	0x00040000	/* Node-specific error summary	*/
/*
 * Laser System Bus configuration register definitions
*/

#define LSB_LOFE	0x80000000	/* Lock on first error 		*/
#define LSB_NRST	0x40000000	/* Node reset			*/
#define LSB_HALT_B	0x00200000	/* halt Cpu 1			*/
#define LSB_HALT_A	0x00100000	/* halt Cpu 0			*/
#define LSB_STF_B	0x00002000	/* Self Test Fail Cpu 1		*/
#define LSB_STF_A	0x00001000	/* Self Test Fail Cpu 0		*/

/*
 * Laser Information Base Repair register (IBR)
*/
#define LSB_SCLK	0x000000004	/* Serial clock bit		*/
#define LSB_XMT_SDAT	0x000000002	/* Serial data transmit bit	*/
#define LSB_RCV_SDAT	0x000000001	/* Serial data receive bit	*/
#define LSB_EEPROM_SREAD 0x0000000A0	/* EEPROM slave read mask	*/
#define LSB_EEPROM_SWRITE 0x0000000A1	/* EEPROM slave write mask	*/

#define LSB_EEPROM_WRITE 0
#define LSB_EEPROM_READ 1

/*
 * Presto defines for lsb
*/
#define LSB_EEPROM_PRESTO	0x7EC	/* adr of status location in eeprom */
#define RUBY_CACHE_SIZE	0x400000L	/* Used to force bcach evictions */
#define MS700_NVRAM_SIZE 0x01000000	/* The MS7bb module is 16 MB	*/

#define LSB_PRESTO_BAT_OK	0x02
#define LSB_PRESTO_CHARGING	0x04
#define LSB_PRESTO_VBB_RESET	0x08
#define LSB_PRESTO_INIT		0x10
#define LSB_PRESTO_BAT_CONN	0x40	/* The manually operated battery
					 * switch is turned on		*/
#define LSB_EEPROM_PRESTO_EXP	0x7E4	/* adr of battery replacement date 
                                           in eeprom */
#define PRESTO_EXP_SIZE		0x08	/* length of battery replacement date
				           string */
/*
 * Number of uS to wait between wiggleing the EEPROM bits...
*/
#define LSB_EEPROM_BITWAIT 5	/* long wait time (stolen from console)	*/
#define LSB_EEPROM_SBITWAIT 1	/* short wait time (dido)		*/

struct lsbsw {

	int	lsb_ldev;		/* LSB device type */
	char	*lsb_name;		/* name of the device*/
	int	(**probes)();		/* funtions to probe at boot time */
	int	(*lsb_reset)();		/* reset routine for device */
	short	lsb_flags;		
};

/*
 * lsbdata is a structure modeled after the bsd xmidata.
*/

#define MAX_LSB_NODE	9

struct lsbdata {
	struct lsbdata *next;		/* points to the next lsbdata. For */
					/* the forseeable future there is  */
					/* only one			*/
	int lsbnum;			/* logical # of lsb, starts at 0*/
	struct lsb_reg *lsbvirt[MAX_LSB_NODE]; /* pointers to lsb slots */
	struct lsb_reg *lsbphys;	/* not used in alpha		*/
	struct lsb_reg *cpu_lsb_addr; 	/* the virtual base addr for the slot*/
					/* the cpu is in		*/
	int (**lsbvec_page)();
	int lsbnodes_alive;
	int lsbintr_dst;		/* 'master' CPU that gets interrupts */
					/* This is a bit mask corresponding  */
					/* to slot number.		*/
	int lsb_err_cnt;		
	unsigned int lsbilast_err_time;
	struct {
		struct lsbsw *plsbsw;
		int lsberr;
		int lsberr1;
	} lsberr[9];
};

extern struct lsbdata *head_lsbdata;
extern struct lsbdata *get_lsb();

#ifdef	__alpha
/*
 * The following node size was 17K in the XMI (because of CIXCD).
 * The LSB spec says LSB CSR space is 64K...
*/
#define LSBNODE_SIZE	65536

/* The total LSB bus size is just LSBNODE_SIZE * number of slots (9)	*/
#define LSBBUS_SIZE	(LSBNODE_SIZE *  MAX_LSB_NODE)

/*
 * The LSB physical starting address is processor specific...
*/
#if	defined(DEC21000)
#define LSB_START_PHYS 0x000000ff88000000
#endif /* DEC21000 */

#endif /* __alpha */

#ifdef __mips
#define LSBNODE_SIZE	4096	/* Not used - and not mapped on mips */
#endif /* __mips */


#define SCB_LSB_LWOFFSET(lsb_nodenum,level) \
	((lsb_nodenum << 2) | level)

#define SCB_LSB_VEC_ADDR(lsbdata,lsbnumber,lsb_nodenum,level) \
	((lsbdata->lsbvec_page)+(((lsb_nodenum << 2) | level)/4))

#define SCB_LSB_ADDR(lsbdata) \
	((lsbdata->lsbvec_page))


/*
 * Define LSB register bits to be used in error parsing machine
 * checks 
 */
#define LBER_E		( 1 << 0x00 )
#define LBER_UCE	( 1 << 0x01 )
#define LBER_UCE2	( 1 << 0x02 )
#define LBER_CE		( 1 << 0x03 )
#define LBER_CE2	( 1 << 0x04 )
#define LBER_CPE	( 1 << 0x05 )
#define LBER_CPE2	( 1 << 0x06 )
#define LBER_CDPE	( 1 << 0x07 )
#define LBER_CDPE2	( 1 << 0x08 )
#define LBER_TDE	( 1 << 0x09 )
#define LBER_STE	( 1 << 0x0A )
#define LBER_CNFE	( 1 << 0x0B )
#define LBER_NXAE	( 1 << 0x0C )
#define LBER_CAE	( 1 << 0x0D )
#define LBER_SHE	( 1 << 0x0E )
#define LBER_DIE	( 1 << 0x0F )
#define LBER_DTCE	( 1 << 0x10 )
#define LBER_CTCE	( 1 << 0x11 )
#define LBER_NSES	( 1 << 0x12 )


#define LBECR0_CA 	0xFFFFFFFF
#define LBECR1_CA 	0x0000007F
#define LBECR1_CA_CMD 	0x00000038
/* moved - #define LBECR1_CID	0x00000780 */
/* defunct - #define LBECR1_RID	0x00007800 */
#define LBECR1_CID	0x00007800
#define LBECR1_CNF	0x00008000
#define LBECR1_SHARED	0x00010000
#define LBECR1_DIRTY	0x00020000
#define LBECR1_DCYCLE	0x000C0000

/* moved - #define LBECR1_CID_SHIFT	0x07 */
#define LBECR1_CID_SHIFT	0x0A /* bkp fix find out source of this on secondary startup */

#define LBECR1_CA_CMD_SHIFT	0x03

#define LBECR1_CA_READ		(0x00 << LBECR1_CA_CMD_SHIFT)
#define LBECR1_CA_WRITE		(0x01 << LBECR1_CA_CMD_SHIFT)
#define LBECR1_CA_RSVD1		(0x02 << LBECR1_CA_CMD_SHIFT)
#define LBECR1_CA_WRITE_VICTIM	(0x03 << LBECR1_CA_CMD_SHIFT)
#define LBECR1_CA_READ_CSR	(0x04 << LBECR1_CA_CMD_SHIFT)
#define LBECR1_CA_WRITE_CSR	(0x05 << LBECR1_CA_CMD_SHIFT)
#define LBECR1_CA_RSVD2		(0x06 << LBECR1_CA_CMD_SHIFT)
#define LBECR1_CA_PRIVATE	(0x07 << LBECR1_CA_CMD_SHIFT)



#define LMERR_PMAPPE	0x000F
#define LMERR_BTAGPE	0x0010
#define LMERR_BSTATPE	0x0020
#define LMERR_BMAPPE	0x0040
#define LMERR_BDATASBE	0x0080
#define LMERR_BDATADBE	0x0100
#define LMERR_ARBCOL	0x0200
#define LMERR_ARBDROP	0x0400
#define LMERR_EDALTO	0x0800


#endif
