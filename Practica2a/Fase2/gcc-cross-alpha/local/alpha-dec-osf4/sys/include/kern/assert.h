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
 *	@(#)$RCSfile: assert.h,v $ $Revision: 4.2.9.4 $ (DEC) $Date: 1995/01/25 18:50:43 $
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
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */

/*	assert.h	4.2	85/01/21	*/

/*
 * Handy assert macro.
 */

#ifndef	_KERN_ASSERT_H_
#define _KERN_ASSERT_H_

#ifdef _KERNEL
#include <mach_assert.h>
#endif

#include <kern/macro_help.h>

#if	MACH_ASSERT


#define ASSERT(ex)	assert(ex)
#if defined(__STDC__)
#define assert(ex)							\
MACRO_BEGIN								\
	if (!(ex)) {							\
		printf("Assertion failed: file: \"%s\", line: %d test: %s\n", \
		       __FILE__, __LINE__, # ex );			\
		panic("assertion failure");				\
	}								\
MACRO_END
#else	/* __STDC__ */
#define assert(ex)							\
MACRO_BEGIN								\
	if (!(ex)) {							\
		printf("Assertion failed: file: \"%s\", line: %d test: %s\n", \
		       __FILE__, __LINE__, "ex");			\
		panic("assertion failure");				\
	}								\
MACRO_END
#endif	/* __STDC__ */

#ifdef	lint
#define assert_static(x)
#else
#define assert_static(x)	assert(x)
#endif

#else	/* MACH_ASSERT */

#define ASSERT(ex)
#define assert(ex)
#define assert_static(ex)

#endif	/* MACH_ASSERT */

#endif	/* _KERN_ASSERT_H_ */
