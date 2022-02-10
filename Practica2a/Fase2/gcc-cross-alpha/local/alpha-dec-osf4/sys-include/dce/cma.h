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
 * @(#)$RCSfile: cma.h,v $ $Revision: 4.2.36.6 $ (DEC) $Date: 1999/02/11 21:04:33 $
 */
/*
 *  FACILITY:
 *
 *	Digital's Proprietary Interface to DECthreads (cma)
 *
 *	This interface is OBSOLETE. Although it will continue to be supported
 *	in the future, no new features will be added (including 64-bit
 *	pointer support for OpenVMS Alpha). In the future, documentation of
 *	this interface will be moved to an "obsolete features" appendix that
 *	may eventually be dropped from the distributed documentation set.
 *
 *	New development should not use this interface. Instead, refer to the
 *	Guide to DECthreads for information on the standard POSIX
 *	1003.1c-1995 interface, which uses the header file <pthread.h>.
 *
 *	In addition, it is usually relatively easy to migrate from the
 * 	proprietary cma interface to the open standard 1003.1c-1995 "pthread"
 *	interface -- the semantics are very similar.
 *
 *  ABSTRACT:
 *
 *	External definitions for the OBSOLETE cma interface to the
 *	DECthreads "core" services.
 *
 *  AUTHORS:
 *
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	 2 November 1988
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Paul Clark
 *	Bob Conti
 *	Paul Curtin
 *	Steve Johnson
 *	Brian Keane
 *	Hans Oser
 *	Peter Portante
 *	Webb Scales
 *	Ravi Chamarti
 *
 *  LAST MODIFICATION DATE:
 *
 *	25 October 1998
 */

#ifndef CMA_INCLUDE
#define CMA_INCLUDE

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef _DECTHREADS_
/*
 * Define a symbol which client code can test to determine the current
 * version of DECthreads.
 *
 * The DECthreads version is encoded in the numeric value of this symbol. The
 * version is normally in the form "Vvv.bb-ll" where "vv" represents the
 * major version, "bb" represents the baselevel (which increases continuously
 * regardless of version), and "ll" is a build level that increases in each
 * DECthreads project build within a baselevel.
 *
 * Higher numeric values are always more recent versions. So to check for
 * support of a feature that appeared in DECthreads V2.12-100, you could
 * check whether the symbol is > 212100.
 */
#define _DECTHREADS_ 314288
#endif

/*
 * The implementation makes these basic decisions
 */

#if defined (vms) || defined (__vms) || defined (VMS) || defined (__VMS) || defined (__vms__)
# include <cma_config.h>		/* configuration symbols */
# include <exc_handling.h>
#else
#  include <dce/cma_config.h>
#  include <dce/exc_handling.h>
#endif

#if _CMA_OSIMPL_ == _CMA__OS_OSF
/*
 * The Digital UNIX standards.h defines POSIX and OSF programming environment
 * symbols if none of the recognized symbols are already defined, but defines
 * no more if any are already defined. To retain as much as possible of the
 * application's desired environment, we'll include unistd.h first to get
 * whatever it thinks we need -- and then define what we really do need if it
 * didn't.
 */
# include <unistd.h>
# include <sched.h>
#endif

#if _CMA_OS_ == _CMA__UNIX
# include <sys/types.h>
# include <sys/time.h>
#endif

#if _CMA_PLATFORM_ == _CMA__ALPHA_VMS
# include <ints.h>
#endif

/*
 * Enable reentrant errno.h
 */
#if (_CMA_OSIMPL_ == _CMA__OS_OSF) && _CMA_REENTRANT_CLIB_
# ifndef _REENTRANT
#  define _REENTRANT	1
# endif
#endif

/*
 * Basic types
 */

typedef long		cma_t_integer;
typedef unsigned long	cma_t_natural;
typedef cma_t_natural	cma_t_boolean;
typedef float		cma_t_interval;
typedef int		cma_t_errno;
#if _CMA_VOID_
typedef void		*cma_t_address;
#else
typedef char		*cma_t_address;
#endif

#define cma_c_false	(cma_t_boolean)0
#define cma_c_true	(cma_t_boolean)1
#define cma_c_null_ptr	(cma_t_address)0


/*
 * If we're on a system with POSIX 1003.4 support, use the system symbols for
 * scheduling policy.
 */
#if _CMA_RT4_KTHREAD_
# define cma_c_sched_fifo	SCHED_FIFO
# define cma_c_sched_rr		SCHED_RR
# define cma_c_sched_throughput	SCHED_FG_NP
# define cma_c_sched_background	SCHED_BG_NP
# define cma_c_sched_ada_low	SCHED_LFI_NP
# define cma_c_sched_ada_rtb	SCHED_LRR_NP

/*
 * NOTE:
 *
 * On Digital UNIX, this header file retains the binary value of cma priority
 * symbols used prior to Digital UNIX 4.0. However, on earlier versions the
 * cma priorities mapped directly to kernel realtime priorities. In the new
 * version of DECthreads, all cma threads are "multiplexed" onto arbitrary
 * kernel threads in user mode, and cma priority has no real relationship to
 * the kernel priority at which the thread runs -- it controls only which
 * user thread the DECthreads core will select to run when a kernel thread
 * becomes available.
 */
# define cma_c_prio_fifo_max	21
# define cma_c_prio_fifo_mid	18
# define cma_c_prio_fifo_min	14
# define cma_c_prio_rr_max	22
# define cma_c_prio_rr_mid	19
# define cma_c_prio_rr_min	15
# define cma_c_prio_through_max	22
# define cma_c_prio_through_mid	19
# define cma_c_prio_through_min	15
# define cma_c_prio_back_max	13
# define cma_c_prio_back_mid	8
# define cma_c_prio_back_min	0
# define cma_c_prio_ada_low_max	13
# define cma_c_prio_ada_low_mid	8
# define cma_c_prio_ada_low_min	0
# define cma_c_prio_ada_rtb_max	13
# define cma_c_prio_ada_rtb_mid	8
# define cma_c_prio_ada_rtb_min	0
#else
# define cma_c_sched_fifo	0
# define cma_c_sched_rr		1
# define cma_c_sched_throughput	2
# define cma_c_sched_background	3
# define cma_c_sched_ada_low	4
# define cma_c_sched_ada_rtb	5

# define cma_c_prio_fifo_max	31
# define cma_c_prio_fifo_mid	((31+16)/2)
# define cma_c_prio_fifo_min	16
# define cma_c_prio_rr_max	cma_c_prio_fifo_max
# define cma_c_prio_rr_mid	cma_c_prio_fifo_mid
# define cma_c_prio_rr_min	cma_c_prio_fifo_min
# define cma_c_prio_through_max	15
# define cma_c_prio_through_mid	((15+8)/2)
# define cma_c_prio_through_min	8
# define cma_c_prio_back_max	7
# define cma_c_prio_back_mid	((7+0)/2)
# define cma_c_prio_back_min	0
# define cma_c_prio_ada_low_max	cma_c_prio_back_max
# define cma_c_prio_ada_low_mid	cma_c_prio_back_mid
# define cma_c_prio_ada_low_min	cma_c_prio_back_min
# define cma_c_prio_ada_rtb_max	cma_c_prio_ada_low_max
# define cma_c_prio_ada_rtb_mid	cma_c_prio_ada_low_mid
# define cma_c_prio_ada_rtb_min	cma_c_prio_ada_low_min
#endif

#define cma_c_sched_default	cma_c_sched_throughput
#define cma_c_sched_other	cma_c_sched_default

/*
 * Contention scope possible values
 */
#if _CMA_OS_ == _CMA__UNIX
#define cma_c_scope_process   0
#define cma_c_scope_system    1
#endif


/*
 * The implementation of the cma_t_date_time type should match the "native
 * time" of the platform: that allows clients to use the full set of platform
 * time operations, rather than just "cma_get_expiration", to compute and
 * test timed waits.
 *
 * This section assumes the platform is either "VMS" or "UNIX-ish".  Others
 * will require changes.
 */
#if _CMA_OS_ == _CMA__VMS
typedef struct CMA_T_DATE_TIME {
    unsigned long int	low;
    unsigned long int	high;
    }				cma_t_date_time;
#else
typedef struct timeval		cma_t_date_time;
#endif

/*
 * Handle type
 */

typedef struct CMA_T_HANDLE {
    cma_t_natural	field1;
    cma_t_natural	field2;
    } cma_t_handle;

#if (_CMA_COMPILER_ == _CMA__CFRONT) && (_CMA_OS_ == _CMA__VMS)
/*
 * The following declaration is a hack to support CFRONT (C++ preprocessor);
 * without an actual instance, the struct definition isn't written out.
 * Creates problems for VAX C when it compiles CFRONT output.
 */
static struct CMA_T_HANDLE	cxxl_unused_handle;
#endif

#define cma_c_handle_size sizeof(cma_t_handle)

/*
 * Predefined null handle
 */
#ifndef _CMA_SUPPRESS_EXTERNALS_
_CMA_IMPORT_ cma_t_handle	cma_c_null;
#endif

/*
 * One-time initialization control block and its initialization macro.
 *
 * Declare a one time initialization control block as:
 *
 *	static cma_t_once	block = cma_once_init;
 */
typedef struct CMA_T_ONCE {
    cma_t_integer	field1;
    cma_t_integer	field2;
    cma_t_integer	field3;
    }				cma_t_once;

#define cma_once_init	{0, 0, 0}

/*
 * Alert state structure
 */
typedef struct CMA_T_ALERT_STATE {
    cma_t_integer	state1;
    cma_t_integer	state2;
    }				cma_t_alert_state;

/*
 * Operations on Handles
 */

extern void _CMA_CALL_
cma_handle_assign (	/*  Assign one handle to another */
	cma_t_handle	*handle1,	/* Input handle */
	cma_t_handle	*handle2);	/* Output handle */

extern cma_t_boolean _CMA_CALL_
cma_handle_equal (	/* Compare two handles */
	cma_t_handle	*handle1,
	cma_t_handle	*handle2);

/*
 * Operations on attributes objects
 */

typedef cma_t_handle	cma_t_attr;

/*
 * An attributes object is created to specify the attributes of other CMA
 * objects that will be created.
 */

extern void _CMA_CALL_
cma_attr_create (
	cma_t_attr	*new_attr,
	cma_t_attr	*attr);

/*
 * An attributes object can be deleted when it is no longer needed.
 */

extern void _CMA_CALL_
cma_attr_delete (
	cma_t_attr	*attr);

/*
 * Operations on threads
 */

typedef cma_t_handle	cma_t_thread;
typedef cma_t_address	(*cma_t_start_routine) (cma_t_address arg);

typedef enum CMA_T_EXIT_STATUS {
    cma_c_term_error = 0,
    cma_c_term_normal = 1,
    cma_c_term_alert = 2
    }			cma_t_exit_status;

typedef enum CMA_T_SCHED_INHERIT {
    cma_c_sched_inherit = 0,
    cma_c_sched_use_default = 1
    }			cma_t_sched_inherit;

typedef enum CMA_T_DETACH_STATE {
    cma_c_create_joinable = 0,
    cma_c_create_detached = 1
    }			cma_t_detach_state;

/*
 * The following procedures can be used to control thread creation,
 * termination and deletion.
 */

/*
 * To create a thread object and runnable thread, a routine must be specified
 * as the new thread's start routine.  An argument may be passed to this
 * routine, as an untyped address; an untyped address may also be returned as
 * the routine's value.  An attributes object may be used to specify details
 * about the kind of thread being created.
 */
extern void _CMA_CALL_
cma_thread_create (
	cma_t_thread		*new_thread,
	cma_t_attr		*attr,
	cma_t_start_routine	start_routine,
	cma_t_address		arg);

/*
 * A thread object may be "detached" to specify that the return value and
 * completion status will not be requested.
 */
extern void _CMA_CALL_
cma_thread_detach (
	cma_t_thread	*thread);

/*
 * A thread may terminate it's own execution.
 */
extern void _CMA_CALL_
cma_thread_exit_error (void);

extern void _CMA_CALL_
cma_thread_exit_normal (
	cma_t_address	result);

/*
 * A thread can await termination of another thread and retrieve the return
 * value and completion status of the thread.
 */
extern void _CMA_CALL_
cma_thread_join (
	cma_t_thread		*thread,
	cma_t_exit_status	*exit_status,
	cma_t_address		*result);

/*
 * Operations to define thread creation attributes
 */

typedef	cma_t_integer		cma_t_priority;
typedef	cma_t_integer		cma_t_sched_policy;
#if _CMA_OS_ == _CMA__UNIX
typedef cma_t_integer		cma_t_scope;
#endif

/*
 * Set or obtain the default thread priority.
 */
extern void _CMA_CALL_
cma_attr_set_priority (
	cma_t_attr	*attr,
	cma_t_priority	pri);

extern void _CMA_CALL_
cma_attr_get_priority (
	cma_t_attr	*attr,
	cma_t_priority	*pri);

/*
 * Set or obtain the default scheduling algorithm
 */
extern void _CMA_CALL_
cma_attr_set_sched (
	cma_t_attr		*attr,
	cma_t_sched_policy	policy,
	cma_t_priority		priority);

extern void _CMA_CALL_
cma_attr_get_sched (
	cma_t_attr		*attr,
	cma_t_sched_policy	*policy);

/*
 * Set or obtain whether a thread will use the scheduling attributes set in
 * the attributes object or inherit them from the creating thread.  Note,
 * inheritance is the default.
 */
extern void _CMA_CALL_
cma_attr_set_inherit_sched (
	cma_t_attr		*attr,
	cma_t_sched_inherit	setting);

extern void _CMA_CALL_
cma_attr_get_inherit_sched (
	cma_t_attr		*attr,
	cma_t_sched_inherit	*setting);

/*
 * Set or obtain the default stack size
 */
extern void _CMA_CALL_
cma_attr_set_stacksize (
	cma_t_attr	*attr,
	cma_t_natural	stacksize);

extern void _CMA_CALL_
cma_attr_get_stacksize (
	cma_t_attr	*attr,
	cma_t_natural	*stacksize);

/*
 * Set or obtain the default guard size
 */
extern void _CMA_CALL_
cma_attr_set_guardsize (
	cma_t_attr	*attr,
	cma_t_natural	guardsize);

extern void _CMA_CALL_
cma_attr_get_guardsize (
	cma_t_attr	*attr,
	cma_t_natural	*guardsize);

/*
 * Set or obtain the default contention scope
 */
#if _CMA_OS_ == _CMA__UNIX
extern void _CMA_CALL_
cma_attr_set_scope (
	cma_t_attr	*attr,
	cma_t_scope	scope);

extern void _CMA_CALL_
cma_attr_get_scope (
	cma_t_attr	*attr,
	cma_t_scope	*scope);
#endif
/*
 * Set or obtain the create-already-detached attribute
 */
extern void _CMA_CALL_
cma_attr_get_detachstate (
	cma_t_attr		*att,
	cma_t_detach_state	*setting);

extern void _CMA_CALL_
cma_attr_set_detachstate (
	cma_t_attr		*att,
	cma_t_detach_state	setting);

/*
 * Thread Scheduling Operations
 */

/*
 * Set or obtain the priority of a thread.
 */
extern void _CMA_CALL_
cma_thread_get_priority (
	cma_t_thread	*thread,
	cma_t_priority	*priority);

extern void _CMA_CALL_
cma_thread_set_priority (
	cma_t_thread	*thread,
	cma_t_priority	priority);

/*
 * Set or obtain the scheduling algorithm of a thread.
 */
extern void _CMA_CALL_
cma_thread_get_sched (
	cma_t_thread		*thread,
	cma_t_sched_policy	*policy);

extern void _CMA_CALL_
cma_thread_set_sched (
	cma_t_thread		*thread,
	cma_t_sched_policy	policy,
	cma_t_priority		priority);

/*
 * A thread may tell the scheduler that its processor can be made available.
 */
extern void _CMA_CALL_
cma_yield (void);

/*
 * A thread may enter a wait state for a specified period of time.
 */
extern void _CMA_CALL_
cma_delay (
	cma_t_interval	interval);

/*
 * Bind a thread to a particular CPU on a multiprocessor system.
 */
extern void _CMA_CALL_
cma_thread_bind_to_cpu (
	cma_t_thread	*thread,
	long		cpu_mask);

/*
 * Thread Information Operations
 */

/*
 * A thread may obtain a copy of its own thread handle.
 */
extern void _CMA_CALL_
cma_thread_get_self (
	cma_t_thread	*thread);

/*
 * Get the sequence number of a thread.
 */
extern cma_t_natural _CMA_CALL_
cma_thread_get_unique (
	cma_t_thread	*thread);

/*
 * Operations on Mutexes
 */

typedef	cma_t_handle	cma_t_mutex;

typedef enum CMA_T_MUTEX_KIND {
    cma_c_mutex_fast = 0,
    cma_c_mutex_recursive = 1,
    cma_c_mutex_nonrecursive = 2
    }				cma_t_mutex_kind;

/*
 * Operations to define mutex creation attributes
 */

/*
 * Set or obtain whether mutex locks can nest.
 */
extern void _CMA_CALL_
cma_attr_set_mutex_kind (
	cma_t_attr		*attr,
	cma_t_mutex_kind	nest);

extern void _CMA_CALL_
cma_attr_get_mutex_kind (
	cma_t_attr		*attr,
	cma_t_mutex_kind	*nest);

/*
 * A thread can create and delete mutexes.
 */
extern void _CMA_CALL_
cma_mutex_create (
	cma_t_mutex	*new_mutex,
	cma_t_attr	*attr);

extern void _CMA_CALL_
cma_mutex_delete (
	cma_t_mutex	*mutex);

/*
 * A thread can lock or unlock a mutex.
 */
extern void _CMA_CALL_
cma_mutex_lock (
	cma_t_mutex	*mutex);

extern cma_t_boolean _CMA_CALL_
cma_mutex_try_lock (
	cma_t_mutex	*mutex);

extern void _CMA_CALL_
cma_mutex_unlock (
	cma_t_mutex	*mutex);

/*
 * A thread may synchronize access to external non-thread-safe code or data,
 * preventing conflict with threads created by other facilities, by using the
 * DECthreads "Global Lock".
 */
extern void _CMA_CALL_
cma_lock_global (void);

extern void _CMA_CALL_
cma_unlock_global (void);

/*
 * Operations on condition variables
 */

typedef cma_t_handle	cma_t_cond;

/*
 * A thread can create and delete condition variables.
 */
extern void _CMA_CALL_
cma_cond_create (
	cma_t_cond	*new_condition,
	cma_t_attr	*attr);

extern void _CMA_CALL_
cma_cond_delete (
	cma_t_cond	*condition);

/*
 * A thread can signal to and broadcast on a condition variable.
 */
extern void _CMA_CALL_
cma_cond_broadcast (
	cma_t_cond	*condition);

extern void _CMA_CALL_
cma_cond_signal (
	cma_t_cond	*condition);

extern void _CMA_CALL_
cma_cond_signal_int (
	cma_t_cond	*condition);

extern void _CMA_CALL_
cma_cond_signal_preempt_int (
#if _CMA_OS_ == _CMA__UNIX
	cma_t_cond	*condition,
	cma_t_address	scp
#else
	cma_t_cond	*condition
#endif
	);

/*
 * A thread can wait for a condition variable to be signalled or broadcast.
 */
extern void _CMA_CALL_
cma_cond_wait (
	cma_t_cond	*condition,
	cma_t_mutex	*mutex);

/*
 * Operations for timed waiting
 */

typedef cma_t_integer		cma_t_status;

/*
 * A thread can perform a timed wait on a condition variable.
 */
extern cma_t_status _CMA_CALL_
cma_cond_timed_wait (
	cma_t_cond	*condition,
	cma_t_mutex	*mutex,
	cma_t_date_time	*expiration);

/*
 * A thread may perform some operations on absolute date-time and intervals.
 */

extern void _CMA_CALL_
cma_time_get_expiration (
	cma_t_date_time	*expiration,
	cma_t_interval	interval);

/*
 * Operations for DECthreads and client initialization.
 */

/*
 * Initialize the DECthreads facility. (Use of this routine is not required
 * on OpenVMS, Digital UNIX or Windows NT.)
 */
extern void _CMA_CALL_
cma_init (void);

/*
 * A thread can declare a one-time initialization routine.  The address of
 * the init block and routine are passed as parameters.
 */

typedef void	(*cma_t_init_routine) (cma_t_address arg);

extern void _CMA_CALL_
cma_once (
	cma_t_once		*init_block,
	cma_t_init_routine	init_routine,
	cma_t_address		arg);

/*
 * Operations for per-thread context
 */

typedef	cma_t_natural	cma_t_key;

typedef void		(*cma_t_destructor) (cma_t_address ctx_value);

/*
 * A unique per-thread context key can be obtained for the process
 */
extern void _CMA_CALL_
cma_key_create (
	cma_t_key		*key,
	cma_t_attr		*attr,
	cma_t_destructor	destructor);

/*
 * A thread can set a per-thread context value identified by a key.
 */
extern void _CMA_CALL_
cma_key_set_context (
	cma_t_key	key,
	cma_t_address	context_value);

/*
 * A thread can retrieve a per-thread context value identified by a key.
 */
extern void _CMA_CALL_
cma_key_get_context (
	cma_t_key	key,
	cma_t_address	*context_value);

/*
 * Operations for alerts.
 */

/*
 * The current thread can request that a thread terminate.
 */

extern void _CMA_CALL_
cma_thread_alert (
	cma_t_thread	*thread);

/*
 * The current thread can poll for alert delivery.
 */
extern void _CMA_CALL_
cma_alert_test (void);

/*
 * The current thread can disable asynchronous alert delivery, restore the
 * previous state of asynchronous alert delivery, or enable asynchronous
 * alert delivery.
 */
extern void _CMA_CALL_
cma_alert_disable_asynch (
	cma_t_alert_state	*prior);

extern void _CMA_CALL_
cma_alert_disable_general (
	cma_t_alert_state	*prior);

extern void _CMA_CALL_
cma_alert_enable_asynch (void);

extern void _CMA_CALL_
cma_alert_enable_general (
	cma_t_alert_state	*prior);

extern void _CMA_CALL_
cma_alert_restore (
	cma_t_alert_state	*prior);

/*
 * A thread may check to see if there is sufficient space on its current stack
 */
extern cma_t_boolean _CMA_CALL_
cma_stack_check_limit_np (
	cma_t_integer	size);

/*
 * Debug threads
 */
extern void _CMA_CALL_
cma_debug (void);

/*
 * The cma_debug_cmd() function returns the status of the last specified
 * operation in the command string.
 */
typedef enum CMA_T_DBG_STATUS {
    cma_s_dbg_success = 0,		/* Command was successful */
    cma_s_dbg_quit = 1,			/* Last command was 'quit' or 'exit' */
    cma_s_dbg_nonesel = 2,		/* No objects selected (e.g., "thread -br") */
    cma_s_dbg_successpend = 3,		/* Alternate success */
    cma_s_dbg_nopriv = -1,		/* No privilege for command */
    cma_s_dbg_invparam = -2,		/* Invalid parameter on command */
    cma_s_dbg_invseq = -3,		/* Invalid object sequence number given */
    cma_s_dbg_inconstate = -4,		/* Inconsistent state for operation */
    cma_s_dbg_corrupt = -5,		/* Unable to complete; internal corruption */
    cma_s_dbg_invoption = -6,		/* Invalid command options */
    cma_s_dbg_noarg = -7,		/* Missing command argument */
    cma_s_dbg_invaddr = -8,		/* Invalid address */
    cma_s_dbg_invcmd = -9,		/* Invalid command */
    cma_s_dbg_nullcmd = -10,		/* No command given */
    cma_s_dbg_conflict = -11,		/* Conflicting options */
    cma_s_dbg_unimpl = -12		/* Unimplemented feature */
    } cma_t_dbg_status;

/*
 * Pass a command string to DECthreads debug for interpretation. The
 * argument is a "char *" command string.
 */
extern cma_t_dbg_status _CMA_CALL_
cma_debug_cmd (char *cmd);

#if _CMA_COMPILER_ == _CMA__VAXC
# pragma standard			/* set in cma_config.h */
#elif ((_CMA_COMPILER_ == _CMA__DECC) || (_CMA_COMPILER_ == _CMA__DECCPLUS))
# if _CMA_OS_ == _CMA__VMS
#  pragma __extern_model __restore	/* saved in cma_config.h */
# endif
#endif

#ifdef __cplusplus
    }
#endif

#endif
