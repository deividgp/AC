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
#pragma ident "@(#)$RCSfile: vfs_conf.c,v $ $Revision: 4.2.85.2 $ (DEC) $Date: 1998/10/30 19:51:12 $"
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)vfs_conf.c	3.2 (Berkeley) 5/30/91
 */

#include <sys/param.h>
#include <sys/mount.h>
#include <sys/user.h>
#include <sys/vnode.h>
#include <mach/vm_param.h>
#include <sys/sysconfig.h>
#include <sys/errno.h>
#include <sys/lock_types.h>
#include <sys/malloc.h>
#include <vm/vm_ubc.h>

/*
 * These define the root filesystem and device.
 */
struct vnode *rootvp = (struct vnode *)0;
struct mount *rootfs = (struct mount *)0;
struct vnode *rootdir = (struct vnode *)0;

/*
 * Set up the filesystem operations for vnodes.
 * The types are defined in mount.h.
 */
extern	struct vfsops ufs_vfsops;

#include <nfs.h>
#if	NFS && !NFS_DYNAMIC
extern	struct vfsops nfs_vfsops;
extern	struct vfsops nfs3_vfsops;
#endif
#if	NFS == 0
	/*
	 * If NFS is not configured then the rpc subsystem will not be
	 * linked into the kernel, thereby leaving the routine rpcinit
	 * undefined.  This stub routine will take its place if NFS is 
	 * not configured.  Placed here beacuse this file is built on
	 * a per platform basis.
	 */
void	rpcinit() {}
#endif 

#include <cdfs.h>
#if	CDFS && !CDFS_DYNAMIC
extern  struct vfsops cdfs_vfsops;
#endif
#if CDFS == 0
struct vnodeops cdfs_vnodeops;
#endif

#include <dvdfs.h>
#if	DVDFS && !DVDFS_DYNAMIC
extern  struct vfsops dvdfs_vfsops;
#endif
#if DVDFS == 0
struct vnodeops dvdfs_vnodeops;
#endif

#include <msfs.h>

#if	MSFS == 0
int	msfs_mntbusybuf() {return(0);}
void	msfs_mntflushbuf() {return;}
struct vfs_ubcops msfs_ubcops;
#endif

#if     MSFS && !MSFS_DYNAMIC
extern  struct vfsops msfs_vfsops;
#endif

#include <dcedfs.h>
#if defined(DCEDFS) && DCEDFS
extern  struct vfsops dfs_vfsops;
#endif

#include <dceefs.h>
#if defined(DCEEFS) && DCEEFS
extern  struct vfsops efs_vfsops;
#endif

#include <ffm_fs.h>
#if FFM_FS && !FFM_FS_DYNAMIC
extern struct vfsops ffm_vfsops;
#endif
#if FFM_FS == 0
int
ffm_inactive(void) {return(0);}
#endif

extern  struct vfsops procfs_vfsops;

extern	struct vfsops fdfs_vfsops;


/********************** Note *********************
 *
 * When adding any file system type past MOUNT_MAXTYPE (sys/mount.h)
 * the generic file system ADDON should be used. Meaning,
 * the vnode v_tag field should be set to VT_ADDON, and file
 * system types should return MOUNT_ADDON. This ensures user
 * level utilities will recognize additional file systems as the
 * generic type "addon".
 *
 * The subordinate file system user level mount command
 * (/sbin/mount_xxx) will need to specify the index into the
 * vfssw structure to pass to mount(2).
 *
 ********************** End Note *****************/
