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
 * @(#)$RCSfile: tis.h,v $ $Revision: 1.1.18.6 $ (DEC) $Date: 1999/02/11 21:04:36 $
 */
/*
 *  FACILITY:
 *
 *	Thread-Independent Synchronization, a subsidiary of DECthreads
 *
 *  ABSTRACT:
 *
 *	TIS provides synchronization (and other miscellaneous "thread"
 *	services, such as thread-specific data) in a manner that is highly
 *	efficient when DECthreads is not active within the process. When
 *	DECthreads is present these functions are automatically and
 *	transparently remapped into DECthreads, providing multithread
 *	safety.
 *
 *	These interfaces are not intended to be used for threaded code
 *	(i.e., libraries or main programs that create threads). Instead, they
 *	are intended to allow creation of "thread safe" code, which operates
 *	correctly when threads are present, but without the overhead imposed
 *	by thread-safety when run without threads.
 *
 *  AUTHORS:
 *
 *	Webb Scales
 *
 *  CREATION DATE:
 *
 *	29 April 1992
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Paul Clark
 *	Peter Portante
 *	Webb Scales
 *	Mark Simons
 *
 *  LAST MODIFIED:
 *
 *	 7 December 1999
 */

#ifndef _TIS_INCLUDE
#define _TIS_INCLUDE

/*
 * <pthread.h> will include <pthread_exception.h> in order to implement some
 * of its required functionality.  The exception header file will cause a few
 * references to be made to the threads library.  If the including module asks
 * for inline routines, <pthread.h> will also cause a few references to be
 * made to the threads library.  We do not want to reference the threads
 * library if the caller is only include tis.h, so we define the
 * _EXC_NO_EXCEPTIONS_ macro to omit the exception handling funcitionality and
 * we define the _TIS_INCLUDE_ENV macro to prevent any other threads library
 * references.
 */
#define _TIS_INCLUDE_ENV
#define _EXC_NO_EXCEPTIONS_
#include <pthread.h>
#undef _EXC_NO_EXCEPTIONS_
#undef _TIS_INCLUDE_ENV

#if defined (_PTHREAD_ENV_DECC)
# if defined (_PTHREAD_ENV_VMS)
#  if __DECC_VER >= 50200000
#   pragma __environment __save
#  else
#   pragma __extern_model __save
#  endif
# else
#  pragma __environment __save
# endif
# pragma member_alignment
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The following routines comprise the DECthreads "Thread Independent
 * Synchronization" Services. These routines provide the indicated
 * functionality when used in a program or application in which threads are
 * present. In the absence of threads, these functions impose minimal
 * overhead on their caller.
 *
 * TIS objects created using this (new) interface are fully interchangeable
 * with DECthreads core (POSIX 1003.1c-1995) objects. That means that you can
 * create a mutex using static initialization or tis_mutex_init, lock it
 * before initialization of DECthreads, and then unlock the mutex.
 *
 * Other assorted TIS "state", such as thread-specific data keys and values,
 * and cancelation state, are also propagated into DECthreads at
 * initialization. Thread-Specific data values appear in the default (main)
 * thread, as does the cancelation state.
 */

#define _TIS_VERSION 315203


/*
 * TIS configuration symbols
 */
#define _TIS__OSF	1
#define _TIS__VMS	2

#ifndef _TIS_OS_
# if defined (__OSF__) || defined (__osf__)
#  define _TIS_OS_	_TIS__OSF
# elif defined (vms) || defined (__vms) || defined (__VMS)
#  define _TIS_OS_	_TIS__VMS
# elif defined (_WIN32) || defined (WIN32)
#  define _TIS_OS_	_TIS__WIN32
# else
#  error _TIS_OS_ is undefined
# endif
#endif

#define _TIS__ALPHA	1
#define _TIS__VAX	2

#ifndef _TIS_HARDWARE_
# if defined (__alpha) || defined (__ALPHA)
#  define _TIS_HARDWARE_ _TIS__ALPHA
# elif defined (vax) || defined (__vax) || defined (__VAX)
#  define _TIS_HARDWARE_ _TIS__VAX
# elif defined (_M_IX86)
#  define _TIS_HARDWARE_ _TIS__X86
# else
#  error _TIS_HARDWARE_ is undefined
# endif
#endif


/*
 * TIS structure declarations
 */
typedef struct tis_rwlock {
    int			valid;		/* Validation flag */
    int			readers;	/* Number of readers */
    int			rwaits;		/* Waiting readers */
    int			writer;		/* Writer active */
    int			wwaits;		/* Waiting writers */
    pthread_mutex_t	mutex;		/* The mutex itself */
    pthread_cond_t	Wreaders;	/* Wait for read access */
    pthread_cond_t	Wwriters;	/* Wait for write access */
    } tis_rwlock_t, *tis_rwlock_p;

#define TIS_RWLOCK_VALID	0xbeebeac1

#define TIS_RWLOCK_INITIALIZER {TIS_RWLOCK_VALID, 0, 0, 0, 0, \
    PTHREAD_MUTEX_INITIALIZER, \
    PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER}

