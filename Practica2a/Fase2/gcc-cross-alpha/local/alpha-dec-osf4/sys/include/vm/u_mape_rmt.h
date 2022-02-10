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
 * @(#)$RCSfile: u_mape_rmt.h,v $ $Revision: 1.1.11.3 $ (DEC) $Date: 1997/05/02 02:00:45 $
 */


#ifndef	__U_MAPE_RMT__
#define	__U_MAPE_RMT__ 1

#include <kern/queue.h>
#include <vm/u_mape_rmr.h>


struct vm_rmt_object {

	/* first five fields must be same as rmr_object */
	/* first seven fields must be same as rmd_object */

        struct vm_object object;   

	struct vm_context *ctx;
	vm_size_t size;            
	unsigned int RM_index;
	unsigned int flags; 
	queue_t mappers;
	decl_simple_lock_data(,mappers_lock)

  	unsigned int pct_flags;
	int target_id;
};

struct vm_rm_xmit_mappers {
	queue_chain_t chain; /* keep first */
	vm_map_t map;
	vm_offset_t start;
};

typedef struct vm_rmt_object *vm_rmt_object_t;
#define	VM_RMT_OBJECT_NULL	(vm_rmr_object_t) 0


        
#endif	/* __U_MAPE_RMT__ */
