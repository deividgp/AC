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
#pragma ident "@(#)$RCSfile: procfs_vnops_stubs.c,v $ $Revision: 1.1.4.5 $ (DEC) $Date: 1995/10/30 19:32:24 $"


#include <sys/vfs_proto.h>
#include <sys/proc.h>
#include <procfs/procfs_l.h>

int	procfs_lookup();
int	procfs_open();
int	procfs_close();
int	procfs_access();
int	procfs_getattr();
int	procfs_read();
int	procfs_write();
int	procfs_ioctl();
int	procfs_select();
int	procfs_einval();
int	procfs_seek();
int	procfs_readdir();
int	procfs_abortop();
int	procfs_inactive();
int	procfs_reclaim();
int	procfs_print();
int	procfs_page_read();
int	procfs_page_write();
int	procfs_unsupp();
int	procfs_einval();
int	procfs_bread();
int	procfs_brelse();
int	procfs_noop();
int	procfs_notsupp();

struct vnodeops procfs_vnodeops = {
        procfs_lookup,		/* lookup */
        procfs_unsupp,		/* create */
        procfs_unsupp,		/* mknod */
        procfs_open,		/* open */
        procfs_close,		/* close */
        procfs_access,		/* access */
        procfs_getattr,		/* getattr */
        procfs_unsupp,		/* setattr */
        procfs_read,		/* read */
        procfs_write,		/* write */
        procfs_ioctl,		/* ioctl */
        procfs_select,		/* select */
        procfs_einval,		/* mmap */
        procfs_unsupp,		/* fsync */
        procfs_seek,		/* seek */
        procfs_unsupp,		/* remove */
        procfs_unsupp,		/* link */
        procfs_unsupp,		/* rename */
        procfs_unsupp,		/* mkdir */
        procfs_unsupp,		/* rmdir */
        procfs_unsupp,		/* symlink */
        procfs_readdir,		/* readdir */
        procfs_unsupp,		/* readlink */
        procfs_abortop,		/* abortop */
        procfs_inactive,	/* inactive */
        procfs_reclaim,		/* reclaim */
        procfs_unsupp,		/* bmap */
        procfs_unsupp,		/* strategy */
        procfs_print,		/* print */
        procfs_page_read,	/* page_read */
        procfs_page_write,	/* page_write */
	procfs_unsupp,		/* swap added for UBC */
	procfs_bread,		/* buffer read */
	procfs_brelse,		/* buffer release */
	procfs_einval,		/* file locking */
	procfs_unsupp,		/* fsync byte range*/
	procfs_noop,		/* Lock a node */
	procfs_noop,		/* Unlock a node */
	procfs_notsupp,		/* Get extended attributes */
	procfs_notsupp,		/* Set extended attributes */
	procfs_notsupp,		/* Delete extended attributes */
     	procfs_einval,		/* pathconf */		
};

decl_simple_lock_info(, procfs_trace_lockinfo)

procfs_unsupp()
{
	return(EACCES);
}

procfs_einval()
{
	return(EINVAL);
}

procfs_notsupp()
{
	return EOPNOTSUPP;
}

procfs_lookup(vp, ndp)
	struct vnode *vp;		/* root vnode for /proc */
	struct nameidata *ndp;		/* input and output data */
{
	return(ENOENT);
}

procfs_open(vpp, mode, cred)
	struct vnode **vpp;
	int mode;
	struct ucred *cred;
{
	return(ENOENT);
}

procfs_close(vp, fflag, cred)
	struct vnode *vp;
	int fflag;
	struct ucred *cred;
{
	return(0);
}

procfs_access(vp, mode, cred)
	struct vnode *vp;
	int mode;
	struct ucred *cred;
{
	return(ENOENT);
}

procfs_getattr(vp, vap, cred)
	struct vnode *vp;
	register struct vattr *vap;
	struct ucred *cred;
{
	return(ENOENT);
}

procfs_read(vp, uio, ioflag, cred)
	struct vnode *vp;
	register struct uio *uio;
	int ioflag;
	struct ucred *cred;
{
	return(0);
}

procfs_write(vp, uio, ioflag, cred)
	register struct vnode *vp;
	struct uio *uio;
	int ioflag;
	struct ucred *cred;
{
	return(0);
}

procfs_seek(vp, oldoff, newoff, cred)
	struct vnode *vp;
	off_t oldoff, newoff;
	struct ucred *cred;
{
	return(0);
}

procfs_readdir(vp, uio, cred, eofflagp)
	struct vnode *vp;
	register struct uio *uio;
	struct ucred *cred;
	int *eofflagp;
{
	return(0);
}
procfs_abortop(ndp)
	register struct nameidata *ndp;
{
	return(0);
}

procfs_inactive(vp)
        struct vnode *vp;
{
	return(0);
}

procfs_reclaim(vp)
        register struct vnode *vp;
{
	return(0);
}

procfs_print(vp)
	struct vnode *vp;
{
	return(0);
}


procfs_page_read(vp, uio, cred)
        struct vnode *vp;
        struct uio *uio;
        struct ucred *cred;
{
	return(EINVAL);
}

procfs_page_write(vp, uio, cred, pager, offset)
        struct vnode    *vp;
        struct uio      *uio;
        struct ucred    *cred;
        memory_object_t pager;
        vm_offset_t     offset;
{
	return(EINVAL);
}

procfs_select(vp, events, revents, scanning, cred)
	struct vnode *vp;		/* vnode for process to check */
	short  *events;			/* mask of events to search for */
	short  *revents;		/* mask of events found */
	int    scanning;		/* ? see bsd/sys_generic.c */
	struct ucred *cred;		/* calling process credentials */
{
	return(0);
}


procfs_ioctl(vp, com, data, fflag, cred)
struct vnode *vp;
u_int com;
caddr_t data;
int fflag;
struct ucred *cred;
{
	return(0);
}

procfs_tioctl(procp, thread, com, data, cred, taskp)
struct proc *procp;
tid_t thread;
int com;
caddr_t data;
struct ucred *cred;
struct task *taskp;
{
	return(0);
}


procfs_bread(vp, lbn, bpp, cred)
	register struct vnode *vp;
	off_t lbn;
	struct buf **bpp;
	struct ucred *cred;
{
	return (EOPNOTSUPP);
}

procfs_brelse(vp, bp)
	register struct vnode *vp;
	register struct buf *bp;
{
	return (EOPNOTSUPP);
}

int
procfs_noop()
{
	return (EOPNOTSUPP);
}

procfs_ioctl_interface(p,args,retval,data,fp,stk_parms) 
	struct proc *p;
	void *args;    
	long *retval;
	caddr_t data;
	struct file *fp;
	int stk_parms;
{
	return (0);
}
