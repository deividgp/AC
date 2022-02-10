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
 * @(#)$RCSfile: sar.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1995/03/22 16:15:09 $
 */

#ifndef _SVR4_SAR_H_
#define _SVR4_SAR_H_

struct _sar_data {
	/* for sar -c support, and other system stuff */
	long _ts_devintr;
	long _ts_passrel;
	long _ts_syscalls;
	long _ts_sysread;
	long _ts_syswrite;
	long _ts_sysexec;
	long _ts_sysfork;
	long _ts_sysvfork;
	long _ts_readch;
	long _ts_writech;
	long _ts_tasksw;
	long _ts_threadsw;
	long _ts_xcpusched;

	/* for sar -a support */
	long _tf_iget;
	long _tf_namei;
	long _tf_dirblk;

	/* for sar -b support */
	long _ts_bread;
	long _ts_bwrite;
	long _ts_lread;
	long _ts_lwrite;
	long _ts_phread;
	long _ts_phwrite;

	/* for sar -k support */
	long _sar_kmem_fail;

	/* for sar -v support */
	long _tbl_proc_ov;
	long _tbl_inod_ov;
	long _tbl_file_ov;

	long _pg_v_pgpgin;
	long _pg_v_sftlock;
	long _pg_v_pgout;
	long _pg_v_dfree;
	long _pg_v_scan;
	long _pg_v_s5ifp;
};

/*
 * Round up size to ensure the per-cpu structs won't lie in same cache block.
 */
#define _SAR_MASK	(63)
#define _SAR_SIZE	((sizeof(struct _sar_data) + _SAR_MASK) & ~_SAR_MASK)

struct sar_data {
	union {
		struct _sar_data _sardata;
		char _sar_pad[_SAR_SIZE];
	} _sarfields;
};

#define ts_devintr	_sarfields._sardata._ts_devintr
#define ts_passrel	_sarfields._sardata._ts_passrel
#define ts_syscalls	_sarfields._sardata._ts_syscalls
#define ts_sysexec	_sarfields._sardata._ts_sysexec
#define ts_sysfork	_sarfields._sardata._ts_sysfork
#define ts_sysvfork	_sarfields._sardata._ts_sysvfork
#define ts_sysread	_sarfields._sardata._ts_sysread
#define ts_syswrite	_sarfields._sardata._ts_syswrite
#define ts_readch	_sarfields._sardata._ts_readch
#define ts_writech	_sarfields._sardata._ts_writech
#define ts_tasksw	_sarfields._sardata._ts_tasksw
#define ts_threadsw	_sarfields._sardata._ts_threadsw
#define ts_xcpusched	_sarfields._sardata._ts_xcpusched

#define tf_iget		_sarfields._sardata._tf_iget
#define tf_namei	_sarfields._sardata._tf_namei
#define tf_dirblk	_sarfields._sardata._tf_dirblk

#define ts_bread	_sarfields._sardata._ts_bread
#define ts_bwrite	_sarfields._sardata._ts_bwrite
#define ts_lread	_sarfields._sardata._ts_lread
#define ts_lwrite	_sarfields._sardata._ts_lwrite
#define ts_phread	_sarfields._sardata._ts_phread
#define ts_phwrite	_sarfields._sardata._ts_phwrite

#define sar_kmem_fail	_sarfields._sardata._sar_kmem_fail

#define tbl_proc_ov	_sarfields._sardata._tbl_proc_ov
#define tbl_inod_ov	_sarfields._sardata._tbl_inod_ov
#define tbl_file_ov	_sarfields._sardata._tbl_file_ov

#define pg_v_pgpgin	_sarfields._sardata._pg_v_pgpgin
#define pg_v_sftlock	_sarfields._sardata._pg_v_sftlock
#define pg_v_pgout	_sarfields._sardata._pg_v_pgout
#define pg_v_dfree	_sarfields._sardata._pg_v_dfree
#define pg_v_scan	_sarfields._sardata._pg_v_scan
#define pg_v_s5ifp	_sarfields._sardata._pg_v_s5ifp

#ifdef	_KERNEL

#include <cpus.h>
#include <rt_preempt.h>
#include <machine/cpu.h>

extern struct sar_data *sar_counters;

/*
 * sar_update: adds val to the sarcntr entry for this cpu.
 * If toggle_preempt is true, preemption is disabled for the updates.
 * Values for toggle_preempt are known at compile time, so the tests
 * are removed.
 */
#define sar_update(sarcntr, val, toggle_preempt)			\
MACRO_BEGIN								\
	if (toggle_preempt) {						\
		(sar_counters + cpu_number_locked())->sarcntr += (val);	\
		cpu_number_unlock();					\
	} else {							\
		(sar_counters + cpu_number())->sarcntr += (val);	\
	}								\
MACRO_END

/* for sar -q support */
extern long sar_runocc, sar_runqueue;

#endif /* _KERNEL */
#endif /* _SVR4_SAR_H_ */
