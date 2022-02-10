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

#pragma	ident	"@(#)$RCSfile: vollocks.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1995/01/31 20:43:51 $"

/* @(#)src/common/uts/io/vxvm/vollocks.h	1.2 03 Sep 1993 15:55:55 -  */
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
 * 11-17-93	WCY022	Wai Yim
 * Change all splhigh to spldevhigh.  The correct sync
 * spl for drivers is spldevhigh on alpha.  Other memory
 * allocation and other mechanisms might break.
 *
 * 11-16-93	WCY021	Wai Yim
 * Changed alpha mp lock init to use non-ted allocation
 * routines so it will work during boot.
 *
 * 11-10-93	WCY019	Wai Yim
 * . Cast the assert_wait and thread_wakeup channel to vm_offset_t.
 * . Cast lock structure allocations in lock macros.
 *
 * 11-05-93	WCY015 Yim
 * Merged smp portion from lsm bl2.
 * Note that simple_lock_t and lock_t are 64 bit pointers
 * to lock structures on alpha.  The offsets in the comment
 * area of these structure are not valid for alpha.
 *
 * 09-29-93	Wai Yim
 * Merged alpha port with vxvm1.2.1 source.
 * Only merged non-smp portion.  smp portion will be merged
 * with smp work.
 *
 * 09-30-93	Wai Yim
 * Merged 1.2.1.1mp code.
 *
 */

/*
 * vollocks - Definition of all VM locks.
 */

#ifndef _SYS_VOLLOCKS_H
#define _SYS_VOLLOCKS_H

/*
 * Generic lock macros and structures.  The following structures contain both
 * the UP and MP definitions for their contents.  They are padded to the
 * same size for the reference Intel architecture so that structure offsets
 * for structures containing these locks can be consistent.
 */

/* CHECKTHIS
 * All MP changes are not merged.  Take care of them when turning on SMP.
 */

/*
 * struct volspin is used to implement the generic spinlock.
 */
struct volspin {
#if defined(MP)
#ifdef __alpha
	simple_lock_t	sp_spin;
	spl_t		sp_pri;
#else /* !__alpha */
	lock_t		*sp_spin;		/* 0x00 */
	lkinfo_t	*sp_lkinfop;		/* 0x04 */
	pl_t		sp_pri;			/* 0x08 */
#endif /* __alpha */
#else /* MP */
	int		sp_pri;			/* 0x00 */
	int		*sp_pad[2];		/* 0x04 */
#endif /* MP */
#if defined(TED_ACTIVE)
	struct volted_pinfo	*sp_owner;	/* 0x0c pinfo of lock holder */
	int			sp_nheld;	/* 0x10 number of times held */
	struct volspin		*sp_next;	/* 0x14 next spinlock in list */
	struct volspin		*sp_prev;	/* 0x18 prev spinlock in list */
	int			sp_hier;	/* 0x1c spinlock hierarchy
						        number. locked by
							increasing value */
	int			sp_magic;	/* 0x20 magic number for asserts
							about alloc status */
#endif /* TED */
};

/*
 * struct volsleep is used to implement the generic sleep lock.
 */
struct volsleep {
#if defined(MP)
#ifdef __alpha
	lock_t		sl_sleep;
	spl_t		*sl_pri;
#else /* !__alpha */
	sleep_t		*sl_sleep;		/* 0x00 sleep lock */
	lkinfo_t	*sl_lkinfop;		/* 0x04 */
	pl_t		*sl_pri;		/* 0x08 saved priority level */
#endif /* __alpha */
#else /* MP */
	ulong_t		sl_flags;		/* 0x00 sleep flags */
	int		sl_pri;			/* 0x04 saved priority level */
	int		*sl_pad;		/* 0x08 */
#endif /* MP */
#if defined(TED_ACTIVE)
	struct volted_pinfo	*sl_owner;	/* 0x0c pinfo of lock holder */
	int			sl_nheld;	/* 0x10 number of times held */
	struct volsleep		*sl_next;	/* 0x14 next lock in list */
	struct volsleep		*sl_prev;	/* 0x18 prev lock in list */
	struct volted_pinfo	*sl_want;	/* 0x1c procs wanting lock */
	int			sl_magic;	/* 0x20 magic number for asserts
							about alloc status */
#endif /* TED */
};

