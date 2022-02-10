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
 *	@(#)$RCSfile: exec.h,v $ $Revision: 4.3.10.2 $ (DEC) $Date: 1996/01/31 22:17:55 $
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
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_EXEC_H_
#define _SYS_EXEC_H_

/*
 * Header prepended to each a.out file.
 */

#if	!defined(mips) && !defined(__alpha)
struct exec {
        long    a_magic;        /* magic number */
        unsigned long   a_text;         /* size of text segment */
        unsigned long   a_data;         /* size of initialized data */
        unsigned long   a_bss;          /* size of uninitialized data */
        unsigned long   a_syms;         /* size of symbol table */
        unsigned long   a_entry;        /* entry point */
        unsigned long   a_trsize;       /* size of text relocation */
        unsigned long   a_drsize;       /* size of data relocation */
};
#endif	/* !defined(mips) && !defined(__alpha) */

#define OMAGIC	0407		/* old impure format */
#define NMAGIC	0410		/* read-only text */
#define ZMAGIC	0413		/* demand load format */

/*
 * Return codes for the recognizers.  These are negative
 * so they can be distinguished from a legitimate error as
 * defined in errno.h.  Also code indicating a handle was
 * freed up in a getloader function.
 */
#define	EXEC_NEEDLDR	-1
#define	EXEC_RECOG	-2
#define	EXEC_FREEHDL	-3

/*
 * Exec buffer declarations
 */
#define MAXEXECBUF	MAXINTERP

#ifdef mips
#if	BYTE_MSF
#define MIPSMAGIC	MIPSEBMAGIC
#else
#define MIPSMAGIC	MIPSELMAGIC
#endif
#endif	/* mips */

#if defined (mips) || defined (__alpha)
/*
 * The macro N_TXTOFF() takes pointers to file header
 * [struct filehdr*] and optional header [struct aouthdr *] and returns
 * the file offset to the start of the raw data for the .text section.
 * The raw data for the three data sections follows the start of the .text
 * section by the value of tsize in the optional header.
 */
/* SCNROUND is the size that section headers are rounded off to */
#define SCNROUND 16
#define OSCNRND  8

#define N_TXTOFF(f, a) \
 ((long)((a).magic == ZMAGIC ? 0 : \
  ((a).vstamp < 23 ? \
   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + OSCNRND-1) & ~(OSCNRND-1)) : \
   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + SCNROUND-1) & ~(SCNROUND-1)))))

#ifndef _KERNEL
#include <aouthdr.h>
#include <filehdr.h>

struct exec {
	struct filehdr	ex_f;
	struct aouthdr	ex_o;
};

#endif /* kernel */
/*
 * for compatibility
 */
#define a_data  ex_o.dsize
#define a_text  ex_o.tsize
#define a_bss   ex_o.bsize
#define a_entry ex_o.entry
#define a_magic ex_o.magic

#endif /* mips || __alpha */

struct execbuf {
	char 	exec[MAXEXECBUF];
};

/*
 * Exec switch table declarations
 */
#define EXEC_VERSION	1
#define EXEC_NULL	((struct execops *)NULL)

extern ulong mgr_id;
extern struct execops *execsw;
extern struct execops *execswinit[];

#ifdef _KERNEL
udecl_simple_lock_data	(extern, exec_switch_lock)
udecl_simple_lock_info	(extern, exec_switch_lockinfo)
#define	EXECSW_LOCK()	usimple_lock(&exec_switch_lock)
#define EXECSW_UNLOCK()	usimple_unlock(&exec_switch_lock)
#define EXECSW_LOCK_INIT()	usimple_lock_setup(&exec_switch_lock, \
						   exec_switch_lockinfo)

/*
 * Macro to unreference the manager and perform any necessary wake ups.
 * The exec_switch_lock MUST be held when this macro is called.
 */
#define	EXEC_MGR_UNREF(mgr)					\
MACRO_BEGIN							\
	LASSERT(SLOCK_HOLDER(&exec_switch_lock));		\
	mgr->refcount--;					\
	if (mgr->refcount == 0 && mgr->flag & EXEC_WAIT) {	\
		mgr->flag &= ~EXEC_WAIT;			\
		thread_wakeup((vm_offset_t)mgr);			\
	}							\
MACRO_END
#endif /* _KERNEL */

/*
 * Switch entry for each manager
 */
struct execops {
	int	(*recognize) ( 	/* vp, vap, buf, len, flagp, handlep, t_start */);
	int	(*getloader)(  	/* vp, file, defldr, flag, arg, handle */);
	int	(*getxfile)(   	/* proc, vp, arg, handle */);
	int	(*ungetxfile)( 	/* omgr, ohandle, nmgr, nhandle, ispriv */);
	int	(*setregs)(    	/* handlep */);
	int	(*reference)(   /* handle */);
	int	refcount;	/* how many are using this manager */
	int	flag;		/* manager flags */
	int	id;		/* manager id for dynamic usage */
	struct execops *next;
	struct execops *prev;
};

/*
 * Flags for execops
 */
#define EXEC_WAIT	0x1

/*
 * Exec operations
 */
#define _EXECOP_(f,m,arg,r)	(r) = (*((m)->f))arg;

#define EXECOP_RECOGNIZE(m,v,a,b,l,f,h,t,r)  _EXECOP_(recognize,(m),((v),(a),(b),(l),(f),(h),(t)),(r))
#define EXECOP_GETLOADER(m,v,f,l,fl,a,h,r) _EXECOP_(getloader,(m),((v),(f),(l),(fl),(a),(h)),(r))
#define EXECOP_GETXFILE(m,p,v,a,h,vr,r)	_EXECOP_(getxfile,(m),((p),(v),(a),(h),(vr)),(r))
#define EXECOP_UNGETXFILE(m,om,oh,nm,nh,p,r)	_EXECOP_(ungetxfile,(m),((om),(oh),(nm),(nh),(p)),(r))
#define EXECOP_SETREGS(m,h,r)		_EXECOP_(setregs,(m),((h)),(r))
#define EXECOP_REFERENCE(m,h,r)		_EXECOP_(reference,(m),((h)),(r))


/*
 * Default Loader File Name
 */
#define	LDR_EXEC_DEFAULT_LOADER	"/sbin/loader"

/*
 *  AT_EXEC_LOADER_FLAGS Auxiliary Vector Entry Value
 */
#define	LDR_EXEC_SYSTEM_MASK	0xffff0000
#define	LDR_EXEC_USER_MASK	0x0000ffff
#define	LDR_EXEC_SETUID_F	0x80000000
#define	LDR_EXEC_SETGID_F	0x40000000
#define	LDR_EXEC_PTRACE_F	0x20000000
#define LDR_EXEC_NOPRIVS_F	0x10000000

#endif	/* _SYS_EXEC_H_ */
