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
 * @(#)$RCSfile: lock.h,v $ $Revision: 4.2.51.2 $ (DEC) $Date: 1999/01/07 19:35:37 $
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
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 *	File:	kern/lock.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Locking primitives definitions
 */

#ifndef	_KERN_LOCK_H_
#define _KERN_LOCK_H_

/*
 *	A simple spin lock.
 */

#if !defined (__STDC__)		/* "normal" kernel version */
struct slock {
	unsigned long	sl_data: 32,	/* lock flag (bit 0) and calling pc */
			sl_info: 16,	/* lockinfo structure table index */
			sl_cpuid: 8,	/* cpu number of last operation */
			sl_lifms: 8;	/* lockinfo flags and minspl */
};
#else			/* ANSI standard version */
struct ansi_slock {
	unsigned int	sl_data;	/* lock flag (bit 0) and calling pc */
	unsigned int	sl_info: 16,	/* lockinfo structure table index */
			sl_cpuid: 8,	/* cpu number of last operation */
			sl_lifms: 8;	/* lockinfo flags and minspl */
};
struct slock {
	union {
		long sl_types;
		struct ansi_slock ansi_slock;
	}sl;
};

#define sl_data		sl.ansi_slock.sl_data
#define sl_info		sl.ansi_slock.sl_info
#define sl_cpuid	sl.ansi_slock.sl_cpuid
#define sl_lifms	sl.ansi_slock.sl_lifms
#endif /* __STDC__ */

typedef struct slock	simple_lock_data_t;
typedef struct slock	*simple_lock_t;

#define decl_simple_lock_data(class,name) class simple_lock_data_t name;

/*
 * reader/writer spin lock structure.  Provides multiple readers/one 
 * writer fuctionality with a busy wait.  Structure is layed out to
 * be cache friendly.
 */


#define RWS_BLOCK_SIZE_SHIFT	6	
#define RWS_BLOCK_STRIDE	((1<<RWS_BLOCK_SIZE_SHIFT) \
			 /sizeof(struct slock))	
struct rws_lock {
	struct slock	rws_writer_mutex[RWS_BLOCK_STRIDE];
	struct slock	rws_reader_mutex[1][RWS_BLOCK_STRIDE];
};

typedef struct rws_lock *rws_lock_t;


/*
 *	The general lock structure.  Provides for multiple readers,
 *	upgrading from read to write, and sleeping until the lock
 *	can be gained.
 *
 *	On some (many) architectures, assembly language code in the inline
 *	program fiddles the lock structures.  It must be changed in concert
 *	with the structure layout.
 */

/* forward decl for ANSI & C++ */
struct thread;

struct lock {
	struct slock	l_lock;		/* simple lock for atomicity control */
	unsigned int	l_caller;	/* half of calling pc of locker */
	int		l_wait_writers; /* number of waiting writers */
	int		l_readers;	/* number of accepted readers */
	unsigned char	l_flags;	/* lock state flags (see below) */
	unsigned char	l_lifms;	/* lockinfo flags and minspl level */
	unsigned short	l_info;		/* lockinfo structure table index */
	struct thread	*l_lastlocker;	/* thread that was last granted lock */
};

/* bit definitions for l_flags field */
#define LF_RECWRITE	  0x07	/* recursive write count */
#define LF_GENERAL_WAIT	  0x10	/* wakeup all writers waiting */
#define LF_WRITE	  0x20	/* locked for writing or writer is waiting */
#define LF_READ_SLEEPING  0x40	/* thread is suspended on read lock */
#define LF_READ_WAKE_LAST 0x80	/* last wakeup was reader */

typedef struct lock	lock_data_t;
typedef struct lock	*lock_t;


/*
 *	Definitions and data structures used by lock debugging logic.
 */

#define MAX_LOCK	16	/* max complex lock nesting level */
#define MAX_SLOCK	32	/* max simple lock nesting level */

struct slock_debug {
	struct slock *sd_addr[MAX_SLOCK]; /* addr of simple lock structure */
	unsigned long sd_time[MAX_SLOCK]; /* time stamp at lock acquisition */
};

struct lockinfo {
	char		*li_name;	/* arbitrary name of class */
	int		li_count;	/* number of lock instances */
	int		li_flgspl;	/* class flags and minspl level */
};

#define LOCKINFO_SHIFT	4		/* log2(sizeof(struct lockinfo)) */

#define LI_SPLMASK	0x07		/* required minimum spl level mask */
#define LI_RWS		0x08		/* reader/writer spin lock type */
#define LI_ORDERED	0x10		/* ordering exists within a class */
#define LI_ORDNEXT	0x20		/* ordering exists thru next class */
#define LI_DOHIER	0x40		/* hierarchy checking is enabled */
#define LI_VALID	0x80		/* lock is properly initialized */
#define LI_PROBE	0x1000		/* set lock to probe mode, note */
					/* this bit is not mirrored     */
					/* lock flags field.	        */

struct lockstats {
	unsigned long	ls_tries;	/* number of acquisition attempts */
	unsigned long	ls_reads;	/* number of acquisitions for read */
	unsigned long	ls_trmax;	/* max time held or number of rdrs */
	unsigned long	ls_misses;	/* number of attempts which missed */
	unsigned long	ls_sleeps;	/* number of thread blocks incurred */
	unsigned long	ls_waitmax;	/* max time spent waiting on a lock */
	unsigned long	ls_waitmin;	/* min time spent waiting on a lock */
	unsigned long	ls_waitsum;	/* total time spent waiting on locks */
};

