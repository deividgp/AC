
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

#pragma ident "@(#)$RCSfile: pci_option_data.c,v $ $Revision: 1.1.145.7 $ (DEC) $Date: 1999/01/13 21:14:23 $"

/* 
 * derived from tc_option_data.c	2.2      (ULTRIX)  3/2/90;
 */

/***************************************************************************/
/*                                                                         */
/* MODULE NAME: pci_option_data.c					   */
/* 									   */ 
/* LOCATION:	.../src/kernel/data					   */
/* 									   */ 
/* DESCRIPTION:								   */
/*		Contains data table for PCI bus options. This table maps   */
/*		option board vendor & device id name with device or        */
/*		controller name in the config file. The pci_option         */
/*		structure is defined in io/dec/pci/pci.h.		   */
/* 									   */ 
/***************************************************************************/


#include <io/dec/pci/pci.h>
#include <io/dec/pci/pci_debug.h>
#include <io/dec/eisa/eisa.h>


extern int decppbconf();
extern struct eisa_sw eisa_sw;

int
nosioconf()
{
	PCIPRINTF(PCID_CNFG_SLOT, ("pci-isa/sio bridge conf code called.\n"));
}

int
nopcebconf()
{
	PCIPRINTF(PCID_CNFG_SLOT, ("pci-eisa/pceb bridge conf code called.\n"));
}


#include "isa.h"
#if NISA > 0
/* for now */
int	sioconf() 
{ 
    extern int sio_dma_alloc();
    extern int sio_dma_load();
    extern int sio_dma_unload();
    extern int sio_dma_dealloc();
    extern int sio_dma_init();
    extern int sio_dma_config();
/*
    extern u_long probe_sysmap;
    extern vm_offset_t isa_io_base;
    extern vm_offset_t isa_mem_base;
*/
    struct controller *get_isa_controller(); /* DGD_TODO */

    /*
     * setup uninitialized portions of eisa switch
     */
    if (!eisa_sw.dma_map_alloc)
      eisa_sw.dma_map_alloc   = sio_dma_alloc;

    if (!eisa_sw.dma_map_load)
      eisa_sw.dma_map_load    = sio_dma_load;

    if (!eisa_sw.dma_map_unload)
      eisa_sw.dma_map_unload  = sio_dma_unload;

    if (!eisa_sw.dma_map_dealloc)
      eisa_sw.dma_map_dealloc = sio_dma_dealloc;

    if (!eisa_sw.dma_init)
      eisa_sw.dma_init        = sio_dma_init;

    if (!eisa_sw.dma_config)
      eisa_sw.dma_config      = sio_dma_config;

    /* These values could be derived from eisa_sw
     * but left in tact for compatibility to platforms that
     * directly support eisa OR isa, but not both
     */
/*
    probe_sysmap = eisa_sw.sparse_io_base;
    isa_io_base = eisa_sw.sparse_io_base;
    isa_mem_base = eisa_sw.sparse_mem_base;
*/

    /* Assumption: rest of eisa_sw setup in platform code before now */
/*
    sio_dma_init();
*/
    PCIPRINTF(PCID_CNFG_SLOT, ("sioconf placeholder \n")); 
}
#else
#define sioconf	nosioconf
#endif /* isa */


