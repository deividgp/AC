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
#pragma ident "@(#)$RCSfile: nfs_server_stubs.c,v $ $Revision: 1.1.18.2 $ (DEC) $Date: 1998/04/28 18:09:34 $"


/*
 * This file was created to remove the NFS server routines
 * and replace them with stub routines. To enable the NFS server,
 * the OPTION "nfs_server" must be added to the configuration
 * file before building the kernel. If nfs_server is not in the
 * OPTION list, nfs_server.c and nfs3_server.c will be dropped
 * and this file (nfs_server_stubs.c) will be used. All nfs
 * server functionality will be unavailable and the kernel will
 * be smaller. The kernel will still support the NFS client.
 */

#include <rpc/rpc.h>
#include <nfs/nfs.h>

int ressize = sizeof(struct nfsrdresult); /* Used in rpc/svc_kudp.c */
int nfs_write_mbufs = 1; /* dbx knob, no SMP locking */
int nfs_nfsds = 0;              /* number of running NFS daemon processes */
int nfs3_write_mbufs = 1; /* dbx knob, no SMP locking */
int nfs_enabled=0;
char *rfsnames[] = {
        "null", "getattr", "setattr", "unused", "lookup", "readlink", "read",
        "unused", "write", "create", "remove", "rename", "link", "symlink",
        "mkdir", "rmdir", "readdir", "fsstat" }; /* read-only, no MP locking */

int     (*nfssvc_func)() = NULL;
int     (*exportfs_func)() = NULL;

extern  nfs_async_daemon();
extern  int (*async_daemon_func)();

/*
 * Ideally, all these server locks must be removed
 * since lockinfo.c has references to all these locks,
 * and since there isn't a separate lockinfo.c for serverless nfs,
 * they have to be declared here.
 * Once lockinfo.c is reconfigurable, the locks, their info
 * and the init routines can go.
 */
udecl_simple_lock_data(,nfs_activewrites_lock)
udecl_simple_lock_info(,nfs_activewrites_lockinfo)
udecl_simple_lock_data(,nfs_xprtfree_lock)
udecl_simple_lock_info(,nfs_xprtfree_lockinfo)
struct nfs_writereq *nfs_writefree = NULL;
udecl_simple_lock_data(,nfs_writefree_lock)
udecl_simple_lock_info(,nfs_writefree_lockinfo)
udecl_simple_lock_data(,nfs_export_lock)
udecl_simple_lock_info(, nfs_tslist_lockinfo)
/* v3 */
udecl_simple_lock_info(, nfs_export_lockinfo)
struct nfs3_writereq *nfs3_activewrites = NULL;
udecl_simple_lock_data(,nfs3_activewrites_lock)
udecl_simple_lock_info(,nfs3_activewrites_lockinfo)
struct nfs3_writereq *nfs3_writefree = NULL;
udecl_simple_lock_data(,nfs3_writefree_lock)
udecl_simple_lock_info(,nfs3_writefree_lockinfo)


/*
 * stub routines
 */

nfs_svc(p, args, retval)
        struct proc *p;
        void *args;
        int *retval;
{
        return(ENOTSUP);
}

nfs_init()
{
        nfssvc_func = exportfs_func = NULL;
        async_daemon_func = nfs_async_daemon;
        return(0);
}



nfs_packet(struct mbuf *m) 
{
         m_freem(m);
	 return;
}

int
rfs_dispatch(req, xprt)
        struct svc_req *req;
        register SVCXPRT *xprt;
{
        return(0);
}

nfssvc(p, args, retval)
        struct proc *p;
        void *args;
        long *retval;
{
        return(ENOTSUP);
}

exportfs(p, args, retval)
        struct proc *p;
        void *args;
        int *retval;
{
        return(ENOTSUP);
}

nfs_exportfs(p, args, retval)
        struct proc *p;
        void *args;
        int *retval;
{
        return(ENOTSUP);
}

void
rfs_xprtfree_lockinit() {	/* Called via nfs_hooks.c */
}

int purge_nfs_requests(struct vnode *vp, int cmd, struct sockaddr *saddr) {
	return ESUCCESS;
}

void
rfsputxprt_udp(SVCXPRT *xprt) {	/* Called from svc_kudp.c/buffree  */
}

char *rfsnames_v3[] = {
        "RFS3_NULL",
        "RFS3_GETATTR",
        "RFS3_SETATTR",
        "RFS3_LOOKUP",
        "RFS3_ACCESS",
        "RFS3_READLINK",
        "RFS3_READ",
        "RFS3_WRITE",
        "RFS3_CREATE",
        "RFS3_MKDIR",
        "RFS3_SYMLINK",
        "RFS3_MKNOD",
        "RFS3_REMOVE",
        "RFS3_RMDIR",
        "RFS3_RENAME",
        "RFS3_LINK",
        "RFS3_READDIR",
        "RFS3_READDIRPLUS",
        "RFS3_FSSTAT",
        "RFS3_FSINFO",
        "RFS3_PATHCONF",
        "RFS3_COMMIT"

};

