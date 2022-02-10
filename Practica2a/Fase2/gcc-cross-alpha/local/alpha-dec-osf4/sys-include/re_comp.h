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
 * @(#)$RCSfile: re_comp.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1994/10/05 19:20:33 $
 */
/*
 * COMPONENT_NAME: re_comp.h
 *
*/                                                                    
#ifndef _RE_COMP_H_
#define _RE_COMP_H_

#include <standards.h>

#ifdef _XOPEN_SOURCE_EXTENDED
_BEGIN_CPLUSPLUS
extern char *re_comp __(( const char *));
extern int  re_exec __(( const char *));
_END_CPLUSPLUS
#endif

#endif /* _RE_COMP_H_ */
