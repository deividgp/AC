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
 * 	@(#)$RCSfile: wd.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1996/09/05 19:16:15 $
 */

#ifndef _WD_H_
#define _WD_H_


/* FIX: should be function prototypes*/

#ifdef KERNEL
/* screen functions */
extern caddr_t wd_init_screen_handle();
extern int wd_init_screen();
extern int wd_clear_screen();
extern int wd_scroll_screen();
extern int wd_blitc();
extern int wd_map_unmap_screen();
extern int wd_ioctl();
extern void wd_close();
extern int wd_set_get_power_level();

/* cursor functions */
extern caddr_t wd_init_cursor_handle();
extern int wd_load_cursor();
extern int wd_recolor_cursor();
extern int wd_set_cursor_position();
extern int wd_cursor_on_off();

/* color map functions */
extern caddr_t wd_init_color_map_handle();
extern int wd_init_color_map();
extern int wd_load_color_map_entry();
extern void wd_clean_color_map();
extern int wd_video_on();
extern int wd_video_off();

/* adaptor functions */
extern void wd_save();
extern void wd_restore();
extern void wd_init();
extern void wd_print();
extern void wd_interrupt();
extern void wd_bot();

/* configuration function */
extern int wd_configure();
#endif /* KERNEL */

#endif /* _WD_H_ */


