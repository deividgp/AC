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

#pragma	ident	"@(#)$RCSfile: volted.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1995/01/31 20:44:01 $"

/* @(#)src/common/uts/io/vxvm/volted.h	5.5 16 Mar 1993 02:08:24 - Copyright (c) 1993 VERITAS Software Corp. */
/*
 * Copyright(C)1993 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 * 
 *               RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *               VERITAS SOFTWARE
 * 4800 GREAT AMERICA PARKWAY, SANTA CLARA, CA 95054
 */
/*
 * Alpha change log
 *
 * 09-29-93	Wai Yim
 * Merged alpha port with vxvm1.2.1 source.
 *
 */

/*
 * sys/volted.h - volume manager tedel only header file
 */

#ifndef _SYS_VOLTED_H
#define _SYS_VOLTED_H

extern size_t		volkmem;		/* total dynamic memory used */

/*
 * volted_pinfo - one struct per proc slot on the system to track locks.
 * Each list structure is the head of a linked list of spin and sleep
 * locks held by this process thread.  Spinlocks can only be obtained and
 * released in the same process thread.  Sleeplocks can be obtained and then
 * released in different threads.
 * The want_next and want_prev pointers are used to link the pinfo structure
 * onto a list of process elements waiting for a specific lock.  Only one list
 * is necessary since a process thread can only be waiting for one lock at
 * a time.  Once the lock is acquired, the process will be removed from the
 * want list and the acquired lock will be put on the process's list of held
 * locks.
 */
struct volted_pinfo {
	struct volted_pinfo	*vtp_want_next;	/* 0x00 */
	struct volted_pinfo	*vtp_want_prev;	/* 0x04 */
	int			vtp_startpri;	/* 0x08 */
	int			vtp_iodonepri;	/* 0x0c */
	struct volspin		*vtp_spinp;	/* 0x10 */
	int			vtp_nspin;	/* 0x14 */
	struct volsleep		*vtp_sleepp;	/* 0x18 */
	int			vtp_nsleep;	/* 0x1c */
};						/* 0x20 */

extern struct volted_pinfo	*volted_pinfo;
extern struct volspin	volted_spin;
#endif /* _SYS_VOLTED_H */