/* structure to hold pointer and counts for recursive read locks held
 * by a thread.
 */
struct lock_read_rec_list {
	struct lock *l;		/* pointer to read lock held recrusive. */
	int rec_count;		/* count of recursive depth */
};


#define LOCKSTATS_SHIFT	6		/* log2(sizeof(struct lockstats)) */


#ifdef _KERNEL

#include <cpus.h>
#include <rt_preempt.h>
#include <mach_ldebug.h>
#include <mach/boolean.h>

#define MACH_SLOCKS	((NCPUS > 1) || MACH_LDEBUG || RT_PREEMPT)

#if MACH_SLOCKS

#define simple_lock_init(l)	simple_lock_setup((l), (struct lockinfo *)0)
#ifdef __cplusplus
extern "C" {
#endif
extern void		simple_lock_setup(simple_lock_t, struct lockinfo *);
extern void		simple_lock_terminate(simple_lock_t);
extern void		simple_lock(simple_lock_t);
extern void		simple_unlock(simple_lock_t);
extern boolean_t	simple_lock_try(simple_lock_t);
extern boolean_t	simple_lock_locked(simple_lock_t);
extern boolean_t	simple_lock_holder(simple_lock_t);

extern rws_lock_t	rws_alloc(struct lockinfo *, int );
extern void		rws_free(rws_lock_t);
extern void		rws_read_lock(rws_lock_t);
extern  boolean_t	rws_read_lock_try(rws_lock_t);
extern void		rws_read_unlock(rws_lock_t);
extern void		rws_write_lock(rws_lock_t);
extern void		rws_write_unlock(rws_lock_t);
#ifdef __cplusplus
}
#endif

#define decl_rws_lock_info(name)		struct lockinfo *name
#define decl_simple_lock_info(class,name)	class struct lockinfo *name;
#define simple_lock_addr(name)			(&(name))

#else /* MACH_SLOCKS */

#define simple_lock_init(l)
#define simple_lock_setup(l,i)
#define simple_lock_terminate(l)
#define simple_lock(l)
#define simple_unlock(l)
#define simple_lock_try(l)		(1)	/* always succeeds */
#define simple_lock_locked(l)		(1)	/* always succeeds */
#define simple_lock_holder(l)		(1)	/* always succeeds */

#define decl_simple_lock_info(class,name)
#define simple_lock_addr(name)			((simple_lock_t)0)

#endif /* MACH_SLOCKS */

#define SLOCK_LOCKED(l)	simple_lock_locked(l)
#define SLOCK_HOLDER(l)	simple_lock_holder(l)

/* Sleep locks must work even if no multiprocessing */

#define lock_read_done(l)	lock_done(l)
#define lock_write_done(l)	lock_done(l)
#define lock_init(l,cs)		lock_setup((l), (struct lockinfo *)0, (cs))
#define lock_init2(l,cs,t)	lock_setup((l), (struct lockinfo *)0, (cs))

#ifdef __cplusplus
extern "C" {
#endif
extern void		lock_setup(lock_t, struct lockinfo *, boolean_t);
extern void		lock_terminate(lock_t);
extern void		lock_write(lock_t);
extern void		lock_read(lock_t);
extern void		lock_done(lock_t);
extern boolean_t	lock_read_to_write(lock_t);
extern void		lock_write_to_read(lock_t);
extern boolean_t	lock_try_write(lock_t);
extern boolean_t	lock_try_read(lock_t);
extern boolean_t	lock_try_read_to_write(lock_t);
extern boolean_t	lock_try_write_assert(lock_t);
extern boolean_t	lock_try_read_assert(lock_t);
extern void		lock_set_recursive(lock_t);
extern void		lock_clear_recursive(lock_t);
extern void		lock_read_recursive(lock_t);
extern void		lock_read_done_recursive(lock_t);
extern void		lock_adopt(lock_t, struct thread *);
extern void		lock_disown(lock_t, struct thread *);
extern boolean_t	lock_readers(lock_t);
extern boolean_t	lock_locked(lock_t);
extern boolean_t	lock_holder(lock_t);
extern boolean_t        lock_recursive_try(lock_t);
extern void		lock_done_clear_recursive(lock_t);
#ifdef __cplusplus
}
#endif

#if MACH_LDEBUG

#include <kern/assert.h>

#define LOCK_READERS(l)		lock_readers(l)
#define LOCK_LOCKED(l)		lock_locked(l)
#define LOCK_HOLDER(l)		lock_holder(l)
#define LASSERT(clause)		if (check_locks) ASSERT(clause)

#else /* MACH_LDEBUG */

#define LOCK_READERS(l)		(1)
#define LOCK_LOCKED(l)		(1)
#define LOCK_HOLDER(l)		(1)
#define LASSERT(clause)

#endif /* MACH_LDEBUG */

#define LOCK_ADOPT(l,th)	if (check_locks) lock_adopt((l), (th))
#define LOCK_DISOWN(l,th)	if (check_locks) lock_disown((l), (th))

extern long lockmode; /* 0: uni, 1: rt, 2: smp, 3: rt/smp, 4: rt/smp/dbg/sts */
extern int check_locks; /* set after current_thread() is usable if debugging */

#endif /* _KERNEL */

#endif /* _KERN_LOCK_H_ */
