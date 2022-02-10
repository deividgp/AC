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
 * @(#)$RCSfile: pcxal_data.c,v $ $Revision: 1.1.35.2 $ (DEC) $Date: 1998/06/26 19:21:03 $
 */

#include <sys/types.h>
#include <kern/queue.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <sys/keysyms.h>
#include <io/dec/ws/pcxal.h>

#ifdef BINARY

extern char pcxal_keycodes[];
extern char pcxal_keysyms[];
extern ws_keycode_modifiers pcxal_modifiers[];
extern ws_keyboard_definition pcxal_definition;
extern ws_keyboard_state pcxal_softc[];
extern ws_keyboard pcxal_keyboard;

extern xlate_t pcxal_xlate[];
extern xkey_t *pcxal_altgr;

extern xkey_t *pcxal_diffs[];
extern xkey_t *pcxal_altgrs[];
extern xkey_t  pcxal_to_lk411_diffs[];
extern xkey_t *pc411_diffs[];
extern xkey_t *pc411_altgrs[];

extern unsigned int mode_3_autorepeats[];

extern char pcxal_name[];
extern char lk411_name[];

#else /* BINARY */

/*
 * Note that if a keycode appears additional times, it defines further
 * symbols on the the same keycode.  DDX translates this to the appropriate
 * data structure.  All this is to save bytes in the kernel.
 * WARNING: keycodes and keysym tables must be EXACTLY in sync!
 */
unsigned char pcxal_keycodes[] = {
    KEY_ESC,
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
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_HELP,
    KEY_DO,
    KEY_F17,
    KEY_PRINT_SCREEN,
    KEY_SCROLL_LOCK,
    KEY_PAUSE,

    KEY_INSERT,
    KEY_HOME,
    KEY_PAGE_UP,
    KEY_DELETE,
    KEY_END,
    KEY_PAGE_DOWN,

    KEY_KP_0,
    KEY_KP_PERIOD,
    KEY_KP_ENTER,
    KEY_KP_1,
    KEY_KP_2,
    KEY_KP_3,
    KEY_KP_4,
    KEY_KP_5,
    KEY_KP_6,
    KEY_KP_PLUS,
    KEY_KP_7,
    KEY_KP_8,
    KEY_KP_9,
    KEY_KP_NUMLOCK,
    KEY_KP_SLASH,
    KEY_KP_STAR,
    KEY_KP_HYPHEN,

    KEY_LEFT,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_UP,

    KEY_SHIFT_L,
    KEY_SHIFT_R,
    KEY_CTRL_L,
    KEY_CTRL_R,
    KEY_CAPS_LOCK,
    KEY_ALT_L,
    KEY_ALT_L,
    KEY_ALT_R,
    KEY_ALT_R,
    KEY_COMPOSE_L,

    KEY_BACKSPACE,
    KEY_ENTER,
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

    KEY_VBAR_102,
    KEY_VBAR_102,

    KEY_TILDE_102J,
    KEY_TILDE_102J,

    KEY_UBAR_J,
    KEY_UBAR_J,

    KEY_VBAR_J,
    KEY_VBAR_J,

    KEY_MUHENKAN,

    KEY_HENKAN,

    KEY_HIRAGANA,
};

unsigned int pcxal_keysyms[] = {
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
    XK_F11,
    XK_F12,
    XK_F13,
    XK_F14,
    XK_Help,
    XK_Menu,
    XK_F17,
    XK_Print,
    XK_Scroll_Lock,
    XK_Pause,

    XK_Insert,
    XK_Home,
    XK_Prior,
    XK_Delete,
    XK_End,
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
    XK_KP_Add,
    XK_KP_7,
    XK_KP_8,
    XK_KP_9,
    XK_Num_Lock,
    XK_KP_Divide,
    XK_KP_Multiply,
    XK_KP_Subtract,

    XK_Left,
    XK_Right,
    XK_Down,
    XK_Up,

    XK_Shift_L,
    XK_Shift_R,
    XK_Control_L,
    XK_Control_R,
    XK_Caps_Lock,
    XK_Alt_L,
    XK_Meta_L,
    XK_Alt_R,
    XK_Meta_R,
    XK_Meta_L,

    XK_BackSpace,
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

    XK_backslash,
    XK_bar,

    XK_numbersign,
    XK_asciitilde,

    XK_backslash,
    XK_underscore,

    XK_backslash,
    XK_bar,

    XK_Muhenkan,

    XK_Henkan,

    XK_Hiragana_Katakana,

};

ws_keycode_modifiers pcxal_modifiers[] = {
    { KEY_CAPS_LOCK, LockMask},
    { KEY_SHIFT_L, ShiftMask},
    { KEY_SHIFT_R, ShiftMask},
    { KEY_CTRL_L, ControlMask},
    { KEY_CTRL_R, ControlMask},
    { KEY_ALT_L, Mod1Mask},
    { KEY_ALT_R, Mod1Mask},
    { KEY_KP_NUMLOCK, Mod4Mask},
};

ws_keyboard_definition pcxal_definition = {
	0,
	PCXAL_GLYPHS_PER_KEY,		/* beware of this constant!!! */
	sizeof (pcxal_keysyms) / sizeof (unsigned int),
	sizeof (pcxal_modifiers) / sizeof (ws_keycode_modifiers),
	3
};

extern ws_keyboard 	keyboard;

#define NPCXAL 1

char pcxal_name[] = "PCXAL";
char lk411_name[] = "LK411";

extern int pcxal_getc();
extern ws_keyboard_state pcxal_softc[NPCXAL];
/* 
 * pcxal-specific public keyboard data 
*/
ws_keyboard pcxal_keyboard = {
    KB_PCXAL,			/* int  hardware_type by default */
    0,					/* int axis_count no axis data */
    (caddr_t) pcxal_softc,	/* caddr_t keyboard_handle private data */
    pcxal_name,				/* char *name */
    pcxal_init_closure,	/* caddr_t (*init_keyboard_handle)() init_closure */
    NULL,				/* int (*ioctl)() */
    NULL,				/* void (*init_keyboard)() */
    pcxal_reset_keyboard, /* void (*reset_keyboard)() reset state */
    pcxal_enable_keyboard,/* void (*enable_keyboard)() enable interrupts */
    NULL,				/* void (*disable_keyboard)() disable */
    pcxal_set_keyboard_control,	/* int  (*set_keyboard_control)() */
    NULL,				/* void (*get_keyboard_info)() */
    pcxal_ring_bell,	/* void (*ring_bell)() */
    pcxal_keyboard_event,/* void (*process_keyboard_event)() */
    (void (*)(caddr_t, u_short))pcxal_keyboard_char,
						/* void (*process_keyboard_char)(caddr_t, u_short) */
/* FIXME FIXME FIXME FIXME */
    {	0,			/* device_number */
	0,			/* flags */
	0,			/* click */
	50,			/* bell */
	440,			/* bell_pitch (middle A :-) */
	100,			/* bell_duration (100 milliseconds) */
	1,			/* autorep on, except for modifiers,
					   return */
	  {
	      0, 0, 0, 0, 0, 0, 0, 0,	/* autorepeats */
	  },
	  0},				/* leds */
/* end FIXME FIXME FIXME FIXME */
    &pcxal_definition,
    pcxal_modifiers,
    pcxal_keysyms,
    pcxal_keycodes,
};

unsigned int mode_3_autorepeats[8] = {
	0xfde9ffff, 0xfdffffff, 0x78ffffff, 0xfdbfffff, 
	0xffffffff, 0xdfffffff, 0xffffffff, 0xffffffff,
};

/****************************************/
/* originally from io/dec/isa/kbdscan.h */
/****************************************/


/*
 * holds a pointer to the ALT-GR table for the current keyboard/language
 */
xkey_t *pcxal_altgr = (xkey_t *)NULL;

/*
 * Main translation table for PCXAL and LK411/LK450 keyboards
 *
 * Index by scan code from a 101 or 102 key
 *  keyboard which generates PS/2 style keycodes.
 *
 * NOTE: the scancodes used here are those generated by the keyboard
 *       when it is in scanmode 3.
 */

xlate_t pcxal_xlate[] = { /* by default, use PCXAL US keymap */
/* unshifted  shifted  */	/* Scan, key number		*/
 { 	0,	0	},	/* 0x00, Key num 0 		*/
 { 	0,	0	},	/* 0x01, Key num 0 		*/
 { 	0,	0	},	/* 0x02, Key num 0 		*/
 { 	0,	0	},	/* 0x03, Key num 0 		*/
 { 	0,	0	},	/* 0x04, Key num 0 		*/
 { 	0,	0	},	/* 0x05, Key num 0 		*/
 { 	0,	0	},	/* 0x06, Key num 0 		*/
 { 	F1,	F1	},	/* 0x07, Key num 112 		*/
 { 	033,	033	},	/* 0x08, Key num 110, ESC 	*/
 { 	LK_F13,	LK_F13	},	/* 0x09, Key num 201, F13	*//* LK411 */
 { 	F14,	F14	},	/* 0x0a, Key num 202, F14	*//* LK411 */
 { 	HELP,	HELP	},	/* 0x0b, Key num 203, HELP	*//* LK411 */
 { 	DO,	DO	},	/* 0x0c, Key num 204, DO	*//* LK411 */
 { 	'\t',	'\t'	},	/* 0x0D, Key num 16 		*/
 { 	'`',	'~',	},	/* 0x0E, Key num 1 		*/
 { 	F2,	F2	},	/* 0x0F, Key num 113 		*/
 { 	F17,	F17	},	/* 0x10, Key num 205, F17	*//* LK411 */
 { 	MOD_CTRL_L,	0},	/* 0x11, Key num 58, CTRL_L	*/
 { 	MOD_SHFT_L,	0},	/* 0x12, Key num 44, SHFT_L	*/
 { 	'-',	'-'	},	/* 0x13, Key num 206, KP-	*//* LK411 */
 { 	MOD_CAPS,	0},	/* 0x14, Key num 30, CAPS	*/
 { 	'q',	'Q'	},	/* 0x15, Key num 17 		*/
 { 	'1',	'!'	},	/* 0x16, Key num 2 		*/
 { 	F3,	F3	},	/* 0x17, Key num 114 		*/
 { 	0,	0	},	/* 0x18, Key num 0 		*/
 { 	MOD_ALT_L,	0},	/* 0x19, Key num 60, ALT_L	*/
 { 	'z',	'Z'	},	/* 0x1A, Key num 46 		*/
 { 	's',	'S'	},	/* 0x1B, Key num 32 		*/
 { 	'a',	'A'	},	/* 0x1C, Key num 31 		*/
 { 	'w',	'W'	},	/* 0x1D, Key num 18 		*/
 { 	'2',	'@'	},	/* 0x1E, Key num 3 		*/
 { 	F4,	F4	},	/* 0x1F, Key num 115 		*/
 { 	0,	0	},	/* 0x20, Key num 0 		*/
 { 	'c',	'C'	},	/* 0x21, Key num 48 		*/
 { 	'x',	'X'	},	/* 0x22, Key num 47 		*/
 { 	'd',	'D'	},	/* 0x23, Key num 33 		*/
 { 	'e',	'E'	},	/* 0x24, Key num 19 		*/
 { 	'4',	'$'	},	/* 0x25, Key num 5 		*/
 { 	'3',	'#'	},	/* 0x26, Key num 4 		*/
 { 	F5,	F5	},	/* 0x27, Key num 116 		*/
 { 	MOD_COMP_L,	0},	/* 0x28, Key num 207, COMP_L	*//* LK411 */
 { 	' ',	' '	},	/* 0x29, Key num 61 		*/
 { 	'v',	'V'	},	/* 0x2A, Key num 49 		*/
 { 	'f',	'F'	},	/* 0x2B, Key num 34 		*/
 { 	't',	'T'	},	/* 0x2C, Key num 21 		*/
 { 	'r',	'R'	},	/* 0x2D, Key num 20 		*/
 { 	'5',	'%'	},	/* 0x2E, Key num 6 		*/
 { 	F6,	F6	},	/* 0x2F, Key num 117 		*/
 { 	0,	0	},	/* 0x30, Key num 0 		*/
 { 	'n',	'N'	},	/* 0x31, Key num 51 		*/
 { 	'b',	'B'	},	/* 0x32, Key num 50 		*/
 { 	'h',	'H'	},	/* 0x33, Key num 36 		*/
 { 	'g',	'G'	},	/* 0x34, Key num 35 		*/
 { 	'y',	'Y'	},	/* 0x35, Key num 22 		*/
 { 	'6',	'^'	},	/* 0x36, Key num 7 		*/
 { 	F7,	F7	},	/* 0x37, Key num 118 		*/
 { 	0,	0	},	/* 0x38, Key num 0 		*/
 { 	MOD_ALT_R,	0},	/* 0x39, Key num 62, ALT_R	*/
 { 	'm',	'M'	},	/* 0x3A, Key num 52 		*/
 { 	'j',	'J'	},	/* 0x3B, Key num 37 		*/
 { 	'u',	'U'	},	/* 0x3C, Key num 23 		*/
 { 	'7',	'&'	},	/* 0x3D, Key num 8 		*/
 { 	'8',	'*'	},	/* 0x3E, Key num 9 		*/
 { 	F8,	F8	},	/* 0x3F, Key num 119 		*/
 { 	0,	0	},	/* 0x40, Key num 0 		*/
 { 	',',	'<'	},	/* 0x41, Key num 53 		*/
 { 	'k',	'K'	},	/* 0x42, Key num 38 		*/
 { 	'i',	'I'	},	/* 0x43, Key num 24 		*/
 { 	'o',	'O'	},	/* 0x44, Key num 25 		*/
 { 	'0',	')'	},	/* 0x45, Key num 11 		*/
 { 	'9',	'('	},	/* 0x46, Key num 10 		*/
 { 	F9,	F9	},	/* 0x47, Key num 120 		*/
 { 	0,	0	},	/* 0x48, Key num 0 		*/
 { 	'.',	'>'	},	/* 0x49, Key num 54 		*/
 { 	'/',	'?'	},	/* 0x4A, Key num 55 		*/
 { 	'l',	'L'	},	/* 0x4B, Key num 39 		*/
 { 	';',	':'	},	/* 0x4C, Key num 40 		*/
 { 	'p',	'P'	},	/* 0x4D, Key num 26 		*/
 { 	'-',	'_'	},	/* 0x4E, Key num 12 		*/
 { 	F10,	F10	},	/* 0x4F, Key num 121 		*/
 { 	0,	0	},	/* 0x50, Key num 0 		*/
 { 	0,	0	},	/* 0x51, Key num 0 		*/
 { 	0x27,	0x22	},	/* 0x52, Key num 41 		*/
 { 	0,	0	},	/* 0x53, Key num 0 		*/
 { 	'[',	'{'	},	/* 0x54, Key num 27 		*/
 { 	'=',	'+'	},	/* 0x55, Key num 13 		*/
 { 	F11,	F11	},	/* 0x56, Key num 122 		*/
 { 	PRTSC,	PRTSC	},	/* 0x57, Key num 124 		*/
 { 	MOD_CTRL_R,	0},	/* 0x58, Key num 64, CTRL_R	*/
 { 	MOD_SHFT_R,	0},	/* 0x59, Key num 57, SHFT_R	*/
 { 	'\r',	'\r'	},	/* 0x5A, Key num 43 		*/
 { 	']',	'}'	},	/* 0x5B, Key num 28 		*/
 { 	'\\',	'|'	},	/* 0x5C, Key num 29 		*/
 { 	0,	0	},	/* 0x5d, Key num 0 		*/
 { 	F12,	F12	},	/* 0x5E, Key num 123 		*/
 { 	MOD_SCROLL,	0},	/* 0x5F, Key num 125, SCROLL	*/
 { 	DOWN,	DOWN	},	/* 0x60, Key num 84 		*/
 { 	LEFT,	LEFT	},	/* 0x61, Key num 79 		*/
 { 	PAUSE,	PAUSE	},	/* 0x62, Key num 126 		*/
 { 	UP,	UP	},	/* 0x63, Key num 83 		*/
 { 	DELE,	DELE	},	/* 0x64, Key num 76 		*/
 { 	END,	END	},	/* 0x65, Key num 81 		*/
 { 	DELE,	DELE	},	/* 0x66, Key num 15 		*/
 { 	INS,	INS	},	/* 0x67, Key num 75 		*/
 { 	0,	0	},	/* 0x68, Key num 0 		*/
 { 	END_NPAD, '1'	},	/* 0x69, Key num 93 		*/
 { 	RIGHT,	RIGHT	},	/* 0x6A, Key num 89 		*/
 { 	LEFT_NPAD, '4'	},	/* 0x6B, Key num 92 		*/
 { 	HOME_NPAD, '7'	},	/* 0x6C, Key num 91 		*/
 { 	PGDWN,	PGDWN	},	/* 0x6D, Key num 86 		*/
 { 	HOME,	HOME	},	/* 0x6E, Key num 80 		*/
 { 	PGUP,	PGUP	},	/* 0x6F, Key num 85 		*/
 { 	INS_NPAD, '0'	},	/* 0x70, Key num 99 		*/
 { 	DELE_NPAD, '.'	},	/* 0x71, Key num 104 		*/
 { 	DOWN_NPAD, '2'	},	/* 0x72, Key num 98 		*/
 { 	MIDDLE_NPAD, '5'},	/* 0x73, Key num 97 		*/
 { 	RIGHT_NPAD, '6'	},	/* 0x74, Key num 102 		*/
 { 	UP_NPAD, '8'	},	/* 0x75, Key num 96 		*/
 { 	MOD_NUML,	0},	/* 0x76, Key num 90, NUML	*/
 { 	'/',	'/'	},	/* 0x77, Key num 95 		*/
 { 	0,	0	},	/* 0x78, Key num 0 		*/
 { 	'\r',	'\r'	},	/* 0x79, Key num 108 	*/
 { 	PGDWN_NPAD, '3'	},	/* 0x7A, Key num 103 		*/
 { 	0,	0	},	/* 0x7b, Key num 0 		*/
 { 	'+',	'+'	},	/* 0x7C, Key num 106 		*/
 { 	PGUP_NPAD, '9'	},	/* 0x7D, Key num 101 		*/
 { 	'*',	'*'	},	/* 0x7E, Key num 100 		*/
 { 	0,	0	},	/* 0x7f, Key num 0 		*/
 { 	0,	0	},	/* 0x80, Key num 0 		*/
 { 	0,	0	},	/* 0x81, Key num 0 		*/
 { 	0,	0	},	/* 0x82, Key num 0 		*/
 { 	0,	0	},	/* 0x83, Key num 0 		*/
 { 	'-',	'-'	},	/* 0x84, Key num 105 		*/
 { 	0,	0	},	/* 0x85, Key num 0 		*/
 { 	0,	0	},	/* 0x86, Key num 0 		*/
 { 	0,	0	},	/* 0x87, Key num 0 		*/
};

/************************************************************************
 * here are all the tables related to the PCXAL keyboard series
 */

/*
 * the following tables hold the differences between the given keyboard
 *  and the default keyboard (PCXAL US)
 */

xkey_t danish_pcxalkd_diffs[] = { /* Dansk */
/* keycode  unshifted  shifted  */	/* Scan, key number		*/
 { 0x0e, 	0xbd,	0xa7	},	/* 0x0E, Key num 1 		*/
 { 0x13, 	'<',	'>'	},	/* 0x13, Key num 45 		*/
 { 0x1e, 	'2',	0x22	},	/* 0x1E, Key num 3 		*/
 { 0x25, 	'4',	0xa4	},	/* 0x25, Key num 5 		*/
 { 0x36,	'6',	'&'	},	/* 0x36, Key num 7 		*/
 { 0x3d,	'7',	'/'	},	/* 0x3D, Key num 8 		*/
 { 0x3e,	'8',	'('	},	/* 0x3E, Key num 9 		*/
 { 0x41,	',',	';'	},	/* 0x41, Key num 53 		*/
 { 0x45,	'0',	'='	},	/* 0x45, Key num 11 		*/
 { 0x46,	'9',	')'	},	/* 0x46, Key num 10 		*/
 { 0x49,	'.',	':'	},	/* 0x49, Key num 54 		*/
 { 0x4a,	'-',	'_'	},	/* 0x4a, Key num 12 		*/
 { 0x4c,	0xe6,	0xc6	},	/* 0x4C, Key num 40 		*/
 { 0x4e,	'+',	'?'	},	/* 0x4E, Key num 12 		*/
 { 0x52,	0xf8,	0xd8	},	/* 0x52, Key num 41 		*/
 { 0x53,	'\'',	'*'	},	/* 0x53, Key num 0 		*/
 { 0x54,	0xe5,	0xc5	},	/* 0x54, Key num 27 		*/
 { 0x55,	0xb4,	'`'	},	/* 0x55, Key num 13 		*/
 { 0x5b,	0xa8,	'^'	},	/* 0x5B, Key num 28 		*/
 {   -1, 	0,	0	},	/* NULL entry to end 		*/
};

xkey_t austrian_german_pcxalkg_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005e,		0x00b0 }, /* ^, , degree	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x0015,	0x0071,		0x0051 }, /* q, , Q	*/
 { 0x001a,	0x0079,		0x0059 }, /* y, , Y	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0026,	0x0033,		0x00a3 }, /* 3, , sterling	*/
 { 0x0035,	0x007a,		0x005a }, /* z, , Z	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003a,	0x006d,		0x004d }, /* m, , M	*/
 { 0x003d,	0x0037,		0x002f }, /* 7, , /	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00f6,		0x00d6 }, /* odiaeresis, Odiaeresis	*/
 { 0x004e,	0x00df,		0x003f }, /* ssharp, ?	*/
 { 0x0052,	0x00e4,		0x00c4 }, /* adiaeresis, Adiaeresis	*/
 { 0x0053,	0x0023,		0x0027 }, /* #, , '	*/
 { 0x0054,	0x00fc,		0x00dc }, /* udiaeresis, Udiaeresis	*/
 { 0x0055,	0x00b4,		0x0060 }, /* acute, `	*/
 { 0x005b,	0x002b,		0x002a }, /* +, , *	*/
 { -1, 0, 0 }
};

