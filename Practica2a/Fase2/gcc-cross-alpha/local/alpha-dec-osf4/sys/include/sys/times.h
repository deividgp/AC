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
 *	@(#)$RCSfile: times.h,v $ $Revision: 4.2.6.2 $ (DEC) $Date: 1995/09/07 17:38:00 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */


/*
 * COMPONENT_NAME: times.h
 *                                                                    
 * ORIGIN: IBM
 *
 * Copyright International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the Rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */                                                                   
/*
 * OSF/1 Release 1.0
 */

#ifndef _SYS_TIMES_H_
#define _SYS_TIMES_H_

#include <standards.h>
#include <sys/types.h>			/* for clock_t */

#if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1)

/*
 * POSIX requires that certain values be included in times.h.  It also
 * requires that when _POSIX_C_SOURCE is defined >=1, only those standard
 * specific values are present.  This header includes all the POSIX
 * required entries.
 */

/*
 * Structure returned by times()
 */
struct tms {
	clock_t	tms_utime;		/* user time */
	clock_t	tms_stime;		/* system time */
	clock_t	tms_cutime;		/* user time, children */
	clock_t	tms_cstime;		/* system time, children */
};

#ifdef _NO_PROTO
extern clock_t times();
#else
#if defined(__STDC__) || defined(__cplusplus)
#if defined(__cplusplus)
extern "C"
{
#endif
extern clock_t times(struct tms *);
#if defined(__cplusplus)
}
#endif
#endif
#endif /* _NO_PROTO */

#endif /* _POSIX_C_SOURCE */
#endif	/* _SYS_TIMES_H_ */
