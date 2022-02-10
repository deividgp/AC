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
 *
 * @(#)$RCSfile: lockmgr.h,v $ $Revision: 1.1.7.4 $ (DEC) $Date: 1994/01/19 23:02:49 $";
 */

/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
 *  		PROPRIETARY NOTICE (Combined)
 *
 *  This source code is unpublished proprietary information
 *  constituting, or derived under license from AT&T's Unix(r) System V.
 *  In addition, portions of such source code were derived from Berkeley
 *  4.3 BSD under license from the Regents of the University of
 *  California.
 *
 *
 *
 *  		Copyright Notice
 *
 *  Notice of copyright on this source code product does not indicate
 *  publication.
 *
 *  	(c) 1986,1987,1988,1989  Sun Microsystems, Inc.
 *  	(c) 1983,1984,1985,1986,1987,1988,1989  AT&T.
 *		All rights reserved.
 */

/*
 * Header file for Kernel<->Network Lock-Manager implementation
 */

#ifndef	_KLM_LOCKMGR_H_
#define	_KLM_LOCKMGR_H_

/*	"@(#)lockmgr.h	1.8	93/07/09 SMI"	 SVr4.0 1.1	*/
/*	From: lockmgr.h 1.6 88/02/08 SMI	*/

#include <nfs/nfs.h>
#include <sys/vnode.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The lockhandle_t uniquely describes any file in a domain.  The NFS
 * version number and file handle are obtained from the per-mount
 * information associated with the vnode.
 */

typedef struct {
	struct vnode *lh_vp;			/* vnode of file */
	char *lh_servername;			/* file server machine name */
} lockhandle_t;


/* define 'well-known' information */
#define	KLM_PROTO	IPPROTO_UDP

#ifdef _KERNEL

/* define public routines */
extern int  klm_lockctl(lockhandle_t *, struct eflock *, int, struct ucred *,
			pid_t, int);

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _KLM_LOCKMGR_H_ */
