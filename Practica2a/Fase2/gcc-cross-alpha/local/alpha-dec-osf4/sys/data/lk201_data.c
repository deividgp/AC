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
 *	@(#)$RCSfile: lk201_data.c,v $ $Revision: 1.2.16.2 $ (DEC) $Date: 1998/06/26 19:20:58 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/************************************************************************
 *									*
 *			Copyright (c) 1990 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any	other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or	reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

#include <sys/types.h>
#include <kern/queue.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <sys/keysyms.h>

#include <io/dec/ws/lk201.h>

#define KEYCODE_BIAS	0x50	/* to save xlate table space */

#ifdef BINARY

extern ws_keyboard_state	lk201_softc[];
extern ws_keyboard		lk201_keyboard;
extern unsigned char		lk201_keycodes[];
extern unsigned int		lk201_keysyms[];
extern ws_keycode_modifiers	lk201_modifiers[];
extern ws_keyboard_definition	lk201_definition;
extern ws_keycode_modifiers	lk443_modifiers[];
extern ws_keyboard_definition	lk443_definition;

extern xlate_t lk201_xlate[];
extern xkey_t *lk201_altgr;

extern xkey_t *lk201_diffs[];
extern xkey_t *lk201_altgrs[];

extern xkey_t  lk201_to_lk401_diffs[];
extern xkey_t *lk401_diffs[];
extern xkey_t *lk401_altgrs[];

extern xkey_t  lk201_to_lk421_diffs[];
extern xkey_t *lk421_diffs[];
extern xkey_t *lk421_altgrs[];

extern xkey_t  lk201_to_lk443_diffs[];
extern xkey_t *lk443_diffs[];
extern xkey_t *lk443_altgrs[];

extern char lk201_name[];
extern char lk401_name[];
extern char lk421_name[];
extern char lk443_name[];


#else /* BINARY */

/*
 * Note that if a keycode appears additional times, it defines further
 * symbols on the same keycode.  DDX translates this to the appropriate
 * data structure.  All this is to save bytes in the kernel.
 * WARNING: keycodes and keysym tables must be EXACTLY in sync!
 */
unsigned char lk201_keycodes[] = {
    KEY_443_ESC,	/* added for LK443/LK444 */
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_ESC,		/* escape is primary, due to previous stupidity...*/
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,

    KEY_HELP,
    KEY_MENU,

    KEY_F17,
    KEY_F18,
    KEY_F19,
    KEY_F20,

    KEY_FIND,
    KEY_INSERT_HERE,
    KEY_REMOVE,
    KEY_SELECT,
    KEY_PREV_SCREEN,
    KEY_NEXT_SCREEN,

    KEY_KP_0,
    KEY_KP_PERIOD,
    KEY_KP_ENTER,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_COMMA,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_HYPHEN,
    KEY_KP_PF1,
    KEY_KP_PF2,
    KEY_KP_PF3,
    KEY_KP_PF4,

    KEY_LEFT,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_UP,

    KEY_SHIFT,
    KEY_SHIFT_R,
    KEY_CTRL,
    KEY_LOCK,
    KEY_COMPOSE,
    KEY_COMPOSE_R,
    KEY_ALT_L,
    KEY_ALT_L,
    KEY_ALT_R,
    KEY_ALT_R,
    KEY_DELETE,
    KEY_RETURN,
    KEY_TAB,

    KEY_TILDE,
    KEY_TILDE,

    KEY_TR_1,
    KEY_TR_1,
    KEY_Q,
    KEY_A,
    KEY_Z,

    KEY_TR_2,
    KEY_TR_2,

    KEY_W,
    KEY_S,
    KEY_X,

    KEY_LANGLE_RANGLE,
    KEY_LANGLE_RANGLE,

    KEY_TR_3,
    KEY_TR_3,

    KEY_E,
    KEY_D,
    KEY_C,

    KEY_TR_4,
    KEY_TR_4,

    KEY_R,
    KEY_F,
    KEY_V,
    KEY_SPACE,

    KEY_TR_5,
    KEY_TR_5,

    KEY_T,
    KEY_G,
    KEY_B,

    KEY_TR_6,
    KEY_TR_6,

    KEY_Y,
    KEY_H,
    KEY_N,

    KEY_TR_7,
    KEY_TR_7,

    KEY_U,
    KEY_J,
    KEY_M,

    KEY_TR_8,
    KEY_TR_8,

    KEY_I,
    KEY_K,

    KEY_COMMA,
    KEY_COMMA,

    KEY_TR_9,
    KEY_TR_9,

    KEY_O,
    KEY_L,

    KEY_PERIOD,
    KEY_PERIOD,

    KEY_TR_0,
    KEY_TR_0,

    KEY_P,

    KEY_SEMICOLON,
    KEY_SEMICOLON,

    KEY_QMARK,
    KEY_QMARK,

    KEY_PLUS,
    KEY_PLUS,

    KEY_RBRACE,
    KEY_RBRACE,

    KEY_VBAR,
    KEY_VBAR,

    KEY_UBAR,
    KEY_UBAR,

    KEY_LBRACE,
    KEY_LBRACE,

    KEY_QUOTE,
    KEY_QUOTE,

};

unsigned int lk201_keysyms[] = {
    XK_Escape,
    XK_F1,
    XK_F2,
    XK_F3,
    XK_F4,
    XK_F5,
    XK_F6,
    XK_F7,
    XK_F8,
    XK_F9,
    XK_F10,
    XK_Escape,
    XK_F11,
    XK_F12,
    XK_F13,
    XK_F14,

    XK_Help,
    XK_Menu,

    XK_F17,
    XK_F18,
    XK_F19,
    XK_F20,

    XK_Find,
    XK_Insert,
    DXK_Remove,
    XK_Select,
    XK_Prior,
    XK_Next,

    XK_KP_0,
    XK_KP_Decimal,
    XK_KP_Enter,
    XK_KP_1,
    XK_KP_2,
    XK_KP_3,
    XK_KP_4,
    XK_KP_5,
    XK_KP_6,
    XK_KP_Separator,
    XK_KP_7,
    XK_KP_8,
    XK_KP_9,
    XK_KP_Subtract,
    XK_KP_F1,
    XK_KP_F2,
    XK_KP_F3,
    XK_KP_F4,

    XK_Left,
    XK_Right,
    XK_Down,
    XK_Up,

    XK_Shift_L,
    XK_Shift_R,
    XK_Control_L,
    XK_Caps_Lock,
    XK_Multi_key,
    XK_Multi_key,
    XK_Alt_L,
    XK_Meta_L,
    XK_Alt_R,
    XK_Meta_R,
    XK_Delete,
    XK_Return,
    XK_Tab,

    XK_quoteleft,
    XK_asciitilde,

    XK_1,
    XK_exclam,
    XK_Q,
    XK_A,
    XK_Z,

    XK_2,
    XK_at,

    XK_W,
    XK_S,
    XK_X,

    XK_less,
    XK_greater,

    XK_3,
    XK_numbersign,

    XK_E,
    XK_D,
    XK_C,

    XK_4,
    XK_dollar,

    XK_R,
    XK_F,
    XK_V,
    XK_space,

    XK_5,
    XK_percent,

    XK_T,
    XK_G,
    XK_B,

    XK_6,
    XK_asciicircum,

    XK_Y,
    XK_H,
    XK_N,

    XK_7,
    XK_ampersand,

    XK_U,
    XK_J,
    XK_M,

    XK_8,
    XK_asterisk,

    XK_I,
    XK_K,

    XK_comma,
    XK_less,

    XK_9,
    XK_parenleft,

    XK_O,
    XK_L,

    XK_period,
    XK_greater,

    XK_0,
    XK_parenright,

    XK_P,

    XK_semicolon,
    XK_colon,

    XK_slash,
    XK_question,

    XK_equal,
    XK_plus,

    XK_bracketright,
    XK_braceright,

    XK_backslash,
    XK_bar,

    XK_minus,
    XK_underscore,

    XK_bracketleft,
    XK_braceleft,

    XK_quoteright,
    XK_quotedbl,

};

/* 
 * derived from qfont.c	2.2	(ULTRIX/OSF)	12/4/90;
 */

/*
 * The following tables are used to translate LK201 key strokes
 * into ascii characters. The tables also support the special
 * keys, by providing a flag indicating when use of "special_keys"
 * table (data/ws_data.c) is necessary.
 */

/*
 * holds a pointer to the ALT-GR table for the current keyboard/language
 */
xkey_t *lk201_altgr = (xkey_t *)NULL;

/* NOTE: table starts at index 0x50, so algorithm must adjust charcode */

xlate_t lk201_xlate[] = {
 { 	0,	0	},	/* 0x50, UNUSED 	*/
 { 	0,	0	},	/* 0x51, UNUSED 	*/
 { 	0,	0	},	/* 0x52, UNUSED 	*/
 { 	0,	0	},	/* 0x53, UNUSED 	*/
 { 	0,	0	},	/* 0x54, UNUSED 	*/
 { 	033,	033	},	/* 0x55, ESCAPE		*//* LK443 */
 { 	F1,	F1	},	/* 0x56, F1		*/
 { 	F2,	F2	},	/* 0x57, F2		*/
 { 	F3,	F3	},	/* 0x58, F3		*/
 { 	F4,	F4	},	/* 0x59, F4		*/
 { 	F5,	F5	},	/* 0x5a, F5		*/
 { 	0,	0	},	/* 0x5b, UNUSED 	*/
 { 	0,	0	},	/* 0x5c, UNUSED 	*/
 { 	0,	0	},	/* 0x5d, UNUSED 	*/
 { 	0,	0	},	/* 0x5e, UNUSED 	*/
 { 	0,	0	},	/* 0x5f, UNUSED 	*/
 { 	0,	0	},	/* 0x60, UNUSED 	*/
 { 	0,	0	},	/* 0x61, UNUSED 	*/
 { 	0,	0	},	/* 0x62, UNUSED 	*/
 { 	0,	0	},	/* 0x63, UNUSED 	*/
 { 	F6,	F6	},	/* 0x64, F7 		*/
 { 	F7,	F7	},	/* 0x65, F8 		*/
 { 	F8,	F8	},	/* 0x66, F9 		*/
 { 	F9,	F9	},	/* 0x67, F10	 	*/
 { 	F10,	F10	},	/* 0x68, UNUSED 	*/
 { 	0,	0	},	/* 0x69, UNUSED 	*/
 { 	0,	0	},	/* 0x6a, UNUSED 	*/
 { 	0,	0	},	/* 0x6b, UNUSED 	*/
 { 	0,	0	},	/* 0x6c, UNUSED 	*/
 { 	0,	0	},	/* 0x6d, UNUSED 	*/
 { 	0,	0	},	/* 0x6e, UNUSED 	*/
 { 	0,	0	},	/* 0x6f, UNUSED 	*/
 { 	0,	0	},	/* 0x70, UNUSED 	*/
 { 	LK_F11,	LK_F11	},	/* 0x71, F11 (ESC)	*/
 { 	LK_F12,	LK_F12	},	/* 0x72, F12 (BS)	*/
 { 	LK_F13,	LK_F13	},	/* 0x73, F13 (LF)	*/
 { 	F14,	F14	},	/* 0x74, F14		*/
 { 	0,	0	},	/* 0x75, UNUSED 	*/
 { 	0,	0	},	/* 0x76, UNUSED 	*/
 { 	0,	0	},	/* 0x77, UNUSED 	*/
 { 	0,	0	},	/* 0x78, UNUSED 	*/
 { 	0,	0	},	/* 0x79, UNUSED 	*/
 { 	0,	0	},	/* 0x7a, UNUSED 	*/
 { 	0,	0	},	/* 0x7b, UNUSED 	*/
 { 	HELP,	HELP	},	/* 0x7c, HELP (F15) 	*/
 { 	DO,	DO	},	/* 0x7d, DO (F16) 	*/
 { 	0,	0	},	/* 0x7e, UNUSED 	*/
 { 	0,	0	},	/* 0x7f, UNUSED 	*/
 { 	F17,	F17	},	/* 0x80, F17		*/
 { 	F18,	F18	},	/* 0x81, F18		*/
 { 	F19,	F19	},	/* 0x82, F19		*/
 { 	F20,	F20	},	/* 0x83, F20		*/
 { 	0,	0	},	/* 0x84, UNUSED 	*/
 { 	0,	0	},	/* 0x85, UNUSED 	*/
 { 	0,	0	},	/* 0x86, UNUSED 	*/
 { 	0,	0	},	/* 0x87, UNUSED 	*/
 { 	0,	0	},	/* 0x88, UNUSED 	*/
 { 	0,	0	},	/* 0x89, UNUSED 	*/
 { 	FIND,	FIND	},	/* 0x8a, FIND		*/
 { 	INS,	INS	},	/* 0x8b, INSERT		*/
 { 	REMOVE,	REMOVE	},	/* 0x8c, REMOVE		*/
 { 	SELECT,	SELECT	},	/* 0x8d, SELECT		*/
 { 	PREV,	PREV	},	/* 0x8e, PREV		*/
 { 	NEXT,	NEXT	},	/* 0x8f, NEXT		*/
 { 	0,	0	},	/* 0x90, UNUSED 	*/
 { 	0,	0	},	/* 0x91, UNUSED 	*/
 { 	KP_0,	KP_0	},	/* 0x92, KP 0	 	*/
 { 	0,	0	},	/* 0x93, UNUSED 	*/
 { 	KP_PERIOD, KP_PERIOD},	/* 0x94, KP .	 	*/
 { 	KP_ENTER,  KP_ENTER},	/* 0x95, KP ENTER 	*/
 { 	KP_1,	KP_1	},	/* 0x96, KP 1	 	*/
 { 	KP_2,	KP_2	},	/* 0x97, KP 2	 	*/
 { 	KP_3,	KP_3	},	/* 0x98, KP 3	 	*/
 { 	KP_4,	KP_4	},	/* 0x99, KP 4	 	*/
 { 	KP_5,	KP_5	},	/* 0x9a, KP 5	 	*/
 { 	KP_6,	KP_6	},	/* 0x9b, KP 6	 	*/
 { 	KP_COMMA,  KP_COMMA},	/* 0x9c, KP ,	 	*/
 { 	KP_7,	KP_7	},	/* 0x9d, KP 7	 	*/
 { 	KP_8,	KP_8	},	/* 0x9d, KP 8	 	*/
 { 	KP_9,	KP_9	},	/* 0x9f, KP 9	 	*/
 { 	KP_MINUS,  KP_MINUS},	/* 0xa0, KP -	 	*/
 { 	KP_PF1,	KP_PF1	},	/* 0xa1, KP PF1	 	*/
 { 	KP_PF2,	KP_PF2	},	/* 0xa2, KP PF2	 	*/
 { 	KP_PF3,	KP_PF3	},	/* 0xa3, KP PF3	 	*/
 { 	KP_PF4,	KP_PF4	},	/* 0xa4, KP PF4	 	*/
 { 	0,	0	},	/* 0xa5, UNUSED 	*/
 { 	0,	0	},	/* 0xa6, UNUSED 	*/
 { 	LEFT,	LEFT	},	/* 0xa7, LEFT	 	*/
 { 	RIGHT,	RIGHT	},	/* 0xa8, RIGHT	 	*/
 { 	DOWN,	DOWN	},	/* 0xa9, DOWN	 	*/
 { 	UP,	UP	},	/* 0xaa, UP	 	*/
 { 	MOD_SHFT_R, 0	},	/* 0xab, SHIFT_R 	*/
 { 	MOD_ALT_L,  0	},	/* 0xac, ALT_L	 	*//* LK401 only */
 { 	MOD_COMP_R, 0	},	/* 0xad, COMP_R	 	*//* LK401 only*/
 { 	MOD_SHFT_L, 0	},	/* 0xae, SHIFT_L 	*/
 { 	MOD_CTRL_L, 0	},	/* 0xaf, CTRL_L	 	*/
 { 	MOD_CAPS,   0	},	/* 0xb0, CAPS	 	*/
 { 	MOD_ALT_L, 0	},	/* 0xb1, ALT_L	 	*//* LK201 base */
 { 	MOD_ALT_R,  0	},	/* 0xb2, ALT_R	 	*//* LK401 only */
 { 	0,	0	},	/* 0xb3, ALLUP	 	*/
 { 	0,	0	},	/* 0xb4, REPEAT 	*/
 { 	0,	0	},	/* 0xb5, UNUSED 	*/
 { 	0,	0	},	/* 0xb6, UNUSED 	*/
 { 	0,	0	},	/* 0xb7, UNUSED 	*/
 { 	0,	0	},	/* 0xb8, UNUSED 	*/
 { 	0,	0	},	/* 0xb9, UNUSED 	*/
 { 	0,	0	},	/* 0xba, UNUSED 	*/
 { 	0,	0	},	/* 0xbb, UNUSED 	*/
 { 	DELE,	DELE	},	/* 0xbc, DELETE 	*/
 { 	'\r',	'\r'	},	/* 0xbd, RETURN 	*/
 { 	0x09,	0x09	},	/* 0xbe, TAB	 	*/
 { 	'`',	'~'	},	/* 0xbf, '`', '~' 	*/
 { 	'1',	'!'	},	/* 0xc0, 	 	*/
 { 	'q',	'Q'	},	/* 0xc1, 		*/
 { 	'a',	'A'	},	/* 0xc2, 		*/
 { 	'z',	'Z'	},	/* 0xc3, 		*/
 { 	0,	0	},	/* 0xc4, UNUSED 	*/
 { 	'2',	'@'	},	/* 0xc5, 		*/
 { 	'w',	'W'	},	/* 0xc6, 		*/
 { 	's',	'S'	},	/* 0xc7, 		*/
 { 	'x',	'X'	},	/* 0xc8, 		*/
 { 	'<',	'>'	},	/* 0xc9, 		*/
 { 	0,	0	},	/* 0xca, UNUSED 	*/
 { 	'3',	'#'	},	/* 0xcb, 		*/
 { 	'e',	'E'	},	/* 0xcc, 		*/
 { 	'd',	'D'	},	/* 0xcd, 		*/
 { 	'c',	'C'	},	/* 0xce, 		*/
 { 	0,	0	},	/* 0xcf, UNUSED 	*/
 { 	'4',	'$'	},	/* 0xd0, 		*/
 { 	'r',	'R'	},	/* 0xd1, 		*/
 { 	'f',	'F'	},	/* 0xd2, 		*/
 { 	'v',	'V'	},	/* 0xd3, 		*/
 { 	' ',	' '	},	/* 0xd4, 		*/
 { 	0,	0	},	/* 0xd5, UNUSED 	*/
 { 	'5',	'%'	},	/* 0xd6, 	 	*/
 { 	't',	'T'	},	/* 0xd7, 		*/
 { 	'g',	'G'	},	/* 0xd8, 		*/
 { 	'b',	'B'	},	/* 0xd9, 		*/
 { 	0,	0	},	/* 0xda, UNUSED 	*/
 { 	'6',	'^'	},	/* 0xdb, 		*/
 { 	'y',	'Y'	},	/* 0xdc, 		*/
 { 	'h',	'H'	},	/* 0xdd, 		*/
 { 	'n',	'N'	},	/* 0xde, 		*/
 { 	0,	0	},	/* 0xdf, UNUSED 	*/
 { 	'7',	'&'	},	/* 0xe0, 		*/
 { 	'u',	'U'	},	/* 0xe1, 		*/
 { 	'j',	'J'	},	/* 0xe2, 		*/
 { 	'm',	'M'	},	/* 0xe3, 		*/
 { 	0,	0	},	/* 0xe4, UNUSED 	*/
 { 	'8',	'*'	},	/* 0xe5, 		*/
 { 	'i',	'I'	},	/* 0xe6, 		*/
 { 	'k',	'K'	},	/* 0xe7, 		*/
 { 	',',	','	},	/* 0xe8, 		*//* LK201 base */
 { 	0,	0	},	/* 0xe9, UNUSED 	*/
 { 	'9',	'('	},	/* 0xea, 		*/
 { 	'o',	'O'	},	/* 0xeb, 		*/
 { 	'l',	'L'	},	/* 0xec, 		*/
 { 	'.',	'.'	},	/* 0xed, 		*//* LK201 base */
 { 	0,	0	},	/* 0xee, UNUSED		*/
 { 	'0',	')'	},	/* 0xef, 		*/
 { 	'p',	'P'	},	/* 0xf0, 		*/
 { 	0,	0	},	/* 0xf1, UNUSED 	*/
 { 	';',	':'	},	/* 0xf2, 	 	*/
 { 	'/',	'?'	},	/* 0xf3, 		*/
 { 	0,	0	},	/* 0xf4, UNUSED 	*/
 { 	'=',	'+'	},	/* 0xf5, 		*/
 { 	']',	'}'	},	/* 0xf6, 		*/
 { 	'\\',	'|'	},	/* 0xf7, 		*/
 { 	0,	0	},	/* 0xf8, UNUSED 	*/
 { 	'-',	'_'	},	/* 0xf9, 		*/
 { 	'[',	'{'	},	/* 0xfa, 		*/
 { 	'\'',	0x22	},	/* 0xfb, 		*/
 { 	0,	0	},	/* 0xfc, UNUSED 	*/
 { 	0,	0	},	/* 0xfd, UNUSED 	*/
 { 	0,	0	},	/* 0xfe, UNUSED 	*/
 { 	0,	0	}	/* 0xff, UNUSED 	*/
};

/************************************************************************
 * here are all the tables related to the LK201 keyboard series
 */

/*
 * the following tables hold the differences between the given keyboard
 *  and the default keyboard (LK201 US)
 *
 * NOTE: when there were 2 keymaps for a given language, a DP and a TW,
 *  the DP version was chosen as being more appropriate (data processing :-).
 *
 * NOTE: when there were 2 flavors of LK201 for a given language, such as
 *  "austrian_german_lk201lg" and "austrian_german_lk201ng", the keymap
 *  chosen was the one which had a "bar" character (ie '|'), for no other
 *  reason except that it would be useful as the shell "pipe" symbol.
 *
 * NOTE: there are no ALT-GR tables, as there is no analogous key here.
 */

xkey_t danish_lk201rd_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x0040 }, /* '~', , '@'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007b,		0x005b }, /* '{', , '['	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x0027,		0x0060 }, /* ''', , '`'	*/
 { 0x00f6,	0x0022,		0x005e }, /* '"', , '^'	*/
 { 0x00f7,	0x0027,		0x002a }, /* ''', , '*'	*/
 { 0x00f9,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x00fa,	0x007d,		0x005d }, /* '}', , ']'	*/
 { 0x00fb,	0x007c,		0x005c }, /* '|', , '\'	*/
 { -1, 0, 0 }
};