xkey_t swiss_german_pcxalmh_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x00a7,		0x00b0 }, /* section, degree	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x0016,	0x0031,		0x002b }, /* 1, , +	*/
 { 0x001a,	0x0079,		0x0059 }, /* y, , Y	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0025,	0x0034,		0x00e7 }, /* 4, , ccedilla	*/
 { 0x0026,	0x0033,		0x002a }, /* 3, , *	*/
 { 0x0035,	0x007a,		0x005a }, /* z, , Z	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003d,	0x0037,		0x002f }, /* 7, , /	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00f6,		0x00e9 }, /* odiaeresis, eacute	*/
 { 0x004e,	0x002b,		0x003f }, /* +, , ?	*/
 { 0x0052,	0x00e4,		0x00e0 }, /* adiaeresis, agrave	*/
 { 0x0053,	0x0024,		0x00a3 }, /* $, , sterling	*/
 { 0x0054,	0x00fc,		0x00e8 }, /* udiaeresis, egrave	*/
 { 0x0055,	0x005e,		0x0060 }, /* ^, , `	*/
 { 0x005b,	0x00a8,		0x0021 }, /* diaeresis, !	*/
 { -1, 0, 0 }
};

xkey_t uk_pcxalae_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x0060,		0x00ac }, /* `, , notsign	*/
 { 0x0013,	0x005c,		0x007c }, /* \, , |	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0026,	0x0033,		0x00a3 }, /* 3, , sterling	*/
 { 0x0052,	0x0027,		0x0040 }, /* ', , @	*/
 { 0x0053,	0x0023,		0x007e }, /* #, , ~	*/
 { -1, 0, 0 }
};

