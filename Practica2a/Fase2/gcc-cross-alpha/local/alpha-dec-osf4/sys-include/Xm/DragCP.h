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
 * (c) Copyright 1989, 1990, 1991, 1992, 1993, 1994 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
*/ 
/* 
ifndef OSF_v1_2_4
 * Motif Release 1.2.3
else
 * Motif Release 1.2.4
endif
*/ 
/*   $RCSfile: DragCP.h,v $ $Revision: 1.1.10.2 $ $Date: 1994/09/09 21:08:14 $ */
/*
*  (c) Copyright 1990, 1991, 1992 HEWLETT-PACKARD COMPANY */
#ifndef _XmDragCP_h
#define _XmDragCP_h
#if defined(VMS) || defined (__VMS)
#include <X11/apienvset.h>
#endif

#include <Xm/XmP.h>
#include <Xm/DragC.h>

#include <X11/Shell.h>
#include <X11/ShellP.h>

#include <Xm/DragIcon.h>
#include <Xm/DragOverS.h>
#include <Xm/DropSMgrP.h>

#ifdef __cplusplus
extern "C" {
#endif


/***********************************************************************
 *
 * DragContext (RootWrapper) Widget Private Data
 *
 ***********************************************************************/

#ifdef _NO_PROTO
typedef void	(*XmDragStartProc)();
typedef void 	(*XmDragCancelProc)();
#else
typedef void	(*XmDragStartProc)( XmDragContext, Widget, XEvent *);
typedef void 	(*XmDragCancelProc)( XmDragContext) ;
#endif /* _NO_PROTO */


#define _XmDragStart(dc, srcW, event) \
  (*((XmDragContextClass)XtClass(dc))->drag_class.start)\
  (dc, srcW, event)

#define _XmDragCancel(dc) \
  (*((XmDragContextClass)XtClass(dc))->drag_class.cancel)\
  (dc)

typedef struct {
    XmDragStartProc		start;
    XmDragCancelProc		cancel;
    XtPointer       		extension;
} XmDragContextClassPart;

typedef struct _XmDragContextClassRec {
    CoreClassPart	      	core_class;
    XmDragContextClassPart	drag_class;
} XmDragContextClassRec;

externalref XmDragContextClassRec xmDragContextClassRec;

#define XtDragByPoll 	0
#define XtDragByEvent	1

typedef struct {
    Window		frame;
    Window		window;
    Widget		shell;
    unsigned char	flags;
    unsigned char	dragProtocolStyle;
    int			xOrigin, yOrigin;
    unsigned int	width, height;
    unsigned int	depth;
    XtPointer		iccInfo;
} XmDragReceiverInfoStruct, *XmDragReceiverInfo;


typedef union _XmConvertSelectionRec
  {
    XtConvertSelectionIncrProc sel_incr ;
    XtConvertSelectionProc     sel ;
  } XmConvertSelectionRec ;
  

typedef struct _XmDragContextPart{
    /****  resources ****/

    Atom			*exportTargets;
    Cardinal			numExportTargets;
    XmConvertSelectionRec	convertProc;
    XtPointer			clientData;
    XmDragIconObject		sourceCursorIcon;
    XmDragIconObject		stateCursorIcon;
    XmDragIconObject		operationCursorIcon;
    XmDragIconObject		sourcePixmapIcon;
    Pixel			cursorBackground;
    Pixel			cursorForeground;
    Pixel			validCursorForeground;
    Pixel			invalidCursorForeground;
    Pixel			noneCursorForeground;
    XtCallbackList		dragMotionCallback;
    XtCallbackList		operationChangedCallback;
    XtCallbackList		siteEnterCallback;
    XtCallbackList		siteLeaveCallback;
    XtCallbackList		topLevelEnterCallback;
    XtCallbackList		topLevelLeaveCallback;
    XtCallbackList		dropStartCallback;
    XtCallbackList		dropFinishCallback;
    XtCallbackList		dragDropFinishCallback;
    unsigned char		dragOperations;
    Boolean			incremental;
    unsigned char		blendModel;

    /* private resources */
    Window			srcWindow;
    Time			dragStartTime;
    Atom			iccHandle;
    Widget			sourceWidget;
    Boolean			sourceIsExternal;

    /**** instance data ****/
    Boolean			topWindowsFetched;
    unsigned char 		commType;
    unsigned char		animationType;

    unsigned char		operation;
    unsigned char		operations;
    unsigned int		lastEventState;
    unsigned char		dragCompletionStatus;
    unsigned char		dragDropCompletionStatus;
    Boolean			forceIPC;
    Boolean			serverGrabbed;
    Boolean			useLocal;
    Boolean			inDropSite;
    XtIntervalId 		dragTimerId;
    
    Time			roundOffTime;
    Time			lastChangeTime;
    Time			crossingTime;

    Time			dragFinishTime;
    Time			dropFinishTime;
    
    Atom			dropSelection;
    Widget			srcShell;
	Position		startX, startY;

    XmID			siteID;

    Screen			*currScreen;
    Window			currWmRoot;
    XmDragOverShellWidget	curDragOver;
    XmDragOverShellWidget	origDragOver;

    XmDragReceiverInfoStruct	*currReceiverInfo;
    XmDragReceiverInfoStruct	*rootReceiverInfo;
    XmDragReceiverInfoStruct	*receiverInfos;
    Cardinal			numReceiverInfos;
    Cardinal			maxReceiverInfos;

    unsigned char		trackingMode;
    unsigned char		activeProtocolStyle;
    unsigned char             activeBlendModel;
#ifdef OSF_v1_2_4
    Boolean			dragDropCancelEffect;
#endif /* OSF_v1_2_4 */
} XmDragContextPart;


typedef  struct _XmDragContextRec{
    CorePart	 		core;
    XmDragContextPart		drag;
} XmDragContextRec;

#define _XmDCtoDD(dc) ((XmDisplay)XtParent(dc))


/********    Private Function Declarations    ********/
#ifdef _NO_PROTO

extern XmDragReceiverInfo _XmAllocReceiverInfo() ;
extern unsigned char _XmGetActiveProtocolStyle() ;

#else

extern XmDragReceiverInfo _XmAllocReceiverInfo( 
                        XmDragContext dc) ;
extern unsigned char _XmGetActiveProtocolStyle( 
                        Widget w) ;

#endif /* _NO_PROTO */
/********    End Private Function Declarations    ********/


#ifdef __cplusplus
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#if defined(VMS) || defined (__VMS)
#include <X11/apienvrst.h>
#endif
#endif /* _XmDragCP_h */
