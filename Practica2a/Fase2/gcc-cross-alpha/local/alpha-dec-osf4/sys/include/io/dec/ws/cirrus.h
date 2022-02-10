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
 * @(#)$RCSfile: cirrus.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1995/08/22 22:40:42 $
 */

#ifndef _CIRRUS_H_
#define _CIRRUS_H_

#ifdef KERNEL
/* screen functions */
extern caddr_t	cirrus_init_screen_handle();
extern int	cirrus_init_screen();
extern int	cirrus_clear_screen();
extern int	cirrus_scroll_screen();
extern int	cirrus_blitc();
extern int	cirrus_ioctl();
extern int	cirrus_map_unmap_screen();
extern void	cirrus_close();

/* cursor functions */
extern caddr_t	cirrus_init_cursor_handle();
extern int	cirrus_load_cursor();
extern int	cirrus_recolor_cursor();
extern int	cirrus_set_cursor_position();
extern int	cirrus_cursor_on_off();

/* colormap functions */
extern caddr_t	cirrus_init_color_map_handle();
extern int	cirrus_init_color_map();
extern int	cirrus_load_color_map_entry();
extern void	cirrus_clean_color_map();
extern int	cirrus_video_on();
extern int	cirrus_video_off();

/* adaptor functions */
extern void cirrus_save();
extern void cirrus_restore();
extern void cirrus_init();
extern void cirrus_print();
extern void cirrus_interrupt();
extern void cirrus_bot();

/* configuration function */
extern int cirrus_configure();
#endif /* KERNEL */

#endif /* _CIRRUS_H_ */
