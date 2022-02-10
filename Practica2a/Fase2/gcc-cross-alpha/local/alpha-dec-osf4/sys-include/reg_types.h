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
 *	@(#)$RCSfile: reg_types.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/08/15 18:49:42 $
 */ 

#ifndef	_REG_TYPES_H_
#define	_REG_TYPES_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>

typedef struct {                /* regcomp() data saved for regexec()   */
        size_t  re_nsub;        /* # of subexpressions in RE pattern    */
        void    *re_comp;       /* compiled RE; freed by regfree()      */
        int     re_cflags;      /* saved cflags for regexec()           */
        size_t  re_erroff;      /* RE pattern error offset              */
        size_t  re_len;         /* # wchar_t chars in compiled pattern  */
        wchar_t re_ucoll[2];    /* min/max unique collating values      */
        uchar_t **re_lsub;      /* start subexp array                   */
        uchar_t **re_esub;      /* end subexp array                     */
	void    *re_filler[8];  /* Filler for any future 'extensions'   */
        uchar_t re_map[256];    /* map of valid pattern characters      */
} regex_t;

typedef off_t regoff_t;


typedef struct {                /* substring locations - from regexec() */
        regoff_t   rm_so;	/* Byte offset from start of string to  */
                                /*   start of substring                 */
        regoff_t   rm_eo;	/* Byte offset from start of string of  */
                                /*   first character after substring    */
} regmatch_t;

#ifdef __cplusplus
}
#endif
#endif	/* _REG_TYPES_H_ */
