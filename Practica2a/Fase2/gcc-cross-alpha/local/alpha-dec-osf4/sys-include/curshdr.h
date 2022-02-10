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
static char rcsid[] = "@(#)$RCSfile: curshdr.h,v $ $Revision: 4.2.13.2 $ (DEC) $Date: 1997/02/24 15:26:56 $";
 */
/*
 * HISTORY
 */
#ifdef IDENT
#ident	"@(#)icurses:screen/include/curshdr.h	1.2"
#endif /* IDENT */

/*
 *      Copyright (c) 1982, 1986, 1988
 *      The Regents of the University of California
 *      All Rights Reserved.
 *      Portions of this document are derived from
 *      software developed by the University of
 *      California, Berkeley, and its contributors.
 */

#ifndef _CURSHDR_H_
#define _CURSHDR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>
#include <stdio.h> /* for FILE */
#include <term.h>
#include <curses.h>
#include <values.h>

typedef struct termios SGTTY;

/*
 * IC and IL overheads and costs should be set to this
 * value if the corresponding feature is missing
 */
#define INFINITY 	500
#define	LARGECOST	500

#define	_NOHASH		(-1)	/* if the hash value is unknown */
#define	_REDRAW		(-2)	/* if line need redrawn */
#define	_BLANK		(-3)	/* if line is blank */
#define	_THASH		(123)	/* base hash if clash with other hashes */
#define	_KEY		(01)
#define	_MACRO		(02)

#define BUFMAX  	1024

#define	_INPUTPENDING	cur_term->_iwait
#define	_PUTS(x, y)	tputs(x, y, _outch)
#define	_VIDS(na, oa)	(vidupdate((na), (oa), _outch), curscr->_attrs = (na))
#define	_ONINSERT()	(_PUTS(enter_insert_mode, 1), SP->phys_irm = TRUE)
#define	_OFFINSERT()	(_PUTS(exit_insert_mode, 1), SP->phys_irm = FALSE)
#define _STRNOTEQ(a, b)	(a == NULL ? (b != NULL) : (b == NULL ? 1 : strcmp(a,b)))

typedef struct
{
    _SHORT       icfixed;                /* Insert char fixed overhead */
    _SHORT       dcfixed;                /* Delete char fixed overhead */
    _SHORT       Insert_character;
    _SHORT       Delete_character;
    _SHORT       Cursor_home;
    _SHORT       Cursor_to_ll;
    _SHORT       Cursor_left;
    _SHORT       Cursor_right;
    _SHORT       Cursor_down;
    _SHORT       Cursor_up;
    _SHORT       Carriage_return;
    _SHORT       Tab;
    _SHORT       Back_tab;
    _SHORT       Clr_eol;
    _SHORT       Clr_bol;
    _SHORT       Parm_ich;
    _SHORT       Parm_dch;
    _SHORT       Parm_left_cursor;
    _SHORT       Parm_up_cursor;
    _SHORT       Parm_down_cursor;
    _SHORT       Parm_right_cursor;
    _SHORT       Cursor_address;
    _SHORT       Row_address;
} COSTS;

#define	_COST(field)	(SP->term_costs.field)

/* Soft label keys */

#define	LABMAX	16	/* max number of labels allowed */
#define	LABLEN	8	/* max length of each label */

typedef	struct
{
    WINDOW	*_win;		/* the window to display labels */
    wchar_t	_ldis[LABMAX][LABLEN+1];/* labels suitable to display */
    char	_lval[LABMAX][LABLEN+1];/* labels' true values */
    wchar_t	_wval[LABMAX][LABLEN+1];/* labels' true wchar_t values */
    short	_labx[LABMAX];	/* where to display labels */
    short	_num;		/* actual number of labels */
    short	_len;		/* real length of labels */
    bool	_changed;	/* TRUE if some labels changed */
    bool	_lch[LABMAX];	/* change status */
} SLK_MAP;

