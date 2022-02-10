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
#pragma ident "@(#)$RCSfile: dlpi_data.c,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1995/08/18 18:40:15 $"
/*---------------------------------------------------------------------------*
 * Microsoft datalink driver
 * @(#)space.c	1.7	7/24/92 
 *
 *	Configurable parameters.
 *---------------------------------------------------------------------------*/

#include "sys/param.h"
#ifndef __osf__
#include "dlconf.h"
#endif
#include <streamsm/dlpi/dldef.h>

#ifdef __osf__
#include "machine/machtime.h"
#define HZ CLOCKS_PER_SEC
#else
#include "config.h"
#endif

struct dl_defaults_struct  dl_defaults = {
	1500,	/* upper queue lo water mark */
	4500,	/* upper queue hi water mark */
	32767,	/* lower queue lo water mark */
	65535,	/* lower queue hi water mark */
	128,	/* DL_DATALINKS, */	/* default = 128 */
	6,	/* DL_MACS,*/		/* default = 2 */
	6,	/* DL_RETRIES,*/	/* default = 6 */
	2048,	/* DL_PKTS2ADAPT, */	/* default = 2048 */
#ifndef __osf__
	HZ * 1000 /* DL_T1_VALUE */ / 1000,	/* default = HZ * 2 (2 sec) */
	HZ * 400  /* DL_T2_VALUE */ / 1000	/* default = HZ / 2 (1/2 sec) */
#else
	2000, /* DL_T1_VALUE */ 	/* default = HZ * 2 (2 sec) */
	500,  /* DL_T2_VALUE */		/* default = HZ / 2 (1/2 sec) */
	250   /* poll freq in ms */
#endif
};

struct dlmac_info_struct dlmac_info[] = {
/*	name, set_mca, del_mca,bind_sap,udreq,maxsdu,srcdest,dlpi_mac,intr*/
#ifdef __osf__
	"adapter", 	0,	0,	0x48,	1,	0,	0,   1,  0,
	"adapter", 	0,	0,	0x48,	1,	0,	0,   1,  0,
	"adapter", 	0,	0,	0x48,	1,	0,	0,   1,  0,
	"adapter", 	0,	0,	0x48,	1,	0,	0,   1,  0,
	"adapter", 	0,	0,	0x48,	1,	0,	0,   1,  0,
	"adapter", 	0,	0,	0x48,	1,	0,	0,   1,  0,
	"adapter", 	0,	0,	0x48,	1,	0,	0,   1,  0,
	"adapter", 	0,	0,	0x48,	1,	0,	0,   1,  0,
#else
	"e503",	0x4d03,	0x4d04,	-2,	1,	-1,	1,   0,  0,
	"neth",	0x4d03,	0x4d04,	-2,	0,	0,	1,   0,  1, 
	"dep",	0x4d03,	0x4d04,	-2,	0,	0,	1,   0,  1, 
	"csma",	0x4d03,	0x4d04,	-2,	0,	0,	0,   1,  0,
	"wd",	0x4d03,	0x4d04,	-2,	0,	0,	1,   0,  0,
#ifndef SVR4
	NULL,	0x4d03,	0x4d04,	-2,	1,	0,	1,   0,  1 /*defaults*/
#else
	NULL,	0x4d03,	0x4d04,	-2,	0,	0,	0,   1,  0  /*defaults*/
#endif
#endif /* __osf__ */
	/* defaults should be last */
};
