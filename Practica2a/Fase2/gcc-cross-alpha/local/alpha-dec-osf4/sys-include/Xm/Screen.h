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
 * (c) Copyright 1989, 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
 * Motif Release 1.2.3
*/ 
/*   $RCSfile: Screen.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:22:27 $ */
/*
*  (c) Copyright 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */

#ifndef _XmScreen_h
#define _XmScreen_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/Xm.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifndef XmIsScreen
#define XmIsScreen(w) (XtIsSubclass(w, xmScreenClass))
#endif /* XmIsScreen */

/* Class record constants */

typedef struct _XmScreenRec *XmScreen;
typedef struct _XmScreenClassRec *XmScreenClass;
externalref 	WidgetClass xmScreenClass;

/********    Public Function Declarations    ********/
#ifdef _NO_PROTO

extern Widget XmGetXmScreen() ;

#else

extern Widget XmGetXmScreen( 
                        Screen *screen) ;
#endif /* _NO_PROTO */
/********    End Public Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmScreen_h */

