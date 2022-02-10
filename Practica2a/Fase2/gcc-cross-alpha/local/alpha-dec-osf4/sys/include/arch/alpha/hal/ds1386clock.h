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
 * @(#)$RCSfile: ds1386clock.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1994/05/20 21:54:42 $
 */

/***************************************************************************
 *
 * 	ds1386clock.h
 *
 *	Dallas Semiconductor DS1386 clock chip.
 *
 ****************************************************************************/

/* 
 * Register definitions
 */

#define RTC_MSECS  0x0
#define RTC_SECS   0x1
#define RTC_MINS   0x2
#define RTC_HRS    0x4
#define RTC_DAYS   0x6
#define RTC_DATE   0x8
#define RTC_MONTHS 0x9
#define RTC_ENABLE 0x9
#define RTC_YEARS  0xa
#define RTC_CMD    0xb

/*
 * Command register masks
 */

#define RTC_ENABLE_UPDATES   0x80

/*
 * hour register masks and flags
 */

#define _12_HOUR_MODE 0x40
#define IS_PM         0x20
#define _12_HOUR_MASK 0x1f
#define _24_HOUR_MASK 0x3f

/*
 * month register mask
 */

#define MONTH_MASK    0x1f
