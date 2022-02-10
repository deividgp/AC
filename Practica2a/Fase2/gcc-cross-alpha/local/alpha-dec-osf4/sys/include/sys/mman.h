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
 *	@(#)$RCSfile: mman.h,v $ $Revision: 4.2.31.2 $ (DEC) $Date: 1998/03/31 21:15:49 $
 */ 
/*
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
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */

#ifndef	_SYS_MMAN_H_
#define _SYS_MMAN_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/* protections are chosen from these bits, or-ed together */
#define PROT_NONE	0		/* no access to these pages */
#define PROT_READ	0x1		/* pages can be read */
#define PROT_WRITE	0x2		/* pages can be written */
#define PROT_EXEC	0x4		/* pages can be executed */

/* flags contain sharing type, mapping type, and options */

/* mapping visibility: choose either SHARED or PRIVATE */
#define MAP_SHARED	0x1		/* share changes */
#define MAP_PRIVATE	0x2		/* changes are private */

/* mapping region: choose either FILE or ANONYMOUS */
#define	MAP_FILE	0x00		/* map from a file */
#define	MAP_ANONYMOUS	0x10		/* man an unnamed region */
#define	MAP_ANON	0x10		/* man an unnamed region */
#define	MAP_TYPE	0xf0		/* the type of the region */


/* mapping placement: choose either FIXED or VARIABLE */
#define	MAP_VARIABLE	0x0000		/* system can place new region */
#define	MAP_FIXED	0x0100		/* addr must be exactly as specified */

/* other flags */

#define	MAP_HASSEMAPHORE 0x0200		/* region may contain semaphores */
#define	MAP_INHERIT	 0x0400		/* region is retained after exec */
#define MAP_UNALIGNED	 0x0800		/* allow non-page-aligned file offset */

#ifdef _OSF_SOURCE  /* Protect from Spec1170 name space */

/* other flags (cont'd) */
#define MAP_TEXT	 0x1000		/* maps text */
#define	MAP_MBUF	 0x2000		/* use mbuf cache for this region */

/* advice to madvise */
#define MADV_NORMAL	0		/* no further special treatment */
#define MADV_RANDOM	1		/* expect random page references */
#define MADV_SEQUENTIAL	2		/* expect sequential page references */
#define MADV_WILLNEED	3		/* will need these pages */
#define MADV_DONTNEED_COMPAT	4	/* for backward compatibility */
#define	MADV_SPACEAVAIL	5		/* ensure resources are available */
#define MADV_DONTNEED	6		/* dont need these pages */

/* functions to memctl */
#define	MC_SYNC		1		/* sync with backing store */
#define	MC_LOCK		2		/* lock pages in memory */
#define	MC_UNLOCK	3		/* unlock pages from memory */
#define	MC_LOCKAS	4		/* lock address space in memory */
#define	MC_UNLOCKAS	5		/* unlock address space from memory */

/* additional attr flags used by memcntl */
#define SHARED		0x10
#define PRIVATE		0x20
#define PROC_TEXT	(PROT_EXEC|PROT_READ)
#define PROC_DATA	(PROT_WRITE|PROT_READ)

/* msem conditions and structure */
typedef struct {
	int msem_state;		/* The semaphore is locked is non-zero. */
	int msem_wanted;	/* Threads are waiting on the semaphore. */
}msemaphore;

#define MSEM_UNLOCKED 	0	/* Initialize the semahore to unlocked */
#define MSEM_LOCKED 	1	/* Initialize the semahore to locked */
#define MSEM_IF_NOWAIT	2	/* Do not wait if semaphore is locked */
#define MSEM_IF_WAITERS	3	/* Unlock only if there are waiters */

#endif /* _OSF_SOURCE */

/* msync flags */
#define MS_ASYNC	1	/* Asynchronous cache flush */
#define MS_SYNC		2	/* Synchronous cache flush */
#define MS_INVALIDATE	4	/* Invalidate cached pages */

#if ( defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) ) || defined(_XOPEN_SOURCE_EXTENDED) 

extern void *mmap __((void *, size_t, int, int, int, off_t));
extern int munmap __((void *, size_t));
#ifdef _XOPEN_SOURCE_EXTENDED
extern int mprotect __((void *, size_t, int));
#else
extern int mprotect __((const void *, size_t, int));
#endif
extern int msync __((void *, size_t, int));

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) 
extern int shm_open __((const char *, int, mode_t));
extern int shm_unlink __((const char *));
#endif /* _POSIX_C_SOURCE */

#else /* not (_POSIX_C_SOURCE || _XOPEN_SOURCE_EXTENDED) */

extern caddr_t	mmap __((caddr_t addr, size_t len, int prot, int flags, int filedes, off_t off));
extern int	munmap __((caddr_t addr, size_t len));
extern int	mprotect __((caddr_t addr, size_t len, int prot));
extern int	msync __((caddr_t addr, size_t len, int flags));

#endif /* _POSIX_C_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef _OSF_SOURCE
extern int	madvise __((caddr_t addr, size_t len, int behav));
extern msemaphore   *msem_init __((msemaphore *sem, int initial_value));
extern int	msem_lock __((msemaphore *sem, int condition));
extern int	msem_remove __((msemaphore *sem));
extern int	msem_unlock __((msemaphore *sem, int condition));
extern int	mvalid __((caddr_t addr, size_t len, int prot));
#endif

#ifdef _OSF_SOURCE
#define MCL_CURRENT	 8192	/* Lock all currently mapped paged */
#define MCL_FUTURE	16384	/* Lock all additions to address space */
#endif

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L) 

#define REGLOCK		   16	/* Lock region */
#define MAP_FAILED	(-1L)	/* unsuccessful return from mmap() */

extern int	memlk __((int, void *, size_t));
extern int	memunlk __((int, void *, size_t));
extern int	mlockall __((int));
extern int	munlockall __((void));
extern int      mlock __((const void *, size_t));
extern int      munlock __((const void *, size_t));

/*
 * POSIX and SVID differ on how mlockall() handles a flags field if
 * neither MCL_CURRENT nor MCL_FUTURE are set. The following macro follows
 * the SVID behavior by setting the TYPE field in the memlk() to NULL (EINVAL).
 * If POSIX is accepted, TYPE should be set to NOP.
*/
#define mlockall(flags) memlk((flags)&(MCL_CURRENT|MCL_FUTURE), NULL, NULL)
#define munlockall() 	memunlk((MCL_CURRENT|MCL_FUTURE), NULL, NULL)
#define mlock(addr, size) 	memlk(REGLOCK, (addr), (size))
#define munlock(addr, size) 	memunlk(REGLOCK, (addr), (size))

#endif /* _POSIX_C_SOURCE */

#ifdef __cplusplus
}
#endif
#endif	/* _SYS_MMAN_H_ */
