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
 *	@(#)$RCSfile: sm_inter.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1994/03/29 18:49:57 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */

/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 * @(#) from SUN 1.5
 */

#ifndef _rpcsvc_sm_inter_h
#define _rpcsvc_sm_inter_h

#include <standards.h>
#include <rpc/xdr.h>

#define SM_PROG 100024
#define SM_VERS 1
#define SM_STAT 1
#define SM_MON 2
#define SM_UNMON 3
#define SM_UNMON_ALL 4
#define SM_SIMU_CRASH 5

#define SM_MAXSTRLEN 1024

struct sm_name {
	char *mon_name;
};
typedef struct sm_name sm_name;
_BEGIN_CPLUSPLUS
bool_t xdr_sm_name __((XDR *, sm_name *));
_END_CPLUSPLUS

struct my_id {
	char *my_name;
	int my_prog;
	int my_vers;
	int my_proc;
};
typedef struct my_id my_id;
_BEGIN_CPLUSPLUS
bool_t xdr_my_id __((XDR *, my_id *));
_END_CPLUSPLUS


struct mon_id {
	char *mon_name;
	struct my_id my_id;
};
typedef struct mon_id mon_id;
_BEGIN_CPLUSPLUS
bool_t xdr_mon_id __((XDR *, mon_id *));
_END_CPLUSPLUS

struct mon {
	struct mon_id mon_id;
	char priv[16];
};
typedef struct mon mon;
_BEGIN_CPLUSPLUS
bool_t xdr_mon __((XDR *, mon *));
_END_CPLUSPLUS

struct sm_stat {
	int state;
};
typedef struct sm_stat sm_stat;
_BEGIN_CPLUSPLUS
bool_t xdr_sm_stat __((XDR *, sm_stat *));
_END_CPLUSPLUS

enum res {
	stat_succ = 0,
	stat_fail = 1
};
typedef enum res res;
_BEGIN_CPLUSPLUS
bool_t xdr_res __((XDR *, res *));
_END_CPLUSPLUS

struct sm_stat_res {
	res res_stat;
	int state;
};
typedef struct sm_stat_res sm_stat_res;
_BEGIN_CPLUSPLUS
bool_t xdr_sm_stat_res __((XDR *, sm_stat_res *));
_END_CPLUSPLUS

struct status {
	char *mon_name;
	int state;
	char priv[16];
};
typedef struct status status;
_BEGIN_CPLUSPLUS
bool_t xdr_status __((XDR *, status *));
_END_CPLUSPLUS

#endif /*!_rpcsvc_sm_inter_h*/
