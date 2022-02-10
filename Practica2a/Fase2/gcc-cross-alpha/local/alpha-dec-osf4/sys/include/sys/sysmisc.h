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
 * @(#)$RCSfile: sysmisc.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1996/12/03 21:49:47 $
 */

#ifndef _SYS_SYSMISC_H
#define _SYS_SYSMISC_H
#if defined(__cplusplus)
extern "C"
{
#endif

#include <sys/types.h>

#if defined(__LANGUAGE_C__) || defined(__cplusplus)

#if defined(_OSF_SOURCE) || ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) ) || defined(_XOPEN_SOURCE_EXTENDED) 


/*
 * SVID3 version of the stack structure - used by sigaltstack
 */
#ifndef _XOPEN_SOURCE_EXTENDED
typedef struct  sigaltstack {
        caddr_t ss_sp;                  /* signal stack pointer */
#else
typedef struct {
        void    *ss_sp;                 /* signal stack pointer */
#endif
        int     ss_flags;		/* current status */
        size_t	ss_size;		/* size of stack - 0 if unknown */
} stack_t;
#endif /*_OSF_SOURCE || _POSIX_C_SOURCE || _XOPEN_SOURCE_EXTENDED */


#if defined(_OSF_SOURCE) || ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) )
/*
 * sigval union and sigevent structure needed by Async I/O and Timer routines.
 * Defines values passed to signal handlers on I/O completion or timer
 * expiration.
 */
typedef union sigval {
	int 	sival_int;
	void	*sival_ptr;
} sigval_t;

/* sigevent defintions */
#define SIGEV_SIGNAL (0)	/* Notify via signal */
#define SIGEV_NONE   (1)	/* Other notification: unsupported */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L) 
#define SIGEV_THREAD (2)	/* Deliver via thread creation */
#endif /* _POSIX_C_SOURCE >= 199506L */

#define SIGEV_MAX_SIZE	(64)
#define SIGEV_PAD_SIZE ((SIGEV_MAX_SIZE/sizeof(int)) - 4)

typedef struct sigevent_event {
	union sigval	_sigev_value;	/* application-defined value */
	int		_sigev_signo;	/* signal to raise */
	int		_sigev_notify;	/* raise a signal? */
} sigevent_event_t;

typedef struct sigevent {
	sigevent_event_t  	_sigev_sigevent;
	union {
		int 		_sigev[SIGEV_PAD_SIZE];

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L) 
		struct {
			/*
			 * These fields appear only when compiling
			 * for threaded applications. See SIGEV_THREAD
			 * above.
			 */
			void (*_sigev_notify_function) __((sigval_t));
			pthread_attr_t *_sigev_notify_attributes;
		} _sigev_un_s;
#endif /* _POSIX_C_SOURCE >= 199506L */
	} _sigev_un;
} sigevent_t;

/*
 * Sigevent struct access macros.
 */
#define sigev_value	_sigev_sigevent._sigev_value
#define sigev_signo	_sigev_sigevent._sigev_signo
#define sigev_notify	_sigev_sigevent._sigev_notify

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L) 
#define sigev_notify_function	_sigev_un._sigev_un_s._sigev_notify_function
#define sigev_notify_attributes _sigev_un._sigev_un_s._sigev_notify_attributes
#endif /* _POSIX_C_SOURCE >= 199506L */

/*
 * Define some nonstandard shortcuts to reference the union fields...
 */
#define sigev_int sigev_value.sival_int
#define sigev_ptr sigev_value.sival_ptr

/* timespec definition */
typedef struct timespec {
        time_t  tv_sec;         /* seconds */
        long    tv_nsec;        /* nanoseconds */
} timespec_t;

/*
 * Internal profiling arguments.
 */
struct uuprof {			/* profile arguments */
	short		*pr_base;	/* buffer base */
	unsigned long	pr_size;	/* buffer size */
	unsigned long	pr_off;		/* pc offset */
	unsigned long	pr_scale;	/* pc scaling */
};

#endif /* _OSF_SOURCE || _POSIX_C_SOURCE */

#endif /* __LANGUAGE_C__ || __cplusplus */

#if defined(__cplusplus)
}
#endif
#endif /* _SYS_SYSMISC_H */
