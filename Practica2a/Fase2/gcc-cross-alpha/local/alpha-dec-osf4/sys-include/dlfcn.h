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
 * @(#)$RCSfile: dlfcn.h,v $ $Revision: 1.1.13.2 $ (DEC) $Date: 1994/03/30 21:32:02 $
 */
/*
 * dlfcn.h
 * Interface to dlopen(), dlclose(), dlsym(), dlerror().
 *
 */

/*
 * Values for 'mode' argument in dlopen().
 *
 */
#ifndef _DLFCN_H_
#define _DLFCN_H_

#include <standards.h>

#define RTLD_LAZY		1
#define RTLD_NOW		2

_BEGIN_CPLUSPLUS
extern void	*dlopen __((const char *, int ));
extern void	*dlsym __((void *, const char *));
extern char	*dlerror __((void));
extern int	 dlclose __((void *));
_END_CPLUSPLUS

/*
 * Interface to rld via unsupported __rld_libdl_interface() call.
 *
 */
#define _LIBDL_RLD_DLOPEN	1
#define _LIBDL_RLD_DLCLOSE	2
#define _LIBDL_RLD_DLSYM	3
#define _LIBDL_RLD_DLERROR	4

#endif /* _DLFCN_H_ */
