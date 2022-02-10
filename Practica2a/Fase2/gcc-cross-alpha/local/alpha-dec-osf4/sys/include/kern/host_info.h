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
#ifndef	_KERN_HOST_INFO_H_
#define	_KERN_HOST_INFO_H_

#include <mach/host_info.h>
#include <kern/macro_help.h>
#ifdef notdef
extern host_paging_info_data_t	vm_stat;
#endif
/*
 * Lock to protect the data stored in the vm_stat structure.
 * It might scale better to eliminate the locks and make the data
 * be per-cpu.
 */
decl_simple_lock_data(extern,vm_stat_lock)
#define	VM_STAT_LOCK()		simple_lock(&vm_stat_lock)
#define	VM_STAT_UNLOCK()	simple_unlock(&vm_stat_lock)

#define VM_STAT(event)				\
MACRO_BEGIN					\
			VM_STAT_LOCK();		\
			vm_stat.event++;	\
			VM_STAT_UNLOCK();	\
MACRO_END

#endif	/* _KERN_HOST_INFO_H_ */
