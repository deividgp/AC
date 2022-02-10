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

#pragma	ident	"@(#)$RCSfile: voltrace.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1995/01/31 20:44:04 $"

/* @(#)src/common/uts/io/vxvm/voltrace.h	5.5 16 Mar 1993 02:08:27 - Copyright (c) 1993 VERITAS Software Corp. */
/*
 * Copyright(C)1993 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 * 
 *               RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *               VERITAS SOFTWARE
 * 4800 GREAT AMERICA PARKWAY, SANTA CLARA, CA 95054
 */
/*
 * Alpha change log
 *
 * 09-29-93	Wai Yim
 * Merged alpha port with vxvm1.2.1 source.
 *
 */

#ifndef _SYS_VOLTRACE_H
#define _SYS_VOLTRACE_H

/*
 * sys/voltrace.h - volume manager header for kernel tracing
 */

#define	VOL_MAXEVENTNO	0x7fffffff

/*
 * general object ID structure for getting stats
 */

struct vol_obid {
	volrid_t	o_dgrid;
	volrid_t	o_rid;
};

struct vol_getstat {
	volrid_t	s_dg_import_id;		/* disk group ID */
	volrid_t	s_rid;			/* object ID */
	union vol_stats	*s_stats;		/* stat buffer */
};

/*
 * volume manager I/O statistics
 */

struct vol_gstat {
	ulong	vs_ops;		/* number of operations */
	ulong	vs_bcnt;	/* number of blocks transferred */
	ulong	vs_time;	/* time spent doing I/O in HZ */
};

union vol_stats {
	struct disk_stat {
		struct vol_gstat vs_reads;	/* stats for reads */
		struct vol_gstat vs_writes;	/* stats for writes */
		ulong		 vs_readfails;	/* read failures */
		ulong		 vs_writefails;	/* write failures */
	} disk_stat;
	struct sd_stat {
		struct vol_gstat vs_reads;	/* stats for reads */
		struct vol_gstat vs_writes;	/* stats for writes */
		ulong		 vs_readfails;	/* read failures */
		ulong		 vs_writefails;	/* write failures */
	} sd_stat;
	struct pl_stat {
		struct vol_gstat vs_reads;	/* stats for reads */
		struct vol_gstat vs_writes;	/* stats for writes */
		ulong		 vs_readfails;	/* read failures */
		ulong		 vs_writefails;	/* write failures */
	} pl_stat;
	struct vol_stat {
		struct vol_gstat vs_reads;	/* stats for reads */
		struct vol_gstat vs_writes;	/* stats for writes */
		struct vol_gstat vs_acopy;	/* stats for atomic copies */
		struct vol_gstat vs_vreads;	/* stats for verify reads */
		struct vol_gstat vs_vwrites;	/* stats for verify writes */
		struct vol_gstat vs_preads;	/* stats for plex reads */
		struct vol_gstat vs_pwrites;	/* stats for plex writes */
		ulong		 vs_readfails;	/* read failures */
		ulong		 vs_writefails;	/* write failures */
		ulong		 vs_readfixes;	/* corrected read failures */
		ulong		 vs_writefixes;	/* corrected write failures */
	} v_stat;
};

struct v_stats {
	int		nvstats;	/* number of objects to get stats on */
	char		*names;		/* names of objects */
	union vol_stats	*vstats;	/* stats area for objects */
};

/*
 * Structure for enabling volume tracing
 */

typedef enum vol_tr_act {
	MIN_VOL_TR_ACT,		/* sentinel value, must be first */
	VT_SET,			/* enable volume trace mask */
	VT_CLR,			/* disable volume trace mask */
	MAX_VOL_TR_ACT		/* sentinel value, must be last */
} vtact_t;

#define	VT_USEMASK	0x80000000	/* use private mask, not system mask */

#define	VT_SETMASK	0x07		/* mask of settable trace bits */

#define	VT_CONFIG	0x01		/* trace configuration changes */
#define	VT_ERROR	0x02		/* trace I/O errors */
#define	VT_IOTRACE	0x04		/* trace I/O operations */

struct vol_tr {
	struct vol_tent {
	    struct vol_obid	vt_ob;		/* volume name */
	    long		vt_mask;	/* mask for enabling tracing */
	    vtact_t		vt_action;	/* type of operation */
	} *vt;					/* ptr to array of vt structs */
	int		vt_nvol;		/* # of entries in vt array */
};

/*
 * Structure for reading events from the volevent device
 */

