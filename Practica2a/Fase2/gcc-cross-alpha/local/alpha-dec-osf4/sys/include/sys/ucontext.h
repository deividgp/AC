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
 * @(#)$RCSfile: ucontext.h,v $ $Revision: 1.1.6.4 $ (DEC) $Date: 1994/12/18 22:29:56 $
 */

#ifndef _SYS_UCONTEXT_H
#define _SYS_UCONTEXT_H
#if defined(__cplusplus)
extern "C"
{
#endif

#include <sys/sysmisc.h>    /* for stack_t */

#ifdef _OSF_SOURCE
#include <sys/user.h>
#endif

#if defined (_OSF_SOURCE) || defined (_XOPEN_SOURCE_EXTENDED)

/* defines the mcontext_t and ucontext_t types */
#include <sys/context_t.h>

/* These are new functions required for Spec1170 */
extern int getcontext __((ucontext_t *));
extern int setcontext __((const ucontext_t *));
extern void makecontext __((ucontext_t *, void (*)(), int, ...));
extern int swapcontext __((ucontext_t *, const ucontext_t *));

#endif /* defined (_OSF_SOURCE) || defined (_XOPEN_SOURCE_EXTENDED) */

#if defined(__cplusplus)
}
#endif
#endif /* _SYS_UCONTEXT_H */
