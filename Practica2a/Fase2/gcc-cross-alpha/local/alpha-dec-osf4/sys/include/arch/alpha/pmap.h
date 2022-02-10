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
 *	@(#)$RCSfile: pmap.h,v $ $Revision: 1.2.51.12 $ (DEC) $Date: 1998/09/11 21:06:18 $
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *
 *	File:	pmap.h
 *
 *	Alpha version
 *
 *	Machine-dependent structures for the physical map module.
 *
 */

#ifndef	_PMAP_MACHINE_
#define	_PMAP_MACHINE_

#define MMF_READ	0
#define MMF_IFETCH	-1
#define MMF_WRITE	1
#define MMF_PMAPINIT	2 /* used by pmap_bootstrap call to pmap_fault_on */

#ifndef	ASSEMBLER
#include <standards.h>
#include <mach/boolean.h>
#include <kern/lock.h>
#include <kern/processor.h>
#include <mach/machine/vm_param.h>
#include <mach/vm_statistics.h>
#include <mach/vm_prot.h>
#include <machine/cpu.h> 
#include <machine/counters.h> 

/*
 *	Alpha Page Table Entry.
 */

union pt_entry {
	unsigned long	quadword;	/* for alignment and atomic writes */
	struct {
		unsigned int	_v:1,		/* valid */
				_for:1,		/* fault on read */
				_fow:1,		/* fault on write */
				_foe:1,		/* fault on execute */
				_asm:1,		/* address space match */
				_gh:2,		/* granularity hint */
				_no_mb:1,	/* suppress MB() in EV6 tbmiss */
				_prot:8,	/* {K|E|S|U}{R|W}E */
				_exec:1,	/* execute access flag */
				_wire:1,	/* wired */
				_seg:1,		/* shared text segment pte */
				_ssm:1,		/* shared data segment pte */
		                _gh_shared:1,
		                _lw_wait:1,	/* wait for LW-unwire */
		                _soft:2,	/* unused software bits */
		                _lw_wire:8,	/* lw wire count.  See */
						 /* LW_WIRE_MAX below */
				_pfn:32;	/* page frame number */
	}		PTE_BITFIELD;
};

#define pg_v		PTE_BITFIELD._v
#define pg_for		PTE_BITFIELD._for
#define pg_fow		PTE_BITFIELD._fow
#define pg_foe		PTE_BITFIELD._foe
#define pg_asm		PTE_BITFIELD._asm
#define pg_gh		PTE_BITFIELD._gh
#define pg_no_mb	PTE_BITFIELD._no_mb
#define pg_prot		PTE_BITFIELD._prot
#define pg_exec		PTE_BITFIELD._exec
#define pg_wire		PTE_BITFIELD._wire
#define pg_seg		PTE_BITFIELD._seg
#define pg_ssm		PTE_BITFIELD._ssm
#define pg_gh_shared	PTE_BITFIELD._gh_shared
#define pg_soft		PTE_BITFIELD._soft
#define pg_lw_wire	PTE_BITFIELD._lw_wire
#define pg_lw_wait	PTE_BITFIELD._lw_wait
#define LW_WIRE_MAX	255
#define pg_pfn		PTE_BITFIELD._pfn

typedef union pt_entry	pt_entry_t;
#define	PT_ENTRY_NULL	((pt_entry_t *) 0)

#define NOTaPFN	((unsigned int)0)
/* The lowest address which is not accessible at any page size. */
#define NOTaVA	((vm_offset_t)(1L<<54))

/*
 * Assumptions:
 *	1) Supervisor and executive modes are not used.
 *	2) User mode accessibility implies kernel mode accessibility.
 */
#define PROT_UW		0x33
#define PROT_KW		0x11
#define PROT_NA		0x00
#define PROT_URKW	0x13
#define PROT_UR		0x03
#define PROT_KR		0x01

/* (some) pte fields as quadword masks */
#define PTEQ_MASK_KWE	(1L << 12)
#define PTEQ_MASK_UWE	(1L << 13)
#define PTEQ_MASK_EXEC	(1L << 16)
#define PTEQ_MASK_FLTON	(7L << 1)

#define PTES_PER_PAGE	(ALPHA_PGBYTES / sizeof(pt_entry_t))

#define PTETOPHYS(pte)	alpha_ptob((pte)->pg_pfn)

#define LEVEL1_PT_OFFSET(ADDR) \
	(((vm_offset_t)(ADDR) >> (3 * PGSHIFT - 6)) & (PGOFSET>>3))
#define LEVEL2_PT_OFFSET(ADDR) \
	(((vm_offset_t)(ADDR) >> (2 * PGSHIFT - 3)) & (PGOFSET>>3))
#define LEVEL3_PT_OFFSET(ADDR) (((vm_offset_t)(ADDR) >> PGSHIFT) & (PGOFSET>>3))
#define EQ_LEVEL1_VPN(XADDR, YADDR) \
	((((XADDR) ^ (YADDR)) >> (3 * PGSHIFT - 6)) == 0)
#define EQ_LEVEL2_VPN(XADDR, YADDR) \
	((((XADDR) ^ (YADDR)) >> (2 * PGSHIFT - 3)) == 0)
#define EQ_LEVEL3_VPN(XADDR, YADDR) ((((XADDR) ^ (YADDR)) >> PGSHIFT) == 0)
#define in_Othermap(PTE) \
	EQ_LEVEL1_VPN((vm_offset_t)(PTE), (vm_offset_t)Othermap)

#ifndef NCPUS
#define NCPUS 1
#endif

/*
 *	Pmap proper
 */
struct pmap {
	simple_lock_data_t	lock;	   /* lock on map		*/
	pt_entry_t *		level1_pt; /* level 1 page table	*/
	cpumask_t		active_on; /* one bit for each CPU	*/
	unsigned long           lw_wirings; /* total lw wirings */
	unsigned long           lw_trans;  /* no. of lw_wire trans.     */
	cpumask_t		new_asn;   /* advance asn on these CPUs	*/
	int			(*coproc_tbi)(); /* synch with PXG maps */
	int			ref_count; /* Reference count.		*/
	int			active_count; /* # cpus active on       */
	simple_lock_data_t	other_lock;/* task mapping window.	*/
	struct pmap_statistics	stats;	   /* Map statistics.		*/
	unsigned short		asn[NCPUS];/* per-cpu ASN assignment	*/
	unsigned long           asn_wrap_count[NCPUS];
	void			*coproc_arg; /* argument to coproc_tbi	*/
};

typedef struct pmap	*pmap_t;
#define	PMAP_NULL	((pmap_t) 0)
#define	PMAP_PTE	((pmap_t) 1)	/* user pte page mapping */
#define	PMAP_KPTE	((pmap_t) 2)	/* kernel pte page mapping */

#define PMAP_MAXASN	255	/* TODO: ev5 is 127; need per chip define? */

typedef int memory_atom;

#ifdef _KERNEL
extern memory_atom	latest_asn[NCPUS];	 /* < 2^16 */
extern memory_atom	asn_wrap_point[NCPUS];
extern unsigned long	asn_wrap_count[NCPUS];
#endif /* _KERNEL */


struct sys_space {
	vm_size_t   s_size;
	vm_offset_t *s_va;
	vm_size_t   s_cpuid;
};

struct scavenge_list {
	long		count;
	vm_offset_t	kseg_start;
};

#ifdef _KERNEL
extern struct scavenge_list scavenge_info;
_BEGIN_CPLUSPLUS
extern void	end_of_boot_text();
_END_CPLUSPLUS
#define START_OF_KERNEL_TEXT	((vm_offset_t)setup_main)
#define END_OF_BOOT_TEXT	((vm_offset_t)end_of_boot_text)
extern vm_offset_t	end_of_scavenge;
#define scavenged(KSEG_ADDR)	((KSEG_ADDR) < end_of_scavenge)
#endif /* _KERNEL */



/* physical memory use type */

#define PMEM_HOLE	0
#define PMEM_CONSMEM	1
#define PMEM_KTEXT	2
#define PMEM_KDATA	3
#define PMEM_KBSS	4
#define PMEM_SCAVENGE	5
#define PMEM_UNIXTABLE	6
#define PMEM_STEAL	7
#define PMEM_MANAGED	8
#define PMEM_CFGMGMT	9
#define PMEM_LOCKS	10
#define PMEM_LOGS	11
#define PMEM_VMTABLES	12
#define PMEM_KDEBUG 	13
#define PMEM_PMAP 	14
#define PMEM_GH 	15
#define PMEM_USE_NTYPE 	16

#define PMEM_USE_TYPE {	\
        "hole",		\
        "consmem",	\
        "text",		\
        "data",		\
        "bss",		\
        "scavenge",	\
        "unixtable",	\
        "stealmem",	\
        "managed",	\
        "cfgmgmt",	\
        "locks",	\
        "logs",		\
        "vmtables",	\
        "kdebug",	\
        "pmap",		\
        "gh",		\
}

