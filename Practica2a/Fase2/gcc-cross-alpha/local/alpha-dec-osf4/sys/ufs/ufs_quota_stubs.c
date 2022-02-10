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
#pragma ident "@(#)$RCSfile: ufs_quota_stubs.c,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1995/05/26 15:49:53 $"

/* stubs for quota routines when quota option is disabled */


#include <sys/secdefines.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/ucred.h>
#include <sys/namei.h>
#include <sys/errno.h>
#if     MACH
#include <kern/thread.h>
#include <kern/kalloc.h>
#include <kern/macro_help.h>
#else
#include <sys/malloc.h>
#endif
#include <sys/file.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/lock_types.h>
#include <ufs/fs.h>
#include <ufs/fs_proto.h>
#include <ufs/quota.h>
#include <ufs/inode.h>
#include <ufs/ufsmount.h>



#if defined( QUOTA )  &&  !QUOTA

struct lockinfo *umpq_lockinfo;
struct lockinfo *dq_lockinfo;

udecl_simple_lock_info(, dqh_lockinfo )
udecl_simple_lock_info(, dqfree_lockinfo )
udecl_simple_lock_data(, mounttab_lock)
udecl_simple_lock_info(, mounttab_lockinfo)
decl_simple_lock_info(, ump_qsync_lockinfo)


getinoquota(ip)
        register struct inode *ip;

{
        return( 0 );
}



chkdq(ip, change, cred, flags)
        register struct inode *ip;
        long change;
        struct ucred *cred;
        int flags;
{
        return( 0 );
}



chkdqchg(ip, change, cred, type)
        struct inode *ip;
        long change;
        struct ucred *cred;
        int type;
{
        return( 0 );
}



chkiq(ip, change, cred, flags)
        register struct inode *ip;
        long change;
        struct ucred *cred;
        int flags;
{
        return( 0 );
}


chkiqchg(ip, change, cred, type)
        struct inode *ip;
        long change;
        struct ucred *cred;
        int type;
{
        return( 0 );
}



quota_chown(ip, new_uid, new_gid, flags, cred)
register struct inode *ip;
uid_t new_uid;
gid_t new_gid;
struct ucred *cred;
{
        return( 0 );
}



quotaon(ndp, mp, type, fname)
        register struct nameidata *ndp;
        struct mount *mp;
        register int type;
        caddr_t fname;
{
        return( 0 );
}



quotaoff(mp, type)
        struct mount *mp;
        register int type;
{
        return( 0 );
}



getquota(mp, id, type, addr)
        struct mount *mp;
        u_int id;
        int type;
        caddr_t addr;
{
        return( 0 );
}



setquota(mp, id, type, addr)
        struct mount *mp;
        u_int id;
        int type;
        caddr_t addr;
{
        return( 0 );
}



setuse(mp, id, type, addr)
        struct mount *mp;
        u_int id;
        int type;
        caddr_t addr;
{
        return( 0 );
}



qsync(mp)
        struct mount *mp;
{
        return (0);
}



dqinit() {}



dqget(vp, id, ump, type, dqp)
        struct vnode *vp;
        u_int id;
        register struct ufsmount *ump;
        register int type;
        struct dquot **dqp;
{
        return( 0 );
}



void dqrele(vp, dq)
        struct vnode *vp;
        register struct dquot *dq;
{
}



void dqput(vp, dq)
        struct vnode *vp;
        register struct dquot *dq;
{
}



dqsync(vp, dq)
        struct vnode *vp;
        register struct dquot *dq;
{
        return( 0 );
}



dqflush(ump, vp)
        register struct ufsmount *ump;
        register struct vnode *vp;
{
        return( 0 );
}



#endif

