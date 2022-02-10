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
 * @(#)$RCSfile: lockdev.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1997/01/14 19:23:32 $
 */

#ifndef _LOCKDEV_H_
#define _LOCKDEV_H_
#include <sys/types.h>
#include <sys/ioctl.h>
#include <kern/lock.h>

#define LOCKDEV_START		_IO('L', 0)
#define LOCKDEV_STOP		_IO('L', 1)
#define LOCKDEV_NUM_CLASSES	_IOR('L',2, unsigned int)
#define LOCKDEV_STAT_UNITS 	_IOR('L',3, long)
#define LOCKDEV_CLEAR_STATS	_IO('L', 4)
#define LOCKDEV_LOCKMODE	_IOR('L',5, unsigned int)
#define LOCKDEV_RT_PREEMPT	_IOR('L',6, unsigned int)
#define LOCKDEV_TRACE_SET	_IOW('L',7, long)
#define LOCKDEV_TRACE_READ	_IOW('L',8, long)
#define LOCKDEV_TRACE_CLEAR	_IO('L', 9)
#define LOCKDEV_TRACE_SET_2_LEVEL _IO('L', 10)
#define LOCKDEV_TRACE_CLEAR_2_LEVEL _IO('L', 11)

#define	LOCKDEV_NAMEBUFLEN 80

struct lock_buf {
	char l_name[LOCKDEV_NAMEBUFLEN];
	int l_count;
	int l_flgspl;
	struct lockstats l_stat[1];	
};

struct lock_pc_hist {
	char *pc;
	char *ra;
	long count;
	long miss;
	long spare1;
	long spare2;
	long spare3;
	long ra_stack_offset;
};

#define LOCK_PC_ENTRIES	256

#ifdef _KERNEL
#include <sys/uio.h>

int lockdev_open(dev_t, int);
int lockdev_ioctl(dev_t, unsigned int, caddr_t, int);
int lockdev_read(dev_t, struct uio *);
int lockdev_close( dev_t, int , int);
long lock_pc_hist_trace(caddr_t,int, caddr_t,long);
void lockdev_init(void);
#endif /* _KERNEL */

#endif /* _LOCKDEV_H_ */
