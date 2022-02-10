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
/* $XConsortium: Xresource.h,v 1.37 94/04/17 20:21:52 rws Exp $ */

/***********************************************************

Copyright (c) 1987, 1988  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.


Copyright 1987, 1988 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef _XRESOURCE_H_
#define _XRESOURCE_H_

/* You must include <X11/Xlib.h> before including this file */

/****************************************************************
 ****************************************************************
 ***                                                          ***
 ***                                                          ***
 ***          X Resource Manager Intrinsics                   ***
 ***                                                          ***
 ***                                                          ***
 ****************************************************************
 ****************************************************************/

_XFUNCPROTOBEGIN

/****************************************************************
 *
 * Memory Management
 *
 ****************************************************************/

extern char *Xpermalloc(
#if NeedFunctionPrototypes
    unsigned int	/* size */
#endif
);

/****************************************************************
 *
 * Quark Management
 *
 ****************************************************************/

#ifndef NO_DEC_BINARY_COMPATIBILITY
/* for R5 compatibility */
typedef long     XrmQuark, *XrmQuarkList;
#else
typedef int     XrmQuark, *XrmQuarkList;
#endif
#define NULLQUARK ((XrmQuark) 0)

typedef char *XrmString;
#define NULLSTRING ((XrmString) 0)

/* find quark for string, create new quark if none already exists */
extern XrmQuark XrmStringToQuark(
#if NeedFunctionPrototypes
    _Xconst char* 	/* string */
#endif
);

extern XrmQuark XrmPermStringToQuark(
#if NeedFunctionPrototypes
    _Xconst char* 	/* string */
#endif
);

/* find string for quark */
extern XrmString XrmQuarkToString(
#if NeedFunctionPrototypes
    XrmQuark 		/* quark */
#endif
);

extern XrmQuark XrmUniqueQuark(
#if NeedFunctionPrototypes
    void
#endif
);

#define XrmStringsEqual(a1, a2) (strcmp(a1, a2) == 0)


/****************************************************************
 *
 * Conversion of Strings to Lists
 *
 ****************************************************************/

typedef enum {XrmBindTightly, XrmBindLoosely} XrmBinding, *XrmBindingList;

extern void XrmStringToQuarkList(
#if NeedFunctionPrototypes
    _Xconst char*	/* string */,
    XrmQuarkList	/* quarks_return */
#endif
);

extern void XrmStringToBindingQuarkList(
#if NeedFunctionPrototypes
    _Xconst char*	/* string */,
    XrmBindingList	/* bindings_return */,
    XrmQuarkList	/* quarks_return */
#endif
);

/****************************************************************
 *
 * Name and Class lists.
 *
 ****************************************************************/

typedef XrmQuark     XrmName;
typedef XrmQuarkList XrmNameList;
#define XrmNameToString(name)		XrmQuarkToString(name)
#define XrmStringToName(string)		XrmStringToQuark(string)
#define XrmStringToNameList(str, name)	XrmStringToQuarkList(str, name)

typedef XrmQuark     XrmClass;
typedef XrmQuarkList XrmClassList;
#define XrmClassToString(c_class)	XrmQuarkToString(c_class)
#define XrmStringToClass(c_class)	XrmStringToQuark(c_class)
#define XrmStringToClassList(str,c_class) XrmStringToQuarkList(str, c_class)



/****************************************************************
 *
 * Resource Representation Types and Values
 *
 ****************************************************************/

typedef XrmQuark     XrmRepresentation;
#define XrmStringToRepresentation(string)   XrmStringToQuark(string)
#define	XrmRepresentationToString(type)   XrmQuarkToString(type)

typedef struct {
    unsigned int    size;
    XPointer	    addr;
} XrmValue, *XrmValuePtr;


/****************************************************************
 *
 * Resource Manager Functions
 *
 ****************************************************************/

typedef struct _XrmHashBucketRec *XrmHashBucket;
typedef XrmHashBucket *XrmHashTable;
typedef XrmHashTable XrmSearchList[];
typedef struct _XrmHashBucketRec *XrmDatabase;


extern void XrmDestroyDatabase(
#if NeedFunctionPrototypes
    XrmDatabase		/* database */    
#endif
);

extern void XrmQPutResource(
#if NeedFunctionPrototypes
    XrmDatabase*	/* database */,
    XrmBindingList	/* bindings */,
    XrmQuarkList	/* quarks */,
    XrmRepresentation	/* type */,
    XrmValue*		/* value */
#endif
);

extern void XrmPutResource(
#if NeedFunctionPrototypes
    XrmDatabase*	/* database */,
    _Xconst char*	/* specifier */,
    _Xconst char*	/* type */,
    XrmValue*		/* value */
#endif
);

extern void XrmQPutStringResource(
#if NeedFunctionPrototypes
    XrmDatabase*	/* database */,
    XrmBindingList      /* bindings */,
    XrmQuarkList	/* quarks */,
    _Xconst char*	/* value */
#endif
);

extern void XrmPutStringResource(
#if NeedFunctionPrototypes
    XrmDatabase*	/* database */,
    _Xconst char*	/* specifier */,
    _Xconst char*	/* value */
#endif
);