struct vfsops_with_fsname vfssw[] = {
        (struct vfsops *)0,	"unknown",	/* 0 = MOUNT_NONE */
	&ufs_vfsops,		"ufs",		/* 1 = MOUNT_UFS */
#if	NFS && !NFS_DYNAMIC
	&nfs_vfsops,		"nfs",		/* 2 = MOUNT_NFS */
#else
	(struct vfsops *)0,	"",		/* 2 = MOUNT_NFS */
#endif
	(struct vfsops *)0,	"",		/* 3 = MOUNT_MFS */
	(struct vfsops *)0,	"",		/* 4 = MOUNT_PC */
	(struct vfsops *)0,    	"",		/* 5 = MOUNT_S5FS */
#if	CDFS && !CDFS_DYNAMIC
        &cdfs_vfsops,           "cdfs",		/* 6 = MOUNT_CDFS */
#else
	(struct vfsops *)0,    	"",		/* 6 = MOUNT_CDFS */
#endif
#if defined(DCEDFS) && DCEDFS
	&dfs_vfsops,            "dfs",		/* 7 = MOUNT_DFS */
#else
	(struct vfsops *)0,     "",		/* 7 = MOUNT_DFS */
#endif
#if defined(DCEEFS) && DCEEFS
	&efs_vfsops,            "efs",		/* 8 = MOUNT_EPI */
#else
	(struct vfsops *)0,     "",		/* 8 = MOUNT_EPI */	
#endif  
	&procfs_vfsops,		"procfs",	/* 9 = MOUNT_PROCFS */
#if     MSFS && !MSFS_DYNAMIC
        &msfs_vfsops,           "advfs",	/* 10 = MOUNT_MSFS */
#else
        (struct vfsops *)0,     "",		/* 10 = MOUNT_MSFS */
#endif
#if	FFM_FS && !FFM_FS_DYNAMIC
	&ffm_vfsops,		"ffm",		/* 11 = MOUNT_FFM */
#else
	(struct vfsops *)0,	"",		/* 11 = MOUNT_FFM */
#endif
	&fdfs_vfsops,		"fdfs",		/* 12 = MOUNT_FDFS */
        (struct vfsops *)0,     "",		/* 13 = MOUNT_ADDON */
#if     NFS && !NFS_DYNAMIC
        &nfs3_vfsops,           "nfsv3", 	/* 14 = MOUNT_NFS3 */
#else
        (struct vfsops *)0,     "",		/* 14 = MOUNT_NFS3 */
#endif
#if     DVDFS && !DVDFS_DYNAMIC
        &dvdfs_vfsops,           "dvdfs", 	/* 15 = MOUNT_DVDFS */
#else
        (struct vfsops *)0,     "",		/* 15 = MOUNT_DVDFS */
#endif
};

int mount_maxtype = sizeof (vfssw) / sizeof (vfssw[0]) - 1;


/*
 * Allow adjustment of the maximum number of locks that may be held.
 * The space required is allocated as necessary but is limited so a
 * wayward program can't eat up all of kernel memory with lock structures.
 * nlock_record may be overridden by something like
 * "options nlock_record = 20000" in the config file.
 */
#ifndef NLOCK_RECORD
#define NLOCK_RECORD 10000
#endif
long nlock_record = NLOCK_RECORD;

