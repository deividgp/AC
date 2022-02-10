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
 * @(#)$RCSfile: kds.h,v $ $Revision: 1.1.2.5 $ (DEC) $Date: 1995/12/04 15:26:33 $
 */
#ifndef _KDS_INCL_
#define _KDS_INCL_

#ifndef KERNEL
/*
 * In user mode, we have to do the following to pull in the kernel
 * definition of the lock structures.
 */

#define SHOW_UTT 1
#include <sys/user.h>			/* Do some magic */
#undef SHOW_UTT
#include <kern/lock.h>			/* Get lock field definition */
#endif

/*
 * Include files.
 */
#include <sys/types.h>			/* Get misc field definition */

/* ---------------------------------------------------------------------- */

/*
 * A database (whether in-memory or on-disk) consists of many different
 * types of data structures.  They are all linked together in some
 * fashion.  Note that it's possible for a sub-system to have more than
 * one database.
 *
 * For clarification, a sample SCSI database will be described.
 *
 *      SCSI_DATABASE
 *      +--------+
 *      |        |
 *      |        |      PDRIVER
 *      |   ----------->+------+     PDRIVER
 *      |        |      |   -------->+------+     PDRIVER
 *      |        |      | DISK |     |   -------->+------+
 *      |        |      +------+     | TAPE |     |  0   |
 *      |        |                   +------+     | FISH |
 *      |        |                                +------+
 *      |        |      LOGDEV
 *      |   ----------->+----+    LOGDEV
 *      |        |      |  ------>+----+    LOGDEV
 *      |        |      | 3  |    |  ------>+----+    LOGDEV
 *      |        |      +----+    | 0  |    |  ------>+----+
 *      |        |                +----+    | 1  |    | 0  |
 *      +--------+                          +----+    | 7  |
 *                                                    +----+
 *
 * In this example, the SCSI database structure contains pointers to two
 * child data structure lists; the PDRIVER data structure list and the
 * LOGDEV data structure list.  If the SCSI database is modelled using
 * the generic database headers defined for the kernel database, then the
 * SCSI database can be written to disk, read back into memory, and
 * connected together by using the generic database software.
 */

/* ---------------------------------------------------------------------- */

#define KDS_PRIORITY		100	/* Callback priority used by the
					   kds subsystem at the VM_AVAIL
					   configuration point */

#define KDS_MAX_PRINT		10	/* Maximum number of levels we can
					   print */

/* ---------------------------------------------------------------------- */

/*
 * Pointer sub-structure.  This sub-structure provides the fields to point
 * to another data structure (either a peer data structure or a child data
 * structure).  While in memory, the fptr and bptr fields are used.  While
 * on disk, the offset field is used.
 */

typedef struct ds_ptr
{
  char* fptr;				/* Forward pointer to next instance
					   of a data structure (in memory) */
  char* bptr;				/* Backward pointer to prev instance
					   of a data structure (in memory) */
  u_int ptr_type;			/* 0 = fptr is a 0 terminated single
					       linked list
					   1 = fptr is a forward queue
					   2 = fptr is a forward queue and
					       bptr is a backward queue */
  u_int offset;				/* Offset to next instance of data
					   structure (on disk) */
  u_int user_only;			/* 0 = pointer used by kernel&user
					   1 = pointer used by user only */
  int spare;				/* Spare field for alignment */
} DS_PTR;

#define DS_PTR_LIST		0x00	/* Pointer is a singly linked list
					   that's zero terminated */
#define DS_PTR_QUEUE1		0x01	/* Pointer is a single queue;
					   forward only */
#define DS_PTR_QUEUE2		0x02	/* Pointer is a double queue;
					   forward and backward */

/* ---------------------------------------------------------------------- */

/*
 * Data structure header sub-structure.  This sub-structure will exist at
 * the beginning of all data structures.  It is there so that the data
 * structures can be identified, parsed, and connected into an in-memory
 * copy of the database from the on-disk copy of the database.
 *
 * The "next" field is used to describe the location of the next instance
 * of the data structure (usually of the same type; a peer).
 *
 * The "ds_type" field is used by the database software (non-generic) to
 * detect the type of data structure.  This can be used to sanity check the
 * data structures in the database.
 *
 * The "ds_num" field will have a unique number for every data structure
 * in the database.  This data structure number is used to easily locate
 * a specific in-memory data structure.  The reason for locating a specific
 * in-memory data structure is so that other (possibly new) data structures
 * can be connected to it, so that it can be deleted, or so that it can be
 * modified.  By giving each data structure instance in the database a
 * unique number, a particular data structure can be located by using
 * generic software.
 *
 * The "num_child" field tells us how many lists of subordinate data
 * structures are pointed to by this data structure.
 *
 * This sub-structure will be at the beginning of all data structures in
 * the database.  This sub-structure will be followed by an array of int
 * fields.  There will be one int field for every "child" list (see the
 * the definition of the num_child field).  These int fields will contain
 * the offset from the beginning of this data structure to a child pointer
 * sub-structure (DS_PTR).
 *
 * As an example, using the SCSI database described earlier:
 *
 *      SCSI_DATABASE data structure will contain:
 *        ds_hdr sub-structure (with num_child set to 2)
 *        int offset to PDRIVER list (say 100)
 *        int offset to LOGDEV list  (say 80)
 *        other fields
 *        ds_ptr sub-structure which is a pointer to LOGDEV data structures
 *               (within the SCSI_DATABASE data structure, this field is at
 *               offset 80)
 *        other fields
 *        ds_ptr sub-structure which is a pointer to PDRIVER data structures
 *               (within the SCSI_DATABASE data structure, this field is at
 *               offset 100)
 *        other fields
 *
 *      PDRIVER data structure will contain:
 *        ds_hdr sub-structure (with num_child set to 0)
 *        (no ints are required because this structure has no children)
 *        other fields
 *
 *      LOGDEV data structure will contain:
 *        ds_hdr sub-structure (with num_child set to 0)
 *        (no ints are required because this structure has no children)
 *        other fields
 */

typedef struct ds_hdr
{
  DS_PTR next;				/* Pointer/offset to next instance
					   of data structure */
  u_int  ds_type;			/* Type of data structure */
  u_int  ds_num;			/* Data structure number */
  u_int  mem_size;			/* Data structure size in memory */
  u_int  disk_size;			/* Data structure size on disk */
  u_int  num_child;			/* Number of child pointers that
					   follow */
  int    spare;				/* Spare field for alignment */
} DS_HDR;

typedef struct ds_hdr_generic
{
  DS_PTR next;				/* Pointer/offset to next instance
					   of data structure */
  u_int  ds_type;			/* Type of data structure */
  u_int  ds_num;			/* Data structure number */
  u_int  mem_size;			/* Data structure size in memory */
  u_int  disk_size;			/* Data structure size on disk */
  u_int  num_child;			/* Number of child pointers that
					   follow */
  int    spare;				/* Spare field for alignment */
  u_int  child[100];			/* Offset from start of this ds to
					   subordinate data structure ptr */
} DS_HDR_GENERIC;

/* ---------------------------------------------------------------------- */

/*
 * Kernel database descriptor data structure.  The kernel database
 * sub-system allows each user to register their kernel database.  By
 * registering their kernel database, additional features of the kernel
 * database sub-system can be used.  The kernel database descriptor is
 * used to describe a kernel database.
 *
 * Note that this data structure follows the kernel database model.  That
 * is, the kernel database sub-system software can be used to maintain this
 * data structure.
 */

#define KDS_DS_DBD		0x00	/* DS number for KDS_DBD */
#define KDS_DS_MAX		0x00	/* Maximum DS number */

#define KDS_NAME_SIZE		32	/* Maximum size of database name */
#define KDS_MAXBUF_SIZE		(1024*32)
					/* Maximum user buffer size for
					   sys_sysinfo */

typedef struct kds_dbd
{
  DS_HDR kds_hdr;			/* Data structure header */
  char   db_name[KDS_NAME_SIZE];	/* Database name (a zero terminated
					   string) */
  u_int   full_service;			/* 0 = owner manages the database
					   1 = kds manages the database */
  u_int   print;			/* 0 = do not print messages
					   1 = print messages */
  u_int   dstype_max;			/* Maximum data structure type for
					   this kernel database */
  u_int   dsnum_next;			/* Next available data structure
					   number for this kernel database */
  u_int   dsoff_next;			/* Next available offset in the
					   on-disk copy of this kernel
					   database */
  u_int   db_locked;			/* 0 = database is not locked
					   1 = database is locked */
  char**  ds_name;			/* Address of an array of pointers
					   to data structure names */
  void    (*func)();			/* Address of the kernel routine
					   to process user mode requests
					   from get/setsysinfo */
  simple_lock_data_t lock;		/* Lock structure */
} KDS_DBD;

/* ---------------------------------------------------------------------- */

/*
 * Database description record.  This structure is the first record in the
 * on-disk copy of the database.  This first record describes the database
 * that is stored in the file.  The second record in the file is the on-disk
 * copy of the database.
 */

typedef struct db_desc
{
  u_int  version;			/* Version of kds used to create
					   this file */
  u_int  size;				/* Number of bytes in the second
					   record */
  u_int  xor;				/* Xor value of the second record;
					   used to detect corruption */
  int    spare;				/* Spare field for alignment */
  char   name[KDS_NAME_SIZE];		/* Name of the database */
} DB_DESC;

/* ---------------------------------------------------------------------- */

/*
 * KDS request data structure.  This data structure will be used by all
 * applications to pass a database request to a database function routine.
 * This data structure will usually be followed by some database-specific
 * fields.
 */

typedef struct kds_req
{
  char  dbname[KDS_NAME_SIZE];		/* Database name */
  u_int function;			/* Function code */
  u_int length;				/* Number of bytes in the request */
  u_int status;				/* Status of this request */
  int   spare1;				/* Reserved for future (init to 0) */
} KDS_REQ;

/* ---------------------------------------------------------------------- */

/*
 * kds routine entry point
 *
 * This macro will be used by the kernel database sub-system software to
 * generate different names for the kernel mode and the user mode routines
 * supplied by the kernel database source modules.
 */

#ifndef USER

#define REP(name) kds##_##name

#else

#define REP(name) uds##_##name

#endif

/* ---------------------------------------------------------------------- */

/*
 * kds get characteristics macro
 *
 * This macro is used to initialize the c_pr and c_fs local variables to
 * contain the characteristics for the current database and to initialize
 * the kdbd variable to point to the database descriptor for the proper
 * database.
 */

#define GET_DBCHAR(kds_locked)						\
  kdbd = REP(getdb)( dbname, kds_locked );				\
  if( kdbd == (KDS_DBD*) 0 ) {						\
    c_pr = gc_pr;							\
    c_fs = 0;								\
  } else {								\
    c_pr = kdbd->print;							\
    c_fs = kdbd->full_service;						\
  }

/* ---------------------------------------------------------------------- */

/*
 * kds lock macros
 *
 * These macros are used by the kernel database sub-system software (in
 * kernel mode only) to guarantee the integrity of the kernel databases.
 * For user mode, these macros generate no code.
 */

#ifdef KERNEL

#define KDS_LOCK_INIT(kdbd)						\
  usimple_lock_setup((simple_lock_t)&(((KDS_DBD*)kdbd)->lock),		\
		     (struct lockinfo *)0)

#define KDS_LOCK(kdbd, s)						\
  if( ((KDS_DBD*)(kdbd) != (KDS_DBD*) NULL) &&				\
     (kds_lock_avail) ) {						\
    s = spldevhigh();							\
    usimple_lock((simple_lock_t)&(((KDS_DBD*)kdbd)->lock));		\
    while( ((KDS_DBD*)(kdbd))->db_locked != 0 ) {			\
      mpsleep(((caddr_t)(kdbd)), (s), "KDS LOCK", 0,			\
	      (void*)(&(((KDS_DBD*)(kdbd))->lock)),			\
	      (MS_LOCK_NO_RELOCK|MS_LOCK_WRITE));			\
      s = spldevhigh();							\
      usimple_lock((simple_lock_t)&(((KDS_DBD*)kdbd)->lock));		\
    }									\
    ((KDS_DBD*)(kdbd))->db_locked = 1;					\
    usimple_unlock((simple_lock_t)&(((KDS_DBD*)kdbd)->lock));		\
    (void)splx(s);							\
  }

#define KDS_UNLOCK(kdbd, s)						\
  if( ((KDS_DBD*)(kdbd) != (KDS_DBD*) NULL) &&				\
     (kds_lock_avail) ) {						\
    s = spldevhigh();							\
    usimple_lock((simple_lock_t)&(((KDS_DBD*)kdbd)->lock));		\
    ((KDS_DBD*)(kdbd))->db_locked = 0;					\
    wakeup((caddr_t)(kdbd));						\
    usimple_unlock((simple_lock_t)&(((KDS_DBD*)kdbd)->lock));		\
    (void)splx(s);							\
  }

#else

#define KDS_LOCK_INIT(kdbd)
#define KDS_LOCK(kdbd, s)
#define KDS_UNLOCK(kdbd, s)

#endif

/* ---------------------------------------------------------------------- */

/*
 * The following constants are used during the READ and WRITE database
 * requests to specify which file to use to perform the operation.  One
 * of these values is passed as the first parameter to the READ/WRITE
 * routine.
 */

#define KDS_FILE		0	/* Use name passed as file name */
#define KDS_PRIMARY		1	/* Use primary file of database */
#define KDS_BACKUP		2	/* Use backup file of database */

/* ---------------------------------------------------------------------- */

/*
 * The following routines are available to the users of the kernel
 * database sub-system.
 */

#ifndef USER
int       REP(info_func)(KDS_REQ*, int);
#endif
int       REP(addds)(char*, DS_HDR*, DS_HDR*, int, int);
char*     REP(connect)(char*, char*);
int       REP(delds)(char*, DS_HDR*, int);
DS_HDR*   REP(findds)(char*, DS_HDR*, int);
void      REP(init)();
void      REP(merge)(char*, DS_HDR*, char*);
int       REP(offset)(char*, DS_HDR*);
int       REP(offsetn)(char*, DS_HDR*, int);
void      REP(print)(char*, DS_HDR*);
char*     REP(read)(int, char*);
int       REP(register)(char*, int, int, int, char**, void(*)());
char*     REP(remds)(char*, DS_HDR*, int);
int       REP(seq)(char*, DS_HDR*);
void      REP(seqn)(char*, DS_HDR*);
int       REP(unregister)(char*);
int       REP(write)(int, char*, DS_HDR*);

/* ---------------------------------------------------------------------- */

#endif /* _KDS_INCL_ */
