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
 *	@(#)$RCSfile: unctrl.h,v $ $Revision: 4.2.3.3 $ (DEC) $Date: 1995/10/20 18:30:03 $
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
 * IBM CONFIDENTIAL
 * Copyright International Business Machines Corp. 1989
 * Unpublished Work
 * All Rights Reserved
 * Licensed Material - Property of IBM
 */
/*
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */ 

/* unctrl.h	5.1 - 86/12/09 - 06:06:38 */
/*
 * unctrl.h
 *
*/


#ifndef _UNCTRL_H
#define _UNCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#ifndef _CHTYPE
/*
 * chtype is the type used to store a character together with attributes.
 * THIS DEFINITION IS DUPLICATED IN CURSES.H AND UNCTRL.H, AND MUST ALWAYS
 * BE THE SAME.  It is required in both places by the XCURSES standard
 * so that each file may stand alone.
 */

#define _CHTYPE
typedef unsigned long chtype;

#endif /* _CHTYPE */


extern char     *_unctrl[];

#if defined(NOMACROS) || defined(lint)
extern char    *unctrl __((chtype));
#else
#define        unctrl(ch)   (_unctrl[ch&0377])
#endif  /* NOMACROS && lint */

#ifdef __cplusplus
}
#endif

#endif  /* _UNCTRL_H */
