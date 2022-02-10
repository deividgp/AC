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
 *	@(#)$RCSfile: search.h,v $ $Revision: 4.2.14.2 $ (DEC) $Date: 1994/10/05 19:40:50 $
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
 * COMPONENT_NAME: (LIBCGEN) Standard C Library General Functions
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <standards.h>
#include <sys/types.h>

#ifdef _XOPEN_SOURCE

/* HSEARCH(3C) */
typedef struct entry { char *key, *data; } ENTRY;
typedef enum { FIND, ENTER } ACTION;

/* TSEARCH(3C) */
typedef enum { preorder, postorder, endorder, leaf } VISIT;

#ifdef	_NONSTD_TYPES
extern char *lsearch();
extern char *lfind();
extern char *tsearch();
extern char *tfind();
extern char *tdelete();
#else
_BEGIN_CPLUSPLUS
extern void *lsearch __((const void *, void *, size_t *, size_t, int (*) (const void *, const void *)));
extern void *lfind __((const void *, const void *, size_t *, size_t, int (*)(const void *, const void *)));
extern void *tsearch __((const void *, void **, int (*)(const void *,const void *)));
extern void *tfind __((const void *, void *const *, int (*) (const void *,const void *)));
extern void *tdelete __((const void *, void **, int (*)(const void *,const void *)));
_END_CPLUSPLUS
#endif	/* _NONSTD_TYPES */

_BEGIN_CPLUSPLUS
extern int hcreate __((size_t));
extern void hdestroy __((void));
extern ENTRY *hsearch __((ENTRY, ACTION));
extern void twalk __((const void *, void (*)(const void *,VISIT,int)));
#ifdef _XOPEN_SOURCE_EXTENDED
extern void insque __((void *, void *));
extern void remque __((void *));
#endif
_END_CPLUSPLUS

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
struct hsearch_data {
	void	*table;
	uint_t	length;
	uint_t	dim;
	uint_t	prcnt;
	uint_t	count;
};

_BEGIN_CPLUSPLUS
extern int hcreate_r __((size_t, struct hsearch_data *));
extern void hdestroy_r __((struct hsearch_data *));
extern int hsearch_r __((ENTRY, ACTION,ENTRY **, struct hsearch_data *));
_END_CPLUSPLUS

#endif  /* _REENTRANT || _THREAD_SAFE */

#endif /* _XOPEN_SOURCE */

#endif /* _SEARCH_H_ */