#define TIS_RWLOCK_INITWITHNAME(_nm_,_am_,_nc1_,_ac1_,_nc2_,_ac2_) \
    {TIS_RWLOCK_VALID, 0, 0, 0, 0, \
    PTHREAD_MUTEX_INITWITHNAME_NP(_nm_,_am_), \
    PTHREAD_COND_INITWITHNAME_NP(_nc1_,_ac1_), \
    PTHREAD_COND_INITWITHNAME_NP(_nc2_,_ac2_)}

/*
 * And a simplified form that uses ANSI C string concatination to form the
 * various object names from a single argument:
 */
#define TIS_RWLOCK_INITWITHNAME1(_nm_,_am_) \
    {TIS_RWLOCK_VALID, 0, 0, 0, 0, \
    PTHREAD_MUTEX_INITWITHNAME_NP(_nm_,_am_), \
    PTHREAD_COND_INITWITHNAME_NP("read-" _nc1_,_ac1_), \
    PTHREAD_COND_INITWITHNAME_NP("write-" _nc2_,_ac2_)}

/*
 * Flags used for tis_mutex_initwithname
 */
typedef enum tis_mflags_tag {
    TIS_MINIT_RECURSIVE =	0x00000001
    } tis_mflags_t;

/*
 * Flags used for tis_allocator_mutex_init
 */
typedef enum tis_alloc_mflags_tag {
    TIS_ALLOC_MUTEX_PSHARED =	0x00000001,
    TIS_ALLOC_MUTEX_NOALLOC =	0x00000002,
    TIS_ALLOC_MUTEX_RECURSIVE =	0x00000004
    } tis_alloc_mflags_t;


#if _TIS_OS_ == _TIS__VMS
 /*
  * On VMS, these routines must begin with "tis$" not "tis_", so use a
  * macro to translate on those platforms.
  */

 /*
  * TIS ERRNO Routines
  */
# define tis_errno_get_addr		tis$errno_get_addr
# define tis_errno_set_value		tis$errno_set_value
# define tis_vmserrno_get_addr		tis$vmserrno_get_addr
# define tis_vmserrno_set_value		tis$vmserrno_set_value

 /*
  * TIS Pthread Routines
  */
# define tis_cond_broadcast		tis$cond_broadcast
# define tis_cond_destroy		tis$cond_destroy
# define tis_cond_init			tis$cond_init
# define tis_cond_signal		tis$cond_signal
# define tis_cond_timedwait		tis$cond_timedwait
# define tis_cond_wait			tis$cond_wait
# define tis_get_expiration		tis$get_expiration
# define tis_getspecific		tis$getspecific
# define tis_key_create			tis$key_create
# define tis_key_create_new		tis$key_create_new
# define tis_key_delete			tis$key_delete
# define tis_lock_global		tis$lock_global
# define tis_mutex_destroy		tis$mutex_destroy
# define tis_mutex_init			tis$mutex_init
# define tis_mutex_initwithname		tis$mutex_initwithname
# define tis_mutex_lock			tis$mutex_lock
# define tis_mutex_trylock		tis$mutex_trylock
# define tis_mutex_unlock		tis$mutex_unlock
# define tis_mutex_unblock		tis$mutex_unblock
# define tis_once			tis$once
# define tis_raise			tis$raise
# define tis_self			tis$self
# define tis_setcancelstate		tis$setcancelstate
# define tis_setspecific		tis$setspecific
# define tis_testcancel			tis$testcancel
# define tis_unlock_global		tis$unlock_global
# define tis_yield			tis$yield

 /*
  * TIS Readers/Writer Locks Routines
  */
