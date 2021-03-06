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
 *	@(#)$RCSfile: slu.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/06/27 20:34:24 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/* 
 * derived from slu.h	4.1	(ULTRIX)	8/9/90
 */

/*
 *
 * Modification history
 *
 *   4-Jul-90	Randall Brown
 *		Created file.
 */

#ifndef _TC_SLU_H_
#define _TC_SLU_H_

struct slu {
    int	(*mouse_init)();
    int	(*mouse_putc)();
    int (*mouse_getc)();
    int	(*kbd_init)();
    int	(*kbd_putc)();
    int (*kbd_getc)();
    int (*slu_putc)();		/* put char out serial line unit */
    struct tty *slu_tty;
};

extern struct slu slu;

#endif
