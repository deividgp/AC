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
 *	@(#)$RCSfile: nfssys.h,v $ $Revision: 4.2.9.2 $ (DEC) $Date: 1995/03/10 16:20:20 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Common functions for loadable NFS system calls.  Temporary
 * until we have general loadable system calls.
 */

#ifndef	_NFS_NFSSYS_H_
#define	_NFS_NFSSYS_H_


#define NULL_FUNC		(int (*)(int))0

udecl_simple_lock_data(extern,nfs_sys_lock)	/* for dynamic loading of nfs */
udecl_simple_lock_info(extern,nfs_sys_lockinfo)/* for dynamic loading of nfs */
#define	NFS_SYS_LOCK()		usimple_lock(&nfs_sys_lock)
#define	NFS_SYS_UNLOCK()	usimple_unlock(&nfs_sys_lock)
#define	NFS_SYS_LOCK_INIT()	usimple_lock_setup(&nfs_sys_lock, nfs_sys_lockinfo)

extern lock_data_t	nfs_daemon_lock; /* for dynamic loading/unloading */
extern struct lockinfo *nfs_daemon_lockinfo;
#define	NFSD_LOCK()		lock_write(&nfs_daemon_lock)
#define	NFSD_READ_LOCK()	lock_read(&nfs_daemon_lock)
#define	NFSD_UNLOCK()		lock_done(&nfs_daemon_lock)
#define	NFSD_LOCK_INIT()	lock_setup(&nfs_daemon_lock,nfs_daemon_lockinfo, TRUE)
#define	NFSD_LOCK_HOLDER()	(LOCK_HOLDER(&nfs_daemon_lock))

udecl_simple_lock_data(extern,asyncdaemon_lock)
udecl_simple_lock_info(extern,asyncdaemon_lockinfo)
#define	ASYNCD_LOCK()		usimple_lock(&asyncdaemon_lock)
#define	ASYNCD_UNLOCK()		usimple_unlock(&asyncdaemon_lock)
#define	ASYNCD_LOCK_INIT()	usimple_lock_setup(&asyncdaemon_lock, asyncdaemon_lockinfo)

#endif	/* _NFS_NFSSYS_H_ */
