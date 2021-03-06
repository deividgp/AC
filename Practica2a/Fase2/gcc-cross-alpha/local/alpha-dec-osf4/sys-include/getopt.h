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
 * @(#)$RCSfile: getopt.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1993/06/08 01:01:31 $
 */
/* 
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.  
 * ALL RIGHTS RESERVED  
 */ 
/* 
 * OSF/1 1.2
 */

#ifndef _GETOPT_H_
#define _GETOPT_H_

#include <standards.h>

#if defined(__cplusplus)
extern "C"
{
#endif
extern int getopt __((int, char * const [], const char *));
#if defined(__cplusplus)
}
#endif

extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;

#endif /* _GETOPT_H_ */
