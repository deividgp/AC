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
 *	@(#)$RCSfile: cons_sw_data.c,v $ $Revision: 1.2.87.2 $ (DEC) $Date: 1996/04/01 23:46:44 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/* 
 * derived from cons_sw_data.c	4.4      (ULTRIX)  9/6/90;
 */

/*
 * Modification History
 *
 * 14-jan-92 - prm
 *      Modified routine names for ruby to match DUART device, 
 *      rather than platform.
 *
 * 03-Oct-91 - ald
 *      Added alpha support for FLAMINGO.
 *
 * 25-Sep-91 - prm
 *      Added ruby support.
 *
 * 10-May-91    Paul Grist
 *	Added Entries for 3MAX+/BIGMAX (DS5000_300).
 *
 * 03-May-91 - afd
 *      Added alpha support for ADU.
 *
 * 05-May-91	Joel Gringorten
 *	Changes for new WS graphics driver.
 *
 * 20-Dec-90 - Kuo-Hsiung Hsieh
 *	Changed DS5100 entry.  Mipsmate driver is now merged into DS3100.
 *	OSF started.
 *	-----------------------------------------------------------------
 *
 * 06-Sep-90 - Randall Brown
 *	Removed entries for 'cfb' and 'pm', they are now folded into fb driver
 *
 * 03-Apr-90 - Tim Burke
 * 	Added console support for Mipsmate (DS5100).
 *
 * 27-Feb-90 - Philip Gapuzte
 *	Added entries for DS5000_100 (3MIN) console ssc.
 *
 * 04-Dec-89 - Sam Hsu
 *	Added entries for DS5000 graphics accelerators to vcons_init.
 *
 * 29-Oct-89 - Randall Brown
 *
 *	Added the c_init entry to each switch entry.  Also added the 
 *	vcons_init table.
 *
 * 20-May-89 - Randall Brown
 *
 *	created file.
 *
 */
#include <hal/cons_sw.h>

/*
 * If the ws driver is not defined, fix up references
 * as opposed to increasing target kernel size 
 * by building ws and fb unecessarily
 */
#include "ws.h"
#if NWS == 0
int install_generic_console() {return(0);}
struct controller * ws_get_default_console() {return(0);}

#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>

#include "scc.h"
#if NSCC > 0 
ws_keyboard	 lk201_keyboard;
ws_hardware_type vsxxx_mouse_closure;
ws_pointer	 vsxxx_mouse;
#endif /* SCC */

#include "gpc.h"
#if NGPC > 0 
ws_keyboard       pcxal_keyboard;
ws_hardware_type  pcxas_mouse_closure;
ws_pointer        pcxas_mouse;
void              pcxal_init_keyboard(){}
ws_keyboard_state pcxal_softc[NGPC];
int               pcxas_init_pointer(){}
void              pcxas_enable_pointer(){}
void              pcxal_disable_keyboard(){}
#endif /* GPC */

#endif /* NWS == 0 */

#include "fb.h"
#if NFB > 0
int fb_cons_init();
#endif

#include "pv.h"
#if NPV > 0
int pv_cons_init();
#endif

#include "pvl.h"
#if NPVL > 0
int pvl_cons_init();
#endif

/* Kubota Pacific Computer TurboChannel Denali */
/* No longer supported in Platinum so commented out */
/* #include "kws_td.h"
/* #if NKWS_TD > 0
/* int kws_td_cons_init();
/* #endif
 */

struct vcons_init_sw vcons_init[] = {

#if NFB > 0
    {   "PMAGB-BA",     fb_cons_init	},	/* SFB */
    {	"PMAG-RO ",	fb_cons_init	},	/* RO*/
    {	"PMAG-JA ",	fb_cons_init	},	/* RO*/
    {	"PMAGD   ",	fb_cons_init	},	/* SFBP-8,-32,-32Z */
    {	"PMAGD-AA",	fb_cons_init	},	/* SFBP-8 */
    {	"PMAGD-BA",	fb_cons_init	},	/* SFBP-32 */
#endif

#if NPV > 0
    {   "PMAGC   ",	pv_cons_init	},	/* Low PV */
    {   "PMAGC-AA",	pv_cons_init	},	/* Low PV */
    {   "PMAGC-BA",	pv_cons_init	},	/* Mid PV */
#endif

#if NPVL > 0
    {   "PMAGC-DA",	pvl_cons_init	},	/* Low PVlite */
    {   "PMAGC-EA",	pvl_cons_init	},	/* Mid PVlite */
#endif

#if NKWS_TD > 0
    {   "KWS_TD  ",     kws_td_cons_init },     /* KPC TCdenali */
#endif

    {	"", 		0 }			/* we must have a 0 entry
						   to end the loop */
    };

