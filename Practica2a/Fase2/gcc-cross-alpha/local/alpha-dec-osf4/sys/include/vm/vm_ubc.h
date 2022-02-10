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
 * @(#)$RCSfile: vm_ubc.h,v $ $Revision: 1.1.19.2 $ (DEC) $Date: 1998/03/31 21:16:25 $
 */

#ifndef	_VM_VM_UBC_H_
#define	_VM_VM_UBC_H_

#include <vm/vm_object.h>

/*
 * File system private data.
 */
union vfs_private {
	struct vnode    *vp;	/* backing vnode */
};
typedef union vfs_private *vfs_private_t;

/*
 * This object describes ubc pages.
 */
struct vm_ubc_object {
	struct vm_object	vu_object;	/* Object common part */
	struct vfs_ubcops	*vu_ops;	/* VFS operations */
	union vfs_private	vu_vfp;		/* VFS private pointer */
	struct vm_page		*vu_cleanpl;	/* Clean page list */
	struct vm_page		*vu_cleanwpl;	/* Clean wired page list */
	struct vm_page		*vu_dirtywpl;	/* Dirty wired page list */
	int			vu_wirecnt;	/* Wired pages */
	int			vu_nsequential;	/* Number of contig lastpage */
	vm_offset_t		vu_loffset;	/* Last offset allocated */
	unsigned int		vu_stamp;	/* Allocation stamp */
	unsigned int		vu_txtref;	/* text references */
	decl_simple_lock_data(, vu_seglock)	/* Segment list lock */
	struct vm_seg		*vu_seglist;	/* Segment list */
};

typedef struct vm_ubc_object	*vm_ubc_object_t;

#define	VM_UBC_OBJECT_NULL	(vm_ubc_object_t)0
#define	vu_dirtypl		vu_object.ob_memq
#define vu_orefcnt		vu_object.ob_ref_count
#define vu_npages		vu_object.ob_resident_pages
#define vu_noutput		vu_object.ob_res_count
#define vu_flags		vu_object.ob_flags
#define vu_vp			vu_vfp.vp

/*
 * Forward declarations of data structures for prototypes
 */
struct	vm_map_entry;
struct	ucred;

/* UBC to VFS callbacks */
struct vfs_ubcops {
	int	(*vfs_refer)(vm_ubc_object_t);
	int	(*vfs_release)(vm_ubc_object_t);
	int	(*vfs_getpage)(vm_ubc_object_t, vm_offset_t, vm_size_t,
			       vm_prot_t *, struct vm_page **, int,
			       struct vm_map_entry *, vm_offset_t, int,
			       struct ucred *);
	int	(*vfs_putpage)(vm_ubc_object_t, struct vm_page **, int, int,
			       struct ucred *);
	int	(*vfs_write_check)(vm_ubc_object_t, struct vm_page *);
};

typedef struct vfs_ubcops *vfs_ubcops_t;

#define _FSOP_(f,obj,arg,r)			\
MACRO_BEGIN					\
	if (!((obj)->vu_flags & OB_FUNNEL)) {	\
		(r) = (*((obj)->vu_ops->f))arg;	\
	} else {				\
		unix_master();			\
		(r) = (*((obj)->vu_ops->f))arg;	\
		unix_release();			\
	}					\
MACRO_END

#define FSOP_REF(obj)	(*((obj)->vu_ops->vfs_refer))(obj)

#define FSOP_RELE(obj)	(*((obj)->vu_ops->vfs_release))(obj)

#define FSOP_GETPAGE(obj, off, l, pt, pl, n, ep, a, rw, cr, r)	\
	_FSOP_(vfs_getpage,obj,(obj,off,l,pt,pl,n,ep,a,rw,cr),r)

#define FSOP_PUTPAGE(obj, pl, n, f, cr, r)	\
	_FSOP_(vfs_putpage,obj,(obj,pl,n,f,cr),r)

/*
 * This call is not funneled as caller may not block.
 *
 * #define FSOP_WRITE_CHECK(obj, pp)	\
 *	(*((obj)->vu_ops->vfs_write_check))(obj, pp)
 *
 * This functionality is not currently used.
 */
#define FSOP_WRITE_CHECK(obj, pp)	(1)

#define UBC_OBJECT_WAIT(obj)    					\
MACRO_BEGIN								\
	vm_object_lock(obj);						\
	while ((obj)->vu_noutput) {					\
		(obj)->vu_flags |= OB_UBCWAIT;				\
		assert_wait_mesg((vm_offset_t)&(obj)->vu_noutput,	\
				 FALSE, "ubcwait");			\
		vm_object_unlock(obj);					\
		thread_block();						\
		vm_object_lock(obj);					\
	}								\
	vm_object_unlock(obj);						\
MACRO_END

#define UBC_OBJECT_WAKEUP(obj)    					\
MACRO_BEGIN								\
	vm_object_lock(obj);						\
	assert((obj)->vu_noutput > 0);					\
	(obj)->vu_noutput--;						\
	if (!(obj)->vu_noutput && ((obj)->vu_flags & OB_UBCWAIT)) {	\
		(obj)->vu_flags &= ~OB_UBCWAIT;				\
		vm_object_unlock(obj);					\
		thread_wakeup((vm_offset_t)&(obj)->vu_noutput);		\
	} else								\
		vm_object_unlock(obj);					\
MACRO_END

#ifdef	KERNEL
#include <machine/vm_ubc.h>

#ifndef	ubc_load
extern int ubc_load(struct vm_page *, vm_offset_t, vm_size_t);
#endif

#ifndef	ubc_unload
extern int ubc_unload(struct vm_page *, vm_offset_t, vm_size_t);
#endif

#ifndef	ubc_kmem_alloc
extern int ubc_kmem_alloc(struct vm_page *);
#endif

#ifndef ubc_kmem_free
extern int ubc_kmem_free(struct vm_page *);
#endif

#ifndef ubc_kmem_cache
extern boolean_t ubc_kmem_cache(struct vm_page *);
#endif

#ifndef ubc_page_zero
extern void ubc_page_zero(struct vm_page *, vm_offset_t, vm_size_t);
#endif

/*
 * ubc_kluster operation flags for hold condition
 */

#define	UBC_HNONE	0x0			/* Don't hold pages */
#define	UBC_HBCP	0x1			/* Hold before center page */
#define	UBC_HACP	0x2			/* Hold after center page */
#define	UBC_HALL	(UBC_HBCP|UBC_HACP)	/* Hold all pages */

#define	ubc_page_wait(PP) {						\
	vm_object_lock((PP)->pg_object);				\
	while ((PP)->pg_busy) {						\
		(PP)->pg_wait = 1;					\
		assert_wait_mesg((vm_offset_t)(PP), FALSE, "pg_wait");	\
		vm_object_unlock((PP)->pg_object);			\
		thread_block();						\
		vm_object_lock((PP)->pg_object);			\
	}								\
	vm_object_unlock((PP)->pg_object);				\
}