xkey_t austrian_german_lk201ng_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x005e }, /* '~', , '^'	*/
 { 0x00c3,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x00a7 }, /* '3', , section	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00dc,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007d,		0x007b }, /* '}', , '{'	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x0027,		0x0060 }, /* ''', , '`'	*/
 { 0x00f6,	0x002b,		0x002a }, /* '+', , '*'	*/
 { 0x00f7,	0x0023,		0x0027 }, /* '#', , '''	*/
 { 0x00f9,	0x007c,		0x003f }, /* '|', , '?'	*/
 { 0x00fa,	0x0040,		0x005c }, /* '@', , '\'	*/
 { 0x00fb,	0x005d,		0x005b }, /* ']', , '['	*/
 { -1, 0, 0 }
};

xkey_t swiss_german_lk201ll_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0021,		0x00b0 }, /* '!', , degree	*/
 { 0x00c0,	0x0031,		0x002b }, /* '1', , '+'	*/
 { 0x00c3,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x002a }, /* '3', , '*'	*/
 { 0x00d0,	0x0034,		0x0040 }, /* '4', , '@'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00dc,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x00f6,		0x005b }, /* odiaeresis, '['	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f7,	0x0024,		0x0023 }, /* '$', , '#'	*/
 { 0x00f9,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x00fa,	0x00fc,		0x005c }, /* udiaeresis, '\'	*/
 { 0x00fb,	0x00e4,		0x005d }, /* adiaeresis, ']'	*/
 { -1, 0, 0 }
};

