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
 *	@(#)$RCSfile: dirent.h,v $ $Revision: 4.2.20.2 $ (DEC) $Date: 1996/09/26 15:32:57 $
 */ 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/*
 */ 
/* dirent.h	1.28  com/inc/sys,3.1,8943 10/18/89 17:01:47 */
/*
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */
#ifndef _DIRENT_H_
#define _DIRENT_H_

#include <standards.h>
#include <sys/types.h>

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)
/*
 * The POSIX standard way of returning directory entries is in directory entry
 * structures, which are of variable length.  Each directory entry has
 * a struct direct at the front of it, containing its inode number,
 * the length of the entry, and the length of the name contained in
 * the entry.  These are followed by the name padded to a 4 byte boundary
 * with null bytes.  All names are guaranteed null terminated.
 * The maximum length of a name in a directory is returned by
 * pathconf(directory_pathname, _PC_NAME_MAX).  The type struct dirent is
 * a template for the beginning of the actual structure, since the
 * length is variable, and so should only be used to declare
 * struct dirent * pointer types.
 */

struct  dirent {
        ino_t    d_ino;               /* file number of entry */
        ushort_t d_reclen;            /* length of this record */
        ushort_t d_namlen;            /* length of string in d_name */
        char    d_name[256];		/* DUMMY NAME LENGTH */
					/* the real maximum length is */
					/* returned by pathconf() */
					/* At this time, this MUST */
					/* be 256 -- the kernel */
					/* requires it */
};
#define _DRECLEN_OFF ((char *)&(((struct dirent *)0)->d_reclen) - (char *)0)

#ifdef _KERNEL
/* used internally between VFS and subordinate file systems. kd_off
   eases NFS readdir() exports. */
struct kdirent {
	ino_t kd_ino;
	ushort_t kd_reclen;
	ushort_t kd_namlen;
	off_t kd_off;			/* kd_off points to beginning of
					   next entry. */
	char kd_name[256];
};
/*#define KDRECLEN_OFF ((char *)&(((struct kdirent *)0)->kd_reclen) - (char *)0)*/

#else /* ! _KERNEL */
/*
 * Definitions for library routines operating on directories.
 */
typedef struct {
#ifdef  _OSF_SOURCE
        int     dd_fd;        /* file descriptor associated with directory */
        long    dd_loc;       /* offset in current buffer */
        long    dd_size;      /* amount of data returned by getdirentries */
        char    *dd_buf;      /* data buffer */
        int     dd_bufsiz;
        int     dd_len;       /* size of data buffer */
        long    dd_seek;      /* magic cookie returned by getdirentries */
        void    *dd_lock;	/* for inter-thread locking */
#else
        int     __dd_fd;        /* file descriptor associated with directory */
        long    __dd_loc;       /* offset in current buffer */
        long    __dd_size;      /* amount of data returned by getdirentries */
        char    *__dd_buf;      /* data buffer */
	int	__dd_bufsiz;
        int     __dd_len;       /* size of data buffer */
        long    __dd_seek;      /* magic cookie returned by getdirentries */
	void	*__dd_lock;	/* for inter-thread locking */
#endif /* _OSF_SOURCE */

} DIR;

#ifdef _OSF_SOURCE
#define __dd_fd     dd_fd
#define __dd_loc    dd_loc
#define __dd_size   dd_size
#define __dd_buf    dd_buf
#define __dd_bufsiz dd_bufsiz
#define __dd_len    dd_len
#define __dd_seek   dd_seek
#define __dd_lock   dd_lock
#endif /* _OSF_SOURCE */

#if defined(__cplusplus)
extern "C" {
#endif	/* __cplusplus */

extern  DIR *opendir __((const char *));
extern  struct dirent *readdir __((DIR *));

#if _POSIX_C_SOURCE>=199506L

#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix "_P"
#else
#define readdir_r(__a,__b,__c) _Preaddir_r(__a,__b,__c)
#endif
#endif	/* !_LIBC_POLLUTION_H_ */
extern int __P_C(readdir_r) __((DIR *, struct dirent *, struct dirent **));
#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix ""
#endif	/* __DECC */
#endif	/* !_LIBC_POLLUTION_H_ */

#else	/* P1003.1c */

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
extern int readdir_r __((DIR *, struct dirent *));
#endif	/* _REENTRANT || _THREAD_SAFE */

#endif	/* P1003.1c */

extern  int closedir __((DIR *));
extern  void rewinddir __((DIR *));

#if defined(__cplusplus)
}
#endif	/* __cplusplus */
#endif /* _KERNEL */

#endif /* _POSIX_C_SOURCE */

#ifdef _XOPEN_SOURCE

#ifndef _KERNEL

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(_SYSV) || !defined(_OSF_SOURCE)
extern void seekdir __((DIR *, long));
#else
extern int seekdir __((DIR *, long));
#endif	/* _SYSV || !_OSF_SOURCE */

extern long telldir __((DIR *));

#if defined(__cplusplus)
}
#endif	/* __cplusplus */
#endif /* _KERNEL */

#endif /* _XOPEN_SOURCE */

#ifdef _OSF_SOURCE

#define d_fileno d_ino          /* backward compatibility */
#define	MAXNAMLEN	NAME_MAX

/* For BSD compatibility */
#ifdef _BSD

/*
 * The DIRSIZ macro gives the minimum record length which will hold
 * the directory entry.  This requires the amount of space in struct dirent
 * without the d_name field, plus enough space for the name with a terminating
 * null byte (dp->d_namlen+1), rounded up to a 4 byte boundary.
 * XXX The "256" below (the size of d_name) is subject to compiler alignment.
 */
#define _DNAMELEN(len) (((len)+1 + 3)&~3)
#define DIRSIZ(dp) \
    ((sizeof (struct dirent) - 256) + _DNAMELEN((dp)->d_namlen))
/* KDIRSIZ is aligned to 8-byte boundaries for alignment of 64-bit offsets */
#define _KNAMELEN(len) (((len)+1 + 7)&~7)
#define KDIRSIZ(kdp) \
    ((sizeof (struct kdirent) - 256) + _KNAMELEN((kdp)->kd_namlen))
/* KENTSIZ computes size of kdirent given name length */
#define KENTSIZ(namlen)	((sizeof (struct kdirent) - 256) + _KNAMELEN(namlen))


#ifndef _KERNEL
#define direct dirent		/* backward compatibility */
#define MAXNAMLEN	NAME_MAX
#endif	/* _KERNEL */
#endif /* _BSD */

#ifndef _KERNEL
#if defined(__cplusplus)
extern "C" {
#endif
extern int scandir __((const char *, struct dirent ***,
			int (*)(struct dirent *),  
			int (*)(struct dirent **, struct dirent **)));
extern int alphasort __((struct dirent **, struct dirent **));
#if defined(__cplusplus)
}
#endif	/* __cplusplus */
#endif /* _KERNEL */

#endif /* _OSF_SOURCE */

#endif /* _DIRENT_H_ */