void
vfs_mountroot()
{
	register int error;
	extern int networkboot;

	/*
	 * Allocate a mount structure for root (rootfs).
	 * Initialize locks and common fields
	 */
	MALLOC(rootfs, struct mount *, sizeof(struct mount), M_MOUNT, M_WAITOK);
        bzero(rootfs, sizeof(*rootfs));
	UNMOUNT_LOCK_INIT(rootfs);
        MOUNT_VLIST_LOCK_INIT(rootfs);
        MOUNT_LOCK_INIT(rootfs);
        rootfs->m_op = vfssw[networkboot ? MOUNT_NFS : MOUNT_UFS].vops_ptr;
        rootfs->m_next = rootfs;
        rootfs->m_prev = rootfs;
	/*
	 * XXX Yuck !
	 */
#if     MSFS && !MSFS_DYNAMIC
	{
		extern lock_data_t Bfs_delete_lk;
		extern struct lockinfo *Bfs_delete_lockinfo;

		lock_setup(&Bfs_delete_lk, Bfs_delete_lockinfo, TRUE);
	}
#endif
        /*
         * Call the filesystem specific mountroot routine.
         */
        VFS_MOUNTROOT(rootfs, &rootvp, error);
        if (networkboot && error)
                panic("vfs_mountroot: cannot mount root");
        if (error && vfssw[MOUNT_MSFS].vops_ptr) {
                rootfs->m_op = vfssw[MOUNT_MSFS].vops_ptr;
                VFS_MOUNTROOT(rootfs, &rootvp, error);
        }
#if     CDFS && !CDFS_DYNAMIC
        if (error && vfssw[MOUNT_CDFS].vops_ptr) {
                rootfs->m_op = vfssw[MOUNT_CDFS].vops_ptr;
                VFS_MOUNTROOT(rootfs, &rootvp, error);
        }
#endif  /* CDFS && !CDFS_DYNAMIC */
        if (error)
                panic("vfs_mountroot: cannot mount root");

	/*
         * Get vnode for '/'.
         * Setup rootdir and u.u_cdir to point to it.
         */
mounted:
        rootvp->v_mount = rootfs;       /* set up root device's mount ptr */
        VFS_ROOT(rootfs, &rootdir, error);
        if (error)
                panic("vfs_mountroot: cannot get root filesystem");
	VFS_START(rootfs, 0, error);
        if (error)
                panic("vfs_mountroot: cannot start root filesystem");
        u.u_cdir = rootdir;
        VREF(u.u_cdir);
        u.u_rdir = NULL;
}

#include <quota.h>
/*
 * operate on filesystem quotas
 */
/* ARGSUSED */
quotactl(p, args, retval)
	struct proc *p;
	void *args;
	long *retval;
{
#if defined(QUOTA) && QUOTA
	register struct args {
		char *path;
		long cmd;
		long uid;
		caddr_t arg;
	} *uap = (struct args *) args;
	register struct mount *mp;
	register struct nameidata *ndp = &u.u_nd;
	struct vnode *vp;
	int error;

	/*
	 * namei will pend at the filesystem's root if
	 * an unmount is in progress so a quotactl operation
	 * can't interfere with a pending unmount.  However,
	 * an unmount can begin after a quotactl operation starts,
	 * so the filesystem-specific unmount routine must handle
	 * potential unmount/quotactl races.
	 *
	 * We defer the vrele until after the quota operation
	 * so that we may hang onto our reference on the filesystem
	 * across the lower layer's operation.  Otherwise, the
	 * filesystem could become unmounted in the normal way while
	 * we do our thing.  (Forcible unmount is another case entirely.)
	 */
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->path;
	if (error = namei(ndp))
		return (error);
	mp = ndp->ni_vp->v_mount;
	vp = ndp->ni_vp;
	VFS_QUOTACTL(mp, uap->cmd, uap->uid, uap->arg, error);
	vrele(vp);
	return (error);
#else
	return(EOPNOTSUPP);
#endif
}

#if !NFS
/*
 * Hack to fix SAS build in MUP.  Real klm_lockctl is in 
 * kernel/klm/klm_lockmgr.c
 */
klm_lockctl(lh, ld, cmd, cred, clid, whereto)
        char *lh;
        char *ld;
        int cmd;
        char *cred;
        int clid;
        int whereto;
{
	return(EOPNOTSUPP);
}
/*
 * real versions of the following programs are in nfs_hooks.c
 */

nfssvc(p, args, retval)
        struct proc *p;
        void *args;
        long *retval;
{
	return(EOPNOTSUPP);
}
async_daemon(p, args, retval)
        struct proc *p;
        void *args;
        long *retval;
{
	return(EOPNOTSUPP);
}

exportfs(p, args, retval)
        struct proc *p;
        void *args;
        int *retval;
{
	return(EOPNOTSUPP);
}

nfs_hooks_init()
{
	return(EOPNOTSUPP);
}

#endif /* NFS */
