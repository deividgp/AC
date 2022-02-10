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
 * @(#)$RCSfile: ucs4.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/06/04 21:11:51 $
 */
/*
 *  Facility:
 *
 *	LIBUCS4
 *
 *  Version: V1.0
 *
 *  Abstract:
 *
 *      This public header file contains the prototype declarations 
 *      and constants for Unicode(TM) Support for Digital UNIX systems.
 *      The APIs described here are non-standard (as there is no 
 *      standard for Unicode support to date).
 */

/*
 * Make sure this file is only included once.
 */
#ifndef __UCS4_H_
#define __UCS4_H_

#include <standards.h>

_BEGIN_CPLUSPLUS

/**********
 *  Include Files
 **********/

#include <stdlib.h>
#include <errno.h>

/*
 *  Locale Independent Mapping Flags.
 */
#define MAP_FOLDCZONE           0x00000010  /* fold compatibility zone chars */
#define MAP_PRECOMPOSED         0x00000020  /* convert to precomposed chars */
#define MAP_COMPOSITE           0x00000040  /* convert to composite chars */
#define MAP_FOLDDIGITS          0x00000080  /* all digits to ASCII 0-9 */

/*
 ** Application definitions
 */
#define UCS_NULL_TERMINATED -1

/**********
 *  Function Prototypes (in alphabetical order)
 **********/

extern int fold_string_w __(( 
         unsigned long    fswMapFlags,
         const wchar_t   *srcString,
         int              cchSrc,
         wchar_t         *destString,
         int              cchDest ));

_END_CPLUSPLUS

/*
 *  DON'T ADD ANYTHING AFTER THIS #endif LINE
 */

#endif /* __UCS4_H_ */
