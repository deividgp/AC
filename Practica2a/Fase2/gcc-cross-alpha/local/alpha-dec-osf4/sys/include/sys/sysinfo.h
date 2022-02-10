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
 *	@(#)$RCSfile: sysinfo.h,v $ $Revision: 4.3.39.2 $ (DEC) $Date: 1998/10/20 19:28:53 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * IBM CONFIDENTIAL
 * Copyright International Business Machines Corp. 1989
 * Unpublished Work
 * All Rights Reserved
 * Licensed Material - Property of IBM
 */
/*
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */ 

/* sysinfo.h	5.2 87/01/09 18:25:51 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _SYS_SYSINFO_H_
#define _SYS_SYSINFO_H_

/*  NOTE:  An assembly-language version of these structures exists
 *            in "sysinfo.m4".  BE SURE to update that file whenever
 *            <sys/sysinfo.h> is changed!!!
 */

#include <standards.h>
#include <sys/types.h>

struct sysinfo {
#define	CPU_NTIMES	4 	/* number of cpu times */
	time_t	cpu[CPU_NTIMES];   /* this array is updated every clock tick,
			     and keys off the state of the current running
			     process */
#define	CPU_IDLE	0 /* slot incremented whenever the 'wait' process
			     is the current running process */
#define	CPU_USER	1 /* slot incremented whenever the current running
			     process is executing in user mode */
#define CPU_KERNEL	2 /* slot incremented whenever the current running 
			     process is executing in kernel mode */
#define	CPU_WAIT	3 /* slot is always zero. This slot used to be
			     incremented whenever the current running process
			     was waiting for a block i/o request to
			     complete. Currently, whenever a process becomes
			     blocked, it is put to sleep and a new process
			     is made the current running process (i.e. processes
			     no longer maintain control of the cpu when they 
			     become blocked). */
	time_t	wait[3];
#define	W_IO	0
#define	W_SWAP	1
#define	W_PIO	2
#define	sysfirst	bread	/* first sysinfo variable - used by sysrates()
			  	   sysfirst define should be maintained as 
				   first non-array sysinfo variable */
	long	bread;
	long	bwrite;
	long	lread;
	long	lwrite;
	long	phread;
	long	phwrite;
	long	pswitch;
	long	syscall;
	long	sysread;
	long	syswrite;
	long	sysfork;  /* field is incremented by one whenever a 'fork'
			     is done */
	long	sysexec;  /* field is incremented by one whenever a 'exec'
			     is done */
	long	runque;   /* every second the process table is scanned to
			     determine the number of processes that are
			     ready to run. If that count is > 0 the
			     current number of ready processes is added 
			     to 'runque' (i.e. 'runque' is a cummulative
			     total of ready processes at second intervals). */
	long	runocc;   /* whenever 'runque' is updated, 'runocc'
			     is incremented by 1 (can be used to compute
			     the simple average of ready processes). */
	long	swpque;   /* every second the process table is scanned to 
			     determine the number of processes that are
			     inactive because they are waiting to be paged
			     in. If that count is > 0 then the current number
			     of processes waiting to be paged in is added
			     to 'swpque' (i.e. 'swpque' is a cummulative
			     total of processes waiting to be swapped in
			     at second intervals). */
	long	swpocc;   /* whenever 'swpque' is updated, 'swpocc' is 
			     incremented by one (can be used to compute
			     the simple average of processes waiting to be 
			     paged in).*/
	long	iget;
	long	namei;
	long	dirblk;
	long	readch;
	long	writech;
	long	rcvint;
	long	xmtint;
	long	mdmint;
	long	rawch;
	long	canch;
	long	outch;
	long	msg;
	long	sema;
	long    ksched;   /* field is incremented by one whenever a kernel
                             process is created */
	long    koverf;   /* field is incremented by one whenever an  attempt
			     is made to create a kernel process and:
				- the user has forked to their maximum limit
					       - OR -
				- the configuration limit of processes has been
				  reached */
	long    kexit;    /* field is incremented by one immediately after the
			     kernel process becomes a zombie */
	long    rbread;         /** remote read requests       **/
	long    rcread;         /** reads from remote cache    **/
	long    rbwrt;          /** remote writes              **/
	long    rcwrt;          /** cached remote writes       **/
#define	syslast		rcwrt	/* last sysinfo variable - used by sysrates() 
				   syslast define should be maintained as 
				   last non-array sysinfo variable */
};

#ifdef KERNEL
extern struct sysinfo sysinfo;
extern struct sysinfo sysrate;
extern struct sysinfo syshist;
#endif /* KERNEL */

struct syswait {
	short	iowait;
	short	physio;
};

#ifdef KERNEL
extern struct syswait syswait;
#endif /* KERNEL */

struct syserr {
	long	inodeovf;
	long	fileovf;
	long	textovf;
	long	procovf;
	long	sbi[5];
#define	SBI_SILOC	0
#define	SBI_CRDRDS	1
#define	SBI_ALERT	2
#define	SBI_FAULT	3
#define	SBI_TIMEO	4
};

#ifdef KERNEL
extern struct syserr syserr;
#endif /* KERNEL */

/*
 * The following structure defines the dump header which identifies the
 * start of a dump on the dump device.  It provides savecore with virtual
 * addresses of certain data items in the dump, and the disk locations
 * and sizes of the pieces of the dump.
 *
 * When adjusting DUMPINFO_MAX or DUMP_NPIECE_MAX, or adding members,
 * keep in mind that the struct dumpinfo must fit with in a DEV_BSIZE
 * byte disk block.
 */
#define OLD_DUMPINFO_SIGNATURE "!DuMpInFo!"
#define DUMPINFO_SIGNATURE "!DumPiNFo!"
#define DUMPINFO_MAX 16
#define X_DUMPDEV       0 /* obsolete */
#define X_DUMPLO        1 /* obsolete */
#define X_TIME          2
#define X_DUMPSIZE      3
#define X_VERSION       4
#define X_PANICSTR      5
#define X_DUMPMAG       6 /* obsolete */
#define X_MSGBUF        7
#define X_BLBUFPADR     8
#define X_BLBUF         9
#define X_PARTDUMPMAG   10 /* obsolete */
#define X_PARTDUMP      11 /* obsolete */
#define X_BOOTEDFILE    12

#define DUMP_NPIECE_MAX	16	/* currently 30 would fit */

/*
 * Begins exactly like an entire old dumpinfo structure (partial_dump,
 * signature, csum, addr), and savecore depends upon that.
 */
struct dumpinfo {
	long		partial_dump;
	char		signature[12];
	int		csum;
	void		*addr[DUMPINFO_MAX];
	struct dump_piece {	/* The pieces of the dump. */
		dev_t	dev;	/* Partition of this piece of the dump.	*/
		u_int	offset;	/* Offset in partition, disk blocks.	*/
		u_int	size;	/* Size of piece in disk blocks.	*/
	} piece[DUMP_NPIECE_MAX];
};


/*
 *	The following contains constants used with the getsysinfo() and
 *	setsysinfo() system calls.
 *
 *	Both of these calls are operation driven; particular
 *	flavors of operation may use arguments, identifiers, flags, etc.
 *	to define the actual result.
 *
 */

/***************************************************************************
 ***************************************************************************
 **  WARNING, HAZARD, WATCH OUT, NOTICE!!!!!!!!!!!!!!
 **
 ** Whenever adding a new GSI or SSI number look in both <sys/sysinfo.h>
 ** and <arch/alpha/hal/hal_sysinfo.h> to make sure that the function
 ** numbers remain unique!  The defines for GSI/SSI appear in these two
 ** header files and can not overlap, otherwise the hal variant would
 ** never be called!
 **
 ***************************************************************************
 **
 ** The GSI range <1:68> is randomly assigned to either <sys/sysinfo.h> or
 ** <arch/alpha/hal/hal_sysinfo.h>.  This random assignment is maintained
 ** to provide backward compatibility, however, in the future assignments
 ** for GSI in this file (<sys/sysinfo.h>) should be in the range 
 ** <69:100, 301:500>.  
 ** Assignments for <arch/alpha/hal/hal_sysinfo.h> will be in the range 
 ** <101:300>.
 **
 ** The SSI range <1:24> is randomly assigned to either<sys/sysinfo.h> or
 ** <arch/alpha/hal/hal_sysinfo.h>.  This random assignment is maintained
 ** to provide backward compatibility, however, in the future assignments
 ** for SSI in this file (<sys/sysinfo.h>) should be in the range
 ** <25:100, 301:500>.
 ** Assignments for <arch/alpha/hal/hal_sysinfo.h> will be in the range
 ** <101:300>.
 **
 ** The SSIN range for this file (<sys/sysinfo.h>) is <1:99>.
 ** Assignments for SSIN for <arch/alpha/hal/hal_sysinfo.h> will be in
 ** the range <100:199>.
 **
 ** If these ranges are ever exhausted, new ranges should be
 ** reserved via a comment similar to this in both files.
 **
 ***************************************************************************
 ***************************************************************************/


/*
 *	getsysinfo() operation types
 */

#define GSI_PROG_ENV	1	/* Return process compatibility mode of */
                                /* the process as defined in <sys/exec.h> */

#define GSI_MAX_UPROCS	2	/* Return the maximum number of processes */
                                /* allowed per user id */

#define	GSI_TTYP	3	/* Return the device number of the */
                                /* controlling terminal */

/* 			4	RESERVED for hal: GSI_NETBLK */

#define GSI_BOOTDEV	5	/* Return the bootdev string */
				/* which is used for install */


/* 
 * ULTRIX binary compatibility - On ULTRIX these return value of the flag 
 * that turns on/off printing the fixed up unaligned access message 
 */
#define GSI_UACSYS      6       /* get system wide flag */

#define GSI_UACPARNT    7	/* get parents */

#define GSI_UACPROC     8	/* get current proc */

#define GSI_LMF         9       /* License management facility (LMF) */

/*			10	RESERVED for hal: GSI_WSD_TYPE */
/*			11	RESERVED for hal: GSI_WSD_UNITS */

#define GSI_MMAPALIGN   12      /* support for mmap device drivers */

#if     defined(mips) || defined(__alpha)
/*
 * Returns network interface boot type
 */
#define GSI_BOOTTYPE    13      /* Network Interface boot type */
#endif

#define GSI_VPTOTAL     14      /* number of vector processors in system */

#define GSI_SCS         15      /* Systems Communications Services */

/*
 * Return value of the flags that control printing of
 * instruction emulation messages.
 */
#define	GSI_IECSYS	16	/* get system wide flag */

#define	GSI_IECPARNT	17	/* get parents */

#define	GSI_IECPROC	18	/* get current proc */

#define	GSI_PHYSMEM	19	/* Amount of physical memory in KB */

#define GSI_DNAUID	20	/* DNA UID genterator (UUID) */

/*			21	RESERVED for hal: GSI_BOOTCTLR */
/*			22 	RESERVED for hal: GSI_CONSTYPE */


/* All values from 1 - 22 are reserved. This is for compatibility */
/* with ULTRIX							  */

/*			23	RESERVED for hal: GSI_BUS_STRUCT */
/*                      24      RESERVED for hal: GSI_BUS_NAME */
/*                      25      RESERVED for hal: GSI_CTLR_STRUCT */
/*                      26      RESERVED for hal: GSI_CTLR_NAME */
/*                      27      RESERVED for hal: GSI_DEV_STRUCT */
/*                      28      RESERVED for hal: GSI_DEV_NAME */
/*                      29      RESERVED for hal: GSI_CPU */
/*                      30      RESERVED for hal: GSI_MAX_CPU */

#define GSI_ROOTDEV     31     /* root device */

#define GSI_DUMPDEV     32     /* dump device */

#define GSI_SWAPDEV     33     /* dump device */

/*                      34      RESERVED for hal: GSI_PRESTO */

#define GSI_COMPAT_MOD	35	/* return compat_mod struct	*/

/*                      36      RESERVED for hal: GSI_GRAPHICTYPE */
/*                      37      RESERVED for hal: GSI_TBD */
/*                      38      RESERVED for hal: GSI_SCS_SYSID */
/*                      39      RESERVED for hal: GSI_BUS_PNAME */
/*                      40      RESERVED for hal: GSI_CTLR_PNAME */

#define	GSI_STATIC_DEF	41	/* return Assign_entry struct	*/

#define	GSI_CLK_TCK	42	/* return system clock hz */

/*                      43      RESERVED for hal: GSI_WSD_CONS */
/*                      44      RESERVED for hal: GSI_BOOTEDFILE */
/*                      45      RESERVED for hal: GSI_IEEE_FP_CONTROL */
/*                      46      RESERVED for hal: GSI_IEEE_STATE_AT_SIGNAL */
/*                      47      RESERVED for hal: GSI_PROM_ENV */

#define GSI_IPRSETUP	48	/* return IP routing status for iprsetup */

#define GSI_DUMPINFO	49	/* return dump info for savecore utility */

/*                      50      RESERVED for hal: GSI_GRAPHIC_RES */
/*                      51      RESERVED for hal: GSI_LURT */
/*                      52      RESERVED for hal: GSI_KEYBOARD */
/*                      53      RESERVED for hal: GSI_POINTER */
 
#define GSI_CURRENT_CPU	54	/* processor currently running on */

#define GSI_CPUS_IN_BOX	55	/* number of processors in system */

/*                      56      RESERVED for hal: GSI_CONS_BOOTPATH */
/*                      57      RESERVED for hal: GSI_CONS_BOOTDEV */

#define GSI_SIGQ_MAX	58	/* number signals sigqueue() can post */

/*                      59      RESERVED for hal: GSI_CPU_INFO */
/*                      60      RESERVED for hal: GSI_PROC_TYPE */
/*                      61      RESERVED for hal: GSI_MODULE_LIST */

#define GSI_VERSIONSTRING 62	/* get version string */

#define GSI_DBASE	63	/* Data base request */

#define GSI_IPDEFTTL	64	/* get default IP TTL */

/*                      65      RESERVED for hal: GSI_LITE_SYSTEM */
/*                      66      RESERVED for hal: GSI_BYTEWORD_IO */

#define GSI_TIMER_MAX	67	/* get max number of realtime timers */

#define GSI_FD_NEWMAX   68	/* get extended fd support on/off status */
#define	GSI_PHYSMEM_START 69	/* get starting address of physical memory */
/*****************************************************************************
 **
 ** THE RANGE <101:300> IS RESERVED FOR USE IN <arch/alpha/hal/hal_sysinfo.h>  
 ** DO NOT USE THESE VALUES FOR GSI IN THIS FILE!
 **
 ** THE VALID RANGE FOR GSI IN THIS FILE IS <70:100, 301:500>.
 **
 ****************************************************************************/

/*                     101      RESERVED for hal: GSI_GET_HWRPB */
/*                     102      RESERVED for hal: GSI_DEV_TYPE */
/*                     103      RESERVED for hal: GSI_PLATFORM_NAME */
/*                     110      RESERVED for hal: GSI_FRU_TABLE_SIZE */
/*                     111      RESERVED for hal: GSI_FRU_TABLE */
/*                     112      RESERVED for hal: GSI_FIRMWARE_REV */
/*                     113      RESERVED for hal: GSI_PALCODE_REV */

/*
 *	setsysinfo() operation types
 */

#define	SSI_NVPAIRS	1	/* Use a list of name value pairs to modify */
                                /* pre-defined system variables */

#define	SSI_ZERO_STRUCT	2	/* Zero a pre-defined system structure */

#define	SSI_SET_STRUCT	3	/* Set a pre-defined system structure to */
                                /* supplied values */

/*                      4       AVAILABLE for sys: SSI_TBD */
/*                      5       AVAILABLE for sys: SSI_TBD */
/*                      6       AVAILABLE for sys: SSI_TBD */

#define SSI_LMF         7       /* License managment faciility (LMF) */

#define SSI_LOGIN       8       /* Identify caller as a login process */
                                /* (Sets SLOGIN flag in proc struct) */

#define SSI_SLIMIT      9      /* BVT */
#define SSI_ULIMIT     10      /* BVT */
#define SSI_DUMPDEV    11      /* Set dump device */

/*                     12       AVAILABLE for sys: SSI_TBD */
 
#define SSI_IPRSETUP    13      /* set IP routing status for iprsetup */

/*                     14       RESERVED for hal: SSI_IEEE_FP_CONTROL */
/*                     15       RESERVED for hal: SSI_IEEE_STATE_AT_SIGNAL */
/*                     16       RESERVED for hal: SSI_IEEE_IGNORE_STATE_AT_SIGNAL */
/*                     17       RESERVED for hal: SSI_PROM_ENV */

#define SSI_DBASE       18      /* Data base request */

#define SSI_IPDEFTTL    19      /* set default IP TTL */

/*                     20       RESERVED for hal: SSI_PROM_SAVE_ENV */

/*                     21       AVAILABLE for sys: SSI_TBD */
/*                     22       AVAILABLE for sys: SSI_TBD */
/*                     23       AVAILABLE for sys: SSI_TBD */


#define SSI_FD_NEWMAX   24      /* set extended fd support on/off */

/*****************************************************************************
 **
 ** THE RANGE <101:300> IS RESERVED FOR USE IN <arch/alpha/hal/hal_sysinfo.h>
 ** DO NOT USE THESE VALUES FOR SSI IN THIS FILE!
 **
 ** THE VALID RANGE FOR SSI IN THIS FILE IS <25:100, 301:500>.
 **
 ****************************************************************************/
 
/*
 *	setsysinfo() SSI_NVPAIRS variable names
 */

/* All values from 1 - 8 are reserved for compatibility with ULTRIX */

#define	SSIN_NFSPORTMON 1	/* A boolean which determines whether */
                                /* incoming NFS traffic is originating */
                                /* at a privileged port or not */

#define	SSIN_NFSSETLOCK	2	/* A boolean which determines whether NFS */
                                /* (daemon) style file and record locking */
                                /* is enabled or not */

#define SSIN_PROG_ENV	3	/* set prog environment, BSD, SYSV, POSIX */

/* see GSI_UACxxx */
#define SSIN_UACSYS	4	/* set system printing on/off */
#define SSIN_UACPARNT	5	/* set parent proc on/off */
#define SSIN_UACPROC	6	/* set current proc on/off */

/* see GSI_IECxxx */
#define SSIN_IECSYS	7	/* set system printing on/off */
#define SSIN_IECPARNT	8	/* set parent proc on/off */
#define SSIN_IECPROC	9	/* set current proc on/off */

/*****************************************************************************
 **
 ** THE RANGE <100:199> IS RESERVED FOR USE IN <arch/alpha/hal/hal_sysinfo.h>
 ** DO NOT USE THESE VALUES FOR SSIN IN THIS FILE!
 **
 ** THE VALID RANGE FOR SSIN IN THIS FILE IS <1:99>.
 **
 ****************************************************************************/


_BEGIN_CPLUSPLUS
extern int setsysinfo __((unsigned long, ...)) ;
extern int getsysinfo __((unsigned long, caddr_t, unsigned long, ...));
_END_CPLUSPLUS

#endif /* _SYS_SYSINFO_H_ */
