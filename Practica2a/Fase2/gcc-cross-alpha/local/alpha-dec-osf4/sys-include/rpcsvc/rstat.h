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
 *	@(#)$RCSfile: rstat.h,v $ $Revision: 4.2.4.3 $ (DEC) $Date: 1994/03/29 18:47:01 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */

/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 * @(#) from SUN 1.9
 */

#ifndef _rpcsvc_rstat_h
#define _rpcsvc_rstat_h

#include <standards.h>
#include <rpc/xdr.h>

#ifndef CPUSTATES
#include <sys/dk.h>
#endif

#include <rpc/types.h>

struct stats {				/* version 1 */
	int cp_time[4];
	int dk_xfer[4];
	u_int v_pgpgin;		/* these are cumulative sum */
	u_int v_pgpgout;
	u_int v_pswpin;
	u_int v_pswpout;
	u_int v_intr;
	int if_ipackets;
	int if_ierrors;
	int if_opackets;
	int if_oerrors;
	int if_collisions;
};
typedef struct stats stats;
_BEGIN_CPLUSPLUS
bool_t xdr_stats __((XDR *, struct stats *));
_END_CPLUSPLUS

struct statsswtch {				/* version 2 */
	int cp_time[4];
	int dk_xfer[4];
	u_int v_pgpgin;
	u_int v_pgpgout;
	u_int v_pswpin;
	u_int v_pswpout;
	u_int v_intr;
	int if_ipackets;
	int if_ierrors;
	int if_opackets;
	int if_oerrors;
	int if_collisions;
	u_int v_swtch;
	long avenrun[3];
	struct timeval boottime;
};
typedef struct statsswtch statsswtch;
_BEGIN_CPLUSPLUS
bool_t xdr_statsswtch __((XDR *, struct statsswtch *));
_END_CPLUSPLUS

struct statstime {				/* version 3 */
	int cp_time[4];
	int dk_xfer[4];
	u_int v_pgpgin;
	u_int v_pgpgout;
	u_int v_pswpin;
	u_int v_pswpout;
	u_int v_intr;
	int if_ipackets;
	int if_ierrors;
	int if_opackets;
	int if_oerrors;
	int if_collisions;
	u_int v_swtch;
	long avenrun[3];
	struct timeval boottime;
	struct timeval curtime;
};
typedef struct statstime statstime;
_BEGIN_CPLUSPLUS
bool_t xdr_statstime __((XDR *, statstime *));
_END_CPLUSPLUS

struct statsvar {				/* version 4 */
	struct {
		u_int cp_time_len;
		int *cp_time_val;
	} cp_time;			/* variable sized */
	struct {
		u_int dk_xfer_len;
		int *dk_xfer_val;
	} dk_xfer;			/* variable sized */
	u_int v_pgpgin;
	u_int v_pgpgout;
	u_int v_pswpin;
	u_int v_pswpout;
	u_int v_intr;
	int if_ipackets;
	int if_ierrors;
	int if_opackets;
	int if_oerrors;
	int if_collisions;
	u_int v_swtch;
	long avenrun[3];
	struct timeval boottime;
	struct timeval curtime;
};
typedef struct statsvar statsvar;
_BEGIN_CPLUSPLUS
bool_t xdr_statsvar __((XDR *, statsvar *));

#define RSTATPROG ((u_int)100001)
#define RSTATVERS_SWTCH ((u_int)2)
#define RSTATPROC_STATS ((u_int)1)
extern statsswtch *rstatproc_stats_2();
#define RSTATPROC_HAVEDISK ((u_int)2)
extern long *rstatproc_havedisk_2();
#define RSTATVERS_TIME ((u_int)3)
extern statstime *rstatproc_stats_3();
extern long *rstatproc_havedisk_3();
#define RSTATVERS_VAR ((u_int)4)
extern statsvar *rstatproc_stats_4();
extern long *rstatproc_havedisk_4();
int havedisk __((char *));
_END_CPLUSPLUS

#endif /*!_rpcsvc_rstat_h*/
