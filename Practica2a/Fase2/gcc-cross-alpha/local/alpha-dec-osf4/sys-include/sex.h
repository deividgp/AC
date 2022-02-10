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
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Drive                                |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */
/* $Header: /usr/sde/osf1/rcs/os/src/usr/include/alpha/sex.h,v 1.1.6.3 1994/05/12 18:03:25 Thomas_Peterson Exp $ */

/*
 * This file contains macro constant names for byte sex flags, the macros for
 * byte swapping words and half words, and the external declarations for the
 * routines in libsex.a which change the sex of structures that appear
 * in object files.
 */

#ifndef _SEX_H_
#define _SEX_H_

#include <standards.h>
#include <filehdr.h>
#include <aouthdr.h>
#include <scnhdr.h>
#include <sym.h>

/* forward decls for C++ */
struct reloc;
struct ranlib;

/*
 * Byte sex constants
 */
#define BIGENDIAN	0
#define LITTLEENDIAN	1
#define UNKNOWNENDIAN	2

/*
 * Byte swaps for word and half words.
 */
#if defined(__mips64) || defined(__alpha)
#define swap_word(a) ( ((a) << 24) | \
		      (((a) << 8) & 0x00ff0000) | \
		      (((a) >> 8) & 0x0000ff00) | \
	((unsigned int)(a) >>24) )
#else
#define swap_word(a) ( ((a) << 24) | \
		      (((a) << 8) & 0x00ff0000) | \
		      (((a) >> 8) & 0x0000ff00) | \
	((unsigned long)(a) >>24) )
#endif

#define swap_half(a) ( ((a & 0xff) << 8) | ((unsigned short)(a) >> 8) )

_BEGIN_CPLUSPLUS
extern
int
gethostsex __((void));

extern
void
swap_filehdr __((FILHDR *, int));

extern
void
swap_aouthdr __((AOUTHDR *, int));

extern
void
swap_scnhdr __((SCNHDR *, int));

extern
void
swap_hdr __((pHDRR, int));

extern
void
swap_fd __((pFDR, int, int));

extern
void
swap_fi __((pFIT, int, int));

extern
void
swap_sym __((pSYMR, int, int));

extern
void
swap_ext __((pEXTR, int, int));

extern
void
swap_pd __((pPDR, int, int));

extern
void
swap_opt __((pOPTR, int, int));

extern
void
swap_aux __((pAUXU, int, int));

extern
void
swap_reloc __((struct reloc *, int, int));

extern
void
swap_ranlib __((struct ranlib *, int, int));

extern
void
swap_gpt __((GPTAB *, int, int));

_END_CPLUSPLUS
#endif /* _SEX_H_ */