xkey_t spanish_pcxalks_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x00ba,		0x00aa }, /* masculine, ordfeminine	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x0016,	0x0031,		0x0021 }, /* 1, , !	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0026,	0x0033,		0x00b7 }, /* 3, , periodcentered	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003d,	0x0037,		0x002f }, /* 7, , /	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00f1,		0x00d1 }, /* ntilde, Ntilde	*/
 { 0x004e,	0x0027,		0x003f }, /* ', , ?	*/
 { 0x0052,	0x00b4,		0x00a8 }, /* acute, diaeresis	*/
 { 0x0053,	0x00e7,		0x00c7 }, /* ccedilla, Ccedilla	*/
 { 0x0054,	0x0060,		0x005e }, /* `, , ^	*/
 { 0x0055,	0x00a1,		0x00bf }, /* exclamdown, questiondown	*/
 { 0x005b,	0x002b,		0x002a }, /* +, , *	*/
 { -1, 0, 0 }
};

xkey_t french_pcxalkp_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x00b2,		0x00b2 }, /* twosuperior, twosuperior	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x0015,	0x0061,		0x0041 }, /* a, , A	*/
 { 0x0016,	0x0026,		0x0031 }, /* &, , 1	*/
 { 0x001a,	0x0077,		0x0057 }, /* w, , W	*/
 { 0x001c,	0x0071,		0x0051 }, /* q, , Q	*/
 { 0x001d,	0x007a,		0x005a }, /* z, , Z	*/
 { 0x001e,	0x00e9,		0x0032 }, /* eacute, 2	*/
 { 0x0025,	0x0027,		0x0034 }, /* ', , 4	*/
 { 0x0026,	0x0022,		0x0033 }, /* quotedbl, , 3	*/
 { 0x002e,	0x0028,		0x0035 }, /* (, , 5	*/
 { 0x0036,	0x002d,		0x0036 }, /* -, , 6	*/
 { 0x003a,	0x002c,		0x003f }, /* ,, , ?	*/
 { 0x003d,	0x00e8,		0x0037 }, /* egrave, 7	*/
 { 0x003e,	0x005f,		0x0038 }, /* _, , 8	*/
 { 0x0041,	0x003b,		0x002e }, /* ;, , .	*/
 { 0x0045,	0x00e0,		0x0030 }, /* agrave, 0	*/
 { 0x0046,	0x00e7,		0x0039 }, /* ccedilla, 9	*/
 { 0x0049,	0x003a,		0x002f }, /* :, , /	*/
 { 0x004a,	0x0021,		0x00a7 }, /* !, , section	*/
 { 0x004c,	0x006d,		0x004d }, /* m, , M	*/
 { 0x004e,	0x0029,		0x00b0 }, /* ), , degree	*/
 { 0x0052,	0x00f9,		0x0025 }, /* ugrave, %	*/
 { 0x0053,	0x002a,		0x00b5 }, /* *, , mu	*/
 { 0x0054,	0x005e,		0x00a8 }, /* ^, , diaeresis	*/
 { 0x0055,	0x003d,		0x002b }, /* =, , +	*/
 { 0x005b,	0x0024,		0x00a3 }, /* $, , sterling	*/
 { -1, 0, 0 }
};

xkey_t french_canadian_pcxalac_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x0023,		0x007c }, /* #, , |	*/
 { 0x0013,	0x00ab,		0x00bb }, /* guillemotleft, guillemotright */
 { 0x0016,	0x0031,		0x0021 }, /* 1, , !	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0025,	0x0034,		0x0024 }, /* 4, , $	*/
 { 0x0026,	0x0033,		0x002f }, /* 3, , /	*/
 { 0x002e,	0x0035,		0x0025 }, /* 5, , %	*/
 { 0x0036,	0x0036,		0x003f }, /* 6, , ?	*/
 { 0x003a,	0x006d,		0x004d }, /* m, , M	*/
 { 0x003d,	0x0037,		0x0026 }, /* 7, , &	*/
 { 0x003e,	0x0038,		0x002a }, /* 8, , *	*/
 { 0x0041,	0x002c,		0x0027 }, /* ,, , '	*/
 { 0x0044,	0x006f,		0x004f }, /* o, , O	*/
 { 0x0045,	0x0030,		0x0029 }, /* 0, , )	*/
 { 0x0046,	0x0039,		0x0028 }, /* 9, , (	*/
 { 0x0049,	0x002e,		0x002e }, /* ., , .	*/
 { 0x004a,	0x00e9,		0x00c9 }, /* eacute, Eacute	*/
 { 0x004c,	0x003b,		0x003a }, /* ;, , :	*/
 { 0x004d,	0x0070,		0x0050 }, /* p, , P	*/
 { 0x004e,	0x002d,		0x005f }, /* -, , _	*/
 { 0x0052,	0x0060,		0x0060 }, /* `, , `	*/
 { 0x0053,	0x003c,		0x003e }, /* <, , >	*/
 { 0x0054,	0x005e,		0x005e }, /* ^, , ^	*/
 { 0x0055,	0x003d,		0x002b }, /* =, , +	*/
 { 0x005b,	0x00e7,		0x00a8 }, /* ccedilla, diaeresis	*/
 { -1, 0, 0 }
};

xkey_t swiss_french_pcxalap_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x00a7,		0x00b0 }, /* section, degree	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x0016,	0x0031,		0x002b }, /* 1, , +	*/
 { 0x001a,	0x0079,		0x0059 }, /* y, , Y	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0025,	0x0034,		0x00e7 }, /* 4, , ccedilla	*/
 { 0x0026,	0x0033,		0x002a }, /* 3, , *	*/
 { 0x0035,	0x007a,		0x005a }, /* z, , Z	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003d,	0x0037,		0x002f }, /* 7, , /	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00e9,		0x00f6 }, /* eacute, odiaeresis	*/
 { 0x004e,	0x0027,		0x003f }, /* ', , ?	*/
 { 0x0052,	0x00e0,		0x00e4 }, /* agrave, adiaeresis	*/
 { 0x0053,	0x0024,		0x00a3 }, /* $, , sterling	*/
 { 0x0054,	0x00e8,		0x00fc }, /* egrave, udiaeresis	*/
 { 0x0055,	0x005e,		0x0060 }, /* ^, , `	*/
 { 0x005b,	0x00a8,		0x0021 }, /* diaeresis, !	*/
 { -1, 0, 0 }
};

xkey_t italian_pcxalki_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x007c }, /* \, , |	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0026,	0x0033,		0x00a3 }, /* 3, , sterling	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003d,	0x0037,		0x002f }, /* 7, , /	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00f2,		0x00e7 }, /* ograve, ccedilla	*/
 { 0x004e,	0x0027,		0x003f }, /* ', , ?	*/
 { 0x0052,	0x00e0,		0x00b0 }, /* agrave, degree	*/
 { 0x0053,	0x00f9,		0x00a7 }, /* ugrave, section	*/
 { 0x0054,	0x00e8,		0x00e9 }, /* egrave, eacute	*/
 { 0x0055,	0x00ec,		0x005e }, /* igrave, circum	*/
 { 0x005b,	0x002b,		0x002a }, /* +, , *	*/
 { -1, 0, 0 }
};

xkey_t dutch_pcxalgh_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x0040,		0x00a7 }, /* @, , section	*/
 { 0x0013,	0x005d,		0x005b }, /* ], , [	*/
 { 0x0016,	0x0031,		0x0021 }, /* 1, , !	*/
 { 0x001a,	0x007a,		0x005a }, /* z, , Z	*/
 { 0x001b,	0x0073,		0x0053 }, /* s, , S	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0021,	0x0063,		0x0043 }, /* c, , C	*/
 { 0x0022,	0x0078,		0x0058 }, /* x, , X	*/
 { 0x0025,	0x0034,		0x0024 }, /* 4, , $	*/
 { 0x0026,	0x0033,		0x0023 }, /* 3, , #	*/
 { 0x002d,	0x0072,		0x0052 }, /* r, , R	*/
 { 0x002e,	0x0035,		0x0025 }, /* 5, , %	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003a,	0x006d,		0x004d }, /* m, , M	*/
 { 0x003d,	0x0037,		0x005f }, /* 7, , _	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x0027 }, /* 0, , '	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x003d }, /* -, , =	*/
 { 0x004c,	0x002b,		0x00b1 }, /* +, , plusminus	*/
 { 0x004e,	0x002f,		0x003f }, /* /, , ?	*/
 { 0x0052,	0x00b4,		0x0060 }, /* acute, `	*/
 { 0x0053,	0x003c,		0x003e }, /* <, , >	*/
 { 0x0054,	0x00a8,		0x005e }, /* diaeresis, ^	*/
 { 0x0055,	0x00b0,		0x007e }, /* degree, ~	*/
 { 0x005b,	0x002a,		0x00a6 }, /* *, , brokenbar	*/
 { -1, 0, 0 }
};

