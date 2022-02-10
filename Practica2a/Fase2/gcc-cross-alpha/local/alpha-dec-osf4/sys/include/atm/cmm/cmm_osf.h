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
 * @(#)$RCSfile: cmm_osf.h,v $ $Revision: 1.1.12.2 $ (DEC) $Date: 1998/09/25 19:38:44 $
 */

#include "sys/param.h"
#include "sys/time.h"
#include "sys/kernel.h"
#include "sys/ioctl.h"
#include "sys/errno.h"
#include "machine/cpu.h"

#include "sys/mbuf.h"


/* Operating system dependent definitions for DEC OSF/1 */

#define atm_cmm_lock_info(class,name)       atm_lock_info(class, (name))
#define atm_cmm_lock_decl(name)     	    atm_lock_decl(name)
#define atm_cmm_lock_init(L)        	    atm_lock_init((L))
#define atm_cmm_lock(oldpri,L)              oldpri = splimp(), atm_lock((L))
#define atm_cmm_unlock(oldpri,L)            atm_unlock((L)), splx(oldpri)
#define atm_cmm_lock_setup(L,I)     	    atm_lock_setup((L),(I))
#define atm_cmm_lock_terminate(L)   	    atm_lock_terminate((L))
#define atm_cmm_lock_addr(L)        	    atm_lock_addr((L))