extern void XrmPutLineResource(
#if NeedFunctionPrototypes
    XrmDatabase*	/* database */,
    _Xconst char*	/* line */
#endif
);

extern  XrmQGetResource(
#if NeedFunctionPrototypes
    XrmDatabase		/* database */,
    XrmNameList		/* quark_name */,
    XrmClassList	/* quark_class */,
    XrmRepresentation*	/* quark_type_return */,
    XrmValue*		/* value_return */
#endif
);

extern Bool XrmGetResource(
#if NeedFunctionPrototypes
    XrmDatabase		/* database */,
    _Xconst char*	/* str_name */,
    _Xconst char*	/* str_class */,
    char**		/* str_type_return */,
    XrmValue*		/* value_return */
#endif
);

extern Bool XrmQGetSearchList(
#if NeedFunctionPrototypes
    XrmDatabase		/* database */,
    XrmNameList		/* names */,
    XrmClassList	/* classes */,
    XrmSearchList	/* list_return */,
    int			/* list_length */
#endif
);

extern Bool XrmQGetSearchResource(
#if NeedFunctionPrototypes
    XrmSearchList	/* list */,
    XrmName		/* name */,
    XrmClass		/* class */,
    XrmRepresentation*	/* type_return */,
    XrmValue*		/* value_return */
#endif
);

/****************************************************************
 *
 * Resource Database Management
 *
 ****************************************************************/

extern void XrmSetDatabase(
#if NeedFunctionPrototypes
    Display*		/* display */,
    XrmDatabase		/* database */
#endif
);

extern XrmDatabase XrmGetDatabase(
#if NeedFunctionPrototypes
    Display*		/* display */
#endif
);

extern XrmDatabase XrmGetFileDatabase(
#if NeedFunctionPrototypes
    _Xconst char*	/* filename */
#endif
);

extern Status XrmCombineFileDatabase(
#if NeedFunctionPrototypes
    _Xconst char* 	/* filename */,
    XrmDatabase*	/* target */,
    Bool		/* override */
#endif
);

extern XrmDatabase XrmGetStringDatabase(
#if NeedFunctionPrototypes
    _Xconst char*	/* data */  /*  null terminated string */
#endif
);

extern void XrmPutFileDatabase(
#if NeedFunctionPrototypes
    XrmDatabase		/* database */,
    _Xconst char*	/* filename */
#endif
);

extern void XrmMergeDatabases(
#if NeedFunctionPrototypes
    XrmDatabase		/* source_db */,
    XrmDatabase*	/* target_db */
#endif
);

extern void XrmCombineDatabase(
#if NeedFunctionPrototypes
    XrmDatabase		/* source_db */,
    XrmDatabase*	/* target_db */,
    Bool		/* override */
#endif
);

#define XrmEnumAllLevels 0
#define XrmEnumOneLevel  1

extern Bool XrmEnumerateDatabase(
#if NeedFunctionPrototypes
    XrmDatabase		/* db */,
    XrmNameList		/* name_prefix */,
    XrmClassList	/* class_prefix */,
    int			/* mode */,
    Bool (*)(
#if NeedNestedPrototypes
	     XrmDatabase*	/* db */,
	     XrmBindingList	/* bindings */,
	     XrmQuarkList	/* quarks */,
	     XrmRepresentation*	/* type */,
	     XrmValue*		/* value */,
	     XPointer		/* closure */
#endif
	     )		/* proc */,
    XPointer		/* closure */
#endif
);

extern char *XrmLocaleOfDatabase(
#if NeedFunctionPrototypes
    XrmDatabase 	/* database */
#endif
);


/****************************************************************
 *
 * Command line option mapping to resource entries
 *
 ****************************************************************/

typedef enum {
    XrmoptionNoArg,	/* Value is specified in OptionDescRec.value	    */
    XrmoptionIsArg,     /* Value is the option string itself		    */
    XrmoptionStickyArg, /* Value is characters immediately following option */
    XrmoptionSepArg,    /* Value is next argument in argv		    */
    XrmoptionResArg,	/* Resource and value in next argument in argv      */
    XrmoptionSkipArg,   /* Ignore this option and the next argument in argv */
    XrmoptionSkipLine,  /* Ignore this option and the rest of argv	    */
    XrmoptionSkipNArgs	/* Ignore this option and the next 
			   OptionDescRes.value arguments in argv */
} XrmOptionKind;

typedef struct {
    char	    *option;	    /* Option abbreviation in argv	    */
    char	    *specifier;     /* Resource specifier		    */
    XrmOptionKind   argKind;	    /* Which style of option it is	    */
    XPointer	    value;	    /* Value to provide if XrmoptionNoArg   */
} XrmOptionDescRec, *XrmOptionDescList;


extern void XrmParseCommand(
#if NeedFunctionPrototypes
    XrmDatabase*	/* database */,
    XrmOptionDescList	/* table */,
    int			/* table_count */,
    _Xconst char*	/* name */,
    int*		/* argc_in_out */,
    char**		/* argv_in_out */		     
#endif
);

_XFUNCPROTOEND

#endif /* _XRESOURCE_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */
