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
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *

 */

#ifndef _A_OUT_H_
#define _A_OUT_H_
#include <nlist.h>	/* included for all machines */

#include <filehdr.h>
#include <aouthdr.h>
#include <scnhdr.h>
#include <reloc.h>
#include <syms.h>

/*
 * The macro N_TXTOFF() takes pointers to file header and optional header and 
 * returns the file offset to the start of the raw data for the text segment.
 * The raw data for the data segment follows the start of the text segment by 
 * the value of tsize in the optional header.
 *
 * For ZMAGIC files the text segment includes the file, optional and section
 * headers, so the N_TXTOFF value is 0.
 */

#define N_TXTOFF(f, a) \
 ((a).magic == ZMAGIC || (a).magic == LIBMAGIC ? 0 : \
  ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + SCNROUND-1) & ~(SCNROUND-1)))
#endif /* _A_OUT_H_ */
