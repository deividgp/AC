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
#pragma ident "@(#)$RCSfile: pvl_data.c,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1995/06/27 20:31:58 $"

/************************************************************************
 *									*
 *			Copyright (c) 1994 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

#define _PVL_DATA_C_

#include <io/dec/ws/pvl.h>

#ifndef BINARY

#include "pvl.h"

#if NPVL > 0

u_short
  pvlstd[] = { 0 };

struct controller
  *pvlinfo[NPVL];

struct driver
  pvldriver = {
    pvlprobe, 0, pvlattach, 0, 0, (caddr_t *) pvlstd, 0, 0, "pvl", pvlinfo };

pvl_info_t
  pvl_softc[NPVL];

int
  npvl_softc = NPVL;

pvl_type_t pvl_types[] = {
  {
    {				/* screen descriptor */
      0,
      MONITOR_VRT19,
      "PMAGC-DA",
      1280, 1024,
      0,
      NDEPTHS,
      NVISUALS,
      0, 0,
      0, 0,
      63, 127,
      10, 16,
      64, 64,
      1, 1,
    },
    {				/* depth descriptor of root window */
      0, 0,
      1280, 1024,
      24,				/* depth (out) */
      32,				/* stride of pixel (out) */
      32,				/* scan line pad */
      0,				/* */
      0,				/* only filled in when mapped */
      0,				/* plane mask */
      0,				/* only filled in when mapped */
    },
    {				/* visual descriptor */
      0,				/* which screen (in) */
      0,				/* which visual of screen (in) */
      TrueColor,			/* class of visual */
      32,				/* number of bits per pixel */
      0xff0000,
      0x00ff00,
      0x0000ff,			/* mask of subfields */
      8,				/* bits per RGB */
      256,			/* color map entries */
    },
    0,
    0,
    0,
    3,
    {				/* Cursor functions. */
      pvl_bt431_init_closure,
      pvl_bt431_load_cursor,
      pvl_recolor_cursor,
      pvl_bt431_set_cursor_position,
      pvl_bt431_cursor_on_off,
      (caddr_t) pvl_bt431_softc,
      NULL,
    },
    {				/* Color map functions. */
      pvl_bt463_init_closure,
      pvl_bt463_init_color_map,
      pvl_bt463_load_color_map_entry,
      NULL,
      pvl_video_on,
      pvl_video_off,
      (caddr_t) pvl_bt463_softc,
      NULL,
    },
    {				/* Screen functions */
      pvl_init_closure,
      pvl_init_screen,
      pvl_clear_screen,
      pvl_scroll_screen,
      pvl_blitc,
      pvl_map_screen,
      pvl_ioctl,			/* ioctl optional */
      pvl_close,			/* close optional */
      (caddr_t) pvl_softc,
      NULL,
      NULL,
      NULL,
    },
    pvl_dd_attach,
    pvl_bootmsg,
    pvl_map_screen,
    pvl_interrupt,
    pvl_setup,
    pvl_invalidate_gcp_tlb,
    (caddr_t) PVL_PVA_OFFSET,
    (caddr_t) PVL_SPARSE_PVA_OFFSET,
    (caddr_t) PVL_RENDER_OFFSET,
    (caddr_t) PVL_SPARSE_RENDER_OFFSET,
    (caddr_t) PVL_SRAM_OFFSET,
    (caddr_t) PVL_SPARSE_SRAM_OFFSET,
    0x010101, 0x0,			/* text fg, bg */
    PV_DTYPE, 			/* ws_display_type */
    (1<<17),			/* 128KB SRAM */
  },
  {					/**** PV - 3da ****/
    {				/* screen descriptor */
      0,				/* screen number (in) */
      MONITOR_VRT19,
      "PMAGC-EA",
      1280, 1024,			/* width, height */
      0,				/* depth */
      NDEPTHS,			/* number of depths present */
      NVISUALS,			/* number of visual types of screen */
      0, 0,			/* current pointer position */
      0, 0,			/* current text position */
      63, 127,			/* maximum row, col text position */
      10, 16,			/* console font width and height */
      64, 64,			/* maximal size cursor for screen */
      1, 1,			/* min, max of visual types */
    },
    {				/* depth descriptor of root window */
      0, 0,			/* which screen and depth (in) */
      1280, 1024,			/* frame buffer size in pixels */
      24,				/* depth (out) */
      32,				/* stride of pixel (out) */
      32,				/* scan line pad */
      0,				/* */
      0,				/* only filled in when mapped */
      0,				/* plane mask */
      0,				/* only filled in when mapped */
    },
    {				/* visual descriptor */
      0,				/* which screen (in) */
      0,				/* which visual of screen (in) */
      TrueColor,			/* class of visual */
      32,				/* number of bits per pixel */
      0xff0000,
      0x00ff00,
      0x0000ff,			/* mask of subfields */
      8,				/* bits per RGB */
      256,			/* color map entries */
    },
    0,
    0,
    0,
    3,
    {				/* Cursor functions. */
      pvl_bt431_init_closure,
      pvl_bt431_load_cursor,
      pvl_recolor_cursor,
      pvl_bt431_set_cursor_position,
      pvl_bt431_cursor_on_off,
      (caddr_t) pvl_bt431_softc,
      NULL,
    },
    {				/* Color map functions. */
      pvl_bt463_init_closure,
      pvl_bt463_init_color_map,
      pvl_bt463_load_color_map_entry,
      NULL,
      pvl_video_on,
      pvl_video_off,
      (caddr_t) pvl_bt463_softc,
      NULL,
    },
    {				/* Screen functions */
      pvl_init_closure,
      pvl_init_screen,
      pvl_clear_screen,
      pvl_scroll_screen,
      pvl_blitc,
      pvl_map_screen,
      pvl_ioctl,			/* ioctl optional */
      pvl_close,			/* close optional */
      (caddr_t) pvl_softc,
      NULL,
    },
    pvl_dd_attach,
    pvl_bootmsg,
    pvl_map_screen,
    pvl_interrupt,
    pvl_setup,
    pvl_invalidate_gcp_tlb,
    (caddr_t) PVL_PVA_OFFSET,
    (caddr_t) PVL_SPARSE_PVA_OFFSET,
    (caddr_t) PVL_RENDER_OFFSET,
    (caddr_t) PVL_SPARSE_RENDER_OFFSET,
    (caddr_t) PVL_SRAM_OFFSET,
    (caddr_t) PVL_SPARSE_SRAM_OFFSET,
    0x010101, 0x0,			/* text fg, bg */
    PV_DTYPE, 			/* ws_display_type */
    (1<<17),			/* 128KB Sram */
  },
};

