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
 * @(#)$RCSfile: errlog.h,v $ $Revision: 1.1.139.4 $ (DEC) $Date: 1998/10/30 20:05:20 $
 */


/*
 * Old logs before move from sys/errlog.h to dec/binlog/errlog.h
 *
 * Revision 4.5.1.2  91/12/16  09:25:59  Gary_Dupuis
 * 	Merge with 4.5
 * 	[91/12/12  11:05:30  Gary_Dupuis]
 * 
 * 	91/12/06	Gary Dupuis
 * 	Added support for Maxine (PERSONAL_DECstation)
 * 	1) Add define for error and status type for MAXine and 3MAX+.
 * 	   ELESR_KN03 and ELESR_KN02CA.
 * 	2) Add defines formemory control types for the 3MAX+ and
 * 	   MAXine. ELMCNTR_KN03 and ELMCNTR_KN02CA.
 * 	3) Define error log structures for the MAXine and 3MAX+.
 * 	   el_esrkn02ba and el_esrkn02ca.
 * 	4) Add entries to the el_esr structure for the MAXine and the
 * 	   3MAX+.
 * 	[91/12/12  11:03:05  Gary_Dupuis]
 * 
 * Revision 4.5.5.2  92/01/19  12:25:20  Scott_Cranston
 * 	- Cleaned up, removed unsupported devices (VAX stuff).
 * 
 * 	- Split ino two files vendor dependent (errlog.h) and vendor
 * 	  independent (binlog.h).
 * 
 * Revision 4.5  91/11/27  15:50:41  devbld_zk3
 * 	Incbaselevel update
 * 
 * Revision 4.2  91/09/19  23:04:08  devbld
 * 	Adding ODE Headers
 * 
 * Revision 4.2.2.3  91/11/20  14:10:30  Hal_Project
 * 	Changed dec/machine/mips include to machinine/
 * 	[91/11/18  00:37:18  Donald_Dutile]
 * 
 * Revision 4.2.2.2  91/10/23  15:09:05  William_Burns
 * 	Merge from ODE/TIN: revision 3.5.9.2
 * 	date: 91/10/17 21:12:28;  author: devrcs;  state: Exp;  lines added/del: 4/2
 * 	sccs rev: 3.7;  orig date: 91/10/02 08:20:10;  orig author: fred
 * 	Fred Canter - fix keywords.
 * 	[91/10/23  09:13:47  William_Burns]
 * 
 */

#ifndef __ERRLOG__
#define __ERRLOG__ 

#include <sys/types.h>
#include <sys/time.h>
#include <dec/binlog/binlog.h>
#include <io/common/devio.h>
#include <io/dec/bi/bireg.h>
#include <io/dec/sysap/mscp_msg.h>

#ifdef __alpha
#include <io/dec/scsi/alpha/scsivar.h>
#include <io/dec/scsi/alpha/scsireg.h>
#endif /* __alpha */


/* Digital Equiptment Corp specific binary event log record definitions */


/* for backward compatibility with TIN and ULTRIX */
#define ealloc (struct el_rec *)binlog_alloc
#define EL_FULL (struct el_rec *)0
#define EVALID(erp) binlog_valid((char *)erp);
#define EL_MAXRECSIZE  8192L       /*  bumped to 8Kb, used by uerf */
#define EL_MAXAPPSIZE   (EL_MAXRECSIZE - EL_MISCSIZE)






/* machinecheck and exception frame types (el_sub_id.subid_type)*/

#define	ELESR_5400	1			/* DS5400 ESR	*/
#define ELESR_kn01      2                       /* DS2100/3100 ESR */
#define	ELESR_kn02	3			/* DS5000 ESR   */
#define	ELESR_5500	4			/* DS5500 ESR	*/
#define ELESR_5100      5                       /* DS5100 ESR   */
#define ELESR_KN02BA	6			/* DS5000_100 ESR */
#define ELESR_KN03      7                       /* DS5000_300 ESR */
#define ELESR_KN02CA    8                       /* DSMAXINE ESR   */
#define ELESR_ALPHA	9	/* generalized subid type for ALPHA */
				/* processors, to be distinguished by */
				/* subid ctldevtyp */

/****PRM: Need to remove RUBY and COBRA, with the advent of ALPHA */ 
#define ELESR_DEC7000      9       /* Dec7000 ESR - machine */
#define ELESR_COBRA	10	/* Cobra ESR - machine */
				/* check */
/****PRM: Need to remove RUBY and COBRA, with the advent of ALPHA */ 

/* generalized exception fault types, ELCT_EXPTFLT, (el_sub_id.subid_type)*/
#define ELEXTYP_HARD	1	/* System Hard failure, for ALPHA this */
				/* accounts for 660 exceptions. */
#define ELEXTYP_MCK	2	/* Machine check error, for ALPHA this */
				/* accounts for 670 exceptions. */
#define ELEXTYP_SYS_CORR 3	/* System correctable error, for ALPHA this */
				/* accounts for 620 exceptions. */
#define ELEXTYP_CORR ELEXTYP_SYS_CORR /* compatability */
#define ELEXTYP_PROC_CORR 4	/* Processor correctible error, for ALPHA */
				/* this accounts for 630 exceptions. */


/* stray intr types (el_sub_id.subid_type) */
   /*  this was VAX specific stuff */


/* console timeout entry types (el_sub_id.subid_type) */
   /*  this was VAX specific stuff */


/* device error types (el_sub_id.subid_type) */
#define ELDEV_MSCP	1
#define ELDEV_REGDUMP	2
#define	ELDEV_SCSI	3

/* device controller error/event types (el_sub_id.subid_type) */
#define ELCI_ATTN	1
#define ELCI_LPKT	2
#define	ELUQ_ATTN	3
#define ELMSCP_CNTRL	6
#define ELTMSCP_CNTRL	7
#define ELMSI_ATTN	8
#define ELMSI_LPKT	9
#define	ELSCSI_CNTRL	10
#define ELXMI_XNA       12
#define ELVME_DEV_CNTL  13          /* general purpose VME dev/ctrl packet */
#define ELFZA		14
#define ELCI_RDCNT      15
#define ELFTA           16
#define _RM_ERRLOG_DEF          /* ease transition for rm_spur.c */ 
#define ELRMSPUR        17                                          

#define ELMCHAN_CNTRL	18

/* adapter error types (el_sub_id.subid_type) */
#define ELADP_VBA       6                       /* VMEbus adapters */
#define ELADP_LAMB      7                       /* LSB to XMI */
#define ELADP_FLAG      8                       /* LSB to Futurebus */
#define ELADP_IOP       9                       /* LSB IOP */
#define ELADP_PCIA      10                      /* TLSB to PCI */

/* bus error types (el_sub_id.subid_type) */

/* stack dump error types (el_sub_id.subid_type) */
#define ELSTK_KER	1
#define ELSTK_INT	2
#define ELSTK_USR	3

/* Soft & Hard error types (el_sub_id.subid_type) */

/* Vector error types (el_sub_id.subid_type) */

/* State, ELCT_STATE, entry types (el_sub_id.subid_type) */
#define ELST_LAST_FAIL	1	/* a general packet created when a */
				/* detected error is cleaned up and */
				/* other error state remains, which */
				/* was not accounted for by error */
				/* parsing. Distinguished by ctldevtyp */
#define ELST_POWER_FAIL	2	/* A packet create when loss of power */
				/* is detected. Distinguished by */
				/* ctldevtyp */ 
#define ELST_CONFIG	3	/* A packet create a boot time */
				/* describing the system */
				/* configuration. Distinguished by */
				/* ctldevtyp */ 

/* (Un)correctable environmentals error types (el_sub_id.subid_type) */
#define ELENV_UNCORR    2       /* uncorrectable environmental */
#define ELENV_CORR      6       /* correctable environmental */

/* vector processor types (el_sub_id.subid_ctldevtyp) */

/* processor variations (el_sub_id.subid_ctldevtyp). */
#define	ELMACH_5400	1	/* DS5400 ESR	*/
#define ELMACH_kn01      2       /* DS2100/3100 ESR */
#define	ELMACH_kn02	3	/* DS5000 ESR   */
#define	ELMACH_5500	4	/* DS5500 ESR	*/
#define ELMACH_5100      5       /* DS5100 ESR   */
#define ELMACH_KN02BA	6	/* DS5000_100 ESR */
#define ELMACH_KN03      7       /* DS5000_300 ESR */
#define ELMACH_KN02CA    8       /* DSMAXINE ESR   */

/* ALPHA processor/platform variations (el_sub_id.subid_ctldevtyp). */
/****PRM: Need to remove 'COBRA' type processor names. replace with */
/*proper cpu codes. */

#define ELMACH_COBRA		9		/* COBRA Processor type	    */
#define ELMACH_DEC7000		10		/* DEC7000 Processor type   */
#define ELMACH_LASER		11		/* LASER Platform type	    */
#define ELMACH_DEC_3000_500	12		/* FLAMINGO Processor type  */
#define ELMACH_DEC_3000_400	13		/* SANDPIPER Processor type */
#define ELMACH_DEC_3000_300	14		/* PELICAN Processor type   */
#define ELMACH_DEC_2000_300	15		/* JENSEN Processor type    */
#define ELMACH_DEC_4000_810	16		/* SABLE Processor type	    */
#define ELMACH_DEC_2000_MUS	17		/* MUSTANG Processor type burnsfix */
#define ELMACH_DEC_2000_AVI	18		/* AVANTI Processor type burnsfix */
#define ELMACH_DEC_AXPPCI33	19		/* NONAME Processor type    */
#define ELMACH_DEC_1000		20		/* DEC1000 Processor type   */ 
#define ELMACH_DEC_2100_C500	21		/* GAMMA Processor type     */
#define ELMACH_DEC21000         22              /* TLASER Processor type    */
#define ELMACH_EB64P		23		/* EB64+ Processor type     */
#define ELMACH_EB66		24		/* EB66 Processor type      */
#define ELMACH_DEC_AXPVME64	25		/* AXPvme system type       */
#define ELMACH_EB164		26		/* EB164 Processor type */
#define ELMACH_DECEV45_PBP	27		/* LEGO K2 Processor type */
#define ELMACH_DEC_1000A        28		/* NORITAKE Processor type  */
#define ELMACH_DEC_ALPHAVME224  29              /* CORTEX EV45 VME processor type  */
#define ELMACH_DEC_4100		30		/* RAWHIDE		*/
#define ELMACH_DECEV56_PBP	31		/* TAKARA Processor type    */
#define ELMACH_ALPHABOOK        32              /* ALPHAbook 1 Processor type */
#define ELMACH_DEC_ALPHAVME320  33              /* Yukon EV56 VME Processor type */
#define ELMACH_KN20AA  		34              /* PINKASA, PINTAKE, ALCOR */
#define ELMACH_DEC_6600		35		/* EV6-Tsunami platform */
#define ELMACH_DMCC_EV6		36		/* DMCC EV6 Passive BP CPU */

/****PRM: Need to remove 'COBRA' type processor names. replace with */

/* MIPS mem cntl types (el_sub_id.subid_ctldevtyp) */
#define ELMCNTR_PMAX    13                      /* PMAX mem. cntl. */
#define	ELMCNTR_5400	16			/* DS5400 mem cntl. */
#define	ELMCNTR_kn02	18			/* DS5000 (3max) mem cntl. */
#define	ELMCNTR_5500	19			/* DS5500 mem cntl. */
#define ELMCNTR_5100    25                      /* DS5100 mem cntl. */
#define ELMCNTR_KN02BA	28			/* DS5000_100 mem. cntl. */
#define ELMCNTR_KN03    29                      /* DS5000_300 mem. cntl. */
#define ELMCNTR_KN02CA  30                      /* DSMAXINE mem. cntl. */
#define ELMCNTR_LASER   31			/* Laser bus memory */
#define ELMCNTR_DEC4000 32			/* DEC 4000 memory */

/* ci hardware port types (el_sub_id.subid_ctldevtyp) */
#define ELCIHPT_CI780   2
#define ELCIHPT_CI750   3
#define ELCIHPT_CIBCI   5
#define ELCIHPT_CIBCABA 10
#define ELCIHPT_CIBCAAA 11
#define ELCIHPT_CIXCD   14
#define ELCIHPT_CIMNA   16
#define ELCIHPT_CITCA   17

/* msi hardware port type (el_sub_id.subid_ctldevtyp) */
#define ELMSIHPT_SII	32

/* bvp hardware port types (el_sub_id.subid_ctldevtyp) */

/* uq hardware port types (el_sub_id.subid_ctldevtyp) */
#define ELUQHPT_UDA50   0
#define ELUQHPT_RC25    1
#define	ELUQHPT_RUX50	2		
#define	ELUQHPT_TK50	3		
#define	ELUQHPT_TU81	5
#define ELUQHPT_UDA50A  6
#define	ELUQHPT_RQDX	7
#define ELUQHPT_KDA50   13
#define	ELUQHPT_TK70	14
#define	ELUQHPT_RV20	15
#define	ELUQHPT_RRD50	16
#define ELUQHPT_KDB50   18
#define	ELUQHPT_RQDX3	19
#define ELUQHPT_KDM70   27

/* controller types mscp (el_sub_id.subid_ctldevtyp) */
#define	ELMPCT_HSC50	1		
#define ELMPCT_UDA50    2
#define ELMPCT_RC25     3
#define ELMPCT_VMS      4
#define	ELMPCT_TU81	5
#define ELMPCT_UDA50A   6
#define	ELMPCT_RQDX	7
#define ELMPCT_TOPS     8
#define	ELMPCT_TK50	9		
#define	ELMPCT_RUX50	10		
#define	ELMPCT_KFBTA	12
#define	ELMPCT_TK70	14
#define	ELMPCT_RV20	15
#define	ELMPCT_RRD50	16
#define	ELMPCT_KDB50	18
#define	ELMPCT_RQDX3	19
#define	ELMPCT_RQDX4	20
#define	ELMPCT_SII_DISK	21
#define	ELMPCT_SII_TAPE	22
#define	ELMPCT_SII_DISK_TAPE	23
#define	ELMPCT_SII_OTHER	24
#define ELMPCT_KDM70    27
#define	ELMPCT_HSC70	32
#define	ELMPCT_HSB50	64
#define	ELMPCT_RF30	96
#define	ELMPCT_RF71	97
#define ELMPCT_ULTRIX   248


/* controller types SCSI (el_sub_id.subid_ctldevtyp) */
#define	ELSCCT_5380	1
#define	ELSCCT_SII	2
#define ELSCCT_ASC	3
#define ELSCCT_KZQ      4

/* disks types mscp (el_sub_id.subid_ctldevtyp) */
#define ELDT_RA80	1
#define ELDT_RC25	2
#define ELDT_RCF25	3
#define ELDT_RA60	4
#define ELDT_RA81	5
#define ELDT_RD51	6
#define ELDT_RX50	7
#define ELDT_RD52	8
#define ELDT_RD53	9
#define ELDT_RX33	10
#define ELDT_RA82	11
#define ELDT_RD31	12
#define ELDT_RD54	13
#define ELDT_RRD50	14
#define ELDT_RV20	15
#define ELDT_RD32	15
/* unused	 	16 */
#define ELDT_RX18	17
#define ELDT_RA70	18
#define ELDT_RA90	19
#define ELDT_RX35	20
#define ELDT_RF30	21
#define ELDT_RF71	22
#define ELDT_SVS00	23
#define ELDT_RD33	24
#define ELDT_ESE20	25
#define ELDT_RRD40	26
#define ELDT_RF31	27
#define ELDT_RF72	28
#define ELDT_RA92	29
#define ELDT_RA72	37
#define ELDT_RA71	40

/* tapes types tmscp (el_sub_id.subid_ctldevtyp) */
#define ELTT_TA78	1
#define ELTT_TU81	2
#define ELTT_TK50	3
#define ELTT_TA81	4
#define ELTT_TA79	5
#define ELTT_TA90	7
#define ELTT_RV60	8
#define ELTT_SVS00	9
#define ELTT_TA91	12
#define ELTT_TK70	14
#define ELTT_TRV20	15

/* disks types SCSI (el_sub_id.subid_ctldevtyp) */
#define	ELSDT_RX23	1
#define ELSDT_RX33	2
#define	ELSDT_RZ22	3
#define	ELSDT_RZ23	4
#define	ELSDT_RZ55	5
#define	ELSDT_RZ56	6
#define	ELSDT_RRD40	7
#define	ELSDT_RZxx	8
#define ELSDT_RZ24      9
#define ELSDT_RZ57      10
#define ELSDT_RZ23L     11
#define ELSDT_RRD42	12
#define ELSDT_RX26	13
#define ELSDT_RZ25	14
#define ELSDT_RZ58	15
#define ELSDT_RZ24L     16
#define ELSDT_RZ26	17
#ifdef ALPHAADU
/*
 * This was changed from 16 to accomodate new disk types.  Old ADU log entries
 * may now report the RZ01 as an RZ24L.
 */
#define ELSDT_RZ01      18
#endif

/* tapes types SCSI (el_sub_id.subid_ctldevtyp) */
#define	ELSTT_TZ30	1
#define	ELSTT_TZK50	2
#define	ELSTT_TZxx	3
#define ELSTT_TLZ04     4
#define ELSTT_TZ05      5
#define ELSTT_TZ07	6
#define ELSTT_TZK08	7
#define	ELSTT_TZK10	8
#define ELSTT_TKZ09	9


/* VMEbus adapter types (el_sub_id.subid_ctldevtype) */
#define ELDT_3VIA       1                      /* 3max VME adapter */
#define ELDT_MVIA       2                      /* Mipsfair-2 VME adapter */
#define ELDT_XBIA       3                      /* Cmax VME adapter (XMI) */
#define ELDT_TC300      4                      /* DAA TC300/VME (TC-VME) */

/* panic exception/fault errcodes (el_sub_id.subid_type) */

/* elmemerr.type */
#define ELMETYP_CRD	1
#define ELMETYP_RDS	2
#define ELMETYP_CNTL	3
#define ELMETYP_WMASK	4
#define ELMETYP_PAR	5
#define ELMETYP_NXM	6

/* el_sub_id.subid_num  for machine check is cpu number */


/* sca( scs, bvp, uq, ci ppd, ci, msi ) event codes definition
 * ( el_sub_id.subid_errcode )
 *
 *  3 3 2 2 2 2 2 2 2 2 2 2 1 2 1 1 1 1 1 1 1 1 
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+---+-----+-----------------------------------------------+
 * |E|E| |   |  E  |                                               |
 * |C|S|E| E |  S  |                                               |
 * |L|U|C| S |  E  |                                               |
 * |A|B|L| E |  V  |                                               |
 * |L|C|A| V |  E  |                    ECODE                      |
 * |W|L|S| M |  R  |                                               |
 * |A|A|S| O |  I  |                                               |
 * |Y|S| | D |  T  |                                               |
 * |A|S| |   |  Y  |                                               |
 * +-+-+-+---+-----+-----------------------------------------------+
 *		
 *  Bits		     		Function
 * -----		-----------------------------------------
 *  0-23		ECODE     - Event Code Number
 * 24-26		ESEVERITY - Event Severity Codes
 *		            Informational	0x00
 *			    Warning		0x01
 *			    Remote Error	0x02
 *			    Error		0x03
 * 		            Severe Error	0x04
 * 		            Fatal Error		0x05
 *			    RSVD( Future Use )	0x06
 *			    RSVD( Future Use )	0x07
 * 27-28		ESEVMOD	  - Event Severity Modifier Codes
 *			    None		0x00
 *			    Path Crash		0x01
 *			    Local Port Crash	0x02
 *			    RSVD( Future Use )	0x03
 *    29		ECLASS	  - Event Class Code
 *			    SCS			0x00
 *			    PD			0x01
 *    30		ESUBCLASS - Event Subclass Code( PD dependent )
 *			    PD			0x00( NP/MSI/CI/BVP/UQ )
 *			    PPD			0x01( NP/MSI/CI )
 *    31		ECLALWAYS - Event Console Loggging Filter Override
 *		
 * Event codes ( ECODE ) are densely assigned for each possible combination
 * of ESEVERITY, ECLASS, and ESUBCLASS.
 *
 *			Definition of Severity Conditions
 *			---------------------------------
 *
 * Informational:		Notifies of a fully successful event.
 *				Notifies of a purely informative event.
 *				Does NOT increment any error counters.
 *
 * Warning:			Warns of possible problems associated with an
 *				 otherwise successful event.
 *				Does NOT increment any error counters.
 *
 * Remote Error:		Notifies of the occurrence of a remote error.
 *				Does NOT increment any error counters.
 *
 * Error:			Notifies of the occurrence of a local
 *				 recoverable error associated with a specific
 *				 path or local port.
 *				May have the path crash modifier applied.
 *				Increments the number of errors associated with
 *				 the appropriate local port.
 *
 * Severe Error:		Notifies of the occurrence of a severe( but
 *				 still recoverable ) local error associated
 *				 with a specific path or local port.
 *				May have the path or local port crash severity
 *				 modifier applied.
 *				Increments the number of errors associated with
 *				 the appropriate local port.
 *
 * Fatal Error:			Notifies of the occurrence of a fatal
 *				 non-recoverable error associated with a
 *				 specific local port.
 *				Increments the number of errors associated with
 *				 the local port.
 *				Always logged to the console.
 */

/*  elbd_flags (el_bdhdr) */
/* 0x00 = write */
/* 0x01 = read */
/* 0x02 = done */
/* 0x04 = error */

/* uq error codes definition (el_sub_id.subid_errcode)
 */
#define ELUQ_SA_FATAL           1       /* Fatal error in SA register   */
#define ELUQ_RESET_FAIL         2       /* Initialization failed        */


/* XNA error codes (el_sub_id.subid_errcode) */
#define XNA_FATAL       0
#define XNA_NONFATAL    1

/* VMEbus device/controller errcode (el_sub_id.subid_errcode) */
#define VME_DEVICE      1
#define VME_CONTROLLER  2


/* VMEbus adapter error codes (el_sub_id.subid_errcode) */
#define VBA_VME_ERROR         0                /* general VME error */
#define VBA_VME_PARITY        1                /* general parity errors */
#define VBA_VME_TIMEOUT       2                /* vme timeout errors */
#define VBA_IBUS_CABLE_FLT    3                /* ibus cable fault */
#define VBA_IBUS_PARITY       4                /* ibus parity errors */
#define VBA_RMW_INTERLOCK     5                /* Read Mod Write/Interlock */
#define VBA_VME_BERR          6                /* VMEbus *BERR signal */
#define VBA_XBIA_INTERNAL     7                /* XBIA internal gate array */
#define VBA_IO_WRITE_FAIL     8                /* I/O write failure */
#define VBA_PMAP_FAULT        9                /* page map fault errors */
#define VBA_YABUS_ERROR      10                /* YAbus errors */
#define VBA_VME_MOD_FAIL     11                /* VME module failure */
#define VBA_VME_AC_LOW       12                /* VME AC below spec */
#define VBA_VIC_LOC_TOUT     13                /* VIC chip local timeout */
#define VBA_VIC_SELF_ACCESS  14                /* VIC self-acess select err */
#define VBA_VIC_LBERR        15                /* VIC *LBERR signal */
#define VBA_INVALID_PFN      16                /* invalid PFN */
#define VBA_MULTIPLE_ERRS    17                /* multiple errors */
#define VBA_CORR_ECC         18                /* correctable ECC */
#define VBA_UNCORR_ECC       19                /* uncorrectable ECC */
#define VBA_SYS_RESET        20                /* VME reset signal asserted */
#define VBA_CABLE_VIOLATION  21                /* Encoding violation on cable */

/* current ci event packet version
 * (el_body.elci.cicommon.ci_evpktver)
 */
#define	CI_EVPKTVER		 0

/* ci optional event packet field bit mask definitions
 * (el_body.elci.cicommon.ci_optfmask1)
 * bits 0x000000001 - 0x00004000 used, next free 0x00008000
 */
					/* ci device attention info fields */
#define	CI_REGS		0x00000001	/*  ci port registers */
#define	CI_BIREGS	0x00000002	/*  biic device registers */
#define	CI_XMIREGS	0x00000004	/*  xmi device registers */
#define	CI_UCODE	0x00000008	/*  bad ucode information */
#define	CI_REVLEV	0x00000010	/*  out-of-rev/invalid ucode info */
#define	CI_CPUREVLEV	0x00000020	/*  out-of-rev CPU ucode information */
#define CI_NPREGS       0x00000400      /*  N_PORT port registers */
#define CI_TCREGS       0x00000800      /*  tc device registers */
#define CI_NPPARMS      0x00001000      /*  N_PORT parmeters    */
					/* CI Logged Packet Info Fields */
#define	CI_LCOMMON	0x00000040	/*  common logged packet information */
#define	CI_PACKET	0x00000080	/*  logged packet */
#define	CI_EXPADRS	0x00000100	/*  explicit addrs format used  */
#define CI_NPPKT        0x00000200      /*  N_PORT format used  */
					/* CI Read Count Data    */
#define CI_TCA_RDCNT    0x00002000      /*  N_PORT CITCA read count data  */
#define CI_XCD_RDCNT    0x00004000      /*  CIPORT CIXCD read count data  */



/* current ci ppd event packet version
 * (el_body.elcippd.cippdcommon.cippd_evpktver)
 */
#define	CIPPD_EVPKTVER		 0

/* ci ppd optional event packet field bit mask definitions
 * (el_body.elcippd.cippdcommon.cippd_optfmask1)
 *
 */
					/* ci ppd sub id fields */
#define	CIPPD_CLTDEVTYP	0x00000001	/*  controller/device type */
#define	CIPPD_CLTDEVNUM	0x00000002	/*  controller number */
					/* ci ppd path specific info fields */
#define	CIPPD_PCOMMON	0x00000004	/*  common path specific information */
#define	CIPPD_DBCOLL	0x00000008	/*  database collision information */
#define	CIPPD_SYSAP	0x00000010	/*  name of local sysap crashing path*/
#define	CIPPD_NEWPATH	0x00000020	/*  new path information */
#define	CIPPD_PPACKET	0x00000040	/*  ci ppd logged packet */
					/* ci ppd common sys lev info fields */
#define	CIPPD_SCOMMON	0x00000080	/*  common system level information */
#define	CIPPD_PROTOCOL	0x00000100	/*  ci ppd protocol information */
#define	CIPPD_SPACKET	0x00000200	/*  ci ppd logged packet */

/* current msi event packet version
 * (el_body.elmsi.msicommon.msi_evpktver)
 */
#define	MSI_EVPKTVER		 0

/* msi optional event packet field bit mask definitions
 * (el_body.elmsi.msicommon.msi_optfmask1)
 *
 */
					/* msi device attention info fields */
#define	MSI_REGS	0x00000001	/*  msi port registers */
					/* msi logged packet info fields */
#define	MSI_LCOMMON	0x00000002	/*  common logged packet information */
#define	MSI_CMDBLK	0x00000004	/*  logged packet command block info */
#define	MSI_PACKET	0x00000008	/*  logged packet */

/* current scs event packet version
 * (el_body.elscs.scscommon.scs_evpktver)
 */
#define	SCS_EVPKTVER		 0

/* scs optional event packet field bit mask definitions
 * (el_body.elscs.scscommon.scs_optfmask1)
 */
					/* scs sub id fields */
#define	SCS_CLTDEVTYP	0x00000001	/*  controller/device type */
#define	SCS_CLTDEVNUM	0x00000002	/*  controller number */
					/* scs optional information fields */
#define	SCS_CONN	0x00000004	/*  scs connection information */
#define	SCS_LDIRID	0x00000008	/*  local directory id number */
#define	SCS_RREASON	0x00000010	/*  connection rejection reason */

#define EL_CILPKTSUBTRACT  EL_MISCSIZE + sizeof(struct ci_common)+ \
			sizeof(struct ci_lcommon) + sizeof(struct ci_packet)
#define EL_EXPTFLTSIZE  sizeof(struct el_exptflt)
#define EL_PNCSIZE	sizeof(struct el_pnc)
#define EL_MEMSIZE	sizeof(struct el_mem)

#define EL_REGMASK	0x012f3f19


struct el_mem {				/* mem. crd/rds packet */
	short elmem_cnt;		/* num. of mem. err structures */
	struct el_memerr {
		short cntl;		/* cntl. number 1-? */
		u_char type;		/*type err 1-crd,2-rds,3-cntl,4-wmask*/
		u_char numerr;		/* num. of errors on this address */
		int regs[6];		/* mem. regs */
	} elmemerr;			/* mem. err structure */
};

struct el_devhdr {			/* device header packet */
	dev_t devhdr_dev;		/* dev. major/minor numbers */
	int devhdr_flags;		/* buffer flags */
	int devhdr_bcount;		/* byte count of transfer */
	daddr_t devhdr_blkno;		/* logical block number */
	short devhdr_retrycnt;		/* retry count */
	short devhdr_herrcnt;		/* hard err count total */
	short devhdr_serrcnt;		/* soft err count total */
	short devhdr_csr;		/* device csr */
};

struct el_bdev {                        /* block device packet disk/tape */
        struct el_devhdr eldevhdr;      /* device header packet */
        union {
                u_int devreg[22];       /* device regs. non mscp drivers */
                struct el_mslg {
                    int mslg_len;      /* mscp packet length */
                    MSLG mscp_mslg;     /* mscp/tmscp datagram packet */
                } elmslg;
#ifdef ALPHAADU
                struct el_scsi elscsi;  /* SCSI eror info and registers */
#endif
        } eldevdata;
};


struct el_esrpmax {                     /* PMAX Error & Status Registers */
        u_int esr_cause;               /* Cause Reg */
        u_int esr_epc;                 /* Exception PC (resume PC) */
        u_int esr_status;              /* Status Reg */
        u_int esr_badva;               /* Bad Virtual Address Reg */
        u_int esr_sp;                  /* Stack Ptr */
};

struct el_esr5100 {                     /* MIPSMATE Error & Status Registers */
        u_int esr_cause;               /* Cause Reg */
        u_int esr_epc;                 /* Exception PC (resume PC) */
        u_int esr_status;              /* Status Reg */
        u_int esr_badva;               /* Bad Virtual Address Reg */
        u_int esr_sp;                  /* Stack Ptr */
	u_int esr_icsr;                /* Interrupt CSR */
	u_int esr_leds;                /* LED register */
	u_int esr_wear;                /* Write Error Add. register */
	u_int esr_oid;                 /* Option ID register */
};

struct el_esrkn02 {                     /* 3MAX Error & Status Registers */
        u_int esr_cause;		/* Cause Reg */
        u_int esr_epc;			/* Exception PC (resume PC) */
        u_int esr_status;		/* Status Reg */
        u_int esr_badva;		/* Bad Virtual Address Reg */
        u_int esr_sp;			/* Stack Ptr */
        u_int esr_csr;			/* system csr */
        u_int esr_erradr;		/* Error Address reg */
};

struct el_esrkn02ba {                     /* 3MAX Error & Status Registers */
        u_int esr_cause;		/* Cause Reg */
        u_int esr_epc;			/* Exception PC (resume PC) */
        u_int esr_status;		/* Status Reg */
        u_int esr_badva;		/* Bad Virtual Address Reg */
        u_int esr_sp;			/* Stack Ptr */
        u_int esr_ssr;                 /* system support reg */
	u_int esr_sir;             	/* system interrupt reg */	
	u_int esr_sirm;             	/* system interrupt mask */
};

struct el_esrkn02ca {                   /* MAXine Error & Status Registers */
        u_int esr_cause;               /* Cause Reg */
	u_int esr_epc;                 /* Exception PC (resume PC) */
	u_int esr_status;              /* Status Reg */
	u_int esr_badva;               /* Bad Virtual Address Reg */
	u_int esr_sp;                  /* Stack Ptr */
	u_int esr_ssr;                 /* system support reg */
	u_int esr_sir;                 /* system interrupt reg */
	u_int esr_sirm;                /* system interrupt mask */
};

struct el_esrkn03 {                     /* 3MAX+ Error & Status Registers */
       u_int esr_cause;               /* Cause Reg */
       u_int esr_epc;                 /* Exception PC (resume PC) */
       u_int esr_status;              /* Status Reg */
       u_int esr_badva;               /* Bad Virtual Address Reg */
       u_int esr_sp;                  /* Stack Ptr */
       u_int esr_ssr;                 /* system support reg */
       u_int esr_sir;                 /* system interrupt reg */
       u_int esr_sirm;                /* system interrupt mask */
       u_int esr_cs;                  /* Memory Control Status reg */
	u_int esr_erradr;              /* Error Address reg */
};

struct el_esr5400 {                     /* MIPsfair Error&Status Regs */
	u_int esr_cause;               /* Cause Reg */
	u_int esr_epc;                 /* Exception PC (resume PC) */
	u_int esr_status;              /* Status Reg */
	u_int esr_badva;               /* Bad Virtual Address Reg */
	u_int esr_sp;                  /* Stack Ptr */
	u_int esr_wear;                /* Write Error Address Reg */
	u_int esr_dser;                /* DMA System Error Reg */
	u_int esr_qbear;               /* QBus Error Address Reg */
	u_int esr_dear;                /* DMA Error Address Reg */
	u_int esr_cbtcr;               /* CDAL Bus Timeout Control Reg */
	u_int esr_isr;                 /* Interrupt Status Reg */
};

struct el_esr5500 {                     /* MIPsfair Error&Status Regs */
        u_int esr_cause;               /* Cause Reg */
        u_int esr_epc;                 /* Exception PC (resume PC) */
        u_int esr_status;              /* Status Reg */
        u_int esr_badva;               /* Bad Virtual Address Reg */
        u_int esr_sp;                  /* Stack Ptr */
	u_int esr_dser;		/* DMA System Error Reg */
	u_int esr_qbear;		/* QBus Error Address Reg */
	u_int esr_dear;		/* DMA Error Address Reg */
	u_int esr_cbtcr;		/* CDAL Bus Timeout Control Reg */
	u_int esr_isr;			/* Interrupt Status Reg	*/
	u_int esr_mser;		/* ECC Memory Error Syndrome Reg */
	u_int esr_mear;		/* ECC Memory Error Address Reg */
	u_int esr_ipcr;			/* Inter Process Communication Reg.*/
};

struct el_esr {				/* Generic error & status regs	*/
	union {
                struct el_esrpmax el_esrkn01;      /* PMAX (DS2100/3100) */
		struct el_esrkn02 el_esrkn02;	   /* 3MAX (DS5000) */
		struct el_esrkn02ba el_esrkn02ba;  /* 3MIN (DS5000_100) */
		struct el_esrkn02ca el_esrkn02ca;  /* MAXine (DSMAXINE)  */
		struct el_esrkn03 el_esrkn03;      /* 3MAX+ (DS5000_300)   */
		struct el_esr5100 el_esr5100;      /* MIPSmate (DS5100) */
		struct el_esr5400 el_esr5400;	   /* Mipsfair (DS5400)	*/
		struct el_esr5500 el_esr5500;	   /* Mipsfair (DS5500)	*/
	} elesr;
};



struct el_uq {				/* uq device attention information */
	u_int	sa_contents;		/* sa register contents		   */
};

 
struct elci_dattn {			/* ci device attention information */
        struct ci_regs {                /* ci port registers */
		u_int ci_cnfr;			/* configuration register */
		u_int ci_pmcsr;		/* port maint ctrl & status */
		u_int ci_psr;			/* port status */
		u_int ci_pfaddr;		/* port failing address */
		u_int ci_pesr;			/* port error */
		u_int ci_ppr;			/* port parameter */
	} ciregs;
	union ci_icregs {		/* optional interconnect regs */
		struct bi_regs cibiregs;        /* biic device registers */
		struct cixmi_regs {		/* xmi device registers */
			u_int	xdev;			/* device type reg */
			u_int	xbe;			/* bus error reg */
			u_int	xfadrl;			/* failg addr reg low*/
			u_int	xfadrh;			/* failg addr reg hi */
			u_int	pidr;			/* port int dst reg */
			u_int	pvr;			/* port vector reg */
			u_int asnr;            /* adapter serial number reg */
			u_int pdcsr;           /* port diag. cntrl status reg*/
			u_int abbr;            /* adapter base block reg */
		} cixmiregs;
		struct citca_regs {     /* tc device registers */
			u_int tcdev;           /* device type register */
			u_int tcber;           /* turbochannel bus err reg */
			u_int asnr;            /* adapter serial number reg */
			u_int pdcsr;           /* port diag. cntrl status reg*/
			u_int abbr;            /* adapter base block reg */
		} citcaregs;
	} ciicregs;
	union ci_dattnopt {		/* optional device attention info */
		struct ci_ucode {		/* faulty ucode information */
			u_int ci_addr;			/* faulty ucode addr */
			u_int ci_bvalue;		/* bad ucode value */
			u_int ci_gvalue;		/* good ucode value */
		} ciucode;
		struct ci_revlev {		/* port microcode information*/
			u_int ci_romlev;		/* PROM/self-test lev*/
			u_int ci_ramlev;		/* RAM/fn ucode level*/
		} cirevlev;
		struct ci_cpurevlev {		/* out-of-rev CPU ucode */
			u_int ci_hwtype;		/* CPU hardware type */
			u_int ci_mincpurev;		/* min CPU rev lev */
			u_int ci_currevlev;		/* cur CPU rev lev */
		} cicpurevlev;
		struct ci_npparms {             /* N_PORT parmeters       */
		       struct ci_npapb {       /* adapter parmeter block */
			       u_int data[8];
		       } cinpapb;
		       struct ci_npcpb {       /* channel parmeter block */
			       u_int data[8];
		       } cinpcpb;
		} cinpparms;
	} cidattnopt;
};

struct elci_lpkt {			/* ci logged packet information */
        struct ci_lcommon {             /* common logged packet information */
		u_char ci_rsaddr[ 6 ];		/* remote station address */
		u_char ci_rsysid[ 6 ];		/* remote system id number */
		u_char ci_rname[ 8 ];		/* remote system node name */
	} cilcommon;
	union ci_lpktopt {		/* optional logged packet info */
		struct ci_packet {		/* logged packet information */
			u_short size;			/* size of pkt logged */
			u_char ci_port;			/* destination port */
			u_char ci_status;		/* status */
			u_char ci_opcode;		/* cmd operation code*/
			u_char ci_flags;		/* port command flags*/
		} cipacket;
		struct ci_nppacket {            /* logged packet information */
			u_short size;           /* size of pkt logged */
			u_char ci_opc;          /* adapter opcode  */
						/* full pkt logged not shown */
		} cinppacket;
	} cilpktopt;
};



struct elci_rdcnt {
	union ci_rdcntopt {
		struct citca_rdcnt {
		       u_int   data[36];
		} citcardcnt;
		struct cixcd_rdcnt {
			u_int   data[40];
		} cixcdrdcnt;
	} cirdcntopt;
};



struct el_ci {				/* ci event packet */
        struct ci_common {		/* common to all ci packets */
		u_int	ci_optfmask1;		/* opt err pkt field bit mask*/
		u_int	ci_optfmask2;		/* opt err pkt field bit mask*/
		u_int	ci_evpktver;		/* version of ci event packet*/
		u_char  ci_lpname[ 4 ];		/* local port name */
		u_char  ci_lname[ 8 ];		/* local system name */
		u_char  ci_lsysid[ 6 ];		/* local system id number */
		u_char  ci_lsaddr[ 6 ];		/* local station address */
		u_short ci_nerrs;		/* number of errors */
		u_short ci_nreinits;		/* number of port reinits */
	} cicommon;
	union ci_types {		/* packet/attention specific info */
		struct elci_dattn cidattn;	/* device attention info */
		struct elci_lpkt cilpkt;	/* logged packet info */
		struct elci_rdcnt cirdcnt;      /* logged read count info */
	} citypes;
};


struct elmsi_dattn {			/* msi device attention information */
        struct msi_regs {               /* msi port registers */
		u_short msi_csr;		/* control/status */
		u_short msi_idr;		/* id */
		u_short	msi_slcs;		/* selector control/status */
		u_short	msi_destat;		/* selection detector status */
		u_short msi_tr;			/* timeout */
		u_short	msi_dmctlr;		/* dma control */
		u_short	msi_dmlotc;		/* dma length to transfer */
		u_short	msi_dmaaddrl;		/* dma address, low */
		u_short	msi_dmaaddrh;		/* dma address, high */
		u_short	msi_stlp;		/* short target list pointer */
		u_short msi_tlp;		/* target list pointer */
		u_short msi_ilp;		/* initiator list pointer */
		u_short msi_dscr;		/* dssi control */
		u_short msi_dssr;		/* dssi status */
		u_short	msi_dstat;		/* data transfer status */
		u_short msi_dcr;		/* diagnostic control */
		u_short	msi_save_dssr;		/* saved dssi status */
		u_short	msi_save_dstat;		/* saved data transfer status*/
	} msiregs;
};

struct elmsi_lpkt {			/* msi logged packet information */
        struct msi_lcommon {		/* common logged packet information */
		u_char msi_rsaddr[ 6 ];		/* remote station address */
		u_char msi_rsysid[ 6 ];		/* remote system id number */
		u_char msi_rname[ 8 ];		/* remote system node name */
	} msilcommon;
	struct msi_cmdblk {		/* logged packet command block info */
		u_short	msi_thread;		/* addr next command block */
		u_short	msi_status;		/* command block Status */
		u_short	msi_command;		/* command word */
		u_short	msi_opcode;		/* command operation code */
		u_char	msi_dst;		/* destination station addr */
		u_char	msi_src;		/* source port station addr */
		u_short	msi_length;		/* frame length */
	} msilcmdblk;
	struct msi_packet {		/* logged packet information */
		u_char msi_opcode;		/* operation code( pkt type )*/
		u_char msi_flags;		/* operation code modifiers */
	} msipacket;
};

struct el_msi {				/* msi event packet */
        struct msi_common {		/* common to all msi packets */
		u_int	msi_optfmask1;		/* opt err pkt field bit mask*/
		u_int	msi_optfmask2;		/* opt err pkt field bit mask*/
		u_int	msi_evpktver;		/* version - msi event packet*/
		u_char  msi_lpname[ 4 ];	/* local port name */
		u_char  msi_lname[ 8 ];		/* local system name */
		u_char  msi_lsysid[ 6 ];	/* local system id number */
		u_char  msi_lsaddr[ 6 ];	/* local station address */
		u_short msi_nerrs;		/* number of errors */
		u_short msi_nreinits;		/* number of port reinits */
	} msicommon;
	union msi_types {		/* packet/attention specific info */
		struct elmsi_dattn msidattn;	/* device attention info */
		struct elmsi_lpkt msilpkt;	/* logged packet info */
	} msitypes;
};

struct elcippd_system {			/* ci ppd system specific information*/
	struct cippd_scommon {		/* common system specific information*/
		u_char	cippd_rswtype[ 4 ];	/* remote software type */
		u_char	cippd_rswver[ 4 ];	/* remote software version */
		u_char	cippd_rswincrn[ 8 ];	/* remote sw incarnation num */
		u_char	cippd_rhwtype[ 4 ];	/* remote hardware type */
		u_char	cippd_rhwver[ 12 ];	/* remote hardware version */
	} cippdscommon;
	union cippd_systemopt {		/* optional system specific info */
		struct cippd_protocol {		/* ci ppd protocol info */
			u_char	cippd_local;		/* local version */
			u_char	cippd_remote;		/* remote version */
		} cippdprotocol;
		struct cippd_spacket {		/* logged packet */
			u_short cippd_mtype;		/* ci ppd msg type */
		} cippdspacket;
	} cippdsystemopt;
};

struct elcippd_path {			/* ci ppd path specific information */
	struct cippd_pcommon {		/* common path specific information */
		u_char cippd_lpname[ 4 ];	/* local port name */
		u_char cippd_lsaddr[ 6 ];	/* local station address */
		u_char cippd_rsaddr[ 6 ];       /* remote station address */
		u_int cippd_pstate;		/* software path state */
	} cippdpcommon;
	union cippd_pathopt {		/* optional path specific information*/
		struct cippd_dbcoll {		/* database collision info */
			u_char cippd_rswincrn[ 8 ];	/* rem sw incrn num */
			u_char cippd_kswincrn[ 8 ];	/* known sw incrn num*/
			u_char cippd_kname[ 8 ];   	/* known system name */
			u_char cippd_ksysid[ 6 ];  	/* known system id # */
			u_char cippd_klsaddr[ 6 ];	/* known lstat'n addr*/
			u_char cippd_krsaddr[ 6 ]; 	/* known rstat'n addr*/
		} cippddbcoll;
		char	cippd_sysap[ 16 ];	/* name SYSAP crashing path */
		struct cippd_newpath {		/* new path information */
			u_short cippd_max_dg;		/* max appl dg size */
			u_short cippd_max_msg;		/* max appl msg size */
			u_char  cippd_swtype[ 4 ];	/* software type */
			u_char  cippd_swver[ 4 ];	/* software version */
			u_char  cippd_swincrn[ 8 ];	/* software incrn num*/
			u_char  cippd_hwtype[ 4 ];	/* hardware type */
			u_char  cippd_hwver[ 12 ];	/* hardware version */
		} cippdnewpath;
		struct cippd_ppacket {		/* logged packet */
			u_short cippd_mtype;		/* ci ppd msg type */
		} cippdppacket;
	} cippdpathopt;
};

struct el_cippd {			/* ci ppd event packet */
	struct cippd_common {		/* common to all packets */
		u_int cippd_optfmask1;		/* opt err pkt field bit mask*/
		u_int cippd_optfmask2;		/* opt err pkt field bit mask*/
		u_int cippd_evpktver;		/* version of cippd event pkt*/
		u_char cippd_lname[ 8 ];	/* local system node name */
		u_char cippd_rname[ 8 ];	/* remote system node name */
		u_char cippd_lsysid[ 6 ];	/* local system id number */
		u_char cippd_rsysid[ 6 ];	/* remote system id number */
		u_short cippd_npaths;		/* num total paths to rem sys*/
		u_short cippd_nerrs;		/* number of errors */
	} cippdcommon;
	union cippd_types {		/* system/path specific information */
		struct elcippd_system cippdsystem; /* system specific info */
		struct elcippd_path cippdpath;	/* path specific info */
	} cippdtypes;
};

struct el_scs {				/* scs event packet */
	struct scs_common {		/* common to all packets */
		u_int  scs_optfmask1;		/* opt err pkt field bit mask*/
		u_int  scs_optfmask2;		/* opt err pkt field bit mask*/
		u_int  scs_evpktver;		/* version of scs event pkt*/
		u_char  scs_lsysap[ 16 ];	/* local sysap name */
		u_char  scs_lconndata[ 16 ];	/* local connection data */
		u_int  scs_lconnid;		/* local connection id number*/
		u_char  scs_lname[ 8 ];		/* local system node name */
		u_char  scs_lsysid[ 6 ];	/* local system id number */
		u_short	scs_cstate;		/* connection state */
	} scscommon;
	union scs_opt {			/* optional scs event information */
		struct scs_conn {		/* scs connection information*/
			u_char  scs_rsysap[ 16 ];	/* remote sysap name */
			u_char  scs_rconndata[ 16 ];	/* remote conn data */
			u_int	scs_rconnid;		/* remote conn id num*/
			u_char  scs_rname[ 8 ];		/* rem sys node name */
			u_char  scs_rsysid[ 6 ];	/* rem system id num */
			u_char  scs_rsaddr[ 6 ];	/* rem station addr */
			u_char  scs_lpname[ 4 ];	/* local port name */
			u_char  scs_lsaddr[ 6 ];	/* local station addr*/
			u_short scs_nconns;		/* num conns on path */
		} scsconn;
		u_short	scs_ldirid;		/* local directory id number */
		u_int	scs_rreason;		/* connection reject reason */
	} scsopt;
};

struct el_strayintr {                   /* stray intr. packet */
	u_char stray_ipl;               /* ipl level */
	short stray_vec;                /* vector */
};


struct el_exptflt {                     /* panic exception/fault packet */
	int exptflt_va;                 /* va. if appropriate else zero */
	int exptflt_pc;                 /* pc at time of exception/fault */
	int exptflt_psl;                /* psl at time of exception/fault */
};

struct el_stkdmp {
        int addr;
	int size;
	int stack[EL_SIZE128];		/* stack dump of kernel/interpt/user */
};

struct el_pnc {				/* panic packet (bug check) */
	char pnc_asc[EL_SIZE64];	/* ascii panic string */
	int pnc_sp;
	int pnc_ap;
	int pnc_fp;
	int pnc_pc;
	struct pncregs {
	    int pnc_ksp;
	    int pnc_usp;
	    int pnc_isp;
	    int pnc_p0br;
	    int pnc_p0lr;
	    int pnc_p1br;
	    int pnc_p1lr;
	    int pnc_sbr;
	    int pnc_slr;
	    int pnc_pcbb;
	    int pnc_scbb;
	    int pnc_ipl;
	    int pnc_astlvl;
	    int pnc_sisr;
	    int pnc_iccs;
	} pncregs;
	struct el_stkdmp kernstk;		/* dump of kernel stack */
	struct el_stkdmp intstk;		/* dump of interrupt stack */
};


struct el_timchg {
	struct timeval timchg_time;	/* time in sec and usec */
	struct timezone timchg_tz;	/* time zone data */
	char timchg_version[EL_SIZE16];	/* ultrix vx.x */
};


/*
 *  VMEbus adapter registers error packet for 3max and Mipsfair2 
 *
 *                     The MVIB is the VME card containing
 *		       the registers for the 3VIA and MVIA,
 *                     which are the host-side cards for the
 *                     VME option on 3max and mipsfair2.
 */

struct el_vba_MVIB {
        int     mvib_viacsr;   /* xVIA control/status register */
        int     mvib_csr;      /* control/status register */
	int     mvib_vfadr;    /* vme failing address register */
	int     mvib_cfadr;    /* cpu failing address register */
	int     mvib_ivs;      /* interrupt vector source */
 	int 	 mvib_besr;	/* VIC bus err summary register */
	int	 mvib_errgi;    /* VIC err group inter. control reg */
	int     mvib_lvb;	/* VIC local vector base reg */
	int     mvib_err;   	/* VIC error vector register */
};



/*
 * XMI-based VMEbus adapter registers error packet (CMAX).
 *
 *           Registers found on both boards, the XBIA on
 *           the host-side, and the XVIB on the VME-side.
 */

struct el_vba_XBIA {            /* 2 board set -- xvib and xbia */

	int     xvib_vdcr;     /* device/configuration register */
	int     xvib_vesr;     /* error summary register */
	int     xvib_vfadr;    /* vme failing address register */
	int     xvib_vicr;     /* interrupt configuration register */
	int     xvib_vvor;     /* vector offset register */
	int     xvib_vevr;     /* error vector register */

	int     xbia_dtype;    /* device type/revision register */
	int     xbia_xbe;      /* XMI bus error register */
	int     xbia_fadr;     /* XMI failing address register */
	int     xbia_arear;    /* xbia responder error address register */
	int     xbia_aesr;     /* xbia error summary register */
	int     xbia_aimr;     /* xbia interrupt mask register */
	int     xbia_aivintr;  /* xbia implied vector inter. dest. register */
	int     xbia_adg1;     /* xbia diag 1 register */

};



/*
 *  VMEbus adapter registers error packet for DAA TC300/VME
 *
 *                     Registers found on both boards.
 */

struct el_vba_TC300 {
	int     tc3_tc_csr;    /* TC300 tc control/status register */
	int     tc3_vme_csr0;  /* TC300 vme control/status register 0 */
	int     tc3_vme_csr1;  /* TC300 vme control/status register 1 */
	   /* csr2 is write-only.  TC300 vme control/status register 2 */
	int     tc3_vme_csr3;  /* TC300 vme control/status register 3 */
};



/* VMEbus adapter error packet */
struct el_vba {
        union {                                  /* depends on adapter type */
		struct el_vba_MVIB elmvib;       /* 3max, mipsfair-2 */
		struct el_vba_XBIA elxbia;       /* cmax (xmi) */
		struct el_vba_TC300 eltc300;     /* DAA TC300/VME (TC-VME) */
	} elvba_reg;
};

/* VMEbus general purpose error packet for VME devices and controllers */
struct el_vme_dev_cntl {
        char module[EL_SIZE64];              /* name from uba structure */
        short num;			     /* num from uba structure */
	caddr_t csr1;                        /* csr1 address from uba struct*/
	caddr_t csr2;                        /* csr2 address from uba struct*/
        struct el_msg el_vme_error_msg;      /* error message from driver */
        struct el_vba elvba;                 /* adapter regs for more info */
};


/* XNA error packet (DEBNI, DEMNA) */
struct el_xna {
	union	xna_type {
		union	xna_xmi {
			struct xna_xmi_fatal {
				int	xna_type;
				int	xna_date_lo;
				int	xna_date_hi;
				int	xna_r0;
				int	xna_r1;
				int	xna_r2;
				int	xna_r3;
				int	xna_r4;
				int	xna_r5;
				int	xna_r6;
				int	xna_r7;
				int	xna_r8;
				int	xna_r9;
				int	xna_r10;
				int	xna_r11;
				int	xna_r12;
				int	xna_xbe;
				int	xna_xfadr;
				int	xna_xfaer;
				int	xna_gacsr;
				int	xna_diag;
				int	xna_xpst_init;
				int	xna_xpd1_init;
				int	xna_xpd2_init;
				int	xna_xpst_final;
				int	xna_xpd1_final;
				int	xnastack[6];
			} xnaxmi_fatal;
			struct xna_xmi_nonfatal {
				int	xna_date_lo;
				int	xna_date_hi;
				int	xna_r0;
				int	xna_r1;
				int	xna_r2;
				int	xna_r3;
				int	xna_xbe;
				int	xna_xfadr;
				int	xna_xfaer;
				int	xna_gacsr;
			} xnaxmi_nonfatal;
		} xnaxmi;
		union	xna_bi {
			struct	xna_bi_fatal {
				int	xna_type;
				int	xna_date_lo;
				int	xna_date_hi;
				int	xna_r0;
				int	xna_r1;
				int	xna_r2;
				int	xna_r3;
				int	xna_r4;
				int	xna_r5;
				int	xna_r6;
				int	xna_r7;
				int	xna_r8;
				int	xna_r9;
				int	xna_r10;
				int	xna_r11;
				int	xna_r12;
				int	xna_ber;
				int	xna_pad1;
				int	xna_pad2;
				int	xna_bicsr;
				int	xna_bci3_csr;
				int	xna_xpst_init;
				int	xna_xpd1_init;
				int	xna_xpd2_init;
				int	xna_xpst_final;
				int	xna_xpd1_final;
				int	xnastack[6];
			} xnabi_fatal;
			struct	xna_bi_nonfatal {
				int	xna_date_lo;
				int	xna_date_hi;
				int	xna_r0;
				int	xna_r1;
				int	xna_r2;
				int	xna_r3;
				int	xna_ber;
			} xnabi_nonfatal;

		} xnabi;
	} xnatype;
};

struct el_fza {
	u_short	fza_id;			/* fza id or version */
	u_short reset_count;		/* reset counter */
	u_int	timestamp_hi;		/* time stamp hi */
	u_short timestamp_lo;		/* time stamp lo */
	u_short write_count;			
	u_short int_reason;		/* Internal failure reason */
	u_short ext_reason;		/* External failure reason */
	u_int  cmd_next_ptr;		/* Next cmd entry to service */
	u_int  cmd_next_cmd;		/* Next cmd descr, 1st entry */
	u_int  dma_next_rmc_ptr;
	u_int  dma_next_rmc_descr;
	u_int  dma_next_rmc_own;
	u_int  dma_next_host_ptr;
	u_int  dma_next_host_descr;
	u_int  unsol_next_ptr;
	u_int  unsol_next_descr;
	u_int  smt_next_put_ptr;
	u_int  smt_next_put_descr;
	u_int  smt_next_take_ptr;
	u_int  smt_next_take_descr;
	u_short pm_csr;			/* Packet mem CSR */
	u_short int_68k_present;	/* 68k interrupt ctrl reg */
	u_short int_68k_mask;		/* 68k interrupt ctrl mask reg */
	u_short pint_event;		/* Port interrupt reg */
	u_short port_ctrl_a;		/* Port control A */
	u_short port_ctrl_a_mask;	/* Port control A mask */
	u_short port_ctrl_b;		/* Port control B */
	u_short port_status;		/* Port status */
	u_short ram_rom_map;		/* Map register */
	u_short phy_csr;		/* Phy CSR */
	u_short dma_done;		/* DMA done */
	u_short dma_err;		/* DMA error */
	u_short dma_start_lo;		/* DMA start dma low addr */
	u_short dma_start_hi;		/* DMA start high addr */
	u_short rmc_cmd;		/* RMC command */
	u_short rmc_mode;		/* RMC mode */
	u_short rmc_rcv_page;		/* RMC rcv page */
	u_short rmc_rcv_params;		/* RMC rcv parameters */
	u_short rmc_xmt_page;		/* RMC xmt page */
	u_short rmc_xmt_params;		/* RMC xmt parameters */
	u_short rmc_interrupts;		/* RMC interrupts */
	u_short rmc_int_mask;		/* RMC interrupt mask */
	u_short rmc_chan_status;	/* RMC channel status */
	u_short mac_rcv_cntrl;		/* MAC */
	u_short mac_xmt_cntrl;
	u_short mac_int_mask_a;
	u_short mac_int_mask_b;
	u_short mac_rcv_status;
	u_short mac_xmt_status;
	u_short mac_mla_a;
	u_short mac_mla_b;
	u_short mac_mla_c;
	u_short mac_t_req;
	u_short mac_tvx_value;
	u_int  crc;			/* TEMPORARY, REMOVE ON NEW ERR LOG */
 } ;


struct el_fta {
	u_int  event_status;           /* status of event header */
	u_int  caller_id;             /* entity that wrote this information */
	u_int  timestamp_l;            /* bits 31:00 of time */
	u_int  timestamp_h;            /* bits 63:32 of time */
	u_int  write_count;            /* # of times err log's been written */
	struct diag {
	u_int  fru_imp_mask;           /* mask of failing units */
	u_int  test_id;                /* id # of test which wrote the log */
	u_int  reserved[6];            /* reserved bytes */
	}diag;
	u_int  fw[111];                /* firmware info */
};

/*
 * Alpha Machine Check Data Structures.
 */

/*
 * KN15AA error log structures.
 *
 * KN15AA/BA has two frame formats:
 *	1) machine check, for hard errors (el_kn15aa_frame_mcheck)
 *	2) ECC, for corrected soft errors (el_kn15aa_frame_corrected)
 * Each structure is composed of a header (el_kn15aa_logout_header) followed
 * by the logout data (el_kn15aa_procdata_mcheck/el_kn15aa_sysdata_mcheck
 * or el_kn15aa_procdata_corrected).
 *
 * Note: the EV4-specific and Alpha-specific fields should be
 * merged into a single structure to combine FLAMINGO, RUBY, COBRA,
 * and all others into a more compact set of structures.
 */

struct el_kn15aa_logout_header {
	u_int	elfl_size;		/* size in bytes of logout area. */
	int	elfl_sbz1:31;		/* Should be zero. */
	char	elfl_retry:1;		/* Retry flag. */
        u_int	elfl_procoffset;	/* Processor-specific offset. */
	u_int	elfl_sysoffset;		/* Offset of system-specific. */
};

struct el_kn15aa_procdata_mcheck {
	u_long		elfmc_paltemp[32];	/* PAL TEMP REGS. */
	/* EV4-specific fields */
	vm_offset_t	elfmc_exc_addr;		/* Address of excepting instruction. */
	u_long		elfmc_exc_sum;		/* Summary of arithmetic traps. */
	u_long		elfmc_exc_mask;		/* Exception mask (from exc_sum). */
	u_long		elfmc_iccsr;		/* IBox hardware enables. */
	vm_offset_t	elfmc_pal_base;		/* Base address for PALcode. */
	u_long		elfmc_hier;		/* Hardware Interrupt Enable. */
	u_long		elfmc_hirr;		/* Hardware Interrupt Request. */
	u_long		elfmc_mm_csr;		/* D-stream fault info. */
	u_long		elfmc_dc_stat;		/* D-cache status (ECC/Parity Err). */
	u_long		elfmc_dc_addr;		/* EV3 Phys Addr for ECC/DPERR. */
	u_long		elfmc_abox_ctl;		/* ABox Control Register. */
	u_long		elfmc_biu_stat;		/* BIU Status. */
	vm_offset_t	elfmc_biu_addr;		/* BUI Address. */
	u_long		elfmc_biu_ctl;		/* BIU Control. */
	u_long		elfmc_fill_syndrome;	/* For correcting ECC errors. */
	vm_offset_t	elfmc_fill_addr;	/* Cache block which was being read. */
	vm_offset_t	elfmc_va;		/* Effective VA of fault or miss. */
	u_long		elfmc_bc_tag;		/* Backup Cache Tag Probe Results. */
};

struct el_kn15aa_sysdata_mcheck {
	/* Platform-specific fields */
	u_long		elfmc_ident;		/* Machine check type */
	u_long		elfmc_mcr_stat;		/* Status */
	u_long		elfmc_io_slot;		/* TC I/O Slot # */
	u_long		elfmc_tc_config;	/* TC Config register */
	u_long		elfmc_f_adr;		/* Failing address */
	u_long		elfmc_tc_ereg;		/* TC Error register */
	u_long		elfmc_isr;		/* IS register */
	u_long		elfmc_imr;		/* IM register */
};

/* Machine check: a header followed by the data */
/* NOTE: not presented this way, must build on the fly */
struct el_kn15aa_frame_mcheck {
	struct el_kn15aa_logout_header elfmc_hdr;
	struct el_kn15aa_procdata_mcheck elfmc_procdata;
	struct el_kn15aa_sysdata_mcheck elfmc_sysdata;
};

struct el_kn15aa_procdata_corrected {
	u_long		elfcc_biu_stat;		/* BIU Status. */
	vm_offset_t	elfcc_biu_addr;		/* BUI Address. */
	u_long		elfcc_dc_stat;		/* D-cache status (ECC/Parity Err). */
	u_long		elfcc_fill_syndrome;	/* For correcting ECC errors. */
	vm_offset_t	elfcc_fill_addr;	/* Cache block which was being read. */
	u_long		elfcc_bc_tag;		/* Backup Cache Tag Probe Results. */
	u_long		elfcc_ident;		/* Machine check type. */
};

/* Corrected error frame: (620 and 630): a header followed by the data */
/* NOTE: not presented this way, must build on the fly */
struct el_kn15aa_frame_corrected {
	struct el_kn15aa_logout_header elfcc_hdr;
	struct el_kn15aa_procdata_corrected elfcc_procdata;
};

struct el_kn16aa_sysdata_mcheck {
        /* Platform-specific fields */
	u_long		elfmc_ident;		/* Machine check type */
	u_long		elfmc_mcr_stat;		/* Status */
	u_long		elfmc_intr;		/* Interrupt Register */
	u_long		elfmc_tc_status;	/* TC Status register */
	u_long		elfmc_config;		/* Memory Config Register */
};

/* Machine check: a header followed by the data */
/* The kn16aa frame is identical to kn15aa except for the */
/* platform specific fields */
/* NOTE: not presented this way, must build on the fly */
struct el_kn16aa_frame_mcheck {
	struct el_kn15aa_logout_header elfmc_hdr;
	struct el_kn15aa_procdata_mcheck elfmc_procdata;
	struct el_kn16aa_sysdata_mcheck elfmc_sysdata;
};

/* 
 *  KN121 (Jensen) logout area definition
 */

struct el_kn121_sysdata_mcheck {        /* Platform-specific fields */

	u_long		elfmc_ident;		/* Machine check type */
	u_long		elfmc_bus_mas;		/* 82357 BusMaster Reg */
	u_long		elfmc_fw_rev;		/* Firmware Rev */
	u_long		elfmc_pic1_mask;	/* PIC<7:0> Mask Reg */
	u_long		elfmc_pic1_irr;		/* PIC<7:0> IRR Reg */
	u_long		elfmc_pic1_isr;		/* PIC<7:0> ISR Reg */
	u_long		elfmc_pic1_elr;		/* PIC<7:0> ELR Reg */
	u_long		elfmc_pic2_mask;	/* PIC<15:8> Mask Reg */
	u_long		elfmc_pic2_irr;		/* PIC<15:8> IRR Reg */
	u_long		elfmc_pic2_isr;		/* PIC<15:8> ISR Reg */
	u_long		elfmc_pic2_elr;		/* PIC<15:8> ELR Reg */
	u_long		elfmc_dma1_mask;	/* DMA<3:0> Mask Reg */
	u_long		elfmc_dma1_stat;	/* DMA<3:0> Status Reg */
	u_long		elfmc_dma2_mask;	/* DMA<7:4> Mask Reg */
	u_long		elfmc_dma2_stat;	/* DMA<7:4> Status Reg */
	u_long		elfmc_dma_cstat;	/* DMA<7:0> Chain Status Reg*/
	u_long		elfmc_dma_intr;		/* DMA<7:0> DMA intr Reg */
	u_long		elfmc_dma_cmode;	/* DMA<7:0> Chain Mode Reg*/
	u_long		elfmc_coma_ie;		/* COMMA Intr Enable Reg*/
	u_long		elfmc_coma_ir;		/* COMMA Intr Request Reg*/
	u_long		elfmc_comb_ie;		/* COMMB Intr Enable Reg*/
	u_long		elfmc_comb_ir;		/* COMMB Intr Request Reg*/
	u_long		elfmc_hae;		/* Host Address Ext Reg*/
	u_long		elfmc_sys;		/* System Control Reg*/
	
};


/* KN121 (Jensen) Machine check logout
 *
 *	Consists of three parts:
 *
 *		- Alpha generic header  (Uses flamingo definition)
 *		- EV4-specific logout   (Again use flamingo definition)
 *		- KN121-specfic logout  (KN121 defined platform area)
 */
struct el_kn121_frame_mcheck {
	struct el_kn15aa_logout_header elfmc_hdr;
	struct el_kn15aa_procdata_mcheck elfmc_procdata;
	struct el_kn121_sysdata_mcheck elfmc_sysdata;
};


/*
 * Cobra Error Log Structures.
 *
 * A Cobra error log frame has the following components:
 *
 *	1. Error log header (defined in binlog.h).
 *	2. Cobra Kernel Event header (struct el_cobra_mcheck_event_header).
 *	   This header contains summary analysis information (unit which
 *	   failed, failure analysis, severity of error).
 *	3. One or more self-describing data frames.  Each frame starts with
 *	   with a longword header (struct el_cobra_frame_header) containing 
 *	   the length of the frame and a frame identifier code.
 *	4. Error log trailer (defined in binlog.h).
 */

/*
 * EV4 registers.
 */
struct el_ev4_csrs {
	vm_offset_t el4_exc_addr;   /* Address of excepting instruction. */
	u_long	    el4_exc_sum;    /* Summary of arithmetic traps. */
	u_long	    el4_exc_mask;   /* Exception mask (from exc_sum). */
	u_long	    el4_iccsr;      /* IBox hardware enables. */
	vm_offset_t el4_pal_base;   /* Base address for PALcode. */
	u_long	    el4_hier;	    /* Hardware Interrupt Enable. */
	u_long	    el4_hirr;	    /* Hardware Interrupt Request. */
	u_long	    el4_mm_csr;     /* D-stream fault info. */
	u_long	    el4_dc_stat;    /* D-cache status (ECC/Parity Err). */
	u_long	    el4_dc_addr;    /* EV3 Phys Addr for ECC/DPERR. */
	u_long	    el4_abox_ctl;   /* ABox Control Register. */
	u_long	    el4_biu_stat;   /* BIU Status. */
	vm_offset_t el4_biu_addr;   /* BUI Address. */
	u_long	    el4_biu_ctl;    /* BIU Control. */
	u_long	    el4_fill_syndrome; /* For correcting ECC errors. */
	vm_offset_t el4_fill_addr;  /* Cache block which was being read. */
	vm_offset_t el4_va;	    /* Effective VA of fault or miss. */
	u_long	    el4_bc_tag;     /* Backup Cache Tag Probe Results. */
};

/*
 * Cobra CPU-Specific CSRS.
 */
struct el_cobra_cpu_csrs {
	u_long	elcsr_bcc;	/* CSR 0 */
	u_long	elcsr_bcce;	/* CSR 1 */
	u_long	elcsr_bccea;	/* CSR 2 */
	u_long	elcsr_bcue;	/* CSR 3 */
	u_long	elcsr_bcuea;	/* CSR 4 */
	u_long	elcsr_dter;	/* CSR 5 */
	u_long	elcsr_cbctl;	/* CSR 6 */
	u_long	elcsr_cbe;	/* CSR 7 */
	u_long	elcsr_cbeal;	/* CSR 8 */
	u_long	elcsr_cbeah;	/* CSR 9 */
	u_long	elcsr_pmbx;	/* CSR 10 */
	u_long	elcsr_ipir;	/* CSR 11 */
	u_long	elcsr_sic;	/* CSR 12 */
	u_long	elcsr_adlk;	/* CSR 13 */
	u_long	elcsr_madrl;	/* CSR 14 */
};

#define KN430_PALTEMPS 31
#define KN430_FIRST_PALTEMP 1
#define KN430_PAL_LOGOUT_VERSION 1

/*
 * Cobra-Specific Kernel Event Header.  This is the header for any error log
 * packet; follows the error logger header defined in errlog.h.
 *
 *   |6                       3|3                       0|
 *   |3                       2|1                       0|
 *   +------------+------------+------------+------------+     
 *   | SCB_Vector | Frame_Rev  |        Byte Count       |  +00
 *   +------------+------------+------------+------------+ 
 *   |  CPU_ID    |Severity    | Reserved   |FRU_2|FRU_1 |  +08
 *   +------------+------------+------------+------------+     
 *   |  reserved  | Fail_Code  | Threshold  |Error_Count |  +10
 *   +------------+------------+------------+------------+     
 *   |              error_field_l <    >                 |  +18
 *   +------------+------------+------------+------------+     
 *   |              error_field_h <    >                 |  +20
 *   +------------+------------+------------+------------+     
 *   |                      reserved                     |  +28
 *   +---------------------------------------------------+
 */
struct el_cobra_mcheck_event_header {
	int	elch_size;	/* Size of entire frame. */
	short	elch_rev;	/* Frame revision. */
	u_short	elch_vector;	/* Vector (0,0x670,0x660,0x630, or 0x620) */
	char	elch_fru1;	/* Most probable cause of error */
	char	elch_fru2;	/* Second most probable cause of error */
	short	elch_res0a;	/* Reserved. */
	short	elch_sev;	/* Severity. */
	short	elch_cpuid;	/* CPU id (0 or 1)*/
	short	elch_count;	/* Error count. */
	short	elch_thresh;	/* Threshold for this error. */
	short	elch_fcode;	/* Failure Code. */
	short	elch_res16;	/* Reserved. */
	u_long	elch_flags[2];	/* Error analysis flags. */
	u_long	elch_res28;	/* Reserved. */
};

/*
 * Frame Format Revision.  Only one, so far...
 */
#define COBRA_ERROR_FRAME_REV_INITIAL 1
#define COBRA_ERROR_FRAME_REV_CURRENT COBRA_ERROR_FRAME_REV_INITIAL

/*
 * FRU Constants (for elch_fru1 and elch_fru2).
 */
#define COBRA_FRU_INVALID	0
#define COBRA_FRU_IO		1
#define COBRA_FRU_CPU1		2
#define COBRA_FRU_CPU2		3
#define COBRA_FRU_MEM0		4
#define COBRA_FRU_MEM1		5
#define COBRA_FRU_MEM2		6
#define COBRA_FRU_MEM3		7

/*
 * Severity constants (for elch_sev):
 */
#define COBRA_SEV_INVALID	0
#define COBRA_SEV_FATAL		1
#define COBRA_SEV_ALARM		2
#define COBRA_SEV_WARNING	3
#define COBRA_SEV_INFO		4

/*
 * Failure Analysis Codes (for elch_fcode):
 */	
#define COBRA_FCODE_UNDEFINED		0/*FC$NOT_VALID*/
#define COBRA_FCODE_EV_0_BC_CORR	2/*FC$EV_0_C_CORR*/
#define COBRA_FCODE_EV_1_BC_CORR	3/*FC$EV_1_C_CORR*/
#define COBRA_FCODE_C3_0_BC_CORR	4/*FC$C3_0_C_CORR*/
#define COBRA_FCODE_C3_1_BC_CORR	5/*FC$C3_1_C_CORR*/

/*
 * Error Flag Macros and Values.  Need COBRA_LONG_BIT until LONG_BIT is
 * correct.
 */
#ifndef COBRA_LONG_BIT
#define COBRA_LONG_BIT 64
#endif /* defined(COBRA_LONG_BIT) */

#define COBRA_ERROR_FLAG_SET(hdr,bit) \
	hdr[(bit)/COBRA_LONG_BIT] |= (1L << ((bit) % COBRA_LONG_BIT))
#define COBRA_ERROR_FLAG_CLR(hdr,bit) \
	hdr[(bit)/COBRA_LONG_BIT] &= ~(1L << ((bit) % COBRA_LONG_BIT))
#define COBRA_ERROR_FLAG_VAL(hdr,bit) \
	(hdr[(bit)/COBRA_LONG_BIT] & (1UL << ((bit) % COBRA_LONG_BIT)))
#define COBRA_ERROR_FLAGS_EMPTY(hdr) \
	((hdr[0] == 0L) && (hdr[1] == 0L))

#define COBRA_CPU0_C3_CA_NOACK		 0
#define COBRA_CPU0_C3_WD_NOACK		 1
#define COBRA_CPU0_C3_RD_PAR		 2
#define COBRA_CPU0_EV_C_UNCORR		 3
#define COBRA_CPU0_EV_TC_PAR		 4
#define COBRA_CPU0_EV_T_PAR		 5
#define COBRA_CPU0_C3_EV		 6

#define COBRA_CPU0I_C3_C_UNCORR		 8
#define COBRA_CPU0I_C3_TC_PAR		 9
#define COBRA_CPU0I_C3_T_PAR		10
#define COBRA_CPU0I_C3_C_CORR		11
#define COBRA_CPU0I_EV_C_CORR		12

#define COBRA_CPU_SHIFT			16

#define COBRA_CPU1_C3_CA_NOACK		16
#define COBRA_CPU1_C3_WD_NOACK		17    
#define COBRA_CPU1_C3_RD_PAR		18
#define COBRA_CPU1_EV_C_UNCORR		19
#define COBRA_CPU1_EV_TC_PAR		20
#define COBRA_CPU1_EV_T_PAR		21
#define COBRA_CPU1_C3_EV		22

#define COBRA_CPU1I_C3_C_UNCORR		24
#define COBRA_CPU1I_C3_TC_PAR		25
#define COBRA_CPU1I_C3_T_PAR		26
#define COBRA_CPU1I_C3_C_CORR		27
#define COBRA_CPU1I_EV_C_CORR		28

#define COBRA_CPU_EV_SYN_1F		32
#define COBRA_CPU_C3_SYN_1F		33
#define COBRA_CPU_DT_PAR		34
#define COBRA_CPU_EV_HARD_ERROR		35

/*
 * Not in PFMS -- Indicates that the system error lock was already held when
 * a processor doing the System Machine Check (0x660) parse tried to take it.
 */
#define COBRA_CPU_SYSLCK		39

#define COBRA_EVC_C3_MEM_R_ERROR	40
#define COBRA_EVC_IO_MEM_R_ERROR	41
#define COBRA_EVC_C3_OCPU_ADD_MATCH	42
#define COBRA_EVC_MIXED_ERRORS		43
 
#define COBRA_IO_EXT_CA_NOACK		48
#define COBRA_IO_EXT_WD_NOACK		49
#define COBRA_IO_EXT_RD_PAR		50
#define COBRA_IO_EXT_CB_UNCORR		51

#define COBRA_IO_INT_LB_DMA_PAR		56
#define COBRA_IO_INT_FB_DMA_PAR		57
#define COBRA_IO_INT_FB_MB_PAR		58
#define COBRA_IO_INT_BUSSYNC		59
#define COBRA_IO_INT_SCSSTALL		60

#define COBRA_C3_0_CA_PAR		64
#define COBRA_C3_1_CA_PAR		65
#define COBRA_MEM0_CA_PAR		66
#define COBRA_MEM1_CA_PAR		67
#define COBRA_MEM2_CA_PAR		68
#define COBRA_MEM3_CA_PAR		69
#define COBRA_IO_CA_PAR			70

#define COBRA_C3_0_WD_PAR		72
#define COBRA_C3_1_WD_PAR		73
#define COBRA_MEM0_WD_PAR		74
#define COBRA_MEM1_WD_PAR		75
#define COBRA_MEM2_WD_PAR		76
#define COBRA_MEM3_WD_PAR		77
#define COBRA_IO_WD_PAR			78

#define COBRA_MEM0_UNCORR		80           
#define COBRA_MEM1_UNCORR		81           
#define COBRA_MEM2_UNCORR		82           
#define COBRA_MEM3_UNCORR		83           

/* Correctible EDC error detected. */
#define COBRA_MEM0_CORR			88
#define COBRA_MEM1_CORR			89
#define COBRA_MEM2_CORR			90
#define COBRA_MEM3_CORR			91

/* EDC Correction disabled -- error not corrected ! */
#define COBRA_MEM0_CORRDIS		92
#define COBRA_MEM1_CORRDIS		93
#define COBRA_MEM2_CORRDIS		94
#define COBRA_MEM3_CORRDIS		95
               
#define COBRA_MEM0_SYNC_ERROR		96
#define COBRA_MEM1_SYNC_ERROR		97
#define COBRA_MEM2_SYNC_ERROR		98
#define COBRA_MEM3_SYNC_ERROR		99

/*
 * Cobra Machine Check Frame Header.  Describes the size of the frame, and the
 * nature of the data in the frame.  All frames start with this header.  A
 * header may be skipped by adding elcf_size to the address of the frame.
 *
 *  |6                       3|3          1|1
 *  |3                       2|1          6|5          0|
 *  +-------------------------+-------------------------+     
 *  |      byte_count         |        Frame ID         |
 *  +-------------------------+-------------------------+
 *
 * The byte_count field contains the size of the appended data, NOT including
 * the header.
 */
struct el_cobra_frame_header {
	u_int	elcf_fid;	/* Frame ID (from above) */
	u_int	elcf_size;	/* Size of frame in bytes */
};

/*
 * Frame Identifiers.  Placed in the fid field of each record.
 * COBRA_FID_S_BC_CORR is obsolete.
 * COBRA_FID_PSC is not implemented.
 */
#define COBRA_FID_END_FRAME	0/* a null quadword header. */
#define COBRA_FID_IO		1/* el_cobra_frame_io */
#define COBRA_FID_MCHECK	2/* el_cobra_frame_mcheck */
#define COBRA_FID_P_BC_CORR	3/* el_cobra_frame_proc_bcache_corr */
#define COBRA_FID_S_BC_CORR	4/* el_cobra_frame_sys_bcache_corr */
#define COBRA_FID_OCPU		5/* el_cobra_frame_other_cpu */
#define COBRA_FID_PSC		6/* el_cobra_frame_power_system */
#define COBRA_FID_FRU		7/* el_cobra_frame_fru */
#define COBRA_FID_MEMORY	8/* el_cobra_frame_memory */

/* 
 * Logout Frame Header.  This is part of any error log frame that may have
 * been received from PAL.  When running under OSF PAL, the logout information
 * in the OSF PAL logout frame header is translated to have this format,
 * so that the bit-to-text tools don't have to be concerned about which
 * header format was present.
 */
struct el_cobra_logout_header {
	int	elcl_size;		/* size in bytes of logout area. */
	int	elcl_sbz1:30;		/* Should be zero. */
	char	elcl_missed:1;		/* Missed correctible error flag. */
	char	elcl_rty:1;		/* Retry flag. */
        int	elcl_procoffset;	/* Processor-specific offset. */
	int	elcl_sysoffset;		/* Offset of system-specific. */
	int	elcl_error_type;	/* PAL error type code. */
	int	elcl_frame_rev;		/* PAL Frame revision. */
};

#define KN430_ERROR_TYPE(elcl) (elcl)->elcl_error_type

/*
 * Cobra Machine Check Frame.
 *
 *  |6                       3|3             
 *  |3                       2|1                       0|
 *  +-------------------------+-------------------------+     
 *  |        Byte_count       |   COBRA_FID_MCHECK      | Error Handler 
 *  +-------------------------+-------------------------+ built header 
 *  +-+-----------------------+------------+------------+-+
 *  |R|                       |        byte count       | | Logout Frame Header
 *  +-+-----------------------+------------+------------+ |
 *  |   SYS$$OFFSET = [   ]   | PROC$$OFFSET = [   ]    | |
 *  +-------------------------+-------------------------+ |
 *  |   M-Check_Frame_Rev     |  PAL_Error_Type_code    | |
 *  +-------------------------+-------------------------+-+
 *  |                                                   |
 *  |                   PAL TEMPS (1-31)                |
 *  |                                                   |
 *  +------------+------------+------------+------------+
 *  |                     EXC_ADDR                      |
 *  +------------+------------+------------+------------+
 *  |                      EXC_SUM                      |
 *  +------------+------------+------------+------------+
 *  |                      EXC_MSK                      |
 *  +------------+------------+------------+------------+
 *  |                       ICCSR                       |
 *  +------------+------------+------------+------------+
 *  |                      PAL_BASE                     |
 *  +------------+------------+------------+------------+
 *  |                        HIER                       |
 *  +------------+------------+------------+------------+
 *  |                        HIRR                       |
 *  +------------+------------+------------+------------+
 *  |                       MM_CSR                      |
 *  +------------+------------+------------+------------+
 *  |                       DC_STAT                     |
 *  +------------+------------+------------+------------+
 *  |                       DC_ADDR                     |
 *  +------------+------------+------------+------------+
 *  |                      ABOX_CTL                     |
 *  +------------+------------+------------+------------+
 *  |                      BIU_STAT                     |
 *  +------------+------------+------------+------------+
 *  |                     BIU_ADDR                      |
 *  +------------+------------+------------+------------+
 *  |                      BIU_CTL                      |      
 *  +------------+------------+------------+------------+      
 *  |                   FILL_SYNDROME                   |      
 *  +------------+------------+------------+------------+      
 *  |                     FILL_ADDR                     |      
 *  +------------+------------+------------+------------+      
 *  |                        VA                         |      
 *  +------------+------------+------------+------------+      
 *  |                       BC_TAG                      |      
 *  +------------+------------+------------+------------+      
 */
/*  +------------+------------+------------+------------+      
 *  |                      BCC-CSR0                     |:+1A0 COBRA Specific:
 *  +------------+------------+------------+------------+      
 *  |                      BCCE-CSR1                    |
 *  +------------+------------+------------+------------+      
 *  |                      BCCEA-CSR2                   |
 *  +------------+------------+------------+------------+      
 *  |                      BCUE-CSR3                    |
 *  +------------+------------+------------+------------+      
 *  |                      BCUEA-CSR4                   |
 *  +------------+------------+------------+------------+      
 *  |                      DTER-CSR5                    |
 *  +------------+------------+------------+------------+      
 *  |                      CBCTL-CSR6                   |
 *  +------------+------------+------------+------------+      
 *  |                      CBE-CSR7                     |
 *  +------------+------------+------------+------------+      
 *  |                      CBEAL-CSR8                   |
 *  +------------+------------+------------+------------+      
 *  |                      CBEAH-CSR9                   |
 *  +------------+------------+------------+------------+      
 *  |                      PMBX-CSR10                   |
 *  +------------+------------+------------+------------+      
 *  |                      IPIR-CSR11                   |
 *  +------------+------------+------------+------------+      
 *  |                      SIC-CSR12                    |
 *  +------------+------------+------------+------------+      
 *  |                      ADLK-CSR13                   |
 *  +------------+------------+------------+------------+      
 *  |                      MADRL-CSR14                  |
 *  +------------+------------+------------+------------+      
 */

#define KN430_ELCMC_REV_CURRENT 1

struct el_cobra_data_mcheck {
	struct el_cobra_logout_header elcmc_lhdr;

	u_long	    elcmc_paltemp[KN430_PALTEMPS];

	vm_offset_t elcmc_exc_addr;   /* Address of excepting instruction. */
	u_long	    elcmc_exc_sum;    /* Summary of arithmetic traps. */
	u_long	    elcmc_exc_mask;   /* Exception mask (from exc_sum). */
	u_long	    elcmc_iccsr;      /* IBox hardware enables. */
	vm_offset_t elcmc_pal_base;   /* Base address for PALcode. */
	u_long	    elcmc_hier;	      /* Hardware Interrupt Enable. */
	u_long	    elcmc_hirr;	      /* Hardware Interrupt Request. */
	u_long	    elcmc_mm_csr;     /* D-stream fault info. */
	u_long	    elcmc_dc_stat;    /* D-cache status (ECC/Parity Err). */
	u_long	    elcmc_dc_addr;    /* EV3 Phys Addr for ECC/DPERR. */
	u_long	    elcmc_abox_ctl;   /* ABox Control Register. */
	u_long	    elcmc_biu_stat;   /* BIU Status. */
	vm_offset_t elcmc_biu_addr;   /* BUI Address. */
	u_long	    elcmc_biu_ctl;    /* BIU Control. */
	u_long	    elcmc_fill_syndrome; /* For correcting ECC errors. */
	vm_offset_t elcmc_fill_addr;  /* Cache block which was being read. */
	vm_offset_t elcmc_va;	      /* Effective VA of fault or miss. */
	u_long	    elcmc_bc_tag;     /* Backup Cache Tag Probe Results. */
	u_long	    elcmc_bcc;	      /* CSR 0 */
	u_long	    elcmc_bcce;	      /* CSR 1 */
	u_long	    elcmc_bccea;      /* CSR 2 */
	u_long	    elcmc_bcue;	      /* CSR 3 */
	u_long	    elcmc_bcuea;      /* CSR 4 */
	u_long	    elcmc_dter;	      /* CSR 5 */
	u_long	    elcmc_cbctl;      /* CSR 6 */
	u_long	    elcmc_cbe;	      /* CSR 7 */
	u_long	    elcmc_cbeal;      /* CSR 8 */
	u_long	    elcmc_cbeah;      /* CSR 9 */
	u_long	    elcmc_pmbx;	      /* CSR 10 */
	u_long	    elcmc_ipir;	      /* CSR 11 */
	u_long	    elcmc_sic;	      /* CSR 12 */
	u_long	    elcmc_adlk;	      /* CSR 13 */
	u_long	    elcmc_madrl;      /* CSR 14 */

#define elcmc_error_code elcmc_lhdr.elcl_error_type
#define KN430_MCHECK_ERROR_TYPE(elcmc) \
	KN430_ERROR_TYPE(&(elcmc)->elcmc_data.elcmc_lhdr)
};

struct el_cobra_frame_mcheck {
	struct el_cobra_frame_header elcmc_hdr; /* id == COBRA_FID_P_BC_COR */
	struct el_cobra_data_mcheck elcmc_data;
};

/*
 * PAL Error Codes, for the elcmc_error_code field.
 *
 * The following error code constants are placeholders, until the PAL sets
 * the machine check elcmc_error_code field.  These constants will need to be
 * updated to match whatever values are used by the PAL.
 */

/* This PAL doesn't implement full parse tree */
#define COBRA_PAL_UNIMP			0

/* B-Cache Tag Parity Error. */
#define COBRA_PAL_EV_T_PAR		128/*MCHK$C_TPERR*/

/* B-Cache Tag Control Parity Error. */
#define COBRA_PAL_EV_TC_PAR		130/*MCHK$C_TCPERR*/

/* Hard error asserted. */
#define COBRA_PAL_HERR			132/*MCHK$C_HERR*/

/* B-Cache Correctable. */
#define COBRA_PAL_ECC_C			134/*MCHK$C_ECC_C*/

/* B-Cache Uncorrectable Error. */
#define COBRA_PAL_EV_C_UNCORR		136/*MCHK$C_ECC_NC*/

/* PAL didn't recognize the error. */
#define COBRA_PAL_UNKNOWN		138/*MCHK$C_UNKNOWN*/

/* Cycle terminated by CACK_SOFT */
#define COBRA_PAL_SCE			140/*MCHK$C_SCE*/

/* PAL Bugcheck (internal error) */
#define COBRA_PAL_BUGCHECK		142/*MCHK$C_BUGCHECK*/

/* OS Bugcheck */
#define COBRA_PAL_OS_BUGCHECK		144/*MCHK$C_OS_BUGCHECK*/

#define COBRA_PAL_DCPERR		146/*MCHK$C_DCPERR*/
#define COBRA_PAL_ICPERR		148/*MCHK$C_ICPERR*/

/*
 * DEC 4000 - Specific Codes (>255).
 */

/* C3 Detected Tag Parity Error. */
#define COBRA_PAL_C3_TAG_PAR		256/*MCHK$C_C3_TAG_PAR*/

/* C3 detected/corrected correctable B-Cache Error */
#define COBRA_PAL_C3_CORR		258/*MCHK$C_C3_CORR*/

/* Last B-Cache Error (OS is disabling B-Cache errors). */
#define COBRA_PAL_ECC_C_LAST (COBRA_PAL_ECC_C+256)/*MCHK$C_ECC_C_LAST*/


/*
 * Cobra Processor B-Cache Correctible Error Frame.
 *
 *  |6                       3|3             
 *  |3                       2|1                       0|
 *  +-------------------------+-------------------------+     
 *  |        Byte_count       |   COBRA_FID_P_BC_CORR   | Error Handler 
 *  +-------------------------+-------------------------+ built header 
 *  +-+----------+------------+------------+------------+-+
 *  |R|                       |        byte count       | | Logout Frame Header
 *  +-+----------+------------+------------+------------+ |
 *  |   SYS$$OFFSET = [   ]   | PROC$$OFFSET = [   ]    | |
 *  +-------------------------+-------------------------+ |
 *  |   M-Check_Frame_Rev     |  PAL_Error_Type_code    | |
 *  +-------------------------+-------------------------+-+
 *  |                      BIU_STAT                     | :+10
 *  +------------+------------+------------+------------+
 *  |                     BIU_ADDR                      | :+18
 *  +------------+------------+------------+------------+
 *  |                      BIU_CTL                      | :+20
 *  +------------+------------+------------+------------+
 *  |                   FILL_SYNDROME                   | :+28
 *  +------------+------------+------------+------------+
 *  |                     FILL_ADDR                     | :+30
 *  +------------+------------+------------+------------+
 *  |                       BC_TAG                      | :+38
 *  +------------+------------+------------+------------+
 *
 * Note: This frame will be supplied by PAL when the PAL code has successfully
 * corrected an error within the B-Cache.
 */
#define KN430_ELCPB_REV_CURRENT 1

struct el_cobra_data_proc_bcache_corr {
	struct	el_cobra_logout_header elcpb_lhdr;
	u_long	elcpb_biu_stat;
	u_long	elcpb_biu_addr;
	u_long	elcpb_biu_ctl;
	u_long	elcpb_fill_syndrome;
	u_long	elcpb_fill_addr;
	u_long	elcpb_bc_tag;
};

struct el_cobra_frame_proc_bcache_corr {
	struct el_cobra_frame_header elcpb_hdr; /* id == COBRA_FID_P_BC_COR */
	struct el_cobra_data_proc_bcache_corr elcpb_data;
};

/*
 * Cobra Memory Error Frame.
 *
 *  |6                       3|3             
 *  |3                       2|1                       0|
 *  +-------------------------+-------------------------+     
 *  |        Byte_count       |    COBRA_FID_MEMORY     | Error Handler 
 *  +-------------------------+-------------------------+ built header 
 *  +-------------------------+-------------------------+
 *  |                         |    Memory Module ID     |
 *  +-------------------------+-------------------------+ 
 *  |                   CSR0- Error Reg 1               | :+08
 *  +---------------------------------------------------+ 
 *  |                   CSR1- Command Trap 1            | :+10         
 *  +---------------------------------------------------+ 
 *  |                   CSR2- Command Trap 2            | :+18         
 *  +---------------------------------------------------+ 
 *  |                   CSR3- Config Register           | :+20         
 *  +---------------------------------------------------+ 
 *  |                   CSR4- EDC Status 1              | :+28         
 *  +---------------------------------------------------+ 
 *  |                   CSR5- EDC Status 2              | :+30         
 *  +---------------------------------------------------+ 
 *  |                   CSR6- EDC Control               | :+38         
 *  +---------------------------------------------------+ 
 *  |                   CSR7- Stream Buffer Control     | :+40         
 *  +---------------------------------------------------+ 
 *  |                   CSR8- Refresh Control           | :+48         
 *  +------------+------------+------------+------------+              
 */
struct el_cobra_data_memory {
	u_int	elcm_module;	/* Module id. */
	u_int	elcm_res04;	/* Reserved. */
	u_long	elcm_merr;	/* CSR0: Error Reg 1. */
	u_long	elcm_mcmd1;	/* CSR1: Command Trap 1. */
	u_long	elcm_mcmd2;	/* CSR2: Command Trap 2. */
	u_long	elcm_mconf;	/* CSR3: Configuration. */
	u_long	elcm_medc1;	/* CSR4: EDC Status 1. */
	u_long	elcm_medc2;	/* CSR5: EDC Status 2. */
	u_long	elcm_medcc;	/* CSR6: EDC Control. */
	u_long	elcm_msctl;	/* CSR7: Stream Buffer Control. */
	u_long	elcm_mref;	/* CSR8: Refresh Control. */
	u_long  elcm_filter;	/* CSR9: CRD Filter Control. */
};

struct el_cobra_frame_memory {
	struct	el_cobra_frame_header elcm_hdr; /* id == COBRA_FID_MEMORY */
	struct el_cobra_data_memory elcm_data;
};

/*
 * Other CPU Error.  Built when one CPU has an error due to an error in the
 * other CPU's B-Cache.
 *
 *  |6                       3|3             
 *  |3                       2|1                       0|
 *  +-------------------------+-------------------------+     
 *  |        Byte_count       |     COBRA_FID_OCPU      | Error Handler 
 *  +-------------------------+-------------------------+ built header 
 *  +--------------------------------------+------------+      
 *  |					   |   CPU ID   | :+00
 *  +--------------------------------------+------------+      
 *  |                      BCC-CSR0                     |
 *  +---------------------------------------------------+      
 *  |                      BCCE-CSR1                    |
 *  +---------------------------------------------------+      
 *  |                      BCCEA-CSR2                   |
 *  +---------------------------------------------------+      
 *  |                      BCUE-CSR3                    |
 *  +---------------------------------------------------+      
 *  |                      BCUEA-CSR4                   |
 *  +---------------------------------------------------+      
 *  |                      DTER-CSR5                    |
 *  +---------------------------------------------------+      
 *  |                      CBCTL-CSR6                   |
 *  +---------------------------------------------------+      
 *  |                      CBE-CSR7                     |
 *  +---------------------------------------------------+      
 *  |                      CBEAL-CSR8                   |
 *  +---------------------------------------------------+      
 *  |                      CBEAH-CSR9                   |
 *  +---------------------------------------------------+      
 *  |                      PMBX-CSR10                   |
 *  +---------------------------------------------------+      
 *  |                      IPIR-CSR11                   |
 *  +---------------------------------------------------+      
 *  |                      SIC-CSR12                    |
 *  +---------------------------------------------------+      
 *  |                      ADLK-CSR13                   |
 *  +---------------------------------------------------+      
 *  |                      MADRL-CSR14                  |
 *  +---------------------------------------------------+      
 */
struct el_cobra_data_other_cpu {
	short	elco_cpuid;	/* CPU ID (0 or 1) */
	short	elco_res02[3];	
	u_long	elco_bcc;	/* CSR 0 */
	u_long	elco_bcce;	/* CSR 1 */
	u_long	elco_bccea;	/* CSR 2 */
	u_long	elco_bcue;	/* CSR 3 */
	u_long	elco_bcuea;	/* CSR 4 */
	u_long	elco_dter;	/* CSR 5 */
	u_long	elco_cbctl;	/* CSR 6 */
	u_long	elco_cbe;	/* CSR 7 */
	u_long	elco_cbeal;	/* CSR 8 */
	u_long	elco_cbeah;	/* CSR 9 */
	u_long	elco_pmbx;	/* CSR 10 */
	u_long	elco_ipir;	/* CSR 11 */
	u_long	elco_sic;	/* CSR 12 */
	u_long	elco_adlk;	/* CSR 13 */
	u_long	elco_madrl;	/* CSR 14 */
};

struct el_cobra_frame_other_cpu {
	struct	el_cobra_frame_header elco_hdr; /* id == COBRA_FID_OCPU */
	struct el_cobra_data_other_cpu elco_data;
};

/*
 * Cobra I/O Error Frame.
 *
 *  |6                       3|3             
 *  |3                       2|1                       0|
 *  +-------------------------+-------------------------+     
 *  |        Byte_count       |   COBRA_FID_IO          | Error Handler 
 *  +-------------------------+-------------------------+ built header 
 *  +---------------------------------------------------+
 *  |                       IOCSR                       | :+00
 *  +---------------------------------------------------+
 *  |                       CERR1                       |
 *  +---------------------------------------------------+
 *  |                       CERR2                       |
 *  +---------------------------------------------------+
 *  |                       CERR3                       |      
 *  +---------------------------------------------------+
 *  |                       LMBPR                       |      
 *  +---------------------------------------------------+
 *  |                       FMBPR                       |      
 *  +---------------------------------------------------+
 *  |                       DIAGCSR                     |      
 *  +---------------------------------------------------+
 *  |                       FERR1                       |      
 *  +---------------------------------------------------+
 *  |                       FERR2                       |      
 *  +---------------------------------------------------+
 *  |                       LINT                        |      
 *  +---------------------------------------------------+
 *  |                       LERR1                       |      
 *  +---------------------------------------------------+
 *  |                       LERR2                       |
 *  +---------------------------------------------------+
 */
struct el_cobra_data_io {
	u_long	elci_iocsr;
	u_long	elci_cerr1;
	u_long	elci_cerr2;
	u_long	elci_cerr3;
	u_long	elci_lmbpr;
	u_long	elci_fmbpr;
	u_long	elci_diagcsr;
	u_long	elci_ferr1;
	u_long	elci_ferr2;
	u_long	elci_lint;  /* Not Used */
	u_long	elci_lerr1;
	u_long	elci_lerr2;
};
struct el_cobra_frame_io {
	struct	el_cobra_frame_header elci_hdr; /* id == COBRA_FID_IO */
	struct el_cobra_data_io elci_data;
};

/*
 * Cobra Field Replaceable Unit (configuration) Frame.
 *
 *  |6                       3|3             
 *  |3                       2|1                       0|
 *  +-------------------------+-------------------------+     
 *  |        Byte_count       |      COBRA_FID_FRU      | Error Handler 
 *  +-------------------------+-------------------------+ built header 
 *  |                                                   |
 *  /      Copy of the HWRPB:FRU_TABLE                  /
 *  |                                                   |
 *  +------------+------------+------------+------------+
 *
 *
 *  Note: This frame is copied from the HWRPB, and dropped into the
 *        Event log. 
 */
struct el_cobra_fru_header {
	u_long	cfru_checksum;
	u_int	cfru_size;
	u_char	cfru_rev;
	u_char  cfru_res_0d[3];
	u_int	cfru_response;
	u_int	cfru_res_14;
};

struct el_cobra_fru_entry_header {
	u_char	cfru_count;	/* Size in quadwords. */
	u_char	cfru_test;	/* Selftest flags. */
	u_char	cfru_id;	/* Device id. */
	u_char	cfru_fid;	/* Frame type. */
};

struct el_cobra_fru_io {
	struct	el_cobra_fru_entry_header cfru_ehdr;
	char	cfru_serial_number[10];
	short	cfru_res_0e;
	char	cfru_part_number[9];
	char	cfru_sw_rev;
	short	cfru_hw_rev;
};

struct el_cobra_fru_cpu {
	struct	el_cobra_fru_entry_header cfru_ehdr;
	char	cfru_serial_number[10];
	short	cfru_res_0e;
	char	cfru_part_number[9];
	char	cfru_sw_rev;
	short	cfru_hw_rev;
};

struct el_cobra_fru_mem {
	struct	el_cobra_fru_entry_header cfru_ehdr;
	char	cfru_serial_number[10];
	short	cfru_res_0e;
	char	cfru_part_number[9];
	char	cfru_sw_rev;
	short	cfru_hw_rev;
	short	cfru_mem_config;	/* Memory CSR3 (config) */
};

struct el_cobra_fru_ncr {
	struct	el_cobra_fru_entry_header cfru_ehdr;
	char	cfru_chip_rev;
	char	cfru_res_01; /* SBZ */
	char	cfru_bus_node_number;
	char	cfru_bus_number;
	char	cfru_name[12];
	u_char	cfru_ncr_scntl0;
	u_char	cfru_ncr_scntl1;
	u_char	cfru_ncr_ctest0;
	u_char	cfru_ncr_ctest7;
	u_char	cfru_ncr_dmode;
	u_char	cfru_ncr_dwt;
	u_char	cfru_ncr_dcntl1;
	u_char	cfru_ncr_res_1b; /* SBZ */
};

struct el_cobra_fru_psc {
	struct	el_cobra_fru_entry_header cfru_ehdr;
	char	cfru_part_number[7];
	char	cfru_rom_version;
	char	cfru_rom_rev_major;
	char	cfru_rom_rev_minor;
	char	cfru_psc_status;
	char	cfru_ups_baud_rate;
	char	cfru_ldc_present;
	char	cfru_ldc_enabled;
	char	cfru_ldc_operation;
	char	cfru_res_13; /* Reserved */
	int	cfru_res_14; /* SBZ */
};

struct el_cobra_fru_mst {
	struct	el_cobra_fru_entry_header cfru_ehdr;
	short	cfru_unit;
	char	cfru_bus_node_number;
	char	cfru_bus_number;
	char	cfru_name[20];
};

struct el_cobra_fru_mst_dssi {
	struct el_cobra_fru_mst cfru_mst;
};

struct el_cobra_fru_mst_scsi_i {
	struct el_cobra_fru_mst cfru_mst;
	u_char	cfru_dev_type:5;
	u_char	cfru_peripheral:3;
	u_char	cfru_dev_type_mod:6;
	u_char	cfru_removable:1;
	u_char	cfru_version_ansi:3;
	u_char	cfru_version_ecma:3;
	u_char	cfru_version_iso:2;
	u_char	cfru_res_03;
	u_char	cfru_len;
};

struct el_cobra_fru_mst_scsi_ii {
	struct el_cobra_fru_mst cfru_mst;
	u_char	cfru_dev_type:5;
	u_char	cfru_peripheral:3;
	u_char	cfru_dev_type_mod:6;
	u_char	cfru_removable:1;
	u_char	cfru_version_ansi:3;
	u_char	cfru_version_ecma:3;
	u_char	cfru_version_iso:2;
	u_char	cfru_response_fmt:4;
	u_char	cfru_res_03_04:2;
	u_char	cfru_TraIOP:1;
	u_char	cfru_AENC:1;
	u_char	cfru_len;
	u_char	cfru_res_20[2];
	u_char	cfru_rsp_flags;
	char	cfru_vendor_id[8];
	char	cfru_product_id[16];
	char	cfru_product_rev[4];
	char	cfru_vendor_spec[12];
};

struct el_cobra_data_fru {
	struct el_cobra_fru_header cfru_header;
	char cfru_pad[1400];	/* Pad to reasonable fru size. */
};

struct el_cobra_frame_fru {
	struct	el_cobra_frame_header elcu_hdr; /* id == COBRA_FID_FRU */
	struct el_cobra_data_fru elcu_data;
};

/*
 * Cobra FRU Frame Types.
 */
#define CFRU_FRAME_MIN 0
#define CFRU_FRAME_IO 1
#define CFRU_FRAME_CPU 2
#define CFRU_FRAME_MEM 3
#define CFRU_FRAME_FBUS 4
#define CFRU_FRAME_PSC 5
#define CFRU_FRAME_DISK 6 /* NCR Chip on I/O module */
#define CFRU_FRAME_SCSI_I 7
#define CFRU_FRAME_SCSI_II 8
#define CFRU_FRAME_DSSI 9
#define CFRU_FRAME_END 0xFF

/*
 * Cobra FRU Device IDs.
 */
#define CFRUID_IO	 0
#define CFRUID_CPU1	 1
#define CFRUID_CPU0	 2
#define CFRUID_MEM0	 3
#define CFRUID_MEM1	 4
#define CFRUID_MEM2	 5
#define CFRUID_MEM3	 6
#define CFRUID_FBUS1	 7
#define CFRUID_FBUS2	 8
#define CFRUID_FBUS3	 9
#define CFRUID_FBUS4	10
#define CFRUID_FBUS5	11
#define CFRUID_FBUS6	12
#define CFRUID_PSC	13
#define CFRUID_BUS0	14
#define CFRUID_BUS1	15
#define CFRUID_BUS2	16
#define CFRUID_BUS3	17
#define CFRUID_BUS4	18
#define CFRUID_MST	19
#define CFRUID_END	0xFF

/*
 * Cobra FRU Response Flags.
 */
#define CFRURSP_IO	(1L << CFRUID_IO)
#define CFRURSP_CPU0	(1L << CFRUID_CPU0)
#define CFRURSP_CPU1	(1L << CFRUID_CPU1)
#define CFRURSP_MEM0	(1L << CFRUID_MEM0)
#define CFRURSP_MEM1	(1L << CFRUID_MEM1)
#define CFRURSP_MEM2	(1L << CFRUID_MEM2)
#define CFRURSP_MEM3	(1L << CFRUID_MEM3)
#define CFRURSP_FBUS1	(1L << CFRUID_FBUS1)
#define CFRURSP_FBUS2	(1L << CFRUID_FBUS2)
#define CFRURSP_FBUS3	(1L << CFRUID_FBUS3)
#define CFRURSP_FBUS4	(1L << CFRUID_FBUS4)
#define CFRURSP_FBUS5	(1L << CFRUID_FBUS5)
#define CFRURSP_FBUS6	(1L << CFRUID_FBUS6)
#define CFRURSP_PSC	(1L << CFRUID_PSC)
#define CFRURSP_BUS0	(1L << CFRUID_BUS0)
#define CFRURSP_BUS1	(1L << CFRUID_BUS1)
#define CFRURSP_BUS2	(1L << CFRUID_BUS2)
#define CFRURSP_BUS3	(1L << CFRUID_BUS3)
#define CFRURSP_BUS4	(1L << CFRUID_BUS4)
#define CFRURSP_MST	(1L << CFRUID_MST)

/*
 * Self-Test Codes.
 */
#define CFRUTEST_PASS		'P'
#define CFRUTEST_FAIL		'F'
#define CFRUTEST_UNKNOWN	0

/*****************************************************************************
 * Alpha Common Memory EDC Packet Header (eventually)			     *
 *****************************************************************************/

struct el_edc_header {
	short emb_revision;		/* Frame Revision */
	short emb_edc_flags;		/* State flags */
	short emb_log_reason;		/* Reason for this entry */
	struct emb_sequence_info {	/* Part N (this) of M (total) */
		unsigned char emb_total;

		unsigned char emb_this;
	} emb_part;
	int   emb_hwrpb_badpgs;		/* Known bad pages (or -1) */
	int   emb_memdsc_size;		/* Size in bytes */
	int   emb_memdsc_offset;	/* Offset from start of header */
	int   emb_num_fprints;
	int   emb_fprint_size;		/* Size of one footprint */
	int   emb_fprint_offset;	/* Offset from start of header */
};

/* Frame Revisions */
#define EMB_CURRENT_REVISION 2

/* EDC Flags */
#define EMB_FLG_DISABLED (1L << 0)
#define EMB_FLG_LOST_INFO (1L << 1)
#define EMB_FLG_INHIBIT (1L << 2)

/* Reason Codes */
#define EMB_RSN_INIT_ERR 1	/* Initialization Error */
#define EMB_RSN_FPRINTS_FULL 2
#define EMB_RSN_SHUTDOWN 3
#define EMB_RSN_DOMAIN_GREW 4
#define EMB_RSN_BADPGS 5
#define EMB_RSN_THRESHOLD 6	/* Reached threshold for logging/suppression */

#define EMB_HWRPB_BADPGS_UNKNOWN (-1)

/*****************************************************************************
 * DEC 4000 Memory Descriptor						     *
 *									     *
 * Used in reporting of CRDs.  Information can be obtained from HWRPB FRU    *
 * table by zeroing out some of the fields.				     *
 *****************************************************************************/

#define KN430_MD_SERNUM_MAX 10
#define KN430_MD_PARTNUM_MAX 9

struct kn430_memdsc {
	struct kn430_md_node {
		unsigned char kn430_mdn_byte_count; 	/* SBZ */
		unsigned char kn430_mdn_selftest;	/* SBZ */
		unsigned char kn430_mdn_slot;		/* 0..3 */
		unsigned char kn430_mdn_res03;		/* SBZ */
	} kn430_md_node;
	char kn430_md_sernum[KN430_MD_SERNUM_MAX];
	short kn430_md_res0e;				/* SBZ */
	char kn430_md_partnum[KN430_MD_PARTNUM_MAX];/* "  B2002BA" */
	short kn430_md_res19;				/* SBZ */
	short kn430_md_hw_rev;				/* From iic eeprom */
	char kn430_md_res1c[3];				/* SBZ */
	int kn430_md_config;				/* CSR3<31:0> */
};

/*****************************************************************************
 * DEC 4000 CRD Footprint						     *
 *****************************************************************************/

struct kn430_edc_fprint {
	u_long kn430_mc_signature;	/* Hardware footprint */
	long kn430_mc_time;		/* System time footprint was created */
	long kn430_mc_lasttime;		/* Time footprint was last touched */
	vm_offset_t kn430_mc_addr_low;	/* Lowest matching physical address */
	vm_offset_t kn430_mc_addr_high;	/* Highest matching physical address */
	vm_offset_t kn430_mc_addr_cum;	/* 1's for bits seen 0 and 1 */
	int kn430_mc_scrub_blksz;	/* System scrub blocksize (0x20) */
	u_short kn430_mc_static_flags;	/* State of footprint */
	short kn430_mc_reason;		/* Reason for  */
	u_int kn430_mc_caller_flags;	/* */
	int kn430_mc_match_cnt;		/* CRDs matching this footprint */
};

/*
 * Signature fields for DEC 4000.
 *
 * The signature is made up of several fields:
 *	MFP_SLOT	Slot this memory module is in.
 *	MFP_HIGH_CMIC	High or Low CMIC.
 *	MFP_BANK	Bank the error was in.
 *	MFP_SYNDROME	Syndrome for the error.
 *
 * Unused bits should be zero.
 */
#define MFP_SYNDROME_SHIFT 0
#define MFP_SYNDROME (0xFFFL << MFP_SYNDROME_SHIFT)
#define MFP_HIGH_CMIC (1L << 15)
#define MFP_BANK_SHIFT 16
#define MFP_BANK (0x3L << MFP_BANK_SHIFT)
#define MFP_SLOT_SHIFT 24
#define MFP_SLOT (0x3L << MFP_SLOT_SHIFT)
#define MFP_UNUSED 0xFFFFFFFFFC000000L

/* Static flags */
#define KN430_MC_SFLG_BUSY (1 << 0)
#define KN430_MC_SFLG_SCRUBBED (1 << 1)
#define KN430_MC_SFLG_FILTER_SHIFT 2
#define KN430_MC_SFLG_FILTER (3 << KN430_MC_SFLG_FILTER_SHIFT)


/* Reason codes */
#define KN430_MC_RSN_DOMAIN_GREW EMB_RSN_DOMAIN_GREW
#define KN430_MC_RSN_THRESHOLD EMB_RSN_THRESHOLD

/* Caller Flags */
#define KN430_MC_CFLG_NOSCRUB (1L << 0) /* Don't scrub */
#define KN430_MC_CFLG_NOREPLACE (1L << 1) /* Don't replace page */
#define KN430_MC_CFLG_MULE (1L << 2) /* Multiple CRDs occurred */

/* Failure Mask */
#define KN430_MC_FAI_PFNTOOBIG (1L << 0)
#define KN430_MC_FAI_MCHK (1L << 1)
#define KN430_MC_FAI_MAPFAI (1L << 2)
#define KN430_MC_FAI_UNMAPFAI (1L << 3)
#define KN430_MC_FAI_TOOMANYRETRY (1L << 4)



struct el_rec {					/* errlog record packet */ 
	struct el_rhdr elrhdr;			/* record header */
	struct el_sub_id elsubid;		/* subsystem id packet */
	union {
		struct el_bdev elbdev;                  /* device errors     */
		struct el_ci elci;			/* ci events         */
		struct el_cippd elcippd;                /* ci ppd events     */
		struct el_esr elesr;			/* gernic err/stat  */
		struct el_exptflt elexptflt;            /* exception fault  */
		struct el_mem elmem;                    /* memory errors */
		struct el_msg elmsg;                    /* ascii text msg    */
		struct el_msi elmsi;			/* msi events	     */
		struct el_pnc elpnc;                    /* panic frame       */
		struct el_strayintr elstrayintr;        /* stray interrupts  */
		struct el_scs elscs;               	/* scs events	     */
		struct el_stkdmp elstkdmp;              /* stack dump        */
		struct el_timchg eltimchg;		/* time change  &    */
							/* startup/shutdown  */
		struct el_uq eluq;                      /* uq port errors    */
		struct el_xna elxna;                    /* xna port errors   */
		struct el_vba   el_vba;                 /* VME adapter errs */
		struct el_vme_dev_cntl elvme_devcntl;   /* VME dev/crtl errs */
		struct el_fza	el_fza;			/* fza port errors */
		struct el_fta   el_fta;                 /* fta port errors */
	} el_body;
	char eltrailer[EL_TRAILERSIZE];			/* asc trailer code  */
};



/*
 * pfms <chapter Ruby error log packets>.2.5 ; fig.x-6
 *
 * Software Error Flags:
 *
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |            reserved           |        PACKET_REVISION        | :00
 * +-------------------------------+-------------------------------+
 * |                                                               | :08
 * +---                     THIS_ERROR_FLAGS                    ---+
 * |                                                               | :10
 * +-------------------------------+-------------------------------+
 *
 */

#ifdef __alpha

 /* define packet present bits. These reside in the second quadword, */
 /* but are refered to in the PFMS as bits offset from the base of the */
 /* elr_soft_flags structure. */

#define SW_FLAG0_INCONSISTENT			(1L<<0)

/* software flags for machine check error frames */
#define SW_FLAG0_READ_BTAG_APE			(1L<<1)
#define SW_FLAG0_WRITE_BTAG_APE			(1L<<2)
#define SW_FLAG0_BIU_INCON			(1L<<3)
#define SW_FLAG0_READ_BTAG_CTRL_PE		(1L<<4)
#define SW_FLAG0_WRITE_BTAG_CTRL_PE		(1L<<5)
#define SW_FLAG0_ISTRM_BCACHE_SBE		(1L<<6)
#define SW_FLAG0_ISTRM_BCACHE_DBE		(1L<<7)
#define SW_FLAG0_LSB_CE				(1L<<8)
#define SW_FLAG0_ISTRM_RD_OTHER_CPU_BCACHE_SBE	(1L<<9)

#define SW_FLAG0_ISTRM_READ_EDAL_SBE		(1L<<11)
#define SW_FLAG0_ISTRM_READ_MEM_DBE		(1L<<12)
#define SW_FLAG0_ISTRM_RD_OTHER_CPU_BCACHE_DBE	(1L<<13)
#define SW_FLAG0_ISTRM_RD_LSB_DBE		(1L<<14)
#define SW_FLAG0_ISTRM_RD_EDAL_DBE		(1L<<15)
#define SW_FLAG0_DSTRM_RD_BCACHE_SBE		(1L<<16)
#define SW_FLAG0_DSTRM_RD_BCACHE_DBE		(1L<<17)
#define SW_FLAG0_DSTRM_RD_LSB_SBE		(1L<<18)
#define SW_FLAG0_DSTRM_RD_OTHER_CPU_BCACHE_SBE	(1L<<19)

#define SW_FLAG0_DSTRM_RD_EDAL_SBE		(1L<<21)
#define SW_FLAG0_DSTRM_RD_MEM_DBE		(1L<<22)
#define SW_FLAG0_DSTRM_RD_OTHER_CPU_BCACHE_DBE	(1L<<23)
#define SW_FLAG0_DSTRM_RD_LSB_DBE		(1L<<24)
#define SW_FLAG0_DSTRM_RD_EDAL_DBE		(1L<<25)

#define SW_FLAG0_EV4_READBLOCK			(1L<<31)
#define SW_FLAG0_EV4_WRITEBLOCK			(1L<<32)
#define SW_FLAG0_EV4_LOADLOCK			(1L<<33)
#define SW_FLAG0_EV4_STORECOND			(1L<<34)

#define SW_FLAG0_CPU_NSES			(1L<<40)
#define SW_FLAG0_670_ARBDROP			(1L<<41)
#define SW_FLAG0_670_ARBCOL			(1L<<42)
#define SW_FLAG0_670_BTAGPE			(1L<<43)
#define SW_FLAG0_670_BSTATPE			(1L<<44)
#define SW_FLAG0_670_INCONSISTENT_1		(1L<<45)
#define SW_FLAG0_LSB_ERR_PRIVATE		(1L<<46)
#define SW_FLAG0_LSB_ERR_RD_CSR			(1L<<47)
#define SW_FLAG0_LSB_ERR_READ			(1L<<48)
#define SW_FLAG0_LSB_ERR_WRITE			(1L<<49)

#define SW_FLAG0_LSB_ERR_WRT_CSR		(1L<<50)
#define SW_FLAG0_SHARED_ERROR			(1L<<51)
#define SW_FLAG0_DIRTY_ERROR			(1L<<52)
#define SW_FLAG0_STALL_ERROR			(1L<<53)
#define SW_FLAG0_CNF_ERROR			(1L<<54)
#define SW_FLAG0_CA_ERROR			(1L<<55)
#define SW_FLAG0_NXM_CSR_READ			(1L<<56)
#define SW_FLAG0_NXM_MEM_READ			(1L<<57)
#define SW_FLAG0_NXM_PRIVATE_SPACE		(1L<<58)
#define SW_FLAG0_670_CPE2			(1L<<59)

#define SW_FLAG0_670_CPE			(1L<<60)
#define SW_FLAG0_CTCE				(1L<<61)
#define SW_FLAG0_LSB_UCE2			(1L<<62)
#define SW_FLAG0_LSB_CDPE			(1L<<63)

#define SW_FLAG1_LSB_CE2			(1L<<(64-64))

#define SW_FLAG1_NXM_MEM_WRITE			(1L<<(66-64))

#define SW_FLAG1_PREVIOUS_SYSTEM_ERROR_LATCHED	(1L<<(69-64))
#define SW_FLAG1_670_INCONSISTENT_2		(1L<<(70-64))

#define SW_FLAG1_CACHE_FILL_SEO			(1L<<(94-64))
#define SW_FLAG1_BIU_SEO			(1L<<(95-64))

/* 660 error flags */
#define SW_FLAG0_660_ARBDRP			(1L<<1)
#define SW_FLAG0_660_ARBCOL			(1L<<2)
#define SW_FLAG0_BMAPPE				(1L<<3)
#define SW_FLAG0_PMAPPE				(1L<<4)
#define SW_FLAG0_BDATASBE			(1L<<5)
#define SW_FLAG0_BDATADBE			(1L<<6)
#define SW_FLAG0_660_BTAGPE			(1L<<7)
#define SW_FLAG0_660_BSTATPE			(1L<<8)
#define SW_FLAG0_INCON_NSES			(1L<<9)

#define SW_FLAG0_LSB_ERR			(1L<<16)
#define SW_FLAG0_SHE				(1L<<17)
#define SW_FLAG0_DIE				(1L<<18)
#define SW_FLAG0_STE				(1L<<19)

#define SW_FLAG0_CNFE				(1L<<20)
#define SW_FLAG0_CAE				(1L<<21)
#define SW_FLAG0_NXAE				(1L<<22)
#define SW_FLAG0_660_CPE			(1L<<23)
#define SW_FLAG0_CE				(1L<<24)
#define SW_FLAG0_UCE				(1L<<25)
#define SW_FLAG0_WRT_CDPE			(1L<<26)
#define SW_FLAG0_BCACHE_FILL_2_3_CE		(1L<<27)
#define SW_FLAG0_BYSTANDER_CE			(1L<<28)
#define SW_FLAG0_BCACHE_FILL_2_3_UCE		(1L<<29)

#define SW_FLAG0_BYSTANDER_UCE			(1L<<30)
#define SW_FLAG0_LBER_INCON			(1L<<31)
#define SW_FLAG0_UCE2				(1L<<32)
#define SW_FLAG0_CE2				(1L<<33)
#define SW_FLAG0_660_CPE2			(1L<<34)
#define SW_FLAG0_CDPE2				(1L<<35)
#define SW_FLAG0_IOP_CMDR			(1L<<36)

#define SW_FLAG0_IOP_STE			(1L<<40)
#define SW_FLAG0_IOP_CAE			(1L<<41)
#define SW_FLAG0_IOP_CNFE			(1L<<42)

#define SW_FLAG0_IOP_LSB_WRITE			(1L<<45)
#define SW_FLAG0_IOP_LSB_READ			(1L<<46)
#define SW_FLAG0_IOP_LSB_CSR_WRITE		(1L<<47)
#define SW_FLAG0_IOP_NXAE			(1L<<48)
#define SW_FLAG0_IOP_NXAE_INCON			(1L<<49)

#define SW_FLAG0_IOP_CPE			(1L<<50)
#define SW_FLAG0_IOP_CPE_INCON			(1L<<51)
#define SW_FLAG0_IOP_CDPE			(1L<<52)
#define SW_FLAG0_IOP_CE				(1L<<53)
#define SW_FLAG0_IOP_UCE			(1L<<54)
#define SW_FLAG0_IOP_LSB_INCON_STATE		(1L<<55)
#define SW_FLAG0_IOP_CPE2			(1L<<56)
#define SW_FLAG0_IOP_CDPE2			(1L<<57)
#define SW_FLAG0_IOP_CE2			(1L<<58)
#define SW_FLAG0_IOP_UCE2			(1L<<59)

#define SW_FLAG0_IOP_NSES			(1L<<60)
#define SW_FLAG0_660_INCON			(1L<<61)

/* 630 error flags */
#define SW_FLAG0_ISTRM_BCACHE_SBE		(1L<<6)
#define SW_FLAG0_630_INCONSISTENT_1		(1L<<7)
#define SW_FLAG0_LSB_CE				(1L<<8)
#define SW_FLAG0_ISTRM_RD_OTHER_CPU_BCACHE_SBE	(1L<<9)

#define SW_FLAG0_ISTRM_READ_EDAL_SBE		(1L<<11)

#define SW_FLAG0_DSTRM_RD_BCACHE_SBE		(1L<<16)
#define SW_FLAG0_630_INCONSISTENT_2		(1L<<17)
#define SW_FLAG0_DSTRM_RD_LSB_SBE		(1L<<18)
#define SW_FLAG0_DSTRM_RD_OTHER_CPU_BCACHE_SBE	(1L<<19)

#define SW_FLAG0_DSTRM_RD_EDAL_SBE		(1L<<21)

/* Common error flags */
#define SW_FLAG1_LSB_PRESENT			(1L<<(96-64))
#define SW_FLAG1_LMA_PRESENT			(1L<<(97-64))
#define SW_FLAG1_LOG_ADAPT_PRES			(1L<<(98-64))
#define SW_FLAG1_DLIST_PRESENT			(1L<<(99-64))
#define SW_FLAG1_LOG_CRD			(1L<<(104-64))
#define SW_FLAG1_UNLOCKFAIL			(1L<<(105-64))
#define SW_FLAG1_LMA_UNLOCKFAIL			(1L<<(106-64))
#define SW_FLAG1_LA_NOTLOCKED			(1L<<(107-64))
#define SW_FLAG1_ALL_ENABLED			(1L<<(110-64))
#define SW_FLAG1_CHANNEL_SUBPACKET_PRES		(1L<<(111-64))
#define SW_FLAG1_XMI_SUBPACKET_PRES		(1L<<(112-64))
#define SW_FLAG1_INHIBIT_LOGGING		(1L<<(123-64))
#define SW_FLAG1_REMOVE_CPU			(1L<<(124-64))
#define SW_FLAG1_LOOP				(1L<<(125-64))
#define SW_FLAG1_ABORT				(1L<<(126-64))
#define SW_FLAG1_BUGCHECK			(1L<<(127-64))

/* Common error flags for Turbo Laser */
#define SW_FLAG1_630_LOGGING_OFF		(1L<<(97-64))
#define SW_FLAG1_620_LOGGING_OFF		(1L<<(98-64))
#define SW_FLAG1_FLAG_SUBPACKET_PRES            (1L<<(114-64))
#define SW_FLAG1_PCIA_SUBPACKET_PRES            (1L<<(115-64))
#define SW_FLAG1_EISA_SUBPACKET_PRES            (1L<<(116-64))
#define SW_FLAG1_PCI_BUS_SNAP                   (1L<<(117-64))

/* IOP Adapter Software Flags */
#define SW_IOP_HOSE3_ERROR			(1L<<16)
#define SW_IOP_HOSE2_ERROR			(1L<<17)	
#define SW_IOP_HOSE1_ERROR			(1L<<18)	
#define SW_IOP_HOSE0_ERROR			(1L<<19)	
#define SW_IOP_MULTINTR_ERROR			(1L<<20)
#define SW_IOP_DNVRTX_ERROR			(1L<<21)	
#define SW_IOP_UPVRTX_ERROR			(1L<<22)	
#define SW_IOP_IPCIE_ERROR			(1L<<23)	
#define SW_IOP_UPHICIE_ERROR			(1L<<24)
#define SW_IOP_UPHOSE3PAR_ERROR			(1L<<25)	
#define SW_IOP_UPHOSE2PAR_ERROR			(1L<<26)	
#define SW_IOP_UPHOSE1PAR_ERROR			(1L<<27)
#define SW_IOP_UPHOSE0PAR_ERROR			(1L<<28)
#define SW_IOP_UPHOSE3PKT_ERROR			(1L<<29)
#define SW_IOP_UPHOSE2PKT_ERROR			(1L<<30)
#define SW_IOP_UPHOSE1PKT_ERROR			(1L<<31)
#define SW_IOP_UPHOSE0PKT_ERROR			(1L<<32)
#define SW_IOP_UPHOSE3OFLO_ERROR		(1L<<33)
#define SW_IOP_UPHOSE2OFLO_ERROR		(1L<<34)
#define SW_IOP_UPHOSE1OFLO_ERROR		(1L<<35)
#define SW_IOP_UPHOSE0OFLO_ERROR		(1L<<36)
#define SW_IOP_HOSE_PWRFAIL_3			(1L<<37)
#define SW_IOP_HOSE_PWRFAIL_2			(1L<<38)
#define SW_IOP_HOSE_PWRFAIL_1			(1L<<39)
#define SW_IOP_HOSE_PWRFAIL_0			(1L<<40)
#define SW_IOP_HOSE_PWRUP_3			(1L<<41)
#define SW_IOP_HOSE_PWRUP_2			(1L<<42)
#define SW_IOP_HOSE_PWRUP_1			(1L<<43)
#define SW_IOP_HOSE_PWRUP_0			(1L<<44)
#define SW_IOP_INCON				(1L<<45)

/* Lamb Adapter Software Flags */
#define SW_LAMB_RESPONDER_ERROR			(1L<<0)
#define SW_LAMB_COMMANDER_ERROR			(1L<<1)
#define SW_LAMB_CC_ERROR			(1L<<2)
#define SW_LAMB_WEI_ERROR			(1L<<3)
#define SW_LAMB_IPE_ERROR			(1L<<4)
#define SW_LAMB_PE_ERROR			(1L<<5)
#define SW_LAMB_WSE_ERROR			(1L<<6)
#define SW_LAMB_RIDNAK_ERROR			(1L<<7)
#define SW_LAMB_WDNAK_ERROR			(1L<<8)
#define SW_LAMB_CRD_ERROR			(1L<<9)
#define SW_LAMB_NRR_ERROR			(1L<<10)
#define SW_LAMB_RSE_ERROR			(1L<<11)
#define SW_LAMB_RER_ERROR			(1L<<12)
#define SW_LAMB_CNAK_ERROR			(1L<<13)
#define SW_LAMB_TTO_ERROR			(1L<<14)
#define SW_LAMB_DHDPE_ERROR			(1L<<15)
#define SW_LAMB_MBPE_ERROR			(1L<<16)
#define SW_LAMB_MBIC_ERROR			(1L<<17)
#define SW_LAMB_MBIA_ERROR			(1L<<18)
#define SW_LAMB_DFDPE_ERROR			(1L<<19)
#define SW_LAMB_RBDPE_ERROR			(1L<<20)
#define SW_LAMB_INCON				(1L<<21)


struct elr_error_flags0 {
	long unused:1;		/* bit 00 */
	long rsvd1:1;		/* bit 01 */
	long rsvd2:62;		/* bit 63:02 */
};

struct elr_error_flags1 {
	long rsvd1:31;		/* bit 94:64 */
	long biu_seo:1;		/* bit 95 */
	long rsvd2:32;		/* bit 127:96 */
};

#endif

/*
 * Software Error flags
 */
struct elr_soft_flags {
	int packet_revision;
	int rsvd1;
	u_long error_flags[2];
};

/* dlist longword */
struct dlist_lw {
	short disable_mask;
	char mbz;
	char id;
};




/*
 * pfms <chapter Ruby error log packets>.3.1 ; fig. x-13
 *
 *  COMMON LEP HEADER AREA
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +                          LOGGING_OFF                          +
 * |                                                               | :08
 * +-------------------------------+-------------------------------+
 * |          HW_REVISION          |          ACTIVE_CPUS          | :10
 * +-------------------------------+-------------------------------+
 * |                      SYSTEM_SERIAL_NUMBER (10 bytes)          | :18
 * +-------------------------------+---------------+               +
 * |                     RSVD                      |               | :20
 * +-------------------------------+-------------------------------+
 * |                      MODULE_SERIAL_NUMBER (10 bytes)          | :28
 * +-------------------------------+---------------+               +
 * |                     RSVD                      |               | :30
 * +-------------------------------+-------------------------------+
 * |             SPARE             |       DISABLE_RESOURCE        | :38
 * +-------------------------------+-------------------------------+
 */

/*
 * Common LEP Header Area
 */

#define SN_SIZE 10
#define RSVD1_SIZE 6
#define RSVD2_SIZE 6

struct elr_lep_common_header {
	u_long log_off[2];
	int active_cpus;
	int hw_rev;
	char sys_sn[SN_SIZE];
	char rsvd1[RSVD1_SIZE];
	char mod_sn[SN_SIZE];
	char rsvd2[RSVD2_SIZE];
	struct dlist_lw dlist_lw;
	int spare;
};



/*
 * pfms <chapter Ruby error log packets>.2.2 ; fig. x-2
 *
 * LEP 670/660 MACHINE CHECK FRAME .............. (472 bytes)
 * 
 * 6          2 2          1 1
 * 3          4 3          6 5          8 7          0
 * +-+----------+------------+------------+------------+
 * |R|                                    | byte count |  :+00 :: Common Area ::
 * +-+----------+------------+------------+------------+  
 * |   SYS$$OFFSET = [168]   | PROC$$OFFSET = [110]    |  :+08
 * +------------+------------+------------+------------+  
 * |                                                   |  :+10
 * |                   PAL TEMPS (0-31)                |  
 * |                                                   |  
 * +------------+------------+------------+------------+     
 * |                     EXC_ADDR                      |  :+110
 * +------------+------------+------------+------------+      
 * |                      EXC_SUM                      |      
 * +------------+------------+------------+------------+      
 * |                      EXC_MSK                      |      
 * +------------+------------+------------+------------+      
 * |                       ICCSR                       |      
 * +------------+------------+------------+------------+      
 * |                      PAL_BASE                     |      
 * +------------+------------+------------+------------+      
 * |                        HIER                       |      
 * +------------+------------+------------+------------+      
 * |                        HIRR                       |      
 * +------------+------------+------------+------------+      
 * |                       MM_CSR                      |      
 * +------------+------------+------------+------------+      
 * |                       DC_STAT                     |      
 * +------------+------------+------------+------------+      
 * |                       DC_ADDR                     |      
 * +------------+------------+------------+------------+      
 * |                      ABOX_CTL                     |      
 * +------------+------------+------------+------------+      
 * |                      BIU_STAT                     |  :+168
 * +------------+------------+------------+------------+      
 * |                     BIU_ADDR                      |      
 * +------------+------------+------------+------------+      
 * |                      BIU_CTL                      |      
 * +------------+------------+------------+------------+      
 * |                   FILL_SYNDROME                   |      
 * +------------+------------+------------+------------+      
 * |                     FILL_ADDR                     |      
 * +------------+------------+------------+------------+      
 * |                        VA                         |      
 * +------------+------------+------------+------------+      
 * |                       BC_TAG                      |      
 * +------------+------------+------------+------------+      
 * | rsvd|$Whami| rsvd|$PMask| rsvd |$Intr| rsvd|$Halt |      
 * +------------+------------+------------+------------+      
 * |        LEP$LBER         |         LEP$LDEV        |      
 * +------------+------------+------------+------------+      
 * |       LEP$LMERR         |         LEP$LCNR        |      
 * +------------+------------+------------+------------+      
 * |       LEP$LBESR1        |        LEP$LBESR0       |      
 * +------------+------------+------------+------------+      
 * |       LEP$LBESR3        |        LEP$LBESR2       |      
 * +------------+------------+------------+------------+      
 * |       LEP$LBECR1        |        LEP$LBECR0       |      
 * +------------+------------+------------+------------+      
 * |       LEP$LLOCK         |        LEP$LMODE        |      
 * +------------+------------+------------+------------+      
 */

struct elr_lep_mchk_frame {
	char byte_cnt;
	char rsvd1[6];
	char retry; /* retry is really the high order bit of this */
			/* field */ 
	int proc_off;
	int sys_off;
	u_long pal_temp[32];
/* errlog.h struct el_ev4_data is identical to the following. */
	u_long exc_addr;
	u_long exc_sum;	
	u_long exc_msk;
	u_long iccsr;	
	u_long pal_base;		
	u_long hier;	
	u_long hirr;	
	u_long mm_csr;	
	u_long dc_stat;	
	u_long dc_addr;		
	u_long abox_ctl;	
	u_long biu_stat;	
	u_long biu_addr;
	u_long biu_ctl;
	u_long fill_synd;
	u_long fill_addr;
	u_long va;
	u_long bc_tag;
/* end common definition with errlog.h */
	u_long encoded_1;
	int lep_ldev;
	int lep_lber;
	int lep_lcnr;
	int lep_lmerr;
	int lep_lbesr0;
	int lep_lbesr1;
	int lep_lbesr2;
	int lep_lbesr3;
	int lep_lbecr0;
	int lep_lbecr1;
	int lep_lmode;
	int lep_llock;
};


/* EV5 Turbolaser TLEP machine check logout frame for 670/660 errorlog */

/* EV5 TLEP 670/660 MACHINE CHECK FRAME .............. (496 bytes)
 * 
 * 6          2 2          1 1
 * 3          4 3          6 5          8 7          0
 * +-+----------+------------+------------+------------+
 * |R|S|D|C|                              | byte count |  :+00  Common Area ::
 * +-+----------+------------+------------+------------+  
 * |   SYS$$OFFSET = [168]   | PROC$$OFFSET = [110]    |  :+08
 * +------------+------------+------------+------------+
 * |  MCHK Frame Rev         |  MCHK Reason mask       |
 * |------------+------------+------------+------------+  :+10
 * |                                                   |  
 * |                   PAL TEMPS (0-31)                |  
 * |                                                   |  
 * +------------+------------+------------+------------+     
 * |                     EXC_ADDR                      |  :+110
 * +------------+------------+------------+------------+      
 * |                      EXC_SUM                      |      
 * +------------+------------+------------+------------+      
 * |                      EXC_MASK                     |  :+120    
 * +------------+------------+------------+------------+      
 * |                      PAL_BASE                     |      
 * +------------+------------+------------+------------+      
 * |                        ISR                        |  :+130
 * +------------+------------+------------+------------+      
 * |                        ICSR                       |      
 * +------------+------------+------------+------------+      
 * |                    IC_PERR_STAT                   |  :+140
 * +------------+------------+------------+------------+      
 * |                    DC_PERR_STAT                   |      
 * +------------+------------+------------+------------+      
 * |                        VA                         |  :+150
 * +------------+------------+------------+------------+      
 * |                      MM_STAT                      |      
 * +------------+------------+------------+------------+      
 * |                      SC_ADDR                      |  :+160
 * +------------+------------+------------+------------+      
 * |                      SC_STAT                      |      
 * +------------+------------+------------+------------+      
 * |                   BC_TAG_ADDR                     |  :+170
 * +------------+------------+------------+------------+      
 * |                      EI_ADDR                      |  
 * +------------+------------+------------+------------+      
 * |                     FILL_SYN                      |  :+180
 * +------------+------------+------------+------------+      
 * |                      EI_STAT                      |      
 * +------------+------------+------------+------------+      
 * |                      LD_LOCK                      |  :+190
 * +------------+------------+------------+------------+      
 * |        reserved         | rsvd |MISCR| rsvd|WHAMI |  :+1A0 system area  
 * +------------+------------+------------+------------+      
 * |         TLBER           |          TLDEV          |      
 * +------------+------------+------------+------------+      
 * |       LEP$LMERR         |          TLCNR          |  :+1B0
 * +------------+------------+------------+------------+      
 * |         TLESR1          |          TLESR0         |      
 * +------------+------------+------------+------------+      
 * |         TLESR3          |          TLESR2         |  :+1C0
 * +------------+------------+------------+------------+      
 * |       TLMODCONFIG       |         TLEPAERR        |      
 * +------------+------------+------------+------------+    
 * |        TLEPDERR         |         TLEPMERR        |  :+1D0  
 * +------------+------------+------------+------------+    
 * |       TLINTRMASK1       |        TLINTRMASK0      |
 * +------------+------------+------------+------------+    
 * |       TLINTRSUM1        |        TLINTRSUM0       |  :+1E0
 * +------------+------------+------------+------------+    
 * |         SPARE2          |         TLEP_VMG        |  
 * +------------+------------+------------+------------+    
 */

/*  Tlaser 670/660 Machine check logout frame. This is used when the
 *        errorlog packet is built in tlaser_log_error() in 
 *       ./arch/alpha/hal/kn8ae.c and is a piece of the machine check
 *        errorlog packet
 */


struct elr_tlep_mchk_frame {
/* Common area */
        int     frame_size;  /* bits <31:0> of first quadword */            
        int     retry;       /* bit 63 of first quadword - retry */ 
                             /* bit 62 of first quadword - second_error bit */
        int     proc_off;      
        int     sys_off;
        long    frame_reason;      
/* PALcode area */
        long    paltemp[32];
/* CPU specific area */
        long    exc_addr;       
        long    exc_sum;        
        long    exc_mask;       
        long    pal_base;       
        long    isr;            
        long    icsr;           
        long    ic_perr_stat;   
        long    dc_perr_stat;   
        long    va;             
        long    mm_stat;        
        long    sc_addr;        
        long    sc_stat;        
        long    bc_tag_addr;    
        long    ei_addr;        
        long    fil_syn;       
        long    ei_stat;        
        long    ld_lock;        
/* System specific area */
        long    rsvdheader;     
        u_int   tldev;          
        u_int   tlber;          
        u_int   tlcnr;          
        u_int   tlvid;          
        u_int   tlesr0;         
        u_int   tlesr1;         
        u_int   tlesr2;         
        u_int   tlesr3;         
        u_int   tlepaerr;       
        u_int   tlmodconfig;    
        u_int   tlepmerr;       
        u_int   tlepderr;       
        u_int   tlintrmask0;
        u_int   tlintrmask1;
        u_int   tlintrsum0;
        u_int   tlintrsum1;
        u_int   tlep_vmg;       
        u_int   spare3;         
        u_int   spare4;
        u_int   spare5;
        u_int   spare6;
        u_int   spare7;
  };

/* EV6 Turbolaser TLEP machine check logout frame for 670/660 errorlog */

/* EV6 TLEP 670/660 MACHINE CHECK FRAME .............. (1152 bytes)
 * 
 *  6 6                     3 3
 *  3 2                     2 1                        0
 * +-+-+--------+------------+------------+------------+
 * |R|S|                     |         Frame Size      |  :+00  Common Area
 * +-+-+--------+------------+------------+------------+
 * |   System Area Offset    |   CPU Area Offset       |  :+08
 * +------------+------------+------------+------------+
 * |     MCHK Frame Rev      |        MCHK Code        |  :+10
 * |------------+------------+------------+------------+
 * |                     I_STAT                        |  :+18
 * |------------+------------+------------+------------+
 * |                     DC_STAT                       |  :+20
 * |------------+------------+------------+------------+
 * |                     C_ADDR                        |  :+28
 * |------------+------------+------------+------------+
 * |                     DC1_SYNDROME                  |  :+30
 * |------------+------------+------------+------------+
 * |                     DC0_SYNDROME                  |  :+38
 * |------------+------------+------------+------------+
 * |                     C_STAT                        |  :+40
 * |------------+------------+------------+------------+
 * |                     C_STS                         |  :+48
 * |------------+------------+------------+------------+
 * |                     RESERVED                      |  :+50
 * +------------+------------+------------+------------+      
 * |                     EXC_ADDR                      |  :+58
 * +------------+------------+------------+------------+      
 * |                     IER_CM                        |  :+60
 * +------------+------------+------------+------------+      
 * |                     ISUM                          |  :+68
 * +------------+------------+------------+------------+      
 * |                     MM_STAT                       |  :+70
 * +------------+------------+------------+------------+      
 * |                     PAL_BASE                      |  :+78
 * +------------+------------+------------+------------+      
 * |                     I_CTL                         |  :+80
 * +------------+------------+------------+------------+      
 * |                     PCTX                          |  :+88
 * +------------+------------+------------+------------+      
 * |                     RESERVED                      |  :+90
 * +------------+------------+------------+------------+      
 * |                     RESERVED                      |  :+98
 * +------------+------------+------------+------------+      
 * |        reserved         | rsvd |MISCR| rsvd|WHAMI |  :+A0 system area  
 * +------------+------------+------------+------------+      
 * |         TLBER           |          TLDEV          |  :+A8
 * +------------+------------+------------+------------+      
 * |         TLVID           |          TLCNR          |  :+B0
 * +------------+------------+------------+------------+      
 * |         TLESR1          |          TLESR0         |  :+B8
 * +------------+------------+------------+------------+      
 * |         TLESR3          |          TLESR2         |  :+C0
 * +------------+------------+------------+------------+      
 * |       TLMODCONFIG1      |       TLMODCONFIG0      |  :+C8
 * +------------+------------+------------+------------+    
 * |         TDIERR          |          TCCERR         |  :+D0  
 * +------------+------------+------------+------------+    
 * |       TLINTRMASK1       |        TLINTRMASK0      |  :+D8
 * +------------+------------+------------+------------+    
 * |       TLINTRSUM1        |        TLINTRSUM0       |  :+E0
 * +------------+------------+------------+------------+    
 * |        TL6WERR0         |         TLEP_VMG        |  :+E8  
 * +------------+------------+------------+------------+    
 * |        TL6WERR2         |        TL6WERR1         |  :+F0
 * +------------+------------+------------+------------+    
 * |         SPARE2          |        TL6WERR3         |  :+F8
 * +------------+------------+------------+------------+    
 * |         SPARE4          |         SPARE3          |  :+100
 * +------------+------------+------------+------------+    
 * |         SPARE6          |         SPARE5          |  :+108
 * +------------+------------+------------+------------+    
 * |         SPARE8          |         SPARE7          |  :+110
 * +------------+------------+------------+------------+    
 * |         SPARE10         |         SPARE9          |  :+118
 * +------------+------------+------------+------------+    
 */


/*  Tlaser 670/660 Machine check logout frame. This is used when the
 *        errorlog packet is built in tlaser_log_error() in 
 *       ./arch/alpha/hal/kn8ae.c and is a piece of the machine check
 *        errorlog packet
 */


struct elr_tlep6_mchk_frame {
/* Common area */
        int     frame_size;  /* bits <31:0> of first quadword */            
        int     retry;       /* bit 63 of first quadword - retry */ 
                             /* bit 62 of first quadword - second_error bit */
        int     proc_off;      
        int     sys_off;
	long	frame_reason;		/* MCHK Frame Rev / MCHK Code */
/* CPU specific area */
        long    i_stat;    
        long    dc_stat;    
        long    c_addr;    
        long    dc1_syndrome;        
        long    dc0_syndrome;        
        long    c_stat;    
        long    c_sts;    
	long	mm_stat;
        long    exc_addr;       
        long    ier_cm;        
        long    isum;       
	long	cpu_reserved1;
        long    pal_base;       
        long    i_ctl;            
        long    pctx;           
	long	cpu_reserved2;
	long	cpu_reserved3;
/* System specific area */
        long    rsvdheader;     
        u_int   tldev;          
        u_int   tlber;          
        u_int   tlcnr;          
	u_int	tlvid;
        u_int   tlesr0;         
        u_int   tlesr1;         
        u_int   tlesr2;         
        u_int   tlesr3;         
	u_int	tlmodconfig0;
	u_int	tlmodconfig1;
	u_int	tccerr;
	u_int	tdierr;
        u_int   tlintrmask0;
        u_int   tlintrmask1;
        u_int   tlintrsum0;
        u_int   tlintrsum1;
        u_int   tlep_vmg;       
	u_int	tl6werr0;
	u_int	tl6werr1;
	u_int	tl6werr2;
	u_int	tl6werr3;
        u_int   spare2;         
        u_int   spare3;         
        u_int   spare4;
        u_int   spare5;
        u_int   spare6;
        u_int   spare7;
        u_int   spare8;
        u_int   spare9;
        u_int   spare10;
};


/*
 * pfms <chapter Ruby error log packets>.none ; fig. <part of x-1>
 *
 * Machine Check counters: and all other types...
 *
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                   Machine Check Error Counters                |
 * +---                        (96 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 *
 */

struct elr_error_counters {
	char error_counters[96];
};



/*
 * pfms <chapter Ruby error log packets>.2.3.1 ; fig.x-4
 *
 * <figure>(RUBY 630 MCHK Stack Frame\630_frame_def)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |R|                                             |  BYTE CNT     | :00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |         Sys$$offset= [010]    |     Proc$$offset= [-1]        |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           BIU_STAT                            | 
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           BIU_ADDR                            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           BIU_CTL                             | 
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                         Fill_Syndrome                         |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                          Fill_ADDR                            | 
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           BC_TAG                              |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * 
 */

struct elr_lep_630_frame {
	char 	byte_cnt;
	char 	rsvd1[6];
	char	retry; /* retry is really the high order bit of this */
			/* field */ 
	int	proc_off;
	int	sys_off;
	long	biu_stat;
	long	biu_addr;
	long	biu_ctl;
        long    fill_syndrome;
        long    fill_addr;
        long    va;
        long    bc_tag;
};


/* EV5 Turbolaser 630/620 Correctable Error Logout Frame 
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
 * |         reserved              |   rsvd|MISCR  |  rsvd|WHAMI   |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |             TLBER             |             TLDEV             |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |             TLESR1            |             TLESR0            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |             TLSER3            |             TLSER2            |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */

/*  Tlaser 630/620 correctable logout frame. This is used when the
 *        errorlog packet is built in tlaser_log_error()  in 
 *        ./arch/alpha/hal/kn8ae.c.c and is a piece of the Correctable
 *        errorlog packet
 */

struct elr_tlep_corr_frame {

/* Common area */
        int     frame_size;  /* bits <31:0> of first quadword */            
        int     retry;       /* bit 63 of first quadword - retry */ 
                             /* bit 62 of first quadword - second_error bit */
     /* the next two are offsets to the PAL */
        int     proc_off;       
        int     sys_off;        
        long    frame_reason;   
/* CPU specific area */
        long    ei_stat;    
        long    ei_addr;    
        long    fil_syn;    
        long    isr;        
/* System specific area */
        long    rsvdheader; 
        int     tldev;      
        int     tlber;      
        int     tlesr0;     
        int     tlesr1;     
        int     tlesr2;     
        int     tlesr3;     
  };

/* EV6 Turbolaser 630/620 Correctable Error Logout Frame 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |R|S|                           |       Frame Size              | :00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |      System area offset       |    CPU area offset            | :08
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |        MCHK Frame Rev         |      MCHK Code                | :10
 * |-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           I_STAT                              | :18
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           DC_STAT                             | :20
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           C_ADDR                              | :28
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           DC1_SYNDROME                        | :30
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           DC0_SYNDROME                        | :38
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           C_STAT                              | :40
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           C_STS                               | :48
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                           RESERVED                            | :50
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |         reserved              |   rsvd|MISCR  |  rsvd|WHAMI   | :58
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |             TLBER             |             TLDEV             | :60
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |             TLESR1            |             TLESR0            | :68
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |             TLSER3            |             TLSER2            | :70
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 */

/*  Tlaser 630/620 correctable logout frame. This is used when the
 *        errorlog packet is built in tlaser_log_error()  in 
 *        ./arch/alpha/hal/kn8ae.c.c and is a piece of the Correctable
 *        errorlog packet
 */

struct elr_tlep6_corr_frame {

/* Common area */
        int     frame_size;  /* bits <31:0> of first quadword */            
        int     retry;       /* bit 63 of first quadword - retry */ 
                             /* bit 62 of first quadword - second_error bit */
     /* the next two are offsets to the PAL */
        int     proc_off;       
        int     sys_off;        
	long	frame_reason;		/* MCHK Frame Rev / MCHK Code */
/* CPU specific area */
        long    i_stat;    
        long    dc_stat;    
        long    c_addr;    
        long    dc1_syndrome;        
        long    dc0_syndrome;        
        long    c_stat;    
        long    c_sts;    
	long	mm_stat;
/* System specific area */
        long    rsvdheader; 
        int     tldev;      
        int     tlber;      
        int     tlesr0;     
        int     tlesr1;     
        int     tlesr2;     
        int     tlesr3;     
	int	tl_rsvd0;
	int	tl_rsvd1;
	int	tl_rsvd2;
	int	tl_rsvd3;
	int	tl_rsvd4;
	int	tl_rsvd5;
};


/* MAB - Subpackets for the various errorlogs -
 *      TODO: adding new EISA subpackets for Turbolaser
 */

/*
 * pfms <chapter Ruby error log packets>.2.7 ; fig. x-8
 *
 * <figure>(CRD Footprint Block\crdef)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |     TYPE      |     FRU_ID    |       ECC Syndrome Code       | :00
 * +---------------+---------------+-------------------------------+
 * |    Highest Detected Address   |    Lowest Detected Address    | :08
 * +---------------+---------------+-------------------------------+
 * |             FLAGS             |           CRD_COUNT           | :10
 * +-------------------------------+-------------------------------+
 * |             MERB              |           MERA	           | :18
 * +-------------------------------+-------------------------------+
 * |             FADR              |           AMR	           | :20
 * +-------------------------------+-------------------------------+
 * 
 * 
 */

/* 'crd_mem_type' defines the fields in 'elr_crd_footprint.type'. */
struct crd_mem_type { 
	short dram_type:1;
	short strings:2;
	short bb_ram:1;
};

struct crd_flags {
	int valid:1;
	int scrubbed:1;
};

struct elr_crd_footprint {
	int	ecc_syndrome;
	short	fru_id;
	struct	crd_mem_type	type;
	int	low_addr;
	int	high_addr;
	int	crd_count;
	int	flags;
	int	mera;
	int	merb;
	int	amr;
	int	fadr;
};



/*
 * pfms <chapter Ruby error log packets>.2.9 ; fig. x-10
 *
 * <figure>(LMA Sub-packet Format\lma_sub)
 * <figure_attributes>(keep)
 * <comment><include>(LMA_SUBPACKET.SDML)
 * <endcomment>
 * <Line_art>(keep)
 * 
 * 
 * 63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |          Physical Address of Memory Controller                | :00
 * +-------+-------+---------------+---------------+---------------+
 * |                        VALID BITS                             | :08
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_LBER               |           LMA_LDEV            | :10
 * +-------+-------+---------------+---------------+---------------+ 
 * |        LMA_SPARE0             |           LMA_LCNR            | :18
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_LBESR1             |           LMA_LBESR0          | :20
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_LBESR3             |           LMA_LBESR2          | :28
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_LBECR1             |           LMA_LBECR0          | :30
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_AMR                |           LMA_MCR             | :38
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_MERA               |           LMA_FADR            | :40
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_MERB               |           LMA_MSYNDA          | :48
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_SPARE1             |           LMA_MSYNDB          | :50
 * +-------+-------+---------------+---------------+---------------+
 * 
 */

struct elr_lma_sub {
	long	lma_addr;
	long	valid_bit_mask;
	int	lma_ldev;
	int	lma_lber;
	int	lma_lcnr;
	int	lma_spare0;
	int	lma_lbesr0;
	int	lma_lbesr1;
	int	lma_lbesr2;
	int	lma_lbesr3;
	int	lma_lbecr0;
	int	lma_lbecr1;	
	int	lma_mcr;
	int	lma_amr;
	int	lma_fadr;
	int	lma_mera;
	int	lma_msynda;
	int	lma_merb;
	int	lma_msyndb;
	int	lma_spare1;
};


/* Turbolaser TMEM subpacket */

struct elr_tmem_subp {
        long    tmem_addr;
        long    valid_bit_mask;
        int     tmem_ldev;
        int     tmem_lber;
        int     tmem_lcnr;
        int     tmem_tlvid;
        int     tlfadr0;
        int     tlfadr1;
        int     tlesr0;
        int     tlesr1;
        int     tlesr2;
        int     tlesr3;
        int     mir;
        int     mcr;
        int     mer;
        int     mdra;
        int     ddr0;
        int     ddr1;
        int     ddr2;
        int     ddr3;
      };

/*
 * pfms <chapter Ruby error log packets>.2.10.1 ; fig. x-none
 *
 * <figure>(LSB CPU Required Registers Format\cpu_req)
 * <line_art>
 * 
 * 
 * 63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                      Physical Address of LEP                  | :00
 * +-------+-------+---------------+---------------+---------------+
 * |                        VALID BITS                             | :08
 * +-------+-------+---------------+---------------+---------------+
 * |            LEP_LBER           |           LEP_LDEV            | :10
 * +-------+-------+---------------+---------------+---------------+ 
 * |            LEP_LMERR          |           LEP_LCNR            | :18
 * +-------+-------+---------------+---------------+---------------+
 * |            LEP_LBESR1         |           LEP_LBESR0          | :20
 * +-------+-------+---------------+---------------+---------------+
 * |            LEP_LBESR3         |           LEP_LBESR2          | :28
 * +-------+-------+---------------+---------------+---------------+
 * |            LEP_LBECR1         |           LEP_LBECR0          | :30
 * +-------+-------+---------------+---------------+---------------+
 * 
 */

struct elr_cpu_req {
	long	lep_addr;
	long	valid_bit_mask;
	int	lep_ldev;
	int	lep_lber;
	int	lep_lcnr;
	int	lep_spare0;
	int	lep_lbesr0;
	int	lep_lbesr1;
	int	lep_lbesr2;
	int	lep_lbesr3;
	int	lep_lbecr0;
	int	lep_lbecr1;
};



/* EV5 Turbolaser TLEP subpacket */

struct elr_tlep_subp {
        long    tlep_addr;
        long    valid_bit_mask;
        int     tlep_ldev;
        int     tlep_lber;
        int     tlep_lcnr;
        int     tlep_tlvid;
        int     tlesr0;
        int     tlesr1;
        int     tlesr2;
        int     tlesr3;
	int	tlepaerr;
	int	tlmodconfig;
	int	tlepmerr;
	int	tlepderr;
        int     tlepintmask0;
        int     tlintrsum0;
        int     tlepintmask1;
        int     tlintrsum1;
        int     tlep_vmg;
        int     rsvd0;
        int     rsvd1;
        int     rsvd2;
};

/* EV6 Turbolaser TLEP subpacket */

struct elr_tlep6_subp {
        long    tlep_addr;
        long    valid_bit_mask;
        int     tlep_ldev;
        int     tlep_lber;
        int     tlep_lcnr;
        int     tlep_tlvid;
        int     tlesr0;
        int     tlesr1;
        int     tlesr2;
        int     tlesr3;
	int	tlmodconfig0;
	int	tlmodconfig1;
	int	tltccerr;
	int	tltdierr;
        int     tlepintmask0;
        int     tlintrsum0;
        int     tlepintmask1;
        int     tlintrsum1;
        int     tlep_vmg;
	int	tl6werr0;
	int	tl6werr1;
	int	tl6werr2;
	int	tl6werr3;
        int     rsvd0;
        int     rsvd1;
        int     rsvd2;
        int     rsvd3;
        int     rsvd4;
        int     rsvd5;
        int     rsvd6;
};

/*
 * pfms <chapter Ruby error log packets>.2.10.2 ; fig. x-none
 *
 * <figure>(LSB LMA Required Registers Format\lma_req)
 * <line_Art>
 * 
 * 
 * 63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                      Physical Address of LMA                  | :00
 * +-------+-------+---------------+---------------+---------------+
 * |                        VALID BITS                             | :08
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_LBER               |           LMA_LDEV            | :10
 * +-------+-------+---------------+---------------+---------------+ 
 * |        LMA_SPARE0             |           LMA_LCNR            | :18
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_LBESR1             |           LMA_LBESR0          | :20
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_LBESR3             |           LMA_LBESR2          | :28
 * +-------+-------+---------------+---------------+---------------+
 * |        LMA_LBECR1             |           LMA_LBECR0          | :30
 * +-------+-------+---------------+---------------+---------------+
 * 
 */

struct elr_lma_req {
	long	lma_addr;
	long	valid_bit_mask;
	int	lma_ldev;
	int	lma_lber;
	int	lma_lcnr;
	int	lma_spare0;
	int	lma_lbesr0;
	int	lma_lbesr1;
	int	lma_lbesr2;
	int	lma_lbesr3;
	int	lma_lbecr0;
	int	lma_lbecr1;	
};



/*
 * pfms <chapter Ruby error log packets>.2.10.3 ; fig. x-none
 *
 * <figure>(LSB IOP Required Registers Format\iop_req)
 * <line_art>
 * 
 * 
 * 63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                    Physical Address of IOP                    | :00
 * +-------+-------+---------------+---------------+---------------+
 * |                        VALID BITS                             | :08
 * +-------+-------+---------------+---------------+---------------+
 * |            IOP_LBER           |           IOP_LDEV            | :10
 * +-------+-------+---------------+---------------+---------------+ 
 * |            SPARE0             |           IOP_LCNR            | :18
 * +-------+-------+---------------+---------------+---------------+
 * |            IOP_LBESR1         |           IOP_LBESR0          | :20
 * +-------+-------+---------------+---------------+---------------+
 * |            IOP_LBESR3         |           IOP_LBESR2          | :28
 * +-------+-------+---------------+---------------+---------------+
 * |            IOP_LBECR1         |           IOP_LBECR0          | :30
 * +-------+-------+---------------+---------------+---------------+
 * 
 */

struct elr_iop_req {
	long	iop_addr;
	long	valid_bit_mask;
	int	iop_ldev;
	int	iop_lber;
	int	iop_lcnr;
	int	iop_spare0;
	int	iop_lbesr0;
	int	iop_lbesr1;
	int	iop_lbesr2;
	int	iop_lbesr3;
	int	iop_lbecr0;
	int	iop_lbecr1;
};


/* Turbolaser TIOP subpacket */

struct elr_tiop_subp {
        long    tiop_addr;
        long    valid_bit_mask;
        int     tiop_tldev;
        int     tiop_tlber;
        int     tiop_tlcnr;
        int     spare0;
        int     tiop_tlmmr0;
        int     tiop_tlmmr1;
        int     tiop_tlmmr2;
        int     tiop_tlmmr3;
        int     tiop_tlmmr4;
        int     tiop_tlmmr5;
        int     tiop_tlmmr6;
        int     tiop_tlmmr7;
        int     tiop_tlfadr0;
        int     tiop_tlfadr1;
        int     tiop_tlesr0;
        int     tiop_tlesr1;
        int     tiop_tlesr2;
        int     tiop_tlesr3;
        int     tiop_tlcpumask;
        int     tiop_iccmsr;
        int     tiop_iccnse;
        int     tiop_iccmtr;
        int     tiop_idpnse0;
        int     tiop_idpnse1;
        int     tiop_idpnse2;
        int     tiop_idpnse3;
        int     tiop_idpvr;
        int     tiop_iccwtr;
        long    tiop_tlmbpr;
        int     tiop_idpdr0;
        int     tiop_idpdr1;
        int     tiop_idpdr2;
        int     tiop_idpdr3;
      };






/*
 * pfms <chapter Ruby error log packets>.2.none ; fig. x-none
 *
 * <figure>(LSB xxx Required Registers Format\cpu_req)
 * <line_art>
 * A generic interpretation of the LSB registers collected from any
 * LSB module. They all (CPU/LMA/IOP) seem to be the same.
 * 
 * 63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                      Physical Address of LSB Node             | :00
 * +-------+-------+---------------+---------------+---------------+
 * |                        VALID BITS                             | :08
 * +-------+-------+---------------+---------------+---------------+
 * |            LSB_LBER           |           LSB_LDEV            | :10
 * +-------+-------+---------------+---------------+---------------+ 
 * |            LSB_LMERR          |           LSB_LCNR            | :18
 * +-------+-------+---------------+---------------+---------------+
 * |            LSB_LBESR1         |           LSB_LBESR0          | :20
 * +-------+-------+---------------+---------------+---------------+
 * |            LSB_LBESR3         |           LSB_LBESR2          | :28
 * +-------+-------+---------------+---------------+---------------+
 * |            LSB_LBECR1         |           LSB_LBECR0          | :30
 * +-------+-------+---------------+---------------+---------------+
 * 
 */

struct elr_lsb_req {
	long	lsb_addr;
	long	valid_bit_mask;
	int	lsb_ldev;
	int	lsb_lber;
	int	lsb_lcnr;
	int	lsb_spare0;
	int	lsb_lbesr0;
	int	lsb_lbesr1;
	int	lsb_lbesr2;
	int	lsb_lbesr3;
	int	lsb_lbecr0;
	int	lsb_lbecr1;
};



/*
 * pfms <chapter Ruby error log packets>.2.10 ; fig. x-11
 *
 * <figure>(LSB Subpacket Format\LSBsnap_def)
 * <figure_attributes>(keep)
 * <Line_art>(keep)
 * 
 * 63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |          Nodes Present        |       Snapshot Size           | :00
 * +-------+-------+---------------+---------------+---------------+
 * |                       Physicial Address                       |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | 
 * +                    LSB Required Registers                     +
 * |                                                               | 
 * +                                                               +
 * |                                                               | 
 * +-------+-------+---------------+---------------+---------------+
 * 
 */

struct elr_lsbsnap {
	int	snapshot_size;
	int	nodes_present;
	long	phys_addr;
	struct elr_lsb_req lsb_req[1]; /* The actual number of */
				       /* elements in this array is */
				       /* equal to the number of bits */
				       /* set in the nodes present */
				       /* field */
};



/* Turbolaser TLSB snapshot header*/

struct elr_tlsbsnap_hdr {
        int     snapshot_size;
        int     nodes_present;
        long    phys_addr;
};


/*
 * pfms <chapter Ruby error log packets>.3.2 ; fig. x-14
 *
 * <figure>(RUBY DLIST Format\dldef)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 *   *  31                           00
 * +-------+-------+-------+-------+
 * |        SUBPACKET_SIZE         | :00
 * +-------+-------+-------+-------+
 * |  ID   |   0   | DISABLE_MASK  | :04
 * +-------+-------+---------------+
 * /      nn DLIST_LONGWORDS       / 
 * +-------------------------------+
 * 
 */

struct elr_dec7000_dlist {
	int subpacket_size;
	struct dlist_lw
		dlist_lw[1];	/* use size field to determine */
					/* actual length of */
					/* dlist_longwords */
};



/*
 * <figure>(XMI Channel Subpacket Format\xmihosedef)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 * +-------------------------------+-------------------------------+
 * |        Valid Bits             |          Chan No.             |
 * +-------------------------------+-------------------------------+
 * |         XBER                  |          XDEV                 |
 * +-------------------------------+-------------------------------+
 * |         XFAER                 |          XFADR                |
 * +-------------------------------+-------------------------------+
 * |         IMSK                  |          LDIAG                |
 * +-------------------------------+-------------------------------+
 * |         LGPR                  |          LEVR                 |
 * +-------------------------------+-------------------------------+
 * |         IPR2                  |          IPR1                 |
 * +-------------------------------+-------------------------------+
 * |         SPARE                 |          IIPR                 |
 * +-------------------------------+-------------------------------+
 * 
 * <endline_art>
 * 
 */
struct elr_xmi_channel_subp {
	int channel;
	int valid;
	int xdev;
	int xber;
	int xfadr;
	int xfaer;
	int ldiag;
	int imsk;
	int levr;
	int lerr;
	int lgpr;
	int ipr1;
	int ipr2;
	int iipr;
};



/* FLAG adaptor subpacket */

struct elr_fbus_channel_subp {
        int channel;
        int valid;
        int FINT;
        int NID;
        int STO;
        int ERRHI;
        int ERRLO;
        int FADRHI;
        int FADRLO;
        int TTO;
        int BZRTRY;
        int FCTL;
        int FERR;
        int spare;
};



/* PCIA adaptor subpacket */

struct elr_pci_channel_subp {
        int channel;
        int valid_pci0;
        int valid_pci1;
        int valid_pci2;
        int pcia_slot;
        int spare;
        u_int ctl0; 
        u_int mretry0;
        u_int err0;
        u_int fadr0;
        u_int imask0;
        u_int diag0;
        u_int ipend0;
        u_int iprog0;
        u_int wmask_a0;
        u_int wbase_a0;
        u_int tbase_a0;
        u_int wmask_b0;
        u_int wbase_b0;
        u_int tbase_b0;
        u_int wmask_c0;
        u_int wbase_c0;
        u_int tbase_c0;
        u_int errvec0;
        u_int devvec0_slot0_inta;
        u_int devvec0_slot0_intb;
        u_int devvec0_slot0_intc;
        u_int devvec0_slot0_intd;
        u_int devvec0_slot1_inta;
        u_int devvec0_slot1_intb;
        u_int devvec0_slot1_intc;
        u_int devvec0_slot1_intd;
        u_int devvec0_slot2_inta;
        u_int devvec0_slot2_intb;
        u_int devvec0_slot2_intc;
        u_int devvec0_slot2_intd;
        u_int devvec0_slot3_inta;
        u_int devvec0_slot3_intb;
        u_int devvec0_slot3_intc;
        u_int devvec0_slot3_intd;
        u_int ctl1; 
        u_int mretry1;
        u_int err1;
        u_int fadr1;
        u_int imask1;
        u_int diag1;
        u_int ipend1;
        u_int iprog1;
        u_int wmask_a1;
        u_int wbase_a1;
        u_int tbase_a1;
        u_int wmask_b1;
        u_int wbase_b1;
        u_int tbase_b1;
        u_int wmask_c1;
        u_int wbase_c1;
        u_int tbase_c1;
        u_int errvec1;
        u_int devvec1_slot0_inta;
        u_int devvec1_slot0_intb;
        u_int devvec1_slot0_intc;
        u_int devvec1_slot0_intd;
        u_int devvec1_slot1_inta;
        u_int devvec1_slot1_intb;
        u_int devvec1_slot1_intc;
        u_int devvec1_slot1_intd;
        u_int devvec1_slot2_inta;
        u_int devvec1_slot2_intb;
        u_int devvec1_slot2_intc;
        u_int devvec1_slot2_intd;
        u_int devvec1_slot3_inta;
        u_int devvec1_slot3_intb;
        u_int devvec1_slot3_intc;
        u_int devvec1_slot3_intd;
        u_int ctl2; 
        u_int mretry2;
        u_int err2;
        u_int fadr2;
        u_int imask2;
        u_int diag2;
        u_int ipend2;
        u_int iprog2;
        u_int wmask_a2;
        u_int wbase_a2;
        u_int tbase_a2;
        u_int wmask_b2;
        u_int wbase_b2;
        u_int tbase_b2;
        u_int wmask_c2;
        u_int wbase_c2;
        u_int tbase_c2;
        u_int errvec2;
        u_int devvec2_slot0_inta;
        u_int devvec2_slot0_intb;
        u_int devvec2_slot0_intc;
        u_int devvec2_slot0_intd;
        u_int devvec2_slot1_inta;
        u_int devvec2_slot1_intb;
        u_int devvec2_slot1_intc;
        u_int devvec2_slot1_intd;
        u_int devvec2_slot2_inta;
        u_int devvec2_slot2_intb;
        u_int devvec2_slot2_intc;
        u_int devvec2_slot2_intd;
        u_int devvec2_slot3_inta;
        u_int devvec2_slot3_intb;
        u_int devvec2_slot3_intc;
        u_int devvec2_slot3_intd;
      };




/*
 * <figure>(IOP Adapter Subpacket\iop_sub)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                 LSB Physical Address of IOP                   | :00 
 * +---------------------------------------------------------------+
 * |                          Valid Bits                           |
 * +---------------------------------------------------------------+
 * |            IOP_LBER           |          IOP_LDEV             |
 * +-------------------------------+-------------------------------+
 * |             SPARE0            |          IOP_LCNR             | 
 * +---------------------------------------------------------------+  
 * |            IOP_LBESR1         |          IOP_LBESR0           |
 * +---------------------------------------------------------------+  
 * |            IOP_LBESR3         |          IOP_LBESR2           |
 * +---------------------------------------------------------------+  
 * |            IOP_LBECR1         |          IOP_LBECR0           |
 * +---------------------------------------------------------------+  
 * |            IOP_IPCVR          |          IOP_IPCNSE           |
 * +---------------------------------------------------------------+  
 * |            IOP_IPCHST         |          IOP_IPCMSR           |
 * +---------------------------------------------------------------+  
 * <endline_art>
 * 
 */
struct elr_iop_adp_subp {
	long iop_addr;
	long valid;
	int	iop_ldev;
	int	iop_lber;
	int	iop_lcnr;
	int	iop_spare0;
	int	iop_lbesr0;
	int	iop_lbesr1;
	int	iop_lbesr2;
	int	iop_lbesr3;
	int	iop_lbecr0;
	int	iop_lbecr1;
	int     iop_ipcnse;
	int     iop_ipcvr;
	int     iop_ipcmsr;
	int     iop_ipchst;
};



/*
 * <figure>(XMI Subpacket Format)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |        Channel No.            |            SIZE               | :00 
 * +---------------------------------------------------------------+
 * | XFAER VALID   |  XFADR VALID  |  XBE VALID    |  XDEV VALID   |
 * +-------------------------------+-------------------------------+
 * |                                               |  Node Present |
 * +                                               +---------------+
 * |                     XMI snapshot registers                    |
 * +                                                               +
 * |                                                               |
 * +-------------------------------+-------------------------------+
 * 
 * <endline_art>
 */

struct elr_xmi_subpacket {
        /* Since this packet is not 32 bit alligned, make all fields
        ** short type to avoid compiler adding pad bytes
        */
        short size;
        short pad1;
        short channel;
        short pad2;
        short xdev_valid;
        short xbe_valid;
        short xfadr_valid;
        short xfaer_valid;
        short node_present;
        short xmi_registers[8*14];    /* 8 16bit short int per a maximum */
                                      /* of 14 nodes */
};


/*
 * Ruby-Specific Machine Check Logout data. As defined in the PFMS 
 * the Ruby Machine Check error log packet is constructed of a number 
 * of possible compenents
 *
 * Several of these components are required. Error log header, which 
 * is provided by the EALLOC request, is required. 
 *
 * Also a Software flags structure is required. This structure 
 * describes what compontents exist in the rest of the error log 
 * packet.
 *
 * A common LEP Header, LEP Machine Check Frame and Machine Check
 * Error Counters make up the rest of the required portion of this packet.
 *
 * Addition subpackets can be further appended to this packet
 * depending on the cause of the machine check. Please see the Ruby
 * PFMS for more details on the error log packet structures defined
 * herein. 
 */

/*
 * <the following comments are taken from the PFMS to make cross
 *  reference easy> 
 *
 * pfms <chapter Ruby error log packets>.2.1 ; fig. x-1
 *
 * Machine Check entry type EMB$C_MC:
 * Machine check error log packet appearance:
 *
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                        ERRORLOG HEADER                        /
 * +---                        (## bytes)                       ---+
 * |                                                               | :##
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                     Software Error Flags                      |
 * +---                        (24 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                    Common LEP Header Area                     /
 * +---                        (64 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                     LEP Machine Check Frame                   /
 * +---                        (456 bytes)                      ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                       PAL code Revision                       |
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                   Machine Check Error Counters                |
 * +---                        (96 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * 
 */

struct elr_pal_rev {
	long pal_revision;
      };

struct el_dec7000_mcheck_data {
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	struct elr_soft_flags soft_flags;
	struct elr_lep_common_header common_header;
	struct elr_lep_mchk_frame mchk_frame;
	struct elr_pal_rev pal_revision;
	struct elr_error_counters mcheck_counters;
	/* There may be sub-packets appended to this data block, as */
	/* indicated by 'present' bits in the elr_soft_flags. when a */
	/* sub-packet exists, it appears inorder, as follows: */
	/*    DLIST; LSB; LMA; Log adapter, presently only IOP */
};



/*
 * pfms <chapter Ruby error log packets>.2.3 ; fig.x-3
 *
 * <figure>(RUBY 630 Entry Format\630_def)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                        ERRORLOG HEADER                        /
 * +---                        (## bytes)                       ---+
 * |                                                               | :##
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                     Software Error Flags                      |
 * +---                        (24 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                    Common LEP Header Area                     /
 * +---                        (64 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                     630 MCHK Stack Frame                      /
 * +---                        (64 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                       PAL code Revision                       |
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                       630 Error Counters                      |
 * +---                        (96 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * 
 */

struct el_dec7000_630_data 
{
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	struct elr_soft_flags soft_flags;
	struct elr_lep_common_header common_header;
	struct elr_lep_630_frame lep_630_frame;
	long pal_revision;
	struct	elr_error_counters lep_630_cntrs;
	/* There may be sub-packets appended to this data block, as */
	/* indicated by 'present' bits in the elr_soft_flags. when a */
	/* sub-packet exists, it appears inorder, as follows: */
	/*    DLIST; LSB; LMA */
};



/*
 * pfms <chapter Ruby error log packets>.2.4 ; fig.x-5
 *
 * <head2>(RUBY 660 Entry Format)
 * <figure>(RUBY 660 Entry\660_def)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                        ERRORLOG HEADER                        /
 * +---                        (## bytes)                       ---+
 * |                                                               | :##
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                     Software Error Flags                      |
 * +---                        (24 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                    Common LEP Header Area                     /
 * +---                        (64 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                     LEP Machine Check Frame                   /
 * +---                        (456 bytes)                      ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                       PAL code Revision                       |
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                         660 Error Counters                    |
 * +---                        (96 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * 
 */

struct el_dec7000_660_data {
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	struct elr_soft_flags soft_flags;
	struct elr_lep_common_header common_header;
	struct elr_lep_mchk_frame mchk_frame;
	long pal_revision;
	struct elr_error_counters counters;
	/* There may be sub-packets appended to this data block, as */
	/* indicated by 'present' bits in the elr_soft_flags. when a */
	/* sub-packet exists, it appears inorder, as follows: */
	/*    DLIST; LSB; LMA; Log adapter, presently only IOP */
};



/*
 * pfms <chapter Ruby error log packets>.2.6 ; fig.x-7
 *
 * <figure>(LASER Soft Error Entry Type SE\sedef)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                        ERRORLOG HEADER                        /
 * +---                        (## bytes)                       ---+
 * |                                                               | :##
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |   CRD Footprint Buffer Size   |        PACKET_REVISION        | :00
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                     CRD FOOTPRINT PACKETS                     / 
 * +---                        (nn bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * 
 */

struct el_soft_error_data {
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	int	packet_revision;
	int	crd_buf_size;
	struct elr_crd_footprint crd_footprints[1];
};

#define CRD_DATA_SIZE (sizeof(struct el_soft_error_data) \
	+ (15*(sizeof(struct elr_crd_footprint))))



