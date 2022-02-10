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
 *	@(#)$RCSfile: dk.h,v $ $Revision: 4.3.19.3 $ (DEC) $Date: 1998/10/02 15:46:05 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_DK_H_
#define _SYS_DK_H_

/* dk.h
 *
 * Modification History
 *
 * 20-Nov-91	Tom Tierney
 *	Modified DK_NDRIVE to support up to 256 disk units.
 *
 */ 
 
/*
 * Instrumentation
 */

/* need to match defines in mach/machine.h CPU_STATE_* */
#define CPUSTATES	5
#define CP_USER		0
#define CP_NICE		1
#define CP_SYS		2
#define CP_IDLE		3
#define CP_WAIT		4

#define DK_NDRIVE	256	

#ifdef	KERNEL
extern int	dk_ndrive;
extern int	dk_busy;
extern long	dk_time[DK_NDRIVE];
extern long	dk_seek[DK_NDRIVE];
extern long	dk_xfer[DK_NDRIVE];
extern long	dk_wds[DK_NDRIVE];
extern long	dk_wpms[DK_NDRIVE];

/*******SAR STATS******/
extern long	dk_initial_busy[];
extern long	dk_time_dev_busy_serv[];
extern long	dk_ref_cnt[];
extern long	dk_avque[];
extern char *   (*dk_pf_info[])( int dkn, int *unit );
extern int      PerfInit( struct device *device, char *(*pf_info)(int dkn, int *unit) );

/*
 * GET_NOW_TIME returns current time in usecs.
 * It uses external (struct timeval)time instead of a subroutine call.
 * !NOTE! Actual granularity is >> usec
 */
#define GET_NOW_TIME(t, t_usec)			\
{						\
extern struct timeval time;			\
    TIME_READ (t);				\
    t_usec = t.tv_sec * 1000000L + t.tv_usec;	\
}

#define CAM_INITIAL_STATS(now_usec, ds)					\
	if (ds != (DISK_SPECIFIC *) NULL &&				\
	(ds->ds_flags & DS_ONLINE)) {					\
		int	index = ds->ds_dkn;				\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index]++ == 0) {			\
				dk_initial_busy[index] = now_usec;	\
			}						\
									\
			dk_avque[index]++;				\
		}							\
	}

#define FD_INITIAL_STATS(now_usec, fd)					\
	if (fd != (struct fd_class *) NULL) {				\
		struct	device *devp = fd->fd_devp;			\
									\
		int	index = (int) devp->perf;			\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index]++ == 0) {			\
				dk_initial_busy[index]			\
				=					\
				now_usec;				\
			}						\
									\
			dk_avque[index]++;				\
		}							\
	}

#define MSCP_INITIAL_STATS(now_usec, devp)				\
	if (devp != (struct device *) NULL) {				\
		int	index = (int) devp->perf;			\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index]++ == 0) {			\
				dk_initial_busy[index] = now_usec;	\
			}						\
									\
			dk_avque[index]++;				\
		}							\
	}

#define RE_INITIAL_STATS(now_usec, rsp)					\
	if (rsp != (RE_SPECIFIC *) NULL) {				\
		int	index = (int) rsp->rs_dkn;			\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index]++ == 0) {			\
				dk_initial_busy[index] = now_usec;	\
			}						\
									\
			dk_avque[index]++;				\
		}							\
	}

#define I2O_BS_INITIAL_STATS(now_usec, bs_softc)			\
	if (bs_softc != (I2O_BS_SOFTC *) NULL) {			\
		int	index = (int) bs_softc->dkn_num;		\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index]++ == 0) {			\
				dk_initial_busy[index] = now_usec;	\
			}						\
									\
			dk_avque[index]++;				\
		}							\
	}

