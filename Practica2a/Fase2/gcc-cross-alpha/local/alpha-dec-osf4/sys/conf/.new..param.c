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
#ifndef lint
static char	*sccsid = "@(#)$RCSfile: param.c,v $ $Revision: 4.3.61.2 $ (DEC) $Date: 1998/11/18 18:43:14 $";
#endif
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 198[7-9] Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */

#include <quota.h>
#include <confdep.h>
#include <cpus.h>
/*
 * NOTE: confdep.h MUST preceed param.h.
 *
 *	This allows overriding System V IPC default
 *	definitions from the kernel config file.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/socket.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <ufs/quota.h>
#include <sys/file.h>
#include <sys/callout.h>
#include <sys/clist.h>
#include <sys/mbuf.h>
#include <sys/kernel.h>
#include <sys/utsname.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <rt_preempt.h>
#include <rt_sched_rq.h>
#if RT_SCHED_RQ
#include <sys/rtpriocntl.h>
#include <kern/sched.h>
#endif
#include <pty.h>

/*
 * System parameter formulae.
 *
 * This file is copied into each directory where we compile
 * the kernel; it should be modified there to suit local taste
 * if necessary.
 *
 * Compiled with -DMAXUSERS=xx
 */

/*
 * On alpha, "hz", "tick", "fixtick", and "tickadj" are initialized at
 * bootup in alpha_init.c.
 */

int hz;
int tick;
int fixtick;
int tickadj;

int     maxdriftrecip = 1000;		/* This is a default which represents
					   a ridiculously poor clock which
					   drifts at a rate of 1 part in 1000,
					   most cpu clocks are good to between
					   1 part in 10000 (maxdriftrecip =
					   10000) and 2 parts in 100000
					   (maxdriftrecip = 50000). This value
					   should be established in some (clock)
					   hardware dependent module, e.g.
					   mc146818clock.c. for the PMAX */
struct utsname utsname = {
	"OSF1",
	"",
	"",
	"",
	MACHINE
};
		
#if !defined(MAXPROC)
int nproc;
#else
int nproc = MAXPROC;
#endif
	
	
int nvnode; 	/* set in vfs_cfg.c now */
int   min_free_vnodes; /* set in vfs_cfg.c now */
int   max_vnodes = MAX_VNODES; /* max vnodes is now a percentage of memory */


#if !defined(VNODE_AGE) /* vnode_age guarantees the duration in seconds.. */
#define VNODE_AGE 120   /* a free vnode will remain on the free_list..    */
#endif                  /* before it may get selected for re-cycling.     */
int vnode_age = VNODE_AGE;

#if !defined(NCACHE_VALID_TIME) /* guarantees the duration in seconds..   */
#define NCACHE_VALID_TIME 1200  /* a namecache entry will be valid..      */
#endif                          /* after which its vnode may be dealloced */
u_long ncache_valid_time = NCACHE_VALID_TIME;

/*
 * maxuprc is set from source by CHILD_MAX in sys/limits.h.  Allow it to be
 * overridden if maxuprc is set in the config file.  Future kernel code should
 * use the global int maxuprc, not MAXUPRC or CHILD_MAX.
 */
#if !defined(MAXUPRC)
int   maxuprc = CHILD_MAX;
#else
int   maxuprc = MAXUPRC;
#endif
unsigned long maxuthreads = 4 * CHILD_MAX;  /* maximum threads per user */

#if !defined(AUTONICE)
int autonice = 0;
#else
int autonice = 1;
#endif

#if !defined(BUFCACHE)
int   bufcache = 3;
#else
int   bufcache = BUFCACHE;
#endif

#if	!defined(UBCMINPERCENT)
int	ubc_minpercent = 10;
#else
int	ubc_minpercent = UBCMINPERCENT;
#endif

#if	!defined(UBCMAXPERCENT)
int	ubc_maxpercent = 100;
#else
int	ubc_maxpercent = UBCMAXPERCENT;
#endif

#if	!defined(WRITEIO_KLUSTER)
vm_size_t vm_max_wrpgio_kluster = 32*1024;
#else
vm_size_t vm_max_wrpgio_kluster = WRITEIO_KLUSTER;
#endif	

#if	!defined(READIO_KLUSTER)
vm_size_t vm_max_rdpgio_kluster = 16*1024;
#else
vm_size_t vm_max_rdpgio_kluster = READIO_KLUSTER;
#endif


#if defined(THREADMAX)
int     thread_max = THREADMAX;  /* max number of threads system-wide */
#else
int	thread_max;
#endif

#if defined(TASKMAX)
int     task_max = TASKMAX;      /* max number of tasks system-wide */
#else
int	task_max;
#endif

int	port_hash_max_num;
int	port_max_num;
int	port_reserved_max_num;
int	set_max_num;

