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
 *	@(#)$RCSfile: ipc_kmesg.h,v $ $Revision: 4.2.12.2 $ (DEC) $Date: 1998/04/15 18:20:57 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */

#ifndef	_KERN_IPC_KMESG_H_
#define _KERN_IPC_KMESG_H_

#include <mach/boolean.h>
#include <mach/message.h>
#include <mach_debug/ipc_statistics.h>
#include <kern/task.h>
#include <kern/kern_msg.h>
#include <kern/ipc_globals.h>
#include <kern/ipc_copyout.h>
#include <kern/kern_port.h>
#include <kern/macro_help.h>
#include <sys/malloc.h>

/*
 *	Kernel message allocation
 *
 *	The IPC system allocates messages in one of two sizes: small or large.
 *	Other kernel subsystems may allocate messages on their own.
 *
 *	The internal allocation routines are noticably macros: their
 *	argument is the by-reference result of the allocation.
 *
 *	To destroy a message involves deallocating the resources
 *	associated with it; this is the normal case.
 */

#define kern_msg_allocate(kmsg, msg_size)			\
MACRO_BEGIN							\
	u_long	size = (msg_size) + sizeof(struct kern_msg) - 	\
					sizeof(msg_header_t);	\
	MALLOC_VAR((kmsg), kern_msg_t, size, M_MIPC, M_WAITOK);	\
	(kmsg)->kernel_message = FALSE;				\
	ipc_event(current); 					\
MACRO_END

#define kern_msg_free(kmsg)				\
MACRO_BEGIN						\
	FREE((kmsg), M_MIPC);				\
	ipc_event_count(current, -1);			\
MACRO_END

#define kern_msg_destroy(kmsgptr)					     \
MACRO_BEGIN							     	     \
	if ((kmsgptr)->kmsg_header.msg_simple) {			     \
		register kern_port_t port;				     \
									     \
		port = (kern_port_t) (kmsgptr)->kmsg_header.msg_remote_port; \
		if (port != KERN_PORT_NULL)				     \
			port_release(port);				     \
									     \
		port = (kern_port_t) (kmsgptr)->kmsg_header.msg_local_port;  \
		if (port != KERN_PORT_NULL)				     \
			port_release(port);				     \
									     \
		kern_msg_free(kmsgptr); 				     \
	} else 								     \
		msg_destroy(kmsgptr);					     \
MACRO_END

#endif	/*_KERN_IPC_KMESG_H_*/
