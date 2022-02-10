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
 * @(#)$RCSfile: rt_limits.h,v $ $Revision: 4.2.12.3 $ (DEC) $Date: 1995/04/28 19:23:52 $
 */
/*
 *	File:	rt_limits.h                  
 *	Limits file for Realtime (P1003.4/D11).
 */

#ifndef _SYS_RT_LIMITS_H_
#define _SYS_RT_LIMITS_H_

#include <machine/machlimits.h>

#define TIMER_MAX 32
#define RTSIG_MAX 16
#define CLOCKDRIFT_MAX 10000000
#define DELAYTIMER_MAX INT_MAX
#define AIO_LISTIO_MAX 64
#define AIO_MAX 64
#define AIO_PRIO_DFL 5
#define AIO_PRIO_MAX 9
#define AIO_PRIO_MIN 0
#define SIGQUEUE_MAX 64

#define SEM_NSEMS_MAX _POSIX_SEM_NSEMS_MAX
#define SEM_VALUE_MAX _POSIX_SEM_VALUE_MAX
#define SEM_NAME_MAX  _POSIX_PATH_MAX

#define MQ_OPEN_MAX             64
#define MQ_PRIO_MAX             256
#define MQ_NAME_MAX  _POSIX_PATH_MAX

#define _POSIX_AIO_LISTIO_MAX	2
#define _POSIX_AIO_MAX 		1
#define _POSIX_CLOCKDRIFT_MAX 	10000000
#define _POSIX_CLOCKRES_MIN 	20000000
#define _POSIX_DELAYTIMER_MAX	32
#define _POSIX_INTERVAL_MAX 	1092

#define _POSIX_SEM_NSEMS_MAX    256
#define _POSIX_SEM_VALUE_MAX    32767

#define _POSIX_TIMER_MAX	32

#define _POSIX_MQ_OPEN_MAX      8
#define _POSIX_MQ_PRIO_MAX      32

#define _POSIX_SIGQUEUE_MAX	32
#define _POSIX_RTSIG_MAX	8
#endif /* _SYS_RT_LIMITS_H */

