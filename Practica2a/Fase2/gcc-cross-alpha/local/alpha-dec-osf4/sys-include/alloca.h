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
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
/* $Header: /usr/sde/osf1/rcs/os/src/usr/include/alpha/alloca.h,v 1.1.4.3 1996/01/11 20:56:44 Thomas_Peterson Exp $ */
#ifndef __ALLOCA_H
#define __ALLOCA_H
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Synopsis
 *   #include <alloca.h>
 *   void *alloca(integral_types);
 *
 * Description:
 *
 * This header is to be included if the intrinsic version of alloca()
 * is desired. The intrinsic version is more efficient in that space
 * is allocated/deallocated off the runtime stack rather than the heap
 * like the libc version does.  See also alloca(3).
 *
 * C++ users:
 *
 * DEC C++ versions prior to V5.3 do not support the intrinsic version
 * of alloca().  Use of pre-V5.3 versions of DEC C++ will result in a
 * compilation warning regarding the #pragma intrinsic below.  However,
 * the prototype for alloca() below is correct and will resolve to the
 * alternate standard C library version of alloca() under pre-V5.3 DEC
 * C++ versions, despite the warning.
 */

#if defined(_CFE) || defined(__DECC) || defined(__cplusplus)
extern void *alloca(int);
#pragma intrinsic(alloca)
#else
/* old C compiler, pre-2.20, would not change */
#define alloca __builtin_alloca
#endif

#ifdef __cplusplus
}
#endif
#endif /* __ALLOCA_H */
