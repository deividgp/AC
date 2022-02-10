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
 * @(#)$RCSfile: thread.h,v $ $Revision: 4.3.89.2 $ (DEC) $Date: 1999/01/08 15:22:41 $
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
 *	File:	thread.h
 *	Author:	Avadis Tevanian, Jr.
 *
 *	This file contains the structure definitions for threads.
 */

#ifndef _SYS_USER_H_
#include <sys/user.h>
#endif

#ifndef	_KERN_THREAD_H_
#define _KERN_THREAD_H_

#ifdef	_KERNEL
#include <mach_host.h>
#include <mach_km.h>
#endif	/* _KERNEL */

#include <mach/policy.h>
#include <mach/port.h>
#include <mach/message.h>
#include <mach/boolean.h>
#include <mach/machine/vm_types.h>
#include <kern/ast.h>
#include <kern/event.h>
#include <kern/queue.h>
#include <kern/processor.h>
#include <kern/task.h>
#include <kern/timer.h>
#include <kern/lock.h>
#include <kern/sched.h>
#include <kern/thread_modes.h>
#include <kern/kern_msg.h>
#include <kern/processor.h>
#include <machine/cpu.h>
#include <machine/thread.h>
#include <machine/pcb.h>
#include <vm/vm_object.h>
#include <procfs/procfs.h>
#if	MACH_KM
#include <kern/kern_mon.h>
#endif

struct thread {
	/* Self-preservation */
	decl_simple_lock_data(,lock)
	int		ref_count;	/* number of references to me */

	/* User-visible scheduling state */
	int		user_stop_count;/* outstanding stops */

	/* Run queues */
	queue_chain_t	links;		/* current run queue links */
	run_queue_t	runq;		/* run queue p is on SEE BELOW */
/*
 *	NOTE:	The runq field in the thread structure has an unusual
 *	locking protocol.  If its value is RUN_QUEUE_NULL, then it is
 *	locked by the thread_lock, but if its value is something else
 *	(i.e. a run_queue) then it is locked by that run_queue's lock.
 */

	/* Task information */
	task_t		task;		/* Task to which I belong */
	queue_chain_t	thread_list;	/* list of threads in task */
	
	/* 2-level scheduler information */
	struct  nxm_sched_state *nxm_sptr; /* sched state if nxm thread */

	int		nxm_flags;		

#define NXM_IDLE	0x1	/* idle with no sched context */
#define NXM_SCHED	0x2	/* sched context valid */
#define NXM_NOSCHED	0x4	/* no sched context valid */
#define NXM_BLOCKED	0x8 	/* blocked NXM thread */
#define NXM_FP_STATE	0x10	/* blocked nxm thread has FP state */
#define NXM_BOUND	0x20 	/* user thread bound to kernel thread */
#define NXM_EXEC	0x40 	/* exec in progress */
#define NXM_RESCHED	0x80	/* force resched */
#define NXM_SAVESCHED	0x100	/* restore sched context after single step */
#define NXM_SIGEV	0x200	/* signal event pending */
#define NXM_MANAGER	0x400	/* thread is a manager */
#define NXM_WAKEUP	0x800	/* thread wakeup is pending */
#define NXM_SUSPEND	0x1000	/* library suspend in effect */
#define NXM_RESUME_POSTED 0x2000 /* resume posted against unsuspended thread */

	unsigned int	cpu_usage;	/* exp. decaying cpu usage [%cpu] */
	/* Thread bookkeeping */
	queue_chain_t	pset_threads;	/* list of all threads in proc set */

	/* Hardware state */
	struct stack_layout *stack; 	/* pointer to uthread/pcb and where
					   aligned stack was allocated */

	/* Blocking information */
	char            *wait_mesg;     /* wait mesg */
	vm_offset_t	wait_event;	/* event we are waiting on */
	kern_return_t	wait_result;	/* outcome of wait */
	int		suspend_count;	/* internal use only */
	boolean_t	interruptible;	/* interruptible wait? */
	int		timer_set;	/* timeout set on wait */
#define TIMER_FALSE   -1
	boolean_t	wake_active;
	int		swap_state;	/* swap state (or unswappable flag) */
	int		state;		/* Thread state: */
/*
 *	Thread states [bits or'ed]
 */
#define TH_WAIT			0x01	/* thread is queued for waiting */
#define TH_SUSP			0x02	/* thread has been asked to stop */
#define TH_RUN			0x04	/* thread is running or on runq */
#define TH_SWAPPED		0x08	/* thread is swapped out */
#define TH_IDLE			0x10	/* thread is an idle thread */

	/* Scheduling information */
	unsigned int	priority;	/* thread's priority */
	unsigned int	max_priority;	/* maximum priority */
	unsigned int	sched_pri;	/* scheduled (computed) priority */
	int		sched_data;	/* for use by policy */
	int		policy;		/* scheduling policy */
	int		depress_priority_cpu; /* cpu timeout queued to */
	int		depress_priority; /* depressed from this priority */
	port_name_t	local_name;	/* quick pick port name */
	unsigned long	sched_usage;	/* load-weighted cpu usage [sched] */
	unsigned int	sched_stamp;	/* last time priority was updated */
	unsigned int	sleep_stamp;	/* last time in TH_WAIT state */
	struct		thread_extension *extension;

	/* VM global variables */
	boolean_t	vm_privilege;	/* can use reserved memory? */
#if	MACH_HOST
	boolean_t	assign_active;	/* someone waiting for may_assign */
#endif
	pmap_t          pmap;           /* pamp for this thread */
	vm_offset_t     lw_va;          /* lw_wire va */
	unsigned long   lw_pages;       /* lw_wire no. pages */

	/* Ast/Halt data structures */
	boolean_t	active;		/* how alive is the thread */
	boolean_t	halted;		/* halted at clean point ? */
	int		ast;    	/* ast's needed.  See ast.h */
	int		flags;		/* suspended for exit or exec */
/* flags bits */
#define TF_EXEC		0x1		/* thread suspended by exit/exec */
#define TF_SHUTDOWN	0x2		/* thread suspended by cpu shtudown */
#define TF_PSUSP	0X4		/* thread can't be suspended */
#define TF_MALLOC	0X8		/* thread was malloc'ed */
#define TF_CLASS_SUSP   0x10

	/* IPC data structures */
	decl_simple_lock_data(,ipc_state_lock) /* Locks most IPC fields */
	msg_return_t	ipc_state;	/* Operation state after awakening */
	boolean_t	ipc_kernel;	/* ipc buffer in kernel space */
	union {
		msg_size_t msize;	/* Maximum size of msg to receive */
		kern_msg_t kmsg;	/* Message that was received */
	} ipc_data;
	port_t		thread_self;	/* Port representing this thread */
	int		wakeup_in_progress;
	int		reserved2;
	port_t		thread_reply;	/* Initial reply port for RPCs */
	port_t		exception_port;
	port_name_t	reply_port;	/* See kern/mig_support.c. */
	port_name_t	kern_reply_port;  /* ... ditto ... */

	/* Timing data structures */
	timer_data_t	user_timer;	/* user mode timer */
	timer_data_t	system_timer;	/* system mode timer */
	timer_save_data_t user_timer_save; /* saved user timer value */
	timer_save_data_t system_timer_save; /* saved sys timer value */
	unsigned int	cpu_delta;	/* cpu usage since last update */
	unsigned long	sched_delta;	/* weighted cpu usage since update */

	/* Processor data structures */
	processor_set_t	processor_set;	/* assigned processor set */
	processor_t	bound_processor;/* bound to processor? */
	processor_t     restore_processor;
	boolean_t 	bound_processor_inherit;/* inherit processor bindings */

	/* Added for RT_SCHED support.  Holds the remaining quantum for a
	 * RR thread which was preempted.  Used to restore the remaining
	 * quantum when the thread is restored. */
	int		rmng_quantum;	/* For RR rescheduling */
	int		psx4_sleep;	/* psx 4 clocks and timers */
	int		reserved3;
	long		time_remaining;	/* psx 4 clocks and timers */
	int		lock_hierarchy;	/* highest lock hierarchy level */
	int		lock_unordered;	/* mixed hierarchy in lock_addr */
	int		lock_count;	/* number of complex locks acquired */
#if	MACH_HOST
	boolean_t	may_assign;	/* may assignment change? */
#endif
	lock_t		*lock_addr;	/* pointers to locks acquired */
	struct lock_read_rec_list *lock_recread_list; /* list of recursive read 
						         locks held */
	queue_chain_t	sigwaitq;	/* queue links for sigwaiting */
	struct t_procfs t_procfs;	/* /proc thread-specific data */
	unsigned int	speculative_state; /* speculative execution state */
/*
 * speculative_fault bits.
 */
#define	TH_SPEC_SEGV	1 /* thread expects a segv fault */
#define	TH_SPEC_BUS	2 /* thread expects a bus fault */
#define	TH_SPEC_FPE	4 /* thread expects a floating point fault */

	/* the rest of this stuff is not currently compiled in */
	int		reserved4;
	processor_t	last_processor; /* processor this last ran on */
	unsigned long   last_run_stamp; /* time when switched off processor */
#if	MACH_KM	
	/* Kernel Monitor data structures */
	monitor_t	monitor_obj;	/* Monitor looking at thread */
	int		monitor_id;	/* Thread's identity for monitor */
	queue_chain_t	monitored_threads; /* queue link for monitor */
#endif
};

struct thread_extension {
	int class;
	queue_chain_t class_links;
};

#define MAX_TSD_SLOTS		8

struct uu_tsd {
	void	*tsd_slots[MAX_TSD_SLOTS];
};

struct super_thread {
	struct thread thread;
	struct np_uthread np_uthread;
	struct thread_extension thread_extension;
	struct uu_tsd uu_tsd;
};

#define thread_to_np_uthread(th) (&((struct super_thread *) (th))->np_uthread)

#define thread_to_tsd(th)	 (&((struct super_thread *) (th))->uu_tsd)

typedef struct thread *thread_t;

#define THREAD_NULL	((thread_t) 0)

typedef	port_t	*thread_array_t;	/* XXX compensate for MiG */

#ifdef	_KERNEL

extern thread_t active_threads[];	/* active threads */

/*
 *	User routines
 */

extern kern_return_t	thread_create(
				task_t		parent_task,
				thread_t	*child_thread);
extern kern_return_t	thread_terminate(thread_t thread);
extern kern_return_t	thread_suspend(thread_t thread);
extern kern_return_t	thread_resume(thread_t	thread);
extern kern_return_t	thread_abort(thread_t	thread);

extern kern_return_t	thread_get_special_port(
				thread_t	thread,
				int		which_port,
				port_t		*port);
extern kern_return_t	thread_set_special_port(
				thread_t	thread,
				int		which_port,
				port_t		port);
extern kern_return_t	thread_assign(
				thread_t	thread,
				processor_set_t	new_pset);
extern kern_return_t	thread_assign_default(thread_t	thread);

#if 0	/* notyet */
extern kern_return_t	thread_get_state(
				thread_t	thread,
				int		flavor,
		/* XXXXX */	thread_state_t	old_state,
				unsigned int	*old_state_count);
extern kern_return_t	thread_set_state(
				thread_t		thread,
				int			flavor,
		/* XXXXX */	thread_state_t		new_state,
				unsigned int		new_state_count);
extern kern_return_t	thread_info(
				thread_t		thread,
				int			flavor,
		/* XXXXX */	thread_info_t		thread_info_out,
				unsigned int		*thread_info_count);
#else
extern kern_return_t	thread_get_state();
extern kern_return_t	thread_set_state();
extern kern_return_t	thread_info();
#endif


/*
 *	Kernel-only routines
 */

extern void		thread_init(void);
extern void		thread_reference(thread_t thread);
extern void		thread_deallocate(thread_t thread);
extern void		thread_hold(thread_t thread);
extern void		thread_hold_delayed(thread_t thread);
extern kern_return_t	thread_dowait(
				thread_t	thread,
				boolean_t	must_halt);
extern void		thread_release(thread_t thread);
extern void		thread_swappable(
				thread_t	thread,
				boolean_t	is_swappable);
extern void		thread_force_terminate(thread_t thread);
extern kern_return_t	thread_halt(
				thread_t	thread,
				boolean_t	must_halt);
extern void		thread_halt_self(void);
extern thread_t		kernel_thread(task_t task, void (*start)());
extern thread_t		kernel_isrthread(task_t task, void (*start)(void), int);
extern thread_t		kernel_thread_w_arg(
				task_t		task,
				void		(*start)(),
				void		*arg);

extern void		reaper_thread(void);
extern void		pcb_init(thread_t thread);

#if	MACH_HOST
extern void		thread_freeze(thread_t thread);
extern kern_return_t	thread_doassign(
				thread_t	thread,
				processor_set_t	new_pset,
				boolean_t	release_freeze);
extern void		thread_unfreeze(thread_t thread);
#endif

/*
 *	Macro-defined routines
 */

#define thread_pcb(th)		(&(th)->stack->pcb)

#define thread_lock(th)		simple_lock(&(th)->lock)
#define thread_unlock(th)	simple_unlock(&(th)->lock)
#define thread_lock_terminate(th) simple_lock_terminate(&(th)->lock)

#define thread_should_halt(thread)	\
	((thread)->ast & (AST_HALT|AST_TERMINATE|AST_SUSPEND|AST_SIGEXIT))

#define ipc_thread_lock(th)	simple_lock(&(th)->ipc_state_lock)
#define ipc_thread_unlock(th)	simple_unlock(&(th)->ipc_state_lock)
#define ipc_thread_lock_terminate(th)	simple_lock_terminate(&(th)->ipc_state_lock)

/*
 *	Machine specific implementations of the current thread macro
 *	designate this by defining CURRENT_THREAD.
 */
#ifndef	CURRENT_THREAD
#define current_thread()	(active_threads[cpu_number()])
#define current_task()		((current_thread())->task)
#endif

/*
 * Kernel thread-specific data definitions and function prototypes
 */

typedef int tsd_key_t, *tsd_key_p;

#define TSD_SUCCESS     0
#define TSD_FAILURE     -1

void tsd_init(void);
int tsd_key_create(tsd_key_p keyp);
int tsd_key_destroy(tsd_key_t key);
int tsd_setspecific(tsd_key_t key, void *val);
void *tsd_getspecific(tsd_key_t key);

#endif	/* _KERNEL */
#endif	/* _KERN_THREAD_H_ */
