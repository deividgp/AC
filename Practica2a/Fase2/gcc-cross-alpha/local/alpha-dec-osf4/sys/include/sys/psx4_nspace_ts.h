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
 * @(#)$RCSfile: psx4_nspace_ts.h,v $ $Revision: 1.1.4.4 $ (DEC) $Date: 1996/02/09 22:03:58 $
 */
/*
 * psx4_nspace_ts.h
 *
 * This file contains the definitions for name space handler for the POSIX 
 * 1003.4/D14 IPC and Counting Semaphores.  This file is the thread-safe
 * counterpart of the draft 11 psx4_nspace.h file.
 */

#ifndef _PSX4_NSPACE_H_TS
#define _PSX4_NSPACE_H_TS 1
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#include <sys/limits.h>

#define SUCCESS  0
#define FAILURE -1
#define TRUE  1
#define FALSE 0
#ifndef NULL
#define NULL  0L
#endif

/* Values for flags argument to p4_find_entry_by_key_ts() */
#define PSX4_LOCK_ENTRY 1
#define PSX4_UNLOCK_ENTRY 0

/* The following is the counting semaphore structure defined
 * in semaphore.h.  It is redefined locally so that semaphore.h
 * doesn't have to be included.  This lock type is used for
 * key table locks and for IPC queue locks.  
 * IF THE DEFINITION IS MODIFIED IN SEMAPHORE.H THEN THIS NEEDS TO BE MODIFIED 
 */
typedef struct psx4_mycsem{
  int semval;                   /* value of the semaphore */
  int semcnt;                   /* # of blocked processes on this semaphore */
  char semname [SEM_NAME_MAX];  /* semaphore name, null-terminated */
}psx4_mycsem_t;

/* Key table lock type, statically allocated in the utility library */
typedef struct psx4_mycsem rtlock_t;
   
/* States of the rtlock counting semaphore used as a mutex */
#define  RTLOCK_LOCKED     0    /* semval is locked when less than 1 */
#define  RTLOCK_UNLOCKED   1	/* semval is unlocked when 1 */

/* 
 * Pass a 0 to the rt_lock/unlock_mutex calls.  It is a currently
 * unused, but if 0 then it means the lock is a key table lock.
 * The key table locks are ONLY needed in a multi-threaded
 * process.  If _THREAD_SAFE is not defined, then this is not
 * a multi-threaded process, and the lock/unlock routines can
 * be defined to be NOP's in the following macros:
 */
#ifdef _THREAD_SAFE
#define RT_LOCK_MUTEX(rt_lock_ptr) rt_lock_mutex(rt_lock_ptr,0)
#define RT_UNLOCK_MUTEX(rt_lock_ptr) rt_unlock_mutex(rt_lock_ptr,0)
#else
#define RT_LOCK_MUTEX(rt_lock_ptr) 0
#define RT_UNLOCK_MUTEX(rt_lock_ptr) 0 
#endif

typedef unsigned short psx4_key_version_t;
typedef unsigned short psx4_key_index_t;

typedef struct psx4_key 
    {
    psx4_key_index_t index;	/* Index of entry */
    psx4_key_version_t version;	/* Version number of key */
    } psx4_key_t;
 
/*
 * These macros isolate knowledge of the format of the key.  
 */
#define PSX4_KEY_INDEX(k) (k).index
#define PSX4_SET_KEY_INDEX(k,v) (k).index = v
#define PSX4_KEY_INDEX_OUTRANGE(key,kt) ((key).index >= (kt)->entry_cnt)
#define PSX4_KEY_VERSION(k) (k).version
#define PSX4_SET_KEY_VERSION(k,v) (k).version = v
#define PSX4_KEY_VERSION_MAX 65535
#define PSX4_KEYS_EQUAL(k1,k2) \
  (((k1).index == (k2).index) && ((k1).version == (k2).version))

#define PSX4_GET_ENTRY(kt, index) (void *)((char *)kt->entry + (kt->entry_size * index))      

typedef struct psx4_key_entry{
       char                  *name;     /* object name -- for debugging only */
       void                  *object;   /* virtual address of object     */
       psx4_key_t            key;       /* valid key (contains version)  */
       pid_t                 pid;       /* process id                    */
       int                   state;    	/* Is this entry available?      */
#define PSX4_KEY_STATE_FREE 0
#define PSX4_KEY_STATE_INUSE 1
#define PSX4_KEY_STATE_MARKED_FOR_DELETE 2
       dev_t   		     st_dev;   /* ID of device containing a directory*/
                                       /*   entry for this file.  File serial*/
                                       /*   no + device ID uniquely identify */
                                       /*   the file within the system 	     */
       ino_t   		     st_ino;   /* File serial number */
       rtlock_t   	     entry_lock; /* entry lock */
       int		     in_use_cnt; /* in-use reference count */
/* IPC specific information: */
       int		     access;     /* local send/receive access to ipc queue */
/* Semaphore specific information */
/* Allocated address of sem_t, returned in multiple opens */
       psx4_key_t            sem_usemdes; /* user level semaphore descriptor */
       uint_t                st_gen; 	  /* file generation number */
     }psx4_key_entry_t;

/*  The purpose of psx4_key_table is to provide a process level binding to  
 *  the object. NOTE that the key table and the descriptors are
 *  in PROCESS space because they are created at the user level.
 *  There must be a separate key table PER PROCESS PER NAMESPACE.
 */
typedef struct psx4_key_table{
       ushort		entry_cnt;   	/* Number of key entries total in the
				      	 *  table */
       ushort   	entry_size;  	/* size of key entry */
       void     	*entry; 	/* start of array of descriptor 
					 * entries */
     }psx4_key_table_t;


#define PSX4_KEY_ENTRY_NULL ((psx4_key_entry_t *)0)
#define PSX4_KEY_TABLE_NULL ((void *)0)

/* Routines in psx4_nspace_ts.c: */

#include <sys/stat.h>

/*
 * Routine definitions
 */
int  p4_return_key_entry_ts __((psx4_key_table_t *kt_ptr,psx4_key_entry_t *ke));

int  p4_get_unique_entry_ts __((psx4_key_table_t **kt_ptr_ptr, \
     rtlock_t *kt_lock_ptr,int num_entries, \
     void *object_va, char *name, struct stat *file_stat, psx4_key_t *desc, \
     psx4_key_entry_t **ke_ptr, int *entry_is_locked_ptr, int *ref_is_incremented_ptr, \
     int *new_entry_ptr));

psx4_key_entry_t *p4_find_entry_by_key_ts __((psx4_key_table_t *kt_ptr, \
     psx4_key_t desc, int flags, \
     int *entry_is_locked_ptr, int *ref_is_incremented_ptr));

psx4_key_entry_t *p4_find_entry_by_id_ts __((psx4_key_table_t *kt_ptr, \
    struct stat *file_stat, int flags, int *entry_is_locked_ptr, \
    int *ref_is_incremented_ptr, int *status));

int  p4_create_key_table_ts __((psx4_key_table_t **kt_ptr_ptr, \
     rtlock_t *kt_lock_ptr,int cnt,int size));

int  p4_desc_cleanup_ts __((psx4_key_table_t *kt_ptr, psx4_key_entry_t *ke, \
     int object_size, int *entry_is_locked_ptr, int *ref_is_incremented_ptr));

int  p4_lock_desc __((psx4_key_entry_t *ke,int *entry_is_locked_ptr));

int  p4_unlock_desc __((psx4_key_entry_t *ke,int *entry_is_locked_ptr));

int  p4_delete_entry __((psx4_key_entry_t *ke, psx4_key_table_t *kt_ptr, \
     int object_size));

int  rt_lock_mutex __((rtlock_t *rt_lock,int lock_type));

int  rt_unlock_mutex __((rtlock_t *rt_lock,int lock_type));

int  rt_init_mutex __((rtlock_t *rt_lock));

/* Non-threadsafe routine -- needed by sem_post() to post a semaphore
 * without locking the entry, in order to be reentrant from a signal
 * handler
 */
psx4_key_entry_t *p4_find_entry_by_key_nts __((psx4_key_table_t *kt_ptr, \
     psx4_key_t desc));

#ifdef __cplusplus
}
#endif
#endif /* PSX4_NSPACE_H_TS */