# define tis_read_lock			tis$read_lock
# define tis_read_trylock		tis$read_trylock
# define tis_read_unlock		tis$read_unlock
# define tis_rwlock_init		tis$rwlock_init
# define tis_rwlock_destroy		tis$rwlock_destroy
# define tis_write_lock			tis$write_lock
# define tis_write_trylock		tis$write_trylock
# define tis_write_unlock		tis$write_unlock

 /*
  * TIS Asynchronous I/O Routines
  */
# define tis_io_complete		tis$io_complete
# define tis_synch			tis$synch
#endif


/*
 * TIS functions.
 */

/*
 * Get the address of errno
 */
extern int *tis_errno_get_addr (void);

/*
 * Set all known errno cells to a particular value
 */
extern void tis_errno_set_value (
	int	value);

#if _TIS_OS_ == _TIS__VMS
/*
 * Get the address of the VMS-specific errno
 */
extern int *tis_vmserrno_get_addr (void);

/*
 * Set all known VMS-specific errno cells to a particular value
 */
extern void tis_vmserrno_set_value (
	int	value);
#endif

#if _TIS_OS_ == _TIS__OSF
/*
 * Allocate and/or initialize a TIS mutex, and allocate a blocking structure.
 * This function can be used by a malloc-replacement so that it can safely be
 * used by libpthread to allocate blocking structures. (Otherwise, a deadlock
 * may occur when contention occurs on the allocator mutex.)
 *
 * handle	Pointer to a pthread_mutex_t*, in which address of a new mutex
 *		is returned; or, if TIS_ALLOC_MUTEX_NOALLOC is specified, a
 *		pointer to a pthread_mutex_t, which is initialized.
 * allocator	An allocation routine that will be used to allocate the mutex
 *		and blocking structure.
 * arg		A value passed to the allocator. This is not interpreted by
 *		TIS.
 * name		A character string representing the name of the mutex. For
 *		example, "myMalloc". This will show up in Visual Threads and
 *		debugger output when mutexes are displayed (e.g., ladebug's
 *		"show mutex").
 * name_arg	An undocumented and unsupported name argument, which you
 *		should specify as 0.
 * flags	One or more of the values in the tis_alloc_mflags_t enum.
 *		(Yes, they're really flags.) TIS_ALLOC_MUTEX_NOALLOC means
 *		that you have already allocated a pthread_mutex_t before
 *		making the call, and "handle" is a pointer to that structure.
 */
extern int
tis_allocator_mutex_init (
	void		*handle,		/* handle */
	void		*(*allocator)(size_t size, void *arg), /* callback */
	void		*arg,			/* allocator argument */
	const char	*name,			/* (mutex name) */
	unsigned int	name_arg,
	unsigned long	flags);			/* (tis_alloc_mflags_t) */
#endif

/*
 * Broadcast on a TIS condition variable
 *
 * "cond" is the address of the condition variable, passed by reference, on
 * which to broadcast.
 */
extern int tis_cond_broadcast (
	pthread_cond_t	*cond);

/*
 * Destroys a TIS condition variable
 *
 * "cond" is the address of the condition variable, passed by reference,
 * which is to be destroyed or "uninitialized".
 */
extern int tis_cond_destroy (
	pthread_cond_t	*cond);

/*
 * Initialize a TIS condition variable.
 *
 * "cond" is a pointer to an condition variable, passed by reference, which
 * is initialized.
 */
extern int tis_cond_init (
	pthread_cond_t	*cond);

/*
 * Signal a TIS condition variable
 *
 * "cond" is the address of the abstract condition variable, passed by
 * reference, on which to signal.
 */
extern int tis_cond_signal (
	pthread_cond_t	*cond);

/*
 * Wait on a TIS condition variable
 *
 * "cond" is the address of the condition variable, passed by reference, on
 * which to wait. "mutex" is the address of the mutex, passed by reference,
 * which is associated with "cond".
 */