/*
 * flags used by the UP sleeplock macros
 */
#define	_VOL_SWANT		0x1		/* the sleep lock is wanted */
#define	_VOL_SLOCK		0x2		/* the sleep lock is held */

/*
 * struct volsync is used to implement the generic sync lock, equivalent
 * to traditional sleep/wakeup or SVR4 MP syncronization variables.
 */
struct volsync {
#if defined(MP)
#ifdef __alpha
	simple_lock_t	sy_lock;
	ulong_t		sy_flags;
#else /* !__alpha */
	sv_t		*sy_sync;		/* 0x00 sync variable */
	ulong_t		sy_flags;		/* 0x04 sync flags */
#endif /* __alpha */
#else /* MP */
	int		sy_sync;		/* 0x00 wait channel */
	ulong_t		sy_flags;		/* 0x04 sync flags */
#endif /* MP */
#if defined(TED_ACTIVE)
	int			sy_wait;	/* 0x08 procs waiting on lock */
	struct volspin		*sy_spin;	/* 0x0c spinlock held by procs 
							sleeping on synclock */
	int			sy_magic;	/* 0x10 magic number for asserts
							about alloc status */
#endif /* TED */
};

/*
 *******************************************************************************
 * Start of MP section for locks. All locks in this section are MP versions of *
 * the locks in the following section.                                         *
 *******************************************************************************
 */
#ifdef MP

/*
 * Spinlock macros.
 *
 * On the SVR4/MP platform, spinlocks are called basic locks.  The only
 * semantic for these locks is to exclude other execution contexts in a
 * sequence of non-reentrant code.  Spinlocks should be held for short
 * periods only since, on an MP, they may cause serialization of operation
 * through a single processor.  They may be obtained while holding other
 * locks, although should always be obtained in the same order.  They must
 * be freed in the reverse sequence from which they are obtained.
 */
#ifdef __alpha
decl_simple_lock_info(extern, vol_alloc_spin_lockinfo)
#define _VOL_ALLOCSPINLOCK(spin)					\
	do {								\
		(spin).sp_spin = (simple_lock_t)			\
				_VOLMEMZALLOC(sizeof(*(spin).sp_spin));	\
		simple_lock_setup((spin).sp_spin, vol_alloc_spin_lockinfo);\
	} while (ZERO)

#define _VOL_FREESPINLOCK(spin)						\
	do {								\
		_VOLMEMFREE((spin).sp_spin,sizeof(*(spin).sp_spin));	\
		(spin).sp_spin = NULL;					\
	}while (ZERO)

#define _VOL_SPINLOCK(spin)						\
	do {								\
		int savipl;						\
                savipl = spldevhigh(); 	     				\
                simple_lock((spin).sp_spin);				\
                (spin).sp_pri = savipl;					\
	}while (ZERO)


#define _VOL_UNSPINLOCK(spin)						\
	do {								\
		int savipl;						\
		savipl=(spin).sp_pri;					\
		simple_unlock((spin).sp_spin);				\
		splx(savipl);						\
	} while (ZERO)
#else /* !__alpha */
#define _VOL_ALLOCSPINLOCK(spin)					\
	do {								\
		(spin).sp_lkinfop = 					\
			_VOLMEMZALLOC(sizeof(*(spin).sp_lkinfop));	\
		(spin).sp_spin = LOCK_ALLOC(1, PRI6, (spin).sp_lkinfop,	\
			KM_SLEEP); 					\
	} while (ZERO)
#define _VOL_FREESPINLOCK(spin)						\
	do {								\
		LOCK_DEALLOC((spin).sp_spin);				\
		_VOLMEMFREE((spin).sp_lkinfop,				\
			sizeof(*(spin).sp_lkinfop));			\
	}while (ZERO)
