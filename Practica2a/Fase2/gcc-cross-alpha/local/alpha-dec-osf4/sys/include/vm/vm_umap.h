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
 * @(#)$RCSfile: vm_umap.h,v $ $Revision: 1.1.16.2 $ (DEC) $Date: 1997/06/17 21:44:44 $
 */
#ifndef	__VM_UMAP__
#define	__VM_UMAP__ 1
#include <kern/lock.h>
#include <sys/unix_defs.h>
#include <vm/vm_vlock.h>
#include <sys/param.h>

/*
 * user mode private map structure
 * The following members can change after creation, and are protected
 * by the map lock:
 * 
 * 	um_actual_size
 * 	um_vpage
 * 	um_lock_future
 * 	um_unload_all
 * 	um_vlock
 */

struct u_map_private {
	vm_size_t		um_maxvas;	/* Maximum VAS allowed */
	vm_size_t		um_maxwired;	/* Max wired space allowed */
	vm_size_t		um_wired;	/* Pages wired */
						/* 
						 * For a working set model.
						 * Any other policy leads
						 * to complication when
						 * maintaining these fields.
						 */
	vm_size_t		um_maxrss;	/* Maximum rss allowed */
	vm_size_t		um_rss;		/* Resident pages in map */
	vm_size_t		um_actual_size;	/* actual size */
	int			um_vpage;	/* vpages allocated */
	unsigned int		
						/* lock all future pages */
				um_lock_future:1,
						/* unloading all address sp */
				um_unload_all:1,
				:30;
	struct vm_vlock		*um_vlock;	/* Virtual space lock by K */
};

#define	vm_mape_lockaddr(VME) simple_lock_addr((VME)->vme_faultlock)

/*
 * The vm_mape_faultwait is called by a thread that has the address map
 * read or write locked.  The thread goes to sleep on the fault lock until
 * vme_faults count goes to zero.
 */
#define vm_mape_faultwait(VME) {					\
	if ((VME)->vme_faults) {					\
		simple_lock(&(VME)->vme_faultlock);			\
		if ((VME)->vme_faults) {				\
			do {						\
				(VME)->vme_faultwait = 1;		\
				assert_wait_mesg((vm_offset_t)(VME),	\
						  FALSE, "fault");	\
				simple_unlock(&(VME)->vme_faultlock);	\
				thread_block();				\
				simple_lock(&(VME)->vme_faultlock);	\
			} while ((VME)->vme_faults);			\
		}							\
		simple_unlock(&(VME)->vme_faultlock);			\
	}								\
}

/*
 * Described return states from u_map_is_wired, see function for definitions.
 */
typedef enum { UMAP_NOCHG, UMAP_KWIRED, UMAP_UWIRED, UMAP_NOWIRED } u_mapwire_t;

#ifdef	KERNEL
extern boolean_t u_map_entry_delete_check(vm_map_t map, vm_map_entry_t ep, 
			vm_offset_t start, vm_offset_t end);
extern boolean_t u_map_entry_clip_check(vm_map_t map, vm_map_entry_t ep,
			vm_offset_t start, vm_offset_t end);
u_mapwire_t u_map_is_wired(vm_map_entry_t, vm_offset_t, vm_offset_t, vm_prot_t);
#endif	/* KERNEL */

#endif /* !__VM_UMAP__ */
