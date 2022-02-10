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
#pragma ident "@(#)$RCSfile: eisa_option_data.c,v $ $Revision: 1.1.65.2 $ (DEC) $Date: 1999/01/06 17:33:39 $"

/***************************************************************************/
/*                                                                         */
/* MODULE NAME: eisa_option_data.c					   */
/* 									   */ 
/* LOCATION:	.../src/kernel/data					   */
/* 									   */ 
/* DESCRIPTION:								   */
/*		Contains data table for EISA bu options. This table maps   */
/*		option board product id name with device or controller     */
/*		name in the config file. The eisa_option structure is	   */
/*		defined in io/dec/eisa/eisa.h.				   */
/* 									   */ 
/***************************************************************************/

#include	<io/common/devdriver.h>
#include	<io/dec/eisa/eisa.h>

/* Declare this here so it will be merged with the isa copy into one */
struct eisa_sw eisa_sw;

#include "pcmcia.h"
#if NPCMCIA > 0
extern int pcicconf();		/* ISA-PCMCIA config. routine */
#else
#define pcicconf 0
#endif


/*************************** Warning!!! ************************************/
/*									   */
/*    This table is not used to support device drivers in the 4.0 	   */
/*    release. It exists as a Notbinary entry in the alpha/files file	   */
/*    for the 4.0 release in order to support older device driver kits.    */
/*									   */
/**************************************************************************/


/* Loose End... To be fixed!!!
 * Dynamically added extern declarations
 * Note: If the struct eisa_option line is changed you must modify
 * the mkdata utility as it keys on that line for placement of
 * dynamically added externs. The mkdata utility searches for the
 * string "option [" with a space between the "n" and the "[".
 */

struct	eisa_option	eisa_option [] =
{
    /* board	  function    driver  intr_b4 itr_aft	     adpt	*/
    /* id	    name       name    probe   attach type  config	*/
    /* ------	 ------------ ------  ------- ------- ----  ------	*/

