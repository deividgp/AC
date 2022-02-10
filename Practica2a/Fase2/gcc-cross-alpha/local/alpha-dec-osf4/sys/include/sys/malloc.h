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
 * @(#)$RCSfile: malloc.h,v $ $Revision: 1.1.111.3 $ (DEC) $Date: 1998/12/01 03:43:35 $
 */
/*
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base: malloc.h	7.16 (Berkeley) 6/28/90
 */

#ifndef	_SYS_MALLOC_H
#define _SYS_MALLOC_H

#include <mach/machine/vm_types.h>

/*
 * Types of memory to be allocated.  Several of these indexes are associated
 * with more descriptive type names in the "netstat" utility (which uses the
 * table(TBL_MALLOCT) system call), so don't renumber them without checking
 * for backwards compatibility.
 */
#define	M_FREE		0	/* should be on free list */
#define M_MBUF		1	/* mbuf (MT_DATA type) */
#define	M_CLUSTER	2	/* mbuf cluster page */
#define	M_SOCKET	3	/* socket structure */
#define	M_PCB		4	/* protocol control block */
#define	M_RTABLE	5	/* routing tables */
#define	M_FTABLE	6	/* fragment reassembly header */
#define	M_IFADDR	7	/* interface address */
#define	M_SOOPTS	8	/* socket options */
#define	M_SONAME	9	/* socket name */
#define	M_MBLK		10	/* mblk */
#define	M_MBDATA	11	/* mblk data */
#define	M_STRHEAD	12	/* Stream head */
#define	M_STRQUEUE	13	/* Streams queue pair */
#define	M_STRQBAND	14	/* Streams queue band */
#define	M_STRMODSW	15	/* Streams modsw */
#define	M_STRSIGS	16	/* Streams setsig */
#define	M_STRPOLLS	17	/* Streams poll */
#define	M_STROSR	18	/* Streams osr */
#define	M_STRSQ		19	/* Streams synch queue */
#define	M_STREAMS	20	/* misc Streams memory */
#define M_IOV		21	/* large iov's */
#define M_FHANDLE	22	/* network file handle */
#define	M_NFSREQ	23	/* NFS request header */
#define	M_NFSMNT	24	/* NFS mount structure */
#define M_FILE		25	/* file struct  */
#define M_FILEDESC	26	/* filedesc struct */
#define M_IOCTLOPS	27	/* ioctl data */
#define M_SELPOLL	28	/* select/poll arrays */
#define M_DEVBUF	29	/* device driver memory */
#define M_PATHNAME	30	/* pathname */
#define M_KTABLE	31	/* kernel table */
#define M_UFSMNT	32      /* UFS mount structure */
#define M_ADVFS 	33	/* Digital ADVfs */
#define M_IPMOPTS	34      /* ip multicast options */
#define M_IPMADDR	35      /* ip multicast address */
#define M_IFMADDR	36      /* interface multicast addess */
#define M_MRTABLE	37      /* multicast routing table */
#define M_VNODE 	38      /* vnode struct */
#define M_IOBUF 	39      /* swap/ubc io buffers */
#define M_PRESTO	40	/* prestoserve */
#define M_DMASG		41	/* DMA subsystem s-g structures and lists */
#define M_SIGQ		42	/* signal queue entries */
#define M_ATMMEM	43	/* non-data ATM buffers */
#define M_DRD		44	/* Distributed Raw Disk */
#define M_DLM		45	/* Distributed Lock Manager */
#define M_CNX		46	/* Connection Manager */
#define M_ESS		47	/* Event Simulation Subsystem */
#define M_KALLOC	48	/* kalloc - obsolescent */
#define M_TEMP		49	/* misc temporary data buffers */
#define M_RM		50	/* Reflective Memory */
#define M_PMAP		51	/* Pmap data structures */
#define M_CRED		52	/* kern credential data structure */
#define M_TASK		53	/* task structure */
#define M_THREAD	54	/* thread structure */
#define M_AIO		55	/* kern aio data structure */
#define M_SELQ		56	
#define M_RTTIME	57
#define M_SVIPC		58
#define M_FILEBUF	59
#define M_MOUNT		60
#define M_NAMEI		61
#define M_MIPC		62	/* mach ipc */
#define M_VMOBJ		63
#define M_VMANON	64
#define M_VMSEG		65
#define M_VMLOCK	66
#define M_VMMAP		67
#define M_VMENTRY	68
#define M_VMCOPY	69
#define M_FLOCK		70	/* file locking */
#define M_THCALL	71	/* thread call */
#define M_FIFO		72	
#define M_ZONE		73	
#define M_ANON          74
#define M_VMVPAGE       75
#define M_NCALLOUT      76
#define M_WS            77
#define M_TGEC          78
#define M_HWINTR	79
#define M_SIGACT	80	/* Dynamic signal actions */
#define M_THREADLOCK	81	/* Dynamic thread lock_addr */
#define M_HEADER        82	/* mbuf packet header */
#define M_HTABLE        83	/* mbuf IMP host table */
#define M_ATABLE        84	/* mbuf address resolution table */
#define M_RIGHTS        85	/* mbuf access rights */
#define M_CONTROL       86	/* mbuf extra-data protocol message */
#define M_OOBDATA       87	/* mbuf expedited data */
#define M_DNA           88	/* DNA */
#define M_WAN           89	/* WAN */
#define M_X25           90	/* X.25 */
#define M_CTF           91	/* CTF */
#define M_SEC_COMM	92	/* socket security data */
#define M_MBATTR	93	/* secure mbufs */
#define M_DLI           94	/* DLI */
#define M_VMSWAP	95	/* swap related data structure */
#define M_IORSRC	96	/* I/O resource map array */
#define M_DT		97	/* Disaster Tolerant */
#define M_USB		98	/* Universal Serial Bus */
#define M_RDG		99	/* Reliable Datagram */
#define M_LAST		100

#define KMEMNAMSZ       12
#define INITKMEMNAMES {				   \
        "FREE",         /*  0 M_FREE		*/ \
        "MBUF",         /*  1 M_MBUF		*/ \
        "MCLUSTER",     /*  2 M_CLUSTER		*/ \
        "SOCKET",       /*  3 M_SOCKET		*/ \
        "PCB",          /*  4 M_PCB		*/ \
        "ROUTETBL",     /*  5 M_RTABLE		*/ \
        "FRAGTBL",      /*  6 M_FTABLE		*/ \
        "IFADDR",       /*  7 M_IFADDR		*/ \
        "SOOPTS",       /*  8 M_SOOPTS		*/ \
        "SONAME",       /*  9 M_SONAME		*/ \
        "MBLK",         /* 10 M_MBLK		*/ \
        "MBLKDATA",     /* 11 M_MBDATA		*/ \
        "STRHEAD",      /* 12 M_STRHEAD		*/ \
        "STRQUEUE",     /* 13 M_STRQUEUE	*/ \
        "STRQBAND",     /* 14 M_STRQBAND	*/ \
        "STRMODSW",     /* 15 M_STRMODSW	*/ \
        "STRSIGS",      /* 16 M_STRSIGS		*/ \
        "STRPOLL",      /* 17 M_STRPOLLS	*/ \
        "STROSR",       /* 18 M_STROSR		*/ \
        "STRSYNCQ",     /* 19 M_STRSQ		*/ \
        "STREAMS",      /* 20 M_STREAMS		*/ \
        "IOV",          /* 21 M_IOV		*/ \
        "FHANDLE",      /* 22 M_FHANDLE		*/ \
        "NFS REQ",      /* 23 M_NFSREQ		*/ \
        "NFS MOUNT",    /* 24 M_NFSMNT		*/ \
        "FILE",         /* 25 M_FILE		*/ \
        "FILE DESC",    /* 26 M_FILEDESC	*/ \
        "IOCTLOPS",     /* 27 M_IOCTLOPS	*/ \
        "SELECT/POLL",  /* 28 M_SELPOLL		*/ \
        "DEVBUF",       /* 29 M_DEVBUF		*/ \
        "PATHNAME",     /* 30 M_PATHNAME	*/ \
        "KERNEL TBL",   /* 31 M_KTABLE		*/ \
	"UFS MOUNT",	/* 32 M_UFSMNT		*/ \
	"ADVFS",	/* 33 M_ADVFS		*/ \
	"IPM OPT",	/* 33 M_IPMOPTS		*/ \
	"IPM ADDR",	/* 35 M_IPMADDR		*/ \
	"IFM ADDR",	/* 36 M_IFMADDR		*/ \
	"MCAST RTTBL",	/* 37 M_MRTABLE		*/ \
	"VNODE",	/* 38 M_VNODE		*/ \
	"IO BUF",	/* 39 M_IOBUF		*/ \
        "PRESTO",       /* 40 M_PRESTO		*/ \
	"DMASG",	/* 41 M_DMASG		*/ \
	"SIGQ",		/* 42 M_SIGQ		*/ \
        "ATM",		/* 43 M_ATMMEM		*/ \
        "DRD",		/* 44 M_DRD		*/ \
        "DLM",		/* 45 M_DLM		*/ \
        "CNX",		/* 46 M_CNX		*/ \
        "ESS",		/* 47 M_ESS		*/ \
        "KALLOC",       /* 48 M_KALLOC		*/ \
        "TEMP",         /* 49 M_TEMP		*/ \
        "RM",		/* 50 M_RM		*/ \
        "PMAP",		/* 51 M_PMAP		*/ \
        "CRED",		/* 52 M_CRED		*/ \
        "TASK",		/* 53 M_TASK		*/ \
        "THREAD",	/* 54 M_THREAD		*/ \
        "AIO",		/* 55 M_AIO		*/ \
        "SELQ",		/* 56 M_SELQ		*/ \
        "RTTIME",	/* 57 M_RTTIME		*/ \
        "SVIPC",	/* 58 M_SVIPC		*/ \
        "FILEBUF",	/* 59 M_FILEBUF		*/ \
        "MOUNT",	/* 60 M_MOUNT		*/ \
        "NAMEI",	/* 61 M_NAMEI		*/ \
        "MIPC",		/* 62 M_MIPC		*/ \
        "VMOBJ",	/* 63 M_VMOBJ		*/ \
        "VMANON",	/* 64 M_VMANON		*/ \
        "VMSEG",	/* 65 M_VMSEG		*/ \
        "VMLOCK",	/* 66 M_VMLOCK		*/ \
        "VMMAP",	/* 67 M_VMMAP		*/ \
        "VMENTRY",	/* 68 M_VMENTRY		*/ \
        "VMCOPY",	/* 69 M_VMCOPY		*/ \
        "FLOCK",	/* 70 M_FLOCK		*/ \
        "THCALL",	/* 71 M_THCALL		*/ \
        "FIFO",		/* 72 M_FIFO		*/ \
        "ZONE",		/* 73 M_ZONE		*/ \
        "ANON",		/* 74 M_ANON		*/ \
        "VMVPAGE",	/* 75 M_VMVPAGE		*/ \
	"NCALLOUT", 	/* 76 M_NCALLOUT	*/ \
        "WS",		/* 77 M_WS              */ \
        "TGEC",		/* 78 M_TGEC            */ \
        "HWINTR",	/* 79 M_HWINTR		*/ \
        "SIGACT",	/* 80 M_SIGACT		*/ \
        "THREADLOCK",	/* 81 M_THREADLOCK	*/ \
        "HEADER",	/* 82 M_HEADER		*/ \
        "HTABLE",	/* 83 M_HTABLE		*/ \
        "ATABLE",	/* 84 M_ATABLE		*/ \
        "RIGHTS",	/* 85 M_RIGHTS		*/ \
        "CONTROL",	/* 86 M_CONTROL		*/ \
        "OOBDATA",	/* 87 M_OOBDATA		*/ \
        "DNA",		/* 88 M_DNA		*/ \
        "WAN",		/* 89 M_WAN		*/ \
        "X25",		/* 90 M_X25		*/ \
        "CTF",		/* 91 M_CTF		*/ \
        "SEC_COMM",     /* 92 M_SEC_COMM	*/ \
        "MBATTR",       /* 93 M_MBATTR  	*/ \
        "DLI",		/* 94 M_DLI		*/ \
        "VMSWAP",	/* 95 M_VMSWAP		*/ \
        "IORSRC",	/* 96 M_IORSRC		*/ \
        "DT",		/* 97 M_DT		*/ \
        "USB",		/* 98 M_USB		*/ \
        "RDG",		/* 99 M_RDG		*/ \
}

