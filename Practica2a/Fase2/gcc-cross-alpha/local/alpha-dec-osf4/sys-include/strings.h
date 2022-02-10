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
 *	@(#)$RCSfile: strings.h,v $ $Revision: 4.2.9.2 $ (DEC) $Date: 1997/01/27 23:15:51 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */ 

/*
 * COMPONENT_NAME: (LIBCSTR) Standard C Library String Handling Functions
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * OSF/1 Release 1.0
 */


#ifndef _STRINGS_H_
#define _STRINGS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <sys/types.h>

#if defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)

#if defined(_LIBC_POLLUTION_H_) && defined(_INTRINSICS)
# undef bcopy		/* make the "pragma intrinsic" work for these */
# undef bzero
#endif

#ifdef _XOPEN_SOURCE_EXTENDED
extern int  bcmp __((const void *, const void *, size_t ));
extern void bcopy __((const void *, void *, size_t));
extern void  bzero __((void *, size_t));
#else
extern int  bcmp __((const char *, const char *, int));
extern void bcopy __((const char *, char *, int));
extern void  bzero __((char *, int));
#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _INTRINSICS
#ifdef _XOPEN_SOURCE_EXTENDED
extern void bcopy(const void *, void *, size_t);
extern void bzero(void *, size_t);
#else
extern void bcopy(const char *, char *, int);
extern void bzero(char *, int);
#endif
#pragma intrinsic(bcopy,bzero)
#endif

extern int  ffs __((int));
extern char *index __((const char*, int));
extern char *rindex __((const char*, int));
extern int  strcasecmp __((const char *, const char *));
extern int  strncasecmp __((const char *, const char *, size_t ));

#endif /* _XOPEN_SOURCE_EXTENDED || _OSF_SOURCE */

#if !defined(_XOPEN_SOURCE_EXTENDED) || defined(_OSF_SOURCE)
#include <string.h>
#endif

#ifdef __cplusplus
}
#endif
#endif /* _STRINGS_H_ */
