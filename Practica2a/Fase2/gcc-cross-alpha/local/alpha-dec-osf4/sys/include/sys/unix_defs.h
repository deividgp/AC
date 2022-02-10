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
 * @(#)$RCSfile: unix_defs.h,v $ $Revision: 4.2.8.16 $ (DEC) $Date: 1994/05/04 22:09:41 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * unix_defs.h:  definitions and macros for extractable UNIX portions
 * of the OSF/1 kernel.
 */
/* 
 * OSF/1 Release 1.0
 */

#ifndef	_UNIX_DEFS_H_
#define	_UNIX_DEFS_H_

#include <kern/lock.h>

#define udecl_lock_data(class,name)	class lock_data_t name;
#define udecl_simple_lock_data(class,name) decl_simple_lock_data(class,name)

#ifdef	_KERNEL

#include <unix_locks.h>
#include <mach_ldebug.h>
#include <mach_assert.h>
#include <bogus_memory.h>
#include <ser_compat.h>
#include <unix_uni.h>
#include <vague_stats.h>
#include <kern/macro_help.h>
#include <kern/assert.h>

/*
 * The OSF/1 kernel can be divided into two portions:  the core kernel,
 * including all the Mach functionality, and the compatibility code,
 * including the filesystem, network, and the Unix interfaces.
 *
 * All of the core code uses lock-based synchronization; in the uni-
 * processor case, simple locks do not get compiled because they are
 * not needed.  In the multiprocessor case, the code is fully
 * parallelized.  Distinguishing between the two cases is done by
 * using the compile-time definition, NCPUS.
 *
 * The compatibility code has also been parallelized but can be built in
 * one of four ways:
 *
 *	1.  Uniprocessor only, with software interrupt synchronization.
 *		Defines:  UNIX_UNI + NCPUS=1
 *	2.  Uniprocessor only, with lock synchronization.
 *		Defines:  UNIX_LOCKS + NCPUS=1
 *	3.  Multiprocessor, with lock synchronization.
 *		Defines:  UNIX_LOCKS + NCPUS>1
 *	4.  Multiprocessor, with lock synchronization and hooks
 *		for compatibility with unparallelized subsystems.
 *		Defines:  UNIX_LOCKS + NCPUS>1 + SER_COMPAT
 *
 * In the first two "uniprocessor" cases, the resulting kernel runs
 * master/slave on a multiprocessor; the Mach core code executes on any
 * processor but the compatibility code runs only on the master processor.
 * Note that using software interrupt synchronization does not imply that
 * no locks are being used at all; just that the original BSD notions of
 * locks are being used rather than OSF locks.
 * 
 * The multiprocessor cases only use lock synchronization.  Interrupt
 * handling is all done at a low-level and what might have been interrupt-
 * level activities in the uniprocessor case (e.g., packet processing) are
 * now handled by additional threads.  When backwards compatibility is
 * turned on so that unparallelized code can be used alongside parallelized
 * code, the kernel pays a time and space penalty to track the various
 * unparallelized portions.
 *
 * Caveat programmer:  there is no internal consistency checking among
 * the various options.
 *
 * There are three debug options that can be used to assist resolving
 * kernel problems.
 *
 *	MACH_LDEBUG turns on lock debugging.  Simple locks will always
 *	be compiled when MACH_LDEBUG is turned on.  Read/write locks
 *	will be checked for common cases like taking the same lock
 *	twice or releasing an unowned lock.  MACH_LDEBUG should be
 *	used in conjunction with MACH_ASSERT.
 *
 *	MACH_ASSERT turns on the assert/ASSERT macros that check
 *	run-time conditions and, if the checks fail, cause a system
 *	panic and crash dump or a pit-stop into the debugger.  There
 *	is a special form of ASSERT, LASSERT, that depends on both
 *	MACH_LDEBUG and MACH_ASSERT being turned on.
 *
 *	XPR_DEBUG records trace messages in a buffer that can be
 *	examined at run-time or in a crash dump.
 *	
 * Lock statistics may be gathered by enabling MACH_LDEBUG.  VAGUE_STATS
 * indicates the user is willing to accept counts that may be slightly off
 * for things like the NFS and RPC operations counts.  When VAGUE_STATS
 * is turned off, simple locks are used around these statistics updates,
 * guaranteeing their accuracy.
 */

#if	__STDC__
#if	UNIX_UNI && UNIX_LOCKS
/* #error this is an error */
#endif
#endif

/*
 * The mp_master and mp_release definitions are used for portions of the
 * Mach code that must interface to Unix without knowing whether the
 * Unix portions have been parallelized.  For unparallelized portions,
 * the Mach code uses mp_master and mp_release, which go away under
 * UNIX_LOCKS but otherwise invoke the unix_* routines.
 */
#if	UNIX_UNI
#define	mp_master()	unix_master()
#define	mp_release()	unix_release()
#endif

#if	UNIX_LOCKS
#define	mp_master()
#define	mp_release()
#endif

#if	!UNIX_LOCKS
/*
 * When locking is disabled for the compatibilty code, synchronization
 * is done via spl's.  The following macros are used for spl synchronization
 * that applies only to the uniprocessor case.  For spl synchronization
 * that must be done in all cases (e.g., when communicating with a device
 * driver) the original, lower-case spl macros must be used.
 *
 * Note that the USPLVAR macro is defined in such a way that it may be used
 * in the middle of a block of declarations as long as the declaration is
 * not followed by a semi-colon.  For example,
 *	int foo;
 *	USPLVAR(s)
 *	int bar;
 * will correctly declare "int s;" when locking is disabled and disappear
 * when locking is enabled.
 */
#define USPLVAR(s)		int s;
#ifdef	__STDC__
#define USPL(s,level)		s = spl##level()
#else
#define USPL(s,level)		s = spl/**/level()
#endif
#define	USPLNET(s)		USPL(s,net)
#define	USPLTTY(s)		USPL(s,tty)
#define	USPLIMP(s)		USPL(s,imp)
#define	USPLBIO(s)		USPL(s,bio)
#define	USPLVM(s)		USPL(s,vm)
#define	USPLHI(s)		USPL(s,hi)
#define	USPLCLOCK(s)		USPL(s,clock)
#define	USPLSOFTCLOCK(s)	USPL(s,softclock)
#define	USPLHIGH(s)		USPL(s,high)
#define	USPLSCHED(s)		USPL(s,sched)
#define USPLX(s)		splx(s)

#else	/* !UNIX_LOCKS */

/*
 * Use locks for synchronization.  Note again that lower-case spl
 * macros must be used to obtain spl synchronization independent of
 * the UNIX_LOCKS conditional.
 */
#define USPLVAR(s)
#define USPL(s,level)
#define	USPLNET(s)
#define	USPLTTY(s)
#define	USPLIMP(s)
#define	USPLBIO(s)
#define	USPLVM(s)
#define	USPLHI(s)
#define	USPLCLOCK(s)
#define	USPLSOFTCLOCK(s)
#define	USPLHIGH(s)
#define	USPLSCHED(s)
#define USPLX(s)

#endif	/* !UNIX_LOCKS */

#if	UNIX_LOCKS

#define ulock_init(l,s)	ulock_setup((l), (struct lockinfo *)0, (s))
extern void		ulock_setup(lock_t, struct lockinfo *, boolean_t);
extern void		ulock_terminate(lock_t);
extern void		ulock_write(lock_t);
extern void		ulock_read(lock_t);
extern void		ulock_done(lock_t);
extern boolean_t	ulock_try_write(lock_t);
extern boolean_t	ulock_try_read(lock_t);
extern void		ulock_write_to_read(lock_t);
extern void		ulock_set_recursive(lock_t);
extern void		ulock_clear_recursive(lock_t);
#define ulock_addr(l)	((lockmode > 0) ? &(l) : (lock_t)0)
#define udecl_lock_info(class,name)	class struct lockinfo *name;
#define usimple_lock(l)			simple_lock(l)
#define usimple_unlock(l)		simple_unlock(l)
#define usimple_lock_try(l)		simple_lock_try(l)
#define usimple_lock_init(l)		simple_lock_init(l)
#define usimple_lock_setup(l,i)		simple_lock_setup(l,i)
#define usimple_lock_terminate(l)	simple_lock_terminate(l)
#define usimple_lock_addr(l)		simple_lock_addr(l)
#define udecl_simple_lock_info(class,name) decl_simple_lock_info(class,name)

#else

#define ulock_init(l,s)
#define ulock_setup(l,i,s)
#define ulock_terminate(l)
#define ulock_write(l)
#define ulock_read(l)
#define ulock_done(l)
#define ulock_try_write(l)		(1)
#define ulock_try_read(l)		(1)
#define ulock_write_to_read(l)
#define ulock_set_recursive(l)
#define ulock_clear_recursive(l)
#define ulock_addr(l)			((lock_t)0)
#define udecl_lock_info(class,name)
#define usimple_lock(l)
#define usimple_unlock(l)
#define usimple_lock_try(l)		(1)
#define usimple_lock_init(l)
#define usimple_lock_setup(l,i)
#define usimple_lock_terminate(l)
#define usimple_lock_addr(l)		((simple_lock_t)0)
#define udecl_simple_lock_info(class,name)

#endif

#define FUNNEL_NULL		(0)

#if	UNIX_LOCKS
#define	MP_ONLY(clause)		(clause)
#define	MP_DECL(decl)		decl;
#define	UNI_ONLY(clause)
#else
#define	MP_ONLY(clause)
#define	MP_DECL(decl)
#define	UNI_ONLY(clause)	(clause)
#endif

/*
 * Statistics.
 */
#if	VAGUE_STATS
#define	vdecl_simple_lock_data(class,name)
#define	VSTATS_LOCK(l)
#define	VSTATS_UNLOCK(l)
#define	VSTATS_LOCK_INIT(l)
#else
#define	vdecl_simple_lock_data(class,name) udecl_simple_lock_data(class,name)
#define	VSTATS_LOCK(l)		usimple_lock(l)
#define	VSTATS_UNLOCK(l)	usimple_unlock(l)
#define	VSTATS_LOCK_INIT(l)	usimple_lock_setup(l, (struct lockinfo *)0)
#endif

#define	STATS_ACTION(l,stmt)						\
MACRO_BEGIN								\
	VSTATS_LOCK(l);							\
	stmt;								\
	VSTATS_UNLOCK(l);						\
MACRO_END

/*
 * Put stmt under control of simple lock l unconditionally (though
 * l is presumed to be a Unix lock).
 */
#define	UCOUNTER_ACTION(l,stmt)						\
MACRO_BEGIN								\
	usimple_lock(l);						\
	stmt;								\
	usimple_unlock(l);						\
MACRO_END

/*
 * Put stmt under control of simple lock l unconditionally (though
 * l is presumed to be a Unix lock).  In addition, disable interrupts
 * around the locking operation.
 */
#define	ICOUNTER_ACTION(l, stmt)					\
MACRO_BEGIN								\
	int s;								\
	s = splhigh();							\
	usimple_lock(l);						\
	stmt;								\
	usimple_unlock(l);						\
	splx(s);							\
MACRO_END

/*
 * Bogus memory locking.  On some architectures, data aligned on
 * "natural" boundaries (e.g., longs always allocated on a longword
 * boundary) can be fetched from memory atomically; i.e., the current
 * value or a slightly stale value can be fetched, but the value will
 * never be trashed as the result of interleaved write operations.
 * Depending on the case, we can take advantage of this property by
 * not holding a lock during the access because the use of the lock
 * makes no difference.  (The Multimax is such a machine.)
 *
 * BM is placed around statements that should only be executed for
 * bogus memory machines.  NM is placed around statements that should
 * only be executed on "nice" memory machines.
 */
#if	BOGUS_MEMORY
#define	BM(clause)	clause
#define	NM(clause)
#else
#define	BM(clause)
#define	NM(clause)	clause
#endif

#endif	/* _KERNEL */

#endif	/* _UNIX_DEFS_H_ */
