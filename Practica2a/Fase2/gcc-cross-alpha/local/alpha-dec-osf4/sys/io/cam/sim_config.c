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
#pragma ident "@(#)$RCSfile: sim_config.c,v $ $Revision: 1.1.89.2 $ (DEC) $Date: 1998/05/01 19:39:22 $"

/************************************************************************
 *
 * File:	sim_config.c
 * Date:	June 17, 1991
 * Author:	Robert P. Scott
 *
 * Description:
 *	CAM peripheral driver configuration information.
 *
 * Modification History:
 *
 *	91/07/03	rps	Changed TC option names to match std.
 *
 *	91/07/20	rps	Added spurious interrupt handling code.
 *
 * 	91/09/09	rps	Added temp. MAXINE/BIGMAX support.
 *
 *	91/09/26	rps	Needed check for turbo channel exist.
 *
 *	91/10/22	janet
 *	o Removed "#ifndef GENERIC" ifdefs.
 *	o Modified sim_enable_interrupts to take SIM_SOFTC pointer
 *	  as an argument.  Added "#ifdef (DS5000 | DS5000_100)" around
 *	  call to tc_enable_option().
 *
 *	91/10/24	janet
 *	Added Mipsmate support.
 *
 *	91/10/25	janet
 *	Added default configuration functins: hba_default_probe(),
 *	hba_default_attach(), hba_default_chip_reset(), dme_default_attach(),
 *	dme_default_unload().
 *
 *	91/11/15	jag
 *	Made the changes from LARRY to the LR specific defines.
 */

#include <io/common/iotypes.h>
#include <sys/types.h>			/* system level types */
#include <sys/param.h>			/* system level parameter defs */
#include <sys/buf.h>
#include <sys/time.h>
#include <kern/lock.h>
#include <io/cam/dec_cam.h>
#include <mach/vm_param.h>
#include <io/cam/cam.h>
#include <io/cam/scsi_all.h>
#include <hal/cpuconf.h>
#include <io/dec/tc/tc.h>
#include <io/cam/cam_config.h>
#include <io/cam/sim_config.h>
#include <io/cam/cam_debug.h>
#include <io/cam/sim_target.h>
#include <io/cam/sim_cirq.h>
#include <io/cam/dme.h>
#include <io/cam/sim.h>
#include <io/cam/sim_common.h>
#include <io/cam/sim_94.h>
#include <io/cam/scsi_status.h>
#include <io/cam/dme_tcds_94_dma.h>
#include <io/common/devdriver.h>

#include "ata.h"
#include "asc.h"
#include "tcds.h"
#include "tza.h"
#include "pza.h"
#include "isp.h"
#include "itpsa.h"

#include "siop.h"
#include "psiop.h"
#include "aha.h"
#include "xza.h"

/* ---------------------------------------------------------------------- */
/* Local defines.
 */

extern int cpu;
extern SIM_SOFTC *softc_directory[];

#if NASC > 0 || NTCDS > 0
extern sim94_probe(), sim94_attach(), sim94_unload();
extern sim_kn02_chip_reset(), sim_kn02ba_chip_reset();
extern sim_fast_chip_reset(), simfast_attach();

extern ram94_dme_attach(), ram94_dme_unload();
extern tcds_dme_attach(), tcds_dme_unload();
#endif

#if NATA > 0
extern ata_probe(), ata_attach(), ata_unload();
extern ata_reset();
extern ata_dme_attach(), ata_dme_unload();
#endif

#if NTZA > 0
extern kztsa_probe(), kztsa_attach(), kztsa_unload();
extern kztsa_reset();
extern kztsa_dme_attach(), kztsa_dme_unload();
#endif

#if NPZA > 0
extern pza_probe(), pza_attach(), pza_unload();
extern pza_adap_reset();
extern pza_dme_attach(), pza_dme_unload();
#endif
                                 
#if NPSIOP > 0
extern psiop_probe(), psiop_pci_attach(), psiop_unload(), psiop_chip_reset();
#endif	/* NPSIOP > 0 */

#if NISP > 0
extern isp_probe(), isp_attach(), isp_unload(), isp_chip_reset();
#endif /* NISP > 0 */

#if NITPSA > 0
extern itpsa_probe(), itpsa_cattach(), itpsa_unload(), itpsa_chip_reset();
#endif  /* NITPSA > 0 */

#if NSIOP > 0
extern siop_probe(), siop_kn430_attach(), siop_unload(), siop_chip_reset();
#endif	/* NSIOP > 0 */

