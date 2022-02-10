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
 *	@(#)$RCSfile: event.h,v $ $Revision: 4.2.8.2 $ (DEC) $Date: 1997/03/28 14:21:26 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
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

#ifndef	_KERN_EVENT_H_
#define	_KERN_EVENT_H_

#include <kern/lock.h>

struct event {
	decl_simple_lock_data(,ev_slock)/* lock protecting event structure */
	unsigned int ev_event;		/* posted flag (event_post caller) */
	unsigned int ev_waiter;		/* wait flag (wait pc) */
};

typedef struct event event_t;

#ifdef	_KERNEL

/*
 * Prototypes and macros for exported functions in the event package.
 */

decl_simple_lock_info(extern, event_lockinfo)

#define event_init(evp)			/* initialize event structure */\
MACRO_BEGIN				\
	(evp)->ev_event = 0;		\
	(evp)->ev_waiter = 0;		\
	simple_lock_setup(&(evp)->ev_slock, event_lockinfo);\
MACRO_END

#define event_clear(evp)		\
MACRO_BEGIN				\
	(evp)->ev_event = 0;		\
	(evp)->ev_waiter = 0;		\
MACRO_END

#define event_posted(evp) 	(evp)->ev_event

#define event_terminate(evp)		/* terminate use of event structure */\
MACRO_BEGIN				\
	simple_lock_terminate(&(evp)->ev_slock);\
MACRO_END

extern void event_post(event_t *);	/* post event and wakeup waiters */
extern int event_wait(event_t *, boolean_t, int); /* wait for event */
extern int event_wait_tmo(event_t *, boolean_t, int); /* wait for event */

#endif	/* _KERNEL */
#endif	/* _KERN_EVENT_H_ */
