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
 *	@(#)$RCSfile: unistd.h,v $ $Revision: 4.2.47.2 $ (DEC) $Date: 1999/01/13 20:22:56 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Copyright (c) 1984 AT&T	
 * All Rights Reserved  
 *
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	
 * The copyright notice above does not evidence any   
 * actual or intended publication of such source code.
 * 
 * unistd.h	1.17  com/inc,3.1,8943 9/22/89 15:13:11
 */

#ifndef _UNISTD_H_
#define _UNISTD_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#ifndef _KERNEL	
#include <sys/types.h>  /* for time_t and size_t */
#include <sys/access.h>	/* for the "access" function */

/*
 * POSIX requires that certain values be included in unistd.h.  It also
 * requires that when _POSIX_C_SOURCE is defined (>= 1) only those 
 * standard specific values are present.  This header includes all the POSIX
 * required entries.
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)
/* Symbolic constants for the "lseek" function: */

#include <sys/seek.h>
#include <getopt.h>

/***AAB-XPG4*** must protect from XPG4 ***/
#ifdef _OSF_SOURCE
extern char **environ;          /* Environment description variable */
#endif /*OSF_SOURCE*/

#ifdef _NONSTD_TYPES
extern int     read();
extern int     write();
#else

#if defined(_OSF_SOURCE)
extern ssize_t	pread __((int, void *, size_t, off_t));
extern ssize_t	pwrite __((int , const void *, size_t, off_t)); 
#endif

extern ssize_t	read __((int, void *, size_t));
extern ssize_t	write __((int , const void *, size_t)); 
#endif  /* _NONSTD_TYPES */

extern int access __((const char *, int ));
extern unsigned int alarm __((unsigned int ));
extern int chdir __((const char *));
extern int chown __((const char *, uid_t , gid_t ));
extern int chroot __((const char *));
extern int close __((int ));
extern size_t confstr __((int, char *, size_t));
#ifndef _XOPEN_SOURCE
extern char *cuserid __((char *));
#endif
extern int dup __((int ));
extern int dup2 __((int , int ));

/***AAB-XPG4 Parameter names not allowed in ANSI-C ***/
extern int execl __((const char *, const char *, ...));
extern int execv __((const char *, char *const[]));
extern int execle __((const char *, const char *, ...)); 
extern int execve __((const char *, char *const[], char *const[]));
extern int execlp __((const char *, const char *, ...)); 
extern int execvp __((const char *, char *const[]));
/*AAB_XPG4*/

extern void _exit __((int ));
extern pid_t fork __((void));
extern long fpathconf __((int , int ));
extern int fsync __((int));
#if (_POSIX_C_SOURCE >= 199306L)
extern int fdatasync __((int));
#endif
extern char *getcwd __((char *, size_t ));
extern gid_t getegid __((void));
extern uid_t geteuid __((void));
extern gid_t getgid __((void));


/***AAB-XPG4 Parameter names not allowed in ANSI-C ***/
extern int getgroups __((int , gid_t []));

extern char *getlogin __((void));
extern pid_t getpgrp __((void));
extern pid_t getpid __((void));
extern pid_t getppid __((void));
extern uid_t getuid __((void));
extern int isatty __((int ));
extern int link __((const char *, const char *));
extern off_t lseek __((int , off_t , int ));
extern long pathconf __((const char *, int ));
extern int pause __((void));


/***AAB-XPG4 Parameter names not allowed in ANSI-C ***/

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define pipe(__a) _Epipe(__a)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int __R(pipe) __((int []));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern int rmdir __((const char *));
extern int setgid __((gid_t ));
extern int setpgid __((pid_t , pid_t ));
extern pid_t setsid __((void));
extern int setuid __((uid_t ));
extern unsigned int sleep __((unsigned int ));

#ifdef _XOPEN_SOURCE_EXTENDED
extern int usleep __((useconds_t ));	/* spec1170 requires a value to be returned */
#else

#ifndef _XOPEN_SOURCE
extern void usleep __((unsigned int));
#endif	/* _XOPEN_SOURCE */

#endif /* _XOPEN_SOURCE_EXTENDED */

extern long sysconf __((int ));
extern pid_t tcgetpgrp __((int ));
extern int tcsetpgrp __((int , pid_t ));
extern char *ttyname __((int ));
extern int unlink __((const char *));
#ifndef __SVID__
extern void swab __((const void *, void *, ssize_t));
#endif

/* POSIX REENTRANT FUNCTIONS */
#if (_POSIX_C_SOURCE >= 199506L)

#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix "_P"
#else
#define	getlogin_r(__a,__b)	_Pgetlogin_r(__a,__b)
#define	ttyname_r(__a,__b,__c)	_Pttyname_r(__a,__b,__c)
#endif	/* __DECC */
#endif	/* !_LIBC_POLLUTION_H_ */
extern int __P_C(getlogin_r) __((char *, size_t));	/* _POSIX_REENTRANT_FUNCTIONS */
extern int __P_C(ttyname_r) __((int, char *, size_t));	/* _POSIX_REENTRANT_FUNCTIONS */
#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix ""
#endif	/* __DECC */
#endif	/* !_LIBC_POLLUTION_H_ */

extern int pthread_atfork __((void (*)(void), void (*)(void), void (*)(void)));

#else

#if !defined (_XOPEN_SOURCE) || defined (_OSF_SOURCE)

extern int getlogin_r __((char *, int));
extern int ttyname_r __((int, char *, int));

#endif /* !defined (_XOPEN_SOURCE) || defined (_OSF_SOURCE) */

#endif	/* P1003.1c */

#define STDIN_FILENO	0
#define STDOUT_FILENO	1
#define STDERR_FILENO	2

#define _POSIX_VERSION  199506L

#endif /* _POSIX_C_SOURCE */
#endif /* ifndef _KERNEL */

/* swab() declaration for SysV */
#ifdef __SVID__
extern void swab __((const char *, char *, int));
#endif

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)