xkey_t norwegian_pcxalkn_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x007c,		0x00a7 }, /* |, , section	*/
 { 0x0013,	0x005c,		0x007c }, /* \, , |	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0025,	0x0034,		0x00a4 }, /* 4, , currency	*/
 { 0x0026,	0x0033,		0x0023 }, /* 3, , #	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003d,	0x0037,		0x002f }, /* 7, , /	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00f8,		0x00d8 }, /* oslash, Ooblique	*/
 { 0x004e,	0x002b,		0x003f }, /* +, , ?	*/
 { 0x0052,	0x00e6,		0x00c6 }, /* ae, AE	*/
 { 0x0053,	0x0027,		0x002a }, /* ', , *	*/
 { 0x0054,	0x00e5,		0x00c5 }, /* aring, Aring	*/
 { 0x0055,	0x005c,		0x0060 }, /* \, , `	*/
 { 0x005b,	0x00a8,		0x005e }, /* diaeresis, ^	*/
 { -1, 0, 0 }
};

xkey_t portuguese_pcxalkv_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x007c }, /* \, , |	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0025,	0x0034,		0x0024 }, /* 4, , $	*/
 { 0x0026,	0x0033,		0x0023 }, /* 3, , #	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003d,	0x0037,		0x005c }, /* 7, , \	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00e7,		0x00c7 }, /* ccedilla, Ccedilla	*/
 { 0x004e,	0x0027,		0x003f }, /* ', , ?	*/
 { 0x0052,	0x00ba,		0x00aa }, /* masculine, ordfeminine	*/
 { 0x0053,	0x007e,		0x005e }, /* ~, , ^	*/
 { 0x0054,	0x002b,		0x002a }, /* +, , *	*/
 { 0x0055,	0x00ab,		0x00bb }, /* guillemotleft, guillemotright */
 { 0x005b,	0x00b4,		0x0060 }, /* acute, `	*/
 { -1, 0, 0 }
};

xkey_t finnish_pcxalca_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x00a7,		0x00bd }, /* section, onehalf	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0025,	0x0034,		0x00a4 }, /* 4, , currency	*/
 { 0x0026,	0x0033,		0x0023 }, /* 3, , #	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003d,	0x0037,		0x002f }, /* 7, , /	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00f6,		0x00d6 }, /* odiaeresis, Odiaeresis	*/
 { 0x004e,	0x002b,		0x003f }, /* +, , ?	*/
 { 0x0052,	0x00e4,		0x00c4 }, /* adiaeresis, Adiaeresis	*/
 { 0x0053,	0x0027,		0x002a }, /* ', , *	*/
 { 0x0054,	0x00e5,		0x00c5 }, /* aring, Aring	*/
 { 0x0055,	0x00b4,		0x0060 }, /* acute, `	*/
 { 0x005b,	0x00a8,		0x005e }, /* diaeresis, ^	*/
 { -1, 0, 0 }
};

xkey_t swedish_pcxalma_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x00a7,		0x00bd }, /* section, onehalf	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x001e,	0x0032,		0x0022 }, /* 2, , quotedbl	*/
 { 0x0025,	0x0034,		0x00a4 }, /* 4, , currency	*/
 { 0x0026,	0x0033,		0x0023 }, /* 3, , #	*/
 { 0x0036,	0x0036,		0x0026 }, /* 6, , &	*/
 { 0x003d,	0x0037,		0x002f }, /* 7, , /	*/
 { 0x003e,	0x0038,		0x0028 }, /* 8, , (	*/
 { 0x0041,	0x002c,		0x003b }, /* ,, , ;	*/
 { 0x0045,	0x0030,		0x003d }, /* 0, , =	*/
 { 0x0046,	0x0039,		0x0029 }, /* 9, , )	*/
 { 0x0049,	0x002e,		0x003a }, /* ., , :	*/
 { 0x004a,	0x002d,		0x005f }, /* -, , _	*/
 { 0x004c,	0x00f8,		0x00d8 }, /* oslash, Ooblique	*/
 { 0x004e,	0x002b,		0x003f }, /* +, , ?	*/
 { 0x0052,	0x00e6,		0x00c6 }, /* ae, AE	*/
 { 0x0053,	0x0027,		0x002a }, /* ', , *	*/
 { 0x0054,	0x00e5,		0x00c5 }, /* aring, Aring	*/
 { 0x0055,	0x00b4,		0x0060 }, /* acute, `	*/
 { 0x005b,	0x00a8,		0x005e }, /* diaeresis, ^	*/
 { -1, 0, 0 }
};

xkey_t belgian_pcxalkb_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x00b2,		0x00b3 }, /* twosuperior, threesuperior	*/
 { 0x0013,	0x003c,		0x003e }, /* <, , >	*/
 { 0x0015,	0x0061,		0x0041 }, /* a, , A	*/
 { 0x0016,	0x0026,		0x0031 }, /* &, , 1	*/
 { 0x001a,	0x0077,		0x0057 }, /* w, , W	*/
 { 0x001c,	0x0071,		0x0051 }, /* q, , Q	*/
 { 0x001d,	0x007a,		0x005a }, /* z, , Z	*/
 { 0x001e,	0x00c9,		0x0032 }, /* Eacute, 2	*/
 { 0x0025,	0x0027,		0x0034 }, /* ', , 4	*/
 { 0x0026,	0x0022,		0x0033 }, /* quotedbl, , 3	*/
 { 0x002e,	0x0028,		0x0035 }, /* (, , 5	*/
 { 0x0036,	0x00a7,		0x0036 }, /* section, 6	*/
 { 0x003a,	0x002c,		0x003f }, /* ,, , ?	*/
 { 0x003d,	0x00c8,		0x0037 }, /* Egrave, 7	*/
 { 0x003e,	0x0021,		0x0038 }, /* !, , 8	*/
 { 0x0041,	0x003b,		0x002e }, /* ;, , .	*/
 { 0x0045,	0x00c0,		0x0030 }, /* Agrave, 0	*/
 { 0x0046,	0x00c7,		0x0039 }, /* Ccedilla, 9	*/
 { 0x0049,	0x003a,		0x002f }, /* :, , /	*/
 { 0x004a,	0x003d,		0x002b }, /* =, , +	*/
 { 0x004c,	0x006d,		0x004d }, /* m, , M	*/
 { 0x004e,	0x0029,		0x00b0 }, /* ), , degree	*/
 { 0x0052,	0x00d9,		0x0025 }, /* Ugrave, %	*/
 { 0x0053,	0x00b5,		0x00a3 }, /* mu, sterling	*/
 { 0x0054,	0x005e,		0x00a8 }, /* ^, , diaeresis	*/
 { 0x0055,	0x002d,		0x005f }, /* -, , _	*/
 { 0x005b,	0x0024,		0x002a }, /* $, , *	*/
 { -1, 0, 0 }
};

xkey_t jis_pcxalaj_diffs[] = {
 /* keycode      unshifted       shifted */
  { 0x001e,      '2',            '"'    }, /* 2, , " */
  { 0x0036,      '6',            '&'    }, /* 6, , & */
  { 0x003d,      '7',            '\''   }, /* 7, , ' */
  { 0x003e,      '8',            '('    }, /* 8, , ( */
  { 0x0046,      '9',            ')'    }, /* 9, , ) */
  { 0x0045,      '0',            '~'    }, /* 0, , ~ */
  { 0x004e,      '-',            '='    }, /* -, , = */
  { 0x0055,      '^',            '~'    }, /* ^, , ~ */
  { 0x005d,      '\\',           '|'    }, /* \, , | */
  { 0x0054,      '@',            '`'    }, /* @, , ` */
  { 0x005b,      '[',            '{'    }, /* [, , { */
  { 0x004c,      ';',            '+'    }, /* ;, , + */
  { 0x0052,      ':',            '*'    }, /* :, , * */
  { 0x0053,      ']',            '}'    }, /* ], , } */
  { 0x0051,      '\\',           '_'    }, /* \, , _ */
  { -1, 0, 0 }
 };

xkey_t *pcxal_diffs[] = {
	danish_pcxalkd_diffs,			/* 0x30 */
	austrian_german_pcxalkg_diffs,		/* 0x32 */
	swiss_german_pcxalmh_diffs,		/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 *//* US is default */
	uk_pcxalae_diffs,			/* 0x38 */
	spanish_pcxalks_diffs,			/* 0x3a */
	french_pcxalkp_diffs,			/* 0x3c */
	french_canadian_pcxalac_diffs,		/* 0x3e */
	swiss_french_pcxalap_diffs,		/* 0x40 */
	italian_pcxalki_diffs,			/* 0x42 */
	dutch_pcxalgh_diffs,			/* 0x44 */
	norwegian_pcxalkn_diffs,		/* 0x46 */
	portuguese_pcxalkv_diffs,		/* 0x48 */
	finnish_pcxalca_diffs,			/* 0x4a */
	swedish_pcxalma_diffs,			/* 0x4c */
	belgian_pcxalkb_diffs,			/* 0x4e */
	jis_pcxalaj_diffs,			/* 0x50 */
	(xkey_t *)NULL,				/* 0x52 *//*no ANSI PCXAL kbds*/
};


/*
 * The following tables are used to hold the ALT-GR translations
 *  for the PCXAL keyboards.
 */

xkey_t danish_pcxalkd_altgr[] = { /* Dansk */
/* keycode  unshifted  shifted  */	/* Scan, key number		*/
 { 0x13, 	'\\',	0	},	/* 0x13, Key num 45 		*/
 { 0x1e, 	'@',	0	},	/* 0x1E, Key num 3 		*/
 { 0x26, 	0xa3,	0	},	/* 0x26, Key num 4 		*/
 { 0x25, 	'$',	0	},	/* 0x25, Key num 5 		*/
 { 0x3d,	'{',	0	},	/* 0x3D, Key num 8 		*/
 { 0x3e,	'[',	0	},	/* 0x3E, Key num 9 		*/
 { 0x46,	']',	0	},	/* 0x46, Key num 10 		*/
 { 0x45,	'}',	0	},	/* 0x45, Key num 11 		*/
 { 0x55,	0xa6,	0	},	/* 0x55, Key num 13 		*/
 { 0x5b,	'~',	0	},	/* 0x5B, Key num 28 		*/
 {   -1, 	0,	0	},	/* NULL entry to end 		*/
};

