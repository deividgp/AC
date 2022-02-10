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
 * @(#)$RCSfile: rnode.h,v $ $Revision: 1.1.17.5 $ (DEC) $Date: 1995/12/16 23:46:59 $
 */
/*	@(#)rnode.h	1.5 90/07/02 NFSSRC4.1 from 1.27 89/12/13 SMI 	*/
/*	Copyright (C) 1988, Sun Microsystems Inc. */

#ifndef _nfs_rnode_h
#define _nfs_rnode_h

typedef struct access_cache {
        uint32 known;
        uint32 allowed;
	struct ucred *cred;
	struct access_cache *next;
} access_cache;

#define NFS_FHANDLE_LEN 64

typedef struct nfs_fhandle {
        int fh_len;
        char fh_buf[NFS_FHANDLE_LEN];
} nfs_fhandle;

typedef struct symlink_cache {
	char *contents;		/* contents of the symbolic link */
	int len;		/* length of the contents */
	int size;		/* size of the allocated buffer */
} symlink_cache;


/*
 * Remote file information structure.
 * The rnode is the "inode" for remote files.  It contains all the
 * information necessary to handle remote file on the client side.
 *
 * Note on file sizes:  we keep two file sizes in the rnode: the size
 * according to the client (r_size) and the size according to the server
 * (r_attr.va_size).   They can differ because we modify r_size during a
 * write system call (nfs_rdwr), before the write request goes over the
 * wire (before the file is actually modified on the server).  If an OTW
 * request occurs before the cached data is written to the server the file
 * size returned from the server (r_attr.va_size) may not match r_size. 
 * r_size is the one we use, in general.  r_attr->va_size is only used to
 * determine whether or not our cached data is valid.
 */

struct rnode {
	udecl_simple_lock_data(, r_statelock) /* 8: protects rnode contents */
	lock_data_t     r_rwlock;       /* 32: serializes dir mods */
	struct rnode	*r_hash;	/* 8: rnode hash chain */
	struct vnode	*r_vnode;	/* 8: vnode for remote file */
	nfs_fhandle	r_fh;		/* 68: file handle */
	u_short		r_flags;	/* 2: flags, see below */
	u_short		r_lockcount;	/* 2: lock count */
	u_int		r_error;	/* 4: async write error */
	daddr_t		r_lastr;	/* 4: last block read (read-ahead) */
	struct ucred	*r_cred;	/* 8: current credentials */
	struct nameidata *r_ndp;	/* 8: unlink information */
	u_long		r_size;		/* 8: client's view of file size */
	struct vattr	r_attr;		/* 96: cached vnode attributes */
	struct timeval	r_attrtime;	/* 8: time attributes become invalid */
	access_cache    *r_acc;         /* 8: cache of access results */
	symlink_cache	r_symlink;	/* 16: cached readlink response */
	writeverf3	r_wrverf;	/* 8: rtned on WRITE and COMMIT */
	int		r_wrverfseq;	/* 4: sequence number of r_wrverf */
};

/*
 * Flags
 */
#define	RFLUSH		0x04		/* data flush in progress */
#define	REOF		0x08		/* EOF encountered on read */
#define	RDIRTY		0x10		/* dirty pages from write operation */
#define RNOCACHE	0x20		/* don't cache read and write blocks */

udecl_simple_lock_info(extern, rnode_state_lockinfo)
extern struct lockinfo *rnode_rw_lockinfo;
udecl_lock_data(extern, rnode_table_lock)
udecl_lock_info(extern, rnode_table_lockinfo)
#define NFS_RTABLE_LOCKINIT() \
	ulock_setup(&rnode_table_lock, rnode_table_lockinfo, TRUE)

/*
 * Convert between vnode and rnode
 */
#define	rtov(rp)	((rp)->r_vnode)
#define	vtor(vp)	((struct rnode *)((vp)->v_data))

#define VTOFH(vp)       (RTOFH(vtor(vp)))
#define vtofh(vp)       (RTOFH(vtor(vp)))
#define RTOFH(rp)       ((fhandle_t *)(((rp)->r_fh.fh_buf)))
#define rtofh(rp)       ((fhandle_t *)(((rp)->r_fh.fh_buf)))

#define VTOFH3(vp)      (RTOFH3(vtor(vp)))
#define RTOFH3(rp)      ((nfs_fh3 *)(&(rp)->r_fh))

#ifdef _KERNEL
_BEGIN_CPLUSPLUS
int nfs3_getfattr3(struct mntinfo *, nfs_fh3 *, fattr3 *, struct ucred *);
_END_CPLUSPLUS
#endif

#endif