#define PMEM_TYPESIZE   16

/*
 * physical memory use structure
 */

struct pmem_use {
	vm_offset_t		start;		/* start addr */
	vm_offset_t		end;		/* end addr */
	int			type;		/* mem use type */
	struct pmem_use 	*next;		/* pointer to next element */
};

typedef struct pmem_use *pmem_use_t;

/*
 * This structure describes a "region" of contiguous memory.  On a typical
 * system this is all of physical memory.  On a system with holes there
 * will be multiple such regions.
 *
 * The start address is an aligned offset into physical memory.  The pmr_shift
 * value is used to index into the table based on physical address.
 */
typedef struct pmap_memory_region {
	vm_offset_t		pmr_avail;	/* pa of first managed page */
	long			pmr_pages;	/* managed page count */
	union pv_list_head 	*pmr_pvh;	/* pv head table */
	struct vm_page		*pmr_vmp;	/* vm page array */
	struct vm_page		**pmr_vmc;	/* vm page color buckets */
	struct vm_page		*pmr_tested;	/* highest tested page */
	vm_offset_t		pmr_base;	/* base phys addr of region */
	vm_size_t		pmr_size;	/* size of memory region */
} pmr_t;

/*
 * Physical memory region data (remains constant after boot-up).
 */
struct pmr_data {
	int	pmr_count;	/* number of physical memory regions */
	int	pmr_shift;	/* phys addr to pmr index shift factor */
	pmr_t	*pmr_table;	/* pointer to table of pmap_memory_region's */
	pmr_t	pmr_no_holes;	/* sole pmr table entry if there are no holes */
};