int   maxusers = MAXUSERS;
int   sys_v_mode = SYS_V_MODE;

/*
 * RT_PREEMPT_OPT is set at config time so that preemption can be
 * turned off in a kernel which has RT_PREEMPT compiled on.
 */
#if (RT_PREEMPT && defined(RT_PREEMPT_OPT))
long	rt_preempt_opt = 1; /* preemption is enabled */
#else
long	rt_preempt_opt = 0; /* preemption is disabled */
#endif

/*
 * callout elements are dynamically allocated now.
 */
int ncallout;

/*
 * Assigned value in data/tty_pty_data.c, reference here because
 * bsd/tty_pty.c looks at it.
 */
int npty;

#if defined(NCLIST)
int	nclist = MAXCLISTS;
#else 
int	nclist;
#endif

int	create_fastlinks = 1;
int	path_num_max = 64;
int	ucred_max = 256;

/*
 *  Note: nmount_max is *not* a hard limit on the total number of mounts (nfs,
 *  	ufs, s5).  It is the number passed to zinit() when initializing the
 *  	'mount_zone' zone.  This zone is dynamically expandable.
 */
int	nmount = NMOUNT;		/* max number of ufs mounts */
int	nmount_max;

int	nchsize;	/* now set in vfs_cfg.c */
int	inohsz = 512;
int	spechsz = 64;
/*
 * nchsz overrides should be set with sysconfig using
 * stanza vfs and parameter name-cache-hash-size.  If no
 * override for vfs: name-cache-hash-size is set in 
 * /etc/sysconfigtab, a default value will be
 * calculated that scales to the name-cache-size.
 */
int	nchsz = 0;
int	bufhsz = 512;
#ifdef	multimax
int	nmbclusters;
#else
#ifndef __alpha
int     nmbclusters = NMBCLUSTERS;
#endif /* ifdef __alpha */
#endif

int ufs_blkpref_lookbehind = 8;

/*
 * The default number of per-process file descriptors is configurable.
 * The getdtablesize(2) system call should be used to obtain the
 * current limit.  open_max_soft is the default per-process limit.
 * A process can increase its soft limit up to its hard limit using 
 * setrlimit(2).  The default hard and soft limits below must be 
 * at least 64, and less than or equal to OPEN_MAX_SYSTEM in param.h.
 */

int open_max_hard = OPEN_MAX_HARD;
int open_max_soft = OPEN_MAX_SOFT;

/*
 * These have to be allocated somewhere; allocating
 * them here forces loader errors if this file is omitted
 * (if they've been externed everywhere else; hah!).
 */
struct	vnode *vnode, *vnodeNVNODE;
struct	file *file, *fileNFILE;
struct	cblock *cfree = 0;
struct	cblock *cfreelist = 0;
int	cfreecount = 0;

/*
 * These are initialized at bootstrap time
 * to values dependent on memory size
 */
struct	buf *buf;
char	*buffers;
/*
 * Declare these as initialized data so we can patch them.
 * moved here from arch/<machine>/startup.c
 */
#ifdef	NBUF
long	nbuf = NBUF;
#else
long	nbuf = 0;
#endif
#ifdef	BUFPAGES
long	bufpages = BUFPAGES;
#else
long	bufpages = 0;
#endif

struct	namecache *namecache;
struct  pid_entry *pidtab, *pidNPID;
#if	QUOTA
struct	quota *quota, *quotaNQUOTA;
struct	dquot *dquot, *dquotNDQUOT;
#endif

/*
 * Establish current and maximum values for task's
 * data and stack sizes. If maxdsiz is specified in
 * the config file, then the define comes from confdep.h,
 * otherwise the defaults in vmparam.h are used. Same
 * for maxssiz, dfldsiz, and dflssiz.
 */
#include <sys/vmparam.h>
#include <vm/vm_tune.h>

struct rlimit vm_initial_limit_stack = { DFLSSIZ, MAXSSIZ };
struct rlimit vm_initial_limit_data = { DFLDSIZ, MAXDSIZ };
struct rlimit vm_initial_limit_core = { RLIM_INFINITY, RLIM_INFINITY };
struct rlimit vm_initial_limit_rss = { DFLRSS, MAXRSS };
struct rlimit vm_initial_limit_vas = { MAXVAS, MAXVAS };

/*
 * System V IPC definitions. Default values come from param.h
 * or user can override the defaults in the kernel config file
 * (in which case values come from confdep.h).
 */

/* messages */
struct msginfo  msginfo = {             /* message parameters */
                           MSGMAX,
                           MSGMNB,
                           MSGMNI,
                           MSGTQL
};

/* semaphores */
struct seminfo  seminfo = {             /* semaphore information structure */
                           SEMMNI,
                           SEMMSL,
                           SEMOPM,
                           SEMUME,
                           SEMVMX,
                           SEMAEM
};

