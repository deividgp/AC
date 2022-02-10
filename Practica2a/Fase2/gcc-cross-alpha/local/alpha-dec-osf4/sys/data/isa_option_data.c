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
#pragma ident "@(#)$RCSfile: isa_option_data.c,v $ $Revision: 1.1.56.2 $ (DEC) $Date: 1996/09/05 19:13:20 $"

/*
 * isa_option_data.c
 *
 * Contains data table for ISA bus options.  This table maps
 * option board product id name with  device  or  controller
 * name  in  the  config file.  The isa_option structure  is
 * defined in io/dec/isa/isa.h.  Items include 'motherboard'
 * ISA devices.
 */

#include	<io/common/devdriver.h>
#include	<io/dec/eisa/isa.h>

#include "pcmcia.h"
#if NPCMCIA > 0
extern int pcicconf();		/* ISA-PCMCIA config. routine */
#else
#define pcicconf 0
#endif

/* Declare this here so it will be merged with the eisa copy into one */
struct eisa_sw eisa_sw;

/*************************** Warning!!! ************************************/
/*                                                                         */
/*    This table is not used to support device drivers in the 4.0          */
/*    release. It exists as a Notbinary entry in the alpha/files file      */
/*    for the 4.0 release in order to support older device driver kits.    */
/*    It will be made Notbinary and remain in the kernel build in the      */
/*    5.0 release at the descression of the individual bus developers.     */
/*                                                                         */
/***************************************************************************/

struct	eisa_option	isa_option [] = {
    /* board	  function    driver  intr_b4 itr_aft	     adpt  */
    /* id	    name       name    probe   attach type  config */
    /* ------	 ------------ ------  ------- ------- ----  ------ */
    { "",        "KBD,MOUSE", "gpc",     0,      1,   'C',    0},    /* Keyboard/Mouse   */
    { "",        "COM",       "ace",     0,      1,   'C',    0},    /* Serial/FAX MODEM */
    { "",        "LPT",       "lp",      0,      0,   'C',    0},    /* parallel port    */
    { "",        "FLOPPY",    "fdi",     0,      1,   'C',    0},    /* Floppy disk      */
    { "",        "DE200-LE",  "le",      0,      1,   'C',    0},    /* DEC_LeMAC        */
    { "",        "DW110",     "tra",     0,      1,   'C',    0},    /* TokenRing card   */
    { "",        "TKRNG",     "tra",     0,      1,   'C',    0},    /* TokenRing card	 */ 
    { "",        "ISA--VGA",  "vga",     0,      0,   'C',    0},    /* Generic ISA VGA  */
    { "",        "MACH64",    "ati",     0,      0,   'C',    0},    /* ISA ATI Mach64 VGA       */
    { "",        "ISA--SCC",  "iscc",    0,      0,   'C',    0},    /* ISA SCC          */

    /*
     * Do not delete any table entries above this line or your system
     * will not configure properly.
     *
     * Add any new controllers or devices here.
     */
    { "",	 "PCIC-PCMCIA", "pcmcia",  0,	 0,   'A',    pcicconf},  /* ISA-PCMCIA adapter with Intel i82365 PCIC chip or its clones */
    { "",        "WD90",  "wd",     0,      0,   'C',    0},    /* WD90C24 graphics controller for ALPHAbook */
    { "",        "H8",  "hmc",     0,      0,   'C',    0},    /* H8 Microcontroller */
    /*
%%% Used by mkdata as placemarker for automatic installation
    */
    

    /*
     * Do not delete this null entry, which terminates the table or your
     * system will not configure properly.
     */
    {	"",		"", "", 0, 0, '', 0	}	/* Null terminator in the table */

};
