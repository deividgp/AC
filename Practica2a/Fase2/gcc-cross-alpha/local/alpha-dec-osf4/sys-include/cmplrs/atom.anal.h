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
 * @(#)$RCSfile: atom.anal.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1998/04/24 18:59:27 $
 */

/*
**  atom.anal.h - 	External interface definition for Atom analysis
**
**	This file defines the external interfaces for Atom.  These
**	interfaces are used by an Atom tool's analysis code.  See
**	<cmplrs/atom.inst.h> for definitions of the instrument-time interfaces.
**	Atom is a general purpose framework for creating sophisticated
**	program analysis tools.
*/

#ifndef _ATOM_ANAL_H_
#define _ATOM_ANAL_H_

/*
 * Formal parameter types for analysis routines.
 */
typedef long    		REGV;
typedef long    		FREGV;
typedef struct XLATE_s		XLATE;
typedef struct thdtab_s 	ThreadTable;
typedef unsigned long 		ThreadId;
typedef ThreadId		ThreadMutex;

/*
 * Routines to translate addresses between instrumented and
 * uninstrumented code.
 */
extern unsigned long	XlateInstTextStart(XLATE *);
extern unsigned long	XlateInstTextSize(XLATE *);
extern long         	XlateLoadShift(XLATE *);
extern unsigned long	XlateAddr(XLATE *, unsigned);
extern unsigned     	XlateNum(XLATE *);

/*
 * Routine to get the base of the analysis heap.
 */
extern unsigned long	AnalHeapBase(void);

/*
 * Value returned by ThreadId() and used by other Thread routines
 * to indicate an undefined or invalid thread id.
 */
#define ThreadNoId 0

/*
 * The error codes returned by the Thread routines.
 */
typedef enum {
	THREAD_SUCCESS = 0,	/* Successful completion of operation */
	THREAD_NO_DATA, 	/* No data found in table to delete */
	THREAD_FOREACH, 	/* Iteration was stopped by callback */
	THREAD_NO_ID, 		/* Specified thread id was ThreadNoId */
	THREAD_LOCKED,		/* Mutex already locked by specified thread */
	THREAD_INTERNAL		/* Thread is internal to DECthreads */
    } ThreadStatus;

/*
 * Routines to find the unique sequence number of the current pthread
 * (for use as the thread id in the other Thread routines) and to
 * indicate whether the thread is internal to DECthreads.
 */
extern ThreadId ThreadGetId(void);
extern int ThreadIsInternal(ThreadId);

/*
 * Routines to allocate, lookup, iterate over, and free per-thread data.
 */
typedef enum {THREAD_LOCK = 1, THREAD_EXISTING=2} ThreadFlags;
extern ThreadTable *ThreadTableInit(unsigned long, unsigned long);
extern ThreadStatus ThreadTableLock(ThreadTable *,ThreadId);
extern void ThreadTableUnlock(ThreadTable *,ThreadId);
extern void ThreadTableFree(ThreadTable *);
extern void *ThreadLookup(ThreadTable *,ThreadId,unsigned long);
extern void ThreadUnlock(ThreadTable *,ThreadId);
extern ThreadStatus ThreadRemove(ThreadTable *,ThreadId);
extern ThreadStatus ThreadForeach(ThreadTable *,
				  ThreadId,
				  unsigned long,
				  void *,
				  void *,
				  void (*)(ThreadId,void *,void *,void *));

/*
 * Debugging routines to get the address of the mutex for a given thread.
 */
extern ThreadMutex *ThreadAddr(ThreadTable *,ThreadId);

/*
 * Routines to claim and release a mutex suitable for use by analysis routines
 * in serializing access to shared data, and to select the length of time
 * a thread sleeps between each attempt to claim a mutex.
 */
extern ThreadStatus ThreadMutexLock(ThreadMutex *,ThreadId);
extern void ThreadMutexUnlock(ThreadMutex *);
extern void ThreadMutexPoll(int);

/*
 * Routine to increment a counter in a thread-safe manner.
 */
extern unsigned long ThreadLockedAdd(unsigned long *, unsigned long);


#endif /* _ATOM_ANAL_H_ */