#define _VOL_SPINLOCK(spin)						\
		((spin).sp_pri = LOCK((spin).sp_spin, plhi))
#define _VOL_UNSPINLOCK(spin)	(UNLOCK((spin).sp_spin, (spin).sp_pri))
#endif /* __alpha */

/*
 * Sleeplock macros.
 *
 * A sleeplock is a mutual exclusion lock for a critical section of code
 * that will cause the calling process to sleep if the lock is already
 * held.  Sleeplocks cannot be acquired with a spinlock held, but can be
 * held with other sleeplocks held.
 */
#ifdef __alpha
extern struct lockinfo *vol_alloc_sleep_lockinfo;
#define _VOL_ALLOCSLEEPLOCK(slp)					\
	do {								\
		(slp).sl_sleep = (lock_t)				\
				_VOLMEMZALLOC(sizeof(*(slp).sl_sleep));	\
		lock_setup((slp).sl_sleep,vol_alloc_sleep_lockinfo,TRUE);\
	} while (ZERO)
#define _VOL_FREESLEEPLOCK(slp)						\
	do {								\
		_VOLMEMFREE((slp).sl_sleep,sizeof(*(slp).sl_sleep));	\
		(slp).sl_sleep = NULL;					\
	}while (ZERO)


#define _VOL_SLEEPLOCK(slp)	(lock_write((slp).sl_sleep))
#define _VOL_UNSLEEPLOCK(slp)	(lock_done((slp).sl_sleep))
#define _VOL_TRYSLEEPLOCK(slp, stat)					\
		((stat) = lock_try_write((slp).sl_sleep))
#else /* !__alpha */
#define _VOL_ALLOCSLEEPLOCK(slp)					\
	do {								\
		(slp).sl_lkinfop =					\
			_VOLMEMZALLOC(sizeof(*(slp).sl_lkinfop));	\
		(slp).sl_sleep = SLEEP_ALLOC(1, (slp).sl_lkinfop,	\
			KM_SLEEP);					\
	} while (ZERO)
#define _VOL_FREESLEEPLOCK(slp)						\
	do {								\
		SLEEP_DEALLOC((slp).sl_sleep);				\
		_VOLMEMFREE((slp).sl_lkinfop, sizeof(*(slp).sl_lkinfop));\
	}while (ZERO)
#define _VOL_SLEEPLOCK(slp)	(SLEEP_LOCK((slp).sl_sleep, pridisk))
#define _VOL_UNSLEEPLOCK(slp)	(SLEEP_UNLOCK((slp).sl_sleep))
#define _VOL_TRYSLEEPLOCK(slp, stat)					\
		((stat) = SLEEP_TRYLOCK((slp).sl_sleep))
#endif /* __alpha */

/*
 * Synclock macros.
 *
 * On a SVR4/MP platform, synclocks are implemented as synchronization
 * variables.  They act in a similar way to the basic unix sleep-wakeup
 * mechanism except that in order to ensure that a wakeup is not missed,
 * they must be called with a spinlock held.  The spinlock is atomically
 * released when the caller goes to sleep.  A wakeup is thus guaranteed
 * not to occur between the acquiring of the spinlock and the start of
 * the sleep.  On exit from the sleep, the spinlock is re-acquired.
 */
#ifdef __alpha
decl_simple_lock_info(extern, vol_allocsync_lockinfo)
#define _VOL_ALLOCSYNC(sync)						\
        do {                                                            \
		(sync).sy_lock = (simple_lock_t)			\
				_VOLMEMZALLOC(sizeof(*(sync).sy_lock));	\
		simple_lock_setup((sync).sy_lock, vol_allocsync_lockinfo);\
		(sync).sy_flags = 0;					\
        } while (ZERO)

#define _VOL_FREESYNC(sync)						\
        do {                                                            \
		_VOLMEMFREE((sync).sy_lock,sizeof(*(sync).sy_lock));	\
		(sync).sy_lock = NULL;					\
        } while (ZERO)