/*
 * pfms <chapter Ruby error log packets>.2.8 ; fig. x-9
 *
 * <figure>(LASER MEMSCAN Entry Type MEMSCAN\msdef)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                        ERRORLOG HEADER                        /
 * +---                        (## bytes)                       ---+
 * |                                                               | :##
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |    CTL CNT    |      FLAGS    |        PACKET_REVISION        | :00
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +                                                            ---+
 * /                        LMA SUB-PACKETS                        / 
 * +---                        (nn bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * 
 */

struct el_memscan_data {
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	int	packet_revision;
	short	flags;
	short	ctl_cnt;
	struct 	elr_lma_sub lma_sub[1];	/* The actual number of */
					/* elements in this array is */
					/* indicated by ctl_cnt */
};



/*
 * <figure>(Power System Packet Format\pwr_def)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                        ERRORLOG HEADER                        /
 * +---                        (## bytes)                       ---+
 * |                                                               | :##
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |								   |
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * /                        Convertor Data                         /
 * |                                                               |
 * +---------------------------------------------------------------+
 * 
 * <endline_art>
 */

#define PS_ST_STATE_CHANGE_PACKET	1
#define PS_ST_HISTORY_PACKET		2
#define PS_ST_BADCHKSUM_NO_ANS_PACKET	3
#define PS_ST_GBUS_REG_EVENT_PACKET	4

