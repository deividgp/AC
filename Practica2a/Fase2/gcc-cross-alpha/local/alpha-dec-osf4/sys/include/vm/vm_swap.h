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
 * @(#)$RCSfile: vm_swap.h,v $ $Revision: 1.1.20.2 $ (DEC) $Date: 1995/06/30 11:51:12 $
 */
#ifndef	__VM_SWAP__
#define __VM_SWAP__
#include <sys/vp_swap.h>
#include <sys/unix_defs.h>
#include <kern/lock.h>
#include <vm/vm_map.h>
#include <kern/macro_help.h>

/*
 * swap arguments for swapon
 */

#define	MS_PREFER	0x0001

struct vm_swap {
	struct vm_swap		*vs_fl,		/* forward and */
				*vs_bl;		/* backward link */
	decl_simple_lock_data(,	vs_lock)	/* Lookup and allocation lock */
	int			vs_oshift;	/* Object shift */
	int			vs_swapsize;	/* Space size */
	int			vs_freespace;	/* Free space */
	int			vs_flags;       /* Flags */
	struct vps_info		vs_vinfo;	/* from VOP_SWAP open */
	struct vm_swap_object	*vs_object;	/* swap object */
	char			*vs_path;	/* pathname of swap file */
	unsigned long		*vs_bitmap;	/* swap allocation bitmap */
	unsigned long		*vs_free;	/* free hint in bitmap */
};
typedef	struct vm_swap	*vm_swap_t;
#define	VM_SWAP_NULL	((vm_swap_t)0)

#define	vs_vp		vs_vinfo.vps_vp
#define	vs_rvp		vs_vinfo.vps_rvp
#define	vs_dev		vs_vinfo.vps_dev
#define	vs_shift	vs_vinfo.vps_shift

struct vm_swap_object {
	struct vm_object sw_object;		/* Object common part */
	struct vm_swap 	*sw_sp;			/* Pointer to vm_swap */
};
typedef	struct vm_swap_object	*vm_swap_object_t;

/*
 * Swap flags
 */

#define	VS_ENABLED	0x01			/* Swapping enabled */


#ifdef	KERNEL

extern int		vm_swap_eager;		/* Eager swap allocation */
extern int		vm_swap_written;	/* Total pages out */
extern vm_size_t	vm_swap_space;		/* Space available in */
extern vm_size_t	vm_total_swap_space;
extern int 	 	vm_swap_lock_wait_time;
extern vm_swap_t	vm_swap_circular;	/* Next swap device to use */
extern struct vm_swap_object
			vm_swap_lazy_object;

decl_simple_lock_data(extern, vm_swap_space_lock)
decl_simple_lock_data(extern, vm_swap_circular_lock)

#define	swap_space_free(SZ) {					\
	simple_lock(&vm_swap_space_lock);			\
	vm_swap_space += (SZ);					\
	simple_unlock(&vm_swap_space_lock);			\
}

#define	swap_space_alloc(SZ, RET) {		\
	simple_lock(&vm_swap_space_lock);	\
	if (RET = ((SZ) <= vm_swap_space))	\
		vm_swap_space -= (SZ); 		\
	simple_unlock(&vm_swap_space_lock);	\
}

struct vm_swap_list {
	decl_simple_lock_data(, vsl_lock)
	int			vsl_flags;
	int			vsl_rcount;
	struct vm_swap		*vsl_head;
};

extern	struct vm_swap_list	vm_swap_list;

#define	VSL_WRITE	1
#define	VSL_WANTWRITE	2

#define	swap_read_lock()	{			\
	simple_lock(&vm_swap_list.vsl_lock);		\
	while (vm_swap_list.vsl_flags) {		\
		register int i;				\
		simple_unlock(&vm_swap_list.vsl_lock);	\
		for (i = vm_swap_lock_wait_time;	\
		     i && vm_swap_list.vsl_flags;	\
		     i--);				\
		simple_lock(&vm_swap_list.vsl_lock);	\
	}						\
	vm_swap_list.vsl_rcount++;	 		\
	simple_unlock(&vm_swap_list.vsl_lock);		\
}

#define	swap_write_lock()	{					\
	simple_lock(&vm_swap_list.vsl_lock);				\
	while (vm_swap_list.vsl_rcount || vm_swap_list.vsl_flags) {	\
		vm_swap_list.vsl_flags |= VSL_WANTWRITE;		\
		assert_wait_mesg((vm_offset_t)&vm_swap_list,		\
				 FALSE, "swaplock");			\
		simple_unlock(&vm_swap_list.vsl_lock);			\
		thread_block();						\
		simple_lock(&vm_swap_list.vsl_lock);			\
	}								\
	vm_swap_list.vsl_flags = VSL_WRITE;				\
	simple_unlock(&vm_swap_list.vsl_lock);				\
}

#define	swap_read_unlock()	{				\
	simple_lock(&vm_swap_list.vsl_lock);			\
	vm_swap_list.vsl_rcount--;	 			\
	if (vm_swap_list.vsl_rcount == 0 &&			\
	    vm_swap_list.vsl_flags & VSL_WANTWRITE) {		\
		vm_swap_list.vsl_flags = 0;			\
		simple_unlock(&vm_swap_list.vsl_lock);		\
		thread_wakeup((vm_offset_t)&vm_swap_list);	\
	} else							\
		simple_unlock(&vm_swap_list.vsl_lock);		\
}

#define	swap_write_unlock()	{				\
	simple_lock(&vm_swap_list.vsl_lock);			\
	if (vm_swap_list.vsl_flags & VSL_WANTWRITE)		\
		thread_wakeup((vm_offset_t)&vm_swap_list);	\
	vm_swap_list.vsl_flags = 0;				\
	simple_unlock(&vm_swap_list.vsl_lock);			\
}

#define swap_vslock(VS)		simple_lock(&((VS)->vs_lock))
#define	swap_vsunlock(VS) 	simple_unlock(&((VS)->vs_lock))

/*
 * Insert page into object/offset hash table.
 */
#define	vm_page_insert_hash(PP, OBJ, OFFSET) \
	vm_page_insert_bucket(PP, OBJ, OFFSET)

/*
 * Remove page from object/offset hash table.  Since the page object/offset
 * pair is not what we hash on, replace them here.  This is okay as this
 * macro is called just before a page is freed.
 */
#define	vm_page_remove_hash(PP, OBJ, OFF) {	\
	(PP)->pg_object = (vm_object_t)OBJ;	\
	(PP)->pg_offset = OFF;			\
	vm_page_remove_bucket(PP);		\
}

extern struct vm_page	*vm_page_lookup_hash(struct vm_swap_object *,
				vm_offset_t);
extern boolean_t	swap_lazy_alloc(struct vm_anon *, struct vm_page *,
				struct vm_swap *, boolean_t);
extern struct vm_swap	*swap_alloc(boolean_t, boolean_t, struct vm_swap *,
				struct vm_anon *);
extern void		swap_free(struct vm_anon *, boolean_t);

#endif	/* KERNEL */
#endif	/* !__VM_SWAP__ */
