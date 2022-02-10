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
 *	@(#)$RCSfile: conf.h,v $ $Revision: 4.4.23.2 $ (DEC) $Date: 1995/11/14 19:00:42 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * conf.h
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_CONF_H_
#define _SYS_CONF_H_

#ifdef	_KERNEL
#include <sys/unix_defs.h>
#endif
#include <sys/types.h>

/*
 * Declaration of block device
 * switch. Each entry (row) is
 * the only link between the
 * main unix code and the driver.
 * The initialization of the

 * device switches is in the
 * file conf.c.
 */

struct bdevsw
{
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_strategy)();
	int	(*d_dump)();
	int	(*d_psize)();
	int	d_flags;
	int	(*d_ioctl)();
	int 	d_funnel;	/* serial code compatibility */
};

#ifdef	_KERNEL
extern struct	bdevsw bdevsw[];
extern int	nblkdev;			/* bdevsw size */
#endif

/* forward declaration required for C++ */
#ifdef __cplusplus
struct tty;
#endif

struct cdevsw
{
	int	(*d_open)();
	int	(*d_close)();
	int	(*d_read)();
	int	(*d_write)();
	int	(*d_ioctl)();
	int	(*d_stop)();
	int	(*d_reset)();
	struct tty *d_ttys;
	int	(*d_select)();
	int	(*d_mmap)();
	int 	d_funnel;	/* serial code compatibility */
	int	(*d_segmap)();		/* xxx_segmap() entry point */
	int	d_flags;		/* if (C_DDIDKI), driver follows
					   SVR4 DDI/DKI interfaces*/
};

/*
 * Flag definitions for d_flags field of cdevsw
 */
#define C_DDIDKI	0x10000000

/*
 * Definitions for d_funnel field of devsw
 */
#define DEV_FUNNEL_NULL  NULL
#define DEV_FUNNEL	 1 


#ifdef	_KERNEL
extern struct	cdevsw cdevsw[];
extern int	nchrdev;			/* cdevsw size */
#endif

/*
 * Declaration of a device switch entry.  This entry is the only link
 * between the main unix code and the driver.  Each entry can be used
 * for access to the driver by both block and character device special
 * files (dev_t values).  If the driver doesn't support access by both
 * block and character, then the driver must perform the appropriate
 * check in the open routine and return an error for the devices it
 * does not support.
 */

struct dsent
{
  int (*d_open)();
  int (*d_close)();
  int (*d_strategy)();
  int (*d_read)();
  int (*d_write)();
  int (*d_ioctl)();
  int (*d_dump)();
  int (*d_psize)();
  int (*d_stop)();
  int (*d_reset)();
  int (*d_select)();
  int (*d_mmap)();
  int (*d_segmap)();
  struct tty *d_ttys;
  int d_funnel;
  int d_bflags;
  int d_cflags;
};

/*
 * tty line control switch.
 */

struct linesw
{
	int	(*l_open)();
	int	(*l_close)();
	int	(*l_read)();
	int	(*l_write)();
	int	(*l_ioctl)();
	int	(*l_rint)();
	int	(*l_rend)();
	int	(*l_meta)();
	int	(*l_start)();
	int	(*l_modem)();
};

/*
 * Swap device information
 */
struct swdevt
{
        dev_t   sw_dev;
        int     sw_freed;
        int     sw_nblks;
        int     sw_type;
        int	*sw_gnodeptr;       /* gnode pointer */
        int	(*sw_strat)( /* bp */ );
        int	sw_priority;
	int	sw_nio;
 };
#define sw_gptr                 sw_gnodeptr
#define sw_pri                  sw_priority

#ifdef	_KERNEL
extern struct	linesw linesw[];
#endif

#ifdef	_KERNEL
#include <ser_compat.h>
#include <rt_preempt.h>
#include <kern/lock.h>
#include <kern/parallel.h>

/*
 * Character and Block Device Switch Locking definition.
 *
 * A device switch lock guards a particular entry in a
 * device switch table; these locks are used by the
 * driver open routines.  Note that these locks have
 * nothing to do with synchronizing the drivers themselves;
 * they guard the use of entries in the devsw arrays.
 */
typedef struct dswlock {
        lock_data_t     dsw_lock;               /* devsw entry r/w lock */
        int             dsw_flags;              /* devsw entry status flags */
} dswlock_t;

/*
 * Parallel device switch lock arrays, one entry
 * for each entry in cdevsw and bdevsw.
 */
extern dswlock_t cdevlock[];                    /* cdevsw lock structure */
extern dswlock_t bdevlock[];                    /* bdevsw lock structure */

extern struct lockinfo *bdev_lockinfo;
extern struct lockinfo *cdev_lockinfo;

						/* dsw flag defines */
#define DSW_INUSE	0x0001
						/* Lock macros for open() */