#define _POSIX_CHOWN_RESTRICTED	 0 /* chown requires appropriate privileges */
#define _POSIX_NO_TRUNC	     	 0 /* too-long path components gen errors */

#ifndef _POSIX_VDISABLE
#define _POSIX_VDISABLE		0377
#endif /* _POSIX_VDISABLE */

#endif /* _POSIX_C_SOURCE */
#ifndef _KERNEL
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)

#define	_POSIX_THREADS		/* 1003.1c (pthreads) comformant */
#define _POSIX_THREAD_ATTR_STACKSIZE /* support for specifiable stack sizes */
#define	_POSIX_REENTRANT_FUNCTIONS  /* multithreaded 1003.1 interfaces */
#define _POSIX_JOB_CONTROL       1  /* implementation supports job control */
#define _POSIX_SAVED_IDS         1  /* saved set-user-id and set-group-id */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L)
#define _POSIX_THREAD_SAFE_FUNCTIONS
#define _POSIX_THREAD_PRIORITY_SCHEDULING
#endif /* _POSIX_C_SOURCE >= 199506L */

#define _POSIX2_C_BIND     1  /* supports the C language binding */
#define _POSIX2_C_DEV      1  /* supports the C development env  */
#define _POSIX2_LOCALEDEF  1  /* supports creation of lacales with localedef */
#define _POSIX2_SW_DEV     1  /* supports software development */
#define _POSIX2_CHAR_TERM  1  /* supports a least one terminal */
#define _POSIX2_UPE        1  /* supports the User Portability Environment */

#undef _POSIX2_FORT_DEV       /* no support for FORTRAN developemnt */
#undef _POSIX2_FORT_RUN       /* no support for FORTRAN runtime */

#define _POSIX2_C_VERSION     199209L /* Support ISO POSIX-2 */
#define _POSIX2_VERSION       199209L /* POSIX.2 standard */


