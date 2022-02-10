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
 * @(#)$RCSfile: vm_anon.h,v $ $Revision: 1.1.52.4 $ (DEC) $Date: 1997/05/13 20:06:34 $
 */
#ifndef _VM_VM_ANON_H_
#define	_VM_VM_ANON_H_
#include <sys/unix_defs.h>
#include <kern/lock.h>
#include <vm/vm_debug.h>

/*
 * This determines how many pages can be in an anon_klock and must fit in
 * the bifields, akl_rpages, akl_anon.
 */
#define	ANON_KLPAGES	16
#define	ANON_KLSHIFT	17
#define	ANON_KLSIZE	(1 << ANON_KLSHIFT)

#define KLOCK	TRUE
#define KUNLOCK	FALSE

/*
 * Control structure for anonymous memory cluster.  
 * The simple lock protects the akl_*lock bits, akl_rpages and akl_pagelist.
 * akl_mlock must be taken to update akl_anon field.
 */
struct anon_klock {
	decl_simple_lock_data(, akl_slock)	
	volatile unsigned int
			akl_want  :21,		/* lock wanted */
			akl_lock  : 1,		/* lock held */
			akl_mlock : 1,		/* mem expansion */
			akl_plock : 1,		/* swap/pageout lock */
			akl_rpages: 8;		/* resident pages */

	unsigned int 	akl_anon;		/* anon allocated */
	struct vm_page	*akl_pagelist;		/* resident page list */
};

typedef	struct anon_klock *alock_t;		/* Anon klock type */

struct anon_cluster {
	struct anon_klock 	acl_klock;
	struct vm_anon 		*acl_anon[ANON_KLPAGES];
};

typedef	struct anon_cluster *anon_cluster_t;

struct vm_anon_object {
	struct vm_object
			ao_object;		/* Object common part */
	unsigned int 	ao_flags;		/* Flags for anon memory */
	unsigned int	ao_ranon;		/* Reserved swap for object */
	vm_offset_t	ao_rbase;		/* Relative base for pages */
	struct vm_object	
			*ao_bobject;		/* Object backed by if any */
	vm_offset_t	ao_boffset;		/* Offset of backing object */
	anon_cluster_t	ao_acla;		/* Anon cluster array */
};

typedef	struct vm_anon_object *vm_anon_object_t;

struct vm_shm_object {
        struct vm_anon_object	so_anon_object;	/* Anon portion of object */
        struct shmid_internal   *so_sp;		/* SystemV specific structure */
	unsigned int		so_wire_count;	/* object wire count */ 
};

typedef struct vm_shm_object *vm_shm_object_t;

#define	ao_size		ao_object.ob_size
#define	ao_refcnt	ao_object.ob_ref_count
#define ao_rescnt       ao_object.ob_res_count
#define ao_oflags	ao_object.ob_flags

#define so_refcnt	so_anon_object.ao_object.ob_ref_count
#define so_rescnt       so_anon_object.ao_object.ob_res_count
#define so_flag		so_anon_object.ao_flags
#define so_anon		so_anon_object.ao_anon
#define so_size		so_anon_object.ao_object.ob_size
#define so_nklock	so_anon_object.ao_nklock
#define so_klock	so_anon_object.ao_klock
#define so_bobject	so_anon_object.ao_bobject
#define so_ranon	so_anon_object.ao_ranon
#define so_oflags	so_anon_object.ao_object.ob_flags

/*
 * anon object flags
 */
#define	AF_PRIVATE	0x01			/* private anon */
#define	AF_SHARED	0x02			/* shared anon */
#define	AF_HOLES	0x04			/* anon array has holes */
#define	AF_SWAPPED	0x08			/* swapped out */
#define AF_LAZY		0x10			/* object swapped lazily? */
#define AF_TEXT		0x20			/* maps text */

/*
 * An anon object is protected by an array of locks whose granularity
 * is determined at boot time by the tuning parameter anonklshift.
 * The lock is computed the following way:
 *
 *	(object offset) >> klshift = lock index
 *
 */

struct vm_anon {
	union {
		struct vm_page	*an_page;	/* Page hint for anon */
		struct vm_swap	*an_swap;	/* swap when paged out */
	} an_un;
	unsigned int	an_refcnt:24,	/* Anon references */
			an_cowfaults:5,	/* Runtime hueristic */
			an_haspage:1,	/* whether an_un is page */
			an_pagealloc:1,	/* page is being allocated */
			an_pagewait:1;	/* waiting for page to be allocated */
	unsigned int	an_spfn;	/* offset into swap in units of page */
};
typedef	struct vm_anon	*vm_anon_t;
#define	VM_ANON_NULL	((vm_anon_t)0)

#define	an_page		an_un.an_page
#define	an_swap		an_un.an_swap
#define	an_hasswap	an_spfn

/*
 * Macros to derive swap offsets from anon and page pointers.
 */
#define	AN_SOFF(ap)	ptoa((ap)->an_spfn)
#define	PG_SOFF(pp)	ptoa((pp)->pg_anon->an_spfn)
#define	PG_SPFN(pp)	(pp)->pg_anon->an_spfn


#define	ANON_COWMAX	0x1f

/*
 * The anon structure size can impact the locking
 * hash constant defined below.  A constant is
 * is used for performance reasons instead of computing
 * the value.
 */

#define	A_LSHIFT	0x4			/* 16 is size maximum */

/*
 * flags to vm_anon_page_alloc()
 */
#define	APA_WAIT	1	/* wait for page */
#define	APA_ZEROED	2	/* need zeroed page */
#define	APA_SHARED	4	/* shared anon */

/*
 * On MP machines concurrent anon updates are serialized
 * by a spin lock.  Having a lock for each anon structure
 * would be very wasteful.  Instead the anon virtual address
 * is used in a hash function to compute an index into a
 * anon simple lock array.
 */

#define	ANON_NLANON		128		/* 128 anon locks */

extern simple_lock_t	anon_lanon;
extern int		anon_nlanon;
extern vm_offset_t	anon_lanon_mask;

#define	a_lockaddr(AP)						\
		(anon_lanon +					\
		((((vm_offset_t) (AP)) >> A_LSHIFT) 		\
		& anon_lanon_mask))

#define	a_lock(AP)		simple_lock(a_lockaddr(AP))
#define a_lock_try(AP)		simple_lock_try(a_lockaddr(AP))
#define a_unlock(AP)		simple_unlock(a_lockaddr(AP))
#define a_locklp(ALP)		simple_lock((ALP))
#define a_unlocklp(ALP)		simple_unlock((ALP))

#define	a_access(AP, AOP) {					\
	register simple_lock_t AL;				\
	AL = a_lockaddr(AP);					\
	simple_lock(AL);					\
	AOP;							\
	simple_unlock(AL);					\
}


