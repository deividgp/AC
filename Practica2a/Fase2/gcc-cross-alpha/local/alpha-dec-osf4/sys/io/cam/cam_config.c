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
#pragma ident "@(#)$RCSfile: cam_config.c,v $ $Revision: 1.1.49.2 $ (DEC) $Date: 1998/05/01 19:38:40 $"

/************************************************************************
 *
 * File:	cam_config.c
 * Date:	March 8, 1991
 * Author:	Robin T. Miller
 *
 * Description:
 *	CAM peripheral driver configuration information.
 *
 * Modification History:
 *
 *	05/24/91	maria
 *			Added an entry in the CAM peripheral driver
 *			configuration table for the CAM disk driver.
 *
 *	06/07/91	maria
 *			Changed uba_driver structure to reflect the
 *			use of rz/asc for booting.
 *			Changed ifdef checks of NCAM to be NASC.
 *	06/20/91	dallas
 *			Added ctape to this file once again.
 *	06/28/91        rps
 *                      Added new configuration code.  Dynamic allocation
 *                      and addition of sim's.  
 *	07/03/91	jag
 *			changed the routines cdrv_*() to ccfg_*().
 *	07/31/91	dallas
 *			Added tz routines for the wrapper
 *	12/04/91	jag
 *			Corrected the comments for VENDORS to add their drivers.
 *
 */

/*
 * This version of cam_config.c is intended for OSF use.
 */
#include <io/common/iotypes.h>
#include <sys/types.h>			/* system level types */

#include <sys/param.h>			/* system level parameter defs */
#include <sys/buf.h>
#include <mach/vm_param.h>
#include <io/cam/dec_cam.h>
#include <io/cam/cam.h>
#include <hal/cpuconf.h>
#include <io/common/devdriver.h>
#include <io/cam/cam_config.h>
#include <io/cam/sim_config.h>
#include <io/cam/cam_debug.h>

#include "asc.h"
#include "tcds.h"
#include "tza.h"
#include "pza.h"
#include "scsi.h"
#include "xza.h"
#include "siop.h"
#include "psiop.h"
#include "aha.h"
#include "ata.h"
#include "isp.h"
#include "itpsa.h"

extern int cpu;

#if NSCSI > 0
int cam_probe();

/* JAG: these should be together */
caddr_t camstd[] = { 0 };
extern struct controller *camminfo[];
extern struct device *camdinfo[];

extern int ccfg_ctlr_attach();
extern int ccfg_slave();
extern int ccfg_attach(); 

extern CAM_HBA_LIST_ENTRY cam_hba_list[];
extern CAM_DME_LIST_ENTRY cam_dme_list[];
extern int cam_hba_entries;
extern int cam_hba_limit;
extern int cam_dme_entries;
extern int cam_dme_limit;

/*
 * Setup the driver structures for auto-configuration code.
 */

struct driver camdriver = {
	cam_probe,		/* CAM SIM ASC HBA probe function.	*/
	ccfg_slave,		/* CAM cdrv slave function.		*/
	ccfg_ctlr_attach,
	ccfg_attach,		/* CAM cdrv attach function.		*/
	(int (*)()) 0,		/* Driver start transfer function.	*/
	camstd,			/* Pointer to device CSR addresses.	*/
	"rz",			/* Name of the device.			*/
	camdinfo,		/* Pointers to device structures.	*/
	"cam",			/* Name of the controller.		*/
	camminfo,		/* Pointers to controller structures.	*/
	0,			/* Want exclusive use of bdp's flag.	*/
	0,			/* Size of first csr area .		*/
	0,			/* Address space of first csr area.	*/
	0,			/* Size of second csr area.		*/
	0 			/* Address space of second csr area.	*/
};

/*
 * "scsi" is the "generic" scsi controller which all SCSI devices
 * are attached to.  "scsi" is then attached to various buses such
 * as tza, tcds, and pza.
 */
int scsiintr() {}
struct driver scsidriver; /* These aren't used, but are needed to satisfy
			   * the references in ioconf.c.
			   */