#if NAHA > 0
extern aha_probe(), aha_attach(), aha_unload(), aha_chip_reset();
#endif  /* NAHA > 0 */

#if NXZA > 0
extern skz_probe(), skz_attach(), skz_reset_attach(), skz_unload();
#else
void xza_enable_intr() {}
#endif /* NXZA > 0 */

extern dme_null_attach(), dme_null_null();

/* Default config functions */
int hba_default_probe(), hba_default_attach(), hba_default_chip_reset(),
    dme_default_attach(), dme_default_unload();


int cam_hba_limit = INIT_CAM_HBA_LIMIT;
int cam_dme_limit = INIT_CAM_DME_LIMIT;

CAM_HBA_LIST_ENTRY           cam_hba_list[INIT_CAM_HBA_LIMIT+1];
CAM_DME_LIST_ENTRY           cam_dme_list[INIT_CAM_DME_LIMIT+1];

int cam_hba_entries = 0;
int cam_dme_entries = 0;

static int config_init = 0;        /* remove this or do it right */

void
init_sim_components( void )
{
    int i;

    if ( config_init != 4192 )           /* init these structs on first */
      {                                  /* time through only */
	for( i=0; i<cam_hba_limit; i++ )
	  {
	    cam_hba_list[i].cs_name = (char *) NULL;
	    cam_hba_list[i].cs_probe = NULL;
	    cam_hba_list[i].cs_unload = NULL;
	  }
	cam_hba_entries = 0;
	
	for( i=0; i<cam_dme_limit; i++ )
	  {
	    cam_dme_list[i].dme_name = (char *) NULL;
	    cam_dme_list[i].dme_init = NULL;
	    cam_dme_list[i].dme_unload = NULL;
	  }
	cam_dme_entries = 0;
	
#if NASC > 0 || NTCDS > 0
    add_cam_hba_entry( "asc", sim94_probe, sim94_attach, sim_kn02_chip_reset, 
		      sim94_unload );
    add_cam_hba_entry( "PMAZ-AA ", sim94_probe, sim94_attach, 
		      sim_kn02_chip_reset, sim94_unload );
    add_cam_hba_entry( "PMAZ-DS ", sim94_probe, sim94_attach, 
		      sim_kn02ba_chip_reset, sim94_unload );
    add_cam_hba_entry( "PMAZ-FS ", sim94_probe, simfast_attach, 
		      sim_fast_chip_reset, sim94_unload );
    add_cam_hba_entry( "PMAZB-AA", sim94_probe, sim94_attach, 
		      sim_kn02ba_chip_reset, sim94_unload );
    add_cam_hba_entry( "PMAZC-AA", sim94_probe, simfast_attach, 
		      sim_fast_chip_reset, sim94_unload );

    add_cam_dme_entry( "ram94", ram94_dme_attach, ram94_dme_unload );
    add_cam_dme_entry( "PMAZ-DS ", tcds_dme_attach, tcds_dme_unload );
    add_cam_dme_entry( "PMAZ-FS ", tcds_dme_attach, tcds_dme_unload );
    add_cam_dme_entry( "PMAZB-AA", tcds_dme_attach, tcds_dme_unload );
    add_cam_dme_entry( "PMAZC-AA", tcds_dme_attach, tcds_dme_unload );
    add_cam_dme_entry( "PMAZ-AA ", ram94_dme_attach, ram94_dme_unload );

#endif /* NASC || NTCDS */

#if NTZA > 0
    add_cam_hba_entry( "KZTSA-AA", kztsa_probe, kztsa_attach,
                      kztsa_reset, kztsa_unload );
    add_cam_dme_entry( "KZTSA-AA", kztsa_dme_attach, kztsa_dme_unload );
#endif /* NTZA */
                       
#if NPZA > 0
    add_cam_hba_entry( "pza", pza_probe, pza_attach,
                       pza_adap_reset, pza_unload );
    add_cam_dme_entry( "pza", pza_dme_attach, pza_dme_unload );
#endif /* NPZA */

#if NPSIOP > 0
    add_cam_hba_entry( "psiop", psiop_probe, psiop_pci_attach,
			psiop_chip_reset, psiop_unload );
#endif /* NPSIOP > 0 */

#if NISP > 0
    add_cam_hba_entry( "isp", isp_probe, isp_attach,
			isp_chip_reset, isp_unload );
#endif /* NISP > 0 */

#if NITPSA > 0
    add_cam_hba_entry( "itpsa", itpsa_probe, itpsa_cattach,
			itpsa_chip_reset, itpsa_unload );
#endif  /* NITPSA > 0 */

#if NSIOP > 0
    add_cam_hba_entry("siopco",siop_probe, siop_kn430_attach,
			siop_chip_reset, siop_unload);
#endif /* NSIOP > 0 */

#if NAHA > 0
    add_cam_hba_entry("aha",aha_probe, aha_attach,
			aha_chip_reset, aha_unload);
#endif /* NAHA > 0 */

#if NATA > 0
    add_cam_hba_entry( "ata", ata_probe, ata_attach, 
		      ata_reset, ata_unload );
    add_cam_dme_entry( "ata", ata_dme_attach, ata_dme_unload );
#endif

#if NXZA > 0
    add_cam_hba_entry ( "xza", skz_probe, skz_attach,
			skz_reset_attach, skz_unload );
#endif /* NXZA > 0 */

    add_cam_dme_entry("null", dme_null_attach, dme_null_null);

    /*
     * Default entries.
     */
    add_cam_hba_entry( "hba_default", hba_default_probe, hba_default_attach,
		       hba_default_chip_reset);
    add_cam_dme_entry( "dme_default", dme_default_attach, dme_default_unload);
    

      }

    config_init = 4192;              /* so we don't go through again */
}

