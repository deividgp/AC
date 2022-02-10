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
 * @(#)$RCSfile: coff_exec.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1993/09/23 14:54:10 $
 */

/*
 *      Fileheaders for coff files.
 */
#include <sysV/scnhdr.h>
#include <sysV/aouthdr.h>
#include <sysV/filehdr.h>

#include <machine/coff_subr.h>

/*
 *      Corresponding definitions are in coff_getxfile because the
 *      section size (SECTALIGN, corresponds to LOADER_PAGE_SIZE)
 *      must be obtained from the file header for some architectures.
 */

#ifdef  LOADER_PAGE_SIZE
#define SECTALIGN               LOADER_PAGE_SIZE
#else
#define LOADER_PAGE_SIZE        SECTALIGN
#endif

/*
 * This is the coff header.
 */
struct coff_hdr {
	struct filehdr fhdr;
	struct aouthdr ohdr;
};

union coff_exec {
	struct coff_hdr coff;
	struct {
		short magic;
	} coff_magic;
};

struct coff_handle {
	struct coff_hdr	hdr;
	memory_object_t	pager;
#if	SEC_BASE
	boolean_t	is_priv;
#endif
};

#define hdr_magic	coff_magic.magic

/*
 * This structure contains a set of machine-dependent data that is set
 * up when exec'ing a COFF file.
 */
struct coff_machine {
	off_t		nopagi_text;
	off_t		nopagi_data;
	vm_offset_t	pagi_text;
	vm_offset_t	pagi_data;
	int		vm_flags;
	size_t		data_size;
};
