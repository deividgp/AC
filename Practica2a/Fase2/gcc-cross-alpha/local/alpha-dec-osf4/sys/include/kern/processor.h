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
 *	@(#)$RCSfile: processor.h,v $ $Revision: 4.3.47.2 $ (DEC) $Date: 1999/01/08 20:45:27 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

/*
 *	processor.h:	Processor and processor-set definitions.
 *
 */

#ifndef	_KERN_PROCESSOR_H_
#define	_KERN_PROCESSOR_H_
#ifdef __cplusplus
extern "C" {
#endif

/*
 *	Data structures for managing processors and sets of processors.
 */

#include <mach/boolean.h>
#include <sys/types.h>
#include <sys/lwc.h>
#include <kern/lock.h>
#include <mach/policy.h>
#include <mach/port.h>
#include <kern/queue.h>
#include <kern/sched.h>
#include <sys/callout.h>
#include <netinet/ip_stat.h>
#include <netinet/tcp_stat.h>

#ifdef __cplusplus
struct task;
#endif

struct processor_set {
	simple_lock_data_t	idle_lock;	/* lock for below */
	queue_head_t		idle_queue;	/* idle processors */
	int			idle_count;	/* number of processors */
	int			set_quantum;	/* current default quantum */
	struct run_queue	runq;		/* runq for this set */
	queue_head_t		processors;	/* all processors here */
	int			processor_count;/* number of processors */
	boolean_t		empty;		/* true if no processors */
	simple_lock_data_t	lock;		/* lock for everything else */
	int			ref_count;	/* structure ref count */
	boolean_t		active;		/* is pset in use */
	int			task_count;	/* number of tasks */
	int			thread_count;	/* number of threads */
	queue_head_t		tasks;		/* tasks in this set */
	queue_head_t		threads;	/* threads in this set */
	queue_chain_t		all_psets;	/* link for all_psets */
	port_t			pset_self;	/* port for operations */
	port_t			pset_name_self;	/* port for information */
	unsigned int		max_priority;	/* maximum priority */
	int			policies;	/* bit vector for policies */
	long			mach_factor;	/* mach_factor */
	long			load_average;	/* load_average */
	long			sched_load;	/* load avg for scheduler */
	int			pset_id;	/* unique identifier */
	int 			state;		/* e.g., exclusive access */
	struct task		*task;		/* task with excl. access */
};

typedef	struct processor_set *processor_set_t;
typedef port_t *processor_set_array_t;

#define PROCESSOR_SET_NULL	(processor_set_t)0
#define PROCESSOR_SET_NAME_NULL	(processor_set_t)0
struct processor_stats {
	int local_hot_dispatch; /* dispatch off local runq  + hot*/
	int local_cold_dispatch;
	int local_warm_dispatch;
	int global_hot_dispatch;
	int global_warm_dispatch;
	int global_cold_dispatch;
	int idle_hot_dispatch;
	int idle_warm_dispatch;
	int idle_cold_dispatch;
	int load_balance_steals;        /* steals because of load balance */
	int load_balance_steals_trys;   /* attempts to steal for load balance */
	int load_balance_idle_steals;   /* steals while idle */
	int same_thread_count;          /* false context switches */
	int processor_spare1;
	int processor_spare2;
	int processor_spare3;
};

struct processor {
	simple_lock_data_t lock;
	struct run_queue runq;		/* local runq for this processor */
		/* XXX want to do this round robin eventually */
	queue_chain_t	processor_queue; /* idle/assign/shutdown queue link */
	int		state;		/* See below */
	int		out_of_balance;	/* set if below balance point */
	struct thread	*next_thread;	/* next thread to run if dispatched */
	struct thread	*idle_thread;	/* this processor's idle thread. */
	int		quantum;	/* quantum for current thread */
	boolean_t	first_quantum;	/* first quantum in succession */
	int		last_quantum;	/* last quantum assigned */
	int             ip_interrupt_req;/* inter-processor interrupt request*/ 
	processor_set_t	processor_set;	/* processor set I belong to */
	processor_set_t processor_set_next;	/* set I will belong to */
	queue_chain_t	processors;	/* all processors in set */
	port_t		processor_self;	/* port for operations */
	int		slot_num;	/* machine-indep slot number */
	int		sched_tick;	/* timestamp for last priority recalc */
	long		load_avg;	/* average run queue depth */
	int		int_cnt;
	int		rt_cnt;
	long		desired_load;
	long		int_load_avg;	/* average interrupt load */
	long		rt_load_avg;	/* average bound rt load */
	struct		processor_stats stats; /* stats on runq activities */
	long		lbolt;
	simple_lock_data_t callout_lock; /* lock for below */
	struct		callout	*calltodo; 	/* timeouts */
	long		callout_lbolt;	
	long		spare1;
	long		spare2;
	struct          callout *abs_calltodo;
	long		spare3;
	long		spare4;
	long		spare5;
	struct		callout *callfree;
	int		ncallfree;
	int 		sema;
	struct		callout	*rt_calltodo[6]; /* spl 6 work requeuing */
	struct 		buf	*ubc_iodone_buf;
	struct		buf	*swap_iodone_buf;	
	struct 		buf	*MsfsIodoneBuf;
	queue_head_t    psignal_queue;

	int		lwc_count[LWC_PRI_MAX];
	port_t		processor_name_self;	/* port for information */
	int		bio_wait_state;		/* waiting for I/O */
	int		cpu_slowdown_enabled;	
	int		ticks_to_skip;     	/* # of clock ticks to skip */
	struct tcpstat tcpstat ;
	struct ipstat ipstat ;
	struct udpstat udpstat;
};

typedef struct processor *processor_t;
typedef port_t *processor_array_t;

#define PROCESSOR_NULL		(processor_t)0
#define PROCESSOR_NAME_NULL	(processor_t)0

/*
 *	NOTE: The processor->processor_set link is needed in one of the
 *	scheduler's critical paths.  [Figure out where to look for another
 *	thread to run on this processor.]  It is accessed without locking.
 *	The following access protocol controls this field.
 *
 *	Read from own processor - just read.
 *	Read from another processor - lock processor structure during read.
 *	Write from own processor - lock processor structure during write.
 *	Write from another processor - NOT PERMITTED.
 *
 */

/*
 *	Processor state locking:
 *
 *	Values for the processor state are defined below.  If the processor
 *	is off-line or being shutdown, then it is only necessary to lock
 *	the processor to change its state.  Otherwise it is only necessary
 *	to lock its processor set's idle_lock.  Scheduler code will
 *	typically lock only the idle_lock, but processor manipulation code
 *	will often lock both.
 */

#define PROCESSOR_OFF_LINE	0	/* Not in system */
#define	PROCESSOR_RUNNING	1	/* Running normally */
#define	PROCESSOR_IDLE		2	/* idle */
#define PROCESSOR_DISPATCHING	3	/* dispatching (idle -> running) */
#define	PROCESSOR_ASSIGN	4	/* Assignment is changing */
#define PROCESSOR_SHUTDOWN	5	/* Being shutdown */

#ifdef	_KERNEL

extern struct processor_set default_pset;

/*
 *	Chain of all processor sets.
 */
extern queue_head_t		all_psets;
extern int			all_psets_count;
decl_simple_lock_data(extern, all_psets_lock)

/*
 *	XXX need a pointer to the master processor structure
 */

extern processor_t	master_processor;

/*
 *	Use processor ptr array to find current processor's data structure.
 *	This replaces a multiplication (index into processor_array) with
 *	an array lookup and a memory reference.  It also allows us to save
 *	space if processor numbering gets too sparse.
 */

extern processor_t	processor_ptr[];

#define cpu_to_processor(i)	(processor_ptr[i])

#define current_processor()	(processor_ptr[cpu_number()])
#define current_processor_set()	(current_processor()->processor_set)

/* Compatibility -- will go away */

#define cpu_state(slot_num)	(processor_ptr[slot_num]->state)
#define cpu_idle(slot_num)	(processor_state(slot_num) == PROCESSOR_IDLE)

/* Useful lock macros */

#define	pset_lock(pset)		simple_lock(&(pset)->lock)
#define pset_unlock(pset)	simple_unlock(&(pset)->lock)

#define processor_lock(pr)	simple_lock(&(pr)->lock)
#define processor_unlock(pr)	simple_unlock(&(pr)->lock)

#define load_avg(avg,last)  ((((avg)<<2) + (last) + ((avg) < (last)  ? 4:0))/5)

#define mark_bio_wait							\
	myprocessor = current_processor();				\
	atomic_incl(&myprocessor->bio_wait_state);

#define unmark_bio_wait							\
	atomic_decl(&myprocessor->bio_wait_state);

#endif	/* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif	/*_PROCESSOR_H_*/