#if (NASC > 0) || (NTCDS > 0)
/*
 * Controller driver structure for ASC Host Bus Adapter (HBA).
 */
extern int sim94_probe();

struct driver ascdriver = {
	sim94_probe,		/* CAM SIM ASC HBA probe function.	*/
	ccfg_slave,		/* CAM cdrv slave function.		*/
	ccfg_ctlr_attach,
	ccfg_attach,		/* CAM cdrv attach function.		*/
	(int (*)()) 0,		/* Driver start transfer function.	*/
	camstd,			/* Pointer to device CSR addresses.	*/
	"rz",			/* Name of the device.			*/
	camdinfo,		/* Pointers to device structures.	*/
	"scsi",			/* Name of the controller.		*/
	camminfo,		/* Pointers to controller structures.	*/
	0,			/* Want exclusive use of bdp's flag.	*/
	0,			/* Size of first csr area .		*/
	0,			/* Address space of first csr area.	*/
	0,			/* Size of second csr area.		*/
	0 			/* Address space of second csr area.	*/
};
#endif /* NASC > 0 || NTCDS > 0 */

#if NXZA > 0
/*
** Controller driver structure for the XZA/SCSI adapter.
*/
extern skz_probe();

struct driver skzdriver = {
	skz_probe,		/* A stub for XZA */
	ccfg_slave,		/* CAM cdrv slave function.		*/
	ccfg_ctlr_attach,
	ccfg_attach,		/* CAM cdrv attach function.		*/
	(int (*)()) 0,		/* Driver start transfer function.	*/
	camstd,			/* Pointer to device CSR addresses.	*/
	"rz",			/* Name of the device.			*/
	camdinfo,		/* Pointers to device structures.	*/
	"scsi",			/* Name of the controller.		*/
	camminfo,		/* Pointers to controller structures.	*/
	0,			/* Want exclusive use of bdp's flag.	*/
	0,			/* Size of first csr area .		*/
	0,			/* Address space of first csr area.	*/
	0,			/* Size of second csr area.		*/
	0 			/* Address space of second csr area.	*/
};

#endif /* NXZA > 0 */


#if NSIOP > 0

/* Cobra SCSI driver */
extern siop_probe();

struct driver siopdriver = {
    siop_probe,       	    /* CAM SIM SIOP HBA probe function.      */
    ccfg_slave,             /* CAM cdrv slave function.             */
    ccfg_ctlr_attach,
    ccfg_attach,            /* CAM cdrv attach function.            */
    (int (*)()) 0,          /* Driver start transfer function.      */
    camstd,                 /* Pointer to device CSR addresses.     */
    "siop",                 /* Name of the device.                  */
    camdinfo,               /* Pointers to device structures.       */
    "scsi",                 /* Name of the controller.              */
    camminfo,               /* Pointers to controller structures.   */
    0,                      /* Want exclusive use of bdp's flag.    */
    0,                      /* Size of first csr area .             */
    0,                      /* Address space of first csr area.     */
    0,                      /* Size of second csr area.             */
    0                       /* Address space of second csr area.    */
};

#endif /* NSIOP > 0 */

#if NTZA > 0
/*
 * Controller driver structure for TZA Host Bus Adapter (HBA).
 */
extern int kztsa_probe();

struct driver tzadriver = {
        kztsa_probe,            /* CAM SIM ASC HBA probe function.      */
        ccfg_slave,             /* CAM cdrv slave function.             */
        ccfg_ctlr_attach,
        ccfg_attach,            /* CAM cdrv attach function.            */
        (int (*)()) 0,          /* Driver start transfer function.      */
        camstd,                 /* Pointer to device CSR addresses.     */
        "tza",                  /* Name of the device.                  */
        camdinfo,               /* Pointers to device structures.       */
        "scsi",                 /* Name of the controller.              */
        camminfo,               /* Pointers to controller structures.   */
        0,                      /* Want exclusive use of bdp's flag.    */
        0,                      /* Size of first csr area .             */
        0,                      /* Address space of first csr area.     */
        0,                      /* Size of second csr area.             */
        0                       /* Address space of second csr area.    */
};
#endif /* NTZA > 0 */

