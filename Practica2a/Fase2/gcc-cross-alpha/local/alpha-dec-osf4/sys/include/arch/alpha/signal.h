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
 *	@(#)$RCSfile: signal.h,v $ $Revision: 1.1.8.7 $ (DEC) $Date: 1995/02/15 22:42:49 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.2
 */

/*
 * COMPONENT_NAME: SYSPROC - signal.h
 *                                                                    
 * ORIGIN: 27
 *
 * Copyright International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 */                                                                   

#ifndef _ALPHA_SIGNAL_H_
#define _ALPHA_SIGNAL_H_
#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_KERNEL) && (defined(__LANGUAGE_C__) || defined(__cplusplus))
typedef int sig_atomic_t;
#endif

#if defined(_OSF_SOURCE) || defined(_XOPEN_SOURCE_EXTENDED)

#if	defined(_KERNEL) || defined (_SIGSET_OPS_MACROS)

/*
 * Macros to manipulate a sigset_t:
 *	sigemptyset, sigfillset, sigaddset, sigdelset,
 *	sigismember, sigsetdiff, sigsetsum, sigfirstset,
 *	siganyset
 * Because a sigset_t == long on the Alpha, these macros are much
 * simpler than original OSF versions. But being now machine
 * dependent, they moved here.
 */

/* sigemptyset: clear a signal set */
#define sigemptyset(setp)						\
	*(setp) = (sigset_t)0

/* sigfillset: fill a signal set */
#define sigfillset(setp)						\
	*(setp) = (sigset_t)~0

/* sigaddset: add signal S to set */
#define sigaddset(setp, S)						\
	*(setp) |= (1L << ((S) - 1))

/* sigdelset: remove signal S from set */
#define sigdelset(setp, S)						\
	*(setp) &= ~(1L << ((S) - 1))

/* sigismember: say whether S is a member of set */
#define sigismember(setp, S)						\
	(*(setp) & (1L << ((S) - 1)))

/* sigsetdiff: create set of signals in setp not in set */
#define sigsetdiff(setp, set)						\
	*(setp) &= ~(set)

/* sigsetsum: create set of signals in either (or both) sets */
#define sigsetsum(setp, set)						\
	*(setp) |= (set)

/* sigsetand: create set of signal in only in both sets */
#define sigsetand(setp, set)						\
	*(setp) &= (set)

/* sigfirstset: return signal number of first signal in set */
#ifdef _KERNEL
#define sigfirstset(setp)						\
	(lsb(*(setp)) + 1)
#else
#define sigfirstset(setp)						\
	ffs(*(setp))
#endif

/* siganyset: say whether setp has any signals set */
#define siganyset(setp)							\
	(*(setp) != 0)

#endif /*  defined(_KERNEL) || defined(_SIGSET_OPS_MACROS) */

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
/*
 * These definition are also used in machdep.c.
 */
#define R_V0	0
#define R_A0	16
#define R_A1	17
#define R_A2	18
#define R_A3	19
#define R_A4	20
#define R_A5	21
#define R_SP	30
#endif

/* defines the machine dependent sigcontext structure */
#include <machine/context.h>

#define     ILL_RESAD_FAULT     0x0     /* reserved addressing fault */
#define     ILL_PRIVIN_FAULT    0x1     /* privileged instruction fault */
#define     ILL_RESOP_FAULT     0x2     /* reserved operand fault */
#define     ILL_INST_FAULT      0x3     /* Illegal instruction */
#define     ILL_MODE_FAULT      0x4     /* Illegal mode - VMSPAL only */

#define     FPE_INTOVF_TRAP     0x1     /* integer overflow */
#define     FPE_INTDIV_TRAP     0x2     /* integer divide by zero */
#define     FPE_FLTOVF_TRAP     0x3     /* floating overflow */
#define     FPE_FLTDIV_TRAP     0x4     /* floating/decimal divide by zero */
#define     FPE_FLTUND_TRAP     0x5     /* floating underflow */
#define     FPE_DECOVF_TRAP     0x6     /* decimal overflow */
#define     FPE_SUBRNG_TRAP     0x7     /* subscript out of range */
#define     FPE_FLTOVF_FAULT    0x8     /* floating overflow fault */
#define     FPE_FLTDIV_FAULT    0x9     /* divide by zero floating fault */
#define     FPE_FLTUND_FAULT    0xa     /* floating underflow fault */
#define     FPE_UNIMP_FAULT     0xb     /* Unimplemented FPU instruction */
#define     FPE_INVALID_FAULT   0xc     /* Invalid operation */
#define     FPE_INEXACT_FAULT   0xd     /* Inexact result */
#define	    FPE_HPARITH_TRAP	0xe	/* High performance trap */
#define     FPE_INTOVF_FAULT    0xf     /* Integer Overflow fault */
#define	    FPE_ILLEGAL_SHADOW_TRAP 0x10 /* Illegal Trap Shadow Trap */
#define	    FPE_GENTRAP		0x11	/* */

#ifndef _XOPEN_SOURCE_EXTENDED
#define BRK_USERBP        0       /* user bp (used by debuggers) */
#define BRK_KERNELBP      1       /* kernel bp (used by prom) */
#define BRK_ABORT         2       /* no longer used */
#define BRK_BD_TAKEN      3       /* for taken bd emulation */
#define BRK_BD_NOTTAKEN   4       /* for not taken bd emulation */
#define BRK_SSTEPBP       5       /* user bp (used by debuggers) */
#define BRK_OVERFLOW      6       /* overflow check */
#define BRK_DIVZERO       7       /* divide by zero check */
#define BRK_RANGE         8       /* range error check */
#define BRK_STACKOVERFLOW 9	  /* used by ada */
#endif

#endif /* _OSF_SOURCE || _XOPEN_SOURCE_EXTENDED */

#ifdef __cplusplus
}
#endif
#endif /* _ALPHA_SIGNAL_H_ */
