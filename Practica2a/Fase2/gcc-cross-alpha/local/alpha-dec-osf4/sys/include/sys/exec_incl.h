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
 *	@(#)$RCSfile: exec_incl.h,v $ $Revision: 4.2.11.3 $ (DEC) $Date: 1995/02/28 22:05:37 $
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
 * OSF/1 Release 1.0
 */
/*
 * This file contains common definitions and include files used by
 *  both kern_exec.c and ldr_exec.c
 */

#ifndef _SYS_EXEC_INCL_H_
#define _SYS_EXEC_INCL_H_

#include <bsd_a_out.h>
#include <sysv_coff.h>
#include <sysv_elf.h>
#include <osf_mach_o.h>
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/mount.h>
#include <sys/ucred.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/mman.h>
#include <sys/vm.h>
#include <sys/file.h>
#include <sys/uio.h>
#include <sys/acct.h>
#include <sys/exec.h>
#include <sys/execargs.h>
#include <machine/reg.h>

#if	SYSV_ELF
/*
 * File headers for ELF files.
 */
#include <sysV/elf_abi.h>
#ifdef mips
#include <sysV/elf_mips.h>
#endif
#endif

#if	SYSV_COFF
/*
 *	Fileheaders for coff files.
 */
#include <sysV/scnhdr.h>
#include <sysV/aouthdr.h>
#include <sysV/filehdr.h>
#endif

#if	OSF_MACH_O
/*
 *	header files for processing OSF/mach-o.
 */
#include <mach_o_header.h>
#include <mach_o_format.h>
#include <kern/kalloc.h>
#endif

/*
 *  Force all namei() calls to permit remote names since this module has
 *  been updated.
 */
#if	MACH_RFS
#undef	namei
#define namei	rnamei
#endif

#include <machine/exec_subr.h>

#include <sys/signal.h>
#include <kern/task.h>
#include <kern/thread.h>

#include <mach/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_object.h>
#include <mach/memory_object.h>
#include <vm/vm_kern.h>
#include <vm/vm_user.h>
#include <kern/kalloc.h>

#include <kern/parallel.h>



#define loader_round_page(x)	((vm_offset_t)((((vm_offset_t)(x)) \
						+ LOADER_PAGE_SIZE - 1) \
					& ~(LOADER_PAGE_SIZE-1)))
#define loader_trunc_page(x)	((vm_offset_t)(((vm_offset_t)(x)) \
					& ~(LOADER_PAGE_SIZE-1)))


/*
 *	A corrupted fileheader can cause getxfile to decide to bail
 *	out without setting up the address space correctly.  It is
 *	essential in this case that control never get back to the
 *	user.  The following error code is used by getxfile to tell
 *	execve that the process must be killed.
 */

#define EGETXFILE	126

/* The exec_privs structure contains the credentials (and privileges,
 * in a secure system) from the original program being exec'ed.
 * These privileges are preserved here across the call to getxfile()
 * or exec_load_loader(), and then established for the process when
 * the getxfile() is complete.
 */

struct exec_privs {
	struct ucred	*creds;		/* credentials */
	boolean_t	is_priv;	/* true iff file had privileges */

#if	SEC_BASE
	struct	vsecattr vsattr;	/* file's security attributes */
#endif	/* SEC_BASE */
};

#endif
