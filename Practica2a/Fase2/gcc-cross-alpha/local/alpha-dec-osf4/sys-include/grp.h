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
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/* @(#)$RCSfile: grp.h,v $ $Revision: 4.2.20.2 $ (OSF) $Date: 1996/10/01 17:55:48 $ */
/* grp.h	1.7  com/inc,3.1,8943 8/8/89 15:24:07 */
/* grp.h	5.1 - 86/12/09 - 06:04:45 */
/*
 * COMPONENT_NAME: grp.h
 *                                                                    
 * Copyright International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 */                                                                   

#ifndef _GRP_H_
#define _GRP_H_

#include <standards.h>
#include <sys/types.h>

/* The POSIX standard requires that certain elements be included in grp.h. 
 * It also requires that when _POSIX_C_SOURCE is defined >=1, only those 
 * standard specific elements are made available.
 * This header includes all the POSIX required entries.
 */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)

struct  group {			 /* see getgrent(3) */
        char    *gr_name;
#ifdef _OSF_SOURCE
        char    *gr_passwd;
#else
        char    *__gr_passwd;
#endif
        gid_t   gr_gid;
        char    **gr_mem;
};
#ifdef _OSF_SOURCE
#define __gr_passwd gr_passwd
#endif

#if defined(__cplusplus)
extern "C"
{
#endif
extern struct group *getgrgid __((gid_t));
extern struct group *getgrnam __((const char *));

#if _POSIX_C_SOURCE>=199506L

#ifndef	_LIBC_POLLUTION_H_
#ifdef	__DECC
#pragma extern_prefix "_P"
#else
#define	getgrgid_r(__a,__b,__c,__d,__e)	_Pgetgrgid_r(__a,__b,__c,__d,__e)
#define	getgrnam_r(__a,__b,__c,__d,__e)	_Pgetgrnam_r(__a,__b,__c,__d,__e)
#endif	/* __DECC */
#endif	/* _LIBC_POLLUTION_H_ */
extern int __P_C(getgrgid_r) __((gid_t, struct group *, char *, size_t, struct group **));
extern int __P_C(getgrnam_r) __((const char *, struct group *, char *, size_t, struct group **));
#ifndef	_LIBC_POLLUTION_H_
#ifdef  __DECC
#pragma extern_prefix ""
#endif  /* __DECC */
#endif	/* _LIBC_POLLUTION_H_ */

#else	/* P1003.1c */

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
extern int getgrgid_r __((gid_t, struct group *, char *, int));
extern int getgrnam_r __((const char *, struct group *, char *, int));
#endif	/* _REENTRANT || _THREAD_SAFE */

#endif	/* P1003.1c */

#if defined(__cplusplus)
}
#endif

#endif /* _POSIX_C_SOURCE */

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#if defined(__cplusplus)
extern "C"
{
#endif
extern struct group *getgrent __((void));
extern void endgrent __((void));
#if defined(__cplusplus)
}
#endif

#ifdef _XOPEN_SOURCE_EXTENDED

#if defined(__cplusplus)
extern "C"
{
#endif
extern void setgrent __((void));
#if defined(__cplusplus)
}
#endif

#else  /* not _XOPEN_SOURCE_EXTENDED but _OSF_SOURCE */

#include <stdio.h>
#include <limits.h>

#ifndef NGROUPS			/* could get it from param.h */
#define NGROUPS NGROUPS_MAX       /** as many as there are **/
#endif

#if defined(__cplusplus)
extern "C"
{
#endif
extern struct group *fgetgrent __((FILE *));
extern int setgrent __((void));
extern int initgroups __((char *, int));
#if defined(__cplusplus)
}
#endif

#if defined(_REENTRANT) || defined(_THREAD_SAFE)

#if defined(__cplusplus)
extern "C"
{
#endif
extern int fgetgrent_r __((FILE *, struct group *, char *, int));
extern int getgrent_r __((struct group *, char *, int, FILE **));
extern int setgrent_r __((FILE **));
extern void endgrent_r __((FILE **));
#if defined(__cplusplus)
}
#endif
#endif	/* _REENTRANT || _THREAD_SAFE */

#endif  /* _XOPEN_SOURCE_EXTENDED */

#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#endif /* _GRP_H_ */