xkey_t austrian_german_pcxalkg_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0013,	0x007c,		0x0000 }, /* |, NULL	*/
 { 0x0015,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x001e,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x0026,	0x00b3,		0x0000 }, /* threesuperior, NULL	*/
 { 0x003a,	0x00b5,		0x0000 }, /* mu, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ], NULL	*/
 { 0x004e,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x005b,	0x007e,		0x0000 }, /* ~, NULL	*/
 { -1, 0, 0 }
};

xkey_t swiss_german_pcxalmh_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0013,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x0016,	0x007c,		0x0000 }, /* |, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* #, NULL	*/
 { 0x0036,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x003d,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x003e,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x004e,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x0052,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x0053,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0055,	0x007e,		0x0000 }, /* ~, NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ], NULL	*/
 { -1, 0, 0 }
};

xkey_t uk_pcxalae_altgr[] = { /* English (British/Irish) */
/* keycode  unshifted  shifted  */	/* Scan, key number		*/
 { 0x0e, 	0xa6,	0	},	/* 0x0E, Key num 1 		*/
 {   -1, 	0,	0	},	/* NULL entry to end 		*/
};

xkey_t spanish_pcxalks_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0016,	0x007c,		0x0000 }, /* |, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* #, NULL	*/
 { 0x0036,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x0052,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x0053,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ], NULL	*/
 { -1, 0, 0 }
};

xkey_t french_pcxalkp_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x001e,	0x007e,		0x0000 }, /* ~, NULL	*/
 { 0x0025,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* #, NULL	*/
 { 0x002e,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0036,	0x007c,		0x0000 }, /* |, NULL	*/
 { 0x003d,	0x0060,		0x0000 }, /* `, NULL	*/
 { 0x003e,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x0045,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0046,	0x005e,		0x0000 }, /* ^, NULL	*/
 { 0x004e,	0x005d,		0x0000 }, /* ], NULL	*/
 { 0x0055,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x005b,	0x00a4,		0x0000 }, /* currency, NULL	*/
 { -1, 0, 0 }
};

xkey_t french_canadian_pcxalac_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x0013,	0x00b0,		0x0000 }, /* degree, NULL	*/
 { 0x0016,	0x00b1,		0x0000 }, /* plusminus, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0025,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x002e,	0x00a4,		0x0000 }, /* currency, NULL	*/
 { 0x0036,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x003a,	0x00b5,		0x0000 }, /* mu, NULL	*/
 { 0x003d,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x003e,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x0041,	0x00af,		0x0000 }, /* macron, NULL	*/
 { 0x0044,	0x00a7,		0x0000 }, /* section, NULL	*/
 { 0x0045,	0x00bc,		0x0000 }, /* onequarter, NULL	*/
 { 0x0046,	0x00b3,		0x0000 }, /* threesuperior, NULL	*/
 { 0x004a,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x004c,	0x007e,		0x0000 }, /* ~, NULL	*/
 { 0x004d,	0x00b6,		0x0000 }, /* paragraph, NULL	*/
 { 0x004e,	0x00bd,		0x0000 }, /* onehalf, NULL	*/
 { 0x0052,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x0053,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0055,	0x00be,		0x0000 }, /* threequarters, NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ], NULL	*/
 { -1, 0, 0 }
};

xkey_t swiss_french_pcxalap_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0013,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x0016,	0x007c,		0x0000 }, /* |, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* #, NULL	*/
 { 0x0036,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x003d,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x003e,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x004e,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x0052,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x0053,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0055,	0x007e,		0x0000 }, /* ~, NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ], NULL	*/
 { -1, 0, 0 }
};

xkey_t italian_pcxalki_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x007c }, /* \, |	*/
 { 0x004c,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0052,	0x0023,		0x0000 }, /* #, NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ], NULL	*/
 { -1, 0, 0 }
};

xkey_t dutch_pcxalgh_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x0013,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x0016,	0x00b9,		0x0000 }, /* onesuperior, NULL	*/
 { 0x001a,	0x00ab,		0x0000 }, /* guillemotleft, NULL	*/
 { 0x001b,	0x00df,		0x0000 }, /* ssharp, NULL	*/
 { 0x001e,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x0021,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x0022,	0x00bb,		0x0000 }, /* guillemotright, NULL	*/
 { 0x0025,	0x00bc,		0x0000 }, /* onequarter, NULL	*/
 { 0x0026,	0x00b3,		0x0000 }, /* threesuperior, NULL	*/
 { 0x002d,	0x00b6,		0x0000 }, /* paragraph, NULL	*/
 { 0x002e,	0x00bd,		0x0000 }, /* onehalf, NULL	*/
 { 0x0036,	0x00be,		0x0000 }, /* threequarters, NULL	*/
 { 0x003a,	0x00b5,		0x0000 }, /* mu, NULL	*/
 { 0x003d,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003e,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x0046,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0049,	0x01ff,		0x0000 }, /* abovedot, NULL	*/
 { 0x004e,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x0055,	0x00b8,		0x0000 }, /* cedilla, NULL	*/
 { -1, 0, 0 }
};

xkey_t norwegian_pcxalkn_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0025,	0x0024,		0x0000 }, /* $, NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ], NULL	*/
 { 0x0055,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x005b,	0x007e,		0x0000 }, /* ~, NULL	*/
 { -1, 0, 0 }
};

xkey_t portuguese_pcxalkv_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x001e,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0025,	0x00a7,		0x0000 }, /* section, NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ], NULL	*/
 { 0x0054,	0x00a8,		0x0000 }, /* diaeresis, NULL	*/
 { -1, 0, 0 }
};

xkey_t finnish_pcxalca_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0013,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0025,	0x0024,		0x0000 }, /* $, NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ], NULL	*/
 { 0x004e,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x005b,	0x007e,		0x0000 }, /* ~, NULL	*/
 { -1, 0, 0 }
};

xkey_t swedish_pcxalma_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0013,	0x007c,		0x0000 }, /* |, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0025,	0x0024,		0x0000 }, /* $, NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ], NULL	*/
 { 0x004e,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x005b,	0x007e,		0x0000 }, /* ~, NULL	*/
 { -1, 0, 0 }
};

xkey_t belgian_pcxalkb_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0013,	0x005c,		0x0000 }, /* \, NULL	*/
 { 0x0016,	0x007c,		0x0000 }, /* |, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* @, NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* #, NULL	*/
 { 0x0036,	0x005e,		0x0000 }, /* ^, NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* }, NULL	*/
 { 0x0046,	0x007b,		0x0000 }, /* {, NULL	*/
 { 0x004a,	0x007e,		0x0000 }, /* ~, NULL	*/
 { 0x0052,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x0053,	0x0060,		0x0000 }, /* `, NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* [, NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ], NULL	*/
 { -1, 0, 0 }
};

xkey_t *pcxal_altgrs[] = {
	danish_pcxalkd_altgr,			/* 0x30 */
	austrian_german_pcxalkg_altgr,		/* 0x32 */
	swiss_german_pcxalmh_altgr,		/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 *//* US has none */
	uk_pcxalae_altgr,			/* 0x38 */
	spanish_pcxalks_altgr,			/* 0x3a */
	french_pcxalkp_altgr,			/* 0x3c */
	french_canadian_pcxalac_altgr,		/* 0x3e */
	swiss_french_pcxalap_altgr,		/* 0x40 */
	italian_pcxalki_altgr,			/* 0x42 */
	dutch_pcxalgh_altgr,			/* 0x44 */
	norwegian_pcxalkn_altgr,		/* 0x46 */
	portuguese_pcxalkv_altgr,		/* 0x48 */
	finnish_pcxalca_altgr,			/* 0x4a */
	swedish_pcxalma_altgr,			/* 0x4c */
	belgian_pcxalkb_altgr,			/* 0x4e */
	(xkey_t *)NULL,				/* 0x50 *//* JIS has none */
	(xkey_t *)NULL,				/* 0x52 *//* ANSI has none */
	
};

/************************************************************************
 * here are all the tables related to the LK411 keyboard series
 */

/*
 * This table contains the diffs between the US LK411 and the US PCXAL.
 * It is used with *every* LK411 to update the default PCXAL to the default
 * LK411, then any further diffs between the US LK411 and the foreign LK411
 * are used to also update the translation table.
 */
 /*
  * NOTE: some LK411-only keys already appear in the pcxal_xlate table, as
  * there's no way a PCXAL keyboard could generate those scancodes.
  */
xkey_t pcxal_to_lk411_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x0060,		0x007e }, /* grave, asciitilde	*/
 { 0x000e,	0x003c,		0x003e }, /* less, greater	*/
 { 0x0056,	LK_F11,		LK_F11 }, /* Escape	*/
 { 0x0057,	F18,		F18    }, /* F18	*/
 { 0x0058,	MOD_COMP_R,	0      }, /* Multi_key	*//* COMP_R */
 { 0x005e,	LK_F12,		LK_F12    }, /* F12	*/
 { 0x005f,	F19,		F19    }, /* F19	*/
 { 0x0062,	F20,		F20    }, /* F20	*/
 { 0x0064,	SELECT,		SELECT }, /* Select	*/
 { 0x0065,	PREV,		PREV   }, /* Prev	*/
 { 0x0066,	DELE,		DELE   }, /* Delete	*/
 { 0x0067,	FIND,		FIND   }, /* Find	*/
 { 0x0069,	KP_1,		KP_1   }, /* KP_1	*/
 { 0x006b,	KP_4,		KP_4   }, /* KP_4	*/
 { 0x006c,	KP_7,		KP_7   }, /* KP_7	*/
 { 0x006d,	NEXT,		NEXT   }, /* Next	*/
 { 0x006e,	INS,		INS    }, /* Insert Here	*/
 { 0x006f,	REMOVE,		REMOVE }, /* Remove	*/
 { 0x0070,	KP_0,		KP_0   }, /* KP_0	*/
 { 0x0071,	KP_PERIOD,	KP_PERIOD }, /* KP_Decimal	*/
 { 0x0072,	KP_2,		KP_2   }, /* KP_2	*/
 { 0x0074,	KP_6,		KP_6   }, /* KP_6	*/
 { 0x0075,	KP_8,		KP_8   }, /* KP_8	*/
 { 0x0076,	KP_PF1,		KP_PF1 }, /* KP_F1	*/
 { 0x0077,	KP_PF2,		KP_PF2 }, /* KP_F2	*/
 { 0x007a,	KP_3,		KP_3   }, /* KP_3	*/
 { 0x007c,	KP_COMMA,	KP_COMMA }, /* KP_Separator	*/
 { 0x007d,	KP_9,		KP_9   }, /* KP_9	*/
 { 0x007e,	KP_PF3,		KP_PF3 }, /* KP_F3	*/
 { 0x0084,	KP_PF4,		KP_PF4 }, /* KP_F4	*/
 { -1, 0, 0 }
};
    
/*
 * the following tables hold the differences between the given (LK411)
 * keyboard and the default (US LK411) keyboard.
 */
