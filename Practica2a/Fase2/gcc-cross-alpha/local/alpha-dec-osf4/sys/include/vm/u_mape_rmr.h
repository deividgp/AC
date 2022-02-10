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
 * @(#)$RCSfile: u_mape_rmr.h,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 1997/05/02 02:00:44 $
 */

#ifndef	__U_MAPE_RMR__
#define	__U_MAPE_RMR__ 1



#define VM_RM_LINKS_LOCK(obj) \
       if(obj->ob_type == OT_RM_U_RCV || obj->ob_type == OT_RM_K_RCV) 	\
            simple_lock(&((vm_rmr_object_t)obj)->links_lock);		\
       else								\
            vm_object_lock(obj);

#define VM_RM_LINKS_UNLOCK(obj) \
       if(obj->ob_type == OT_RM_U_RCV || obj->ob_type == OT_RM_K_RCV) 	\
            simple_unlock(&((vm_rmr_object_t)obj)->links_lock);		\
       else								\
            vm_object_unlock(obj);



struct vm_context {
	vm_object_t * object_map_recv;
	simple_lock_data_t object_map_recv_lock;
	vm_object_t * object_map_trans;
	simple_lock_data_t object_map_trans_base_lock;
	simple_lock_data_t object_map_trans_intr_lock;
	vm_object_t * object_map_dual;
	simple_lock_data_t object_map_dual_base_lock;
	simple_lock_data_t object_map_dual_intr_lock;
	int * object_map_recv_hold;
	int size;
	volatile vm_offset_t base_address;
	simple_lock_data_t base_address_lock;
	int init_state;
	int logical_rail;
	int physical_rail;
};


struct vm_rmr_object {

	/* first five fields must be same as rmt_object */

        struct vm_object object;

	struct vm_context *ctx;
	vm_size_t size;
	unsigned int RM_index;  /* stored scrubbed */
	unsigned int flags; 

	vm_offset_t original_offset;
	vm_offset_t original_start;		/* used for existing obj mapping */
	vm_map_t original_map;
	unsigned int pct_flags;
	struct vm_rmr_object * link_obj;
	decl_simple_lock_data	(,links_lock)
	struct vm_rmr_object * next;
	struct vm_rmr_object * prev;
};

typedef struct vm_rmr_object *vm_rmr_object_t;
#define	VM_RMR_OBJECT_NULL	(vm_rmr_object_t) 0

struct vm_rm_args {
	struct vm_context *ctx;
	vm_offset_t va;
	vm_size_t size;
	unsigned int RM_index;
	unsigned int flags;
	int target_id;
};

        
#endif	/* __U_MAPE_RMR__ */
