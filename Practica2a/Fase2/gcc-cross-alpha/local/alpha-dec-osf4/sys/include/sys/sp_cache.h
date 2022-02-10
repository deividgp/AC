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
 * @(#)$RCSfile: sp_cache.h,v $ $Revision: 1.1.3.4 $ (DEC) $Date: 1995/10/24 20:32:48 $
 */

#ifndef __SP_CACHE__

#define __SP_CACHE__
#include <sys/lock.h>
#include <sys/types.h>
#include <sys/sp_attr.h>


#define DEFAULT_HASH_MAX	   15   /* Default # of entriess to hash */
#define DEFAULT_BUCKETS		   64   /* Default number of buckets */
#define DEFAULT_THRESHOLD	   32   /* Threshold of slot entries to
                                           expand cache */
#define DEFAULT_MAX_IR_SIZE	  512   /* Default max ir size to store */
#define DEFAULT_MAX_CACHE_SIZE 512000   /* Default max cache size */


#define IR_ENTRY_TO_ATTR(ir_ent) \
		((attribute_t *) ir_ent->ir_rep)

struct  ir_entry {
	attribute_t	 *ir_rep;	/* the actual attribute */
	struct ir_entry  *next_slot;	/* Pointer to the next cache entry */
	struct ir_entry  *prev_slot;  	/* Pointer to the prev cache entry */
	decl_simple_lock_data(,slot_lock)	 /* The lock for this particular
					      	    slot */
	int		 slot_ref;	/* Number references to this slot */
	u_int		 hash_value;	/* Value that this entry hashes to */
};

typedef struct ir_entry ir_entry_t;


typedef struct{
	u_int n_entries;	/* current number of entries in this bucket */
	u_int n_insertions;	/* number of inserts in this bucket */
	u_int n_failures;	/* number of failed inserts in this bucket */
	u_int n_deletions;	/* number of deletions in this bucket */
	u_int n_matches;	/* number of matches in this bucket */
	u_int max_n_entries;	/* maximum number of entries in this bucket */
} bucket_stats_t;

typedef struct{
#ifdef SEC_DYNAMIC
	u_int threshold;		/* Threshold to expand cache at */
#endif
	u_int ir_cache_buckets;		/* Number of buckets in the cache */
	u_int hash_max;  	        /* The max number entries to hash */
	u_int max_cache_size;		/* The largest size of the cache */
	u_int max_ir_size;		/* Max size ir to store */
} cache_policy_config_t;

typedef struct {
	lock_data_t	bucket_lock;	/* The lock for the bucket */
	ir_entry_t	*ir_slot; 	/* Pointer to the slots for this
					   bucket */
	bucket_stats_t	stats;		/* Statistics for this bucket */
} ir_bucket_t;



typedef struct {
	ir_bucket_t 		*ir_buckets; 	  /* Pointer to the hash
						     buckets */
	lock_data_t		cache_gl_lock;	  /* The global lock for the
						     entire cache. */
	cache_policy_config_t	config;		  /* Configuration params */
	u_int			cache_size;	  /* Current size of the 
						     cache */
	int			(* cache_hash)(); /* Pointer to the hash
						     routine for this cache */
	int			(* ir_compare)(); /* Comparison routine for ir
						     entries in the cache. */
} sec_cache_t;

/*
 * Function definitions
 */

extern int		sp_delete_ir(ir_entry_t *, sec_cache_t *);
extern ir_entry_t *	sp_insert_ir(attribute_t *, sec_cache_t *);
extern sec_cache_t *	sp_ir_cache_init(cache_policy_config_t *, int (*)(),
					 int (*)());


#endif
