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
 *	@(#)$RCSfile: sched.h,v $ $Revision: 4.2.13.3 $ (DEC) $Date: 1997/01/13 21:30:20 $
 */
/*
 */
/*
 * sched.h
 *
 * POSIX 1003.1b Scheduling Interface definitions.
 */

#ifndef _SCHED_H_
#define _SCHED_H_ 1

#if defined(__cplusplus)
extern "C"
{
#endif

#include <standards.h>

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)

#include <sys/types.h>
#include <sys/timers.h>

/*
 * POSIX 1003.1b scheduling policies:
 *
 *   SCHED_FIFO		First-In-First-Out (defined by 1003.1b).
 *   SCHED_RR		Round-Robin (defined by 1003.1b).
 *   SCHED_OTHER	Standard Timesharing Policy (allowed by 1003.1b).
 */

#define SCHED_FIFO 1
#define SCHED_RR 2
#define SCHED_OTHER 3

/*
 * DECthreads scheduling policies
 *
 *   SCHED_FG_NP	"Foreground" (Timeshare)
 *   SCHED_BG_NP	"Background"
 *   SCHED_LFI_NP	"Low FIFO" (background FIFO)
 *   SCHED_LRR_NP	"Low RR" (background RR)
 */

#define SCHED_FG_NP	SCHED_OTHER
#define SCHED_BG_NP	(SCHED_OTHER+1)
#define SCHED_LFI_NP	(SCHED_OTHER+2)
#define SCHED_LRR_NP	(SCHED_OTHER+3)

/*
 * Define the smallest and the largest value that the policy can assume.
 */

#define _SCHED_MIN	SCHED_FIFO
#define _SCHED_MAX	SCHED_LRR_NP


/*
 * POSIX 1003.1b scheduling parameters.
 */

struct sched_param {
  int sched_priority;          	/* Scheduling priority. */
};


/*
 * POSIX 1003.1b scheduling function prototypes.
 */

int sched_setparam __((pid_t pid, struct sched_param *param));
int sched_getparam __((pid_t pid, struct sched_param *param));
int sched_setscheduler __((pid_t pid, int policy, struct sched_param *param));
int sched_getscheduler __((pid_t pid));
int sched_yield __((void));
int sched_get_priority_max __((int policy));
int sched_get_priority_min __((int policy));
int sched_rr_get_interval __((pid_t pid, struct timespec *min));

/*
 * The following constants are NOT defined by POSIX 1003.1b.  However, the
 * prefix SCHED_ is reserved for POSIX implementations, so it is alright to
 * define these when _POSIX_C_SOURCE is on (that is, >= 199309L).
 *
 * These constants define priority ranges for various classes of application.
 * There are three classes of application: user (non-time critical), system
 * (more important than user, but still not highly time critical), and
 * realtime (highly time-critical).  Each class has a minimum and maximum
 * priority.  The minimum priority is the lowest priority which will not suffer
 * from interference by lower priority classes.  The maximum priority is the
 * highest priority which should be given to an application of this class.
 *
 * Note that these constants are advisory in nature, and there are no
 * mechanisms for testing or enforcing their validity.
 *
 * These constants may be useful for application developers who want to find
 * a particular part of the priority range to run in.  When porting to other
 * POSIX 1003.1b implementations, the developer will have to define these
 * constants.  For example, an application could do the following:
 *
 *	#include <sched.h>
 *	#ifndef SCHED_PRIO_RT_MIN
 *	#define SCHED_PRIO_RT_MIN sched_get_priority_min(SCHED_FIFO)
 *	#endif
 *
 *	main()
 *	{
 *	  int min_pri = SCHED_PRIO_RT_MIN;
 *
 *	  ...
 *	}
 */
#define SCHED_PRIO_RT_MAX 63
#define SCHED_PRIO_RT_MIN 32
#define SCHED_PRIO_SYSTEM_MAX 31
#define SCHED_PRIO_SYSTEM_MIN 20
#define SCHED_PRIO_USER_MAX 19
#define SCHED_PRIO_USER_MIN 0

#define SCHED_PRIO_BG_MAX 13
#define SCHED_PRIO_LFI_MAX 13
#define SCHED_PRIO_LRR_MAX 13

#endif /* _POSIX_C_SOURCE */

#if defined(__cplusplus)
}
#endif

#endif /* _SCHED_H_ */