int
  npvl_types = sizeof( pvl_types ) / sizeof( pvl_type_t ),
  _pvl_level,
  _pvl_debug = PVL_CONSOLE;


pvl_bt463_info_t
  pvl_bt463_softc[NPVL];

pvl_bt463_info_t
  pvl_bt463_type[] = {
    {	
      (pvl_bt463_t *) PVL_BT463_OFFSET,
      0,
      1,			/* screen initally on 	   */
      0,			/* colormap clean		   */
      0,			/* cursor map clean		   */
      227, 34,		/* magic offsets to video position */
      -1,			/* module unit number */
      NULL,			/* enable cfb interrupt on V.R.	   */
      NULL,			/* hack */
      { 0, 0, 0, 0, },
      { 0, 0, 0, 0, },
      { 0, 0, 0, 0, },
      256, 0,
    },
  };

pvl_bt431_info_t
  pvl_bt431_softc[NPVL];

pvl_bt431_info_t
  pvl_bt431_type[] = {
    {	
      (pvl_bt431_t *) PVL_BT431_0_OFFSET,
      (pvl_bt431_t *) PVL_BT431_1_OFFSET,
      0,
      1,			/* screen initally on 	   	   */
      1,			/* cursor initially on		   */
      0,		        /* cursor clean 		   */
      0x170, 0x24,		/* magic offsets to video position */
      0, 0,			/* hot spot of current cursor 	   */
      -1,			/* module unit number */
      0,			/* not initialized yet - hack!!!   */
      NULL,			/* enable cfb interrupt on V.R.	   */
    },
  };

#else /* NPVL */

int
  npvl_softc = 0,
  npvl_types = 0;

#endif /* NPVL */

#endif /* BINARY */