xkey_t uk_lk201re_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00cb,	0x0033,		0x00a3 }, /* '3', , sterling	*/
 { -1, 0, 0 }
};

xkey_t spanish_lk201ls_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0040,		0x005c }, /* '@', , '\'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x00f1,		0x00d1 }, /* ntilde, ,Ntilde	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x005d,		0x005b }, /* ']', , '['	*/
 { 0x00f6,	0x002b,		0x002a }, /* '+', , '*'	*/
 { 0x00f7,	0x00e7,		0x00c7 }, /* ccedilla, Ccedilla	*/
 { 0x00f9,	0x0027,		0x003f }, /* ''', , '?'	*/
 { -1, 0, 0 }
};

xkey_t belgian_french_lk201lp_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x0026,		0x0031 }, /* '&', , '1'	*/
 { 0x00c1,	0x0061,		0x0041 }, /* 'a', , 'A'	*/
 { 0x00c2,	0x0071,		0x0051 }, /* 'q', , 'Q'	*/
 { 0x00c3,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x00c5,	0x00e9,		0x0032 }, /* eacute, '2'	*/
 { 0x00c6,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00cb,	0x0022,		0x0033 }, /* '"', , '3'	*/
 { 0x00d0,	0x0027,		0x0034 }, /* ''', , '4'	*/
 { 0x00d6,	0x0028,		0x0035 }, /* '(', , '5'	*/
 { 0x00db,	0x005b,		0x0036 }, /* '[', , '6'	*/
 { 0x00e0,	0x005d,		0x0037 }, /* ']', , '7'	*/
 { 0x00e3,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x00e5,	0x0021,		0x0038 }, /* '!', , '8'	*/
 { 0x00e8,	0x003b,		0x002e }, /* ';', , '.'	*/
 { 0x00ea,	0x00e7,		0x0039 }, /* ccedilla, '9'	*/
 { 0x00ed,	0x003a,		0x002f }, /* ':', , '/'	*/
 { 0x00ef,	0x00e0,		0x0030 }, /* agrave, '0'	*/
 { 0x00f2,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x00f3,	0x003d,		0x002b }, /* '=', , '+'	*/
 { 0x00f5,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f6,	0x0024,		0x002a }, /* '$', , '*'	*/
 { 0x00f7,	0x0023,		0x0040 }, /* '#', , '@'	*/
 { 0x00f9,	0x0029,		0x00b0 }, /* ')', , degree	*/
 { 0x00fb,	0x005c,		0x0025 }, /* '\', , '%'	*/
 { -1, 0, 0 }
};

xkey_t canadian_french_lk201lc_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	'~',		0x00b0 }, /* '~', , degree	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x002f }, /* '3', , '/'	*/
 { 0x00db,	0x0036,		0x003f }, /* '6', , '?'	*/
 { 0x00e8,	0x002c,		0x0027 }, /* ',', , '''	*/
 { 0x00f3,	0x00e9,		0x00c9 }, /* eacute, , Eacute	*/
 { 0x00f6,	0x0023,		0x0040 }, /* '#', , '@'	*/
 { 0x00fa,	0x005d,		0x005b }, /* ']', , '['	*/
 { -1, 0, 0 }
};

xkey_t swiss_french_lk201lk_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0021,		0x00b0 }, /* '!', , degree	*/
 { 0x00c0,	0x0031,		0x002b }, /* '1', , '+'	*/
 { 0x00c3,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x002a }, /* '3', , '*'	*/
 { 0x00d0,	0x0034,		0x0040 }, /* '4', , '@'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00dc,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x00e9,		0x005b }, /* eacute, '['	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f7,	0x0024,		0x0023 }, /* '$', , '#'	*/
 { 0x00f9,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x00fa,	0x00e8,		0x005c }, /* egrave, '\'	*/
 { 0x00fb,	0x00e0,		0x005d }, /* agrave, ']'	*/
 { -1, 0, 0 }
};

xkey_t italian_lk201li_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x0040,		0x0031 }, /* '@', , '1'	*/
 { 0x00c3,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x00c5,	0x0023,		0x0032 }, /* '#', , '2'	*/
 { 0x00c6,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00cb,	0x0022,		0x0033 }, /* '"', , '3'	*/
 { 0x00d0,	0x0027,		0x0034 }, /* ''', , '4'	*/
 { 0x00d6,	0x0028,		0x0035 }, /* '(', , '5'	*/
 { 0x00db,	0x005f,		0x0036 }, /* '_', , '6'	*/
 { 0x00e0,	0x00e8,		0x0037 }, /* egrave, '7'	*/
 { 0x00e3,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x00e5,	'^',		'8'    }, /* '^', , '8'	*/
 { 0x00e8,	0x003b,		0x002e }, /* ';', , '.'	*/
 { 0x00ea,	0x005b,		0x0039 }, /* '[', , '9'	*/
 { 0x00ed,	0x003a,		0x002f }, /* ':', , '/'	*/
 { 0x00ef,	0x005d,		0x0030 }, /* ']', , '0'	*/
 { 0x00f2,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x00f3,	0x00f2,		0x0021 }, /* ograve, '!'	*/
 { 0x00f5,	0x002d,		0x002b }, /* '-', , '+'	*/
 { 0x00f6,	0x0024,		0x0026 }, /* '$', , '&'	*/
 { 0x00f7,	0x002a,		0x005c }, /* '*', , '\'	*/
 { 0x00f9,	0x0029,		0x00b0 }, /* ')', , degree	*/
 { 0x00fa,	0x00ec,		0x003d }, /* igrave, '='	*/
 { 0x00fb,	0x00f9,		0x0025 }, /* ugrave, '%'	*/
 { -1, 0, 0 }
};

xkey_t dutch_lk201lh_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	'~',		0x00b0 }, /* '~', , degree	*/
 { 0x00c0,	0x0031,		0x00bc }, /* '1', , onequarter	*/
 { 0x00c5,	0x0032,		0x005b }, /* '2', , '['	*/
 { 0x00cb,	0x0033,		0x005d }, /* '3', , ']'	*/
 { 0x00db,	0x0036,		0x0023 }, /* '6', , '#'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003b }, /* '.', , ';'	*/
 { 0x00ef,	0x0030,		0x005c }, /* '0', , '\'	*/
 { 0x00f2,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f3,	0x002b,		0x003d }, /* '+', , '='	*/
 { 0x00f5,	0x002f,		0x003a }, /* '/', , ':'	*/
 { 0x00f6,	0x002a,		0x0021 }, /* '*', , '!'	*/
 { 0x00f7,	0x0040,		0x007c }, /* '@', , '|'	*/
 { 0x00f9,	0x0027,		0x0022 }, /* ''', , '"'	*/
 { -1, 0, 0 }
};

xkey_t norwegian_lk201rn_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x0040 }, /* '~', , '@'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007c,		0x005c }, /* '|', , '\'	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x0027,		0x0060 }, /* ''', , '`'	*/
 { 0x00f6,	0x0022,		0x005e }, /* '"', , '^'	*/
 { 0x00f7,	0x0027,		0x002a }, /* ''', , '*'	*/
 { 0x00f9,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x00fa,	0x007d,		0x005d }, /* '}', , ']'	*/
 { 0x00fb,	0x007b,		0x005b }, /* '{', , '['	*/
 { -1, 0, 0 }
};

xkey_t portuguese_lk201lv_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x005c,		0x007c }, /* '\', , '|'	*/
 { 0x00db,	0x0036,		0x0022 }, /* '6', , '"'	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00f2,	0x00e7,		0x00c7 }, /* ccedilla, , Ccedilla */
 { 0x00f7,	0x005b,		0x007b }, /* '[', , '{'	*/
 { -1, 0, 0 }
};

xkey_t finnish_lk201nx_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x0040 }, /* '~', , '@'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007c,		0x005c }, /* '|', , '\'	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x005e,		0x0060 }, /* '^', , '`'	*/
 { 0x00f6,	0x007e,		0x005e }, /* '~', , '^'	*/
 { 0x00f7,	0x0027,		0x002a }, /* ''', , '*'	*/
 { 0x00f9,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x00fa,	0x007d,		0x005d }, /* '}', , ']'	*/
 { 0x00fb,	0x007b,		0x005b }, /* '{', , '['	*/
 { -1, 0, 0 }
};

xkey_t swedish_lk201nm_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x00b0 }, /* '~', , degree	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x0040 }, /* '3', , '@'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007d,		0x007b }, /* '}', , '{'	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x005e,		0x0060 }, /* '^', , '`'	*/
 { 0x00f6,	0x0023,		0x005c }, /* '#', , '\'	*/
 { 0x00f7,	0x0027,		0x002a }, /* ''', , '*'	*/
 { 0x00f9,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x00fa,	0x005d,		0x005b }, /* ']', , '['	*/
 { 0x00fb,	0x007c,		0x007c }, /* '|', , '|'	*/
 { -1, 0, 0 }
};

xkey_t flemish_lk201lb_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x0026,		0x0031 }, /* '&', , '1'	*/
 { 0x00c1,	0x0061,		0x0041 }, /* 'a', , 'A'	*/
 { 0x00c2,	0x0071,		0x0051 }, /* 'q', , 'Q'	*/
 { 0x00c3,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x00c5,	0x00e9,		0x0032 }, /* eacute, '2'	*/
 { 0x00c6,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00cb,	0x0022,		0x0033 }, /* '"', , '3'	*/
 { 0x00d0,	0x0027,		0x0034 }, /* ''', , '4'	*/
 { 0x00d6,	0x0028,		0x0035 }, /* '(', , '5'	*/
 { 0x00db,	0x005b,		0x0036 }, /* '[', , '6'	*/
 { 0x00e0,	0x005d,		0x0037 }, /* ']', , '7'	*/
 { 0x00e3,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x00e5,	0x0021,		0x0038 }, /* '!', , '8'	*/
 { 0x00e8,	0x003b,		0x002e }, /* ';', , '.'	*/
 { 0x00ea,	0x00e7,		0x0039 }, /* ccedilla, '9'	*/
 { 0x00ed,	0x003a,		0x002f }, /* ':', , '/'	*/
 { 0x00ef,	0x00e0,		0x0030 }, /* agrave, '0'	*/
 { 0x00f2,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x00f3,	0x003d,		0x002b }, /* '=', , '+'	*/
 { 0x00f5,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f6,	0x0024,		0x002a }, /* '$', , '*'	*/
 { 0x00f7,	0x0023,		0x0040 }, /* '#', , '@'	*/
 { 0x00f9,	0x0029,		0x00b0 }, /* ')', , degree	*/
 { 0x00fb,	0x005c,		0x0025 }, /* '\', , '%'	*/
 { -1, 0, 0 }
};

xkey_t *lk201_diffs[] = {
	danish_lk201rd_dp_diffs,		/* 0x30 */
	austrian_german_lk201ng_dp_diffs,	/* 0x32 */
	swiss_german_lk201ll_dp_diffs,		/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 *//* US is default */
	uk_lk201re_diffs,			/* 0x38 */
	spanish_lk201ls_dp_diffs,		/* 0x3a */
	belgian_french_lk201lp_dp_diffs,	/* 0x3c *//* belgian? */
	canadian_french_lk201lc_dp_diffs,	/* 0x3e */
	swiss_french_lk201lk_dp_diffs,		/* 0x40 */
	italian_lk201li_dp_diffs,		/* 0x42 */
	dutch_lk201lh_dp_diffs,			/* 0x44 */
	norwegian_lk201rn_dp_diffs,		/* 0x46 */
	portuguese_lk201lv_diffs,		/* 0x48 */
	finnish_lk201nx_dp_diffs,		/* 0x4a */
	swedish_lk201nm_dp_diffs,		/* 0x4c */
	flemish_lk201lb_dp_diffs,		/* 0x4e */
};


/************************************************************************
 * here are all the tables related to the LK401 keyboard series
 */

/*
 * This table contains the diffs between the US LK401 and the US LK201.
 * It is used with *every* LK401 to update the default LK201 to the default
 * LK401, then any further diffs between the US LK401 and the foreign LK401
 * are used to also update the translation table.
 *
 * NOTE: other differences are some additional keys an LK401 has; however,
 *  these have been made part of the base lk201_xlate table, because an LK201
 *  (theoretically) will never generate them.
 */
