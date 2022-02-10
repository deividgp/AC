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
 *	@(#)$RCSfile: ftw.h,v $ $Revision: 4.2.14.4 $ (DEC) $Date: 1995/06/28 16:00:37 $
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
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */ 

/*
 *	Codes for the third argument to the user-supplied function
 *	which is passed as the second argument to ftw
 */
#ifndef _FTW_H_
#define _FTW_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/stat.h>

#ifdef _XOPEN_SOURCE

#define	FTW_F	0	/* file */
#define	FTW_D	1	/* directory */
#define	FTW_DNR	2	/* directory without read permission */
#define	FTW_NS	3	/* unknown type, stat failed */


#if defined(_AES_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)
#define FTW_SL	4	/* symbolic link */
#endif /* _AES_SOURCE || _XOPEN_SOURCE_EXTENDED */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#define FTW_PHYS	0x00000001
#define FTW_MOUNT	0x00000002
#define FTW_DEPTH	0x00000004
#define FTW_CHDIR	0x00000008

#define FTW_DP	5	/* directory was previously visited */

struct FTW {
	int base;
	int level;
}; 

#ifdef _XOPEN_SOURCE_EXTENDED
/* Added for Spec1170 */

#define FTW_SLN	6	/* symbolic link that names a non-existent file */

#endif  /* _XOPEN_SOURCE_EXTENDED */

#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */


#if !defined (LINT) /*gaf: This causes a problem in the lint library */
struct stat;
#endif

/* declaration & renaming block for ftw() and nftw() */
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define ftw(__a,__b,__c) _Eftw(__a,__b,__c)
#define nftw(__a,__b,__c,__d) _Enftw(__a,__b,__c,__d)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */
extern int __R(ftw) __((const char *, int (*)(const char *, 
		       const struct stat *, int), int ));
#if defined(_XOPEN_SOURCE_EXTENDED)
extern int __R(nftw) __((const char *, int (*)(const char *, const struct stat *, 
		       int, struct FTW *), int, int));
#elif defined(_OSF_SOURCE)
extern int nftw __((const char *, int (*)(char *, const struct stat *, 
		       int, struct FTW), int, int));
#endif
#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

#endif /* _XOPEN_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _FTW_H_ */