#define	ubc_page_hold(PP) {				\
	vm_object_lock((PP)->pg_object);		\
	(PP)->pg_hold++;				\
	vm_object_unlock((PP)->pg_object);		\
}

extern struct vm_page	*ubc_dirty_kluster(vm_ubc_object_t, struct vm_page *,
					   vm_offset_t, vm_size_t, int,
					   boolean_t, int *);
extern struct vm_page	*ubc_kluster(vm_ubc_object_t, struct vm_page *,
				     vm_offset_t, vm_size_t, int, int, int *);
extern struct vm_page	*ubc_alloc(vm_ubc_object_t, vm_offset_t);
extern vm_ubc_object_t	ubc_object_allocate(vfs_private_t, vfs_ubcops_t, int);
extern struct buf	*ubc_bufget(void);
extern struct buf	*ubc_bufalloc(struct vm_page *, int, int, int, int);
extern void		ubc_buffree(struct buf *);
extern void		ubc_dirty_thread_loop(void);
extern void		ubc_async_iodone_lwc(void);
extern int		ubc_sync_iodone(struct buf *);
extern void		ubc_page_release(struct vm_page *, int);
extern void		ubc_memory_flushdirty(void);
extern int		ubc_init(void);
extern int		ubc_memory_purge(int, int, int);
extern int		ubc_free_page(vm_ubc_object_t, struct vm_page *, int);
extern void		ubc_page_stealer(int);
extern void		ubc_object_free(vm_ubc_object_t);
extern int		ubc_invalidate(vm_ubc_object_t, vm_offset_t,
				       vm_size_t, int);
extern void		ubc_page_lookup(vm_ubc_object_t, vm_offset_t,
					struct vm_page **);
extern boolean_t	ubc_incore(vm_ubc_object_t, vm_offset_t, vm_size_t);
extern int		ubc_lookup(vm_ubc_object_t, vm_offset_t, vm_size_t,
				   vm_size_t, struct vm_page **, int *);
extern int		ubc_page_alloc(vm_ubc_object_t, vm_offset_t, vm_size_t,
				       vm_size_t, struct vm_page **, int *);
extern int		ubc_page_dirty(struct vm_page *);
extern int		advfs_ubc_page_dirty(struct vm_page *);
extern int		ubc_check_mod(struct vm_ubc_object *);
extern int		ubc_msync(vm_ubc_object_t, vm_offset_t, vm_size_t, int);
extern int		ubc_flush_dirty(vm_ubc_object_t, int);
extern void		ubc_count_dirty(vm_ubc_object_t, vm_offset_t *,
					vm_size_t *);
extern int		ubc_free_memory(struct vm_page *);
extern int		ubc_wire(struct vm_page **, int, boolean_t);
extern int		ubc_unwire(struct vm_page **, int, boolean_t, boolean_t);
extern int		ubc_page_busy(struct vm_page *, int);
extern struct vm_page	*ubc_written_kluster(vm_ubc_object_t, struct vm_page *,
					     int);
#endif	/* KERNEL */
#endif	/* !_VM_VM_UBC_H_ */