#define _VOL_SYNCWAIT(sync, spin)					\
	do {								\
		int savipl;						\
		assert_wait((vm_offset_t)&(sync).sy_flags, FALSE);	\
		savipl=(spin).sp_pri;					\
		simple_unlock((spin).sp_spin);				\
		splx(savipl);						\
		thread_block();						\
		_VOL_SPINLOCK(spin);					\
        } while (ZERO)

#define _VOL_SYNCWAITSIG(sync, spin, signalled)				\
	do {								\
		if (mpsleep(&(sync).sy_flags, PZERO + 1 | PCATCH,	\
		   "vxvm", 0, (spin).sp_spin,				\
		   MS_LOCK_SIMPLE | MS_LOCK_ON_ERROR)) {		\
			signalled = 1;					\
		} else {						\
			signalled = 0;					\
		}							\
	} while (ZERO)

#define _VOL_SYNCSIG(sync)	thread_wakeup((vm_offset_t)&(sync).sy_flags)

#define _SWAP_LOCK()
#define _SWAP_UNLOCK()
#else /* !__alpha */
#define _VOL_ALLOCSYNC(sync)	((sync).sy_sync = SV_ALLOC(KM_SLEEP))
#define _VOL_FREESYNC(sync)	(SV_DEALLOC((sync).sy_sync))
#define _VOL_SYNCWAIT(sync, spin)					\
	do {								\
		SV_WAIT((sync).sy_sync, pridisk, (spin).sp_spin);	\
		_VOL_SPINLOCK(spin);					\
	} while (ZERO)
#define _VOL_SYNCWAITSIG(sync, spin, signalled)				\
	do {								\
		signalled = SV_WAIT_SIG((sync).sy_sync, prihi, 		\
			(spin).sp_spin);				\
		_VOL_SPINLOCK(spin);					\
		signalled = !signalled;					\
	} while (ZERO)
#define _VOL_SYNCSIG(sync)	 SV_BROADCAST((sync).sy_sync, 0)
#define _SWAP_LOCK()							\
		do {							\
			proc_t	*cprocp = NULL;				\
			pl_t	pri;					\
									\
			(void)drv_getparm(UPROCP, (ulong_t *)&cprocp);	\
			pri = splhi();					\
			locked_or(cprocp->p_flag, SSYS);		\
			splx(pri);					\
		} while (ZERO)

#define _SWAP_UNLOCK()							\
		do {							\
			proc_t	*cprocp = NULL;				\
			pl_t	pri;					\
									\
			(void)drv_getparm(UPROCP, (ulong_t *)&cprocp);	\
			pri = splhi();					\
			locked_and(cprocp->p_flag, ~SSYS);		\
			splx(pri);					\
		} while (ZERO)
#endif /* __alpha */

/*
 *******************************************************************************
 * Start of UP section for locks. All locks in this section are UP versions of *
 * the locks in the prior section.                                             *
 *******************************************************************************
 */
#else /* MP */

#ifdef __alpha
/*
 * The UP locking primtives need only to have the routine name splhi()
 * changed to splhigh() for OSF.
 */
#define splhi() spldevhigh()

#endif /* __alpha */

/*
 * Spinlock macros.
 *
 * On a UP platform, spinlocks reduce to interrupt locks.  The only
 * semantic for these locks is to exclude other execution contexts in a
 * sequence of non-reentrant code.  Spinlocks should be held for short
 * periods only since they prevent interrupts from occuring and can lead
 * to poor real-time response characteristics. They may be obtained while
 * holding other locks, although should always be obtained in the same
 * order.  They must be freed in the reverse sequence from which they are
 * obtained so that the stored priorities can be restored correctly.
 */
#define _VOL_ALLOCSPINLOCK(spin)
#define _VOL_FREESPINLOCK(spin)
#define _VOL_SPINLOCK(spin)		((spin).sp_pri = splhi())
#define _VOL_UNSPINLOCK(spin)		(splx((spin).sp_pri))

