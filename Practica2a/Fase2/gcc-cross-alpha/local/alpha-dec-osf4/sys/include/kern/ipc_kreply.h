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
#ifndef	_KERN_IPC_KREPLY_
#define	_KERN_IPC_KREPLY_

#include <mach/kern_return.h>
#include <mach/port.h>

/*
 *	Reply port cache is private data.  Define sizes here.
 */

#define REPLY_PORT_CACHE_MAX    8
#define REPLY_PORT_CACHE_EMPTY  0


/*
 *	Functions that manipulate kernel reply ports.
 */

void		kern_init_reply_cache();
port_name_t 	kern_get_reply_port();
void 		kern_release_reply_port();
kern_return_t 	kern_reply_abort();
void		kern_dealloc_reply_port();

#endif	/* _KERN_IPC_KREPLY_ */
