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
 *	@(#)$RCSfile: kdb_print.h,v $ $Revision: 4.2.8.2 $ (DEC) $Date: 1995/01/03 23:10:59 $
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
 *	File:	kern/kdb_print.h
 *
 *	Machine-independent printing routines for KDB.
 *
 *	Because of routine name remappings, this file should not
 *	be compiled directly, but should instead be included by
 *	another KDB source file.
 */

#ifndef	_KERN_KDB_PRINT_H_
#define _KERN_KDB_PRINT_H_

#include <mach/time_value.h>
#include <mach/boolean.h>
#include <kern/processor.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <kern/queue.h>
#include <vm/vm_page.h>

extern	print_stack_trace();

print_thread(thread)
	thread_t	thread;
{
	time_value_t	user_time;
	time_value_t	system_time;
	char		active = 'R';

	if (thread_is_active(thread)) active  = 'A';
	printf(" %c", (thread->state & TH_RUN)  ? active : ' ');
	printf( "%c", (thread->state & TH_WAIT) ? 'W' : ' ');
	printf( "%c", (thread->state & TH_SUSP) ? 'S' : ' ');
	printf( "%c", (!thread->interruptible)  ? 'N' : ' ');
	printf( "%s", (thread->state & TH_SWAPPED)
						? "(swapped)" : "");

	if (thread->state & TH_WAIT ) {
		printf(" ");
		psymoff((long)thread->wait_event, ISYM, "");
		if (thread->wait_mesg)
			printf(" %s", thread->wait_mesg);
	}
	else {
		thread_read_times(thread, &user_time, &system_time);
		printf(" pri = %D, %Du %Ds %Dc",
			thread->sched_pri,
			user_time.seconds,
			system_time.seconds,
			thread->cpu_usage);
	}

	printf("\n");
}

print_task_long(task, thread_print_routine)
	task_t		task;
	int		(*thread_print_routine)();
{
	struct proc	*p;
	thread_t	thread;
	struct utask	*utaskp = task->u_address;

	p = (struct proc *)0;
	if (utaskp->uu_procp)
		p = utaskp->uu_procp;
	printf("task 0x%X [%-20.20s] proc %X pid %d map 0x%X: ", task,
#ifdef	u_comm
		utaskp ? utaskp->uu_comm : ""
#else	/*u_comm*/
		""
#endif	/*u_comm*/
		,utaskp ? p : 0
		,(utaskp && p) ? p->p_pid : -1
	       , task->map
		);
	if (task->thread_count == 0) {
		printf("no threads\n");
	}
	else if (task->thread_count > 1) {
		printf("%d threads:\n",
				task->thread_count);
	}
	thread = (thread_t) queue_first(
			&task->thread_list);
	while (!queue_end(&task->thread_list, (queue_entry_t) thread)) {
		printf("thread 0x%X ", thread);
		(void) thread_print_routine(thread);
		thread = (thread_t) queue_next(&thread->thread_list);
	}
}

int		print_task_short_per_line = 8;
int		print_task_short_counter = 0;

print_task_short(task, routine)
	task_t		task;
	int		(*routine)();
{
#ifdef	lint
	(void) (*routine)();
#endif	/*lint*/

	if (print_task_short_counter++ == print_task_short_per_line) {
		printf("\n");
		print_task_short_counter = 1;
	}
	printf("%X ", task);
}

print_all_tasks(task_print_routine, thread_print_routine)
	int		(*task_print_routine)();
	int		(*thread_print_routine)();
{
	task_t		task;
	processor_set_t	pset;

	pset = (processor_set_t) queue_first(&all_psets);
	while (!queue_end(&all_psets, (queue_entry_t) pset)) {
		task = (task_t) queue_first(&pset->tasks);
		while (!queue_end(&pset->tasks, (queue_entry_t) task)) {
			(void) task_print_routine(task, thread_print_routine);
			task = (task_t) queue_next(&task->pset_tasks);
		}
		pset = (processor_set_t) queue_next(&pset->all_psets);
	}
}

boolean_t
thread_is_active(thread)
	thread_t thread;
{
	int 		i;

	for (i = 0; i < NCPUS; i++) {
		if (thread == active_threads[i]) {
			return(TRUE);
		}
	}
	return(FALSE);
}

#if	NCPUS <= 1
#define freeze_all_processors(x)
#define thaw_all_processors()
#endif	/*NCPUS <= 1*/

/*
 */

#ifndef	ADDRESS_WAS_SPECIFIED
#define ADDRESS_WAS_SPECIFIED	adrflg
#endif	/*ADDRESS_WAS_SPECIFIED*/

#ifndef	ADDRESS_VALUE
#define ADDRESS_VALUE		adrval
#endif	/*ADDRESS_VALUE*/

#define LV_PRINT_CASES							\
	case 'V':							\
		lv_print(nextchar(), dot);				\
		break;

#include <streams.h>
extern int streams_loaded;
#define STREAMS_PRINT_CASES						\
	case 'Z':							\
		if(streams_loaded != 0)					\
	        	streams_print(nextchar(), dot);			\
		break;
#else
#define STREAMS_PRINT_CASES
#endif

/*
 *	Define the standard KDB commands
 */

#define KDB_PRINT_CASES							\
	case 'k':							\
		print_stack_trace(current_thread());			\
									\
	case 'K':							\
		if (ADDRESS_WAS_SPECIFIED)				\
			print_stack_trace((thread_t) ADDRESS_VALUE);	\
		break;							\
	case 'l':							\
		if (ADDRESS_WAS_SPECIFIED)				\
			print_task_long((task_t) ADDRESS_VALUE,		\
						 print_thread);		\
		 else							\
			print_all_tasks(print_task_long, print_thread);	\
		break;							\
									\
	case 'L':							\
		print_all_tasks(print_task_long, print_stack_trace);	\
		break;							\
									\
	case 'Q':							\
		print_all_tasks(print_task_short, (int (*)()) 0);	\
		printf("\n");						\
		break;							\
	case 'f':							\
	case 'F':							\
		freeze_all_processors(cpu_number());			\
		break;							\
	case 't':							\
	case 'T':							\
		thaw_all_processors();					\
		break;							\
	case 'm':							\
		vm_map_print((vm_map_t)dot);				\
		break;							\
	case 'G':							\
		vfs_print(nextchar(), dot);				\
		break;							\
	case 'U':							\
		if (ADDRESS_WAS_SPECIFIED)				\
			proc_print(dot);				\
		else if (current_task()->u_address &&			\
		    current_task()->u_address->uu_procp)		\
			proc_print(current_task()->u_address->uu_procp);\
		else							\
			printf("no current process\n");			\
		break;							\
	LV_PRINT_CASES							\
	case 'P':							\
		switch(nextchar()) {					\
			case 't':					\
				break;					\
			case 'T':					\
				break;					\
			case 'p':					\
				port_print((port_t)dot);		\
				break;					\
			case 's':					\
				break;					\
			case 'I':					\
				break;					\
			case 'O':					\
				vm_object_print((vm_object_t)dot);	\
				break;					\
			case 'M':					\
				vm_map_print((vm_map_t)dot);		\
				break;					\
			case 'P':					\
				vm_page_print((vm_page_t)dot);		\
				break;					\
			default:					\
				printf("cannot print unknown object\n");\
				break;					\
		}							\
		break;							\
	STREAMS_PRINT_CASES
#endif	/*_KERN_KDB_PRINT_H_*/
