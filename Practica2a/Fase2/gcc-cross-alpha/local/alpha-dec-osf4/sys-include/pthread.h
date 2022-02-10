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
 * @(#)$RCSfile: pthread.h,v $ $Revision: 1.1.64.7 $ (DEC) $Date: 1999/02/17 18:46:20 $
 */
/*
 *  FACILITY:
 *
 *	DECthreads POSIX 1003.1c
 *
 *  ABSTRACT:
 *
 *	External definitions for POSIX 1003.1c interfaces
 *
 *	General notice: some of the types defined and used in this header are
 *	not standard POSIX 1003.1c types. The DECthreads specific types are
 *	generally used instead of "void *" and "long" where pointer size
 *	#pragma declarations are necessary to support the OpenVMS Alpha 64-bit
 *	programming environment. (And in a few other cases where it's
 *	convenient.) These types should not present any obstacle to programs
 *	coded using the standard types. The "addon" types are distinguished by
 *	naming convention -- they begin with "__pthread" and the remainder
 *	appears in mixed-case without punctuation. For example,
 *	"__pthreadLongAddr_t" for "void *" and "__pthreadLongUint_t" for
 *	"unsigned long".
 *
 *	This header file contains extensive comments regarding the structures
 *	and options. Please read them carefully before relying upon any
 *	undocumented features -- they're undocumented for a reason! We want
 *	you to be able to take advantage of them where appropriate, but you
 *	must also understand the restrictions and risks.
 *
 *  AUTHORS:
 *
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	January 1995
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Paul Clark
 *	Steve Johnson
 *	Richard Love
 *	Peter Portante
 *	Webb Scales
 *	Brian Silver
 *	Mark Simons
 *
 *  LAST MODIFICATION DATE:
 *
 *	 4 February 1999
 */

#ifndef _PTHREAD_HEADER
# define _PTHREAD_HEADER

/******************************************************************************
 *
 * NOTICE: Temporary support for POSIX 1003.4a/D4 migration
 * --------------------------------------------------------
 *
 * Support 1003.4a/D4 ("DCE threads") source migration mode by allowing
 * programmer to cause #include <pthread.h> to define the old interfaces (with
 * modified names) if the _PTHREAD_USE_D4 macro is defined. This is equivalent
 * to #include <pthread_d4.h> -- the remainder of this header file is not
 * processed.
 *
 * In practice, the easiest way to do this is to continue to build threaded
 * code using the "-threads" switch, which will define _PTHREAD_USE_D4:
 *
 *	cc -threads foo.c
 *
 * Or, you can invoke the source migration mode by the following sequence
 * within your .c or .h files:
 *
 *	#define _PTHREAD_USE_D4
 *	#include <pthread.h>
 *
 * Or, finally, by modifying your Makefile (or manual build sequence) to use
 * the -D compiler option. (Note: you must ALWAYS define _REENTRANT when
 * compiling threaded or thread-safe code on Digital UNIX. Using "cc -threads"
 * or "cc -pthread" does this automatically.)
 *
 *	cc -D_PTHREAD_USE_D4 -D_REENTRANT foo.c
 *
 * On OpenVMS, use the #define solution, or the following DECC command (it is
 * not necessary to define _REENTRANT on OpenVMS):
 *
 *	cc /define=_PTHREAD_USE_D4 foo.c
 *
 * The POSIX 1003.4a/D4 migration support may be retired (this clause will be
 * removed from pthread.h!) in the next major release of each operating system
 * (OpenVMS VAX, OpenVMS Alpha, and Digital UNIX) that occurs at least one
 * year after the initial release of the POSIX 1003.1c interfaces in Digital
 * UNIX 4.0 and OpenVMS 7.0.
 *
 *****************************************************************************/

#if defined (_PTHREAD_USE_D4) || defined (PTHREAD_USE_D4)
# if defined (__unix__) || defined (__unix) || defined (unix)
#  include <dce/pthread_d4.h>
# else
#  include <pthread_d4.h>
# endif
#else

/******************************************************************************
 *
 * NOTICE: inline function performance vs. binary compatibility
 * ------------------------------------------------------------
 *
 * This version of pthread.h supports the capability of generating inlined
 * code on OpenVMS Alpha and Digital UNIX for improved performance on some
 * critical operations -- especially mutex synchronization and reading thread
 * specific data.
 *
 * There is a balance between performance and maintainability, however. Inline
 * code sequences cannot be transparently fixed by future versions of
 * DECthreads. Thus, if a bug is found in the inlined code and later fixed,
 * programs using the inlined sequences must be recompiled to acquire the fix.
 * Additionally changes may be made to inlined sequences to improve
 * reliability or performance in the future. Digital cannot guarantee that the
 * new sequences will be binary compatible with the old sequences, and
 * therefore any such changes may also require recompilation.
 *
 * By default, this version of pthread.h will generate calls to carefully
 * tuned assembly code functions within DECthreads that implement the same
 * algorithm as the inline asm() code sequences. This provides safety at the
 * expense of performance by adding the overhead of a call and some
 * unavoidable procedure prolog and epilog code. If you need the performance
 * advantage of avoiding those calls, AND ARE WILLING TO ACCEPT THE RISK THAT
 * YOU WILL NEED TO RECOMPILE LATER, define the preprocessor symbol
 * _PTHREAD_USE_INLINE before including this header file; either by compiling
 * with
 *
 *	cc -D_PTHREAD_USE_INLINE
 *
 * or by using "#define" before including this header file:
 *
 *	#define _PTHREAD_USE_INLINE
 *	#include <pthread.h>
 *
 * Although _PTHREAD_USE_INLINE is made available for experimentation and
 * where the need for performance is extreme, Digital STRONGLY RECOMMENDS that
 * use of this option be avoided.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * NOTICE: DECthreads metered sychronization and static mutex initialization
 * -------------------------------------------------------------------------
 *
 * When a program using DECthreads is run with the environment variable
 * PTHREAD_CONFIG containing the option "METER=1", DECthreads will record all
 * synchronization operations. Normally, when a mutex is statically
 * initialized using PTHREAD_MUTEX_INITIALIZER that mutex is excluded from
 * metering until the first time a thread is required to block on the mutex
 * (when contention occurs). Although this may be fine, during debugging it's
 * often useful to know when "nonblocking" locks occur, as well.
 *
 * If the preprocessor symbol _PTHREAD_NOMETER_STATIC is not defined when this
 * header file is included, statically initialized mutexes will be set up such
 * that the first attempt to lock the mutex (regardless of whether the thread
 * must block) will involve a call into DECthreads. If metering is enabled the
 * operation (and all future operations on the mutex) will be metered. If
 * metering is not enabled, the mutex will be modified such that nonblocking
 * locks (and unlocks without waiters) will not require additional calls into
 * DECthreads. In other words, when metering is not enabled the extra cost of
 * the default mode (_PTHREAD_NOMETER_STATIC not defined) is a single call the
 * first time a thread uses each mutex.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * NOTICE: POSIX 1003.1c support
 * -----------------------------
 *
 * The POSIX 1003.1c-1995 standard was formally approved at the June 1995
 * meeting of the IEEE Standards Board. The correct configuration test macro
 * for strictly conforming POSIX 1003.1c-1995 applications is
 *
 *	#define _POSIX_C_SOURCE 199506L
 *
 * The POSIX standard requires that, for portability, the application must
 * define _POSIX_C_SOURCE within each compilation unit, for example, by
 * compiling with -D_POSIX_C_SOURCE=199506L. The Digital UNIX <standards.h>
 * will default _POSIX_C_SOURCE to the latest POSIX 1003.1 revision supported
 * by the operating system (currently 1003.1c-1995) if no other confining
 * standard definitions are already defined. In other words, unless the
 * programmer specifies a specific restriction, the programmer will have
 * access to all standards that aren't inherently incompatible.
 *
 * Compiling with some other standards modes will disable POSIX 1003.1c-1995
 * support, as the thread interfaces violate name space rules required by
 * those standards. For example, defining any of the symbols _POSIX_SOURCE
 * (1003.1-1990), _POSIX_C_SOURCE=199309L (1003.1b-1993), _XOPEN_SOURCE or
 * _XOPEN_SOURCE_EXTENDED (UNIX95 or earlier, which require 1003.1-1990), or
 * _ANSI_C_SOURCE (ANSI C) will disable thread support. A program built with
 * any of these options that includes <pthread.h> will not compile properly,
 * as <sys/types.h> will fail to define types and symbols required by
 * pthread.h.
 *
 * Note that the Single UNIX Specification, Version 2 (UNIX98) from The Open
 * Group (X/Open) provides threads, and therefore defining _XOPEN_SOURCE=500
 * (XSH5) does not conflict with use of POSIX threads. In fact XSH5 requires
 * that setting _XOPEN_SOURCE=500 overrides "inappropriate" settings of
 * _POSIX_C_SOURCE, _POSIX_SOURCE, or _ANSI_C_SOURCE.
 *
 * The <unistd.h> header always defines _POSIX_VERSION to the latest POSIX.1
 * revision supported by the system -- 199506L (1003.1c-1995) for Digital UNIX
 * 4.0. A portable program can use this symbol (or specific POSIX feature test
 * macros such as _POSIX_THREADS, also defined in <unistd.h>) to determine
 * whether the system supports POSIX 1003.1c-1995. (However, beware that
 * implementations of early drafts of 1003.1c, such as "DCE threads", which
 * supported 1003.4a/D4, may also define _POSIX_THREADS, but will not define
 * _POSIX_VERSION to 199506L.)
 *
 *****************************************************************************/

#if defined (__cplusplus) || defined (__DECCXX)
# define _PTHREAD_ENV_CXX
#endif

#if defined (__DECC) || defined (__decc)
# define _PTHREAD_ENV_DECC
#endif

/*
 * Many features of DECC and DECCXX are common, so this macro allows us to
 * avoid unnecessarily checking both. But for features of one that aren't
 * shared by the other, don't use this one.
 */
#if defined (_PTHREAD_ENV_CXX) || defined (_PTHREAD_ENV_DECC)
# define _PTHREAD_ENV_DECC_CXX
#endif

#if defined (VMS) || defined (__VMS) || defined (__vms) || defined (vms)
# define _PTHREAD_ENV_VMS
#endif

#if defined (__unix__) || defined (__unix) || defined (unix)
# define _PTHREAD_ENV_UNIX
#endif

#if defined (_WIN32) || defined (WIN32)
# define _PTHREAD_ENV_WIN32
#endif

#if defined (vax) || defined (VAX) || defined (__vax) || defined (__VAX)
# define _PTHREAD_ENV_VAX
#endif

#if defined (__alpha) || defined (__ALPHA)
# define _PTHREAD_ENV_ALPHA
#endif

#if defined (_M_IX86)
# define _PTHREAD_ENV_X86
#endif

#if !defined (_PTHREAD_ENV_DECC) && defined (_PTHREAD_ENV_VAX)
# if defined (vaxc) || defined (VAXC) || defined (__vaxc) || defined (__VAXC)
#  define _PTHREAD_ENV_VAXC
# endif
#endif

#ifdef _PTHREAD_ENV_CXX
    extern "C" {
#endif

#if defined (_PTHREAD_ENV_DECC_CXX)
# if defined (_PTHREAD_ENV_VMS)
#  if (__DECC_VER >= 50200000) || (__DECCXX_VER >= 50200000)
#   pragma __environment __save
#  else
#   pragma __extern_model __save
#  endif
#  pragma __extern_model __strict_refdef
# else
#  pragma __environment __save
# endif
# pragma member_alignment
# define _PTHREAD_IMPORT_	extern
#elif defined (_PTHREAD_ENV_VAXC)
# pragma nostandard
# define _PTHREAD_IMPORT_	globalref
#else
# define _PTHREAD_IMPORT_	extern
#endif

/*
 * Enable reentrant errno.h
 */
#ifdef _PTHREAD_ENV_UNIX
# ifndef _REENTRANT
#  define _REENTRANT	1
# endif
#endif
#ifdef _PTHREAD_ENV_WIN32
# ifndef _MT
#  error "Please compile the module including pthread.h with /MT"
# endif
#endif

#ifdef _PTHREAD_ENV_UNIX
# include <standards.h>
# include <unistd.h>
#endif

#include <stddef.h>

#if defined (_PTHREAD_ENV_UNIX) && !defined (_PTHREAD_CORE_BUILD_)
# define _PTHREAD_EXC_INCL_CLEAN
#endif
#include <pthread_exception.h>
#ifdef _PTHREAD_EXC_INCL_CLEAN
# undef _PTHREAD_EXC_INCL_CLEAN
#endif

#ifdef _PTHREAD_ENV_UNIX
# if !defined (_PTHREAD_ENV_CXX) && defined (_OSF_SOURCE)
#  if defined (__DECC)
#   include <c_asm.h>
#   define _PTHREAD_USE_ASM_		1
#  endif
# endif
# define _PTHREAD_USE_MANGLED_NAMES_	1
# if defined (_PTHREAD_ENV_DECC) && !defined (_PTHREAD_LEGACY_NP)
#  define _PTHREAD_USE_PTDNAM_
# endif
# define _PTDNAM(name) __##name
# include <sched.h>
# include <timers.h>
# include <sys/types.h>
# include <time.h>
#else
# include <types.h>
# if defined (_PTHREAD_ENV_DECC) && (__DECC_VER >= 50260000)
#  include <timers.h>
# else
#  ifndef _TIMESPEC_T_
#   define _TIMESPEC_T_
typedef struct timespec {
    unsigned long	tv_sec;		/* seconds */
    long		tv_nsec;	/* nanoseconds */
    } timespec_t;
#  endif
# endif
# ifndef _SCHEDPARAM_T_
#  define _SCHEDPARAM_T_
typedef struct sched_param {
    int sched_priority;
    } sched_param_t;
# endif
# ifndef sched_yield
#  define sched_yield	pthread_yield_np
# endif
#endif

#ifdef _PTHREAD_ENV_WIN32
# include <windows.h>
# include <time.h>
# define _PTHREAD_CALL_			__stdcall
# define _PTHREAD_CDECL_CALL_		__cdecl
# ifndef _PTHREAD_ENV_CXX
#  define _PTHREAD_USE_ASM_		1
# endif
#else
# define _PTHREAD_CALL_
# define _PTHREAD_CDECL_CALL_
#endif

#ifndef _PTDNAM
# define _PTDNAM(name) name
#endif

#if defined (_PTHREAD_ENV_VMS) && defined (_PTHREAD_ENV_ALPHA)
# if defined (__DECC) && (__DECC_VER >= 50000000)
#  define _PTHREAD_USE_ASM_		1
#  if __DECC_VER < 50230004
#   define _PTHREAD_SKIP_LOOPY_ASM_	1
#  endif
#  include <c_asm.h>
# endif
# define _PTHREAD_ALLOW_MIXED_PROTOS_	1
#endif

#if !defined (_PTHREAD_ENV_UNIX)
/*
 * If we are not a UNIX system, then the field names for the POSIX standard
 * types don't have to be name space protected.
 */
# define _Pfield(_arg_)	_arg_
#endif

#ifdef _PTHREAD_ENV_VAXC
/*
 * If compiling on OpenVMS VAX under VAX C, define missing POSIX 1003.1c error
 * symbols to the values used by DEC C so they'll match what DECthreads
 * returns.
 */
# ifdef ENOSYS
#  undef ENOSYS
# endif
# define ENOSYS		76
# ifdef ENOTSUP
#  undef ENOTSUP
# endif
# define ENOTSUP	81
# ifdef EDEADLK
#  undef EDEADLK
# endif
# define EDEADLK	82
#endif

/*
 * On Windows, there is no errno value of ETIMEDOUT.  Many of the DECthreads
 * routines rely on the definition of this value, so we define it here to be
 * its Win32 counterpart, WAIT_TIMEOUT.  This is the value returned by all of
 * the Win32 "WaitFor...Object()" routines if a timeout has occurred.
 *
 * There is also no definition for ENOTSUP in Windows. Since this is a part
 * of the POSIX requirements, define it here.
 *
 * Use '__asm' (the Microsoft C compiler's inline assembly keyword) instead of
 * 'asm'.
 */
#ifdef _PTHREAD_ENV_WIN32
# define ETIMEDOUT	WAIT_TIMEOUT
# define ENOTSUP	99
# define asm		__asm
#endif


/******************************************************************************
 *
 * NOTICE: Digital UNIX and Win32 "name mangling" in initial release
 * -----------------------------------------------------------------
 *
 * On Digital UNIX, maintaining binary compatibility for call_shared code
 * using the old 1003.4a/D4 interfaces (many of which have the same names as
 * the 1003.1c functions) requires that the compatibility interfaces retain
 * their names. Since the 1003.4a/D4 and 1003.1c functions must be able to
 * coexist within a process, this inevitably leads to the conclusion that we
 * must give the 1003.1c functions "mangled" names during the 1 year
 * 1003.4a/D4 retirement period.
 *
 * To that end, we map the 1003.1c standard names into "mangled" internal
 * names. When 1003.4a/D4 is retired these macros will be removed; the 1003.1c
 * functions will then be given their proper names. Binary compatibility for
 * images compiled during the retirement period will be retained by aliases
 * for the transition names. Note that we "mangle" only the names that are
 * identical to 1003.4a/D4 names. New functions (such as pthread_key_delete)
 * and functions with changed names (such as pthread_key_create, contrasted to
 * 1003.4a/D4's pthread_keycreate) are not mangled.
 *
 * The following names are "mangled":
 *
 *	pthread_attr_getguardsize_np
 *	pthread_attr_getinheritsched
 *	pthread_attr_getstacksize
 *	pthread_attr_setguardsize_np
 *	pthread_attr_setinheritsched
 *	pthread_attr_setstacksize
 *	pthread_cancel
 *	pthread_cond_broadcast
 *	pthread_cond_destroy
 *	pthread_cond_init
 *	pthread_cond_sig_preempt_int_np
 *	pthread_cond_signal
 *	pthread_cond_signal_int_np
 *	pthread_cond_timedwait
 *	pthread_cond_wait
 *	pthread_create
 *	pthread_delay_np
 *	pthread_detach
 *	pthread_equal
 *	pthread_exit
 *	pthread_get_expiration_np
 *	pthread_getspecific
 *	pthread_join
 *	pthread_lock_global_np
 *	pthread_mutex_destroy
 *	pthread_mutex_init
 *	pthread_mutex_lock
 *	pthread_mutex_trylock
 *	pthread_mutex_unlock
 *	pthread_once
 *	pthread_self
 *	pthread_setspecific
 *	pthread_testcancel
 *	pthread_unlock_global_np
 *
 * On OpenVMS this is irrelevant since name binding occurs at link time: when
 * images are activated they bind to a known offset within the image symbol
 * vector (Alpha) or transfer vector (VAX). The binary compatibility interface
 * names have been changed, but the arrangement of the transfer vector and
 * symbol vector remain the same. Thus old code linked against the old
 * shareable images will call the correct new routine.
 *
 *****************************************************************************/

/*
 * Define a symbol which client code can test to determine whether the
 * underlying threads package is DECthreads or not. This is especially
 * important to clients of the POSIX 1003.1c interface who may want to use
 * DECthreads extensions, such as the TEB, global lock and non-real-time
 * scheduling policies while maintaining portability to a "vanilla"
 * 1003.1c-1995 implementation.
 *
 * The DECthreads version is encoded in this number. The version is normally
 * in the form "Vvv.bb-lll" where "vv" represents the major version, "bb"
 * represents the baselevel (which increases continuously regardless of
 * version), and "lll" is a build level that increases in each DECthreads
 * project build within a baselevel.
 *
 * Higher numeric values are always more recent versions. So to check for
 * support of a feature that appeared in DECthreads V3.13-100, you could check
 * whether the symbol is > 212100L.
 */

#ifdef _DECTHREADS_VERSION
# undef _DECTHREADS_VERSION
#endif
#define _DECTHREADS_VERSION 315397

#ifndef _DECTHREADS_
# define _DECTHREADS_ _DECTHREADS_VERSION
#endif

/*
 *
 *
 * NOTICE: OpenVMS Alpha 64-bit pointer support
 * --------------------------------------------
 *
 * On OpenVMS Alpha DECthreads generally supports both the 64 bit and 32 bit
 * programming environments. Some external data structures (such as the TEB
 * and attributes objects) cannot vary between interfaces, and are defined to
 * contain 64 bit values regardless of programming environment. Only one
 * 1003.1c routine varies between the interfaces: pthread_join, which writes a
 * "void *" to a caller-provided address. For pthread_join32 only the low 32
 * bits of the thread return value is written. For pthread_join64 all 64 bits
 * are written (this will corrupt caller data if the allocated "void *" is 32
 * bits wide). The default definition of "pthread_join" depends upon the
 * programming environment specified by compiler switches -- in other words,
 * the value of the _INITIAL_POINTER_SIZE macro.
 *
 * The following typedefs allow fields with required sizes to be declared
 * without needing a lot of #pragma __required_pointer_size statements
 * scattered through the header. On OpenVMS VAX and Digital UNIX these types
 * always correspond unambiguously to a single type. On OpenVMS Alpha the
 * types select the appropriate size to maintain datastructure layout
 * regardless of the default pointer size.
 *
 * Per the convention the 64-bit task force has established, a compilation on
 * OpenVMS Alpha that occurs without any /pointer_size switch should yield
 * only a 32-bit interface. But, if compilation on OpenVMS Alpha occurs with
 * an explicit /pointer_size switch, then (a) all prototypes should accept
 * long [64] bit pointers as arguments and (b) all functions which return
 * pointer values should return [32] bit pointers unless the function is a
 * variant with _64 in the name.
 *
 * The DECthreads team has no intention of supporting short pointer
 * compilation on Digital UNIX.
 *
 *	NOTE: _PTHREAD_ALLOW_MIXED_PROTOS_ should be defined only for the
 *	OpenVMS Alpha platform.
 *
 *
 */
#ifdef _PTHREAD_ALLOW_MIXED_PROTOS_
# ifdef __INITIAL_POINTER_SIZE
   /*
    * This is a DECC compiler with 64-bit pointer support.
    */
#  ifdef _PTHREAD_CORE_BUILD_
#   define _PTHREAD_MIXED_PROTOS_
#  else
#   if __INITIAL_POINTER_SIZE > 0
     /*
      * The compilation has an explicit /pointer_size.
      */
#    define _PTHREAD_MIXED_PROTOS_
#   endif
#  endif
# else
   /*
    * This is some compiler on AXP/VMS that does not have 64-bit pointer
    * support.
    */
#  ifdef _PTHREAD_CORE_BUILD_
#   error OpenVMS Alpha compiler without 64-bit pointer support
#  endif
# endif
#endif

#ifdef _PTHREAD_ALLOW_MIXED_PROTOS_
/*
 * On OpenVMS Alpha, some of the fields in DECthreads structures (TEB,
 * pthread_mutex_t, pthread_cond_t) need to be 64-bit pointers regardless of
 * the default pointer size in use by the compiler. They need to be 64 bit
 * fields even on older versions of DEC C (prior to V5.0) which don't support
 * 64 bit pointers at all.
 *
 * If the compiler supports long pointers, we use the __required_pointer_size
 * pragma to force the proper interpretation of these pointers. On older
 * compilers, we use uint64 instead.
 */
typedef __int64			__pthreadLongInt_t;
typedef unsigned __int64	__pthreadLongUint_t;
# ifdef __INITIAL_POINTER_SIZE
#  pragma __required_pointer_size __save
#  pragma __required_pointer_size __long
typedef void*			__pthreadLongAddr_t;
typedef char*			__pthreadLongString_t;
typedef __pthreadLongAddr_t*	__pthreadLongAddr_p;
#  pragma __required_pointer_size __short
typedef void*			__pthreadShortAddr_t;
typedef char*			__pthreadShortString_t;
typedef __pthreadLongAddr_t*	__pthreadShortAddr_p;
#  pragma __required_pointer_size __restore
# else			/* OpenVMS Alpha with no long pointer support */
typedef unsigned __int64	__pthreadLongAddr_t;
typedef unsigned __int64	__pthreadLongString_t;
typedef unsigned __int64	__pthreadLongAddr_p;
typedef void*			__pthreadShortAddr_t;
typedef char*			__pthreadShortString_t;
typedef __pthreadLongAddr_t*	__pthreadShortAddr_p;
# endif					/* Long pointer support */
#else					/* No mixed pointers */
typedef long			__pthreadLongInt_t;
typedef unsigned long		__pthreadLongUint_t;
typedef void*			__pthreadLongAddr_t;
typedef char*			__pthreadLongString_t;
typedef __pthreadLongAddr_t*	__pthreadLongAddr_p;
typedef void*			__pthreadShortAddr_t;
typedef char*			__pthreadShortString_t;
typedef __pthreadLongAddr_t*	__pthreadShortAddr_p;
#endif

typedef __pthreadLongAddr_p	__pthreadTsd_t;

#ifndef PTHREAD_KEYS_MAX
# define PTHREAD_KEYS_MAX		255
#endif
#ifndef _PTHREAD_ENV_UNIX
# ifndef PTHREAD_DESTRUCTOR_ITERATIONS
#  define PTHREAD_DESTRUCTOR_ITERATIONS	4
# endif
#endif
#ifndef PTHREAD_STACK_MIN
# ifdef _PTHREAD_ENV_VAX
#  define PTHREAD_STACK_MIN		6656
# else
#  define PTHREAD_STACK_MIN		8192
# endif
#endif

#define PTHREAD_CANCEL_DISABLE		0
#define PTHREAD_CANCEL_ENABLE		1

#define PTHREAD_CANCEL_DEFERRED		0
#define PTHREAD_CANCEL_ASYNCHRONOUS	1

#define PTHREAD_CANCELED		(void *)-1

#define PTHREAD_SCOPE_PROCESS		0
#define PTHREAD_SCOPE_SYSTEM		1

#define PTHREAD_MUTEX_NORMAL		0
#define PTHREAD_MUTEX_RECURSIVE		1
#define PTHREAD_MUTEX_ERRORCHECK	2
#define PTHREAD_MUTEX_DEFAULT		PTHREAD_MUTEX_NORMAL

#define PTHREAD_PROCESS_PRIVATE		0
#define PTHREAD_PROCESS_SHARED		1

/*
 * For source compatability prior to XOPEN UNIX 98 Brand
 */
#define PTHREAD_MUTEX_NORMAL_NP		PTHREAD_MUTEX_NORMAL
#define PTHREAD_MUTEX_RECURSIVE_NP	PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEX_ERRORCHECK_NP	PTHREAD_MUTEX_ERRORCHECK


#define _PTHREAD_MSTATE_REFCNT	0x0000ffff	/* Internal reference count */
#define _PTHREAD_MSTATE_OVFCNT	0x000f0000	/* Overflow if not zero! */
#define _PTHREAD_MSTATE_LOCK	0x00100000	/* Primary lock bit */
#define _PTHREAD_MSTATE_LOCK_B	20		/*  (bit offset of lock) */
#define _PTHREAD_MSTATE_SLOW	0x00200000	/* Slow lock/unlock */
#define _PTHREAD_MSTATE_SLOW_B	21		/*  (bit offset of slow bit) */
#define _PTHREAD_MSTATE_PSHARED	0x00400000	/* Process shared object flag */
#define _PTHREAD_MSTATE_PSHARED_B 22		/*  (bit offset of pshared) */
#define _PTHREAD_MSTATE_TYPE	0x0f000000	/* Mutex type */
#define _PTHREAD_MSTATE_TYPE_B	24		/*  (bit offset of mutex type */
#define _PTHREAD_MTYPE_NORMAL	0x00000000	/*  Normal (fast or metered) */
#define _PTHREAD_MTYPE_RECURS	0x01000000	/*  Recursive: relock in */
						/*   same thread */
#define _PTHREAD_MTYPE_ERRCHK	0x02000000	/*  Detect usage errors */

#define _PTHREAD_CSTATE_REFCNT	0x0000ffff	/* Internal reference count */
#define _PTHREAD_CSTATE_OVFCNT	0x000f0000	/* Overflow if not zero! */
#define _PTHREAD_CSTATE_EVENT	0x00100000	/* Might be waiters */
#define _PTHREAD_CSTATE_EVENT_B	20		/*  (bit offset of event) */
#define _PTHREAD_CSTATE_SLOW	0x00200000	/* Slow signal/broadcast */
#define _PTHREAD_CSTATE_SLOW_B	21		/*  (bit offset of slow bit) */
#define _PTHREAD_CSTATE_PSHARED	0x00400000	/* Process shared object flag */
#define _PTHREAD_CSTATE_PSHARED_B 22		/*  (bit offset of pshared) */
#define _PTHREAD_CSTATE_PEND	0x00800000	/* Pending waiters bit */
#define _PTHREAD_CSTATE_PEND_B 23		/*  (bit offset of pend) */

/*
 * Validation of caller-allocated structures is minimal, but to allow basic
 * consistency checking each structure comes with a "validation" field that
 * helps to determine whether it's likely to be the correct type. Following
 * are the constants. Note that with the exception of the mutex and condition
 * variable, these constants are stored into memory passed into DECthreads, so
 * we're trusting what the caller says. Mutexes and condition variables, if
 * statically initialized using PTHREAD_COND_INITIALIZER,
 * PTHREAD_MUTEX_INITIALIZER, or their relatives, are loaded with the
 * validation constants at compile time.
 */
#define _PTHREAD_CVALID		(0x06facbd1L)	/* Condition variable */
#define _PTHREAD_MVALID		(0x05bcafe1L)	/* Mutex */
#define _PTHREAD_PVALID		(0xdeadbeefL)	/* Paddock */
#define _PTHREAD_RWVALID	(0x02bacab1L)	/* Read/Write lock */

#define _PTHREAD_CAVALID	(0xaceface1L)	/* Condition attributes */
#define _PTHREAD_MAVALID	(0xecafeca1L)	/* Mutex attributes */
#define _PTHREAD_TAVALID	(0xbeefeed1L)	/* Thread attributes */

/*
 * The top 5 bits of the rwlock valid field are reserved for DECthreads flags.
 * Setting these bits improperly may either prevent the program from running
 * or reduce the usefulness of debugging information.
 */
#define _PTHREAD_RWVF_STA	0x08000000L
#define _PTHREAD_RWVF_INT	0x10000000L
#define _PTHREAD_RWVF_PRE	0x20000000L
#define _PTHREAD_RWVF_INL	0x40000000L
#define _PTHREAD_RWVF_NAM	0x80000000L

/*
 * The top 5 bits of the mutex valid field are reserved for DECthreads flags.
 * Setting these bits improperly may either prevent the program from running
 * or reduce the usefulness of debugging information.
 */
#define _PTHREAD_MVF_STA	0x08000000L
#define _PTHREAD_MVF_INT	0x10000000L
#define _PTHREAD_MVF_PRE	0x20000000L
#define _PTHREAD_MVF_INL	0x40000000L
#define _PTHREAD_MVF_NAM	0x80000000L

/*
 * The top 5 bits of the CV valid field are reserved for DECthreads flags.
 * Setting these bits improperly may either prevent the program from running
 * or reduce the usefulness of debugging information.
 */
#define _PTHREAD_CVF_STA	0x08000000L

#ifndef _PTHREAD_NOMETER_STATIC
# define PTHREAD_MUTEX_INITIALIZER \
    {_PTHREAD_MSTATE_SLOW, _PTHREAD_MVALID | _PTHREAD_MVF_STA}
# define PTHREAD_COND_INITIALIZER \
    {_PTHREAD_CSTATE_SLOW, _PTHREAD_CVALID | _PTHREAD_CVF_STA}
# define PTHREAD_MUTEX_INITWITHNAME_NP(_n_,_a_) \
    {_PTHREAD_MSTATE_SLOW, _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}
# define PTHREAD_COND_INITWITHNAME_NP(_n_,_a_) \
    {_PTHREAD_CSTATE_SLOW, _PTHREAD_CVALID | _PTHREAD_CVF_STA, _n_, _a_}
#else
# define PTHREAD_MUTEX_INITIALIZER {0, _PTHREAD_MVALID | _PTHREAD_MVF_STA}
# define PTHREAD_COND_INITIALIZER  {0, _PTHREAD_CVALID | _PTHREAD_CVF_STA}
# define PTHREAD_MUTEX_INITWITHNAME_NP(_n_,_a_) \
    {0, _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}
# define PTHREAD_COND_INITWITHNAME_NP(_n_,_a_) \
    {0, _PTHREAD_CVALID | _PTHREAD_CVF_STA, _n_, _a_}
#endif

#define PTHREAD_RWLOCK_INITIALIZER {_PTHREAD_RWVALID | _PTHREAD_RWVF_STA}
#define PTHREAD_RWLOCK_INITWITHNAME_NP(_n_,_a_) \
	{_PTHREAD_RWVALID | _PTHREAD_RWVF_STA, _n_, _a_}

#define PTHREAD_MUTEX_INITFAST_NP {0, _PTHREAD_MVALID | _PTHREAD_MVF_STA}
#define PTHREAD_MUTEX_INITFASTWITHNAME_NP(_n_,_a_) \
    {0, _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}
#define PTHREAD_MUTEX_INITRECURSIVE_NP \
    {_PTHREAD_MTYPE_RECURS | _PTHREAD_MSTATE_SLOW, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA}
#define PTHREAD_MUTEX_INITRECURSIVEWITHNAME_NP(_n_,_a_) \
    {_PTHREAD_MTYPE_RECURS | _PTHREAD_MSTATE_SLOW, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}
#define PTHREAD_MUTEX_INITERRCHK_NP \
    {_PTHREAD_MTYPE_ERRCHK | _PTHREAD_MSTATE_SLOW, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA}
#define PTHREAD_MUTEX_INITERRCHKWITHNAME_NP(_n_,_a_) \
    {_PTHREAD_MTYPE_ERRCHK | _PTHREAD_MSTATE_SLOW, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA, _n_, _a_}

/*
 * This macro is a special variant of the PTHREAD_MUTEX_INITIALIZER macro.
 *
 * It provides a solution for any library (or main program) that needs to
 * preempt the malloc() family of functions from libc during link. DECthreads
 * uses malloc to dynamically create an "extension" to mutex (pthread_mutex_t)
 * when a thread needs to block on the mutex, or when synchronization metering
 * is enabled. Since a thread-safe malloc will generally use a mutex, there's
 * a potential recursion in the process that needs to be resolved. It can be
 * avoided for libc, since DECthreads knows which mutexes are "special". For
 * any other malloc package that might satisfy the DECthreads references to
 * malloc, free, and valloc, another mechanism is required.
 *
 * Until DECthreads initializes, use of TIS mutexes is "safe" -- they can
 * never block, and will not need the "extension". When DECthreads
 * initializes, it alters the TIS functions to call into DECthreads. If
 * metering is enabled the next lock of your malloc will need to associate an
 * extension with the mutexes involved in malloc.
 *
 * During initialization, and before making TIS "multithreaded", DECthreads
 * also preallocates a number of "mutex extension" structures and caches
 * them. These will be claimed by the first few mutexes that need to meter or
 * block. Unless metering is enabled, however, it's difficult to ensure that
 * your malloc mutexes will need an extension early enough to get one of those
 * preallocated structures.
 *
 * The solution is to initialize your malloc mutexes with this special macro.
 * The "_PTHREAD_MSTATE_SLOW" flag will ensure that the first attempt to lock
 * the mutex will call into DECthreads. This call must be made after
 * DECthreads has initialized (the TIS "stub" code won't do anything for
 * you). The special "valid" field value will cause DECthreads to immediately
 * assign that mutex an extension, even if metering isn't enabled and there's
 * no need to block. Additionally, the extension will be specially marked so
 * that DECthreads will never reassign that extension (which it might
 * otherwise do when no threads are blocked). In short, it makes the malloc
 * mutex "safe".
 *
 * The special valid field has no effect if no preallocated extension
 * structures are available, which could result in a disastrous infinite
 * recursion. That would probably mean that your code, or some other code that
 * ran between DECthreads initialization and your code, has acquired all of
 * the preallocated structures. The way around that is to reconfigure
 * DECthreads to allocate "more of them". You can do that by setting the
 * PTHREAD_CONFIG environment variable to a string including the phrase
 * "mutexes=<n>" where <n> is a number. For example,
 *
 *	export PTHREAD_CONFIG="mutexes=200"
 *
 * How big a number? That depends on how many mutexes get in your way. Try
 * setting a break point at the point where you want to lock your malloc mutex.
 * Using ladebug use the "mutex -a" command to list all of the existing
 * mutexes.  You should preallocate more extension structures than the number
 * of mutexes currently listed.
 */
#define _PTHREAD_MUTEX_INITPRE \
    {_PTHREAD_MSTATE_SLOW, _PTHREAD_MVALID|_PTHREAD_MVF_STA|_PTHREAD_MVF_PRE}
#define _PTHREAD_MUTEX_INITPREWITHNAME(_n_,_a_) \
    {_PTHREAD_MSTATE_SLOW, _PTHREAD_MVALID|_PTHREAD_MVF_STA|_PTHREAD_MVF_PRE, \
    _n_, _a_}
#define _PTHREAD_MUTEX_INITPRERECUR \
    {_PTHREAD_MTYPE_RECURS | _PTHREAD_MSTATE_SLOW, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA | _PTHREAD_MVF_PRE}
#define _PTHREAD_MUTEX_INITPRERECURWITHNAME(_n_,_a_) \
    {_PTHREAD_MTYPE_RECURS | _PTHREAD_MSTATE_SLOW, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA | _PTHREAD_MVF_PRE, _n_, _a_}
#define _PTHREAD_MUTEX_INITPREERRCHK \
    {_PTHREAD_MTYPE_ERRCHK | _PTHREAD_MSTATE_SLOW, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA | _PTHREAD_MVF_PRE}
#define _PTHREAD_MUTEX_INITPREERRCHKWITHNAME(_n_,_a_) \
    {_PTHREAD_MTYPE_ERRCHK | _PTHREAD_MSTATE_SLOW, \
    _PTHREAD_MVALID | _PTHREAD_MVF_STA | _PTHREAD_MVF_PRE, _n_, _a_}

/*
 * "Constructor keys" (keys created using pthread_key_create_new_np) must
 * be statically initialized using this macro prior to creation, e.g.,
 *
 *	pthread_key_t	key = PTHREAD_KEY_INITIALIZER_NP;
 */
#define PTHREAD_KEY_INITIALIZER_NP	0

/*
 * Flags for pthread_key_construct_np
 */
#define PTHREAD_KEY_ALLTHREAD_NP	0x1  /* Constr/Destr in all threads */

#ifndef _PTHREAD_ENV_UNIX
/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_attr_t {
    __pthreadLongUint_t		_Pfield(valid);
    __pthreadLongString_t	_Pfield(name);
    __pthreadLongUint_t		_Pfield(arg);
    __pthreadLongUint_t		_Pfield(reserved)[19];
    } pthread_attr_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_mutexattr_t {
    __pthreadLongUint_t	_Pfield(valid);
    __pthreadLongUint_t	_Pfield(reserved)[15];
    } pthread_mutexattr_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_condattr_t {
    __pthreadLongUint_t	_Pfield(valid);
    __pthreadLongUint_t	_Pfield(reserved)[13];
    } pthread_condattr_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_rwlockattr_t {
    __pthreadLongUint_t	_Pfield(valid);		/* Validation flag */
    __pthreadLongUint_t	_Pfield(reserved)[15];
    } pthread_rwlockattr_t;
#endif

/*
 * All references to "individual attributes" fields within these attributes
 * object structures MUST be made through the defined function calls in this
 * header file. Not all fields in these structures mean what you might infer
 * from the field type. Not all of the fields are implemented at this time.
 * The name and order of fields may change without notice, although the size
 * of the structure will never change.
 */
typedef struct __pthread_paddockattr_t {
    __pthreadLongUint_t	_Pfield(valid);		/* Validation flag */
    __pthreadLongUint_t	_Pfield(reserved)[15];
    } pthread_paddockattr_t;

/*
 * All references to "individual paddock" fields within these object structures
 * MUST be made through the defined function calls in this header file. Not all
 * fields in these structures mean what you might infer from the field type. Not
 * all of the fields are implemented at this time.  The name and order of fields
 * may change without notice, although the size of the structure will never
 * change.
 */
typedef struct __pthread_paddock_t {
    __pthreadLongUint_t		_Pfield(valid);
    __pthreadLongString_t	_Pfield(name);
    __pthreadLongUint_t		_Pfield(arg);
    __pthreadLongUint_t		_Pfield(reserved)[19];
    } pthread_paddock_t;

#ifndef _PTHREAD_ENV_UNIX
/*
 * DECthreads maintains a substantial amount of internal information about
 * each thread in a "Thread Control Block" that is not directly accessible to
 * the programmer. However, some of this information is required by
 * application, library, or debug/profile code in performance critical code
 * paths. Thus, DECthreads provides an "architected Thread Environment Block"
 * that makes a subset of the TCB information available directly. On Alpha
 * hardware systems the address of the TEB is available by using the CALL_PAL
 * RDUNIQ instruction. DECthreads also provides both a macro and a callable
 * function to return the TEB address, for convenience and portability.
 */
# if defined (_PTHREAD_ALLOW_MIXED_PROTOS_) && defined (__INITIAL_POINTER_SIZE)
#  pragma __required_pointer_size __save
#  pragma __required_pointer_size __long
# endif

# if defined(_OSF_SOURCE) || !defined(_PTHREAD_ENV_UNIX)
/*
 * Define the TEB's version.
 *
 * Version 0: Digital UNIX 4.0 and OpenVMS 7.0
 * Version 1: Digital UNIX 4.0D and OpenVMS 7.2
 */
#  define PTHREAD_TEB_VERSION		1	/* Current version */
#  define PTHREAD_TEB_SIZE \
     ((size_t)((char *)&((pthread_t)0L)->_Pfield(thd_errno) \
     - (char *)0L)) + sizeof (int)
#  define PTHREAD_TEB_EFLG_USER		0x01	/* User thread */
#  define PTHREAD_TEB_EFLG_INITIAL	0x02	/* Process initial thread */

#  define PTHREAD_TEB_CREATOR_PTHREAD	1   /* Created by 1003.1c API */
#  define PTHREAD_TEB_CREATOR_CMA	2   /* Created by CMA API */
#  define PTHREAD_TEB_CREATOR_D4	3   /* Created by Draft 4 API */
#  define PTHREAD_TEB_CREATOR_D4EXC	4   /* Created by D4-Exception API */
# endif

/*
 * Thread Environment Block (TEB).
 *
 * NOTE: Modification of any field in a thread's TEB structure will result in
 * undefined behavior. Fields that are commented as "RESERVED" are
 * undocumented and unsupported, and the contents or meaning may change at any
 * time.
 *
 * Each public field is documented with a comment that begins with the TEB
 * version in which the field was created or documented. If the TEB "version"
 * has a value lower than version in which the field became accessible, do not
 * depend upon the value of that field.
 */

typedef struct __pthreadTeb_t {
    __pthreadLongAddr_p	_Pfield(reserved1);	/* Reserved to DECthreads */
    __pthreadLongAddr_p	_Pfield(reserved2);	/* Reserved to DECthreads */
    unsigned short	_Pfield(size);		/* V1: Size of TEB */
    unsigned char	_Pfield(version);	/* TEB version */
    unsigned char	_Pfield(reserved3);	/* Reserved to DECthreads */
    unsigned char	_Pfield(external);	/* V1: PTHREAD_TEB_EFLG_ flgs */
    unsigned char	_Pfield(reserved4)[2];	/* RESERVED */
    unsigned char	_Pfield(creator);	/* V1: PTHREAD_TEB_CREATOR_* */
    __pthreadLongUint_t	_Pfield(sequence);	/* V0: Thread sequence */
    __pthreadLongUint_t	_Pfield(reserved5)[2];	/* Reserved to DECthreads */
    __pthreadLongAddr_t	_Pfield(per_kt_area);	/* V0: Reserved */
    __pthreadLongAddr_t	_Pfield(stack_base);	/* V0: Initial SP */
    __pthreadLongAddr_t	_Pfield(stack_reserve); /* V0: reserved stack */
    __pthreadLongAddr_t	_Pfield(stack_yellow);	/* V0: yellow zone */
    __pthreadLongAddr_t	_Pfield(stack_guard);	/* V0: guard (red) zone */
    __pthreadLongUint_t	_Pfield(stack_size);	/* V0: total stack size */
    __pthreadTsd_t	_Pfield(tsd_values);	/* V0: TSD array (void *) */
    unsigned long	_Pfield(tsd_count);	/* V0: TSD array size */
    unsigned int	_Pfield(reserved6);	/* Reserved to DECthreads */
    unsigned int	_Pfield(reserved7);	/* Reserved to DECthreads */
    unsigned int	_Pfield(thread_flags);	/* Reserved to DECthreads */
    int			_Pfield(thd_errno);	/* V1: thread's errno */
    __pthreadLongAddr_t	_Pfield(stack_hiwater);	/* V1: lowest known SP */
    } pthreadTeb_t, *pthreadTeb_p;
# if defined (_PTHREAD_ALLOW_MIXED_PROTOS_) && defined (__INITIAL_POINTER_SIZE)
typedef pthreadTeb_p	pthread_t;	/* Long pointer if possible */
#  pragma __required_pointer_size __restore
# elif defined (_PTHREAD_ENV_ALPHA) && defined (_PTHREAD_ENV_VMS)
typedef unsigned __int64	pthread_t;	/* Force 64 bits anyway */
# else
typedef pthreadTeb_p		pthread_t;	/* Pointers is pointers */
# endif
#endif

#ifndef _PTHREAD_ENV_UNIX
typedef unsigned int	pthread_key_t;
#endif

typedef void*	_PTHREAD_CALL_		__pthreadStartFunc_t (void *);
typedef void	_PTHREAD_CALL_		__pthreadDestructorFunc_t (void*);
typedef void*	_PTHREAD_CALL_		__pthreadConstructorFunc_t (
	pthread_key_t, pthread_t);
typedef void	_PTHREAD_CALL_		__pthreadExtDestructorFunc_t (
	void*, pthread_t, pthread_key_t);
typedef void	_PTHREAD_CALL_		__pthreadOnceFunc_t (void);

typedef __pthreadStartFunc_t*		__pthreadStart_t;
typedef __pthreadDestructorFunc_t*	__pthreadDestructor_t;
typedef __pthreadConstructorFunc_t*	__pthreadConstructor_t;
typedef __pthreadExtDestructorFunc_t*	__pthreadExtDestructor_t;
typedef __pthreadOnceFunc_t*		__pthreadOnce_t;

/*
 * Macros to utilize the TEB directly for maximum efficiency. With hardware
 * and a compiler that supports it, this uses inline instructions to get
 * access to the thread's TEB... otherwise this will result in a simple call
 * into DECthreads.
 *
 * It is perfectly reasonable for code to freely access any defined TEB field
 * on any DECthreads platform, as long as you meet all of the following rules
 * (read this section carefully!)
 *
 * You must not depend in any way upon the content or meaning of any
 * "reserved" fields (reserved1, reserved2, reserved3, etc.). These are for
 * DECthreads internal use only and are subject to change without notice.
 *
 * You may not write directly to any field of the TEB. Any modification may
 * result in undefined and possibly severe errors that may show up only much
 * later in the program.
 *
 * Don't make any assumptions about the nature of the sequence number returned
 * by pthread_getsequence_np or pthread_getselfseq_np, except that it is a
 * unique integer among all threads created within the current image.
 * Consecutively created threads may not necessarily have consecutive sequence
 * numbers, nor are all possible sequence numbers necessarily assigned by
 * DECthreads. A thread created "later" does not necessarily have a sequence
 * number higher than that of a thread created "earlier".
 *
 * A thread may read or write thread-specific data values directly to its own
 * tsd_values array. Writing a value to any array element of tsd_values that
 * does not correspond to the value of a thread-specific data key "owned" by
 * the calling subsystem (returned by a call to pthread_key_create or
 * pthread_key_create_new) is erroneous. If you choose to code inline access
 * to the TSD array, do so very cautiously! Write to another thread's
 * tsd_values array only if your code provides sufficient synchronization to
 * ensure that this is "safe" -- in general, this is not a good idea.
 *
 * Only DECthreads and the O/S may use the value of the "per_kt_area" pointer;
 * for other code this is unpredictable and undefined.
 */
#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_self __pthread_self
# endif
#endif
extern pthread_t _PTHREAD_CALL_ pthread_self (void);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#if (defined _PTHREAD_USE_ASM_) && (!defined _PTHREAD_ENV_WIN32)
# ifdef pthread_self
#  undef pthread_self
# endif
# define pthread_self() ((pthread_t)asm ("call_pal 0x9e"))
#endif

#ifdef _PTHREAD_ENV_UNIX
# define pthread_unchecked_getspecific_np(_key_) \
    (pthread_self ()->_Pfield(tsd_values)[_key_])
# define pthread_unchecked_setspecific_np(_key_,_value_) \
    (pthread_self ()->_Pfield(tsd_values)[_key_] = (_value_))
#else
# define pthreadTeb()	((pthreadTeb_p)pthread_self ())
# define pthread_unchecked_getspecific_np(_key_) \
    (pthreadTeb ()->_Pfield(tsd_values)[_key_])
# define pthread_unchecked_setspecific_np(_key_,_value_) \
    (pthreadTeb ()->_Pfield(tsd_values)[_key_] = (_value_))
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * This is the primary structure controlling the identity and state of a
 * mutex. The "lock" field contains the primary mutex lock bit, a flag
 * indicating whether lock/unlock protocols are "fast" or "slow", the full
 * type of the mutex, and an internal reference count. The reference count
 * assures atomicity of unlock/wake sequences with respect to deletion.
 *
 * The "sequence" field gives each mutex a unique identifier, which is
 * primarily used for debugging. A new static mutex has a sequence number of
 * zero; DECthreads assigns a real sequence number when a thread first blocks
 * on the mutex. (A mutex created by calling pthread_mutex_init has a sequence
 * number assigned at creation.)
 *
 * Beware that the name and order of these fields are undocumented and
 * unsupported. Directly accessing any in your program may result in serious
 * difficulties in future releases of the operating system.
 */
typedef struct __pthread_mutex_t {
    unsigned int	_Pfield(lock);		/* LOCK, SLOW, TYPE, REFCNT */
    unsigned int	_Pfield(valid);		/* Validation info */
    __pthreadLongString_t	_Pfield(name);	/* Name of mutex */
    unsigned int	_Pfield(arg);		/* printf argument for name */
    unsigned int	_Pfield(depth);		/* Recursive lock depth */
    unsigned long	_Pfield(sequence);	/* Mutex sequence number */
    unsigned long	_Pfield(owner);		/* Current owner (if known) */
    __pthreadLongAddr_p	_Pfield(block);		/* Pointer to blocking struct */
    } pthread_mutex_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * Similar to pthread_mutex_t, but for a condition variable.
 */
typedef struct __pthread_cond_t {
    unsigned int	_Pfield(state);		/* EVENT, SLOW, REFCNT, etc. */
    unsigned int	_Pfield(valid);		/* Validation info */
    __pthreadLongString_t	_Pfield(name);	/* Name of condition variable */
    unsigned int	_Pfield(arg);		/* printf argument for name */
    unsigned long	_Pfield(sequence);	/* Condition variable seq # */
    __pthreadLongAddr_p	_Pfield(block);		/* Pointer to blocking struct */
    } pthread_cond_t;
#endif

/*
 * Ensure that an initialization routine is called exactly once.
 */
#define PTHREAD_ONCE_UNINIT	0
#define PTHREAD_ONCE_INITING	1
#define PTHREAD_ONCE_INITED	2
#define PTHREAD_ONCE_INIT	{PTHREAD_ONCE_UNINIT}
#ifndef _PTHREAD_ENV_UNIX
typedef volatile struct __pthread_once_t {
    long	_Pfield(state);
    long	_Pfield(reserved)[10];
    } pthread_once_t;
#endif

#ifndef _PTHREAD_ENV_UNIX
/*
 * Readers-Writers Locks
 */
typedef struct __pthread_rwlock_t {
    unsigned int	_Pfield(valid);		/* Validation flag */
    unsigned int	_Pfield(flags);		/* Internal flags */
    __pthreadLongString_t	_Pfield(name);	/* Name of rwlock */
    unsigned int	_Pfield(arg);		/* printf argument for name */
    unsigned int	_Pfield(readers);	/* Number of readers */
    unsigned int	_Pfield(rwaits);	/* Waiting readers */
    unsigned int	_Pfield(wwaits);	/* Waiting writers */
    __pthreadLongUint_t	_Pfield(sequence);	/* rwlock variable seq # */
    unsigned long	_Pfield(wrid);		/* Current write owner */
    __pthreadLongAddr_p	_Pfield(block);		/* Pointer to blocking struct */
    __pthreadLongUint_t	_Pfield(reserved1);	/* Reserved to DECthreads */
    } pthread_rwlock_t;
#endif

#define PTHREAD_INHERIT_SCHED		0
#define PTHREAD_EXPLICIT_SCHED		1

#define PTHREAD_CREATE_JOINABLE		0
#define PTHREAD_CREATE_DETACHED		1

#ifndef _PTHREAD_ENV_UNIX
# define SCHED_FIFO	1		/* Digital UNIX sched.h defines */
# define SCHED_RR	2		/* these constants already */
# define SCHED_OTHER	3
# define SCHED_FG_NP	SCHED_OTHER	/* "Foreground" (Timeshare) */
# define SCHED_BG_NP	(SCHED_OTHER+1)	/* "Background" */
# define SCHED_LFI_NP	(SCHED_OTHER+2)	/* "Low FIFO" (background FIFO) */
# define SCHED_LRR_NP	(SCHED_OTHER+3)	/* "Low RR" (background RR) */
#endif

#if (defined _PTHREAD_ENV_UNIX) && (defined _OSF_SOURCE)
# define PRI_FIFO_MIN	14
# define PRI_FIFO_MAX	SCHED_PRIO_RT_MAX
# define PRI_RR_MIN	14
# define PRI_RR_MAX	SCHED_PRIO_RT_MAX
# define PRI_OTHER_MIN	14
# define PRI_OTHER_MAX	SCHED_PRIO_RT_MAX
# define PRI_FG_MIN_NP	14
# define PRI_FG_MAX_NP	63
# define PRI_BG_MIN_NP	0
# define PRI_BG_MAX_NP	13
# define PRI_LFI_MIN_NP	0
# define PRI_LFI_MAX_NP	13
# define PRI_LRR_MIN_NP	0
# define PRI_LRR_MAX_NP	13
#elif  defined _PTHREAD_ENV_WIN32
# define PRI_RR_MIN	THREAD_PRIORITY_NORMAL
# define PRI_RR_MAX	THREAD_PRIORITY_HIGHEST
# define PRI_FIFO_MIN	THREAD_PRIORITY_NORMAL
# define PRI_FIFO_MAX	THREAD_PRIORITY_HIGHEST
# define PRI_OTHER_MIN	THREAD_PRIORITY_BELOW_NORMAL
# define PRI_OTHER_MAX	THREAD_PRIORITY_ABOVE_NORMAL
# define PRI_FG_MIN_NP	THREAD_PRIORITY_BELOW_NORMAL
# define PRI_FG_MAX_NP	THREAD_PRIORITY_ABOVE_NORMAL
# define PRI_BG_MIN_NP	THREAD_PRIORITY_LOWEST
# define PRI_BG_MAX_NP	THREAD_PRIORITY_BELOW_NORMAL
# define PRI_LFI_MIN_NP	THREAD_PRIORITY_LOWEST
# define PRI_LFI_MAX_NP	THREAD_PRIORITY_BELOW_NORMAL
# define PRI_LRR_MIN_NP	THREAD_PRIORITY_LOWEST
# define PRI_LRR_MAX_NP	THREAD_PRIORITY_BELOW_NORMAL
# define sched_get_priority_max (_pol_) \
    (_pol_ == SCHED_RR ? THREAD_PRIORITY_HIGHEST \
    :(_pol_ == SCHED_FIFO ? THREAD_PRIORITY_HIGHEST \
    :(_pol_ == SCHED_FG ? THREAD_PRIORITY_ABOVE_NORMAL \
    : THREAD_PRIORITY_BELOW_NORMAL )))
# define sched_get_priority_min (_pol_) \
    (_pol_ == SCHED_RR ? THREAD_PRIORITY_NORMAL \
    :(_pol_ == SCHED_FIFO ? THREAD_PRIORITY_NORMAL \
    :(_pol_ == SCHED_OTHER ? THREAD_PRIORITY_BELOW_NORMAL \
    : THREAD_PRIORITY_LOWEST )))
#elif defined (_PTHREAD_ENV_VMS)
# define PRI_FIFO_MIN	16
# define PRI_FIFO_MAX	31
# define PRI_RR_MIN	16
# define PRI_RR_MAX	31
# define PRI_OTHER_MIN	PRI_FG_MIN_NP
# define PRI_OTHER_MAX	PRI_FG_MAX_NP
# define PRI_FG_MIN_NP	8
# define PRI_FG_MAX_NP	15
# define PRI_BG_MIN_NP	0
# define PRI_BG_MAX_NP	7
# define PRI_LFI_MIN_NP	0
# define PRI_LFI_MAX_NP	7
# define PRI_LRR_MIN_NP	0
# define PRI_LRR_MAX_NP	7

# define sched_get_priority_max (_pol_) \
   (_pol_ == SCHED_OTHER ? PRI_FG_MAX_NP : PRI_FIFO_MAX)
# define sched_get_priority_min (_pol_) \
   (_pol_ == SCHED_OTHER ? PRI_FG_MIN_NP : PRI_FIFO_MIN)
#endif

#ifdef _PTHREAD_ENV_UNIX
# if !defined (_XOPEN_SOURCE) || (_XOPEN_SOURCE+0 < 400)
extern int pthread_sigmask (int, const sigset_t*, sigset_t*);

extern int pthread_kill (pthread_t, int);
# endif
#endif

extern int _PTHREAD_CALL_ pthread_mutexattr_init (pthread_mutexattr_t*);

extern int _PTHREAD_CALL_ pthread_mutexattr_destroy (pthread_mutexattr_t*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_init __pthread_mutex_init
# endif
#endif
extern int _PTHREAD_CALL_ pthread_mutex_init (
	pthread_mutex_t*,
	const pthread_mutexattr_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_destroy __pthread_mutex_destroy
# endif
#endif
extern int _PTHREAD_CALL_ pthread_mutex_destroy (pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int _PTHREAD_CALL_ pthread_mutex_block (pthread_mutex_t*);

extern int _PTHREAD_CALL_ pthread_mutex_tryrec (pthread_mutex_t*);

extern int _PTHREAD_CALL_ pthread_mutex_unblock (pthread_mutex_t*);

#ifdef  _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_lock __pthread_mutex_lock
# endif
#endif
extern int _PTHREAD_CALL_ pthread_mutex_lock (pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_trylock __pthread_mutex_trylock
# endif
#endif
extern int _PTHREAD_CALL_ pthread_mutex_trylock (pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_mutex_unlock __pthread_mutex_unlock
# endif
#endif
extern int _PTHREAD_CALL_ pthread_mutex_unlock (pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif


#if defined (_PTHREAD_USE_ASM_) \
	&& !defined (_PTHREAD_SKIP_LOOPY_ASM_) \
	&& (defined (_PTHREAD_USE_INLINE) \
		|| defined (_PTHREAD_CORE_BUILD_) \
		|| defined (_TIS_CORE_BUILD_))

/*
 * See the note near the top of this header for the risks and benefits of
 * using inlined operations! They are NOT compiled into your program by
 * default, and if you choose to enable them you will be required to
 * recompile should DECthreads ever need to change the inline instruction
 * sequences! (While we will not do this arbitrarily, we will not hesitate
 * should it become necessary to substantially improve code performance or
 * reliability, or to fix a bug!)
 */
__inline static int
pthread_mutex_lock_prim (pthread_mutex_t* __mutex)
    {
# if defined (_PTHREAD_ENV_ALPHA)
    return asm (
	    "    ldah	%t1,0x10(%r31) ;"
	    "10: ldl_l	%v0,(%a0) ;"
	    "    zap    %v0,0x3,%t2 ;"
            "	 bne	%t2,20f ;"
	    "    or	%v0,%t1,%t0 ;"
	    "    stl_c	%t0,(%a0) ;"
	    "    beq	%t0,10b ;"
	    "    mb	;"
	    "    bis	%r31,%r31,%v0 ;"
            "20:",
	    &(__mutex->_Pfield(lock)));
# elif defined (_PTHREAD_ENV_X86)
    DWORD	*__locval = &(__mutex->_Pfield(lock));
    DWORD	__retval = *__locval;


    if (!(__retval & _PTHREAD_MSTATE_LOCK)) {
	DWORD	__newval = __retval | _PTHREAD_MSTATE_LOCK;


	__asm {
	    MOV		    ESI,__locval
	    MOV		    EAX,__retval
	    MOV		    EBX,__newval
	    LOCK CMPXCHG    DS:[ESI],EBX
	    MOV		    __retval,EAX
	    }

	__retval = (__retval & _PTHREAD_MSTATE_LOCK);
	}

    return __retval;
# else
#  error pthread_mutex_lock_prim not implemented for this platform
# endif
    }

__inline static int
pthread_mutex_unlock_prim (pthread_mutex_t* __mutex)
    {
# if defined (_PTHREAD_ENV_ALPHA)
    return asm (
	    "    mb ;"
	    "    ldah	%t0,0x10(%r31) ;"
	    "10: ldl_l	%v0,(%a0) ;"
	    "    bic	%v0,%t0,%t1 ;"
	    "    cmoveq	%t1,%t1,%v0 ;"
	    "    bne	%v0, 20f ;"
	    "    stl_c	%t1,(%a0) ;"
	    "    beq	%t1,10b ;"
	    "20:",
	    &(__mutex->_Pfield(lock)));
# elif defined (_PTHREAD_ENV_X86)
    DWORD	*__locval = &(__mutex->_Pfield(lock));
    DWORD	__retval = *__locval;


    __asm {
	    MOV		    ESI,__locval
	    MOV		    EAX,0x00100000
	    MOV		    EBX,0x00000000
	    LOCK CMPXCHG    DS:[ESI],EBX
	    JE		    end
	    MOV		    EBX,EAX
	end:
	    MOV		    __retval,EBX
	}

    return __retval;
# else
#  error pthread_mutex_unlock_prim not implemented for this platform
# endif
    }

# if !((defined (_PTHREAD_CORE_BUILD_) && _PTHREAD_CORE_BUILD_ == 0) \
	|| defined (_TIS_CORE_BUILD_) || defined (_TIS_INCLUDE_ENV))
__inline static int
pthread_mutex_lock_inline (pthread_mutex_t* __mutex)
    {
    int	__status;


    if ((__mutex->_Pfield(lock) & _PTHREAD_MSTATE_SLOW)
	    || (pthread_mutex_lock_prim (__mutex)))
	__status = pthread_mutex_block (__mutex);
    else
	__status = 0;

    return __status;
    }

__inline static int
pthread_mutex_trylock_inline (pthread_mutex_t* __mutex)
    {
    int __status;


    if (__mutex->_Pfield(lock) & _PTHREAD_MSTATE_SLOW)
	__status = pthread_mutex_tryrec (__mutex);
    else {

	if (pthread_mutex_lock_prim (__mutex))
	    __status = EBUSY;
	else
	    __status = 0;

	}

    return __status;
    }

__inline static int
pthread_mutex_unlock_inline (pthread_mutex_t* __mutex)
    {
    int __status;


    if ((__mutex->_Pfield(lock) & _PTHREAD_MSTATE_SLOW)
	    || (pthread_mutex_unlock_prim (__mutex)))
	/*
	 * We need to call unblock because there may be threads waiting on
	 * the mutex (or we're metering or otherwise "slow").  Unblock is
	 * responsible for unlocking the mutex.
	 */
	__status = pthread_mutex_unblock (__mutex);
    else
	__status = 0;

    return __status;
    }
/*
 * See the note near the top of this header for the risks and benefits of
 * using inlined operations! They are NOT compiled into your program by
 * default, and if you choose to enable them you will be required to
 * recompile should DECthreads ever need to change the inline instruction
 * sequences! (While we will not do this arbitrarily, we will not hesitate
 * should it become necessary to substantially improve code performance or
 * reliability, or to fix a bug!)
 */

#  ifdef _PTHREAD_USE_INLINE
#   ifdef pthread_mutex_lock
#    undef pthread_mutex_lock
#    undef pthread_mutex_trylock
#    undef pthread_mutex_unlock
#   endif
#   define pthread_mutex_lock		pthread_mutex_lock_inline
#   define pthread_mutex_trylock	pthread_mutex_trylock_inline
#   define pthread_mutex_unlock		pthread_mutex_unlock_inline
#  endif
# endif
#else
# define pthread_mutex_lock_inline	pthread_mutex_lock
# define pthread_mutex_trylock_inline	pthread_mutex_trylock
# define pthread_mutex_unlock_inline	pthread_mutex_unlock
# define pthread_mutex_unlock_prim(_m_)	(TRUE)
#endif

extern int _PTHREAD_CALL_ pthread_condattr_init (pthread_condattr_t*);

extern int _PTHREAD_CALL_ pthread_condattr_destroy (pthread_condattr_t*);

#ifdef _PTHREAD_ENV_UNIX
extern int pthread_condattr_setpshared (pthread_condattr_t*, int);

extern int pthread_condattr_getpshared (const pthread_condattr_t*, int*);
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_init __pthread_cond_init
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cond_init (
	pthread_cond_t*,
	const pthread_condattr_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_destroy __pthread_cond_destroy
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cond_destroy (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_signal __pthread_cond_signal
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cond_signal (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_broadcast __pthread_cond_broadcast
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cond_broadcast (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_wait __pthread_cond_wait
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cond_wait (pthread_cond_t*, pthread_mutex_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_timedwait __pthread_cond_timedwait
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cond_timedwait (
	pthread_cond_t*,
	pthread_mutex_t*,
	const struct timespec*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int _PTHREAD_CALL_ pthread_attr_setscope (pthread_attr_t*, int);

extern int _PTHREAD_CALL_ pthread_attr_getscope (const pthread_attr_t*, int*);

/*
 * Routines to get/set the stack address for a thread that will be created
 * using the attributes object. Note that "stackaddr" must be the correct
 * initial stack BASE for the thread, which is highly machine-dependent.
 * (E.g., does the machine increment or decrement the stack, and does it do so
 * before or after storing a new value?) Use of these functions is inherently
 * NON-PORTABLE, and they should be used only with great caution.
 * Additionally, they do not provide any way for the implementation to know
 * the size of the stack, so it can neither prevent nor detect stack overflows
 * or the corruption that may be caused by this application error. (See the
 * DECthreads extension pthread_attr_setstackaddr_np.)
 */
extern int _PTHREAD_CALL_ pthread_attr_setstackaddr (pthread_attr_t*, void*);

extern int _PTHREAD_CALL_ pthread_attr_getstackaddr (
	const pthread_attr_t*,
	void**);

/*
 * Extended versions of set/get stackaddr routines that allow the caller to
 * specify the stack using a low address and size. The implementation will
 * compute the proper "stack base" using this information. E.g. you might mmap
 * space, add the size to the returned pointer, and then pass the result to
 * pthread_attr_setstackaddr on a machine with a pre-decremented stack
 * pointer; but on a machine with a post-incremented stack you would pass the
 * pointer returned by mmap. Using pthread_attr_setstackaddr_np instead, you
 * always pass the pointer returned by mmap and the requested size.
 */
extern int _PTHREAD_CALL_ pthread_attr_setstackaddr_np (
	pthread_attr_t*,
	void*,
	size_t);

extern int _PTHREAD_CALL_ pthread_attr_getstackaddr_np (
	const pthread_attr_t*,
	void**,
	size_t*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_setinheritsched __pthread_attr_setinheritsched
# endif
#endif
extern int _PTHREAD_CALL_ pthread_attr_setinheritsched (pthread_attr_t*, int);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_getinheritsched __pthread_attr_getinheritsched
# endif
#endif
extern int _PTHREAD_CALL_ pthread_attr_getinheritsched (
	const pthread_attr_t*,
	int*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int _PTHREAD_CALL_ pthread_attr_setschedpolicy (pthread_attr_t*, int);

extern int _PTHREAD_CALL_ pthread_attr_getschedpolicy (
	const pthread_attr_t*,
	int*);

extern int _PTHREAD_CALL_ pthread_attr_setschedparam (
	pthread_attr_t*,
	const struct sched_param*);

extern int _PTHREAD_CALL_ pthread_attr_getschedparam (
	const pthread_attr_t*,
	struct sched_param*);

extern int _PTHREAD_CALL_ pthread_getschedparam (
	pthread_t,
	int*,
	struct sched_param*);

extern int _PTHREAD_CALL_ pthread_setschedparam (
	pthread_t,
	int,
	const struct sched_param*);

extern int _PTHREAD_CALL_ pthread_getconcurrency (void);

extern int _PTHREAD_CALL_ pthread_setconcurrency (int);

extern int _PTHREAD_CALL_ pthread_attr_init (pthread_attr_t*);

extern int _PTHREAD_CALL_ pthread_attr_destroy (pthread_attr_t*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_setstacksize __pthread_attr_setstacksize
# endif
#endif
extern int _PTHREAD_CALL_ pthread_attr_setstacksize (pthread_attr_t*, size_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_getstacksize __pthread_attr_getstacksize
# endif
#endif
extern int _PTHREAD_CALL_ pthread_attr_getstacksize (
	const pthread_attr_t*,
	size_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int _PTHREAD_CALL_ pthread_attr_setdetachstate (pthread_attr_t*, int);

extern int _PTHREAD_CALL_ pthread_attr_getdetachstate (
	const pthread_attr_t*,
	int*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_create __pthread_create
# endif
#endif
extern int _PTHREAD_CALL_ pthread_create (
	pthread_t*,
	const pthread_attr_t*,
	void* (*)(void *),
	void*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_MIXED_PROTOS_
extern int _PTHREAD_CALL_ pthread_join64 (pthread_t, __pthreadLongAddr_t*);
extern int _PTHREAD_CALL_ pthread_join32 (pthread_t, __pthreadShortAddr_t*);
# ifdef pthread_join
#  undef pthread_join
# endif
# if __INITIAL_POINTER_SIZE == 64
#  define pthread_join pthread_join64
# else
#  define pthread_join pthread_join32
# endif
#else
# ifdef _PTHREAD_ALLOW_MIXED_PROTOS_
#  ifdef pthread_join
#   undef pthread_join
#  endif
#  define pthread_join pthread_join32
# else
#  ifdef _PTHREAD_USE_MANGLED_NAMES_
#   ifdef _PTHREAD_USE_PTDNAM_
#    pragma extern_prefix "__"
#   else
#    define pthread_join __pthread_join
#   endif
#  endif
# endif
extern int _PTHREAD_CALL_ pthread_join (pthread_t, void**);
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix ""
# endif
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_detach __pthread_detach
# endif
#endif
extern int _PTHREAD_CALL_ pthread_detach (pthread_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_exit __pthread_exit
# endif
#endif
extern void _PTHREAD_CALL_ pthread_exit (void*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_equal __pthread_equal
# endif
#endif
extern int _PTHREAD_CALL_ pthread_equal (pthread_t, pthread_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

/*
 * See the note near the top of this header for the risks and benefits of
 * using inlined operations! They are NOT compiled into your program by
 * default, and if you choose to enable them you will be required to
 * recompile should DECthreads ever need to change the inline instruction
 * sequences! (While we will not do this arbitrarily, we will not hesitate
 * should it become necessary to substantially improve code performance or
 * reliability, or to fix a bug!)
 */

#ifdef _PTHREAD_USE_INLINE
# ifdef pthread_equal
#  undef pthread_equal
# endif
# define pthread_equal(t1,t2) (t1==t2)
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_once __pthread_once
# endif
#endif
extern int _PTHREAD_CALL_ pthread_once (pthread_once_t*, __pthreadOnce_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int _PTHREAD_CALL_ pthread_key_create (
	pthread_key_t*,
	__pthreadDestructor_t);

extern int _PTHREAD_CALL_ pthread_key_delete (pthread_key_t);

extern int _PTHREAD_CALL_ pthread_key_create_new_np (
	pthread_key_t*,
	__pthreadConstructor_t,
	__pthreadExtDestructor_t,
	int);

/*
 * See the note near the top of this header for the risks and benefits of
 * using inlined operations! They are NOT compiled into your program by
 * default, and if you choose to enable them you will be required to
 * recompile should DECthreads ever need to change the inline instruction
 * sequences! (While we will not do this arbitrarily, we will not hesitate
 * should it become necessary to substantially improve code performance or
 * reliability, or to fix a bug!)
 *
 * Additional note:
 *
 * pthread_getspecific can't be implemented as a macro in ANSI C, since it
 * involves two invocations of pthread_self(), which the compiler can't be
 * depended upon to combine. The next best alternative is a static inlined
 * routine; even if the #pragma inline isn't recognized by your compiler it's
 * no worse than the real call (and may be better because the compiler can use
 * optimized local call sequences); and the routine is small. Consider this an
 * experiment -- it can be used for a lot more if it works well.
 */

#if defined (_PTHREAD_USE_ASM_) && defined (_PTHREAD_USE_INLINE)
__inline static void *
pthread_getspecific (pthread_key_t __key)
    {
# ifdef _PTHREAD_ENV_UNIX
    pthread_t		__self = pthread_self ();
# else
    pthreadTeb_p	__self = pthreadTeb ();
# endif
    return (void *)(__key >= __self->_Pfield(tsd_count)
		? NULL : __self->_Pfield(tsd_values)[__key]);
    }
#else
# ifdef _PTHREAD_USE_MANGLED_NAMES_
#  ifdef _PTHREAD_USE_PTDNAM_
#   pragma extern_prefix "__"
#  else
#   define pthread_getspecific __pthread_getspecific
#  endif
# endif
extern void* _PTHREAD_CALL_ pthread_getspecific (pthread_key_t);
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix ""
# endif
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_setspecific __pthread_setspecific
# endif
#endif
extern int _PTHREAD_CALL_ pthread_setspecific (pthread_key_t, const void*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#if defined (_PTHREAD_ENV_DECC) && defined (_PTHREAD_ENV_UNIX)
# define pthread_cleanup_push(_routine_,_arg_) \
    { \
    void (*_XXX_proc) (void *) = (void (*)(void *))(_routine_); \
    void *_XXX_arg = (void *)(_arg_); \
    int _XXX_completed = 0; \
    __builtin_try {
# define pthread_cleanup_pop(_execute_) \
    _XXX_completed = 1;} \
    __builtin_finally { \
	if ((! _XXX_completed) || (_execute_)) _XXX_proc (_XXX_arg);} \
    }
#elif defined (_PTHREAD_ENV_WIN32)
# define pthread_cleanup_push(_routine_,_arg_) \
    { \
    void (*_XXX_proc) (void *) = (void (*)(void *))(_routine_); \
    void *_XXX_arg = (void *)(_arg_); \
    int _XXX_completed = 0; \
    __try {
# define pthread_cleanup_pop(_execute_)	\
    _XXX_completed = 1;} \
    __finally { \
	if ((! _XXX_completed) || (_execute_)) _XXX_proc (_XXX_arg);} \
    }
#else
# define pthread_cleanup_push(_routine_,_arg_)	\
    { \
    void (*_XXX_proc) (void *) = (void (*)(void *))(_routine_); \
    void *_XXX_arg = (void *)(_arg_); \
    int _XXX_completed = 0; \
    PTHREAD_TRY_NP {

# define pthread_cleanup_pop(_execute_)	\
    _XXX_completed = 1;} \
    PTHREAD_FINALLY_NP { \
	if ((! _XXX_completed) || (_execute_)) _XXX_proc (_XXX_arg);} \
    PTHREAD_ENDTRY_NP}
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cancel __pthread_cancel
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cancel (pthread_t);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int _PTHREAD_CALL_ pthread_setcancelstate (int, int*);

extern int _PTHREAD_CALL_ pthread_setcanceltype (int, int*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_testcancel __pthread_testcancel
# endif
#endif
extern void _PTHREAD_CALL_ pthread_testcancel (void);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

/*
 * DECthreads non-portable extensions to POSIX 1003.1c-1995.
 */

/*
 * Get or set a name to be associated with threads created using the
 * attributes object. Note that only the thread attributes object includes a
 * name -- for other objects, it is sufficient to set the name immediately
 * after initializing the object (whereas a thread may run between the call to
 * pthread_create and the call to pthread_setname_np, without a name).
 *
 * Note that the "void*" value to which "mbz" points MAY be written by the
 * thread library. On Alpha hardware (Digital UNIX and OpenVMS) the value to
 * which "mbz" points must be a 64-bit pointer. If you are compiling with
 * short pointers, you must take extra steps to ensure that you have allocated
 * a 64-bit value to receive the result.
 */
extern int _PTHREAD_CALL_ pthread_attr_getname_np (
	const pthread_attr_t*,
	char*,
	size_t,
	void**);

extern int _PTHREAD_CALL_ pthread_attr_setname_np (
	pthread_attr_t*,
	const char*,
	void*);

/*
 * Get or set a name on a condition variable.
 */
extern int _PTHREAD_CALL_ pthread_cond_getname_np (
	pthread_cond_t*,
	char*,
	size_t);

extern int _PTHREAD_CALL_ pthread_cond_setname_np (
	pthread_cond_t*,
	const char*,
	void*);

/*
 * Get or set a name on a thread-specific data key
 */
extern int _PTHREAD_CALL_ pthread_key_getname_np (
	pthread_key_t,
	char*,
	size_t);

extern int _PTHREAD_CALL_ pthread_key_setname_np (
	pthread_key_t,
	const char*,
	void*);

/*
 * Get or set a name on a mutex
 */
extern int _PTHREAD_CALL_ pthread_mutex_getname_np (
	pthread_mutex_t*,
	char*,
	size_t);

extern int _PTHREAD_CALL_ pthread_mutex_setname_np (
	pthread_mutex_t*,
	const char*,
	void*);

/*
 * Get or set a name on a rwlock
 */
extern int _PTHREAD_CALL_ pthread_rwlock_getname_np (
	pthread_rwlock_t*,
	char*,
	size_t);

extern int _PTHREAD_CALL_ pthread_rwlock_setname_np (
	pthread_rwlock_t*,
	const char*,
	void*);

/*
 * Get or set a name on a thread
 */
extern int _PTHREAD_CALL_ pthread_getname_np (
	pthread_t,
	char*,
	size_t);

extern int _PTHREAD_CALL_ pthread_setname_np (
	pthread_t,
	const char*,
	void*);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_sig_preempt_int_np __pthread_cond_sig_preempt_int_np
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cond_sig_preempt_int_np (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_cond_signal_int_np __pthread_cond_signal_int_np
# endif
#endif
extern int _PTHREAD_CALL_ pthread_cond_signal_int_np (pthread_cond_t*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_get_expiration_np __pthread_get_expiration_np
# endif
#endif
extern int _PTHREAD_CALL_ pthread_get_expiration_np (
	const struct timespec*,
	struct timespec*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_delay_np __pthread_delay_np
# endif
#endif
extern int _PTHREAD_CALL_ pthread_delay_np (
	const struct timespec*);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_lock_global_np __pthread_lock_global_np
# endif
#endif
extern int _PTHREAD_CALL_ pthread_lock_global_np (void);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_unlock_global_np __pthread_unlock_global_np
# endif
#endif
extern int _PTHREAD_CALL_ pthread_unlock_global_np (void);
#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_setguardsize_np __pthread_attr_setguardsize_np
# endif
#endif
extern int _PTHREAD_CALL_ pthread_attr_setguardsize_np (
	pthread_attr_t*,
	size_t);

#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int _PTHREAD_CALL_ pthread_attr_setguardsize (
	pthread_attr_t*,
	size_t);

#ifdef _PTHREAD_USE_MANGLED_NAMES_
# ifdef _PTHREAD_USE_PTDNAM_
#  pragma extern_prefix "__"
# else
#  define pthread_attr_getguardsize_np __pthread_attr_getguardsize_np
# endif
#endif
extern int _PTHREAD_CALL_ pthread_attr_getguardsize_np (
	const pthread_attr_t*,
	size_t*);

#ifdef _PTHREAD_USE_PTDNAM_
# pragma extern_prefix ""
#endif

extern int _PTHREAD_CALL_ pthread_attr_getguardsize (
	const pthread_attr_t*,
	size_t*);

extern unsigned long _PTHREAD_CALL_ pthread_getsequence_np (pthread_t);

extern unsigned long _PTHREAD_CALL_ pthread_getselfseq_np (void);

/*
 * By default (unless #undef-ed) use an inlined macro version of
 * pthread_getsequence_np, since it's trivial.
 */
#ifdef _PTHREAD_ENV_UNIX
# define pthread_getsequence_np(_t_) (((pthread_t)(_t_))->_Pfield(sequence))
# define pthread_getselfseq_np() (pthread_self ()->_Pfield(sequence))
#else
# define pthread_getsequence_np(_t_) (((pthreadTeb_p)(_t_))->_Pfield(sequence))
# define pthread_getselfseq_np() (pthreadTeb ()->_Pfield(sequence))
#endif

/*
 * The POSIX 1003.1c pthread_getspecific() function doesn't report any
 * errors. If the key value is illegal, or if the thread has no value for the
 * key, it returns NULL without any error indication. Normally that's not a
 * problem. However if you really want to know whether a key is valid, you
 * can use this function. It will return EINVAL if the key is invalid, ENOENT
 * if the key exists but the thread has no value for the key (or value is
 * NULL), and 0 if the key is valid and the thread has a value.
 */
extern int _PTHREAD_CALL_ pthread_key_validate_np (pthread_key_t);

/*
 * DECthreads provides three distinct types of mutex. The default (normal or
 * "fast" mutex), which can lock and unlock with completely inline code on
 * Alpha processors, but does no consistency checking; the "recursive" mutex
 * which allows a given thread to lock a mutex it already owns without
 * deadlock (it remains locked until all nested locks are released); and the
 * "errorcheck" mutex, which behaves much like a normal mutex but checks for
 * self deadlock and for releasing a mutex that is either unowned or is owned
 * by another thread. The recursive and errorcheck mutexes require a call
 * into the DECthreads library for every lock and unlock.
 *
 * When synchronization metering is enabled, all mutex types monitor every
 * lock and unlock. A mutex statically initialized using
 * PTHREAD_MUTEX_INITIALIZER is "normal", but is set up so that the first use
 * of the mutex will result in a call into DECthreads (as if the mutex was
 * already locked). If synchronization metering is not enabled, DECthreads
 * will disable this extra state so that future references (in the absence of
 * normal mutex contention) will not cause unnecessary calls. Should you wish
 * to avoid this initial call, you can compile with _PTHREAD_NOMETER_STATIC;
 * normal mutexes statically initialized using this option are not metered.
 */
extern int _PTHREAD_CALL_ pthread_mutexattr_gettype (
	const pthread_mutexattr_t*,
	int*);

extern int _PTHREAD_CALL_ pthread_mutexattr_gettype_np (
	const pthread_mutexattr_t*,
	int*);

extern int _PTHREAD_CALL_ pthread_mutexattr_settype (
	pthread_mutexattr_t*,
	int);

extern int _PTHREAD_CALL_ pthread_mutexattr_settype_np (
	pthread_mutexattr_t*,
	int);

#ifdef _PTHREAD_ENV_UNIX
extern int pthread_mutexattr_setpshared (pthread_mutexattr_t*, int);

extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t*, int*);
#endif

extern int _PTHREAD_CALL_ pthread_rwlock_init (
	pthread_rwlock_t*,
	const pthread_rwlockattr_t*);

extern int _PTHREAD_CALL_ pthread_rwlock_destroy (pthread_rwlock_t*);

extern int _PTHREAD_CALL_ pthread_rwlock_rdlock (pthread_rwlock_t*);

extern int _PTHREAD_CALL_ pthread_rwlock_tryrdlock (pthread_rwlock_t*);

extern int _PTHREAD_CALL_ pthread_rwlock_wrlock (pthread_rwlock_t*);

extern int _PTHREAD_CALL_ pthread_rwlock_trywrlock (pthread_rwlock_t*);

extern int _PTHREAD_CALL_ pthread_rwlock_unlock (pthread_rwlock_t*);

extern int _PTHREAD_CALL_ pthread_rwlockattr_init (pthread_rwlockattr_t*);

extern int _PTHREAD_CALL_ pthread_rwlockattr_destroy (pthread_rwlockattr_t*);

#ifdef _PTHREAD_ENV_UNIX
extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t*, int*);

extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t*, int);
#endif

extern int _PTHREAD_CALL_ pthread_yield_np (void);

/*
 * Debugging functions
 */

extern void _PTHREAD_CALL_ pthread_debug (void);

/*
 * The pthread_debug_cmd() function returns the status of the last specified
 * operation in the command string.
 */
typedef enum pthreadDbgStatus_t {
    PTHREAD_DBG_SUCCESS = 0,		/* Command was successful */
    PTHREAD_DBG_QUIT = 1,		/* Last command was 'quit' or 'exit' */
    PTHREAD_DBG_NONESEL = 2,		/* No objects selected */
					/*  (e.g., "thread -br") */
    PTHREAD_DBG_SUCCESSPEND = 3,	/* Alternate success */
    PTHREAD_DBG_NOPRIV = -1,		/* No privilege for command */
    PTHREAD_DBG_INVPARAM = -2,		/* Invalid parameter on command */
    PTHREAD_DBG_INVSEQ = -3,		/* Invalid object sequence number */
    PTHREAD_DBG_INCONSTATE = -4,	/* Inconsistent state for operation */
    PTHREAD_DBG_CORRUPT = -5,		/* Unable to complete; */
					/*  internal corruption */
    PTHREAD_DBG_INVOPTION = -6,		/* Invalid command options */
    PTHREAD_DBG_NOARG = -7,		/* Missing command argument */
    PTHREAD_DBG_INVADDR = -8,		/* Invalid address */
    PTHREAD_DBG_INVCMD = -9,		/* Invalid command */
    PTHREAD_DBG_NULLCMD = -10,		/* No command given */
    PTHREAD_DBG_CONFLICT = -11,		/* Conflicting options */
    PTHREAD_DBG_UNIMPL = -12		/* Unimplemented feature */
    } pthreadDbgStatus_t;

/*
 * Pass a command string to DECthreads debug for interpretation. The
 * argument is a "char *" command string.
 */
extern pthreadDbgStatus_t _PTHREAD_CALL_ pthread_debug_cmd (char *);

#if defined (_PTHREAD_ENV_DECC_CXX)
# if defined (_PTHREAD_ENV_VMS)
#  if (__DECC_VER >= 50200000) || (__DECCXX_VER >= 50200000)
#   pragma __environment __restore
#  else
#   pragma __extern_model __restore
#  endif
# else
#  pragma __environment __restore
# endif
#elif defined (_PTHREAD_ENV_VAXC)
# pragma standard
#endif

#ifdef _PTHREAD_ENV_CXX
    } /* End of extern "C" { */
#endif

#endif					/* _PTHREAD_USE_D4 */

#endif
