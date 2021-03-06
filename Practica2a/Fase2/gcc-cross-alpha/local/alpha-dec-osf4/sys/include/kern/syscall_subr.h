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
 *	@(#)$RCSfile: syscall_subr.h,v $ $Revision: 4.2.27.2 $ (DEC) $Date: 1998/10/30 16:48:39 $
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

#ifndef	_KERN_SYSCALL_SUBR_H_
#define _KERN_SYSCALL_SUBR_H_

#include <mach_emulation.h>
#include <mach_sctimes.h>

#include <mach/port.h>
#include <mach/kern_return.h>

extern	port_t		task_by_pid();
extern	kern_return_t	init_process();

extern int	swtch();
extern boolean_t	swtch_pri(int);
extern int	semop_fast(long, long, long, long);
extern int	thread_switch();

extern int	map_fd();

extern kern_return_t lw_wire();
extern kern_return_t lw_unwire();
extern kern_return_t lw_syscall();

extern kern_return_t nxm_task_init();
extern kern_return_t nxm_sched_thread();
extern kern_return_t nxm_idle();
extern kern_return_t nxm_wakeup_idle();
extern kern_return_t nxm_set_pthid();
extern kern_return_t nxm_thread_kill();
extern kern_return_t nxm_thread_block();
extern kern_return_t nxm_thread_wakeup();
extern kern_return_t nxm_resched();
extern kern_return_t nxm_set_cancel();
extern kern_return_t nxm_thread_create();
extern kern_return_t nxm_get_state();
extern kern_return_t nxm_signal_check();
extern kern_return_t nxm_thread_suspend();
extern kern_return_t nxm_thread_resume();
extern kern_return_t nxm_get_psetinfo();
extern kern_return_t nxm_get_binding();
extern kern_return_t nxm_set_binding();

#if	MACH_EMULATION
extern int	htg_unix_syscall();
#endif	

#if	MACH_SCTIMES
extern kern_return_t mach_sctimes_0();
extern kern_return_t mach_sctimes_1();
extern kern_return_t mach_sctimes_2();
extern kern_return_t mach_sctimes_3();
extern kern_return_t mach_sctimes_4();
extern kern_return_t mach_sctimes_5();
extern kern_return_t mach_sctimes_6();
extern kern_return_t mach_sctimes_7();
extern kern_return_t mach_sctimes_8();
extern kern_return_t mach_sctimes_9();
extern kern_return_t mach_sctimes_10();
extern kern_return_t mach_sctimes_11();
extern kern_return_t mach_sctimes_port_alloc_dealloc();
#endif	

#endif	/* _KERN_SYSCALL_SUBR_H_ */