struct kmem_leak_user {
        long            timestamp;	/* time of allocation */
        vm_offset_t     caller; /* routine requesting the action */
        vm_offset_t     addr;   /* memory address */
        vm_size_t       size;   /* memory size */
        int             type;   /* type */
};

typedef struct kmem_leak_user *kmem_leak_user_t;

#ifdef	_KERNEL

#include <kern/lock.h>
#include <mach/vm_param.h>
#include <kern/thread.h>
#include <kern/sched_prim.h>

/*
 * The following 2 options affect only kern_malloc.c and cmu_syscalls.c.
 */
#define KMEMTYPES	/* whether type-based use and limits are supported */
/*#define KMEMSTATS*/	/* whether type and bucket stats are supported */

/*
 * Set of buckets for each size of memory block that is retained
 */
struct kmembuckets {
	decl_simple_lock_data(,kb_lock)
	void	*kb_next;	/* list of free blocks */
	long	kb_size;	/* bucket element size */
	long	kb_free;	/* # of free elements in this bucket */
	long	kb_total;	/* # of elements allocated to this bucket */
	long	kb_elmpercl;	/* # of elements in this sized allocation */
	long	kb_highwat;	/* # of elements allowed to keep before gc */
	long	kb_failed;	/* # of times failed due to NOWAIT */
	long	kb_indx;
#ifdef KMEMSTATS
	long	kb_calls;	/* stat: total calls to allocate this size */
	long	kb_couldfree;	/* stat: # of pages over high water mark
							 and could free */
	long	kb_noelem;	/* stat: # of times that (kb_next == NULL) */
	long	kb_borrowed;	/* stat: # of times that this bucket borrowed */
	long	kb_lent;	/* stat: # of times that this bucket lent */
#endif /* KMEMSTATS */
};
typedef struct kmembuckets	*kmembucket_t;