struct vol_eb {
	struct volevent	*volev;	/* ptr to array of volevent structures */
	int		nvolev;	/* num of elements in volev */
	long		evnum;	/* event number to start reading from */
};

/*
 * Structure of events in the volevent device log
 */

struct volevent {
	long	vt_evnum;	/* event number */
	long	vt_type;	/* event type */
	union	vt_event {
	    struct ve_conf {		/* configuration change event */
		clock_t	vec_lbolt;	/* lbolt when event traced */
		int	vec_cmd;	/* ioctl issued */
		int	vec_rval;	/* return value for ioctl */
		int	vec_errno;	/* errno for ioctl */
		long	vec_tid;	/* transaction for ioctl */
		char	vec_name1[NAME_SZ];	/* object acted upon */
		char	vec_name2[NAME_SZ];	/* 2nd object acted upon */
	    } ve_conf;
	    struct ve_err1 {		/* I/O error specific event */
		clock_t	vee_lbolt;	/* lbolt when event traced */
		long	vee_reqid;	/* unique request ID */
		int	vee_iotype;	/* type of I/O */
		int	vee_lblkno;	/* block number in logical request */
		int	vee_blkno;	/* block number on underlying device */
		int	vee_count;	/* byte count of I/O */
		int	vee_resid;	/* residual byte count on I/O */
		int	vee_errno;	/* b_error on I/O */
		char	vee_vol[NAME_SZ];	/* volume involved */
		char	vee_plex[NAME_SZ];	/* plex involved */
		char	vee_sd[NAME_SZ];	/* subdisk involved */
		char	vee_dg[NAME_SZ];	/* disk group involved */
		char	vee_disk[NAME_SZ];	/* disk involved */
	    } ve_err1;
	    struct ve_err2 {		/* I/O error summary event */
		clock_t	vee_lbolt;	/* lbolt when event traced */
		long	vee_reqid;	/* unique request ID */
		int	vee_iotype;	/* type of I/O */
		int	vee_except;	/* exception recognized */
		int	vee_succeed;	/* successful participating plexes */
		int	vee_failed;	/* failed participating plexes */
		int	vee_nsucceed;	/* successful non-participating plexes */
		int	vee_nfailed;	/* failed non-participating plexes */
		char	vee_vol[NAME_SZ];	/* volume involved */
		char	vee_plex[NAME_SZ];	/* plex involved */
		char	vee_sd[NAME_SZ];	/* subdisk involved */
		char	vee_dg[NAME_SZ];	/* disk group involved */
		char	vee_disk[NAME_SZ];	/* disk involved */
	    } ve_err2;
	    struct ve_iotrace {		/* I/O activity trace event */
		clock_t	vio_lbolt;	/* lbolt when event traced */
		long	vio_reqid;	/* unique request ID */
		int	vio_type;	/* type of I/O */
		int	vio_lblkno;	/* block within logical request */
		int	vio_blkno;	/* start of request */
		int	vio_length;	/* length of request */
		int	vio_status;	/* status of I/O request */
		long	vio_time;	/* elapsed time for request */
		char	vio_vol[NAME_SZ];	/* volume involved */
		char	vio_plex[NAME_SZ];	/* plex involved */
		char	vio_sd[NAME_SZ];	/* subdisk involved */
		char	vio_dg[NAME_SZ];	/* disk group involved */
		char	vio_disk[NAME_SZ];	/* disk involved */
	    } ve_iotrace;
	} vt_event;
};

#define	vt_conf		vt_event.ve_conf
#define	vt_err1		vt_event.ve_err1
#define	vt_err2		vt_event.ve_err2
#define	vt_iotrace	vt_event.ve_iotrace

/*
 * I/O types for trace records
 */

#define	VIOT_READ		1	/* read operation */
#define	VIOT_WRITE		2	/* write operation */
#define	VIOT_REREAD		3	/* reread operation */
#define	VIOT_WRITEBACK		4	/* writeback operation */
#define	VIOT_ATOMIC_COPY	5	/* atomic copy operation */
#define	VIOT_PLEX_READ		6	/* plex read operation */
#define	VIOT_PLEX_WRITE		7	/* plex write operation */
#define	VIOT_VERIFY_READ	8	/* verify read operation */
#define	VIOT_VERIFY_WRITE	9	/* verify write operation */
#define VIOT_LOG		10	/* log write operation */

#endif /* _SYS_VOLTRACE_H */
