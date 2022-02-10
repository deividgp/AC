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
 * @(#)$RCSfile: vm_ubc.h,v $ $Revision: 1.1.10.2 $ (DEC) $Date: 1998/03/31 21:12:30 $
 */
#ifndef	__MACHINE_VM_UBC__
#define	__MACHINE_VM_UBC__ 1
#include <machine/cpu.h>
#include <vm/vm_debug.h>

#define ubc_kmem_alloc(PP) 
#define ubc_kmem_free(PP)
#define ubc_kmem_cache(PP) FALSE
#define	ubc_load(PP, OFFSET, SIZE) PHYS_TO_KSEG(page_to_phys(PP))
#define	ubc_unload(PP, OFFSET, SIZE)
#define	ubc_page_zero(PP, O, S)						\
	bzero(PHYS_TO_KSEG(page_to_phys((PP))) + (O) , (S))

#define	ubc_page_referenced(PP)						\
	pmap_is_referenced(page_to_phys(PP))
#define	ubc_page_clear_reference(PP) 					\
	pmap_clear_reference(page_to_phys(PP))

#if	UBC_PAGE_CHECK

#undef	ubc_load
#undef	ubc_page_zero
#define ubc_load(PP, OFFSET, SIZE) 					\
	ubc_load_page_check(PP, OFFSET, SIZE)
#define	ubc_page_zero(PP, O, S) 					\
	ubc_page_zero_page_check(PP, O, S)

#endif	/* UBC_PAGE_CHECK */

#endif	/* !__MACHINE_VM_UBC__ */
