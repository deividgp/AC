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

#pragma ident "@(#)$RCSfile: ws_data.c,v $ $Revision: 1.1.30.2 $ (DEC) $Date: 1996/11/19 19:35:57 $"

/************************************************************************
 * Modification History
 * 3-July-91 -- Jim Gettys
 *	       Added HX (sfb) support for bt459
 *
 * 13-Aug-90 -- Sam Hsu
 * 
 *	       Created from fb_data.c, px_data.c, ws_device.c.
 *
 ************************************************************************/
#define _WS_DATA_C_

#include <sys/param.h>
#include <sys/errno.h>
#include <sys/buf.h>
#include <kern/queue.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devio.h>
#include <io/common/devdriver.h>
#include <io/dec/ws/vsxxx.h>	
#include <io/dec/ws/slu.h>	
#include <sys/keysyms.h>


/* The following data declarations are *always* needed */


/*
 *  global flag set on boot or through configure
 *  entrypoint that allows user to override default
 *  graphics configuration. Definitions in sys/wsdevice.h
 */
long ws_graphics = 0;


/*
 * On a workstation, these variables identify
 * the type of graphics display device and
 * which units are present. This info is filled
 * in by the graphics device drivers.
 */
int   ws_display_type = 0;    /* Major device number of display device */
int   ws_display_units = 0;   /* Bit field of units (bit0 = unit 0, etc) */
int   ws_num_controllers = 0;    /* number of graphics options */
int   ws_graphics_config_error = 0; /* flag for gfx config problems */
char   *(*ws_graphics_name_proc)(); /* routine to return graphics option name */
char   *(*ws_keyboard_name_proc)(); /* routine to return keyboard name */
char   *(*ws_pointer_name_proc)(); /* routine to return pointer name */
int	(*ws_graphics_get_width_proc)();
int	(*ws_graphics_get_height_proc)();


/* These entry points are used by the keyboard/mouse interface layer */
int 	(*v_consputc)()  = 0;
int 	(*v_consgetc)()  = 0;
int 	(*vs_gdopen)()   = 0;
int 	(*vs_gdclose)()  = 0;
int 	(*vs_gdread)()   = 0;
int 	(*vs_gdwrite)()  = 0;
int 	(*vs_gdselect)() = 0;
int 	(*vs_gdkint)()   = 0;	/* keyboard interrupt */
int 	(*vs_gdpint)()   = 0;	/* pointer interrupt */
int	(*vs_gdmmap)()   = 0;
int 	(*vs_gdioctl)()  = 0;
int 	(*vs_gdstop)()   = 0;

/* global keyboard and mouse data */
/* the *real* keyboard and mouse stuff is copied into here */
/* during console initialization early in boot-up, */
/* by the hardware-specific console init code; */
/* for example, the lk201 keyboard and vsxxx mouse particulars are */
/* copied during scc_cons_init processing on FLAMINGO */

ws_keyboard keyboard;
ws_hardware_type mouse_closure;
ws_pointer mouse;
struct  slu slu;  
ws_pointer_report current_rep;
u_short pointer_id;


/*
 * workstation driver data structures
 */
#include "ws.h"

#if NWS > 0
/*
 * This is so an X server can deal with different phosphor types.
 */
ws_monitor monitor_type[] = {
    MONITOR_VRUNK,
    MONITOR_VR299,
    MONITOR_VR290,
    MONITOR_VR260,
    MONITOR_VR262,
    MONITOR_VR150,
    MONITOR_VRE01,
    MONITOR_VR160,
    MONITOR_VR297,
    MONITOR_VRT19,
};
int nmon_types = sizeof(monitor_type) / sizeof(ws_monitor);

unsigned int cdata[16] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

ws_cursor_data default_cursor = {
    DEFAULT_CURSOR ,
};

/*
 * Generic keyboard special purpose keys. Translations from the
 * specific keyboard tables (currently just PCXAL and LK201) 
 * includes codes for the function keys and other goodies. They are
 * currently flagged by the presence of the 8th bit being set.  The 
 * following table is accessed by removing that bit and using the 
 * result as the index to the following table. Note that table begins
 * a null entry.
 *
 * NOTE: These may be equivalent to VT 220 keysyms for the special
 *	 keys.
 */
