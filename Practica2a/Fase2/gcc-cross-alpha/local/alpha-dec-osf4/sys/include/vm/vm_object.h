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
 *	@(#)$RCSfile: vm_object.h,v $ $Revision: 4.2.58.2 $ (DEC) $Date: 1998/10/15 20:12:42 $
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
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *	File:	vm_object.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Virtual memory object module definitions.
 *
 */
#ifndef	_VM_VM_OBJECT_H_
#define	_VM_VM_OBJECT_H_
#include <sys/param.h>
#include <sys/types.h>
#include <sys/unix_defs.h>
#include <vm/pmap.h>
#include <mach/kern_return.h>
#include <mach/boolean.h>
#include <mach/memory_object.h>
#include <mach/machine/vm_types.h>
#include <kern/lock.h>

/*
 *	The common part of all VM objects
 *
 */
struct vm_object {
	struct vm_page		*ob_memq;	/* Resident memory */
	decl_simple_lock_data	(,ob_lock)	/* lock to protect common */
	struct vm_object_ops	*ob_ops;	/* Object Operations */
	struct vm_object	*ob_aux_obj;	/* Auxiliary object */
	int			ob_ref_count;	/* Number of references */
	int 			ob_res_count;	/* Object resident count */
	vm_size_t		ob_size;	/* Size of object */
	int 			ob_resident_pages;/* Page in ob_memq list */
	ushort			ob_flags;	/* Flags */
	ushort			ob_type;	/* Object type */
};

typedef struct vm_object	*vm_object_t;
#define VM_OBJECT_NULL		((vm_object_t) 0)

/*
 * Granularity Hints
 */

#define GH_UNALLOCATED 0
#define GH_ALLOCATED 1
#define GH_ALLOCATION_IN_PROGRESS 2
#define GH_FAILED 3
#define GH_RW	0
#define GH_R	1

/* mapping state */


struct vm_granhint {
	decl_simple_lock_data(, mapping_lock)
	vm_offset_t phys_buffs;
	pt_entry_t *ptes[2];
	u_long size;
	u_long phys_mem_state;
	u_long mapping_l3_shared;
	u_long mapping_waiters;
	long waiters;
	u_long att_warning;
};
struct vm_granhint_stats {
	u_long total_mappers;
	u_long shared_mappers;
	u_long unshared_mappers;
	u_long total_unmappers;
	u_long shared_unmappers;
	u_long unshared_unmappers;
	u_long unaligned_mappers;
	u_long access_violations;
	u_long unaligned_size_requests;
	u_long unaligned_attachers;
	u_long wired_bypass;
	u_long wired_returns;
};

decl_simple_lock_data(extern, gh_stats_lock )

#define INC_GH_STATS(FLD)                \
          simple_lock(&gh_stats_lock);     \
          gh_stats->/**/FLD/**/++;         \
          simple_unlock(&gh_stats_lock);



#define GH_SEG_SIZE 0x800000
#define LARGE_PAGE_SIZE 0x400000
#define MED_PAGE_SIZE 0x80000
#define SMALL_PAGE_SIZE 0x10000
#define GH_ALIGNED_8MEG(a) (a == (a  & ~(GH_SEG_SIZE - 1)))
#define GH_ALIGNED_4MEG(a) (a == (a  & ~(LARGE_PAGE_SIZE - 1)))


/*
 * Flags field of object
 */

#define	OB_SWAPON	    0x0001	/* Object swapping enabled */
#define	OB_SWAP		    0x0002	/* Object is being swapped */
#define	OB_SWAPWAIT	    0x0004	/* Waiting for swap to complete */
#define	OB_CHANGE	    0x0008	/* Object change taking place */
#define	OB_CHANGEWAIT	    0x0010	/* Waiting for change to complete */
#define	OB_SEMWAIT	    0x0020	/* Semaphore wait */
#define	OB_SEGALLOC	    0x0040	/* A segment is being allocated */
#define	OB_SEGWAIT	    0x0080	/* Waiting for seg alloc to complete */
#define OB_DO_NOT_COALESCE  0x0100      /* Don't coalesce this object */
#define	OB_UBCWAIT	    0x0200	/* Waiting write completion in UBC */
#define OB_RM_EXISTING	    0x0400	/* RM existing object */
#define OB_GRAN_HINT 	    0x0800	/* Granularity hint object */
					/* unused bits */
#define OB_IOERROR	    0x1000	/* If an I/O error occured
					 * during async flush. */
#define	OB_FUNNEL	    0x8000	/* operations are funneled */

/*
 * Object address plus this offset for wakeup address
 */

#define	OB_WSWAP	0x0
#define	OB_WCHANGE	0x1
#define	OB_WSEM		0x2

#define	vm_object_wait(OBJ,WHY) {					\
	while (((vm_object_t)(OBJ))->ob_flags & OB_/**/WHY) {		\
		assert_wait_mesg(vm_object_sleep_addr(OBJ,WHY),		\
				 FALSE, "objwait");			\
		((vm_object_t)(OBJ))->ob_flags |= OB_/**/WHY/**/WAIT;	\
		vm_object_unlock((vm_object_t)(OBJ));			\
		thread_block();						\
		vm_object_lock((vm_object_t)(OBJ));			\
	}								\
}