#if NPZA > 0
/*
 * Controller driver structure for PZA Host Bus Adapter (HBA).
 */
extern int pza_probe();

struct driver pzadriver = {
        pza_probe,              /* CAM SIM ASC HBA probe function.      */
        ccfg_slave,             /* CAM cdrv slave function.             */
        ccfg_ctlr_attach,
        ccfg_attach,            /* CAM cdrv attach function.            */
        (int (*)()) 0,          /* Driver start transfer function.      */
        camstd,                 /* Pointer to device CSR addresses.     */
        "pza",                  /* Name of the device.                  */
        camdinfo,               /* Pointers to device structures.       */
        "scsi",                 /* Name of the controller.              */
        camminfo,               /* Pointers to controller structures.   */
        0,                      /* Want exclusive use of bdp's flag.    */
        0,                      /* Size of first csr area .             */
        0,                      /* Address space of first csr area.     */
        0,                      /* Size of second csr area.             */
        0                       /* Address space of second csr area.    */
};
#endif /* NPZA > 0 */

#if NATA > 0

/*
 * Controller driver structure for ATA/IDE Bus Adapter (HBA).
 */
extern ata_probe();

struct driver atadriver = {
    ata_probe,       	    /* CAM SIM AHA HBA probe function.      */
    ccfg_slave,             /* CAM cdrv slave function.             */
    ccfg_ctlr_attach,
    ccfg_attach,            /* CAM cdrv attach function.            */
    (int (*)()) 0,          /* Driver start transfer function.      */
    camstd,                 /* Pointer to device CSR addresses.     */
    "ata",                  /* Name of the device.                  */
    camdinfo,               /* Pointers to device structures.       */
    "scsi",                  /* Name of the controller.              */
    camminfo,               /* Pointers to controller structures.   */
    0,                      /* Want exclusive use of bdp's flag.    */
    0,                      /* Size of first csr area .             */
    0,                      /* Address space of first csr area.     */
    0,                      /* Size of second csr area.             */
    0                       /* Address space of second csr area.    */
};

#endif /* NATA > 0 */

#if NAHA > 0

/* Jensen SCSI driver */
extern aha_probe();

struct driver ahadriver = {
    aha_probe,       	    /* CAM SIM AHA HBA probe function.      */
    ccfg_slave,             /* CAM cdrv slave function.             */
    ccfg_ctlr_attach,
    ccfg_attach,            /* CAM cdrv attach function.            */
    (int (*)()) 0,          /* Driver start transfer function.      */
    camstd,                 /* Pointer to device CSR addresses.     */
    "aha",                  /* Name of the device.                  */
    camdinfo,               /* Pointers to device structures.       */
    "scsi",                  /* Name of the controller.              */
    camminfo,               /* Pointers to controller structures.   */
    0,                      /* Want exclusive use of bdp's flag.    */
    0,                      /* Size of first csr area .             */
    0,                      /* Address space of first csr area.     */
    0,                      /* Size of second csr area.             */
    0                       /* Address space of second csr area.    */
};

#endif /* NAHA > 0 */


#if NPSIOP > 0

/* PCI NCR 53c810 SCSI driver */
extern psiop_probe();

struct driver psiopdriver = {
    psiop_probe,       	    /* CAM SIM PSIOP HBA probe function.      */
    ccfg_slave,             /* CAM cdrv slave function.             */
    ccfg_ctlr_attach,
    ccfg_attach,            /* CAM cdrv attach function.            */
    (int (*)()) 0,          /* Driver start transfer function.      */
    camstd,                 /* Pointer to device CSR addresses.     */
    "psiop",                /* Name of the device.                  */
    camdinfo,               /* Pointers to device structures.       */
    "scsi",                /* Name of the controller.              */
    camminfo,               /* Pointers to controller structures.   */
    0,                      /* Want exclusive use of bdp's flag.    */
    0,                      /* Size of first csr area .             */
    0,                      /* Address space of first csr area.     */
    0,                      /* Size of second csr area.             */
    0                       /* Address space of second csr area.    */
};

