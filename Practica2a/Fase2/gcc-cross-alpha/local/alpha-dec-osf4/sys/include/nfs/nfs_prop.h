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
 * @(#)$RCSfile: nfs_prop.h,v $ $Revision: 1.1.12.2 $ (DEC) $Date: 1998/03/18 21:35:58 $
 */

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 * 
 * Attention:  According to Ric Werme, the previous comment may be ignored.
 */

#include <rpc/types.h>
#include <nfs/nfs.h>

enum propstat {
	PROP_OK = 0,
	PROPERR_PERM = 1,
	PROPERR_NOENT = 2,
	PROPERR_INTR = 4,
	PROPERR_IO = 5,
	PROPERR_NXIO = 6,
	PROPERR_NOMEM = 12,
	PROPERR_ACCES = 13,
	PROPERR_FAULT = 14,
	PROPERR_BUSY = 16,
	PROPERR_EXIST = 17,
	PROPERR_NOTDIR = 20,
	PROPERR_INVAL = 22,
	PROPERR_NFILE = 23,
	PROPERR_MFILE = 24,
	PROPERR_NOSPC = 28,
	PROPERR_ROFS = 30,
	PROPERR_AGAIN = 35,
	PROPERR_OPNOTSUPP = 45,
	PROPERR_NETUNREACH = 51,
	PROPERR_TIMEDOUT = 60,
	PROPERR_LOOP = 62,
	PROPERR_NAMETOOLONG = 63,
	PROPERR_DQUOT = 69,
	PROPERR_STALE = 70,
	PROPERR_REMOTE = 71,
	PROPERR_NOTSUP = 99,
	PROPERR_SERVERFAULT = 10006,
	PROPERR_GET = 10009
};
typedef enum propstat propstat;
bool_t xdr_propstat();

extern bool_t xdr_fhandle();

extern bool_t xdr_nfs_fh3();

typedef char *nameptr;
bool_t xdr_nameptr();

typedef struct {
        u_int val_len;
        char *val_val;
} val;
bool_t xdr_val();

enum propflags {
        PROPAGATE_ON_COPY = 0x00000001
};
typedef enum propflags propflags;
bool_t xdr_propflags();

struct prlistname_args {
	u_int pl_mask;
	struct {
		u_int pl_names_len;
		nameptr *pl_names_val;
	} pl_names;
};
typedef struct prlistname_args prlistname_args;
bool_t xdr_prlistname_args();

struct PROPGETargs {
	fhandle_t ga_fh;
	prlistname_args ga_name_args;
};
typedef struct PROPGETargs PROPGETargs;
bool_t xdr_PROPGETargs();

struct PROPGET3args {
        nfs_fh3 ga_fh;
        prlistname_args ga_name_args;
};
typedef struct PROPGET3args PROPGET3args;
bool_t xdr_PROPGET3args();

struct propattr {
	nameptr attr_name;
	val attr_val;
	u_int attr_mask;
};
typedef struct propattr propattr;
bool_t xdr_propattr();

struct PROPGETresok {
	u_int gr_ret;
	struct {
                u_int gr_buf_len;
                propattr *gr_buf_val;
        } gr_buf;
};
typedef struct PROPGETresok PROPGETresok;
bool_t xdr_PROPGETresok();

struct PROPGETres {
	propstat gr_status;
	union {
		PROPGETresok pgres;
	} PROPGETres_u;
};
typedef struct PROPGETres PROPGETres;
bool_t xdr_PROPGETres();

struct PROPSETargs {
	fhandle_t sa_fh;
	struct {
		u_int sa_buf_len;
                propattr *sa_buf_val;
        } sa_buf;
};
typedef struct PROPSETargs PROPSETargs;
bool_t xdr_PROPSETargs();

struct PROPSET3args {
        nfs_fh3 sa_fh;
        struct {
                u_int sa_buf_len;
                propattr *sa_buf_val;
        } sa_buf;
};
typedef struct PROPSET3args PROPSET3args;
bool_t xdr_PROPSET3args();

struct PROPSETres {
	propstat sr_status;
	union {
		u_int psres;
	} PROPSETres_u;
};
typedef struct PROPSETres PROPSETres;
bool_t xdr_PROPSETres();

struct PROPDELargs {
	fhandle_t da_fh;
	prlistname_args da_name_args;
};
typedef struct PROPDELargs PROPDELargs;
bool_t xdr_PROPDELargs();

struct PROPDEL3args {
        nfs_fh3 da_fh;
        prlistname_args da_name_args;
};
typedef struct PROPDEL3args PROPDEL3args;
bool_t xdr_PROPDEL3args();

struct PROPACCESSargs {
        fhandle_t pa_fh;
        u_int pa_access;
};
typedef struct PROPACCESSargs PROPACCESSargs;
bool_t xdr_PROPACCESSargs();

struct PROPACCESSres {
        propstat pa_status;
        union {
                u_int pa_access;
        } PROPACCESSres_u;
};
typedef struct PROPACCESSres PROPACCESSres;
bool_t xdr_PROPACCESSres();

extern bool_t xdr_timeval();

extern bool_t xdr_fattr();

struct PROPGETATTRres {
        propstat pga_status;
        union {
                struct nfsfattr attributes;
        } PROPGETATTRres_u;
};
typedef struct PROPGETATTRres PROPGETATTRres;
bool_t xdr_PROPGETATTRres();

#define PROPLIST_PROGRAM ((u_int)300020)
#define PROPLIST_VERSION2 ((u_int)2)
#define PROPROC_NULL ((u_int)0)
extern void *proproc_null_2();
#define PROPROC_GET ((u_int)1)
extern PROPGETres *proproc_get_2();
#define PROPROC_SET ((u_int)2)
extern PROPSETres *proproc_set_2();
#define PROPROC_DEL ((u_int)3)
extern propstat *proproc_del_2();
#define PROPROC_ACCESS ((u_int)4)
extern PROPACCESSres *proproc_access_2();
#define PROPROC_GETATTR ((u_int)5)
extern PROPGETATTRres *proproc_getattr_2();

#define PROPLIST_PROGRAM ((u_int)300020)
#define PROPLIST_VERSION3 ((u_int)3)
#define PROPROC3_NULL ((u_int)0)
extern void *proproc3_null_3();
#define PROPROC3_GET ((u_int)1)
extern PROPGETres *proproc3_get_3();
#define PROPROC3_SET ((u_int)2)
extern PROPSETres *proproc3_set_3();
#define PROPROC3_DEL ((u_int)3)
extern propstat *proproc3_del_3();
