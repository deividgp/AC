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
 *	@(#)$RCSfile: auxv.h,v $ $Revision: 4.2.9.4 $ (DEC) $Date: 1995/01/25 18:50:49 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * OSF/1 Release 1.0
 */
/*
 *                       The Auxiliary Vector
 *
 * AT_NULL	The auxiliary vector has no fixed length; instead its
 * 		last entry's a_type member has this value.
 * 
 * AT_IGNORE	This type indicates the entry has no meaning.  The
 * 		corresponding value of a_un is undefined.
 * 
 * AT_EXECFD	exec() or exec_with_loader() may pass control to an
 * 		interpreter program.  When this happens, the system
 * 		places either and entry of type AT_EXECFD or one of
 * 		type AT_PHDR in the auxiliary vector.  The entry for
 * 		type AT_EXECFD uses the a_val member to contain a file
 * 		descriptor open to read the application program's
 * 		object file.
 * 
 * AT_PHDR	Under some conditions, the system creates the memory
 * 		image of the application program before passing
 * 		control to the interpreter program.  When this
 * 		happens, the a_ptr member of the AT_PHDR entry tells
 * 		the interpreter where to find the program header table
 * 		in the memory image.  If the AT_PHDR entry is present,
 * 		entries of types AT_PHENT, AT_PHNUM, and AT_ENTRY must
 * 		also be present.  AT_EXEC_LOADER_FILENAME
 * 
 * AT_PHENT	The a_val member of this entry holds the size, in
 * 		bytes, of one entry in the program header table to
 * 		which the entry points.
 * 
 * AT_PHNUM	The a_val member of this entry holds the number of
 * 		entries in the program header table to which the
 * 		AT_PHDR entry points.
 * 
 * AT_PAGESZ	If present, this entry's a_val member gives the system
 * 		page size, in bytes.  The same information also is
 * 		available through sysconf().
 * 
 * AT_BASE	The a_ptr member of this entry holds the base address
 * 		at which the interpreter program was loaded into
 * 		memory.
 * 
 * AT_FLAGS	If present, the a_val member of this entry holds
 * 		one-bit flags.  Bits with undefined semantics are set
 * 		to zero.  Currently, no flag definitions exist for
 * 		this entry.  Nonetheless, bits under the 0xff000000
 * 		mask are reserved for system semantics.
 * 
 * AT_ENTRY	The a_ptr member of this entry holds the entry poiint
 * 		of the application program to which the interpreter
 * 		program should transfer control.
 * 
 * AT_EXEC_FILENAME
 * 		The a_ptr member of this entry holds a pointer to a
 * 		character array that contains the filename as passed
 * 		to exec() or exec_with_loader().
 * 
 * AT_EXEC_LOADER_FILENAME
 * 		If present, the a_ptr member of this entry holds a
 * 		pointer to a character array that contains the
 * 		filename of the loader as passed to
 * 		exec_with_loader(), or the filename of the default
 * 		loader, if NULL was passed to exec_with_loader() or
 * 		exec() was invoked.
 * 
 * AT_EXEC_LOADER_FLAGS
 * 		If present, the a_val member of this entry holds
 * 		one-bit flags intended for use by the loader.  Bits
 * 		with undefined semantics are set to zero.  Currently,
 * 		no flag definitions exist for this entry.
 * 		Nonetheless, bits under the 0xff000000 mask are
 * 		reserved for system semantics.
 */

#ifndef _SYS_AUXV_H_
#define _SYS_AUXV_H_
#ifdef __cplusplus
extern "C" {
#endif

#define	AT_NULL		0
#define	AT_IGNORE	1
#define	AT_EXECFD	2
#define	AT_PHDR		3
#define	AT_PHENT	4
#define	AT_PHNUM	5
#define	AT_PAGESZ	6
#define	AT_BASE		7
#define	AT_FLAGS	8
#define	AT_ENTRY	9

#define	AT_OSF_BASE		1000
#define	AT_EXEC_FILENAME	(AT_OSF_BASE+1)
#define	AT_EXEC_LOADER_FILENAME	(AT_OSF_BASE+2)
#define	AT_EXEC_LOADER_FLAGS	(AT_OSF_BASE+3)
#define	AT_EXEC_FD		(AT_EXECFD)

union auxv_data {
	long	a_val;
	void	*a_ptr;
	void	(*a_fcn)();
};

typedef struct auxv
{
	int	a_type;
	union auxv_data a_un;
} auxv_t;

/*
 * The kernel_auxv is simply an auxv with pointers for an auxv list.
 * This is used so we can dynamically add/remove auxv entries for exec.
 * The auxv structure itself is used by user level program so don't
 * muck with its declaration.
 */
typedef struct kernel_auxv
{
	struct kernel_auxv *next, *prev;
	auxv_t a;
} kauxv_t;

#ifdef __cplusplus
}
#endif
#endif /* _SYS_AUXV_H_ */