/*
 * Array of descriptors that describe the contents of each page
 */
struct kmemusage {
	union {
		kmembucket_t	kbp;	/* pointer to bucket */
		void		*prev;	/* previous element for 12k bucket */
	} ku_un0;
	union {
		long	freecnt;/* for small allocations, free pieces in page */
		long	size;	/* for large allocations, size in bytes */
	} ku_un1;
};
typedef struct kmemusage	*kmemusage_t;

#define ku_kbp			ku_un0.kbp
#define ku_prev			ku_un0.prev
#define ku_freecnt		ku_un1.freecnt
#define ku_size			ku_un1.size

/*
 * structure that describe the contents of each kseg page
 */
struct ksegpage {
	struct ksegpage		*ks_mnext;	/* malloc pages list */
	struct ksegpage 	*ks_mprev;	/* malloc pages list */
	union {
	    struct {
        	struct ksegpage	*_ks_pnext;    	/* pages in a bucket list */
		struct ksegpage	*_ks_pprev;	/* pages in a bucket list */
	    } _blist;
	    struct ksegpage     *_ks_rnext;	/* malloc reserve list */
	    struct ksegpage     *_ks_vnext;	/* malloc priv list */
	} _kslist;
	void			*ks_enext;	/* next element */
	struct kmembuckets 	*ks_kbp; 	/* pointer to bucket */
	long			ks_freecnt;	/* free elements in page */
};

