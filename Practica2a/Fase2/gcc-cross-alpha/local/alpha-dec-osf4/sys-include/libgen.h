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
 * @(#)$RCSfile: libgen.h,v $ $Revision: 1.1.4.4 $ (DEC) $Date: 1995/06/28 16:00:39 $
 */

/* Spec1170 - definitions for pattern matching functions */

#ifndef _LIBGEN_H_
#define _LIBGEN_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>


#ifdef _XOPEN_SOURCE_EXTENDED

extern char      *__loc1;     /* Used by regex() to report pattern location */

extern char    *regcmp __((const char  * , ...));

/* declaration & renaming block for basename() & dirname() */
#ifndef _LIBC_POLLUTION_H_
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define basename(__a) _Ebasename(__a)
#define dirname(__a) _Edirname(__a)
#endif
#endif /* !_LIBC_POLLUTION_H_ */
extern char    * __R(basename) __((char  *));
extern char    * __R(dirname) __((char  *));
#ifndef _LIBC_POLLUTION_H_
#ifdef __DECC
#pragma extern_prefix ""
#endif
#endif /* !_LIBC_POLLUTION_H_ */

extern char    *regex __((const char  * , const char  * , ...));

#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef __cplusplus
}
#endif
#endif   /* _LIBGEN_H_ */
