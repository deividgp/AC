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
 * @(#)$RCSfile: ComposeInt.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/05/09 20:37:29 $
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

#ifndef COMPOSE_INT_H
#define	COMPOSE_INT_H 1

#include <X11/Compose.h>

	/*
	 * values for useFlags in ComposeTbl
	 */
#define	COMPOSE_CAN_FREE	(1<<0)
#define	COMPOSE_INACTIVE	(1<<1)

/***====================================================================***/

typedef struct {
	int	(*proc)(XComposeStatus *,KeySym,ComposeRtrn *);
	XComposeStatus	*sanity;
	ComposeTbl	*table;
	void	 	*state;
} ComposeState;

/***====================================================================***/

#define	COMPOSE_TREE	1
#define	COMPOSE_TREE_SHORTCUT	2
#define	COMPOSE_STRING	3

#define	NEXT_IS_UNDEFINED 'U'
#define	NEXT_IS_NODE	'N'
#define	NEXT_IS_RESULT	'R'

typedef struct _ComposeTreeNode {
	CARD16		 back;
	ShortKeySym	 sym;
	CARD16		 str;
	ShortKeySym	*nextSym;
	CARD32		*next;
	char		*what;
} ComposeTreeNode;

typedef struct _ComposeTree {
	ComposeTbl	 common;
	ComposeTreeNode	*node;
	int		 nNodes;
} ComposeTree;

extern	int		 CTGetNodeResult(ComposeTreeNode *pNode,
						int ndx,KeySym *sym,void *str);
extern	int		 CTSetNodeResult(ComposeTreeNode *pNode,
						int ndx,KeySym sym,void *str);

#define	CTResultSym(i,n,x)	(ShortKSToKS((n)->next[x]&0xffff,\
						(i)->common.privateSyms))
#define	CTResultStr(i,n,x)	(&(i)->common.resultStr[((n)->next[x]>>16)&0xffff])

#define	CTNextIndex(n,x)	((n)->next[x]&0xffff)
#define	CTNodeNext(i,n,x)	(&(i)->node[(n)->next[x]&0xffff])
#define	CTNode(i,n)		(&(i)->node[n])
#define	CTNodeIndex(i,n)	((n)-(i)->node)

typedef struct _ComposeTreeShortcut {
	ComposeTbl	 common;
	ComposeTree	*tbl;
	ComposeTreeNode	*node;
} ComposeTreeShortcut;

typedef struct _ComposeStringTbl {
	ComposeTbl	  common;
	int			  maxLen;
	int			  nSequence;
	ShortKeySym		**sequence;
	CARD32			 *yields;
	KeySym		 	 *terminators;
} ComposeStringTbl;

#endif /* COMPOSE_INT_H */
