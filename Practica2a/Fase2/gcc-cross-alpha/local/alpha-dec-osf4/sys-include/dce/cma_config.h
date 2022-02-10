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
 * @(#)$RCSfile: cma_config.h,v $ $Revision: 4.2.22.2 $ (DEC) $Date: 1998/10/02 21:40:52 $
 */
/*
 *  FACILITY:
 *
 *	DECthreads core
 *
 *  ABSTRACT:
 *
 *	Configuration header file to set up control symbols.
 *
 *  AUTHORS:
 *
 *	Dave Butenhof
 *
 *  CREATION DATE:
 *
 *	26 January 1990
 *
 *  MODIFIED BY:
 *
 *	Dave Butenhof
 *	Bob Conti
 *	Paul Curtin
 *	Webb Scales
 *	Brian Keane
 *	Brian Silver
 *
 *  LAST MODIFIED:
 *
 *	13 August 1998
 */

#ifndef CMA_CONFIG
#define CMA_CONFIG

/*
 *  INCLUDE FILES
 */

/*
 * CONFIGURATION SYMBOLS
 */

/*
 * Quick reference guide to the external DECthreads configuration symbols:
 *
 *	_CMA_COMPILER_		(CC, VAXC, DECC, CFRONT, GCC,
 *				DECCPLUS, GCPLUS, MSC)
 *			Each compiler has its own quirks, and DECthreads
 *			tries to do as much with each as possible. For
 *			example, it instantiates function prototypes where
 *			possible, even if the compiler is not fully ANSI C
 *			compliant.
 *	_CMA_HARDWARE_		(MIPS, VAX, ALPHA, X86)
 *			The computer on which DECthreads will run.
 *	_CMA_OS_		(UNIX, VMS, NT)
 *			The operating system on which DECthreads will run;
 *			generally, all UNIX-descended systems have certain
 *			similarities which need to be considered as a group.
 *	_CMA_PLATFORM_		(MIPS/UNIX, VAX/VMS, VAX/UNIX, ALPHA/UNIX,
 *				 ALPHA/VMS, X86/NT, ALPHA/NT)
 *			This is a convenience to test both hardware and O/S
 *			variants together.
 *	_CMA_PROTO_	(1 or undefined)
 *			This is set if the compiler supports function
 *			prototypes (if __STDC__ is true, or if any of a
 *			number of specific compilers is being used). Note:
 *			this must be tested by an #ifdef.
 *	_CMA_OSIMPL_		(OSF, BSD, SYSV)
 *			The closest ancestor of the UNIX operating system,
 *			since each family inherits common characteristics
 *			(particularly in signal behaviors).
 *	_CMA_VOID_		(0, 1)
 *			This is TRUE (1) if the compiler supports the use of
 *			"void *" types. Most __STDC__ compilers do (except
 *			that a version of MIPS C had a bug that prevented its
 *			use). If _CMA_VOID_ is FALSE (0), DECthreads will use
 *			"char *" instead.
 *	_CMA_VOLATILE_		("volatile" or "")
 *			DECthreads requires "volatile" storage class in
 *			several places, including exception handling. Since
 *			some compilers do not support "volatile", DECthreads
 *			uses this symbol in place of the "volatile" keyword.
 *			Note that DECthreads runtimes built with compilers
 *			that do not support volatile may show incorrect
 *			behavior under certain circumstances (particularly
 *			during delivery of exceptions). Because these
 *			situations tend to occur only when errors have
 *			already occurred, it is hoped that the absence of
 *			volatile will not prevent normal DECthreads
 *			operation.
 *	_CMA_REENTRANT_CLIB_	(0, 1)
 *			If TRUE (1) then the C library functions are thread
 *			reentrant.
 *	_CMA_IMPORT_, _CMA_EXPORT_
 *			Specifies the keywords used for EXPORTing variables
 *			from DECthreads, or IMPORTing those variables to
 *			client code. For normal UNIX systems, IMPORT is
 *			usually "extern" and EXPORT is usually null. Because
 *			of oddities in the VAX C implementation of extern,
 *			DECthreads uses "globaldef" for EXPORT and
 *			"globalref" for IMPORT.
 *	_CMA_NOWRAPPERS_	(1 or undefined)
 *			If defined, DECthreads will not use its I/O and C
 *			library wrapper functions. Generally, this is set to
 *			1 for building DECthreads, and undefined for building
 *			client code.  [There is no default definition provided
 *			for this symbol in this file, since the default is for
 *			it to be undefined.]
 *	_CMA_VSSCANF_		(0, 1)
 *			If set to 1, the DECthreads stdio wrappers will
 *			include the scanf family. The wrappers cannot be
 *			built without the real "v*scanf" functions, which don't
 *			exist on most platforms; but we're prepared if we
 *			ever find a platform that does support them. Note that
 *			we assume that using one symbol implicitly assumes
 *			that if one of the v*scanf family is present, they
 *			all will be.
 *	_CMA_CONST_	("const" or "")
 *			Similar to _CMA_VOID_ and _CMA_VOLATILE_; used for the
 *			I/O wrappers to make compliant with POSIX and ANSI C.
 *	_CMA_RT4_KTHREAD_	(0, 1)
 *			Set if O/S supports POSIX scheduling policies on
 *			kernel threads.
 *	_CMA_POSIX_SCHED_	(0, 1)
 *			Set if DECthreads should support POSIX scheduling
 *			policy & priorities. Set for all user-mode builds;
 *			clear for kernel-thread builds unless O/S threads can
 *			handle it.
 *	_CMA_CALL_	("__stdcall" or "")
 *			Denotes the calling convention for an external routine.
 *			Only significant on Windows NT systems.
 *
 */

/*
 * NOTE: all configuration symbols are set up such that they can be
 * overridden by a -D switch on the command line if desired (but be sure
 * that you know what you're doing).
 */

/*
 * Name of the platform C compiler
 */
#define _CMA__CC	1
#define _CMA__VAXC	2
#define _CMA__DECC	3
#define _CMA__CFRONT	4
#define _CMA__GCC	5
#define _CMA__DECCPLUS	6
#define _CMA__GCPLUS	7
#define _CMA__MSC	8

/*
 * Test for C++ compilers before C compilers because Glockenspiel C++ also
 * defines symbols for the VAX C compiler and this could be the case for
 * other C++/C compiler combinations
 */
#ifndef _CMA_COMPILER_
# if defined (__cplusplus)
#  if defined (__DECCXX)
#   define _CMA_COMPILER_	_CMA__DECCPLUS
#  elif defined (WIN32) || defined (_WIN32)
#   define _CMA_COMPILER_	 _CMA__MSC
#  else
#   define _CMA_COMPILER_	_CMA__CFRONT
#  endif
# elif defined (__decc) || defined (__DECC)
#  define _CMA_COMPILER_	_CMA__DECC
# elif defined (vaxc) || defined (VAXC) || defined (__vaxc) || defined (__VAXC)
#  define _CMA_COMPILER_	_CMA__VAXC
# elif defined (__GNUC__) || defined (__GNUC) || defined (__gnuc)
#  define _CMA_COMPILER_	_CMA__GCC
# elif defined (WIN32) || defined (_WIN32)
#  define _CMA_COMPILER_	_CMA__MSC
# else
#  define _CMA_COMPILER_	_CMA__CC
# endif
#endif

/*
 * Name of the hardware platform
 */
#define _CMA__MIPS	1
#define _CMA__VAX	2
#define _CMA__ALPHA	3
#define _CMA__X86	4

#ifndef	_CMA_HARDWARE_
# if defined (vax) || defined (VAX) || defined (__vax) || defined (__VAX)
#  define _CMA_HARDWARE_	_CMA__VAX
# elif defined (mips) || defined (MIPS) || defined (__mips) || defined (__MIPS)
#  define _CMA_HARDWARE_	_CMA__MIPS
# elif defined (__ALPHA) || defined (__alpha)
#  define _CMA_HARDWARE_	_CMA__ALPHA
# elif defined (_M_IX86)
#  define _CMA_HARDWARE_	_CMA__X86
# else
!  error _CMA_HARDWARE_ not set
# endif
#endif

/*
 * Name of the software platform (i.e., the OS)
 */
#define _CMA__UNIX	1
#define _CMA__VMS	2
#define _CMA__WIN32	3
# define _CMA__NT	_CMA__WIN32	/* for compatibility */

#ifndef	_CMA_OS_
# if defined (unix) || defined (__unix) \
     || defined (__OSF__) || defined (__osf__)
#  define _CMA_OS_	_CMA__UNIX
# elif defined (vms) || defined (__vms) || defined (VMS) || defined (__VMS)
#  define _CMA_OS_	_CMA__VMS
# elif defined (WIN32) || defined (_WIN32)
#  define _CMA_OS_	_CMA__WIN32
# else
!  error _CMA_OS_ not set
# endif
#endif

/*
 * Combined platform (OS + hardware)
 */
#define _CMA__MIPS_UNIX		1
#define _CMA__VAX_VMS		2
#define _CMA__VAX_UNIX		3
#define _CMA__ALPHA_UNIX	4
#define _CMA__ALPHA_VMS		5
#define _CMA__ALPHA_NT		6
#define _CMA__X86_NT		7

#ifndef _CMA_PLATFORM_
# if _CMA_OS_ == _CMA__UNIX
#  if _CMA_HARDWARE_ == _CMA__MIPS
#   define _CMA_PLATFORM_	_CMA__MIPS_UNIX
#  elif _CMA_HARDWARE_ == _CMA__VAX
#   define _CMA_PLATFORM_	_CMA__VAX_UNIX
#  elif _CMA_HARDWARE_ == _CMA__ALPHA
#   define _CMA_PLATFORM_	_CMA__ALPHA_UNIX
#  else
!   error Undefined Unix hardware platform
#  endif
# elif _CMA_OS_ == _CMA__VMS
#  if _CMA_HARDWARE_ == _CMA__VAX
#   define _CMA_PLATFORM_	_CMA__VAX_VMS
#  elif _CMA_HARDWARE_ == _CMA__ALPHA
#   define _CMA_PLATFORM_	_CMA__ALPHA_VMS
#  else
!   error Undefined VMS hardware platform
#  endif
# elif _CMA_OS_ == _CMA__WIN32
#  if _CMA_HARDWARE_ == _CMA__X86
#   define _CMA_PLATFORM_	_CMA__X86_NT
#  elif _CMA_HARDWARE_ == _CMA__ALPHA
#   define _CMA_PLATFORM_	_CMA__ALPHA_NT
#  else
!   error Undefined Win32 hardware platform
#  endif
# else
!  error _CMA_PLATFORM_ not set
# endif
#endif

/*
 * Unix derivative (default to BSD)
 */
#define _CMA__OS_OSF	1
#define _CMA__OS_BSD	2
#define _CMA__OS_SYSV	3

#ifndef _CMA_OSIMPL_
# if _CMA_OS_ == _CMA__UNIX
#  ifdef __osf__
#   define _CMA_OSIMPL_ _CMA__OS_OSF
#  elif 0
#   define _CMA_OSIMPL_ _CMA__OS_SYSV
#  else
#   define _CMA_OSIMPL_ _CMA__OS_BSD
#  endif
# else
#  define _CMA_OSIMPL_ 0	/* Not an implementation of Unix */
# endif
#endif

/*
 * This controls whether ANSI C function prototypes are used for CMA
 * interfaces.
 */
#ifndef	_CMA_PROTO_
# if !((_CMA_PLATFORM_ == _CMA__VAX_UNIX) && (_CMA_COMPILER_ == _CMA__CC))
#  define _CMA_PROTO_		1
# endif
#else
# if _CMA_PROTO_ == 0
#  undef _CMA_PROTO_
    /* _CMA_PROTO_ is undefined, which means do not use prototypes. */
# endif
#endif

#ifdef _CMA_PROTO_
# define _CMA_PROTOTYPE_(arg)	arg
#else
# define _CMA_PROTOTYPE_(arg)	()
#endif

/*
 * Define a macro to control calling convention.  Only significant on
 * Windows NT.
 */
#ifndef	_CMA_CALL_
# if _CMA_OS_ == _CMA__WIN32
#  define _CMA_CALL_ __stdcall
# else
#  define _CMA_CALL_
# endif
#endif


/*
 * Define whether to use "void *" or "char *" pointers, based on whether the
 * compiler can support them.
 */
#ifndef	_CMA_VOID_
# if (_CMA_PLATFORM_ == _CMA__VAX_UNIX) && (_CMA_COMPILER_ == _CMA__CC)
#  define _CMA_VOID_	0
# else
#  define _CMA_VOID_	1
# endif
#endif

/*
 * Set this to "volatile" unless using a deficient compiler.
 */
#ifndef	_CMA_VOLATILE_
# if (_CMA_PLATFORM_ == _CMA__VAX_UNIX) && (_CMA_COMPILER_ == _CMA__CC)
#  define _CMA_VOLATILE_
# elif _CMA_COMPILER_ == _CMA__CFRONT
#  define _CMA_VOLATILE_
# else
#  define _CMA_VOLATILE_	volatile
# endif
#endif

/*
 * Kernel-threads type.
 * (These are values used to define _CMA_KTHREADS_in cma_os.h)
 */
#define _CMA__NONE	0
#define _CMA__MACH	1
#define _CMA__NTTHREADS 2

/*
 * _CMA_REENTRANT_CLIB_ is true IFF the platform's C library is reentrant.
 */
#ifndef _CMA_REENTRANT_CLIB_
# if _CMA_OSIMPL_ == _CMA__OS_OSF
#  define _CMA_REENTRANT_CLIB_	1
# elif (_CMA_COMPILER_ == _CMA__DECC) || (_CMA_COMPILER_ == _CMA__DECCPLUS)
#  define _CMA_REENTRANT_CLIB_	1
# elif _CMA_OS_ == _CMA__WIN32
#  define _CMA_REENTRANT_CLIB_  1
# else
#  define _CMA_REENTRANT_CLIB_	0
# endif
#endif

/*
 * Define the symbols used to "import" and "export" symbols for the client
 * interface.  Note that these shouldn't be used for symbols shared only
 * between CMA modules; it's for those symbols which are "imported" in the
 * cma.h (or pthread.h) header files, such as cma_c_null,
 * pthread_attr_default, and the exception names.
 */
#if ((_CMA_COMPILER_ == _CMA__DECC) || (_CMA_COMPILER_ == _CMA__DECCPLUS)) \
    && (_CMA_OS_ == _CMA__VMS)
# pragma __extern_model __save		/* restored at the end of cma.h */
# pragma __extern_model __strict_refdef
# define _CMA_IMPORT_ extern
# define _CMA_EXPORT_
#elif _CMA_COMPILER_ == _CMA__VAXC
# pragma nostandard			/* restored at the end of cma.h */
# define _CMA_IMPORT_ globalref
# define _CMA_EXPORT_ globaldef
#else
# define _CMA_IMPORT_ extern
# define _CMA_EXPORT_
#endif

/*
 * True if the system supplies the vsscanf() function
 */
#ifndef _CMA_VSSCANF_
# define _CMA_VSSCANF_	0
#endif

/*
 * ANSI C defines some parameters using the const modifier. Use this macro
 * to make the function signatures ANSI and POSIX compliant for STDIO and
 * thread I/O. wrappers. Size_t is defined by including stdio.h which is
 * included in cma_stdio.h and cma_stdio.c
 */
#if defined (__STDC__) || (_CMA_COMPILER_ == _CMA__MSC)
# define _CMA_CONST_ const
# define _CMA_SIZE_T size_t
#else
# define _CMA_CONST_
# define _CMA_SIZE_T unsigned int
#endif

/*
 * Set a symbol if we're building a kernel thread version on a system that
 * supports POSIX.4 scheduling semantics for kernel threads.
 */
#ifndef _CMA_RT4_KTHREAD_
# if _CMA_OSIMPL_ == _CMA__OS_OSF
#  define _CMA_RT4_KTHREAD_	1
# else
#  define _CMA_RT4_KTHREAD_	0
# endif
#endif

/*
 * _CMA_POSIX_SCHED_ is true if not kernel threads, or if it's a specific
 * type of kernel threads that supports POSIX scheduling.
 */
#ifndef _CMA_POSIX_SCHED_
# if _CMA_OS_ != _CMA__WIN32
#  define _CMA_POSIX_SCHED_	1
# else
#  define _CMA_POSIX_SCHED_	0
# endif
#endif

#endif					/* CMA_CONFIG */