xkey_t austrian_german_lk411ag_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x005e,		0x00b0 }, /* '^', , degree	*/
 { 0x000e,	0x003c,		0x003e }, /* '<', , '>'	*/
 { 0x0015,	0x0071,		0x0051 }, /* 'q', , 'Q'	*/
 { 0x0016,	0x0031,		0x0021 }, /* '1', , '!'	*/
 { 0x001a,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x001b,	0x0073,		0x0053 }, /* 's', , 'S'	*/
 { 0x001c,	0x0061,		0x0041 }, /* 'a', , 'A'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0021,	0x0063,		0x0043 }, /* 'c', , 'C'	*/
 { 0x0022,	0x0078,		0x0058 }, /* 'x', , 'X'	*/
 { 0x0023,	0x0064,		0x0044 }, /* 'd', , 'D'	*/
 { 0x0025,	0x0034,		0x0024 }, /* '4', , '$'	*/
 { 0x0026,	0x0033,		0x00a7 }, /* '3', , section	*/
 { 0x0029,	0x0020,		0x0020 }, /* ' ', , ' '	*/
 { 0x002b,	0x0066,		0x0046 }, /* 'f', , 'F'	*/
 { 0x002d,	0x0072,		0x0052 }, /* 'r', , 'R'	*/
 { 0x002e,	0x0035,		0x0025 }, /* '5', , '%'	*/
 { 0x0035,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003a,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0042,	0x006b,		0x004b }, /* 'k', , 'K'	*/
 { 0x0044,	0x006f,		0x004f }, /* 'o', , 'O'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00f6,		0x00d6 }, /* odiaeresis, Odiaeresis	*/
 { 0x004d,	0x0070,		0x0050 }, /* 'p', , 'P'	*/
 { 0x004e,	0x00df,		0x003f }, /* ssharp, '?'	*/
 { 0x0054,	0x00fc,		0x00dc }, /* udiaeresis, Udiaeresis	*/
 { 0x0055,	0x0027,		0x0060 }, /* ''', , '`'	*/
 { 0x005b,	0x002b,		0x002a }, /* '+', , '*'	*/
 { 0x005c,	0x0023,		0x0027 }, /* '#', , '''	*/
 { -1, 0, 0 }
};
xkey_t belgian_lk411ab_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00b2,		0x00b3 }, /* twosuperior, threesuperior	*/
 { 0x000e,	0x003c,		0x003e }, /* '<', , '>'	*/
 { 0x0015,	0x0061,		0x0041 }, /* 'a', , 'A'	*/
 { 0x0016,	0x0026,		0x0031 }, /* '&', , '1'	*/
 { 0x001a,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x001c,	0x0071,		0x0051 }, /* 'q', , 'Q'	*/
 { 0x001d,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x001e,	0x00e9,		0x0032 }, /* eacute, '2'	*/
 { 0x0025,	0x0027,		0x0034 }, /* ''', , '4'	*/
 { 0x0026,	0x0022,		0x0033 }, /* '"', , '3'	*/
 { 0x002e,	0x0028,		0x0035 }, /* '(', , '5'	*/
 { 0x0036,	0x00a7,		0x0036 }, /* section, '6'	*/
 { 0x003a,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x003d,	0x00e8,		0x0037 }, /* egrave, '7'	*/
 { 0x003e,	0x0021,		0x0038 }, /* '!', , '8'	*/
 { 0x0041,	0x003b,		0x002e }, /* ';', , '.'	*/
 { 0x0045,	0x00e0,		0x0030 }, /* agrave, '0'	*/
 { 0x0046,	0x00e7,		0x0039 }, /* ccedilla, '9'	*/
 { 0x0049,	0x003a,		0x002f }, /* ':', , '/'	*/
 { 0x004a,	0x003d,		0x002b }, /* '=', , '+'	*/
 { 0x004c,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x004e,	0x0029,		0x00b0 }, /* ')', , degree	*/
 { 0x0052,	0x00f9,		0x0025 }, /* ugrave, '%'	*/
 { 0x0054,	0x005e,		0x00a8 }, /* '^', , diaeresis	*/
 { 0x0055,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x005b,	0x0024,		0x002a }, /* '$', , '*'	*/
 { 0x005c,	0x00b5,		0x00a3 }, /* mu, sterling	*/
 { -1, 0, 0 }
};
xkey_t danish_lk411ad_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00bd,		0x00a7 }, /* onehalf, section	*/
 { 0x000e,	0x003c,		0x003e }, /* '<', , '>'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0025,	0x0034,		0x00a4 }, /* '4', , currency	*/
 { 0x0026,	0x0033,		0x0023 }, /* '3', , '#'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00e6,		0x00c6 }, /* ae, AE	*/
 { 0x004e,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x0052,	0x00d8,		0x00f8 }, /* Ooblique, oslash	*/
 { 0x0054,	0x00e5,		0x00c5 }, /* aring, Aring	*/
 { 0x0055,	0x00b4,		0x0060 }, /* acute, '`'	*/
 { 0x005b,	0x00a8,		0x005e }, /* diaeresis, '^'	*/
 { 0x005c,	0x0027,		0x002a }, /* ''', , '*'	*/
 { -1, 0, 0 }
};
xkey_t dutch_lk411ah_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x0040,		0x00a7 }, /* '@', , section	*/
 { 0x000e,	0x005d,		0x005b }, /* ']', , '['	*/
 { 0x0016,	0x0031,		0x0021 }, /* '1', , '!'	*/
 { 0x001a,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x001b,	0x0073,		0x0053 }, /* 's', , 'S'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0021,	0x0063,		0x0043 }, /* 'c', , 'C'	*/
 { 0x0022,	0x0078,		0x0058 }, /* 'x', , 'X'	*/
 { 0x0025,	0x0034,		0x0024 }, /* '4', , '$'	*/
 { 0x0026,	0x0033,		0x0023 }, /* '3', , '#'	*/
 { 0x002d,	0x0072,		0x0052 }, /* 'r', , 'R'	*/
 { 0x002e,	0x0035,		0x0025 }, /* '5', , '%'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003a,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x003d,	0x0037,		0x005f }, /* '7', , '_'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x0027 }, /* '0', , '''	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x003d }, /* '-', , '='	*/
 { 0x004c,	0x002b,		0x00b1 }, /* '+', , plusminus	*/
 { 0x004e,	0x002f,		0x003f }, /* '/', , '?'	*/
 { 0x0052,	0x00b4,		0x0060 }, /* acute, '`'	*/
 { 0x0054,	0x00a8,		0x005e }, /* diaeresis, '^'	*/
 { 0x0055,	0x00b0,		0x007e }, /* degree, '~'	*/
 { 0x005b,	0x002a,		0x00a6 }, /* '*', , brokenbar	*/
 { 0x005c,	0x003c,		0x003e }, /* '<', , '>'	*/
 { -1, 0, 0 }
};
xkey_t finnish_lk411af_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00a7,		0x00bd }, /* section, onehalf	*/
 { 0x000e,	0x003c,		0x003e }, /* '<', , '>'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0025,	0x0034,		0x00a4 }, /* '4', , currency	*/
 { 0x0026,	0x0033,		0x0023 }, /* '3', , '#'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00f6,		0x00d6 }, /* odiaeresis, Odiaeresis	*/
 { 0x004e,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x0052,	0x00e4,		0x00c4 }, /* adiaeresis, Adiaeresis	*/
 { 0x0054,	0x00e5,		0x00c5 }, /* aring, Aring	*/
 { 0x0055,	0x00b4,		0x0060 }, /* acute, '`'	*/
 { 0x005b,	0x00a8,		0x005e }, /* diaeresis, '^'	*/
 { 0x005c,	0x0027,		0x002a }, /* ''', , '*'	*/
 { -1, 0, 0 }
};
xkey_t french_canadian_lk411ac_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x0023,		0x007c }, /* '#', , '|'	*/
 { 0x000e,	0x00ab,		0x00bb }, /* guillemotleft, guillemotright	*/
 { 0x0016,	0x0031,		0x0021 }, /* '1', , '!'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0025,	0x0034,		0x0024 }, /* '4', , '$'	*/
 { 0x0026,	0x0033,		0x002f }, /* '3', , '/'	*/
 { 0x002e,	0x0035,		0x0025 }, /* '5', , '%'	*/
 { 0x0036,	0x0036,		0x003f }, /* '6', , '?'	*/
 { 0x003a,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x003d,	0x0037,		0x0026 }, /* '7', , '&'	*/
 { 0x003e,	0x0038,		0x002a }, /* '8', , '*'	*/
 { 0x0041,	0x002c,		0x0027 }, /* ',', , '''	*/
 { 0x0044,	0x006f,		0x004f }, /* 'o', , 'O'	*/
 { 0x0045,	0x0030,		0x0029 }, /* '0', , ')'	*/
 { 0x0046,	0x0039,		0x0028 }, /* '9', , '('	*/
 { 0x0049,	0x002e,		0x002e }, /* '.', , '.'	*/
 { 0x004a,	0x00e9,		0x00c9 }, /* eacute, Eacute	*/
 { 0x004c,	0x003b,		0x003a }, /* ';', , ':'	*/
 { 0x004d,	0x0070,		0x0050 }, /* 'p', , 'P'	*/
 { 0x004e,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x0052,	0x0060,		0x0060 }, /* '`', , '`'	*/
 { 0x0054,	0x005e,		0x005e }, /* '^', , '^'	*/
 { 0x0055,	0x003d,		0x002b }, /* '=', , '+'	*/
 { 0x005b,	0x00e7,		0x00a8 }, /* ccedilla, diaeresis	*/
 { 0x005c,	0x003c,		0x003e }, /* '<', , '>'	*/
 { -1, 0, 0 }
};
xkey_t french_lk411ap_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00b2,		0x00b2 }, /* twosuperior, twosuperior	*/
 { 0x0015,	0x0061,		0x0041 }, /* 'a', , 'A'	*/
 { 0x0016,	0x0026,		0x0031 }, /* '&', , '1'	*/
 { 0x001a,	0x0077,		0x0057 }, /* 'w', , 'W'	*/
 { 0x001c,	0x0071,		0x0051 }, /* 'q', , 'Q'	*/
 { 0x001d,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x001e,	0x00e9,		0x0032 }, /* eacute, '2'	*/
 { 0x0025,	0x0027,		0x0034 }, /* ''', , '4'	*/
 { 0x0026,	0x0022,		0x0033 }, /* '"', , '3'	*/
 { 0x002e,	0x0028,		0x0035 }, /* '(', , '5'	*/
 { 0x0036,	0x002d,		0x0036 }, /* '-', , '6'	*/
 { 0x003a,	0x002c,		0x003f }, /* ',', , '?'	*/
 { 0x003d,	0x00e8,		0x0037 }, /* egrave, '7'	*/
 { 0x003e,	0x005f,		0x0038 }, /* '_', , '8'	*/
 { 0x0041,	0x003b,		0x002e }, /* ';', , '.'	*/
 { 0x0045,	0x00e0,		0x0030 }, /* agrave, '0'	*/
 { 0x0046,	0x00e7,		0x0039 }, /* ccedilla, '9'	*/
 { 0x0049,	0x003a,		0x002f }, /* ':', , '/'	*/
 { 0x004a,	0x0021,		0x00a7 }, /* '!', , section	*/
 { 0x004c,	0x006d,		0x004d }, /* 'm', , 'M'	*/
 { 0x004e,	0x0029,		0x00b0 }, /* ')', , degree	*/
 { 0x0052,	0x00f9,		0x0025 }, /* ugrave, '%'	*/
 { 0x0054,	0x005e,		0x00a8 }, /* '^', , diaeresis	*/
 { 0x0055,	0x003d,		0x002b }, /* '=', , '+'	*/
 { 0x005b,	0x0024,		0x00a3 }, /* '$', , sterling	*/
 { 0x005c,	0x002a,		0x00b5 }, /* '*', , mu	*/
 { -1, 0, 0 }
};
xkey_t italian_lk411ai_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x005c,		0x00a6 }, /* '\', , brokenbar	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0026,	0x0033,		0x00a3 }, /* '3', , sterling	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00f2,		0x00e7 }, /* ograve, ccedilla	*/
 { 0x004e,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x0052,	0x00e0,		0x00b0 }, /* agrave, degree	*/
 { 0x0054,	0x00e8,		0x00e9 }, /* egrave, eacute	*/
 { 0x0055,	0x00ec,		0x005e }, /* igrave, '^'	*/
 { 0x005b,	0x002b,		0x002a }, /* '+', , '*'	*/
 { 0x005c,	0x00f9,		0x00a7 }, /* ugrave, section	*/
 { -1, 0, 0 }
};
xkey_t norwegian_lk411an_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x007c,		0x00a7 }, /* '|', , section	*/
 { 0x000e,	0x005c,		0x007c }, /* '\', , '|'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0025,	0x0034,		0x00a4 }, /* '4', , currency	*/
 { 0x0026,	0x0033,		0x0023 }, /* '3', , '#'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00f8,		0x00d8 }, /* oslash, Ooblique	*/
 { 0x004e,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x0052,	0x00e6,		0x00c6 }, /* ae, AE	*/
 { 0x0054,	0x00e5,		0x00c5 }, /* aring, Aring	*/
 { 0x0055,	0x005c,		0x0060 }, /* '\', , '`'	*/
 { 0x005b,	0x00a8,		0x005e }, /* diaeresis, '^'	*/
 { 0x005c,	0x0027,		0x002a }, /* ''', , '*'	*/
 { -1, 0, 0 }
};
xkey_t portuguese_lk411av_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x005c,		0x007c }, /* '\', , '|'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0025,	0x0034,		0x0024 }, /* '4', , '$'	*/
 { 0x0026,	0x0033,		0x0023 }, /* '3', , '#'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x005c }, /* '7', , '\'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00e7,		0x00c7 }, /* ccedilla, Ccedilla	*/
 { 0x004e,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x0052,	0x00ba,		0x00aa }, /* masculine, ordfeminine	*/
 { 0x0054,	0x002b,		0x002a }, /* '+', , '*'	*/
 { 0x0055,	0x00ab,		0x00bb }, /* guillemotleft, guillemotright	*/
 { 0x005b,	0x00b4,		0x0060 }, /* acute, '`'	*/
 { 0x005c,	0x007e,		0x005e }, /* '~', , '^'	*/
 { -1, 0, 0 }
};
xkey_t spanish_lk411as_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00ba,		0x00aa }, /* masculine, ordfeminine	*/
 { 0x0016,	0x0031,		0x0021 }, /* '1', , '!'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0026,	0x0033,		0x00b7 }, /* '3', , periodcentered	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00f1,		0x00d1 }, /* ntilde, Ntilde	*/
 { 0x004e,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x0052,	0x00b4,		0x00a8 }, /* acute, diaeresis	*/
 { 0x0054,	0x0060,		0x005e }, /* '`', , '^'	*/
 { 0x0055,	0x00a1,		0x00bf }, /* exclamdown, questiondown	*/
 { 0x005b,	0x002b,		0x002a }, /* '+', , '*'	*/
 { 0x005c,	0x00e7,		0x00c7 }, /* ccedilla, Ccedilla	*/
 { -1, 0, 0 }
};
xkey_t swedish_lk411am_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00a7,		0x00bd }, /* section, onehalf	*/
 { 0x000e,	0x003c,		0x003e }, /* '<', , '>'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0025,	0x0034,		0x00a4 }, /* '4', , currency	*/
 { 0x0026,	0x0033,		0x0023 }, /* '3', , '#'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00d8,		0x00f8 }, /* Ooblique, oslash	*/
 { 0x004e,	0x002b,		0x003f }, /* '+', , '?'	*/
 { 0x0052,	0x00e6,		0x00c6 }, /* ae, AE	*/
 { 0x0054,	0x00e5,		0x00c5 }, /* aring, Aring	*/
 { 0x0055,	0x00b4,		0x0060 }, /* acute, '`'	*/
 { 0x005b,	0x00a8,		0x005e }, /* diaeresis, '^'	*/
 { 0x005c,	0x0027,		0x002a }, /* ''', , '*'	*/
 { -1, 0, 0 }
};
xkey_t swiss_french_lk411ak_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00a7,		0x00b0 }, /* section, degree	*/
 { 0x000e,	0x003c,		0x003e }, /* '<', , '>'	*/
 { 0x0016,	0x0031,		0x002b }, /* '1', , '+'	*/
 { 0x001a,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0025,	0x0034,		0x00e7 }, /* '4', , ccedilla	*/
 { 0x0026,	0x0033,		0x002a }, /* '3', , '*'	*/
 { 0x0035,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00e9,		0x00f6 }, /* eacute, odiaeresis	*/
 { 0x004e,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x0052,	0x00e0,		0x00e4 }, /* agrave, adiaeresis	*/
 { 0x0054,	0x00e8,		0x00fc }, /* egrave, udiaeresis	*/
 { 0x0055,	0x005e,		0x0060 }, /* '^', , '`'	*/
 { 0x005b,	0x00a8,		0x0021 }, /* diaeresis, '!'	*/
 { 0x005c,	0x0024,		0x00a3 }, /* '$', , sterling	*/
 { -1, 0, 0 }
};
xkey_t swiss_german_lk411al_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00a7,		0x00b0 }, /* section, degree	*/
 { 0x000e,	0x003c,		0x003e }, /* '<', , '>'	*/
 { 0x0016,	0x0031,		0x002b }, /* '1', , '+'	*/
 { 0x001a,	0x0079,		0x0059 }, /* 'y', , 'Y'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0025,	0x0034,		0x00e7 }, /* '4', , ccedilla	*/
 { 0x0026,	0x0033,		0x002a }, /* '3', , '*'	*/
 { 0x0035,	0x007a,		0x005a }, /* 'z', , 'Z'	*/
 { 0x0036,	0x0036,		0x0026 }, /* '6', , '&'	*/
 { 0x003d,	0x0037,		0x002f }, /* '7', , '/'	*/
 { 0x003e,	0x0038,		0x0028 }, /* '8', , '('	*/
 { 0x0041,	0x002c,		0x003b }, /* ',', , ';'	*/
 { 0x0045,	0x0030,		0x003d }, /* '0', , '='	*/
 { 0x0046,	0x0039,		0x0029 }, /* '9', , ')'	*/
 { 0x0049,	0x002e,		0x003a }, /* '.', , ':'	*/
 { 0x004a,	0x002d,		0x005f }, /* '-', , '_'	*/
 { 0x004c,	0x00f6,		0x00e9 }, /* odiaeresis, eacute	*/
 { 0x004e,	0x0027,		0x003f }, /* ''', , '?'	*/
 { 0x0052,	0x00e4,		0x00e0 }, /* adiaeresis, agrave	*/
 { 0x0054,	0x00fc,		0x00e8 }, /* udiaeresis, egrave	*/
 { 0x0055,	0x005e,		0x0060 }, /* '^', , '`'	*/
 { 0x005b,	0x00a8,		0x0021 }, /* diaeresis, '!'	*/
 { 0x005c,	0x0024,		0x00a3 }, /* '$', , sterling	*/
 { -1, 0, 0 }
};

