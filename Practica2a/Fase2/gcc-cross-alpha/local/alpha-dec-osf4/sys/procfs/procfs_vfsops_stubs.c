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
#pragma ident "@(#)$RCSfile: procfs_vfsops_stubs.c,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1995/03/21 14:29:54 $"


#include <sys/types.h>
#include <sys/errno.h>
#include <sys/vfs_proto.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <procfs/procfs_l.h>

int	procfs_mount();
int	procfs_start();
int	procfs_unmount();
int	procfs_root();
int	procfs_quotactl();
int	procfs_statfs();
int	procfs_sync();
int	procfs_init();
int	procfs_badop();

struct vfsops procfs_vfsops = {
        procfs_mount,
        procfs_start,
        procfs_unmount,
        procfs_root,
        procfs_quotactl,
        procfs_statfs,
        procfs_sync,
        procfs_badop,	/* no fhtovp */
        procfs_badop,	/* no vptofh */
        procfs_init,
	procfs_badop,	/* mountroot  added for UBC changes */
	procfs_badop	/* swapvp  added for UBC changes */
};

extern struct vnodeops procfs_vnodeops;

procfs_badop()
{
	return(EINVAL);
}

procfs_mount(mp, path, data, ndp)
	register struct mount *mp;	/* allocated by vfs layer */
	char *path;			/* mounted on directory */
	caddr_t data;			/* mount "device" */
	struct nameidata *ndp;		/* unused */
{
	return (ENXIO);
}

procfs_start(mp, flags)
	struct mount *mp;
	int flags;
{
	return (EINVAL);
}

procfs_unmount(mp, mntflags)
	struct mount *mp;
	int mntflags;
{
	return(0);
}

procfs_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
	*vpp = NULLVP;
	return (0);
}

procfs_quotactl(mp, cmds, uid, arg)
	struct mount *mp;
	int cmds;
	uid_t uid;
	caddr_t arg;
{
	return(0);
}

procfs_statfs(mp)
	struct mount *mp;
{
	return (0);
}

procfs_sync(mp, waitfor)
	struct mount *mp;
	int waitfor;
{
	return(0);
}

procfs_fhtovp(mp, fhp, vpp)
	register struct mount *mp;
	struct fid *fhp;
	struct vnode **vpp;
{
	return (0);
}

procfs_init()
{
	return (0);
}
