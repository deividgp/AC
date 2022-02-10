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

#ifndef _SYS_FDFS_H
#define _SYS_FDFS_H

#include <sys/types.h>

#ifdef _KERNEL
#include <kern/lock.h>
#endif
/*
 * characters in d_name is set much smaller.
 */
struct fdfs_dirent
{
  ino_t    d_ino;               /* file number of entry */
  ushort_t d_reclen;            /* length of this record */
  ushort_t d_namlen;            /* length of string in d_name */
  char    d_name[4];
} ;

/*
 * Number of bytes in a directory block for FDFS.
 */
#define	FDFS_DIRBLKSZ	1024
/*
 * Most file systems use the v_data field to contain a pointer to file system
 * dependent information (e.g., inode).  We only need an integer.
 */
#define FILE_DESCRIPTOR(vptr) (*((int *)(vptr->v_data)))

/*
 * The number of FDFS files when mounted.
 */
extern int fdfs_file_count;

/*
 * Address of the FDFS directory block buffer.
 */
extern struct fdfs_dirent *fdfs_dirbuf;

/*
 * Pointer to the FDFS root directory.  When FDFS is not mounted, this should be
 * NULL.
 */
extern struct vnode *fdfs_root_directory;

#ifdef _KERNEL
extern lock_data_t fdfs_lock;       /* for fdfs operations on global data */
extern struct lockinfo *fdfs_lockinfo;
#define FDFS_READ_LOCK()    lock_read(&fdfs_lock)
#define FDFS_READ_UNLOCK()   lock_read_done(&fdfs_lock)
#define FDFS_WRITE_LOCK()   lock_write(&fdfs_lock)
#define FDFS_WRITE_UNLOCK()   lock_write_done(&fdfs_lock)
#define FDFS_TRY_WRITE_LOCK()   lock_try_write(&fdfs_lock)
#define FDFS_LOCK_INIT()    lock_setup(&fdfs_lock, fdfs_lockinfo, TRUE)
#endif

#endif 