xkey_t uk_lk411aa_diffs[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x0060,		0x00ac }, /* '`', , notsign	*/
 { 0x000e,	0x005c,		0x007c }, /* '\', , '|'	*/
 { 0x001e,	0x0032,		0x0022 }, /* '2', , '"'	*/
 { 0x0026,	0x0033,		0x00a3 }, /* '3', , sterling	*/
 { 0x0052,	0x0027,		0x0040 }, /* ''', , '@'	*/
 { 0x005c,	0x0023,		0x007e }, /* '#', , '~'	*/
 { -1, 0, 0 }
};

xkey_t jis_lk411jj_diffs[] = {
/* keycode	unshifted	shifted */
  { 0x001e,      '2',            '"'    }, /* 2, , " */
  { 0x0036,      '6',            '&'    }, /* 6, , & */
  { 0x003d,      '7',            '\''   }, /* 7, , ' */
  { 0x003e,      '8',            '('    }, /* 8, , ( */
  { 0x0046,      '9',            ')'    }, /* 9, , ) */
  { 0x0045,      '0',            '0'    }, /* 0, , 0 */
  { 0x004e,      '-',            '='    }, /* -, , = */
  { 0x0055,      '^',            '~'    }, /* ^, , ~ */
  { 0x005d,      '\\',           '|'    }, /* \, , | */
  { 0x0054,      '@',            '`'    }, /* @, , ` */
  { 0x005b,      '[',            '{'    }, /* [, , { */
  { 0x004c,      ';',            '+'    }, /* ;, , + */
  { 0x0052,      ':',            '*'    }, /* :, , * */
  { 0x0053,      ']',            '}'    }, /* ], , } */
  { 0x0051,      '\\',           '_'    }, /* \, , _ */
 { -1, 0, 0 }
};

xkey_t *pc411_diffs[] = {
	danish_lk411ad_diffs,			/* 0x30 */
	austrian_german_lk411ag_diffs,		/* 0x32 */
	swiss_german_lk411al_diffs,		/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 *//* US default */
	uk_lk411aa_diffs,			/* 0x38 */
	spanish_lk411as_diffs,			/* 0x3a */
	french_lk411ap_diffs,			/* 0x3c */
	french_canadian_lk411ac_diffs,		/* 0x3e */
	swiss_french_lk411ak_diffs,		/* 0x40 */
	italian_lk411ai_diffs,			/* 0x42 */
	dutch_lk411ah_diffs,			/* 0x44 */
	norwegian_lk411an_diffs,		/* 0x46 */
	portuguese_lk411av_diffs,		/* 0x48 */
	finnish_lk411af_diffs,			/* 0x4a */
	swedish_lk411am_diffs,			/* 0x4c */
	belgian_lk411ab_diffs,			/* 0x4e */
	jis_lk411jj_diffs,			/* 0x50 */
	(xkey_t *)NULL,				/* 0x52 *//* -AJ same as US */

};

