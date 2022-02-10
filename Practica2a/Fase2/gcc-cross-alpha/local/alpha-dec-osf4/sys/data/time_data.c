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
#pragma ident "@(#)$RCSfile: time_data.c,v $ $Revision: 1.1.2.4 $ (DEC) $Date: 1995/05/31 14:07:25 $"

#include <micro_time.h>
#include <ntp_time.h>
#include <sys/errno.h>

#if	MICRO_TIME
int microsecond_time = 1;
#else
int microsecond_time = 0;
#endif	/* MICRO_TIME */

#if	NTP_TIME
int ntp_precision_time = 1;
#else
int ntp_precision_time = 0;

ntp_gettime(p, args, retval)
	struct proc *p;
	void *args;
	long *retval;
{
	return(ENOSYS);
}

ntp_adjtime(p, args, retval)
	struct proc *p;
	void *args;
	long *retval;
{
	return(ENOSYS);
}

void ntp_tick_adjust(t)
	struct timeval *t;
{
}

void ntp_init()
{
}

#endif /* NTP_TIME */

#if	!MICRO_TIME

void micro_time(tvp)
	struct timeval *tvp;
{
}

void microset()
{
}

#endif  /* !MICRO_TIME */
