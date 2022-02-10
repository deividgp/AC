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
#pragma ident "@(#)$RCSfile: xcr_data.c,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1994/03/28 02:03:02 $"

#include "xcr.h"			/* Config generated defines file */
#include <io/common/iotypes.h>
#include <sys/secdefines.h>
#if SEC_BASE
#include <sys/security.h>
#endif
#include <labels.h>
#include <sys/poll.h>
#include <sys/syslog.h>
#include <sys/systm.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/buf.h>
#include <io/common/devio.h>
#include <sys/mtio.h>
#include <sys/param.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/mode.h>
#include <sys/disklabel.h>
#include <sys/sysinfo.h>
#include <sys/user.h>
#include <mach/vm_param.h>
#include <sys/malloc.h>
#include <ufs/fs.h>
#include <io/common/pt.h>
#include <io/common/devdriver.h>
#include <io/common/devdriver_loadable.h>
#include <io/dec/eisa/xcr_port.h>
#include <io/dec/eisa/xcr_common.h>
#include <io/dec/eisa/re.h>
#include <hal/cpuconf.h>



extern int re_slave();
extern int re_attach();
extern int xcr_probe();
extern int xcr_attach();

#define NSYSDEV 8	/* Max number of devices per controller */
/* --------------------------------------------------------------*/



int nXCR_CTRLS = NXCR;




/* 
 * Configuration structures
 */
struct device *redinfo[NXCR * NSYSDEV];
struct controller *reminfo[NXCR];

XCR_SOFTC *xcr_directory[NXCR];


/* 
 * The unit table
 */

RE_TABLE_ELEM re_unit_table[NXCR * NSYSDEV];

int nRE_MAXUNITS = (NXCR * NSYSDEV);


/*
 * Default i/o timeout
 */
u_long nDEF_IO_TIMO = 40; /* 40 seconds */

/*
 * Default passthru timeout
 */
u_long nDEF_PASS_TIMEOUT = 60*60; /* 1 hour */



/*
 * The default partition sizes (a-h) for the
 * Astro controller.
 */
RE_DEF_SIZE xcr_def_sizes[8] = {
   131072, 0,
   262144, 131072,
  -1, 0,
   0, 0,
   0, 0,
   0, 0,
  -1, 393216,
   0, 0,
};

/*
 * How we get probed
 */
caddr_t xcrstd[] = { 0 };

struct driver xcrdriver = { xcr_probe, re_slave, xcr_attach, re_attach, 0, xcrstd, 
				"re", redinfo, "xcr", reminfo, };
