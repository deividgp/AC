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
	.rdata
	.asciiz "@(#)$RCSfile: entry.s,v $ $Revision: 1.2.28.2 $ (DEC) $Date: 1998/10/30 17:13:22 $"
	.text

#include <assym.s>	     /* RPB_EXT_VA_SIZE: rpb->rpb_ext_va_size offset */
#include <machine/asm.h>
#include <machine/regdef.h>
#include <machine/pal.h>
#include <machine/rpb.h>		/* HWRPB_ADDR */
#include <machine/vmparam.h>

#define VPTBASE	0xfffffffc00000000

#define	VA_43_48_BIT_MODE		/* on by default in this module */

/************************************************************************
 *									*
 *	OSFpalcode version of the entry code				*
 *									*
 ************************************************************************/

/*
 * Kernel entry point table
 */
	.text
	.globl	start
	.ent	start
	.globl	eprol
	.frame	sp,0,ra
	.mask	0,0
/*
 * This is the real entry point for the kernel image.  The boot programs
 * enter here with: a0 = pfn of the first available page, a1 = the ptbr,
 * a2 = argc, and a3 = argv.
 * We are running under OSFpal at this point.
 */
start:
eprol:
	br	zero,_realstart		# starting point of the kernel
	.end
/*
 * saveterm entrypoint used for kernel to reset console hardware
 */
	.globl	saveterm
	.ent	saveterm

saveterm:
	br	zero,do_saveterm	# reset console state on halt
	.end
	
/*
 * This is the restart entry point, which is used to generate a crash dump.
 */
	.globl	restart
	.ent	restart
restart:
	br	zero,doadump		# dump core to dump device	
	.end

/*
 * realstart
 *
 * This routine sets up the global ptr (gp) and calls several kernel
 * initialization routines.
 *
 * It passes along the argc, argv from the bootpath to alpha_init.
 */
	.ent	_realstart
	.frame	sp,8,ra
	.mask	M_RA,-8
	.globl	kgp			# make symbol available to dbx

	.align	3			# force quadword alignment
	.set	noreorder
_realstart:
	lda	sp,-8(sp)
	br	t0, 1f			# addr of pad bytes preceding .quad
kgp:	.quad	_gp
1:	ldq	gp,0(t0)		# load permanent value for gp
	stq	zero,0(sp)		# init start frame for debugger

/*
 * Save argument values passed in by the bootstrap.
 */
	bis	a0,zero,s0		# a0 has first usable pfn
	bis	a1,zero,s1		# a1 has page table root
	bis     a2,zero,s2		# a2 has argc value
	bis     a3,zero,s3		# a3 has argv value

#ifdef VA_43_48_BIT_MODE
	/*
	 * Fix up the global pointer for EV6 if booted in 48-bit VA mode.
	 * CAUTION: Be careful not to access global data before gp is set!
	 */
	ldiq	t1,HWRPB_ADDR		# t1 = 0x10000000 (HWRPB @ 256 MB)
	sra	gp,NVABITS-2,t2		# determine segment of original gp
	ldl	s4,RPB_EXT_VA_SIZE(t1)	# get extended VA size from HWRPB
	addq	t2,2,t3			# set up KSEG-based gp test value
	sll	gp,66-NVABITS,t4	# toss out 23 segment address bits 
	srl	t4,66-NVABITS,t5	# isolate KSEG offset from orig gp
	bic	gp,t5,t6		# isolate segment addr bits of gp
	cmoveq	s4,1,t3			# force branch if not ext va mode
	bne	t3,2f			# branch if shouldn't change gp

	sll	t6,s4,t7		# get extended VA mode KSEG base
	bis	t7,t5,gp		# assign corrected gp value
	stq	gp,0(t0)		# fix up kgp for debugging
2:
#endif /* VA_43_48_BIT_MODE */

	bis	gp,zero,a0		# tell palcode our gp value
	call_pal PAL_wrkgp

