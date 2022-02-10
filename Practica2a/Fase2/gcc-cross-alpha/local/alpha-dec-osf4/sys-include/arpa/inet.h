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
 *	@(#)$RCSfile: inet.h,v $ $Revision: 4.2.11.5 $ (DEC) $Date: 1995/06/06 21:26:06 $
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
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *

 */

#ifndef _ARPA_INET_H
#define _ARPA_INET_H

/*
 * External definitions for
 * functions in inet(3N)
 */
#include <netinet/in.h>

#if defined (_XOPEN_SOURCE_EXTENDED) && !defined (_OSF_SOURCE)
#include <machine/endian.h>
#endif

_BEGIN_CPLUSPLUS
extern in_addr_t	inet_addr	__((const char *));
extern int		inet_aton	__((const char *, struct in_addr *));
extern in_addr_t	inet_lnaof	__((struct in_addr));
extern struct in_addr	inet_makeaddr	__((in_addr_t, in_addr_t));
extern in_addr_t	inet_netof	__((struct in_addr));
extern in_addr_t	inet_network	__((const char *));
extern char *		inet_ntoa	__((struct in_addr));
_END_CPLUSPLUS

#endif	/* _ARPA_INET_H */