/*
 * Macros for accessing the memory descriptor based on physical address.
 */
#ifdef _KERNEL
#define PA_TO_MRI(pa)	((pa) >> pmr_data.pmr_shift)
#define PA_TO_MRP(pa)	(&pmr_data.pmr_table[PA_TO_MRI(pa)])
#define PA_INDEX(pa)	(alpha_btop((pa) - PA_TO_MRP(pa)->pmr_avail))
#define PA_TO_VP(pa)	(&PA_TO_MRP(pa)->pmr_vmp[PA_INDEX(pa)])
#define pa_to_pvh(pa)	(&PA_TO_MRP(pa)->pmr_pvh[PA_INDEX(pa)])
#define managed(pa)	((pa) >= avail_start && (pa) < avail_end)
#endif /* _KERNEL */

/*
 * Virtual address size data (remains constant after boot-up)
 */
struct vas_data {
	int		vas_nvabits;	/* number of virtual address bits */
	int		vas_ext_vabits;	/* extended virtual address bits */
	int		vas_seg0_shift;	/* number of variable SEG0 bits */
	int		vas_seg1_shift;	/* number of variable SEG1 bits */
	vm_offset_t	vas_kseg_base;	/* base address of KSEG segment */
	vm_offset_t	vas_seg1_base;	/* base address of SEG1 segment */
};

/*
 *	Macros
 */

#ifdef	KERNEL

#define vtopte(v)	(&Selfmap[((vm_offset_t)(v) & ADDRESS_MASK) >> PGSHIFT])
#define Root_pt		vtopte(vtopte(Selfmap))

/*
 * Macros replaced by functions (in pal_lib.s).
 */
