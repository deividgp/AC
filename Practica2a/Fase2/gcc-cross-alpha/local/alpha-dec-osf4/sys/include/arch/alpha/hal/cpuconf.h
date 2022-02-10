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
 *	@(#)cpuconf.h	9.6	(ULTRIX/OSF)	11/18/91
 */ 
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
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Derived from cpuconf.h	4.6	(ULTRIX)	9/3/90
 */

/*
 * Modification History: cpuconf.h
 *
 * 10-May-91	Paul Grist
 * 	Added support for 3max+/bigmax (DS_5000_300).
 *
 * 20-Aug-90	Matt Thomas
 *	Added maxdriftrecip (The reciprocal of the maximum clock drift
 *	rate) for both VAX and MIPS.
 *
 * 13-Aug-90	sekhar
 *	added print_consinfo interface for both vax and mips.
 *	added log_errinfo interface for both vax and mips.
 *
 * 03-Aug-90	Randall Brown
 *	Added system specific entries for all spl's and the intr() routine.
 *	Added entries for specific clock variables ( todrzero, rdclk_divider).
 *	Added #define for DS_5000_100 (3MIN).
 *
 * 03-Aug-90	rafiey (Ali Rafieymehr)
 *	Added support for VAX9000.
 *
 * 01-May-90    szczypek
 *      Added Mariah ID and Mariah variant.
 *
 * 01-May-90    Paul Grist
 *      Added support for mipsmate - DECsystem 5100
 *
 * 10-July-89	burns
 *	Moved Vax io related items to common section of table for DS5800.
 *	Added memsize and cpuinit for afd.
 *
 * 30-June-89	afd
 *	Add memory sizing routine to cpu switch table.
 *
 * 09-June-89	afd
 *	Added field HZ to cpusw (used to be in param.c).
 *	hz, tick, tickadj are set in processor specific init routines.
 *
 * 02-May-89	afd
 *	Added define VAX_3900 for Mayfair III system.
 *
 * 07-Apr-89	afd
 *	Created this file as a merged version of the old VAX cpuconf.h
 *	with new entries for MIPS based systems.  This file now supports
 *	both VAX and MIPS based systems.
 *
 *	Moved cpu type and system type defines here from cpu.h
 *	Moved macros for getting items from "systype" word here from hwconf.h
 *	Moved defines for R2000a cpu type and PMAX systype here from hwconf.h
 *	Added additional defines for CPU types, systypes and cpusw indexes.
 */


#ifndef _CPUCONF_H_
#define _CPUCONF_H_

#include <machine/inst.h>
/*
 * If we are not compiling as KERNEL, we need to include c_asm so
 * the GET_CPU_FAMILY macro can properly access the implver call via
 * the asm instruction generation method.
 */
#ifndef KERNEL
#include <c_asm.h>
#define implver() asm("implver %v0")
#endif

#define HARD_PARTITIONS		/* define to include hard partitions support */
#define HARD_PARTITIONS_DEBUG	/* define to enable debug code */
/* HWP_TODO: disable HARD_PARTITIONS_DEBUG before submit */

/*
 * DEC processor types for Alpha systems.  Found in HWRPB.
 * These values are architected.
 */

#define EV3_CPU			1	/* EV3			*/
#define EV4_CPU			2	/* EV4 (21064)		*/
#define LCA4_CPU		4	/* LCA4 (21066/21068)	*/
#define EV5_CPU			5	/* EV5 (21164)		*/
#define EV45_CPU		6	/* EV4.5 (21064/xxx)	*/
#define	EV56_CPU		7	/* EV5.6 (21164A)	*/
#define	EV6_CPU			8	/* EV6 (21264)		*/
#define	PCA56_CPU		9	/* EV5.6 (21164PC)	*/
#define	PCA57_CPU		10	/* EV5.7 (21164PC)	*/
#define	EV67_CPU		11	/* EV6.7 (21264A)	*/
#define	EV68CB_CPU		12	/* EV6.8CB (21264C)	*/
#define	EV68AL_CPU		13	/* EV6.8AL (21264B)	*/
#define	EV68CX_CPU		14	/* EV6.8CX (21264D)	*/

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

/* Get the CPU number of the base cpu for the generation.
 * The main use of this macro is to get the cpu part
 * of the family-cpu-smm platform identification that the SRM
 * firmware uses.
 */
#define GET_CPU_FAMILY(cpu)                    \
  switch (implver()) {                              \
	case IMPLVER_EV4_FAMILY:   *cpu = EV4_CPU; break; \
	case IMPLVER_EV5_FAMILY:   *cpu = EV5_CPU; break; \
	case IMPLVER_EV6_FAMILY:   *cpu = EV6_CPU; break; \
	default:                        break; \
	}


#define CPU_TYPE_TO_TEXT(type, string) \
	switch (type) {						\
	case EV3_CPU:  string = "EV3";			break;	\
	case EV4_CPU:  string = "EV4 (21064)";		break;	\
	case LCA4_CPU: string = "LCA4 (21066/21068)";	break;	\
	case EV5_CPU:  string = "EV5 (21164)";		break;	\
	case EV56_CPU: string = "EV5.6 (21164A)";	break;	\
	case PCA56_CPU: string = "EV5.6 (21164PC)";	break;	\
	case PCA57_CPU: string = "EV5.7 (21164PC)";	break;	\
	case EV45_CPU: string = "EV4.5 (21064)";	break;	\
	case EV6_CPU:  string = "EV6 (21264)";		break;	\
	case EV67_CPU:  string = "EV6.7 (21264A)";	break;	\
	case EV68CB_CPU:  string = "EV6.8CB (21264C)";	break;	\
	case EV68AL_CPU:  string = "EV6.8AL (21264B)";	break;	\
	case EV68CX_CPU:  string = "EV6.8CX (21264D)";	break;	\
	default:       string = "";			break;	\
	}
	
#endif    /* __LANGUAGE_C__ || __cplusplus */

/*
 * DEC system types for Alpha systems.  Found in HWRPB.
 * These values are architected.
 */

#define ST_ADU			1	/* Alpha ADU systype	*/
#define ST_DEC_4000		2	/* Cobra systype 	*/
#define ST_DEC_7000		3	/* Ruby systype		*/
#define ST_DEC_3000_500		4	/* Flamingo systype	*/
#define ST_DEC_2000_300		6	/* Jensen systype	*/
#define ST_DEC_3000_300         7       /* Pelican systype	*/
#define ST_DEC_2100_A500	9	/* Sable systype	*/
#define ST_DEC_AXPVME_64       10	/* AXPvme system type	*/
#define ST_DEC_AXPPCI_33       11       /* NoName system type   */
#define ST_DEC_21000	       12	/* Turbolaser systype */
#define ST_DEC_2100_A50	       13	/* Avanti systype	*/
#define ST_DEC_MUSTANG	       14	/* Mustang systype	*/
#define ST_DEC_KN20AA          15	/* kn20aa systype */ 
#define	ST_DEC_1000	       17	/* Mikasa systype       */
#define ST_EB66		       19	/* EB66 systype 	*/
#define ST_EB64P               20       /* EB64+ systype        */
#define ST_ALPHABOOK1          21       /* Alphabook1           */
#define	ST_DEC_4100	       22	/* RAWHIDE systype 	*/
#define	ST_DEC_EV45_PBP	       23	/* LEGO K2 Passive SBC systype */
#define ST_DEC_2100A_A500      24	/* LYNX systype		*/
#define ST_EB164               26       /* EB164 systype        */
#define ST_DEC_1000A	       27	/* Noritake systype	*/
#define ST_DEC_ALPHAVME_224    28       /* Cortex systype       */
#define ST_DEC_550	       30	/* miata systype	*/
#define ST_DEC_EV56_PBP        32	/* Takara systpe	*/
#define ST_DEC_ALPHAVME_320    33       /* Yukon systype        */
#define	ST_DEC_6600	       34	/* EV6-Typhoon systype 	*/
#define ST_DMCC_EV6	       37       /* EV6 Eiger DMCC systype */
/*
 * Bits in the Alpha processor variation field
 */
#define VAR_VAXFP	0x0000000000000001
#define VAR_IEEEFP	0x0000000000000002

/*
 * Bits in the Alpha system variation field
 */
#define SYS_MP		0x0000000000000001

/*
 * Value to be stored in the global variable "cpu".
 * The contents of "cpu" is no longer used to index into the "cpusw".
 * These values are arbitrarily assigned by ULTRIX (now OSF), but must each 
 * be unique and must be in the range 0 through (256 * 1024 -1). 	
 * See note on 3rd party CPU support below. 			 	
 * The variable "cpu" really contains a unique "system" identifier.
 *
 * note: the vector cpu_types[] within ../../io/scs/scsvar.c must be
 * updated when new cpu values are defined.
 *
 * These values must also track with MIPs (VAX) stuff, since the common
 * vector cpu_types[] uses them.
 *
 * note: Macros for registration of 3rd party CPUs are defined in
 * mach/machine.h  Digital is Vendor ID 0. 
 * Full macro definitions for each Digital CPU type are not provided here,  
 * but would be as shown in the example below for Flamingo:
 *
 *      #define DEC_VENDOR_ID   0       
 *      #define VENDOR_ID DEC_VENDOR_ID 
 *      #define DEC_3000_500  MAKESID(30)
 *  
 */

#define UNKN_SYSTEM	0
#define VAX_780         1
#define VAX_750         2
#define VAX_730         3
#define VAX_8600        4
#define VAX_8200        5
#define VAX_8800        6
#define MVAX_I          7
#define MVAX_II         8
#define V_VAX           9	/* Virtual VAX			*/
#define VAX_3600        10	/* Mayfair I			*/
#define VAX_6200        11	/* CVAX/Calypso			*/
#define VAX_3400        12	/* Mayfair II			*/
#define C_VAXSTAR       13	/* VAX3100 (PVAX)		*/
#define VAX_60          14	/* Firefox			*/
#define VAX_3900        15	/* Mayfair III			*/
#define	DS_3100		16	/* DECstation 3100 (PMAX)	*/
#define VAX_8820        17	/* This is the SID for Polarstar*/
#define	DS_5400 	18	/* MIPSfair			*/
#define	DS_5800		19	/* ISIS				*/
#define	DS_5000		20	/* 3MAX				*/
#define	DS_CMAX		21	/* CMAX				*/
#define VAX_6400	22	/* RIGEL/Calypso		*/
#define VAXSTAR		23	/* VAXSTAR			*/
#define DS_5500		24	/* MIPSFAIR-2			*/
#define DS_5100		25	/* MIPSMATE			*/
#define	VAX_9000	26	/* VAX9000			*/
#define DS_5000_100	27	/* 3MIN 			*/

#define ALPHA_ADU	28	/* Alpha ADU			*/
#define DEC_4000	29	/* Cobra			*/
#define DEC_3000_500	30	/* Flamingo workstation		*/
#define DEC_7000	31	/* EV4 on Lazer platform	*/
#define DS_5000_300	32	/* 3MAX+/BIGMAX			*/
#define DEC_3000_300	33	/* Pelican workstation		*/
#define DEC_2000_300	34	/* Jensen Alpha PC		*/
#define DEC_2100_A500	35	/* Sable			*/
#define	LCA_MUSTANG	36	/* Mustang Desktop PC		*/
#define	DEC_2100_A50	37	/* Avanti Alpha PC system	*/
#define ALPHA_KN20AA	38	/* kn20aa workstation		*/
#define DEC_21000	39	/* TurboLaser			*/
#define DEC_AXPVME_64   40      /* Medulla                      */
#define DEC_2100_C500	41	/* Gamma			*/
#define DEC_AXPPCI_33   42      /* NoName		        */
#define DEC_1000	43	/* Mikasa APS Server		*/
#define EB64_PLUS	44	/* EB64+ Evaluation Board       */
#define LCA_EB66	45	/* EB66 Evaluation Board	*/
#define ALPHA_EB164	46	/* EB164 Evaluation Board	*/
#define DEC_EV45_PBP	47	/* LEGO K2 Passive Backplane SBC */
#define DEC_1000A	48	/* Noritake			*/
#define DEC_4100	49	/* RAWHIDE			*/
#define DEC_ALPHAVME_224 50     /* Cortex                       */
#define DEC_1000_5	51	/* Mikasa/Pinnacle		*/
#define DEC_1000A_5	52	/* Noritake/Pinnacle		*/
#define DEC_EV56_PBP	53	/* TAKARA Passive Backplane SBC */
#define ALPHABOOK_1	54      /* Alphabook1                   */
#define DEC_ALPHAVME_320 55     /* Yukon                        */
#define DEC_550		56	/* Miata 			*/
#define DEC_6600	57	/* EV6-Typhoon based systems    */
#define DMCC_EV6	58      /* EV6 Eiger DMCC passive bacplane system */
#define CPU_MAX		58      /* Same # as last real entry    */

#define S_CORR_ERR    	0x620   /* System correctable error	*/
#define P_CORR_ERR	0x630   /* Processor correctable error	*/
#define S_MCHECK	0x660   /* System machine check 	*/
#define P_MCHECK	0x670   /* Processor machine check	*/
#define S_SRVMGMT_EVT	0x680	/* Server Management events	*/
/*
 * Defines for possible values of the flags field for mips and alpha
 */

#define SCS_START_SYSAPS	0x00000001
#define MSCP_POLL_WAIT		0x00000002

#ifndef ASSEMBLER
/*
 * The system switch is defined here.  Each entry is the only
 * line between the main unix code and the cpu dependent
 * code.  The initialization of the system switch is in the
 * file cpuconf.c.  The index values used in the switch are
 * defined in cpu.h.
 */

struct platform_callsw
{
        int (*platform_machcheck)();            /* hardware trap             */
        int (*platform_harderr_intr)();         /* hard error                */
        int (*platform_softerr_intr)();         /* soft error                */
        int (*platform_memenable)();            /*                           */
        int (*platform_config)();               /* system configuration      */
        int (*platform_badaddr)();              /* probe addresses           */
        int (*platform_readtodr)();             /* read time of day          */
        int (*platform_writetodr)();            /* write time of day         */
        int (*platform_ring_bell)();            /* ring bell                 */
        int (*platform_testpage)();             /* test a physical frame     */
        int (*platform_config_secondary)();     /* configure data structures
                                                   needed to start secondary;
                                                   runs on primary           */
        int (*platform_init_secondary)();       /* initialize secondary; runs
                                                   on secondary              */
        int (*platform_trans_dumpdev)();        /* get system specific device
                                                   string for fw             */
        int (*platform_get_info)();             /* get system specific info  */
        int (*platform_init)();                 /* initialization            */
};


/*
 * The following enum is used by the memory testing function to communicate
 * with the machine check handler as to what it is trying to do with the
 * memory.  We first need to initialize the memory prior to testing it and this
 * initialization may cause ECC errors depending upon the state of the memory
 * at power up.  These mchecks should be ignored and not be used as an
 * indication of whether or not the memory is in fact bad.  It is only when
 * we're trying to read the memory that machine check errors should cause
 * us to mark the page as bad.
 *
 *	INACTIVE_MEM:	memory testing not in progress
 *	INITING_MEM:	initializing memory to known state
 *	TESTING_MEM:	testing memory
 *	BAD_MEM:	memory is bad
 */
typedef enum {INACTIVE_MEM, INITING_MEM, TESTING_MEM, BAD_MEM} memtest_t;

#endif /* ASSEMBLER */
#endif /* _CPUCONF_H_ */

