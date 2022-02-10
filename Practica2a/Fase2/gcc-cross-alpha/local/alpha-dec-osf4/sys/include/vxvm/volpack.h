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

#pragma	ident	"@(#)$RCSfile: volpack.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1995/01/31 20:43:56 $"

/* @(#)src/common/uts/io/vxvm/volpack.h	5.3 16 Mar 1993 02:07:45 - Copyright (c) 1993 VERITAS Software Corp. */
/*
 * Copyright(C)1993 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 * 
 *               RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *               VERITAS SOFTWARE
 * 4800 GREAT AMERICA PARKWAY, SANTA CLARA, CA 95054
 */
/*
 * Alpha change log
 *
 * 09-29-93	Wai Yim
 * Merged alpha port with vxvm1.2.1 source.
 *
 */

#ifndef _SYS_VOLPACK_H
#define _SYS_VOLPACK_H

/*
 * definitions for transforming between values stored in a host-
 * independent order and size, and native values.
 *
 * For example, given an internal structure:
 *
 *	struct foo {
 *		ulong_t		foo_long;
 *		ushort_t	foo_short;
 *		volrid_t	foo_rid;
 *	};
 *
 * This structure can be transformed into a 14-byte host-independent
 * stucture stored in a character array using:
 *
 *	struct foo x;
 *	char buf[VOL_ULONG_BYTES + VOL_USHORT_BYTES + VOL_RID_BYTES];
 *	char *p = buf;
 *	...
 *
 *	VOL_ULONG_STORE(x.foo_long, p);
 *	VOL_USHORT_STORE(x.foo_long, p);
 *	VOL_RID_STORE(x.foo_rid, p);
 *
 * To transform form host-independent to internal form, use:
 *
 *	VOL_ULONG_LOAD(x.foo_long, p);
 *	VOL_USHORT_LOAD(x.foo_long, p);
 *	VOL_RID_LOAD(x.foo_rid, p);
 *
 * At the end of such sequences, the value p-buf will equal the
 * size of the host-independent structure parsed or generated up
 * to that point.
 *
 * 64-bits are reserved for voff_t types even on machines where a
 * voff_t type is 32 bits.  However, if a 64-bit voff_t is written
 * on a machine with 64-bits, then reading the value back on a
 * 32-bit machine will truncate the value to 32 bits.
 */

#define VOL_USHORT_BYTES	((size_t)2)
#define VOL_UMIDDLE_BYTES	((size_t)3)
#define VOL_ULONG_BYTES		((size_t)4)
#define VOL_VOFF_BYTES		((size_t)8)
#define VOL_SEQNO_BYTES		(2 * VOL_ULONG_BYTES)
#define VOL_RID_BYTES		VOL_SEQNO_BYTES

#define VOL_UCHAR_LOAD(c, p)	\
	((c) = ((unsigned char *)(p))[0],			\
	 (p) += 1)

#define VOL_USHORT_LOAD(s, p)	\
	((s) = (((ushort_t)((unsigned char *)(p))[0] << 8) |	\
		((ushort_t)((unsigned char *)(p))[1])),		\
	 (p) += VOL_USHORT_BYTES)

#define VOL_UMIDDLE_LOAD(l, p)	\
	((l) = (((ulong_t)((unsigned char *)(p))[0] << 16) |	\
		((ulong_t)((unsigned char *)(p))[1] << 8) |	\
		((ulong_t)((unsigned char *)(p))[2])),		\
	 (p) += VOL_MIDDLE_BYTES)

#define VOL_ULONG_LOAD(l, p)	\
	((l) = (((ulong_t)((unsigned char *)(p))[0] << 24) |	\
		((ulong_t)((unsigned char *)(p))[1] << 16) |	\
		((ulong_t)((unsigned char *)(p))[2] << 8) |	\
		((ulong_t)((unsigned char *)(p))[3])),		\
	 (p) += VOL_ULONG_BYTES)

#if VOFF_T_QUAD
#define VOL_VOFF_LOAD(v, p)	\
	((v) = (voff_t)		\
	       (((uvoff_t)((unsigned char *)(p))[0] << 56) |	\
		((uvoff_t)((unsigned char *)(p))[1] << 48) |	\
		((uvoff_t)((unsigned char *)(p))[2] << 40) |	\
		((uvoff_t)((unsigned char *)(p))[3] << 32) |	\
		((uvoff_t)((unsigned char *)(p))[4] << 24) |	\
		((uvoff_t)((unsigned char *)(p))[5] << 16) |	\
		((uvoff_t)((unsigned char *)(p))[6] << 8) |	\
		((uvoff_t)((unsigned char *)(p))[7])),		\
	 (p) += VOL_VOFF_BYTES)
