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
 * @(#)$RCSfile: processor.h,v $ $Revision: 1.1.4.4 $ (DEC) $Date: 1995/06/16 22:55:04 $
 */

/* 
 * This file exists to provides SVR4 compatibility.
 */

#ifndef _SYS_PROCESSOR_H
#define	_SYS_PROCESSOR_H

/*
 * CPU resource defines.
 */

/* bind_thread_to_cpu() thread defines */
#define ALL_THREADS     0       /* target all threads belonging to task */
/* bind_thread_to_cpu() flag defines */
#define BIND_INHERIT    0
#define BIND_NO_INHERIT	1       /* children will not inherit binding */

/* assign cpu_to_pset defines */
#define ANY_CPU		1	/* don't caare about cpu numbers */

/* bind_task_to_pset flag defines here */
#define PSET_EXCLUSIVE		1 /* Only this process can run on this pset */
#define PSET_NON_EXCLUSIVE 	2 /* Any process can run on this pset */

#ifndef _KERNEL

#include <sys/types.h>
#include <sys/procset.h>
#include <machine/cpuconf.h> 

/*
 * If "PSR_TEST" is set in the user environment, prsadm and processor_set
 * functions attempt log the transaction in wtmp by replacing a previous,
 * identical transaction.  The intent is that when stress testing takes place,
 * the wtmp file will not grow to multi-megabytes.
 */
#define PSR_TEST "PSR_TEST"

#define NCPUS	16

#define INVALID_PROCESSOR_SET_ID	-500
#define PROCESSOR_SET_ACTIVE		-501
#define	TOO_MANY_PROCESSORS		-502
#define	PROCESSOR_SET_IN_USE		-503
#define	PROCESSOR_SET_EXCLUSIVE_USE	-504

/*
 * Definitions for p_online and processor_info system calls.
 */

/*
 * Type for processor name (CPU number).
 */
typedef	int	processorid_t;

/*
 * Flags and return values for p_online(2), and pi_state for processor_info(2)
 */
#define	P_OFFLINE	1	/* offline cpu or cpu is offline */
#define	P_ONLINE	2	/* online cpu or cpu is online  */
#define	P_QUERY		3	/* request status */
#define	P_STATUS	P_QUERY	
#define P_BAD		4

/*
 * Structure for processor_info(2).
 *
 * The string fields are guaranteed to contain at least a NULL in the
 * zeroth position.
 *
 */
#define	PI_TYPELEN	32	/* size of CPU type string */
#define	PI_FPUTYPE	32	/* size of FPU types string */

typedef struct {
  int	pi_state;			/* P_ONLINE or P_OFFLINE */
  char	pi_processor_type[PI_TYPELEN];	/* ASCII CPU type */
  char	pi_fputypes[PI_FPUTYPE];	/* ASCII FPU types */
  int	pi_clock;			/* CPU clock freq in MHz */
#if defined(__SVE__)
} processor_info_t;
#else
} proc_info_t;
#endif /* __SVE__ */

/*
 * Binding values for processor_bind(2).
 */
#define	PBIND_NONE	-1	/* process thread is not bound */
#define	PBIND_QUERY	-2	/* don't set, just return the binding *
/

/*
 * User-level system call interface prototypes.
 */
/*
 * MP function definitions
 */
#ifndef _DEC
#if defined(__SVE__) || !defined(NO_SVR4_COMPAT)
#define processor_info(p,i)	__sve_processor_info((p),(i))
#define p_online(p,f)		__sve_p_online((p),(f))
#define processor_bind(i,id,p,o) __sve_processor_bind((i),(id),(p),(o))

extern int __sve_p_online	__((processorid_t processorid, int flag));
#if defined(__SVE__)
extern int __sve_processor_info	__((processorid_t processorid, 
				    processor_info_t *infop));
#else /* __SVE__ */
extern int __sve_processor_info	__((processorid_t processorid, 
				    proc_info_t *infop));
#endif /* __SVE__ */
extern int __sve_processor_bind	__((idtype_t idtype, id_t id, 
				    processorid_t processorid, 
				    processorid_t *obind));
#endif /* __SVE__ */

#endif /* _DEC */
#endif /* _KERNEL */
#endif	/* _SYS_PROCESSOR_H */


