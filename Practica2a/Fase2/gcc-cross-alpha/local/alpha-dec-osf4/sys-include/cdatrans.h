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
 * @(#)$RCSfile: cdatrans.h,v $ $Revision: 1.1.3.2 $ (DEC) $Date: 1992/04/15 08:14:56 $
 */
#ifndef _cdatrans_
#define _cdatrans_
/*
**++
**
**  COPYRIGHT (c) 1991, 1992 BY
**  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.
**  ALL RIGHTS RESERVED.
**
**  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND  COPIED
**  ONLY  IN  ACCORDANCE  WITH  THE  TERMS  OF  SUCH  LICENSE AND WITH THE
**  INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR  ANY  OTHER
**  COPIES  THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY
**  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE  IS  HEREBY
**  TRANSFERRED.
**
**  THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE  WITHOUT  NOTICE
**  AND  SHOULD  NOT  BE  CONSTRUED  AS  A COMMITMENT BY DIGITAL EQUIPMENT
**  CORPORATION.
**
**  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE OR  RELIABILITY  OF  ITS
**  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.
**
**  ABSTRACT:
**	This file contains the translation table to define ANSI C style
**	predefined symbols back to their pre ANSI C counterparts if we are
**	not compiling with a conformant compiler.
**
**--
**/

/*
 * Define __ predefined symbols in sources back to pre ansi style
 * if we are compiling with non ANSI C conformant compiler.
 */
#ifndef __STDC__
#ifdef unix
#ifndef __unix__
#define __unix__ unix
#endif
#endif
#ifdef vms
#ifndef __vms__
#define __vms__ vms
#endif
#endif
#ifdef vax
#ifndef __vax__
#define __vax__ vax
#endif
#endif
#ifdef vaxc
#ifndef __vaxc__
#define __vaxc__ vaxc
#endif
#endif
#endif

/* Handle case of __unix defined but not __unix__ (c89) */
#ifdef __unix
#ifndef __unix__
#define __unix__ __unix
#endif
#endif

#endif  /* ifndef _cdatrans_ */
