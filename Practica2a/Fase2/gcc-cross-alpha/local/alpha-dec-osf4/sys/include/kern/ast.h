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
 *	@(#)$RCSfile: ast.h,v $ $Revision: 4.2.19.3 $ (DEC) $Date: 1997/01/20 13:21:58 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

/*
 *	kern/ast.h: Definitions for Asynchronous System Traps.
 *
 *	Revision History:
 *
 * 6-Apr-91	Ron Widyono
 *	Implement Kernel mode ASTs for preemption points.  Per-processor
 *	flag ast_mode[] indicates whether an AST request is User mode or 
 *	Kernel mode.  Conditionalized under RT_PREEMPT.
 *
 */

/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */

/*
 *	kern/ast.h: Definitions for Asynchronous System Traps.
 */

#ifndef	_KERN_AST_H_
#define _KERN_AST_H_
#ifdef __cplusplus
extern "C" {
#endif

/*
 *	There are two types of AST's:
 *		1.  This thread must context switch [call thread_block()]
 *		2.  This thread must do something bizarre
 *			[call thread_halt_self()]
 *
 *	Type 2 ASTs are kept in a field in the thread which encodes the
 *	bizarre thing the thread must do.
 *
 *	The need_ast array (per processor) records whether ASTs are needed
 *	for each processor.  For now each processor only has access to its
 *	own cell in that array.  [May change when we record which 
 *	processor each thread is executing on.]
 *
 *	need_ast is initialized from the thread's ast field at context
 *	switch.  Type 1 ASTs are entered directly into the field
 *	by aston().  The actual values in need_ast do not matter, 
 *	an ast is required if it is non-zero.
 */

#ifdef _KERNEL
#include <cpus.h>
#include <hw_ast.h>
#endif

#include <machine/cpu.h>

/*
 *	Bits for reasons
 */

#define	AST_ZILCH		0x0
#define AST_HALT		0x1
#define AST_TERMINATE		0x2
/*#define AST_PROFILE		0x4  For future use */
#define AST_SUSPEND		0x8
#define AST_SIGEXIT		0x10
#define AST_BIND_CPU		0x20
/* 
 * following are defined in machine/ast.h
 * #define AST_SCHED_KERNEL 	0x40	
 * #define AST_SCHED_USER   	0x80
 */
#define AST_SIGPROF		0x100
#define AST_SET_PRIORITY 	0x200
#define AST_SIGCREDIT		0x400
#define AST_SIGVTALRM		0x800
#define AST_SIGXCPU		0x1000
#define AST_BLOCKED_UPCALL 	0x2000
#define AST_NXM_QUANTUM_EXP	0x4000
#define AST_SIGNAL_UPCALL 	0x8000
#define AST_NXM_INTERRUPT 	0x10000
#define AST_PRSTOP 		0x20000
#define AST_NXM_RESCHED		0x40000
#define AST_UCOPY		0x80000
#define AST_NXM_MANAGER		0x100000

/*
 * Machines with hardware support (e.g. vax) turn on HW_AST option.
 * This causes all type 1 ast support to be pulled in from machine/ast.h.
 */
#ifdef _KERNEL
#if	HW_AST
#include <machine/ast.h>
#else	/*HW_AST*/

extern int	need_ast[NCPUS];

/*
 *	Type 1 ASTs
 */
#define	aston()		need_ast[cpu_number()] = 1
#define astoff()	need_ast[cpu_number()] = 0

#endif	/*HW_AST*/
/*
 *	Type 2 ASTs
 */
#define	thread_ast_set(thread, reason) 				\
{								\
	(thread)->ast |= (reason);				\
	if ((thread) == current_thread())			\
		ast_propagate((thread), current_cpu());		\
}

#define thread_ast_clear(thread, reason)	(thread)->ast &= ~(reason)
#define thread_ast_clear_all(thread)	(thread)->ast = AST_ZILCH

/*
 *	NOTE: if thread is the current thread, thread_ast_set should
 *	be followed by aston() 
 */

#if	HW_AST
/*
 *	machine/ast.h must define versions of these macros.
 */
#else	/*HW_AST*/
/*
 *	Macros to propagate thread asts to need_ast at context switch and
 *	clock interrupts.  (Context switch replaces old ast requests,
 *	clock interrupt reflects new requests from thread to need_ast.
 *
 *	NOTE: cpu is always the current cpu.  It is in these macros
 *	solely to avoid recalculating it on machines where that may
 *	be expensive.
 */

#define	ast_context(thread, cpu)	need_ast[(cpu)] = (thread)->ast
#define	ast_propagate(thread, cpu)	need_ast[(cpu)] |= (thread)->ast
#define	ast_needed(cpu)			need_ast[(cpu)]
#endif	/*HW_AST*/
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif	/*_KERN_AST_H_*/