extern int tis_cond_wait (
	pthread_cond_t	*cond,
	pthread_mutex_t	*mutex);

/*
 * Timed Wait on a TIS condition variable
 *
 * "cond" is the address of the condition variable, passed by reference, on
 * which to wait. "mutex" is the address of the mutex, passed by reference,
 * which is associated with "cond".  "abstime" is the address of the timespec
 * containing the absolute time in which the wait expires.
 */
extern int tis_cond_timedwait (
	pthread_cond_t	*cond,
	pthread_mutex_t	*mutex,
	const struct timespec *abstime);

/*
 * Get an expiration time, in preparation for calling tis_cond_timedwait()
 *
 * "delta" is the address of the timespec structure that is the number of
 * seconds and nanoseconds to add to the current system time.
 * "abstime" is the address of the timespec structure of the result 
 * representing the absolute expiration time computed from the current system
 * time plus the given "delta".
 */
extern int tis_get_expiration (
	const struct timespec *delta,
	struct timespec *abstime);

/*
 * Lock the TIS global lock
 */
extern int tis_lock_global (void);

/*
 * Create a thread specific data (tsd) key.
 *
 * "key" is the address of a variable which will receive the key value; this
 * value is used in calls to tis_setspecific() and tis_getspecific() to get
 * and set the value associated with this key. The same key value is used in
 * each thread to access that thread's context, when and if DECthreads is
 * initialized in the process.
 *
 * "Destructor" is the address of a routine which is called to destroy (e.g.,
 * deallocate) the thread-specific data value when a thread terminates with a
 * non-NULL value for the key. If DECthreads is initialized after a TIS tsd
 * key is created, the key (and destructor) is taken over by DECthreads
 * transparently.
 */
extern int tis_key_create (
	pthread_key_t		*key,
	__pthreadDestructor_t	destructor);

/*
 * Create a thread specific data (tsd) "constructor" key.
 *
 * "key" is the address of a variable which will receive the key
 * value; this value is used in calls to tis_setspecific() and
 * tis_getspecific() to get and set the value associated with this
 * key. The same key value is used in each thread to access that
 * thread's context, when and if DECthreads is initialized in the
 * process.
 *
 * "Constructor" is the address of a routine which is called to create
 * a value when a new thread is created. Constructor will also be
 * called with appropriate arguments for each CURRENTLY EXISTING
 * THREAD when the key is created, if the PTHREAD_KEY_ALLTHREAD_NP
 * flag is specified. The call, in this case, it made in the context
 * of the thread that creates the key, and thus cannot call anything
 * else that relies upon thread context.
 *
 * "Destructor" is the address of a routine which is called to destroy
 * (e.g., deallocate) the thread-specific data value when a thread
 * terminates with a non-NULL value for the key. Note that the
 * prototype for constructor key destructor routines is different than
 * that of the destructor for normal keys. When a constructor key
 * created with the PTHREAD_KEY_ALLTHREAD_NP flag is deleted by
 * calling tis_key_delete or pthread_key_delete, the destructor is
 * called for all currently existing threads -- again, in the context
 * of the thread deleting the key.
 *
 * If DECthreads is initialized after a TIS tsd key is created, the
 * key (and destructor) is taken over by DECthreads transparently.
 */
extern int tis_key_create_new (
	pthread_key_t			*key,
	__pthreadConstructor_t		constructor,
	__pthreadExtDestructor_t	destructor,
	int				flags);

/*
 * Delete a thread specific data (tsd) key.
 *
 * Deletes a thread specific data key previously returned by
 * tis_key_create(). The application must free any storage or do any cleanup
 * on the data structures associated with the key. The cleanup may be done
 * before or after tis_key_delete is called.
 */
extern int tis_key_delete (
	pthread_key_t	key);

/*
 * Get the thread specific data (tsd) value associated with a particular key.
 *
 * "Key" is a key value returned by a call to tis_key_create(). The thread
 * specific data value associated with this key is returned by the call to
 * the tis_getspecific().
 */
extern void *tis_getspecific (
	pthread_key_t	key);

/*
 * Initialize a TIS mutex
 *
 * "mutex" is a pointer to a mutex, which will be initialized.
 */
extern int tis_mutex_init (
	pthread_mutex_t	*mutex);