#ifdef	_KERNEL
extern vm_offset_t phys_to_kseg();
extern vm_offset_t kseg_to_phys();
#define PHYS_TO_KSEG(addr) phys_to_kseg(addr)
#define KSEG_TO_PHYS(addr) kseg_to_phys(addr)
#else	/* _KERNEL */
#define PHYS_TO_KSEG(addr) ((vm_offset_t)(addr) + UNITY_BASE)
#define KSEG_TO_PHYS(addr) ((vm_offset_t)(addr) - UNITY_BASE)
#endif	/* _KERNEL */

/*
 * pmap_context is not a noop because we need to load the pcb with the
 * asn from the map, and that asn may have changed.
 */

#define PMAP_CONTEXT(pmap, new_thread, my_cpu) pmap_activate(pmap, new_thread, my_cpu)

#define PMAP_ACTIVATE(pmap, th, my_cpu) pmap_activate(pmap, th, my_cpu)

#define PMAP_DEACTIVATE(pmap, thread, cpu) pmap_deactivate(pmap, thread, cpu)

/*
 * LIVE_CPU_P should be in ./cpu.h.  It is a predicate which is true
 * when "cpu_no" can receive and could acknowledge an interprocessor
 * interrupt.
 */
#define LIVE_CPU_P(cpu_no)						\
	(cpu_to_processor(cpu_no)					\
	 && (cpu_to_processor(cpu_no)->state != PROCESSOR_OFF_LINE)	\
	 && (cpu_to_processor(cpu_no)->state != PROCESSOR_SHUTDOWN))

#if	NCPUS > 1

#define INVALIDATE_ASNS(pmap)	((pmap)->new_asn |= ~(pmap)->active_on)
#define PMAP_UPDATE(pmap, addr)	((!multicpu) ? INVALIDATE_ASNS(pmap) : \
					pmap_update_send((pmap), (addr)))
struct pmap_update_info {
	int             from_cpu[2];
	vm_offset_t     addr[2];
	memory_atom	shoot_pending;
	unsigned int	xcpu_intrs;
};

#else	/* NCPUS == 1 */

       /* don't understand this.  seems to me that INVALIDATE_ASNS
	  should be the same for NCPUS == 1 and > 1
	  for one cpu the setting of new_asn should be depndent
	  on whether that map is active on that cpu.
	  all testing on warp5 is with ncpus = 16 !
	  also, its plain wrong to always clear the 0 bit -
	  it should be set if the pmap is not active.
	  This main explain some data corruption...
	  */

#define INVALIDATE_ASNS(pmap)		((pmap)->new_asn = ~1L)
#define PMAP_UPDATE(pmap, addr)		(INVALIDATE_ASNS(pmap))
#define pmap_update_info_init()

#endif	/* NCPUS */

struct pmap_seg {
	simple_lock_data_t
			ps_seglock;		/* Segment lock */
	unsigned short	ps_refcnt;		/* Segment ref count */
	unsigned short	ps_rescnt;		/* Segment resident count */
	unsigned int	ps_loadedpte;		/* Ptes in page table */
	vm_offset_t	ps_pagetable;		/* Page table */
	struct pv_entry *ps_pvsegment;		/* PV for segment */
};

typedef struct pmap_seg * pmap_seg_t;
#define	PMAP_SEG_NULL	((pmap_seg_t) 0)

/*
 * Support for large SystemV shared memory
 */
#ifdef	ALPHA_VARIABLE_PAGE_SIZE
# not implemented
#else

/*
 * The following supports 8Meg shared data segments.
 */
#define	SSM_SHIFT		23		
#define	SSM_SIZE		(1L << SSM_SHIFT)
#define	SSM_MASK		((SSM_SIZE) - 1)

#define	SSM_ROUND(va)		(((va) + SSM_MASK) & ~SSM_MASK)
#define	SSM_TRUNC(va)		((va) & ~SSM_MASK)
#define	VA_TO_SSM(va)		((va) >> SSM_SHIFT)
#define	SSM_TO_VA(va)		((va) << SSM_SHIFT)
#define	PAGES_PER_SSM		(1L << (SSM_SHIFT - PGSHIFT))

struct pmap_ssm {
	decl_simple_lock_data	(,pss_lock)	 /* Segment lock */
	unsigned int		pss_rescnt;	 /* Segment resident count */
	unsigned int		pss_loadedpte[2];/* Ptes in page table */
	vm_offset_t		pss_pagetable[2];/* Page tables */
	struct pv_entry		*pss_pvlist;	 /* list of mappers */
};

