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
 * @(#)$RCSfile: vga.h,v $ $Revision: 1.1.12.4 $ (DEC) $Date: 1995/08/22 22:40:58 $
 */

#ifndef _VGA_H_
#define _VGA_H_


/* screen functions */
extern caddr_t vga_init_screen_handle();
extern int VGA_init_screen();
extern int vga_init_screen();
extern int vga_clear_screen();
extern int vga_scroll_screen();
extern int vga_blitc();
extern int vga_map_unmap_screen();
extern int vga_ioctl();
extern void vga_close();

/* cursor functions */
extern caddr_t vga_init_cursor_handle();
extern int vga_load_cursor();
extern int vga_recolor_cursor();
extern int vga_set_cursor_position();
extern int vga_cursor_on_off();

/* color map functions */
extern caddr_t vga_init_color_map_handle();
extern int vga_init_color_map();
extern int vga_load_color_map_entry();
extern int vga_load_color_map_entry_6bit();
extern void vga_clean_color_map();
extern int vga_video_on();
extern int vga_video_off();


/* configuration function */
extern int vga_configure();

#endif /* _VGA_H_ */