#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)
/*
 * POSIX 1003.1b Feature Test Macros
 * Supported features
 */

#define _POSIX_ASYNCHRONOUS_IO
#define _POSIX_SYNCHRONIZED_IO
#define _POSIX_FSYNC
#define _POSIX_MAPPED_FILES
#define _POSIX_MEMLOCK
#define _POSIX_MEMLOCK_RANGE
#define _POSIX_MEMORY_PROTECTION
#define _POSIX_PRIORITY_SCHEDULING
#define _POSIX_SHARED_MEMORY_OBJECTS
#define _POSIX_TIMERS
#define _POSIX_REALTIME_SIGNALS
#define _POSIX_MESSAGE_PASSING 
#define _POSIX_SEMAPHORES    

/*
 * NOTE: _SC_PAGESIZE for sysconf() is defined both in POSIX 1003.1b,
 * and in AES, below. Keep same as AES definition.
 */
#ifndef _AES_SOURCE
#define _SC_PAGESIZE		43
#endif /* ifndef _AES_SOURCE */

/* Realtime arguments for the sysconf() function */
#define _SC_4VERSION            100
#define _SC_LISTIO_AIO_MAX      101
#define _SC_AIO_MAX             102
#define _SC_CLOCKDRIFT_MAX      103
#define _SC_DELAYTIMER_MAX      104
#define _SC_RTSIG_MAX		105
#define _SC_SEM_NAME_MAX	106
#define _SC_SEM_NSEMS_MAX	107
#define _SC_TIMER_MAX		109
#define _SC_ASYNCHRONOUS_IO	110
#define _SC_FSYNC		112
#define _SC_MAPPED_FILES	113
#define _SC_MEMLOCK		114
#define _SC_MEMLOCK_RANGE	115
#define _SC_MEMORY_PROTECTION	116
#define _SC_MESSAGE_PASSING	117
#define _SC_PRIORITIZED_IO	118
#define _SC_PRIORITY_SCHEDULING	119
#define _SC_REALTIME_SIGNALS	121
#define _SC_SHARED_MEMORY_OBJECTS 122
#define _SC_SYNCHRONIZED_IO	123
#define _SC_TIMERS		124
#define _SC_SEMAPHORES          125
#define _SC_SEM_VALUE_MAX       126
#define _SC_MQ_OPEN_MAX         127
#define _SC_MQ_PRIO_MAX         128
#define _SC_SIGQUEUE_MAX	130
/*
 * NOTE: these values are hardcoded for SIGRTMIN and SIGRTMAX
 * in <sys/signal.h>. Any change here must be reflected there.
 */
#define _SC_RTSIG_LOW		131
#define _SC_RTSIG_HI		132
#endif /* _POSIX_C_SOURCE >= 199309L */

/*
 * definitions for the MP extensions to sysconf()
 */

#define _SC_NPROC_CONF  200
#define _SC_NPROCESSORS_CONF _SC_NPROC_CONF
#define	_SC_NPROC_ONLN	201
#define	_SC_NPROCESSORS_ONLN _SC_NPROC_ONLN

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199506L)
/*
 * definitions for the POSIX thread arguments to sysconf()
 */
#define _SC_THREAD_DESTRUCTOR_ITERATIONS 210
#define _SC_THREAD_KEYS_MAX              211
#define _SC_THREAD_STACK_MIN             212
#define _SC_THREAD_THREADS_MAX           213
#define _SC_THREADS                      214
#define _SC_THREAD_SAFE_FUNCTIONS        215
#define _SC_THREAD_ATTR_STACKSIZE        216
#define _SC_THREAD_PRIORITY_SCHEDULING   217
#define	_SC_GETGR_R_SIZE_MAX		218
#define	_SC_GETPW_R_SIZE_MAX		219
#define	_SC_LOGIN_NAME_MAX		220
#define	_SC_TTY_NAME_MAX		221
#define	_SC_THREAD_ATTR_STACKADDR	222
#define	_SC_THREAD_PRIO_INHERIT		223
#define	_SC_THREAD_PRIO_PROTECT		224
#define	_SC_THREAD_PROCESS_SHARED	225
#endif /* _POSIX_C_SOURCE >= 199506L */

