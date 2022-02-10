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
 *	@(#)$RCSfile: kloadcall.h,v $ $Revision: 4.2.11.2 $ (DEC) $Date: 1998/10/05 18:35:39 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _SYS_KLOADCALL_H_
#define _SYS_KLOADCALL_H_
/*
 * Operation Code for kloadcall(2)
 */

#define	KLC_VM_ALLOCATE		1
#define	KLC_VM_DEALLOCATE	2
#define	KLC_VM_READ		3
#define	KLC_VM_WRITE		4
#define	KLC_VM_PROTECT		5
#define	KLC_VM_ALLOCATE_WIRED	6

#define	KLC_CALL_FUNCTION	100

#ifdef __alpha
#define KLC_SET_STATE		101
#define KLC_GET_BOOTLINK_SYMTAB	102
#endif

#endif