char	*special_keys[]={
	0,						/* 0'th */
	"\33[11~",			/* f1 */	/* 1'th */
	"\33[12~",			/* f2 */	/* 2'th */
	"\33[13~",			/* f3 */	/* 3'th */
	"\33[14~",			/* f4 */	/* 4'th */
	"\33[15~",			/* f5 */	/* 5'th */
	"\33[17~",			/* f6 */	/* 6'th */
	"\33[18~",			/* f7 */	/* 7'th */
	"\33[19~",			/* f8 */	/* 8'th */
	"\33[20~",			/* f9 */	/* 9'th */
	"\33[21~",			/* f10 */	/* a'th */
	"\33[26~",			/* f14 */	/* b'th */
	"\33[28~",			/* f15 */	/* c'th */
	"\33[29~",			/* f16 */	/* d'th */
	"\33[31~",			/* f17 */	/* e'th */
	"\33[32~",			/* f18 */	/* f'th */
	"\33[33~",			/* f19 */	/* 10'th */
	"\33[34~",			/* f20 */	/* 11'th */
	"\33[1~",			/* find */	/* 12'th */
	"\33[2~",			/* insert */	/* 13'th */
	"\33[3~",			/* remove */	/* 14'th */
	"\33[4~",			/* select */	/* 15'th */
	"\33[5~",			/* prev */	/* 16'th */
	"\33[6~",			/* next */	/* 17'th */
	"\33OP",			/* pf1 */	/* 18'th */
	"\33OQ",			/* pf2 */	/* 19'th */
	"\33OR",			/* pf3 */	/* 1a'th */
	"\33OS",			/* pf4 */	/* 1b'th */
	"\33[D",			/* left */	/* 1c'th */
	"\33[C",			/* right */	/* 1d'th */
	"\33[B",			/* down */	/* 1e'th */
	"\33[A",			/* up */	/* 1f'th */
	"\33Op",			/* key pad 0 */	/* 20'th */
	"\33On",			/* key pad . */	/* 21'th */
	"\33OM",			/* key pad enter *//* 22'th */
	"\33Oq",			/* key pad 1 */	/* 23'th */
	"\33Or",			/* key pad 2 */	/* 24'th */
	"\33Os",			/* key pad 3 */	/* 25'th */
	"\33Ot",			/* key pad 4 */	/* 26'th */
	"\33Ou",			/* key pad 5 */	/* 27'th */
	"\33Ov",			/* key pad 6 */	/* 28'th */
	"\33Ol",			/* key pad , */	/* 29'th */
	"\33Ow",			/* key pad 7 */	/* 2a'th */
	"\33Ox",			/* key pad 8 */	/* 2b'th */
	"\33Oy",			/* key pad 9 */	/* 2c'th */
	"\33Om",			/* key pad - */	/* 2d'th */
	"",				/* unused    */ /* 2e'th */
	"",				/* unused    */ /* 2f'th */
	"\33[23~",			/* f11	     */ /* 30'th */
	"\33[24~",			/* f12	     */ /* 31'th */
	"\33[H",			/* home	     */ /* 32'th */
	"",				/* middle    */ /* 33'th */
	"",				/* prtsc     */ /* 34'th */
	"",				/* pause     */ /* 35'th */

#ifdef NOT_USED
/* NOTE: no idea if this stuff actually gets referenced from lk201 code */
	/*
	 * The following strings are to allow a numeric keypad
	 * mode and still use the same translation tables
	 */
	"0",
	".",
	"\r",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	",",
	"7",
	"8",
	"9",
	"-"
#endif /* NOT_USED */
};

int	special_keys_size = sizeof(special_keys) / sizeof(char *);

#endif /* NWS > 0 */



char *language_names[] = {
	"Dansk",
	"Deutsch",
	"Deutsch (Schweiz)",
	"English (American)",
	"English (British/Irish)",
	"Espanol",
	"Francais",
	"Francais (Canadian)",
	"Francais (Suisse Romande)",
	"Italiano",
	"Nederlands",
	"Norsk",
	"Portugues",
	"Suomi",
	"Svenska",
	"Vlaams",
	"Japanese (JIS)",
	"Japanese (ANSI)",
};

/*
 * define the set of legal COMPOSE sequences
 *
 * initially taken from /usr/include/X11/iso_compose.h
 */

#define COMPOSE_SEQUENCE(a,b,c) {(a),(b),(c)}

