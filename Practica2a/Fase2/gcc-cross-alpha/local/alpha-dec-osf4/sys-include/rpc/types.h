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
 *	@(#)$RCSfile: types.h,v $ $Revision: 4.2.7.3 $ (DEC) $Date: 1994/03/29 18:39:07 $
 */
/*
 */


/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 */


/*
 * Rpc additions to <sys/types.h>
 */

#ifndef	__rpc_types_h
#define	__rpc_types_h

#include <standards.h>

#define	bool_t	int
#define	enum_t	int
#define __dontcare__	-1

#ifndef FALSE
#	define	FALSE	(0)
#endif

#ifndef TRUE
#	define	TRUE	(1)
#endif

#ifndef NULL
#	define NULL 0
#endif

/* Definitions used for NFS V3 and handy for others */
typedef unsigned long uint64;
typedef unsigned long u_longlong_t;

typedef long int64;
typedef long longlong_t;

typedef unsigned int uint32;

typedef int int32;

#ifndef	KERNEL
#include <sys/types.h>
#include <stdlib.h>      /* for malloc() */
#define	mem_alloc(bsize)	malloc(bsize)
#define	mem_free(ptr, bsize)	free(ptr)
#else
_BEGIN_CPLUSPLUS
extern char *kmem_alloc();
_END_CPLUSPLUS
#define	mem_alloc(bsize)	kmem_alloc((u_int)bsize)
#define	mem_free(ptr, bsize)	kmem_free((caddr_t)(ptr), (u_int)(bsize))
#endif

#ifdef KERNEL
#include "../h/types.h"

#ifndef _TIME_
#include "time.h"
#endif 

#else

#ifndef _TIME_
#include <sys/time.h>
#endif

#endif /* KERNEL */
#endif	/* !__rpc_types_h */
