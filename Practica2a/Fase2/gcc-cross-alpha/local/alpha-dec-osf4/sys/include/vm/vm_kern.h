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
 *	@(#)$RCSfile: vm_kern.h,v $ $Revision: 4.2.18.2 $ (DEC) $Date: 1995/10/17 17:03:17 $
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
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 *	File:	vm/vm_kern.h
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Kernel memory management definitions.
 *
 *	Revision History:
 *
 * 8-Apr-91	Ron Widyono
 *	Delay inclusion of sys/preempt.h (for RT_PREEMPT) to avoid circular
 *	include file problem.
 *
 */

#ifndef	_VM_VM_KERN_H_
#define _VM_VM_KERN_H_
#include <mach/kern_return.h>
#include <sys/types.h>
#include <vm/vm_map.h>

#define	M_PRIV	0x1000	/* privilege MALLOC allocation  */

/*
 * flag values for kernel_memory_allocate()
 */
#define	KMA_HERE	0x01	/* base address given, else "anywhere" */
#define	KMA_NOPAGEWAIT	0x02	/* don't wait for pages if unavailable */
#define	KMA_NOZEROFILL	0x04	/* don't need zero-filled memory */
#define KMA_TIMEDWAIT	0x08	/* don't wait forever for memory */

extern void		kmem_init();
extern kern_return_t	kernel_memory_allocate();
extern vm_offset_t	kmem_alloc();
extern vm_offset_t	kmem_stack_alloc();
extern vm_offset_t	kmem_alloc_pageable();
extern void		kmem_free();
extern void		kmem_stack_free();
extern vm_map_t		kmem_suballoc();
extern vm_map_t		kmem_csuballoc();

extern vm_map_t		kernel_map;
extern vm_map_t		kernel_pageable_map;
extern vm_map_t		kernel_copy_map;
extern vm_map_t		user_pt_map;

extern vm_offset_t	vm_kern_zero_page;	/* A page full of nothing */

/* Flags for VM use */

#define VM_MAP_SPACE_ANYWHERE   1
#define VM_MAP_SPACE_RM         2
                                               
#endif	/* _VM_VM_KERN_H_ */
