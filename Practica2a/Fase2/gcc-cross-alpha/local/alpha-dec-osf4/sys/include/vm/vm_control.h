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
 * @(#)$RCSfile: vm_control.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1996/02/08 19:08:27 $
 */
#ifndef __VM_CONTROL__
#define __VM_CONTROL__ 1

/*
 * General level control functions.
 */

typedef enum {
	VMC_INHERITANCE,		/* entry inheritance */
	VMC_KEEP_ON_EXEC,		/* entry keep on exec */
	VMC_MSYNC,			/* msync */
	VMC_SEM_SLEEP,			/* BSD semaphore sleep */
	VMC_SEM_WAKEUP,			/* BSD semaphore wakeup */
	VMC_MADV_DONTNEED		/* madvise MADV_DONTNEED */
}	vm_control_t;	


#endif /* !__VM_CONTROL__ */
