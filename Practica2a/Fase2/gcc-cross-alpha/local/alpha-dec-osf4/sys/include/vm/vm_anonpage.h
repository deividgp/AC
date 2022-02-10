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
 * @(#)$RCSfile: vm_anonpage.h,v $ $Revision: 1.1.5.3 $ (DEC) $Date: 1996/01/30 21:52:54 $
 */
#ifndef	_VM_VM_ANONPAGE_H_
#define	_VM_VM_ANONPAGE_H_

/*
 * This structure describes the swap status of an anonymous page.  Anonymous
 * pages are initially allocated without any swap (swap space will be
 * reserved if requested for user memory), and therfore the swap object will
 * be set to lazy.  pg_anon is set to the corresponding anonymous memory
 * descriptor.  Real swap space is allocated at pageout time and swap object
 * is filled in.  When page is freed after pageout this information is
 * transferred to the corresponding anon.  On pagein, the swap info. is
 * re-established for the new page.
 *
 * Kernel anonymous memory is handled in a slightly different manner.  For a
 * kernel pageable page swap and anonymous memory descriptors are allocated
 * at pageout time and it is moved to the swap object.  Until freed they stay
 * with the swap object.
 *
 * Page ownership is determined by the pg_object field of struct vm_page.
 */
struct vm_anonpage {
	struct vm_swap_object	*ap_sobject;	/* swap object */
	struct vm_anon		*ap_anon;	/* anon that owns swap */
};

#define	pg_sobject	_upg._apg.ap_sobject
#define pg_anon		_upg._apg.ap_anon

#endif	/* !_VM_VM_ANONPAGE_H_ */