#include "eisa.h"
#if NEISA > 0
int	pcebconf() 
{ 
    extern int isp_dma_alloc();
    extern int isp_dma_load();
    extern int isp_dma_unload();
    extern int isp_dma_dealloc();
    extern int isp_dma_init();
    extern int isp_dma_config();
    extern io_handle_t       isp_base;

    /*
     * setup uninitialized portions of eisa switch
     */
    if (!eisa_sw.dma_map_alloc)
      eisa_sw.dma_map_alloc   = isp_dma_alloc;

    if (!eisa_sw.dma_map_load)
      eisa_sw.dma_map_load    = isp_dma_load;

    if (!eisa_sw.dma_map_unload)
      eisa_sw.dma_map_unload  = isp_dma_unload;

    if (!eisa_sw.dma_map_dealloc)
      eisa_sw.dma_map_dealloc = isp_dma_dealloc;

    if (!eisa_sw.dma_init)
      eisa_sw.dma_init        = isp_dma_init;

    if (!eisa_sw.dma_config)
      eisa_sw.dma_config      = isp_dma_config;

    /* These values could be derived from eisa_sw
     * but left in tact for compatibility to platforms that
     * directly support eisa OR isa, but not both
     */
    isp_base = eisa_sw.sparse_io_base;

    /* Assumption: rest of eisa_sw setup in platform code before now */
    isp_dma_init();
     
     PCIPRINTF(PCID_CNFG_SLOT, ("pcebconf placeholder \n")); 
}
#else
#define pcebconf nopcebconf
#endif /* eisa */

#include "i2o.h"
#if NI2O > 0
extern int	i2o960conf();
extern int	i2oSA_FBconf();
extern int	i2ogen_conf();
#else
int i2o960conf() 
   { PCIPRINTF(PCID_CNFG_SLOT, ("i2o960conf placeholder \n")); }
int i2oSA_FBconf() 
   { PCIPRINTF(PCID_CNFG_SLOT, ("i2oSA_FBconf placeholder \n")); }
int i2ogen_conf() 
   { PCIPRINTF(PCID_CNFG_SLOT, ("i2ogen_conf placeholder \n")); }
#endif /* i2o */

#include "vba.h"
#if NVBA > 0
extern int	ebv10_vmeconf();
#define vmeconf ebv10_vmeconf
extern int	 univ_vmeconf();
#define vmeconf1 univ_vmeconf
#else
int
vmeconf()
{ 
     PCIPRINTF(PCID_CNFG_SLOT, ("vmeconf placeholder \n")); 
}
int
vmeconf1()
{ 
     PCIPRINTF(PCID_CNFG_SLOT, ("vmeconf1 placeholder \n")); 
}
#endif /* vba */

#include "pcmcia.h"
#if NPCMCIA > 0
extern int
pd6729_conf();
#else
int
pd6729_conf()
{ 
     PCIPRINTF(PCID_CNFG_SLOT, ("pd6729_conf placeholder \n")); 
}
#endif 

#include "ata.h"
#if NATA > 0
extern int 
ACER_M1543C_conf();
extern int
CMD_PCI0646_conf();
extern int
CMD_PCI0640B_conf();
extern int
CYPRESS_82C693_conf();
extern int
DATATECH_2130S_conf();
extern int
SYMPHONY_101P_conf();
extern int
ata_unknown_conf();
#else
int
ACER_M1543C_conf()
{
  PCIPRINTF(PCID_CNFG_SLOT, ("ACER M1543C placeholder \n")); 
}
int
CMD_PCI0646_conf()
{
  PCIPRINTF(PCID_CNFG_SLOT, ("CMD_0646 placeholder \n")); 
}
int
CMD_PCI0640B_conf()
{
  PCIPRINTF(PCID_CNFG_SLOT, ("CMD_0640B placeholder \n")); 
}
int
CYPRESS_82C693_conf()
{
  PCIPRINTF(PCID_CNFG_SLOT, ("CYPRESS_82C693 placeholder \n")); 
}
int
DATATECH_2130S_conf()
{
  PCIPRINTF(PCID_CNFG_SLOT, ("DATATECH_2130S placeholder \n")); 
}
int
SYMPHONY_101P_conf()
{
  PCIPRINTF(PCID_CNFG_SLOT, ("SYMPHONY_101P placeholder \n")); 
}
int
ata_unknown_conf()
{
  PCIPRINTF(PCID_CNFG_SLOT, ("unknown ata device placeholder \n")); 
}
#endif

/*
 * Dynamically added extern declarations
 * Note: If the struct pci_option line is changed you must modify
 * the mkdata utility as it keys on that line for placement of
 * dynamically added externs. The mkdata utility searches for the
 * string "option [" with a space between the "n" and the "[".
 */
