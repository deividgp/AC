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
 *	@(#)$RCSfile: uio.h,v $ $Revision: 4.2.24.2 $ (DEC) $Date: 1998/09/29 22:25:49 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *

 */

#ifndef	_SYS_UIO_H_
#define _SYS_UIO_H_

#include <standards.h>
#include <sys/types.h>
#ifdef _OSF_SOURCE
#include <sys/limits.h>
#endif

#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_POSIX_PII)
struct iovec {
	void   *iov_base;
	size_t	iov_len;
};

struct __Oiovec {
#else
struct iovec {
#endif
	caddr_t	iov_base;
	int	iov_len;
};

#ifdef _OSF_SOURCE

enum	uio_rw { UIO_READ, UIO_WRITE, UIO_AIORW };

/*
 * Segment flag values.
 */
enum	uio_seg {
	UIO_USERSPACE,		/* from user data space */
	UIO_SYSSPACE,		/* from system space */
	UIO_USERISPACE,		/* from user I space */
	UIO_PHYSSPACE		/* from physical address space */
};

struct uio {
	struct	iovec *uio_iov;
	off_t	uio_offset;
	int	uio_iovcnt;
	int	uio_resid;
	enum	uio_seg uio_segflg;
	enum	uio_rw uio_rw;
	/*
	 * The next two fields were added to support DDI/DKI interfaces.
	 */
	int	uio_fmode;	/* File mode flags. Drivers can't set this */
	daddr_t	uio_limit;	/* Max. blk. offset for file. Drivers can't
				   set this */
};

 /*
  * Limits
  */
#define UIO_MAXIOV	IOV_MAX
#define UIO_SMALLIOV	8		/* 8 on stack, else malloc */

#endif /* _OSF_SOURCE */

#ifndef _KERNEL
_BEGIN_CPLUSPLUS

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined(_LIBC_POLLUTION_H_)
#ifdef __DECC
#pragma extern_prefix "_E"
#else
#define readv(__a,__b,__c) _Ereadv(__a,__b,__c)
#define writev(__a,__b,__c) _Ewritev(__a,__b,__c)
#endif
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ */

#ifdef _XOPEN_SOURCE_EXTENDED
extern ssize_t __R(readv) __((int, const struct iovec *, int));
extern ssize_t __R(writev) __((int, const struct iovec *, int));
#else
extern ssize_t readv __((int, struct iovec *, int));
extern ssize_t writev __((int, struct iovec *, int));
#endif /* _XOPEN_SOURCE_EXTENDED */

#if defined(_XOPEN_SOURCE_EXTENDED) && !defined( _LIBC_POLLUTION_H_) && defined (__DECC)
#pragma extern_prefix ""
#endif /* _XOPEN_SOURCE_EXTENDED && !_LIBC_POLLUTION_H_ && __DECC*/

_END_CPLUSPLUS
#endif	/* _KERNEL */

#endif	/* _SYS_UIO_H_ */