#define PS_HIST_DATA_SIZE		56
#define PS_MAX_REGULATORS		9

struct el_laser_ps_data {

	int	reg_summary;
	char	reg_version[8];
	int	record_subtype;
	char 	reg_data[PS_MAX_REGULATORS*PS_HIST_DATA_SIZE];
};



/*
 * <figure>(LAMB Adapter Format\lambdef)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 * 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                        ERRORLOG HEADER                        /
 * +---                        (## bytes)                       ---+
 * |                                                               | :##
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               |
 * +                                                               +
 * |                          S/W FLAGS                            |
 * +                                                               +
 * |                                                               |
 * +-------------------------------+-------------------------------+
 * |        Valid Bits             |          Chan No.             |
 * +-------------------------------+-------------------------------+
 * |         XBER                  |          XDEV                 |
 * +-------------------------------+-------------------------------+
 * |         XFAER                 |          XFADR                |
 * +-------------------------------+-------------------------------+
 * |         LERR                  |          LDIAG                |
 * +-------------------------------+-------------------------------+
 * |         LEVR                  |          IMSK                 |
 * +-------------------------------+-------------------------------+
 * |         IPR2                  |          IPR1                 |
 * +-------------------------------+-------------------------------+
 * |         SPARE                 |          IIPR                 |
 * +-------------------------------+-------------------------------+
 * |                                                               |
 * /                     96 Bytes of Counters                      /
 * |                                                               |
 * +-------------------------------+-------------------------------+
 * Possible Subpacket:
 *        - XMI
 * <endline_art>
 */