/*
 * The eight (possible) PCI config header Device Identification
 * fields and a match-on flag (mo_flag) to indicate whether the
 * register should be used to match driver to device.
 */

struct pci_option pci_option [] =
{
 /*  SW	   vendor   device   rev     base     sub-     prog.    subsys   subsys  */
 /*  REV     id       id             class    class    i/f      vendor   device  */
 /*                                                               id       id    */
 /*  ---   -----    ----      ---    -----    -----    ----     ------   ------  */
 /*         vid      did     rev      base     sub      pif     sub-vid  sub-did */
 /*       mo_flag  mo_flag  mo_flag  mo_flag  mo_flag  mo_flag  mo_flag  mo_flag */
 /*  ---  -------  -------  -------  -------  -------  -------  -------  ------- */
 /* driver   type   adpt					                 */
 /*  name           config							 */

 /* DEC 21050 PPB */

 { 0x210, DEC_ID, DEC_21040,  0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tu",   'C',     0},
 { 0x210, DEC_ID, DEC_21041,  0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tu",   'C',     0},
 { 0x210, DEC_ID, DEC_21140,  0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tu",   'C',     0},
 { 0x210, DEC_ID, DEC_21142,  0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tu",   'C',     0},
 { 0x210, TI_ID, TI_TMS380,   0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tra",  'C',     0},
 { 0x210, TCC_ID, TI_TMS380,  0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tra",  'C',     0},
 { 0x210, 0x10EF, 0x8154,     0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tra",  'C',     0},
 { 0x210, DEC_ID, DEC_DEFPA,  0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "fta",  'C',     0},
 { 0x210, DEC_ID, DEC_DGLPB,  0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "lta",  'C',     0},
 { 0x210,TOSHIBA_ID,DEC_DGLPA,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "lpa",  'C',     0},
 { 0x210, TI_ID, TI_COMET,    0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "comet",  'C',     0},
 { 0x210, DEC_ID, DEC_TGA,    0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tga",  'C',     0},
 { 0x210, DEC_ID, DEC_TGA2,    0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "tga",  'C',     0},
 { 0x210, DEC_ID, DEC_PVP,    0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "pvp",  'C',     0},
 { 0x210, DEC_ID, DEC_PZA,    0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "pza",  'A',     0},
 /* DEC 21050 PPB */
 { 0x210, DEC_ID, DEC_PPB,    0, BASE_BRIDGE, SUB_PCI,   0,      0,        0,
             1,      1,       0,       1,       1,       0,      0,        0,
    "pci",  'A',  decppbconf},
 /* Future DEC PPBs */
 { 0x210, DEC_ID,    0,       0, BASE_BRIDGE, SUB_PCI,   0,      0,        0,
             1,      0,       0,       1,       1,       0,      0,        0,
    "pci",  'A',  decppbconf},
 /* Third-party PPBs */
 { 0x210,    0,      0,       0, BASE_BRIDGE, SUB_PCI,   0,      0,        0,
             0,      0,       0,       1,       1,       0,      0,        0,
    "pci",  'A',  decppbconf},
 { 0x210,INTEL_ID,INTEL_PCEB, 0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "eisa", 'A',    pcebconf},
 { 0x210, INTEL_ID,INTEL_SIO, 0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "isa",  'A',    sioconf},
 { 0x210,    0,      0,       0, BASE_BRIDGE, SUB_ISA,   0,      0,        0,
             0,      0,       0,       1,       1,       0,      0,        0,
    "isa",  'A',    sioconf},
 { 0x210, DEC_ID, DEC_NVRAM,  0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
  "pnvram", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_875,0,       0,	0,	 0,	 0,	   0,
	     1,	     1,	      0,       0,	0,	 0,	 0,	   0,
   "itpsa", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_895,0,       0,	0,	 0,	 0,	   0,
	     1,	     1,	      0,       0,	0,	 0,	 1,	   0,
   "itpsa", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_895,0,       0,	0,	 0, OLD_NCR_ID,	   0,
	     1,	     1,	      0,       0,	0,	 0,	 1,	   0,
   "itpsa", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_895,0,       0,	0,	 0, 0x13e9,	   0,
	     1,	     1,	      0,       0,	0,	 0,	 1,	   0,
   "itpsa", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_896,0,       0,	0,	 0,	 0,	   0,
	     1,	     1,	      0,       0,	0,	 0,	 1,	   0,
   "itpsa", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_896,0,       0,	0,	 0, 0x0e11,	   0,
	     1,	     1,	      0,       0,	0,	 0,	 1,	   0,
   "itpsa", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_896,0,       0,	0,	 0, OLD_NCR_ID,	   0,
	     1,	     1,	      0,       0,	0,	 0,	 1,	   0,
   "itpsa", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_896,0,       0,	0,	 0, 0x13e9,	   0,
	     1,	     1,	      0,       0,	0,	 0,	 1,	   0,
   "itpsa", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_810,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
   "psiop", 'C',     0},
 { 0x210, NCR_ID,  NCR_810,   0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
   "psiop", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_810A, 0,     0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
   "psiop", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_825,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
   "psiop", 'C',     0},
 { 0x210, OLD_NCR_ID, NCR_860,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
   "psiop", 'C',     0},
 /* ncr810-driver entry for itpsa-875 failover */
 { 0x210, OLD_NCR_ID, NCR_875,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
   "psiop", 'C',     0},
 { 0x210,ATI_ID,ATI_MACH64_GX,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "ati",  'C',     0},
 { 0x210,ATI_ID,ATI_MACH64_CX,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "ati",  'C',     0},
 { 0x210,ATI_ID,ATI_MACH64_CT,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "ati",  'C',     0},
 { 0x210,CPQ_1280P_VID,CPQ_1280P_DID,0,0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "qvision",  'C',     0},
 { 0x210, S3_ID, S3_TRIO32,   0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "trio",  'C',     0},
 { 0x210, S3_ID, S3_TRIO64,   0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "trio",  'C',     0},

 /* Generic VGA driver */
 { 0x210,    0,      0,       0, BASE_DISPLAY, SUB_VGA,  0,      0,        0,
             0,      0,       0,       1,       1,       0,      0,        0,
    "vga",  'C',     0},

 /* Generic VGA driver, prior to finalized class codes */
 { 0x210,    0,      0,       0, BASE_BC, SUB_PRE_VGA,   0,      0,        0,
             0,      0,       0,       1,       1,       0,      0,        0,
    "vga",  'C',     0},

 { 0x210,QLOGIC_ID,QLOGIC_ISP1020,0,   0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "isp",  'A',     0},
 { 0x210, DEC_ID, DEC_7407,   0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "vba",  'A',   vmeconf},
 { 0x210, TUNDRA_ID, CA91C142,0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "vba",  'A',   vmeconf1},
 { 0x210,MYLEX_ID,MYLEX_960P, 0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "xcr",  'C',     0},

 /* Some different PCI ATA/EIDE adapters, some with only limited testing */
 { 0x210, DATATECH_ID, DATATECH_2130S, 0, 0,    0,       0,      0,        0,
	     1,      1,       0,       0,       0,       0,      0,        0,
    "ata", 'A',            DATATECH_2130S_conf},
 { 0x210, SYMPHONY_ID, SYMPHONY_101P, 0, 0,     0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "ata", 'A',      SYMPHONY_101P_conf},
 { 0x210, SYMPHONY_ID, SYMPHONY_105, 0, 0,      0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "ata", 'A',      0},
 { 0x210, CMDTECH_ID, CMD_PCI0646, 0,  0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "ata", 'A',      CMD_PCI0646_conf},
 { 0x210, CMDTECH_ID, CMD_PCI0640B, 0, 0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
    "ata", 'A',      CMD_PCI0640B_conf},
 { 0x210, CYPRESS_ID,CYPRESS_82C693,0,BASE_MASS,SUB_IDE, 0,      0,        0,
             1,      1,       0,       1,       1,       0,      0,        0,
    "ata", 'A',      CYPRESS_82C693_conf},
 { 0x210, ACER_ID,ACER_M1543C,0,BASE_MASS,SUB_IDE,       0,      0,        0,
             1,      1,       0,       1,       1,       0,      0,        0,
    "ata", 'A',      ACER_M1543C_conf},
 { 0x210, 0, 0, 0, BASE_SERIAL_BUS, SUB_USB, PIF_USB_OHCI, 0, 0,
          0, 0, 0, 1,               1,       1,            0, 0,
  "usb", 'A',  0},
 /* Other unknown IDE chips */
 { 0x210,    0,      0,       0, BASE_MASS, SUB_IDE,     0,      0,        0,
             0,      0,       0,       1,       1,       0,      0,        0,
    "ata",  'A',     ata_unknown_conf},

 { 0x210, CIRRUS_ID, CIRRUS_PD6729, 0, 0,	0,	 0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
  "pcmcia", 'A',   pd6729_conf},

 /* KGPSA Fibre Channel Card */
 { 0x210, 0x10df, 0x1ae5,     0,       0,	0,	 0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
  "emx",    'A',     0},
 { 0x210, 0x10df, 0xf700,     0,       0,	0,	 0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
  "emx",    'A',     0},
/* PPB built into i960RP */
 { 0x210,INTEL_ID, 0x0960,    0, BASE_BRIDGE, SUB_PCI,   0,      0,        0,
             1,      1,       0,       1,       1,       0,      0,        0,
    "pci",  'A',  decppbconf},
/* ATU in i960RP -- include I2O msg unit & atu to secondary PCI addresses */
/* hard-code dev-id for now to avoid modifying pci.h			*/
 { 0x210,INTEL_ID,INTEL_I960_ATU, 0,BASE_INTELLIGENT,SUB_I2O,0,	 0,        0,
             1,      1,           0,       1,       1,   0,	 0,        0,
    "i2o",  'A',  i2o960conf},
/* StrongArm-Footbridge I2O */
 { 0x210,  DEC_ID, DEC_SA285, 0,BASE_INTELLIGENT,SUB_I2O,0,      0,        0,
             1,      1,       0,       1,       1,       0,      0,        0,
    "i2o",  'A',  i2oSA_FBconf},
/* Generic I2O -- per 4.2.1.5.1 of V1.5 
 * Note: need to update pci.h w/new class info
 */
 { 0x210,    0,      0,       0,BASE_INTELLIGENT,SUB_I2O,0,      0,        0,
             0,      0,       0,       1,       1,       0,      0,        0,
    "i2o",  'A',  i2ogen_conf},

/* Cluster mem-channel */
 { 0x210, DEC_ID,DEC_RM_SPUR, 0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
  "mchan", 'C',     0},
/* Gigabit Ethernet */
 { 0x210, 0x12ae,  0x1,	      0,       0,	0,	 0,   0x1011,  0x600A, 
	     1,      1,       0,       0,       0,       0,      1,        1,
  "alt", 'C',     0},
/* DAPBA/DAPCA ATM */
 { 0x210, 0x1127,  0x400,     0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
  "lfa", 'C',     0},
    /*
     * Do not delete any table entries above this line or your system
     * will not configure properly.
     *
     * Add any new controllers or devices here.
     */

    /*
	Automatically added entries
    */
    

    /*
     * Do not delete this null entry, which terminates the table or your
     * system will not configure properly.
     */
 { 0x210, PCI_VID_INVALID, 0, 0,       0,       0,       0,      0,        0,
             1,      1,       0,       0,       0,       0,      0,        0,
      "",    '',     0}
					/* Null terminator in the table */
};