#ifndef NULL
#define NULL	0L
#endif


/* arguments for the confstr() function */

#define	_CS_PATH		1
#define _CSPATH			"/usr/bin"

/* arguments for the sysconf() function */

#define _SC_ARG_MAX		1
#define _SC_CHILD_MAX		2
#define _SC_CLK_TCK		3
#define _SC_JOB_CONTROL		4
#define _SC_NGROUPS_MAX		5
#define _SC_OPEN_MAX		6
#define _SC_SAVED_IDS		8
#define _SC_VERSION		9
#define _SC_STREAM_MAX		13
#define _SC_TZNAME_MAX		14
#define _SC_BC_BASE_MAX         15
#define _SC_BC_DIM_MAX          16
#define _SC_BC_SCALE_MAX        17
#define _SC_BC_STRING_MAX       18
#define _SC_COLL_WEIGHTS_MAX    20
#define _SC_EXPR_NEST_MAX       21
#define _SC_LINE_MAX            22
#define _SC_2_C_DEV             23
#define _SC_2_FORT_DEV          24
#define _SC_2_FORT_RUN          25
#define _SC_2_LOCALEDEF         26
#define _SC_2_SW_DEV            27
#define _SC_2_VERSION           28
#define _SC_RE_DUP_MAX          29
#define _SC_THREAD_MAX          34
#define _SC_TASK_MAX            35
#define _SC_MAXUTHREADS         36
#define _SC_STACK_SIZE          37
#define _SC_STACK_SIZE_MAX      38
#define _SC_DATA_SIZE           39
#define _SC_DATA_SIZE_MAX       40
#define _SC_ADDR_SPACE          41
#define _SC_ADDR_SPACE_MAX      42
#define _SC_2_UPE               47

#ifdef _XOPEN_SOURCE

#define _SC_XOPEN_CRYPT         48
#define _SC_XOPEN_ENH_I18N      49
#define _SC_XOPEN_SHM           50
#define _SC_XOPEN_XCU_VERSION   51
#define _SC_2_C_BIND            52
#endif

#define _SC_2_C_VERSION         53
#define _SC_2_CHAR_TERM         54

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#define _SC_XOPEN_UNIX          55
#define _SC_IOV_MAX 		56		/* required for spec1170 */
#endif

#endif /* _POSIX_C_SOURCE >= 1 */
#endif /* ifndef _KERNEL */
#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1) 

/* arguments for the pathconf() function */

#define _PC_CHOWN_RESTRICTED	10
#define _PC_LINK_MAX		11
#define _PC_MAX_CANON		12
#define _PC_MAX_INPUT		13
#define _PC_NAME_MAX		14
#define _PC_NO_TRUNC		15
#define _PC_PATH_MAX		16
#define _PC_PIPE_BUF		17
#define _PC_VDISABLE 		18
#if _POSIX_C_SOURCE >= 199309L
#define _PC_ASYNC_IO		19
#define _PC_SYNC_IO		20
#define _PC_PRIO_IO		-1
/*
 * Return values for _PC queries.
 */
#define _POSIX_ASYNC_IO		1
#define _POSIX_SYNC_IO		2
#endif

#endif /* _POSIX_C_SOURCE >= 1 */
#ifndef _KERNEL

#ifdef _XOPEN_SOURCE

#define _SC_PASS_MAX		7
#define _SC_XOPEN_VERSION	19

#define _XOPEN_VERSION		4
#define _XOPEN_XCU_VERSION	4
#define _XOPEN_XPG4		4

