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
/*** ColorObj.h ***/

#ifndef _ColorObj_h
#define _ColorObj_h

#include <Xm/Xm.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#ifdef DEC_MOTIF_BUG_FIX
externalref WidgetClass  _xmColorObjClass;
#else
extern WidgetClass  _xmColorObjClass;
#endif

typedef struct _ColorObjClassRec *ColorObjClass;
typedef struct _ColorObjRec      *ColorObj;

#define XmNprimaryColorSetId          "primaryColorSetId"
#define XmCPrimaryColorSetId          "PrimaryColorSetId"
#define XmNsecondaryColorSetId        "secondaryColorSetId"
#define XmCSecondaryColorSetId        "SecondaryColorSetId"
#define XmNactiveColorSetId           "activeColorSetId"
#define XmCActiveColorSetId           "ActiveColorSetId"
#define XmNinactiveColorSetId         "inactiveColorSetId"
#define XmCInactiveColorSetId         "InactiveColorSetId"
#define XmNuseColorObj                "useColorObj"
#define XmCUseColorObj                "UseColorObj"

#define XmNtextColorSetId             "textColorSetId"
#define XmCTextColorSetId             "TextColorSetId"
#define XmNuseTextColor               "useTextColor"
#define XmCUseTextColor               "UseTextColor"
#define XmNuseTextColorForList        "useTextColorForList"
#define XmCUseTextColorForList        "UseTextColorForList"

#define XmNuseMask		"useMask"
#define XmCUseMask		"UseMask"
#define XmNuseMultiColorIcons	"useMultiColorIcons"
#define XmCUseMultiColorIcons	"UseMultiColorIcons"

/** misc structures, defines, and functions for using ColorObj **/

typedef struct {
    Pixel fg;
    Pixel bg;
    Pixel ts;
    Pixel bs;
    Pixel sc;
} PixelSet;

#define  DitherTopShadow(display, screen, pixelSet) \
                        ((pixelSet)->bs == BlackPixel((display), (screen)))

#define  DitherBottomShadow(display, screen, pixelSet) \
                        ((pixelSet)->ts == WhitePixel((display), (screen)))

#define  DITHER     "50_foreground"
#define  NO_DITHER  "unspecified_pixmap"

/* defines for color usage */
#define B_W           0
#define LOW_COLOR     1
#define MEDIUM_COLOR  2
#define HIGH_COLOR    3

#define COLOR_SRV_NAME "ColorServer"

/* defines for palette.c */
#define VALUE_THRESHOLD 225

/* defines for Atom strings */
#define PIXEL_SET        "Pixel Sets"
#define PALETTE_NAME     "DefaultPalette Name"
#define TYPE_OF_MONITOR  "Type Of Monitor"
#define UPDATE_FILE      "Update Default File"
#define CUST_DATA        "Customize Data:"

#define  MAX_NUM_COLORS  8
#define  NUM_COLORS  MAX_NUM_COLORS

#if defined(__cplusplus) || defined(c_plusplus)
}  /* Close scope of 'extern "C"' declaration which encloses file. */
#endif

#endif /* _ColorObj_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
