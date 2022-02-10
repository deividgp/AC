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
 * @(#)$RCSfile: ast.h,v $ $Revision: 1.1.8.5 $ (DEC) $Date: 1995/06/20 19:18:14 $
 */

#ifndef	_ALPHA_AST_ 
#define _ALPHA_AST_ 
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL
#include <rt_preempt.h>
#endif
#include <machine/pcb.h>

#define AST_SCHED_KERNEL 	0x40
#define AST_SCHED_USER		0x80

#ifndef ASSEMBLER

extern int rt_preempt_enabled;

#define ast_context(thread, cpu) {					\
	thread_pcb(thread)->pcb_ast.flags.need_ast = (thread)->ast;	\
}
#define ast_propagate(thread, cpu) \
	get_sp()->pcb.pcb_ast.flags.need_ast |= (thread)->ast

#define ast_needed(cpu) \
	(get_sp()->pcb.pcb_ast.flags.need_ast)

#define sched_kernel_astoff() \
	get_sp()->pcb.pcb_ast.flags.need_ast &= ~AST_SCHED_KERNEL

#define sched_aston() \
	get_sp()->pcb.pcb_ast.flags.need_ast |= \
		(rt_preempt_enabled ? \
			(AST_SCHED_USER | AST_SCHED_KERNEL) : AST_SCHED_USER)

#define aston() \
	get_sp()->pcb.pcb_ast.flags.need_ast |= 1

#define sched_kernel_ast_needed() \
	(get_sp()->pcb.pcb_ast.flags.need_ast & AST_SCHED_KERNEL)

#define sched_ast_needed() \
	(get_sp()->pcb.pcb_ast.flags.need_ast & \
					(AST_SCHED_KERNEL | AST_SCHED_USER))

#define astoff() \
	get_sp()->pcb.pcb_ast.flags.need_ast = 0

#endif 	/* ASSEMBLER */

#ifdef __cplusplus
}
#endif
#endif	/* _ALPHA_AST_ */
