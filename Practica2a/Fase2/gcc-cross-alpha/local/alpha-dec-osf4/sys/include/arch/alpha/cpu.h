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

#ifndef	_CPU_H_
#define	_CPU_H_

#ifndef ASSEMBLER

typedef unsigned long cpumask_t; /* bit mask of cpus (NCPUS must be <= 64) */

#ifdef KERNEL

extern int ncpus;	/* the highest available cpu number plus one */
extern int multicpu;	/* flag set just before starting secondaries */
extern int master_cpu;	/* the cpu number of the master (or boot) cpu */
extern int master_cpuid;/* the whami register value of the master cpu */
extern int cpus_in_box;	/* the number of processors present in the system */

#include <cpus.h>
#include <rt_preempt.h>
#include <mach/alpha/vm_param.h>

/*
 * The following cpu_number() interfaces retrieve the current cpu number as
 * efficiently as possible.  The cpu number is stored in the pcb_current_cpu
 * field of the pcb.  When the system has been booted for uniprocessor
 * operation (lockmode 0 or 1), the get_cpu_number_patch() routine patches
 * a "bis" instruction in place of the call to assign the master cpu number
 * into v0 without making a function call or memory reference.  When the
 * system has been booted for multiprocessor operation (lockmode 2, 3, or
 * 4), an "ldl" instruction is used for patching to fetch the value out of
 * the pcb.
 *
 * If a code sequence needs to use the cpu number without the risk of a
 * kernel preemption, the cpu_number_locked() and cpu_number_unlock() macros
 * can be used to temporarily disable kernel preemption.  When the system has
 * been booted with real time preemption disabled (lockmode 0 or 2), the
 * lock_cpu_number_patch() and unlock_cpu_number_patch() routines patch a
 * no-op instruction in place of the call to avoid future calls.  When the
 * system has been booted with real time preemption enabled (lockmode 1, 3,
 * or 4), an "stl" instruction is used for patching to assign a non-zero or
 * zero flag value into the pcb_curcpu_lock field of the pcb.  This kernel
 * preemption disabling facility must not be used at interrupt level.
 *
 * The 3 patching routines reside in locore.s.
 */

#if NCPUS > 1 || RT_PREEMPT

#define cpu_number() \
	(get_cpu_number_patch(get_sp()))
#define cpu_number_locked() \
	(lock_cpu_number_patch(get_sp()), get_cpu_number_patch(get_sp()))
#define cpu_number_unlock() \
	(unlock_cpu_number_patch(get_sp()))

#else

#define cpu_number()		(0)
#define cpu_number_locked()	(0)
#define cpu_number_unlock()

#endif /* NCPUS > 1 || RT_PREEMPT */

#define cause_ast_check(cpu)	intrpt_cpu((cpu), IPI_SCHED)
void intrpt_cpu(int, int);

#endif /* KERNEL */

/*
 * Generic Machinecheck Stack Frame
 */
struct mcframe	{
	int	mc_bcnt;		/* byte count */
	int	mc_summary;		/* summary parameter */
};

#define cpu_exitproc	cpu_archdep.cp_exitproc
#define cpu_idleproc	cpu_archdep.cp_idleproc
#define	cpu_inisr	cpu_archdep.cp_inisr

#define splextreme()	swap_ipl(SPLEXTREME)
#define spl7()		swap_ipl(SPLEXTREME)
#define spldevrt()	swap_ipl(SPLDEVRT)
#define spl6()		swap_ipl(SPLHIGH)
#define splhigh()	swap_ipl(SPLHIGH)
#define splsched()	swap_ipl(SPLSCHED)
#define splvm()		swap_ipl(SPLDEVHIGH)
#define splshootdown()	swap_ipl(SPLCLOCK)
#define splclock()	swap_ipl(SPLCLOCK)
#define	splsoftclock()	swap_ipl(SPLSOFTC)

#define spldevhigh()	swap_ipl(SPLDEVHIGH)
#define spl5()		swap_ipl(SPLDEVHIGH)
#define spltty()	swap_ipl(SPLTTY)
#define splimp()	swap_ipl(SPLIMP)
#define splbio()	swap_ipl(SPLBIO)
#define splmemchn()     swap_ipl(SPLMEMCHN)
#define spldevlow()	swap_ipl(SPLDEVLOW)
#define splnet()	swap_ipl(SPLNET)
#define splsoftc()	swap_ipl(SPLSOFTC)
#define spl1()		swap_ipl(SPL1)

#define spl0()		swap_ipl_preempt_check(SPLNONE)
#define splnone()	swap_ipl_preempt_check(SPLNONE)
#define splx(S)		swap_ipl_preempt_check(S)

#define spl0_nopreempt()  swap_ipl(SPLNONE)
#define splx_nopreempt(S) swap_ipl(S)

