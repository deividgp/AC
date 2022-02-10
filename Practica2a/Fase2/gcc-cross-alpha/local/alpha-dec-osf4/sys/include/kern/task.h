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
 *	@(#)$RCSfile: task.h,v $ $Revision: 4.3.30.2 $ (DEC) $Date: 1998/04/03 20:18:32 $
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
 *	File:	task.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	This file contains the structure definitions for tasks.
 */

#include <sys/user.h>
#include <sys/proc.h>

#ifndef	_KERN_TASK_H_
#define _KERN_TASK_H_

#include <mach_emulation.h>
#include <mach_ipc_tcache.h>
#include <mach/boolean.h>
#include <mach/port.h>
#include <mach/time_value.h>
#include <kern/lock.h>
#include <kern/queue.h>
#include <kern/mach_param.h>
#include <kern/kern_obj.h>
#include <kern/kern_set.h>
#include <kern/processor.h>
#include <kern/syscall_emulation.h>
#include <kern/processor.h>
#include <vm/vm_map.h>
#include <procfs/procfs.h>
#include <mach/task_info.h>
#include <kern/host.h>

struct task {
	/* Synchronization/destruction information */
	decl_simple_lock_data(,lock)	/* Task's lock */
	int		ref_count;	/* Number of references to me */
	boolean_t	active;		/* Task has not been terminated */

	/* Miscellaneous */
	vm_map_t	map;		/* Address space description */
	queue_chain_t	pset_tasks;	/* list of tasks assigned to pset */
	int		suspend_count;	/* Internal scheduling only */

	/* 2-level scheduler information */
	int 		nxm_sched_max;	/* max scheduler threads */
	int		nxm_sched_cnt;  /* active scheduler threads*/
	int		nxm_sched_blocked_cnt;	/* sched threads blocked */
	int		nxm_extra_threads; 	/* extra threads */	
	int		nxm_extra_threads_blocked; /* extra threads blocked */
	struct thread	*nxm_manager;		/* library's manager thread */
	sigset_t	nxm_signal_upcall;	/* signals needing upcalls */
	struct 		nxm_shared *nxm_share;	/* pointer to shared space */
	struct 		nxm_shared *nxm_user;	/* pointer user's mapping */


	/* Thread information */

	queue_head_t	thread_list;	/* list of threads */
	int		thread_count;	/* number of threads */
	int		res_thread_count; /* number of resident threads */
	processor_set_t	processor_set;	/* processor set for new threads */
	boolean_t	may_assign;	/* can assigned pset be changed? */
	boolean_t	assign_active;	/* waiting for may_assign */

	/* User-visible scheduling information */
	int		user_stop_count;	/* outstanding stops */
	short		priority;		/* for new threads */
	short 		max_priority;

	/* Information for kernel-internal tasks */
	boolean_t	kernel_ipc_space; /* Uses kernel's port names? */
	boolean_t	kernel_vm_space; /* Uses kernel's pmap? */

	/* Special ports */
	port_t		task_self;	/* Port representing the task */
	port_t		task_tself;	/* What the task thinks is task_self */
	port_t		task_notify;	/* Where notifications get sent */
	port_t		exception_port;	/* Where exceptions are sent */
	port_t		bootstrap_port;	/* Port passed on for task startup */

	/* IPC structures */
	boolean_t	ipc_privilege;	/* Can use kernel resource pools? */
	unsigned short	nxm_retry_count; /* nxm_get_thread() retries */
#define NXM_NO_TIMEOUT USHRT_MAX
	unsigned short	nxm_retry_cpu;  /* nxm_get_thread() timeout cpu */
	decl_simple_lock_data(,ipc_translation_lock)
	queue_head_t	ipc_translations; /* Per-task port naming */
	boolean_t	ipc_active;	/* Can IPC rights be added? */
	int		policy;		/* task's scheduling "policy" */
	port_name_t	ipc_next_name;	/* Next local name to use */

#if	MACH_IPC_TCACHE
#define OBJ_CACHE_MAX		010	/* Number of cache lines */
#define OBJ_CACHE_MASK		007	/* Mask for name->line */

	struct {
		port_name_t	name;
		kern_obj_t	object;
	}		obj_cache[OBJ_CACHE_MAX];
					/* Fast object translation cache */
#endif	/*MACH_IPC_TCACHE*/

	int		class;		/* class scheduler index */

	/*
	 * set if ipc name space conflict is possible.  Under control of 
	 * task ipc_translation_lock lock.
	 */
	int		ipc_name_conflict_test;	
						
	/* IPC compatibility garbage */
	port_t		ipc_ports_registered[TASK_PORT_REGISTER_MAX];

#if	MACH_EMULATION
	/* User space system call emulation support */
	struct 	eml_dispatch	*eml_dispatch;
#endif	/* MACH_EMULATION */

	queue_chain_t	task_link;	/* Pointer to next task on swap queue */
	int		swap_state;	/* current swap state of task */
	int		swap_request;	/* current swap request of task */
	unsigned	inswap_stamp;	/* time of last inswap */
	unsigned	outswap_stamp;	/* time of last outswap */
	int		working_set;	/* number of pages reclaimed by swapper */
	int 		swap_nswap;	/* number of times this task swapped */

	struct procfs procfs;		/* /proc task-specific data */
	struct vnode *proc_vnptr;  /* vnode in /proc fs if open via /proc*/
};
struct super_task {
	struct task task;
	struct proc proc;
	struct utask utask;
};

#define task_to_proc(t) ((struct proc *) &((struct super_task *)(t))->proc) 
#define task_to_utask(t) ((struct utask *) &((struct super_task *)(t))->utask) 
#define proc_to_task(p)	((struct task *) (((char *)(p)) - sizeof(struct task)))
#define proc_to_utask(p) ((struct utask *) (((char *)(p)) + sizeof(struct proc)))
#define utask_to_proc(ut) (( struct proc *) (((char *)(ut)) - sizeof(struct proc)))
#define utask_to_task(ut) (( struct task *) (((char *)(ut)) - sizeof(struct proc) - sizeof(struct task)))


typedef struct task *task_t;

#define TASK_NULL	((task_t) 0)

typedef	port_t	*task_array_t;
/*
 * This typedef is necessary for the MiG generated interfaces for
 * task-related functions (vm_allocate, etc.) Inside the kernel,
 * the functions take vm_map_t's. The client side uses a task_t
 * (see mach/mach_types.h)
 */
typedef vm_map_t vm_task_t;

/*
 * Describes how a child inherits its parent's address space.
 *
 * 
 *	TI_NONE:        don't use parent's address space
 *	TI_INHERIT:     inherit parent's address space, i.e. COW
 *	TI_VFORK:	use vfork model (lazy swap task).
 */
typedef enum {TI_NONE, TI_INHERIT, TI_VFORK} task_inherit_t;

#define task_lock(task)		simple_lock(&(task)->lock)
#define task_unlock(task)	simple_unlock(&(task)->lock)
#define task_lock_terminate(task) simple_lock_terminate(&(task)->lock)

#define ipc_task_lock(t)	simple_lock(&(t)->ipc_translation_lock)
#define ipc_task_unlock(t)	simple_unlock(&(t)->ipc_translation_lock)
#define ipc_task_lock_terminate(t) simple_lock_terminate(&(t)->ipc_translation_lock)
/*
 *	Exported routines/macros
 */

extern kern_return_t	task_create(
		task_t		parent_task,
		task_inherit_t	inherit_memory,
		task_t		 child_task);
extern kern_return_t	task_terminate( task_t	task);
extern kern_return_t	task_suspend(task_t task);
extern kern_return_t	task_resume(task_t task);
extern kern_return_t	task_info(
		task_t		task,
		int		flavor,
		task_info_t	task_info_out,	/* pointer to OUT array */
		unsigned int	*task_info_count );	/* IN/OUT */
extern kern_return_t	task_get_special_port(
		task_t		task,
		int		which_port,
		port_t		*port);
extern kern_return_t	task_set_special_port(
		task_t		task,
		int		which_port,
		port_t		port );
extern kern_return_t	task_assign(
		task_t	task,
		processor_set_t	new_pset,
		boolean_t	assign_threads );
extern kern_return_t	task_assign_default(
		task_t		task,
		boolean_t	assign_threads );
/* XXXXX extern kern_return_t
 * task_threads(task_t task, thread_array_t *thread_list, unsigned int *count);
 */ extern kern_return_t	task_threads();

/*
 *	Internal only routines
 */

extern void		task_init(void);
extern void		task_reference( task_t task );
extern void		task_deallocate( task_t task );
extern kern_return_t	task_hold( task_t task );
extern kern_return_t	task_hold_delayed( task_t task );
extern kern_return_t	task_dowait( task_t task, boolean_t must_wait );
extern kern_return_t	task_release( task_t task );
extern kern_return_t	task_halt( task_t task );
extern kern_return_t	task_suspend_nowait( task_t task );
extern kern_return_t	task_suspend_self( boolean_t );

extern task_t	kernel_task;
extern int	task_count;		/* # of allocated task struct */
extern int	task_bucket_size;	/* size of malloc bucket for task*/

/*****************************************************
 * Layout of memory allocated by task_alloc
 *  +----------------------------------+
 *  |                                  |
 *  |  space for task                  |
 *  |  sizeof(struct super_task)       |
 *  |                                  |
 *  +----------------------------------+
 *  |  bitmap sizeof(long)             |
 *  +----------------------------------+
 *  |  space for thread 1              |
 *  |  sizeof(struct super_thread)     |
 *  +----------------------------------+
 *
 * The bitmap field is used to indicate availablity of a thread.
 * The n'th thread is free when the n'th bit (starting from LSB) in the
 * bitmap is set to one. The bitmap is tested/set/reset by thread space
 * allocation and release routines. Because of this, the minimum space
 * should be MALLOC'd by task_alloc is sizeof(struct super_task) +
 * sizeof(long). ALLOC_TASK_SIZE is currently defined as a constant.
 * The initial task bitmap is pre-calculated in task_init().
 *****************************************************/

/* The real size task_alloc will at least allocate */
#define ALLOC_TASK_SIZE	(sizeof(struct super_task) + sizeof(long))

/* task_alloc allocate at least one thread */
#define task_alloc(TASK)						\
	if(task_count >= task_max)					\
		(TASK) = (struct task *)NULL;				\
	else {								\
		register long *thread_bmp;				\
		extern long threads_in_task_bucket;			\
        	MALLOC((TASK), task_t, ALLOC_TASK_SIZE,			\
			M_TASK, M_WAITOK | M_ZERO);			\
		atomic_incl(&task_count);				\
		thread_bmp = (long *)((char*)(TASK)+sizeof(struct super_task));\
		*thread_bmp = threads_in_task_bucket;			\
	}
		
#define task_free(TASK)				\
        	FREE((TASK), M_TASK); 		\
		atomic_decl(&task_count);

#define thread_first_set(setp)		(lsb(*(setp)))
#define thread_delete_set(setp, n)	 *(setp) &= ~(1L << (n))
#define thread_add_set(setp, n)		 *(setp) |= (1L << (n))

#endif	/*_KERN_TASK_H_*/
