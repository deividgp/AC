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
 *	@(#)$RCSfile: poll.h,v $ $Revision: 4.2.14.6 $ (DEC) $Date: 1995/12/19 18:43:59 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _SYS_POLL_H_ 
#define _SYS_POLL_H_ 

/** Copyright (c) 1989  Mentat Inc.
 ** poll.h 1.1, last change 8/8/89
 **/
/*
 *	x0.8	Ajay Kachrani	Add no C poroto for poll() (QAR 1610)
 *
 */
/** Copyright (c) 1989  Mentat Inc.
 ** poll.h 1.1, last change 8/8/89
 **/

#include <standards.h>		/* define feature-test macros */

#if defined(_KERNEL)

#include <kern/queue.h>

#endif /* defined(_KERNEL) */

#if defined(_AES_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

/* Poll masks */
#define	POLLNORM	01	/* message available on read queue */

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
#define	POLLOUT		04      /* stream is writable */
#else
#define	POLLOUT		0404    /* stream is writable */
#endif

#define	POLLERR		010	/* error message has arrived */
#define	POLLHUP		020	/* hangup has occurred */
#define	POLLNVAL	040	/* invalid fd */
#define	POLLRDNORM	0100	/* A non-priority message is available */
#define	POLLRDBAND	0200	/* A band>0 message is available */

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
#define	POLLWRNORM		0400    /* Same as POLLOUT */
#else
#define	POLLWRNORM		0404    /* Same as POLLOUT for real */
#endif

#define	POLLWRBAND	01000	/* A priority band exists and is writable */
#define	POLLMSG		02000	/* A SIGPOLL message has reached the
				 * front of the queue */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#define	POLLIN		POLLNORM

#define	POLLPRI		02	/* priority message available */
#ifdef _OSF_SOURCE
#define	INFTIM		(-1)	/* infinite poll timeout */
#endif /* _OSF_SOURCE */
#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#if defined(_KERNEL)

/* kernel internal view of pollfd's */
struct pollfd {
#ifdef        __alpha
	int	fd;
	int	events;
	int	revents;
};
/* user view of pollfd's */
struct user_pollfd {
#endif	/* __alpha */
	int	fd;
	short	events;
	short	revents;
};
#else

/* array of streams to poll */
struct pollfd {
	int	fd;
	short	events;
	short	revents;
};

#endif

/* Required by Spec1170 - new type for number of file descriptors */
typedef	unsigned int	nfds_t;


/*
 * This was added to support the SVR4 style select entry point for
 * character drivers and the SVR4 pollwakeup call.
 *
 * A queue_entry structure is an OSF/1 data structure which roughly 
 * corresponds to an SVR4 pollhead structure.  
 */
#ifdef _OSF_SOURCE
typedef struct queue_entry pollhead;
#endif

#ifndef _KERNEL
#ifdef _NO_PROTO
extern int poll();
#else /* _NO_PROTO */
#ifdef __cplusplus
extern "C" {
#endif
extern int poll( struct pollfd[], nfds_t, int );
#ifdef __cplusplus
}
#endif
#endif /* _NO_PROTO */
#endif /* _KERNEL */

#endif /* _AES_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef _OSF_SOURCE

#define	NPOLLFILE	20

#endif /* _OSF_SOURCE */

#endif
