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
#ifndef lint
static char	*sccsid = "@(#)$RCSfile: llib-lcrses.c,v $ $Revision: 4.2.4.3 $ (DEC) $Date: 1995/12/19 20:09:23 $";
#endif 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * COMPONENT_NAME: (CMDPROG) Programming Utilities
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27; 10
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*LINTLIBRARY*/

#define __CURSES__
#define _OSF_SOURCE

#include        <curses.h>

/*LINTSTDLIB_curses.h*/
/*LINTSTDLIB_termios.h*/
/*LINTSTDLIB_unctrl.h*/

/********  external variables ***********/

bool            AM, BS, CA, DA, DB, EO, HC, HZ, IN, MI, MS, NC, NS, OS, UL,
                XB, XN, XT, XS, XX;
char            *AL, *BC, *BT, *CD, *CE, *CL, *CM, *CR, *CS, *DC, *DL,
                *DM, *DO, *ED, *EI, *K0, *K1, *K2, *K3, *K4, *K5, *K6,
                *K7, *K8, *K9, *HO, *IC, *IM, *IP, *KD, *KE, *KH, *KL,
                *KR, *KS, *KU, *LL, *MA, *ND, *NL, *RC, *SC, *SE, *SF,
                *SO, *SR, *TA, *TE, *TI, *UC, *UE, *UP, *US, *VB, *VS,
                *VE, *AL_PARM, *DL_PARM, *UP_PARM, *DOWN_PARM,
                *LEFT_PARM, *RIGHT_PARM;
char     PC;


int      LINES, COLS, COLORS, COLOR_PAIRS;

WINDOW   *stdscr, *curscr;

cchar_t *_wacs_map;

char     *_unctrl[1];
/****************  bsd externals *************/


int _curses_istty;

bool     GT, NONL, UPPERCASE, normtty, _pfast;

bool     My_term, _echoit, _rawmode, __bsd__endwin;

char     *Def_term, ttytype[128];

chtype   _acs_map[1];

char     *curs_err_strings[1];

int      _tty_ch, _res_flg;