struct el_laser_lamb_data {
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	struct elr_soft_flags soft_flags;
	int lamb_chan;
	int lamb_valid;
	int lamb_xdev;
	int lamb_xber;
	int lamb_xfadr;
	int lamb_xfaer;
	int lamb_ldiag;
	int lamb_imsk;
	int lamb_levr;
	int lamb_lerr;
	int lamb_lgpr;
	int lamb_ipr1;
	int lamb_ipr2;
	int lamb_iipr;
	struct elr_error_counters count;
	/* There may be sub-packets appended to this data block, as */
	/* indicated by 'present' bits in the elr_soft_flags. when a */
	/* sub-packet exists, it appears inorder, as follows: */
	/*    XMI */
};



struct el_tlaser_lamb_data {
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	struct elr_soft_flags soft_flags;
        long iop_phys_addr;
	int lamb_chan;
	int lamb_valid;
	int lamb_xdev;
	int lamb_xber;
	int lamb_xfadr;
	int lamb_xfaer;
	int lamb_ldiag;
	int lamb_imsk;
	int lamb_levr;
	int lamb_lerr;
	int lamb_lgpr;
	int lamb_ipr1;
	int lamb_ipr2;
	int lamb_iipr;
	/* There may be sub-packets appended to this data block, as */
	/* indicated by 'present' bits in the elr_soft_flags. when a */
	/* sub-packet exists, it appears inorder, as follows: */
	/*    XMI */
};



