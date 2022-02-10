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
 * @(#)$RCSfile: sysmacros.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1993/09/15 18:03:37 $
 */

#ifndef _SYS_SYSMACROS_H
#define	_SYS_SYSMACROS_H

/*
 * Sysmacros.h is specified in the V.4 Streams Programmer's Guide.
 */

/* The definitions for minor and major are found in types.h */
#include <sys/types.h>
#define	getminor	minor
#define	getmajor	major
#define	makedevice	makedev

#endif
