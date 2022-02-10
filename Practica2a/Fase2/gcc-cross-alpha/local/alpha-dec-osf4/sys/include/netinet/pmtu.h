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
 * @(#)$RCSfile: pmtu.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1995/12/15 18:10:03 $
 */

#ifndef PMTU_H
#define PMTU_H

#ifdef	_KERNEL

#define PMTU_RT_CHECK_INTVL 10*PR_SLOWHZ	/* 10 seconds */
#define PMTU_DECREASE_INTVL 600*PR_SLOWHZ	/* 10 minutes */
#define PMTU_INCREASE_INTVL 120*PR_SLOWHZ	/* 2 minutes */

#define PMTU_MIN_MTU 68			/* minimum mtu */
#define PMTU_MAX_MTU 65535		/* maximum mtu */

extern	int	pmtu_enabled;		/* 0 = disabled, !0 = enabled */
extern	u_int	pmtu_rt_check_intvl;	/* route check interval */
extern	u_int	pmtu_rt_check_timer;	/* route check timer */
extern	u_int	pmtu_decrease_intvl;	/* wait after pmtu decrease */
extern	u_int	pmtu_increase_intvl;	/* wait after pmtu increase */

#endif	/* _KERNEL */

#endif	/* PMTU_H */