/*
 * <figure>(I/O Adapter Errorlog Entry Type\iodef)
 * <figure_attributes>(keep)
 * <Line_art>(keep)
 * 
 * 
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00 
 * +--                                                           --+
 * |                                                               |  
 * /--                                                           --/
 * |                        Errorlog Header                        | 
 * +--                                                           --+
 * |                                                               | :##
 * +===============+===============+===============+===============+ 
 * |                                                               | :00
 * +--                                                           --+
 * |                        S/W FLAGS                              | 
 * +--                                                           --+
 * |                                                               | :##
 * +===============+===============+===============+===============+ 
 * |                                                               | :00
 * +--                                                           --+
 * |                                                               |
 * /--                   IOP Adapter Subpacket                   --/
 * |                                                               |
 * +--                                                           --+
 * |                                                               | :TBD
 * +===============+===============+===============+===============+
 * |                                                               |
 * /                      96 BYTES of Counters                     /
 * |                                                               |
 * +===============================================================+
 * Possible Subpacket:
 *          - Channel
 * <Endline_art>
 */
struct el_laser_iop_data {
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	struct elr_soft_flags soft_flags;
	struct elr_iop_adp_subp iop_adp_subp;
	struct elr_error_counters count;
	/* There may be sub-packets appended to this data block, as */
	/* indicated by 'present' bits in the elr_soft_flags. when a */
	/* sub-packet exists, it appears inorder, as follows: */
	/*    CHANNEL */
};