#define ks_pnext	_kslist._blist._ks_pnext
#define ks_pprev	_kslist._blist._ks_pprev
#define ks_rnext	_kslist._ks_rnext
#define ks_vnext	_kslist._ks_vnext

typedef struct ksegpage *ksegpage_t;

/*
 * Flags to malloc and/or contig_malloc()
 */
#define M_WAITOK	0x0000
#define M_NOWAIT	0x0001
#define M_ZERO		0x0002
#define M_SAVE		0x0004
#define M_TIMEDWAIT	0x0008
#define M_FORCENODE     0x0010

/*
 * Default node flag to contig_malloc_internal() when traditional calls 
 * to contig_malloc() are utilized.
 */
#define CONTIG_MALLOC_LOCAL  (-1)
#define BUCKETINDEX(size)  \
        (((size) <= 768) \
            ? (((size) <= 256) \
                ? (((size) <= 96) \
                    ? (((size) <= 32) \
                        ? (((size) <= 16) ? 0 : 1) \
                        : (((size) <= 64) ? 2 : 16)) \
                    : (((size) <= 160) \
                        ? (((size) <= 128) ? 3 : 17) \
                        : (((size) <= 192) ? 18 : 4))) \
                : (((size) <= 512) \
                    ? (((size) <= 384) \
                         ? (((size) <= 320) ? 19 : 20)  \
                         : (((size) <= 448) ? 21 : 5)) \
                    : (((size) <= 640) \
                        ? (((size) <= 576) ? 22 : 23)  \
                        : (((size) <= 704) ? 24 : 25)))) \
            : (((size) <= 4096) \
                ? (((size) <= 1344) \
                    ? (((size) <= 1024) \
                        ? (((size) <=  896) ? 26 : 6) \
                        : (((size) <= 1152) ? 27 : 28)) \
                    : (((size) <= 2048) \
                        ? (((size) <= 1600) ? 29 : 7) \
                        : (((size) <= 2688) ? 30 : 8))) \
                : (((size) <= 32*1024) \
                    ? (((size) <= 12*1024) \
                         ? (((size) <=  8*1024) ? 9 : 31)  \
                         : (((size) <= 16*1024) ? 10 : 11)) \
                    : (((size) <= 128*1024) \
                        ? (((size) <= 64*1024) ? 12 : 13)  \
                        : (((size) <= 256*1024) ? 14 : 15)))))

