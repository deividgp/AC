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
 * @(#)$RCSfile: mqueue.h,v $ $Revision: 1.1.18.2 $ (DEC) $Date: 1996/12/03 21:50:27 $
 */
/*
 *
 *  Description
 *      This module defines functions, structures, and constants needed to
 *      support POSIX 1003.1b IPC Message Passing.  It is included from user 
 *      applications that use IPC, and also from kern_mman.c for the kernel 
 *      sleep/wakeup functions for IPC.
 *
 */

#ifndef _MQUEUE_H_
#define _MQUEUE_H_

#if defined(__cplusplus)
extern "C"
{
#endif

#include <standards.h>
#include <sys/signal.h>
#if defined(_KERNEL) || defined(_LIBRT_BUILD)
#include <sys/psx4_nspace_ts.h>
#endif

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)

typedef int mqd_t;   /* Process-level message queue descriptor */

typedef struct mq_attr {
	long mq_maxmsg;	/* max # of messages allowed in MQ */
	long mq_msgsize;  	/* max size of any one message */
	long mq_flags;	/* actions and state for mq operations */
	long mq_curmsgs;	/* # of messages currently on mq */
} mq_attr_t;

/* POSIX 1003.1b Message passing functions */

mqd_t mq_open __((const char *, int, ...));
int mq_close __((mqd_t));
int mq_unlink __((const char *));
int mq_notify __((mqd_t, const struct sigevent *));
int mq_send __((mqd_t, const char *_ptr, size_t, unsigned int));
ssize_t mq_receive __((mqd_t, char *, size_t, unsigned int *));
int mq_getattr __((mqd_t, const struct mq_attr *));
int mq_setattr __((mqd_t, const struct mq_attr *, struct mq_attr *));

#endif  /* _POSIX_C_SOURCE */

#if defined(_KERNEL) || defined(_LIBRT_BUILD)
/*
 * A generic doubly-linked list (queue)
 */
typedef struct psx4queue_entry {
        u_long  next_off;  /* offset to next element's hdr (psx4queue_entry)*/
        u_long  prev_off;  /* offset to prev element's hdr (psx4queue_entry)*/
} psx4queue_entry_t;

/* 
 * Message Queue Header 
 */
typedef struct p4ipc_qhdr {
	rtlock_t qlock;			/* Lock for queue access 	*/
	long num_blocked_senders; 	/* Number of blocked senders 	*/
	long num_blocked_receivers;	/* Number of blocked senders 	*/
	struct psx4queue_entry mq_free;	/* Free message queue header, the 
				     	 *  address of which blocked senders 
					 *  wait on */
	struct psx4queue_entry mq_used; /* Used message queue header, the 
				     	 *  address of which blocked receivers 
					 *  wait on */
	char qname[MQ_NAME_MAX];	/* Pathname of associated object   */
	int qsize;			/* Total size of queue, incl. msgs */
	mq_attr_t qattr;		/* Message queue attribute struct  */
	pid_t qsignal_pid;		/* process id of process that has
				 	 *  a notification request attached 
				 	 *  to the queue. */
	struct sigevent qsigevent; /* Structure containing signal information*/
	void *qkey;		   /* kernel-supplied "transaction key" */
	long last_msg_offset;	   /* For range checking on prev/next ptrs
				    *  within message headers, this is the
				    *  offset to the last valid message hdr,
				    *  anything beyond this is a bogus ptr.
				    *  Remember that the queue is preallocated,
				    *  so we know what address range things
				    *  will reside in. CURRENTLY NOT USED.
				    */
#ifdef _KERNEL
	void *sigevptr;
#else
	sigev_data_p sigevptr;	   /* Point to sigev data */
#endif
	int qhdr_reserved[2];      /* Reserved */
} p4ipc_qhdr_t;
#endif

#if defined(__cplusplus)
}
#endif
#endif  /* _MQUEUE_H */
