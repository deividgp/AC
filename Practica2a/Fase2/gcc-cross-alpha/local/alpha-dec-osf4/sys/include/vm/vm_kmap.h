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
 * @(#)$RCSfile: vm_kmap.h,v $ $Revision: 1.1.7.4 $ (DEC) $Date: 1994/03/02 04:37:16 $
 */
#ifndef	__VM_KMAP__
#define	__VM_KMAP__ 1
#include <kern/sched_prim.h>
#include <sys/unix_defs.h>
#include <sys/param.h>

/*
 * The kernel fault wait strategy is unlike that for the U maps and C maps.
 * It would be hazardous to hold a map write lock waiting for faults to
 * complete.  For that matter it could result in a deadlock.  Instead for
 * the kernel we let write lock synchronize themselves at the map level.
 * A write lock proceeds to operate until it encounters a map entry with
 * fault activity.  The operation releases the map write lock while holding
 * the map entry fault lock.  It indicates its desire to modify the map
 * entry by updating the entry's wait field.  Other writers who progress
 * to this map entry will do the same if their intent of crossing the
 * map entry is anything other than list traversal.  All operations are in a 
 * retry mode.  A finishing faulter checks to see if the wait bit is set.  It
 * does so with the entry fault lock taken.  If there are writers waiting
 * on the entry, then they are all awakened and race to acquire the write
 * lock once again.  All map entry routines are passed the entry with the
 * fault lock taken and the map write locked.  The handle should release the
 * map write lock as quickly as possibly to enable other map activity 
 * to proceed.
 *
 * All write map entry operation handles have a fault lock acquired for
 * them and the map is passed write locked.  This is true because the
 * entry faultlock couldn't have been acquired if there was any fault
 * activity.  The entry operation is assumed to release the map write
 * lock before engaging in any activity which could suspend the thread
 * executing the code.  When the operation completes the fault lock is
 * released by the upper level map operation routine.
 *
 * The vm_mape_faultwait() is called by a thread that has the address
 * map write locked.  Pagefaults always precede map modification
 * requests; such as protection, deletion and wiring.
 */
#define vm_mape_faultwait(VME,RETRY) {					\
	if ((VME)->vme_faults) {					\
		simple_lock(&(VME)->vme_faultlock);			\
		if ((VME)->vme_faults) {				\
			vm_map_unlock((VME)->vme_map);			\
			(VME)->vme_faultwait = 1;			\
			assert_wait((vm_offset_t) (VME), FALSE);	\
			simple_unlock(&(VME)->vme_faultlock);		\
			thread_block();					\
			RETRY;						\
		} else							\
			simple_unlock(&(VME)->vme_faultlock);		\
	}								\
}
#endif /* !__VM_KMAP__ */