int
add_cam_hba_entry( char *name, int (*probe)(), int (*attach)(),
		  int (*reset_attach)(), int (*unload)() )
{
    int i;

    if ( cam_hba_entries == cam_hba_limit )
      {
        PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT, 
	       ("[b/t/l] (add_cam_hba_entry) Count = %d, cannot yet expand list.\n" ));
	return CAM_REQ_CMP_ERR;
      }

    for( i=0; i<cam_hba_entries && cam_hba_list[i].cs_name &&
	strcmp( name, cam_hba_list[i].cs_name );
	i++ )
      {}

    if ( i < cam_hba_entries )   /* we didn't hit the end of the list? */
      {
	PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT, 
	       ("[b/t/l] (add_cam_hba_entry) duplicate entry '%s'\n", name ));
	return CAM_REQ_CMP_ERR;
      }

    cam_hba_list[cam_hba_entries].cs_name = name;
    cam_hba_list[cam_hba_entries].cs_probe = probe;
    cam_hba_list[cam_hba_entries].cs_attach = attach;
    cam_hba_list[cam_hba_entries].cs_reset_attach = reset_attach;
    cam_hba_list[cam_hba_entries].cs_unload = unload;

    cam_hba_entries++;
    return CAM_REQ_CMP;
}

int 
remove_cam_hba_entry( char *name )
{
    int i;

    for( i=0; i<cam_hba_entries && cam_hba_list[i].cs_name && 
	strcmp( name, cam_hba_list[i].cs_name );
	i++ )
      {}

    if ( i == cam_hba_entries )          /* we hit the end of the list? */
        return CAM_REQ_CMP_ERR;

    while( i < cam_hba_entries )
      {
	cam_hba_list[i].cs_name = 
            cam_hba_list[i+1].cs_name;
	cam_hba_list[i].cs_probe = 
            cam_hba_list[i+1].cs_probe;
	cam_hba_list[i].cs_unload = 
            cam_hba_list[i+1].cs_unload;
	
	i++;
      }

    cam_hba_list[i].cs_name = (char *) NULL;
    cam_hba_list[i].cs_probe = NULL;
    cam_hba_list[i].cs_unload = NULL;

    cam_hba_entries--;
    return CAM_REQ_CMP;
}

int
name_lookup_hba_probe(name, ba, prb)
char *name;
char *ba;
struct controller *prb;
{
  int i;

  for( i=0; i<cam_hba_entries && cam_hba_list[i].cs_name &&
      strcmp( name, cam_hba_list[i].cs_name );
      i++ )
    {}

  if ( i == cam_hba_entries )
    {
      PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT,
	     ("[b/t/l] (name_lookup_hba_probe) name '%s' not found.\n", name ) );
      return CAM_REQ_CMP_ERR;
    }

  return cam_hba_list[i].cs_probe( ba, prb );
}

int
name_lookup_hba_attach( char *name, SIM_SOFTC *sc )
{
  int i;

    PRINTD( NOBTL,NOBTL,NOBTL,CAMD_INOUT,
	   ("[b/t/l] (name_lookup_hba_attach) entry - name='%s', sc=0x%x \n", 
	    name, sc ) );

  for( i=0; i<cam_hba_entries && cam_hba_list[i].cs_name &&
      strcmp( name, cam_hba_list[i].cs_name );
      i++ )
    {}

  if ( i == cam_hba_entries )
    {
      PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT,
	     ("[b/t/l] (name_lookup_hba_attach) name '%s' not found.\n", name ) );
      return CAM_REQ_CMP_ERR;
    }

  return cam_hba_list[i].cs_attach( sc );
}

