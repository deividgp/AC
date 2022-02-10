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
 * @(#)$RCSfile: context.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1995/07/28 21:21:11 $
 */

#ifndef _ALPHA_CONTEXT_H
#define _ALPHA_CONTEXT_H

#ifndef ASSEMBLER

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
#define __XSE(__bar) __bar
#else
#define __XSE(__bar) __##__bar
#endif

/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to properly restore state if
 * a non-standard exit is performed.
 */

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
struct  sigcontext {
#else 
struct  _sigcontext {
#endif

	/*
	 *  Backward compatibility -- correlates with user space
	 *  notion of layout.
	 */
	long    __XSE(sc_onstack);		/* sigstack state to restore */
	long    __XSE(sc_mask);		/* signal mask to restore */
	long	__XSE(sc_pc);			/* pc at time of signal */
	long	__XSE(sc_ps);			/* psl to retore */
	long	__XSE(sc_regs)[32];		/* processor regs 0 to 31 */
	long	__XSE(sc_ownedfp);		/* fp has been used */
	long	__XSE(sc_fpregs)[32];		/* fp regs 0 to 31 */
	unsigned long __XSE(sc_fpcr);		/* floating point control register */
	unsigned long __XSE(sc_fp_control);	/* software fpcr */
	/*
	 * END OF REGION THAT MUST AGREE WITH jmp_buf REGION IN setjmp.h
	 */
	long __XSE(sc_reserved1);		/* reserved for kernel */
	int __XSE(sc_kreserved1);		/* reserved for kernel */
	int __XSE(sc_kreserved2);		/* reserved for kernel */
#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
#define sc_sp	sc_regs[R_SP]
#endif
	size_t	__XSE(sc_ssize);		/* stack size */
	caddr_t	__XSE(sc_sbase);		/* stack start */
	unsigned long __XSE(sc_traparg_a0);	/* a0 argument to trap on exception */
	unsigned long __XSE(sc_traparg_a1);	/* a1 argument to trap on exception */
	unsigned long __XSE(sc_traparg_a2);	/* a2 argument to trap on exception */
	unsigned long __XSE(sc_fp_trap_pc);	/* imprecise pc  */
	unsigned long __XSE(sc_fp_trigger_sum); /* Exception summary at trigger pc */
	unsigned long __XSE(sc_fp_trigger_inst); /* Instruction at trigger pc */
};

#endif  /* __ASSEMBLER__ */

#endif /* _ALPHA_CONTEXT_H */