/*
 * Initialize a TIS mutex with additional parameters
 *
 * "mutex" is a pointer to a mutex, which will be initialized. You may specify 
 * a name for the mutex, and you may set the mutex "recursive". The "arg"
 * parameter is officially undefined, and you should specify 0. Also, the name 
 * string should be a string literal, or other storage that will remain for
 * the life of the mutex -- the library will not copy the string.
 */
extern int tis_mutex_initwithname (
	pthread_mutex_t	*mutex,
	const char	*name,			/* (mutex name) */
	int		arg,
	int		flags);			/* (tis_mflags_t) */

/*
 * Destroy a TIS mutex
 *
 * "mutex" is the address of the mutex which is to be destroyed. The mutex
 * object becomes "uninitialized".
 */
extern int tis_mutex_destroy (
	pthread_mutex_t	*mutex);

/*
 * Lock a TIS mutex
 *
 * "mutex" is the address of the mutex which is to be locked.
 */
extern int tis_mutex_lock (
	pthread_mutex_t	*mutex);

/*
 * Non-blocking TIS mutex lock
 *
 * "mutex" is the address of the mutex which is to be locked.
 *
 * The function returns a boolean value indicating if the mutex was
 * successfully locked.
 */
extern int tis_mutex_trylock (
	pthread_mutex_t	*mutex);

/*
 * Unlock a TIS mutex
 *
 * "mutex" is the address of the mutex which is to be unlocked.
 */
extern int tis_mutex_unlock (
	pthread_mutex_t	*mutex);

/*
 * Unblock from a TIS mutex
 *
 * "mutex" is the address of the mutex from which threads may be unblocked.
 */
extern int tis_mutex_unblock (
	pthread_mutex_t	*mutex);

/*
 * Execute a one-time initialization routine.
 *
 * The specified routine is called exactly once during a program's execution,
 * even if multiple threads call tis_once() simultaneously. This is useful
 * for performing one-time initialization tasks (e.g., for a facility API),
 * such as creating mutexes and thread specific data keys. (Although note
 * that with statically initialized mutexes, it's rarely necessary to call
 * tis_once.)
 *
 * "once_control" is the address of a one-time initialization control block.
 * This should be in static storage and unique to the initialization routine.
 * "init_routine" is the address of the initialization routine to call.
 */
extern int tis_once (
	pthread_once_t	*once_control,
	void		(*init_routine) (void));

/*
 *  Raise (send) the signal to the current thread or process.
 */
extern int tis_raise (
	int	sig);

/*
 * Get current thread "ID". NOTE: without DECthreads, this returns a
 * "prototype" TEB which is not used by DECthreads. The value returned by
 * tis_self within the main thread will change when DECthreads initializes!
 */
extern pthread_t tis_self (void);

/*
 * Set the caller's cancelability to state, and return the previous
 * cancelability state to the location referenced by oldstate.
 */
extern int tis_setcancelstate (
	int	state,
	int	*oldstate);

/*
 * Set the thread specific data (tsd) value associated with a particular key.
 *
 * "Key" is a key value returned by a call to tis_key_create(). "Value" is
 * value to be associated with this key. Once set, this value can be
 * retrieved in this thread using the same key in a call to
 * tis_getspecific().
 */
extern int tis_setspecific (
	pthread_key_t	key,
	const void	*value);

/*
 * Creates a cancellation point in the calling thread. Has no effect if
 * cancelability is disabled or DECthreads is not initialized.
 */
extern void tis_testcancel (void);

/*
 * Unlock the TIS global lock
 */
extern int tis_unlock_global (void);

/*
 *  Yield this thread to another.
 */
extern void tis_yield (void);

/*
 * Initialize a readers/writer lock
 */
extern int tis_rwlock_init (
	tis_rwlock_t *lock);

/*
 * Destroy a readers/writer lock.
 */
extern int tis_rwlock_destroy (
	tis_rwlock_t *lock);

/*
 * Locks a readers/writer lock for read.
 */
extern int tis_read_lock (
	tis_rwlock_t *lock);

/*
 * Locks a readers/writer lock for write.
 */
extern int tis_write_lock (
	tis_rwlock_t *lock);

