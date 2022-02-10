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
 * @(#)$RCSfile: dvdfsmount.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1999/01/28 12:57:19 $
 */
#ifndef _DVDFSMOUNT_
#define	_DVDFSMOUNT_


/*
 * Mount structure.
 * One allocated on every mount.
 * Used to find the primary volume descriptor.
 */

struct	dvdfsmount {
	int	dm_flag;		/* Flags for perm/version... */
	struct	mount *dm_mountp;	/* vfs structure for this filesystem */
	dev_t	dm_dev;			/* device mounted */
	struct	vnode *dm_devvp;	/* vnode for block device mounted */
	struct	vnode *dm_rootvp;	/* vnode for root of filesystem */
	struct	dvdfs *dm_fs;		/* pointer to pvd */
	struct {
		uid_t	default_uid;	/* default uid if no xar */
		gid_t	default_gid;	/* default gid if no xar */
		mode_t	default_fmode;	/* default file mode if no xar */
		mode_t	default_dmode;	/* default dir mode if no xar */
		int	map_uid_ct;	/* map uid array size */
		map_id	*map_uid;	/* map uid array */
		int	map_gid_ct;	/* map gid array size */
		map_id	*map_gid;	/* map gid array */
	} dm_args;
#ifdef	_KERNEL
	udecl_simple_lock_data(,dm_lock)/* multiprocessor exclusion */
#endif
};


#ifdef	_KERNEL

/*
 * Convert mount ptr to dvdfsmount ptr.
 */

#define VFSTODVDFS(mp)	((struct dvdfsmount *)((mp)->m_data))

#endif
#endif