/* Configuration FRU table header  - created by console but the data is used
** for a Turbolaser configuration packet errorlog generated at boottime.
** We only need byte count field to determine size of the errorlog packet.
*/
struct fru_table {
 long checksum;
 int byte_count;
 int table_rev;
};


/* Turbolaser I/O adaptor errorlog */

struct el_tlaser_tiop_data {
        /*
         * The ERRORLOG HEADER is defined in errlog.h as:
         *
         *     struct el_rhdr elrhdr;
         *
         * it is not defined as part of the data contain with in an
         * error log packet.
         */
        struct elr_soft_flags soft_flags;
        struct elr_tiop_subp tiop_adp_subp;

        /* There may be sub-packets appended to this data block, as */
        /* indicated by 'present' bits in the elr_soft_flags. when a */
        /* sub-packet exists, it appears inorder, as follows: */
        /*    CHANNEL */
      };



/*
 * pfms <chapter Ruby error log packets>.2.3 ; fig.x-3
 *
 * <figure>(RUBY 630 Entry Format\630_def)
 * <figure_attributes>(keep)
 * <line_art>(keep)
 * 
 *  63                           32 31                           00
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                        ERRORLOG HEADER                        /
 * +---                        (## bytes)                       ---+
 * |                                                               | :##
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                     Software Error Flags                      |
 * +---                        (24 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                    Common LEP Header Area                     /
 * +---                        (64 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * /                     630 MCHK Stack Frame                      /
 * +---                        (64 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * |                       PAL code Revision                       |
 * +-------------------------------+-------------------------------+
 * |                                                               | :00
 * +---                                                         ---+
 * |                       630 Error Counters                      |
 * +---                        (96 bytes)                       ---+
 * |                                                               | :nn
 * +-------------------------------+-------------------------------+
 * 
 */

struct el_lep_630_data 
{
	/*
	 * The ERRORLOG HEADER is defined in errlog.h as:
	 *
	 *     struct el_rhdr elrhdr;
	 *
	 * it is not defined as part of the data contain with in an
	 * error log packet.
	 */
	struct elr_soft_flags soft_flags;
	struct elr_lep_common_header common_header;
	struct elr_lep_630_frame lep_630_frame;
	struct	elr_error_counters lep_630_cntrs;
};

struct el_common_logout_header {
	u_int	elfl_size;		/* size in bytes of logout area. */
	int	elfl_sbz1:31;		/* Should be zero. */
	char	elfl_retry:1;		/* Retry flag. */
        u_int	elfl_procoffset;	/* Processor-specific offset. */
	u_int	elfl_sysoffset;		/* Offset of system-specific. */
};

struct el_common_procdata_mcheck {
	u_long		elfmc_paltemp[32];	/* PAL TEMP REGS. */
	/* EV4-specific fields */
	vm_offset_t	elfmc_exc_addr;		/* Address of excepting instruction. */
	u_long		elfmc_exc_sum;		/* Summary of arithmetic traps. */
	u_long		elfmc_exc_mask;		/* Exception mask (from exc_sum). */
	u_long		elfmc_iccsr;		/* IBox hardware enables. */
	vm_offset_t	elfmc_pal_base;		/* Base address for PALcode. */
	u_long		elfmc_hier;		/* Hardware Interrupt Enable. */
	u_long		elfmc_hirr;		/* Hardware Interrupt Request. */
	u_long		elfmc_mm_csr;		/* D-stream fault info. */
	u_long		elfmc_dc_stat;		/* D-cache status (ECC/Parity Err). */
	u_long		elfmc_dc_addr;		/* EV3 Phys Addr for ECC/DPERR. */
	u_long		elfmc_abox_ctl;		/* ABox Control Register. */
	u_long		elfmc_biu_stat;		/* BIU Status. */
	vm_offset_t	elfmc_biu_addr;		/* BUI Address. */
	u_long		elfmc_biu_ctl;		/* BIU Control. */
	u_long		elfmc_fill_syndrome;	/* For correcting ECC errors. */
	vm_offset_t	elfmc_fill_addr;	/* Cache block which was being read. */
	vm_offset_t	elfmc_va;		/* Effective VA of fault or miss. */
	u_long		elfmc_bc_tag;		/* Backup Cache Tag Probe Results. */
};

/* 
 * Sable processor specific Machine Check Data segment.
 */

struct el_kn450_logout_header {
	u_int	elfl_size;		/* size in bytes of logout area. */
	int	elfl_sbz1:31;		/* Should be zero. */
	char	elfl_retry:1;		/* Retry flag. */
        u_int	elfl_procoffset;	/* Processor-specific offset. */
	u_int	elfl_sysoffset;		/* Offset of system-specific. */
	u_int	elfl_error_type;	/* PAL error type code. */
	u_int	elfl_frame_rev;		/* PAL Frame revision. */
};
struct el_kn450_procdata_mcheck {
	u_long		elfmc_paltemp[31];	/* PAL TEMP REGS. */
	vm_offset_t	elfmc_exc_addr;		/* Addr of excepting instuct */
	u_long		elfmc_exc_sum;		/* Summary of arith trap. */
	u_long		elfmc_exc_mask;		/* Except mask (exc_sum) */
	u_long		elfmc_iccsr;		/* IBox hardware enables. */
	vm_offset_t	elfmc_pal_base;		/* Base address for PALcode. */
	u_long		elfmc_hier;		/* Hardware Interrupt Enable */
	u_long		elfmc_hirr;		/* Hardware Interrupt Req */
	u_long		elfmc_mm_csr;		/* D-stream fault info. */
	u_long		elfmc_dc_stat;		/* D-cache (ECC/Parity Err) */
	u_long		elfmc_dc_addr;		/* Phys Addr for ECC/DPERR */
	u_long		elfmc_abox_ctl;		/* ABox Control Register */
	u_long		elfmc_biu_stat;		/* BIU Status */
	vm_offset_t	elfmc_biu_addr;		/* BUI Address */
	u_long		elfmc_biu_ctl;		/* BIU Control */
	u_long		elfmc_fill_syndrome;	/* For corr ECC errors */
	vm_offset_t	elfmc_fill_addr;	/* Cache block read. */
	vm_offset_t	elfmc_va;		/* Effect VA of fault */
	u_long		elfmc_bc_tag;		/* BCache Tag Probe Results */
};

struct el_kn450_sysdata_mcheck {
	u_long	    elcmc_bcc;	      /* CSR 0 */
	u_long	    elcmc_bcce;	      /* CSR 1 */
	u_long	    elcmc_bccea;      /* CSR 2 */
	u_long	    elcmc_bcue;	      /* CSR 3 */
	u_long	    elcmc_bcuea;      /* CSR 4 */
	u_long	    elcmc_dter;	      /* CSR 5 */
	u_long	    elcmc_cbctl;      /* CSR 6 */
	u_long	    elcmc_cbe;	      /* CSR 7 */
	u_long	    elcmc_cbeal;      /* CSR 8 */
	u_long	    elcmc_cbeah;      /* CSR 9 */
	u_long	    elcmc_pmbx;	      /* CSR 10 */
	u_long	    elcmc_ipir;	      /* CSR 11 */
	u_long	    elcmc_sic;	      /* CSR 12 */
	u_long	    elcmc_adlk;	      /* CSR 13 */
	u_long	    elcmc_madrl;      /* CSR 14 */
	u_long	    elcmc_crrev4;     /* CSR 15 */
};

/*
 * Sable memory error frame - sable pfms section 3.42
 */
struct el_kn450_data_memory {
       struct	el_cobra_frame_header elcm_hdr;	/* ID$MEM-FERR = 0x08 */
	u_int	elcm_module;	/* Module id. */
	u_int	elcm_res04;	/* Reserved. */
	u_long	elcm_merr;	/* CSR0: Error Reg 1. */
	u_long	elcm_mcmd1;	/* CSR1: Command Trap 1. */
	u_long	elcm_mcmd2;	/* CSR2: Command Trap 2. */
	u_long	elcm_mconf;	/* CSR3: Configuration. */
	u_long	elcm_medc1;	/* CSR4: EDC Status 1. */
	u_long	elcm_medc2;	/* CSR5: EDC Status 2. */
	u_long	elcm_medcc;	/* CSR6: EDC Control. */
	u_long	elcm_msctl;	/* CSR7: Stream Buffer Control. */
	u_long	elcm_mref;	/* CSR8: Refresh Control. */
	u_long  elcm_filter;	/* CSR9: CRD Filter Control. */
};


/*
 * Sable other cpu error frame - sable pfms section 3.43
 */
struct el_kn450_data_other_cpu {
	short	elco_cpuid;	/* CPU ID */
	short	elco_res02[3];	
	u_long	elco_bcc;	/* CSR 0 */
	u_long	elco_bcce;	/* CSR 1 */
	u_long	elco_bccea;	/* CSR 2 */
	u_long	elco_bcue;	/* CSR 3 */
	u_long	elco_bcuea;	/* CSR 4 */
	u_long	elco_dter;	/* CSR 5 */
	u_long	elco_cbctl;	/* CSR 6 */
	u_long	elco_cbe;	/* CSR 7 */
	u_long	elco_cbeal;	/* CSR 8 */
	u_long	elco_cbeah;	/* CSR 9 */
	u_long	elco_pmbx;	/* CSR 10 */
	u_long	elco_ipir;	/* CSR 11 */
	u_long	elco_sic;	/* CSR 12 */
	u_long	elco_adlk;	/* CSR 13 */
	u_long	elco_madrl;	/* CSR 14 */
	u_long	elco_crrev4;	/* CSR 15 */
};

/*
 * Sable other cpu error frame - sable pfms section 3.44
 */
struct el_kn450_data_t2{
        struct el_cobra_frame_header elct_hdr;	/* ID$T2-FRAME */
	u_long	elct_iocsr;	/* IO Control and Status Register */
	u_long	elct_cerr1;	/* Cbus Error Register 1 */
	u_long	elct_cerr2;	/* Cbus Error Register 2 */
	u_long	elct_cerr3;	/* Cbus Error Register 3 */
	u_long	elct_perr1;	/* PCI Error Register 1 */
	u_long	elct_perr2;	/* PCI Error Register 2 */
	u_long	elct_hae0_1;	/* High Address Extension Register 1 */
	u_long	elct_hae0_2;	/* High Address Extension Register 2 */
	u_long	elct_hbase;	/* High Base Register */
	u_long	elct_wbase1;	/* Window Base Register 1 */
	u_long	elct_wmask1;	/* Window Mask Register 1 */
	u_long	elct_tbase1;	/* Translated Base Register 1 */
	u_long	elct_wbase2;	/* Window Base Register 2 */
	u_long	elct_wmask2;	/* Window Mask Register 2 */
	u_long	elct_tbase2;	/* Translated Base Register 2 */
	u_long	elct_tdr0;	/* TLB Data Register 0 */
	u_long	elct_tdr1;	/* TLB Data Register 1 */
	u_long	elct_tdr2;	/* TLB Data Register 2 */
	u_long	elct_tdr3;	/* TLB Data Register 3 */
	u_long	elct_tdr4;	/* TLB Data Register 4 */
	u_long	elct_tdr5;	/* TLB Data Register 5 */
	u_long	elct_tdr6;	/* TLB Data Register 6 */
	u_long	elct_tdr7;	/* TLB Data Register 7 */
};

/*
 * Sable error log data structure - sable pfms section 3.40
 */
struct el_kn450_data_corrected {
	u_long	elcpb_biu_stat;
	u_long	elcpb_biu_addr;
	u_long	elcpb_biu_ctl;
	u_long	elcpb_fill_syndrome;
	u_long	elcpb_fill_addr;
	u_long	elcpb_bc_tag;
};

/* 
 * Sable error log data structure
 * Note there are 4 memory slots on sable (see kn450.h)
 */