#if defined(_USE_KERNEL_INTRINSICS)
#define wmb()		asm("wmb")
#define mtpr_fen(S)	asm("call_pal 43", S)
#define mtpr_usp(S)	asm("call_pal 56", S)
#define mfpr_usp()	asm("call_pal 58")
#define implver()	asm("implver %v0")
#define ecb(va)		asm("ecb (%a0)", va)
#define wh64(va)	asm("wh64 (%a0)", va)
#define amask(mask)	asm("amask %a0, %v0", mask)
#endif /* _USE_KERNEL_INTRINSICS */

#endif /* !ASSEMBLER */


/* #define MISS_TICK_CHECK 
 *
 * by uncommenting this define and rebuilding spl.s, locore.s, 
 * and machdep.c, will enable code that will detect code sequences 
 * where the IPL is kept at clock or above for longer then a clock 
 * tick (see cpu_miss_tick_debug in file machdep.c).
 */


/*
 * OSF PAlcode has 8 levels 0..7
 *
 *	7	machine check
 *	6	realtime device interrupt
 *	5	clock and ip interrupts
 *	4	device level 1 interrupts
 *	3	device level 0 interrupts
 *	2	software level 1 interrupts
 *	1	software level 0 interrupts
 *	0	any interrupt
 */
#define SPLEXTREME	7
#define SPLDEVRT	6
#define SPLCLOCK	5
#define SPLHIGH		5
#define SPLSCHED	5
#define SPLDEVHIGH	4
#define SPLTTY		4
#define SPLIMP	   4 /* because of SLIP interface, splimp must be >= spltty */
#define SPLBIO		4
#define SPLMEMCHN       4
#define SPLDEVLOW	3
#define SPLNET		2		/* software (soft net) */
#define SPLSOFTC	1		/* software (soft clock) */
#define SPL1		1
#define SPLNONE		0		/* no interrupts blocked */

/*
 * Flags for the nofault handler. 0 means no fault is expected.
 */
#define	NF_BADADDR	1	/* badaddr, wbadaddr */
#define	NF_COPYIO	2	/* copyin, copyout */
#define	NF_ADDUPC	3	/* addupc */
#define	NF_FSUMEM	4	/* fubyte, subyte, fuword, suword */
#define	NF_USERACC	5	/* useracc */
#define	NF_SOFTFP	6	/* softfp */
#define	NF_REVID	7	/* revision ids */
#define	NF_COPYSTR	8	/* copyinstr, copyoutstr */
#define	NF_SOFTFPI	9	/* fp instr fetch */
#define NF_SIGRETURN_COPYIN 10	/* copyin errors for sigreturn */ 
#define NF_SENDSIG_COPYOUT 11	/* copy out errors for sendsig */ 
#define NF_LWERR        12      /* faults in pmap_lw_wire */
#define NF_LW_UNERR     13      /* faults in pmap_lw_unwire */
#define NF_LW_UNERR_ASS 14      /* faults in pmap_lw_unwire */
#define NF_LWERR_ASS    15
#define NF_PTEFETCH	16	/* pmap_fault_on() */
#define NF_LW_UNERR_OTHER_MAP 17 /* faults in pmap_lw_unwire_other_map */
#define	NF_COPYIO_TRY	18	/* copyin_try */
#define NF_DART         19	/* DART hook */
#define NF_NXM_UPCALL	20	/* used by nxm_upcall */
#define NF_NEW_LW_ERR           21
#define NF_NEW_LW_UN_ERR       22
#define NF_REMOVE_WIRED_FAST	23
#define NF_NENTRIES	24

/*
 * State bits for the kernel global "printstate"
 */
#define PROMPRINT 0x1		/* only print available is thru PROM */
#define CONSPRINT 0x2		/* print thru console device driver available */
#define MEMPRINT  0x4		/* print to errlog available */
#define PANICPRINT 0x8		/* panic in progress, print to screen */

/*
 * IP interrupt bit numbers
 */
#define IPI_PANIC	0	/* panic */
#define IPI_KM_TLBSHOOT	1	/* kernel map TLB shootdown */
#define IPI_SCHED	2	/* cause resched */
#define IPI_PRINTF	3	/* printf from secondary */
#define IPI_HALT	4	/* halt secondary */
#define IPI_KDEBUG	5	/* kdebug breakpoint */
#define IPI_PFM		6	/* performance monitor request */
#define IPI_PCC		7	/* microsecond timing pcc synch */
#define IPI_UM_TLBSHOOT	8	/* User map TLB shootdown */
#define	IPI_HOLD	9	/* hold a cpu until released */
#define IPI_IMB		10	/* flush icache */
#define IPI_MAX		11

/* MCES Register bit defines per ECO's #45/#51 */
#define MCES_MCK 0x1	/* Clear machine check flag */
#define MCES_SCE 0x2	/* Clear system corrected error flag */
#define MCES_PCE 0x4	/* Clear processor correct error flag */
#define MCES_DPC 0x8	/* Disable processor corrected error reporting */
#define MCES_DSC 0x10	/* Disable system corrected error reporting */
#define MCES_DISABLE	(MCES_DPC|MCES_DSC)	/* Disable both PCE/SCE */

#endif /* _CPU_H_ */
