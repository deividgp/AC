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
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * @(#)$RCSfile: curses.h,v $ $Revision: 4.2.14.2 $ (DEC) $Date: 1998/09/28 20:11:33 $
 */
/*
 * HISTORY
 * 
 * COMPONENT_NAME: (LIBCURSE) Curses Library
 *
 * FUNCTIONS:   curses.h
 *
 * ORIGINS: 3, 10, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _CURSES_H_
#define _CURSES_H_	/* define prevents multiple includes */

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#ifndef _BSD

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
#include <stdio.h>	/* get definition of FILE */
#include <va_list.h>	/* get definition of va_list */

#ifdef _OSF_SOURCE

#include <sys/ioctl.h>
#include <unctrl.h>

#ifdef NOMACROS
#ifndef _NOMACROS

#define _NOMACROS

#endif /* _NOMACROS */
#endif /* NOMACROS */

#ifdef MINICURSES
#ifndef _MINICURSES

#define _MINICURSES

#endif /* _MINICURSES */
#endif /* MINICURSES */

#define	INFINI	(-1)
#define reg	register

#endif /* _OSF_SOURCE */

/* For performance reasons 'int' is much better than 'short' on Alpha. */
typedef int _SHORT;

/*
 * Capabilities from termcap
 */

extern bool     AM, BS, CA, DA, DB, EO, HC, HZ, IN, MI, MS, NC, NS, OS, UL,
                XB, XN, XT, XS, XX;
extern char     *AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL,
                *DM, *DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6,
                *K7, *K8, *K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL,
                *KR, *KS, *KU, *LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF,
                *SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VS,
                *VE, *AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM,
                *LEFT_PARM, *RIGHT_PARM;
extern char     PC;

/*
 * chtype is the type used to store a character together with attributes.
 * THIS DEFINITION IS DUPLICATED IN CURSES.H AND UNCTRL.H, AND MUST ALWAYS
 * BE THE SAME.  It is required in both places by the XCURSES standard
 * so that each file may stand alone and can be set to "char" to save space, 
 * or "long" to get more attributes.
 */

#ifndef _CHTYPE

#define _CHTYPE
typedef unsigned long chtype;

#endif /* _CHTYPE */

#ifndef _WINT_T
#   define _WINT_T
        typedef unsigned int wint_t;
#endif /* _WINT_T */

#ifndef WEOF
#   define WEOF (-1)
#endif

/* TRUE and FALSE get defined so many times, */
/* let's not get in the way of other definitions. */
#if	!defined(TRUE) || ((TRUE) != 1)
#undef TRUE
#define TRUE	(1)
#endif
#if	!defined(FALSE) || ((FALSE) != 0)
#undef FALSE
#define FALSE	(0)
#endif
#if	!defined(ERR) || ((ERR) != -1)
#undef ERR
#define ERR	(-1)
#endif
#if	!defined(OK) || ((OK) != 0)
#undef OK
#define OK	(0)
#endif

struct _win_st;              /* will define this in a moment */
typedef struct _win_st	WINDOW;

struct _win_st
{
	_SHORT		_cury, _curx;	/* current coordinates */
	_SHORT		_maxy, _maxx;	/* max coordinates */
	_SHORT		_begy, _begx;	/* (0,0) screen coordinates */
	char		_flags;
	_SHORT		_yoffset;	/* actual begy is _begy+_yoffset */
	bool		_clear,		/* clearok() info */
			_leave_,	/* leaveok() info */
			_immed,		/* window in immediate mode */
			_sync;		/* auto syncup of parent */
	WINDOW		*_padwin;	/* "pad" area for current window */
	_SHORT		*_firstch;	/* first change in line */
	_SHORT		*_lastch;	/* last change in line */
	_SHORT		_tmarg, _bmarg;	/* scrolling region bounds */
					/* MUST stay at this offset in WINDOW */
	unsigned	_scroll		: 1;	/* scrollok() info */
	unsigned	_use_idl	: 1;	
	unsigned	_use_keypad	: 1;
	unsigned	_notimeout	: 1;
	unsigned	_use_idc	: 1;	
	attr_t		_attrs;		/* current window attributes */
	cchar_t		_bkgd;		/* background, normally blank */
	int		_delay;		/* delay period on wgetch
					 * 0:  for nodelay
					 * <0: for infinite delay
					 * >0: delay time in units of millisec
					 */
	_SHORT		_ndescs;	/* number of descendants */
	_SHORT		_parx, _pary;	/* coords relative to parent (0,0) */
	WINDOW		*_parent;	/* the parent if this is a subwin */
	cchar_t		**_y;		/* lines of data */
#define _CSMAX	4
	unsigned char	_waitc[_CSMAX+1];/* array to store partial m-width char*/
	char		_index;
#define _WAITC_FREE	0
#define _WAITC_IN	1
#define _WAITC_ADD	2
#define _WAITC_INS	3
	char		_inuse;
};

typedef struct _screen	SCREEN;

/* _lastch is initially set to this, _firstch is set to win->_maxx */
#define _NOCHANGE	-1
#define _INFINITY	16000	/* no line can be longer than this */

/* values for win->_flags */
#define _ISPAD		001
#define _WINCHANGED	002
#define _WINMOVED	004
#define _WINSDEL	010
#define _CANT_BE_IMMED	020
#define _WIN_ADD_ONE	040
#define _WIN_INS_ONE	100

/*
 * Various tricks to quiet lint about things that are okay.
 */
#if defined(lint) && !defined(__CURSES__) /* if not internal to curses source */
 struct _screen {
	 int _nobody_;
 };
#endif /* lint */

/* common external variables */

extern int	LINES, COLS, COLORS, COLOR_PAIRS;

extern WINDOW	*stdscr, *curscr;

extern	cchar_t	*_wacs_map;

extern chtype	_acs_map[];

extern char    	*curs_err_strings[];

    /* Function declarations */

/*    Some routines are not yet implemented; they will be represented
 *    as macros even in the NOMACROS case until they are available
 *    as functions.  Some RETURN* macros will supply fake returns for
 *    them if the real effect cannot be easily simulated.
 */

#define RETURNOK (OK)
#define RETURNADDR (0)


#ifndef _MINICURSES


#ifdef _XOPEN_SOURCE_EXTENDED

/* These are the ENHANCED CURSES interfaces in X/Open Curses, Issue 4 */


#if defined(_NOMACROS) || defined(lint)
extern int	add_wch __((const cchar_t *));
extern int	add_wchnstr __((const cchar_t *, int));
extern int	add_wchstr __((const cchar_t *));
extern int	addchnstr __((const chtype *, int));
extern int	addnstr __((const char *, int));
extern int	addnwstr __((const wchar_t *, int));
extern int	addstr __((const char *));
extern int	addwstr __((const wchar_t *));
extern int	attr_get __((attr_t *, short *, void *));
extern int	attr_off __((attr_t, void *));
extern int	attr_on __((attr_t, void *));
extern int	attr_set __((attr_t, short, void *));
#else
#define add_wch(ch)		wadd_wch(stdscr,ch)
#define add_wchnstr(s,n)	wadd_wchnstr(stdscr,s,n)
#define add_wchstr(s)		wadd_wchstr(stdscr,s)
#define addchnstr(s,n)		waddchnstr(stdscr,s,n)
#define addnstr(s,n)		waddnstr(stdscr,s,n)
#define addnwstr(ws,n)		waddnwstr(stdscr,ws,n)
#define addstr(s)		waddstr(stdscr, s)
#define addwstr(ws)		waddwstr(stdscr,ws)
#define attr_get(a,b,c)		wattr_get(stdscr,(a),(b),(c))
#define attr_off(at,v)		wattr_off(stdscr,at,v)
#define attr_on(at,v)		wattr_on(stdscr,at,v)
#define attr_set(at,c,v)	wattr_set(stdscr,at,c,v)
#endif

#if defined(_NOMACROS) || defined(lint)
extern int	bkgd __((chtype));
extern void	bkgdset __((chtype));
extern int	bkgrnd __((const cchar_t *));
extern void	bkgrndset __((const cchar_t *));
extern int	border __((chtype, chtype, chtype, chtype, chtype, chtype,
		  chtype, chtype));
extern int	border_set __((const cchar_t *, const cchar_t *, 
		  const cchar_t *, const cchar_t *, const cchar_t *, 
		  const cchar_t *, const cchar_t *, const cchar_t *));
extern int	box_set __((WINDOW *, const cchar_t *, const cchar_t *));
#else
#define bkgd(c)			wbkgd(stdscr,c)
#define bkgdset(c)		wbkgdset(stdscr,c)
#define bkgrnd(ch)              wbkgrnd(stdscr,ch)
#define bkgrndset(ch)           wbkgrndset(stdscr,ch)
#define border(a,b,c,d,e,f,g,h) wborder(stdscr,a,b,c,d,e,f,g,h)	
#define border_set(a,b,c,d,e,f,g,h) wborder_set(stdscr,a,b,c,d,e,f,g,h)
#define box_set(w,v,h)          wborder_set(w,v,v,h,h,0,0,0,0)
#endif


#if defined(_NOMACROS) || defined(lint)
extern int	COLOR_PAIR __((int));
extern int	chgat __((int, attr_t, short, const void *));
extern int	color_set __((short, void *));
#else
#define COLOR_PAIR(n)	((n) << 25)
#define chgat(n,a,c,r)		wchgat(stdscr,n,a,c,r)
#define color_set(c,v)		wcolor_set(stdscr,c,v)
#endif

extern bool	can_change_color __((void));
extern int	color_content __((short, short *, short *, short *));
extern int	copywin __((const WINDOW *, WINDOW *, int, int, int, int, 
		  int, int, int));
extern int	curs_set __((int));


extern void	delscreen __((SCREEN *));
extern WINDOW	*derwin __((WINDOW *, int, int, int, int));
extern WINDOW	*dupwin __((WINDOW *));


#if defined(_NOMACROS) || defined(lint)
extern int	echochar __((const chtype));
#else
#define echochar(ch)            wechochar(stdscr,ch)
#endif

extern int	echo_wchar __((const cchar_t *));
extern int	erasewchar __((wchar_t *));


extern void	filter __((void));


#if defined(_NOMACROS) || defined(lint)
extern int	get_wch __((wint_t *));
extern int	get_wstr __((wint_t *));

/* FOR NOW: extern void     getbegyx __((WINDOW *, int, int));
 * FOR NOW: extern void     getmaxyx __((WINDOW *, int, int));
 * FOR NOW: extern void     getparyx __((WINDOW *, int, int));
 */
#define getbegyx(w,y,x)	((y) = getbegy(w), (x) = getbegx(w))
#define getmaxyx(w,y,x)	((y) = getmaxy(w), (x) = getmaxx(w))
#define getparyx(w,y,x)	((y) = getpary(w), (x) = getparx(w))

extern int      getn_wstr __((wint_t *, int));
extern int      getnstr __((char *, int));
#else
#define get_wch(ch)		wget_wch(stdscr,ch)
#define get_wstr(s)		wget_wstr(stdscr,s)
#define getbegyx(w,y,x)	((y) = getbegy(w), (x) = getbegx(w))
#define getmaxyx(w,y,x)	((y) = getmaxy(w), (x) = getmaxx(w))
#define getn_wstr(s,n)		wgetn_wstr(stdscr,s,n)
#define getparyx(w,y,x)	((y) = getpary(w), (x) = getparx(w))
#define getnstr(ws,n)		wgetnstr(stdscr,ws,n)
#endif

extern chtype	getbkgd __((WINDOW *));
extern int	getbkgrnd __((cchar_t *));
extern int	getcchar __((const cchar_t *, wchar_t *, attr_t *, short *, void *));
extern int	getn_wstr __((wint_t *, int));
extern WINDOW	*getwin __((FILE *));


#if defined(_NOMACROS) || defined(lint)
extern int	hline __((chtype, int));
extern int	hline_set __((const cchar_t *, int));
#else
#define hline(c,num)		whline(stdscr,c,num)
#define hline_set(c,num)	whline_set(stdscr,c,num)
#endif

extern int	halfdelay __((int));
extern bool	has_colors __((void));


#if defined(_NOMACROS) || defined(lint)
extern int      in_wch __((cchar_t *));
extern int	in_wchnstr __((cchar_t *, int));
extern int	in_wchstr __((cchar_t *));
extern int	inchnstr __((chtype *, int));
extern int	inchstr __((chtype *));
extern int	innstr __((char *, int));
extern int	innwstr __((wchar_t *, int));
extern int      ins_nwstr __((const wchar_t *, int));
extern int      ins_wch __((const cchar_t *));
extern int      ins_wstr __((const wchar_t *));
extern int	insdelln __((int));
extern int	insnstr __((const char *, int));
extern int	insstr __((const char *));
extern int	instr __((char *));
extern int	inwstr __((wchar_t *));
#else
#define in_wch(wch)		win_wch(stdscr,wch)
#define in_wchnstr(s,n)		win_wchnstr(stdscr,s,n)
#define in_wchstr(s)		win_wchstr(stdscr,s)
#define inchnstr(s,n)		winchnstr(stdscr,s,n)
#define inchstr(s)		winchstr(stdscr,s)
#define innstr(s,n)		winnstr(stdscr,(s),(n))
#define innwstr(ws,n)		winnwstr(stdscr,ws,n)
#define ins_nwstr(ws,n)         wins_nwstr(stdscr,ws,n)
#define ins_wch(c)		wins_wch(stdscr,c)
#define ins_wstr(ws)		wins_wstr(stdscr,ws)
#define insdelln(id)		winsdelln(stdscr,id)
#define insnstr(s,n)		winsnstr(stdscr,s,n)
#define insstr(s)		winsstr(stdscr,s)
#define instr(s)		winstr(stdscr,(s))
#define inwstr(ws)		winwstr(stdscr,ws)
#endif

extern void	idcok __((WINDOW *, bool));
extern void	immedok __((WINDOW *, bool));
extern int	init_color __((short, short, short, short));
extern int	init_pair __((short, short, short));
extern bool	is_linetouched __((WINDOW *, int));
extern bool	is_wintouched __((WINDOW *));
extern bool	isendwin __((void));


extern char	*key_name __((wchar_t));
extern char	*keyname __((int));
extern int	killwchar __((wchar_t *));


extern int	meta __((WINDOW *, bool));
extern int	mvcur __((int, int, int, int));
extern int	mvderwin __((WINDOW *, int, int));


#if defined(_NOMACROS) || defined(lint)
extern int	mvadd_wch __((int, int, const cchar_t *));
extern int	mvadd_wchnstr __((int, int, const cchar_t *, int));
extern int	mvadd_wchstr __((int, int, const cchar_t *));
extern int	mvaddchnstr __((int, int, const chtype *, int));
extern int	mvaddnstr __((int, int, const char *, int));
extern int	mvaddnwstr __((int, int, const wchar_t *, int));
extern int	mvaddstr __((int, int, const char *));
extern int	mvaddwstr __((int, int, const wchar_t *));
extern int	mvchgat __((int, int, int, attr_t, short, const void *));
extern int	mvget_wch __((int, int, wint_t *));
extern int	mvget_wstr __((int, int, wint_t *));
extern int	mvgetn_wstr __((int, int, wint_t *, int));
extern int      mvgetnstr __((int, int, char *, int));
extern int	mvhline __((int, int, chtype, int));
extern int	mvhline_set __((int, int, const cchar_t *, int));
#else
#define mvadd_wch(y,x,ch)	mvwadd_wch(stdscr,y,x,ch)
#define mvadd_wchnstr(y,x,s,n)	mvwadd_wchnstr(stdscr,y,x,s,n)
#define mvadd_wchstr(y,x,s)	mvwadd_wchstr(stdscr,y,x,s)
#define mvaddchnstr(y,x,s,n)	mvwaddchnstr(stdscr,y,x,s,n)
#define mvaddnstr(y,x,s,n)	mvwaddnstr(stdscr,y,x,s,n)
#define mvaddnwstr(y,x,ws,n)	mvwaddnwstr(stdscr,y,x,ws,n)
#define mvaddstr(y,x,s)		mvwaddstr(stdscr,y,x,s)
#define mvaddwstr(y,x,ws)	mvwaddwstr(stdscr,y,x,ws)
#define mvchgat(y,x,n,a,c,r)	mvwchgat(stdscr,y,x,n,a,c,r)
#define mvget_wch(y,x,ch)	mvwget_wch(stdscr,y,x,ch)
#define mvget_wstr(y,x,s)	mvwget_wstr(stdscr,y,x,s)
#define mvgetn_wstr(y,x,s,n)	mvwgetn_wstr(stdscr,y,x,s,n)
#define mvgetnstr(y,x,s,n)	mvwgetnstr(stdscr,y,x,s,n)
#define mvhline(y,x,c,num)	mvwhline(stdscr,y,x,c,num)
#define mvhline_set(y,x,c,num)	mvwhline_set(stdscr,y,x,c,num)
#endif


#if defined(_NOMACROS) || defined(lint)
extern int      mvin_wch __((int, int, cchar_t *));
extern int	mvin_wchnstr __((int, int, cchar_t *, int));
extern int	mvin_wchstr __((int, int, cchar_t *));
extern int	mvinchnstr __((int, int, chtype *, int));
extern int	mvinchstr __((int, int, chtype *));
extern int	mvinnstr __((int, int, char *, int));
extern int	mvinnwstr __((int, int, wchar_t *, int));
extern int      mvins_nwstr __((int, int, const wchar_t *, int));
extern int      mvins_wch __((int, int, const cchar_t *));
extern int      mvins_wstr __((int, int, const wchar_t *));
extern int	mvinsnstr __((int, int, const char *, int));
extern int	mvinsstr __((int, int, const char *));
extern int	mvinstr __((int, int, char *));
extern int	mvinwstr __((int, int, wchar_t *));
extern int	mvvline __((int, int, chtype, int));
extern int	mvvline_set __((int, int, const cchar_t *, int));
#else
#define mvin_wch(y,x,wc)	mvwin_wch(stdscr,y,x,wc)
#define mvin_wchnstr(y,x,s,n)	mvwin_wchnstr(stdscr,y,x,s,n)
#define mvin_wchstr(y,x,s)	mvwin_wchstr(stdscr,y,x,s)
#define mvinchnstr(y,x,s,n)	mvwinchnstr(stdscr,y,x,s,n)
#define mvinchstr(y,x,s)	mvwinchstr(stdscr,y,x,s)
#define mvinnstr(y,x,s,n)	mvwinnstr(stdscr,y,x,(s),(n))
#define mvinnwstr(y,x,ws,n)	mvwinnwstr(stdscr,y,x,ws,n)
#define mvins_nwstr(y,x,ws,n)	mvwins_nwstr(stdscr,y,x,ws,n)
#define mvins_wch(y,x,c)	mvwins_wch(stdscr,y,x,c)
#define mvins_wstr(y,x,ws)	mvwins_wstr(stdscr,y,x,ws)
#define mvinsnstr(y,x,s,n)	mvwinsnstr(stdscr,y,x,s,n)
#define mvinsstr(y,x,s)		mvwinsstr(stdscr,y,x,s)
#define mvinstr(y,x,s)		mvwinstr(stdscr,y,x,(s))
#define mvinwstr(y,x,ws)	mvwinwstr(stdscr,y,x,ws)
#define mvvline(y,x,c,num)	mvwvline(stdscr,y,x,c,num)
#define mvvline_set(y,x,c,num)	mvwvline_set(stdscr,y,x,c,num)
#endif


#if defined(_NOMACROS) || defined(lint)
extern int	mvwadd_wch __((WINDOW *, int, int, const cchar_t *));
extern int	mvwadd_wchnstr __((WINDOW *, int, int, const cchar_t *, int));
extern int	mvwadd_wchstr __((WINDOW *, int, int, const cchar_t *));
extern int	mvwaddchnstr __((WINDOW *, int, int, const chtype *, int));
extern int	mvwaddnstr __((WINDOW *, int, int, const char *, int));
extern int	mvwaddnwstr __((WINDOW *, int, int, const wchar_t *, int));
extern int	mvwaddstr __((WINDOW *, int, int, const char *));
extern int	mvwaddwstr __((WINDOW *, int, int, const wchar_t *));
extern int	mvwchgat __((WINDOW *, int, int, int, attr_t, short, const void *));
extern int	mvwget_wch __((WINDOW *, int, int, wint_t *));
extern int	mvwget_wstr __((WINDOW *, int, int, wint_t *));
extern int	mvwgetn_wstr __((WINDOW *, int, int, wint_t *, int));
extern int      mvwgetnstr __((WINDOW *, int, int, char *, int));
extern int	mvwhline __((WINDOW *, int, int, chtype, int));
extern int	mvwhline_set __((WINDOW *, int, int, const cchar_t *, int));
#else
#define mvwadd_wch(w,y,x,ch)	(wmove(w,y,x)==ERR?ERR:wadd_wch(w,ch))
#define mvwadd_wchnstr(w,y,x,s,n) (wmove(w,y,x)==ERR?ERR:wadd_wchnstr(w,s,n))
#define mvwadd_wchstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:wadd_wchstr(w,s))
#define mvwaddchnstr(w,y,x,s,n)	(wmove(w,y,x)==ERR?ERR:waddchnstr(w,s,n))
#define mvwaddnstr(w,y,x,s,n)	(wmove(w,y,x)==ERR?ERR:waddnstr(w,s,n))
#define mvwaddnwstr(w,y,x,ws,n) (wmove(w,y,x)==ERR?ERR:waddnwstr(w,ws,n))
#define mvwaddstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:waddstr(w,s))
#define mvwaddwstr(w,y,x,ws)	(wmove(w,y,x)==ERR?ERR:waddwstr(w,ws))
#define mvwchgat(w,y,x,n,a,c,r)	(wmove(w,y,x)==ERR?ERR:wchgat(w,n,a,c,r))
#define mvwget_wch(w,y,x,ch)	(wmove(w,y,x)==ERR?ERR:wget_wch(w,ch))
#define mvwget_wstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:wget_wstr(w,s))
#define mvwgetn_wstr(w,y,x,s,n)	(wmove(w,y,x)==ERR?ERR:wgetn_wstr(w,s,n))
#define mvwgetnstr(w,y,x,ws,n)	(wmove(w,y,x)==ERR?ERR:wgetnstr(w,ws,n))
#define mvwhline(w,y,x,c,num)	(wmove(w,y,x)==ERR?ERR:whline(w,c,num))
#define mvwhline_set(w,y,x,c,num) (wmove(w,y,x)==ERR?ERR:whline_set(w,c,num))
#endif


#if defined(_NOMACROS) || defined(lint)
extern int      mvwin_wch __((WINDOW *, int, int, cchar_t *));
extern int	mvwin_wchnstr __((WINDOW *, int, int, cchar_t *, int));
extern int	mvwin_wchstr __((WINDOW *, int, int, cchar_t *));
extern int	mvwinchnstr __((WINDOW *, int, int, chtype *, int));
extern int	mvwinchstr __((WINDOW *, int, int, chtype *));
extern int	mvwinnstr __((WINDOW *, int, int, char *, int));
extern int	mvwinnwstr __((WINDOW *, int, int, wchar_t *, int));
extern int      mvwins_nwstr __((WINDOW *, int, int, const wchar_t *, int));
extern int      mvwins_wch __((WINDOW *, int, int, const cchar_t *));
extern int      mvwins_wstr __((WINDOW *, int, int, const wchar_t *));
extern int	mvwinsnstr __((WINDOW *, int, int, const char *, int));
extern int	mvwinsstr __((WINDOW *, int, int, const char *));
extern int	mvwinstr __((WINDOW *, int, int, char *));
extern int	mvwinwstr __((WINDOW *, int, int, wchar_t *));
extern int	mvwvline __((WINDOW *, int, int, chtype, int));
extern int	mvwvline_set __((WINDOW *, int, int, const cchar_t *, int));
#else
#define mvwin_wch(w,y,x,wc)	(wmove(w,y,x)==ERR?ERR:win_wch(w,wc))
#define mvwin_wchnstr(w,y,x,s,n) (wmove(w,y,x)==ERR?ERR:win_wchnstr(w,s,n))
#define mvwin_wchstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:win_wchstr(w,s))
#define mvwinchnstr(w,y,x,s,n)	(wmove(w,y,x)==ERR?ERR:winchnstr(w,s,n))
#define mvwinchstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:winchstr(w,s))
#define mvwinnstr(w,y,x,s,n)	(wmove(w,y,x)==ERR?ERR:winnstr(w,s,n))
#define mvwinnwstr(w,y,x,ws,n)	(wmove(w,y,x)==ERR?ERR:winnwstr(w,ws,n))
#define mvwins_nwstr(w,y,x,ws,n) (wmove(w,y,x)==ERR?ERR:wins_nwstr(w,ws,n))
#define mvwins_wch(w,y,x,c)	(wmove(w,y,x)==ERR?ERR:wins_wch(w,c))
#define mvwins_wstr(w,y,x,ws)	(wmove(w,y,x)==ERR?ERR:wins_wstr(w,ws))
#define mvwinsnstr(w,y,x,s,n)	(wmove(w,y,x)==ERR?ERR:winsnstr(w,s,n))
#define mvwinsstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:winsstr(w,s))
#define mvwinstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:winstr(w,s))
#define mvwinwstr(w,y,x,ws)	(wmove(w,y,x)==ERR?ERR:winwstr(w,ws))
#define mvwvline(w,y,x,c,num)	(wmove(w,y,x)==ERR?ERR:wvline(w,c,num))
#define mvwvline_set(w,y,x,c,num) (wmove(w,y,x)==ERR?ERR:wvline_set(w,c,num))
#endif


extern int	napms __((int));
extern void	noqiflush __((void));
extern int	notimeout __((WINDOW *, bool));


#if defined(_NOMACROS) || defined(lint)
extern int	PAIR_NUMBER __((int));
#else
#define PAIR_NUMBER(n)	(((n) & A_COLOR) >> 25)
#endif

extern int	pair_content __((short, short *, short *));
extern int	pecho_wchar __((WINDOW *, const cchar_t*));
extern int	pechochar __((WINDOW *, chtype));
extern int      putp __((const char *));
extern int	putwin __((WINDOW *, FILE *));


extern void	qiflush __((void));


extern int	redrawwin __((WINDOW *));
extern int	ripoffline __((int, int (*)(WINDOW *, int)));


#if defined(_NOMACROS) || defined(lint)
extern int	scrl __((int));
extern int	slk_init __((int));
#else
#define scrl(n)			wscrl(stdscr,n)
#define slk_init(f)		slk_start(((f == 0) ? 3 : 2),NULL)
#endif

extern int	scr_dump __((const char *));
extern int	scr_init __((const char *));
extern int	scr_restore __((const char *));
extern int	scr_set __((const char *));
extern int	setcchar __((cchar_t*, const wchar_t*, const attr_t, short, const void*));
extern int	slk_attr_off __((const attr_t, void *));
extern int	slk_attr_on __((const attr_t, void *));
extern int	slk_attr_set __((const attr_t, short, void *));
extern int	slk_attroff __((const chtype));
extern int	slk_attron __((const chtype));
extern int	slk_attrset __((const chtype));
extern int	slk_clear __((void));
extern int	slk_color __((short));
extern char	*slk_label __((int));
extern int	slk_noutrefresh __((void));
extern int	slk_refresh __((void));
extern int	slk_restore __((void));
extern int	slk_set __((int, const char *, int));
extern int	slk_touch __((void));
extern int      slk_wset __((int, const wchar_t *, int));
extern int	start_color __((void));
extern WINDOW	*subpad __((WINDOW *, int, int, int, int));
extern int	syncok __((WINDOW *, bool));


#if defined(_NOMACROS) || defined(lint)
extern void	timeout __((int));
extern int	touchline __((WINDOW *, int, int));
#else
#define timeout(tm)		wtimeout(stdscr,tm)
#define touchline(w,y,n)	wtouchln((w),(y),(n),TRUE)
#endif

extern attr_t	term_attrs __((void));
extern chtype	termattrs __((void));
extern char	*termname __((void));
extern int     	tigetflag __((char *));
extern int	tigetnum __((char *));
extern char    	*tigetstr __((char *));
extern char	*tparm __((char *, ...));


extern int	unget_wch __((const wchar_t));
extern int	ungetch __((int));
extern int	untouchwin __((WINDOW *));
extern void	use_env __((bool));


#if defined(_NOMACROS) || defined(lint)
extern int	vline __((chtype, int));
extern int	vline_set __((const cchar_t *, int));
#else
#define vline(c,num)		wvline(stdscr,c,num)
#define vline_set(c,num)	wvline_set(stdscr,c,num)
#endif

extern int      vid_attr __((attr_t, short, void *));
extern int      vid_puts __((attr_t, short, void *, int (*)(int)));
extern int	vidattr __((chtype));
extern int      vidputs __((chtype, int (*)(int)));
extern int	vw_printw __((WINDOW *, char *, va_list));
extern int	vw_scanw __((WINDOW *, char *, va_list));
extern int	vwprintw __((WINDOW *, char *, va_list));
extern int	vwscanw __((WINDOW *, char *, va_list));


#if defined(_NOMACROS) || defined(lint)
extern int	wadd_wchstr __((WINDOW *, const cchar_t *));
extern int	waddstr __((WINDOW *, const char *));
extern int	waddwstr __((WINDOW *, const wchar_t *));
extern int	wins_wstr __((WINDOW *, const wchar_t *));
extern int	winchstr __((WINDOW *, chtype *));
extern int	winsstr __((WINDOW *, const char *));
#else
#define wadd_wchstr(w,s)	wadd_wchnstr(w,s,-1)
#define waddstr(w,s)		waddnstr(w,s,-1)
#define waddwstr(w,s)		waddnwstr(w,s,-1)
#define wins_wstr(w,ws)		wins_nwstr(w,ws,-1)
#define winchstr(w,s)		winchnstr((w),(s),-1)
#define winsstr(w,s)		winsnstr((w),(s),-1)
#endif

extern int	wadd_wch __((WINDOW *, const cchar_t *));
extern int	wadd_wchnstr __((WINDOW *, const cchar_t *, int));
extern int	waddchnstr __((WINDOW *, const chtype *, int));
extern int	waddnstr __((WINDOW *, const char *, int));
extern int	waddnwstr __((WINDOW *, const wchar_t *, int));
extern int	wattr_get __((WINDOW *, attr_t *, short *, void *));
extern int	wattr_off __((WINDOW *, attr_t, void *));
extern int	wattr_on __((WINDOW *, attr_t, void *));
extern int	wattr_set __((WINDOW *, attr_t, short, void *));
extern int	wbkgd __((WINDOW *, chtype));
extern void	wbkgdset __((WINDOW *, chtype));
extern int	wbkgrnd __((WINDOW *, const cchar_t *));
extern void	wbkgrndset __((WINDOW *, const cchar_t *));
extern int	wborder __((WINDOW *, chtype, chtype, chtype, chtype, 
		  chtype, chtype, chtype, chtype));
extern int	wborder_set __((WINDOW *, const cchar_t *, const cchar_t *, 
		  const cchar_t *, const cchar_t *, const cchar_t *, 
		  const cchar_t *, const cchar_t *, const cchar_t *));
extern int	wchgat __((WINDOW *, int, attr_t, short, const void *));
extern int	wcolor_set __((WINDOW *, short, void *));
extern void	wcursyncup __((WINDOW *));
extern int	wecho_wchar __((WINDOW *, const cchar_t *));
extern int	wechochar __((WINDOW *, const chtype));
extern int	wget_wch __((WINDOW *, wint_t *));
extern int	wget_wstr __((WINDOW *, wint_t *));
extern int	wgetbkgrnd __((WINDOW *, cchar_t *));
extern int	wgetn_wstr __((WINDOW *, wint_t *, int));
extern int	wgetnstr __((WINDOW *, char *, int));
extern int	whline __((WINDOW *, chtype, int));
extern int	whline_set __((WINDOW *, const cchar_t *, int));
extern int	win_wch __((WINDOW *, cchar_t *));
extern int	win_wchnstr __((WINDOW *, cchar_t *, int));
extern int	win_wchstr __((WINDOW *, cchar_t *));
extern int	winchnstr __((WINDOW *, chtype *, int));
extern int	winnstr __((WINDOW *, char *, int));
extern int	winnwstr __((WINDOW *, wchar_t *, int));
extern int      wins_nwstr __((WINDOW *, const wchar_t *, int));
extern int	wins_wch __((WINDOW *, const cchar_t *));
extern int	winsdelln __((WINDOW *, int));
extern int	winsnstr __((WINDOW *, const char *, int));
extern int	winstr __((WINDOW *, char *));
extern int	winwstr __((WINDOW *, wchar_t *));
extern int	wredrawln __((WINDOW *, int, int));
extern int	wscrl __((WINDOW *, int));
extern void	wsyncdown __((WINDOW *));
extern void	wsyncup __((WINDOW *));
extern void	wtimeout __((WINDOW *, int));
extern int	wtouchln __((WINDOW *, int, int, int));
extern wchar_t	*wunctrl __((cchar_t *));
extern int	wvline __((WINDOW *, chtype, int));
extern int	wvline_set __((WINDOW *, const cchar_t *, int));

#endif  /* _XOPEN_SOURCE_EXTENDED */


#ifdef _XOPEN_SOURCE

/* These interfaces are carried forward from XPG3 curses;
 * when _XOPEN_SOURCE_EXTENDED is defined, _XOPEN_SOURCE
 * will automatically be defined as well.
 */

#if defined(_NOMACROS) || defined(lint)
extern int	addch __((const chtype));
extern int	addchstr __((const chtype *));
extern int	attroff __((int));
extern int	attron __((int));
extern int	attrset __((int));
extern int	beep __((void));
extern int	clear __((void));
extern int	clrtobot __((void));
extern int	clrtoeol __((void));
extern int	delch __((void));
extern int	deleteln __((void));
extern int	echo __((void));
extern int      erase __((void));
extern int	flash __((void));
extern int	getch __((void));
extern int	getstr __((char *));

/* FOR NOW: extern void     getyx __((WINDOW *, int, int));
 */
#define getyx(w,y,x)    ((y) = getcury(w), (x) = getcurx(w))

extern chtype	inch __((void));
extern int	insch __((chtype));
extern int	insertln __((void));
extern int      move __((int, int));
extern int	mvaddch __((int, int, const chtype));
extern int	mvaddchstr __((int, int, const chtype *));
extern int	mvdelch __((int, int));
extern int	mvgetch __((int, int));
extern int	mvgetstr __((int, int, char *));
extern chtype	mvinch __((int, int));
extern int	mvinsch __((int, int, chtype));
extern int	mvwaddch __((WINDOW *, int, int, const chtype));
extern int	mvwaddchstr __((WINDOW *, int, int, const chtype *));
extern int	mvwdelch __((WINDOW *, int, int));
extern int	mvwgetch __((WINDOW *, int, int));
extern int      mvwgetstr __((WINDOW *, int, int, char *));
extern chtype	mvwinch __((WINDOW *, int, int));
extern int	mvwinsch __((WINDOW *, int, int, chtype));
extern int	nl __((void));
extern int	noecho __((void));
extern int	nonl __((void));
extern int	refresh __((void));
extern int	scroll __((WINDOW *));
extern SCREEN	*set_term __((SCREEN *));
extern int	setscrreg __((int, int));
extern int	standend __((void));
extern int	standout __((void));
extern int	waddchstr __((WINDOW *, const chtype *));
extern int	wclear __((WINDOW *));
extern int	wdeleteln __((WINDOW *));
extern int	werase __((WINDOW *));
extern int	winsertln __((WINDOW *));
#else /* _NOMACROS || lint */
#define addch(ch)		waddch(stdscr, ch)
#define addchstr(s)		waddchstr(stdscr,s)
#define attroff(at)		wattroff(stdscr,at)
#define attron(at)		wattron(stdscr,at)
#define attrset(at)		wattrset(stdscr,at)
#define beep()			_ring(TRUE)
#define clear()			wclear(stdscr)
#define clrtobot()		wclrtobot(stdscr)
#define clrtoeol()		wclrtoeol(stdscr)
#define delch()			wdelch(stdscr)
#define deleteln()		wdeleteln(stdscr)
#define echo()			_setecho(TRUE)
#define erase()			werase(stdscr)
#define flash()			_ring(FALSE)
#define getch()                 wgetch(stdscr)
#define getstr(s)		wgetstr(stdscr,s)
#define getyx(w,y,x)	((y) = getcury(w), (x) = getcurx(w))
#define inch()			winch(stdscr)
#define insch(c)		winsch(stdscr,c)
#define insertln()		winsertln(stdscr)
#define move(y,x)		wmove(stdscr,y,x)
#define mvaddch(y,x,ch)		mvwaddch(stdscr,y,x,ch)
#define mvaddchstr(y,x,s)	mvwaddchstr(stdscr,y,x,s)
#define mvdelch(y,x)		mvwdelch(stdscr,y,x)
#define mvgetch(y,x)		mvwgetch(stdscr,y,x)
#define mvgetstr(y,x,s)		mvwgetstr(stdscr,y,x,s)
#define mvinch(y,x)		mvwinch(stdscr,y,x)
#define mvinsch(y,x,c)		mvwinsch(stdscr,y,x,c)
#define mvwaddch(w,y,x,ch)	(wmove(w,y,x)==ERR?ERR:waddch(w,ch))
#define mvwaddchstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:waddchstr(w,s))
#define mvwdelch(w,y,x)		(wmove(w,y,x)==ERR?ERR:wdelch(w))
#define mvwgetch(w,y,x)		(wmove(w,y,x)==ERR?ERR:wgetch(w))
#define mvwgetstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:wgetstr(w,s))
#define mvwinch(w,y,x)		(wmove(w,y,x)==ERR?(chtype) ERR:winch(w))
#define mvwinsch(w,y,x,c)	(wmove(w,y,x)==ERR?ERR:winsch(w,c))
#define nl()			_setnonl(FALSE)
#define noecho()		_setecho(FALSE)
#define nonl()			_setnonl(TRUE)
#define refresh()		wrefresh(stdscr)
#define scroll(w)		wscrl((w),1)
#define set_term(s)		setcurscreen(s)
#define setscrreg(t,b)		wsetscrreg(stdscr,t,b)
#define standend()		wstandend(stdscr)
#define standout()		wstandout(stdscr)
#define waddchstr(w,s)		waddchnstr(w,s,-1)
#define wclear(w)		(clearok((w),TRUE), werase(w))
#define wdeleteln(w)		winsdelln((w),-1)
#define werase(w)		(wmove((w),0,0), wclrtobot(w))
#define winsertln(w)		winsdelln((w),1)
#endif

extern int	baudrate __((void));
extern int	box __((WINDOW *, chtype, chtype));
extern int	cbreak __((void));
extern int	clearok __((WINDOW *, bool));
extern int	def_prog_mode __((void));
extern int	def_shell_mode __((void));
extern int	delay_output __((int));
extern int	delwin __((WINDOW *));
extern int	doupdate __((void));
extern int	endwin __((void));
extern char	erasechar __((void));
extern int	flushinp __((void));
extern bool	has_ic __((void));
extern bool	has_il __((void));
extern int	idlok __((WINDOW *, bool));
extern WINDOW	*initscr __((void));
extern int	intrflush __((WINDOW *, bool));
extern int	keypad __((WINDOW *, bool));
extern char	killchar __((void));
extern int	leaveok __((WINDOW *, bool));
extern char	*longname __((void));
extern int	mvprintw __((int, int, char *, ...));
extern int	mvscanw __((int, int, char *, ...));
extern int	mvwin __((WINDOW *, int, int));
extern int	mvwprintw __((WINDOW *, int, int, char *, ...));
extern int	mvwscanw __((WINDOW *, int, int, char *, ...));
extern WINDOW	*newpad __((int, int));
extern SCREEN	*newterm __((char *, FILE *, FILE *));
extern WINDOW	*newwin __((int, int, int, int));
extern int	nocbreak __((void));
extern int	nodelay __((WINDOW *, bool));
extern int	noraw __((void));
extern int	overlay __((const WINDOW *, WINDOW *));
extern int	overwrite __((const WINDOW *, WINDOW *));
extern int	pnoutrefresh __((WINDOW *, int, int, int, int, int, int));
extern int	prefresh __((WINDOW *, int, int, int, int, int, int));
extern int	printw __((char *, ...));
extern int	raw __((void));
extern int	reset_prog_mode __((void));
extern int	reset_shell_mode __((void));
extern int	resetty __((void));
extern int	savetty __((void));
extern int	scanw __((char *, ...));
extern int	scrollok __((WINDOW *, bool));
extern WINDOW	*subwin __((WINDOW *, int, int, int, int));
extern int	touchwin __((WINDOW *));
extern int	typeahead __((int));
extern int	waddch __((WINDOW *, const chtype));
extern int	wattroff __((WINDOW *, int));
extern int	wattron __((WINDOW *, int));
extern int	wattrset __((WINDOW *, int));
extern int	wclrtobot __((WINDOW *));
extern int	wclrtoeol __((WINDOW *));
extern int	wdelch __((WINDOW *));
extern int	wgetch __((WINDOW *));
extern int	wgetstr __((WINDOW *, char *));
extern chtype	winch __((WINDOW *));
extern int	winsch __((WINDOW *, chtype));
extern int	wmove __((WINDOW *, int, int));
extern int	wnoutrefresh __((WINDOW *));
extern int	wprintw __((WINDOW *, char *, ...));
extern int	wrefresh __((WINDOW *));
extern int	wscanw __((WINDOW *, char *, ...));
extern int	wsetscrreg __((WINDOW *, int, int));
extern int	wstandend __((WINDOW *));
extern int	wstandout __((WINDOW *));

#endif /* _XOPEN_SOURCE */


#if defined(_OSF_SOURCE) || defined(__CURSES__)

    /* Additional functions for SVR4 MNLS compatibility */

#if defined(_NOMACROS) || defined(lint)

extern int	addwch __((chtype));
extern int	addwchnstr __((chtype *, int));
extern int	addwchstr __((chtype *));
extern int	echowchar __((chtype));
extern int	getnwstr __((wchar_t *, int));
extern int	getwch __((void));
extern int	getwstr __((wchar_t *));
extern int	insnwstr __((wchar_t *, int));
extern int	inswch __((chtype));
extern int	inswstr __((wchar_t *));
extern chtype	inwch __((void));
extern int	inwchnstr __((chtype *, int));
extern int	inwchstr __((chtype *));
extern int	mvaddwch __((int, int, chtype));
extern int	mvaddwchnstr __((int, int, chtype *, int));
extern int	mvaddwchstr __((int, int, chtype *));
extern int	mvgetnwstr __((int, int, wchar_t *, int));
extern int	mvgetwch __((int, int));
extern int	mvgetwstr __((int, int, wchar_t *));
extern int	mvinsnwstr __((int, int, wchar_t *, int));
extern int	mvinswch __((int, int, chtype));
extern int	mvinswstr __((int, int, wchar_t *));
extern chtype	mvinwch __((int, int));
extern int	mvinwchnstr __((int, int, chtype *, int));
extern int	mvinwchstr __((int, int, chtype *));
extern int	mvwaddwch __((WINDOW *, int, int, chtype));
extern int	mvwaddwchnstr __((WINDOW *, int, int, chtype *, int));
extern int	mvwaddwchstr __((WINDOW *, int, int, chtype *));
extern int	mvwgetnwstr __((WINDOW *, int, int, wchar_t *, int));
extern int      mvwgetwch __((WINDOW *, int, int));
extern int      mvwgetwstr __((WINDOW*, int, int, wchar_t *));
extern int	mvwinsnwstr __((WINDOW *, int, int, wchar_t *, int));
extern int	mvwinswch __((WINDOW *, int, int, chtype));
extern int	mvwinswstr __((WINDOW *, int, int, wchar_t *));
extern chtype	mvwinwch __((WINDOW *, int, int));
extern int	mvwinwchnstr __((WINDOW *, int, int, chtype *, int));
extern int	mvwinwchstr __((WINDOW *, int, int, chtype *));
extern int	waddwchstr __((WINDOW *, chtype *));
extern int	winswstr __((WINDOW *, wchar_t *));

#else  /* defined(_NOMACROS) || defined(lint) */

#define addwch(ch)		waddwch(stdscr,ch)
#define addwchnstr(s,n)		waddwchnstr(stdscr,s,n)
#define addwchstr(s)		waddwchstr(stdscr,s)
#define echowchar(ch)		wechowchar(stdscr,ch)
#define getnwstr(ws,n)		wgetnwstr(stdscr,ws,n)
#define getwch()		wgetwch(stdscr)
#define getwstr(ws)		wgetwstr(stdscr,ws)
#define insnwstr(ws,n)          winsnwstr(stdscr,ws,n)
#define inswch(c)		winswch(stdscr,c)
#define inswstr(ws)		winswstr(stdscr,ws)
#define inwch()			winwch(stdscr)
#define inwchnstr(s,n)		winwchnstr(stdscr,s,n)
#define inwchstr(s)		winwchstr(stdscr,s)
#define mvaddwch(y,x,ch)	mvwaddwch(stdscr,y,x,ch)
#define mvaddwchnstr(y,x,s,n)	mvwaddwchnstr(stdscr,y,x,s,n)
#define mvaddwchstr(y,x,s)	mvwaddwchstr(stdscr,y,x,s)
#define mvgetnwstr(y,x,ws,n)	mvwgetnwstr(stdscr,y,x,ws,n)
#define mvgetwch(y,x)		mvwgetwch(stdscr,y,x)
#define mvgetwstr(y,x,ws)	mvwgetwstr(stdscr,y,x,ws)
#define mvinsnwstr(y,x,ws,n)	mvwinsnwstr(stdscr,y,x,ws,n)
#define mvinswch(y,x,c)		mvwinswch(stdscr,y,x,c)
#define mvinswstr(y,x,ws)	mvwinswstr(stdscr,y,x,ws)
#define mvinwch(y,x)		mvwinwch(stdscr,y,x)
#define mvinwchnstr(y,x,s,n)	mvwinwchnstr(stdscr,y,x,s,n)
#define mvinwchstr(y,x,s)	mvwinwchstr(stdscr,y,x,s)
#define mvwaddwch(w,y,x,ch)	(wmove(w,y,x)==ERR?ERR:waddwch(w,ch))
#define mvwaddwchnstr(w,y,x,s,n) (wmove(w,y,x)==ERR?ERR:waddwchnstr(w,s,n))
#define mvwaddwchstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:waddwchstr(w,s))
#define mvwgetnwstr(w,y,x,ws,n) (wmove(w,y,x)==ERR?ERR:wgetnwstr(w,ws,n))
#define mvwgetwch(w,y,x)	(wmove(w,y,x)==ERR?ERR:wgetwch(w))
#define mvwgetwstr(w,y,x,ws)	(wmove(w,y,x)==ERR?ERR:wgetwstr(w,ws))
#define mvwinsnwstr(w,y,x,ws,n) (wmove(w,y,x)==ERR?ERR:winsnwstr(w,ws,n))
#define mvwinswch(w,y,x,c)	(wmove(w,y,x)==ERR?ERR:winswch(w,c))
#define mvwinswstr(w,y,x,ws)	(wmove(w,y,x)==ERR?ERR:winswstr(w,ws))
#define mvwinwch(w,y,x)		(wmove(w,y,x)==ERR?(chtype)ERR:winwch(w))
#define mvwinwchnstr(w,y,x,s,n)	(wmove(w,y,x)==ERR?ERR:winwchnstr(w,s,n))
#define mvwinwchstr(w,y,x,s)	(wmove(w,y,x)==ERR?ERR:winwchstr(w,s))
#define waddwchstr(w,s)		waddwchnstr(w,s,-1)
#define winswstr(w,ws)		winsnwstr(w,ws,-1)

#endif	/* _NOMACROS || lint */

extern int	pechowchar __((WINDOW *, chtype));
extern int	ungetwch __((wchar_t));
extern int	waddwch __((WINDOW *, chtype));
extern int	waddwchnstr __((WINDOW *, const chtype *, int));
extern int	wechowchar __((WINDOW *, chtype));
extern int	wgetnwstr __((WINDOW *, wchar_t *, int));
extern int	wgetwch __((WINDOW *));
extern int	wgetwstr __((WINDOW *, wchar_t *));
extern int	winsnwstr __((WINDOW *, wchar_t *, int));
extern int	winswch __((WINDOW *, chtype));
extern chtype	winwch __((WINDOW *));
extern int	winwchnstr __((WINDOW *, chtype *, int));
extern int	winwchstr __((WINDOW *, chtype *));

    /* END MNLS INTERFACES */

    /* Other legacy interfaces. */

#if defined(_NOMACROS) || defined(lint)

extern int	crmode __((void));
extern int	garbagedlines __((WINDOW *, int, int));
extern int	garbagedwin __((WINDOW *));
extern int	gettmode __((void));
extern int	nocrmode __((void));
extern int	setterm __((char *));

#else  /* _NOMACROS || lint */

#define crmode()	       	cbreak()
#define garbagedlines(w,m,n)   	wredrawln(w,m,n)
#define garbagedwin(w)		redrawwin(w)
#define gettmode()		(OK)
#define nocrmode()		nocbreak()
#define setterm(name)		setupterm((name),1,(char*)NULL)

#endif  /* _NOMACROS || lint */

extern int	_meta __((bool));
extern int	_overlay __((WINDOW *, WINDOW *, int));
extern int      cursor_on __((void));
extern int      cursor_off __((void));
extern void	curserr __((void));
extern int	draino __((int));
extern chtype	getattrs __((WINDOW *));
extern unsigned long getbmap __((void));
extern unsigned long getmouse __((void));
extern int	map_button __((unsigned long));
extern int	mouse_off __((long int));
extern int	mouse_on __((long int));
extern int	mouse_set __((long int));
extern int	newkey __((char *, int, int));
extern SCREEN	*newscreen __((char *, int, int, int, FILE *, FILE *));
extern int	request_mouse_pos __((void));
extern int	resetterm __((void));
extern int	setsyx __((int, int));
extern int	traceoff __((void));
extern int	traceon __((void));
extern void	vidupdate __((chtype, chtype, int (*)(int)));
extern chtype	wgetbkgd __((WINDOW *));
extern void	wmouse_position __((WINDOW *, int *, int *));

#endif  /* defined(_OSF_SOURCE) || defined(__CURSES__) */

#else  /* _MINICURSES */

    /* First, map MINICURSES functions to std ones as needed. */

# define	addch(ch)		waddch(stdscr,(chtype)ch)
# define	addstr(str)		waddstr(stdscr,str)
# define	attroff(at)		wattroff(stdscr,at)
# define	attron(at)		wattron(stdscr,at)
# define	attrset(at)		wattrset(stdscr,at)
# define	clear()			wclear(stdscr)
# define	erase()			werase(stdscr)
# define	move(y,x)		wmove(stdscr,y,x)
# define	mvaddch(y,x,ch)		move(y, x), addch(ch)
# define	mvaddstr(y,x,str)	move(y, x), addstr(str)
# define	refresh()		wrefresh(stdscr)
# define	standout()		wstandout(stdscr)
# define	standend()		wstandend(stdscr)

    /* Describe std functions needed for MINICURSES */

extern WINDOW	*initscr __((void));
extern SCREEN	*newterm __((char *, FILE *, FILE *));
extern int	waddch __((WINDOW *, const chtype));
extern int	waddstr __((WINDOW *, const char *));
extern int	wattroff __((WINDOW *, int));
extern int	wattron __((WINDOW *, int));
extern int	wattrset __((WINDOW *, int));
extern int	wclear __((WINDOW *));
extern int      werase __((WINDOW *));
extern int	wmove __((WINDOW *, int, int));
extern int	wrefresh __((WINDOW *));
extern int	wstandend __((WINDOW *));
extern int	wstandout __((WINDOW *));


/*
 * These functions don't exist in minicurses, so we define them
 * to nonexistent functions to help the user catch the error.
 */

#define	getch		m_getch
#define	getstr		m_getstr
#define	clrtobot	m_clrtobot
#define	clrtoeol	m_clrtoeol
#define	insertln	m_insertln
#define	deleteln	m_deleteln
#define	inch		m_inch
#define	insch		m_insch
#define	delch		m_delch
/* mv functions that aren't valid */
#define	mvwaddch	m_mvwaddch
#define	mvwgetch	m_mvwgetch
#define	mvwaddstr	m_mvaddstr
#define	mvwgetstr	m_mvwgetstr
#define	mvwinch		m_mvwinch
#define	mvwdelch	m_mvwdelch
#define	mvwinsch	m_mvwinsch
#define	mvgetch		m_mvwgetch
#define	mvgetstr	m_mvwgetstr
#define	mvinch		m_mvwinch
#define	mvdelch		m_mvwdelch
#define	mvinsch		m_mvwinsch
/* Real functions that aren't valid */
#define box		m_box
#define delwin		m_delwin
#define longname	m_longname
#define makenew		m_makenew
#define mvprintw	m_mvprintw
#define mvscanw		m_mvscanw
#define mvwin		m_mvwin
#define mvwprintw	m_mvwprintw
#define mvwscanw	m_mvwscanw
#define newwin		m_newwin
#define _outchar        m_outchar
#define overlay		m_overlay
#define overwrite	m_overwrite
#define printw		m_printw
#define putp		m_putp
#define scanw		m_scanw
#define scroll		m_scroll
#define subwin		m_subwin
#define touchwin	m_touchwin
#define _tscroll        m_tscroll
#define _tstp		m_tstp
#define vidattr		m_vidattr
#define wclrtobot	m_wclrtobot
#define wclrtoeol	m_wclrtoeol
#define wdelch		m_wdelch
#define wdeleteln	m_wdeleteln
#define wgetch		m_wgetch
#define wgetstr		m_wgetstr
#define winsch		m_winsch
#define winsertln	m_winsertln
#define wprintw		m_wprintw
#define wscanw		m_wscanw
#define setscrreg	m_setscrreg
#define wsetscrreg	m_wsetscrreg

#endif /* _MINICURSES */


    /* assorted support functions */
    /* always define these        */

extern int	_getsyx __((int *, int *));
extern int	_ring __((int));
extern int	_setecho __((int));
extern int	_setnonl __((int));
extern int	getbegx __((WINDOW *));
extern int	getbegy __((WINDOW *));
extern int	getcurx __((WINDOW *));
extern int	getcury __((WINDOW *));
extern int	getmaxx __((WINDOW *));
extern int	getmaxy __((WINDOW *));
extern int	getparx __((WINDOW *));
extern int	getpary __((WINDOW *));
extern SCREEN	*setcurscreen __((SCREEN *));
extern int	slk_start __((int, int *));

    /* always define this macro */

#define getsyx(y,x)	_getsyx(&(y),&(x))


/*
 * Standard alternate character set.  The current ACS world is evolving,
 * so we support only a widely available subset: the line drawing characters
 * from the VT100, plus a few from the Teletype 5410v1.  Eventually there
 * may be support of more sophisticated ACS line drawing, such as that
 * in the Teletype 5410, the HP line drawing set, and the like.  There may
 * be support for some non line oriented characters as well.
 *
 * Line drawing ACS names are of the form ACS_trbl, where t is the top, r
 * is the right, b is the bottom, and l is the left.  t, r, b, and l might
 * be B (blank), S (single), D (double), or T (thick).  The subset defined
 * here only uses B and S.
 */

#define ACS_BSSB	(_acs_map['l'])
#define ACS_SSBB	(_acs_map['m'])
#define ACS_BBSS	(_acs_map['k'])
#define ACS_SBBS	(_acs_map['j'])
#define ACS_SBSS	(_acs_map['u'])
#define ACS_SSSB	(_acs_map['t'])
#define ACS_SSBS	(_acs_map['v'])
#define ACS_BSSS	(_acs_map['w'])
#define ACS_BSBS	(_acs_map['q'])
#define ACS_SBSB	(_acs_map['x'])
#define ACS_SSSS	(_acs_map['n'])

#define WACS_BSSB	(&(_wacs_map['l']))
#define WACS_SSBB	(&(_wacs_map['m']))
#define WACS_BBSS	(&(_wacs_map['k']))
#define WACS_SBBS	(&(_wacs_map['j']))
#define WACS_SBSS	(&(_wacs_map['u']))
#define WACS_SSSB	(&(_wacs_map['t']))
#define WACS_SSBS	(&(_wacs_map['v']))
#define WACS_BSSS	(&(_wacs_map['w']))
#define WACS_BSBS	(&(_wacs_map['q']))
#define WACS_SBSB	(&(_wacs_map['x']))
#define WACS_SSSS	(&(_wacs_map['n']))

/*
 * Human readable names for the most commonly used characters.
 * "Upper", "right", etc. are chosen to be consistent with the vt100 manual.
 */

#define WACS_ULCORNER	WACS_BSSB
#define WACS_LLCORNER	WACS_SSBB
#define WACS_URCORNER	WACS_BBSS
#define WACS_LRCORNER	WACS_SBBS
#define WACS_RTEE	WACS_SBSS
#define WACS_LTEE	WACS_SSSB
#define WACS_BTEE	WACS_SSBS
#define WACS_TTEE	WACS_BSSS
#define WACS_HLINE	WACS_BSBS
#define WACS_VLINE	WACS_SBSB
#define WACS_PLUS	WACS_SSSS

#define ACS_ULCORNER	ACS_BSSB
#define ACS_LLCORNER	ACS_SSBB
#define ACS_URCORNER	ACS_BBSS
#define ACS_LRCORNER	ACS_SBBS
#define ACS_RTEE	ACS_SBSS
#define ACS_LTEE	ACS_SSSB
#define ACS_BTEE	ACS_SSBS
#define ACS_TTEE	ACS_BSSS
#define ACS_HLINE	ACS_BSBS
#define ACS_VLINE	ACS_SBSB
#define ACS_PLUS	ACS_SSSS

#define ACS_S1		(_acs_map['o']) /* scan line 1 */
#define ACS_S9 		(_acs_map['s']) /* scan line 9 */
#define ACS_DIAMOND	(_acs_map['`']) /* diamond */
#define ACS_CKBOARD	(_acs_map['a']) /* checker board */
#define ACS_DEGREE	(_acs_map['f']) /* degree symbol */
#define ACS_PLMINUS	(_acs_map['g']) /* plus/minus */
#define ACS_BULLET	(_acs_map['~']) /* bullet */

#define WACS_S1		(&(_wacs_map['o'])) /* scan line 1 */
#define WACS_S9 	(&(_wacs_map['s'])) /* scan line 9 */
#define WACS_DIAMOND	(&(_wacs_map['`'])) /* diamond */
#define WACS_CKBOARD	(&(_wacs_map['a'])) /* checker board */
#define WACS_DEGREE	(&(_wacs_map['f'])) /* degree symbol */
#define WACS_PLMINUS	(&(_wacs_map['g'])) /* plus/minus */
#define WACS_BULLET	(&(_wacs_map['~'])) /* bullet */

	/* Teletype 5410v1 symbols */
#define ACS_LARROW	(_acs_map[',']) /* arrow left */
#define ACS_RARROW	(_acs_map['+']) /* arrow right */
#define ACS_DARROW	(_acs_map['.']) /* arrow down */
#define ACS_UARROW	(_acs_map['-']) /* arrow up */
#define ACS_BOARD	(_acs_map['h']) /* board of squares */
#define ACS_LANTERN	(_acs_map['i']) /* lantern symbol */
#define ACS_BLOCK	(_acs_map['0']) /* solid square block */

#define WACS_LARROW	(&(_wacs_map[','])) /* arrow left */
#define WACS_RARROW	(&(_wacs_map['+'])) /* arrow right */
#define WACS_DARROW	(&(_wacs_map['.'])) /* arrow down */
#define WACS_UARROW	(&(_wacs_map['-'])) /* arrow up */
#define WACS_BOARD	(&(_wacs_map['h'])) /* board of squares */
#define WACS_LANTERN	(&(_wacs_map['i'])) /* lantern symbol */
#define WACS_BLOCK	(&(_wacs_map['0'])) /* solid square block */

/* Funny "characters" enabled for various special function keys for input */
/* This list is created from caps and curses.ed. Do not edit it! */
#define KEY_CODE_YES	0377		/* A key was returned */
#define KEY_MIN		0401		/* Minimum curses key */
#define KEY_BREAK	0401		/* break key (unreliable) */
#define KEY_DOWN	0402		/* Sent by terminal down arrow key */
#define KEY_UP		0403		/* Sent by terminal up arrow key */
#define KEY_LEFT	0404		/* Sent by terminal left arrow key */
#define KEY_RIGHT	0405		/* Sent by terminal right arrow key */
#define KEY_HOME	0406		/* Sent by home key. */
#define KEY_BACKSPACE	0407		/* Sent by backspace key */
#define KEY_F0		0410		/* Sent by function key f0. */
#define KEY_F(n)	(KEY_F0+(n))	/* Space for 64 function keys is 
reserved. */
#define KEY_DL		0510		/* Sent by delete line key. */
#define KEY_IL		0511		/* Sent by insert line. */
#define KEY_DC		0512		/* Sent by delete character key. */
#define KEY_IC		0513		/* Sent by ins char/enter ins mode key. 
*/
#define KEY_EIC		0514		/* Sent by rmir or smir in insert mode. 
*/
#define KEY_CLEAR	0515		/* Sent by clear screen or erase key. */
#define KEY_EOS		0516		/* Sent by clear-to-end-of-screen key. 
*/
#define KEY_EOL		0517		/* Sent by clear-to-end-of-line key. */
#define KEY_SF		0520		/* Sent by scroll-forward/down key */
#define KEY_SR		0521		/* Sent by scroll-backward/up key */
#define KEY_NPAGE	0522		/* Sent by next-page key */
#define KEY_PPAGE	0523		/* Sent by previous-page key */
#define KEY_STAB	0524		/* Sent by set-tab key */
#define KEY_CTAB	0525		/* Sent by clear-tab key */
#define KEY_CATAB	0526		/* Sent by clear-all-tabs key. */
#define KEY_ENTER	0527		/* sent by enter/send key */
#define KEY_SRESET	0530		/* soft (partial) reset (unreliable) */
#define KEY_RESET	0531		/* reset or hard reset (unreliable) */
#define KEY_PRINT	0532		/* sent by print or copy key */
#define KEY_LL		0533		/* Sent by home-down key */
					/* The keypad is arranged like this: */
					/*    a1    up    a3   */
					/*   left   b2  right  */
					/*    c1   down   c3   */
#define KEY_A1		0534		/* Upper left of keypad */
#define KEY_A3		0535		/* Upper right of keypad */
#define KEY_B2		0536		/* Center of keypad */
#define KEY_C1		0537		/* Lower left of keypad */
#define KEY_C3		0540		/* Lower right of keypad */
#define KEY_ACTION	0541		/* Sent by the action key. */
#define KEY_BEG		0542		/* sent by beg(inning) key */
#define KEY_CANCEL	0543		/* sent by cancel key */
#define KEY_CLOSE	0544		/* sent by close key */
#define KEY_COMMAND	0545		/* Command request key */
#define KEY_COPY	0546		/* sent by copy key */
#define KEY_CREATE	0547		/* sent by create key */
#define KEY_END		0550		/* End key */
#define KEY_EXIT	0551		/* sent by exit key */
#define KEY_FIND	0552		/* sent by find key */
#define KEY_HELP	0553		/* Help key */
#define KEY_MARK	0554		/* sent by mark key */
#define KEY_MESSAGE	0555		/* sent by message key */
#define KEY_MOVE	0556		/* sent by move key */
#define KEY_NEXT	0557		/* sent by next-object key */
#define KEY_OPEN	0560		/* sent by open key */
#define KEY_OPTIONS	0561		/* sent by options key */
#define KEY_PREVIOUS	0562		/* sent by previous-object */
#define KEY_REDO	0563		/* sent by redo key */
#define KEY_REFERENCE	0564		/* sent by ref(erence) key */
#define KEY_REFRESH	0565		/* sent by refresh key */
#define KEY_REPLACE	0566		/* sent by replace key */
#define KEY_RESTART	0567		/* sent by restart key */
#define KEY_RESUME	0570		/* sent by resume key */
#define KEY_SAVE	0571		/* sent by save key */
#define KEY_SBEG	0572		/* sent by shifted beginning key */
#define KEY_SCANCEL	0573		/* sent by shifted cancel key */
#define KEY_SCOMMAND	0574		/* sent by shifted */
#define KEY_SCOPY	0575		/* sent by shifted copy key */
#define KEY_SCREATE	0576		/* sent by shifted create key */
#define KEY_SDC		0577		/* sent by shifted delete-char key */
#define KEY_SDL		0600		/* sent by shifted delete-line key */
#define KEY_SELECT	0601		/* Select key */
#define KEY_SEND	0602		/* sent by shifted end key */
#define KEY_SEOL	0603		/* sent by shifted clear-line key */
#define KEY_SEXIT	0604		/* sent by shifted exit key */
#define KEY_SFIND	0605		/* sent by shifted find key */
#define KEY_SHELP	0606		/* sent by shifted help key */
#define KEY_SHOME	0607		/* sent by shifted home key */
#define KEY_SIC		0610		/* sent by shifted input key */
#define KEY_SLEFT	0611		/* sent by shifted left-arrow */
#define KEY_SMESSAGE	0612		/* sent by shifted message */
#define KEY_SMOVE	0613		/* sent by shifted move key */
#define KEY_SNEXT	0614		/* sent by shifted next key */
#define KEY_SOPTIONS	0615		/* sent by shifted options */
#define KEY_SPREVIOUS	0616		/* sent by shifted prev */
#define KEY_SPRINT	0617		/* sent by shifted print key */
#define KEY_SREDO	0620		/* sent by shifted redo key */
#define KEY_SREPLACE	0621		/* sent by shifted replace */
#define KEY_SRIGHT	0622		/* sent by shifted */
#define KEY_SRSUME	0623		/* sent by shifted resume */
#define KEY_SSAVE	0624		/* sent by save key */
#define KEY_SSUSPEND	0625		/* sent by shifted suspend */
#define KEY_SUNDO	0626		/* sent by shifted undo key */
#define KEY_SUSPEND	0627		/* sent by */
#define KEY_UNDO	0630		/* sent by undo key */
#define KEY_MOUSE	0631		/* mouse event has occured */
#define KEY_BTAB	0632		/* sent by back-tab key */
#define KEY_MAX		0777		/* Maximum curses key */

/* Various video attributes */

#define A_STANDOUT	000000200000L	/* Terminal's best highlighting mode */
#define _STANDOUT	A_STANDOUT	/* for compatability with old curses */
#define A_UNDERLINE	000000400000L	/* Underlining */
#define A_REVERSE	000001000000L	/* Reverse video */
#define A_BLINK		000002000000L	/* Blinking */
#define A_DIM		000004000000L	/* Half bright */
#define A_BOLD		000010000000L	/* Extra bright or bold */
#define A_ALTCHARSET	000100000000L	/* Alternate character set */

/* The next two are subject to change so don't depend on them */
#define A_INVIS		000020000000L
#define A_PROTECT	000040000000L

#define A_NORMAL	000000000000L
#define A_ATTRIBUTES	037777600000L	/* 0xFFFF0000 */
#define A_CHARTEXT	000000177777L	/* 0x0000FFFF */
#define A_COLOR		017600000000L

/* Various video attributes defines for WA_  */

#define WA_STANDOUT	A_STANDOUT	/* Terminal's best highlighting mode */
#define WA_UNDERLINE	A_UNDERLINE	/* Underlining */
#define WA_REVERSE	A_REVERSE	/* Reverse video */
#define WA_BLINK	A_BLINK 	/* Blinking */
#define WA_DIM		A_DIM 		/* Half bright */
#define WA_BOLD		A_BOLD 		/* Extra bright or bold */
#define WA_ALTCHARSET	A_ALTCHARSET	/* Alternate character set */
#define WA_INVIS	A_INVIS
#define WA_PROTECT	A_PROTECT
#define WA_NORMAL	A_NORMAL 

#define WA_HORIZONTAL	000000000001L	/* Horizontal highlight */
#define WA_LEFT		000000000002L	/* Left highlight */
#define WA_LOW		000000000004L	/* Low highlight */
#define WA_RIGHT	000000000010L	/* Right highlight */
#define WA_TOP		000000000020L	/* Top highlight */
#define WA_VERTICAL	000000000040L	/* Vertical highlight */

/* definition of 8 basic color	*/
#define COLOR_BLACK	0
#define COLOR_RED	1
#define COLOR_GREEN	2
#define COLOR_YELLOW	3
#define COLOR_BLUE	4
#define COLOR_MAGENTA	5
#define COLOR_CYAN	6
#define COLOR_WHITE	7

/* mouse related macros: don't change these definitions or bit-masks. */
/* they are interdependent (used by _map_button() in tgetch()	      */
#define BUTTON_RELEASED            0
#define BUTTON_PRESSED             1
#define BUTTON_CLICKED             2
#define BUTTON_DOUBLE_CLICKED      3
#define BUTTON_TRIPLE_CLICKED      4

#define MOUSE_X_POS                (Mouse_status._x)
#define MOUSE_Y_POS                (Mouse_status._y)
#define A_BUTTON_CHANGED           (Mouse_status._changes & 7)
#define MOUSE_MOVED                (Mouse_status._changes & 8)
#define MOUSE_POS_REPORT	   (Mouse_status._changes & 16)
#define BUTTON_CHANGED(x)          (Mouse_status._changes & (1 << ((x) - 1)))
#define BUTTON_STATUS(x)           (Mouse_status._button[(x)-1])

/* definition of mouse bit-masks	*/
#define BUTTON1_RELEASED	000000000001L
#define BUTTON1_PRESSED		000000000002L
#define BUTTON1_CLICKED		000000000004L
#define BUTTON1_DOUBLE_CLICKED	000000000010L
#define BUTTON1_TRIPLE_CLICKED	000000000020L
#define BUTTON2_RELEASED	000000000040L
#define BUTTON2_PRESSED		000000000100L
#define BUTTON2_CLICKED		000000000200L
#define BUTTON2_DOUBLE_CLICKED	000000000400L
#define BUTTON2_TRIPLE_CLICKED	000000001000L
#define BUTTON3_RELEASED	000000002000L
#define BUTTON3_PRESSED		000000004000L
#define BUTTON3_CLICKED		000000010000L
#define BUTTON3_DOUBLE_CLICKED	000000020000L
#define BUTTON3_TRIPLE_CLICKED	000000040000L
#define ALL_MOUSE_EVENTS	000000077777L
#define REPORT_MOUSE_POSITION	000000100000L

#else   /* _BSD */

/*
 * BSD curses
 */

/*
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)curses.h	5.4 (Berkeley) 6/30/88
 */

#include <stdio.h>
#include <sgtty.h>

/* #ifndef _BOOL_IS_BUILTIN */
typedef char   bool;
/* #endif */ /* _BOOL_IS_BUILTIN */

typedef struct sgttyb SGTTY;
typedef int _SHORT;

#define INFINI (-1)
#define reg register

# define	TRUE	1
# define	FALSE	0
# define	ERR	(0)
# define	OK	(1)

# define	_ENDLINE	001
# define	_FULLWIN	002
# define	_SCROLLWIN	004
# define	_FLUSH		010
# define	_FULLLINE	020
# define	_IDLINE		040
# define	_STANDOUT	0200
# define	_NOCHANGE	-1

#define	_puts(s)	tputs(s, 0, _putchar)

/*
 * Capabilities from termcap
 */

extern bool     AM, BS, CA, DA, DB, EO, HC, HZ, IN, MI, MS, NC, NS, OS, UL,
                XB, XN, XT, XS, XX;
extern char     *AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL,
                *DM, *DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6,
                *K7, *K8, *K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL,
                *KR, *KS, *KU, *LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF,
                *SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VS,
                *VE, *AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM,
                *LEFT_PARM, *RIGHT_PARM;
extern char     PC;

extern int _curses_istty;

/*
 * From the tty modes...
 */

extern bool	GT, NONL, UPPERCASE, normtty, _pfast;

struct _bsd_win_st {
	_SHORT		_cury, _curx;
	_SHORT		_maxy, _maxx;
	_SHORT		_begy, _begx;
	_SHORT		_flags;
	_SHORT		_ch_off;
	bool		_clear;
	bool		_leave_;
	bool		_scroll;
	char		**_y;
	_SHORT		*_firstch;
	_SHORT		*_lastch;
	struct _bsd_win_st	*_nextp, *_orig;
};

typedef struct _bsd_win_st BSD_WINDOW;

extern bool	My_term, _echoit, _rawmode, __bsd__endwin;

extern char	*Def_term, ttytype[128];

extern int	LINES, COLS, _tty_ch, _res_flg;

extern SGTTY	_tty;

extern BSD_WINDOW	*bsd_stdscr, *bsd_curscr;

/*
 *	Define VOID to stop lint from generating "null effect"
 * comments.
 */
# ifdef lint
int	__void__;
# define	VOID(x)	(__void__ = (int) (x))
# else
# define	VOID(x)	(x)
# endif

/*
 * defines to hide all the BSD coded functions, etc., from the SYS V 
 * macros keep their names.
 */

#define WINDOW		BSD_WINDOW
#define curscr		bsd_curscr
#define stdscr		bsd_stdscr
#define _win_st		_bsd_win_st
#define _endwin		__bsd__endwin

#define _id_subwins	_bsd_id_subwins
#define _putchar	_bsd_putchar
#define _set_subwin_	_bsd_set_subwin_
#define _sscans		_bsd_sscans
#define _swflags_	_bsd_swflags_

#define box 		_bsd_box
#define delwin 		_bsd_delwin
#define endwin 		_bsd_endwin
#define fgoto		_bsd_fgoto
#define fullname	_bsd_fullname
#define getcap		_bsd_getcap
#define gettmode	_bsd_gettmode
#define idlok		_bsd_idlok
#define initscr 	_bsd_initscr
#define longname 	_bsd_longname
#define mvcur 		_bsd_mvcur
#define mvprintw	_bsd_mvprintw
#define mvscanw		_bsd_mvscanw
#define mvwin		_bsd_mvwin
#define mvwprintw	_bsd_mvwprintw
#define mvwscanw	_bsd_mvwscanw
#define newwin 		_bsd_newwin
#define overlay 	_bsd_overlay
#define overwrite 	_bsd_overwrite
#define plod		_bsd_plod
#define plodput		_bsd_plodput
#define printw 		_bsd_printw
#define scanw 		_bsd_scanw
#define scroll 		_bsd_scroll
#define setterm 	_bsd_setterm
#define subwin 		_bsd_subwin
#define tabcol		_bsd_tabcol
#define touchline	_bsd_touchline
#define touchoverlap	_bsd_touchoverlap
#define touchwin 	_bsd_touchwin
#define tstp		_bsd_tstp
#define waddbytes	_bsd_waddbytes
#define waddch 		_bsd_waddch
#define waddstr 	_bsd_waddstr
#define wclear 		_bsd_wclear
#define wclrtobot 	_bsd_wclrtobot
#define wclrtoeol 	_bsd_wclrtoeol
#define wdelch 		_bsd_wdelch
#define wdeleteln 	_bsd_wdeleteln
#define werase 		_bsd_werase
#define wgetch 		_bsd_wgetch
#define wgetstr 	_bsd_wgetstr
#define winsch 		_bsd_winsch
#define winsertln 	_bsd_winsertln
#define wmove 		_bsd_wmove
#define wprintw 	_bsd_wprintw
#define wrefresh 	_bsd_wrefresh
#define wscanw 		_bsd_wscanw
#define wstandend 	_bsd_wstandend
#define wstandout 	_bsd_wstandout
#define zap		_bsd_zap

/*
 * We must not let BSD programs use the termlib/termcap routines built
 * in to libcurses, so we pull the same trick of redefining all the
 * function calls.  These new routines are incorporated into libcurses,
 * where usualy they have remained seprate in libtermcap.
 * Note: These defines are duplicated in the curses library C modules.
 */

#define tfindent 	_bsd_tfindent
#define tgetent 	_bsd_tgetent
#define tgetflag	_bsd_tgetflag
#define tgetnum		_bsd_tgetnum
#define tgetstr		_bsd_tgetstr
#define tgetwinsize	_bsd_tgetwinsize
#define tnamatch	_bsd_tnamatch
#define tnchktc		_bsd_tnchktc
#define tgoto		_bsd_tgoto
#define tputs		_bsd_tputs

/* Prototypes for things that don't return int. */

extern char   *fullname __((char *, char *));
extern char   *getcap __((const char *));
extern WINDOW *initscr __((void));
extern char   *longname __((const char *, char *));
extern WINDOW *newwin __((int, int, int, int));
extern WINDOW *subwin __((WINDOW *, int, int, int, int));
extern char   *tgetstr __((char *, char **));
extern char   *tgoto __((const char *, int, int));
extern char   *wstandend __((WINDOW *));
extern char   *wstandout __((WINDOW *));

#ifdef __cplusplus

/* Additional prototypes needed for C++. */

extern int	box __((WINDOW*, char, char));
extern int	delwin __((WINDOW *));
extern int	endwin __((void));
extern int	fgoto __((void));
extern int	gettmode __((void));
extern int	idlok __((WINDOW *, bool));
extern int	mvcur __((int, int, int, int));
extern int	mvprintw __((int, int, char *, ...));
extern int	mvscanw __((int, int, char *, ...));
extern int	mvwin __((WINDOW *, int, int));
extern int	mvwprintw __((WINDOW *, int, int, char *, ...));
extern int	mvwscanw __((WINDOW *, int, int, char *, ...));
extern int	overlay __((WINDOW *, WINDOW *));
extern int	overwrite __((WINDOW *, WINDOW *));
extern int	plod __((int));
extern int	plodput __((char));
extern int	printw __((char *, ...));
extern int	scanw __((char *, ...));
extern int	scroll __((WINDOW *));
extern int	setterm __((char *));
extern int	tabcol __((int, int));
extern int	tfindent __((char *, const char *));
extern int	tgetent __((char *, const char *));
extern int	tgetflag __((char *));
extern int	tgetnum __((char *));
extern int	tgetwinsize __((char *));
extern int	tnamatch __((const char *));
extern int	tnchktc __((void));
extern int 	touchline __((WINDOW *, int, int, int));
extern int	touchoverlap __((WINDOW *, WINDOW *));
extern int	touchwin __((WINDOW *));
extern int	tputs __((const char *, int, int (*)(char)));
extern void	tstp __((void));
extern int	waddbytes __((WINDOW *, char*, int));
extern int	waddch __((WINDOW *, char));
extern int	waddstr __((WINDOW *, char *));
extern int	wclear __((WINDOW *));
extern int	wclrtobot __((WINDOW *));
extern int	wclrtoeol __((WINDOW *));
extern int	wdelch __((WINDOW *));
extern int	wdeleteln __((WINDOW *));
extern int	werase __((WINDOW *));
extern int	wgetch __((WINDOW *));
extern int	wgetstr __((WINDOW *, char *));
extern int	winsch __((WINDOW *, char));
extern int	winsertln __((WINDOW *));
extern int	wmove __((WINDOW *, int, int));
extern int	wprintw __((WINDOW *, char *, ...));
extern int	wrefresh __((WINDOW *));
extern int	wscanw __((WINDOW *, char *, ...));
extern int	zap __((void));
#endif /* __cplusplus */

/*
 * psuedo functions for standard screen
 */
# define	addch(ch)	(!_curses_istty ? ERR :VOID(waddch(stdscr, ch)))
# define	getch()		(!_curses_istty ? ERR :VOID(wgetch(stdscr)))
# define	addbytes(da,co)	(!_curses_istty ? ERR :VOID(waddbytes(stdscr, da,co)))
# define	addstr(str)	(!_curses_istty ? ERR :VOID(waddbytes(stdscr, str, strlen(str))))
# define	getstr(str)	(!_curses_istty ? ERR :VOID(wgetstr(stdscr, str)))
# define	move(y, x)	(!_curses_istty ? ERR :VOID(wmove(stdscr, y, x)))
# define	clear()		(!_curses_istty ? ERR :VOID(wclear(stdscr)))
# define	erase()		(!_curses_istty ? ERR :VOID(werase(stdscr)))
# define	clrtobot()	(!_curses_istty ? ERR :VOID(wclrtobot(stdscr)))
# define	clrtoeol()	(!_curses_istty ? ERR :VOID(wclrtoeol(stdscr)))
# define	insertln()	(!_curses_istty ? ERR :VOID(winsertln(stdscr)))
# define	deleteln()	(!_curses_istty ? ERR :VOID(wdeleteln(stdscr)))
# define	refresh()	(!_curses_istty ? ERR :VOID(wrefresh(stdscr)))
# define	inch()		(!_curses_istty ? ERR :VOID(winch(stdscr)))
# define	insch(c)	(!_curses_istty ? ERR :VOID(winsch(stdscr,c)))
# define	delch()		(!_curses_istty ? ERR :VOID(wdelch(stdscr)))
# define	standout()	(!_curses_istty ? ERR :VOID(wstandout(stdscr)))
# define	standend()	(!_curses_istty ? ERR :VOID(wstandend(stdscr)))

/*
 * mv functions
 */
#define	mvwaddch(win,y,x,ch)	VOID(wmove(win,y,x)==ERR?ERR:waddch(win,ch))
#define	mvwgetch(win,y,x)	VOID(wmove(win,y,x)==ERR?ERR:wgetch(win))
#define	mvwaddbytes(win,y,x,da,co) \
		VOID(wmove(win,y,x)==ERR?ERR:waddbytes(win,da,co))
#define	mvwaddstr(win,y,x,str) \
		VOID(wmove(win,y,x)==ERR?ERR:waddbytes(win,str,strlen(str)))
#define mvwgetstr(win,y,x,str)  VOID(wmove(win,y,x)==ERR?ERR:wgetstr(win,str))
#define	mvwinch(win,y,x)	VOID(wmove(win,y,x) == ERR ? ERR : winch(win))
#define	mvwdelch(win,y,x)	VOID(wmove(win,y,x) == ERR ? ERR : wdelch(win))
#define	mvwinsch(win,y,x,c)	VOID(wmove(win,y,x) == ERR ? ERR:winsch(win,c))
#define	mvaddch(y,x,ch)		mvwaddch(stdscr,y,x,ch)
#define	mvgetch(y,x)		mvwgetch(stdscr,y,x)
#define	mvaddbytes(y,x,da,co)	mvwaddbytes(stdscr,y,x,da,co)
#define	mvaddstr(y,x,str)	mvwaddstr(stdscr,y,x,str)
#define mvgetstr(y,x,str)       mvwgetstr(stdscr,y,x,str)
#define	mvinch(y,x)		mvwinch(stdscr,y,x)
#define	mvdelch(y,x)		mvwdelch(stdscr,y,x)
#define	mvinsch(y,x,c)		mvwinsch(stdscr,y,x,c)

/*
 * psuedo functions
 */

#define	clearok(win,bf)	 (win->_clear = bf)
#define	leaveok(win,bf)	 (win->_leave_ = bf)
#define	scrollok(win,bf) (win->_scroll = bf)
#define flushok(win,bf)	 (bf ? (win->_flags |= _FLUSH):(win->_flags &= ~_FLUSH))
#define	getyx(win,y,x)	 y = win->_cury, x = win->_curx
#define	winch(win)	 (win->_y[win->_cury][win->_curx] & 0177)

#define raw()	 (_tty.sg_flags|=RAW, _pfast=_rawmode=TRUE, stty(_tty_ch,&_tty))
#define noraw()	 (_tty.sg_flags&=~RAW,_rawmode=FALSE,_pfast=!(_tty.sg_flags&CRMOD),stty(_tty_ch,&_tty))
#define cbreak() (_tty.sg_flags |= CBREAK, _rawmode = TRUE, stty(_tty_ch,&_tty))
#define nocbreak() (_tty.sg_flags &= ~CBREAK,_rawmode=FALSE,stty(_tty_ch,&_tty))
#define crmode() cbreak()	/* backwards compatability */
#define nocrmode() nocbreak()	/* backwards compatability */
#define echo()	 (_tty.sg_flags |= ECHO, _echoit = TRUE, stty(_tty_ch, &_tty))
#define noecho() (_tty.sg_flags &= ~ECHO, _echoit = FALSE, stty(_tty_ch, &_tty))
#define nl()	 (_tty.sg_flags |= CRMOD,_pfast = _rawmode,stty(_tty_ch, &_tty))
#define nonl()	 (_tty.sg_flags &= ~CRMOD, _pfast = TRUE, stty(_tty_ch, &_tty))
#define	savetty() ((void) gtty(_tty_ch, &_tty), _res_flg = _tty.sg_flags)
#define	resetty() (_tty.sg_flags = _res_flg, (void) stty(_tty_ch, &_tty))

#define	erasechar()	(_tty.sg_erase)
#define	killchar()	(_tty.sg_kill)
#define baudrate()	(_tty.sg_ospeed)

/*
 * Used to be in unctrl.h.
 */

extern char *_unctrl[];
#define unctrl(c)       _unctrl[(c) & 0177]

#endif  /* _BSD */

#ifdef __cplusplus
}
#endif

#endif /* _CURSES_H_ */