struct	_screen
{
	unsigned    fl_echoit : 1;  /* in software echo mode */
    	unsigned    fl_endwin : 2;  /* has called endwin */
    	unsigned    fl_meta : 1;    /* in meta mode */
    	unsigned    fl_nonl : 1;    /* do not xlate input \r-> \n */
    	unsigned    yesidln : 1;    /* has idln capabilities */
    	unsigned    dmode : 1;      /* Terminal has delete mode */
    	unsigned    imode : 1;      /* Terminal has insert mode */
    	unsigned    ichok : 1;      /* Terminal can insert characters */
    	unsigned    dchok : 1;      /* Terminal can delete characters */
    	unsigned    sid_equal : 1;  /* enter insert and delete mode equal */
    	unsigned    eid_equal : 1;  /* exit insert and delete mode equal */
    	unsigned    phys_irm : 1;   /* in insert mode or not */
    	long	baud;		/* baud rate of this tty */
    	short	kp_state;	/* 1 iff keypad is on, else 0 */
    	short	Yabove;		/* How many lines are above stdscr */
    	short	lsize;		/* How many lines decided by newscreen */
    	short	csize;		/* How many columns decided by newscreen */
    	short	tsize;		/* How big is a tab decided by newscreen */
    	WINDOW	*std_scr;	/* primary output screen */
    	WINDOW	*cur_scr;	/* what's physically on the screen */
    	WINDOW	*virt_scr;	/* what's virtually on the screen */
    	int		*cur_hash;	/* hash table of curscr */
    	int		*virt_hash;	/* hash table of virtscr */
    	TERMINAL	*tcap;		/* TERMINFO info */
    	FILE	*term_file;	/* File to write on for output. */
    	FILE	*input_file;	/* Where to get keyboard input */
    	SLK_MAP	*slk;		/* Soft label information */
    	char	**_mks;		/* marks, only used with xhp terminals */
    	COSTS	term_costs;	/* costs of various capabilities */
    	SGTTY	save_tty_buf;	/* saved state of this tty */
    	char	**_color_mks;	/* marks, only used with color xhp terminals */
    	unsigned long  _trap_mbe;	/* trap these mouse button events    */
    	unsigned long  _map_mbe_to_key;	/* map selected buttons on top of    */
					/* slk's to function keys */
};

extern	SCREEN	*SP;
extern	WINDOW	*_virtscr;

#ifdef	DEBUG
#ifndef	outf
extern	FILE	*outf;
#endif	/* outf */
#endif	/* DEBUG */

/* Declared in newscreen.c */
extern int _curs_mb_max;	/* maximum bytes in an mb char */
extern int _curs_mc_max;	/* maximum columns in multi-column ch */
extern int _curs_zl_max;	/* maximum zero-length characters per column */

/* optimization functions */
#define _WCWIDTH(n) \
	(_curs_mc_max>1?wcwidth(n):1)
#define _MBTOWC(A,B,C) \
	(_curs_mb_max>1?mbtowc(A,(const char *)B,C):(*(A)=(wchar_t)*(B),1))
#define _WCTOMB(A,B) \
	(_curs_mb_max>1?wctomb((char *)A,B):(*(A)=(char)((B)&0x0ff),1))

#define _CCHAR_COPY(A,B,C) \
	(_curs_zl_max>0?\
	(void)memcpy((void*)(A),(void*)(B),(C)*sizeof(cchar_t)):\
	_cchar_copy_nozlc((A),(B),(C)))
#define _CCHAR_SET(A,B,C) \
	(_curs_zl_max>0?_cchar_set((A),(B),(C)):_cchar_set_nozlc((A),(B),(C)))
#define _CCHAR_EQUAL(A,B) \
	(_curs_zl_max>0?_cchar_equal((A),(B)):((A)._a==(B)._a&&(A)._c==(B)._c))

#define SETMCC(__wc)		((__wc)._c = 0)
#define CLRMCC(win, __wc)	((__wc) = (win)->_bkgd)
#define ISMCC(__wc)		((__wc)._c == 0)


/* terminfo magic number */
#define	MAGNUM	0432

/* curses screen dump magic number */
#define	SVR2_DUMP_MAGIC_NUMBER	0433
#define	SVR3_DUMP_MAGIC_NUMBER	0434
#define	DUMP_MAGIC_NUMBER	0435

#define	_BLNKCHAR	' '
#define	_CTRL(c)	(c | 0100)
#define	_ATTR(c)	((attr_t)((c) & A_ATTRIBUTES))
#define	_CHAR(c)	((wchar_t)((c) & A_CHARTEXT))

#define WA_ATTRIBUTES	037777600077L	/* 0xFFFF003F */
#define NEW_WA_ATTRS	000000000077L	/* 0x0000003F */
#define OLD_VID_ATTRS	000177600000L	/* 0x01FF0000 */