/* shared memory */
struct  shminfo shminfo = {     /* shared memory info structure */
                SHMMAX,
                SHMMIN,
                SHMMNI,
                SHMSEG
};


/* 
 * vm tune parameters 
 * If any of the vm_tune parameters are defined in
 * the config file, then the define comes from
 * confdep.h, otherwise the defaults in vm_tune.h
 * are used.
 */

struct vm_tune vm_tune = {
		COWFAULTS,		/* Copy point */
		MAPENTRIES,		/* Maximum map entries */
		MAXVAS,			/* Maximum VAS for user map */
		MAXWIRE,		/* Maximum wired memory */
		HEAPPERCENT,		/* Percent of memory for heap */
		ANONKLSHIFT,		/* 128K anon page shift */
		ANONKLPAGES,		/* Use system default anon_klpages */
		VPAGEMAX,		/* Maximum vpage for umap */
		SEGMENTATION,		/* Segmentation on or off */
		UBCPAGESTEAL,		/* Steal from vnode clean list */
		UBCDIRTYPERCENT,	/* Percent dirty UBC buffers */
		UBCSEQSTARTPERCENT,	/* Start when ubc is this percent */
		UBCSEQPERCENT,		/* Percent sequential allocates */
		CSUBMAPSIZE,		/* Size of kernel copy map */
		UBCBUFFERS,		/* Maximum UBC buffers */
		SYNCSWAPBUFFERS,	/* Maximum synchronous swap buffers */
		ASYNCSWAPBUFFERS,	/* Maximum asynchronous swap buffers */
		CLUSTERMAP,		/* ckluster dup map size*/
		CLUSTERSIZE,            /* max cluster bp size */
		ZONE_SIZE,              /* zone_map size */
		KENTRY_ZONE_SIZE,       /* kentry_map size */
		SYSWIREDPERCENT,	/* max pct of wired memory system-wide*/
		INSWAPPEDMIN		/* minimum inswapped ticks */
		
};

/*
 * This is the size in bytes of the kernel memory area that is available
 * to the SVR4 versions of kmem_alloc() and kmem_zalloc().  See ddi_init()
 * for details.
 */
int ddi_map_size = 0x10000;

#if RT_SCHED_RQ
/*
 * The quantum table, indexed by SVR4 RT priority.  Note that this table must
 * be editted when the number of RT priorities change because of changes in
 * SVR4_RT_MAX and/or SVR4_RT_MIN.  The priorities are given as MACH
 * priorities, and (SVR4_RT_MAX < SVR4_RT_MIN) and (SVR4_RT_MIN <=
 * BASEPRI_HIGHEST-1).
 */

#define SVR4_RT_MAX	(0)
#define SVR4_RT_MIN	(BASEPRI_HIGHEST-1)

int svr4_rt_max	= SVR4_RT_MAX;
int svr4_rt_min	= SVR4_RT_MIN;

struct rt_default_quantum rt_default_quantum[SVR4_RT_MIN - SVR4_RT_MAX + 1] =
{
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
  { 1, 0 },
};
#endif	/* RT_SCHED_RQ */
/*
 * provide configurable size for the basic dma window. This is being
 * added for reflective memory (Cluster Memory Channel), but could be
 * useful for other, dma-intensive devices. If the variable defined
 * here is zero, the normal DMA window sizing code in the appropriate
 * platform (kn...c) file executes. If this is non-zero (i.e. has been
 * set by a sysconfigdb call or an entry in the /etc/sysconfigtab
 * file, this is the size of the window (* 1048576), then rounded up
 * to the next reasonable megabyte boundary. So, to force a 512-MB 
 * DMA window, this entry would be 512. To force a gigabyte window, 
 * this entry would be 1024. NOTE that this is *not* something that
 * can change dynamically, while the system is running. Setting the
 * DMA window only happens _very_ early in the bootup sequence, so
 * changing this variable requires a reboot for it to take effect.
 *     -bill grava
 */
int basic_dma_window_size = 0;	/* init to the default platform logic */

/*
 * SCSI CAM subsystem CCB pool parameters.
 * Moved here from cam_data.c so they can
 * be configured via /etc/sysconfigtab.
 */
#include <io/common/iotypes.h>

U32 cam_ccb_pool_size = 200;
U32 cam_ccb_low_water = 100;
U32 cam_ccb_increment = 50;
/*U32 cam_ccb_high_water = 1000;	NOT USED */

/*
 * Enable/Disable use of EV56 byte/word IO maps.
 * non-zero = auto enable/disable; zero = force disable,
 * to disable byte/word maps:
 *    >>> b -fl i; vmunix ev56_bw_io_maps=0
 * or edit param.c and rebuild kernel,
 * or dbx /vmunix; patch ev56_bw_io_maps=0.
 */
long	ev56_bw_io_maps = 1;
