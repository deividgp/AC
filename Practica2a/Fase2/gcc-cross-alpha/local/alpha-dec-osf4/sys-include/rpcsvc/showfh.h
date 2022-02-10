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
 *	@(#)$RCSfile: showfh.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1994/03/29 18:48:33 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 */

/*
 * showfh - show file handle client/server definitions
 */
#ifndef _rpcsvc_showfh_h
#define _rpcsvc_showfh_h

#include <standards.h>
#include <sys/types.h>
#include <rpc/xdr.h>

#define MAXNAMELEN 	1024
#define SHOWFH_SUCCESS	0
#define SHOWFH_FAILED	1
#define FHSIZE		8

struct res_handle {
	char *file_there;	/* Name of the file or error message */
	int result;		/* succeeded or failed ? */
};
typedef struct res_handle res_handle;
_BEGIN_CPLUSPLUS
bool_t xdr_res_handle __((XDR *, res_handle *));
_END_CPLUSPLUS

struct nfs_handle {
	struct {
		u_int cookie_len;
		u_int *cookie_val;
	} cookie;
};
typedef struct nfs_handle nfs_handle;
_BEGIN_CPLUSPLUS
bool_t xdr_nfs_handle __((XDR *, nfs_handle *));

#define FILEHANDLE_PROG ((u_long)100043)
#define FILEHANDLE_VERS ((u_long)1)
#define GETRHANDLE ((u_long)1)
extern res_handle *getrhandle_1();
_END_CPLUSPLUS

#endif /*!_rpcsvc_showfh_h*/
