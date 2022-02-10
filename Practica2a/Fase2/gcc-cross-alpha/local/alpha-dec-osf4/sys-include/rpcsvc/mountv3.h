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
 * @(#)$RCSfile: mountv3.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1994/03/29 18:43:00 $
 */
/*
 * This file was originally generated by rpcgen, and should not be edited.
 * On the other hand, we don't regenerate this during the build, so here
 * it is.  Edit with care!
 */

#ifndef _RPCSVC_MOUNTV3_H_
#define _RPCSVC_MOUNTV3_H_

#include <standards.h>
#include <rpc/types.h>
#include <rpc/xdr.h>

#define FHSIZE3 64

typedef struct {
	u_int fhandle3_len;
	char *fhandle3_val;
} fhandle3;
_BEGIN_CPLUSPLUS
bool_t xdr_fhandle3 __((XDR *, fhandle3 *));
_END_CPLUSPLUS

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
typedef enum mountstat3 mountstat3;
_BEGIN_CPLUSPLUS
bool_t xdr_mountstat3 __((XDR *, mountstat3 *));
_END_CPLUSPLUS

struct mountres3_ok {
	fhandle3 fhandle;
	struct {
		u_int auth_flavors_len;
		int *auth_flavors_val;
	} auth_flavors;
};
typedef struct mountres3_ok mountres3_ok;
_BEGIN_CPLUSPLUS
bool_t xdr_mountres3_ok __((XDR *, mountres3_ok *));
_END_CPLUSPLUS

struct mountres3 {
	mountstat3 fhs_status;
	union {
		mountres3_ok mountinfo;
	} mountres3_u;
};
typedef struct mountres3 mountres3;
_BEGIN_CPLUSPLUS
bool_t xdr_mountres3 __((XDR *, mountres3 *));
_END_CPLUSPLUS

#define MOUNTVERS3 ((u_int)3)

#endif /* _RPCSVC_MOUNTV3_H_ */