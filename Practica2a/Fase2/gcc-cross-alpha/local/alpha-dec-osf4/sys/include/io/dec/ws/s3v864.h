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
 * @(#)$RCSfile: s3v864.h,v $ $Revision: 1.1.4.3 $ (DEC) $Date: 1995/08/22 22:40:55 $
 */

#ifndef _S3v864_H_
#define _S3v864_H_

#ifdef KERNEL
/* screen functions */
extern caddr_t	s3v864_init_screen_handle();
extern int	s3v864_init_screen();
extern int	s3v864_clear_screen();
extern int	s3v864_scroll_screen();
extern int	s3v864_blitc();
extern int	s3v864_ioctl();
extern int	s3v864_map_unmap_screen();
extern void	s3v864_close();

/* cursor functions */
extern caddr_t	s3v864_init_cursor_handle();
extern int	s3v864_load_cursor();
extern int	s3v864_recolor_cursor();
extern int	s3v864_set_cursor_position();
extern int	s3v864_cursor_on_off();

/* colormap functions */
extern caddr_t	s3v864_init_color_map_handle();
extern int	s3v864_init_color_map();
extern int	s3v864_load_color_map_entry();
extern void	s3v864_clean_color_map();
extern int	s3v864_video_on();
extern int	s3v864_video_off();

/* adaptor functions */
extern void s3v864_save();
extern void s3v864_restore();
extern void s3v864_init();
extern void s3v864_print();
extern void s3v864_interrupt();
extern void s3v864_bot();

/* configuration function */
extern int s3v864_configure();
#endif /* KERNEL */

#endif /* _S3v864_H_ */