#define	vm_object_assert_wait(OBJ,WHY,INTERRUPT) {			\
	assert_wait_mesg(vm_object_sleep_addr(OBJ,WHY), INTERRUPT, "objwait");\
	((vm_object_t)(OBJ))->ob_flags |= OB_/**/WHY/**/WAIT;		\
}

#define	vm_object_sleep_addr(OBJ,WHY)					\
	((vm_offset_t)(OBJ) + OB_W/**/WHY)

#define	vm_object_wakeup(OBJ,WHY)					\
	if (((vm_object_t)(OBJ))->ob_flags & OB_/**/WHY/**/WAIT) {	\
		thread_wakeup(vm_object_sleep_addr(OBJ, WHY));		\
		((vm_object_t) (OBJ))->ob_flags ^= OB_/**/WHY/**/WAIT;	\
	}

/*
 * Object control operations used for control functions.
 */

typedef enum {
	VMOC_NOOP, 			/* No operation */
	VMOC_MSYNC,			/* Sync memory cache with backstore */
	VMOC_PAGELOCK,			/* Lock the page */
	VMOC_PAGEUNLOCK,		/* Unlock the page */
	VMOC_FREE			/* Free the pages */
	} vm_ocontrol_t;

/*
 * Object page control operations
 */

#define	VMOP_RELEASE	0x01		/* Release a hold on the page */
#define	VMOP_LOCK	0x02		/* Lock the page */
#define	VMOP_UNLOCK	0x04		/* Unlock the page */

/*
 * Object operations called by map map entry fault handles when there
 * is a backing object.  Without a backing object, the handle should 
 * know how to call the call the object management functions explictly.
 * To avoid polluting the kernel with numerous common operations handles
 * when object(s) don't require a handle or any special action, the vm_object.c
 * module exports routines with the naming convention:
 *
 *	vm_ops_##name##def
 */

struct vm_object_ops {
	boolean_t	(*ops_lock_try)(vm_object_t, struct vm_page *);
	void		(*ops_unlock)(vm_object_t, struct vm_page *);
	void		(*ops_reference)(vm_object_t);
	void		(*ops_deallocate)(vm_object_t);
	int		(*ops_pagein)(vm_object_t, vm_offset_t, vm_size_t,
				struct vm_map_entry *, vm_offset_t,
				struct vm_page **, int, vm_prot_t *);
	int		(*ops_pageout)(vm_object_t, struct vm_page *,
				vm_size_t);
	int		(*ops_swap)(vm_object_t, int *);
	int 		(*ops_control)(vm_object_t, vm_offset_t, int,
				vm_ocontrol_t, int);
	int		(*ops_pagectl)(vm_object_t, struct vm_page **,
				int, int);
	kern_return_t	(*ops_pagesteal)(vm_object_t, struct vm_page *);
	int		(*ops_pagewrite)(vm_object_t, struct vm_page *);
};

/*
 * Type casts to make compiler happy for place holder functions.
 */
#define	CAST_LOCK_TRY	(boolean_t (*)())
#define	CAST_UNLOCK	(void (*)())
#define	CAST_REFERENCE	(void (*)())
#define	CAST_DEALLOCATE	(void (*)())
#define CAST_PAGEIN	(int (*)())
#define	CAST_PAGEOUT	(int (*)())
#define	CAST_SWAP	(int (*)())
#define	CAST_CONTROL	(int (*)())
#define	CAST_PAGECTL	(int (*)())
#define CAST_PAGESTEAL	(int (*)())
#define CAST_PAGEWRITE	(int (*)())

#define OOP_PAGEWRITE(OBJ, PP)						\
         (*((vm_object_t)(OBJ))->ob_ops->ops_pagewrite)(OBJ, PP)

#define	OOP_LOCK_TRY(OBJ, PP)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_lock_try)(OBJ, PP)

#define OOP_UNLOCK(OBJ, PP)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_unlock)(OBJ, PP)

#define	OOP_REFERENCE(OBJ)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_reference)(OBJ)

#define OOP_DEALLOCATE(OBJ)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_deallocate)(OBJ)

#define	OOP_PAGEIN(OBJ, OFFSET, SIZE, VME, ADDR, PGLIST, PSIZE, PROT)	\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pagein)			\
	(OBJ, OFFSET, SIZE, VME, ADDR, PGLIST, PSIZE, PROT)

#define OOP_PAGEOUT(OBJ, PP, SIZE)					\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pageout)(OBJ, PP, SIZE)

#define	OOP_SWAP(OBJ,PAGES)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_swap)(OBJ, PAGES)

