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
 * @(#)$RCSfile: pfcntr.h,v $ $Revision: 1.1.32.3 $ (DEC) $Date: 1999/02/12 17:15:58 $
 */
#include <sys/types.h>
#include <sys/ioctl.h>

#ifndef _PFCNTR_H_
#define _PFCNTR_H_


/*
 * Sparse definition of the iccsr register.  Only the bits we can actually
 * change are set.  The rest are in `ignore' fields.
 */
struct iccsr {				/* ev4 iccsr register encoding */
	ulong	iccsr_pc1:1,
		iccsr_ign0:2,
		iccsr_pc0:1,
		iccsr_ign1:4,
		iccsr_mux0:4,
		iccsr_ign2:20,
		iccsr_mux1:3,
		iccsr_disable:2,
		iccsr_ign3:27;
};


/*
 * These are the driver's counts of interrupts not the chip's
 * count of events.  First the EV4 version, arg for PCNTGETCNT:
 */
struct pfcntrs {
	ulong	pf_cntr0;		/* driver's counter 1		*/
	ulong	pf_cntr1;		/*   ""		""  2		*/
	ulong	pr_cycle;		/* process cycle counter	*/
};
/* Now the EV5 version, arg for PCNT5GETCNT: */
struct pfcntrs_ev5 {
	ulong	pr_cycle;	/* process cycle counter */
	ulong	pf_cntr0;	/* driver's first counter */
	ulong	pf_cntr1;	/* driver's second counter */
	ulong	pf_cntr2;	/* driver's third counter */
};

/*
 * These are address ranges for user profiling.
 */
struct addr_range {
	ulong start;			/* Starting text address */
	ulong end;			/* Ending text address */
};

typedef struct {
	ulong start;			/* Starting text address */
	ulong end;			/* Ending text address */
	ulong stride;			/* Number of instructions / bucket */
	ulong res0;			/* Reserved for future use */
} addr_range_t;


/*
 * These unions are used to build an argument for PCNT?SETCTRS
 * or to decode the return from PCNT?GETCTRS.
 */

#define PMCTRS_ALL_CPUS		0xFF

union pmctrs_ev5 {
    ulong	pmctrs_ev5_long;
    struct {
	ulong	pmctrs_ev5_s_sel:  3,
				:  5,
		pmctrs_ev5_s_cpu:  8,
		pmctrs_ev5_s_c2 : 14,
				:  2,
		pmctrs_ev5_s_c1 : 16,
		pmctrs_ev5_s_c0 : 16;
    } pmctrs_ev5_struct;
};

#define pmctrs_ev5_select	pmctrs_ev5_struct.pmctrs_ev5_s_sel
#define pmctrs_ev5_cpu		pmctrs_ev5_struct.pmctrs_ev5_s_cpu
#define pmctrs_ev5_cntr0	pmctrs_ev5_struct.pmctrs_ev5_s_c0
#define pmctrs_ev5_cntr1	pmctrs_ev5_struct.pmctrs_ev5_s_c1
#define pmctrs_ev5_cntr2	pmctrs_ev5_struct.pmctrs_ev5_s_c2

union pmctrs_ev6 {
    ulong	pmctrs_ev6_long;
    struct {
	ulong	pmctrs_ev6_s_sel:  2,
				:  4,
		pmctrs_ev6_s_c1 : 20,
				:  2,
		pmctrs_ev6_s_c0 : 20,
				:  8,
		pmctrs_ev6_s_cpu:  8;
    } pmctrs_ev6_struct;
};

#define pmctrs_ev6_select	pmctrs_ev6_struct.pmctrs_ev6_s_sel
#define pmctrs_ev6_cpu		pmctrs_ev6_struct.pmctrs_ev6_s_cpu
#define pmctrs_ev6_cntr0	pmctrs_ev6_struct.pmctrs_ev6_s_c0
#define pmctrs_ev6_cntr1	pmctrs_ev6_struct.pmctrs_ev6_s_c1



/*
 * There are three modes for opening the counter device
 * These are designed to bitwise OR in with O_RDONLY on the open */
#define PCNTOPENONE	0100000		/* Only open this CPU */
#define PCNTOPENEACH	0200000		/* Separate all CPUs */
#define PCNTOPENALL	0300000		/* Aggregate all CPUs */
#define PCNTOPENMASK	0300000		/* Mask for these mode bits */

/*
 * These are the items that can be counted.
 * Set them with PCNTSETITEMS ioctl().
 */
#define PFM_COUNTERS	1	/* Counters only (default) */
#define PFM_IPL		2	/* Collect IPL statistics */
#define PFM_PROFILING	4	/* User or Kernel PC samples */

#ifdef KERNEL
/* Pseudo-states: closed, and which type of profiling to use */
#define PFM_CLOSED	0	/* Driver is closed */
#define PFM_KSAMPLES	8	/* Kernel PC samples */
#define PFM_USAMPLES	16	/* User PC samples */
#define PFM_CALLER	32	/* Use caller (ra) with KSAMPLES */
#define PFM_MASK	7	/* Mask of three modes */
#endif	/* KERNEL */


/* Alpha base family independent ioctl's: */

#define PCNTRDISABLE     _IO('P',  0)                       /* disable the performance counters */
#define PCNTRENABLE      _IO('P',  1)                       /* enable the performance counters */
#define PCNTLOGALL       _IO('P',  3)                       /* count all processes */
#define PCNTLOGSELECT    _IO('P',  4)                       /* count only those with enable set */
#define PCNTCLEARCNT     _IO('P',  5)                       /* clear driver counters */
#define PCNTCLEARPCBPME  _IO('P',  7)                       /* clear this procs PCB_PME_BIT */
#define PCNTCALLER	 _IO('P',  8)			    /* Use RA from utility routines when KPROFILING */
#define PCNTGETRSIZE    _IOR('P', 10, long)                 /* get ring size */
#define PCNTGETIPLHIS   _IOW('P', 11, struct pfipls *)      /* collect IPL histograms */
#define PCNTSETITEMS    _IOW('P', 31, long)                 /* Set items to count */
#define PCNTSETUADDR    _IOW('P', 32, struct addr_range)    /* Set user address range */
#define PCNTSETKADDR    _IOW('P', 33, struct addr_range)    /* Set kernel address range */
#define PCNTSETURANGE   _IOW('P', 34, addr_range_t)         /* Set user address range w/ variable stride */
#define PCNTSETKRANGE   _IOW('P', 35, addr_range_t)         /* Set kernel address range w/ variable stride */

/* EV4 specific ioctl's:  */

#define PCNTSETMUX      _IOW('P',  2, struct iccsr)         /* set mux bits */
#define PCNTGETCNT      _IOW('P',  6, struct pfcntrs *)     /* read driver cntrs */

/* EV5 specific ioctl's:  */

#define PCNT5CTXTS      _IOW('P', 40, long)                 /* Set contexts in which to count */
#define PCNT5MUX        _IOW('P', 41, long)                 /* Set items to count */
#define PCNT5FREQ       _IOW('P', 42, long)                 /* Set counts per interrupt */
#define PCNT5DISABLE    _IOW('P', 43, long)                 /* Disable selected counters */
#define PCNT5ENABLE     _IOW('P', 44, long)                 /* Enable selected counters */
#define PCNT5CLEAR      _IOW('P', 45, long)                 /* Zero selected counters */
#define PCNT5RESTART    _IOW('P', 46, long)                 /* Zero and enable selected counters */
#define PCNT5SETCNTRS   _IOW('P', 47, long)                 /* Write selected counters */
#define PCNT5GETCNTRS  _IOWR('P', 48, long)                 /* Read all the counters on cpu*/
#define PCNT5GETCNT     _IOW('P', 49, struct pfcntrs_ev5 *) /* read driver cntrs */

/* EV6 specific ioctl's:  */

#define PCNT6MUX        _IOW('P', 51, long)                 /* Set items to count */
#define PCNT6ENABWRITE  _IOW('P', 52, long)                 /* Write and enable selected counters */
#define PCNT6DISABLE    _IOW('P', 53, long)                 /* Disable selected counters */
#define PCNT6ENABLE     _IOW('P', 54, long)                 /* Enable selected counters */
#define PCNT6CLEAR      _IOW('P', 55, long)                 /* Zero selected counters */
#define PCNT6RESTART    _IOW('P', 56, long)                 /* Zero and enable selected counters */
#define PCNT6SETCNTRS   _IOW('P', 57, long)                 /* Write selected counters */
#define PCNT6GETCNTRS  _IOWR('P', 58, long)                 /* Read all the counters on cpu*/
#define PCNT6GETCNT     _IOW('P', 59, struct pfcntrs *)     /* read driver cntrs */


/*
 * The following are EV4 specific multiplexor definations
 *
 * mux0 definitions
 */
#define PF_ISSUES	0x0	/* total issues/2			*/
#define PF_PIPEDRY	0x2	/* pipeline dry, ie lack of valid i-str	*/
#define PF_LOADI	0x4	/* load instructions			*/
#define PF_PIPEFROZEN	0x6	/* pipeline frozen, resource conflicts	*/
#define PF_BRANCHI	0x8	/* branch, and function calls		*/
#define PF_CYCLES	0xa	/* total cycles				*/
#define PF_PALMODE	0xb	/* cycles while executing palcode	*/
#define PF_NONISSUES	0xc	/* non_issues / 2			*/
#define PF_EXTPIN0	0xe	/* external pin, platform specific	*/

/*
 * mux1 definitions
 */
#define PF_DCACHE	0x0	/* data cache misses			*/
#define PF_ICACHE	0x1	/* instruction cache misses		*/
#define PF_DUAL		0x2	/* dual issue				*/
#define PF_BRANCHMISS	0x3	/* branch mispredictions		*/
#define PF_FPINST	0x4	/* floating point operate instructions	*/
#define PF_INTOPS	0x5	/* integer operations			*/
#define PF_STOREI	0x6	/* store instructions			*/
#define PF_EXTPIN1	0x7	/* external pin, platform specific	*/

/* Values for struct iccsr iccsr_pc0 (counter 0 "frequency"): */
#define PF_C0_INT_EVERY_65536	0	/* interrupt every 65536 mux0 events */
#define PF_C0_INT_EVERY_4096	1	/* interrupt every 4096 mux0 events */

/* Values for struct iccsr iccsr_pc1 (counter 1 "frequency"): */
#define PF_C1_INT_EVERY_4096	0	/* interrupt every 4096 mux1 events */
#define PF_C1_INT_EVERY_256	1	/* interrupt every 256 mux1 events */

/*
 * The following are EV5 specific constants for use in ioctl arguments:
 * 
 * First, please note some things with regard to limiting count collection
 * to specific processing modes . . . .
 * 
 * There are four hardware modes:  Kernel, Executive, Supervisor, and User.
 * Digital Unix uses only two modes:  Kernel and User.  To limit count
 * collection to Kernel mode events, use PF5_CTXT_KERNEL (below).  User
 * mode, however, looks to the palcode like the hardware Executive mode.
 * This means that User mode event counts are collected as Executive counts.
 * Moreover, to collect statistics only during Executive and Supervisor
 * events (i.e. only Executive events on Unix since there are no Supervisor
 * events), you actually specify all modes.  So, to limit count collection
 * exclusively to User mode events, you should use PF5_CTXT_EXEC_AND_SUPER
 * (below) to select only Executive mode counting which will really give you
 * only the User mode counts.
 */

/* PCNT5CTXTS arguments, choose one of: */

#define PF5_CTXT_SEL_PROC	1	/* only profile processes
					   whose PME bit is set. */
#define PF5_CTXT_PME_THIS	2	/* set the PME bit in this
					   process. */
#define PF5_CTXT_ALL_PROC	0	/* profile all processes */
#define PF5_CTXT_THIS_PROC	3	/* profile this process (set
					   PME and selective) */
