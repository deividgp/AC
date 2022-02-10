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
 *	@(#)$RCSfile: timers.h,v $ $Revision: 4.2.13.6 $ (DEC) $Date: 1995/10/30 21:48:39 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _SYS_TIMERS_H
#define _SYS_TIMERS_H
#if defined(__cplusplus)
extern "C"
{
#endif

#include <sys/sysmisc.h>

#ifdef POSIX_4D9
#include <sys/types.h>
#define TIMEOFDAY	1		/* time of day clock type */
struct itimerspec {
	struct timespec	it_interval;	/* timer period */
	struct timespec	it_value;	/* timer expiration */
};

struct itimercb {
#ifdef _POSIX_ASYNCHRONOUS_EVENTS
	struct event	itcb_event;	/* timer event definition */
#endif
	int		itcb_count;	/* timer "overrun" count */
};


/*
 * Notification types
 */
#define DELIVERY_SIGNALS	1
#define DELIVERY_EVENTS		2

#ifdef nanosleep
#undef nanosleep
#endif
#define nanosleep(rqtp,rmtp)   nanosleep_d9(rqtp,rmtp)
/*
 * Functions
 */
int getclock(int clock_type, struct timespec *tp);
int setclock(int clock_type, struct timespec *tp);
int resclock(int clock_type, struct timespec *res, struct timespec *maxval);
timer_t mktimer(int clock_type, int notify_type, void *reserved);
int rmtimer(timer_t timerid);
int gettimer(timer_t timerid, struct itimerspec *value);
int reltimer(timer_t timerid, struct itimerspec *value, struct itimerspec *ovalue);
int abstimer(timer_t timerid, struct itimerspec *value, struct itimerspec *ovalue);
int resrel(timer_t timerid, struct timespec *res, struct timespec *max);
int resabs(timer_t timerid, struct timespec *res, struct timespec *max);
int nanosleep_d9(struct timespec *rqtp, struct timespec *rmtp);
int ressleep(struct timespec *res, struct timespec *max);

#elif defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) 

/* 
 * Constants and Macros
 */

#define TIMEOFDAY	1	/* time of day clock type */

typedef int             clockid_t;

/*
 * Data Structure Definitions
 */

/*
 * The maximum timeout value, in seconds, allowed for an P1003.4
 * interval timers.
 */

struct	itimerspec {
	struct		timespec it_interval; /* timer interval */
	struct		timespec it_value; /* current value */
};

/* 
 * useful macros,  note these are not defined by P1003.4
 */

#define	nsec_timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_nsec)
#define	nsec_timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_nsec = 0

/*
 * Compare two nano_second timers.  Not this only works for
 * <, > or = but not for any conbination of the two.
 */

#define	nsec_timercmp(tvp, fvp, cmp)			        	\
	((tvp)->tv_sec cmp (fvp)->tv_sec ||				\
	(tvp)->tv_sec == (fvp)->tv_sec &&				\
	(tvp)->tv_nsec cmp (fvp)->tv_nsec)

/* 
 * routine definitions
 */

int clock_gettime __((clockid_t clock_id, struct timespec *tp));
int clock_settime __((clockid_t clock_id, const struct timespec *tp));
int clock_getdrift __((int clock_id, int *oppb));
int clock_setdrift __((int clock_id, const int ppb, int *oppb));
int timer_create __((clockid_t clock_id, struct sigevent *evp, 
		     timer_t *timer_created));
int timer_delete __((timer_t timerid));
int timer_gettime __((timer_t timerid, struct itimerspec *value));
int timer_settime __((timer_t timerid, int flags,
		      const struct itimerspec *value, 
		      struct itimerspec *ovalue));
int timer_getoverrun __((timer_t timerid));
int nanosleep __((const struct timespec *rqtp, struct timespec *rmtp));
int clock_getres __((clockid_t clock_id,struct timespec *res));

#endif  /* _POSIX_C_SOURCE */
#if defined(__cplusplus)
}
#endif
#endif	/* _SYS_TIMERS_H */
