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
 * (c) Copyright 1990, 1999, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*	
 *	@(#)$RCSfile: mesg.h,v $ $Revision: 4.2.14.2 $ (DEC) $Date: 1998/10/19 18:56:12 $
 */ 
/*
 */
/*
 * COMPONENT_NAME: INC
 *
 * FUNCTIONS: mesg.h
 *
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989, 1991
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * (Copyright statements and/or associated legends of other
 * companies whose code appears in any part of this module must
 * be copied here.)
 */

#ifndef _MESG_H_
#define _MESG_H_

#include <stdio.h>
#include <nl_types.h>
#include <limits.h>
#include <sys/types.h>

#define CAT_MAGIC 	505
#define CATD_ERR 	((nl_catd) -1)
#define NL_MAXOPEN	10

struct _message {
	unsigned short 	_set,
			_msg;
	char 		*_text;
	unsigned	_old;
};

struct _header {
	int 		_magic;
	unsigned short	_n_sets,
			_setmax;
	char		_filler[20];
};
struct _msgptr {
	unsigned short 	_msgno,
			_msglen;
	unsigned int	_offset;
};

struct _catset {
	unsigned short 	_setno,
			_n_msgs;
	struct _msgptr 	*_mp;
	int		_msgs_expanded;
};


struct __catalog_descriptor {
	char		*_mem;
	char		*_name;
	char		*_lc_message;
	char		*_nlspath;
	struct _header 	*_hd;
	struct _catset 	*_set;
	void		*_iconv;	/* Ptr to iconv data */
	int 		_fd;		/* i/o descriptor */
	int		_catlen;	/* Size of mapped object */
	int		_setmax;	/* # message sets in file */
	int		_count;
	int		_magic;		/* Also holds copy of CAT_MAGIC */
	int		_n_sets;	/* max index in _set array */
	int		_sets_expanded;
};


_BEGIN_CPLUSPLUS
#ifdef _XOPEN_SOURCE
extern struct _catset *__cat_get_catset(nl_catd, int);
#endif /* _XOPEN_SOURCE */
extern struct _msgptr *__cat_get_msgptr(struct _catset *, int);
_END_CPLUSPLUS

#endif  /* _MESG_H_ */