xkey_t lk201_to_lk401_diffs[] = {
/* keycode      unshifted       shifted */
 { 0x00b1,      MOD_COMP_L,	MOD_COMP_L },	/* Compose_L	*/
 { 0x00e8,      ',',		'<'	},	/* comma, '<'	*/
 { 0x00ed,      '.',		'>'	},	/* period, '>'	*/
 { -1, 0, 0 }
};

/*
 * the following tables hold the differences between the given keyboard
 *  and the default keyboard (LK201 US)
 */

xkey_t danish_lk401ad_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x0040 }, /* '~', , '@'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007b,		0x005b }, /* '{', , '['	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x0027,		0x0060 }, /* ''', , '`'	*/
 { 0x00f6,	0x0022,		0x005e }, /* '"', , '^'	*/
 { 0x00f7,	0x0027,		0x002a }, /* ''', , '*'	*/
 { 0x00f9,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x00fa,	0x007d,		0x005d }, /* '}', , ']'	*/
 { 0x00fb,	0x007c,		0x005c }, /* '|', , '\'	*/
 { -1, 0, 0 }
};

xkey_t austrian_german_lk401ag_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0094,	KP_COMMA,	KP_COMMA }, /* KP,	*/
 { 0x009c,	KP_PERIOD,	KP_PERIOD }, /* KP.	*/
 { 0x00bf,	0x005e,		0x00b0 }, /* '^', , degree	*/
 { 0x00c0,	0x0031,		0x0021 }, /* '1', , '!'	*/
 { 0x00c1,	0x0071,		0x0051 }, /* 'q', , 'Q'	*/
 { 0x00c2,	0x0061,		0x0041 }, /* 'a', , 'A'	*/
 { 0x00c3,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00c6,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x00c7,	0x0073,		0x0053 }, /* 's', , 'S'	*/
 { 0x00c8,	0x0078,		0x0058 }, /* 'x', , 'X'	*/
 { 0x00c9,	0x003c,		0x003e }, /* '<', , '>'	*/
 { 0x00cb,	0x0033,		0x00a7 }, /* '3', , section	*/
 { 0x00cc,	0x0065,		0x0045 }, /* 'e', , 'E'	*/
 { 0x00cd,	0x0064,		0x0044 }, /* 'd', , 'D'	*/
 { 0x00ce,	0x0063,		0x0043 }, /* 'c', , 'C'	*/
 { 0x00d0,	0x0034,		0x0024 }, /* '4', , '$'	*/
 { 0x00d1,	0x0072,		0x0052 }, /* 'r', , 'R'	*/
 { 0x00d2,	0x0066,		0x0046 }, /* 'f', , 'F'	*/
 { 0x00d3,	0x0076,		0x0056 }, /* 'v', , 'V'	*/
 { 0x00d4,	0x0020,		0x0020 }, /* ' ', , ' '	*/
 { 0x00d6,	0x0035,		0x0025 }, /* '5', , '%'	*/
 { 0x00d7,	0x0074,		0x0054 }, /* 't', , 'T'	*/
 { 0x00d8,	0x0067,		0x0047 }, /* 'g', , 'G'	*/
 { 0x00d9,	0x0062,		0x0042 }, /* 'b', , 'B'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00dc,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00dd,	0x0068,		0x0048 }, /* 'h', , 'H'	*/
 { 0x00de,	0x006e,		0x004e }, /* 'n', , 'N'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e1,	0x0075,		0x0055 }, /* 'u', , 'U'	*/
 { 0x00e2,	0x006a,		0x004a }, /* 'j', , 'J'	*/
 { 0x00e3,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e6,	0x0069,		0x0049 }, /* 'i', , 'I'	*/
 { 0x00e7,	0x006b,		0x004b }, /* 'k', , 'K'	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00eb,	0x006f,		0x004f }, /* 'o', , 'O'	*/
 { 0x00ec,	0x006c,		0x004c }, /* 'l', , 'L'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f0,	0x0070,		0x0050 }, /* 'p', , 'P'	*/
 { 0x00f2,	0x00f6,		0x00d6 }, /* odiaeresis, Odiaeresis	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x0027,		0x0060 }, /* ''', , '`'	*/
 { 0x00f6,	0x002b,		0x002a }, /* '+', , '*'	*/
 { 0x00f7,	0x0023,		0x0027 }, /* '#', , '''	*/
 { 0x00f9,	0x00df,		0x003f }, /* ssharp, '?'	*/
 { 0x00fa,	0x00fc,		0x00dc }, /* udiaeresis, Udiaeresis	*/
 { 0x00fb,	0x00e4,		0x00c4 }, /* adiaeresis, Adiaeresis	*/
 { -1, 0, 0 }
};

xkey_t swiss_german_lk401al_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0021,		0x00b0 }, /* '!', , degree	*/
 { 0x00c0,	0x0031,		0x002b }, /* '1', , '+'	*/
 { 0x00c3,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x002a }, /* '3', , '*'	*/
 { 0x00d0,	0x0034,		0x0040 }, /* '4', , '@'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00dc,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007b,		0x005b }, /* '{', , '['	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f7,	0x0024,		0x0023 }, /* '$', , '#'	*/
 { 0x00f9,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x00fa,	0x007c,		0x005c }, /* '|', , '\'	*/
 { 0x00fb,	0x007d,		0x005d }, /* '}', , ']'	*/
 { -1, 0, 0 }
};

xkey_t uk_lk401aa_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00cb,	0x0033,		0x00a3 }, /* '3', , sterling	*/
 { 0x00e8,	0x002c,		0x002c }, /* ',', , ','	*/
 { 0x00ed,	0x002e,		0x002e }, /* '.', , '.'	*/
 { -1, 0, 0 }
};

xkey_t spanish_lk401as_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0040,		0x005c }, /* '@', , '\'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007b,		0x007d }, /* '{', , '}'	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x005d,		0x005b }, /* ']', , '['	*/
 { 0x00f6,	0x002b,		0x002a }, /* '+', , '*'	*/
 { 0x00f7,	0x007c,		'~'    }, /* '|', , '~'	*//* FIXME tilde */
 { 0x00f9,	0x0027,		0x003f }, /* ''', , '?'	*/
 { -1, 0, 0 }
};

xkey_t belgian_french_lk401ap_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x0026,		0x0031 }, /* '&', , '1'	*/
 { 0x00c1,	0x0061,		0x0041 }, /* 'a', , 'A'	*/
 { 0x00c2,	0x0071,		0x0051 }, /* 'q', , 'Q'	*/
 { 0x00c3,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x00c5,	0x007c,		0x0032 }, /* '|', , '2'	*/
 { 0x00c6,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00cb,	0x0022,		0x0033 }, /* '"', , '3'	*/
 { 0x00d0,	0x0027,		0x0034 }, /* ''', , '4'	*/
 { 0x00d6,	0x0028,		0x0035 }, /* '(', , '5'	*/
 { 0x00db,	0x005b,		0x0036 }, /* '[', , '6'	*/
 { 0x00e0,	0x005d,		0x0037 }, /* ']', , '7'	*/
 { 0x00e3,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x00e5,	0x0021,		0x0038 }, /* '!', , '8'	*/
 { 0x00e8,	0x003b,		0x002e }, /* ';', , '.'	*/
 { 0x00ea,	0x007b,		0x0039 }, /* '{', , '9'	*/
 { 0x00ed,	0x003a,		0x002f }, /* ':', , '/'	*/
 { 0x00ef,	0x007d,		0x0030 }, /* '}', , '0'	*/
 { 0x00f2,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x00f3,	0x003d,		0x002b }, /* '=', , '+'	*/
 { 0x00f5,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f6,	0x0024,		0x002a }, /* '$', , '*'	*/
 { 0x00f7,	0x0023,		0x0040 }, /* '#', , '@'	*/
 { 0x00f9,	0x0029,		0x00b0 }, /* ')', , degree	*/
 { 0x00fb,	0x005c,		0x0025 }, /* '\', , '%'	*/
 { -1, 0, 0 }
};

xkey_t canadian_french_lk401ac_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	'~',		0x00b0 }, /* '~', , degree *//* FIXME tilde */
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x002f }, /* '3', , '/'	*/
 { 0x00db,	0x0036,		0x003f }, /* '6', , '?'	*/
 { 0x00e8,	0x002c,		0x0027 }, /* ',', , '''	*/
 { 0x00ed,	0x002e,		0x002e }, /* '.', , '.'	*/
 { 0x00f3,	0x00e9,		0x00c9 }, /* eacute, Eacute	*/
 { 0x00f6,	0x0023,		0x0040 }, /* '#', , '@'	*/
 { 0x00fa,	0x005d,		0x005b }, /* ']', , '['	*/
 { -1, 0, 0 }
};

xkey_t swiss_french_lk401ak_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0021,		0x00b0 }, /* '!', , degree	*/
 { 0x00c0,	0x0031,		0x002b }, /* '1', , '+'	*/
 { 0x00c3,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x002a }, /* '3', , '*'	*/
 { 0x00d0,	0x0034,		0x0040 }, /* '4', , '@'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00dc,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007b,		0x005b }, /* '{', , '['	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f7,	0x0024,		0x0023 }, /* '$', , '#'	*/
 { 0x00f9,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x00fa,	0x007c,		0x005c }, /* '|', , '\'	*/
 { 0x00fb,	0x007d,		0x005d }, /* '}', , ']'	*/
 { -1, 0, 0 }
};

xkey_t italian_lk401ai_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x0040,		0x0031 }, /* '@', , '1'	*/
 { 0x00c3,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x00c5,	0x0023,		0x0032 }, /* '#', , '2'	*/
 { 0x00c6,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00cb,	0x0022,		0x0033 }, /* '"', , '3'	*/
 { 0x00d0,	0x0027,		0x0034 }, /* ''', , '4'	*/
 { 0x00d6,	0x0028,		0x0035 }, /* '(', , '5'	*/
 { 0x00db,	0x005f,		0x0036 }, /* '_', , '6'	*/
 { 0x00e0,	0x00e8,		0x0037 }, /* egrave, '7'	*/
 { 0x00e3,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x00e5,	'^',		'8'    }, /* '^', , '8'	*/
 { 0x00e8,	0x003b,		0x002e }, /* ';', , '.'	*/
 { 0x00ea,	0x005b,		0x0039 }, /* '[', , '9'	*/
 { 0x00ed,	0x003a,		0x002f }, /* ':', , '/'	*/
 { 0x00ef,	0x005d,		0x0030 }, /* ']', , '0'	*/
 { 0x00f2,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x00f3,	0x007c,		0x0021 }, /* '|', , '!'	*/
 { 0x00f5,	0x002d,		0x002b }, /* '-', , '+'	*/
 { 0x00f6,	0x0024,		0x0026 }, /* '$', , '&'	*/
 { 0x00f7,	0x002a,		0x005c }, /* '*', , '\'	*/
 { 0x00f9,	0x0029,		0x00b0 }, /* ')', , degree	*/
 { 0x00fa,	0x007d,		0x003d }, /* '}', , '='	*/
 { 0x00fb,	0x007b,		0x0025 }, /* '{', , '%'	*/
 { -1, 0, 0 }
};

xkey_t dutch_us_lk401ah_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00e8,	0x002c,		0x002c }, /* ',', , ','	*/
 { 0x00ed,	0x002e,		0x002e }, /* '.', , '.'	*/
 { -1, 0, 0 }
};

xkey_t norwegian_lk401an_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x0040 }, /* '~', , '@'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007c,		0x005c }, /* '|', , '\'	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x0027,		0x0060 }, /* ''', , '`'	*/
 { 0x00f6,	0x0022,		0x005e }, /* '"', , '^'	*/
 { 0x00f7,	0x0027,		0x002a }, /* ''', , '*'	*/
 { 0x00f9,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x00fa,	0x007d,		0x005d }, /* '}', , ']'	*/
 { 0x00fb,	0x007b,		0x005b }, /* '{', , '['	*/
 { -1, 0, 0 }
};