#define	anon_klround(KOFF)					\
	(((vm_offset_t)(KOFF) + (ANON_KLSIZE - 1)) & ~(ANON_KLSIZE - 1))

#define anon_kltrunc(KOFF)					\
	(((vm_offset_t)(KOFF) & ~(ANON_KLSIZE - 1)))

#define anon_kloffset(KOFF)					\
	((vm_offset_t)(KOFF) & (ANON_KLSIZE - 1))

#define	anon_nklock(SIZE)					\
	( ((SIZE) + (ANON_KLSIZE - 1)) >> ANON_KLSHIFT)

#define anon_klpindex(KOFF)					\
	(anon_kloffset((KOFF)) >> PAGE_SHIFT)

#define anon_pages(OFFSET, END, NPAGES)	{			\
	vm_offset_t KEND;					\
	KEND = MIN(anon_klround(OFFSET +1), END);		\
	NPAGES = MIN( ANON_KLPAGES, atop(KEND - (OFFSET)) );	\
}

#define acla_to_lp(AARP, OFFSET) \
	&( ((AARP) + ((OFFSET) >> ANON_KLSHIFT)) ->acl_klock) 
		
#define acla_to_anonp(AARP, OFFSET) \
      (&(((AARP) + (OFFSET >> ANON_KLSHIFT))->acl_anon[anon_klpindex(OFFSET)])) 

decl_simple_lock_info(extern, akl_slock_lockinfo)
#define lk_lock_init(LP) {						\
		simple_lock_setup(&(LP)->akl_slock, akl_slock_lockinfo); \
		(LP)->akl_want = 0;					\
		(LP)->akl_lock = 0;					\
		(LP)->akl_mlock = 0;					\
		(LP)->akl_plock = 0;					\
}	

#define lk_lock_terminate(LP) {				\
		simple_lock_terminate(&(LP)->akl_slock); \
}

#if	MACH_SLOCKS
#define	lk_slock(LP)	simple_lock(&(LP)->akl_slock)
#define	lk_sunlock(LP)	simple_unlock(&(LP)->akl_slock)
#else
#define	lk_slock(LP)	1
#define	lk_sunlock(LP)	1
#endif

/*
 * Memory lock on LK
 */
#define lk_mlock(LP) {							\
	simple_lock(&(LP)->akl_slock);					\
	while ((LP)->akl_lock) {					\
		assert_wait_mesg((vm_offset_t)(LP), FALSE, "lk_mlock");	\
		(LP)->akl_want++;					\
		simple_unlock(&(LP)->akl_slock);			\
		thread_block();						\
		simple_lock(&(LP)->akl_slock);				\
	}								\
	(LP)->akl_lock = 1;						\
	(LP)->akl_mlock = 1;						\
	simple_unlock(&(LP)->akl_slock);				\
}