#endif /* NPSIOP > 0 */

#if NISP > 0

/* PCI QLOGIC ISP1020 SCSI driver */
extern isp_probe();

struct driver ispdriver = {
    isp_probe,              /* CAM SIM ISP HBA probe function.      */
    ccfg_slave,             /* CAM cdrv slave function.             */
    ccfg_ctlr_attach,
    ccfg_attach,            /* CAM cdrv attach function.            */
    (int (*)()) 0,          /* Driver start transfer function.      */
    camstd,                 /* Pointer to device CSR addresses.     */
    "isp",                  /* Name of the device.                  */
    camdinfo,               /* Pointers to device structures.       */
    "scsi",                 /* Name of the controller.              */
    camminfo,               /* Pointers to controller structures.   */
    0,                      /* Want exclusive use of bdp's flag.    */
    0,                      /* Size of first csr area .             */
    0,                      /* Address space of first csr area.     */
    0,                      /* Size of second csr area.             */
    0                       /* Address space of second csr area.    */
};

#endif /* NISP > 0 */

#if NITPSA > 0

extern itpsa_probe();

struct driver itpsadriver = {
        itpsa_probe,            /* probe */
        ccfg_slave,             /* slave */
        ccfg_ctlr_attach,       /* cattach */
        ccfg_attach,            /* dattach */
        (int (*)()) 0,          /* go */
        camstd,                 /* addr_list */
        "itpsa",                /* dev_name */
        camdinfo,               /* dev_list */
        "scsi",                 /* ctlr_name */
        camminfo,               /* ctlr_list */
        0,                      /* xclu */
        0,                      /* addr1_size */
        0,                      /* addr1_atype */
        0,                      /* addr2_size */
        0,                      /* addr2_atype */
        0,                      /* ctlr_unattach */
        0                       /* dev_unattach */
};

#endif  /* NITPSA > 0 */

/* VENDOR: Add the extern declaratios for your hardware following this
    comment line! */

/*
 * CAM Peripheral Driver Configuration Table.
 */

int
pdrv_dummy_sa_rtn()
{
 return( 0 );
}

CAM_PERIPHERAL_DRIVER cam_peripheral_drivers[] = {

/* VENDOR: Add your hardware entries following this comment line! */


/* VENDOR: Add your hardware entries before this comment line! */

	{ "zz", pdrv_dummy_sa_rtn, pdrv_dummy_sa_rtn }
};

int cam_pdrv_entries =
  (sizeof(cam_peripheral_drivers) / sizeof(cam_peripheral_drivers[0])) - 1;

void
init_cam_components( void )
{
}

cam_probe(csr, prb)
caddr_t csr;
struct controller *prb;
{
    int retval = 1;
    char *hbaname;
    char *dmename;
    char modname[32];             /* this shouldn't be hard coded - RPS */

    switch( cpu )
        {
	case DEC_4000:
	    hbaname = "siopco";
	    dmename = "null";
	    break;

        case DEC_2000_300:
	case DEC_1000:
	case DEC_2100_A500:
	case DEC_2100_C500:
            hbaname = "aha";
            dmename = "null";
            break;

        default:
	    if ( prb->ctlr_num == 0 )               /* base scsi? */
	      {
		hbaname = "asc";
		dmename = "dma94";
	      }
            else                               /* TC scsi */
	      {
		if( tc_addr_to_name( csr, modname ) == -1)
		  printf("cam_probe: tc_addr_to_name failed ");
		hbaname = modname;
		dmename = modname;
	      }
	    break;
	}

    if ( name_lookup_hba_probe( hbaname, csr, prb ) != CAM_REQ_CMP )
        {
	/* 
	 * If the attach fails don't do any further initialization.
	 */
	PRINTD( prb->ctlr_num, NOBTL, NOBTL, CAMD_INOUT,
	   ("cam_probe: hba probe lookup ('%s') failed.\n", hbaname ) );
	retval = CAM_FAILURE;
        }

    return retval;
    }

#endif
