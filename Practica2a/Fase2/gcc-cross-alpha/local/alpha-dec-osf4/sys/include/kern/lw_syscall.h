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
 *	@(#)$RCSfile: lw_syscall.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1996/12/20 18:26:37 $
 */ 

#ifndef lw_syscall_h
#define lw_syscall_h

/************************************************************************
 *
 *  File:   lw_syscall.h
 *  Author: Mark O. Yeager
 *
 *  Purpose - 
 *      Used by subsystems and device drivers in the kernel that make use
 *      of the light weight system call functionality.
 *
 ************************************************************************/

/************************************************************************
 *
 *                             Macros
 *
 ************************************************************************/

/*  Flag to lw_syscall_register() to indicate lw_syscall software
 *  should choose the index for the function being registered.
 */
#define LW_SYSCALL_GENERATE_INDEX                   (-1)

/*  Flag to lw_syscall_unregister() to indicate lw_syscall software
 *  should unregister all instances of the given function.
 */
#define LW_SYSCALL_UNREGISTER_ALL                   (-2)

/*  status from lw_syscall_register() and from
 *  lw_syscall_unregister()
 */
#define LW_SYSCALL_SUCCESS                          (0)
#define LW_SYSCALL_ERROR_MAX_REGISTERED_FUNCTION    (-1)
#define LW_SYSCALL_ERROR_MALLOC                     (-2)
#define LW_SYSCALL_ERROR_INDEX_IN_USE               (-3)
#define LW_SYSCALL_ERROR_MIN_REGISTERED_FUNCTION    (-4)


/*
 * Kernel-private interfaces
 */
#if defined(_KERNEL)

/************************************************************************
 *
 *               External Function and Function Type Declarations
 *
 ************************************************************************/

typedef kern_return_t (*lw_syscall_func_t)(
    unsigned long registered_function_index, 
    unsigned long arg1, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4,
    unsigned long arg5
    );

extern long
  lw_syscall_register(
    lw_syscall_func_t func, 
    long registered_function_index, 
    int smp_safe,
    int force_overwrite
    );

extern long
lw_syscall_unregister(
    lw_syscall_func_t func,
    long registered_function_index
    );

#endif /* _KERNEL */

#endif /* lw_syscall_h */
/************************************************************************
 *
 *                           End of File lw_syscall.h
 *
 ************************************************************************/
