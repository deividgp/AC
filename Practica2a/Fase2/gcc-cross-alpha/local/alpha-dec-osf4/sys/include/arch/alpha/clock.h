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
 *	"@(#)clock.h	9.1	(ULTRIX/OSF)	10/21/91"
 */

/*
 * Modification History: alpha/clock.h
 *
 * 26-Apr-91 -- afd
 *	Created this file for Alpha support.
 */


/*
 * Time define constants
 */
#define SECMIN		((unsigned)(60))		/* seconds per min */
#define SECHOUR		((unsigned)(60*SECMIN))		/* seconds per hr  */
#define	SECDAY		((unsigned)(24*SECHOUR))	/* seconds per day */
#define SECFEB		((unsigned)(28*SECDAY))		/* per Feb	   */
#define SECLFEB		((unsigned)(29*SECDAY))		/* per Feb (leap)  */
#define SECJUN		((unsigned)(30*SECDAY))		/* per short month */
#define SECJAN		((unsigned)(31*SECDAY))		/* per long month  */
#define	SECYR		((unsigned)(365*SECDAY))	/* per common year */
#define SECQYR		((unsigned)(4*SECYR+SECDAY))	/* per typical 4yr */

#define	YRREF		1970
#define	YRREFCLK	70
#define	LEAPYEAR(year)	((year)%4==0)		/* good till the year 2400 */

/*
 * This offset used to change the contents of the year field
 * in the TOY chips to a value that the console will not
 * recognize and adjust according to the following console
 * init code
 *
 * If (os_type == NT) {
 *     if ((toy.year >= 93) && (toy.year <= 99)) toy.year -= 80;
 *     else if ((toy.year >= 0) && (toy.year <= 12)) toy.year += 20;
 * } else {
 *     if ((toy.year >= 13) && (toy.year <= 19)) toy.year += 80;
 *     else if ((toy.year >= 20) && (toy.year <= 40)) toy.year -= 20;
 * }
 *
 * This algorithm is used on Jensen, Alcor and friends, Avanti, and Sable
 * that I know of.
 *
 * A number of 52 will give UNIX a starting number of 96 - 52 => 44 for the
 * TOY year field.  40 is in range of the implied VMS console checking above.
 */
#define UNIX_YEAR_OFFSET 52

/* Following defines are no longer being used */

#define	UNITSPERSEC	((unsigned)(10000000))		/* 100ns units/sec */

/*
 * TODRZERO is what the TODR should contain when the ``year'' begins.
 * The TODR should always contain a number between [TODRZERO] and
 * [TODRZERO + "number of 100ns time units in a year"].
 * On Alpha systems, the TODR (AT) is kept as the number of 100ns time units.
 * The value 0x185C22CE4000 is the number of 100ns time units in 31 days.
 * We use this as a base value in the TODR to detect if the TODR has been reset.
 */
#define	TODRZERO	0x185c22ce4000
