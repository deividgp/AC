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
 *	@(#)$RCSfile: ndbm.h,v $ $Revision: 4.2.26.3 $ (DEC) $Date: 1997/08/28 17:24:05 $
 */ 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/* @(#)$RCSfile: ndbm.h,v $ $Revision: 4.2.26.3 $ (OSF) $Date: 1997/08/28 17:24:05 $ */
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	ndbm.h	5.1 (Berkeley) 5/30/85
 */

#ifndef _NDBM_H_
#define _NDBM_H_

#include <standards.h>

#ifdef _XOPEN_SOURCE_EXTENDED
#include <sys/types.h>
#endif

/*
 * Hashed key data base library.
 */
#ifdef _XOPEN_SOURCE_EXTENDED
#define DBM_PBLKSIZ 1024
#define DBM_DBLKSIZ 4096
#else	/* _OSF_SOURCE */
#define PBLKSIZ 1024
#define DBLKSIZ 4096
#endif	/* _XOPEN_SOURCE_EXTENDED */

typedef struct {
	int	dbm_dirf;		/* open directory file */
	int	dbm_pagf;		/* open page file */
	int	dbm_flags;		/* flags, see below */
	int	dbm_pblksiz;		/* page file block size */
	long	dbm_maxbno;		/* last ``bit'' in dir file */
	long	dbm_bitno;		/* current bit number */
	long	dbm_hmask;		/* hash mask */
	long	dbm_blkptr;		/* current block for dbm_nextkey */
	int	dbm_keyptr;		/* current key for dbm_nextkey */
	long	dbm_blkno;		/* current page to read/write */
	long	dbm_pagbno;		/* current page in pagbuf */
#ifdef _XOPEN_SOURCE_EXTENDED
	char	dbm_pagbuf[DBM_PBLKSIZ];/* page file block buffer */
#else
	char	dbm_pagbuf[PBLKSIZ];	/* page file block buffer */
#endif
	long	dbm_dirbno;		/* current block in dirbuf */
#ifdef _XOPEN_SOURCE_EXTENDED
	char	dbm_dirbuf[DBM_DBLKSIZ];/* directory file block buffer */
#else
	char	dbm_dirbuf[DBLKSIZ];	/* directory file block buffer */
#endif
	void	*dbm_lock;		/* for inter-thread locking */
} DBM;

#define _DBM_RDONLY	0x1	/* data base open read-only */
#define _DBM_IOERR	0x2	/* data base I/O error */

#define dbm_getpblksiz(db)	((db)->dbm_pblksiz)
#define dbm_rdonly(db)	((db)->dbm_flags & _DBM_RDONLY)

#define dbm_error(db)	((db)->dbm_flags & _DBM_IOERR)
	/* use this one at your own risk! */
#define dbm_clearerr(db)	((db)->dbm_flags &= ~_DBM_IOERR)

/* for flock(2) and fstat(2) */
#define dbm_dirfno(db)	((db)->dbm_dirf)
#define dbm_pagfno(db)	((db)->dbm_pagf)

#ifdef _XOPEN_SOURCE_EXTENDED
typedef struct {
	void	*dptr;
	size_t	dsize;
} datum;
#endif

typedef struct {
	char	*dptr;
	int	dsize;
#ifdef _XOPEN_SOURCE_EXTENDED
} __Odatum;
#else
} datum;
#endif

/*
 * flags to dbm_store()
 */
#define DBM_INSERT	0
#define DBM_REPLACE	1

_BEGIN_CPLUSPLUS
#ifdef _XOPEN_SOURCE_EXTENDED
extern DBM      *dbm_open __((const char *, int, mode_t));
#else	/* _OSF_SOURCE */
extern DBM      *dbm_open __((char *, int, int));
#endif
extern void     dbm_close __((DBM *));
extern int      dbm_setpblksiz __((DBM *, int));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define dbm_fetch(__a,__b) _Edbm_fetch(__a,__b)
#define dbm_firstkey(__a) _Edbm_firstkey(__a)
#define dbm_nextkey(__a) _Edbm_nextkey(__a)
#define dbm_do_nextkey(__a,__b) _Edbm_do_nextkey(__a,__b)
#define dbm_forder(__a,__b) _Edbm_forder(__a,__b)
#define dbm_delete(__a,__b) _Edbm_delete(__a,__b)
#define dbm_store(__a,__b,__c,__d) _Edbm_store(__a,__b,__c,__d)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

extern datum    __R(dbm_fetch) __((DBM *, datum));
extern datum    __R(dbm_firstkey) __((DBM *));
extern datum    __R(dbm_nextkey) __((DBM *));
extern datum	__R(dbm_do_nextkey) __((DBM*, datum)); /* Obsolete */
extern long     __R(dbm_forder) __((DBM *, datum));
extern int      __R(dbm_delete) __((DBM *, datum));
extern int      __R(dbm_store) __((DBM *, datum, datum, int));

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_) &&  defined(__DECC)
#pragma extern_prefix ""
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ && __DECC*/

_END_CPLUSPLUS

#endif /* _NDBM_H_ */

