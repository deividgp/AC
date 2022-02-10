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
 * @(#)$RCSfile: semaphore.h,v $ $Revision: 1.1.11.2 $ (DEC) $Date: 1998/02/17 13:28:55 $
 */
/*
 * semaphore.h
 *
 *  This module defines fuctions, structures, and constants needed to
 *  support POSIX 1003.1b Counting Semaphores.
 */
#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H 1
#if defined(__cplusplus)
extern "C"
{
#endif

#include <standards.h>

#include <sys/limits.h>
#include <sys/psx4_nspace_ts.h>	/* Use new thread-safe namespace routines */

/*
 * Semaphore operation failure value.
 */
#define SEM_FAILED -1

/*
 * semaphore descriptor, sem_t is user visible representation of the semaphore
 */
typedef psx4_key_t sem_t;	/* semaphore descriptor is the key */
				/* it should equate to int */

/*
 * p4csemid structure holds the information about the semaphore which is
 * used in the actual synchronization.
 * it is the object for the namespace routines
 */
typedef struct p4csemid {
  int semval;			/* value of the semaphore */
  int semcnt;			/* # of blocked processes on this semaphore */
  char semname [SEM_NAME_MAX];	/* semaphore name, null-terminated */
}p4csemid_t;

/*
 * Process-wide semaphore descriptor table which is an instance of 
 * psx4_key_table_t is managed by the namespace routines (keytable code)
 * There is one semaphore descriptor table per process
 */
typedef psx4_key_table_t p4csemdes_table_t;

/*
 * semaphore descriptor entry 
 * when valid, contains key descriptor, pointer to semaphore name and
 * pointer to the object (mapped semaphore region)
 */
typedef psx4_key_entry_t p4csemdes_entry_t;

/*
 * Semaphore operation parameter to be used in the syscall
 */
#define _CSEM_SLEEP	1
#define _CSEM_WAKEUP	2
#define _CSEM_TIMING0	3
#define _CSEM_TIMING1	4
#define _CSEM_TIMING2	5
#define _CSEM_TIMING3	6


#if !defined(_KERNEL)

/*
 * POSIX 1003.1b Counting Semaphores functions
 */
int sem_init __((sem_t *sem, int pshared, unsigned int value));
int sem_destroy __((sem_t *sem));
sem_t *sem_open __((const char *name, int oflag, ...)); 
/* sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value); */
int sem_close __((sem_t *sem));
int sem_unlink __((const char *name));
int sem_wait __((sem_t *sem));
int sem_trywait __((sem_t *sem));
int sem_post __((sem_t *sem));
int sem_getvalue __((sem_t *sem, int *sval));

#endif /* !defined(_KERNEL) */

#if defined(__cplusplus)
}
#endif
#endif /* _SEMAPHORE_H */
