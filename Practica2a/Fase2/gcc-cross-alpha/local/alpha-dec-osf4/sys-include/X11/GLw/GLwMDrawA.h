/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: GLwMDrawA.h,v $
 * Revision 1.1.2.6  1994/04/19  19:31:32  Andy_Vesper
 * 	Fix #if defined so that we don't require /DEFINE=DEC
 * 	for every VMS compile.
 * 	[1994/04/19  19:21:07  Andy_Vesper]
 *
 * Revision 1.1.2.5  1994/01/14  16:46:21  Andy_Vesper
 * 	Don't use <X11/GLw/...> on VMS
 * 	[1994/01/13  21:56:03  Andy_Vesper]
 * 
 * Revision 1.1.2.4  1993/10/06  21:18:34  John_Dennis
 * 	brought source up to SGI release 1.0.11
 * 	[1993/10/06  21:05:33  John_Dennis]
 * 
 * Revision 1.1.2.3  1993/05/20  18:50:48  John_Dennis
 * 	brought source up to SGI release 1.0.9
 * 	[1993/05/20  18:18:03  John_Dennis]
 * 
 * Revision 1.1.2.2  1993/04/07  03:19:39  John_Dennis
 * 	new files in SGI OpenGL 1.0.8 release
 * 	[1993/03/26  21:27:00  John_Dennis]
 * 
 * $EndLog$
 */
#ifndef __GLX_MOTIF
#define __GLX_MOTIF 1
#endif
#if (defined(DEC) || 1) && defined(__vms)
#include "GLwDrawA.h"
#else /* not vms */
#include <X11/GLw/GLwDrawA.h>
#endif /* not vms */
