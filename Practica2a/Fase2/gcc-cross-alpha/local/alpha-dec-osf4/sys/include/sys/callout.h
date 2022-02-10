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
 *	@(#)$RCSfile: callout.h,v $ $Revision: 4.2.17.2 $ (DEC) $Date: 1997/07/02 15:59:54 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */

#ifndef	_SYS_CALLOUT_H_
#define _SYS_CALLOUT_H_

#include <sys/types.h>

/*
 * The callout structure is for
 * a routine arranging
 * to be called by the clock interrupt
 * (clock.c) with a specified argument,
 * in a specified amount of time.
 * Used, for example, to time tab
 * delays on typewriters.
 */

#ifndef	KERNEL
struct	callout {
	long c_time;		/* lbolt time to expire */
	caddr_t	c_arg;		/* argument to routine */
	int	(*c_func)();	/* routine */
	struct	callout *c_next;
};

#else 

#include <kern/lock.h>
#include <sys/time.h>
#include <kern/queue.h>
struct	callout {
	union {
		long c_ticks;
		struct timeval c_tv;
	} c_u;
	caddr_t	c_arg;		/* argument to routine */
	int	(*c_func)();	/* routine */

	struct callout *c_next;	 /* time ordered hash queue */
	struct callout *c_prev;	

	struct callout *e_next;	 /* func/event hash queue */
	struct callout *e_prev;	
};

#define ABS_CALLTODO_TIME       0x00ffffffL
#define ABS_CALLTODO_CPU_SHFT   24

#define CALLTODO_TIME   0x00ffffffffffffffL
#define CALLTODO_CPU_SHFT       56

#define CALLOUT_MASTER          1
#define CALLOUT_TYPE            2
#define CALLOUT_TYPE_MO         (CALLOUT_TYPE|CALLOUT_MASTER)
#define ABS_CALLOUT_TYPE        4
#define ABS_CALLOUT_TYPE_MO     (ABS_CALLOUT_TYPE|CALLOUT_MASTER)
#define	CALLOUT_REALITIMER	8
#define CALLOUT_POSIX_TIMER	0x10
extern struct callout *callfree, *callout, calltodo;
extern int ncallout;
decl_simple_lock_data(extern,callout_lock)

#endif	/* KERNEL */
#endif	/* _SYS_CALLOUT_H_ */
