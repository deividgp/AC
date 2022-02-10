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
#ifndef	_KERN_SPL_H_
#define	_KERN_SPL_H_

#include <machine/spl.h>

/*
 *	This file defines the interrupt priority levels used by
 *	machine-independent code. The machine-dependent header file
 *	<machine/spl.h> may define additional levels, inlining macros,
 *	or other extensions to these interfaces.
 */
#ifndef splhigh
extern spl_t	splhigh(void);	/* Block all interrupts */
#endif

#ifndef splsched
extern spl_t	splsched(void);	/* Block all scheduling activity */
#endif
#ifndef splclock
extern spl_t	splclock(void);	/* Block clock interrupt */
#endif
#ifndef spltty
extern spl_t	spltty(void);	/* Block all terminal interrupts */
#endif
#ifndef splstr
extern spl_t	splstr(void);	/* Block all streams interrupts */
#endif
#ifndef splbio
extern spl_t	splbio(void);	/* Block all disk and tape interrupts */
#endif
#ifndef splimp
extern spl_t	splimp(void);	/* Block network interfaces */
#endif
#ifndef splnet
extern spl_t	splnet(void);	/* Block software interrupts */
#endif
#ifndef splsoftclock
extern spl_t	splsoftclock(void);	/* Block software interrupts */
#endif
#ifndef splvm
extern spl_t	splvm(void);	/* Block against VM interrupts */
#endif

#ifndef splx
extern void	splx(spl_t);	/* Restore previous level */
#endif

#ifndef spl0
extern spl_t	spl0(void);		/* Enable all interrupts */
#endif

#endif	/* _KERN_SPL_H_ */
