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
 * @(#)$RCSfile: mc146818clock.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 1995/06/26 19:38:14 $
 */

#ifndef _HAL_MCCLOCK_H_
#define _HAL_MCCLOCK_H_
/*
 * Standard PC location for Base address of RDP and RAP
 * Initialize mc146818clock_rdp/rap to these values.
 * So a standard PC will not need to init them, otherwise
 * a system needs to init tem in cpu_init().
 */
#define PC_RAP_BASE	0x70
#define PC_RDP_BASE	0x71

/* 
 * Register definitions
 */
#define RTC_SECS   0x0
#define RTC_MINS   0x2
#define RTC_HRS    0x4
#define RTC_DAYS   0x7
#define RTC_MONTHS 0x8
#define RTC_YEARS  0x9
#define RTC_REGA   0xa
#define RTC_REGB   0xb
#define RTC_REGC   0xc
#define RTC_REGD   0xd

/*
 * Register A bit definitions
 */
#define RTA_DV_MASK	(u_char)0x70
#define RTA_DV_OSC_ENABLE (u_char)0x20

#define	RTA_UIP		(u_char)0x80		/* update in progress */
#define	RTA_DV2		(u_char)0x40
#define	RTA_DV1		(u_char)0x20
#define	RTA_DV0		(u_char)0x10
#define	RTA_DVRESET	(u_char)(7<<4)		/* reset divider chain */
#define	RTA_RSNONE	(u_char)0		/* disable periodic intr and SQW */
#define RTA_RS0		(u_char)0x01
#define RTA_RS1		(u_char)0x02
#define RTA_RS2		(u_char)0x04
#define RTA_RS3		(u_char)0x08
/* Here are rates to drive the periodic interrupt - we can try other rates */
#define RTA_1ms		(u_char)(RTA_RS1|RTA_RS2)	/* every 1 ms */
#define RTA_2ms		(u_char)(RTA_RS0|RTA_RS1|RTA_RS2)/* every 2 ms */
#define RTA_4ms		(u_char)(RTA_RS3)		/*       4 ms */
#define RTA_8ms		(u_char)(RTA_RS0|RTA_RS3)	/*       8 ms */
#define RTA_15ms	(u_char)(RTA_RS1|RTA_RS3)	/*      15 ms */

/*
 * Register B bit definitions
 */
#define	RTB_SET		(u_char)0x80	/* inhibit date update */
#define	RTB_PIE		(u_char)0x40	/* enable periodic interrupt */
#define	RTB_AIE		(u_char)0x20	/* enable alarm interrupt */
#define	RTB_UIE		(u_char)0x10	/* enable update-ended interrupt */
#define	RTB_SQWE	(u_char)0x08	/* square wave enable */
#define	RTB_DMBINARY	(u_char)0x04	/* binary data (0 => bcd data) */
#define	RTB_24HR	(u_char)0x02	/* 24 hour mode (0 => 12 hour) */
#define	RTB_DSE		(u_char)0x01	/* daylight savings mode enable */

#define RTB_EXPECT_MASK	(u_char)(RTB_DMBINARY | RTB_24HR | RTB_DSE)
#define RTB_EXPECT	(u_char)(RTB_DMBINARY | RTB_24HR)


/*
 * Register C bit definitions
 */
#define	RTC_IRQF	(u_char)0x80	/* interrupt request flag */
#define	RTC_PF		(u_char)0x40	/* periodic interrupt flag */
#define	RTC_AF		(u_char)0x20	/* alarm interrupt flag */
#define	RTC_UF		(u_char)0x10	/* update-ended interrupt flag */

/*
 * Register D bit definitions
 */
#define	RTD_VRT		(u_char)0x80	/* valid RAM and time flag */

/*
 * Function prottypes
 */
u_long	mc146818_readtodr();
int	mc146818_writetodr(u_long yrtime);

#endif
