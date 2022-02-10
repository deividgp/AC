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
 * @(#)$RCSfile: vpage.h,v $ $Revision: 1.1.5.4 $ (DEC) $Date: 1995/04/05 16:03:46 $
 */
#ifndef	_VM_VPAGE_H_
#define	_VM_VPAGE_H_	1

/*
 * The vpage structure should have any information
 * the is of value for pushes a page out.  This
 * must be true for non K map operations.
 * It is possible that vpage might become pageable
 * in the future.  Care must be taken in acquiring
 * vpage information before taking any spin locks
 * in map entry handlers that require the vpage
 * information.
 */

struct vpage {

	/*
	 * Union of kernel and user vpage fields.  Identical ones
	 * must be in the same bit field position.
	 */

	union {
		struct {
		unsigned int
		_uvp_prot	: 3,		/* Keep protection here */
		_uvp_plock	: 1,		/* Page locked */
				: 28;
		} _uvp;
		struct {
		unsigned int
		_kvp_prot	: 3,		/* Same as user */
				: 5,
		_kvp_kwire	: 8,		/* Wiring count */
				:16;
		} _kvp;
	} _uvpage;
};

#define vp_prot		_uvpage._uvp._uvp_prot
#define vp_plock	_uvpage._uvp._uvp_plock
#define	vp_kwire	_uvpage._kvp._kvp_kwire

#define	VP_WAIT		0x1	/* wait on allocations */
#define	VP_NOCHK	0x2	/* don't check resource limits */

#ifdef	KERNEL
/*
 * Forward declarations of data structures for prototypes
 */
struct vm_map;
struct vm_map_entry;

extern kern_return_t u_vpage_alloc(struct vm_map *,
				   vm_size_t, struct vpage **, int);
extern void u_vpage_free(struct vm_map *, struct vpage *, vm_size_t, boolean_t);
extern kern_return_t u_vpage_reserve(struct vm_map *, vm_size_t);
extern void u_vpage_free_reserve(struct vm_map *, vm_size_t);
extern void u_vpage_expand(struct vpage **, vm_size_t, vm_size_t, vm_size_t);
extern	kern_return_t u_vpage_init(struct vm_map_entry *, int);
extern void vm_vpage_clip(struct vm_map_entry *, int);
extern void vm_vpage_clip_end(struct vm_map_entry *, struct vm_map_entry *,
        						int, boolean_t, int);
extern void vm_vpage_clip_start(struct vm_map_entry *, struct vm_map_entry *,
        						int, boolean_t, int);
extern void vm_vpage_clip_both(struct vm_map_entry *, struct vm_map_entry *,
				struct vm_map_entry *, int, boolean_t, int);
#endif	/* KERNEL */

#endif	/* !_VM_VPAGE_H_ */
