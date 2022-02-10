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
 *	"@(#)endian.h	9.1	(ULTRIX/OSF)	10/21/91"
 */ 
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
/************************************************************************
 *			Modification History: alpha/endian.h
 *
 *  28-May-91	afd
 *	Created this file for Alpha/OSF support
 *
 ************************************************************************/

#ifndef	_MACHINE_ENDIAN_H_
#define _MACHINE_ENDIAN_H_

#if !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE)
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */

/* MIPS may use either endian, compiler tells us which. */
#define	BYTE_ORDER	LITTLE_ENDIAN


#endif /* !defined (_XOPEN_SOURCE_EXTENDED) || defined (_OSF_SOURCE) */

/*
 * Macros for network/external number representation conversion.
 */
#ifdef KERNEL
#define	ntohl(x)	nuxi_32(x)
#define	ntohs(x)	nuxi_16(x)
#define	htonl(x)	nuxi_32(x)
#define	htons(x)	nuxi_16(x)
#define NTOHL(x)	(x) = ntohl((u_int)x)
#define NTOHS(x)	(x) = ntohs((u_short)x)

#if defined(_USE_KERNEL_INTRINSICS)

/*
 * DO NOT MERGE THIS INTO STEEL.  'r2' is actually preserved by the
 * nuxi_16/32 routines in V4.0F, but listing it as preserved in V4.0F
 * would break binaries built on V4.0F that were to be taken back to 
 * V4.0D/E.
 */
#pragma linkage nuxi_linkage = \
  (preserved(r3,r4,r5,r6,r7,r8,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25))
#pragma use_linkage nuxi_linkage(nuxi_16)
#pragma use_linkage nuxi_linkage(nuxi_32)
#endif
#else /* !KERNEL */
#if defined(__STDC__) || defined(__cplusplus)
#if defined(__cplusplus)
extern "C" {
#endif
unsigned short	ntohs(unsigned short), htons(unsigned short);
unsigned int	ntohl(unsigned int), htonl(unsigned int);
#if defined(__cplusplus)
}
#endif
#else
unsigned short	ntohs(), htons();
unsigned int	ntohl(), htonl();
#endif
#endif /* !KERNEL */

#endif
