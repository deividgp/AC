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
 *	@(#)$RCSfile: wchar.h,v $ $Revision: 4.2.19.3 $ (DEC) $Date: 1997/09/29 14:02:05 $
 */ 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/* 1.5  com/inc/wchar.h, 9123320, bos320 5/16/91 09:44:57 */
/*
 * COMPONENT_NAME: (LIBCNLS) Standard C Library National Language Support
 *
 * FUNCTIONS: 
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989, 1991
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _WCHAR_H_
#define _WCHAR_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

#ifndef WCHAR_MAX
#define WCHAR_MAX	((wchar_t)~0)
#endif

#if (__STDC_VERSION__ == 199409) || defined(_OSF_SOURCE)
#ifndef WCHAR_MIN
#define WCHAR_MIN	0
#endif
#endif

#ifndef _WINT_T
#define _WINT_T
        typedef unsigned int wint_t;         /* Wide character */
#endif

#ifndef WEOF
#define WEOF	(wint_t)(-1)
#endif /* WEOF */

#ifndef _MBSTATE_T
#define _MBSTATE_T
typedef struct {
    void	*__hdr;		/* pointer to _LC_object_t */
    void	*__attrobj;	/* pointer to attribute object */
    void	*__state;	/* currently unused state flag */
} mbstate_t;
#endif

#if (__STDC_VERSION__ != 199409)
#include <wctype.h>
#endif

extern wint_t	fgetwc __((FILE *));
extern wchar_t  *fgetws __((wchar_t *, int, FILE *));
extern wint_t	fputwc __((wint_t,FILE *));
extern int	fputws __((const wchar_t *, FILE *));
extern wint_t	getwc __((FILE *));
extern wint_t	putwc __((wint_t, FILE *));
extern wint_t	getwchar __((void));
extern wint_t	putwchar __((wint_t));

#if (__STDC_VERSION__ == 199409) || defined(_OSF_SOURCE)
/* Additional ISO C interface definitions */
extern wchar_t	*wmemchr __((const wchar_t *, wchar_t, size_t));
extern int	wmemcmp __((const wchar_t *, const wchar_t *, size_t));
extern wchar_t	*wmemcpy __((wchar_t *, const wchar_t *, size_t));
extern wchar_t	*wmemmove __((wchar_t *, const wchar_t *, size_t));
extern wchar_t	*wmemset __((wchar_t *, wchar_t, size_t));
extern wchar_t  *wcsstr __((const wchar_t *, const wchar_t *));
extern int	wscanf __((const wchar_t *, ...));
extern int	swscanf __((const wchar_t *, const wchar_t *, ...));
extern int	fwscanf __((FILE *, const wchar_t *, ...));
extern int	wprintf __((const wchar_t *, ...));
extern int	swprintf __((wchar_t *, size_t, const wchar_t *, ...));
extern int	fwprintf __((FILE *, const wchar_t *, ...));
extern int	vwprintf __((const wchar_t *, va_list));
extern int	vswprintf __((wchar_t *, size_t, const wchar_t *, va_list));
extern int	vfwprintf __((FILE *, const wchar_t *, va_list));
extern wint_t	btowc __((int));
extern int	wctob __((wint_t));
extern int	mbsinit __((const mbstate_t *));
extern size_t	mbrlen __((const char *, size_t, mbstate_t *));
extern size_t	mbrtowc __((wchar_t *, const char *, size_t, mbstate_t *));
extern size_t	wcrtomb __((char *, wchar_t, mbstate_t *));
extern size_t	mbsrtowcs __((wchar_t *, const char **, size_t, mbstate_t *));
extern size_t	wcsrtombs __((char *, const wchar_t **, size_t, mbstate_t *));
#endif

#ifdef _LIBC_POLLUTION_H_
#ifdef getwchar
#undef getwchar
#endif /* getwchar */
#ifdef putwchar
#undef putwchar
#endif /* putwchar */
#endif /* _LIBC_POLLUTION_H_ */
#define getwchar()	getwc(stdin)
#define putwchar(c)	putwc(c, stdout)

extern wint_t	ungetwc __((wint_t, FILE *));
extern double	wcstod __((const wchar_t *, wchar_t **));
extern long int	wcstol __((const wchar_t *, wchar_t **, int));
extern unsigned long int wcstoul __((const wchar_t *, wchar_t **, int));
extern wchar_t	*wcscat __((wchar_t *, const wchar_t *));
extern wchar_t	*wcschr __((const wchar_t *, wchar_t));
extern int	wcscmp __((const wchar_t *, const wchar_t *));
extern int	wcscoll __((const wchar_t *, const wchar_t *));
extern wchar_t	*wcscpy __((wchar_t *, const wchar_t *));
extern size_t	wcscspn __((const wchar_t *, const wchar_t *));
extern size_t	wcslen __((const wchar_t *));
extern wchar_t	*wcsncat __((wchar_t *, const wchar_t *, size_t));
extern int	wcsncmp __((const wchar_t *, const wchar_t *, size_t));
extern wchar_t	*wcsncpy __((wchar_t *, const wchar_t *, size_t));
extern wchar_t	*wcspbrk __((const wchar_t *, const wchar_t *));
extern wchar_t	*wcsrchr __((const wchar_t *, wchar_t));
extern size_t	wcsspn __((const wchar_t *, const wchar_t *));
#if (__STDC_VERSION__ == 199409)
extern int      fwide __((FILE *, int));
extern wchar_t	*wcstok_r __((wchar_t *, const wchar_t *, wchar_t **));
extern size_t   __wcsftime_isoc __((wchar_t *, size_t, const wchar_t *, const struct tm *));
#define wcstok wcstok_r
#define wcsftime __wcsftime_isoc
#else
extern wchar_t	*wcstok __((wchar_t *, const wchar_t *));
extern size_t	wcsftime __((wchar_t *, size_t, const char *, const struct tm *));
#  if defined(_REENTRANT) || defined(_THREAD_SAFE)
extern wchar_t	*wcstok_r __((wchar_t *, const wchar_t *, wchar_t **));
#  endif	/* _REENTRANT || _THREAD_SAFE */
#endif /* __STDC_VERSION__ */
extern wchar_t	*wcswcs __((const wchar_t *, const wchar_t *));
extern int	wcswidth __((const wchar_t *, size_t));
extern size_t	wcsxfrm __((wchar_t *, const wchar_t *, size_t));
extern int	wcwidth __((const wchar_t));

#ifdef __cplusplus
}
#endif
#endif /* _WCHAR_H_ */
