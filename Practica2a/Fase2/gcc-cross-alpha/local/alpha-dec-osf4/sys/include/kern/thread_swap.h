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
 *	@(#)$RCSfile: thread_swap.h,v $ $Revision: 4.2.10.2 $ (DEC) $Date: 1995/04/21 18:27:38 $
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
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 *	File:	kern/thread_swap.h
 *
 *	Declarations of thread swap_states and swapping routines.
 */

/*
 *	Swap states for threads.
 */

#ifndef	_KERN_THREAD_SWAP_H_
#define _KERN_THREAD_SWAP_H_

#define	TH_SW_STATE		7	/* mask of swap state bits */
#define TH_SW_UNSWAPPABLE	1	/* not swappable */
#define TH_SW_IN		2	/* swapped in */
#define TH_SW_GOING_OUT		3	/* being swapped out */
#define TH_SW_WANT_IN		4	/* being swapped out, but should
					   immediately be swapped in */
#define TH_SW_OUT		5	/* swapped out */
#define TH_SW_COMING_IN		6	/* queued for swapin, or being
					   swapped in */

#define TH_SW_MAKE_UNSWAPPABLE	8	/*not state, command to swapin_thread */

/* 
 * This flag is only used by the task swapper.  It implies that
 * the thread is about to be swapped, but hasn't yet.
 */
#define TH_SW_TASK_SWAPPING	0x10

decl_simple_lock_data(extern, swapper_lock_data)
decl_simple_lock_info(extern, swapper_lockinfo)

#define swapper_lock()          simple_lock(&swapper_lock_data)
#define swapper_unlock()        simple_unlock(&swapper_lock_data)


/*
 *	exported routines
 */
extern void	thread_swapper_init(void);
extern void	swapin_thread(void);
extern void	swapin_wakeup(void);
extern void	swapout_thread(void);
extern void	thread_doswapin(thread_t thread);
extern boolean_t thread_swapin(thread_t thread, boolean_t make_unswappable);
extern void	swapout_threads(boolean_t now);

extern void	thread_swappable(thread_t thread, boolean_t swappable);

#endif	/*_KERN_THREAD_SWAP_H_*/