    { "CPQ3011", "",           "qvision",    0,  0,   'C',    0},    /* QVISION "spruce" */
    { "CPQ3111", "",           "qvision",    0,  0,   'C',    0},    /* QVISION "fir" */
    { "CPQ3112", "",           "qvision",    0,  0,   'C',    0},    /* QVISION "juniper" */
    { "DEC4220", "NET,ETH",    "ln",     0,      1,   'C',    0},    /* DEC_LANCE */
    { "ADP0001", "AHA1740",    "aha",    0,      1,   'C',    0},    /* ADP1740A SCSI */
    { "ADP0002", "AHA1740",    "aha",    0,      1,   'C',    0},    /* ADP1742A SCSI */
    { "ADP0002", "MSD,FPYCTL", "fdi",    0,      1,   'C',    0},    /* ADP1742A FLPY */
    { "DEC3001", "",           "fta",    0,      1,   'C',    0},    /* DEC_FDDI */
    { "DEC3002", "",           "fta",    0,      1,   'C',    0},    /* DEC_FDDI */
    { "DEC2500", "",           "envram", 0,      0,   'C',    0},    /* EISA NVRAM */
    { "ISA1010", "COM,1",      "ace",    0,      1,   'C',    0},    /* COMM PORTS */
    { "ISA1010", "COM,2",      "ace",    0,      1,   'C',    0},    /* COMM PORTS */
    { "ISA1010", "PAR",        "lp",     0,      0,   'C',    0},    /* PAR PORT */
    { "DEC4250", "",            "tu",    0,      1,   'C',    0},    /* TULIP */
    { "PRO6000", "",            "tra",   0,      1,   'C',    0},    /* DW300 */
    { "PRO6001", "",            "tra",   0,      1,   'C',    0},    /* DW300 */
    { "PRO6002", "",            "tra",   0,      1,   'C',    0},    /* DW300 */
    { "DEC2400", "MSD,FPYCTL", "fdi",    0,      1,   'C',    0},    /* Jensen FLPY */
    { "DEC2A01", "SYSMEM",     "",       0,      1,   'C',    0},    /* DUMMY FOR SLOT 0 */
    { "DEC2A01", "ACECOM,1",      "ace",    0,   1,   'C',    0},    /* COMM PORT 0 */
    { "DEC2A01", "ACECOM,2",      "ace",    0,   1,   'C',    0},    /* COMM PORT 1 */
    { "DEC2A01", "PAR",        "lp",     0,      0,   'C',    0},    /* PAR PORT */
    { "DEC2A01", "MSD,FPYCTL", "fdi",    0,      1,   'C',    0},    /* FLOPPY */
    { "MLX0070", "",    "xcr",   0,      1,   'C',    0},    /* EISA Raid */
    { "MLX0075", "",    "xcr",   0,      1,   'C',    0},    /* EISA Raid */
    { "MLX0077", "",    "xcr",   0,      1,   'C',    0},    /* EISA Raid */
    { "DEC5301", "SYSMEM",     "",       0,      1,   'C',    0},    /* DUMMY FOR SLOT 0 */
    { "DEC5301", "ACECOM,1",      "ace",    0,   1,   'C',    0},    /* COMM PORT 0 */
    { "DEC5301", "ACECOM,2",      "ace",    0,   1,   'C',    0},    /* COMM PORT 1 */
    { "DEC5301", "PAR",        "lp",     0,      0,   'C',    0},    /* PAR PORT */
    { "DEC5301", "MSD,FPYCTL", "fdi",    0,      1,   'C',    0},    /* FLOPPY */
    { "DEC5000", "SYSMEM",     "",       0,      1,   'C',    0},    /* DUMMY FOR SLOT 0 */
    { "DEC5000", "ACECOM,1",      "ace",    0,   1,   'C',    0},    /* COMM PORT 0 */
    { "DEC5000", "ACECOM,2",      "ace",    0,   1,   'C',    0},    /* COMM PORT 1 */
    { "DEC5000", "PAR",        "lp",     0,      0,   'C',    0},    /* PAR PORT */
    { "DEC5000", "MSD,FPYCTL", "fdi",    0,      1,   'C',    0},    /* FLOPPY */
    { "DEC5000", "VID",        "cirrus",    0,   0,   'C',    0},    /* ON BOARD VGA */
    { "PHI8041", "",           "vga",    0,      0,   'C',    0},    /* ISA VGA */
    { "ISA6400", "",           "ati",    0,      0,   'C',    0},    /* ISA ATI Mach64 VGA */
    { "DEC5100", "SYSMEM",     "",       0,      1,   'C',    0},    /* DUMMY FOR SLOT 0 */
    { "DEC5100", "ACECOM,1",      "ace",    0,   1,   'C',    0},    /* COMM PORT 0 */
    { "DEC5100", "ACECOM,2",      "ace",    0,   1,   'C',    0},    /* COMM PORT 1 */
    { "DEC5100", "PAR",        "lp",     0,      0,   'C',    0},    /* PAR PORT */
    { "DEC5100", "MSD,FPYCTL", "fdi",    0,      1,   'C',    0},    /* FLOPPY */
    { "DEC6000", "SYSMEM",     "",       0,      1,   'C',    0},    /* DUMMY FOR SLOT 0 */
    { "DEC6000", "MSD,FPYCTL", "fdi",    0,      1,   'C',    0},    /* FLOPPY */
    { "DEC6000", "ACECOM,1",      "ace",    0,	 1,   'C',    0},    /* COMM PORT 0 */
    { "DEC6000", "ACECOM,2",      "ace",    0,	 1,   'C',    0},    /* COMM PORT 1 */
    { "ISA3000", "", "pcmcia",  0,	 0,   'A',    pcicconf},  /* ISA-PCMCIA adapter with Intel i82365 PCIC chip or its clones */
    { "DEC6400", "SYSMEM",     "",       0,	 1,   'C',    0},    /* DUMMY FOR SLOT 0 */
    { "DEC6400", "ACECOM,1",      "ace",    0,	 1,   'C',    0},    /* COMM PORT 0 */
    { "DEC6400", "ACECOM,2",      "ace",    0,	 1,   'C',    0},    /* COMM PORT 1 */
    { "DEC6400", "PAR",        "lp",     0,	 0,   'C',    0},    /* PAR PORT */
    { "DEC6400", "MSD,FPYCTL", "fdi",    0,	 1,   'C',    0},    /* FLOPPY */
    /*
     * Do not delete any table entries above this line or your system
     * will not configure properly.
     *
     * Add any new controllers or devices here.
     * Remember, the module name must be blank padded to 7 bytes.
     */

    /*
%%% Used by mkdata as placemarker for automatic installation
    */
    

    /*
     * Do not delete this null entry, which terminates the table or your
     * system will not configure properly.
     */
    {	"",		""	}	/* Null terminator in the table */

};







