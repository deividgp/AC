/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: glxmd.h,v $
 * Revision 1.1.3.2  1997/02/17  21:24:17  devbld_mlo
 * 	This is the new version for OpenGL V1.1
 * 	[1997/01/07  19:28:24  Ben_Lipchak]
 *
 * $EndLog$
 */
/*
 * OLD HISTORY
 * Revision 1.1.2.2  1996/06/03  19:45:51  Andy_Vesper
 * 	OpenGL Sample Implementation release 1.1.0
 * 	[1996/06/03  19:37:53  Andy_Vesper]
 *
 */
#ifndef _GLX_glxmd_h_
#define _GLX_glxmd_h_

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

/*
** Machine dependent declarations.
*/

/*
** Define floating point wire types.  These are in IEEE format on the wire.
*/
typedef float FLOAT32;
typedef double FLOAT64;

/*
** Like B32, but this is used to store floats in a request.
**
** NOTE: Machines that have a native 32-bit IEEE float can define this as 
**       nothing.  Machines that don't might mimic the float with an integer,
**       and then define this to :32.
*/
#define F32

#endif /* _GLX_glxmd_h_ */
