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
 *	@(#)$RCSfile: resource.h,v $ $Revision: 4.2.14.6 $ (DEC) $Date: 1995/10/16 19:37:02 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */

#ifndef	_SYS_RESOURCE_H_
#define _SYS_RESOURCE_H_

#include <sys/time.h>
#include <sys/types.h>
#include <standards.h>

/*
 * Process priority specifications to get/setpriority.
 */
#define PRIO_MIN	-20
#define PRIO_MAX	20

#define PRIO_PROCESS	0
#define PRIO_PGRP	1
#define PRIO_USER	2

/*
 * CPU resource defines.
 */
#ifdef _OSF_SOURCE	/* Hide from Spec1170 name space */

/* bind_thread_to_cpu() thread defines */
#define	ALL_THREADS 	0	/* target all threads belonging to task */
/* bind_thread_to_cpu() flag defines */
#define BIND_NO_INHERIT	1	/* children will not inherit binding */

#endif	/* _OSF_SOURCE */

/*
 * Resource utilization information.
 */

#define RUSAGE_THREAD	1
#define RUSAGE_SELF	0
#define RUSAGE_CHILDREN	-1

struct	rusage {
	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
	long	ru_maxrss;
#define ru_first	ru_ixrss
	long	ru_ixrss;		/* integral shared memory size */
	long	ru_idrss;		/* integral unshared data " */
	long	ru_isrss;		/* integral unshared stack " */
	long	ru_minflt;		/* page reclaims - total vmfaults */
	long	ru_majflt;		/* page faults */
	long	ru_nswap;		/* swaps */
	long	ru_inblock;		/* block input operations */
	long	ru_oublock;		/* block output operations */
	long	ru_msgsnd;		/* messages sent */
	long	ru_msgrcv;		/* messages received */
	long	ru_nsignals;		/* signals received */
	long	ru_nvcsw;		/* voluntary context switches */
	long	ru_nivcsw;		/* involuntary " */
#define ru_last		ru_nivcsw
};
#define ru_totflt		ru_minflt

#ifdef _KERNEL
/* Note: page reclaims ( totflt - majflt)*/
struct	thread_rusage {
	int	tru_totflt;		/* total vm faults */
	int	tru_majflt;		/* pagin faults */
	int	tru_inblock;		/* block input operations */
	int	tru_oublock;		/* block output operations */
	int	tru_msgsnd;		/* messages sent */
	int	tru_msgrcv;		/* messages received */
	int	tru_nsignals;		/* signals received */
	int	tru_nvcsw;		/* voluntary context switches */
	int	tru_nivcsw;		/* involuntary " */
};
#endif /* _KERNEL */

/*
 * Resource limits
 */
#define RLIMIT_CPU	0		/* cpu time in seconds */
#define RLIMIT_FSIZE	1		/* maximum file size */
#define RLIMIT_DATA	2		/* data size */
#define RLIMIT_STACK	3		/* stack size */
#define RLIMIT_CORE	4		/* core file size */
#define RLIMIT_RSS	5		/* resident set size */
#define RLIMIT_NOFILE	6		/* open files */
#define RLIMIT_AS	7		/* address space */
#define RLIMIT_VMEM	RLIMIT_AS	/* V.4 alias for AS */

#if defined(__alpha)
#define	RLIM_INFINITY	0x7fffffffffffffffL
#else /* !defined(__alpha) */
#define	RLIM_INFINITY	0x7fffffff
#endif /* defined(__alpha) */

#define RLIM_NLIMITS	8		/* number of resource limits */

struct rlimit {
	rlim_t	rlim_cur;		/* current (soft) limit */
	rlim_t	rlim_max;		/* maximum value for rlim_cur */
};


#ifdef _OSF_SOURCE
/*
 *  Special rusage structure returned with WLOGINDEV option to wait3().
 */

struct rusage_dev {
	struct rusage ru_rusage;
	dev_t	      ru_dev;
};

/*
 *  Resource pause system call definitions
 */

#define RPAUSE_SAME	0		/* leave state unchanged */
#define RPAUSE_DISABLE	1		/* disable pause on error type(s) */
#define RPAUSE_ENABLE	2		/* enable pause on error type(s) */

#define RPAUSE_ALL	0x7fffffff	/* all error number types */

#endif	/* _OSF_SOURCE */

#ifndef _KERNEL
_BEGIN_CPLUSPLUS
#ifdef _XOPEN_SOURCE_EXTENDED
extern int getpriority __((int, id_t));
extern int setpriority __((int, id_t, int));

#if !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define setrlimit(__a,__b) _Esetrlimit(__a,__b)
#endif
#endif /* !_LIBC_POLLUTION_H_ */

extern int __R(setrlimit) __((int, const struct rlimit *));

#if !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* !_LIBC_POLLUTION_H_ */

#else	/* _OSF_SOURCE */
extern int getpriority __((int, int));
extern int setpriority __((int, int, int));
extern int setrlimit __((int, struct rlimit *));
#endif
extern int getrlimit __((int, struct rlimit *));
extern int getrusage __((int, struct rusage *));
_END_CPLUSPLUS
#endif	/* _KERNEL */

#ifdef _OSF_SOURCE
#define TIME_MICROS_MAX	(1000000)

#define ru_thread_time_add(result, addend)		{		\
	(result)->tv_usec += (addend)->microseconds;			\
	(result)->tv_sec += (addend)->seconds;			\
	if ((result)->tv_usec >= TIME_MICROS_MAX) {		\
	    (result)->tv_usec -= TIME_MICROS_MAX;		\
	    (result)->tv_sec++;					\
	}							\
}
#endif	/* _OSF_SOURCE */

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)

#define PROFIL_MAX 64 

/*
 * Structure needed to allow profiling of a number of non-contiguous
 * address ranges.  An array of these is found in the user's space at
 * the location specified by the first arguement to profile, normally
 * the address of the single profiling buffer, when the second
 * arguement, normally the buffer size, is -1. The array is terminated
 * according to a count passed second argument. The maximum number
 * of elements if PROFIL_MAX
 */
struct profil_args {
	unsigned int 	*buffer; /* User buffer address */
	void		*highpc; /* Last PC profiled in last buffer slot */
	void		*lowpc;  /* 1st PC profiled in 1st buffer slot */
	unsigned long 	scale; 	 /* How many PC's per slot * 0x10000 */
};

/*
 * There are some values of scale which have special meaning, rather than
 * being scales.  They are all crowded at the small scale region, i.e.;
 * many buckets per instruction, so they are unlikely to be missed.
 */
#define PROFIL_SCALE_TOTAL	2 /* record every tick in first slot */
#define PROFIL_SCALE_STOP_1	1 /* (with DELTA) stop profiling offset */
#define PROFIL_SCALE_STOP	0 /* Same as STOP_1 */

/*
 * When the second arguement to profile is -1 (see above), the fourth is
 * a flags arguement.  Here are legal components of its value:
 */
#define PROFIL_FLAGS_ALL_THREADS 1 /* rather than just caller's thread */

#endif /* !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE) */

#endif	/* _SYS_RESOURCE_H_ */
