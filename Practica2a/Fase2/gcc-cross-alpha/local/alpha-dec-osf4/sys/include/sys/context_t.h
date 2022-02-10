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
 * @(#)$RCSfile: context_t.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1994/12/18 22:26:47 $
 */

#ifndef _SYS_CONTEXT_T_H
#define _SYS_CONTEXT_T_H

#include <sys/types.h>

/* defines the machine dependent sigcontext structure */
#include <machine/context.h>

/* defines the stack_t type */
#include <sys/sysmisc.h>

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
typedef struct sigcontext mcontext_t;
#else
typedef struct _sigcontext mcontext_t;
#endif

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
typedef struct ucontext {
#else
typedef struct _ucontext {
#endif
  unsigned long		uc_flags;
#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
  struct ucontext	*uc_link;
#else
  struct _ucontext	*uc_link;
#endif
  sigset_t		uc_sigmask;
  stack_t		uc_stack;
  mcontext_t		uc_mcontext;
  long			uc_filler[5];	/* pad structure to 512 bytes */
} ucontext_t;

#endif /* _SYS_CONTEXT_T_H */