#define CAM_COMPLETE_STATS(now, now_usec, initial_busy, ds)		\
	if (ds != (DISK_SPECIFIC *) NULL &&				\
	(ds->ds_flags & DS_ONLINE)) {					\
		int	index = ds->ds_dkn;				\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index] > 0L) {			\
				GET_NOW_TIME(now, now_usec)		\
									\
				initial_busy = dk_initial_busy[index];	\
				dk_time_dev_busy_serv[index]		\
				+=					\
				now_usec - initial_busy;		\
									\
				if (--dk_ref_cnt[index] > 0L) {		\
					dk_initial_busy[index] =	\
					now_usec;			\
				}					\
									\
				dk_avque[index]--;			\
			}						\
		}							\
	}

#define FD_COMPLETE_STATS(now, now_usec, initial_busy, devp)		\
   	if (devp != (struct device *) NULL) {				\
		int	index = (int) devp->perf;			\
									\
		if (index != -1) {					\
			dk_xfer[index]++;				\
			dk_wds[index] += scp->cur_bp->b_bcount >> 6;	\
									\
			if (dk_ref_cnt[index] >= 0L) {			\
				GET_NOW_TIME(now, now_usec)		\
									\
				initial_busy = 				\
				dk_initial_busy[index];			\
				dk_time_dev_busy_serv[index]		\
				+=					\
				now_usec - initial_busy;		\
									\
				if (--dk_ref_cnt[index] > 0L) {		\
					dk_initial_busy[index]		\
				=					\
				now_usec;				\
				}					\
									\
				dk_avque[index]--;			\
			}						\
		}							\
	}

#define MSCP_COMPLETE_STATS(now, now_usec, initial_busy, devp)		\
        if (devp != (struct device *) NULL) {				\
		int	index = (int) devp->perf;			\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index] > 0L) {			\
				GET_NOW_TIME(now, now_usec)		\
									\
				initial_busy =				\
				dk_initial_busy[index];			\
				dk_time_dev_busy_serv[index]		\
				+=					\
				now_usec - initial_busy;		\
									\
				if (--dk_ref_cnt[index] > 0L) {		\
					dk_initial_busy[index]		\
				=					\
				now_usec;				\
				}					\
									\
				dk_avque[index]--;			\
			}						\
		}							\
        }

#define RE_COMPLETE_STATS(now, now_usec, initial_busy, rsp)		\
	if (rsp != (RE_SPECIFIC *) NULL) {				\
		int	index = rsp->rs_dkn;				\
									\
		if (index != -1) {					\
			GET_NOW_TIME(now, now_usec)			\
									\
			dk_xfer[index]++;				\
			dk_wds[index] += xfer_count >> 6;		\
									\
			initial_busy =					\
			dk_initial_busy[index];				\
			dk_time_dev_busy_serv[index]			\
			+=						\
			now_usec - initial_busy;			\
									\
			if (--dk_ref_cnt[index] > 0L) {			\
				dk_initial_busy[index] = now_usec;	\
			}						\
									\
			dk_avque[index]--;				\
		}							\
	}

#define I2O_BS_COMPLETE_STATS(now, now_usec, initial_busy, bs_softc)	\
        if (bs_softc != (I2O_BS_SOFTC *) NULL) {			\
		int	index = (int) bs_softc->dkn_num;		\
									\
		if (index != -1) {					\
			if (dk_ref_cnt[index] > 0L) {			\
				GET_NOW_TIME(now, now_usec)		\
									\
				initial_busy =				\
				dk_initial_busy[index];			\
				dk_time_dev_busy_serv[index]		\
				+=					\
				now_usec - initial_busy;		\
									\
				if (--dk_ref_cnt[index] > 0L) {		\
					dk_initial_busy[index]		\
				=					\
				now_usec;				\
				}					\
									\
				dk_avque[index]--;			\
			}						\
		}							\
        }
/*******SAR STATS******/

extern long	tk_nin;
extern long	tk_nout;
extern int      tk_cancc;
extern int      tk_rawcc;

#endif	/* KERNEL */
#endif	/* _SYS_DK_H_ */
