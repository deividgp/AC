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
 * @(#)$RCSfile: exec_subr.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1993/09/23 14:52:24 $
 */

#include <sys/ptrace.h>

/*
 * Generic machine dependencies
 */
#define EXEC_SIGTRAP()
#define EXEC_STACK	EF_SP

/*
 * Machine dependencies for init
 */
/* 
 * SETUP_INIT_ARGS is called just before the first exec of the boot.
 * It is the last place where pmap_scavenge_boot() can be called.  This is
 * desirable because this routine reclaims the address space for the used
 * only once kernel code.
 */
#define SETUP_INIT_ARGS() pmap_scavenge_boot()

#define ALLOW_INITNAME	1
#define GETS(i)		gets(i)

/*
 * Machine dependencies for reading and writing argument pointers
 */

#define WRITE_ARG_PTR(app, ucpp) (suqword(app, ucpp))
#define READ_ARG_PTR(app) (fuqword(app))