/*
 * Sleeplock macros.
 *
 * A sleeplock is a mutual exclusion lock for a critical section of code
 * that will cause the calling process to sleep if the lock is already
 * held.  Sleeplocks cannot be acquired with a spinlock held, but can be
 * held with other sleeplocks held.
 */
#define _VOL_ALLOCSLEEPLOCK(slp)	((slp).sl_flags = 0)
#define _VOL_FREESLEEPLOCK(slp)
#define _VOL_SLEEPLOCK(slp)						\
	do {								\
		int	x;						\
									\
		x = splhi();						\
		for (;;) {						\
			if (((slp).sl_flags & (_VOL_SLOCK | _VOL_SWANT)) == \
			    0) { 					\
				(slp).sl_flags |= _VOL_SLOCK;		\
				break;					\
			} else {					\
				(slp).sl_flags |= _VOL_SWANT;		\
				(void)sleep((caddr_t)&(slp), PZERO);		\
			}						\
		}							\
		splx(x);						\
	} while (ZERO)
#define _VOL_UNSLEEPLOCK(slp)						\
	do {								\
		int	x;						\
									\
		x = splhi();						\
		(slp).sl_flags &= ~_VOL_SLOCK;				\
		if ((slp).sl_flags & _VOL_SWANT) {			\
			(slp).sl_flags &= ~_VOL_SWANT;			\
			(void)wakeup((caddr_t)&(slp));			\
		}							\
		splx(x);						\
	} while (ZERO)
#define _VOL_TRYSLEEPLOCK(slp, stat)					\
	do {								\
		int	x;						\
									\
		x = splhi();						\
		if (((slp).sl_flags & (_VOL_SLOCK | _VOL_SWANT)) == 0) {\
			(slp).sl_flags |= _VOL_SLOCK;			\
			(stat) = 1;					\
		} else {						\
			(stat) = 0;					\
		}							\
		splx(x);						\
	} while (ZERO)

/*
 * Synclock macros.
 *
 * On a UP platform, synclocks are implemented as basic unix sleep-wakeup
 * calls except that in order to ensure that a wakeup is not missed,
 * they must be called with a spinlock held.  The spinlock is atomically
 * released when the caller goes to sleep.  A wakeup is thus guaranteed
 * not to occur between the acquiring of the spinlock and the start of
 * the sleep.  On exit from the sleep, the spinlock is re-acquired.
 */
#define _VOL_ALLOCSYNC(sync)	((sync).sy_flags = 0)
#define _VOL_FREESYNC(sync)
#define _VOL_SYNCWAIT(sync, s)						\
	do {								\
		int	savepri = (s).sp_pri;				\
									\
		(void)sleep((caddr_t)&((sync).sy_sync), PZERO);		\
		(void)splhi();						\
		(s).sp_pri = savepri;					\
	} while (ZERO)
#define _VOL_SYNCWAITSIG(sync, s, signalled)				\
	do {								\
		int	savepri = (s).sp_pri;				\
									\
		signalled = sleep((caddr_t)&((sync).sy_sync), PSLEP | PCATCH);\
		(void)splhi();						\
		(s).sp_pri = savepri;					\
	} while (ZERO)
#define _VOL_SYNCSIG(sync)	((void)wakeup((caddr_t)&((sync).sy_sync)))

/*
 * Other locking macros.
 */
#ifdef __alpha
#define _SWAP_LOCK()
#define _SWAP_UNLOCK()
#else /* !__alpha */
#define _SWAP_LOCK()							\
		do {							\
			proc_t	*cprocp = NULL;				\
			int	pri;					\
			(void)drv_getparm(UPROCP, (ulong_t *)&cprocp);	\
			pri = splhi();					\
			cprocp->p_swlocks++;				\
			cprocp->p_flag |= (SSWLOCKS | SSYS);		\
			splx(pri);					\
		} while (ZERO)