/* and either any collection of these: */

#define PF5_CTXT_NO_USER	0x40000000	/* events occuring in
						   user mode are
						   ignored. */
#define PF5_CTXT_NO_PAL		0x200	/* events occuring in pal mode
					   are ignored. */

#define PF5_CTXT_NO_KERNEL	0x100	/* events occuring in kernel,
					   executive, and supervisor
					   mode are ignored. */
/* or exactly one of these: */

#define PF5_CTXT_USER		0x300	/* only profile user */
#define PF5_CTXT_PAL		0x40000100	/* only profile pal */
#define PF5_CTXT_USER_AND_PAL	0x100	/* profile user and pal */
#define PF5_CTXT_KERNEL		0x40000200	/* executive and
						   supervisor are
						   implied */
#define PF5_CTXT_USER_AND_KERNEL	0x200	/* executive and
						   supervisor are
						   implied */
#define PF5_CTXT_PAL_AND_KERNEL		0x40000000 	/* executive
							   and
							   supervisor
							   are implied */
#define PF5_CTXT_ALL_MODES		0	/* executive and
						   supervisor are
						   implied */
#define PF5_CTXT_EXEC_AND_SUPER	0x40000300	/* only executive and
						   supervisor */

/*
 * PCNT5MUX arguments.
 * choose one of (counter 0 counts) (on EV5, EV56, and PCA56):
 */