struct el_kn450_frame_mcheck {
        struct el_cobra_frame_header elfmc_header;	/* ID$P-FRAME_MCHECK */
	struct el_kn450_logout_header elfmc_hdr;
	struct el_kn450_procdata_mcheck elfmc_procdata;
	struct el_kn450_sysdata_mcheck elfmc_sysdata;
	struct el_kn450_data_t2 elfmc_t2data;
	struct el_kn450_data_memory elfmc_memdata[4]; 
        struct el_cobra_frame_header elfmc_footer;	/* empty */
};


/* 
 * Sable error log data structures on memory errors
 */
struct el_kn450_frame_corrected {
        struct el_cobra_frame_header elfcc_header;	/* ID$P-BC-COR */
	struct el_kn450_logout_header elfcc_hdr;
	struct el_kn450_data_corrected elfcc_procdata; 
/*	struct el_kn450_data_t2 elfcc_t2data;		*/
/*	struct el_kn450_data_memory elfcc_memdata[4];	*/
        struct el_cobra_frame_header elfcc_footer;	/* empty */
};


/* Mustang */
struct el_common_lcadata_mcheck {
	u_long		elfmc_paltemp[32];	/* PAL TEMP REGS. */
	/* EV4-specific fields */
	vm_offset_t	elfmc_exc_addr;		/* Address of excepting instruction. */
	u_long		elfmc_exc_sum;		/* Summary of arithmetic traps. */
	u_long		elfmc_exc_mask;		/* Exception mask (from exc_sum). */
	u_long		elfmc_iccsr;		/* IBox hardware enables. */
	vm_offset_t	elfmc_pal_base;		/* Base address for PALcode. */
	u_long		elfmc_hier;		/* Hardware Interrupt Enable. */
	u_long		elfmc_hirr;		/* Hardware Interrupt Request. */
	u_long		elfmc_mm_csr;		/* D-stream fault info. */
	u_long		elfmc_dc_stat;		/* D-cache status (ECC/Parity Err). */
	u_long		elfmc_dc_addr;		/* EV3 Phys Addr for ECC/DPERR. */
	u_long		elfmc_abox_ctl;		/* ABox Control Register. */
	/* fields that are differnt from EV4 for LCA */
	u_long		elfmc_lca_esr;		
	vm_offset_t	elfmc_lca_ear;		
	u_long		elfmc_lca_car;		
	u_long		elfmc_lca_stat0;	
	vm_offset_t	elfmc_lca_stat1;	
	/* End different fields for lca */
	vm_offset_t	elfmc_va;		/* Effective VA of fault or miss. */
	u_long		elfmc_bc_tag;		/* Backup Cache Tag Probe Results. */
};

struct el_lca_sysdata_mcheck {
    u_long	err_code;			
};

struct el_lca_frame_mcheck {
	struct el_common_logout_header elfmc_hdr;
	struct el_common_lcadata_mcheck elfmc_procdata;
	struct el_lca_sysdata_mcheck elfmc_sysdata;
};

/* Avanti */

struct el_apecs_sysdata_mcheck {
    u_long	coma_gcr;			
    u_long	coma_edsr;			
    u_long	coma_ter;			
    u_long	coma_elar;			
    u_long	coma_ehar;			
    u_long	coma_ldlr;			
    u_long	coma_ldhr;			
    u_long	coma_base0;			
    u_long	coma_base1;			
    u_long	coma_base2;			
    u_long	coma_cnfg0;			
    u_long	coma_cnfg1;			
    u_long	coma_cnfg2;			
    u_long	epic_dcsr;			
    u_long	epic_pear;			
    u_long	epic_sear;			
    u_long	epic_tbr1;			
    u_long	epic_tbr2;			
    u_long	epic_pbr1;			
    u_long	epic_pbr2;			
    u_long	epic_pmr1;			
    u_long	epic_pmr2;			
    u_long	epic_harx1;			
    u_long	epic_harx2;			
    u_long	epic_pmlt;			
    u_long	epic_tag0;			
    u_long	epic_tag1;			
    u_long	epic_tag2;			
    u_long	epic_tag3;			
    u_long	epic_tag4;			
    u_long	epic_tag5;			
    u_long	epic_tag6;			
    u_long	epic_tag7;			
    u_long	epic_data0;			
    u_long	epic_data1;			
    u_long	epic_data2;			
    u_long	epic_data3;			
    u_long	epic_data4;			
    u_long	epic_data5;			
    u_long	epic_data6;			
    u_long	epic_data7;			
};

struct el_apecs_frame_mcheck {
	struct el_common_logout_header elfmc_hdr;
	struct el_common_procdata_mcheck elfmc_procdata;
	struct el_apecs_sysdata_mcheck elfmc_sysdata;
};
                                                                  

/*
 * KN20AA machine error logging support
 */

/* Uncorrectable Machine Check Error Codes as in EV5 PAL
 */
#define TAG_PARITY	0x080L		/* TAG parity Error 				*/
#define	TAG_CTRL	0x082L		/* Tag Control Parity Erros			*/
#define	HARD_ERR	0x084L		/* Generic Hard Error				*/
#define	CPU_DETECTED	0x088L		/* Processor Detected uncorrectable ECC error	*/
#define	OS_BUG_CHK	0x08aL		/* Bugcheck generated by OS specific PAL	*/
#define	PAL_BUG_CHK	0x090L		/* Bugcheck generated by PAL			*/
#define	ICACHE_READ_ERR	0x096L		/* I-Cache Read retryable error			*/
#define	CPU_HARD_ERR	0x098L		/* Processor Detected Hard Error		*/
/* KN20AA platform Machine Check Error Codes (May become EV5 general MCHECH Codes
 * as things stablize )
 */
#define	SYS_ECC		0x201L		/* System Detected Uncorrectable ECC Error	*/
#define	CIA_MEM_PORT	0x202L		/* CIA MEM_PORT Error				*/
#define	EV5_TO_CIA	0x203L		/* EV5 to CIA interface Error			*/
#define	ILL_CMD		0x204L		/* Illegal EV5 Command Sequence			*/
#define	CIA_HARD_ERR	0x205L		/* CIA Hardware Error				*/
#define	SCAT_GATH	0x206L		/* Scatter Gather TLB Invalid entry		*/
#define	NXM		0x207L		/* Non-Existent Memory or Non-Existent CSR	*/
#define	SPARSE_RSVD	0x208L		/* Sparce Space Reserved Address Detected	*/
#define	PCI_SERR	0x209L		/* PCI SERR Detected				*/
#define	PCI_DATA_PARITY	0x20aL		/* PCI bad data parity detected			*/
#define	PCI_PROTOCOL	0x20bL		/* PCI Protocol Error				*/
#define	PCI_MEM_WRITE	0x20cL		/* PCI Memory Write and Invalidate Command sent
					   data which was not a cache multiple in size  */
#define	PCI_ADD_PARITY	0x20dL		/* PCI address parity error			*/
#define	TARGET_ABORT	0x20eL		/* Target Abort Error				*/
#define	MASTER_ABORT	0x20fL		/* Master abort error				*/
#define	ILOCK		0x210L		/* IOCK#, EISA add-in board parity error or 
					   other catastropic error.			*/
#define	FAILSAFE_TIMEER	0x211L		/* Fail Safe Timer Timeout			*/
#define	EIAS_BUS_TO	0x212L		/* EISA Bus Timeout				*/
#define	OS_NMI		0x213L		/* Software Generated NMI			*/

/* Machine check codes */
#define EV5_corrected		0x00000086L
#define System_corrected 	0x00000201L

/* DEC 1000 */                                                    
                                                                  
struct el_1000_sysdata_mcheck {
	u_long	coma_gcr;
	u_long	coma_edsr;
	u_long	coma_ter;
	u_long	coma_elar;
	u_long	coma_ehar;
	u_long	coma_ldlr;
	u_long	coma_ldhr;
	u_long	coma_base0;
	u_long	coma_base1;
	u_long	coma_base2;
	u_long	coma_base3;
	u_long	coma_cnfg0;
	u_long	coma_cnfg1;
	u_long	coma_cnfg2;
	u_long	coma_cnfg3;
	u_long	epic_dcsr;
	u_long	epic_pear;
	u_long	epic_sear;
	u_long	epic_tbr1;
	u_long	epic_tbr2;
	u_long	epic_pbr1;
	u_long	epic_pbr2;
	u_long	epic_pmr1;
	u_long	epic_pmr2;
	u_long	epic_harx1;
	u_long	epic_harx2;
	u_long	epic_pmlt;
	u_long	epic_tag0;
	u_long	epic_tag1;
	u_long	epic_tag2;
	u_long	epic_tag3;
	u_long	epic_tag4;
	u_long	epic_tag5;
	u_long	epic_tag6;
	u_long	epic_tag7;
	u_long	epic_data0;
	u_long	epic_data1;
	u_long	epic_data2;
	u_long	epic_data3;
	u_long	epic_data4;
	u_long	epic_data5;
	u_long	epic_data6;
	u_long	epic_data7;

	u_long	pceb_vid;
	u_long	pceb_did;
	u_long	pceb_revision;
	u_long	pceb_command;
	u_long	pceb_status;
	u_long	pceb_latency;
	u_long	pceb_control;
	u_long	pceb_arbcon;
	u_long	pceb_arbpri;

	u_long	esc_id;
	u_long	esc_revision;
	u_long	esc_int0;
	u_long	esc_int1;
	u_long	esc_elcr0;
	u_long	esc_elcr1;
	u_long	esc_last_eisa;
	u_long	esc_nmi_stat;

	u_long	pci_ir;
	u_long	pci_imr;
	u_long	svr_mgr;
};
                                                                  
struct el_1000_frame_mcheck {                                     
	struct el_common_logout_header elfmc_hdr;                 
	struct el_common_procdata_mcheck elfmc_procdata;          
	struct el_1000_sysdata_mcheck elfmc_sysdata;              
};

/* DEC 1000A */                                                    
                                                                  
struct el_1000A_sysdata_mcheck {
	u_long	coma_gcr;
	u_long	coma_edsr;
	u_long	coma_ter;
	u_long	coma_elar;
	u_long	coma_ehar;
	u_long	coma_ldlr;
	u_long	coma_ldhr;
	u_long	coma_base0;
	u_long	coma_base1;
	u_long	coma_base2;
	u_long	coma_base3;
	u_long	coma_cnfg0;
	u_long	coma_cnfg1;
	u_long	coma_cnfg2;
	u_long	coma_cnfg3;
	u_long	epic_dcsr;
	u_long	epic_pear;
	u_long	epic_sear;
	u_long	epic_tbr1;
	u_long	epic_tbr2;
	u_long	epic_pbr1;
	u_long	epic_pbr2;
	u_long	epic_pmr1;
	u_long	epic_pmr2;
	u_long	epic_harx1;
	u_long	epic_harx2;
	u_long	epic_pmlt;
	u_long	epic_tag0;
	u_long	epic_tag1;
	u_long	epic_tag2;
	u_long	epic_tag3;
	u_long	epic_tag4;
	u_long	epic_tag5;
	u_long	epic_tag6;
	u_long	epic_tag7;
	u_long	epic_data0;
	u_long	epic_data1;
	u_long	epic_data2;
	u_long	epic_data3;
	u_long	epic_data4;
	u_long	epic_data5;
	u_long	epic_data6;
	u_long	epic_data7;

	u_long	pceb_vid;
	u_long	pceb_did;
	u_long	pceb_revision;
	u_long	pceb_command;
	u_long	pceb_status;
	u_long	pceb_latency;
	u_long	pceb_control;
	u_long	pceb_arbcon;
	u_long	pceb_arbpri;

	u_long	esc_id;
	u_long	esc_revision;
	u_long	esc_int0;
	u_long	esc_int1;
	u_long	esc_elcr0;
	u_long	esc_elcr1;
	u_long	esc_last_eisa;
	u_long	esc_nmi_stat;

	u_long	pci_ir1;
	u_long	pci_ir2;
	u_long	pci_ir3;
	u_long	pci_imr1;
	u_long	pci_imr2;
	u_long	pci_imr3;
	u_long	ppb_pstatus;
	u_long	ppb_sstatus;
	u_long	svr_mgr;
};
                                                                  
struct el_1000A_frame_mcheck {                                     
	struct el_common_logout_header elfmc_hdr;                 
	struct el_common_procdata_mcheck elfmc_procdata;          
	struct el_1000A_sysdata_mcheck elfmc_sysdata;              
};

/* ==============================  EV5 ==========================
 */


/* This is a common header that all machine check frames have.
 */

struct el_common_EV5_logout_header {
	u_int	elfl_size;		/* size in bytes of logout area. */
	int	elfl_sbz1:30;		/* Should Be Zero		 */
	int	elfl_2nd_error:1;	/* 1 for second error occured	 */
	int	elfl_retry:1;		/* Retry flag. 			 */
        u_int	elfl_procoffset;	/* Processor-specific offset.	 */
	u_int	elfl_sysoffset;		/* Offset of system-specific. 	 */
        u_long  elfl_mcheck_code;	/* machine check code 		 */
};

/* Machine Check Frame for uncorrectable errors (Large format)
 *	--- This is used to log uncorrectable errors shuch as double bit ECC errors.
 *	--- These errors are detceted by both processor and systems.
 */
struct el_common_EV5_uncorrectable_mcheck {
	u_long		elfmc_shadow[8];	/* Shadow reg. 8-14, 25		  */
	u_long		elfmc_paltemp[24];	/* PAL TEMP REGS. 		  */
	vm_offset_t	elfmc_exc_addr;		/* Address of excepting instruction*/
	u_long		elfmc_exc_sum;		/* Summary of arithmetic traps.   */
	u_long		elfmc_exc_mask;		/* Exception mask (from exc_sum). */
	vm_offset_t	elfmc_pal_base;		/* Base address for PALcode. 	  */
	u_long		elfmc_isr;		/* Interrupt Status Reg. 	  */
	u_long		elfmc_icsr;		/* CURRENT SETUP OF EV5 IBOX	  */
	u_long		elfmc_ic_perr_stat;	/* I-CACHE Reg. <11> set Data parity
						                <12> set TAG parity*/
	u_long		elfmc_dc_perr_stat;	/* D-CACHE error Reg. Bits set to 1:
						     <2> Data error in bank 0
						     <3> Data error in bank 1
						     <4> Tag error in bank 0
						     <5> Tag error in bank 1 	  */
	vm_offset_t	elfmc_va;		/* Effective VA of fault or miss. */
	u_long		elfmc_mm_stat;		/* Holds the reason for D-stream 
						   fault or D-cache parity errors */
	vm_offset_t	elfmc_sc_addr;		/* Address that was being accessed
						   when EV5 detected Secondary cache
						   failure.			  */
	u_long		elfmc_sc_stat;		/* Helps determine if the error was
						   TAG/Data parity(Secondary Cache)*/
	vm_offset_t	elfmc_bc_tag_addr;	/* Contents of EV5 BC_TAG_ADDR	  */
	vm_offset_t	elfmc_ei_addr;		/* Physical address of any transfer
						   that is logged in the EV5 EI_STAT*/
	u_long		elfmc_fill_syndrome;	/* For correcting ECC errors.	  */
	u_long		elfmc_ei_stat;		/* Helps identify reason of any 
						   processor uncorrectable error
						   at its external interface.	  */

	u_long		elfmc_LD_LOCK;		/* Contents of EV5 LD_LOCK register*/
};

/* Correctable Machine Check logout frame.
 *	---Used to log correctable errors shuch as Single bit ECC errors.
 *	---These errors can be detected by either the processor or the system
 */
struct el_common_EV5_correctable_mcheck {
	vm_offset_t	elfcc_ei_addr;
	u_long		elfcc_fill_syndrome;	/* For correcting ECC errors.	  */
	u_long		elfcc_ei_stat;		/* Helps identify reason of any 
						   processor uncorrectable error
						   at its external interface.	  */

	u_long		elfcc_isr;		/* Interrupt Status Reg. 	  */
};

/*
 * System specific portion of the correctable machine check logout frame for
 * Digital Unix on the Alphastation 600
 */
struct el_kn20aa_correctable_mcheck {
	u_long		elfcc_ecc_syn;		/* Contents of the CIA Error Syndrome 
						   Register Isolates the failing bit in
						   the Quadword system detected correctable
						   error.  The register will contain the failing
						   ECC syndrome for system detected ECC
						   errors. Data in EV5 FILL_SYN register should
						   NOT be used to isolate a single bit error. */
	u_long		elfcc_mem_err0;		/* low order address bits for the
						   location in memory that contains 
						   a single bit error.		  */
	u_long		elfcc_mem_err1;		/* high order address bits for the
						   location in memory that contains 
						   a single bit error.		  */
	u_long		elfcc_cia_err_stat;	/* Contentes of the CIA Error Status
						   register which contains translation type
						   or current state of the CIA, .... etc. */
	u_long		elfcc_cia_err;		/* Contents of the CIA Error register.
						   If <0> is set a system detected correctable 
						   error.  The PALcode will write a zero
						   to the register after it has logged all the 
						   appropriate information.  This will unlock the
						   CIA Error register so they can be updated on 
						   a future error. 		*/
};

/* KN20AA Machine Check Logout Frame
 */
struct el_kn20aa_mcheck {
	u_long		elfmc_eir0;		/* Low order address bits 
						   (EV5 ADDR_H <31:4>
						   of the CPU address/CMD Bus
						   are locked into this 
						   register upon an EV5 interface
						   error. A write to it unlocks
						   it. If anpther error occurs while
						   it is locked the data is
						   unchanged BUT the  EV5_LOST bit
						   in ER1 is set		  */
	u_long		elfmc_eir1;		/* High order address bits 
						   (EV5 ADDR_H <39:2> as well as 
						   other information.		  */
	u_long		elfmc_cia_err;		/* The contents of the CIA_ERR
						   register at the time of error.
						   */
	u_long		elfmc_cia_err_stat;	/* CIA_ERR_STAT reg. at time 
						   of error */
	u_long		elfmc_cia_err_mask;	/* CIA_ERR_MASK at time of error */
	u_long		elfmc_ecc_syn;		/* ECC_SYN register	  */
	u_long		elfmc_mem_err0;		/* Low order address bits 
						   (MEM)ADDR_H<31:4>		  */
        u_long          elfmc_mem_err1;         /* CIA_MEM1 register.    */
        u_long          elfmc_pci_err0;         /* PCI_ERR0 register.    */
        u_long          elfmc_pci_err1;         /* PCI_ERR1 register.    */
        u_long          elfmc_nmi_info;         /* EISA bridge NMI status & control
                                                   register                       */
        u_long          elfmc_pci_err2;         /* PCI_ERR2 register.    */
};


/* KN20AA Un-corrected error log data structures
 */
struct el_kn20aa_uncorrected_frame_mcheck {
	struct el_common_EV5_logout_header elfmc_hdr;
	struct el_common_EV5_uncorrectable_mcheck elfmc_procdata;
	struct el_kn20aa_mcheck elfmc_sysdata;
};

/* KN20AA corrected error log data structures
 */
struct el_kn20aa_corrected_frame_mcheck {
	struct el_common_EV5_logout_header elfcc_hdr;
	struct el_common_EV5_correctable_mcheck elfcc_procdata;
	struct el_kn20aa_correctable_mcheck elfcc_sysdata;
};

/*
 * GAMMA - machine check error log data structures
 */

struct el_kn470_sysdata_mcheck {
	u_long elcmc_creg;	
	u_long elcmc_esreg;	
	u_long elcmc_evbcr;	
	u_long elcmc_evbear;	
	u_long elcmc_evbcer;	
	u_long elcmc_evbcear;	
	u_long elcmc_evbuer;	
	u_long elcmc_evbuear;	
	u_long elcmc_evresv;	
	u_long elcmc_dtctr;	
	u_long elcmc_dter;	
	u_long elcmc_dttcr;	
	u_long elcmc_dttr;	
	u_long elcmc_dtresv;	
	u_long elcmc_ibcsr;	
	u_long elcmc_ibear;	
	u_long elcmc_acr;	
	u_long elcmc_cbcr;	
	u_long elcmc_cber;	
	u_long elcmc_cbealr;	
	u_long elcmc_cbeahr;	
	u_long elcmc_cbresv;	
	u_long elcmc_alr;	
	u_long elcmc_pmbr;	
	u_long elcmc_iirr;	
	u_long elcmc_sicr;	
	u_long elcmc_mresv;	
	u_long elcmc_pmr1;	
	u_long elcmc_pmr2;	
	u_long elcmc_pmr3;	
	u_long elcmc_pmr4;	
	u_long elcmc_pmr5;	
};

/*
 * Sable other cpu error frame - sable pfms section 3.43
 */
struct el_kn470_data_other_cpu {
	short	elco_cpuid;	/* CPU ID */
	short	elco_res02[3];	
	u_long elco_creg;	
	u_long elco_esreg;	
	u_long elco_evbcr;	
	u_long elco_evbear;	
	u_long elco_evbcer;	
	u_long elco_evbcear;	
	u_long elco_evbuer;	
	u_long elco_evbuear;	
	u_long elco_evresv;	
	u_long elco_dtctr;	
	u_long elco_dter;	
	u_long elco_dttcr;	
	u_long elco_dttr;	
	u_long elco_dtresv;	
	u_long elco_ibcsr;	
	u_long elco_ibear;	
	u_long elco_acr;	
	u_long elco_cbcr;	
	u_long elco_cber;	
	u_long elco_cbealr;	
	u_long elco_cbeahr;	
	u_long elco_cbresv;	
	u_long elco_alr;	
	u_long elco_pmbr;	
	u_long elco_iirr;	
	u_long elco_sicr;	
	u_long elco_mresv;	
	u_long elco_pmr1;	
	u_long elco_pmr2;	
	u_long elco_pmr3;	
	u_long elco_pmr4;	
	u_long elco_pmr5;	
};

/* 
 * Gamma error log data structure
 * Note there are 4 memory slots on sable (see kn450.h)
 */
struct el_kn470_uncorrected_frame_mcheck {
        struct el_cobra_frame_header elfmc_header;	/* ID$P-FRAME_MCHECK */
	struct el_common_EV5_logout_header elfmc_hdr;
	struct el_common_EV5_uncorrectable_mcheck elfmc_procdata;
	struct el_kn470_sysdata_mcheck elfmc_sysdata;
	struct el_kn450_data_t2 elfmc_t2data;
	struct el_kn450_data_memory elfmc_memdata[4]; 
        struct el_cobra_frame_header elfmc_footer;	/* empty */
};
/* 
 * Gamma error log data structure for corrected data
 */

struct el_kn470_EV5_correctable_mcheck {
	vm_offset_t	elfcc_ei_addr;
	u_long		elfcc_fill_syndrome; /* For correcting ECC errors.   */
	u_long		elfcc_ei_stat;	     /* Helps identify reason of     */
	                                     /* any processor uncorrectable  */
	                                     /* error at its external        */
	                                     /* interface.                   */

	u_long		elfcc_isr;	     /* Interrupt Status Reg.        */
};

struct el_kn470_correctable_mcheck {
	u_long             elfce_creg_csr0;
	u_long             elfce_esreg_csr1;
	u_long             elfce_evbcr_csr2;
	u_long             elfce_evbcer_csr4;
	u_long             elfce_evbcear_csr5;
};

struct el_kn470_corrected_frame_mcheck {
	struct el_cobra_frame_header elfcc_header; /* ID$P-BC-COR */
	struct el_common_EV5_logout_header elfcc_hdr;
	struct el_kn470_EV5_correctable_mcheck elfcc_procdata;
	struct el_kn470_correctable_mcheck elfcc_sysdata;
	struct el_cobra_frame_header elfcc_footer; /* empty */
};




/*
 * AXPpci33 NoName Machine Check Error Codes
 */
#define EBP10_MCHK_SERR		0x14	/* SIO - error PCI SERR signal */
#define EBP10_MCHK_IOCHK	0x15	/* SIO - ISA IOCHK signal */
#define EBP10_MCHK_PCIERR	0x84	/* LCA IO - PCI error */
#define EBP10_MCHK_CTE		0x80	/* MEMORY - Bcache Tag Parity */
#define EBP10_MCHK_NXM		0x84	/* MEMORY - Nonexistent Memory */
#define EBP10_MCHK_UEE		0x88	/* MEMEORY - Uncorrectable Memory */

#define PROC_MCHECK	0x670		/* Processor Machine Check Vector */
#define	SYS_MCHECK	0x660		/* System Machine Check Vector */

/*
 * AXPpci33 NoName Machinecheck logout frame header
 */
struct el_ebp10_logout_header {
        u_int   elfl_size;              /* size in bytes of logout area. */
        int     elfl_sbz1:31;           /* Should be zero. */
        char    elfl_retry:1;           /* Retry flag. */
        u_int   elfl_procoffset;        /* Processor-specific offset. */
        u_int   elfl_sysoffset;         /* Offset of system-specific. */
	u_int	elfl_mchk_code;		/* machine check code (from PAL) */
	u_int	elfl_frame_rev;		/* logout frame revision (from PAL) */
};

/*
 * AXPpci33 NoName Processor specific data for 
 * uncorrectable machine check logout frame 
 */
struct el_ebp10_uprocdata {
        u_long          elfmc_paltemp[31];	/* PAL TEMP REGS. */
        /* EV4-specific fields */
        vm_offset_t     elfmc_exc_addr;	/* Address of excepting instruction. */
        u_long          elfmc_exc_sum;  /* Summary of arithmetic traps. */
        u_long          elfmc_exc_mask; /* Exception mask (from exc_sum). */
        u_long          elfmc_iccsr;    /* IBox hardware enables. */
        vm_offset_t     elfmc_pal_base; /* Base address for PALcode. */
        u_long          elfmc_hier;     /* Hardware Interrupt Enable. */
        u_long          elfmc_hirr;     /* Hardware Interrupt Request. */
        u_long          elfmc_mm_csr;   /* D-stream fault info. */
        u_long          elfmc_dc_stat;  /* D-cache status (ECC/Parity Err). */
        u_long          elfmc_dc_addr;  /* EV3 Phys Addr for ECC/DPERR. */
        u_long          elfmc_abox_ctl; /* ABox Control Register. */
        /* fields that are differnt from EV4 for LCA */
        u_long          elfmc_lca_esr;
        vm_offset_t     elfmc_lca_ear;
        u_long          elfmc_lca_car;
        u_long          elfmc_lca_stat0;
        vm_offset_t     elfmc_lca_stat1;
        /* End different fields for lca */
        vm_offset_t     elfmc_va;       /* Effective VA of fault or miss. */
        u_long          elfmc_bc_tag;   /* Backup Cache Tag Probe Results. */
};

/*
 * AXPpci33 NoName Processor specific data for 
 * correctable mchine check logout frame
 */
struct el_ebp10_cprocdata {
	u_long		elfmc_esr;	/* memory controller error status */
	u_long		elfmc_ear;	/* memory controller error address */
	u_long		elfmc_dc_stat;	/* data cache address register */
	u_long		elfmc_stat0;	/* i/o controller status 0 register */
	u_long		elfmc_stat1;	/* i/o controller status 1 register */
	u_long		elfmc_bc_tag;	/* Backup Cache Tag Probe Results */
};

/* 
 * AXPpci33 NoName System specific data in logout frame  
 */
struct el_ebp10_sysdata {
	u_long		elfmc_sio_status;/* SIO Status 		WORD */
	u_long		elfmc_sio_rev;	/* SIO Revision 	BYTE */
	u_long		elfmc_sio_ubcsa; /* SIO Util Bus CSA 	BYTE */
	u_long		elfmc_sio_ubcsb; /* SIO Util Bus CSB	BYTE */
	u_long		elfmc_sio_pirq;	/* PIRQ Route Regs  LONGWORD */
	u_long		elfmc_sio_irq_mask0; /* IRQ Mask Reg 0	BYTE */
	u_long		elfmc_sio_irq_mask1; /* IRQ Mask Reg 1	BYTE */
	u_long		elfmc_sio_irq_edge0; /* IRQ Edge/Lvl 0	BYTE */
	u_long		elfmc_sio_irq_edge1; /* IRQ Edge/Lvl 1	BYTE */
	u_long		elfmc_sio_irq_irr0; /* IRQ Int Req Reg 0 BYTE */
	u_long		elfmc_sio_irq_irr1; /* IRQ Int Req Reg 1 BYTE */
	u_long		elfmc_sio_irq_isr0; /* IRQ Int Sts Reg 0 BYTE */
	u_long		elfmc_sio_irq_isr1; /* IRQ Int Sts Reg 1 BYTE */
	u_long		elfmc_sio_nmi_status; /* NMI Sts/Ctl	BYTE */
	u_long		elfmc_sio_dma_status0; /* DMA Status 0	BYTE */
	u_long		elfmc_sio_dma_status1; /* DMA Status 1	BYTE */
};

/*
 * AXPpci33 NoName Correctable Processor Machine Check Logout Frame
 *        [*** Not Yet Implemented ***]
 */
struct el_ebp10_frame_proc_corr {
	struct el_ebp10_logout_header	elfmc_hdr;
	struct el_ebp10_cprocdata	elfmc_cprocdata;
	struct el_ebp10_sysdata		elfmc_sysdata;
};

/*
 * AXPpci33 NoName Uncorrectable Processor Machine check logout frame 
 */
struct el_ebp10_frame_proc_uncorr {
	struct el_ebp10_logout_header	elfmc_hdr;
	struct el_ebp10_uprocdata	elfmc_uprocdata;
	struct el_ebp10_sysdata		elfmc_sysdata;
};

/*
 * EB164 Machine Check Logout Frame
 */
struct el_eb164_mcheck {
	u_long		elfmc_eir0;		/* Low order address bits 
						   (EV5 ADDR_H <31:4>
						   of the CPU address/CMD Bus
						   are locked into this 
						   register upon an EV5 interface
						   error. A write to it unlocks
						   it. If anpther error occurs while
						   it is locked the data is
						   unchanged BUT the  EV5_LOST bit
						   in ER1 is set.

						   On Miata, this is a dummy reg */

	u_long		elfmc_eir1;		/* High order address bits 
						   (EV5 ADDR_H <39:2> as well as 
						   other information.

						   On Miata, this is the data that
						   was being transferred on a dma
						   cycle when a failure occurred. */

	u_long		elfmc_cia_err;		/* The contents of the CIA_ERR
						   register at the time of error.
						   */
	u_long		elfmc_cia_err_stat;	/* CIA_ERR_STAT reg. at time 
						   of error */
	u_long		elfmc_cia_err_mask;	/* CIA_ERR_MASK at time of error */
	u_long		elfmc_ecc_syn;		/* CIA ASIC ECC_SYN register	  */
	u_long		elfmc_mem_err0;		/* Low order address bits 
						   (MEM)ADDR_H<31:4>		  */
	u_long		elfmc_mem_err1;		/* CIA ASIC CIA_MEM1 register.    */
	u_long		elfmc_pci_err0;		/* CIA ASIC CIA_ERR0 register.    */
	u_long		elfmc_pci_err1;		/* CIA ASIC CIA_ERR1 register.    */
	u_long		elfmc_nmi_info;		/* EISA bridge NMI status & control
						   register 			  */
	u_long		elfmc_pci_err2;		/* PCI_ERR2 register.    */
};

/*
 * System specific portion of the correctable machine check logout frame for EB164
 */
struct el_eb164_correctable_mcheck {
	u_long		elfcc_ecc_syn;		/* Contents of the CIA Error Syndrome 
						   Register Isolates the failing bit in
						   the Quadword system detected correctable
						   error.  The register will contain the failing
						   ECC syndrome for system detected ECC
						   errors. Data in EV5 FILL_SYN register should
						   NOT be used to isolate a single bit error. */
	u_long		elfcc_mem_err0;		/* low order address bits for the
						   location in memory that contains 
						   a single bit error.		  */
	u_long		elfcc_mem_err1;		/* high order address bits for the
						   location in memory that contains 
						   a single bit error.		  */
	u_long		elfcc_cia_err_stat;	/* Contentes of the CIA Error Status
						   register which contains translation type
						   or current state of the CIA, .... etc. */
	u_long		elfcc_cia_err;		/* Contents of the CIA Error register.
						   If <0> is set a system detected correctable 
						   error.  The PALcode will write a zero
						   to the register after it has logged all the 
						   appropriate information.  This will unlock the
						   CIA Error register so they can be updated on 
						   a future error. 		*/
};

/*
 * EB164 Un-corrected error log data structures
 */
struct el_eb164_uncorrected_frame_mcheck {
	struct el_common_EV5_logout_header elfmc_hdr;
	struct el_common_EV5_uncorrectable_mcheck elfmc_procdata;
	struct el_eb164_mcheck elfmc_sysdata;
};