/*
 * Let DECC decide if BUCKETINDEX can be used.  
 */ 
#if defined(__DECC) && __DECC_VER >= 50860003
#define	FINDINDEX(size) (__builtin_isconstant(size) ? BUCKETINDEX(size) : -1)
#else
#define	FINDINDEX(size) BUCKETINDEX(size)
#endif

#define MALLOC(space, cast, size, type, flags) \
	(space) = (cast)malloc((u_long)(size), FINDINDEX(size), type, flags)

#define FREE(addr, type) free((void *)(addr), type)

/*
 * MALLOC_VAR is provided for callers who pass a variable
 * for size. Since the compiler can not compute the index during compile
 * time in this case, there is no reason to expand the BUCKETINDEX macro
 * for each call. This interface will reduce the size of the object
 * for such cases.
 */

#define MALLOC_VAR(space, cast, size, type, flags) \
	(space) = (cast)malloc((u_long)(size), -1, type, flags)

/* define for contig_malloc init */

#define CONTIG_MALLOC_DISABLED  0
#define BOOT_ENABLED            1
#define SAVED_ENABLED           2

#ifdef __cplusplus
extern "C" {
#endif
extern void *malloc(u_long, int, int, int);
extern void *malloc_var(u_long, int, int);
extern void free(void *, int);
extern void malloc_inc_highwater(int, int);
extern void kmeminit(void);
extern void kmeminit_thread(int);
extern long *kmemtypetable;
extern long **kmemtypetblp;
extern long *kmemtypemax;
extern unsigned int kmemsize[];
extern int kmempages;
extern int malloc_num_buckets;
extern void *contig_malloc(u_long, u_long, u_long, int, int);
extern void *contig_malloc_ext(u_long, u_long, u_long, int, int, int);
extern void contig_free(void *, u_long, int);
#ifdef __cplusplus
}
#endif

struct kmem_leak_data {
        long  		timestamp;
        vm_offset_t     caller; /* routine requesting the action */
        vm_offset_t     addr;   /* memory address */
        vm_size_t       size;   /* memory size */
        int             type;   /* type */
        int             flag;   /* malloc or free */
};

typedef struct kmem_leak_data *kmem_leak_data_t;

struct kmem_audit_data {
        vm_offset_t     thread; /* thread requesting the action */
        vm_offset_t     caller; /* routine requesting the action */
        vm_offset_t     addr;   /* memory address */
        vm_size_t       size;   /* memory size */
        int             type;   /* memory type */
        int             action; /* malloc or free */
};

typedef struct kmem_audit_data *kmem_audit_data_t;

#define KMEM_LEAK_PPAGE  ((PAGE_SIZE-8)/(sizeof (struct kmem_leak_data)))
#define KMEM_LEAK_ARRAY_SHIFT 20

extern kmem_audit_data_t kmem_audit_data; 
extern kmem_leak_data_t *kmem_leak_array;
extern kmem_leak_data_t kmem_leak_seg;
extern long kmem_leak_array_size;
extern long kmem_leak_count;
extern long kmem_audit_count;
extern long kmem_debug;
extern simple_lock_data_t kmem_debug_lock;

#endif	/* _KERNEL */
#endif	/* _SYS_MALLOC_H */
