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
 * @(#)$RCSfile: ati64.h,v $ $Revision: 1.1.6.4 $ (DEC) $Date: 1995/10/26 18:33:31 $
 */

#ifndef _ATI64_H_
#define _ATI64_H_

#ifdef KERNEL
/* screen functions */
extern caddr_t	ati64_init_screen_handle();
extern int	ati64_init_screen();
extern int	ati64_clear_screen();
extern int	ati64_scroll_screen();
extern int	ati64_blitc();
extern int	ati64_ioctl();
extern int	ati64_map_unmap_screen();
extern void	ati64_close();
extern int	ati64_set_get_power_level();

/* cursor functions */
extern caddr_t	ati64_init_cursor_handle();
extern int	ati64_load_cursor();
extern int	ati64_recolor_cursor();
extern int	ati64_set_cursor_position();
extern int	ati64_cursor_on_off();

/* colormap functions */
extern caddr_t	ati64_init_color_map_handle();
extern int	ati64_init_color_map();
extern int	ati64_load_color_map_entry();
extern void	ati64_clean_color_map();
extern int	ati64_video_on();
extern int	ati64_video_off();

/* adaptor functions */
extern void ati64_save();
extern void ati64_restore();
extern void ati64_init();
extern void ati64_print();
extern void ati64_interrupt();
extern void ati64_bot();

/* configuration function */
extern int ati64_configure();
#endif /* KERNEL */

#endif /* _ATI64_H_ */