#define _ISCTRL(c)	((c) < ' ' || (c) == _CTRL('?'))

#define	_UNCTRL(c)	((c) ^ 0100)

/* blank lines info of curscr */
#define	_BEGNS		curscr->_firstch
#define	_ENDNS		curscr->_lastch

/* hash tables */
#define	_CURHASH	SP->cur_hash
#define _VIRTHASH	SP->virt_hash

/* top/bot line changed */
#define _VIRTTOP	_virtscr->_parx
#define _VIRTBOT	_virtscr->_pary

/* video marks */
#define	_MARKS		SP->_mks
#define	_COLOR_MARKS	SP->_color_mks

#define	_NUMELEMENTS(x)	(sizeof(x)/sizeof(x[0]))

#define	_CHTYPE_TO_OCHTYPE(x)	((_ochtype)((_ATTR(x)>>9)|(x&0177)))
#define	_OCHTYPE_TO_CHTYPE(x)	((chtype) ((x&0177) | ((x&0177600)<<9)))
#define	_ATTR_FROM_OCHTYPE(x)	((attr_t)((((long)(x))&0177600)>>7))
#define	_CHAR_FROM_OCHTYPE(x)	((wchar_t)(((long)(x))&0177))

#define _CCHAR_INIT(W,C,A)	((W)._c = (C), (W)._a = (A), (W)._z[0] = 0)

#define _CCHAR_ISBLANK(ch) \
	(_curs_zl_max>0?(((ch)._c==_BLNKCHAR)&&((ch)._z[0]==0)&&((ch)._a==0)):\
	(((ch)._c==_BLNKCHAR) && ((ch)._a==0)))

#define _CCHAR_TO_BLANK(ch) \
	_CCHAR_INIT(ch, _BLNKCHAR, 0)

#define _OCHTYPE_TO_CCHAR(ch,wch) \
	_CCHAR_INIT(wch, _CHAR_FROM_OCHTYPE(ch),_ATTR_FROM_OCHTYPE(ch))

#define _CHTYPE_TO_CCHAR(C,W) \
	_CCHAR_INIT(W, _CHAR(C), _ATTR(C))

#define _CCHAR_TO_CHTYPE(W) \
	((chtype)(_ATTR((W)._a)|_CHAR((W)._c)))

#define _CCHAR_ISNULL(wch) \
	((_curs_zl_max>0)?(wch->_c == 0 && wch->_z[0] ==0):(wch->_c == 0))

#ifdef _WCHAR16
#define _CCHAR_TO_PCODE(W)	_CCHAR_TO_CHTYPE(W)
#define _PCODE_TO_CCHAR(C,W)	_CHTYPE_TO_CCHAR(C,W)
#else
#define _CCHAR_TO_PCODE(W)	((chtype)(W)._c)
#define _PCODE_TO_CCHAR(C,W)	_CCHAR_INIT(W, _CHAR(C), _ATTR(C))
#endif

/* functions for screen updates */
extern	int	(*_setidln)(int, int), 
		(*_useidln)(void);

/* min/max functions */
#define	_MIN(a, b)	((a) < (b) ? (a) : (b))
#define	_MAX(a, b)	((a) > (b) ? (a) : (b))

extern	int	(*_do_slk_ref)(), (*_do_slk_tch)(), (*_do_slk_noref)();
extern	void	(*_slk_init)(), (*_rip_init)();

/* Mouse status */

struct _Mouse {
	int _x, _y;
	_SHORT _button[3];
	int    _changes;
};

typedef struct _Mouse	MOUSE_STATUS;

extern MOUSE_STATUS	Mouse_status;

/* Defines and catalog names for error messages */

#define CURS_STUPID             1
#define CURS_UNKNOWN            2
#define CURS_BAD_MALLOC         3
#define CURS_DBG_BAD_MALLOC     4

#define CURSES_MSGCAT           "curses.cat"
#define CURS_ERR_SET            1

extern  _SHORT  curs_errno;
extern	short	term_errno;
extern	char     curs_parm_err[], term_parm_err[];
extern  int     TABSIZE;
extern  char    ttytype[];

#ifdef __cplusplus
}
#endif

#endif /* _CURSHDR_H_ */