xcomp_t comp_seq[] = {
/*2020a0*/COMPOSE_SEQUENCE (XK_space, XK_space, XK_nobreakspace),
/*202222*/COMPOSE_SEQUENCE (XK_space, XK_quotedbl, XK_quotedbl),
/*202727*/COMPOSE_SEQUENCE (XK_space, XK_quoteright, XK_quoteright),
/*202ab0*/COMPOSE_SEQUENCE (XK_space, XK_asterisk, XK_degree),
/*205e5e*/COMPOSE_SEQUENCE (XK_space, XK_asciicircum, XK_asciicircum),
/*206060*/COMPOSE_SEQUENCE (XK_space, XK_quoteleft, XK_quoteleft),
/*207e7e*/COMPOSE_SEQUENCE (XK_space, XK_asciitilde, XK_asciitilde),
/*20a8a8*/COMPOSE_SEQUENCE (XK_space, XK_diaeresis, XK_diaeresis),
/*20b0b0*/COMPOSE_SEQUENCE (XK_space, XK_degree, XK_degree),
/*20b4b4*/COMPOSE_SEQUENCE (XK_space, XK_acute, XK_acute),
/*2121a1*/COMPOSE_SEQUENCE (XK_exclam, XK_exclam, XK_exclamdown),
/*2150b6*/COMPOSE_SEQUENCE (XK_exclam, XK_P, XK_paragraph),
/*2153a7*/COMPOSE_SEQUENCE (XK_exclam, XK_S, XK_section),
/*2170b6*/COMPOSE_SEQUENCE (XK_exclam, XK_p, XK_paragraph),
/*2173a7*/COMPOSE_SEQUENCE (XK_exclam, XK_s, XK_section),
/*222022*//*COMPOSE_SEQUENCE (XK_quotedbl, XK_space, XK_quotedbl),*/
/*2222a8*/COMPOSE_SEQUENCE (XK_quotedbl, XK_quotedbl, XK_diaeresis),
/*2241c4*/COMPOSE_SEQUENCE (XK_quotedbl, XK_A, XK_Adiaeresis),
/*2245cb*/COMPOSE_SEQUENCE (XK_quotedbl, XK_E, XK_Ediaeresis),
/*2249cf*/COMPOSE_SEQUENCE (XK_quotedbl, XK_I, XK_Idiaeresis),
/*224fd6*/COMPOSE_SEQUENCE (XK_quotedbl, XK_O, XK_Odiaeresis),
/*2255dc*/COMPOSE_SEQUENCE (XK_quotedbl, XK_U, XK_Udiaeresis),
/*2261e4*/COMPOSE_SEQUENCE (XK_quotedbl, XK_a, XK_adiaeresis),
/*2265eb*/COMPOSE_SEQUENCE (XK_quotedbl, XK_e, XK_ediaeresis),
/*2269ef*/COMPOSE_SEQUENCE (XK_quotedbl, XK_i, XK_idiaeresis),
/*226ff6*/COMPOSE_SEQUENCE (XK_quotedbl, XK_o, XK_odiaeresis),
/*2275fc*/COMPOSE_SEQUENCE (XK_quotedbl, XK_u, XK_udiaeresis),
/*2279ff*/COMPOSE_SEQUENCE (XK_quotedbl, XK_y, XK_ydiaeresis),
/*272027*//*COMPOSE_SEQUENCE (XK_quoteright, XK_space, XK_quoteright),*/
/*2727b4*/COMPOSE_SEQUENCE (XK_quoteright, XK_quoteright, XK_acute),
/*2741c1*/COMPOSE_SEQUENCE (XK_quoteright, XK_A, XK_Aacute),
/*2745c9*/COMPOSE_SEQUENCE (XK_quoteright, XK_E, XK_Eacute),
/*2749cd*/COMPOSE_SEQUENCE (XK_quoteright, XK_I, XK_Iacute),
/*274fd3*/COMPOSE_SEQUENCE (XK_quoteright, XK_O, XK_Oacute),
/*2755da*/COMPOSE_SEQUENCE (XK_quoteright, XK_U, XK_Uacute),
/*2759dd*/COMPOSE_SEQUENCE (XK_quoteright, XK_Y, XK_Yacute),
/*2761e1*/COMPOSE_SEQUENCE (XK_quoteright, XK_a, XK_aacute),
/*2765e9*/COMPOSE_SEQUENCE (XK_quoteright, XK_e, XK_eacute),
/*2769ed*/COMPOSE_SEQUENCE (XK_quoteright, XK_i, XK_iacute),
/*276ff3*/COMPOSE_SEQUENCE (XK_quoteright, XK_o, XK_oacute),
/*2775fa*/COMPOSE_SEQUENCE (XK_quoteright, XK_u, XK_uacute),
/*2779fd*/COMPOSE_SEQUENCE (XK_quoteright, XK_y, XK_yacute),
/*28285b*/COMPOSE_SEQUENCE (XK_parenleft, XK_parenleft, XK_bracketleft),
/*282d7b*/COMPOSE_SEQUENCE (XK_parenleft, XK_minus, XK_braceleft),
/*29295d*/COMPOSE_SEQUENCE (XK_parenright, XK_parenright, XK_bracketright),
/*292d7d*/COMPOSE_SEQUENCE (XK_parenright, XK_minus, XK_braceright),
/*2a20b0*//*COMPOSE_SEQUENCE (XK_asterisk, XK_space, XK_degree),*/
/*2a41c5*/COMPOSE_SEQUENCE (XK_asterisk, XK_A, XK_Aring),
/*2a61e5*/COMPOSE_SEQUENCE (XK_asterisk, XK_a, XK_aring),
/*2b2b23*/COMPOSE_SEQUENCE (XK_plus, XK_plus, XK_numbersign),
/*2b2db1*/COMPOSE_SEQUENCE (XK_plus, XK_minus, XK_plusminus),
/*2c2cb8*/COMPOSE_SEQUENCE (XK_comma, XK_comma, XK_cedilla),
/*2c43c7*/COMPOSE_SEQUENCE (XK_comma, XK_C, XK_Ccedilla),
/*2c63e7*/COMPOSE_SEQUENCE (XK_comma, XK_c, XK_ccedilla),
/*2d287b*//*COMPOSE_SEQUENCE (XK_minus, XK_parenleft, XK_braceleft),*/
/*2d297d*//*COMPOSE_SEQUENCE (XK_minus, XK_parenright, XK_braceright),*/
/*2d2bb1*//*COMPOSE_SEQUENCE (XK_minus, XK_plus, XK_plusminus),*/
/*2d2cac*/COMPOSE_SEQUENCE (XK_minus, XK_comma, XK_notsign),
/*2d2dad*/COMPOSE_SEQUENCE (XK_minus, XK_minus, XK_hyphen),
/*2d3af7*/COMPOSE_SEQUENCE (XK_minus, XK_colon, XK_division),
/*2d44d0*/COMPOSE_SEQUENCE (XK_minus, XK_D, XK_Eth),
/*2d4ca3*/COMPOSE_SEQUENCE (XK_minus, XK_L, XK_sterling),
/*2d59a5*/COMPOSE_SEQUENCE (XK_minus, XK_Y, XK_yen),
/*2d5eaf*/COMPOSE_SEQUENCE (XK_minus, XK_asciicircum, XK_macron),
/*2d64f0*/COMPOSE_SEQUENCE (XK_minus, XK_d, XK_eth),
/*2d6ca3*/COMPOSE_SEQUENCE (XK_minus, XK_l, XK_sterling),
/*2d79a5*/COMPOSE_SEQUENCE (XK_minus, XK_y, XK_yen),
/*2e5eb7*/COMPOSE_SEQUENCE (XK_period, XK_asciicircum, XK_periodcentered),
/*2f2f5c*/COMPOSE_SEQUENCE (XK_slash, XK_slash, XK_backslash),
/*2f3c5c*/COMPOSE_SEQUENCE (XK_slash, XK_less, XK_backslash),
/*2f43a2*/COMPOSE_SEQUENCE (XK_slash, XK_C, XK_cent),
/*2f4fd8*/COMPOSE_SEQUENCE (XK_slash, XK_O, XK_Ooblique),
/*2f55b5*/COMPOSE_SEQUENCE (XK_slash, XK_U, XK_mu),
/*2f5e7c*/COMPOSE_SEQUENCE (XK_slash, XK_asciicircum, XK_bar),
/*2f63a2*/COMPOSE_SEQUENCE (XK_slash, XK_c, XK_cent),
/*2f6ff8*/COMPOSE_SEQUENCE (XK_slash, XK_o, XK_oslash),
/*2f75b5*/COMPOSE_SEQUENCE (XK_slash, XK_u, XK_mu),
/*3043a9*/COMPOSE_SEQUENCE (XK_0, XK_C, XK_copyright),
/*3052ae*/COMPOSE_SEQUENCE (XK_0, XK_R, XK_registered),
/*3053a7*/COMPOSE_SEQUENCE (XK_0, XK_S, XK_section),
/*3058a4*/COMPOSE_SEQUENCE (XK_0, XK_X, XK_currency),
/*305eb0*/COMPOSE_SEQUENCE (XK_0, XK_asciicircum, XK_degree),
/*3063a9*/COMPOSE_SEQUENCE (XK_0, XK_c, XK_copyright),
/*3072ae*/COMPOSE_SEQUENCE (XK_0, XK_r, XK_registered),
/*3073a7*/COMPOSE_SEQUENCE (XK_0, XK_s, XK_section),
/*3078a4*/COMPOSE_SEQUENCE (XK_0, XK_x, XK_currency),
/*3132bd*/COMPOSE_SEQUENCE (XK_1, XK_2, XK_onehalf),
/*3134bc*/COMPOSE_SEQUENCE (XK_1, XK_4, XK_onequarter),
/*315eb9*/COMPOSE_SEQUENCE (XK_1, XK_asciicircum, XK_onesuperior),
/*325eb2*/COMPOSE_SEQUENCE (XK_2, XK_asciicircum, XK_twosuperior),
/*3334be*/COMPOSE_SEQUENCE (XK_3, XK_4, XK_threequarters),
/*335eb3*/COMPOSE_SEQUENCE (XK_3, XK_asciicircum, XK_threesuperior),
/*3a2df7*//*COMPOSE_SEQUENCE (XK_colon, XK_minus, XK_division),*/
/*3c2f5c*//*COMPOSE_SEQUENCE (XK_less, XK_slash, XK_backslash),*/
/*3c3cab*/COMPOSE_SEQUENCE (XK_less, XK_less, XK_guillemotleft),
/*3d4ca3*/COMPOSE_SEQUENCE (XK_equal, XK_L, XK_sterling),
/*3d59a5*/COMPOSE_SEQUENCE (XK_equal, XK_Y, XK_yen),
/*3d6ca3*/COMPOSE_SEQUENCE (XK_equal, XK_l, XK_sterling),
/*3d79a5*/COMPOSE_SEQUENCE (XK_equal, XK_y, XK_yen),
/*3e3ebb*/COMPOSE_SEQUENCE (XK_greater, XK_greater, XK_guillemotright),
/*3f3fbf*/COMPOSE_SEQUENCE (XK_question, XK_question, XK_questiondown),
/*4122c4*//*COMPOSE_SEQUENCE (XK_A, XK_quotedbl, XK_Adiaeresis),*/
/*4127c1*//*COMPOSE_SEQUENCE (XK_A, XK_quoteright, XK_Aacute),*/
/*412ac5*//*COMPOSE_SEQUENCE (XK_A, XK_asterisk, XK_Aring),*/
/*414140*/COMPOSE_SEQUENCE (XK_A, XK_A, XK_at),
/*4145c6*/COMPOSE_SEQUENCE (XK_A, XK_E, XK_AE),
/*415ec2*/COMPOSE_SEQUENCE (XK_A, XK_asciicircum, XK_Acircumflex),
/*415faa*/COMPOSE_SEQUENCE (XK_A, XK_underscore, XK_ordfeminine),
/*4160c0*/COMPOSE_SEQUENCE (XK_A, XK_quoteleft, XK_Agrave),
/*416140*/COMPOSE_SEQUENCE (XK_A, XK_a, XK_at),
/*417ec3*/COMPOSE_SEQUENCE (XK_A, XK_asciitilde, XK_Atilde),
/*41a8c4*/COMPOSE_SEQUENCE (XK_A, XK_diaeresis, XK_Adiaeresis),
/*41b0c5*/COMPOSE_SEQUENCE (XK_A, XK_degree, XK_Aring),
/*41b4c1*/COMPOSE_SEQUENCE (XK_A, XK_acute, XK_Aacute),
/*432cc7*//*COMPOSE_SEQUENCE (XK_C, XK_comma, XK_Ccedilla),*/
/*432fa2*//*COMPOSE_SEQUENCE (XK_C, XK_slash, XK_cent),*/
/*4330a9*//*COMPOSE_SEQUENCE (XK_C, XK_0, XK_copyright),*/
/*434fa9*/COMPOSE_SEQUENCE (XK_C, XK_O, XK_copyright),
/*436fa9*/COMPOSE_SEQUENCE (XK_C, XK_o, XK_copyright),
/*437ca2*/COMPOSE_SEQUENCE (XK_C, XK_bar, XK_cent),
/*442dd0*//*COMPOSE_SEQUENCE (XK_D, XK_minus, XK_Eth),*/
/*4522cb*//*COMPOSE_SEQUENCE (XK_E, XK_quotedbl, XK_Ediaeresis),*/
/*4527c9*//*COMPOSE_SEQUENCE (XK_E, XK_quoteright, XK_Eacute),*/
/*455eca*/COMPOSE_SEQUENCE (XK_E, XK_asciicircum, XK_Ecircumflex),
/*4560c8*/COMPOSE_SEQUENCE (XK_E, XK_quoteleft, XK_Egrave),
/*45a8cb*/COMPOSE_SEQUENCE (XK_E, XK_diaeresis, XK_Ediaeresis),
/*45b4c9*/COMPOSE_SEQUENCE (XK_E, XK_acute, XK_Eacute),
/*4922cf*//*COMPOSE_SEQUENCE (XK_I, XK_quotedbl, XK_Idiaeresis),*/
/*4927cd*//*COMPOSE_SEQUENCE (XK_I, XK_quoteright, XK_Iacute),*/
/*495ece*/COMPOSE_SEQUENCE (XK_I, XK_asciicircum, XK_Icircumflex),
/*4960cc*/COMPOSE_SEQUENCE (XK_I, XK_quoteleft, XK_Igrave),
/*49a8cf*/COMPOSE_SEQUENCE (XK_I, XK_diaeresis, XK_Idiaeresis),
/*49b4cd*/COMPOSE_SEQUENCE (XK_I, XK_acute, XK_Iacute),
/*4c2da3*//*COMPOSE_SEQUENCE (XK_L, XK_minus, XK_sterling),*/
/*4c3da3*//*COMPOSE_SEQUENCE (XK_L, XK_equal, XK_sterling),*/
/*4e7ed1*/COMPOSE_SEQUENCE (XK_N, XK_asciitilde, XK_Ntilde),
/*4f22d6*//*COMPOSE_SEQUENCE (XK_O, XK_quotedbl, XK_Odiaeresis),*/
/*4f27d3*//*COMPOSE_SEQUENCE (XK_O, XK_quoteright, XK_Oacute),*/
/*4f2fd8*//*COMPOSE_SEQUENCE (XK_O, XK_slash, XK_Ooblique),*/
/*4f43a9*//*COMPOSE_SEQUENCE (XK_O, XK_C, XK_copyright),*/
/*4f52ae*/COMPOSE_SEQUENCE (XK_O, XK_R, XK_registered),
/*4f53a7*/COMPOSE_SEQUENCE (XK_O, XK_S, XK_section),
/*4f58a4*/COMPOSE_SEQUENCE (XK_O, XK_X, XK_currency),
/*4f5ed4*/COMPOSE_SEQUENCE (XK_O, XK_asciicircum, XK_Ocircumflex),
/*4f5fba*/COMPOSE_SEQUENCE (XK_O, XK_underscore, XK_masculine),
/*4f60d2*/COMPOSE_SEQUENCE (XK_O, XK_quoteleft, XK_Ograve),
/*4f63a9*/COMPOSE_SEQUENCE (XK_O, XK_c, XK_copyright),
/*4f72ae*/COMPOSE_SEQUENCE (XK_O, XK_r, XK_registered),
/*4f73a7*/COMPOSE_SEQUENCE (XK_O, XK_s, XK_section),
/*4f78a4*/COMPOSE_SEQUENCE (XK_O, XK_x, XK_currency),
/*4f7ed5*/COMPOSE_SEQUENCE (XK_O, XK_asciitilde, XK_Otilde),
/*4fa8d6*/COMPOSE_SEQUENCE (XK_O, XK_diaeresis, XK_Odiaeresis),
/*4fb4d3*/COMPOSE_SEQUENCE (XK_O, XK_acute, XK_Oacute),
/*5021b6*//*COMPOSE_SEQUENCE (XK_P, XK_exclam, XK_paragraph),*/
/*5230ae*//*COMPOSE_SEQUENCE (XK_R, XK_0, XK_registered),*/
/*524fae*//*COMPOSE_SEQUENCE (XK_R, XK_O, XK_registered),*/
/*526fae*/COMPOSE_SEQUENCE (XK_R, XK_o, XK_registered),
/*5321a7*//*COMPOSE_SEQUENCE (XK_S, XK_exclam, XK_section),*/
/*5330a7*//*COMPOSE_SEQUENCE (XK_S, XK_0, XK_section),*/
/*534fa7*//*COMPOSE_SEQUENCE (XK_S, XK_O, XK_section),*/
/*536fa7*/COMPOSE_SEQUENCE (XK_S, XK_o, XK_section),
/*5448de*/COMPOSE_SEQUENCE (XK_T, XK_H, XK_Thorn),
/*5522dc*//*COMPOSE_SEQUENCE (XK_U, XK_quotedbl, XK_Udiaeresis),*/
/*5527da*//*COMPOSE_SEQUENCE (XK_U, XK_quoteright, XK_Uacute),*/
/*555edb*/COMPOSE_SEQUENCE (XK_U, XK_asciicircum, XK_Ucircumflex),
/*5560d9*/COMPOSE_SEQUENCE (XK_U, XK_quoteleft, XK_Ugrave),
/*55a8dc*/COMPOSE_SEQUENCE (XK_U, XK_diaeresis, XK_Udiaeresis),
/*55b4da*/COMPOSE_SEQUENCE (XK_U, XK_acute, XK_Uacute),
/*5830a4*//*COMPOSE_SEQUENCE (XK_X, XK_0, XK_currency),*/
/*584fa4*//*COMPOSE_SEQUENCE (XK_X, XK_O, XK_currency),*/
/*5858d7*/COMPOSE_SEQUENCE (XK_X, XK_X, XK_multiply),
/*586fa4*/COMPOSE_SEQUENCE (XK_X, XK_o, XK_currency),
/*5878d7*/COMPOSE_SEQUENCE (XK_X, XK_x, XK_multiply),
/*5927dd*//*COMPOSE_SEQUENCE (XK_Y, XK_quoteright, XK_Yacute),*/
/*592da5*//*COMPOSE_SEQUENCE (XK_Y, XK_minus, XK_yen),*/
/*593da5*//*COMPOSE_SEQUENCE (XK_Y, XK_equal, XK_yen),*/
/*59b4dd*/COMPOSE_SEQUENCE (XK_Y, XK_acute, XK_Yacute),
/*5e205e*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_space, XK_asciicircum),*/
/*5e2daf*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_minus, XK_macron),*/
/*5e2eb7*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_period, XK_periodcentered),*/
/*5e2f7c*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_slash, XK_bar),*/
/*5e30b0*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_0, XK_degree),*/
/*5e31b9*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_1, XK_onesuperior),*/
/*5e32b2*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_2, XK_twosuperior),*/
/*5e33b3*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_3, XK_threesuperior),*/
/*5e41c2*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_A, XK_Acircumflex),*/
/*5e45ca*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_E, XK_Ecircumflex),*/
/*5e49ce*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_I, XK_Icircumflex),*/
/*5e4fd4*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_O, XK_Ocircumflex),*/
/*5e55db*//*COMPOSE_SEQUENCE (XK_asciicircum, XK_U, XK_Ucircumflex),*/
/*5e5faf*/COMPOSE_SEQUENCE (XK_asciicircum, XK_underscore, XK_macron),
/*5e61e2*/COMPOSE_SEQUENCE (XK_asciicircum, XK_a, XK_acircumflex),
/*5e65ea*/COMPOSE_SEQUENCE (XK_asciicircum, XK_e, XK_ecircumflex),
/*5e69ee*/COMPOSE_SEQUENCE (XK_asciicircum, XK_i, XK_icircumflex),
/*5e6ff4*/COMPOSE_SEQUENCE (XK_asciicircum, XK_o, XK_ocircumflex),
/*5e75fb*/COMPOSE_SEQUENCE (XK_asciicircum, XK_u, XK_ucircumflex),
/*5f41aa*//*COMPOSE_SEQUENCE (XK_underscore, XK_A, XK_ordfeminine),*/
/*5f4fba*//*COMPOSE_SEQUENCE (XK_underscore, XK_O, XK_masculine),*/
/*5f5eaf*//*COMPOSE_SEQUENCE (XK_underscore, XK_asciicircum, XK_macron),*/
/*5f61aa*/COMPOSE_SEQUENCE (XK_underscore, XK_a, XK_ordfeminine),
/*5f6fba*/COMPOSE_SEQUENCE (XK_underscore, XK_o, XK_masculine),
/*602060*//*COMPOSE_SEQUENCE (XK_quoteleft, XK_space, XK_quoteleft),*/
/*6041c0*//*COMPOSE_SEQUENCE (XK_quoteleft, XK_A, XK_Agrave),*/
/*6045c8*//*COMPOSE_SEQUENCE (XK_quoteleft, XK_E, XK_Egrave),*/
/*6049cc*//*COMPOSE_SEQUENCE (XK_quoteleft, XK_I, XK_Igrave),*/
/*604fd2*//*COMPOSE_SEQUENCE (XK_quoteleft, XK_O, XK_Ograve),*/
/*6055d9*//*COMPOSE_SEQUENCE (XK_quoteleft, XK_U, XK_Ugrave),*/
/*6061e0*/COMPOSE_SEQUENCE (XK_quoteleft, XK_a, XK_agrave),
/*6065e8*/COMPOSE_SEQUENCE (XK_quoteleft, XK_e, XK_egrave),
/*6069ec*/COMPOSE_SEQUENCE (XK_quoteleft, XK_i, XK_igrave),
/*606ff2*/COMPOSE_SEQUENCE (XK_quoteleft, XK_o, XK_ograve),
/*6075f9*/COMPOSE_SEQUENCE (XK_quoteleft, XK_u, XK_ugrave),
/*6122e4*//*COMPOSE_SEQUENCE (XK_a, XK_quotedbl, XK_adiaeresis),*/
/*6127e1*//*COMPOSE_SEQUENCE (XK_a, XK_quoteright, XK_aacute),*/
/*612ae5*//*COMPOSE_SEQUENCE (XK_a, XK_asterisk, XK_aring),*/
/*614140*//*COMPOSE_SEQUENCE (XK_a, XK_A, XK_at),*/
/*615ee2*//*COMPOSE_SEQUENCE (XK_a, XK_asciicircum, XK_acircumflex),*/
/*615faa*//*COMPOSE_SEQUENCE (XK_a, XK_underscore, XK_ordfeminine),*/
/*6160e0*//*COMPOSE_SEQUENCE (XK_a, XK_quoteleft, XK_agrave),*/
/*616140*/COMPOSE_SEQUENCE (XK_a, XK_a, XK_at),
/*6165e6*/COMPOSE_SEQUENCE (XK_a, XK_e, XK_ae),
/*617ee3*/COMPOSE_SEQUENCE (XK_a, XK_asciitilde, XK_atilde),
/*61a8e4*/COMPOSE_SEQUENCE (XK_a, XK_diaeresis, XK_adiaeresis),
/*61b0e5*/COMPOSE_SEQUENCE (XK_a, XK_degree, XK_aring),
/*61b4e1*/COMPOSE_SEQUENCE (XK_a, XK_acute, XK_aacute),
/*632ce7*//*COMPOSE_SEQUENCE (XK_c, XK_comma, XK_ccedilla),*/
/*632fa2*//*COMPOSE_SEQUENCE (XK_c, XK_slash, XK_cent),*/
/*6330a9*//*COMPOSE_SEQUENCE (XK_c, XK_0, XK_copyright),*/
/*634fa9*//*COMPOSE_SEQUENCE (XK_c, XK_O, XK_copyright),*/
/*636fa9*/COMPOSE_SEQUENCE (XK_c, XK_o, XK_copyright),
/*637ca2*/COMPOSE_SEQUENCE (XK_c, XK_bar, XK_cent),
/*642df0*//*COMPOSE_SEQUENCE (XK_d, XK_minus, XK_eth),*/
/*6522eb*//*COMPOSE_SEQUENCE (XK_e, XK_quotedbl, XK_ediaeresis),*/
/*6527e9*//*COMPOSE_SEQUENCE (XK_e, XK_quoteright, XK_eacute),*/
/*655eea*//*COMPOSE_SEQUENCE (XK_e, XK_asciicircum, XK_ecircumflex),*/
/*6560e8*//*COMPOSE_SEQUENCE (XK_e, XK_quoteleft, XK_egrave),*/
/*65a8eb*/COMPOSE_SEQUENCE (XK_e, XK_diaeresis, XK_ediaeresis),
/*65b4e9*/COMPOSE_SEQUENCE (XK_e, XK_acute, XK_eacute),
/*6922ef*//*COMPOSE_SEQUENCE (XK_i, XK_quotedbl, XK_idiaeresis),*/
/*6927ed*//*COMPOSE_SEQUENCE (XK_i, XK_quoteright, XK_iacute),*/
/*695eee*//*COMPOSE_SEQUENCE (XK_i, XK_asciicircum, XK_icircumflex),*/
/*6960ec*//*COMPOSE_SEQUENCE (XK_i, XK_quoteleft, XK_igrave),*/
/*69a8ef*/COMPOSE_SEQUENCE (XK_i, XK_diaeresis, XK_idiaeresis),
/*69b4ed*/COMPOSE_SEQUENCE (XK_i, XK_acute, XK_iacute),
/*6c2da3*//*COMPOSE_SEQUENCE (XK_l, XK_minus, XK_sterling),*/
/*6c3da3*//*COMPOSE_SEQUENCE (XK_l, XK_equal, XK_sterling),*/
/*6e7ef1*/COMPOSE_SEQUENCE (XK_n, XK_asciitilde, XK_ntilde),
/*6f22f6*//*COMPOSE_SEQUENCE (XK_o, XK_quotedbl, XK_odiaeresis),*/
/*6f27f3*//*COMPOSE_SEQUENCE (XK_o, XK_quoteright, XK_oacute),*/
/*6f2ff8*//*COMPOSE_SEQUENCE (XK_o, XK_slash, XK_oslash),
/*6f43a9*//*COMPOSE_SEQUENCE (XK_o, XK_C, XK_copyright),*/
/*6f52ae*//*COMPOSE_SEQUENCE (XK_o, XK_R, XK_registered),*/
/*6f53a7*//*COMPOSE_SEQUENCE (XK_o, XK_S, XK_section),*/
/*6f58a4*//*COMPOSE_SEQUENCE (XK_o, XK_X, XK_currency),*/
/*6f5ef4*//*COMPOSE_SEQUENCE (XK_o, XK_asciicircum, XK_ocircumflex),*/
/*6f5fba*//*COMPOSE_SEQUENCE (XK_o, XK_underscore, XK_masculine),*/
/*6f60f2*//*COMPOSE_SEQUENCE (XK_o, XK_quoteleft, XK_ograve),*/
/*6f63a9*//*COMPOSE_SEQUENCE (XK_o, XK_c, XK_copyright),*/
/*6f72ae*/COMPOSE_SEQUENCE (XK_o, XK_r, XK_registered),
/*6f73a7*/COMPOSE_SEQUENCE (XK_o, XK_s, XK_section),
/*6f78a4*/COMPOSE_SEQUENCE (XK_o, XK_x, XK_currency),
/*6f7ef5*/COMPOSE_SEQUENCE (XK_o, XK_asciitilde, XK_otilde),
/*6fa8f6*/COMPOSE_SEQUENCE (XK_o, XK_diaeresis, XK_odiaeresis),
/*6fb4f3*/COMPOSE_SEQUENCE (XK_o, XK_acute, XK_oacute),
/*7021b6*//*COMPOSE_SEQUENCE (XK_p, XK_exclam, XK_paragraph),*/
/*7230ae*//*COMPOSE_SEQUENCE (XK_r, XK_0, XK_registered),*/
/*724fae*//*COMPOSE_SEQUENCE (XK_r, XK_O, XK_registered),*/
/*726fae*//*COMPOSE_SEQUENCE (XK_r, XK_o, XK_registered),*/
/*7321a7*//*COMPOSE_SEQUENCE (XK_s, XK_exclam, XK_section),*/
/*7330a7*//*COMPOSE_SEQUENCE (XK_s, XK_0, XK_section),*/
/*734fa7*//*COMPOSE_SEQUENCE (XK_s, XK_O, XK_section),*/
/*736fa7*//*COMPOSE_SEQUENCE (XK_s, XK_o, XK_section),*/
/*7373df*/COMPOSE_SEQUENCE (XK_s, XK_s, XK_ssharp),
/*7468fe*/COMPOSE_SEQUENCE (XK_t, XK_h, XK_thorn),
/*7522fc*//*COMPOSE_SEQUENCE (XK_u, XK_quotedbl, XK_udiaeresis),*/
/*7527fa*//*COMPOSE_SEQUENCE (XK_u, XK_quoteright, XK_uacute),*/
/*755efb*//*COMPOSE_SEQUENCE (XK_u, XK_asciicircum, XK_ucircumflex),*/
/*7560f9*//*COMPOSE_SEQUENCE (XK_u, XK_quoteleft, XK_ugrave),*/
/*75a8fc*/COMPOSE_SEQUENCE (XK_u, XK_diaeresis, XK_udiaeresis),
/*75b4fa*/COMPOSE_SEQUENCE (XK_u, XK_acute, XK_uacute),
/*7830a4*//*COMPOSE_SEQUENCE (XK_x, XK_0, XK_currency),*/
/*784fa4*//*COMPOSE_SEQUENCE (XK_x, XK_O, XK_currency),*/
/*7858d7*//*COMPOSE_SEQUENCE (XK_x, XK_X, XK_multiply),*/
/*786fa4*//*COMPOSE_SEQUENCE (XK_x, XK_o, XK_currency),*/
/*7878d7*/COMPOSE_SEQUENCE (XK_x, XK_x, XK_multiply),
/*7922ff*//*COMPOSE_SEQUENCE (XK_y, XK_quotedbl, XK_ydiaeresis),*/
/*7927fd*//*COMPOSE_SEQUENCE (XK_y, XK_quoteright, XK_yacute),*/
/*792da5*//*COMPOSE_SEQUENCE (XK_y, XK_minus, XK_yen),*/
/*793da5*//*COMPOSE_SEQUENCE (XK_y, XK_equal, XK_yen),*/
/*79a8ff*/COMPOSE_SEQUENCE (XK_y, XK_diaeresis, XK_ydiaeresis),
/*79b4fd*/COMPOSE_SEQUENCE (XK_y, XK_acute, XK_yacute),
/*7c43a2*//*COMPOSE_SEQUENCE (XK_bar, XK_C, XK_cent),*/
/*7c63a2*//*COMPOSE_SEQUENCE (XK_bar, XK_c, XK_cent),*/
/*7c7ca6*/COMPOSE_SEQUENCE (XK_bar, XK_bar, XK_brokenbar),
/*7e207e*//*COMPOSE_SEQUENCE (XK_asciitilde, XK_space, XK_asciitilde),*/
/*7e41c3*//*COMPOSE_SEQUENCE (XK_asciitilde, XK_A, XK_Atilde),*/
/*7e4ed1*//*COMPOSE_SEQUENCE (XK_asciitilde, XK_N, XK_Ntilde),*/
/*7e4fd5*//*COMPOSE_SEQUENCE (XK_asciitilde, XK_O, XK_Otilde),*/
/*7e61e3*//*COMPOSE_SEQUENCE (XK_asciitilde, XK_a, XK_atilde),*/
/*7e6ef1*//*COMPOSE_SEQUENCE (XK_asciitilde, XK_n, XK_ntilde),*/
/*7e6ff5*//*COMPOSE_SEQUENCE (XK_asciitilde, XK_o, XK_otilde),*/
/*a820a8*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_space, XK_diaeresis),*/
/*a841c4*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_A, XK_Adiaeresis),*/
/*a845cb*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_E, XK_Ediaeresis),*/
/*a849cf*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_I, XK_Idiaeresis),*/
/*a84fd6*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_O, XK_Odiaeresis),*/
/*a855dc*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_U, XK_Udiaeresis),*/
/*a861e4*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_a, XK_adiaeresis),*/
/*a865eb*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_e, XK_ediaeresis),*/
/*a869ef*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_i, XK_idiaeresis),*/
/*a86ff6*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_o, XK_odiaeresis),*/
/*a875fc*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_u, XK_udiaeresis),*/
/*a879ff*//*COMPOSE_SEQUENCE (XK_diaeresis, XK_y, XK_ydiaeresis),*/
/*b020b0*//*COMPOSE_SEQUENCE (XK_degree, XK_space, XK_degree),*/
/*b041c5*//*COMPOSE_SEQUENCE (XK_degree, XK_A, XK_Aring),*/
/*b061e5*//*COMPOSE_SEQUENCE (XK_degree, XK_a, XK_aring),*/
/*b420b4*//*COMPOSE_SEQUENCE (XK_acute, XK_space, XK_acute),*/
/*b441c1*//*COMPOSE_SEQUENCE (XK_acute, XK_A, XK_Aacute),*/
/*b445c9*//*COMPOSE_SEQUENCE (XK_acute, XK_E, XK_Eacute),*/
/*b449cd*//*COMPOSE_SEQUENCE (XK_acute, XK_I, XK_Iacute),*/
/*b44fd3*//*COMPOSE_SEQUENCE (XK_acute, XK_O, XK_Oacute),*/
/*b455da*//*COMPOSE_SEQUENCE (XK_acute, XK_U, XK_Uacute),*/
/*b459dd*//*COMPOSE_SEQUENCE (XK_acute, XK_Y, XK_Yacute),*/
/*b461e1*//*COMPOSE_SEQUENCE (XK_acute, XK_a, XK_aacute),*/
/*b465e9*//*COMPOSE_SEQUENCE (XK_acute, XK_e, XK_eacute),*/
/*b469ed*//*COMPOSE_SEQUENCE (XK_acute, XK_i, XK_iacute),*/
/*b46ff3*//*COMPOSE_SEQUENCE (XK_acute, XK_o, XK_oacute),*/
/*b475fa*//*COMPOSE_SEQUENCE (XK_acute, XK_u, XK_uacute),*/
/*b479fd*//*COMPOSE_SEQUENCE (XK_acute, XK_y, XK_yacute),*/
/*  END */COMPOSE_SEQUENCE (0, 0, 0),
};