/*
 * Page table indexes.
 */
#define	PT_READ	0
#define	PT_RDWR	1

typedef struct pmap_ssm *pmap_ssm_t;
#endif

/*
 *	For each vm_page_t, there is a list of all currently
 *	valid virtual mappings of that page.  An entry is
 *	a pv_entry_t; the lists' heads are in the pv_table.
 *
 *	Rather than maintain separate arrays for lock, modify,
 *	and reference bits, we steal the three low-order bits
 *	of the virtual address field in each list header.  It
 *	works because operations on the virtual address are really
 *	operations on the virtual page number, and the low-order
 *	bits are "noise".
 */

struct pv_entry {
	union {				 /* overlaid with pv_bits (below) */
		vm_offset_t	_pv_va;	 /* va for this mapping */
		struct vm_page	*_pv_pg; /* vm page for this (pte)page */
	} _upv0;
	union {
		pmap_t		_pv_pmap;	/* pmap where mapping lies */
		pmap_seg_t	_pv_seg;	/* segment */
		pmap_ssm_t	_pv_ssm;	/* shared data segment */
		int		_pv_mappings;	/* valid mapping count */
	} _upv1;
	struct pv_entry	*pv_next;	/* next pv_entry */
};

#define	pv_va		_upv0._pv_va
#define	pv_pg		_upv0._pv_pg
#define	pv_pmap		_upv1._pv_pmap
#define	pv_seg		_upv1._pv_seg
#define	pv_ssm		_upv1._pv_ssm
#define	pv_mappings	_upv1._pv_mappings

struct pvh_lock {
        void    *pad0;
        void    *pad1;
        void    *pad2;
        simple_lock_data_t      lock;
};

#define pvhlock         pvh_lock.lock

union pv_list_head {
	struct pvh_lock pvh_lock;
	long bits;
#define PV_BIT_UNLOCK	1L /* assumed to be lowest order bit in atomic_ops.s */
#define PV_BIT_MODIFY	2L
#define	PV_BIT_REF	4L
	struct pv_entry	entry;
};

#define PV_BITS	(PV_BIT_UNLOCK | PV_BIT_MODIFY | PV_BIT_REF)

#define PV_LIST_HEAD_NULL ((union pv_list_head *) 0)

typedef struct pv_entry *pv_entry_t;
#define	PV_ENTRY_NULL	((pv_entry_t) 0)



/*
 * Steal bit 3 of the VA to identify the pv entry as belonging to a segment.
 * We chose 3 because bits 0 thru 2 are being used in the pv head for other
 * purposes.  Also bit 3 will be preserved because it will be treated a part
 * of the VA.  Same for bit 4.
 */

#define	PV_SEGFLAG	0x00000008L	/* Ored in pv_va for seg id. */
#define	PV_SSM		0x00000010L	/* segmented shared memory */

/*
 * Enable segmentation
 */

#define	PMAP_SEGMENTATION	1

#define	PMAP_SEG_SIZE		(PTES_PER_PAGE * ALPHA_PGBYTES)
#define	PMAP_SEG_MASK		((PMAP_SEG_SIZE) - 1)

#define	pmap_seg_lock(SP)	simple_lock(&(SP)->ps_seglock)
#define	pmap_seg_lock_try(SP)	simple_lock_try(&(SP)->ps_seglock)
#define	pmap_seg_unlock(SP)	simple_unlock(&(SP)->ps_seglock)

#define PMAP_COPROC_INVALIDATE_STLB	0
#define PMAP_COPROC_EXIT		1

#define PDEVCMD_ONE     PMAP_COPROC_INVALIDATE_STLB
#define PDEVCMD_ALL     PMAP_COPROC_EXIT

#define ALL_THRESHHOLD	(1<<20)

#define pmap_set_coproc_tbi(pmap, func, arg)		\
do {							\
	(pmap)->coproc_tbi = func;			\
	(pmap)->coproc_arg = arg;			\
} while (0)