xkey_t portuguese_lk401av_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x005c,		0x007c }, /* '\', , '|'	*/
 { 0x00db,	0x0036,		0x0022 }, /* '6', , '"'	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00f2,	0x00e7,		0x00c7 }, /* ccedilla,Ccedilla	*/
 { 0x00f7,	0x005b,		0x007b }, /* '[', , '{'	*/
 { -1, 0, 0 }
};

xkey_t finnish_lk401af_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x0040 }, /* '~', , '@'	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007c,		0x005c }, /* '|', , '\'	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x005e,		0x0060 }, /* '^', , '`'	*/
 { 0x00f6,	0x007e,		0x005e }, /* '~', , '^'	*/
 { 0x00f7,	0x0027,		0x002a }, /* ''', , '*'	*/
 { 0x00f9,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x00fa,	0x007d,		0x005d }, /* '}', , ']'	*/
 { 0x00fb,	0x007b,		0x005b }, /* '{', , '['	*/
 { -1, 0, 0 }
};

xkey_t swedish_lk401am_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007e,		0x00b0 }, /* '~', , degree	*/
 { 0x00c5,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x00cb,	0x0033,		0x0040 }, /* '3', , '@'	*/
 { 0x00db,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x00e0,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x00e5,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x00e8,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x00ea,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x00ed,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x00ef,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x00f2,	0x007d,		0x007b }, /* '}', , '{'	*/
 { 0x00f3,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f5,	0x005e,		0x0060 }, /* '^', , '`'	*/
 { 0x00f6,	0x0023,		0x005c }, /* '#', , '\'	*/
 { 0x00f7,	0x0027,		0x002a }, /* ''', , '*'	*/
 { 0x00f9,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x00fa,	0x005d,		0x005b }, /* ']', , '['	*/
 { 0x00fb,	0x007c,		0x007c }, /* '|', , '|'	*/
 { -1, 0, 0 }
};

xkey_t flemish_lk401ab_dp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x0026,		0x0031 }, /* '&', , '1'	*/
 { 0x00c1,	0x0061,		0x0041 }, /* 'a', , 'A'	*/
 { 0x00c2,	0x0071,		0x0051 }, /* 'q', , 'Q'	*/
 { 0x00c3,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x00c5,	0x007c,		0x0032 }, /* '|', , '2'	*/
 { 0x00c6,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x00cb,	0x0022,		0x0033 }, /* '"', , '3'	*/
 { 0x00d0,	0x0027,		0x0034 }, /* ''', , '4'	*/
 { 0x00d6,	0x0028,		0x0035 }, /* '(', , '5'	*/
 { 0x00db,	0x005b,		0x0036 }, /* '[', , '6'	*/
 { 0x00e0,	0x005d,		0x0037 }, /* ']', , '7'	*/
 { 0x00e3,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x00e5,	0x0021,		0x0038 }, /* '!', , '8'	*/
 { 0x00e8,	0x003b,		0x002e }, /* ';', , '.'	*/
 { 0x00ea,	0x007b,		0x0039 }, /* '{', , '9'	*/
 { 0x00ed,	0x003a,		0x002f }, /* ':', , '/'	*/
 { 0x00ef,	0x007d,		0x0030 }, /* '}', , '0'	*/
 { 0x00f2,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x00f3,	0x003d,		0x002b }, /* '=', , '+'	*/
 { 0x00f5,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x00f6,	0x0024,		0x002a }, /* '$', , '*'	*/
 { 0x00f7,	0x0023,		0x0040 }, /* '#', , '@'	*/
 { 0x00f9,	0x0029,		0x00b0 }, /* ')', , degree	*/
 { 0x00fb,	0x005c,		0x0025 }, /* '\', , '%'	*/
 { -1, 0, 0 }
};

xkey_t *lk401_diffs[] = {
	danish_lk401ad_dp_diffs,		/* 0x30 */
	austrian_german_lk401ag_diffs,		/* 0x32 */
	swiss_german_lk401al_dp_diffs,		/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 *//* US is default */
	uk_lk401aa_diffs,			/* 0x38 */
	spanish_lk401as_dp_diffs,		/* 0x3a */
	belgian_french_lk401ap_dp_diffs,	/* 0x3c *//* belgian? */
	canadian_french_lk401ac_dp_diffs,	/* 0x3e */
	swiss_french_lk401ak_dp_diffs,		/* 0x40 */
	italian_lk401ai_dp_diffs,		/* 0x42 */
	dutch_us_lk401ah_diffs,			/* 0x44 */
	norwegian_lk401an_dp_diffs,		/* 0x46 */
	portuguese_lk401av_diffs,		/* 0x48 */
	finnish_lk401af_dp_diffs,		/* 0x4a */
	swedish_lk401am_dp_diffs,		/* 0x4c */
	flemish_lk401ab_dp_diffs,		/* 0x4e */
};

/*
 * The following tables are used to hold the ALT-GR translations
 *  for the LK401 keyboards.
 */

xkey_t austrian_german_lk401ag_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x00c0,	0x00b9,		0x00a1 }, /* onesuperior, exclamdown	*/
 { 0x00c1,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c2,	0x00e6,		0x00c6 }, /* ae, AE	*/
 { 0x00c3,	0x00ab,		0x003c }, /* guillemotleft, '<'	*/
 { 0x00c5,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x00c7,	0x00df,		0x00a7 }, /* ssharp, section	*/
 { 0x00c8,	0x00bb,		0x003e }, /* guillemotright, '>'	*/
 { 0x00c9,	0x007c,		0x00a6 }, /* '|', brokenbar	*/
 { 0x00cb,	0x00b3,		0x00a3 }, /* threesuperior, sterling	*/
 { 0x00cd,	0x00f0,		0x00d0 }, /* eth, ETH	*/
 { 0x00ce,	0x00a2,		0x00a9 }, /* cent, copyright	*/
 { 0x00d0,	0x00bc,		0x00a4 }, /* onequarter, currency	*/
 { 0x00d1,	0x00b6,		0x00ae }, /* paragraph, registered	*/
 { 0x00d2,	0x00aa,		0x0000 }, /* ordfeminine, NULL	*/
 { 0x00d4,	0x00a0,		0x00a0 }, /* nobreakspace, nobreakspace	*/
 { 0x00d6,	0x00bd,		0x0000 }, /* onehalf, NULL	*/
 { 0x00db,	0x00be,		0x0000 }, /* threequarters, NULL	*/
 { 0x00dc,	0x00a5,		0x0000 }, /* yen, NULL	*/
 { 0x00e0,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00e3,	0x00b5,		0x00ba }, /* mu, masculine	*/
 { 0x00e5,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00e7,	0x0026,		0x0000 }, /* '&', NULL	*/
 { 0x00e8,	0x00d7,		0x0000 }, /* multiply, NULL	*/
 { 0x00ea,	0x005d,		0x00b1 }, /* ']', plusminus	*/
 { 0x00eb,	0x00f8,		0x00d8 }, /* oslash, Ooblique	*/
 { 0x00ed,	0x00b7,		0x00f7 }, /* periodcentered, division	*/
 { 0x00ef,	0x007d,		0x00b0 }, /* '}', degree	*/
 { 0x00f0,	0x00fe,		0x00de }, /* thorn, THORN	*/
 { 0x00f2,	0x0027,		0x0000 }, /* Dacute_accent, NULL	*/
 { 0x00f3,	0x00ad,		0x0000 }, /* hyphen, NULL	*/
 { 0x00f5,	0x00b8,		0x0000 }, /* Dcedilla_accent, NULL	*/
 { 0x00f6,	0x007e,		0x00af }, /* '~', macron	*/
 { 0x00f7,	0x0060,		0x0000 }, /* Dgrave_accent, NULL	*/
 { 0x00f9,	0x005c,		0x00bf }, /* '\', questiondown	*/
 { 0x00fa,	0x00a8,		0x00b0 }, /* Ddiaeresis, '°'	*/
 { 0x00fb,	0x005e,		0x0000 }, /* Dcircumflex_accent, NULL	*/
 { -1, 0, 0 }
};

xkey_t *lk401_altgrs[] = {
	(xkey_t *)NULL,				/* 0x30 */
	austrian_german_lk401ag_altgr,		/* 0x32 */
	(xkey_t *)NULL,				/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 */
	(xkey_t *)NULL,				/* 0x38 */
	(xkey_t *)NULL,				/* 0x3a */
	(xkey_t *)NULL,				/* 0x3c */
	(xkey_t *)NULL,				/* 0x3e */
	(xkey_t *)NULL,				/* 0x40 */
	(xkey_t *)NULL,				/* 0x42 */
	(xkey_t *)NULL,				/* 0x44 */
	(xkey_t *)NULL,				/* 0x46 */
	(xkey_t *)NULL,				/* 0x48 */
	(xkey_t *)NULL,				/* 0x4a */
	(xkey_t *)NULL,				/* 0x4c */
	(xkey_t *)NULL,				/* 0x4e */
};

/************************************************************************
 * here are all the tables related to the LK421 keyboard series
 */

/*
 * The following tables hold the differences between the LK421 keyboards
 *  and the default keyboard (LK201 US)
 *
 * NOTE: as was the case with LK401 vs LK201:
 *  other differences are some additional keys an LK421 has; however,
 *  these have been made part of the base lk201_xlate table, because an LK201
 *  (theoretically) will never generate them.
 */

xkey_t us_lk421aa_diffs[] = {
/* keycode      unshifted       shifted */
 { 0x00b1,      MOD_COMP_L,	MOD_COMP_L },	/* Compose_L	*/
 { 0x00bf,      033,		033	},	/* Escape	*/
 { 0x00c9,      '`',		'~'	},	/* grave, tilde	*/
 { 0x00e8,      ',',		'<'	},	/* comma, less	*/
 { 0x00ed,      '.',		'>'	},	/* period, greater	*/
 { -1, 0, 0 }
};

xkey_t uk_lk421aa_diffs[] = {
/* keycode      unshifted       shifted */
 { 0x00b1,	MOD_COMP_L,	MOD_COMP_L },	/* Compose_L	*/
 { 0x00cb,	'3',		0xa3	},	/* '3', sterling	*/
 { -1, 0, 0 }
};

/* NOTE: make all foreign languages use the US version */
xkey_t *lk421_diffs[] = {
	us_lk421aa_diffs,			/* 0x30 */
	us_lk421aa_diffs,			/* 0x32 */
	us_lk421aa_diffs,			/* 0x34 */
	us_lk421aa_diffs,			/* 0x36 */
	uk_lk421aa_diffs,			/* 0x38 */
	us_lk421aa_diffs,			/* 0x3a */
	us_lk421aa_diffs,			/* 0x3c */
	us_lk421aa_diffs,			/* 0x3e */
	us_lk421aa_diffs,			/* 0x40 */
	us_lk421aa_diffs,			/* 0x42 */
	us_lk421aa_diffs,			/* 0x44 */
	us_lk421aa_diffs,			/* 0x46 */
	us_lk421aa_diffs,			/* 0x48 */
	us_lk421aa_diffs,			/* 0x4a */
	us_lk421aa_diffs,			/* 0x4c */
	us_lk421aa_diffs,			/* 0x4e */
};

/************************************************************************
 * here are all the tables related to the LK443 keyboard series
 */

/*
 * This table contains the diffs between the US LK443 and the US LK201.
 * It is used with *every* LK443 to update the default LK201 to the default
 * LK443, then any further diffs between the US LK443 and the foreign LK443
 * are used to also update the translation table.
 */