#else	/* not VOFF_T_QUAD */
#define VOL_VOFF_LOAD(v, p)	\
	((v) = (voff_t)		\
	       (((ulong_t)((unsigned char *)(p))[4] << 24) |	\
		((ulong_t)((unsigned char *)(p))[5] << 16) |	\
		((ulong_t)((unsigned char *)(p))[6] << 8) |	\
		((ulong_t)((unsigned char *)(p))[7])),		\
	 (p) += VOL_VOFF_BYTES)
#endif	/* VOFF_T_QUAD */

#define VOL_SEQNO_LOAD(sq, p)	\
	(VOL_ULONG_LOAD((sq).seqno_hi, (p)),			\
	 VOL_ULONG_LOAD((sq).seqno_lo, (p)))

#define VOL_RID_LOAD(rid, p)	VOL_SEQNO_LOAD((rid), (p))

#define VOL_UCHAR_STORE(c, p)	\
	(((unsigned char *)(p))[0] = (c) & 0xff,		\
	 (p) += 1)

#define VOL_USHORT_STORE(s, p)	\
	(((unsigned char *)(p))[0] = ((s) >> 8)&0xff,		\
	 ((unsigned char *)(p))[1] = (s)&0xff,			\
	 (p) += VOL_USHORT_BYTES)

#define VOL_UMIDDLE_STORE(l, p)	\
	(((unsigned char *)(p))[0] = ((l) >> 16)&0xff,		\
	 ((unsigned char *)(p))[1] = ((l) >> 8)&0xff,		\
	 ((unsigned char *)(p))[2] = (l)&0xff,			\
	 (p) += VOL_UMIDDLE_BYTES)

#define VOL_ULONG_STORE(l, p)	\
	(((unsigned char *)(p))[0] = ((l) >> 24)&0xff,		\
	 ((unsigned char *)(p))[1] = ((l) >> 16)&0xff,		\
	 ((unsigned char *)(p))[2] = ((l) >> 8)&0xff,		\
	 ((unsigned char *)(p))[3] = (l)&0xff,			\
	 (p) += VOL_ULONG_BYTES)

#if VOFF_T_QUAD
#define VOL_VOFF_STORE(v, p)	\
	(((unsigned char *)(p))[0] = ((uvoff_t)(v) >> 56)&0xff,	\
	 ((unsigned char *)(p))[1] = ((uvoff_t)(v) >> 48)&0xff,	\
	 ((unsigned char *)(p))[2] = ((uvoff_t)(v) >> 40)&0xff,	\
	 ((unsigned char *)(p))[3] = ((uvoff_t)(v) >> 32)&0xff,	\
	 ((unsigned char *)(p))[4] = ((uvoff_t)(v) >> 24)&0xff,	\
	 ((unsigned char *)(p))[5] = ((uvoff_t)(v) >> 16)&0xff,	\
	 ((unsigned char *)(p))[6] = ((uvoff_t)(v) >> 8)&0xff,	\
	 ((unsigned char *)(p))[7] = (uvoff_t)(v)&0xff,		\
	 (p) += VOL_VOFF_BYTES)
#else	/* not VOFF_T_QUAD */
#define VOL_VOFF_STORE(v, p)	\
	(((unsigned char *)(p))[4] = ((uvoff_t)(v) >> 24)&0xff,	\
	 ((unsigned char *)(p))[5] = ((uvoff_t)(v) >> 16)&0xff,	\
	 ((unsigned char *)(p))[6] = ((uvoff_t)(v) >> 8)&0xff,	\
	 ((unsigned char *)(p))[7] = (uvoff_t)(v)&0xff,		\
	 (p) += VOL_VOFF_BYTES)
#endif	/* VOFF_T_QUAD */

#define VOL_SEQNO_STORE(sq, p)	\
	(VOL_ULONG_STORE((sq).seqno_hi, (p)),			\
	 VOL_ULONG_STORE((sq).seqno_lo, (p)))

#define VOL_RID_STORE(rid, p)	VOL_SEQNO_STORE((rid), (p))

#endif	/* _SYS_VOLPACK_H */