#define PF5_MUX0_CYCLES	0	/* cycles */
#define PF5_MUX0_ISSUES	0x80000000	/* instructions */

/* and one of (counter 1 counts) (on EV5, EV56, and PCA56): */
#define PF5_MUX1_NON_ISSUE_CYCLES	0	/* non-issue cycles */
#define PF5_MUX1_SPLIT_ISSUE_CYCLES	0x10	/* split issue cycles */
#define PF5_MUX1_PIPELINE_DRY	0x20	/* pipe-dry cycles */
#define PF5_MUX1_REPLAY_TRAP	0x30	/* replay traps */
#define PF5_MUX1_SINGLE_ISSUE_CYCLES	0x40	/* cycles with one issue */
#define PF5_MUX1_DUAL_ISSUE_CYCLES	0x50	/* cycles with two issues */
#define PF5_MUX1_TRIPLE_ISSUE_CYCLES	0x60	/* cycles with three issues */
#define PF5_MUX1_QUAD_ISSUE_CYCLES	0x70	/* cycles with four issues */
#define PF5_MUX1_FLOW_CHANGE	0x80	/* non-inline flow (brances, etc.) */
#define PF5_MUX1_INTEGER_OPERATE	0x90	/* integer ops */
#define PF5_MUX1_C_FP_INSTRUCTIONS	0xA0	/* floating ops */
#define PF5_MUX1_C_LOAD_INSTRUCTIONS	0xB0	/* loads */
#define PF5_MUX1_C_STORE_INSTRUCTIONS	0xC0	/* stores */
#define PF5_MUX1_C_ICACHE_ACCESS	0xD0	/* Icache accesses */
#define PF5_MUX1_C_DCACHE_ACCESS	0xE0	/* Dcache accesses */
#define PF5_MUX1_C_BCACHE_VICTIM 0x300000000000F0 /* Bcache victims */
/* On a normal EV5 or EV56 */
#define PF5_MUX1_C_SCACHE_ACCESS	0xF0	/* Scache accesses */
#define PF5_MUX1_C_SCACHE_READ	  0x80000000000F0 /* Scache reads */
#define PF5_MUX1_C_SCACHE_WRITE	 0x100000000000F0 /* Scache writes */
#define PF5_MUX1_C_SCACHE_VICTIM 0x180000000000F0 /* Scache victims */
#define PF5_MUX1_C_BCACHE_REF	 0x280000000000F0 /* Bcache references */
#define PF5_MUX1_C_SYS_REQ	 0x380000000000F0 /* system requests */
/* But if on a PCA56 */
#define PF5_MUX1_C_BCACHE_READ          0xF0   /* Bcache read operations*/
#define PF5_MUX1_C_BCACHE_DREAD_HIT    0x80000000000F0 /* Bcache Dread hits */
#define PF5_MUX1_C_BCACHE_DREAD_FILL  0x100000000000F0 /* Bcache Dread fills */
#define PF5_MUX1_C_BCACHE_WRITE       0x180000000000F0 /* Write operations */
#define PF5_MUX1_C_BCACHE_CLN_WRT_HIT 0x280000000000F0 /* Clean write hits */
#define PF5_MUX1_C_READ_MISS_2        0x380000000000F0 /* Read miss 2 launch */

