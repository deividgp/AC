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
 * @(#)$RCSfile: atm_osf.h,v $ $Revision: 1.1.12.2 $ (DEC) $Date: 1998/09/25 19:39:07 $
 */

#ifndef _ATM_ATM_OSF_H_
#define _ATM_ATM_OSF_H_

/* OSF/1 kernel include files required by modules */
#include "sys/param.h"
#include "sys/cred.h"
#include "sys/time.h"
#include "sys/kernel.h"
#include "sys/ioctl.h"
#include "sys/errno.h"
#ifdef _KERNEL
#include "kern/thread.h"
#endif
#include "sys/mbuf.h"

/* Operating system dependent definitions for DEC OSF/1 */

/* locking prematives */

#ifdef KERNEL
#define atm_lock_info(class,name)	udecl_simple_lock_info(class, (name))
#define atm_lock_decl(name)	udecl_simple_lock_data(, (name))
#define atm_lock_init(L)	usimple_lock_init((L))
#define atm_lock(L)		usimple_lock((L))
#define atm_unlock(L)		usimple_unlock((L))
#define atm_lock_try(L)		usimple_lock_try((L))
#define atm_lock_setup(L,I)	usimple_lock_setup((L),(I))
#define atm_lock_terminate(L)	usimple_lock_terminate((L))
#define atm_lock_addr(L)	usimple_lock_addr((L))

#ifdef ATM_MALLOC_DEBUG
void *atm_malloc(int,char *,int,int);
void atm_free(void *,char *,int);
#define ATM_MALLOC(P,C,S)   	(P) = (C)atm_malloc((S),__FILE__,__LINE__,\
						    (M_NOWAIT|M_ZERO))
#define ATM_MALLOCW(P,C,S)   	(P) = (C)atm_malloc((S),__FILE__,__LINE__,\
						    (M_WAITOK|M_ZERO))
#define ATM_MALLOC_VAR(P,C,S)	(P) = (C)atm_malloc((S),__FILE__,__LINE__,\
						    (M_NOWAIT|M_ZERO))
#define ATM_MALLOCW_VAR(P,C,S)	(P) = (C)atm_malloc((S),__FILE__,__LINE__,\
						    (M_WAITOK|M_ZERO))
#define ATM_FREE(P)		atm_free((void *)(P),__FILE__,__LINE__),\
					(P) = NULL
#else
#define ATM_MALLOC(P,C,S)   	MALLOC((P),C,(S),M_ATMMEM,(M_NOWAIT|M_ZERO))
#define ATM_MALLOCW(P,C,S)	MALLOC((P),C,(S),M_ATMMEM,(M_WAITOK|M_ZERO))
#define ATM_MALLOC_VAR(P,C,S)  	MALLOC_VAR((P),C,(S),M_ATMMEM,\
					   (M_NOWAIT|M_ZERO))
#define ATM_MALLOCW_VAR(P,C,S)	MALLOC_VAR((P),C,(S),M_ATMMEM,\
					   (M_WAITOK|M_ZERO))
#define ATM_FREE(P)		if((P)) FREE((P),M_ATMMEM), (P) = NULL
#endif	/* ATM_MALLOC_DEBUG */

#endif	/* KERNEL */

#endif /* _ATM_ATM_OSF_H_ */
