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
 * @(#)$RCSfile: lc_core.h,v $ $Revision: 1.1.11.8 $ (DEC) $Date: 1996/02/02 18:18:59 $
 */
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/* 1.6  com/inc/sys/lc_core.h, libccnv, bos320, 9132320m 8/11/91 14:14:46
 *
 * COMPONENT_NAME: (LIBCLOC) Locale Related Data Structures and API
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef __H_LC_CORE
#define __H_LC_CORE
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>
#include <locale.h>

/* only include when using full prototypes to avoid extra */
/* name space cruft in default case */
#ifndef _NO_PROTO
#include <nl_types.h>
#include <va_list.h>
#ifdef __cplusplus
#include <reg_types.h>
#endif
#endif

/*
 * In OSF/1, method elements in the structures point to functions
 */

/*
** Valid type ids for NLS objects
*/
typedef enum __lc_type_id_t {
    _LC_CAR=1,
    _LC_LOCALE=2,
    _LC_CHARMAP=3,
    _LC_CTYPE=4,
    _LC_COLLATE=5,
    _LC_NUMERIC=6,
    _LC_MONETARY=7,
    _LC_TIME=8,
    _LC_RESP=9 } __lc_type_id_t;

/* Valid locale formats */
#define _LC_DENSE_FORMAT 0x0
#define _LC_UCS4_FORMAT  0x1

typedef struct {
    __lc_type_id_t
	type_id;
    unsigned short
	magic;
    unsigned short
	format;
    unsigned long
	version;
    
    unsigned long  size;

} _LC_object_t;


/* forward decls for ANSI C and C++ */
struct _LC_charmap_t;
struct _LC_ctype_t;
struct _LC_collate_t;
struct _LC_time_t;
struct _LC_monetary_t;
struct _LC_numeric_t;
struct _LC_resp_t;
struct _LC_locale_t;

/*
** Object magic (Looks like "OSF1")
*/
#define _LC_MAGIC     0x05F1

/*
** Version.  Anytime the data structures in localedef or lc_core change
**	     in an incompatible way, this number should change
*/
#define _LC_VERSION   0x2


typedef struct {

    _LC_object_t  hdr;

    /* locale info method */
    char     *(*nl_langinfo) __((__nl_item, struct _LC_charmap_t *));
    
    /* Process code conversion methods */
    int   (*mbtowc) __((wchar_t *, const char *, size_t, struct _LC_charmap_t *));
    size_t   (*mbstowcs) __((wchar_t *, const char *, size_t, struct _LC_charmap_t *));
    int      (*wctomb) __((char *, wchar_t, struct _LC_charmap_t *));
    size_t   (*wcstombs) __((char *, const wchar_t *, size_t, struct _LC_charmap_t *));
    
    /* Character encoding length method */
    int      (*mblen) __((const char *, size_t, struct _LC_charmap_t *));
    
    /* Character display width methods */
    int   (*wcswidth) __((const wchar_t *, size_t, struct _LC_charmap_t *));
    int   (*wcwidth) __((const wchar_t, struct _LC_charmap_t *));
    
    /* private PC/CP converters */
    int      (*__mbtopc) __((wchar_t *, char *, size_t, int *, struct _LC_charmap_t *));
    int      (*__mbstopcs) __((wchar_t *, size_t, char *, size_t, int, char **, int *, struct _LC_charmap_t *));
    int      (*__pctomb) __((char *, wchar_t *, size_t, int *, struct _LC_charmap_t *));
    int      (*__pcstombs) __((char *, size_t, wchar_t *, size_t, char **, int *, struct _LC_charmap_t *));
    
    /* implementation initialization */
    struct _LC_charmap_t *(*init) __((struct _LC_locale_t *));
    void     *data;
} _LC_core_charmap_t;


typedef struct {
 
    _LC_object_t  hdr; 
    
    /* case convertersion methods */
    wint_t  (*towupper) __((wint_t, struct _LC_ctype_t *));
    wint_t  (*towlower) __((wint_t, struct _LC_ctype_t *));
    
    /* classification methods */
    wctype_t    (*wctype) __((char *, struct _LC_ctype_t *));
    int      (*iswctype) __((wint_t, wctype_t, struct _LC_ctype_t *));
    
    /* implementation initialization */
    struct _LC_ctype_t   *(*init) __((struct _LC_locale_t *));
    void     *data;
} _LC_core_ctype_t;


/*
 * Under the C programming environment, full function prototyping support 
 * for regular expression method pointers are only provided when the header 
 * file reg_types.h is included before this file.
 */
#ifndef _REG_TYPES_H_
#define __LCPROTO(__args__)	()
#else
#define __LCPROTO(__args__)	__(__args__)
#endif /* !_REG_TYPES_H_ */

typedef struct {

    _LC_object_t  hdr;

    /* character collation methods */
    int      (*strcoll) __((const char *, const char *, struct _LC_collate_t *));
    size_t   (*strxfrm) __((char *, const char *, size_t, struct _LC_collate_t *));
    
    /* process code collation methods */
    int      (*wcscoll) __((const wchar_t *, const wchar_t *, struct _LC_collate_t *));
    size_t   (*wcsxfrm) __((wchar_t *, const wchar_t *, size_t, struct _LC_collate_t *));
    
    /* filename matching methods */
    int      (*fnmatch) __((const char *, const char *, const char *, int, struct _LC_collate_t *));
    
    /* regular expression methods */
    int      (*regcomp) __LCPROTO((regex_t *, const char *, int, struct _LC_collate_t *));
    size_t   (*regerror) __LCPROTO((int, const regex_t *, char *, size_t, struct _LC_collate_t *));
    int      (*regexec) __LCPROTO((const regex_t *, const char *, size_t, regmatch_t *, int, struct _LC_collate_t *));
    void     (*regfree) __LCPROTO((regex_t *, struct _LC_collate_t *));

    /* implementation initialization */
    struct _LC_collate_t *(*init) __((struct _LC_locale_t *));
    void     *data;
} _LC_core_collate_t;


struct tm;
typedef struct {

    _LC_object_t  hdr;
    
    /* time info method */
    char     *(*nl_langinfo) __((__nl_item, struct _LC_time_t *));
    
    /* time character string formatting methods */
    size_t   (*strftime) __((char *, size_t, const char *, const struct tm *, struct _LC_time_t *));
    char     *(*strptime) __((const char *, const char *, struct tm *, struct _LC_time_t *));
    
    /* time process code string formatting methods */
    size_t   (*wcsftime) __((wchar_t *, size_t, const char *, const struct tm *, struct _LC_time_t *));
    
    /* implementation initialization */
    struct _LC_time_t    *(*init) __((struct _LC_locale_t *));
    void     *data;
} _LC_core_time_t;


typedef struct {

    _LC_object_t  hdr;

    /* monetary info method */
    char     *(*nl_langinfo) __((__nl_item, struct _LC_monetary_t *));
    
    /* character string monetary formatting method */
    ssize_t   (*strfmon) __((char *, size_t, const char *, va_list, struct _LC_monetary_t *));
    
    /* implementation initialization */
    struct _LC_monetary_t        *(*init) __((struct _LC_locale_t *));
    void     *data;
} _LC_core_monetary_t;


typedef struct {

    _LC_object_t  hdr;

    /* langinfo method */
    char     *(*nl_langinfo) __((__nl_item, struct _LC_numeric_t *));
    
    /* implementation initialization */
    struct _LC_numeric_t *(*init) __((struct _LC_locale_t *));
    void     *data;
} _LC_core_numeric_t;


typedef struct {

    _LC_object_t  hdr;
    
    /* langinfo method */
    char        *(*nl_langinfo) __((__nl_item, struct _LC_resp_t *));
    
    /* response matching method */
    int		(*rpmatch) __((const char *, struct _LC_resp_t *));
    
    /* implementation initialization */
    struct _LC_resp_t    *(*init) __((struct _LC_locale_t *));
    void        *data;
} _LC_core_resp_t;

typedef struct {

    _LC_object_t hdr;

    /* langinfo method */
    char         *(*nl_langinfo) __((__nl_item, struct _LC_locale_t *));
    struct lconv * (*localeconv) __((struct _LC_locale_t *));
    
    /* Initialization */
    struct _LC_locale_t  *(*init) __((struct _LC_locale_t *));
    void         *data;
} _LC_core_locale_t;

#ifdef __cplusplus
}
#endif
#endif /* __H_LC_CORE */