xkey_t lk201_to_lk443_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0071,	F11,		F11    }, /* keycode 113 F11		*/
 { 0x0072,	F12,		F12    }, /* keycode 114 F12		*/
 { 0x0073,	PRTSC,		PRTSC  }, /* keycode 115 Print, Sys_Req	*/
 { 0x0074,	MOD_SCROLL,	MOD_SCROLL }, /* keycode 116 Scroll_Lock*/
 { 0x007c,	PAUSE,		PAUSE  }, /* keycode 124 Pause		*/
 { 0x008a,	INS,		INS    }, /* keycode 138 Insert	*/
 { 0x008b,	HOME,		HOME   }, /* keycode 139 Home	*/
 { 0x008c,	PREV,		PREV   }, /* keycode 140 Prior	*/
 { 0x008d,	DELE,		DELE   }, /* keycode 141 Delete	*/
 { 0x008e,	END,		END    }, /* keycode 142 End	*/
 { 0x0092,	INS_NPAD,	'0'    }, /* keycode 146 KP_Insert, KP_0*/
 { 0x0094,	DELE_NPAD,	'.'    }, /* keycode 148 KP_Delete, KP_Decimal*/
 { 0x0096,	END_NPAD,	'1'    }, /* keycode 150 KP_End, KP_1	*/
 { 0x0097,	DOWN_NPAD,	'2'    }, /* keycode 151 KP_Down, KP_2	*/
 { 0x0098,	PGDWN_NPAD,	'3'    }, /* keycode 152 KP_Next, KP_3	*/
 { 0x0099,	LEFT_NPAD,	'4'    }, /* keycode 153 KP_Left, KP_4	*/
 { 0x009b,	RIGHT_NPAD,	'6'    }, /* keycode 155 KP_Right, KP_6	*/
 { 0x009c,	'+',		'+'    }, /* keycode 156 KP_Add	*/
 { 0x009d,	HOME_NPAD,	'7'    }, /* keycode 157 KP_Home, KP_7	*/
 { 0x009e,	UP_NPAD,	'8'    }, /* keycode 158 KP_Up, KP_8	*/
 { 0x009f,	PGUP_NPAD,	'9'    }, /* keycode 159 KP_Prior, KP_9	*/
 { 0x00a1,	MOD_NUML,	MOD_NUML }, /* keycode 161 Num_Lock	*/
 { 0x00a2,	'/',		'/'    }, /* keycode 162 KP_Divide	*/
 { 0x00a3,	'*',		'*'    }, /* keycode 163 KP_Multiply	*/
 { 0x00a4,	'-',		'-'    }, /* keycode 164 KP_Subtract	*/
 { 0x00ac,	MOD_ALT_L,	MOD_ALT_L }, /* keycode 172 Alt_L	*/
 { 0x00ad,	MOD_CTRL_R,	MOD_CTRL_R }, /* keycode 173 Control_R	*/
 { 0x00b2,	MOD_ALT_R,	MOD_ALT_R }, /* keycode 178 Alt_R	*/
/* { 0x00bc,	0x0008,		0x0008 },*/ /* keycode 188 BackSpace	*/
 { 0x00e8,	0x002c,		0x003c }, /* keycode 232 comma, less	*/
 { 0x00ed,	0x002e,		0x003e }, /* keycode 237 period, greater*/
 { -1, 0, 0 }
};

/*
 * the following tables hold the differences between the given keyboard
 *  and the default keyboard (LK443 US)
 */

xkey_t austrian_german_lk444kg_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x005e,		0x00b0 }, /* keycode 191 asciicircum, degree*/
 { 0x00c1,	0x0071,		0x0051 }, /* keycode 193 q, Q	*/
 { 0x00c2,	0x0061,		0x0041 }, /* keycode 194 a, A	*/
 { 0x00c3,	0x0079,		0x0059 }, /* keycode 195 y, Y	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x00a3 }, /* keycode 203 3, sterling	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00dc,	0x007a,		0x005a }, /* keycode 220 z, Z	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e3,	0x006d,		0x004d }, /* keycode 227 m, M	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00f6,		0x00d6 }, /* keycode 242 odiaeresis, Odiaer*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x00b4,		0x0060 }, /* keycode 245 acute, grave	*/
 { 0x00f6,	0x002b,		0x002a }, /* keycode 246 plus, asterisk	*/
 { 0x00f7,	0x0023,		0x0027 }, /* keycode 247 numbersign, apost*/
 { 0x00f9,	0x00df,		0x003f }, /* keycode 249 ssharp, question*/
 { 0x00fa,	0x00fc,		0x00dc }, /* keycode 250 udiaeresis, Udiaer*/
 { 0x00fb,	0x00e4,		0x00c4 }, /* keycode 251 adiaeresis, Adiaer*/
 { -1, 0, 0 }
};

xkey_t belgian_lk444kb_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00b2,		0x00b3 }, /* keycode 191 twosuper, threesuper*/
 { 0x00c0,	0x0026,		0x0031 }, /* keycode 192 ampersand, 1	*/
 { 0x00c1,	0x0061,		0x0041 }, /* keycode 193 A	*/
 { 0x00c2,	0x0071,		0x0051 }, /* keycode 194 Q	*/
 { 0x00c3,	0x0077,		0x0057 }, /* keycode 195 W	*/
 { 0x00c5,	0x00e9,		0x0032 }, /* keycode 197 eacute, 2	*/
 { 0x00c6,	0x007a,		0x005a }, /* keycode 198 Z	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0022,		0x0033 }, /* keycode 203 quotedbl, 3	*/
 { 0x00d0,	0x0027,		0x0034 }, /* keycode 208 apostrophe, 4	*/
 { 0x00d6,	0x0028,		0x0035 }, /* keycode 214 parenleft, 5	*/
 { 0x00db,	0x00a7,		0x0036 }, /* keycode 219 section, 6	*/
 { 0x00e0,	0x00e8,		0x0037 }, /* keycode 224 egrave, 7	*/
 { 0x00e3,	0x002c,		0x003f }, /* keycode 227 comma, question*/
 { 0x00e5,	0x0021,		0x0038 }, /* keycode 229 exclam, 8	*/
 { 0x00e8,	0x003b,		0x002e }, /* keycode 232 semicolon, period*/
 { 0x00ea,	0x00e7,		0x0039 }, /* keycode 234 ccedilla, 9	*/
 { 0x00ed,	0x003a,		0x002f }, /* keycode 237 colon, slash	*/
 { 0x00ef,	0x00e0,		0x0030 }, /* keycode 239 agrave, 0	*/
 { 0x00f2,	0x006d,		0x004d }, /* keycode 242 M	*/
 { 0x00f3,	0x003d,		0x002b }, /* keycode 243 equal, plus	*/
 { 0x00f5,	0x002d,		0x005f }, /* keycode 245 minus, underscore*/
 { 0x00f6,	0x0024,		0x002a }, /* keycode 246 dollar, asterisk*/
 { 0x00f7,	0x00b5,		0x00a3 }, /* keycode 247 mu, sterling	*/
 { 0x00f9,	0x0029,		0x00b0 }, /* keycode 249 parenright, degree*/
 { 0x00fa,	0x005e,		0x00a8 }, /* keycode 250 asciicircum, diaer*/
 { 0x00fb,	0x00f9,		0x0025 }, /* keycode 251 ugrave, percent*/
 { -1, 0, 0 }
};

xkey_t danish_lk444kd_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00bd,		0x00a7 }, /* keycode 191 onehalf, section*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x0023 }, /* keycode 203 3, numbersign	*/
 { 0x00d0,	0x0034,		0x00a4 }, /* keycode 208 4, currency	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00e6,		0x00c6 }, /* keycode 242 ae, AE	*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x00b4,		0x0060 }, /* keycode 245 acute, grave	*/
 { 0x00f6,	0x00a8,		0x005e }, /* keycode 246 diaeresis, circum*/
 { 0x00f7,	0x0027,		0x002a }, /* keycode 247 apostrophe, asterisk*/
 { 0x00f9,	0x002b,		0x003f }, /* keycode 249 plus, question	*/
 { 0x00fa,	0x00e5,		0x00c5 }, /* keycode 250 aring, Aring	*/
 { 0x00fb,	0x00f8,		0x00d8 }, /* keycode 251 oslash, Ooblique*/
 { -1, 0, 0 }
};

xkey_t dutch_lk444gh_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0040,		0x00a7 }, /* keycode 191 at, section	*/
 { 0x00c0,	0x0031,		0x0021 }, /* keycode 192 1, exclam	*/
 { 0x00c3,	0x007a,		0x005a }, /* keycode 195 z, Z	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c7,	0x0073,		0x0053 }, /* keycode 199 s, S	*/
 { 0x00c8,	0x0078,		0x0058 }, /* keycode 200 x, X	*/
 { 0x00c9,	0x005d,		0x005b }, /* keycode 201 brakright, brakleft*/
 { 0x00cb,	0x0033,		0x0023 }, /* keycode 203 3, numbersign	*/
 { 0x00ce,	0x0063,		0x0043 }, /* keycode 206 c, C	*/
 { 0x00d0,	0x0034,		0x0024 }, /* keycode 208 4, dollar	*/
 { 0x00d1,	0x0072,		0x0052 }, /* keycode 209 r, R	*/
 { 0x00d6,	0x0035,		0x0025 }, /* keycode 214 5, percent	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00e0,	0x0037,		0x005f }, /* keycode 224 7, underscore	*/
 { 0x00e3,	0x006d,		0x004d }, /* keycode 227 m, M	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x0027 }, /* keycode 239 0, apostrophe	*/
 { 0x00f2,	0x002b,		0x00b1 }, /* keycode 242 plus, plusminus*/
 { 0x00f3,	0x002d,		0x003d }, /* keycode 243 minus, equal	*/
 { 0x00f5,	0x00b0,		0x007e }, /* keycode 245 degree, tilde*/
 { 0x00f6,	0x002a,		0x00a6 }, /* keycode 246 asterisk, brokenbar*/
 { 0x00f7,	0x003c,		0x003e }, /* keycode 247 less, greater	*/
 { 0x00f9,	0x002f,		0x003f }, /* keycode 249 slash, question*/
 { 0x00fa,	0x00a8,		0x005e }, /* keycode 250 diaeresis, circum*/
 { 0x00fb,	0x00b4,		0x0060 }, /* keycode 251 acute, grave	*/
 { -1, 0, 0 }
};

xkey_t finnish_lk444ca_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00a7,		0x00bd }, /* keycode 191 section, onehalf*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x0023 }, /* keycode 203 3, numbersign	*/
 { 0x00d0,	0x0034,		0x00a4 }, /* keycode 208 4, currency	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00f6,		0x00d6 }, /* keycode 242 odiaeresis, Odiaer*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x00b4,		0x0060 }, /* keycode 245 acute, grave	*/
 { 0x00f6,	0x00a8,		0x005e }, /* keycode 246 diaeresis, circum*/
 { 0x00f7,	0x0027,		0x002a }, /* keycode 247 apostrophe, asterisk*/
 { 0x00f9,	0x002b,		0x003f }, /* keycode 249 plus, question	*/
 { 0x00fa,	0x00e5,		0x00c5 }, /* keycode 250 aring, Aring	*/
 { 0x00fb,	0x00e4,		0x00c4 }, /* keycode 251 adiaeresis, Adiaer*/
 { -1, 0, 0 }
};

xkey_t french_canadian_lk444ac_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0023,		0x007c }, /* keycode 191 numbersign, bar*/
 { 0x00c0,	0x0031,		0x0021 }, /* keycode 192 1, exclam	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x00ab,		0x00bb }, /* keycode 201 guilleft, guilright*/
 { 0x00cb,	0x0033,		0x002f }, /* keycode 203 3, slash	*/
 { 0x00d0,	0x0034,		0x0024 }, /* keycode 208 4, dollar	*/
 { 0x00d6,	0x0035,		0x0025 }, /* keycode 214 5, percent	*/
 { 0x00db,	0x0036,		0x003f }, /* keycode 219 6, question	*/
 { 0x00e0,	0x0037,		0x0026 }, /* keycode 224 7, ampersand	*/
 { 0x00e3,	0x006d,		0x004d }, /* keycode 227 m, M	*/
 { 0x00e5,	0x0038,		0x002a }, /* keycode 229 8, asterisk	*/
 { 0x00e8,	0x002c,		0x0027 }, /* keycode 232 comma, apostrophe*/
 { 0x00ea,	0x0039,		0x0028 }, /* keycode 234 9, parenleft	*/
 { 0x00eb,	0x006f,		0x004f }, /* keycode 235 o, O	*/
 { 0x00ed,	0x002e,		0x002e }, /* keycode 237 period, period	*/
 { 0x00ef,	0x0030,		0x0029 }, /* keycode 239 0, parenright	*/
 { 0x00f0,	0x0070,		0x0050 }, /* keycode 240 p, P	*/
 { 0x00f2,	0x003b,		0x003a }, /* keycode 242 semicolon, colon*/
 { 0x00f3,	0x00e9,		0x00c9 }, /* keycode 243 eacute, Eacute	*/
 { 0x00f5,	0x003d,		0x002b }, /* keycode 245 equal, plus	*/
 { 0x00f6,	0x00e7,		0x00a8 }, /* keycode 246 ccedilla, diaeresis*/
 { 0x00f7,	0x003c,		0x003e }, /* keycode 247 less, greater	*/
 { 0x00f9,	0x002d,		0x005f }, /* keycode 249 minus, underscore*/
 { 0x00fa,	0x005e,		0x005e }, /* keycode 250 asciicircum, circum*/
 { 0x00fb,	0x0060,		0x0060 }, /* keycode 251 grave, grave	*/
 { -1, 0, 0 }
};

