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
 * @(#)$RCSfile: ati.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 1995/08/22 22:40:34 $
 */


#ifndef _ATI_H_
#define _ATI_H_

#ifdef KERNEL
/* screen functions */
extern caddr_t	ati_init_screen_handle();
extern int	ati_init_screen();
extern int	ati_clear_screen();
extern int	ati_scroll_screen();
extern int	ati_blitc();
extern int	ati_ioctl();
extern int	ati_map_unmap_screen();
extern void	ati_close();

/* cursor functions */
extern caddr_t	ati_init_cursor_handle();
extern int	ati_load_cursor();
extern int	ati_recolor_cursor();
extern int	ati_set_cursor_position();
extern int	ati_cursor_on_off();

/* colormap functions */
extern caddr_t	ati_init_color_map_handle();
extern int	ati_init_color_map();
extern int	ati_load_color_map_entry();
extern void	ati_clean_color_map();
extern int	ati_video_on();
extern int	ati_video_off();

/* adaptor functions */
extern void ati_save();
extern void ati_restore();
extern void ati_print();
extern void ati_interrupt();


/* configuration function */
extern int ati_configure();
#endif /* KERNEL */

#endif /* _ATI_H_ */