/*
 * Setup the entry point addresses for the palcode
 */
	lda	a0,_XentInt_boot	# interrupts
	ldiq	a1,0
	call_pal PAL_wrent

	lda	a0,_XentArith		# arithmetic traps
	ldiq	a1,1
	call_pal PAL_wrent

	lda	a0,_XentMM		# memory management faults
	ldiq	a1,2
	call_pal PAL_wrent

	lda	a0,_XentIF		# instruction faults
	ldiq	a1,3
	call_pal PAL_wrent

	lda	a0,_XentUna		# unaligned accesses
	ldiq	a1,4
	call_pal PAL_wrent

	lda	a0,_Xsyscall		# system calls
	ldiq	a1,5
	call_pal PAL_wrent

	/*
	 * Patch kseg<->phys and is_*_va routines in pal_lib.s.
	 */
#ifdef VA_43_48_BIT_MODE
	zapnot	s4,0x0f,a0		# arg is 0 (43-bit VA) or 5 (48-bit VA)
#else
	bis	zero,zero,a0		# force non-extended VA mode handling
#endif /* VA_43_48_BIT_MODE */
	bsr	ra,ext_va_size_patch	# patch kseg<->phys & is_*_va routines

/*
 * The first usable pfn (in s0) and the current page table base register
 * value (in s1) are passed into alpha_bootstrap, which passes them along
 * to pmap_bootstrap, both of which return the kernel startup ppcb.  This
 * value is used below to switch the kernel's virtual memory mapping.
 *
 * The argc (in s2) and argv (in s3) values passed to "start" are also
 * provided to alpha_bootstrap, which needs to copy the startup arguments
 * from their current location (at old addresses) to kernel storage which
 * will be accessible when the mapping is changed.
 *
 * Note that alpha_bootstrap is invoked under the old mapping, before the
 * kernel's bss is zeroed, and before kdebug can be used.  After it calls
 * kdebug_bootstrap, which copies the reserved-for-software field of the
 * rpb (rpb_software) into the global kernel variable kdebug_bkpt_vector,
 * breakpoints will work.
 */
	bis	s0,zero,a0		# 1st arg is pfn
	bis	s1,zero,a1		# 2nd arg is ptbr
	bis     s2,zero,a2		# 3rd arg is argc
	bis     s3,zero,a3		# 4th arg is argv
	jsr	ra,alpha_bootstrap	# bootstrap the kernel
	bis	v0,zero,s0		# save the proc 0 ppcb
	bis	gp,zero,s1		# save the kernel gp

/*
 * Setup the virtual page table pointer and switch from the boot environment
 * to the kernel startup ppcb.  The two pal calls required must not cross a
 * page boundary because the ITB fill would cause a double machine check.
 * Therefore, there are two copies of the required code sequence, and if the
 * first crosses a page boundary, the second copy will be executed instead.
 */
	lda	t0,(1<<PGSHIFT)-1(zero)	# get address mask for page offset
	lda	t1,pca1			# get address of wrvptptr pal call
	lda	t2,pca2			# get address of swpctx pal call
	ldiq	a0,VPTBASE		# get value to assign into vptbr 
	xor	t1,t2,t3		# identify address bit differences
	bic	t3,t0,t4		# mask off bits within page offset
	bne	t4,2f			# branch if first calls cross page
					# otherwise, execute first sequence
pca1:	call_pal PAL_wrvptptr		# 1: assign vptbr
	bis	s0,zero,a0		# 1: get new ppcb
pca2:	call_pal PAL_swpctx		# 1: swap context
	br	zero,3f			# branch to common code
2:					# here to execute second sequence
	call_pal PAL_wrvptptr		# 2: assign vptbr
	bis	s0,zero,a0		# 2: get new ppcb
	call_pal PAL_swpctx		# 2: swap context
3:					# here to execute common code path
	bis	s1,zero,gp		# restore kernel gp value saved above

/*
 * At this point we're running in the context set up by pmap_bootstrap.
 * Push a zero ra value onto the new stack to parallel what was done at
 * entry.  Then call alpha_init, which calls main(), which starts "init".
 */
	lda	sp,-8(sp)
	stq	zero,0(sp)
	bis     s2,zero,a0              # pass argc,argv
	bis     s3,zero,a1
	jsr	ra,alpha_init		# alpha_init(argc, argv)
1:
	call_pal PAL_halt		# should never return here
	br	zero,1b			#  but if it does
	.end