/* and one of (counter 2 counts) (on EV5, EV56, and PCA56): */
#define PF5_MUX2_C_LONG_STALLS		0	/* long (> 12 cycles) stalls */
#define PF5_MUX2_C_PC_MISPR		2	/* PC miss predicts */
#define PF5_MUX2_C_BRANCH_MISPREDICTS	3	/* branch miss predicts */
#define PF5_MUX2_C_ICACHE_MISSES	4	/* Icache/RFB misses */
#define PF5_MUX2_C_ITB_MISS		5	/* ITB miss services */
#define PF5_MUX2_C_DCACHE_MISSES	6	/* Dcache LD misses */
#define PF5_MUX2_C_DTB_MISS		7	/* DTB misses */
#define PF5_MUX2_C_LOADS_MERGED		8	/* LDs merged in MAF */
#define PF5_MUX2_C_LDU_REPLAYS		9	/* LDU replays */
#define PF5_MUX2_C_WB_MAF_FULL_REPLAYS	0xA	/* WB/MAF full replays */
#define PF5_MUX2_C_EXTERNAL		0xB	/* external perf_mon input */
#define PF5_MUX2_C_CYCLES		0xC	/* cycles */
#define PF5_MUX2_C_MEM_BARRIER		0xD	/* memory barriers (cycles?) */
#define PF5_MUX2_C_LOAD_LOCKED		0xE	/* load lockeds (cycles?) */
/* On a normal EV5 or EV56 */
#define PF5_MUX2_C_SCACHE_MISS		0xF	/* Scache misses */
#define PF5_MUX2_C_SCACHE_READ_MISS  0x4000000000000F /* Scache read misses */
#define PF5_MUX2_C_SCACHE_WRITE_MISS 0x8000000000000F /* Scache write misses */
#define PF5_MUX2_C_SCACHE_SH_WRITE   0xC000000000000F	/* Scache shared
							   writes */