#define CDEVSW_READ_LOCK(maj)		lock_read(&(cdevlock[maj].dsw_lock))
#define CDEVSW_WRITE_LOCK(maj)		lock_write(&(cdevlock[maj].dsw_lock))
#define CDEVSW_READ_UNLOCK(maj)		lock_done(&(cdevlock[maj].dsw_lock))
#define CDEVSW_WRITE_UNLOCK(maj)	lock_done(&(cdevlock[maj].dsw_lock))
#define BDEVSW_READ_LOCK(maj)		lock_read(&(bdevlock[maj].dsw_lock))
#define BDEVSW_WRITE_LOCK(maj)		lock_write(&(bdevlock[maj].dsw_lock))
#define BDEVSW_WRITE_UNLOCK(maj)	lock_done(&(bdevlock[maj].dsw_lock))
#define BDEVSW_READ_UNLOCK(maj)		lock_done(&(bdevlock[maj].dsw_lock))
#define CDEVSW_LOCK_INIT(maj)		\
		lock_setup(&(cdevlock[maj].dsw_lock),cdev_lockinfo, TRUE)
#define BDEVSW_LOCK_INIT(maj)		\
		lock_setup(&(bdevlock[maj].dsw_lock),bdev_lockinfo, TRUE)

#ifdef __STDC__
#define PASTE(a,b) a##b
#else
#define PASTE(a,b) a/**/b
#endif

/*
 * The following macros hide the use of funneling from most kernel code.
 */

#if SER_COMPAT || RT_PREEMPT
#define	DEVSW_FUNNEL(sw,maj)	(PASTE(sw,devsw)[(maj)].d_funnel)
#else
#define	DEVSW_FUNNEL(sw,maj)	(0)
#endif

#define	_DVC_(sw,f,maj,args,ret)					\
MACRO_BEGIN								\
	if (!DEVSW_FUNNEL(sw,maj)) {					\
		(ret) = (*PASTE(sw,devsw)[(maj)].PASTE(d_,f))args;	\
	} else {							\
		unix_master();						\
		(ret) = (*PASTE(sw,devsw)[(maj)].PASTE(d_,f))args;	\
		unix_release();						\
	}								\
MACRO_END

#define	_DVC_OPT_(sw,f,maj,args,ret)					\
MACRO_BEGIN								\
	if (PASTE(sw,devsw)[(maj)].PASTE(d_,f)) {			\
		if (!DEVSW_FUNNEL(sw,maj)) {				\
			(ret) = (*PASTE(sw,devsw)[(maj)].PASTE(d_,f))args;\
		} else {						\
			unix_master();					\
			(ret) = (*PASTE(sw,devsw)[(maj)].PASTE(d_,f))args;\
			unix_release();					\
		}							\
	} else {							\
  		(ret) = -1;						\
	}								\
MACRO_END

/*
 * These macros were developed to have a single interface for the cdevsw
 * and the bdevsw in code, but easily adding funneling.
 *
 * They are all called with 'similar' arguments:
 *	(major device #, arg1, arg2, ..., result)
 * where:
 *	result will be set to the return value of the b/cdevsw call.
 *	arg[12...] is the list of arguments to be passed into the call.
 *
 * Special-case open macros to use devsw locking to synchronize with 
 * dynamic installation of drivers.
 */

#define	BDEVSW_OPEN(maj,dev,mode,flag,ret,cred,priv)			\
MACRO_BEGIN								\
	BDEVSW_READ_LOCK(maj);						\
	_DVC_(b,open,maj,(dev,mode,flag,cred,priv),ret);		\
	BDEVSW_READ_UNLOCK(maj);					\
MACRO_END
#define	BDEVSW_CLOSE(m,d,f,f2,r,c,p)	_DVC_(b,close,m,(d,f,f2,c,p),r)
#define	BDEVSW_STRATEGY(m,bp,r)		_DVC_(b,strategy,m,(bp),r)
#define	BDEVSW_DUMP(m,d,lo,s,bl,f,r)	_DVC_(b,dump,m,(d,lo,s,bl,f),r)
#define	BDEVSW_PSIZE(m,d,r)		_DVC_OPT_(b,psize,m,(d),r)
#define	BDEVSW_IOCTL(m,d,c,d1,f,r,e,p,rv) \
					_DVC_(b,ioctl,m,(d,c,d1,f,e,p,rv),r)
#define	BDEVSW_FLAGS(m,r)		(r) = bdevsw[(m)].d_flags

/*
 * In OSF/1, a pointer to a ucred block is passed all the way through
 * to all the spec_xxx() functions, but not to the device specific
 * entry points.  This pointer must be passed to the open, close, read,
 * write and ioctl entry points of block drivers that follow the DDI/DKI
 * interfaces.
 */

#define	BDEVSW_DDI_OPEN(maj,dev,mode,flag,up,ret)			\
MACRO_BEGIN								\
	BDEVSW_READ_LOCK(maj);						\
	_DVC_(b,open,maj,(&dev,mode,flag,up),ret);			\
	BDEVSW_READ_UNLOCK(maj);					\
