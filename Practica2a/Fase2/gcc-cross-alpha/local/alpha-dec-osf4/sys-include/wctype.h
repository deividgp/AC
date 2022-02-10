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
 *	@(#)$RCSfile: wctype.h,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 1997/09/29 14:02:07 $
 */ 

#ifndef _WCTYPE_H_
#define _WCTYPE_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

#ifndef _WCTRANS_T
#define _WCTRANS_T
typedef unsigned long wctrans_t;
#endif

#ifndef _WCTYPE_T
#define _WCTYPE_T
typedef unsigned int wctype_t;
#endif

#ifndef _WINT_T
#define _WINT_T
        typedef unsigned int wint_t;         /* Wide character */
#endif

#ifndef WEOF
#define WEOF	(wint_t)(-1)
#endif /* WEOF */

#if (__STDC_VERSION__ == 199409) || defined(_OSF_SOURCE)
extern wctrans_t wctrans __((const char *));
extern wint_t    towctrans __((wint_t, wctrans_t));
#endif

extern int	iswalpha __((wint_t));
extern int	iswalnum __((wint_t));
extern int	iswcntrl __((wint_t));
extern int	iswdigit __((wint_t));
extern int	iswgraph __((wint_t));
extern int	iswlower __((wint_t));
extern int	iswprint __((wint_t));
extern int	iswpunct __((wint_t));
extern int	iswspace __((wint_t));
extern int	iswupper __((wint_t));
extern int	iswxdigit __((wint_t));
extern wint_t	towupper __((wint_t));
extern wint_t	towlower __((wint_t));
extern int	iswctype __((wint_t, wctype_t));
#if defined(_XOPEN_SOURCE_EXTENDED) || (__STDC_VERSION__ == 199409)
extern wctype_t	wctype __((const char *));
#else
extern wctype_t	wctype __((char *));
#endif /* _XOPEN_SOURCE_EXTENDED */

#if defined(_OSF_SOURCE) && !defined(__cplusplus)
#include <ctype.h>
#define iswalpha(c)	_ISWMACRO(c,_ISALPHA)
#define iswupper(c)	_ISWMACRO(c,_ISUPPER)
#define iswlower(c)	_ISWMACRO(c,_ISLOWER)
#define iswdigit(c)	_ISWMACRO(c,_ISDIGIT)
#define iswxdigit(c)	_ISWMACRO(c,_ISXDIGIT)
#define iswspace(c)	_ISWMACRO(c,_ISSPACE)
#define iswpunct(c)	_ISWMACRO(c,_ISPUNCT)
#define iswalnum(c)	_ISWMACRO(c,_ISALNUM)
#define iswprint(c)	_ISWMACRO(c,_ISPRINT)
#define iswgraph(c)	_ISWMACRO(c,_ISGRAPH)
#define iswcntrl(c)	_ISWMACRO(c,_ISCNTRL)

#define towupper(c)	_TOWUPPER(c)
#define towlower(c)	_TOWLOWER(c)
#endif /* _OSF_SOURCE && !__cplusplus */

#ifdef __cplusplus
}
#endif
#endif /* _WCTYPE_H_ */
