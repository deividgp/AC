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
 *	@(#)$RCSfile: file.h,v $ $Revision: 4.2.18.2 $ (DEC) $Date: 1998/10/15 19:02:57 $
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
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
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_SYS_FILE_H_
#define _SYS_FILE_H_

#include <sys/types.h>
#include <sys/param.h>
#include <sys/access.h>
#include <sys/fcntl.h>

#if	defined(_KERNEL) || defined(KERNEL_FILE)

#include <sys/unix_defs.h>
#include <kern/lock.h>

/*
 * One file structure is allocated for each open/creat/pipe call.
 * Main use is to hold the read/write pointer associated with
 * each open file.
 */
struct file {
	udecl_simple_lock_data(,f_incore_lock)
	int	f_flag;			/* see below */
	uint_t	f_count;		/* reference count */
	int	f_type;			/* descriptor type */
	int	f_msgcount;		/* references from message queue */
	struct	ucred *f_cred;		/* descriptor's credentials */
	struct	fileops {
		int	(*fo_read)();
		int	(*fo_write)();
		int	(*fo_ioctl)();
		int	(*fo_select)();
		int	(*fo_close)();
	} *f_ops;
	caddr_t	f_data;			/* vnode, socket, etc. */
	union {				/* offset or next free file struct */
		off_t		fu_offset;
		struct file	*fu_freef;
	} f_u;
	uint_t	f_io_lock;		/* i/o lock (low half of thread ptr) */
	int	f_io_waiters;		/* number of waiters on i/o lock */
};

#define	f_offset	f_u.fu_offset
#define	f_freef		f_u.fu_freef

#define	DTYPE_FREE	0	/* unused file structure */
#define DTYPE_VNODE	1	/* file */
#define DTYPE_SOCKET	2	/* communications endpoint */
#define	DTYPE_RESERVED	3	/* open/close in progress XXX */

#endif	/* defined(_KERNEL) || defined(KERNEL_FILE) */

/*
 * Lseek call.
 */
#define L_SET		0	/* absolute offset */
#define L_INCR		1	/* relative to current offset */
#define L_XTND		2	/* relative to end of file */

#ifdef	_KERNEL

extern struct file *file, *fileNFILE;

#include <kern/macro_help.h>
#include <kern/assert.h>

/*
 * File structure locking constraints.
 *
 *	Field			Comment
 *	-----			-------
 *	f_flag			incore lock (but FREAD/FWRITE are read-only)
 *	f_type			read-only
 *	f_count			incore lock
 *	f_msgcount		incore lock
 *	f_cred			read-only
 *	f_ops			read-only
 *	f_data			read-only
 *	f_offset		i/o lock, incore lock
 *	f_io_lock		incore lock
 *	f_io_waiters		incore lock
 *
 * A read-only field is one set during the allocation process; no other
 * processor or thread within the same task knows about the file structure
 * yet so the values in the field don't matter while the structure is
 * being allocated.  After allocation and initialization, the value in
 * such a field never changes until the structure is de-allocated.
 *
 * The f_io_lock serializes I/O through a shared file structure.  Programs
 * that naively expect to fork and read or write streams will receive non-
 * overlapping, unduplicated input and generate non-overlapping, unduplicated
 * output (although possibly interleaved between "atomic" i/o calls).  The
 * f_io_lock accomplishes this purpose by preventing f_offset from being
 * changed between the time the I/O request is initiated and the time
 * it completes.  Although the f_io_lock is provided at the file layer, the
 * lock is used at the discretion of the lower-level fileops.  In the vnode
 * layer, this lock is used to serialize access through plain files and
 * directories but not through character-special files, symbolic links
 * or sockets.  In the latter two cases, f_offset has no meaning.  We do
 * not guarantee I/O on character-special files because device drivers
 * may have additional constraints beyond the knowledge of the file layer.
 * For example, the terminal driver must be permitted to do the job of
 * sorting out competing claims on a terminal:  if we used the f_io_lock,
 * processes sharing file structures would not be able to do output while
 * one of their number has a read outstanding on the terminal.
 *
 * The f_io_lock has one other important use:  it serializes F_SETFL
 * operations on the same file structure.  The ordinary f_incore_lock
 * does not suffice because the flags word is modified in one routine
 * but its value must be guaranteed to remain constant until it is used
 * in another.
 *
 * Finally, the file structure credentials pointer never changes during
 * the working lifetime of a file structure.  Because routines that use
 * file structures must increase their reference counts, there is no way
 * for the credentials to be deallocated while a system call is in progress.
 * For this reason, it is possible to pass the file structure's credentials
 * pointer to lower-level routines without incrementing the credentials'
 * reference count.
 */

/*
 * The FP_LOCK macros are used to prevent multiple processors from
 * accessing fields in a file structure simultaneously.  The FP_IO_LOCK
 * serializes I/O through shared file structures.
 */
#define	FP_LOCK(fp)		usimple_lock(&(fp)->f_incore_lock)
#define	FP_UNLOCK(fp)		usimple_unlock(&(fp)->f_incore_lock)
#define	FP_LOCK_HOLDER(fp)	SLOCK_HOLDER(&(fp)->f_incore_lock)

extern void fiolock(struct file *);
extern void fiounlock(struct file *);
#define	FP_IO_LOCK(fp)		fiolock(fp)
#define	FP_IO_UNLOCK(fp)	fiounlock(fp)

/*
 * The FP_REF_MT/FP_UNREF_MT takes/releases a file structure reference
 * only if the current_task() is multi-threaded.  The field 
 * uu_file_state.utask_need_to_lock is used to detirmine if the task
 * is multi-threaded.  It is cleared on a forked child, and set in 
 * thread_create() when the 2nd thread is started in a task.
 *
 * The reason the reference is needed in a multi-thread task, is so that
 * another thread with in the task doesn't close (and release) a file
 * structure in the middle of an operation.  Ofcourse this can't happen
 * in a single threaded task.
 *
 * Count uses of a file structure by the kernel itself as well as
 * by file descriptors.  FP_REF_MT never sleeps.  FP_UNREF_MT may sleep
 * when the count falls to zero and closef_locked is called.
 */
#define	FP_REF_MT(fp,ufp)						\
MACRO_BEGIN								\
	if ((ufp)->utask_need_to_lock) {				\
		FP_LOCK(fp);						\
		(fp)->f_count++;					\
		ASSERT(fp->f_count > 0);				\
		FP_UNLOCK(fp);						\
	}								\
MACRO_END

#define	FP_UNREF_MT(fp,ufp)						\
MACRO_BEGIN								\
	if ((ufp)->utask_need_to_lock) { 				\
		FP_LOCK(fp);						\
		ASSERT(fp->f_count > 0);				\
		if ((fp)->f_count > 1) {				\
			(fp)->f_count--;				\
			FP_UNLOCK(fp);					\
		} else {						\
			FP_UNLOCK(fp);					\
			(void) closef(fp);				\
		}							\
	} 								\
MACRO_END
/*
 * FP_REF_ALWAYS/FP_UNREF_ALWAYS will take/release a file reference.  This
 * is used in cases like fork/closef that really need to do the reference
 * in all cases.
 */
#define	FP_REF_ALWAYS(fp)						\
MACRO_BEGIN								\
	FP_LOCK(fp);							\
	(fp)->f_count++;						\
	ASSERT(fp->f_count > 0);					\
	FP_UNLOCK(fp);							\
MACRO_END

#define	FP_UNREF_ALWAYS(fp)						\
MACRO_BEGIN								\
	FP_LOCK(fp);							\
	ASSERT(fp->f_count > 0);					\
	if ((fp)->f_count > 1) {					\
		(fp)->f_count--;					\
		FP_UNLOCK(fp);						\
	} else {							\
		extern void closef_locked(struct file *);		\
		closef_locked(fp);					\
	}								\
MACRO_END

/*
 * File descriptor constraints.
 *
 * In Mach, multiple threads within the same task share a file
 * descriptor table, permitting races not found in the traditional
 * BSD model of one process + one file descriptor table.
 *
 * File descriptor allocation is broken into two steps:  (1) reserving
 * a file descriptor and (2) after the open succeeds, resetting the
 * reserved file descriptor to point to the new file structure.  The
 * U_FD_SET macro performs the reset.  If the open fails, U_FD_SET(fd,NULL)
 * frees up the reserved file descriptor.
 *
 * getf translates a file descriptor to a file structure and increments
 * the file structure's reference count.  The reference count is used
 * to prevent the file structure from being deallocated while the kernel
 * uses it.
 *
 * The file descriptor table lock may be held while acquiring a file
 * structure's f_incore_lock.
 */

#define	U_FD_RESERVED		((struct file *) -1)
#define	FILE_FLAGS_NULL		((char *) 0)

extern int getf();
extern int getf_ref_always();

#define	U_FD_SET(fd, fp, ufp)						\
MACRO_BEGIN								\
	U_FDTABLE_LOCK_ALWAYS(ufp);					\
	ASSERT(U_OFILE(fd, ufp) == U_FD_RESERVED); 		        \
	U_OFILE_SET(fd, fp, ufp); 				        \
	U_FDTABLE_UNLOCK_ALWAYS(ufp);					\
MACRO_END

/*
 * The FOP macros simplify calling through the file structure operations
 * table by taking into account a number of important details, such as
 * possible backwards compatibility with unparallelized subsystems.
 *
 * It is not legal to hold any simple locks across an FOP call.
 *
 * Funneling at the file descriptor level is no longer supported.
 */

#define	FOP_READ(fp,uio,cred,ret_val) \
	(ret_val) = (*(fp)->f_ops->fo_read)((fp),(uio),(cred))

#define	FOP_WRITE(fp,uio,cred,ret_val) \
	(ret_val) = (*(fp)->f_ops->fo_write)((fp),(uio),(cred))

#define	FOP_IOCTL(fp,cmd,value,rv,ret_val) \
	(ret_val) = (*(fp)->f_ops->fo_ioctl)((fp),(cmd),(value),(rv))

#define	FOP_SELECT(fp,ev,rev,scanning,ret_val) \
	(ret_val) = (*(fp)->f_ops->fo_select)((fp),(ev),(rev),(scanning))

#define	FOP_CLOSE(fp,ret_val) \
	(ret_val) = (*(fp)->f_ops->fo_close)(fp)

#endif	/* _KERNEL */
#endif	/* _SYS_FILE_H_ */