#define pmap_clear_coproc_tbi(pmap)				\
	if ((pmap)->coproc_tbi) {				\
		(*(pmap)->coproc_tbi)(PDEVCMD_ALL, 0,		\
					(pmap)->coproc_arg);	\
		(pmap)->coproc_tbi = (int(*)())NULL;		\
		(pmap)->coproc_arg = (void *)NULL;		\
	} else

#define pmap_load           pmap_mmu_load
#define pmap_unload         pmap_mmu_unload
#define pmap_tb             pmap_mmu_tb
#define svatophys           pmap_svatophys
#define tbsync              pmap_tbsync

#define TB_SYNC_NONE        1
#define TB_SYNC_LOCAL       2
#define TB_SYNC_ALL         4

typedef unsigned int        vm_tbop_t;

_BEGIN_CPLUSPLUS
extern void pmap_pagemove __((vm_offset_t, vm_offset_t, vm_size_t));
_END_CPLUSPLUS

#define pmap_pageable(p_map, sva, eva, pageable)
#define	pmap_resident_count(pmap)	((pmap)->stats.resident_count)
#define pmap_resident_text(pmap)	((pmap)->stats.resident_text)
#define pmap_resident_data(pmap)	(pmap_resident_count(pmap)	\
					 - pmap_resident_stack(pmap)	\
					 - pmap_resident_text(pmap))

#define	pmap_phys_address(frame)	((vm_offset_t) (alpha_ptob(frame)))
#define pmap_phys_to_frame(phys)	((int) (alpha_btop(phys)))
#define pmap_copy(dst,src,from,len,to)
#define pmap_update()
#define pmap_kernel()			kernel_pmap

#if defined(_USE_KERNEL_INTRINSICS) 
#define	mtpr_tbis(vaddr)	asm("call_pal 51", 3, vaddr)
#define	mtpr_tbisi(vaddr)	asm("call_pal 51", 1, vaddr)
#define	mtpr_tbisd(vaddr)	asm("call_pal 51", 2, vaddr)
#define	mtpr_tbia()		asm("call_pal 51", -2L)
#define	mtpr_tbiap()		asm("call_pal 51", -1L)
#else
#define	mtpr_tbis(vaddr)	mtpr_tbi(3, vaddr)
#define	mtpr_tbisi(vaddr)	mtpr_tbi(1, vaddr)
#define	mtpr_tbisd(vaddr)	mtpr_tbi(2, vaddr)
#define	mtpr_tbia()		mtpr_tbi(-2L)
#define	mtpr_tbiap()		mtpr_tbi(-1L)
#endif /* _USE_KERNEL_INTRINSICS */

/*
 * Return values from pmap_lw_unwire_new()
 */
#define	LWU_SUCCESS	0
#define	LWU_HW_WIRE	1	/* has upper-level (heavy weight) wirings */
#define	LWU_AMBIGUOUS	2	/* shared pte has upper-level wirings */

/*
 * Indexes into proto_ptepage_ptetab[] (must be consistent with IS_SYS_VA)
 */
#define PT_USER	0	/* pte pages which support user space mappings */
#define PT_KERN	1	/* pte pages which support only kernel mappings */

/*
 * Data structures this module exports
 */
#ifdef	_KERNEL
extern pmap_t kernel_pmap;		/* pointer to the kernel pmap */
extern int free_ptepages_count;		/* number of free pte pages */
extern int nonseg_free_ptepages_count;	/* scavenged free pte pages */
extern int kernel_ptepages_count;	/* number of kernel pte pages */
extern int pmem_use_count;		/* count of pmem_use structures */
extern pmem_use_t pmem_use_head;	/* head of pmem_use linked list */
extern vm_offset_t virtual_avail;	/* lowest avail kernel virtual addr */
extern vm_offset_t virtual_end;		/* highest avail kernel virtual addr */
extern vm_offset_t avail_start;		/* first available physical address */
extern vm_offset_t avail_end;		/* last available physical addr + 1 */
#ifndef	PMAP_INIT
extern const struct pmr_data pmr_data;	/* physical memory region data */
extern const struct vas_data vas_data;	/* virtual address size data */
#endif	/* PMAP_INIT */
#endif	/* _KERNEL */

#endif	/* KERNEL */
#endif	/* !ASSEMBLER */
#endif	/* _PMAP_MACHINE_ */