xkey_t french_lk444kp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00b2,		0x00b2 }, /* keycode 191 twosuper, twosuper*/
 { 0x00c0,	0x0026,		0x0031 }, /* keycode 192 ampersand, 1	*/
 { 0x00c1,	0x0061,		0x0041 }, /* keycode 193 A	*/
 { 0x00c2,	0x0071,		0x0051 }, /* keycode 194 Q	*/
 { 0x00c3,	0x0077,		0x0057 }, /* keycode 195 W	*/
 { 0x00c5,	0x00e9,		0x0032 }, /* keycode 197 eacute, 2	*/
 { 0x00c6,	0x007a,		0x005a }, /* keycode 198 Z	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0022,		0x0033 }, /* keycode 203 quotedbl, 3	*/
 { 0x00d0,	0x0027,		0x0034 }, /* keycode 208 apostrophe, 4	*/
 { 0x00d6,	0x0028,		0x0035 }, /* keycode 214 parenleft, 5	*/
 { 0x00db,	0x002d,		0x0036 }, /* keycode 219 minus, 6	*/
 { 0x00e0,	0x00e8,		0x0037 }, /* keycode 224 egrave, 7	*/
 { 0x00e3,	0x002c,		0x003f }, /* keycode 227 comma, question*/
 { 0x00e5,	0x005f,		0x0038 }, /* keycode 229 underscore, 8	*/
 { 0x00e8,	0x003b,		0x002e }, /* keycode 232 semicolon, period*/
 { 0x00ea,	0x00e7,		0x0039 }, /* keycode 234 ccedilla, 9	*/
 { 0x00ed,	0x003a,		0x002f }, /* keycode 237 colon, slash	*/
 { 0x00ef,	0x00e0,		0x0030 }, /* keycode 239 agrave, 0	*/
 { 0x00f2,	0x006d,		0x004d }, /* keycode 242 M	*/
 { 0x00f3,	0x0021,		0x00a7 }, /* keycode 243 exclam, section*/
 { 0x00f5,	0x003d,		0x002b }, /* keycode 245 equal, plus	*/
 { 0x00f6,	0x0024,		0x00a3 }, /* keycode 246 dollar, sterling*/
 { 0x00f7,	0x002a,		0x00b5 }, /* keycode 247 asterisk, mu	*/
 { 0x00f9,	0x0029,		0x00b0 }, /* keycode 249 parenright, degree*/
 { 0x00fa,	0x005e,		0x00a8 }, /* keycode 250 circum, diaeresis*/
 { 0x00fb,	0x00f9,		0x0025 }, /* keycode 251 ugrave, percent*/
 { -1, 0, 0 }
};

xkey_t italian_lk444ki_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x005c,		0x00a6 }, /* keycode 191 backslash, brokenbar*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x00a3 }, /* keycode 203 3, sterling	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00f2,		0x00e7 }, /* keycode 242 ograve, ccedilla*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x00ec,		0x005e }, /* keycode 245 igrave, circum	*/
 { 0x00f6,	0x002b,		0x002a }, /* keycode 246 plus, asterisk	*/
 { 0x00f7,	0x00f9,		0x00a7 }, /* keycode 247 ugrave, section*/
 { 0x00f9,	0x0027,		0x003f }, /* keycode 249 apostrophe, question*/
 { 0x00fa,	0x00e8,		0x00e9 }, /* keycode 250 egrave, eacute	*/
 { 0x00fb,	0x00e0,		0x00b0 }, /* keycode 251 agrave, degree	*/
 { -1, 0, 0 }
};

xkey_t norwegian_lk444kn_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x007c,		0x00a7 }, /* keycode 191 bar, section	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x005c,		0x007c }, /* keycode 201 backslash, bar	*/
 { 0x00cb,	0x0033,		0x0023 }, /* keycode 203 3, numbersign	*/
 { 0x00d0,	0x0034,		0x00a4 }, /* keycode 208 4, currency	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00f8,		0x00d8 }, /* keycode 242 oslash, Ooblique*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x005c,		0x0060 }, /* keycode 245 backslash, grave*/
 { 0x00f6,	0x00a8,		0x005e }, /* keycode 246 diaeresis, circum*/
 { 0x00f7,	0x0027,		0x002a }, /* keycode 247 apostrophe, asterisk*/
 { 0x00f9,	0x002b,		0x003f }, /* keycode 249 plus, question	*/
 { 0x00fa,	0x00e5,		0x00c5 }, /* keycode 250 aring, Aring	*/
 { 0x00fb,	0x00e6,		0x00c6 }, /* keycode 251 ae, AE	*/
 { -1, 0, 0 }
};

xkey_t portuguese_lk444kv_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x005c,		0x007c }, /* keycode 191 backslash, bar	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x0023 }, /* keycode 203 3, numbersign	*/
 { 0x00d0,	0x0034,		0x0024 }, /* keycode 208 4, dollar	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00e0,	0x0037,		0x005c }, /* keycode 224 7, backslash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00e7,		0x00c7 }, /* keycode 242 ccedilla, Ccedilla*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x00ab,		0x00bb }, /* keycode 245 guilleleft, guiright*/
 { 0x00f6,	0x00b4,		0x0060 }, /* keycode 246 acute, grave	*/
 { 0x00f7,	0x007e,		0x005e }, /* keycode 247 asciitilde, circum*/
 { 0x00f9,	0x0027,		0x003f }, /* keycode 249 apostrophe, question*/
 { 0x00fa,	0x002b,		0x002a }, /* keycode 250 plus, asterisk	*/
 { 0x00fb,	0x00ba,		0x00aa }, /* keycode 251 masculine, ordfem*/
 { -1, 0, 0 }
};

xkey_t spanish_lk444ks_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00ba,		0x00aa }, /* keycode 191 masculine, ordfem*/
 { 0x00c0,	0x0031,		0x0021 }, /* keycode 192 1, exclam	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x00b7 }, /* keycode 203 3, periodcentered*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00f1,		0x00d1 }, /* keycode 242 ntilde, Ntilde	*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x00a1,		0x00bf }, /* keycode 245 exclamdown,questdown*/
 { 0x00f6,	0x002b,		0x002a }, /* keycode 246 plus, asterisk	*/
 { 0x00f7,	0x00e7,		0x00c7 }, /* keycode 247 ccedilla, Ccedilla*/
 { 0x00f9,	0x0027,		0x003f }, /* keycode 249 apostrophe, question*/
 { 0x00fa,	0x0060,		0x005e }, /* keycode 250 grave, asciicircum*/
 { 0x00fb,	0x00b4,		0x00a8 }, /* keycode 251 acute, diaeresis*/
 { -1, 0, 0 }
};

xkey_t swedish_lk444ma_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00a7,		0x00bd }, /* keycode 191 section, onehalf*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x0023 }, /* keycode 203 3, numbersign	*/
 { 0x00d0,	0x0034,		0x00a4 }, /* keycode 208 4, currency	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00f8,		0x00d8 }, /* keycode 242 oslash, Ooblique*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x00b4,		0x0060 }, /* keycode 245 acute, grave	*/
 { 0x00f6,	0x00a8,		0x005e }, /* keycode 246 diaeresis, circum*/
 { 0x00f7,	0x0027,		0x002a }, /* keycode 247 apostrophe, asterisk*/
 { 0x00f9,	0x002b,		0x003f }, /* keycode 249 plus, question	*/
 { 0x00fa,	0x00e5,		0x00c5 }, /* keycode 250 aring, Aring	*/
 { 0x00fb,	0x00e6,		0x00c6 }, /* keycode 251 ae, AE	*/
 { -1, 0, 0 }
};

xkey_t swiss_french_lk444ap_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00a7,		0x00b0 }, /* keycode 191 section, degree*/
 { 0x00c0,	0x0031,		0x002b }, /* keycode 192 1, plus	*/
 { 0x00c3,	0x0079,		0x0059 }, /* keycode 195 Y	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x002a }, /* keycode 203 3, asterisk	*/
 { 0x00d0,	0x0034,		0x00e7 }, /* keycode 208 4, ccedilla	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00dc,	0x007a,		0x005a }, /* keycode 220 Z	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00e9,		0x00f6 }, /* keycode 242 eacute, odiaeresis*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x005e,		0x0060 }, /* keycode 245 asciicircum, grave*/
 { 0x00f6,	0x00a8,		0x0021 }, /* keycode 246 diaeresis, exclam*/
 { 0x00f7,	0x0024,		0x00a3 }, /* keycode 247 dollar, sterling*/
 { 0x00f9,	0x0027,		0x003f }, /* keycode 249 apostrophe, question*/
 { 0x00fa,	0x00e8,		0x00fc }, /* keycode 250 egrave, udiaeresis*/
 { 0x00fb,	0x00e0,		0x00e4 }, /* keycode 251 agrave, adiaeresis*/
 { -1, 0, 0 }
};

xkey_t swiss_german_lk444mh_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00a7,		0x00b0 }, /* keycode 191 section, degree*/
 { 0x00c0,	0x0031,		0x002b }, /* keycode 192 1, plus	*/
 { 0x00c3,	0x0079,		0x0059 }, /* keycode 195 Y	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x003c,		0x003e }, /* keycode 201 less, greater	*/
 { 0x00cb,	0x0033,		0x002a }, /* keycode 203 3, asterisk	*/
 { 0x00d0,	0x0034,		0x00e7 }, /* keycode 208 4, ccedilla	*/
 { 0x00db,	0x0036,		0x0026 }, /* keycode 219 6, ampersand	*/
 { 0x00dc,	0x007a,		0x005a }, /* keycode 220 Z	*/
 { 0x00e0,	0x0037,		0x002f }, /* keycode 224 7, slash	*/
 { 0x00e5,	0x0038,		0x0028 }, /* keycode 229 8, parenleft	*/
 { 0x00e8,	0x002c,		0x003b }, /* keycode 232 comma, semicolon*/
 { 0x00ea,	0x0039,		0x0029 }, /* keycode 234 9, parenright	*/
 { 0x00ed,	0x002e,		0x003a }, /* keycode 237 period, colon	*/
 { 0x00ef,	0x0030,		0x003d }, /* keycode 239 0, equal	*/
 { 0x00f2,	0x00f6,		0x00e9 }, /* keycode 242 odiaeresis, eacute*/
 { 0x00f3,	0x002d,		0x005f }, /* keycode 243 minus, underscore*/
 { 0x00f5,	0x005e,		0x0060 }, /* keycode 245 asciicircum, grave*/
 { 0x00f6,	0x00a8,		0x0021 }, /* keycode 246 diaeresis, exclam*/
 { 0x00f7,	0x0024,		0x00a3 }, /* keycode 247 dollar, sterling*/
 { 0x00f9,	0x0027,		0x003f }, /* keycode 249 apostrophe, question*/
 { 0x00fa,	0x00fc,		0x00e8 }, /* keycode 250 udiaeresis, egrave*/
 { 0x00fb,	0x00e4,		0x00e0 }, /* keycode 251 adiaeresis, agrave*/
 { -1, 0, 0 }
};

xkey_t uk_lk444ae_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x0060,		0x00ac }, /* keycode 191 grave, notsign	*/
 { 0x00c5,	0x0032,		0x0022 }, /* keycode 197 2, quotedbl	*/
 { 0x00c9,	0x005c,		0x007c }, /* keycode 201 backslash, bar	*/
 { 0x00cb,	0x0033,		0x00a3 }, /* keycode 203 3, sterling	*/
 { 0x00f7,	0x0023,		0x007e }, /* keycode 247 numbersign, tilde*/
 { 0x00fb,	0x0027,		0x0040 }, /* keycode 251 apostrophe, at	*/
 { -1, 0, 0 }
};