#define _SWAP_UNLOCK()							\
		do {							\
			proc_t	*cprocp = NULL;				\
			int	pri;					\
			(void)drv_getparm(UPROCP, (ulong_t *)&cprocp);	\
			pri = splhi();					\
			if (--cprocp->p_swlocks == 0) {			\
				cprocp->p_flag &= ~SSWLOCKS;		\
			}						\
			cprocp->p_flag &= ~SSYS;			\
			splx(pri);					\
		} while (ZERO)
#endif /* __alpha */
#endif /* MP */


/*
 *******************************************************************************
 * Start of section for TED definitions used for lock debugging.               *
 *******************************************************************************
 */
#if defined(TED_ACTIVE)

#define VOL_ALLOCSPINLOCK(spin, hier)	_vol_allocspinlock(__LINE__, __FILE__, \
							   &(spin), hier)
#define VOL_FREESPINLOCK(spin)		_vol_freespinlock(__LINE__, __FILE__, \
							  &(spin))
#define VOL_SPINLOCK(spin)		_vol_spinlock(&(spin))
#define VOL_UNSPINLOCK(spin)		_vol_unspinlock(&(spin))
#define VOL_ALLOCSLEEPLOCK(slp)		_vol_allocsleeplock(__LINE__,	\
							    __FILE__, &(slp))
#define VOL_FREESLEEPLOCK(slp)		_vol_freesleeplock(__LINE__, __FILE__, \
							   &(slp))
#define VOL_SLEEPLOCK(slp)		_vol_sleeplock(&(slp))
#define VOL_UNSLEEPLOCK(slp)		_vol_unsleeplock(&(slp))
#define VOL_TRYSLEEPLOCK(slp, ret)	_vol_trysleeplock(&(slp), &(ret))
#define VOL_ALLOCSYNC(sync)		_vol_allocsync(__LINE__, __FILE__, \
						       &(sync))
#define VOL_FREESYNC(sync)		_vol_freesync(__LINE__, __FILE__, \
						      &(sync))
#define VOL_SYNCWAIT(sync, sp)		_vol_syncwait(&(sync), &(sp))
#define VOL_SYNCWAITSIG(sync, sp, ret)	_vol_syncwaitsig(&(sync), &(sp), &(ret))
#define VOL_SYNCSIG(sync)		_vol_syncsig(&(sync))
#define SWAP_LOCK()			_SWAP_LOCK()
#define SWAP_UNLOCK()			_SWAP_UNLOCK()

#else /* TED_ACTIVE */

#define VOL_ALLOCSPINLOCK(spin, hier)	_VOL_ALLOCSPINLOCK(spin)
#define VOL_FREESPINLOCK(spin)		_VOL_FREESPINLOCK(spin)
#define VOL_SPINLOCK(spin)		_VOL_SPINLOCK(spin)
#define VOL_UNSPINLOCK(spin)		_VOL_UNSPINLOCK(spin)
#define VOL_ALLOCSLEEPLOCK(slp)		_VOL_ALLOCSLEEPLOCK(slp)
#define VOL_FREESLEEPLOCK(slp)		_VOL_FREESLEEPLOCK(slp)
#define VOL_SLEEPLOCK(slp)		_VOL_SLEEPLOCK(slp)
#define VOL_UNSLEEPLOCK(slp)		_VOL_UNSLEEPLOCK(slp)
#define VOL_TRYSLEEPLOCK(slp, ret)	_VOL_TRYSLEEPLOCK(slp, ret)
#define VOL_ALLOCSYNC(sync)		_VOL_ALLOCSYNC(sync)
#define VOL_FREESYNC(sync)		_VOL_FREESYNC(sync)
#define VOL_SYNCWAIT(sync, sp)		_VOL_SYNCWAIT(sync, sp)
#define VOL_SYNCWAITSIG(sync, sp, ret)	_VOL_SYNCWAITSIG(sync, sp, ret)
#define VOL_SYNCSIG(sync)		_VOL_SYNCSIG(sync)
#define SWAP_LOCK()			_SWAP_LOCK()
#define SWAP_UNLOCK()			_SWAP_UNLOCK()

#endif /* TED_ACTIVE */

#endif /* _SYS_VOLLOCKS_H */
