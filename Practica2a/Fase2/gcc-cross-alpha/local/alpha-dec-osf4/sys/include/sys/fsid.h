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
 * @(#)$RCSfile: fsid.h,v $ $Revision: 1.1.5.2 $ (DEC) $Date: 1995/06/12 18:04:29 $
 */

#ifndef _SYS_FSID_H
#define _SYS_FSID_H

/* Fstyp names for use in fsinfo structure. These names */
/* must be constant across releases and will be used by a */
/* user level routine to map fstyp to fstyp index as used */
/* ip->i_fstyp. This is necessary for programs like mount. */


#define	NFS	"nfs"
#define MFS	"mfs"
#define PCFS	"pcfs"
#define S5FS	"s5fs"
#define CDFS	"cdfs"
#define FDFS	"fdfs"
#define DFS	"dfs"
#define EFS	"efs"
#define PROCFS	"procfs"
#define MSFS	"msfs"
#define FFM	"ffm"
#define MAXFS	"addon"
#define NFSV3	"nfsv3"
#ifndef KERNEL
#define	UFS	"ufs"
/* filesystem name strings for user utilities */
#else	/* KERNEL */
#define	UFS_STRING	"ufs"
#endif

#endif
