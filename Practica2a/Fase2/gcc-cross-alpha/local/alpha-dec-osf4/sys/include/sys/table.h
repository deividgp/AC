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
 *	@(#)$RCSfile: table.h,v $ $Revision: 4.2.33.2 $ (DEC) $Date: 1998/05/12 14:21:16 $
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
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef	_SYS_TABLE_H_
#define _SYS_TABLE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#include <mach/vm_prot.h>
#include <net/if.h>
#include <netinet/in.h>

#define TBL_TTYLOC		0	/* index by device number */
#define TBL_U_TTYD		1	/* index by process ID */
#define TBL_UAREA		2	/* index by process ID */
#define TBL_LOADAVG		3	/* (no index) */
#define TBL_INCLUDE_VERSION	4	/* (no index) */
#define TBL_FSPARAM		5	/* index by device number */
#define TBL_ARGUMENTS		6	/* index by process ID */
#define TBL_MAXUPRC		7	/* index by process ID */
#define TBL_AID			8	/* index by process ID */
#define TBL_MODES		9	/* index by process ID */
#define TBL_PROCINFO		10	/* index by proc table slot */
#define TBL_ENVIRONMENT		11	/* index by process ID */
#define TBL_SYSINFO		12	/* (no index) */
#define TBL_DKINFO		13	/* index by disk */
#define TBL_TTYINFO		14	/* (no index) */
#define TBL_MSGDS		15	/* index by array index */
#define TBL_SEMDS		16	/* index by array index */
#define TBL_SHMDS		17	/* index by array index */
#define TBL_MSGINFO		18	/* index by structure element */
#define TBL_SEMINFO		19	/* index by structure element */
#define TBL_SHMINFO		20	/* index by structure element */
#define TBL_INTR		21	/* (no index) */
#define TBL_SWAPINFO		22	/* index by vm_swap element */
#define TBL_SCALLS      	23      /* system call info table (no index) */
#define TBL_FILEINFO    	24      /* file access status (no index) */
#define TBL_TBLSTATS    	25      /* system tables status (no index) */
#define TBL_RUNQ        	26      /* run queue status (no index) */
#define TBL_BUFFER      	27      /* buffer activity (no index) */
#define TBL_KMEM      		28      /* kernel memory activity (no index) */
#define TBL_PAGING      	29      /* paging activity (no index) */
#define TBL_MALLOCT             30      /* same as TBL_MALLOCTYPES */
#define TBL_MAPINFO		31	/* process address map */
#define TBL_MALLOCBUCKETS	32	/* get malloc allocator kmembuckets */
#define TBL_MALLOCTYPES		33	/* get malloc allocator kmemtypes */
#define TBL_MALLOCNAMES		34	/* get malloc memory type names */
#define TBL_KNLIST		35	/* get kernel namelist table */
#define TBL_NETINFO             36      /* get netisr info */
#define TBL_MALLOCLEAK          37      /* get malloc leak info */
#define TBL_MALLOCLEAKCOUNT     38      /* get malloc leak count */
#define TBL_MALLOCNTYPES	39	/* get number of malloc types - M_LAST*/
#define TBL_MALLOCNBUCKETS      40      /* get number of malloc buckets*/
#define TBL_PMEMSTATS      	41      /* physical memory stats */
#define TBL_PMEMCLUSTERTYPE    	42      /* physical memory cluster type */
#define TBL_PMEMUSETYPE      	43      /* physical memory use type */
#define TBL_PMEMUSAGE      	44      /* physical memory usage */
#define TBL_PMEMCLUSTERS      	45      /* physical memory clusters */
#define TBL_VMSTATS      	46      /* vmstat */
#define TBL_MALLOCMSTATS      	47      /* malloc */
#define	TBL_MACHINE_SLOT	48	/* machine slot */

/* ======================== QAR30285 ================================
                SVE Multiprocessor Version of Above
   ================================================================== */

#define     TBL_SYSINFO_MP      49
#define     TBL_BUFFER_MP       50
#define     TBL_SCALLS_MP       51
#define     TBL_FILEINFO_MP     52
#define     TBL_PAGING_MP       53
#define     TBL_INTR_MP         54

#define     TBL_TCPCONN         55      /* set(delteTCB) tcp conn state */

/* ======================== QAR30285 ================================ */

#define	TBL_UIDINFO		56	/* get uid_max; ignore arguments */
					/* except nel (== 1) */
#define	TBL_PROCESSOR_STATS_INFO 58	/* Get all processor_stats structs */
#define TBL_UMAST_INFO		60	/* Get unix_master_info */
#define TBL_XCPU_INTR_MP	61	/* Get per-CPU TB shootdown xintrs */
#define	TBL_PROCESSOR_INFO 	62	/* Get all tbl_processor structs */
#define MSGINFO_MAX		0	/* max message size */
#define MSGINFO_MNB		1	/* max # bytes on queue */
#define MSGINFO_MNI		2	/* # of message queue identifiers */
#define MSGINFO_TQL		3	/* # of system message headers */
#define MSGINFO_SAR     	4       /* # of send and receive messages */

#define	SEMINFO_MNI		0	/* # of semaphore identifiers */
#define	SEMINFO_MSL		1	/* max # of semaphores per id */
#define	SEMINFO_OPM		2	/* max # of operations per semop call */
#define	SEMINFO_UME		3	/* max # of undo entries per process */
#define	SEMINFO_VMX		4	/* semaphore maximum value */
#define	SEMINFO_AEM		5	/* adjust on exit max value */
#define SEMINFO_OPT     	6       /* # of semaphore operations */

#define SHMINFO_MAX		0	/* max shared memory segment size */
#define SHMINFO_MIN		1	/* min shared memory segment size */
#define SHMINFO_MNI		2	/* num shared memory identifiers */
#define SHMINFO_SEG		3	/* max attached shared memory segments per process */

/*
 *  TBL_FSPARAM data layout
 */

struct tbl_fsparam
{
    long tf_used;		/* free fragments */
    long tf_iused;		/* free inodes */
    long tf_size;		/* total fragments */
    long tf_isize;		/* total inodes */
};


/*
 *  TBL_LOADAVG data layout
 */

struct tbl_loadavg
{
    union {
	    long   l[3];
	    double d[3];
    } tl_avenrun;
    int    tl_lscale;		/* 0 scale when floating point */
    long   tl_mach_factor[3];
};


/*
 *  TBL_INTR data layout
 */

struct tbl_intr
{
	long   	in_devintr;	/* Device interrupts (non-clock) */
	long   	in_context;	/* Context switches */
	long   	in_syscalls;	/* Syscalls */
	long   	in_forks;	/* Forks */
	long   	in_vforks;	/* Vforks */
};


/*
 *  TBL_MODES bit definitions
 */

#define UMODE_P_GID	01	/* - 4.2 parent GID on inode create */
#define UMODE_NOFOLLOW	02	/* - don't follow symbolic links */
#define UMODE_NONICE	04	/* - don't auto-nice long job */



/*
 *	TBL_PROCINFO data layout
 */
#define PI_COMLEN	19	/* length of command string */
struct tbl_procinfo
{
    int		pi_uid;		/* (effective) user ID */
    int		pi_pid;		/* proc ID */
    int		pi_ppid;	/* parent proc ID */
    int		pi_pgrp;	/* proc group ID */
    int		pi_ttyd;	/* controlling terminal number */
    int		pi_status;	/* process status: */
#define PI_EMPTY	0	    /* no process */
#define PI_ACTIVE	1	    /* active process */
#define PI_EXITING	2	    /* exiting */
#define PI_ZOMBIE	3	    /* zombie */
    int		pi_flag;	/* other random flags */
    char	pi_comm[PI_COMLEN+1];
				/* short command name */
    int		pi_ruid;        /* (real) user ID */
    int		pi_svuid;       /* saved (effective) user ID */
    int         pi_rgid;        /* (real) group ID */
    int         pi_svgid;       /* saved (effective) group ID */
    int		pi_session;	/* session ID */
    int         pi_tpgrp;       /* tty pgrp */
    int         pi_tsession;    /* tty session id */
    int         pi_jobc;        /* # procs qualifying pgrp for job control */
    int         pi_cursig;
    sigset_t    pi_sig;         /* signals pending */
    sigset_t    pi_sigmask;     /* current signal mask */
    sigset_t    pi_sigignore;   /* signals being ignored */
    sigset_t    pi_sigcatch;    /* signals being caught by user */
};

/*
 *	TBL_SYSINFO data layout
 */
struct tbl_sysinfo {
        long	si_user;		/* User time */
        long	si_nice;		/* Nice time */
        long	si_sys;			/* System time */
        long	si_idle;		/* Idle time */
        long    si_hz;
        long    si_phz;
	long 	si_boottime;		/* Boot time in seconds */
        long wait; /* Wait time */
#define usr si_user
#define sys si_sys
#define idle si_idle
};

/*
 *	TBL_DKINFO data layout
 */
#define DI_NAMESZ	8
struct tbl_dkinfo {
	/*******SAR STATS******/
        int	di_ndrive;
        int	di_busy;
        long	di_time;
        long	di_seek;
        long	di_xfer;
        long	di_wds;
        long	di_wpms;
        int	di_unit;
        char    di_name[DI_NAMESZ+1];
        long di_avque;  /* ave # of outstanding requests */
        long di_avwait; /* ave time (ms) in wait queue */
        long di_avserv; /* ave time (ms) for transfer completion */
	long di_usec;
	long di_initial_busy;
	long di_ref_cnt;
	long di_num_req_initiated;
	long di_num_req_completed;
	/*******SAR STATS******/
};
        
/*
 *	TBL_UMAST_INFO data layout
 */

struct tbl_umast_info {
	int	umast_calls;
	int	umast_to_master;
	int	umast_block;
	int	umast_release;
	int	umast_rel_cpu;
	int	umast_rel_block;
};

/*
 *	TBL_TTYINFO data layout
 */
struct tbl_ttyinfo {
        long	ti_nin;
        long	ti_nout;
        long	ti_cancc;
        long	ti_rawcc;
        long rcvin;     /* # of receive hardware interrupts (always zero) */
        long xmtin;     /* # of transmit hardware interrupts (always zero) */
        long mdmin;     /* # of modem interrupts (always zero) */
#define rawch ti_nin    /* see above */
#define canch ti_cancc  /* see above */
#define outch ti_nout   /* see above */
};

/*
 *	TBL_SWAPINFO data layout
 */
struct tbl_swapinfo {
	int	flags;
	int	size;
	int	free;
	dev_t	dev;
	ino_t	ino;
	};

/* 
 *	TBL_FILEINFO data layout - file access stats
 */
struct tbl_file {
	long iget;
	long namei;
	long dirblk;
};

/*
 *	 TBL_RUNQ data layout - run queue stats
 */
struct tbl_runq {
	long runque; /* processes in run queue */
	long runocc; /* % of time run queue is occupied */
};

/*
 *	TB__SCALLS data layout - system call stats
 */
struct tbl_scalls {
	long syscall; /* all system calls */
	long sysread; /* read system calls */
	long sysfork; /* fork system calls */
	long syswrite; /* write system calls */
	long sysexec; /* exec system calls */
	ulong readch; /* bytes transferred on read system calls */
	ulong writech; /* bytes transferred on write system calls */
};

/*
 *	TBL_BUFFER data layout - buffer activity
 */
struct tbl_buffer {
	long bread; /* # of physical block reads into system */
	long bwrite; /* # of physical writes from system buffers */
	long lread; /* logical reads from system buffer */
	long lwrite; /* logical writes from system buffer */
	long phread; /* # of physical read requests */
	long phwrite; /* # of physical write requests */
};

/*
 *	TBL_TBLSTATS - file tables stats
 */

struct tbl_tblstats {
	long tb_procu; /* process table entries used */
	long tb_proca; /* process table entries allocated */
	long tb_inodu; /* inode table entries used */
	long tb_inoda; /* inode table entries alocated */
	long tb_fileu; /* file table entries used */
	long tb_filea; /* file table entries allocated */
	long tb_procov; /* proc table overflows */
	long tb_inodov; /* inode table overflows */
	long tb_fileov; /* file table overflows */
	long tb_locku; /* shared memory table entries used */
	long tb_locka; /* shared memory table entries allocated */
};

/*
 *	TBL_KMEM - kernel memory stats
 */

struct tbl_kmem {
	ulong kmem_avail;		/* total kernel memory available */
	ulong kmem_alloc;		/* total kernel memory allocated */
	long kmem_fail;			/* # of kernel memory request failures */
};

/*
 *	TBL_PAGING - paging stats
 */
struct tbl_paging {
	/* sar -g and -p */
	long v_pgpgin;			/* # of pages paged-in */
	long v_sftlock;			/* # of software lock faults */
	long v_pgout;			/* # of page-out requests */
	long v_dfree;			/* # of pages freed */
	long v_scan;			/* # of pages scanned */
	long v_s5ifp;			/* # of s5 inodes taken of freelist */
	/* sar -r */
	long freeswap;			/* # of 512-byte disk blocks avail for page swapping */
};

/*
 *	TBL_MALLOCT and TBL_MALLOCTYPES data layout.
 */
struct tbl_malloct {
	long	kt_memuse;	/* # of bytes of this type in use */
	long	kt_limit;	/* # of bytes of this type allowed to exist */
	long    kt_wait;        /* blocking flag for this type of memory */
	long	kt_limblocks;	/* stat: # of times blocked for hitting limit */
	long	kt_failed;	/* stat: # of times failed for hitting
							limit with NOWAIT */
	long	kt_maxused;	/* stat: max # of bytes of this type ever used*/
};

/*
 *	TBL_MALLOCBUCKETS data layout.
 */
struct tbl_mallocb {
	void	*kb_next;	/* list of free blocks */
	long	kb_indx;	/* this bucket's index */
	long	kb_size;	/* bucket element size */
	long	kb_free;	/* # of free elements in this bucket */
	long	kb_total;	/* # of elements allocated to this bucket at
							 any given time */
	long	kb_failed;	/* # of times we failed to allocate */
};

/*
 * physical memory stats 
 */

struct  tbl_pmemstats {
	long 	pagesize;
	long 	physmem;
	long	npmem_clusters;
	long	npmem_cluster_type;
	long	npmem_usage;
	long	npmem_use_type;
	long	pmem_typesize;
};

/*
 * physical memory use 
 */

struct  tbl_pmemuse {
        vm_offset_t             start;          /* start addr */
        vm_offset_t             end;            /* end addr */
        int                     type;           /* mem use type */
        struct pmem_use         *next;          /* pointer to next element */
};

/*
 * physical memory cluster 
 */

struct  tbl_pmemcluster {
        vm_offset_t             start;          /* start addr */
        vm_offset_t             end;            /* end addr */
        int                     type;           /* mem use type */
};

/*
 * vmstats 
 */

struct  tbl_vmstats {
        long    pagesize;               /* page size in bytes */
        long    free_count;             /* # of pages free */
        long    active_count;           /* # of pages active */
        long    inactive_count;         /* # of pages inactive */
        long    wire_count;             /* total # of pages wired down */
        long    zero_fill_count;        /* # of zero fill pages */
        long    reactivations;          /* # of pages reactivated */
        long    pageins;                /* # of pageins */
        long    pageouts;               /* # of pageouts */
        long    faults;                 /* # of faults */
        long    cow_faults;             /* # of copy-on-writes */
        long    lookups;                /* object cache lookups */
        long    hits;                   /* object cache hits */
        long    user_ptepages;          /* # of user pte pages */
        long    kernel_ptepages;        /* # of kernel pte pages */
        long    free_ptepages;          /* # of free ptepages */
        long    ubc_pages;              /* # of ubc pages */
        long    contig_pages;           /* # of contig_malloc pages */
        long    malloc_pages;           /* # of malloc pages */
        long    vm_wired_count;         /* # of vm wired pages */
        long    ubc_wired_count;        /* # of ubc wired pages */
        long    meta_data_count;        /* # of meta data buffer pages */
};

#if !defined(__STDC__) && !defined(__cplusplus)
#define MAPINFO_PFN_MAX 8
enum xlated {UNMAPPED, SEGMENT, MAPPED};
struct tbl_mapinfo {
	vm_offset_t	start_va, end_va;
	vm_prot_t	access;
	enum xlated	mapping;
	unsigned int	pfn[MAPINFO_PFN_MAX];
};

typedef struct {unsigned long vpn:48, pid:16;} * tbl_mapinfo_index;
#define MAPINFO_PID(NDX)	(((tbl_mapinfo_index)&(NDX))->pid)
#define MAPINFO_VPN(NDX)	(((tbl_mapinfo_index)&(NDX))->vpn)
#endif

/*
 *	TBL_KNLIST data layout.
 */
#define TBL_KNLIST_NAMSIZ 24
struct tbl_knlist {
	void	*kn_addr;			/* symbol address */
	char	kn_name[TBL_KNLIST_NAMSIZ];	/* symbol name */
};
/* Netisr thread info */
struct tbl_netinfo {
        int     nt_nthreads;    /* # configured netisr threads */
        int     nt_maxactive;   /* max # concurrently active threads */
};

#ifndef	_KERNEL
extern	int    table __((long, long, void *, long, u_long));
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif
/* MALLOC_STATS is used in bsd/{kern_malloc,cmu_syscalls}.c */
#undef MALLOC_STATS
#define MSTATS_REQUEST 50
struct malloc_stats {
	int request_size;
	int bucket_size;
	long nmalloc;		/* number of invokations */
};

/*
 *    TBL_TCPCONN data layout.
 */
#define       DELETETCB       12
#define       ABORT_IF_TCBS   1

struct tbl_tcpconn {
      int             state;      /* must be DELETETCB or ABORT_IF_TCBS */
      struct in_addr  local_addr; /* local IP address for this conn. */
      u_short         local_port; /* local port number for this conn. */
      struct in_addr  rem_addr;   /* remote IP address for this conn. */
      u_short         rem_port;   /* remote port number for this conn. */
};

struct abort_inps  {
      struct inpcb    *abortinp;  /* ptr to inpcb */
};

/*
 * 	TBL_PROCESSOR_INFO data layout
 */
struct tbl_processor {
	long desired_load;		/* target load average for procesor */
	long load_avg;			/* current load average */
	long int_load_avg;		/* interrupt load average */
	long rt_load_avg;		/* realtime thread load average */
	struct timeval start_stop_time;	
	struct timeval pset_assign_time;
	long spare[50];
};
#endif	/* _SYS_TABLE_H_ */
