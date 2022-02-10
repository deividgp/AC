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
 * @(#)$RCSfile: mount.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1994/10/17 22:34:53 $
 */
/*	@(#)mount.h	1.3 90/07/19 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 */

#ifndef _rpcsvc_mount_h
#define _rpcsvc_mount_h

#define	FHSIZE3			64

#define MOUNTPROG 100005
#define MOUNTPROC_MNT		1
#define MOUNTPROC_DUMP		2
#define MOUNTPROC_UMNT		3
#define MOUNTPROC_UMNTALL	4
#define MOUNTPROC_EXPORT	5
#define MOUNTPROC_EXPORTALL	6
#define MOUNTPROC_PATHCONF	7
#define MOUNTVERS		1
#define MOUNTVERS_POSIX		2
#define	MOUNTVERS3		3

#ifndef svc_getcaller
#define svc_getcaller(x) (&(x)->xp_raddr)
#endif


bool_t xdr_fhstatus();
bool_t xdr_mountres3();

enum mountstat3 {
	MNT_OK = 0,
	MNT3ERR_PERM = 1,
	MNT3ERR_NOENT = 2,
	MNT3ERR_IO = 5,
	MNT3ERR_ACCES = 13,
	MNT3ERR_NOTDIR = 20,
	MNT3ERR_INVAL = 22,
	MNT3ERR_NAMETOOLONG = 63,
	MNT3ERR_NOTSUPP = 10004,
	MNT3ERR_SERVERFAULT = 10006
};

struct mountlist {		/* what is mounted */
	char *ml_name;
	char *ml_path;
	struct mountlist *ml_nxt;
};

struct fhstatus {
	int fhs_status;
	fhandle_t fhs_fh;
};

struct fhandle3 {
	u_int fhandle3_len;
	char *fhandle3_val;
};

struct mountres3_ok {
	struct fhandle3 fhandle;
	struct {
		u_int auth_flavors_len;
		int *auth_flavors_val;
	} auth_flavors;
};

struct mountres3 {
	enum mountstat3 fhs_status;
	union {
		struct mountres3_ok mountinfo;
	} mountres3_u;
};

/*
 * List of exported directories
 * An export entry with ex_groups
 * NULL indicates an entry which is exported to the world.
 */
struct exports {
	dev_t		  ex_dev;	/* dev of directory */
	char		 *ex_name;	/* name of directory */
	struct groups	 *ex_groups;	/* groups allowed to mount this entry */
	struct exports	 *ex_next;
	short		  ex_rootmap;	/* id to map root requests to */
	short		  ex_flags;	/* bits to mask off file mode */
};

struct groups {
	char		*g_name;
	struct groups	*g_next;
};

#endif /*!_rpcsvc_mount_h*/
