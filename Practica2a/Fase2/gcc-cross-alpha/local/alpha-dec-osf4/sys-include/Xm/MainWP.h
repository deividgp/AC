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
/*   $RCSfile: MainWP.h,v $ $Revision: 1.1.12.2 $ $Date: 1994/09/09 21:16:56 $ */
/*
*  (c) Copyright 1987, 1988, 1989, 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmMainWindowP_h
#define _XmMainWindowP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/MainW.h>
#include <Xm/ScrolledWP.h>
#include <Xm/SeparatoG.h>

#ifdef __cplusplus
extern "C" {
#endif


#define DEFAULT_HEIGHT 20
#define DEFAULT_WIDTH 20

/* Constraint part record for MainWindow widget */

typedef struct _XmMainWindowConstraintPart
{
   char unused;
} XmMainWindowConstraintPart, * XmMainWindowConstraint;


/* New fields for the MainWindow widget class record */
typedef struct {
   XtPointer extension;   /* Pointer to extension record */
} XmMainWindowClassPart;

/****************
 *
 * Class record declaration
 *
 ****************/
typedef struct _XmMainWindowClassRec {
    CoreClassPart	core_class;
    CompositeClassPart  composite_class;
    ConstraintClassPart constraint_class;
    XmManagerClassPart  manager_class;
    XmScrolledWindowClassPart	swindow_class;
    XmMainWindowClassPart	mwindow_class;
} XmMainWindowClassRec;

externalref XmMainWindowClassRec xmMainWindowClassRec;

/****************
 *
 * Main Window instance structure.
 *
 ****************/
typedef struct {


   Dimension	AreaWidth,AreaHeight;
   Dimension	margin_width,margin_height;
   Widget       CommandWindow;
   Widget       MenuBar;
   Widget       Message;
   unsigned char CommandLoc;
   XmSeparatorGadget       Sep1,Sep2,Sep3;
   Boolean	ManagingSep;
   Boolean	ShowSep;
   
} XmMainWindowPart;


/************************************************************************
 *									*
 * Full instance record declaration					*
 *									*
 ************************************************************************/

typedef struct _XmMainWindowRec {
    CorePart	    core;
    CompositePart   composite;
    ConstraintPart constraint;
    XmManagerPart   manager;
    XmScrolledWindowPart   swindow;
    XmMainWindowPart   mwindow;
} XmMainWindowRec;


/********    Private Function Declarations    ********/
#ifdef _NO_PROTO


#else


#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmMainWindowP_h */
/* DON'T ADD STUFF AFTER THIS #endif */
