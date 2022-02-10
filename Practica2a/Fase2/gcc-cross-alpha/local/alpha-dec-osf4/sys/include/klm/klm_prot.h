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
 * @(#)$RCSfile: klm_prot.h,v $ $Revision: 1.1.7.3 $ (DEC) $Date: 1994/01/19 23:02:47 $";
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
 *  	(c) 1986,1987,1988,1989,1993  Sun Microsystems, Inc.
 *  	(c) 1983,1984,1985,1986,1987,1988,1989  AT&T.
 *		All rights reserved.
 */
/*
 * This file was originally generated using rpcgen.
 */

#ifndef	_KLM_PROT_H_RPCGEN
#define	_KLM_PROT_H_RPCGEN

#pragma ident	"@(#)klm_prot.h	1.9	93/07/09 SMI"   /*  SVr4 1.1 */

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Important NLM constants from <rpcsvc/nlm_prot.h>.  The NLM stuff
 * generally lives in user-land, so we don't have direct access to the
 * relevant .h or .x files.  Copying the constants here is a bit slimy; we
 * should fix this sometime.
 */
#define	NLM_VERS	((u_long)1)
#define	NLM4_VERS	((u_long)4)

#define	LM_MAXSTRLEN 1024

enum klm3_stats {
	KLM3_GRANTED = 0,
	KLM3_DENIED = 1,
	KLM3_DENIED_NOLOCKS = 2,
	KLM3_WORKING = 3,
	KLM3_DEADLCK = 5,
	KLM3_ROFS = 6,
	KLM3_STALE_FH = 7,
	KLM3_FBIG = 8,
	KLM3_FAILED = 9
};
typedef enum klm3_stats klm3_stats;

struct klm3_lock {
	char *server_name;
	netobj fh;
	uint32 nlm_vers;
	uint64 base;
	uint64 length;
	int32 type;
	int32 granted;
	int32 color;
	int32 LockID;
	int32 class;
	uint32 pid;
	uint32 rsys;
	uint32 rpid;
};
typedef struct klm3_lock klm3_lock;

struct klm3_holder {
	bool_t exclusive;
	uint64 base;
	uint64 length;
	int32 type;
	int32 granted;
	int32 color;
	int32 LockID;
	uint32 pid;
	int32 class;
	uint32 rsys;
	uint32 rpid;
};
typedef struct klm3_holder klm3_holder;

struct klm3_stat {
	klm3_stats stat;
};
typedef struct klm3_stat klm3_stat;

struct klm3_testrply {
	klm3_stats stat;
	union {
		struct klm3_holder holder;
	} klm3_testrply_u;
};
typedef struct klm3_testrply klm3_testrply;

struct klm3_lockargs {
	bool_t block;
	bool_t exclusive;
	struct klm3_lock alock;
};
typedef struct klm3_lockargs klm3_lockargs;

struct klm3_testargs {
	bool_t exclusive;
	struct klm3_lock alock;
};
typedef struct klm3_testargs klm3_testargs;

struct klm3_unlockargs {
	struct klm3_lock alock;
};
typedef struct klm3_unlockargs klm3_unlockargs;

#define	KLM_PROG ((u_long)100020)
#define	KLM3_VERS ((u_long)3)

#define	KLMPROC3_NULL ((u_long)0)
#define	KLMPROC3_TEST ((u_long)1)
#define	KLMPROC3_LOCK ((u_long)2)
#define	KLMPROC3_CANCEL ((u_long)3)
#define	KLMPROC3_UNLOCK ((u_long)4)
#define	KLMPROC3_GRANTED ((u_long)5)

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_klm3_stat(XDR *, klm3_stat*);
extern  bool_t xdr_klm3_testrply(XDR *, klm3_testrply*);
extern  bool_t xdr_klm3_lockargs(XDR *, klm3_lockargs*);
extern  bool_t xdr_klm3_testargs(XDR *, klm3_testargs*);
extern  bool_t xdr_klm3_unlockargs(XDR *, klm3_unlockargs*);

#else /* K&R C */
bool_t xdr_klm3_stat();
bool_t xdr_klm3_testrply();
bool_t xdr_klm3_lockargs();
bool_t xdr_klm3_testargs();
bool_t xdr_klm3_unlockargs();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif	/* !_KLM_PROT_H_RPCGEN */