/*
 * EB164 corrected error log data structures
 */
struct el_eb164_corrected_frame_mcheck {
	struct el_common_EV5_logout_header elfcc_hdr;
	struct el_common_EV5_correctable_mcheck elfcc_procdata;
	struct el_eb164_correctable_mcheck elfcc_sysdata;
};

/*
 * TAKARA correctable Machinecheck System Specific Data
 */
struct el_ebm20_correctable_mcheck {
	u_long	elfcc_ecc_syn;	/* Contents of the CIA Error Syndrome 
				   Register Isolates the failing bit in
				   the Quadword system detected correctable
				   error. The register will contain the failing
				   ECC syndrome for system detected ECC
				   errors. Data in EV5 FILL_SYN register should
				   NOT be used to isolate a single bit error */
	u_long	elfcc_mem_err0;	/* low order address bits for the
				   location in memory that contains 
				   a single bit error.		  */
	u_long	elfcc_mem_err1;	/* high order address bits for the
				   location in memory that contains 
				   a single bit error.		  */
	u_long	elfcc_cia_err_stat; /* Contentes of the CIA Error Status
				      register which contains translation type
				      or current state of the CIA, .... etc. */
	u_long	elfcc_cia_err;	/* Contents of the CIA Error register.
				   If <0> is set a system detected correctable 
				   error.  The PALcode will write a zero
				   to the register after it has logged all the 
				   appropriate information.  This will unlock 
				   the CIA Error register so they can  
				   be updated on a future error.      	*/
};


/*
 * TAKARA Machine Check Logout Data System Specific portion
 */
struct el_ebm20_mcheck {
	u_long	elfmc_eir0;	/* Low order address bits 
				   (EV5 ADDR_H <31:4>
				   of the CPU address/CMD Bus
				   are locked into this 
				   register upon an EV5 interface
				   error. A write to it unlocks
				   it. If anpther error occurs while
				   it is locked the data is
				   unchanged BUT the  EV5_LOST bit
				   in ER1 is set		  */
	u_long	elfmc_eir1;	/* High order address bits 
				   (EV5 ADDR_H <39:2> as well as 
				   other information.		  */
	u_long	elfmc_cia_err;	/* The contents of the CIA_ERR
				   register at the time of error. */
	u_long	elfmc_cia_err_stat; /* CIA_ERR_STAT reg. at time 
				       of error */
	u_long	elfmc_cia_err_mask; /* CIA_ERR_MASK at time of error */
	u_long	elfmc_ecc_syn;	/* CIA ASIC ECC_SYN register	  */
	u_long	elfmc_mem_err0;	/* Low order address bits 
				   (MEM)ADDR_H<31:4>		  */
	u_long	elfmc_mem_err1;	/* CIA ASIC CIA_MEM1 register.    */
	u_long	elfmc_pci_err0;	/* CIA ASIC CIA_ERR0 register.    */
	u_long	elfmc_pci_err1;	/* CIA ASIC CIA_ERR1 register.    */
	u_long  elfmc_pci_err2;	/* CIA ASIC CIA_ERR2 register. (for CIA2)   */
	/* Takara Systsem Specific specific */
	/* Interrupt, Watchdog and Server Registers */
    u_long	inter_config;
    u_long	inter_reg1;
    u_long	inter_reg2;
    u_long	inter_reg3;
    u_long	inter_reg4;
    u_long	watchdog_reg;
    u_long	srvman_reg;
	/* TAKARA Specific */
	/* SIO (82378ZB) Registers */
    u_long	sio_status;
    u_long	sio_rev;
    u_long	sio_ubcsa;
    u_long	sio_ubcsb;
    u_long	sio_pirq;
    u_long	sio_irq_mask0;
    u_long	sio_irq_mask1;
    u_long	sio_irq_edge0;
    u_long	sio_irq_edge1;
    u_long	sio_irq_irr0;
    u_long	sio_irq_irr1;
    u_long	sio_irq_isr0;
    u_long	sio_irq_isr1;
    u_long	sio_nmi_status;
    u_long	sio_dma_stat0;
    u_long	sio_dma_stat1;
};


/*
 * TAKARA Un-corrected error log frame
 */
struct el_ebm20_uncorrected_frame_mcheck {
	struct el_common_EV5_logout_header elfmc_hdr;
	struct el_common_EV5_uncorrectable_mcheck elfmc_procdata;
	struct el_ebm20_mcheck elfmc_sysdata;
};

/* TAKARA corrected error log data structures
 */
struct el_ebm20_corrected_frame_mcheck {
	struct el_common_EV5_logout_header elfcc_hdr;
	struct el_common_EV5_correctable_mcheck elfcc_procdata;
	struct el_ebm20_correctable_mcheck elfcc_sysdata;
};


/*
 * AXPvme logout frame formats & constants
 *
 * AXPvme-based systems support two logout frames for:
 *
 *   1. processor correctable machine checks
 *   2. processor uncorrectable machine checks
 *
 * Each logout frame consists of a common frame header followed by
 * processor-specific frame data unique to the particular  machine
 * check - whether correctable or uncorrectable.
 *
 * In any case, no logout frames make use of system-specific  data
 * and system machine checks (correctable or uncorrectable) cannot
 * be generated.
 */


/*
 * machine check codes
 */

#define	EBV10_PROC_CORR	       0x0630	/* correctable processor machine check	     */
#define	EBV10_PROC_UCORR       0x0670	/* uncorrectable processor machine check     */


/*
 * machine check error codes
 */

#define	EBV10_MCHK_BUGCHK      0x008e	/* PALcode internal error		     */
#define	EBV10_MCHK_CORRECC     0x0086	/* correctable ecc error		     */
#define	EBV10_MCHK_HERR	       0x0084	/* non-existent memory or i/o controller     */
					/* error				     */
#define	EBV10_MCHK_OS_BUGCHK   0x0090	/* OS internal error			     */
#define	EBV10_MCHK_PCISERR     0x00a0	/* pci 'serr' error			     */
#define	EBV10_MCHK_TPERR       0x0080	/* backup cache tag parity error	     */
#define	EBV10_MCHK_UNCORRECC   0x0088	/* uncorrectable ecc error		     */
#define	EBV10_MCHK_UNKOWN      0x008a	/* unknown error			     */


/*
 * machine check logout frame header
 */

struct el_ebv10_logout_header
    {
    u_int	elfhd_size;		/* size of logout frame (in bytes)	     */
    int		elfhd_sbz1:30;		/* should be zero (sbz)			     */
    char	elfhd_sce:1;		/* second correctable error flag	     */
    char	elfhd_retry:1;		/* retry instruction flag		     */
    u_int	elfhd_procoffset;	/* processor-specific logout frame offset    */
    u_int	elfhd_sysoffset;	/* system-specific logout frame offset 	     */
    u_int	elfhd_mchk_code;	/* machine check error code (from PALcode)   */
    u_int	elfhd_frame_rev;	/* logout frame revision (from PALcode)	     */
    };


/*
 * processor-specific data for correctable machine
 * check logout frame 
 */

struct el_ebv10_procdata_corr
    {
    u_long	elfpd_esr;		/* memory controller error status register   */
    u_long	elfpd_ear;		/* memory controller error address register  */
    u_long	elfpd_dc_addr;		/* data cache address register		     */
    u_long	elfpd_stat0;		/* i/o controller status 0 register	     */
    u_long	elfpd_stat1;		/* i/o controller status 1 register	     */
    };


/*
 * correctable processor machine check logout frame 
 */

struct el_ebv10_frame_proc_corr
    {
    struct el_ebv10_logout_header  elfcp_hdr;
					/* logout frame header for correctable	     */
					/* processor machine check		     */
    struct el_ebv10_procdata_corr  elfcp_procdata;
					/* processor-specific data for correctable   */
					/* processor machine check		     */
    };


/*
 * processor-specific data for uncorrectable machine
 * check logout frame 
 */

struct el_ebv10_procdata_ucorr
    {
    u_long	elfpd_paltemp[31];	/* PALcode temporary processor registers     */
    vm_offset_t elfpd_exc_addr;		/* exception address register		     */
    u_long	elfpd_exc_sum;		/* exception summary register		     */
    u_long	elfpd_exc_mask;		/* exception mask register		     */
    u_long	elfpd_iccsr;		/* instruction cache control/status register */
    vm_offset_t	elfpd_pal_base;		/* base address for PALcode		     */
    u_long	elfpd_hier;		/* hardware interrupt enable register	     */
    u_long	elfpd_hirr;		/* hardware interrupt request register	     */
    u_long	elfpd_mm_csr;		/* memory management control/status register */
    u_long	elfpd_dc_stat;		/* data cache status register		     */
    u_long	elfpd_dc_addr;		/* data cache address register		     */
    u_long	elfpd_abox_ctl;		/* abox control register		     */
    u_long	elfpd_esr;		/* memory controller error status register   */
    u_long	elfpd_ear;		/* memory controller error address register  */
    u_long	elfpd_car;		/* memory controller cache register	     */
    u_long	elfpd_stat0;		/* i/o controller status 0 register	     */
    u_long	elfpd_stat1;		/* i/o controller status 1 register	     */
    vm_offset_t	elfpd_va;		/* virtual address register		     */
    };


/*
 * uncorrectable processor machine check logout frame 
 */

struct el_ebv10_frame_proc_ucorr
    {
    struct el_ebv10_logout_header  elfup_hdr;
					/* logout frame header for uncorrectable     */
					/* processor machine check		     */
    struct el_ebv10_procdata_ucorr elfup_procdata;
					/* processor-specific data for uncorrectable */
					/* processor machine check		     */
    };


/*
 * Lego K2 Machine Check Error Code
 */

/*
 * BIU_STAT errors detected by CPU	
 */
#define	EBM10_MCHK_CPU_BCACHE_ADDR	0x80 /* Bcache TAG address RAM parit */
#define	EBM10_MCHK_CPU_BCACHE_CTRL	0x82 /* Bcache TAG control RAM parit */

/*
 * DC_STAT errors detected by CPU
 */
#define	EBM10_MCHK_CPU_ICACHE_PAR	0x94 /* CPU Internal Icache parity */
#define	EBM10_MCHK_CPU_DCACHE_PAR	0x92 /* CPU Internal Dcache parity */

/*
 * BIU_STAT errors detected by CPU
 */
#define	EBM10_MCHK_CPU_CACHE_UNCOR	0x88 /* CPU cache FILL uncorrectable */
#define	EBM10_MCHK_CPU_CACHE_CORR	0x86 /* CPU cache FILL correctable */

/*
 * DECchip 21070-CA [Commanche] Errors 
 */
#define	EBM10_MCHK_COM_BCACHE_ADDR	0x20A /* Bcache TAG address parity */
#define	EBM10_MCHK_COM_BCACHE_CTRL	0x20B /* Bcache TAG control parity */
#define	EBM10_MCHK_COM_NXM		0x20C /* Non-existent memory access */

/*
 * DECchip 21070-DA [Epic] Errors
 */
#define	EBM10_MCHK_EPIC_PCI_IO_RETRY	0x210 /* PCI I/O Retry timeout error */
#define	EBM10_MCHK_EPIC_PCI_DMA_DATA	0x202 /* PCI DMA data parity error */
#define	EBM10_MCHK_EPIC_PCI_IO_DATA	0x203 /* PCI IO data parity error */
#define	EBM10_MCHK_EPIC_PCI_TRGT_ABRT	0x204 /* PCI target abort error */
#define EBM10_MCHK_EPIC_NO_DEVICE	0x205 /* PCI No Device error */
#define	EBM10_MCHK_EPIC_CORR_MEM_READ	0x206 /* Correctable memory read err */
#define	EBM10_MCHK_EPIC_UNCOR_MEM_READ	0x207 /* Uncorrectable memory read */
#define	EBM10_MCHK_EPIC_INVAL_PAGE	0x208 /* Invalid Page Lookup (sc/ga) */
#define	EBM10_MCHK_EPIC_MEM_CYCLE	0x209 /* Memory Cycle Error */

/*
 * SIO NMI/HALT/Server Management MCHKs
 */
#define EBM10_MCHK_FAN1_FAIL		0x223 /* CPU FAN Fail */
#define EBM10_MCHK_TEMP_FAIL		0x220 /* System Temperature Fail */
#define EBM10_MCHK_NMI_SYSERR		0x20D /* PCI bus SYSERR error */
#define EBM10_MCHK_NMI_IOCHK		0x20E /* ISA bus IOCHK error */


/*
 * Lego K2 Machinecheck logout frame header
 */
struct el_ebm10_logout_header	{
        u_int   elfl_size;              /* size in bytes of logout area. */
        int     elfl_sbz1:31;           /* Should be zero. */
        u_char  elfl_retry:1;	        /* retry flag. */
        u_int   elfl_procoffset;        /* Processor-specific offset. */
        u_int   elfl_sysoffset;         /* Offset of system-specific. */
	u_int	elfl_mchk_code;		/* machine check code (from PAL) */
	u_int	elfl_frame_rev;		/* logout frame revision (from PAL) */
};

/*
 * Lego K2 Processor specific data for
 * uncorrectable machine check logout frame
 */
struct el_ebm10_uprocdata  {
        u_long          elfmc_paltemp[31];	/* PAL TEMP REGS. */
        /* EV4-specific fields */
        vm_offset_t     elfmc_exc_addr;	/* Address of excepting instruction. */
        u_long          elfmc_exc_sum;  /* Summary of arithmetic traps. */
        u_long          elfmc_exc_mask; /* Exception mask (from exc_sum). */
        u_long          elfmc_iccsr;    /* IBox hardware enables. */
        vm_offset_t     elfmc_pal_base; /* Base address for PALcode. */
        u_long          elfmc_hier;     /* Hardware Interrupt Enable. */
        u_long          elfmc_hirr;     /* Hardware Interrupt Request. */
        u_long          elfmc_mm_csr;   /* D-stream fault info. */
        u_long          elfmc_dc_stat;  /* D-cache status (ECC/Parity Err). */
        u_long          elfmc_dc_addr;  /* EV3 Phys Addr for ECC/DPERR. */
        u_long          elfmc_abox_ctl; /* ABox Control Register. */
	u_long		elfmc_biu_stat;	/* BIU Status. */
	vm_offset_t	elfmc_biu_addr;	/* BUI Address. */
	u_long		elfmc_biu_ctl;	/* BIU Control. */
	u_long		elfmc_fill_syndrome; /* For correcting ECC errors */
	vm_offset_t	elfmc_fill_addr; /* Cache block  being read. */
        vm_offset_t     elfmc_va;       /* Effective VA of fault or miss. */
        u_long          elfmc_bc_tag;   /* Backup Cache Tag Probe Results. */
};

/*
 * Lego K2 System specific data in the machinecheck logout frame
 */
struct el_ebm10_sysdata {
				/* 21070-CA Commanche Registers */
    u_long	coma_gcr;			
    u_long	coma_edsr;			
    u_long	coma_ter;			
    u_long	coma_elar;			
    u_long	coma_ehar;			
    u_long	coma_ldlr;			
    u_long	coma_ldhr;			
    u_long	coma_base0;			
    u_long	coma_base1;			
    u_long	coma_base2;			
    u_long	coma_cnfg0;			
    u_long	coma_cnfg1;			
    u_long	coma_cnfg2;			
				/* 21070-DA Epic Registers */
    u_long	epic_dcsr;			
    u_long	epic_pear;			
    u_long	epic_sear;			
    u_long	epic_tbr1;			
    u_long	epic_tbr2;			
    u_long	epic_pbr1;			
    u_long	epic_pbr2;			
    u_long	epic_pmr1;			
    u_long	epic_pmr2;			
    u_long	epic_harx1;			
    u_long	epic_harx2;			
    u_long	epic_pmlt;			
    u_long	epic_tag0;			
    u_long	epic_tag1;			
    u_long	epic_tag2;			
    u_long	epic_tag3;			
    u_long	epic_tag4;			
    u_long	epic_tag5;			
    u_long	epic_tag6;			
    u_long	epic_tag7;			
    u_long	epic_data0;			
    u_long	epic_data1;			
    u_long	epic_data2;			
    u_long	epic_data3;			
    u_long	epic_data4;			
    u_long	epic_data5;			
    u_long	epic_data6;			
    u_long	epic_data7;			
				/* K2 specific */
				/* Interrupt, Watchdog and Server Registers */
    u_long	inter_config;
    u_long	inter_reg1;
    u_long	inter_reg2;
    u_long	inter_reg3;
    u_long	inter_reg4;
    u_long	watchdog_reg;
    u_long	srvman_reg;
				/* K2 Specific */
				/* SIO (82378ZB) Registers */
    u_long	sio_status;
    u_long	sio_rev;
    u_long	sio_ubcsa;
    u_long	sio_ubscb;
    u_long	sio_pirq;
    u_long	sio_irq_mask0;
    u_long	sio_irq_mask1;
    u_long	sio_irq_edge0;
    u_long	sio_irq_edge1;
    u_long	sio_irq_irr0;
    u_long	sio_irq_irr1;
    u_long	sio_irq_isr0;
    u_long	sio_irq_isr1;
    u_long	sio_nmi_status;
    u_long	sio_dma_stat0;
    u_long	sio_dma_stat1;
};


/*
 * Lego K2 Processor specific data for 
 * correctable error logout frame
 */
struct el_ebm10_cprocdata {
        u_long          elfmc_biu_stat;	/* BIU status */
        u_long          elfmc_biu_addr;	/* BIU address */
        u_long          elfmc_dc_stat; /* D-cache status (ECC/Parity Err) */
        u_long          elfmc_fill_syndrome; /* For correcting ECC errors */
        u_long          elfmc_fill_addr; /* Cache block being read */
        u_long          elfmc_bc_tag;   /* Backup Cache Tag Probe Results */
};


/*
 * Lego K2 Correctable Processor Error Logout Frane
 * Only a short frame (size = 0x48) is logged
 */
struct el_ebm10_frame_proc_corr {
        struct el_ebm10_logout_header	elfmc_hdr;
	struct  el_ebm10_cprocdata	elfmc_cprocdata;
	/* struct el_ebm10_sysdata	elfmc_sysdata; */
};

/*
 * Lego K2 Uncorrectable Processor Machine check logout frame
 */
struct el_ebm10_frame_proc_uncorr {
        struct el_ebm10_logout_header	elfmc_hdr;
	struct el_ebm10_uprocdata	elfmc_uprocdata;
	struct el_ebm10_sysdata         elfmc_sysdata;
};

/*
 * Cortex - AlphaVME 4/2xx 
 */
struct el_ebv14_logout_header	{
        u_int   elfl_size;              /* size in bytes of logout area. */
        int     elfl_sbz1:31;           /* Should be zero. */
        u_char  elfl_retry:1;	        /* retry flag. */
        u_int   elfl_procoffset;        /* Processor-specific offset. */
        u_int   elfl_sysoffset;         /* Offset of system-specific. */
	u_int	elfl_mchk_code;		/* machine check code (from PAL) */
	u_int	elfl_frame_rev;		/* logout frame revision (from PAL) */
};

struct el_ebv14_uprocdata { 
	u_long		elfmc_paltemp[31];	/* PAL TEMP REGS. */
	/* EV4-specific fields */
	vm_offset_t	elfmc_exc_addr;		/* Address of excepting instruction. */
	u_long		elfmc_exc_sum;		/* Summary of arithmetic traps. */
	u_long		elfmc_exc_mask;		/* Exception mask (from exc_sum). */
	u_long		elfmc_iccsr;		/* IBox hardware enables. */
	vm_offset_t	elfmc_pal_base;		/* Base address for PALcode. */
	u_long		elfmc_hier;		/* Hardware Interrupt Enable. */
	u_long		elfmc_hirr;		/* Hardware Interrupt Request. */
	u_long		elfmc_mm_csr;		/* D-stream fault info. */
	u_long		elfmc_dc_stat;		/* D-cache status (ECC/Parity Err). */
	u_long		elfmc_dc_addr;		/* EV3 Phys Addr for ECC/DPERR. */
	u_long		elfmc_abox_ctl;		/* ABox Control Register. */
	u_long		elfmc_biu_stat;		/* BIU Status. */
	vm_offset_t	elfmc_biu_addr;		/* BUI Address. */
	u_long		elfmc_biu_ctl;		/* BIU Control. */
	u_long		elfmc_fill_syndrome;	/* For correcting ECC errors. */
	vm_offset_t	elfmc_fill_addr;	/* Cache block which was being read. */
	vm_offset_t	elfmc_va;		/* Effective VA of fault or miss. */
	u_long		elfmc_bc_tag;		/* Backup Cache Tag Probe Results. */
};

struct el_ebv14_sysdata {
    /* Comanche specific data */
    u_long	coma_gcr;			
    u_long	coma_edsr;			
    u_long	coma_ter;			
    u_long	coma_elar;			
    u_long	coma_ehar;			
    u_long	coma_ldlr;			
    u_long	coma_ldhr;			
    u_long	coma_base0;			
    u_long	coma_base1;			
    u_long	coma_base2;			
    u_long	coma_base3;			
    u_long	coma_cnfg0;			
    u_long	coma_cnfg1;			
    u_long	coma_cnfg2;			
    u_long	coma_cnfg3;			

    /* EPIC specific data */
    u_long	epic_dcsr;			
    u_long	epic_pear;			
    u_long	epic_sear;			
    u_long	epic_tbr1;			
    u_long	epic_tbr2;			
    u_long	epic_pbr1;			
    u_long	epic_pbr2;			
    u_long	epic_pmr1;			
    u_long	epic_pmr2;			
    u_long	epic_harx1;			
    u_long	epic_harx2;			
    u_long	epic_pmlt;			
    u_long	epic_tag0;			
    u_long	epic_tag1;			
    u_long	epic_tag2;			
    u_long	epic_tag3;			
    u_long	epic_tag4;			
    u_long	epic_tag5;			
    u_long	epic_tag6;			
    u_long	epic_tag7;			
    u_long	epic_data0;			
    u_long	epic_data1;			
    u_long	epic_data2;			
    u_long	epic_data3;			
    u_long	epic_data4;			
    u_long	epic_data5;			
    u_long	epic_data6;			
    u_long	epic_data7;			
};

/*
 * Cortex Processor specific data for correctable error logout frame
 */
struct el_ebv14_cprocdata {
	u_long          elfmc_biu_stat;		/* BIU status */
	u_long          elfmc_biu_addr;		/* BIU address */
	u_long          elfmc_dc_stat; 		/* D-cache status (ECC/Parity Err) */
	u_long          elfmc_fill_syndrome; 	/* For correcting ECC errors */
	u_long          elfmc_fill_addr;	/* Cache block being read */
	u_long          elfmc_bc_tag;   	/* Backup Cache Tag Probe Results */
};

/*
 * Cortex Uncorrectable Processor Machine check logout frame
 */
struct el_ebv14_frame_proc_uncorr {
	struct el_ebv14_logout_header   elfmc_hdr;
	struct el_ebv14_uprocdata       elfmc_uprocdata;
	struct el_ebv14_sysdata         elfmc_sysdata;
};

/*
 * Cortex Correctable Processor Error Logout Frane
 * Only a short frame is logged
 */
struct el_ebv14_frame_proc_corr {
        struct el_ebv14_logout_header	elfmc_hdr;
	struct el_ebv14_cprocdata	elfmc_cprocdata;
};

/*
 * Alphabook Support
 */

/*
 *  Machine Check Error Codes
 */
#define ALPHABOOK_MCHK_SERR		0x14	/* SIO - error PCI SERR signal */
#define ALPHABOOK_MCHK_IOCHK		0x15	/* SIO - ISA IOCHK signal */
#define ALPHABOOK_MCHK_PCIERR		0x84	/* LCA IO - PCI error */
#define ALPHABOOK_MCHK_CTE		0x80	/* MEMORY - Bcache Tag Parity */
#define ALPHABOOK_MCHK_NXM		0x84	/* MEMORY - Nonexistent Memory */
#define ALPHABOOK_MCHK_UEE		0x88	/* MEMEORY - Uncorrectable Memory */

#define PROC_MCHECK	0x670		/* Processor Machine Check Vector */
#define	SYS_MCHECK	0x660		/* System Machine Check Vector */

/*
 * Alpha Notebook Machinecheck logout frame header
 */
struct el_alphabook_logout_header {
        u_int   elfl_size;              /* size in bytes of logout area. */
        int     elfl_sbz1:31;           /* Should be zero. */
        char    elfl_retry:1;           /* Retry flag. */
        u_int   elfl_procoffset;        /* Processor-specific offset. */
        u_int   elfl_sysoffset;         /* Offset of system-specific. */
	u_int	elfl_mchk_code;		/* machine check code (from PAL) */
	u_int	elfl_frame_rev;		/* logout frame revision (from PAL) */
};

/*
 * Alpha Notebook Processor specific data for 
 * uncorrectable machine check logout frame 
 */
struct el_alphabook_uprocdata {
        u_long          elfmc_paltemp[31];	/* PAL TEMP REGS. */
        /* EV4-specific fields */
        vm_offset_t     elfmc_exc_addr;	/* Address of excepting instruction. */
        u_long          elfmc_exc_sum;  /* Summary of arithmetic traps. */
        u_long          elfmc_exc_mask; /* Exception mask (from exc_sum). */
        u_long          elfmc_iccsr;    /* IBox hardware enables. */
        vm_offset_t     elfmc_pal_base; /* Base address for PALcode. */
        u_long          elfmc_hier;     /* Hardware Interrupt Enable. */
        u_long          elfmc_hirr;     /* Hardware Interrupt Request. */
        u_long          elfmc_mm_csr;   /* D-stream fault info. */
        u_long          elfmc_dc_stat;  /* D-cache status (ECC/Parity Err). */
        u_long          elfmc_dc_addr;  /* EV3 Phys Addr for ECC/DPERR. */
        u_long          elfmc_abox_ctl; /* ABox Control Register. */
        /* fields that are differnt from EV4 for LCA */
        u_long          elfmc_lca_esr;
        vm_offset_t     elfmc_lca_ear;
        u_long          elfmc_lca_car;
        u_long          elfmc_lca_stat0;
        vm_offset_t     elfmc_lca_stat1;
        /* End different fields for lca */
        vm_offset_t     elfmc_va;       /* Effective VA of fault or miss. */
        u_long          elfmc_bc_tag;   /* Backup Cache Tag Probe Results. */
};

/*
 * Alpha Notebook Processor specific data for 
 * correctable mchine check logout frame
 */
struct el_alphabook_cprocdata {
	u_long		elfmc_esr;	/* memory controller error status */
	u_long		elfmc_ear;	/* memory controller error address */
	u_long		elfmc_dc_stat;	/* data cache address register */
	u_long		elfmc_stat0;	/* i/o controller status 0 register */
	u_long		elfmc_stat1;	/* i/o controller status 1 register */
	u_long		elfmc_bc_tag;	/* Backup Cache Tag Probe Results */
};

/* 
 * Alpha Notebook System specific data in logout frame  
 */
struct el_alphabook_sysdata {
	u_long		elfmc_sio_status;/* SIO Status 		WORD */
	u_long		elfmc_sio_rev;	/* SIO Revision 	BYTE */
	u_long		elfmc_sio_ubcsa; /* SIO Util Bus CSA 	BYTE */
	u_long		elfmc_sio_ubcsb; /* SIO Util Bus CSB	BYTE */
	u_long		elfmc_sio_pirq;	/* PIRQ Route Regs  LONGWORD */
	u_long		elfmc_sio_irq_mask0; /* IRQ Mask Reg 0	BYTE */
	u_long		elfmc_sio_irq_mask1; /* IRQ Mask Reg 1	BYTE */
	u_long		elfmc_sio_irq_edge0; /* IRQ Edge/Lvl 0	BYTE */
	u_long		elfmc_sio_irq_edge1; /* IRQ Edge/Lvl 1	BYTE */
	u_long		elfmc_sio_irq_irr0; /* IRQ Int Req Reg 0 BYTE */
	u_long		elfmc_sio_irq_irr1; /* IRQ Int Req Reg 1 BYTE */
	u_long		elfmc_sio_irq_isr0; /* IRQ Int Sts Reg 0 BYTE */
	u_long		elfmc_sio_irq_isr1; /* IRQ Int Sts Reg 1 BYTE */
	u_long		elfmc_sio_nmi_status; /* NMI Sts/Ctl	BYTE */
	u_long		elfmc_sio_dma_status0; /* DMA Status 0	BYTE */
	u_long		elfmc_sio_dma_status1; /* DMA Status 1	BYTE */
};

/*
 * Alpha Notebook Correctable Processor Machine Check Logout Frame
 *        [*** Not Yet Implemented ***]
 */
struct el_alphabook_frame_proc_corr {
	struct el_alphabook_logout_header	elfmc_hdr;
	struct el_alphabook_cprocdata	elfmc_cprocdata;
	struct el_alphabook_sysdata		elfmc_sysdata;
};

/*
 * Alpha Notebook Uncorrectable Processor Machine check logout frame 
 */
struct el_alphabook_frame_proc_uncorr {
	struct el_alphabook_logout_header	elfmc_hdr;
	struct el_alphabook_uprocdata	elfmc_uprocdata;
	struct el_alphabook_sysdata		elfmc_sysdata;
};

/*
 * EBV16 Machine Check Logout Frame
 */
struct el_ebv16_mcheck {
	u_long		elfmc_eir0;		/* Low order address bits 
						   (EV5 ADDR_H <31:4>
						   of the CPU address/CMD Bus
						   are locked into this 
						   register upon an EV5 interface
						   error. A write to it unlocks
						   it. If anpther error occurs while
						   it is locked the data is
						   unchanged BUT the  EV5_LOST bit
						   in ER1 is set		  */
	u_long		elfmc_eir1;		/* High order address bits 
						   (EV5 ADDR_H <39:2> as well as 
						   other information.		  */
	u_long		elfmc_cia_err;		/* The contents of the CIA_ERR
						   register at the time of error.
						   */
	u_long		elfmc_cia_err_stat;	/* CIA_ERR_STAT reg. at time 
						   of error */
	u_long		elfmc_cia_err_mask;	/* CIA_ERR_MASK at time of error */
	u_long		elfmc_ecc_syn;		/* CIA ASIC ECC_SYN register	  */
	u_long		elfmc_mem_err0;		/* Low order address bits 
						   (MEM)ADDR_H<31:4>		  */
	u_long		elfmc_mem_err1;		/* CIA ASIC CIA_MEM1 register.    */
	u_long		elfmc_pci_err0;		/* CIA ASIC CIA_ERR0 register.    */
	u_long		elfmc_pci_err1;		/* CIA ASIC CIA_ERR1 register.    */
	u_long  	elfmc_pci_err2;		/* CIA ASIC CIA_ERR2 register. (for CIA2)   */
};

/*
 * System specific portion of the correctable machine check logout frame for EBV16
 */
struct el_ebv16_correctable_mcheck {
	u_long		elfcc_ecc_syn;		/* Contents of the CIA Error Syndrome 
						   Register Isolates the failing bit in
						   the Quadword system detected correctable
						   error.  The register will contain the failing
						   ECC syndrome for system detected ECC
						   errors. Data in EV5 FILL_SYN register should
						   NOT be used to isolate a single bit error. */
	u_long		elfcc_mem_err0;		/* low order address bits for the
						   location in memory that contains 
						   a single bit error.		  */
	u_long		elfcc_mem_err1;		/* high order address bits for the
						   location in memory that contains 
						   a single bit error.		  */
	u_long		elfcc_cia_err_stat;	/* Contentes of the CIA Error Status
						   register which contains translation type
						   or current state of the CIA, .... etc. */
	u_long		elfcc_cia_err;		/* Contents of the CIA Error register.
						   If <0> is set a system detected correctable 
						   error.  The PALcode will write a zero
						   to the register after it has logged all the 
						   appropriate information.  This will unlock the
						   CIA Error register so they can be updated on 
						   a future error. 		*/
};

/*
 * EBV16 Un-corrected error log data structures
 */
struct el_ebv16_uncorrected_frame_mcheck {
	struct el_common_EV5_logout_header elfmc_hdr;
	struct el_common_EV5_uncorrectable_mcheck elfmc_procdata;
	struct el_ebv16_mcheck elfmc_sysdata;
};

/*
 * EBV16 corrected error log data structures
 */
struct el_ebv16_corrected_frame_mcheck {
	struct el_common_EV5_logout_header elfcc_hdr;
	struct el_common_EV5_correctable_mcheck elfcc_procdata;
	struct el_ebv16_correctable_mcheck elfcc_sysdata;
};

#endif /* __ERRLOG__ */

