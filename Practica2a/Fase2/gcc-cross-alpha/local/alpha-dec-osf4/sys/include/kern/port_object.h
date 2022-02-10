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
 *	@(#)$RCSfile: port_object.h,v $ $Revision: 4.2.7.3 $ (DEC) $Date: 1994/09/12 13:41:49 $
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
/*
 * Port "kernel object" declarations
 */

#ifndef	_KERN_PORT_OBJECT_H_
#define _KERN_PORT_OBJECT_H_

#include <mach_km.h>

typedef	enum {
		PORT_OBJECT_NONE,
		PORT_OBJECT_TASK,
		PORT_OBJECT_THREAD,
		PORT_OBJECT_PAGING_REQUEST,
		PORT_OBJECT_PAGER,
		PORT_OBJECT_HOST,
		PORT_OBJECT_HOST_PRIV,
		PORT_OBJECT_PROCESSOR,
		PORT_OBJECT_PSET,
		PORT_OBJECT_PSET_NAME,
		PORT_OBJECT_PAGER_TERMINATING,
		PORT_OBJECT_PROCESSOR_NAME
#if	MACH_KM
		,PORT_OBJECT_MONITOR
#endif	/*MACH_KM*/
} port_object_type_t;

typedef struct {
		port_object_type_t kp_type;
		void *kp_object;
} port_object_t;

#define port_object_type(port)	((port)->port_object.kp_type)
#define port_object_get(port)	((port)->port_object.kp_object)
#define port_object_set(port, type, object) \
				(port)->port_object.kp_type = (type), \
				(port)->port_object.kp_object = (object)

#define ipc_kobject_vm_page_list(p) \
			(port_object_type((p)) == PORT_OBJECT_PAGING_REQUEST)

#define ipc_kobject_vm_page_steal(p) \
			(port_object_type((p)) == PORT_OBJECT_PAGING_REQUEST)

#endif	/*_KERN_PORT_OBJECT_H_*/
