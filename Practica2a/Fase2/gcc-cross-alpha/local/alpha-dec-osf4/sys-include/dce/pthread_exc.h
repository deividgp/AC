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
 * @(#)$RCSfile: pthread_exc.h,v $ $Revision: 4.2.17.2 $ (DEC) $Date: 1998/10/02 21:42:01 $
 */
/*
 *  FACILITY:
 *
 *	DECthreads core
 *
 *  ABSTRACT:
 *
 *	External definitions for DECthreads POSIX 1003.4a/D4 exception
 *	services (ALL are non-standard, in that while resembling the
 *	1003.4a/D4 interfaces they report error by raising exceptions rather
 *	than returning -1 and setting errno).
 *
 *  AUTHORS:
 *
 *	Paul Curtin
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	27 August 1990
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Paul Clark
 *	Paul Curtin
 *	Steve Johnson
 *	Brian Keane
 *	Peter Portante
 *	Webb Scales
 *
 *  LAST MODIFIED:
 *
 *	16 September 1998
 */

#ifndef PTHREAD_EXC
#define PTHREAD_EXC

#ifdef __cplusplus
    extern "C" {
#endif

#if defined(vms) || defined(__vms) || defined(VMS) || defined(__VMS) 
# include <cma.h>
# ifndef _TIMESPEC_T_
#  define _TIMESPEC_T_
typedef struct timespec {
    unsigned long	tv_sec;		/* seconds */
    long		tv_nsec;	/* nanoseconds */
    } timespec_t;
# endif
#else
# include <dce/cma.h>
# include <signal.h>
#endif

/*
 * The implementation makes these basic decisions
 */

#ifndef _POSIX_THREADS
# define _POSIX_THREADS				1
#endif
#ifndef _POSIX_THREAD_ATTR_STACKSIZE
# define _POSIX_THREAD_ATTR_STACKSIZE		1
#endif
#if _CMA_POSIX_SCHED_
# define _POSIX_THREADS_REALTIME_SCHEDULING	1
#elif defined(_POSIX_THREADS_REALTIME_SCHEDULING)
# undef _POSIX_THREADS_REALTIME_SCHEDULING
#endif
#ifndef _POSIX_THREADS_PER_PROCESS_SIGNALS_1
# define _POSIX_THREADS_PER_PROCESS_SIGNALS_1	1
#endif


#if ((_CMA_COMPILER_ != _CMA__DECCPLUS) && (_CMS_OS_ == _CMA__UNIX))
/*
 * Implement push and pop for cancellation handlers, using the compiler's
 * native try/finally constructs.
 */
# define pthread_cleanup_push(_routine_,_arg_) \
    { \
    pthread_cleanup_t _XXX_proc = (pthread_cleanup_t)(_routine_); \
    pthread_addr_t _XXX_arg = (pthread_addr_t)(_arg_); \
    int _XXX_completed = 0; \
    try {

# define pthread_cleanup_pop(_execute_) \
    _XXX_completed = 1;} \
    finally { \
	if ((! _XXX_completed) || (_execute_)) _XXX_proc (_XXX_arg);} \
    }
#else
/*
 * Implement push and pop for cancellation handlers, using TRY and ENDTRY
 */
# define pthread_cleanup_push(_routine_,_arg_) \
    { \
    pthread_cleanup_t _XXX_proc = (pthread_cleanup_t)(_routine_); \
    pthread_addr_t _XXX_arg = (pthread_addr_t)(_arg_); \
    int _XXX_completed = 0; \
    TRY {

# define pthread_cleanup_pop(_execute_) \
    _XXX_completed = 1;} \
    FINALLY { \
	if ((! _XXX_completed) || (_execute_)) _XXX_proc (_XXX_arg);} \
    ENDTRY}
#endif

/*
 *  Macros used to convert normal pthread routine calls to exception 
 *  returning routines.  This is done by including this file, pthread_exc.h,
 *  in the place of pthread.h.
 */

#define pthread_equal_np(__t1,__t2) \
    ptdexc_equal (__t1,__t2)

#define pthread_equal(__t1,__t2) \
    ptdexc_equal (__t1,__t2)

#define pthread_attr_create(__attr) \
    ptdexc_attr_create (__attr)

#define pthread_attr_delete(__attr) \
    ptdexc_attr_delete (__attr)

#define pthread_attr_setdetach_np(__attr,__detachstate) \
    ptdexc_attr_setdetach_np (__attr,__detachstate)

#define pthread_attr_getdetach_np(__attr) \
    ptdexc_attr_getdetach_np (__attr)

#define pthread_attr_setprio(__attr,__priority) \
    ptdexc_attr_setprio (__attr,__priority)

#define pthread_attr_getprio(__attr) \
    ptdexc_attr_getprio (__attr)

#define pthread_attr_setsched(__attr,__scheduler) \
    ptdexc_attr_setsched (__attr,__scheduler)

#define pthread_attr_getsched(__attr) \
    ptdexc_attr_getsched (__attr)

#define pthread_attr_setinheritsched(__attr,__inherit) \
    ptdexc_attr_setinheritsched (__attr,__inherit)

#define pthread_attr_getinheritsched(__attr) \
    ptdexc_attr_getinheritsched (__attr)

#define pthread_attr_setstacksize(__attr,__stacksize) \
    ptdexc_attr_setstacksize (__attr,__stacksize)

#define pthread_attr_getstacksize(__attr) \
    ptdexc_attr_getstacksize (__attr)

#define pthread_attr_setguardsize_np(__attr,__guardsize) \
    ptdexc_attr_setguardsize_np (__attr,__guardsize)

#define pthread_attr_getguardsize_np(__attr) \
    ptdexc_attr_getguardsize_np (__attr)

#define pthread_bind_to_cpu_np(__thread,__mask) \
    ptdexc_bind_to_cpu_np (__thread,__mask)

#define pthread_create(__thread,__attr,__start_routine,__arg) \
    ptdexc_create (__thread,__attr,__start_routine,__arg)

#define pthread_detach(__thread) \
    ptdexc_detach (__thread)

#define pthread_exit(__status) \
    ptdexc_exit (__status)

#define pthread_get_expiration_np(__delta,__abstime) \
    ptdexc_get_expiration_np (__delta,__abstime)

#define pthread_join(__thread,__status) \
    ptdexc_join (__thread,__status)

#define pthread_setprio(__thread,__priority) \
    ptdexc_setprio (__thread,__priority)

#define pthread_setscheduler(__thread,__scheduler,__priority) \
    ptdexc_setscheduler (__thread,__scheduler,__priority)

#define pthread_yield() \
    ptdexc_yield ()

#define pthread_self() \
    ptdexc_self ()

#define pthread_getunique_np(__thread) \
    ptdexc_getunique_np (__thread)

#define pthread_getprio(__thread) \
    ptdexc_getprio (__thread)

#define pthread_getscheduler(__thread) \
    ptdexc_getscheduler (__thread)

#define pthread_mutexattr_create(__attr) \
    ptdexc_mutexattr_create (__attr)

#define pthread_mutexattr_delete(__attr) \
    ptdexc_mutexattr_delete (__attr)

#define pthread_mutexattr_setkind_np(__attr,__kind) \
    ptdexc_mutexattr_setkind_np (__attr,__kind)

#define pthread_mutexattr_getkind_np(__attr) \
    ptdexc_mutexattr_getkind_np (__attr)

#define pthread_mutexattr_setmetered_np(__attr,__meter) \
    ptdexc_mutexattr_setmetered_np (__attr,__meter)

#define pthread_mutexattr_getmetered_np(__attr) \
    ptdexc_mutexattr_getmetered_np (__attr)

#define pthread_mutex_init(__mutex,__attr) \
    ptdexc_mutex_init (__mutex,__attr)

#define pthread_mutex_destroy(__mutex) \
    ptdexc_mutex_destroy (__mutex)

#define pthread_mutex_lock(__mutex) \
    ptdexc_mutex_lock (__mutex)

#define pthread_mutex_trylock(__mutex) \
    ptdexc_mutex_trylock (__mutex)

#define pthread_mutex_unlock(__mutex) \
    ptdexc_mutex_unlock (__mutex)

#define pthread_condattr_create(__attr) \
    ptdexc_condattr_create (__attr)

#define pthread_condattr_delete(__attr) \
    ptdexc_condattr_delete (__attr)

#define pthread_cond_init(__cond,__attr) \
    ptdexc_cond_init (__cond,__attr)

#define pthread_cond_destroy(__cond) \
    ptdexc_cond_destroy (__cond)

#define pthread_cond_broadcast(__cond) \
    ptdexc_cond_broadcast (__cond)

#define pthread_cond_signal(__cond) \
    ptdexc_cond_signal (__cond)

#define pthread_cond_signal_int_np(__cond) \
    ptdexc_cond_signal_int_np (__cond)

#if _CMA_OS_ == _CMA__UNIX
# define pthread_cond_sig_preempt_int_np(__cond,__arg) \
    ptdexc_cond_sigprmpt_int_np (__cond,__arg)
#else
# define pthread_cond_sig_preempt_int_np(__cond) \
    ptdexc_cond_sigprmpt_int_np (__cond)
#endif

#define pthread_cond_wait(__cond,__mutex) \
    ptdexc_cond_wait (__cond,__mutex)

#define pthread_cond_timedwait(__cond,__mutex,__abstime) \
    ptdexc_cond_timedwait (__cond,__mutex,__abstime)

#define pthread_once(__once_block,__init_routine) \
    ptdexc_once (__once_block,__init_routine)

#define pthread_keycreate(__key,__destructor) \
    ptdexc_keycreate (__key,__destructor)

#define pthread_setspecific(__key,__value) \
    ptdexc_setspecific (__key,__value)

#define pthread_getspecific(__key,__value) \
    ptdexc_getspecific (__key,__value)

#define pthread_cancel(__thread) \
    ptdexc_cancel (__thread)

#define pthread_testcancel() \
    ptdexc_testcancel ()

#define pthread_setasynccancel(__state) \
    ptdexc_setasynccancel (__state)

#define pthread_setcancel(__state) \
    ptdexc_setcancel (__state)

#define pthread_delay_np(__interval) \
    ptdexc_delay_np (__interval)

#define pthread_lock_global_np() \
    ptdexc_lock_global_np ()

#define pthread_unlock_global_np() \
    ptdexc_unlock_global_np ()

# if _CMA_OS_ != _CMA__VMS
#  define pthread_sig_to_can_thread_np(__sigset,__target,__thread) \
    ptdexc_sig_to_can_thread_np (__sigset,__target,__thread)

#  define pthread_signal_to_cancel_np(__sigset,__target) \
    ptdexc_signal_to_cancel_np (__sigset,__target)
# endif

/*
 * Sample decisions for the environment types
 */

typedef cma_t_key		pthread_key_t;

typedef cma_t_address		pthread_addr_t;

/*
 * For compatibility with OSF/1 pthreads
 */
typedef pthread_addr_t		any_t;

typedef void (*pthread_cleanup_t) (pthread_addr_t arg);

/*
 * Sample decision for a one-time initialization control block and its
 * initialization macro.
 *
 * Declare a one time initialization control block as:
 *
 *	static pthread_once_t	block = pthread_once_init;
 */
typedef cma_t_once	pthread_once_t;

#define pthread_once_init	cma_once_init

#define CANCEL_ON	1
#define CANCEL_OFF	0

/*
 * The following are the portable pthread definitions
 */

/*
 * Operations on Handles
 */

/*
 * Operations on attributes objects
 */

typedef cma_t_attr	pthread_attr_t;


/*
 * An attributes object is created to specify the attributes of other CMA
 * objects that will be created.
 */

void _CMA_CALL_
ptdexc_attr_create (pthread_attr_t	*attr);

/*
 * An attributes object can be deleted when it is no longer needed.
 */

void _CMA_CALL_
ptdexc_attr_delete (pthread_attr_t	*attr);

/*
 * Operations on threads
 */

typedef cma_t_thread		pthread_t;
typedef cma_t_start_routine	pthread_startroutine_t;
typedef pthread_startroutine_t	pthread_func_t;

#define PTHREAD_INHERIT_SCHED	(int)cma_c_sched_inherit
#define PTHREAD_DEFAULT_SCHED	(int)cma_c_sched_use_default

#define PTHREAD_CREATE_JOINABLE	(int)cma_c_create_joinable
#define PTHREAD_CREATE_DETACHED	(int)cma_c_create_detached

#if !_CMA_RT4_KTHREAD_
# define SCHED_FIFO		cma_c_sched_fifo
# define SCHED_RR		cma_c_sched_rr
# define SCHED_OTHER		cma_c_sched_throughput
# define SCHED_FG_NP		cma_c_sched_throughput
# define SCHED_BG_NP		cma_c_sched_background
#endif

#define PRI_FIFO_MIN		cma_c_prio_fifo_min
#define PRI_FIFO_MAX		cma_c_prio_fifo_max
#define PRI_RR_MIN		cma_c_prio_rr_min
#define PRI_RR_MAX		cma_c_prio_rr_max
#define PRI_FG_MIN_NP		cma_c_prio_through_min
#define PRI_FG_MAX_NP		cma_c_prio_through_max
#define PRI_BG_MIN_NP		cma_c_prio_back_min
#define PRI_BG_MAX_NP		cma_c_prio_back_max
#define PRI_OTHER_MIN		cma_c_prio_through_min
#define PRI_OTHER_MAX		cma_c_prio_through_max


int _CMA_CALL_
ptdexc_equal (				/* Compare two handles */
	pthread_t	handle1,
	pthread_t	handle2);

/*
 * Operations to define thread creation attributes
 */

/*
 * Set or obtain the default thread priority.
 */
void _CMA_CALL_
ptdexc_attr_setprio (
	pthread_attr_t	*attr,
	int		priority);

int _CMA_CALL_
ptdexc_attr_getprio (pthread_attr_t	attr);

/*
 * Set or obtain the default scheduling algorithm
 */
void _CMA_CALL_
ptdexc_attr_setsched (
	pthread_attr_t	*attr,
	int		scheduler);

int _CMA_CALL_
ptdexc_attr_getsched (
	pthread_attr_t	attr);

/*
 * Set or obtain whether a thread will use the default scheduling attributes,
 * or inherit them from the creating thread.
 */
void _CMA_CALL_
ptdexc_attr_setinheritsched (
	pthread_attr_t	*attr,
	int		inherit);

int _CMA_CALL_
ptdexc_attr_getinheritsched (pthread_attr_t	attr);

/*
 * Set or obtain the default stack size
 */
void _CMA_CALL_
ptdexc_attr_setstacksize (
	pthread_attr_t	*attr,
	long		stacksize);

unsigned long _CMA_CALL_
ptdexc_attr_getstacksize (pthread_attr_t	attr);

/*
 * Set or obtain the default guard size
 */
void _CMA_CALL_
ptdexc_attr_setguardsize_np (
	pthread_attr_t	*attr,
	long		guardsize);

unsigned long _CMA_CALL_
ptdexc_attr_getguardsize_np (pthread_attr_t	attr);

/*
 * Set or obtain the detach state
 */
void _CMA_CALL_
ptdexc_attr_setdetach_np (
	pthread_attr_t	*attr,
	int		detachstate);

int _CMA_CALL_
ptdexc_attr_getdetach_np (pthread_attr_t	attr);

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
void _CMA_CALL_
ptdexc_create (
	pthread_t		*thread,
	pthread_attr_t		attr,
	pthread_startroutine_t	start_routine,
	pthread_addr_t		arg);

/*
 * A thread object may be "detached" to specify that the return value and
 * completion status will not be requested.
 */
void _CMA_CALL_
ptdexc_detach (pthread_t	*thread);

/* 
 * A thread may terminate it's own execution.
 */
void _CMA_CALL_
ptdexc_exit (pthread_addr_t	status);

/* 
 * A thread can await termination of another thread and retrieve the return
 * value of the thread.
 */
void _CMA_CALL_
ptdexc_join (
	pthread_t	thread,
	pthread_addr_t	*status);

/*
 * Thread Scheduling Operations
 */

/*
 * The current user_assigned priority of a thread can be changed.
 */
int _CMA_CALL_
ptdexc_setprio (
	pthread_t	thread,
	int		priority);

/*
 * The current user_assigned scheduler algorithm of a thread can be changed.
 */
int _CMA_CALL_
ptdexc_setscheduler (
	pthread_t	thread,
	int		scheduler,
	int		priority);

/*
 * A thread may tell the scheduler that its processor can be made available.
 */
void _CMA_CALL_
ptdexc_yield (void);

/*
 * Bind a thread to a particular CPU on a multiprocessor system.
 */
void _CMA_CALL_
ptdexc_bind_to_cpu_np (
	pthread_t	thread,
	long		cpu_mask);

/*
 * Thread Information Operations
 */

/*
 * A thread may obtain a copy of its own thread handle.
 */
pthread_t _CMA_CALL_
ptdexc_self (void);

/*
 * Obtain a thread's sequence number. This will usually be a unique integer
 * across all threads within a process (until a large number of threads has
 * been created).
 */
long _CMA_CALL_
ptdexc_getunique_np (pthread_t	*thread);

/*
 * The current user_assigned priority of a thread can be read.
 */
int _CMA_CALL_
ptdexc_getprio (pthread_t	thread);

/*
 * The current user_assigned scheduler algorithm of a thread can be read.
 */
int _CMA_CALL_
ptdexc_getscheduler (pthread_t	thread);

/*
 * Operations on Mutexes
 */
#define MUTEX_FAST_NP		(int)cma_c_mutex_fast
#define MUTEX_RECURSIVE_NP	(int)cma_c_mutex_recursive
#define MUTEX_NONRECURSIVE_NP	(int)cma_c_mutex_nonrecursive

typedef cma_t_attr	pthread_mutexattr_t;
typedef cma_t_mutex	pthread_mutex_t;

void _CMA_CALL_
ptdexc_mutexattr_create (pthread_mutexattr_t	*attr);

void _CMA_CALL_
ptdexc_mutexattr_delete (pthread_mutexattr_t	*attr);

void _CMA_CALL_
ptdexc_mutexattr_setkind_np (
	pthread_mutexattr_t	*attr,
	int			kind);

int _CMA_CALL_
ptdexc_mutexattr_getkind_np (pthread_mutexattr_t	attr);

void _CMA_CALL_
ptdexc_mutexattr_setmetered_np (
	pthread_mutexattr_t	*attr,
	int			meter);

int _CMA_CALL_
ptdexc_mutexattr_getmetered_np (pthread_mutexattr_t	attr);

/* 
 * The following routines create, delete, lock and unlock mutexes.
 */
void _CMA_CALL_
ptdexc_mutex_init (
	pthread_mutex_t		*mutex,
	pthread_mutexattr_t	attr);

void _CMA_CALL_
ptdexc_mutex_destroy (pthread_mutex_t	*mutex);

void _CMA_CALL_
ptdexc_mutex_lock (pthread_mutex_t	*mutex);

int _CMA_CALL_
ptdexc_mutex_trylock (pthread_mutex_t	*mutex);

void _CMA_CALL_
ptdexc_mutex_unlock (pthread_mutex_t	*mutex);

/*
 * Operations on condition variables
 */
typedef cma_t_attr	pthread_condattr_t;
typedef cma_t_cond	pthread_cond_t;

void _CMA_CALL_
ptdexc_condattr_create (pthread_condattr_t	*attr);

void _CMA_CALL_
ptdexc_condattr_delete (pthread_condattr_t	*attr);

/*
 * A thread can create and delete condition variables.
 */
void _CMA_CALL_
ptdexc_cond_init (
	pthread_cond_t		*cond,
	pthread_condattr_t	attr);

void _CMA_CALL_
ptdexc_cond_destroy (pthread_cond_t	*cond);

/*
 * A thread can signal to and broadcast on a condition variable.
 */
void _CMA_CALL_
ptdexc_cond_broadcast (pthread_cond_t	*cond);

void _CMA_CALL_
ptdexc_cond_signal (pthread_cond_t	*cond);

void _CMA_CALL_
ptdexc_cond_signal_int_np (pthread_cond_t	*cond);

void _CMA_CALL_
ptdexc_cond_sigprmpt_int_np (
#if _CMA_OS_ == _CMA__UNIX
	pthread_cond_t	*condition,
	pthread_addr_t	scp);
#else
	pthread_cond_t	*condition);
#endif

/*
 * A thread can wait for a condition variable to be signalled or broadcast.
 */
void _CMA_CALL_
ptdexc_cond_wait (
	pthread_cond_t	*cond,
	pthread_mutex_t	*mutex);

/*
 * Operations for timed waiting
 */

/*
 * A thread can perform a timed wait on a condition variable.
 */
int _CMA_CALL_
ptdexc_cond_timedwait (
	pthread_cond_t	*cond,
	pthread_mutex_t	*mutex,
	struct timespec	*abstime);

/*
 * Operations for client initialization.
 */
typedef void (*pthread_initroutine_t) (void);

void _CMA_CALL_
ptdexc_once (
	pthread_once_t		*once_block,
	pthread_initroutine_t	init_routine);

/*
 * Operations for per-thread context
 */
typedef cma_t_destructor	pthread_destructor_t;

/*
 * A unique per-thread context key can be obtained for the process
 */
void _CMA_CALL_
ptdexc_keycreate (
	pthread_key_t		*key,
	pthread_destructor_t	destructor);

/*
 * A thread can set a per-thread context value identified by a key.
 */
void _CMA_CALL_
ptdexc_setspecific (
	pthread_key_t	key,
	pthread_addr_t	value);

/*
 * A thread can retrieve a per-thread context value identified by a key.
 */
void _CMA_CALL_
ptdexc_getspecific (
	pthread_key_t	key,
	pthread_addr_t	*value);

/*
 * Operations for alerts.
 */

/*
 * The current thread can request that a thread terminate it's execution.
 */

void _CMA_CALL_
ptdexc_cancel (pthread_t	thread);

/*
 * The current thread can poll for alert delivery.
 */
void _CMA_CALL_
ptdexc_testcancel (void);

/*
 * The current thread can enable or disable alert delivery (PTHREAD
 * "cancels"); it can control "general cancelability" (CMA "defer") or
 * just "asynchronous cancelability" (CMA "asynch disable").
 */
int _CMA_CALL_
ptdexc_setasynccancel (int	state);

int _CMA_CALL_
ptdexc_setcancel (int	state);

#ifndef _CMA_SUPPRESS_EXTERNALS_
_CMA_IMPORT_ pthread_attr_t		pthread_attr_default;
_CMA_IMPORT_ pthread_mutexattr_t	pthread_mutexattr_default;
_CMA_IMPORT_ pthread_condattr_t		pthread_condattr_default;
#endif

/*
 * Define nonportable extensions
 */

extern void _CMA_CALL_
ptdexc_get_expiration_np (
	struct timespec	*delta,
	struct timespec	*abstime);

extern void _CMA_CALL_
ptdexc_delay_np (struct timespec	*interval);

extern void _CMA_CALL_
ptdexc_lock_global_np (void);

extern void _CMA_CALL_
ptdexc_unlock_global_np (void);

#if _CMA_OS_ != _CMA__VMS
extern void  _CMA_CALL_
ptdexc_sig_to_can_thread_np (
	sigset_t	*sigset,
	pthread_t	*target,
	pthread_t	*thread);

extern void  _CMA_CALL_
ptdexc_signal_to_cancel_np (
	sigset_t	*sigset,
	pthread_t	*target);
#endif

#ifdef __cplusplus
    }
#endif

#endif