#define	_XOPEN_CRYPT		1
#define _XOPEN_ENH_I18N		1 /* Supports enhanced internationalization */
#define _XOPEN_SHM		1 /* Supports Shared Memory Feature Group */
#define _XOPEN_UNIX		1 /* Supports XSH4 extended feature group */

/*** AAB-XPG4 Illegal symbols ***/
#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#define F_ULOCK	0	/* Unlock a previously locked region */
#define F_LOCK	1	/* Lock a region for exclusive use */
#define F_TLOCK	2	/* Test and lock a region for exclusive use */
#define F_TEST	3	/* Test a region for other processes locks */
#endif /*_OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */
/*AAB-XPG4*/

#endif /* _XOPEN_SOURCE */

#if defined(_AES_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#define _SC_ATEXIT_MAX		10
#define _SC_PAGE_SIZE		11

#ifndef _SC_PAGESIZE
#define _SC_PAGESIZE		43  /* NOTE: keep synch with realtime, above */
#endif

#ifdef _AES_SOURCE
#define _SC_AES_OS_VERSION	12

#define _AES_OS_VERSION		1
#endif

extern int  fchown __((int, uid_t, gid_t));
extern int  ftruncate __((int, off_t));
#ifdef _XOPEN_SOURCE_EXTENDED
extern int  readlink __((const char *, char *, size_t));
extern int  fchdir __((int));
extern long gethostid __((void));
#else
extern int  readlink __((const char *, char *, int));
#endif
extern int  symlink __((const char *, const char *));
#ifdef _AES_SOURCE
extern int  setgroups __((int, gid_t []));
#endif
extern int  truncate __((const char *, off_t));

#endif 	/* _AES_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef _XOPEN_SOURCE

extern char *crypt __((const char *, const char *));
extern char *cuserid __((char *));
extern char *ctermid __((char *));
extern void encrypt __((char [], int));
extern char *getpass __((const char *));
extern int  nice __((int));

#define _SC_MAJ_NUM_SHIFT          53

#endif /* _XOPEN_SOURCE */

/*** AAB-XPG4 The protos below were removed from above since XPG4
 does not allow them to be visible. They were put here just in case
 they are needed for compilation. Should remove them if not needed ***/

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#ifdef _XOPEN_SOURCE_EXTENDED
extern int  brk __((void *));
extern int  gethostname __((char *, size_t));
#else
extern int  brk __((char *));
extern int  gethostname __((char *, int));
#endif
extern int  getpagesize __((void));
extern pid_t getpgid __((pid_t));
extern pid_t getsid __((pid_t));
extern char *getwd __((char *));
extern int lchown __((const char *, uid_t, gid_t));
extern int lockf __((int, int, off_t));
#ifdef _XOPEN_SOURCE_EXTENDED
extern void *sbrk __((int));
extern useconds_t ualarm __((useconds_t, useconds_t));
#else
extern void *sbrk __((ssize_t));
extern unsigned int ualarm __((unsigned int, unsigned int));
#endif
extern void sync __((void));
#if defined(_XOPEN_SOURCE_EXTENDED) || defined(__SVID__)

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define setpgrp() _Esetpgrp()
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern pid_t __R(setpgrp) __((void));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

#else
extern int setpgrp __((pid_t, pid_t));
#endif

extern int  setregid __((gid_t, gid_t));
extern int  setreuid __((uid_t, uid_t));
extern pid_t vfork __((void));
extern int  getdtablesize __((void));

#ifdef _OSF_SOURCE
extern char *gettxt __((const char *, const char *));
extern char *getenv __((const char *));
extern int rename __((const char *, const char *));
extern int rresvport __((int *));
extern int rresvport2 __((int *, int));
extern int  seteuid __((uid_t));
extern int  setegid __((gid_t));
extern int  setlogin __((char *));
extern int  setrgid __((gid_t));
extern int  setruid __((uid_t));
#endif

#endif /*_OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */
#endif /* ifndef _KERNEL */	
#ifdef __cplusplus
}
#endif
#endif /* _UNISTD_H_ */
