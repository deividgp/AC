/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: glx.h,v $
 * Revision 1.1.3.2  1997/02/17  21:24:22  devbld_mlo
 * 	This is the new version for OpenGL V1.1
 * 	[1997/01/07  19:28:20  Ben_Lipchak]
 *
 * $EndLog$
 */
/*
 * OLD HISTORY from src/xc/include/GL/glx.h
 *
 * Revision 1.1.2.3  1996/10/03  14:58:28  Tony_Yamamoto
 * 	OpenGL V1.1 Port of DEC specific changes
 * 	[1996/10/03  14:57:48  Tony_Yamamoto]
 *
 * Revision 1.1.2.2  1996/06/03  19:45:43  Andy_Vesper
 * 	OpenGL Sample Implementation release 1.1.0
 * 	[1996/06/03  19:37:45  Andy_Vesper]
 * 
 */
#ifndef __GLX_glx_h__
#define __GLX_glx_h__

/*
** Copyright 1991, 1992, Silicon Graphics, Inc.
** All Rights Reserved.
** 
** This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
** the contents of this file may not be disclosed to third parties, copied or
** duplicated in any form, in whole or in part, without the prior written
** permission of Silicon Graphics, Inc.
** 
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
** rights reserved under the Copyright Laws of the United States.
*/

#include <X11/Xlib.h>
#if defined(DEC) || 1
/* AFV 10-Nov-1992: Xutil.h needs caddr_t defined.	     */
/* This is best done in Xresource.h			     */
#include <X11/Xresource.h>
#endif
#include <X11/Xutil.h>
#include <X11/Xmd.h>
#include <GL/gl.h>
#include <GL/glxproto.h>
#include <GL/glxtokens.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
** GLX resources.
*/
typedef XID GLXContextID;
typedef XID GLXPixmap;
typedef XID GLXDrawable;

/*
** GLXContext is a pointer to opaque data.
**/
#if (defined(DEC) || 1) && defined(PEER)
typedef char * OpaquePtr;
typedef OpaquePtr	GLXContext;
#else
typedef struct __glXContextRec *GLXContext;
#endif


#ifdef DEC
/* Routines that Digital does not support must be #if'd out by		     */
/* means of an #if clause that looks exactly like:			     */
/*									     */
/*      #if !defined(DEC)						     */
/*	extern void name (args) ...					     */
/*	#else / * GL_EXT_xxx not supported * /				     */
/*									     */
/*	#endif								     */
/*									     */
/* Any other form will result in bad behavior from the gather tool in	     */
/* extensions/glPeer/tools/gather.c; which always takes the else part of an  */
/* #if clause.								     */

/* START_TABLE_GATHER */
#endif


/************************************************************************/

extern XVisualInfo* glXChooseVisual (Display *dpy, int screen, int *attribList);
extern void glXCopyContext (Display *dpy, GLXContext src, GLXContext dst, unsigned long mask);
extern GLXContext glXCreateContext (Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct);
extern GLXPixmap glXCreateGLXPixmap (Display *dpy, XVisualInfo *vis, Pixmap pixmap);
extern void glXDestroyContext (Display *dpy, GLXContext ctx);
extern void glXDestroyGLXPixmap (Display *dpy, GLXPixmap pix);
extern int glXGetConfig (Display *dpy, XVisualInfo *vis, int attrib, int *value);
extern GLXContext glXGetCurrentContext (void);
extern GLXDrawable glXGetCurrentDrawable (void);
extern Bool glXIsDirect (Display *dpy, GLXContext ctx);
extern Bool glXMakeCurrent (Display *dpy, GLXDrawable drawable, GLXContext ctx);
extern Bool glXQueryExtension (Display *dpy, int *errorBase, int *eventBase);
extern Bool glXQueryVersion (Display *dpy, int *major, int *minor);
extern void glXSwapBuffers (Display *dpy, GLXDrawable drawable);
extern void glXUseXFont (Font font, int first, int count, int listBase);
extern void glXWaitGL (void);
extern void glXWaitX (void);
extern const char * glXGetClientString (Display *dpy, int name );
extern const char * glXQueryServerString (Display *dpy, int screen, int name );
extern const char * glXQueryExtensionsString (Display *dpy, int screen );

#if !defined(DEC)
extern Display *glXGetCurrentDisplayEXT(void);
#else /* GLX_EXT_import_context not supported */

#endif
#if !defined(DEC)
extern GLXDrawable glXGetCurrentDrawableEXT(void);
#else /* GLX_EXT_import_context not supported */

#endif
#if !defined(DEC)
extern GLXContextID glXGetContextIDEXT(const GLXContext ctx);
#else /* GLX_EXT_import_context not supported */

#endif
#if !defined(DEC)
extern GLXContext glXImportContextEXT(Display *dpy, GLXContextID contextID);
#else /* GLX_EXT_import_context not supported */

#endif
#if !defined(DEC)
extern void glXFreeContextEXT(Display *dpy, GLXContext ctx);
#else /* GLX_EXT_import_context not supported */

#endif
#if !defined(DEC)
extern int glXQueryContextInfoEXT(Display *dpy, GLXContext ctx, int attribute, int *value);
#else /* GLX_EXT_import_context not supported */

#endif
#ifdef DEC
/* END_TABLE_GATHER */
#endif


#ifdef __cplusplus
}
#endif

#endif /* !__GLX_glx_h__ */
