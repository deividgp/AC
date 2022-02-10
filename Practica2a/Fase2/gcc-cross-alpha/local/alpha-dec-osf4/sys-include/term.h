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
 * @(#)$RCSfile: term.h,v $ $Revision: 1.1.2.11 $ (DEC) $Date: 1995/12/19 17:22:40 $
 */
/*		copyright	"%c%" 	*/

/*
 *	Copyright (c) 1982, 1986, 1988
 *	The Regents of the University of California
 *	All Rights Reserved.
 *	Portions of this document are derived from
 *	software developed by the University of
 *	California, Berkeley, and its contributors.
 */


#ifdef IDENT
#ident	"@(#)icurses:screen/term/maketerm.ed	05.21"
#endif /* IDENT */

#ifndef _TERM_H_
#define _TERM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <stddef.h>	/* get definition of wchar_t */

#ifndef _CURSES_TERM_TYPES
#define _CURSES_TERM_TYPES

/* The following typedefs are duplicated in term.h and curses.h so that
 * include order won't matter and each may stand alone.
 */

/*
 * The following ifndef must ALWAYS be present since C++ may use
 * _BOOL_EXISTS to prevent the header from trying to redefine a
 * C++ reserved word.
 */
#ifndef _BOOL_EXISTS
#define _BOOL_EXISTS
typedef	char bool;
#endif  /* _BOOL_EXISTS */

typedef unsigned long	attr_t;

#define _ZLC_MOD_MAX	5

typedef struct {
	attr_t	_a;
	wchar_t	_c;
	wchar_t _z[_ZLC_MOD_MAX];
} cchar_t;

#endif /* _CURSES_TERM_TYPES */

#include <termios.h>

#ifdef _OSF_SOURCE

#ifdef NOMACROS
#define _NOMACROS
#endif /* NOMACROS */

#ifdef SINGLE
#define _SINGLE
#endif /* SINGLE */

#endif /* _OSF_SOURCE */

#define auto_left_margin 		CURB _auto_left_margin
#define auto_right_margin 		CURB _auto_right_margin
#define no_esc_ctlc 			CURB _no_esc_ctlc
#define ceol_standout_glitch 		CURB _ceol_standout_glitch
#define eat_newline_glitch 		CURB _eat_newline_glitch
#define erase_overstrike 		CURB _erase_overstrike
#define generic_type 			CURB _generic_type
#define hard_copy 			CURB _hard_copy
#define has_meta_key 			CURB _has_meta_key
#define has_status_line 		CURB _has_status_line
#define insert_null_glitch 		CURB _ins_null_glitch
#define memory_above 			CURB _mem_above
#define memory_below 			CURB _mem_below
#define move_insert_mode 		CURB _move_insert_mode
#define move_standout_mode 		CURB _move_standout_mode
#define over_strike 			CURB _over_strike
#define status_line_esc_ok 		CURB _status_line_esc_ok
#define dest_tabs_magic_smso 		CURB _dest_tabs_magic_smso
#define tilde_glitch 			CURB _tilde_glitch
#define transparent_underline 		CURB _transparent_underline
#define xon_xoff 			CURB _xon_xoff
#define back_color_erase 		CURB _back_color_erase
#define can_change 			CURB _can_change
#define col_addr_glitch 		CURB _col_addr_glitch
#define cpi_changes_res 		CURB _cpi_changes_res
#define cr_cancels_micro_mode 		CURB _cr_cancels_micro_mode
#define hard_cursor 			CURB _hard_cursor
#define has_print_wheel 		CURB _has_print_wheel
#define hue_lightness_saturation 	CURB _hue_lightness_saturation
#define lpi_changes_res 		CURB _lpi_changes_res
#define needs_xon_xoff 			CURB _needs_xon_xoff
#define non_dest_scroll_region 		CURB _non_dest_scroll_region
#define non_rev_rmcup 			CURB _non_rev_rmcup
#define no_pad_char 			CURB _no_pad_char
#define prtr_silent 			CURB _prtr_silent
#define row_addr_glitch 		CURB _row_addr_glitch
#define semi_auto_right_margin 		CURB _semi_auto_right_margin

#define columns 			CURN _columns
#define init_tabs 			CURN _init_tabs
#define lines 				CURN _lines
#define lines_of_memory 		CURN _lines_of_memory
#define magic_cookie_glitch 		CURN _magic_cookie_glitch
#define padding_baud_rate 		CURN _padding_baud_rate
#define virtual_terminal 		CURN _virtual_terminal
#define width_status_line 		CURN _width_status_line
#define bit_image_entwining 		CURN _bit_image_entwining
#define bit_image_type 			CURN _bit_image_type
#define buffer_capacity 		CURN _buffer_capacity
#define buttons 			CURN _buttons
#define dot_vert_spacing 		CURN _dot_vert_spacing
#define dot_horz_spacing 		CURN _dot_horz_spacing
#define label_height 			CURN _labl_height
#define label_width 			CURN _labl_width
#define max_attributes 			CURN _max_attributes
#define max_colors 			CURN _max_colors
#define max_micro_address 		CURN _max_micro_address
#define max_micro_jump 			CURN _max_micro_jump
#define max_pairs 			CURN _max_pairs
#define maximum_windows 		CURN _maximum_windows
#define micro_col_size 			CURN _micro_col_size
#define micro_line_size 		CURN _micro_line_size
#define no_color_video 			CURN _no_color_video
#define number_of_pins 			CURN _number_of_pins
#define num_labels 			CURN _num_labels
#define output_res_char 		CURN _output_res_char
#define output_res_line 		CURN _output_res_line
#define output_res_horz_inch 		CURN _output_res_horz_inch
#define output_res_vert_inch 		CURN _output_res_vert_inch
#define print_rate 			CURN _print_rate
#define wide_char_size 			CURN _wide_char_size

#define back_tab			CURS strs._back_tab
#define bell 				CURS strs._bell
#define carriage_return 		CURS strs._carriage_return	
#define change_scroll_region 		CURS strs._change_scroll_region
#define clear_all_tabs 			CURS strs._clear_all_tabs
#define clear_screen 			CURS strs._clear_screen
#define clr_eol 			CURS strs._clr_eol
#define clr_eos 			CURS strs._clr_eos
#define column_address 			CURS strs._column_address
#define command_character 		CURS strs._command_character
#define cursor_address 			CURS strs._crsr_address 
#define cursor_down 			CURS strs._crsr_down
#define cursor_home 			CURS strs._crsr_home
#define cursor_invisible 		CURS strs._crsr_invisible
#define cursor_left 			CURS strs._crsr_left
#define cursor_mem_address 		CURS strs._crsr_mem_address
#define cursor_normal 			CURS strs._crsr_normal
#define cursor_right 			CURS strs._crsr_right
#define cursor_to_ll 			CURS strs._crsr_to_ll
#define cursor_up 			CURS strs._crsr_up
#define cursor_visible 			CURS strs._crsr_visible
#define delete_character 		CURS strs._dlt_character
#define delete_line 			CURS strs._dlt_line
#define dis_status_line 		CURS strs._dis_status_line
#define down_half_line 			CURS strs._down_half_line
#define enter_alt_charset_mode 		CURS strs._entr_alt_charset_mode 
#define enter_blink_mode 		CURS strs._entr_blink_mode 
#define enter_bold_mode 		CURS strs._entr_bold_mode
#define enter_ca_mode 			CURS strs._entr_ca_mode
#define enter_delete_mode 		CURS strs._entr_delete_mode
#define enter_dim_mode 			CURS strs._entr_dim_mode
#define enter_insert_mode 		CURS strs._entr_insert_mode
#define enter_secure_mode 		CURS strs._entr_secure_mode
#define enter_protected_mode 		CURS strs._entr_protected_mode
#define enter_reverse_mode 		CURS strs._entr_reverse_mode
#define enter_standout_mode 		CURS strs._entr_standout_mode
#define enter_underline_mode 		CURS strs._entr_underline_mode
#define erase_chars 			CURS strs._erase_chars
#define exit_alt_charset_mode 		CURS strs._exit_alt_charset_mode
#define exit_attribute_mode 		CURS strs._exit_attribute_mode
#define exit_ca_mode 			CURS strs._exit_ca_mode
#define exit_delete_mode 		CURS strs._exit_delete_mode
#define exit_insert_mode 		CURS strs._exit_insert_mode
#define exit_standout_mode 		CURS strs._exit_standout_mode
#define exit_underline_mode 		CURS strs._exit_underline_mode
#define flash_screen 			CURS strs._flash_screen
#define form_feed 			CURS strs._form_feed
#define from_status_line 		CURS strs._from_status_line
#define init_1string 			CURS strs._init_1string
#define init_2string 			CURS strs._init_2string
#define init_3string 			CURS strs._init_3string
#define init_file 			CURS strs._init_file
#define insert_character 		CURS strs._ins_character
#define insert_line 			CURS strs._ins_line
#define insert_padding 			CURS strs._ins_padding
#define key_backspace 			CURS strs._ky_backspace
#define key_catab 			CURS strs._ky_catab
#define key_clear 			CURS strs._ky_clear
#define key_ctab 			CURS strs._ky_ctab
#define key_dc 				CURS strs._ky_dc
#define key_dl 				CURS strs._ky_dl
#define key_down 			CURS strs._ky_down
#define key_eic 			CURS strs._ky_eic
#define key_eol 			CURS strs._ky_eol
#define key_eos 			CURS strs._ky_eos
#define key_f0 				CURS strs._ky_f0
#define key_f1 				CURS strs._ky_f1
#define key_f10 			CURS strs._ky_f10
#define key_f2 				CURS strs._ky_f2
#define key_f3 				CURS strs._ky_f3
#define key_f4 				CURS strs._ky_f4
#define key_f5 				CURS strs._ky_f5
#define key_f6 				CURS strs._ky_f6
#define key_f7 				CURS strs._ky_f7
#define key_f8 				CURS strs._ky_f8
#define key_f9 				CURS strs._ky_f9
#define key_home 			CURS strs._ky_home
#define key_ic 				CURS strs._ky_ic
#define key_il 				CURS strs._ky_il
#define key_left 			CURS strs._ky_left
#define key_ll 				CURS strs._ky_ll
#define key_npage 			CURS strs._ky_npage
#define key_ppage 			CURS strs._ky_ppage
#define key_right 			CURS strs._ky_right
#define key_sf 				CURS strs._ky_sf
#define key_sr 				CURS strs._ky_sr
#define key_stab 			CURS strs._ky_stab 
#define key_up 				CURS strs._ky_up
#define keypad_local 			CURS strs._kpad_local
#define keypad_xmit 			CURS strs._kpad_xmit
#define lab_f0 				CURS strs._lab_f0
#define lab_f1 				CURS strs._lab_f1 
#define lab_f10 			CURS strs._lab_f10
#define lab_f2 				CURS strs._lab_f2
#define lab_f3 				CURS strs._lab_f3
#define lab_f4 				CURS strs._lab_f4
#define lab_f5 				CURS strs._lab_f5
#define lab_f6 				CURS strs._lab_f6
#define lab_f7 				CURS strs._lab_f7
#define lab_f8 				CURS strs._lab_f8

#define lab_f9 				CURS strs2._lab_f9
#define meta_off 			CURS strs2._meta_off
#define meta_on 			CURS strs2._meta_on
#define newline 			CURS strs2._newline 
#define pad_char 			CURS strs2._pad_char
#define parm_dch 			CURS strs2._prm_dch
#define parm_delete_line 		CURS strs2._prm_delete_line
#define parm_down_cursor 		CURS strs2._prm_down_cursor
#define parm_ich 			CURS strs2._prm_ich
#define parm_index 			CURS strs2._prm_index
#define parm_insert_line 		CURS strs2._prm_insert_line
#define parm_left_cursor 		CURS strs2._prm_left_cursor
#define parm_right_cursor 		CURS strs2._prm_right_cursor
#define parm_rindex 			CURS strs2._prm_rindex
#define parm_up_cursor 			CURS strs2._prm_up_cursor
#define pkey_key 			CURS strs2._pkey_key
#define pkey_local 			CURS strs2._pkey_local
#define pkey_xmit 			CURS strs2._pkey_xmit
#define print_screen 			CURS strs2._print_screen
#define prtr_off 			CURS strs2._prtr_off
#define prtr_on 			CURS strs2._prtr_on
#define repeat_char 			CURS strs2._repeat_char
#define reset_1string 			CURS strs2._reset_1string
#define reset_2string 			CURS strs2._reset_2string
#define reset_3string 			CURS strs2._reset_3string
#define reset_file 			CURS strs2._reset_file
#define restore_cursor 			CURS strs2._restore_cursor
#define row_address 			CURS strs2._row_address
#define save_cursor 			CURS strs2._save_cursor
#define scroll_forward 			CURS strs2._scrll_forward 
#define scroll_reverse 			CURS strs2._scrll_reverse
#define set_attributes 			CURS strs2._set_attributes
#define set_tab 			CURS strs2._set_tab
#define set_window 			CURS strs2._set_window
#define tab 				CURS strs2._tab
#define to_status_line 			CURS strs2._to_status_line
#define underline_char 			CURS strs2._underline_char
#define up_half_line 			CURS strs2._up_half_line
#define init_prog 			CURS strs2._init_prog
#define key_a1 				CURS strs2._ky_a1
#define key_a3 				CURS strs2._ky_a3
#define key_b2 				CURS strs2._ky_b2
#define key_c1 				CURS strs2._ky_c1
#define key_c3 				CURS strs2._ky_c3
#define prtr_non 			CURS strs2._prtr_non
#define box_chars_1 			CURS strs2._box_chars_1
#define box_chars_2 			CURS strs2._box_chars_2
#define box_attr_1 			CURS strs2._box_attr_1
#define box_attr_2 			CURS strs2._box_attr_2
#define color_bg_0 			CURS strs2._color_bg_0
#define color_bg_1 			CURS strs2._color_bg_1
#define color_bg_2 			CURS strs2._color_bg_2
#define color_bg_3 			CURS strs2._color_bg_3
#define color_bg_4 			CURS strs2._color_bg_4
#define color_bg_5 			CURS strs2._color_bg_5
#define color_bg_6 			CURS strs2._color_bg_6
#define color_bg_7 			CURS strs2._color_bg_7
#define color_fg_0 			CURS strs2._color_fg_0
#define color_fg_1 			CURS strs2._color_fg_1
#define color_fg_2 			CURS strs2._color_fg_2
#define color_fg_3 			CURS strs2._color_fg_3
#define color_fg_4 			CURS strs2._color_fg_4
#define color_fg_5 			CURS strs2._color_fg_5
#define color_fg_6 			CURS strs2._color_fg_6
#define color_fg_7 			CURS strs2._color_fg_7
#define font_0 				CURS strs2._font_0
#define font_1 				CURS strs2._font_1
#define font_2 				CURS strs2._font_2
#define font_3 				CURS strs2._font_3
#define font_4 				CURS strs2._font_4
#define font_5 				CURS strs2._font_5
#define font_6 				CURS strs2._font_6
#define font_7 				CURS strs2._font_7
#define key_back_tab 			CURS strs2._ky_back_tab
#define key_do 				CURS strs2._ky_do
#define key_command 			CURS strs2._ky_command
#define key_command_pane 		CURS strs2._ky_command_pane
#define key_end 			CURS strs2._ky_end
#define key_help 			CURS strs2._ky_help
#define key_newline 			CURS strs2._ky_newline
#define key_next_pane 			CURS strs2._ky_next_pane
#define key_prev_cmd 			CURS strs2._ky_prev_cmd
#define key_prev_pane 			CURS strs2._ky_prev_pane
#define key_quit 			CURS strs2._ky_quit
#define key_select 			CURS strs2._ky_select
#define key_scroll_left 		CURS strs2._ky_scroll_left
#define key_scroll_right 		CURS strs2._ky_scroll_right
#define key_tab 			CURS strs2._ky_tab
#define key_smap_in1 			CURS strs2._ky_smap_in1
#define key_smap_out1 			CURS strs2._ky_smap_out1
#define key_smap_in2 			CURS strs2._ky_smap_in2
#define key_smap_out2 			CURS strs2._ky_smap_out2
#define key_smap_in3 			CURS strs2._ky_smap_in3
#define key_smap_out3 			CURS strs2._ky_smap_out3
#define key_smap_in4 			CURS strs2._ky_smap_in4
#define key_smap_out4 			CURS strs2._ky_smap_out4
#define key_smap_in5 			CURS strs2._ky_smap_in5
#define key_smap_out5 			CURS strs2._ky_smap_out5
#define appl_defined_str 		CURS strs2._appl_defined_str
#define key_smap_in6 			CURS strs2._ky_smap_in6

#define key_smap_out6 			CURS strs3._ky_smap_out6
#define key_smap_in7 			CURS strs3._ky_smap_in7
#define key_smap_out7 			CURS strs3._ky_smap_out7
#define key_smap_in8 			CURS strs3._ky_smap_in8
#define key_smap_out8 			CURS strs3._ky_smap_out8
#define key_smap_in9 			CURS strs3._ky_smap_in9
#define key_smap_out9 			CURS strs3._ky_smap_out9
#define key_sf1 			CURS strs3._ky_sf1
#define key_sf2 			CURS strs3._ky_sf2
#define key_sf3 			CURS strs3._ky_sf3
#define key_sf4 			CURS strs3._ky_sf4
#define key_sf5 			CURS strs3._ky_sf5
#define key_sf6 			CURS strs3._ky_sf6
#define key_sf7 			CURS strs3._ky_sf7
#define key_sf8 			CURS strs3._ky_sf8
#define key_sf9 			CURS strs3._ky_sf9
#define key_sf10 			CURS strs3._ky_sf10
#define key_f11 			CURS strs3._ky_f11
#define key_f12 			CURS strs3._ky_f12
#define key_f13 			CURS strs3._ky_f13
#define key_f14 			CURS strs3._ky_f14
#define key_f15 			CURS strs3._ky_f15
#define key_f16 			CURS strs3._ky_f16
#define key_f17 			CURS strs3._ky_f17
#define key_f18 			CURS strs3._ky_f18
#define key_f19 			CURS strs3._ky_f19
#define key_f20 			CURS strs3._ky_f20
#define key_f21 			CURS strs3._ky_f21
#define key_f22 			CURS strs3._ky_f22
#define key_f23 			CURS strs3._ky_f23
#define key_f24 			CURS strs3._ky_f24
#define key_f25 			CURS strs3._ky_f25
#define key_f26 			CURS strs3._ky_f26
#define key_f27 			CURS strs3._ky_f27
#define key_f28 			CURS strs3._ky_f28
#define key_f29 			CURS strs3._ky_f29
#define key_f30 			CURS strs3._ky_f30
#define key_f31 			CURS strs3._ky_f31
#define key_f32 			CURS strs3._ky_f32
#define key_f33 			CURS strs3._ky_f33
#define key_f34 			CURS strs3._ky_f34
#define key_f35 			CURS strs3._ky_f35
#define key_f36 			CURS strs3._ky_f36
#define key_action 			CURS strs3._ky_action
#define acs_chars 			CURS strs3._acs_chars
#define alt_scancode_esc 		CURS strs3._alt_scancode_esc
#define bit_image_repeat 		CURS strs3._bit_image_repeat
#define bit_image_newline 		CURS strs3._bit_image_newline
#define bit_image_carriage_return 	CURS strs3._bit_image_carriage_return
#define change_char_pitch 		CURS strs3._change_char_pitch
#define change_line_pitch 		CURS strs3._change_line_pitch
#define change_res_horz 		CURS strs3._change_res_horz
#define change_res_vert 		CURS strs3._change_res_vert
#define char_padding 			CURS strs3._char_padding
#define char_set_names 			CURS strs3._char_set_names
#define clear_margins 			CURS strs3._clear_margins
#define clr_bol 			CURS strs3._clr_bol
#define code_set_init 			CURS strs3._code_set_init
#define color_names 			CURS strs3._color_names
#define create_window 			CURS strs3._create_window
#define define_bit_image_region 	CURS strs3._define_bit_image_region
#define define_char 			CURS strs3._define_char
#define device_type 			CURS strs3._device_type
#define dial_phone 			CURS strs3._dial_phone
#define display_clock 			CURS strs3._display_clock
#define display_pc_char 		CURS strs3._display_pc_char
#define ena_acs 			CURS strs3._ena_acs
#define end_bit_image_region 		CURS strs3._end_bit_image_region
#define enter_am_mode 			CURS strs3._entr_am_mode
#define enter_doublewide_mode 		CURS strs3._entr_doublewide_mode
#define enter_draft_quality 		CURS strs3._entr_draft_quality
#define enter_italics_mode 		CURS strs3._entr_italics_mode
#define enter_leftward_mode 		CURS strs3._entr_leftward_mode
#define enter_micro_mode 		CURS strs3._entr_micro_mode
#define enter_near_letter_quality 	CURS strs3._entr_near_letter_quality
#define enter_normal_quality 		CURS strs3._entr_normal_quality
#define enter_pc_charset_mode 		CURS strs3._entr_pc_charset_mode
#define enter_scancode_mode 		CURS strs3._entr_scancode_mode
#define enter_shadow_mode 		CURS strs3._entr_shadow_mode
#define enter_subscript_mode 		CURS strs3._entr_subscript_mode
#define enter_superscript_mode 		CURS strs3._entr_superscript_mode
#define enter_upward_mode 		CURS strs3._entr_upward_mode
#define enter_xon_mode 			CURS strs3._entr_xon_mode
#define exit_am_mode 			CURS strs3._exit_am_mode
#define exit_doublewide_mode 		CURS strs3._exit_doublewide_mode
#define exit_italics_mode 		CURS strs3._exit_italics_mode
#define exit_leftward_mode 		CURS strs3._exit_leftward_mode
#define exit_micro_mode 		CURS strs3._exit_micro_mode
#define exit_pc_charset_mode 		CURS strs3._exit_pc_charset_mode
#define exit_scancode_mode 		CURS strs3._exit_scancode_mode
#define exit_shadow_mode 		CURS strs3._exit_shadow_mode
#define exit_subscript_mode 		CURS strs3._exit_subscript_mode
#define exit_superscript_mode 		CURS strs3._exit_superscript_mode
#define exit_upward_mode 		CURS strs3._exit_upward_mode
#define exit_xon_mode 			CURS strs3._exit_xon_mode
#define fixed_pause 			CURS strs3._fixed_pause
#define flash_hook 			CURS strs3._flash_hook
#define get_mouse 			CURS strs3._get_mouse
#define goto_window 			CURS strs3._goto_window
#define hangup 				CURS strs3._hangup

#define initialize_color 		CURS strs4._initialize_color
#define initialize_pair 		CURS strs4._initialize_pair
#define key_beg 			CURS strs4._ky_beg
#define key_btab 			CURS strs4._ky_btab
#define key_cancel 			CURS strs4._ky_cancel
#define key_close 			CURS strs4._ky_close
#define key_copy 			CURS strs4._ky_copy
#define key_create 			CURS strs4._ky_create
#define key_enter 			CURS strs4._ky_enter
#define key_exit 			CURS strs4._ky_exit
#define key_f37 			CURS strs4._ky_f37
#define key_f38 			CURS strs4._ky_f38
#define key_f39 			CURS strs4._ky_f39
#define key_f40 			CURS strs4._ky_f40
#define key_f41 			CURS strs4._ky_f41
#define key_f42 			CURS strs4._ky_f42
#define key_f43 			CURS strs4._ky_f43
#define key_f44 			CURS strs4._ky_f44
#define key_f45 			CURS strs4._ky_f45
#define key_f46 			CURS strs4._ky_f46
#define key_f47 			CURS strs4._ky_f47
#define key_f48 			CURS strs4._ky_f48
#define key_f49 			CURS strs4._ky_f49
#define key_f50 			CURS strs4._ky_f50
#define key_f51 			CURS strs4._ky_f51
#define key_f52 			CURS strs4._ky_f52
#define key_f53 			CURS strs4._ky_f53
#define key_f54 			CURS strs4._ky_f54
#define key_f55 			CURS strs4._ky_f55
#define key_f56 			CURS strs4._ky_f56
#define key_f57 			CURS strs4._ky_f57
#define key_f58 			CURS strs4._ky_f58
#define key_f59 			CURS strs4._ky_f59
#define key_f60 			CURS strs4._ky_f60
#define key_f61 			CURS strs4._ky_f61
#define key_f62 			CURS strs4._ky_f62
#define key_f63 			CURS strs4._ky_f63
#define key_find 			CURS strs4._ky_find
#define key_mark 			CURS strs4._ky_mark
#define key_message 			CURS strs4._ky_message
#define key_mouse 			CURS strs4._ky_mouse
#define key_move 			CURS strs4._ky_move
#define key_next 			CURS strs4._ky_next
#define key_open 			CURS strs4._ky_open
#define key_options 			CURS strs4._ky_options
#define key_previous 			CURS strs4._ky_previous
#define key_print 			CURS strs4._ky_print
#define key_redo 			CURS strs4._ky_redo
#define key_reference 			CURS strs4._ky_reference
#define key_refresh 			CURS strs4._ky_refresh
#define key_replace 			CURS strs4._ky_replace
#define key_restart 			CURS strs4._ky_restart
#define key_resume 			CURS strs4._ky_resume
#define key_save 			CURS strs4._ky_save
#define key_sbeg 			CURS strs4._ky_sbeg
#define key_scancel 			CURS strs4._ky_scancel
#define key_scommand 			CURS strs4._ky_scommand
#define key_scopy 			CURS strs4._ky_scopy
#define key_screate 			CURS strs4._ky_screate
#define key_sdc 			CURS strs4._ky_sdc
#define key_sdl 			CURS strs4._ky_sdl
#define key_send 			CURS strs4._ky_send
#define key_seol 			CURS strs4._ky_seol
#define key_sexit 			CURS strs4._ky_sexit
#define key_sfind 			CURS strs4._ky_sfind
#define key_shelp 			CURS strs4._ky_shelp
#define key_shome 			CURS strs4._ky_shome
#define key_sic 			CURS strs4._ky_sic
#define key_sleft 			CURS strs4._ky_sleft
#define key_smessage 			CURS strs4._ky_smessage
#define key_smove 			CURS strs4._ky_smove
#define key_snext 			CURS strs4._ky_snext
#define key_soptions 			CURS strs4._ky_soptions
#define key_sprevious 			CURS strs4._ky_sprevious
#define key_sprint 			CURS strs4._ky_sprint
#define key_sredo 			CURS strs4._ky_sredo
#define key_sreplace 			CURS strs4._ky_sreplace
#define key_sright 			CURS strs4._ky_sright
#define key_srsume 			CURS strs4._ky_srsume
#define key_ssave 			CURS strs4._ky_ssave
#define key_ssuspend 			CURS strs4._ky_ssuspend
#define key_sundo 			CURS strs4._ky_sundo
#define key_suspend 			CURS strs4._ky_suspend
#define key_undo 			CURS strs4._ky_undo
#define label_format 			CURS strs4._labl_format
#define label_off 			CURS strs4._labl_off
#define label_on 			CURS strs4._labl_on
#define micro_column_address 		CURS strs4._micro_column_address
#define micro_down 			CURS strs4._micro_down
#define micro_left 			CURS strs4._micro_left
#define micro_right 			CURS strs4._micro_right
#define micro_row_address 		CURS strs4._micro_row_address
#define micro_up 			CURS strs4._micro_up
#define mouse_info 			CURS strs4._mouse_info
#define order_of_pins 			CURS strs4._order_of_pins
#define orig_colors 			CURS strs4._orig_colors
#define orig_pair 			CURS strs4._orig_pair
#define parm_down_micro 		CURS strs4._prm_down_micro
#define parm_left_micro 		CURS strs4._prm_left_micro
#define parm_right_micro 		CURS strs4._prm_right_micro
#define parm_up_micro 			CURS strs4._prm_up_micro
#define pc_term_options 		CURS strs4._pc_term_options
#define pkey_plab 			CURS strs4._pkey_plab
#define plab_norm 			CURS strs4._plab_norm
#define pulse 				CURS strs4._pulse
#define quick_dial 			CURS strs4._quick_dial
#define req_for_input 			CURS strs4._req_for_input
#define req_mouse_pos 			CURS strs4._req_mouse_pos
#define remove_clock 			CURS strs4._remove_clock
#define scancode_escape 		CURS strs4._scancode_escape
#define select_char_set 		CURS strs4._select_char_set
#define set0_des_seq 			CURS strs4._set0_des_seq
#define set1_des_seq 			CURS strs4._set1_des_seq
#define set2_des_seq 			CURS strs4._set2_des_seq
#define set3_des_seq 			CURS strs4._set3_des_seq
#define set_a_background 		CURS strs4._set_a_background
#define set_a_foreground 		CURS strs4._set_a_foreground
#define set_background 			CURS strs4._set_background
#define set_bottom_margin 		CURS strs4._set_bottom_margin
#define set_bottom_margin_parm 		CURS strs4._set_bottom_margin_parm
#define set_clock 			CURS strs4._set_clock
#define set_color_band 			CURS strs4._set_color_band
#define set_color_pair 			CURS strs4._set_color_pair
#define set_foreground 			CURS strs4._set_foreground
#define set_left_margin 		CURS strs4._set_left_margin
#define set_left_margin_parm 		CURS strs4._set_left_margin_parm
#define set_lr_margin 			CURS strs4._set_lr_margin
#define set_page_length 		CURS strs4._set_page_length
#define set_right_margin 		CURS strs4._set_right_margin
#define set_right_margin_parm 		CURS strs4._set_right_margin_parm
#define set_tb_margin 			CURS strs4._set_tb_margin
#define set_top_margin 			CURS strs4._set_top_margin
#define set_top_margin_parm 		CURS strs4._set_top_margin_parm
#define start_bit_image 		CURS strs4._start_bit_image
#define start_char_set_def 		CURS strs4._start_char_set_def
#define stop_bit_image 			CURS strs4._stop_bit_image
#define stop_char_set_def 		CURS strs4._stop_char_set_def
#define subscript_characters 		CURS strs4._subscript_characters
#define superscript_characters 		CURS strs4._superscript_characters
#define these_cause_cr 			CURS strs4._these_cause_cr
#define tone 				CURS strs4._tone
#define user0 				CURS strs4._user0
#define user1 				CURS strs4._user1
#define user2 				CURS strs4._user2
#define user3 				CURS strs4._user3
#define user4 				CURS strs4._user4
#define user5 				CURS strs4._user5
#define user6 				CURS strs4._user6
#define user7 				CURS strs4._user7
#define user8 				CURS strs4._user8
#define user9 				CURS strs4._user9
#define wait_tone 			CURS strs4._wait_tone
#define xoff_character 			CURS strs4._xoff_character
#define xon_character 			CURS strs4._xon_character
#define zero_motion 			CURS strs4._zero_motion
#define set_pglen_inch			CURS strs4._set_pglen_inch

#define enter_horizontal_hl_mode        CURS strs4._entr_horizontal_hl_mode
#define enter_left_hl_mode              CURS strs4._entr_left_hl_mode
#define enter_low_hl_mode               CURS strs4._entr_low_hl_mode
#define enter_right_hl_mode             CURS strs4._entr_right_hl_mode
#define enter_top_hl_mode               CURS strs4._entr_top_hl_mode
#define enter_vertical_hl_mode          CURS strs4._entr_vertical_hl_mode
#define set_a_attributes                CURS strs4._set_a_attributes

typedef char *charptr;
struct strs {
    charptr
	_back_tab,		/* Back tab (P) */
	_bell,			/* Audible signal (bell) (P) */
	_carriage_return,	/* Carriage return (P*) */
	_change_scroll_region,	/* change to lines #1 thru #2 (vt100) (PG) */
	_clear_all_tabs,	/* Clear all tab stops. (P) */
	_clear_screen,		/* Clear screen (P*) */
	_clr_eol,		/* Clear to end of line (P) */
	_clr_eos,		/* Clear to end of display (P*) */
	_column_address,	/* Set cursor column (PG) */
	_command_character,	/* Term. settable cmd char in prototype */
	_crsr_address,		/* Cursor motion to row #1 col #2 (PG) */
	_crsr_down,		/* Down one line */
	_crsr_home,		/* Home cursor (if no cup) */
	_crsr_invisible,	/* Make cursor invisible */
	_crsr_left,		/* Move cursor left one space. */
	_crsr_mem_address,	/* Memory relative cursor addressing. */
	_crsr_normal,		/* Make cursor appear normal (undo vs/vi) */
	_crsr_right,		/* Non-destructive space (cursor right) */
	_crsr_to_ll,		/* Last line, first column (if no cup) */
	_crsr_up,		/* Upline (cursor up) */
	_crsr_visible,		/* Make cursor very visible */
	_dlt_character,		/* Delete character (P*) */
	_dlt_line,		/* Delete line (P*) */
	_dis_status_line,	/* Disable status line */
	_down_half_line,	/* Half-line down (forward 1/2 linefeed) */
	_entr_alt_charset_mode,	/* Start alternate character set (P) */
	_entr_blink_mode,	/* Turn on blinking */
	_entr_bold_mode,	/* Turn on bold (extra bright) mode */
	_entr_ca_mode,		/* String to begin programs that use cup */
	_entr_delete_mode,	/* Delete mode (enter) */
	_entr_dim_mode,		/* Turn on half-bright mode */
	_entr_insert_mode,	/* Insert mode (enter); */
	_entr_secure_mode,	/* Turn on blank mode (chars invisible) */
	_entr_protected_mode,	/* Turn on protected mode */
	_entr_reverse_mode,	/* Turn on reverse video mode */
	_entr_standout_mode,	/* Begin stand out mode */
	_entr_underline_mode,	/* Start underscore mode */
	_erase_chars,		/* Erase #1 characters (PG) */
	_exit_alt_charset_mode,	/* End alternate character set (P) */
	_exit_attribute_mode,	/* Turn off all attributes */
	_exit_ca_mode,		/* String to end programs that use cup */
	_exit_delete_mode,	/* End delete mode */
	_exit_insert_mode,	/* End insert mode; */
	_exit_standout_mode,	/* End stand out mode */
	_exit_underline_mode,	/* End underscore mode */
	_flash_screen,		/* Visible bell (may not move cursor) */
	_form_feed,		/* Hardcopy terminal page eject (P*) */
	_from_status_line,	/* Return from status line */
	_init_1string,		/* Terminal initialization string */
	_init_2string,		/* Terminal initialization string */
	_init_3string,		/* Terminal initialization string */
	_init_file,		/* Name of file containing is */
	_ins_character,		/* Insert character (P) */
	_ins_line,		/* Add new blank line (P*) */
	_ins_padding,		/* Insert pad after character inserted (P*) */
	_ky_backspace,		/* KEY_BACKSPACE, 0407, Sent by backspace key */
	_ky_catab,		/* KEY_CATAB, 0526, Sent by clear-all-tabs key. */
	_ky_clear,		/* KEY_CLEAR, 0515, Sent by clear screen or erase key. */
	_ky_ctab,		/* KEY_CTAB, 0525, Sent by clear-tab key */
	_ky_dc,			/* KEY_DC, 0512, Sent by delete character key. */
	_ky_dl,			/* KEY_DL, 0510, Sent by delete line key. */
	_ky_down,		/* KEY_DOWN, 0402, Sent by terminal down arrow key */
	_ky_eic,		/* KEY_EIC, 0514, Sent by rmir or smir in insert mode. */
	_ky_eol,		/* KEY_EOL, 0517, Sent by clear-to-end-of-line key. */
	_ky_eos,		/* KEY_EOS, 0516, Sent by clear-to-end-of-screen key. */
	_ky_f0,			/* KEY_F(0), 0410, Sent by function key f0. */
	_ky_f1,			/* KEY_F(1), 0411, Sent by function key f1. */
	_ky_f10,		/* KEY_F(10), 0422, Sent by function key f10. */
	_ky_f2,			/* KEY_F(2), 0412, Sent by function key f2. */
	_ky_f3,			/* KEY_F(3), 0413, Sent by function key f3. */
	_ky_f4,			/* KEY_F(4), 0414, Sent by function key f4. */
	_ky_f5,			/* KEY_F(5), 0415, Sent by function key f5. */
	_ky_f6,			/* KEY_F(6), 0416, Sent by function key f6. */
	_ky_f7,			/* KEY_F(7), 0417, Sent by function key f7. */
	_ky_f8,			/* KEY_F(8), 0420, Sent by function key f8. */
	_ky_f9,			/* KEY_F(9), 0421, Sent by function key f9. */
	_ky_home,		/* KEY_HOME, 0406, Sent by home key. */
	_ky_ic,			/* KEY_IC, 0513, Sent by ins char/enter ins mode key. */
	_ky_il,			/* KEY_IL, 0511, Sent by insert line. */
	_ky_left,		/* KEY_LEFT, 0404, Sent by terminal left arrow key */
	_ky_ll,			/* KEY_LL, 0533, Sent by home-down key */
	_ky_npage,		/* KEY_NPAGE, 0522, Sent by next-page key */
	_ky_ppage,		/* KEY_PPAGE, 0523, Sent by previous-page key */
	_ky_right,		/* KEY_RIGHT, 0405, Sent by terminal right arrow key */
	_ky_sf,			/* KEY_SF, 0520, Sent by scroll-forward/down key */
	_ky_sr,			/* KEY_SR, 0521, Sent by scroll-backward/up key */
	_ky_stab,		/* KEY_STAB, 0524, Sent by set-tab key */
	_ky_up,			/* KEY_UP, 0403, Sent by terminal up arrow key */
	_kpad_local,		/* Out of "keypad transmit" mode */
	_kpad_xmit,		/* Put terminal in "keypad transmit" mode */
	_lab_f0,		/* Labels on function key f0 if not f0 */
	_lab_f1,		/* Labels on function key f1 if not f1 */
	_lab_f10,		/* Labels on function key f10 if not f10 */
	_lab_f2,		/* Labels on function key f2 if not f2 */
	_lab_f3,		/* Labels on function key f3 if not f3 */
	_lab_f4,		/* Labels on function key f4 if not f4 */
	_lab_f5,		/* Labels on function key f5 if not f5 */
	_lab_f6,		/* Labels on function key f6 if not f6 */
	_lab_f7,		/* Labels on function key f7 if not f7 */
	_lab_f8;		/* Labels on function key f8 if not f8 */
};

struct strs2 {
    charptr
	_lab_f9,		/* Labels on function key f9 if not f9 */
	_meta_off,		/* Turn off "meta mode" */
	_meta_on,		/* Turn on "meta mode" (8th bit) */
	_newline,		/* Newline (behaves like cr followed by lf) */
	_pad_char,		/* Pad character (rather than null) */
	_prm_dch,		/* Delete #1 chars (PG*) */
	_prm_delete_line,	/* Delete #1 lines (PG*) */
	_prm_down_cursor,	/* Move cursor down #1 lines. (PG*) */
	_prm_ich,		/* Insert #1 blank chars (PG*) */
	_prm_index,		/* Scroll forward #1 lines. (PG) */
	_prm_insert_line,	/* Add #1 new blank lines (PG*) */
	_prm_left_cursor,	/* Move cursor left #1 spaces (PG) */
	_prm_right_cursor,	/* Move cursor right #1 spaces. (PG*) */
	_prm_rindex,		/* Scroll backward #1 lines. (PG) */
	_prm_up_cursor,		/* Move cursor up #1 lines. (PG*) */
	_pkey_key,		/* Prog funct key #1 to type string #2 */
	_pkey_local,		/* Prog funct key #1 to execute string #2 */
	_pkey_xmit,		/* Prog funct key #1 to xmit string #2 */
	_print_screen,		/* Print contents of the screen */
	_prtr_off,		/* Turn off the printer */
	_prtr_on,		/* Turn on the printer */
	_repeat_char,		/* Repeat char #1 #2 times.  (PG*) */
	_reset_1string,		/* Reset terminal completely to sane modes. */
	_reset_2string,		/* Reset terminal completely to sane modes. */
	_reset_3string,		/* Reset terminal completely to sane modes. */
	_reset_file,		/* Name of file containing reset string. */
	_restore_cursor,	/* Restore cursor to position of last sc. */
	_row_address,		/* Like hpa but sets row. (PG) */
	_save_cursor,		/* Save cursor position. (P) */
	_scrll_forward,		/* Scroll text up (P) */
	_scrll_reverse,		/* Scroll text down (P) */
	_set_attributes,	/* Define the video attributes (PG9) */
	_set_tab,		/* Set a tab in all rows, current column. */
	_set_window,		/* Current window is lines #1-#2 cols #3-#4 */
	_tab,			/* Tab to next 8 space hardware tab stop. */
	_to_status_line,	/* Go to status line */
	_underline_char,	/* Underscore one char and move past it */
	_up_half_line,		/* Half-line up (reverse 1/2 linefeed) */
	_init_prog,		/* Path name of program for init. */
	_ky_a1,			/* KEY_A1, 0534, Upper left of keypad */
	_ky_a3,			/* KEY_A3, 0535, Upper right of keypad */
	_ky_b2,			/* KEY_B2, 0536, Center of keypad */
	_ky_c1,			/* KEY_C1, 0537, Lower left of keypad */
	_ky_c3,			/* KEY_C3, 0540, Lower right of keypad */
	_prtr_non,		/* Turn on the printer for #1 bytes. */
	_box_chars_1,		/* Box characters primary set */
	_box_chars_2, 		/* Box characters alternate set */
	_box_attr_1,		/* Attributes for box_chars_1 */
	_box_attr_2,		/* Attributes for box_chars_2 */
	_color_bg_0,		/* Background color 0 black */
	_color_bg_1,		/* Background color 1 red */
	_color_bg_2,		/* Background color 2 green */
	_color_bg_3,		/* Background color 3 brown */
	_color_bg_4,		/* Background color 4 blue */
	_color_bg_5,		/* Background color 5 magenta */
	_color_bg_6,		/* Background color 6 cyan */
	_color_bg_7,		/* Background color 7 white */
	_color_fg_0,		/* Foreground color 0 white */
	_color_fg_1,		/* Foreground color 1 red */
	_color_fg_2,		/* Foreground color 2 green */
	_color_fg_3,		/* Foreground color 3 brown */
	_color_fg_4,		/* Foreground color 4 blue */
	_color_fg_5,		/* Foreground color 5 magenta */
	_color_fg_6,		/* Foreground color 6 cyan */
	_color_fg_7,		/* Foreground color 7 black */
	_font_0,		/* Select font 0 */
	_font_1,		/* Select font 1 */
	_font_2,		/* Select font 2 */
	_font_3,		/* Select font 3 */
	_font_4,		/* Select font 4 */
	_font_5,		/* Select font 5 */
	_font_6,		/* Select font 6 */
	_font_7,		/* Select font 7 */
	_ky_back_tab,		/* Backtab key */
	_ky_do,			/* Do request key */
	_ky_command,		/* KEY_COMMAND, 0545, Command request key */
	_ky_command_pane,	/* Command pane key */
	_ky_end,		/* KEY_END, 0550, End key */
	_ky_help,		/* KEY_HELP, 0553, Help key */
	_ky_newline,		/* Newline key */
	_ky_next_pane,		/* Next pane key */
	_ky_prev_cmd,		/* Previous command key */
	_ky_prev_pane,		/* Previous pane key */
	_ky_quit,		/* Quit key */
	_ky_select,		/* KEY_SELECT, 0601, Select key */
	_ky_scroll_left,	/* Scroll left */
	_ky_scroll_right,	/* Scroll right */
	_ky_tab,		/* Tab key */
	_ky_smap_in1,		/* input for special mapped key 1 */
	_ky_smap_out1,		/* output for mapped key 1 */
	_ky_smap_in2,		/* input for special mapped key 2 */
	_ky_smap_out2,		/* output for mapped key 2 */
	_ky_smap_in3,		/* input for special mapped key 3 */
	_ky_smap_out3,		/* output for mapped key 3 */
	_ky_smap_in4,		/* input for special mapped key 4 */
	_ky_smap_out4,		/* output for mapped key 4 */
	_ky_smap_in5,		/* input for special mapped key 5 */
	_ky_smap_out5,		/* output for mapped key 5 */
	_appl_defined_str,	/* Application defined terminal string */
	_ky_smap_in6;		/* input for special mapped key 6 */
};

struct strs3 {
    charptr
	_ky_smap_out6,		/* output for mapped key 6 */
	_ky_smap_in7,		/* input for special mapped key 7 */
	_ky_smap_out7,		/* output for mapped key 7 */
	_ky_smap_in8,		/* input for special mapped key 8 */
	_ky_smap_out8,		/* output for mapped key 8 */
	_ky_smap_in9,		/* input for special mapped key 9 */
	_ky_smap_out9,		/* output for mapped key 9 */
	_ky_sf1,		/* Special function key 1 */
	_ky_sf2,		/* Special function key 2 */
	_ky_sf3,		/* Special function key 3 */
	_ky_sf4,		/* Special function key 4 */
	_ky_sf5,		/* Special function key 5 */
	_ky_sf6,		/* Special function key 6 */
	_ky_sf7,		/* Special function key 7 */
	_ky_sf8,		/* Special function key 8 */
	_ky_sf9,		/* Special function key 9 */
	_ky_sf10,		/* Special function key 10 */
	_ky_f11,		/* KEY_F(11), 0423,Sent by function key f11. */
	_ky_f12,		/* KEY_F(12), 0424,Sent by function key f12. */
	_ky_f13,		/* KEY_F(13), 0425,Sent by function key f13. */
	_ky_f14,		/* KEY_F(14), 0426,Sent by function key f14. */
	_ky_f15,		/* KEY_F(15), 0427,Sent by function key f15. */
	_ky_f16,		/* KEY_F(16), 0430,Sent by function key f16. */
	_ky_f17,		/* KEY_F(17), 0431,Sent by function key f17. */
	_ky_f18,		/* KEY_F(18), 0432,Sent by function key f18. */
	_ky_f19,		/* KEY_F(19), 0433,Sent by function key f19. */
	_ky_f20,		/* KEY_F(20), 0434,Sent by function key f20. */
	_ky_f21,		/* KEY_F(21), 0435,Sent by function key f21. */
	_ky_f22,		/* KEY_F(22), 0436,Sent by function key f22. */
	_ky_f23,		/* KEY_F(23), 0437,Sent by function key f23. */
	_ky_f24,		/* KEY_F(24), 0440,Sent by function key f24. */
	_ky_f25,		/* KEY_F(25), 0441,Sent by function key f25. */
	_ky_f26,		/* KEY_F(26), 0442,Sent by function key f26. */
	_ky_f27,		/* KEY_F(27), 0443,Sent by function key f27. */
	_ky_f28,		/* KEY_F(28), 0444,Sent by function key f28. */
	_ky_f29,		/* KEY_F(29), 0445,Sent by function key f29. */
	_ky_f30,		/* KEY_F(30), 0446,Sent by function key f30. */
	_ky_f31,		/* KEY_F(31), 0447,Sent by function key f31. */
	_ky_f32,		/* KEY_F(32), 0450,Sent by function key f32. */
	_ky_f33,		/* KEY_F(33), 0451,Sent by function key f33. */
	_ky_f34,		/* KEY_F(34), 0452,Sent by function key f34. */
	_ky_f35,		/* KEY_F(35), 0453,Sent by function key f35. */
	_ky_f36,		/* KEY_F(36), 0454,Sent by function key f36. */
	_ky_action,		/* KEY_ACTION, 0541, Sent by the action key. */
	_acs_chars,		/* Graphic charset pairs aAbBcC */
	_alt_scancode_esc,	/* Alternate escape for scancode emulation */
	_bit_image_repeat,	/* Repeat bit-image cell #1 #2 times (use tparm) */
	_bit_image_newline,	/* Move to next row of the bit image (use tparm) */
	_bit_image_carriage_return,	/* Move to beginning of same row (use tparm) */
	_change_char_pitch,	/* Change number of characters per inch */
	_change_line_pitch,	/* Change number of lines per inch */
	_change_res_horz,	/* Change horizontal resolution */
	_change_res_vert,	/* Change vertical resolution */
	_char_padding,		/* Like ip but when in replace mode */
	_char_set_names,	/* List of character set names */
	_clear_margins,		/* Clear all margins (top, bottom, and sides) */
	_clr_bol,		/* Clear to beginning of line, inclusive */
	_code_set_init,		/* Init sequence for multiple codesets */
	_color_names,		/* Give name for color #1 */
	_create_window,		/* Define win #1 to go from #2,#3 to #4,#5 */
	_define_bit_image_region, /* Define rectangular bit-image region (use tparm) */
	_define_char,		/* Define a character in a character set| */
	_device_type,		/* Indicate language/codeset support */
	_dial_phone,		/* Dial phone number #1 */
	_display_clock,		/* Display time-of-day clock */
	_display_pc_char,	/* Display PC character */
	_ena_acs,		/* Enable alternate character set */
	_end_bit_image_region,	/* End a bit-image region (use tparm) */
	_entr_am_mode,		/* Turn on automatic margins */
	_entr_doublewide_mode,	/* Enable double wide printing */
	_entr_draft_quality,	/* Set draft quality print */
	_entr_italics_mode,	/* Enable italics */
	_entr_leftward_mode,	/* Enable leftward carriage motion */
	_entr_micro_mode,	/* Enable micro motion capabilities */
	_entr_near_letter_quality,	/* Set near-letter quality print */
	_entr_normal_quality,	/* Set normal quality print */
	_entr_pc_charset_mode,	/* Enter PC character display mode */
	_entr_scancode_mode,	/* Enter PC scancode mode */
	_entr_shadow_mode,	/* Enable shadow printing */
	_entr_subscript_mode,	/* Enable subscript printing */
	_entr_superscript_mode,	/* Enable superscript printing */
	_entr_upward_mode,	/* Enable upward carriage motion */
	_entr_xon_mode,		/* Turn on xon/xoff handshaking */
	_exit_am_mode,		/* Turn off automatic margins */
	_exit_doublewide_mode,	/* Disable double wide printing */
	_exit_italics_mode,	/* Disable italics */
	_exit_leftward_mode,	/* Enable rightward (normal) */
	_exit_micro_mode,	/* Disable micro motion capabilities */
	_exit_pc_charset_mode,	/* Disable PC character display mode */
	_exit_scancode_mode,	/* Disable PC scancode mode */
	_exit_shadow_mode,	/* Disable shadow printing */
	_exit_subscript_mode,	/* Disable subscript printing */
	_exit_superscript_mode,	/* Disable superscript printing */
	_exit_upward_mode,	/* Enable downward (normal) */
	_exit_xon_mode,		/* Turn off xon/xoff handshaking */
	_fixed_pause,		/* Pause for 2-3 seconds */
	_flash_hook,		/* Flash the switch hook */
	_get_mouse,		/* Curses should get button events */
	_goto_window,		/* Got to window #1 */
	_hangup;		/* Hang-up phone */
};

struct strs4 {
    charptr
	_initialize_color,	/* Initialize the definition of color */
	_initialize_pair,	/* Initialize color-pair */
	_ky_beg,		/* KEY_BEG, 0542, sent by beg(inning) key */
	_ky_btab,		/* KEY_BTAB, 0632, sent by back-tab key */
	_ky_cancel,		/* KEY_CANCEL, 0543, sent by cancel key */
	_ky_close,		/* KEY_CLOSE, 0544, sent by close key */
	_ky_copy,		/* KEY_COPY, 0546, sent by copy key */
	_ky_create,		/* KEY_CREATE, 0547, sent by create key */
	_ky_enter,		/* KEY_ENTER, 0527, sent by enter/send key */
	_ky_exit,		/* KEY_EXIT, 0551, sent by exit key */
	_ky_f37,		/* KEY_F(37), 0455, sent by function key f37 */
	_ky_f38,		/* KEY_F(38), 0456, sent by function key f38 */
	_ky_f39,		/* KEY_F(39), 0457, sent by function key f39 */
	_ky_f40,		/* KEY_F(40), 0460, sent by function key f40 */
	_ky_f41,		/* KEY_F(41), 0461, sent by function key f41 */
	_ky_f42,		/* KEY_F(42), 0462, sent by function key f42 */
	_ky_f43,		/* KEY_F(43), 0463, sent by function key f43 */
	_ky_f44,		/* KEY_F(44), 0464, sent by function key f44 */
	_ky_f45,		/* KEY_F(45), 0465, sent by function key f45 */
	_ky_f46,		/* KEY_F(46), 0466, sent by function key f46 */
	_ky_f47,		/* KEY_F(47), 0467, sent by function key f47 */
	_ky_f48,		/* KEY_F(48), 0470, sent by function key f48 */
	_ky_f49,		/* KEY_F(49), 0471, sent by function key f49 */
	_ky_f50,		/* KEY_F(50), 0472, sent by function key f50 */
	_ky_f51,		/* KEY_F(51), 0473, sent by function key f51 */
	_ky_f52,		/* KEY_F(52), 0474, sent by function key f52 */
	_ky_f53,		/* KEY_F(53), 0475, sent by function key f53 */
	_ky_f54,		/* KEY_F(54), 0476, sent by function key f54 */
	_ky_f55,		/* KEY_F(55), 0477, sent by function key f55 */
	_ky_f56,		/* KEY_F(56), 0500, sent by function key f56 */
	_ky_f57,		/* KEY_F(57), 0501, sent by function key f57 */
	_ky_f58,		/* KEY_F(58), 0502, sent by function key f58 */
	_ky_f59,		/* KEY_F(59), 0503, sent by function key f59 */
	_ky_f60,		/* KEY_F(60), 0504, sent by function key f60 */
	_ky_f61,		/* KEY_F(61), 0505, sent by function key f61 */
	_ky_f62,		/* KEY_F(62), 0506, sent by function key f62 */
	_ky_f63,		/* KEY_F(63), 0507, sent by function key f63 */
	_ky_find,		/* KEY_FIND, 0552, sent by find key */
	_ky_mark,		/* KEY_MARK, 0554, sent by mark key */
	_ky_message,		/* KEY_MESSAGE, 0555, sent by message key */
	_ky_mouse,		/* KEY_MOUSE, 0631, mouse event has occured */
	_ky_move,		/* KEY_MOVE, 0556, sent by move key */
	_ky_next,		/* KEY_NEXT, 0557, sent by next-object key */
	_ky_open,		/* KEY_OPEN, 0560, sent by open key */
	_ky_options,		/* KEY_OPTIONS, 0561, sent by options key */
	_ky_previous,		/* KEY_PREVIOUS, 0562, sent by prevous object */
	_ky_print,		/* KEY_PRINT, 0532, sent by print or copy key */
	_ky_redo,		/* KEY_REDO, 0563, sent by redo key */
	_ky_reference,		/* KEY_REFERENCE, 0564, sent by ref(erence) key */
	_ky_refresh,		/* KEY_REFRESH, 0565, sent by refresh key */
	_ky_replace,		/* KEY_REPLACE, 0566, sent by replace key */
	_ky_restart,		/* KEY_RESTART, 0567, sent by restart key */
	_ky_resume,		/* KEY_RESUME, 0570, sent by resume key */
	_ky_save,		/* KEY_SAVE, 0571, sent by save key */
	_ky_sbeg,		/* KEY_SBEG, 0572, sent by shifted beginning key */
	_ky_scancel,		/* KEY_SCANCEL, 0573, sent by shifted cancel key */
	_ky_scommand,		/* KEY_SCOMMAND, 0574, sent by shifted */
	_ky_scopy,		/* KEY_SCOPY, 0575, sent by shifted copy key */
	_ky_screate,		/* KEY_SCREATE, 0576, sent by shifted create key */
	_ky_sdc,		/* KEY_SDC, 0577, sent by shifted delete-char key */
	_ky_sdl,		/* KEY_SDL, 0600, sent by shifted delete-line key */
	_ky_send,		/* KEY_SEND, 0602, sent by shifted end key */
	_ky_seol,		/* KEY_SEOL, 0603, sent by shifted clear-line key */
	_ky_sexit,		/* KEY_SEXIT, 0604, sent by shifted exit key */
	_ky_sfind,		/* KEY_SFIND, 0605, sent by shifted find key */
	_ky_shelp,		/* KEY_SHELP, 0606, sent by shifted help key */
	_ky_shome,		/* KEY_SHOME, 0607, sent by shifted home key */
	_ky_sic,		/* KEY_SIC, 0610, sent by shifted input key */
	_ky_sleft,		/* KEY_SLEFT, 0611, sent by shifted left-arrow */
	_ky_smessage,		/* KEY_SMESSAGE, 0612, sent by shifted message */
	_ky_smove,		/* KEY_SMOVE, 0613, sent by shifted move key */
	_ky_snext,		/* KEY_SNEXT, 0614, sent by shifted next key */
	_ky_soptions,		/* KEY_SOPTIONS, 0615, sent by shifted options */
	_ky_sprevious,		/* KEY_SPREVIOUS, 0616, sent by shifted prev */
	_ky_sprint,		/* KEY_SPRINT, 0617, sent by shifted print key */
	_ky_sredo,		/* KEY_SREDO, 0620, sent by shifted redo key */
	_ky_sreplace,		/* KEY_SREPLACE, 0621, sent by shifted replace */
	_ky_sright,		/* KEY_SRIGHT, 0622, sent by shifted */
	_ky_srsume,		/* KEY_SRSUME, 0623, sent by shifted resume */
	_ky_ssave,		/* KEY_SSAVE, 0624, sent by save key */
	_ky_ssuspend,		/* KEY_SSUSPEND, 0625, sent by shifted suspend */
	_ky_sundo,		/* KEY_SUNDO, 0626, sent by shifted undo key */
	_ky_suspend,		/* KEY_SUSPEND, 0627, sent by */
	_ky_undo,		/* KEY_UNDO, 0630, sent by undo key */
	_labl_format,		/* Label format */
	_labl_off,		/* Turn off soft labels */
	_labl_on,		/* Turn on soft labels */
	_micro_column_address,	/* Like _for micro */
	_micro_down,		/* Like curser_down for micro adjustment */
	_micro_left,		/* Like cursor_left for micro adjustment */
	_micro_right,		/* Like cursor_right for micro */
	_micro_row_address,	/* Like row_address micro adjustment */
	_micro_up,		/* Like cursor_up for micro adjustment */
	_mouse_info,		/* Mouse status information */
	_order_of_pins,		/* Matches software bits to print-head pins */
	_orig_colors,		/* Set all color(-pair)s to the original ones */
	_orig_pair,		/* Set default color-pair to the original one */
	_prm_down_micro,	/* Like parm_down_cursor for micro adjust. */
	_prm_left_micro,	/* Like parm_left_cursor for micro */
	_prm_right_micro,	/* Like parm_right_cursor for micro adjust. */
	_prm_up_micro,		/* Like parm_up_cursor for micro adjust. */
	_pc_term_options,	/* PC terminal options */
	_pkey_plab,		/* Prog key #1 to xmit string #2 and show string #3 */
	_plab_norm,		/* Prog label #1 to show string #2 */
	_pulse,			/* Select pulse dialing */
	_quick_dial,		/* Dial phone number #1, without progress detection */
	_req_for_input,		/* Send next input char (for ptys) */
	_req_mouse_pos,		/* Request mouse position report */
	_remove_clock,		/* Remove time-of-day clock */
	_scancode_escape,	/* Escape for scancode emulation */
	_select_char_set,	/* Select character set */
	_set0_des_seq,		/* Shift into codeset 0 (EUC set 0, ASCII) */
	_set1_des_seq,		/* Shift into codeset 1 */
	_set2_des_seq,		/* Shift into codeset 2 */
	_set3_des_seq,		/* Shift into codeset 3 */
	_set_a_background,	/* Set background color using ANSI escape */
	_set_a_foreground,	/* Set foreground color using ANSI escape */
	_set_background,	/* Set current background color */
	_set_bottom_margin,	/* Set bottom margin at current line */
	_set_bottom_margin_parm,	/* Set bottom margin at line #1 or #2 */
	_set_clock,		/* Set time-of-day clock */
	_set_color_band,	/* Change to ribbon color #1 */
	_set_color_pair,	/* Set current color-pair */
	_set_foreground,	/* Set current foreground color1 */
	_set_left_margin,	/* Set left margin at current line */
	_set_left_margin_parm,	/* Set left (right) margin at column #1 (#2) */
	_set_lr_margin,		/* Sets both left and right margins */
	_set_page_length,	/* Set page length to #1 lines (use tparm) */
	_set_right_margin,	/* Set right margin at current column */
	_set_right_margin_parm,	/* Set right margin at column #1 */
	_set_tb_margin,		/* Sets both top and bottom margins */
	_set_top_margin,	/* Set top margin at current line */
	_set_top_margin_parm,	/* Set top (bottom) margin at line #1 (#2) */
	_start_bit_image,	/* Start printing bit image graphics */
	_start_char_set_def,	/* Start definition of a character set */
	_stop_bit_image,	/* End printing bit image graphics */
	_stop_char_set_def,	/* End definition of a character set */
	_subscript_characters,	/* List of ``subscript-able'' characters */
	_superscript_characters, /* List of ``superscript-able'' characters */
	_these_cause_cr,	/* Printing any of these chars causes cr */
	_tone,			/* Select touch tone dialing */
	_user0,			/* User string 0 */
	_user1,			/* User string 1 */
	_user2,			/* User string 2 */
	_user3,			/* User string 3 */
	_user4,			/* User string 4 */
	_user5,			/* User string 5 */
	_user6,			/* User string 6 */
	_user7,			/* User string 7 */
	_user8,			/* User string 8 */
	_user9,			/* User string 9 */
	_wait_tone,		/* Wait for dial tone */
	_xoff_character,	/* X-off character */
	_xon_character,		/* X-on character */
	_zero_motion,		/* No motion for the subsequent character */
	_set_pglen_inch,	/* Set page length to #1 hundredth of an inch */
        _entr_horizontal_hl_mode,/* Turn on horizontal highlight mode */
        _entr_left_hl_mode,     /* Turn on left highlight mode */
        _entr_low_hl_mode,      /* Turn on low highlight mode */
        _entr_right_hl_mode,    /* Turn on right highlight mode */
        _entr_top_hl_mode,      /* Turn on top highlight mode */
        _entr_vertical_hl_mode, /* Turn on vertical highlight mode */
        _set_a_attributes,      /* Define second set of video attributes #1-#6 */
	Sentinel;		/* End of strings. DO NOT MOVE! */
};

struct _bool_struct {
    char
	_auto_left_margin,	/* cub1 wraps from column 0 to last column */
	_auto_right_margin,	/* Terminal has automatic margins */
	_no_esc_ctlc,		/* Beehive (f1=escape, f2=ctrl C) */
	_ceol_standout_glitch,	/* Standout not erased by overwriting (hp) */
	_eat_newline_glitch,	/* newline ignored after 80 cols (Concept) */
	_erase_overstrike,	/* Can erase overstrikes with a blank */
	_generic_type,		/* Generic line type (e.g. dialup, switch). */
	_hard_copy,		/* Hardcopy terminal */
	_has_meta_key,		/* Has a meta key (shift, sets parity bit) */
	_has_status_line,	/* Has extra "status line" */
	_ins_null_glitch,	/* Insert mode distinguishes nulls */
	_mem_above,		/* Display may be retained above the screen */
	_mem_below,		/* Display may be retained below the screen */
	_move_insert_mode,	/* Safe to move while in insert mode */
	_move_standout_mode,	/* Safe to move in standout modes */
	_over_strike,		/* Terminal overstrikes */
	_status_line_esc_ok,	/* Escape can be used on the status line */
	_dest_tabs_magic_smso,	/* Tabs destructive, magic so char (t1061) */
	_tilde_glitch,		/* Hazeltine; can't print ~'s */
	_transparent_underline,	/* underline character overstrikes */
	_xon_xoff,		/* Terminal uses xon/xoff handshaking */
	_back_color_erase,	/* Screen erased with background color */
	_can_change,		/* Terminal can re-define existing color */
	_col_addr_glitch,	/* Only positive motion for hpa/mhpa caps */
	_cpi_changes_res,	/* Changing character pitch changes resolution */
	_cr_cancels_micro_mode,	/* Using cr turns off micro mode */
	_hard_cursor,		/* Cursor is hard to see */
	_has_print_wheel,	/* Printer needs operator to change */
	_hue_lightness_saturation,	/* Terminal uses only HLS color notation (Tektronix) */
	_lpi_changes_res,	/* Changing line pitch changes resolution */
	_needs_xon_xoff,	/* Padding won't work, xon/xoff required */
	_non_dest_scroll_region,/* Scrolling region is non-destructive */
	_non_rev_rmcup,		/* smcup does not reverse rmcup */
	_no_pad_char,		/* Pad character doesn't exist */
	_prtr_silent,		/* Printer won't echo on screen */
	_row_addr_glitch,	/* Only positive motion for rpa/mvpa caps */
	_semi_auto_right_margin,	/* Printing in last column causes cr */
	Sentinel;		/* End of bools. DO NOT MOVE! */
};

struct _num_struct {
    short
	_columns,		/* Number of columns in a line */
	_init_tabs,		/* Tabs initially every # spaces. */
	_lines,			/* Number of lines on screen or page */
	_lines_of_memory,	/* Lines of memory if > lines.  0 => varies */
	_magic_cookie_glitch,	/* Number blank chars left by smso or rmso */
	_padding_baud_rate,	/* Lowest baud rate where padding needed */
	_virtual_terminal,	/* Virtual terminal number (CB/Unix) */
	_width_status_line,	/* # columns in status line */
	_bit_image_entwining,	/* Number of passes for each bit-image row */
	_bit_image_type,	/* Type of bit-image device */
	_buffer_capacity,	/* Number of bytes buffered before printing */
	_buttons,		/* Number of buttons on the mouse */
	_dot_vert_spacing,	/* Spacing of pins vertically in pins per inch */
	_dot_horz_spacing,	/* Spacing of dots horizontally in dots per inch */
	_labl_height,		/* Number of rows in each label */
	_labl_width,		/* Number of columns in each label */
	_max_attributes,	/* Max combined video attributes terminal can display */
	_max_colors,		/* Maximum number of colors on the screen */
	_max_micro_address,	/* Maximum value in micro_..._address */
	_max_micro_jump,	/* Maximum value in parm_..._micro */
	_max_pairs,		/* Maximum number of color-pairs on the screen */
	_maximum_windows,	/* Maximum number of defineable windows */
	_micro_col_size,	/* Character step size when in micro mode */
	_micro_line_size,	/* Line step size when in micro mode */
	_no_color_video,	/* Video attributes that can't be used */
	_number_of_pins,	/* Number of pins in print-head */
	_num_labels,		/* Number of labels on screen (start at 1) */
	_output_res_char,	/* Horizontal resolution in units per character */
	_output_res_line,	/* Vertical resolution in units per line */
	_output_res_horz_inch,	/* Horizontal resolution in units per inch */
	_output_res_vert_inch,	/* Vertical resolution in units per inch */
	_print_rate,		/* Print rate in characters per second */
	_wide_char_size,	/* Character step size when in double */
	Sentinel;		/* End of nums. DO NOT MOVE! */
};

struct _str_struct {
	struct strs strs;
	struct strs2 strs2;
	struct strs3 strs3;
	struct strs4 strs4;
};

#define NUM_ATTRIBUTES		9
#define WNUM_ATTRIBUTES		15
#define	UNACCESSIBLE		1
#define	NO_TERMINAL		2
#define CORRUPTED		3
#define	ENTRY_TOO_LONG		4
#define	TERMINFO_TOO_LONG	5
#define	TERM_BAD_MALLOC		6
#define NOT_READABLE		7
#define	TERM_DBG_BAD_MALLOC	8

#define TERM_ERR_SET		2

typedef struct {
	char *_sends;	/* Characters sent when key is pressed */
	short _keyval;	/* "char" we pass back to program */
} _KEY_MAP;

typedef struct {
	short  foreground;   /* foreground color */
	short  background;   /* background color */
	bool   init;         /* TRUE if pair was initialized */
} _Color_pair;


typedef struct {
	short	r, g, b;
} _Color;


struct term {
	short Filedes;		/* file descriptor being written to */
	struct termios Ottyb;	/* original state of the terminal */
	struct termios Nttyb;	/* current state of the terminal */
#ifdef DIOCSETT
#ifdef __cplusplus
	struct termcb new_term, old_term;       /* CB/UNIX virtual terminals */
#else
	struct termcb new, old; /* CB/UNIX virtual terminals */
#endif /* __cplusplus */
#endif /* DIOCSETT */
#ifdef LTILDE
	int newlmode, oldlmode;	/* BSD tty driver */
#endif
	struct _bool_struct *_bools;
	struct _num_struct *_nums;
	struct _str_struct *_strs;
	char *_strtab;
#ifdef FIONREAD
	long timeout;		/* for BSD halfdelay mode */
#endif
	attr_t sgr_mode;		/* current phys. graphic rendition */
	attr_t sgr_faked;		/* attributes faked by vidputs */
	int    _delay;			/* timeout for inputs */
	int    _inputfd;		/* input file descriptor */
	int    _check_fd;		/* typeahead file descriptor */
	_KEY_MAP	**_keys,	/* key map */
			*internal_keys;	/* pointer to free key structures */
	short		_ksz,		/* size of keymap */
			_lastkey_ordered,/* where the last ordered key is */
			_lastmacro_ordered,/* where the last ordered macro is */
			_first_macro;
	bool				/* map of which chars start fn keys */
			funckeystarter[0400];	
	bool		_fl_rawmode,	/* in cbreak(=1) or raw(=2) mode */
			fl_typeahdok,	/* ok to use typeahead */
			_cursorstate,	/* cursor: 0=invis, 1=norm, 2=vvis */
			_iwait;		/* true if input-pending */
	short		_regs[26];	/* tparm static registers */
#define INP_QSIZE	32
	int				/* a place to put stuff ungetch'ed */
			_input_queue[INP_QSIZE];
	short		_ungotten;	/* # chars ungotten by ungetch() */
	char		_chars_on_queue; /* # chars on queue */
	cchar_t		*_acsmap;	/* map of alternate char set chars */
	char		*turn_on_seq[WNUM_ATTRIBUTES];
	attr_t		bit_vector;
	char		*cursor_seq[3];
	char		_termname[15];
	char		*turn_off_seq[3];
	attr_t		check_turn_off;
    	_Color_pair	_cur_pair;
    	_Color_pair	*_pairs_tbl;
    	_Color		*_color_tbl;
};

typedef struct term TERMINAL;

/* allow old names for these capabilities */
#define beehive_glitch	no_esc_ctlc
#define teleray_glitch	dest_tabs_magic_smso
#define micro_char_size micro_col_size

extern TERMINAL			*cur_term;
extern struct _bool_struct	*cur_bools;
extern struct _num_struct	*cur_nums;
extern struct _str_struct	*cur_strs;

#ifdef _SINGLE
extern TERMINAL			_first_term;
extern struct _bool_struct	_frst_bools;
extern struct _num_struct	_frst_nums;
extern struct _str_struct	_frst_strs;

# define CUR			_first_term.
# define CURB			_frst_bools.
# define CURN			_frst_nums.
# define CURS			_frst_strs.
# define PROGTTY		_first_term.Nttyb
# define SHELLTTY		_first_term.Ottyb
#else /* _SINGLE */
# define CUR			cur_term->
# define CURB			cur_bools->
# define CURN			cur_nums->
# define CURS			cur_strs->
# define PROGTTY		(cur_term->Nttyb)
# define SHELLTTY		(cur_term->Ottyb)
#endif /* _SINGLE */

extern	char	*Def_term, *boolnames[], *boolcodes[], *boolfnames[],
		*numnames[], *numcodes[], *numfnames[],
		*strnames[], *strcodes[], *strfnames[];

/* These interfaces are required by X/Open Curses, Issue 4 */

extern int     	del_curterm __((TERMINAL *));
extern int	putp __((const char *));
extern int     	restartterm __((char *, int, int *));
extern TERMINAL	*set_curterm __((TERMINAL *));
extern int	setupterm __((char *, int, int *));
extern int	tgetent __((char *, const char *));
extern int	tgetflag __((char *));
extern int	tgetnum __((char *));
extern char    	*tgetstr __((char *, char **));
extern char	*tgoto __((const char *, int, int));
extern int     	tigetflag __((char *));
extern int	tigetnum __((char *));
extern char    	*tigetstr __((char *));
extern char	*tparm __((char *, ...));
extern int     	tputs __((const char *, int, int (*)(int)));

/* These are additional support interfaces */

extern int      fixterm __((void));
extern int	delterm __((TERMINAL *));
extern int      saveterm __((void));
extern TERMINAL	*setcurterm __((TERMINAL *));
extern void	termerr __((void));
extern void	tinputfd __((int));

#ifdef __cplusplus
}
#endif

#endif /* _TERM_H_ */
