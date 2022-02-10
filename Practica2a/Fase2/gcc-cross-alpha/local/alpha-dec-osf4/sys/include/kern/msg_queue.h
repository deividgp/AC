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
 *	@(#)$RCSfile: msg_queue.h,v $ $Revision: 4.2.5.5 $ (DEC) $Date: 1994/02/28 19:34:27 $
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
 * OSF/1 Release 1.0
 */
/*
 *	kern/msg_queue.h
 */

#ifndef	_KERN_MSG_QUEUE_H_
#define _KERN_MSG_QUEUE_H_

#include <kern/queue.h>
#include <kern/lock.h>

typedef struct msg_queue {
	decl_simple_lock_data(,lock)
	queue_head_t messages;
} msg_queue_t;

#ifdef	_KERNEL

#include <kern/macro_help.h>

#define msg_queue_lock(mq)	simple_lock(&(mq)->lock)
#define msg_queue_unlock(mq)	simple_unlock(&(mq)->lock)
#define msg_queue_init(mq)					\
MACRO_BEGIN							\
	decl_simple_lock_info(extern, msg_queue_lockinfo)	\
	simple_lock_setup(&(mq)->lock, msg_queue_lockinfo);	\
	queue_init(&(mq)->messages);				\
MACRO_END
#define msg_queue_terminate(mq)	simple_lock_terminate(&(mq)->lock)

#endif	/* _KERNEL */
#endif	/* _KERN_MSG_QUEUE_H_ */