/*
 * Memory or paging unlock
 */
#define lk_mpunlock(LP,L,H) {						\
		simple_lock(&(LP)->akl_slock);				\
		if (!(LP)->akl_/**/H/**/lock) {				\
			if  ((LP)->akl_want) {				\
				thread_wakeup_one((vm_offset_t) (LP));	\
				(LP)->akl_want--;			\
			}						\
			(LP)->akl_lock = 0;				\
		}							\
		(LP)->akl_/**/L/**/lock = 0;				\
		simple_unlock(&(LP)->akl_slock);			\
}

/*
 * Release the paging or memory lock
 * whe the spin lock already held.
 */
#define lk_hmpunlock(LP,L,H) {						\
		if (!(LP)->akl_/**/H/**/lock) {				\
			if  ((LP)->akl_want) {				\
				thread_wakeup_one((vm_offset_t) (LP));	\
				(LP)->akl_want--;			\
			}						\
			(LP)->akl_lock = 0;				\
		}							\
		(LP)->akl_/**/L/**/lock = 0;				\
		simple_unlock(&(LP)->akl_slock);			\
}

#define lk_lock(LP) {							\
	simple_lock(&(LP)->akl_slock);					\
	while ((LP)->akl_lock) {					\
		assert_wait_mesg((vm_offset_t)(LP), FALSE, "lk_lock");	\
		(LP)->akl_want++;					\
		simple_unlock(&(LP)->akl_slock);			\
		thread_block();						\
		simple_lock(&(LP)->akl_slock);				\
	}								\
	(LP)->akl_lock = 1;						\
	simple_unlock(&(LP)->akl_slock);				\
}

#define lk_unlock(LP) {							\
		simple_lock(&(LP)->akl_slock);				\
		if ((LP)->akl_want) {					\
			thread_wakeup_one((vm_offset_t) (LP));		\
			(LP)->akl_want--;				\
		}							\
		(LP)->akl_lock = 0;					\
		simple_unlock(&(LP)->akl_slock);			\
}

extern boolean_t lk_lock_try(alock_t lp);

		
#ifdef	KERNEL

#if	VM_ANON_TRACK

struct an_track {
	char	at_written;
	short	at_writes;
	short	at_reads;
	long	at_writepc;
	long	at_readpc;
};

#define	APTOAT(AP) {							\
	register struct vm_swap *SP;					\
	vm_offset_t SOFFSET;						\
	SP = a_aptosp((AP), &SOFFSET);					\
	((struct an_track *) 						\
	(SP->vs_anbase + SP->vs_swapsize)) + 				\
	((AP) - SP->vs_anbase)						\
}

#define	AN_TRACK_WRITTEN(AP)	an_track_written((AP))
#define	AN_TRACK_WRITE(AP)	an_track_write((AP))
#define	AN_TRACK_READ(AP)	an_track_read((AP))
#define	AN_TRACK_FREE(AP)	an_track_free((AP))

#else

#define	AN_TRACK_WRITTEN(AP)
#define	AN_TRACK_WRITE(AP)
#define	AN_TRACK_READ(AP)
#define	AN_TRACK_FREE(AP)

#endif	/* VM_ANON_TRACK */

/*
 * forward declarations for prototypes to keep compiler happy
 */
struct vm_map_entry;
struct vm_page;
struct vm_swap_object;

extern vm_anon_t	anon_allocate();
extern void		anon_free(vm_anon_t, boolean_t);
extern void		anon_getpage(vm_anon_object_t, vm_offset_t,
			     struct vm_map_entry *, vm_offset_t, alock_t,
			     struct vm_page **, int, vm_anon_t);
extern vm_anon_t	anon_appage_alloc(vm_anon_object_t, 
				vm_offset_t, alock_t, vm_anon_t *);
extern vm_anon_t	anon_cowpage_alloc(vm_anon_object_t,
				vm_offset_t, alock_t, vm_anon_t, vm_anon_t *);
extern vm_anon_t	anon_pagezero_alloc(vm_anon_object_t,
				vm_offset_t, alock_t);

extern struct vm_page	*vm_anon_kpage_alloc(struct vm_swap_object *,
				vm_offset_t);
extern struct vm_page	*vm_anon_page_alloc(struct vm_anon_object *, 
				vm_offset_t, struct anon_klock *, 
				vm_anon_t, boolean_t);
extern			vm_anon_page_free(struct vm_anon_object *, 
				vm_offset_t, vm_anon_t);

extern boolean_t	swap_reserve(struct vm_anon_object *, vm_size_t);
extern void		swap_release(struct vm_anon_object *, vm_size_t);

#endif	/* KERNEL */
#endif /* !_VM_VM_ANON_H_ */
