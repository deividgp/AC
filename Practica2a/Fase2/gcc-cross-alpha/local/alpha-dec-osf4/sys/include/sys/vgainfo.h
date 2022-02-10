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
 * @(#)$RCSfile: vgainfo.h,v $ $Revision: 1.1.13.3 $ (DEC) $Date: 1995/08/22 22:41:16 $
 */
#ifndef _VGAINFO_H_
#define _VGAINFO_H_ 1


#define NDEPTHS 1			/* all current hardware just has one*/
#define NVISUALS 1

/*
 * the reason a different color cell representation is used is
 * to reduce kernel memory usage.  This form is sufficient for
 * a 256 entry color map, and saves 8 bytes/cell, or 2k bytes/screen.
 */
struct vga_color_cell 
{
        unsigned char dirty_cell;
        unsigned char red;	      /* only need 8 bits */
        unsigned char green;
        unsigned char blue;
};


struct vga_info {
	ws_screen_descriptor screen;
	ws_depth_descriptor depth[NDEPTHS];
	ws_visual_descriptor visual[NVISUALS];
	ws_screen_functions sf;
	ws_color_map_functions cmf;
	ws_cursor_functions cf;
	unsigned int state;
	short ctlr_type;
	short bus_type;
	pid_t mapped_pid;
	unsigned short attribute;		/* char mode attribute */
	unsigned short unit;
	unsigned short board_id;
	short min_dirty;
	short max_dirty;
	short x_hot;
	short y_hot;
	ws_color_cell cursor_fg;
	ws_color_cell cursor_bg;
	unsigned long mem_phys;
	io_handle_t mem_handle;
	unsigned long cursor_offset;
	unsigned int mem_size;
	u_int bits[256];  /* 1KB */
	struct vga_color_cell cells[256];  /* 1KB */
};

/* "state" field defines */
#define VGA_STATE_MAPPED	0x0001		/* has unit been mapped */
#define VGA_STATE_DIRTY_CURSOR	0x0002
#define VGA_STATE_DIRTY_CMAP	0x0004
#define VGA_STATE_CURSOR_ON	0x0008
#define VGA_STATE_SCREEN_ON	0x0010
#define VGA_STATE_6BIT_DAC	0x0020

/* "state" field test macros */
#define IS_VGA_MAPPED(vp)		((vp)->state & VGA_STATE_MAPPED)
#define IS_VGA_DIRTY_CURSOR(vp)		((vp)->state & VGA_STATE_DIRTY_CURSOR)
#define IS_VGA_DIRTY_CMAP(vp)		((vp)->state & VGA_STATE_DIRTY_CMAP)
#define IS_VGA_CURSOR_ON(vp)		((vp)->state & VGA_STATE_CURSOR_ON)
#define IS_VGA_SCREEN_ON(vp)		((vp)->state & VGA_STATE_SCREEN_ON)
#define IS_VGA_6BIT_DAC(vp)		((vp)->state & VGA_STATE_6BIT_DAC)

/* "state" field set and clear macros */
#define SET_VGA_MAPPED(vp)		(vp)->state |= VGA_STATE_MAPPED
#define CLR_VGA_MAPPED(vp)		(vp)->state &= ~VGA_STATE_MAPPED
#define SET_VGA_DIRTY_CURSOR(vp)	(vp)->state |= VGA_STATE_DIRTY_CURSOR
#define CLR_VGA_DIRTY_CURSOR(vp)	(vp)->state &= ~VGA_STATE_DIRTY_CURSOR
#define SET_VGA_DIRTY_CMAP(vp)		(vp)->state |= VGA_STATE_DIRTY_CMAP
#define CLR_VGA_DIRTY_CMAP(vp)		(vp)->state &= ~VGA_STATE_DIRTY_CMAP
#define SET_VGA_CURSOR_ON(vp)		(vp)->state |= VGA_STATE_CURSOR_ON
#define CLR_VGA_CURSOR_ON(vp)		(vp)->state &= ~VGA_STATE_CURSOR_ON
#define SET_VGA_SCREEN_ON(vp)		(vp)->state |= VGA_STATE_SCREEN_ON
#define CLR_VGA_SCREEN_ON(vp)		(vp)->state &= ~VGA_STATE_SCREEN_ON
#define SET_VGA_6BIT_DAC(vp)		(vp)->state |= VGA_STATE_6BIT_DAC
#define CLR_VGA_6BIT_DAC(vp)		(vp)->state &= ~VGA_STATE_6BIT_DAC

/* "bus_type" field defines */
#define VGA_BUS_NONE	0x0000
#define VGA_BUS_ISA	0x0001
#define VGA_BUS_EISA	0x0002
#define VGA_BUS_PCI	0x0004

/* "state" field test macros */
#define IS_VGA_ISA(vp)		((vp)->bus_type & VGA_BUS_ISA)
#define IS_VGA_EISA(vp)		((vp)->bus_type & VGA_BUS_EISA)
#define IS_VGA_PCI(vp)		((vp)->bus_type & VGA_BUS_PCI)


struct vga_type {
	ws_screen_descriptor screen;
	ws_depth_descriptor depth[NDEPTHS];
	ws_visual_descriptor visual[NVISUALS];
	int screen_type;
	ws_cursor_functions cf;
	int cursor_type;
	ws_color_map_functions cmf;
	int color_map_type;
	ws_screen_functions sf;
	int bus_type;
};


#endif /* !_VGAINFO_H_ */
