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
 * @(#)$RCSfile: decwcursor.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1995/04/07 22:27:58 $
 */
#ifndef USE_OLD_DECWCURSOR

#define decw_c_num_glyphs 	        54
#define decw_c_select_cursor             0
#define decw_c_leftselect_cursor         0
#define decw_c_help_select_cursor        2
#define decw_c_wait_cursor               4
#define decw_c_inactive_cursor           6
#define decw_c_resize_cursor             8
#define decw_c_vpane_cursor             10
#define decw_c_hpane_cursor             12
#define decw_c_text_insertion_cursor    14
#define decw_c_text_insertion_bl_cursor 16
#define decw_c_cross_hair_cursor        18
#define decw_c_draw_cursor	        20
#define decw_c_pencil_cursor	        22
#define decw_c_rpencil_cursor	        22
#define decw_c_center_cursor	        24
#define decw_c_rightselect_cursor       26
#define decw_c_wselect_cursor	        28
#define decw_c_eselect_cursor	        30
#define decw_c_x_cursor		        32
#define decw_c_circle_cursor	        34
#define decw_c_mouse_cursor	        36
#define decw_c_lpencil_cursor	        38
#define decw_c_leftgrab_cursor	        40
#define decw_c_grabhand_cursor	        42
#define decw_c_rightgrab_cursor	        44
#define decw_c_leftpointing_cursor      46
#define decw_c_uppointing_cursor        48
#define decw_c_rightpointing_cursor     50
#define decw_c_check_cursor             52

#else

/* 
 * note: 
 *   Use of the $ in a variable name is prohibited by ANSI-C.
 *   support for -DUSE_OLD_DECWCURSOR will be removed at some
 *   future time. It is currently provided for compatability 
 *   reasons only
 */
#define decw$c_num_glyphs 	        54
#define decw$c_select_cursor             0
#define decw$c_leftselect_cursor         0
#define decw$c_help_select_cursor        2
#define decw$c_wait_cursor               4
#define decw$c_inactive_cursor           6
#define decw$c_resize_cursor             8
#define decw$c_vpane_cursor             10
#define decw$c_hpane_cursor             12
#define decw$c_text_insertion_cursor    14
#define decw$c_text_insertion_bl_cursor 16
#define decw$c_cross_hair_cursor        18
#define decw$c_draw_cursor	        20
#define decw$c_pencil_cursor	        22
#define decw$c_rpencil_cursor	        22
#define decw$c_center_cursor	        24
#define decw$c_rightselect_cursor       26
#define decw$c_wselect_cursor	        28
#define decw$c_eselect_cursor	        30
#define decw$c_x_cursor		        32
#define decw$c_circle_cursor	        34
#define decw$c_mouse_cursor	        36
#define decw$c_lpencil_cursor	        38
#define decw$c_leftgrab_cursor	        40
#define decw$c_grabhand_cursor	        42
#define decw$c_rightgrab_cursor	        44
#define decw$c_leftpointing_cursor      46
#define decw$c_uppointing_cursor        48
#define decw$c_rightpointing_cursor     50
#define decw$c_check_cursor             52

#endif
