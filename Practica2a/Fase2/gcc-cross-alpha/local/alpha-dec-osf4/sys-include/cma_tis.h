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
 * @(#)$RCSfile: cma_tis.h,v $ $Revision: 1.1.10.2 $ (DEC) $Date: 1998/10/02 21:42:22 $
 */
/*
 *  FACILITY:
 *
 *	Thread-Independent Synchronization, a subsidiary of DECthreads
 *
 *  ABSTRACT:
 *
 *	This header defines OBSOLETE interfaces. While programs using these
 *	interfaces will continue to be supported, Digital recommends that you
 *	use the improved interfaces described in <tis.h>.
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
 *	Peter Portante
 *	Webb Scales
 *	Mary Sullivan
 *
 *  LAST MODIFIED:
 *
 *	13 May 1998
 */
#ifndef _CMA_TIS_
#define _CMA_TIS_

/*
 * CMA_TIS configuration symbols
 */
#define _CMA_TIS__OSF	1
#define _CMA_TIS__VMS	2

#ifndef _CMA_TIS_OS_
# if defined (__OSF__) || defined (__osf__)
#  define _CMA_TIS_OS_	_CMA_TIS__OSF
# elif defined (vms) || defined (__vms) || defined (__VMS)
#  define _CMA_TIS_OS_	_CMA_TIS__VMS
# elif defined (_WIN32) || defined (WIN32)
#  define _CMA_TIS_OS_	_CMA_TIS__WIN32
# else
#  error _CMA_TIS_OS_ is undefined
# endif
#endif

#define _CMA_TIS__ALPHA	1
#define _CMA_TIS__VAX	2
#define _CMA_TIS__X86	3

#ifndef _CMA_TIS_HARDWARE_
# if defined (__alpha) || defined (__ALPHA)
#  define _CMA_TIS_HARDWARE_ _CMA_TIS__ALPHA
# elif defined (vax) || defined (__vax) || defined (__VAX)
#  define _CMA_TIS_HARDWARE_ _CMA_TIS__VAX
# elif defined (_M_IX86)
#  define _CMA_TIS_HARDWARE_ _CMA_TIS__X86
# else
#  error _CMA_TIS_HARDWARE_ is undefined
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * On OpenVMS Alpha, make sure that all the "obsolete" TIS interfaces treat
 * client values as strictly 32-bit addresses for compatibility.  If you need
 * 64 bit pointers, you must upgrade to the "native" TIS interfaces.
 */
#if (_CMA_TIS_OS_ == _CMA_TIS__VMS) && (_CMA_TIS_HARDWARE_ == _CMA_TIS__ALPHA)
# if __INITIAL_POINTER_SIZE == 64
#  pragma __required_pointer_size __save
#  pragma __required_pointer_size __short
# endif
#endif

/*
 * General address type
 */
typedef void	*cma_tis_addr_t;

/*
 * TIS condition variable: the address of an internal condition variable object.
 */
typedef cma_tis_addr_t	cma_tis_cond_t;

/*
 * TIS mutex: the address of an internal mutex object.
 */
typedef cma_tis_addr_t	cma_tis_mutex_t;

#if (_CMA_TIS_OS_ == _CMA_TIS__VMS) && (_CMA_TIS_HARDWARE_ == _CMA_TIS__ALPHA)
# if __INITIAL_POINTER_SIZE == 64
#  pragma __required_pointer_size __restore
# endif
#endif

/*
 * TIS one-time initialization control block and its initialization macro.
 *
 * Declare a one time initialization control block as:
 *
 *      static cma_tis_once_t	block = cma_tis_once_init;
 */
typedef struct cma_tis_once_tag {
    long	field1;
    long	field2;
    long	field3;
    }				cma_tis_once_t;

#define cma_tis_once_init	{0, 0, 0}

/*
 * Per-thread context types
 */
typedef long cma_tis_key_t;
typedef void (*cma_tis_destructor_t) (cma_tis_addr_t value);

/*
 * TIS thread-ID: the address of a internal thread object.
 */
typedef cma_tis_addr_t	cma_tis_thread_t;


#if _CMA_TIS_OS_ == _CMA_TIS__VMS
  /*
   * On VMS, these routines must begin with "CMA$" not "cma_", so use a
   * macro to translate on those platforms.
   */
# define cma_tis_errno_get_addr		CMA$TIS_ERRNO_GET_ADDR
# define cma_tis_errno_set_value	CMA$TIS_ERRNO_SET_VALUE
# define cma_tis_vmserrno_get_addr	CMA$TIS_VMSERRNO_GET_ADDR
# define cma_tis_vmserrno_set_value	CMA$TIS_VMSERRNO_SET_VALUE
# define cma_tis_cond_create		CMA$TIS_COND_CREATE
# define cma_tis_cond_delete		CMA$TIS_COND_DELETE
# define cma_tis_cond_broadcast		CMA$TIS_COND_BROADCAST
# define cma_tis_cond_signal		CMA$TIS_COND_SIGNAL
# define cma_tis_cond_wait		CMA$TIS_COND_WAIT
# define cma_tis_key_create		CMA$TIS_KEY_CREATE
# define cma_tis_key_get_context	CMA$TIS_KEY_GET_CONTEXT
# define cma_tis_key_set_context	CMA$TIS_KEY_SET_CONTEXT
# define cma_tis_lock_global		CMA$TIS_LOCK_GLOBAL
# define cma_tis_mutex_create		CMA$TIS_MUTEX_CREATE
# define cma_tis_mutex_delete		CMA$TIS_MUTEX_DELETE
# define cma_tis_mutex_lock		CMA$TIS_MUTEX_LOCK
# define cma_tis_mutex_trylock		CMA$TIS_MUTEX_TRYLOCK
# define cma_tis_mutex_unlock		CMA$TIS_MUTEX_UNLOCK
# define cma_tis_once			CMA$TIS_ONCE
# define cma_tis_thread_get_self	CMA$TIS_THREAD_GET_SELF
# define cma_tis_unlock_global		CMA$TIS_UNLOCK_GLOBAL
#endif

/*
 * TIS functions.
 */

#if (_CMA_TIS_OS_ == _CMA_TIS__VMS) && (_CMA_TIS_HARDWARE_ == _CMA_TIS__ALPHA)
# if __INITIAL_POINTER_SIZE == 64
#  pragma __required_pointer_size __save
#  pragma __required_pointer_size __short
# endif
#endif

/*
 * Get the address of errno
 */
extern int *
cma_tis_errno_get_addr (void);

/*
 * Set all known errno cells to a particular value
 */
extern void
cma_tis_errno_set_value (
	int value);

#if _CMA_TIS_OS_ == _CMA_TIS__VMS
/*
 * Get the address of the VMS-specific errno
 */
extern int *
cma_tis_vmserrno_get_addr (void);

/*
 * Set all known VMS-specific errno cells to a particular value
 */
extern void
cma_tis_vmserrno_set_value (
	int value);

#endif

/*
 * Create a TIS condition variable.
 *
 * "cond" is a pointer to an abstract condition variable, passed by reference,
 * which receives the address of the new condition variable object.
 */
extern int
cma_tis_cond_create (
	cma_tis_cond_t *cond);

/*
 * Delete a TIS condition variable
 *
 * "cond" is the address of the abstract condition variable, passed by
 * reference, which is to be deleted.
 */
extern int
cma_tis_cond_delete (
	cma_tis_cond_t *cond);

/*
 * Broadcast on a TIS condition variable
 *
 * "cond" is the address of the abstract condition variable, passed by
 * reference, on which to broadcast.
 */
extern int
cma_tis_cond_broadcast (
	cma_tis_cond_t *cond);

/*
 * Signal a TIS condition variable
 *
 * "cond" is the address of the abstract condition variable, passed by
 * reference, on which to signal.
 */
extern int
cma_tis_cond_signal (
	cma_tis_cond_t *cond);

/*
 * Wait on a TIS condition variable
 *
 * "cond" is the address of the abstract condition variable, passed by
 * reference, on which to wait.  "mutex" is the address of the abstract mutex,
 * passed by reference, which is associated with "cond".
 */
extern int
cma_tis_cond_wait (
	cma_tis_cond_t	*cond,
	cma_tis_mutex_t	*mutex);

/*
 * Lock and unlock the DECthreads global lock (if present).
 */
extern int
cma_tis_lock_global (void);

extern int
cma_tis_unlock_global (void);

/*
 * Create a per-thread context (also known as "thread-specific storage" key).
 *
 * "Key" is the address of a cell which will receive the key value; this
 * value is used in calls to cma_tis_key_set_context() and
 * cma_tis_key_get_context() to get and set the per-thread context associated
 * with this key.  The same key value is used in each thread to access that
 * thread's context.
 * "Destructor" is the address of a routine which is called to destroy
 * (e.g., deallocate) the per-thread context value when the thread terminates.
 */
extern int
cma_tis_key_create (
	cma_tis_key_t		*key,
	cma_tis_destructor_t	destructor);

/*
 * Get the per-thread context value associated with a particular key.
 *
 * "Key" is a key value returned by a call to cma_tis_key_create().
 * "Value" is the address of a cell which will receive the per-thread context
 * value associated with this key.  The value returned is dependent on the
 * value of the key specified, but unaffected by the actions of any other
 * threads.
 */
extern int
cma_tis_key_get_context (
	cma_tis_key_t	key,
	cma_tis_addr_t	*value);

/*
 * Set the per-thread context value associated with a particular key.
 *
 * "Key" is a key value returned by a call to cma_tis_key_create().
 * "Value" is value to be associated with this key.  Once set, this value
 * can be retrieved in this thread using the same key in a call to
 * cma_tis_key_get_context(); however, other threads' use of this key value
 * is unaffected.
 */
extern int
cma_tis_key_set_context (
	cma_tis_key_t	key,
	cma_tis_addr_t	value);

/*
 * Create a TIS mutex
 *
 * "mutex" is a pointer to an abstract mutex, passed by reference, which
 * receives the address of the new mutex object.
 */
extern int
cma_tis_mutex_create (
	cma_tis_mutex_t *mutex);

/*
 * Delete a TIS mutex
 *
 * "mutex" is the address of the abstract mutex, passed by reference, which is
 * to be deleted.
 */
extern int
cma_tis_mutex_delete (
	cma_tis_mutex_t *mutex);

/*
 * Lock a TIS mutex
 *
 * "mutex" is the address of the abstract mutex, passed by reference, which is
 * to be locked.
 */
extern int
cma_tis_mutex_lock (
	cma_tis_mutex_t *mutex);

/*
 * Non-blocking TIS mutex lock
 *
 * "mutex" is the address of the abstract mutex, passed by reference, which is
 * to be locked.
 *
 * The function returns a boolean value indicating if the mutex was
 * successfully locked.
 */
extern int
cma_tis_mutex_trylock (
	cma_tis_mutex_t *mutex);

/*
 * Unlock a TIS mutex
 *
 * "mutex" is the address of the abstract mutex, passed by reference, which is
 * to be unlocked.
 */
extern int
cma_tis_mutex_unlock (
	cma_tis_mutex_t *mutex);

/*
 * Execute a one-time initialization routine.
 *
 * The specified routine is called exactly once during a program's execution,
 * even if multiple threads call cma_tis_once() simultaneously.  This is
 * useful for performing one-time initialization tasks (e.g., for a facility
 * API), such as creating mutexes and per-thread-context keys.
 *
 * "init_block" is the address of a one-time initialization control block.  This
 * should be in static storage and unique to the initialization routine.
 * "init_routine" is the address of the initialization routine to call.
 * "arg" is a user argument which is passed to the initialization routine.
 */
extern int
cma_tis_once (
	cma_tis_once_t	*init_block,
	void		(*init_rtn) (cma_tis_addr_t arg),
	cma_tis_addr_t	init_arg);

/*
 * Get current thread "ID".  (Returns zero if there are no threads.)
 */
extern cma_tis_thread_t
cma_tis_thread_get_self (void);

#if (_CMA_TIS_OS_ == _CMA_TIS__VMS) && (_CMA_TIS_HARDWARE_ == _CMA_TIS__ALPHA)
# if __INITIAL_POINTER_SIZE == 64
#  pragma __required_pointer_size __restore
# endif
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _CMA_TIS_ */