xkey_t *lk443_diffs[] = {
	danish_lk444kd_diffs,			/* 0x30 */
	austrian_german_lk444kg_diffs,		/* 0x32 */
	swiss_german_lk444mh_diffs,		/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 *//* US is default */
	uk_lk444ae_diffs,			/* 0x38 */
	spanish_lk444ks_diffs,			/* 0x3a */
	french_lk444kp_diffs,			/* 0x3c */
	french_canadian_lk444ac_diffs,		/* 0x3e */
	swiss_french_lk444ap_diffs,		/* 0x40 */
	italian_lk444ki_diffs,			/* 0x42 */
	dutch_lk444gh_diffs,			/* 0x44 */
	norwegian_lk444kn_diffs,		/* 0x46 */
	portuguese_lk444kv_diffs,		/* 0x48 */
	finnish_lk444ca_diffs,			/* 0x4a */
	swedish_lk444ma_diffs,			/* 0x4c */
	belgian_lk444kb_diffs,			/* 0x4e */
};

/*
 * The following tables are used to hold the ALT-GR translations
 *  for the LK443 keyboards.
 */

xkey_t austrian_german_lk444kg_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c1,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c5,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x00c9,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x00cb,	0x00b3,		0x0000 }, /* threesuperior, NULL	*/
 { 0x00e0,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00e3,	0x00b5,		0x0000 }, /* mu, NULL	*/
 { 0x00e5,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00ea,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00ef,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f6,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x00f9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { -1, 0, 0 }
};

xkey_t belgian_lk444kb_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x00cb,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x00db,	0x005e,		0x0000 }, /* '^', NULL	*/
 { 0x00ea,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00ef,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f3,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x00f6,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00f7,	0x0060,		0x0000 }, /* '`', NULL	*/
 { 0x00fa,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00fb,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { -1, 0, 0 }
};

xkey_t danish_lk444kd_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x00cb,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x00d0,	0x0024,		0x0000 }, /* '$', NULL	*/
 { 0x00e0,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00e5,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00ea,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00ef,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f5,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x00f6,	0x007e,		0x0000 }, /* '~', NULL	*/
 { -1, 0, 0 }
};

xkey_t dutch_lk444gh_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x00c0,	0x00b9,		0x0000 }, /* onesuperior, NULL	*/
 { 0x00c3,	0x00ab,		0x0000 }, /* guillemotleft, NULL	*/
 { 0x00c5,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x00c7,	0x00df,		0x0000 }, /* ssharp, NULL	*/
 { 0x00c8,	0x00bb,		0x0000 }, /* guillemotright, NULL	*/
 { 0x00c9,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x00cb,	0x00b3,		0x0000 }, /* threesuperior, NULL	*/
 { 0x00ce,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x00d0,	0x00bc,		0x0000 }, /* onequarter, NULL	*/
 { 0x00d1,	0x00b6,		0x0000 }, /* paragraph, NULL	*/
 { 0x00d6,	0x00bd,		0x0000 }, /* onehalf, NULL	*/
 { 0x00db,	0x00be,		0x0000 }, /* threequarters, NULL	*/
 { 0x00e0,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x00e3,	0x00b5,		0x0000 }, /* mu, NULL	*/
 { 0x00e5,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00ea,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00ed,	0x00b7,		0x0000 }, /* periodcentered, NULL	*/
 { 0x00f5,	0x00b8,		0x0000 }, /* cedilla, NULL	*/
 { 0x00f9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { -1, 0, 0 }
};

xkey_t finnish_lk444ca_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x00cb,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x00d0,	0x0024,		0x0000 }, /* '$', NULL	*/
 { 0x00e0,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00e5,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00ea,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00ef,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f6,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x00f9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { -1, 0, 0 }
};

xkey_t french_canadian_lk444ac_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x00c0,	0x00b1,		0x0000 }, /* plusminus, NULL	*/
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c9,	0x00b0,		0x0000 }, /* degree, NULL	*/
 { 0x00cb,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x00d0,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x00d6,	0x00a4,		0x0000 }, /* currency, NULL	*/
 { 0x00db,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x00e0,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x00e3,	0x00b5,		0x0000 }, /* mu, NULL	*/
 { 0x00e5,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x00e8,	0x00af,		0x0000 }, /* macron, NULL	*/
 { 0x00ea,	0x00b3,		0x0000 }, /* threesuperior, NULL	*/
 { 0x00eb,	0x00a7,		0x0000 }, /* section, NULL	*/
 { 0x00ef,	0x00bc,		0x0000 }, /* onequarter, NULL	*/
 { 0x00f0,	0x00b6,		0x0000 }, /* paragraph, NULL	*/
 { 0x00f2,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x00f3,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x00f5,	0x00be,		0x0000 }, /* threequarters, NULL	*/
 { 0x00f6,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00f7,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f9,	0x00bd,		0x0000 }, /* onehalf, NULL	*/
 { 0x00fa,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00fb,	0x007b,		0x0000 }, /* '{', NULL	*/
 { -1, 0, 0 }
};

xkey_t french_lk444kp_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c5,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x00cb,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x00d0,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00d6,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00db,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x00e0,	0x0060,		0x0000 }, /* '`', NULL	*/
 { 0x00e5,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x00ea,	0x005e,		0x0000 }, /* '^', NULL	*/
 { 0x00ef,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00f5,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f6,	0x00a4,		0x0000 }, /* currency, NULL	*/
 { 0x00f9,	0x005d,		0x0000 }, /* ']', NULL	*/
 { -1, 0, 0 }
};

xkey_t italian_lk444ki_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00f2,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00f6,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00fa,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00fb,	0x0023,		0x0000 }, /* '#', NULL	*/
 { -1, 0, 0 }
};

xkey_t norwegian_lk444kn_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00cb,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x00d0,	0x0024,		0x0000 }, /* '$', NULL	*/
 { 0x00e0,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00e5,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00ea,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00ef,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f5,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x00f6,	0x007e,		0x0000 }, /* '~', NULL	*/
 { -1, 0, 0 }
};

xkey_t portuguese_lk444kv_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00cb,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x00d0,	0x00a7,		0x0000 }, /* section, NULL	*/
 { 0x00e0,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00e5,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00ea,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00ef,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00fa,	0x00a8,		0x0000 }, /* diaeresis, NULL	*/
 { -1, 0, 0 }
};

xkey_t spanish_lk444ks_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x00c0,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00cb,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x00db,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x00f6,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00f7,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00fa,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00fb,	0x007b,		0x0000 }, /* '{', NULL	*/
 { -1, 0, 0 }
};

xkey_t swedish_lk444ma_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c9,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x00cb,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x00d0,	0x0024,		0x0000 }, /* '$', NULL	*/
 { 0x00e0,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x00e5,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00ea,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00ef,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f6,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x00f9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { -1, 0, 0 }
};

xkey_t swiss_french_lk444ap_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x00cb,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x00db,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x00e0,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x00e5,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x00f5,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x00f6,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00f7,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f9,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x00fa,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00fb,	0x007b,		0x0000 }, /* '{', NULL	*/
 { -1, 0, 0 }
};

xkey_t swiss_german_lk444mh_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00c0,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x00c5,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x00c9,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x00cb,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x00db,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x00e0,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x00e5,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x00f5,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x00f6,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x00f7,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x00f9,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x00fa,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x00fb,	0x007b,		0x0000 }, /* '{', NULL	*/
 { -1, 0, 0 }
};

xkey_t uk_lk444ae_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x00bf,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { -1, 0, 0 }
};

xkey_t *lk443_altgrs[] = {
	danish_lk444kd_altgr,			/* 0x30 */
	austrian_german_lk444kg_altgr,		/* 0x32 */
	swiss_german_lk444mh_altgr,		/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 *//* US has none */
	uk_lk444ae_altgr,			/* 0x38 */
	spanish_lk444ks_altgr,			/* 0x3a */
	french_lk444kp_altgr,			/* 0x3c */
	french_canadian_lk444ac_altgr,		/* 0x3e */
	swiss_french_lk444ap_altgr,		/* 0x40 */
	italian_lk444ki_altgr,			/* 0x42 */
	dutch_lk444gh_altgr,			/* 0x44 */
	norwegian_lk444kn_altgr,		/* 0x46 */
	portuguese_lk444kv_altgr,		/* 0x48 */
	finnish_lk444ca_altgr,			/* 0x4a */
	swedish_lk444ma_altgr,			/* 0x4c */
	belgian_lk444kb_altgr,			/* 0x4e */
};

/* LK-series keyboard models */

char lk201_name[] = "LK201";
char lk401_name[] = "LK401";
char lk421_name[] = "LK421";
char lk443_name[] = "LK443";

/* for support of LK201/LK401/LK421 keyboards */

ws_keycode_modifiers lk201_modifiers[] = {
    { KEY_LOCK, LockMask},
    { KEY_SHIFT, ShiftMask},
    { KEY_SHIFT_R, ShiftMask},
    { KEY_CTRL, ControlMask},
    { KEY_ALT_L, Mod1Mask},
    { KEY_ALT_R, Mod1Mask},
    { KEY_COMPOSE, Mod2Mask},
    { KEY_COMPOSE_R, Mod2Mask},
};

ws_keyboard_definition lk201_definition = {
	0,
	LK201_GLYPHS_PER_KEY,		/* beware of this constant!!! */
	sizeof (lk201_keysyms) / sizeof (unsigned int),
	sizeof (lk201_modifiers) / sizeof (ws_keycode_modifiers),
	3
};

/* for support of LK443/LK444 keyboards */

ws_keycode_modifiers lk443_modifiers[] = {
    { KEY_LOCK, LockMask},
    { KEY_SHIFT, ShiftMask},
    { KEY_SHIFT_R, ShiftMask},
    { KEY_CTRL, ControlMask},
    { KEY_CTRL_R, ControlMask},
    { KEY_ALT_L, Mod1Mask},
    { KEY_ALT_R, Mod1Mask},
    { KEY_KP_NUMLOCK, Mod4Mask},
};

ws_keyboard_definition lk443_definition = {
	0,
	LK201_GLYPHS_PER_KEY,		/* beware of this constant!!! */
	sizeof (lk201_keysyms) / sizeof (unsigned int),
	sizeof (lk443_modifiers) / sizeof (ws_keycode_modifiers),
	3
};

/* private keyboard data */
extern ws_keyboard 	keyboard;
#define NLK201 1

#if 0
ws_keyboard_state lk201_softc[NLK201] = {
    lk201_getc,
    lk201_putc,
    90							/* was 75 in 4.L */,	/* timeout */
    9,							/* interval */
    &keyboard,
	0,							/* device number */
    0,							/* status */
    {0,0,0,0,0,0,0,0},			/* keys */
    NULL, NULL, 0
    };

/* lk201-specific public keyboard data */
extern void scc_enable_keyboard();	/* to enable keyboard interrupts */

ws_keyboard lk201_keyboard = {
    KB_LK401,				/* int hardware_type by default */
    0,						/* int axis_count no axis data */
    (caddr_t) lk201_softc,	/* caddr_t keyboard_handle private data */
    lk401_name,				/* default name */
    lk201_init_closure,			/* init_closure */
    NULL,				/* ioctl */
    lk201_up_down_mode,			/* init keyboard */
    lk201_reset_keyboard,		/* reset (close to def lk201) state */
    scc_enable_keyboard,		/* enable interrupts */
    NULL,				/* can't disable */
    lk201_set_keyboard_control,		/* set_keyboard_control */
    NULL,				/* get_keyboard_info */
    lk201_ring_bell,			/* ring_bell */
    lk201_keyboard_event,		/* process_keyboard_event */
    lk201_keyboard_char,		/* process_keyboard_char */
    { 0, 0, 50, 50, 400, 100,
	  1,				/* autorep on, except for modifiers,
					   return */
	  {
	      0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
	      0xffffffff, 0xdff807ff, 0xffffffff, 0xffffffff,
	  },
	  0},				/* leds */
    &lk201_definition,
    lk201_modifiers,
    lk201_keysyms,
    lk201_keycodes,
};
#endif
#endif /* BINARY */