unsigned long
name_lookup_hba_reset_attach( char *name, SIM_SOFTC *sc )
{
  int i;

    PRINTD( NOBTL,NOBTL,NOBTL,CAMD_INOUT,
	   ("[b/t/l] (name_lookup_hba_reset_attach) entry - name='%s', sc=0x%x \n", 
	    name, sc ) );

  for( i=0; i<cam_hba_entries && cam_hba_list[i].cs_name &&
      strcmp( name, cam_hba_list[i].cs_name );
      i++ )
    {}

  if ( i == cam_hba_entries )
    {
      PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT,
	     ("[b/t/l] (name_lookup_hba_reset_attach) name '%s' not found.\n", name ) );
      return CAM_REQ_CMP_ERR;
    }

  return (unsigned long) cam_hba_list[i].cs_reset_attach;
}


int
add_cam_dme_entry( char *name, int (*init)(), int (*unload)() )
{
    int i;

    if ( cam_dme_entries == cam_dme_limit )
      {
        PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT, 
	       ("[b/t/l] (add_cam_dme_entry) Count = %d, cannot yet expand list.\n" ) );
	return CAM_REQ_CMP_ERR;
      }
    
    for( i=0; i<cam_dme_entries && cam_dme_list[i].dme_name &&
        strcmp( name, cam_dme_list[i].dme_name );
        i++ )
      {}

    if ( i < cam_dme_entries )
      {
	PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT, 
	       ("[b/t/l] (add_cam_dme_entry) duplicate name '%s'\n", name ) );
        return CAM_REQ_CMP_ERR;
      }

    cam_dme_list[cam_dme_entries].dme_name = name;
    cam_dme_list[cam_dme_entries].dme_init = init;
    cam_dme_list[cam_dme_entries].dme_unload = unload;

    cam_dme_entries++;
    return CAM_REQ_CMP;
}

int 
remove_cam_dme_list( char *name )
{
    int i;

    for( i=0; i<cam_dme_entries &&  cam_dme_list[i].dme_name &&
	strcmp( name, cam_dme_list[i].dme_name );
	i++ )
      {}

    if ( i == cam_dme_entries )          /* we hit the end of the list? */
        return CAM_REQ_CMP_ERR;

    while( i < cam_dme_entries )
      {
	cam_dme_list[i].dme_name = 
            cam_dme_list[i+1].dme_name;
	cam_dme_list[i].dme_init = 
            cam_dme_list[i+1].dme_init;
	cam_dme_list[i].dme_unload = 
            cam_dme_list[i+1].dme_unload;
	
	i++;
      }

    cam_dme_list[i].dme_name = (char *) NULL;
    cam_dme_list[i].dme_init = NULL;
    cam_dme_list[i].dme_unload = NULL;

    cam_dme_entries--;
    return CAM_REQ_CMP;
}

int
name_lookup_dme_init( char *name, SIM_SOFTC *sc )
{
  int i;

    PRINTD( NOBTL,NOBTL,NOBTL,CAMD_INOUT,
	   ("[b/t/l] (name_lookup_dme_init) entry - name='%s', sc=0x%x \n", 
	    name, sc ) );

  for( i=0; i<cam_dme_entries && cam_dme_list[i].dme_name &&
      strcmp( name, cam_dme_list[i].dme_name );
      i++ )
    {}

  if ( i == cam_dme_entries )
    {
      PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT,
	     ("[b/t/l] (name_lookup_dme_init) name '%s' not found.\n", name ) );
      return CAM_REQ_CMP_ERR;
    }

  return cam_dme_list[i].dme_init( sc );
}

