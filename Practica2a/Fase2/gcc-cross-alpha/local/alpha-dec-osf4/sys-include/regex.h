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
 *	@(#)$RCSfile: regex.h,v $ $Revision: 4.2.9.4 $ (DEC) $Date: 1995/08/15 18:49:43 $
 */ 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */

/*
 * definitions for the reentrant versions of regular expression functions
 */

#ifndef	_REGEX_H_
#define	_REGEX_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>

#define _REG_SUBEXP_MAX  49       /* Maximum # of subexpressions          */

/* regcomp() cflags */

#define REG_EXTENDED    0x001   /* Use Extended RE syntax rules         */
#define REG_ICASE       0x002   /* Ignore case in match                 */
#define REG_NEWLINE     0x004   /* Convert <backslash><n> to <newline>  */
#define REG_NOSUB       0x008   /* regexec() not report subexpressions  */
#define REG_WORD	0x010   /* Understand \< and \> 		*/

/* regexec() eflags */

#define REG_NOTBOL      0x100   /* First character not start of line    */
#define REG_NOTEOL      0x200   /* Last character not end of line       */


/* Regular Expression error codes */

#define REG_NOMATCH     1       /* RE pattern not found                 */
#define REG_BADPAT      2       /* Invalid Regular Expression           */
#define REG_ECOLLATE    3       /* Invalid collating element            */
#define REG_ECTYPE      4       /* Invalid character class              */
#define REG_EESCAPE     5       /* Last character is \                  */
#define REG_ESUBREG     6       /* Invalid number in \digit             */
#define REG_EBRACK      7       /* [] imbalance                         */
#define REG_EPAREN      8       /* \( \) or () imbalance                */
#define REG_EBRACE      9       /* \{ \} or { } imbalance               */
#define REG_BADBR       10      /* Invalid \{ \} range exp              */
#define REG_ERANGE      11      /* Invalid range exp endpoint           */
#define REG_ESPACE      12      /* Out of memory                        */
#define REG_BADRPT      13      /* ?*+ not preceded by valid RE         */
#define REG_ECHAR       14      /* invalid multibyte character          */

#ifdef _XOPEN_SOURCE
#define REG_ENOSYS	17	/* Implementation doesn't support function */
#endif

/* regex_t, regoff_t and regmatch_t moved to <reg_types.h> for use in */
/* other headers without adding additional cruft from this header */
#include <reg_types.h>

/* Regular Expression function prototypes */

extern  int     regcomp  __((regex_t *, const char *, int));
extern  int     regexec  __((const regex_t *, const char *, size_t, regmatch_t *, int));
extern  size_t  regerror __((int, const regex_t *, char *, size_t));
extern  void    regfree  __((regex_t *));

#ifdef _OSF_SOURCE
#if defined(_REENTRANT) || defined(_THREAD_SAFE)

#define	ESIZE	512
#define	NBRA	9

typedef	struct regex_data {
	char	expbuf[ESIZE],
		*braslist[NBRA],
		*braelist[NBRA],
		circf;
} REGEXD;

extern	char	*re_comp_r __((char *, REGEXD *));
extern	int	 re_exec_r __((char *, REGEXD *));
#endif	/* _REENTRANT || _THREAD_SAFE */
#endif  /* _OSF_SOURCE */

#ifdef __cplusplus
}
#endif
#endif	/* _REGEX_H_ */
