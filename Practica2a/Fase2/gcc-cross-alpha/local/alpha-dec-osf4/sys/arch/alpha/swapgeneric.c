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
#pragma ident "@(#)$RCSfile: swapgeneric.c,v $ $Revision: 1.2.13.5 $ (DEC) $Date: 1994/03/27 09:58:37 $"

/*
 * Modification History: machine/alpha/swapgeneric.c
 *
 * 10-Sep-90 -- afd
 *	Created this file for Alpha support.
 */

#include <sys/param.h>
#include <hal/cpuconf.h>
#include <io/dec/tc/tc.h>
#include <io/common/devdriver.h>

/* for console callbacks */
#include <machine/rpb.h>
#include <machine/entrypt.h>


/*
 * Generic configuration;  all in one
 */
#define BOOTDEVLEN 256

	dev_t	rootdev = NODEV;
	dev_t	dumpdev = NODEV;
	daddr_t	dumplo;
	int	nswap;
	long askme = 0;				/* set by getargs */
	char bootdevice[BOOTDEVLEN];	/* the name of the bootdevice */

extern int bootdevice_translate();

/*
 * This routine takes a console booted_dev string as definied in the SRM and
 * translates this into an rz/ra type name for us. Since the string is platform
 * dependant we call getinfo so the platform code can translate it for us.
 */
void setconf()
{
	if (rootdev != NODEV)
		return;

	if (askme || rootdev == NODEV) {

		/* bootdevice is initialized within pmap_bootstrap before *The Switch* */
		if (!bootdevice_translate(bootdevice, 0)) {
			printf("setconf: Bootdevice parser failed to translate bootdevice %s.\n",bootdevice);
			panic("setconf: bootdevice_parser failed");
		}
	}
}