#define	OOP_CONTROL(OBJ, OFFSET, SIZE, CONTROL, FLAG)			\
	(*((vm_object_t)(OBJ))->ob_ops->ops_control)			\
		(OBJ, OFFSET, SIZE, CONTROL, FLAG)
	
#define OOP_PAGECTL(OBJ, PLIST, PLS, FLAGS)				\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pagectl)			\
		(OBJ, PLIST, PLS, FLAGS)

#define OOP_PAGESTEAL(OBJ, PP)						\
	(*((vm_object_t)(OBJ))->ob_ops->ops_pagesteal)(OBJ, PP)	

#define OOP_PAGEWRITE(OBJ, PP)						\
        (*((vm_object_t)(OBJ))->ob_ops->ops_pagewrite)(OBJ, PP)

/*
 * A small amount of informationn is exported to the module
 * vm_object.c by each object type.  The is done thru an
 * object configuration structure.
 */

struct vm_object_config {
						/* 
						 * object private allocation 
						 * this is optional
						 */
	kern_return_t		(*oc_allocate)(vm_object_t, caddr_t);
						/* object termination 
						 * this is optional
						 * ob_ref_count == 1
						 * the termination handle
						 * does the actual free of
						 * the object structure.
						 */
	void			(*oc_terminate)(vm_object_t);
	vm_size_t		oc_osize;	/* Size of object struct */
	struct vm_object_ops	*oc_ops;	/* pointer to op handles */
	struct vm_map_entry_ops	*oc_mape;	/* map entry operations */
};


/*
 * Object types
 */
#define	OT_NULL		0x00	/* No actions supported */
#define	OT_UBC		0x01	/* File sytem shared vnode */
#define	OT_ANON		0x02	/* Anonymous memory */
#define	OT_SWAP		0x03	/* Swap object */
#define	OT_DEVMAP	0x04	/* Memory mapped device */
#define	OT_KERNEL	0x05	/* Non-paged kernel */
#define	OT_PKERNEL	0x06	/* Pageable kernel */
#define	OT_SHM		0x07	/* System V shared memory */
#define	OT_SEG		0x08	/* Segment address space */
#define	OT_RM_K_RCV	0x09	/* Reflective memory, kernel receive */
#define	OT_RM_K_TRANS	0x0a	/* Reflective memory, kernel transmit */
#define	OT_RM_U_RCV	0x0b	/* Reflective memory, user receive */
#define	OT_RM_U_TRANS	0x0c	/* Reflective memory, user transmit */
#define	OT_RM_U_DUAL	0x0d	/* Reflective memory, user dual window */
#define	OT_RM_K_DUAL	0x0e	/* Reflective memory, kernel dual window */
#define	OT_SSM		0x0f	/* System V shared memory, segmented */
#define	OT_LAST		0x10	/* Maximum */

#define	vm_object_type(OBJ)	(OBJ)->ob_type
#define ismmaper(entry)							\
	(vm_object_type(entry->vme_object) == OT_UBC)                 

#ifdef	KERNEL

/*
 *	Object locking macros for object
 *	common part (with and without debugging).
 */
#define vm_object_lock_init(OBJECT)					\
	simple_lock_setup(&((vm_object_t)(OBJECT))->ob_lock, vm_object_lockinfo)
#define vm_object_lock(OBJECT)						\
	simple_lock(&((vm_object_t)(OBJECT))->ob_lock)
#define vm_object_unlock(OBJECT)					\
	simple_unlock(&((vm_object_t)(OBJECT))->ob_lock)
#define vm_object_lock_try(OBJECT)					\
	simple_lock_try(&((vm_object_t)(OBJECT))->ob_lock)

extern kern_return_t	vm_object_allocate(int, vm_size_t,
					   caddr_t, vm_object_t *);
extern void		vm_ops_reference_def(vm_object_t);
extern void		vm_ops_deallocate_def(vm_object_t);
extern int		vm_ops_pagein_def();
extern int		vm_ops_swap_def(vm_object_t, int *);
extern int		vm_ops_pageout_def(vm_object_t, vm_offset_t, vm_size_t);
extern void		vm_object_free(vm_object_t);

/*
 * Old functions now implemented as macros
 */

#define vm_object_reference(OBJ) 	OOP_REFERENCE(OBJ)
#define vm_object_deallocate(OBJ)	OOP_DEALLOCATE(OBJ)
#define vm_object_swapon(OBJ) 					\
	((vm_object_t)(OBJ))->ob_flags |= OB_SWAPON

extern struct vm_object_config *vm_object_config[];
#define vm_object_to_vmeops(OBJ)				\
	vm_object_config[((vm_object_t)(OBJ))->ob_type]->oc_mape
	
extern vm_object_t	nkernel_object, pkernel_object, kernel_object;
extern struct lockinfo	*vm_object_lockinfo;

#endif	/* KERNEL */

#endif /* !_VM_VM_OBJECT_H_ */
