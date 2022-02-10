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
 * @(#)$RCSfile: coff_subr.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1995/11/10 20:55:57 $
 */

/*
 * Machine dependencies for COFF format
 */

/*
 * The macro N_TXTOFF() takes pointers to file header
 * [struct filehdr*] and optional header [struct aouthdr *] and returns
 * the file offset to the start of the raw data for the .text section.
 * The raw data for the three data sections follows the start of the .text
 * section by the value of tsize in the optional header.
 */
/* SCNROUND is the size that section headers are rounded off to */
#ifndef SCNROUND
#define SCNROUND ((long)16)
#endif
#ifndef OSCNRND
#define OSCNRND  ((long)8)
#endif

#ifndef N_TXTOFF
#define N_TXTOFF(f, a) \
 ((a).magic == ZMAGIC ? 0 : \
  ((a).vstamp < 23 ? \
   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + OSCNRND-1) & ~(OSCNRND-1)) : \
   ((FILHSZ + AOUTHSZ + (f).f_nscns * SCNHSZ + SCNROUND-1) & ~(SCNROUND-1))))
#endif

/*
 * for compatibility
 */
#define a_data	ex_o.dsize
#define a_text	ex_o.tsize
#define a_bss	ex_o.bsize
#define a_entry	ex_o.entry
#define a_magic	ex_o.magic

#define INIT_LOC_ZERO_HACK(map)

#define SECTALIGN	((vm_offset_t) 8192)
#define NOPAGI_TEXT_OFFSET      N_TXTOFF(*fhd, *ap)
#define NOPAGI_DATA_OFFSET      (N_TXTOFF(*fhd, *ap) + ap->tsize)
#define PAGI_TEXT_OFFSET        NOPAGI_TEXT_OFFSET
#define PAGI_DATA_OFFSET        (trunc_page(NOPAGI_DATA_OFFSET))

