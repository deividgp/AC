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
 * @(#)$RCSfile: task_swap.h,v $ $Revision: 1.1.20.2 $ (DEC) $Date: 1998/10/16 17:59:35 $
 */
/*	
 *	@(#)task_swap.h	3.2	(ULTRIX/OSF)	11/20/91
 */ 
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
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *	File:   kern/task_swap.h
 *	Declarations of thread swap_states and swapping routines.
 */

/*
 *	Swap states for threads.
 */

#ifndef	_KERN_TASK_SWAP_H_
#define	_KERN_TASK_SWAP_H_

/* task swap_state values */
#define TASK_NOT_QUEUED		0x00
#define TASK_INSWAPPED		0x01
#define TASK_OUTSWAPPED		0x02
#define TASK_COMING_IN		0x03
#define TASK_GOING_OUT		0x04
#define TASK_UNSWAPPABLE	0x05

/* task swap_request values */
#define TASK_ALL_SET		0x01
#define TASK_WANTS_IN		0x02

/*
 *      exported queues
 */
extern  queue_head_t    task_inswapped_queue;   /* queue of resident tasks */
extern  queue_head_t    task_outswapped_queue;  /* queue of swapped tasks */
extern  queue_head_t    task_inswap_work_queue; /* queue of incomming tasks */
extern  queue_head_t    task_outswap_work_queue;/* queue of outgoing tasks */
/*
 *      exported counts
 */
extern  int     task_inswapped_queue_count;
extern  int     task_outswapped_queue_count;
extern  int     task_inswap_work_queue_count;
extern  int     task_outswap_work_queue_count;
/*
 *      exported misc.
 */
extern  int     task_swap_work;
decl_simple_lock_data(extern,task_swap_queues_lock)

#define EXCESSIVE_FAULTRATE(task_fault_rate, average_fault_rate)        \
                (task_fault_rate > average_fault_rate)

#define THREAD_TASK_SWAPPABLE(time_sleeping)    \
                (sched_tick - time_sleeping > 2)

#define THREAD_LONGTIME_SLEEPER(time_sleeping)    \
                (sched_tick - time_sleeping > 30)

#endif	/* _KERN_TASK_SWAP_H_ */