#define PF5_MUX2_C_SCACHE_WRITE	    0x10000000000000F /* Scache writes */
#define PF5_MUX2_C_BCACHE_MISS	    0x14000000000000F /* Bcache misses */
#define PF5_MUX2_C_SYS_INV	    0x18000000000000F /* system invalidates */
#define PF5_MUX2_C_SYS_READ_REQ	    0x1C000000000000F /* system read requests */
/* But if on a PCA56 */
#define PF5_MUX2_C_BCACHE_DREAD        0xF	/* Bcache Dread operations */
#define PF5_MUX2_C_BCACHE_READ_HIT      0x4000000000000F /* Bcache read hits */
#define PF5_MUX2_C_BCACHE_READ_FILL     0x8000000000000F /* Bcache read fills */
#define PF5_MUX2_C_BCACHE_WRITE_HIT     0xC000000000000F /* Bcache write hits */
#define PF5_MUX2_C_BCACHE_WRITE_FILL   0x10000000000000F /* Bcache write fills*/
#define PF5_MUX2_C_SYS_READ_FLUSH_HIT  0x14000000000000F /* System read/flush
							    bcache hits */
#define PF5_MUX2_C_SYS_READ_FLUSH_MISS 0x18000000000000F /* System read/flush
							    bcache misses */
#define PF5_MUX2_C_READ_MISS_3         0x1C000000000000F /* Rd miss 3 launch */

/* PCNT5FREQ arguments, choose one of (counter 0 "frequency"): */
#define PF5_C0_INT_EVERY_256	0x300	/* interrupt every 256 mux0 events */
#define PF5_C0_INT_EVERY_65536	0x200	/* interrupt every 65536 mux0 events */

/* and one of (counter 1 "frequency"): */
#define PF5_C1_INT_EVERY_256	0xC0	/* interrupt every 256 mux1 events */
#define PF5_C1_INT_EVERY_65536	0x80	/* interrupt every 65536 mux1 events */

/* and one of (counter 2 "frequency"): */
#define PF5_C2_INT_EVERY_256	0x30	/* interrupt every 256 mux2 events */
#define PF5_C2_INT_EVERY_16384	0x20	/* interrupt every 16384 mux2 events */

/*
 * Note that using PF5_Cx_INT_EVERY_256 requires privilege because it is
 * possible -- if the PF5_MUX events are selected carelessly -- to overwhelm
 * the system with too many interrupts.
 */


/*
 * Arguments for PCNT5DISABLE, PCNT5ENABLE, PCNT5RESTART, PCNT5CLEAR,
 * and the select member of the union whose long member is used as the
 * argument for PCNT5SETCTRS.  Choose any combination of:
 */
#define PF5_SEL_COUNTER_0	1	/* Op applies to counter 0 */
#define PF5_SEL_COUNTER_1	2	/* Op applies to counter 1 */
#define PF5_SEL_COUNTER_2	4	/* Op applies to counter 2 */


/*
 * PCNT6MUX arguments; choose one of (counter 0 counts) :
 */

#define PF6_MUX0_CYCLES                0x00	/* cycles */
#define PF6_MUX0_RET_INSTRUCTIONS      0x10	/* retired instructions */