/*
 * Tries to lock a readers/writer lock for read. Does not wait if lock is
 * unavailable.
 */
extern int tis_read_trylock (
	tis_rwlock_t *lock);

/*
 * Tries to lock a readers/writer lock for write. Does not wait if lock is
 * unavailable.
 */
extern int tis_write_trylock (
	tis_rwlock_t *lock);

/*
 * Unlocks the readers/writer lock from read access.
 */
extern int tis_read_unlock (
	tis_rwlock_t *lock);

/*
 * Unlocks the readers/writer lock from write access.
 */
extern int tis_write_unlock (
	tis_rwlock_t *lock);

#if _TIS_OS_ == _TIS__VMS
/*
 * Declare completion of Asynchronous I/O operation.
 *
 * Note: this routine can be called from AST level.
 */
extern void tis_io_complete (void);

/*
 * Wait for Asynchronous I/O to complete.
 */
extern unsigned long tis_synch (unsigned long efn, void *iosb);
#endif

/*
 * Define the inline mutex operations using pthread_mutex_*_prim* macros. We
 * need to define the inline macros using the __tis_mutex_*() version since
 * the name of the tis_mutex_* routines are defined to their inline counter
 * parts. We need to access the routine names directly in the macros, though.
 */
#if defined(_PTHREAD_USE_ASM_) \
	&& !defined(_PTHREAD_SKIP_LOOPY_ASM_) \
	&& (defined (_PTHREAD_USE_INLINE) || defined (_TIS_CORE_BUILD_))

__inline static int
tis_mutex_lock_inline (pthread_mutex_t* __mutex)
    {
    int	__status;


    if ((__mutex->_Pfield(lock) & _PTHREAD_MSTATE_SLOW)
	    || (pthread_mutex_lock_prim (__mutex)))
# if _TIS_OS_ == _TIS__OSF
	__status = __tis_mutex_lock (__mutex);
# else
	__status = tis$mutex_lock (__mutex);
# endif
    else
	__status = 0;

    return __status;
    }

__inline static int
tis_mutex_trylock_inline (pthread_mutex_t* __mutex)
    {
    int __status;


    if (__mutex->_Pfield(lock) & _PTHREAD_MSTATE_SLOW)
# if _TIS_OS_ == _TIS__OSF
	__status = __tis_mutex_trylock (__mutex);
# else
	__status = tis$mutex_trylock (__mutex);
# endif
    else {

	if (pthread_mutex_lock_prim (__mutex))
	    __status = EBUSY;
	else
	    __status = 0;

	}

    return __status;
    }

__inline static int
tis_mutex_unlock_inline (pthread_mutex_t* __mutex)
    {
    int __status;


    if ((__mutex->_Pfield(lock) & _PTHREAD_MSTATE_SLOW)
	    || (pthread_mutex_unlock_prim (__mutex)))
	/*
	 * We need to call unblock because there may be threads waiting on
	 * the mutex (or we're metering or otherwise "slow").  Unblock is
	 * responsible for unlocking the mutex.
	 */
# if _TIS_OS_ == _TIS__OSF
	__status = __tis_mutex_unblock (__mutex);
# else
	__status = tis$mutex_unblock (__mutex);
# endif
    else
	__status = 0;

    return __status;
    }

# ifdef _PTHREAD_USE_INLINE
#  ifdef tis_mutex_lock
#   undef tis_mutex_lock
#   undef tis_mutex_trylock
#   undef tis_mutex_unlock
#  endif
#  define tis_mutex_lock		tis_mutex_lock_inline
#  define tis_mutex_trylock		tis_mutex_trylock_inline
#  define tis_mutex_unlock		tis_mutex_unlock_inline
# endif
#else
# define tis_mutex_lock_inline		tis_mutex_lock
# define tis_mutex_trylock_inline	tis_mutex_trylock
# define tis_mutex_unlock_inline	tis_mutex_unlock
#endif


#if defined (_PTHREAD_ENV_DECC)
# if defined (_PTHREAD_ENV_VMS)
#  if __DECC_VER >= 50200000
#   pragma __environment __restore
#  else
#   pragma __extern_model __restore
#  endif
# else
#  pragma __environment __restore
# endif
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _TIS_INCLUDE */
