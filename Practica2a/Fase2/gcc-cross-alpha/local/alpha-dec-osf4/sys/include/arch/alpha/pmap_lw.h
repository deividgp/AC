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
 * @(#)$RCSfile: pmap_lw.h,v $ $Revision: 1.1.16.2 $ (DEC) $Date: 1999/01/23 16:20:05 $
 */

#ifndef _PMAP_LW_H_
#define _PMAP_LW_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#ifdef _KERNEL
#include <vm/vm_map.h>
#endif
#include <machine/pmap.h>

#define	LWW_MASK 0x20000L
#define VALID_MASK 0x1L
#define SEG_MASK 0x40000L
#define VM_FULL_WIRE 0x8000000000000000

extern int pmap_lw_wire __((pmap_t, vm_offset_t, int, u_long *, u_long));
extern int pmap_lw_unwire __((pmap_t, vm_offset_t, int));
extern void pmap_get_pfns __((pmap_t, vm_offset_t, int, u_long *));
extern void lw_init __((void));

#ifdef _KERNEL
extern long pmap_lw_wire_new(pmap_t, vm_offset_t, long, int *,
				vm_prot_t, boolean_t);
#endif

#ifdef __cplusplus
}
#endif
#endif /* _PMAP_LW_H_ */