/* and one of (counter 1 counts) : */

#define PF6_MUX1_CYCLES                 0x0	/* cycles */
#define PF6_MUX1_RET_COND_BRANCHES      0x1	/* retired conditional branches */
#define PF6_MUX1_RET_BRANCH_MISPREDICTS 0x2	/* not implemented -- actually cycles */
#define PF6_MUX1_RET_DTB_SINGLE_MISSES  0x3	/* retired dtb single misses (bug -- 2 for each miss in p1) */
#define PF6_MUX1_RET_DTB_DOUBLE_MISSES  0x4	/* retired dtb double misses */
#define PF6_MUX1_RET_ITB_MISSES         0x5	/* retired itb misses */
#define PF6_MUX1_RET_UNALIGNED_TRAPS    0x6	/* retired unaligned traps */
#define PF6_MUX1_REPLAY_TRAP            0x7	/* replay traps */

/* EV6 counter frequencies */
#define PF6_C0_INT_EVERY_1048576	0x0	/* interrupt every 1048576 mux0 events */
#define PF6_C1_INT_EVERY_1048576	0x1	/* interrupt every 1048576 mux1 events */

/* EV6 counter selection bits */
#define PF6_SEL_COUNTER_0	1	/* Op applies to counter 0 */
#define PF6_SEL_COUNTER_1	2	/* Op applies to counter 1 */


/*
 * PCNT67MUX aggregate mode arguments :
 */

#define PF67_RET_INST_AND_CYCLES	0x0	/* PCTR0 <- retired  PCTR1 <- cycles */
#define PF67_CYCLES_AND_UNDEFINED	0x4	/* PCTR0 <- cycles   PCTR1 <- undefined */
#define PF67_RET_INST_AND_BCACHE_MISS	0x8	/* PCTR0 <- retired  PCTR1 <- bcache misses/long probe latency */
#define PF67_CYCLES_AND_REPLAY_TRAPS	0xC	/* PCTR0 <- cycles   PCTR1 <- Mbox replay traps */





#ifdef _KERNEL
/*
 * WRPERFMON functions: values are determined by palcode.
 * The pfm driver assumes the values/functions are the same
 * across alpha base families (e.g. PFOPT = PF5OPT = PF6OPT).
 */
/* EV4 */
#define PFDISABLE	0
#define PFENABLE	1
#define PFSET		2
#define PFOPT		3
/* EV5 */
#define PF5DISABLE	0
#define PF5ENABLE	1
#define PF5MUXSEL	2
#define PF5OPT		3
#define PF5FREQSEL	4
#define PF5READ		5
#define PF5WRITE	6
#define PF5ENABRESET	7
/* EV6 */
#define PF6DISABLE	0
#define PF6ENABLE	1
#define PF6MUXSEL	2
#define PF6OPT		3
/*  no  PF6FREQSEL	4 */
#define PF6READ		5
#define PF6WRITE	6
#define PF6ENABWRITE	7

#define PFRPCC		0x17	/* not wrperfmon, but need to read pcc	*/
#define PF5SETCTRS	0x18	/* not wrperfmon, selected CPU(s) write */
#define PF6SETCTRS	0x28	/* not wrperfmon, selected CPU(s) write */

/* Masks for wrperfmon arguments to get appropriate MBZ fields */

#define PF5_ABLE_KMASK			0x00000007
#define PF5_MUX_KMASK		0x01F80000000000FF
#define PF5_MUX_CBOX_KMASK	0x01F8000000000000
#define PF5_MUX_CBOX_KSHIFT			32
#define PFPCA56_MUX_CBOX_KSHIFT			43
#define PF5_CTXT_KMASK			0x40000301
#define PF5_FREQ_KMASK			0x000003F0
#define PF5_FREQ_KFORCE			0x000002A0
#define PF5_FREQ_FAST_MASK		0x00000150	/* Any high freq bits set? */
#define PF5_WRITE_KMASK		0xFFFFFFFF3FFF0000
#define PF5_CPU_KMASK		0x000000000000FF00

#define PF6_CPU_KMASK		0xFF00000000000000
#define PF6_MUX_KMASK		0x000000000000001F
#define PF6_WRITE_KMASK		0xFF00FFFFF3FFFFC3

#endif /* _KERNEL */

#endif /* _PFCNTR_H_ */

