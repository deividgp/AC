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
 * @(#)$RCSfile: sp_attr.h,v $ $Revision: 1.1.3.11 $ (DEC) $Date: 1995/11/09 22:39:53 $
 */

#ifndef	   __SP_ATTR__

#define __SP_ATTR__

#include <sys/types.h>
#include <sys/acl_def.h>
#include <kern/lock.h>
#include <sys/uio.h>


/*
 * Used for telling the operation type for access decisions.  These
 * flags may be or'd togther.
 */

#define ATTR_NOTHING		0	/* Indicates no additional access
					   checks. */
#define ATTR_RETRIEVE		1	/* Indicates additional access checks required 
					   for retrieving the attribute. */
#define ATTR_SET		2	/* Indicates additional access checks required
					   for setting the attribute */
#define ATTR_DELETE		4	/* Indicates additional access checks required
					   for deleting the attribute */


/*
 * The following defines are used in two distinct case.
 *	1) The attr being returned from pacl_fs_get (attirbute_t *)
 *	2) Pointer to the entry in the cache (ir_entry_t *)
 */

#define NO_ATTR         (caddr_t) -1
#define UNKNOWN_ATTR_VAL    (caddr_t) -2
#define MULTIPLE_ATTRS    (caddr_t) -3		/* The attr in the vn will
						 * never be set to this, only
					 	 * functions that may
						 * retrieve more then 1 attr
						 * will use this.
						 */

#define NUMB_IR_CHARS	4		/* This is used to make it very clear
					 * the padding that goes on in the
					 * attribute_t.
					 *
					 * If attribute_t.ir is defined as 1 we still
					 * will allocate the same space as if
					 * attribute_t.ir was defined as 4 because
					 * padding.
					 *
					 * NUMB_IR_CHARS is used in the 
					 * calculation of the size of the
					 * attr with no ir present.
					 */

typedef struct {
        int version;
        int ir_length;            	/* length of internal representation */
        uchar_t  ir[NUMB_IR_CHARS];     /* internal representation pointer, this
					   is expected to be address aligned. */
} attribute_t;

/*
 * note that we subtract the NUMB_IR_CHARS out of the attribute_t, this is because it
 * is already represented in the ir length
 */

#define ATTR_SIZE 	(sizeof(attribute_t) - NUMB_IR_CHARS)

typedef  ulong_t attr_mask_t;

#define NUMBER_SP_ATTRS 3


typedef struct {
        caddr_t acl_attr[NUM_ACL_IR_TYPES];
	lock_data_t     secattr_lock;   /* Protects the attribute_t struct */
	int             ref_count;      /* Number of threads ref this  */
	int             flag;           /* Used to indicate the various 
					 * possible states of the attribute_t
					 * data.  See below for a list of
					 * flags.
					 */
} secinfo_t;

#define ATTR_RMBIT(m,b)      m &= ~BIT_IN_WORD(b)


#ifdef	   KERNEL

extern struct uio *	alloc_setproplist_data(attr_mask_t mask,
					       attribute_t * attr);
extern attribute_t *	dup_sec_attr(attribute_t *);
extern int		build_attr_name(attr_mask_t, char **);

#define	SECATTR_OK		0	/* v_secattr is ok */
#define	SECATTR_REMOVE		1	/* v_secattr is marked for removal */

#endif	/* KERNEL */
#endif	/* __SP_ATTR__ */