/*
 * The following tables are used to hold the ALT-GR translations
 *  for the LK411 keyboards.
 */
xkey_t austrian_german_lk411ag_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x000e,	0x007c,		0x00a6 }, /* '|', brokenbar	*/
 { 0x0015,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0016,	0x00b9,		0x00a1 }, /* onesuperior, exclamdown	*/
 { 0x001a,	0x00ab,		0x003c }, /* guillemotleft, '<'	*/
 { 0x001b,	0x00df,		0x00a7 }, /* ssharp, section	*/
 { 0x001c,	0x00e6,		0x00c6 }, /* ae, AE	*/
 { 0x001e,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x0021,	0x00a2,		0x00a9 }, /* cent, copyright	*/
 { 0x0022,	0x00bb,		0x003e }, /* guillemotright, '>'	*/
 { 0x0023,	0x00f0,		0x00d0 }, /* eth, ETH	*/
 { 0x0025,	0x00bc,		0x00a4 }, /* onequarter, currency	*/
 { 0x0026,	0x00b3,		0x00a3 }, /* threesuperior, sterling	*/
 { 0x0029,	0x00a0,		0x00a0 }, /* nobreakspace, nobreakspace	*/
 { 0x002b,	0x00aa,		0x0000 }, /* ordfeminine, NULL	*/
 { 0x002d,	0x00b6,		0x00ae }, /* paragraph, registered	*/
 { 0x002e,	0x00bd,		0x0000 }, /* onehalf, NULL	*/
 { 0x0035,	0x00a5,		0x0000 }, /* yen, NULL	*/
 { 0x0036,	0x00be,		0x0000 }, /* threequarters, NULL	*/
 { 0x003a,	0x00b5,		0x00ba }, /* mu, masculine	*/
 { 0x003d,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0041,	0x00d7,		0x0000 }, /* multiply, NULL	*/
 { 0x0042,	0x0026,		0x0000 }, /* '&', NULL	*/
 { 0x0044,	0x00f8,		0x00d8 }, /* oslash, Ooblique	*/
 { 0x0045,	0x007d,		0x00b0 }, /* '}', degree	*/
 { 0x0046,	0x005d,		0x00b1 }, /* ']', plusminus	*/
 { 0x0049,	0x00b7,		0x00f7 }, /* periodcentered, division	*/
 { 0x004a,	0x00ad,		0x0000 }, /* hyphen, NULL	*/
 { 0x004c,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x004d,	0x00fe,		0x00de }, /* thorn, THORN	*/
 { 0x004e,	0x005c,		0x00bf }, /* '\', questiondown	*/
 { 0x0054,	0xfe22,		0xfeb0 }, /* Ddiaeresis, '°'	*/
 { 0x0055,	0xfe2c,		0x0000 }, /* Dcedilla_accent, NULL	*/
 { 0x005b,	0xfe7e,		0x00af }, /* '~', macron	*/
 { 0x005c,	0xfe60,		0x0000 }, /* Dgrave_accent, NULL	*/
 { -1, 0, 0 }
};
xkey_t belgian_lk411ab_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x0016,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x0036,	0x005e,		0x0000 }, /* '^', NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x0046,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x004a,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x0052,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x005c,	0x0060,		0x0000 }, /* '`', NULL	*/
 { -1, 0, 0 }
};
xkey_t danish_lk411ad_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0025,	0x0024,		0x0000 }, /* '$', NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x0055,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x005b,	0x007e,		0x0000 }, /* '~', NULL	*/
 { -1, 0, 0 }
};
xkey_t dutch_lk411ah_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x000e,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x0016,	0x00b9,		0x0000 }, /* onesuperior, NULL	*/
 { 0x001a,	0x00ab,		0x0000 }, /* guillemotleft, NULL	*/
 { 0x001b,	0x00df,		0x0000 }, /* ssharp, NULL	*/
 { 0x001e,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x0021,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x0022,	0x00bb,		0x0000 }, /* guillemotright, NULL	*/
 { 0x0025,	0x00bc,		0x0000 }, /* onequarter, NULL	*/
 { 0x0026,	0x00b3,		0x0000 }, /* threesuperior, NULL	*/
 { 0x002d,	0x00b6,		0x0000 }, /* paragraph, NULL	*/
 { 0x002e,	0x00bd,		0x0000 }, /* onehalf, NULL	*/
 { 0x0036,	0x00be,		0x0000 }, /* threequarters, NULL	*/
 { 0x003a,	0x00b5,		0x0000 }, /* mu, NULL	*/
 { 0x003d,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003e,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x0046,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x0049,	0x00b7,		0x0000 }, /* periodcentered, NULL	*/
 { 0x004e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x0055,	0x00b8,		0x0000 }, /* cedilla, NULL	*/
 { -1, 0, 0 }
};
xkey_t finnish_lk411af_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0025,	0x0024,		0x0000 }, /* '$', NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x004e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x005b,	0x007e,		0x0000 }, /* '~', NULL	*/
 { -1, 0, 0 }
};
xkey_t french_canadian_lk411ac_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x000e,	0x00b0,		0x0000 }, /* degree, NULL	*/
 { 0x0016,	0x00b1,		0x0000 }, /* plusminus, NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0025,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x002e,	0x00a4,		0x0000 }, /* currency, NULL	*/
 { 0x0036,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x003a,	0x00b5,		0x0000 }, /* mu, NULL	*/
 { 0x003d,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x003e,	0x00b2,		0x0000 }, /* twosuperior, NULL	*/
 { 0x0041,	0x00af,		0x0000 }, /* macron, NULL	*/
 { 0x0044,	0x00a7,		0x0000 }, /* section, NULL	*/
 { 0x0045,	0x00bc,		0x0000 }, /* onequarter, NULL	*/
 { 0x0046,	0x00b3,		0x0000 }, /* threesuperior, NULL	*/
 { 0x004a,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x004c,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x004d,	0x00b6,		0x0000 }, /* paragraph, NULL	*/
 { 0x004e,	0x00bd,		0x0000 }, /* onehalf, NULL	*/
 { 0x0052,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0055,	0x00be,		0x0000 }, /* threequarters, NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x005c,	0x007d,		0x0000 }, /* '}', NULL	*/
 { -1, 0, 0 }
};
xkey_t french_lk411ap_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x001e,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x0025,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x002e,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0036,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x003d,	0x0060,		0x0000 }, /* '`', NULL	*/
 { 0x003e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x0045,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0046,	0x005e,		0x0000 }, /* '^', NULL	*/
 { 0x004e,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x0055,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x005b,	0x00a4,		0x0000 }, /* currency, NULL	*/
 { -1, 0, 0 }
};
xkey_t italian_lk411ai_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x004c,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0052,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ']', NULL	*/
 { -1, 0, 0 }
};
xkey_t norwegian_lk411an_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0025,	0x0024,		0x0000 }, /* '$', NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x0055,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x005b,	0x007e,		0x0000 }, /* '~', NULL	*/
 { -1, 0, 0 }
};
xkey_t portuguese_lk411av_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0025,	0x00a7,		0x0000 }, /* section, NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x0054,	0x00a8,		0x0000 }, /* diaeresis, NULL	*/
 { -1, 0, 0 }
};
xkey_t spanish_lk411as_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x0016,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x0036,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x0052,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x005c,	0x007d,		0x0000 }, /* '}', NULL	*/
 { -1, 0, 0 }
};
xkey_t swedish_lk411am_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0025,	0x0024,		0x0000 }, /* '$', NULL	*/
 { 0x0026,	0x00a3,		0x0000 }, /* sterling, NULL	*/
 { 0x003d,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x003e,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0045,	0x007d,		0x0000 }, /* '}', NULL	*/
 { 0x0046,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x004e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x005b,	0x007e,		0x0000 }, /* '~', NULL	*/
 { -1, 0, 0 }
};
xkey_t swiss_french_lk411ak_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x0016,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x0036,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x003d,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x003e,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x004e,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x0052,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0055,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x005c,	0x007d,		0x0000 }, /* '}', NULL	*/
 { -1, 0, 0 }
};
xkey_t swiss_german_lk411al_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x000e,	0x005c,		0x0000 }, /* '\', NULL	*/
 { 0x0016,	0x007c,		0x0000 }, /* '|', NULL	*/
 { 0x001e,	0x0040,		0x0000 }, /* '@', NULL	*/
 { 0x0026,	0x0023,		0x0000 }, /* '#', NULL	*/
 { 0x0036,	0x00ac,		0x0000 }, /* notsign, NULL	*/
 { 0x003d,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { 0x003e,	0x00a2,		0x0000 }, /* cent, NULL	*/
 { 0x004e,	0x00b4,		0x0000 }, /* acute, NULL	*/
 { 0x0052,	0x007b,		0x0000 }, /* '{', NULL	*/
 { 0x0054,	0x005b,		0x0000 }, /* '[', NULL	*/
 { 0x0055,	0x007e,		0x0000 }, /* '~', NULL	*/
 { 0x005b,	0x005d,		0x0000 }, /* ']', NULL	*/
 { 0x005c,	0x007d,		0x0000 }, /* '}', NULL	*/
 { -1, 0, 0 }
};
xkey_t uk_lk411aa_altgr[] = {
/* keycode	unshifted	shifted */
 { 0x0008,	0x00a6,		0x0000 }, /* brokenbar, NULL	*/
 { -1, 0, 0 }
};

xkey_t *pc411_altgrs[] = {
	danish_lk411ad_altgr,			/* 0x30 */
	austrian_german_lk411ag_altgr,		/* 0x32 */
	swiss_german_lk411al_altgr,		/* 0x34 */
	(xkey_t *)NULL,				/* 0x36 *//* US has none */
	uk_lk411aa_altgr,			/* 0x38 */
	spanish_lk411as_altgr,			/* 0x3a */
	french_lk411ap_altgr,			/* 0x3c */
	french_canadian_lk411ac_altgr,		/* 0x3e */
	swiss_french_lk411ak_altgr,		/* 0x40 */
	italian_lk411ai_altgr,			/* 0x42 */
	dutch_lk411ah_altgr,			/* 0x44 */
	norwegian_lk411an_altgr,		/* 0x46 */
	portuguese_lk411av_altgr,		/* 0x48 */
	finnish_lk411af_altgr,			/* 0x4a */
	swedish_lk411am_altgr,			/* 0x4c */
	belgian_lk411ab_altgr,			/* 0x4e */
	(xkey_t *)NULL,				/* 0x50 *//* JIS has none */
	(xkey_t *)NULL,				/* 0x36 *//* ANSI has none */
};

#endif /* BINARY */
