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
#pragma ident "@(#)$RCSfile: dcedfs_data.c,v $ $Revision: 1.1.11.3 $ (DEC) $Date: 1995/10/19 18:03:48 $"

/*
 * Stub routines to support DFS as a layered product
 * options DFS is enabled in BINARY to accommodate 
 * future configurability of DFS;  these stubs are 
 * DEFINED ONLY WHEN THE DCE DFS LAYERED PRODUCT IS NOT CONFIGURED
 */

#include <dcedfs.h>

#if !(defined(DCEDFS) && DCEDFS)

#include <sys/secdefines.h>

#include <sys/types.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/namei.h>
#include <sys/uio.h>
#include <sys/vnode.h>
#include <sys/specdev.h>
#include <sys/mount.h>
#include <sys/buf.h>
#include <sys/biostats.h>
#include <sys/ucred.h>
#include <sys/errno.h>

int
dfs_readop (vp, uio, ioflg, cred) 
     struct vnode *vp;
     struct uio   *uio;
     int          ioflg;
     struct ucred cred;
{
     register int error;

     VOP_READ (vp, uio, ioflg, cred, error);
     return (error);
}

int
dfs_writeop (vp, uio, ioflg, cred) 
     struct vnode *vp;
     struct uio   *uio;
     int          ioflg;
     struct ucred cred;
{
     register int error;

     VOP_WRITE (vp, uio, ioflg, cred, error);
     return (error);
}

int
dfs_getattrop (vp, vattr, cred)
     struct vnode *vp;
     struct vattr *vattr;
     struct ucred cred;
{
     register int error;

     VOP_GETATTR (vp, vattr, cred, error);
     return (error);
}

int
dfs_setattrop (vp, vattr, cred)
     struct vnode *vp;
     struct vattr *vattr;
     struct ucred cred;
{
     register int error;

     VOP_SETATTR (vp, vattr, cred, error);
     return (error);
}

int
afs_syscall (p, args, retval)
     struct proc *p;
     void *args;
     long *retval;
{
     *retval = -1L;
     return(ENOSYS);
}

/*
 * DFS Extended Ioctl system call (stub)
 */
int
dfs_xioctl(p, args, retval)
     struct proc *p;
     void *args;
     int *retval;
{
     return (ioctl_base (p, args, retval));
}

/*
 * DFS Extended Setgroups call (stub)
 */
int
dfs_xsetgroups(p, args, retval)
     register struct proc *p;
     void *args;
     int *retval;
{
     return (setgroups (p, args, retval));
}

dfs_scrunchfid(vp, fidp)
struct vnode *vp;
struct fid *fidp;
{
    return (EREMOTE);
}

dfs_expandfid(mp, fidp, vp)
struct mount *mp;
struct fid *fidp;
struct vnode *vp;
{
    return -1;
}

int
at_translate_creds(addr, uid, cred) 
struct sockaddr *addr;
uid_t uid;
struct ucred *cred;
{
    return 0;
}
#endif /* DCEDFS */

int
dfs_xxdebug ()
{
	return (1);
}
