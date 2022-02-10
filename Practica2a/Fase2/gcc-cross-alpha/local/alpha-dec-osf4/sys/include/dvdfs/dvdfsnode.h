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
 * @(#)$RCSfile: dvdfsnode.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1999/01/28 12:57:20 $
 */
/*
 * The dvdnode is the dvdfs equivalent to ufs's inode. Any similarity
 * is purely coincidental.
 * There is a unique dvdnode allocated for each active file,
 * each current directory, each mounted-on file, text file, and the root.
 * A dvdnode is 'named' by its dev and unique number. (dvdget/dvdfs_node.c)
 */

/*
 * Since the DVDFS is a read-only file system, almost everything
 * in the dvdnode structure is static once a node has been initialized.
 *
 * The one exception is dvd_rdev, which may change due to a device mapping
 * user request.  When a dvd_rdev changes, however, a node is vgone()d.  
 * Anybody holding it open will lose their access (all I/O will then go via 
 * dead_vnops).
 *
 * So, locking is fairly simple:  just hold a reference to the associated 
 * vnode to prevent the deactivation of a node, and you can read the fields
 * as you like.
 */

#ifndef _CDFSNODE_H_
#define _CDFSNODE_H_

struct dvdnode {
	struct	dvdnode *dvd_chain[2];  /* hash chain, MUST be first */
	struct	vnode *dvd_vnode;	/* vnode associated with this node */
	struct	vnode *dvd_devvp;	/* vnode for block I/O */
	u_int	dvd_flag;		/* see below */
	u_short	dvd_mode;		/* file mode */
	u_short dvd_nlink;
	uid_t   dvd_uid;
	gid_t   dvd_gid;
	time_t  dvd_atime;       /* 16: time last accessed */
        time_t  dvd_mtime;       /* 24: time last modified */
        time_t  dvd_ctime;       /* 32: last time cdnode changed */
	int	dvd_gen;
	dev_t	dvd_dev;	/* device where dvdnode resides */
	dev_t	dvd_rdev;	/* device node identity (mapped) */
	dev_t	dvd_ondiskrdev;	/* device node identity on disk */
	ino_t	dvd_number;	/* disk address of entries dir record */
	struct	dvdfs *dvd_fs;	/* file sys associated with this dvdnode */
/*	struct	iso_idir cd_cdin;  the translated dvdnode */
#ifdef	_KERNEL
	lock_data_t	dvd_io_lock;	/* reading file's contents */
	event_t		dvd_iodone;	/* dvdnode is in transit from disk */
	udecl_simple_lock_data(,dvd_incore_lock)
#endif
};

#define	dvd_forw		dvd_chain[0]
#define	dvd_back		dvd_chain[1]


#ifdef	_KERNEL

/*
 * Convert between inode pointers and vnode pointers
 */

#define VTODVD(vp)	((struct dvdnode *)(vp)->v_data)
#define DVDTOV(dvdp)	((dvdp)->dvd_vnode)

#endif

#endif

