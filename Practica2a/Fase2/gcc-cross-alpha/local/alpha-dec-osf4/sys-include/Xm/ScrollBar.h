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
 * (c) Copyright 1989, 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
 * Motif Release 1.2
*/ 
/*   $RCSfile: ScrollBar.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:22:54 $ */
/*
*  (c) Copyright 1989, DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS. */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmScrollBar_h
#define _XmScrollBar_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif


#include <Xm/Xm.h>

#ifdef __cplusplus
extern "C" {
#endif


/*  ScrollBar Widget  */

externalref WidgetClass xmScrollBarWidgetClass;

typedef struct _XmScrollBarClassRec * XmScrollBarWidgetClass;
typedef struct _XmScrollBarRec      * XmScrollBarWidget;

/* ifndef for Fast Subclassing  */

#ifndef XmIsScrollBar
#define XmIsScrollBar(w)	XtIsSubclass(w, xmScrollBarWidgetClass)
#endif  /* XmIsScrollBar */


/********    Public Function Declarations    ********/
#ifdef _NO_PROTO

extern Widget XmCreateScrollBar() ;
extern void XmScrollBarGetValues() ;
extern void XmScrollBarSetValues() ;

#else

extern Widget XmCreateScrollBar( 
                        Widget parent,
                        char *name,
                        ArgList arglist,
                        Cardinal argcount) ;
extern void XmScrollBarGetValues( 
                        Widget w,
                        int *value,
                        int *slider_size,
                        int *increment,
                        int *page_increment) ;
extern void XmScrollBarSetValues( 
                        Widget w,
                        int value,
                        int slider_size,
                        int increment,
                        int page_increment,
#if NeedWidePrototypes
                        int notify) ;
#else
                        Boolean notify) ;
#endif /* NeedWidePrototypes */

#endif /* _NO_PROTO */
/********    End Public Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmScrollBar_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */