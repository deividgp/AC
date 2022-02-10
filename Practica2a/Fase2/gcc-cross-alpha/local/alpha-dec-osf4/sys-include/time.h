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
 *	@(#)$RCSfile: time.h,v $ $Revision: 4.3.22.2 $ (DEC) $Date: 1996/09/24 13:08:24 $
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
 * COMPONENT_NAME: time.h
 *                                                                    
 * Copyright International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the Rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 * 
 *	time.h   1.23  com/inc,3.1,9013 1/18/90 09:56:02 
 */                                                                   

#ifndef _TIME_H_
#define _TIME_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

/*
 *
 *      The ANSI standard requires that certain values be in time.h.
 *      It also requires that if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present.
 *
 *      This header includes all the ANSI required entries.  In addition
 *      other entries for the XIX system are included.
 *
 */
#ifdef _ANSI_C_SOURCE

#include <machine/machtime.h>		/* for CLOCKS_PER_SEC */

/* The following definitions are required to be in time.h by ANSI */

#ifndef NULL
#define NULL 	0L
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long 	size_t;
#endif

#ifndef _CLOCK_T
#define _CLOCK_T
typedef int		clock_t;
#endif

#ifndef _TIME_T
#define _TIME_T
typedef int		time_t;
#endif

struct	tm {			/* see ctime(3) */
        int     tm_sec;         /* seconds after the minute [0-60] */
        int     tm_min;         /* minutes after the hour [0-59] */
        int     tm_hour;        /* hours since midnight [0-23] */
        int     tm_mday;        /* day of the month [1-31] */
        int     tm_mon;         /* months since January [0-11] */
        int     tm_year;        /* years since 1900 */
        int     tm_wday;        /* days since Sunday [0-6] */
        int     tm_yday;        /* days since January 1 [0-365] */
        int     tm_isdst;       /* Daylight Savings Time flag */
#ifdef _OSF_SOURCE
        long    tm_gmtoff;
        char    *tm_zone;
#else
	long    __tm_gmtoff;
        char    *__tm_zone;
#endif	
};

#ifdef _OSF_SOURCE
#define __tm_gmtoff tm_gmtoff
#define __tm_zone   tm_zone
#endif

extern clock_t 	clock __((void));
extern double 	difftime __((time_t , time_t ));
extern time_t 	mktime __((struct tm *));
extern time_t 	time __((time_t *));
extern char 	*asctime __((const struct tm *));
extern char 	*ctime __((const time_t *));
extern struct tm *gmtime __((const time_t *));
extern struct tm *localtime __((const time_t *));
extern size_t 	strftime __((char *, size_t , const char *,const struct tm *));

/* REENTRANT FUNCTIONS */
#if _POSIX_C_SOURCE>=199506L

#ifndef	_LIBC_POLLUTION_H_
#ifdef  __DECC
#pragma extern_prefix "_P"
#else
#define	asctime_r(__a,__b)	_Pasctime_r(__a,__b)
#define	ctime_r(__a,__b)	_Pctime_r(__a,__b)
#define	gmtime_r(__a,__b)	_Pgmtime_r(__a,__b)
#define	localtime_r(__a,__b)	_Plocaltime_r(__a,__b)
#endif	/* __DECC */
#endif	/* !_LIBC_POLLUTION_H_ */
extern char * __P_C(asctime_r) __((const struct tm *, char *));
extern char * __P_C(ctime_r) __((const time_t *, char *));
extern struct tm * __P_C(gmtime_r) __((const time_t *, struct tm *));
extern struct tm * __P_C(localtime_r) __((const time_t *, struct tm *));
#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix ""
#endif	/* __DECC */
#endif	/* _LIBC_POLLUTION_H_ */

#else	/* P1003.1c */

#if defined(_THREAD_SAFE) || defined(_REENTRANT)
extern int 	asctime_r __((const struct tm *, char *, int));
extern int	ctime_r __((const time_t *, char *, int));
extern int	gmtime_r __((const time_t *, struct tm *));
extern int 	localtime_r __((const time_t *, struct tm *));
#endif

#endif	/* P1003.1c */

#endif /*_ANSI_C_SOURCE */
 
/*
 *   The following are values that have historically been in time.h.
 *
 *   They are NOT part of the ANSI defined time.h and therefore are
 *   not included when _ANSI_C_SOURCE is defined.
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)

#include <sys/types.h>

#ifndef CLK_TCK
#define CLK_TCK   60       /* clock ticks/second, >= 10 */
#endif

/*
 * POSIX 1003.1b Clocks and Timers constants are now defined in <time.h>,
 * not <sys/timers.h>. For compatibility with earlier drafts, they
 * will continue to live in <timers.h> and be included indirectly
 * here.
 */
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)
#include <sys/timers.h>
#define MAX_SECONDS LONG_MAX
#define NSEC_PER_USEC (1000)
#define NSEC_PER_SEC (1000000000)
#define TIMER_ABS 1
#define TIMER_ABSTIME 0x00000001
#define CLOCK_REALTIME 1
#endif	/* _POSIX_C_SOURCE >= 199309L */
#endif  /* _POSIX_C_SOURCE >= 1 */

extern char *tzname[];

extern void tzset __((void));

#ifdef _XOPEN_SOURCE
#ifndef _BSD
#ifdef _SVID3_COMPAT
extern time_t timezone;
#else
extern long timezone;
#endif /* _SVID3_COMPAT */
#endif /* ! _BSD */
extern int daylight;

extern char *strptime __((const char *, const char *, struct tm *));

#endif /* _XOPEN_SOURCE */

#ifdef _XOPEN_SOURCE_EXTENDED
extern struct tm *getdate __((const char *));
extern int getdate_err;
#endif

#ifdef _OSF_SOURCE

#define TIMELEN 26
#define TMZNLEN 50

#define TM_GMTOFF       tm_gmtoff
#define TM_ZONE         tm_zone

#ifndef RTPC_NO_NLS
/*  Suggested default length of time/date buffer */
#define NLTBMAX	64

extern unsigned char *NLctime __((long *));
extern unsigned char *NLasctime __((struct tm *));
extern char *NLstrtime __((char *, size_t , const char *, const struct tm *));
#ifndef _XOPEN_SOURCE_EXTENDED
extern struct tm *getdate __((char *));
extern int getdate_err;
#endif
#if defined(_THREAD_SAFE) || defined(_REENTRANT)
struct tm *getdate_r __((char *, struct tm *, int *));
#endif

#endif /* RTPC_NO_NLS */

#endif /* _OSF_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _TIME_H_ */
