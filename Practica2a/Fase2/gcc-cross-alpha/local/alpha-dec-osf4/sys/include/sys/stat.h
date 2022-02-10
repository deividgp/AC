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
 *	@(#)$RCSfile: stat.h,v $ $Revision: 4.3.16.2 $ (DEC) $Date: 1998/09/29 22:25:38 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _SYS_STAT_H_
#define _SYS_STAT_H_

#include <standards.h>
#include <sys/types.h>
#include <sys/mode.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * POSIX requires that certain values be included in stat.h.  It also
 * requires that when _POSIX_C_SOURCE is defined >= 1, only those standard
 * specific values are present.  This header includes all the POSIX
 * required entries.
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1) 

/*
 *	Stat structure
 *
 */



struct  stat
{
	dev_t	st_dev;			/* ID of device containing a directory*/
					/*   entry for this file.  File serial*/
					/*   no + device ID uniquely identify */
					/*   the file within the system */
	ino_t	st_ino;			/* File serial number */
	mode_t	st_mode;		/* File mode; see #define's in */
					/*   sys/mode.h */
	nlink_t	st_nlink;		/* Number of links */
	uid_t	st_uid;			/* User ID of the file's owner */
	gid_t	st_gid;			/* Group ID of the file's group */
	dev_t	st_rdev;		/* ID of device */
					/*   This entry is defined only for */
					/*   character or block special files */
	off_t	st_size;		/* File size in bytes */

					/* Times measured in seconds since */
					/*   00:00:00 GMT, Jan. 1, 1970 */
	time_t	st_atime;		/* Time of last access */
	int	st_spare1;
	time_t	st_mtime;		/* Time of last data modification */
	int	st_spare2;
	time_t	st_ctime;		/* Time of last file status change */
	int	st_spare3;

	uint_t	st_blksize;		/* Size of block in file */
        int     st_blocks;              /* blocks allocated for file */

        uint_t  st_flags;               /* user defined flags for file */
        uint_t  st_gen;                 /* file generation number */

};
			/* End of the stat structure */

#ifndef _KERNEL
extern int	mkdir __((const char *, mode_t )); 
extern mode_t	umask __((mode_t )); 
extern int	stat __((const char *, struct stat *));
extern int	fstat __((int , struct stat *));
extern int	chmod __((const char *, mode_t ));
#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED) 
extern int	fchmod __((int, mode_t ));
#ifdef _XOPEN_SOURCE_EXTENDED
extern int	mknod __((const char *, mode_t, dev_t ));
#endif
#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */
extern int	mkfifo __((const char *, mode_t ));
/* This is required for POSIX 1003.1g Sockets compliance */
#ifdef _POSIX_PII
extern int	isfdtype __((int, int));
#endif /* _POSIX_PII */
#endif /* _KERNEL */

#endif /* _POSIX_C_SOURCE */

#if defined(_AES_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
extern int 	lstat __((const char *, struct stat *));
#endif /* _AES_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef _OSF_SOURCE

#define S_BLKSIZE       512     /* block size used in the stat struct */

#endif /* _OSF_SOURCE */

#if defined(__cplusplus)
}
#endif

#endif /* _SYS_STAT_H_ */
