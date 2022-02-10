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
 * @(#)$RCSfile: latstr.h,v $ $Revision: 1.1.2.4 $ (DEC) $Date: 1994/05/31 19:29:54 $
 */
/* @(#)latstr.h 1.1 11/23/92 MTC_SRC; from MTC 6.2 11/20/92 */
/*----------------------------------------------------------------------
    latstr		(h) LAT STREAMS implementation consants

    This Software and Related Documentation are Proprietary to
    Meridian Technology Corporation.

    Copyright 1992 Meridian Technology Corporation, St. Louis, MO
    Unpublished -
    All Rights Reserved Under the Copyright Laws of the United States.

    Restricted Rights Legend:  Use, Duplication, or Disclosure by
    the Government is Subject to Restrictions as Set Forth in
    Paragraph (c)(1)(ii) of the Rights in Technical Data and
	Computer Software Clause at DFARS 252.227-7013.  Meridian
	Technology Corporation.
 -----------------------------------------------------------------------*/

#ifndef	LATSTR_H
#define	LATSTR_H	0	/* Indicate file has been read	 */


/*----------------------------------------------------------------------
    Define the compiler limits on how much of bad packets to retain.
 -----------------------------------------------------------------------*/
#define	LATS_E_SIZE	128	/* Retain first 128 bytes	 */

/*----------------------------------------------------------------------
    Define the compiler limits on sessions.
 -----------------------------------------------------------------------*/
#define SES_CREDITS	2	/* 2 credits/session		 */

/*----------------------------------------------------------------------
    Define the ethernet types.
 -----------------------------------------------------------------------*/
#define	LATS_ETHER_NIT		0	/* Sun NIT Interface        */
#define	LATS_ETHER_3COM		0	/* 3com                     */
#define	LATS_ETHER_WDN		1	/* Western Digital          */
#define	LATS_ETHER_WEDL		2	/* Wang WEDL board          */
#define	LATS_ETHER_ES		3	/* Interlan board           */

#define LATS_ETHER_WDD		8	/* DEC WDN driver           */
#define LATS_ETHER_DEP		9	/* DEPCA board              */
#define LATS_ETHER_XDEP		10	/* DEPCA board, old driver  */

#define LATS_DST_SRC		0	/* ATT DLPI standard for    */
                			/* dst and src addresses    */
#define LATS_SRC_DST		1	/* other way around         */
#endif