int
hba_dme_attach( U32 pathid, SIM_SOFTC *sc )
{
    int retval = CAM_REQ_CMP;
    char *hbaname, *dmename;            /* used in config process */
    char modname[32];                   /* TC module name - what size? -RPS */
    caddr_t csr;			/* CSR addess from softc struct */
    unsigned long tpt;

    PRINTD( NOBTL,NOBTL,NOBTL,CAMD_INOUT,
	   ("[b/t/l] (hba_dme_attach) entry - pathid=%d, sc=0x%x \n", pathid, sc ) );

    csr = sc->csr_probe;		/* get what was stored by probe */

    switch( cpu )
        {
	case DEC_3000_500:
	case DEC_3000_300:
	    if( tc_addr_to_name( csr, modname ) == -1)
	      PRINTD( NOBTL, NOBTL, NOBTL, CAMD_INOUT, 
		     ("[b/t/l] (hba_dme_attach) tc_addr_to_name failed ") );
	    hbaname = modname;
	    dmename = modname;
	    break;

	case DEC_4000:
	    hbaname = "siopco";
	    dmename = "null";
	    break;

        default:
	    /* 
	     * Get our controller name and compare it
	     */
	    if(strcmp(((struct controller *)sc->um_probe)->bus_name, 
			    "psiop") == NULL)
	    { 
		hbaname = "psiop";
		dmename = "null";
	    }
	    else if(strcmp(((struct controller *)sc->um_probe)->bus_name, 
			    "aha") == NULL)
	    {
		hbaname = "aha";
		dmename = "null";
	    }
	    else if(strcmp(((struct controller *)sc->um_probe)->bus_name, 
			   "pza") == NULL)
	    {
		hbaname = "pza";
		dmename = "null";
	    }
	    else if(strcmp(((struct controller *)sc->um_probe)->bus_name, 
                            "isp") == NULL)
            {
                hbaname = "isp";
                dmename = "null";
            }
	    else if(strcmp(((struct controller *)sc->um_probe)->bus_name,
			    "itpsa") == NULL)
	    {
		hbaname = "itpsa";
		dmename = "null";
            }
	    else if(strcmp(((struct controller *)sc->um_probe)->bus_name, 
                            "xza") == NULL)
            {
                hbaname = "xza";
                dmename = "null";
            }
	    else if(strcmp(((struct controller *)sc->um_probe)->bus_name, 
                            "ata") == NULL)
            {
                hbaname = "ata";
                dmename = "ata";
            }
	    else 
            {
		 hbaname = "hba_default";
		 dmename = "dme_default";
	    }
            break;
	}

    /*
     * First perform the attach function which will link the SIM XPT to the
     * underlying SIM HBA's and DME's. The softc for this HBA is setup to
     * allow further initialization of the CAM subsystem.
     */
    if ( name_lookup_hba_attach( hbaname, sc ) != CAM_REQ_CMP )
        {
	/* 
	 * If the attach fails don't do any further initialization.
	 */
	printf("hba_dme_attach: (%d/n/n) - hba '%s' attach failed.\n", 
	       pathid, hbaname );
	retval = CAM_REQ_CMP_ERR;
        }
    else
    {
	tpt = name_lookup_hba_reset_attach( hbaname, sc );
	if ( tpt != CAM_REQ_CMP_ERR )
	{
	    sc->hba_chip_reset = (void *) tpt;
	}
	else
	{
	    printf("hba_dme_attach: (%d/n/n) - reset attach of '%s' failed.\n",
		   pathid, hbaname );
	}
    }

    if ( name_lookup_dme_init( dmename, sc ) != CAM_REQ_CMP )
	{
	printf("hba_dme_attach: (%d/n/n) - dme '%s' attach failed.\n",
	       pathid, dmename );
	retval = CAM_REQ_CMP_ERR;
	}

    return retval;
}

sim_enable_interrupts(sc)
SIM_SOFTC *sc;
{
    struct controller attach;	/* used by tc_enable_option */
    struct controller *prb = (struct controller *)sc->um_probe;
    char adapt[30];

    (&attach)->tcindx = prb->tcindx; /* used by tc_enable_option */

    if ((strncmp(prb->bus_name, "tc", 2) == 0) || 
	(strncmp(prb->bus_name, "tza", 3) == 0) || 
	(strncmp(prb->bus_name, "asc", 3) == 0)) {
	/*
	 * CPU doesn't matter in this case, if it's on a tc (or tcds)
	 * then we must enable the tc slot for interrupts.
	 */
	tc_enable_option( &attach );
    }

    switch( cpu )
    {

    default:
	break;
	
    }
}

hba_default_probe()
{
    printf("HBA Probe: Unable to determine SCSI host bus adapter type!\n");
    return(0);
}
hba_default_attach()
{
    printf("HBA Attach: Unable to determine SCSI host bus adapter type!\n");
}
hba_default_chip_reset()
{
    printf("HBA Chip Reset: Unable to determine SCSI host bus adapter type!\n");
}
dme_default_attach()
{
    printf("DME Attach: Unable to determine SCSI host bus adapter type!\n");
}
dme_default_unload()
{
    printf("DME Unload: Unable to determine SCSI host bus adapter type!\n");
}
