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
#pragma ident "@(#)$RCSfile: pvp_data.c,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 1996/10/11 20:18:56 $"

#define _PVP_DATA_C_

#include <io/dec/ws/pvp.h>

#include "pvp.h"

#ifndef BINARY

#if NPVP > 0

caddr_t
  pvpstd[] = { 0 };

struct controller
  *pvpinfo[NPVP];

struct driver
  pvpdriver = {
    pvpprobe, 0, pvpattach, 0, 0, pvpstd, 0, 0, "pvp", pvpinfo };

pvp_info_t
  pvp_softc[NPVP];

int
  npvp_softc = NPVP;

int
    pvp_doorbell[2] = { PVP_DOORBELL_0_PIXELMAP_ID, PVP_DOORBELL_1_PIXELMAP_ID };

pvp_type_t pvp_types[] = {
    {
	{				/* screen descriptor */
	    0,
	    MONITOR_VRT19,
	    "DPI PV PCI",		/* PCI PV card */
	    1280, 1024,
	    0,
	    NDEPTHS,
	    NVISUALS,
	    0, 0,
	    0, 0,
	    63, 127,
	    10, 16,			/* XXX console font w,h */
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
	0,				/* cursor type */
	0,				/* cmap type */
	0,				/* screen type */
	{				/* Cursor functions. */
	    pvp_561_init_closure,
	    pvp_561_load_cursor,
	    pvp_561_recolor_cursor,
	    pvp_561_set_cursor_position,
	    pvp_561_cursor_on_off,
	    (caddr_t) pvp_561_softc,
	    NULL,
	},
	{				/* Color map functions. */
	    pvp_561_init_closure,
	    pvp_561_init_color_map,
	    pvp_561_load_color_map_entry,
	    NULL,
	    pvp_561_video_on,
	    pvp_561_video_off,
	    (caddr_t) pvp_561_softc,
	    NULL,
	},
	{				/* Screen functions */
	    pvp_init_closure,
	    pvp_init_screen,
	    pvp_clear_screen,		/* XXX */
	    pvp_scroll_screen,		/* XXX */
	    pvp_blitc,			/* XXX */
	    pvp_map_screen,
	    pvp_ioctl,			/* ioctl optional */
	    pvp_close,			/* close optional */
	    (caddr_t) pvp_softc,
	    NULL,
	    NULL,
	    NULL,
	},
	pvp_dd_attach,
	pvp_bootmsg,
	pvp_map_screen,
	pvp_interrupt,
	pvp_setup,
	pvp_invalidate_page,
	0x010101, 0x0,			/* text fg, bg */
	PV_DTYPE,			/* ws_display_type */
    },
};

int
  npvp_types = sizeof( pvp_types ) / sizeof( pvp_type_t ),
  _pvp_level,
  _pvp_debug = PVP_CONSOLE;


pvp_561_info_t
  pvp_561_softc[NPVP];

pvp_561_type_t
  pvp_561_types[] = {
      {
	  0,				/* addr */
	  0x0, 0x0,			/* x/y offset */
	  256, 0,			/* min/max dirty */
	  0xff,
      },
  };
int
    npvp_561_softc = NPVP,
    npvp_561_types = sizeof( pvp_561_types ) / sizeof( pvp_561_type_t );

pvp_dma_handle	dma_page;
pvp_dma_handle	dma_image;

pvp_monitor_data_t pvp_monitor_data[] = 
{
#if 0
    {					/* mode 2:  1280x1024 60.10Hz	*/
	PVP_MSPEC(1280,1024,60),	/* Timing from DEC VRC21 Spec. Mode 8 */
	PVP_VIDEO_HOE,			/* Flags */
	60,				/* Refresh */
	66, 6, 2,			/* 110.15Mhz */
	0, 0, 0, 0,			/* vga PLL */
	1024,				/* Active lines */
	57,				/* VBlank lines */
	6,				/* VSync front porch lines */
	7,				/* VSync width lines */
	1, 3,				/* vga V border */
	1280,				/* Active line pixels */
	416,				/* HBlank pixels */
	19,				/* HSync front porch pixels */
	163,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
#endif
    {					/* mode 0:  1280x1024 72.56Hz	*/
	PVP_MSPEC(1280,1024,72),	/* Timing from DEC VRC21 Spec. Mode 10 */
	PVP_VIDEO_SOG,			/* Flags */
	72,				/* Refresh */
	85, 13, 3,			/* 130.808Mhz */
	0, 0, 0, 0,			/* vga PLL */
	1024,				/* Active lines */
	39,				/* VBlank lines */
	3,				/* VSync front porch lines */
	3,				/* VSync width lines */
	1, 3,				/* vga V border */
	1280,				/* Active line pixels */
	416,				/* HBlank pixels */
	32,				/* HSync front porch pixels */
	160,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 1:  1280x1024 66.47Hz	*/
	PVP_MSPEC(1280,1024,66),	/* Timing from DEC VRC21 Spec. Mode 9 */
	PVP_VIDEO_SOG,			/* Flags */
	66,				/* Refresh */
	72, 6, 2,			/* 119.84Mhz */
	0, 0, 0, 0,			/* vga PLL */
	1024,				/* Active lines */
	39,				/* VBlank lines */
	3,				/* VSync front porch lines */
	3,				/* VSync width lines */
	1, 3,				/* vga V border */
	1280,				/* Active line pixels */
	416,				/* HBlank pixels */
	32,				/* HSync front porch pixels */
	160,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 2:  1280x1024 60.10Hz	*/
	PVP_MSPEC(1280,1024,60),	/* Timing from DEC VRC21 Spec. Mode 8 */
	PVP_VIDEO_SOG,			/* Flags */
	60,				/* Refresh */
	66, 6, 2,			/* 110.15Mhz */
	0, 0, 0, 0,			/* vga PLL */
	1024,				/* Active lines */
	57,				/* VBlank lines */
	6,				/* VSync front porch lines */
	7,				/* VSync width lines */
	1, 3,				/* vga V border */
	1280,				/* Active line pixels */
	416,				/* HBlank pixels */
	19,				/* HSync front porch pixels */
	163,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 3:  1280x1024 75.025Hz	*/
	PVP_MSPEC(1280,1024,75),	/* Timing from VESA */
	PVP_VIDEO_SOG,			/* Flags */
	75,				/* Refresh */
	81, 12, 3,			/* 135.00Mhz */
	0, 0, 0, 0,			/* vga PLL */
	1024,				/* Active lines */
	42,				/* VBlank lines */
	1,				/* VSync front porch lines */
	3,				/* VSync width lines */
	1, 3,				/* vga V border */
	1280,				/* Active line pixels */
	408,				/* HBlank pixels */
	16,				/* HSync front porch pixels */
	144,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 4:  1152x900  76.15Hz	*/
	PVP_MSPEC(1152,900,76),		/* Timing from DEC VRC21 Spec. Mode 5 */
	PVP_VIDEO_SOG,			/* Flags */
	76,				/* Refresh */
	108, 10, 2,			/* 108.00Mhz */
	0, 0, 0, 0,			/* vga PLL */
	900,				/* Active lines */
	43,				/* VBlank lines */
	2,				/* VSync front porch lines */
	8,				/* VSync width lines */
	1, 3,				/* vga V border */
	1152,				/* Active line pixels */
	352,				/* HBlank pixels */
	32,				/* HSync front porch pixels */
	128,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 5:  1152x900  66.00Hz	*/
	PVP_MSPEC(1152,900,66),		/* Timing from DEC VRC21 Spec. Mode 11 */
	PVP_VIDEO_SOG,			/* Flags */
	66,				/* Refresh */
	104, 11, 2,			/* 94.50Mhz */
	0, 0, 0, 0,			/* vga PLL */
	900,				/* Active lines */
	37,				/* VBlank lines */
	2,				/* VSync front porch lines */
	4,				/* VSync width lines */
	1, 3,				/* vga V border */
	1152,				/* Active line pixels */
	376,				/* HBlank pixels */
	40,				/* HSync front porch pixels */
	128,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 6:  1024x864  60.00Hz	*/
	PVP_MSPEC(1024,864,60),		/* Timing from DEC VRC21 Spec. Mode 7 */
	PVP_VIDEO_SOG,			/* Flags */
	60,				/* Refresh */
	70, 10, 2,			/* 70.00Mhz */
	0xef, 88, 18, 0,		/* vga PLL */
	864,				/* Active lines */
	37,				/* VBlank lines */
	0,				/* VSync front porch lines */
	3,				/* VSync width lines */
	0, 3,				/* vga V border */
	1024,				/* Active line pixels */
	271,				/* HBlank pixels */
	23,				/* HSync front porch pixels */
	130,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 7:  1024x768  75.029Hz	*/
	PVP_MSPEC(1024,768,75),		/* Timing from VESA */
	PVP_VIDEO_SOG,			/* Flags */
	75,				/* Refresh */
	126, 16, 2,			/* 78.750Mhz */
	0x2f, 99, 18, 0,		/* vga PLL */
	768,				/* Active lines */
	32,				/* VBlank lines */
	1,				/* VSync front porch lines */
	3,				/* VSync width lines */
	1, 3,				/* vga V border */
	1024,				/* Active line pixels */
	288,				/* HBlank pixels */
	16,				/* HSync front porch pixels */
	96,				/* HSync width pixels */
	8, 16,				/* vga H border */
    },
    {					/* mode 8:  1024x768  72Hz	*/
	PVP_MSPEC(1024,768,72),		/* Timing from DEC VRC21 Spec. Mode 6 */
	PVP_VIDEO_HOE,			/* Flags */
	72,				/* Refresh */
	119, 16, 2,			/* 74.37Mhz */
	0xef, 109, 21, 0,		/* vga PLL */
	768,				/* Active lines */
	29,				/* VBlank lines */
	1,				/* VSync front porch lines */
	6,				/* VSync width lines */
	1, 3,				/* vga V border */
	1024,				/* Active line pixels */
	272,				/* HBlank pixels */
	16,				/* HSync front porch pixels */
	128,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 9:  1024x768  70.069Hz	*/
	PVP_MSPEC(1024,768,70),		/* Timing from VESA */
	PVP_VIDEO_HOE,			/* Flags */
	70,				/* Refresh */
	75, 10, 2,			/* 75.00Mhz */
	0xef, 110, 21, 0,		/* vga PLL */
	768,				/* Active lines */
	38,				/* VBlank lines */
	3,				/* VSync front porch lines */
	6,				/* VSync width lines */
	1, 3,				/* vga V border */
	1024,				/* Active line pixels */
	304,				/* HBlank pixels */
	24,				/* HSync front porch pixels */
	136,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 10: 1024x768  60.000Hz	*/
	PVP_MSPEC(1024,768,60),		/* Timing from VESA */
	PVP_VIDEO_HOE,			/* Flags */
	60,				/* Refresh */
	65, 10, 2,			/* 65.00Mhz */
	0xef, 118, 26, 0,		/* vga PLL */
	768,				/* Active lines */
	38,				/* VBlank lines */
	3,				/* VSync front porch lines */
	6,				/* VSync width lines */
	1, 3,				/* vga V border */
	1024,				/* Active line pixels */
	320,				/* HBlank pixels */
	24,				/* HSync front porch pixels */
	136,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 11:  800x600  75.000Hz	*/
	PVP_MSPEC(800,600,75),		/* Timing from VESA */
	PVP_VIDEO_SOG,			/* Flags */
	75,				/* Refresh */
	99, 10, 1,			/* 49.500Mhz */
	0x2f, 83, 24, 0,		/* vga PLL */
	600,				/* Active lines */
	25,				/* VBlank lines */
	1,				/* VSync front porch lines */
	3,				/* VSync width lines */
	1, 3,				/* vga V border */
	800,				/* Active line pixels */
	256,				/* HBlank pixels */
	16,				/* HSync front porch pixels */
	80,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 12:  800x600  72.187Hz VESA */
	PVP_MSPEC(800,600,72),		/* DEC VRC21 Spec. Mode 4 */
	PVP_VIDEO_SOG,			/* Flags */
	72,				/* Refresh */
	70, 7, 1,			/* 50.000Mhz */
	0x2f, 98, 28, 0,		/* vga PLL */
	600,				/* Active lines */
	66,				/* VBlank lines */
	37,				/* VSync front porch lines */
	6,				/* VSync width lines */
	1, 3,				/* vga V border */
	800,				/* Active line pixels */
	240,				/* HBlank pixels */
	56,				/* HSync front porch pixels */
	120,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 13:  800x600  60.3165Hz	VESA */
	PVP_MSPEC(800,600,60),		/* DEC VRC21 Spec. Mode 3 */
	PVP_VIDEO_SOG,			/* Flags */
	60,				/* Refresh */
	72, 9, 1,			/* 40.000Mhz */
	0x2f, 81, 29, 0,		/* vga PLL */
	600,				/* Active lines */
	28,				/* VBlank lines */
	1,				/* VSync front porch lines */
	4,				/* VSync width lines */
	1, 3,				/* vga V border */
	800,				/* Active line pixels */
	256,				/* HBlank pixels */
	40,				/* HSync front porch pixels */
	128,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 14:  640x480  75.000Hz	*/
	PVP_MSPEC(640,480,75),		/* Timing from VESA */
	PVP_VIDEO_HOE,			/* Flags */
	75,				/* Refresh */
	126, 10, 0,			/* 31.500Mhz */
	0xef, 66, 15, 1,		/* vga PLL */
	480,				/* Active lines */
	20,				/* VBlank lines */
	1,				/* VSync front porch lines */
	3,				/* VSync width lines */
	1, 3,				/* vga V border */
	640,				/* Active line pixels */
	200,				/* HBlank pixels */
	16,				/* HSync front porch pixels */
	64,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 15:  640x480  72.809Hz VESA */
	PVP_MSPEC(640,480,72),		/* DEC VRC21 Spec. Mode 2 */
	PVP_VIDEO_HOE,			/* Flags */
	72,				/* Refresh */
	126, 10, 0,			/* 31.500Mhz */
	0xef, 66, 15, 1,		/* vga PLL */
	480,				/* Active lines */
	40,				/* VBlank lines */
	9,				/* VSync front porch lines */
	3,				/* VSync width lines */
	5, 6,				/* vga V border */
	640,				/* Active line pixels */
	192,				/* HBlank pixels */
	24,				/* HSync front porch pixels */
	40,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 16:  640x480  59.94Hz	*/
	PVP_MSPEC(640,480,60),		/* Timing from DEC VRC21 Spec. Mode 1 */
	PVP_VIDEO_HOE,			/* Flags */
	60,				/* Refresh */
	121, 12, 0,			/* 25.208Mhz */
	0xef, 102, 29, 1,		/* vga PLL, 25.180 Mhz */
	480,				/* Active lines */
	45,				/* VBlank lines */
	10,				/* VSync front porch lines */
	2,				/* VSync width lines */
	7, 9,				/* vga V border */
	640,				/* Active line pixels */
	160,				/* HBlank pixels */
	16,				/* HSync front porch pixels */
	96,				/* HSync width pixels */
	0, 16,				/* vga H border */
    },
    {					/* mode 17: 1280x512 139.32Hz, stereo	*/
	PVP_MSPEC(1280,512,139),	/* Timing from DEC VRC21 Spec. Mode 12 */
	PVP_VIDEO_SOG|PVP_VIDEO_STEREO,	/* Flags */
	139,				/* Refresh */
	85, 13, 3,			/* 130.808Mhz */
	0, 0, 0, 0,			/* vga PLL */
	512,				/* Active lines */
	39,				/* VBlank lines */
	3,				/* VSync front porch lines */
	3,				/* VSync width lines */
	1, 3,				/* vga V border */
	1280,				/* Active line pixels */
	424,				/* HBlank pixels */
	32,				/* HSync front porch pixels */
	160,				/* HSync width pixels */
	0, 16,				/* vga H border */
    }
};
int npvp_monitor_data =
    sizeof( pvp_monitor_data ) / sizeof( pvp_monitor_data_t );

ws_screens pv_console_screen;
ws_screens pv_graphic_screen;

vm_offset_t pvp_misc;
vm_offset_t pvp_image;
vm_offset_t pvp_pmap;

unsigned int pvp_image_size;
unsigned int pvp_cmd_size;

#else /*NPVP */

int
  npvp_softc = 0,
  npvp_types = 0;

#endif /*NPVP */

#endif /*BINARY */
