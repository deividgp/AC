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
 * @(#)$RCSfile: Compose.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/05/09 20:37:24 $
 */

/************************************************************
 Copyright (c) 1993 by Silicon Graphics Computer Systems, Inc.

 Permission to use, copy, modify, and distribute this
 software and its documentation for any purpose and without
 fee is hereby granted, provided that the above copyright
 notice appear in all copies and that both that copyright
 notice and this permission notice appear in supporting
 documentation, and that the name of Silicon Graphics not be 
 used in advertising or publicity pertaining to distribution 
 of the software without specific prior written permission.
 Silicon Graphics makes no representation about the suitability 
 of this software for any purpose. It is provided "as is"
 without any express or implied warranty.

 SILICON GRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS 
 SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
 AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SILICON
 GRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
 DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, 
 DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
 OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
 THE USE OR PERFORMANCE OF THIS SOFTWARE.

 ********************************************************/

#ifndef COMPOSE_H
#define	COMPOSE_H 1

typedef	CARD16	ShortKeySym;
#define	COMPOSE_ShortVoidSymbol	0xffff
extern	KeySym			ShortKSToKS( ShortKeySym sym,
						 KeySym *private );
extern	ShortKeySym		KSToShortKS( KeySym sym, KeySym *private,
							    int create );

/***====================================================================***/

typedef struct _ComposeTbl {
	CARD8		 type;
	CARD8		 keycode;
	CARD16		 useFlags;	/* private to Compose.c */
	CARD16		 kindFlags;
	CARD16		 szResultStr;
	KeySym		 introducer;
	KeySym		*privateSyms;
	CARD8		*resultStr;
	KeySym		*ignore;
	char		*name;
	char		*charset;
	void		*next;
	void		*appPriv;	/* for use by App */
} ComposeTbl;


extern	void		 ComposeInitTables(void);

extern	ComposeTbl	*ComposeReadTables(char *path);
extern	ComposeTbl	*ComposeFreeTables(ComposeTbl *);

extern	ComposeTbl	*ComposeGetTables(void);
extern	int		 ComposeUseTables(ComposeTbl*,ComposeTbl**);
extern	int		 ComposeEnableTable(ComposeTbl *,int enable);

/***====================================================================***/

extern	void	*composeStateStart;
extern	void	*composeStateEnd;

#define	ComposeLegalState(p) \
	((!p)||((((void*)(p))>=composeStateStart)&&\
			(((void*)(p))<=composeStateEnd)))
#define	ComposeLegalStatus(p) \
	(((!(p)->compose_ptr)&&((p)->chars_matched==0))\
	 ||(((((void*)(p)->compose_ptr))>=composeStateStart)&&\
			(((void*)(p)->compose_ptr)<=composeStateEnd)))

#define	COMPOSE_MAX_SYMS	30
#define	COMPOSE_SYMS_SIZE	(COMPOSE_MAX_SYMS+1)
#define	COMPOSE_MAX_CHARS	100
#define	COMPOSE_CHARS_SIZE	(COMPOSE_MAX_CHARS+1)

#define	COMPOSE_MAX_PRIVATE	0x0fff

typedef struct _ComposeRtrn {
	ComposeTbl	*tbl;
	KeySym		 matchSym;
	KeySym		 sym[COMPOSE_SYMS_SIZE];
	char		 str[COMPOSE_CHARS_SIZE];
} ComposeRtrn;

	/*
	 * return values for ProcessComposeSym
	 */
#define	COMPOSE_IGNORE	0
#define	COMPOSE_IN_PROGRESS	1
#define	COMPOSE_SUCCEED	2
#define	COMPOSE_FAIL	3

extern	int	IsComposeKey(KeySym sym,int keycode,XComposeStatus *status);
extern	int	ProcessComposeSym(XComposeStatus *status,KeySym sym,
							ComposeRtrn *rtrn);
extern	void	ResetComposeStatus(XComposeStatus *status);
extern	int	GetPreedit(XComposeStatus *status, ComposeRtrn *pRtrn);

#endif /* COMPOSE_H */