MACRO_END
#define	BDEVSW_DDI_CLOSE(m,d,f,f2,up,r)	_DVC_(b,close,m,(d,f,f2,up),r)
#define	BDEVSW_DDI_IOCTL(m,d,c,d1,f,up,rp,r) \
					_DVC_(b,ioctl,m,(d,c,d1,f,up,rp),r)

#define	CDEVSW_OPEN(maj,dev,mode,flag,newdev,ret,cred,priv)		\
MACRO_BEGIN								\
	CDEVSW_READ_LOCK(maj);						\
	_DVC_(c,open,maj,(dev,mode,flag,newdev,cred,priv),ret);		\
	CDEVSW_READ_UNLOCK(maj);					\
MACRO_END
#define	CDEVSW_CLOSE(m,d,f,mo,r,cr,p)	_DVC_(c,close,m,(d,f,mo,cr,p),r)
#define	CDEVSW_READ(m,d,u,f,r,p)	_DVC_(c,read,m,(d,u,f,p),r)
#define	CDEVSW_WRITE(m,d,u,f,r,p)	_DVC_(c,write,m,(d,u,f,p),r)
#define	CDEVSW_IOCTL(m,d,com,t,f,r,cr,p,rv) \
					_DVC_(c,ioctl,m,(d,com,t,f,cr,p,rv),r)
#define	CDEVSW_STOP(m,t,w,r)		_DVC_(c,stop,m,(t,w),r)
#define	CDEVSW_RESET(m,i,r)		_DVC_(c,reset,m,(i),r)
#define	CDEVSW_SELECT(m,d,e,re,s,r,p)	_DVC_(c,select,m,(d,e,re,s,p),r)
#define	CDEVSW_MMAP(m,d,o,p,r)		_DVC_(c,mmap,m,(d,o,p),r)
#define	CDEVSW_FLAGS(maj,r)		(r) = cdevsw[(maj)].d_flags
#define	CDEVSW_TTYS(maj,min,r)		(r) = cdevsw[(maj)].d_ttys + (min)

/*
 * In OSF/1, a pointer to a ucred block is passed all the way through
 * to all the spec_xxx() functions, but not to the device specific
 * entry points.  This pointer must be passed to the open, close, read,
 * write, ioctl and segmap entry points of character drivers that follow
 * the DDI/DKI interfaces.
 */

#define	CDEVSW_DDI_OPEN(maj,dev,mode,flag,up,ret)		        \
MACRO_BEGIN								\
	CDEVSW_READ_LOCK(maj);						\
	_DVC_(c,open,maj,(&dev,mode,flag,up),ret);			\
	CDEVSW_READ_UNLOCK(maj);					\
MACRO_END
#define	CDEVSW_DDI_CLOSE(m,d,f,mo,up,r)	_DVC_(c,close,m,(d,f,mo,up),r)
#define	CDEVSW_DDI_READ(m,d,u,up,r)	_DVC_(c,read,m,(d,u,up),r)
#define	CDEVSW_DDI_WRITE(m,d,u,up,r)	_DVC_(c,write,m,(d,u,up),r)
#define	CDEVSW_DDI_IOCTL(m,d,com,t,f,up,rp,r) \
					_DVC_(c,ioctl,m,(d,com,t,f,up,rp),r)
#define CDEVSW_DDI_SELECT(m,d,ev,a,rv,up,r) \
					_DVC_(c,select,m,(d,ev,a,rv,up),r)
#define	CDEVSW_SEGMAP(m,d,o,as,ad,l,p,mp,f,up,r) \
				_DVC_(c,segmap,m,(d,o,as,ad,l,p,mp,f,up),r)
#endif	/* _KERNEL */

/* size of ascii strings within the assign_table */
#define	ANAMELEN	80

/* struct that is returned to caller as a result of a getsyscall with op =
 * GSI_STATIC_NXT or GSI_STATIC_DEF
 */
typedef	struct	aentry {
	char	config_name[ANAMELEN];
	char	bc[2];
	int	mode;
	char	username[ANAMELEN];
	uid_t	user;
	char	groupname[ANAMELEN];
	gid_t	group;
	char	dirname[ANAMELEN];
	int	ae_major;
	int	ae_minor;
	char	dev_name[ANAMELEN];
} Assign_entry;

/* struct of assign table as it is really stored in conf.c */
typedef struct atable {
	char	config_name[ANAMELEN];
	char	bc[2];
	int     mode;
	char    username[ANAMELEN];
	uid_t   user;
	char    groupname[ANAMELEN];
	gid_t   group;
	char	dirname[ANAMELEN];
	int	at_major;
	int	*at_minor;
	char	*dev_name;
} Assign_table;

#endif	/* _SYS_CONF_H_ */
