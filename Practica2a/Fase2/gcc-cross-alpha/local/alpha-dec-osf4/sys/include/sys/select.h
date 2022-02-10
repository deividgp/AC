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
 *	@(#)$RCSfile: select.h,v $ $Revision: 4.2.13.5 $ (DEC) $Date: 1995/08/15 18:14:27 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1988 Encore Computer Corporation
 * All rights reserved.
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef	_SYS_SELECT_H_
#define	_SYS_SELECT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#ifdef	_KERNEL
#include <kern/event.h>
#include <kern/queue.h>

/*
 * Problems with select in a parallelized Unix environment.
 *
 * The existing BSD select mechanism, a set of variable contained in
 * each selectable object and a set of global variables to handle
 * "select collisions" does not work well in a parallelized Unix kernel.
 * First, there is the obvious race between one thread attempting to
 * set itself up to be notified of a change in the state of a selectable
 * object and another thread attempting to signal that a selectable
 * object's state has just changed.
 *
 * Second, and more insidious, is the problem of the task's file descriptor
 * array changing during the select due to the action of another thread
 * within the task.  For example, at the time thread A initiates a select()
 * operation, file descriptor X could be open and specified as part of one
 * of the select masks.  Thread A might then sleep, waiting for one of the
 * select'ed objects to change state.  In the meantime, thread B might close
 * file descriptor X.  According to the original code, thread A would not be
 * awakened as the result of thread B's close operation.  Possibly thread A
 * might never awaken, if it was only waiting on the object closed out by B.
 * Should thread A finally awoken, thread A will return with a select error
 * because it now has an invalid file descriptor in one of its select masks.
 *
 * The solution Encore developed for select uses a queue of select events in
 * each selectable object and a select event in the uthread structure.
 * Threads add themselves to a selectable object's select queue and then sleep
 * on the uthread's select event.  When a state change takes place, any
 * threads linked on the object's select queue are awoken.  At the end of a
 * select operation, unselect routines are invoked for each object to clean
 * up any remaining entries on the various select queues.
 *
 * Each object close routine changes to wake up any threads queued on the
 * object's select queue.  These threads will then re-poll all of the
 * objects that interest them; possibly some will then report invalid
 * file descriptors as the result of the original close.
 *
 * Changes:
 *	fo_select	now takes an additional "scanning" argument
 *	xxx_select	now takes an additional "scanning" argument
 *			and calls select_{enqueue,dequeue} as appropriate
 *	xxx_close	now must do a "select_wakeup"
 *	xxx_whatever	changes to do a "select_wakeup"
 * When "scanning" is non-zero, select() is performing the normal select
 * operation and the lower-level routine must return non-zero if the
 * object is selectable.  When "scanning" is zero, select() is cleaning
 * out old select queue entries and the lower-level routine must return zero.
 */

struct sel_queue {
	struct queue_entry	links;
	struct event		*event;
};

typedef struct sel_queue	sel_queue_t;

void	select_init();		/* Initialize select subsystem */
void	select_enqueue();	/* Put current thread on a select queue */
void	select_dequeue();	/* Remove current thread from a sel queue */
void	select_dequeue_all();	/* Remove all threads from a sel queue */
void	select_wakeup();	/* Notify all threads parked on a sel queue */
void	select_cleanup();	/* Purge accumulated sel events */

#endif  /* _KERNEL */

#if defined (_OSF_SOURCE) || defined ( _XOPEN_SOURCE_EXTENDED )

/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here is equal
 * to OPEN_MAX_SYSTEM in param.h since that defines the absolute maximum 
 * number of file descriptors that a process can open.
 */


#ifdef _XOPEN_SOURCE_EXTENDED

/* We don't really want to include all of limits.h to get the 
   real value of this, so we leave this ugly constant here */
#define	FD_NBBY	8		/* number of bits in a byte */
#define FD_MAX_NOFILE      4096
/* How many things we'll allow select to use. 0 if unlimited */
#define FD_MAXSELFD        MAX_NOFILE
#define FD_NFDBITS	(sizeof(long) * FD_NBBY)	/* bits per mask */

#define	_fds_howmany(x, y)	(((x)+((y)-1))/(y))


#else	/* _OSF_SOURCE */

typedef int	fd_mask;

#define	NBBY	8		/* number of bits in a byte */
#define MAX_NOFILE      4096
/* How many things we'll allow select to use. 0 if unlimited */
#define MAXSELFD        MAX_NOFILE
#define NFDBITS	(sizeof(fd_mask) * NBBY)	/* bits per mask */

#define FD_MAX_NOFILE MAX_NOFILE
#define FD_NFDBITS NFDBITS

#ifndef howmany
#define	howmany(x, y)	(((x)+((y)-1))/(y))
#define fds_howmany(x, y) howmany(x, y)
#endif


#endif	/* _XOPEN_SOURCE_EXTENDED */

#ifndef	FD_SETSIZE
#define	FD_SETSIZE	FD_MAX_NOFILE
#endif

#ifndef _XOPEN_SOURCE_EXTENDED
typedef	struct fd_set {
	fd_mask	fds_bits[fds_howmany(FD_SETSIZE, FD_NFDBITS)];
} fd_set;

#define	FD_SET(n, p)	((p)->fds_bits[(n)/FD_NFDBITS] |= (1L << ((n) % FD_NFDBITS)))
#define	FD_CLR(n, p)	((p)->fds_bits[(n)/FD_NFDBITS] &= ~(1L << ((n) % FD_NFDBITS)))
#define	FD_ISSET(n, p)	((p)->fds_bits[(n)/FD_NFDBITS] & (1L << ((n) % FD_NFDBITS)))

#else
typedef	struct {
	long	fds_bits[_fds_howmany(FD_SETSIZE, FD_NFDBITS)];
} fd_set;

#define	FD_SET(n, p) do {									\
			   int _fd;								\
			   fd_set *_fds;							\
												\
			   _fd = (n);								\
			   _fds = (p);								\
			   ((_fds)->fds_bits[(_fd)/FD_NFDBITS] |= (1L << ((_fd) % FD_NFDBITS)));\
			 } while (0)

#define	FD_CLR(n, p) do {									  \
			   int _fd;								  \
			   fd_set *_fds;							  \
												  \
			   _fd = (n);								  \
			   _fds = (p);								  \
			   ((_fds)->fds_bits[(_fd)/FD_NFDBITS] &= ~(1L << ((_fd) % FD_NFDBITS))); \
			 } while (0)

extern int FD_ISSET (int, fd_set *);
#endif

#ifdef _XOPEN_SOURCE_EXTENDED
#define FD_ZERO(p) (bzero((void *)(p), sizeof(*(p))))
#else
#define FD_ZERO(p) (bzero((char *)(p), sizeof(*(p))))
#endif /* _XOPEN_SOURCE_EXTENDED */

#if !defined (_KERNEL)
#ifdef _OSF_SOURCE

/* put both spec1170 and original decl for bzero here plus intrisic to
 * avoid conflicts when this header is included along with <strings.h>
 * which also contains these bzero decls.
 */
#if defined(_LIBC_POLLUTION_H_) && defined(_INTRINSICS)
# undef bzero
#endif
#ifdef _XOPEN_SOURCE_EXTENDED
extern void  bzero __((void *, size_t));
#else
extern void bzero __((char *, int));
#endif
#ifdef _INTRINSICS
#pragma intrinsic(bzero)
#endif

#endif /* _OSF_SOURCE */
struct timeval;
int select __((int, fd_set *, fd_set *, fd_set *, struct timeval *));
#endif /* _KERNEL */

#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_SELECT_H_ */
