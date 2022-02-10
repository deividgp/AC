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
 *	@(#)$RCSfile: time.h,v $ $Revision: 4.4.52.2 $ (DEC) $Date: 1998/01/23 17:11:32 $
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

#ifndef	_SYS_TIME_H_
#define _SYS_TIME_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#ifdef	_KERNEL
#include <sys/unix_defs.h>
#endif

#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
#include <sys/limits.h>
#endif
#include <sys/types.h>

struct timeval {
	time_t	tv_sec;		/* seconds */
	int	tv_usec;	/* microseconds */
		/* the type of the tv_usec field may be replaced by   */
		/* useconds_t in the next rev of XPG4 based on waiver */
};

struct	itimerval {
	struct		timeval it_interval; /* timer interval */
	struct		timeval it_value; /* current value */
};

#ifdef _OSF_SOURCE
#include <sys/signal.h>
#endif

#ifdef  _KERNEL
/*
 * Structure returned by gmtime and localtime calls (see ctime(3)).
 */
struct tm {
        int     tm_sec;
        int     tm_min;
        int     tm_hour;
        int     tm_mday;
        int     tm_mon;
        int     tm_year;
        int     tm_wday;
        int     tm_yday;
        int     tm_isdst;
	long    tm_gmtoff;
        char    *tm_zone;
};
#else   /* _KERNEL  */
#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
#include <time.h>
#endif
#endif  /*  _KERNEL  */

/*
 * The rest of this file is the interface to the BSD timer services.
 * Most of these services are implemented as subroutines that convert
 * the interface to the corresponding POSIX timer service.
 */

/*
 * The following are the BSD labels for the timer types.
 */
#define	ITIMER_REAL		0	/* Real time */
#define	ITIMER_VIRTUAL		1	/* Per-process time */
#define	ITIMER_PROF		2	/* Per-process user time */

 /*
  * Make timer interval for BSD "ITIMER_REAL"
  * timers and sleep functions.
  */

#ifdef _OSF_SOURCE
#define TOD_MAX_SECONDS 100000000

/*
 * Operations on timevals.
 *
 * Note that timercmp only works for cmp values of !=, >, and <.
 */
#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0
#define	timercmp(tvp, fvp, cmp)						\
	((tvp)->tv_sec cmp (fvp)->tv_sec ||				\
	 (tvp)->tv_sec == (fvp)->tv_sec &&				\
	 (tvp)->tv_usec cmp (fvp)->tv_usec)
#endif /* _OSF_SOURCE */

#ifdef _OSF_SOURCE
/*
 * The following provides a way to convert the current time in GMT
 * to a local time.
 */
struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};

#define DST_NONE	0	/* not on dst */
#define DST_USA		1	/* USA style dst */
#define DST_AUST	2	/* Australian style dst */
#define DST_WET		3	/* Western European dst */
#define DST_MET		4	/* Middle European dst */
#define DST_EET		5	/* Eastern European dst */
#define DST_CAN		6	/* Canada */
#endif /* _OSF_SOURCE */

#ifndef _KERNEL

#ifdef _OSF_SOURCE
extern int adjtime __((struct timeval *, struct timeval *));
extern int settimeofday __((struct timeval *, struct timezone *));
#endif

#ifdef _XOPEN_SOURCE_EXTENDED

extern int gettimeofday __((struct timeval *, void *));

extern int utimes __((const char *, const struct timeval *));
extern int setitimer __((int, const struct itimerval *, struct itimerval *));
#else
extern int setitimer __((int, struct itimerval *, struct itimerval *));
extern int gettimeofday __((struct timeval *, struct timezone *));
extern int utimes __((const char *, struct timeval *));
#endif
extern int getitimer __((int, struct itimerval *));

#include <sys/select.h>

#endif  /* _KERNEL */


#ifdef	_KERNEL

udecl_simple_lock_data(extern,callout_lock)
#define	TIME_LOCK()		usimple_lock(&callout_lock)
#define	TIME_UNLOCK()		usimple_unlock(&callout_lock)

#ifdef __alpha

/*
 * Access to the global variables "time" and "tz" on alpha can be done in a 
 * single 64-bit bus cycle.  This allows reading of the whole timeval
 * or timezone structures without locking or manipulating the spl level.
 * However, arguments to the 6 macros below are required to be simple 
 * timeval/timezone variables (either * global or auto), that is, they must
 * not be fields of another structure  or indirection on pointers to timeval 
 * structures. This works because the alpha compiler will (currently) 
 * quad-align both the global "time" and  "tz" and the macro argument.
 */

#define	TIME_READ(t)		*(long *)&t = *(long volatile *)&time
#define	TIME_LOAD(t)		*(long *)&t = *(long volatile *)&time
#define	TIME_STORE(t)		*(long volatile *)&time = *(long *)&t

#define	TZ_READ(t)		*(long *)&t = *(long volatile *)&tz
#define	TZ_LOAD(t)		*(long *)&t = *(long volatile *)&tz
#define	TZ_STORE(t)		*(long volatile *)&tz = *(long *)&t

#else /* __alpha */

#define	TIME_READ(t)		do { \
					int s = splclock(); \
					TIME_LOCK(); \
					t = time; \
					TIME_UNLOCK(); \
					splx(s); \
				} while (0)
#define	TIME_LOAD(t)		t = time
#define	TIME_STORE(t)		time = t

#define	TZ_READ(t)		do { \
					int s = splclock(); \
					TIME_LOCK(); \
					t = tz; \
					TIME_UNLOCK(); \
					splx(s); \
				} while (0)
#define	TZ_LOAD(t)		t = tz
#define	TZ_STORE(t)		tz = t

#endif /* __alpha */

#define MAX_SECONDS LONG_MAX
#define NSEC_PER_USEC (1000)
#define NSEC_PER_SEC (1000000000)
#ifndef TIMER_ABS
#define TIMER_ABS 1
#endif
#ifndef TIMER_ABSTIME
#define TIMER_ABSTIME 0x00000001
#endif
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 1
#endif
extern	int	microsecond_time;	/* MICRO_TIME configured? */
extern	void	micro_time(struct timeval *);
#define	MICROTIME(t)	{ \
			if (microsecond_time) \
				micro_time((t)); \
			else \
				microtime((t)); \
			}

#endif	/* _KERNEL */

#ifdef _KERNEL
/* 
 * P1003.1b Timer structures.
 */
typedef struct psx4_timer_struct {
	int		psx4t_tid;	/* Timer's own ID */
	int		psx4t_overrun; 	/* timeout overrun count */
	int		psx4t_overran;	/* timeout overrun count */
#define PSX4T_CPU    0xff
#define PSX4T_ACTIVE 0x100
#define PSX4T_ABORT  0x200
#define PSX4T_ABSTIME 0X400
	volatile unsigned int	psx4t_flags; /* timer active, etc. */
	struct itimerval psx4t_timeval;	/* timeout and interval values */
	void     	*psx4t_p_proc;	/* pointer to proc/thread sig later */
	sigqueue_t	psx4t_sigqueue; /* pointer to our queue entry */
} psx4_timer_t;

typedef struct tid_array {
	int	     	psx4_gen;
	int		psx4_next;
	psx4_timer_t 	*psx4_timerp;
} psx4_tid_t;

typedef struct psx4_tblock_struct {
        int		psx4_free;
	int		psx4_count;
	int		psx4_max;
	psx4_tid_t 	psx4_timers[1];
} psx4_tblock_t;

#define PSX4_TIMER_HSIZE (sizeof(psx4_tblock_t) - sizeof(psx4_tid_t))

#endif 	/* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_TIME_H_ */
