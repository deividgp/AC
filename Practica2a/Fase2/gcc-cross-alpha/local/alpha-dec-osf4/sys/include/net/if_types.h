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
 *	@(#)$RCSfile: if_types.h,v $ $Revision: 4.2.12.4 $ (DEC) $Date: 1995/11/03 22:54:45 $
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
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base:	if_types.h	7.2 (Berkeley) 9/20/89
 *	Merged:	if_types.h	7.3 (Berkeley) 6/28/90
 */


#ifndef _IF_TYPES_H_
#define _IF_TYPES_H_
/*
 * latest IANA sanctioned types can be found at:
 * ftp.isi.edu/in-notes/iana/assignments/smi-numbers
 */

/* interface types for benefit of parsing media address headers */
#define IFT_OTHER	0x1		/* none of the following */
#define IFT_1822	0x2		/* old-style arpanet imp */
#define IFT_HDH1822	0x3		/* HDH arpanet imp */
#define IFT_X25DDN	0x4		/* x25 to imp */
#define IFT_X25		0x5		/* PDN X25 interface */
#define	IFT_ETHER	0x6		/* Ethernet I or II */
#define	IFT_ISO88023	0x7		/* CMSA CD */
#define	IFT_ISO88024	0x8		/* Token Bus */
#define	IFT_ISO88025	0x9		/* Token Ring */
#define	IFT_ISO88026	0xa		/* MAN */
#define	IFT_STARLAN	0xb
#define	IFT_P10		0xc		/* Proteon 10MBit ring */
#define	IFT_P80		0xd		/* Proteon 10MBit ring */
#define IFT_HY		0xe		/* Hyperchannel */
#define IFT_FDDI	0xf
#define IFT_LAPB	0x10
#define IFT_SDLC	0x11
#define IFT_T1		0x12
#define IFT_CEPT	0x13
#define IFT_ISDNBASIC	0x14
#define IFT_ISDNPRIMARY	0x15
#define IFT_PTPSERIAL	0x16
#define IFT_PPP		0x17		/* Point to Point Protocol*/	
#define	IFT_LOOP	0x18		/* loopback */
#define IFT_EON		0x19		/* ISO over IP */
#define	IFT_XETHER	0x1a		/* obsolete 3MB experimental ethernet */
#define	IFT_NSIP	0x1b		/* XNS over IP */
#define	IFT_SLIP	0x1c		/* IP over generic TTY */
#define	IFT_ULTRA	0x1d		/* RFC 1213 */
#define IFT_DS3		0x1e		/* DS3/E3 interface (RFC 1407) */
#define	IFT_SIP		0x1f		/* SMDS (RFC 1305) */
#define	IFT_FRAMERELAY 	0x20		/* Frame Relay (RFC 1315) */
#define IFT_RS232	0x21		/* RS232 Objects (RFC 1659) */
#define IFT_PARALLEL	0x22		/* Parallel Objects (RFC 1660) */
#define IFT_ARCNET	0x23		/* ARC network */
#define IFT_ARCNET_PLUS	0x24		/* ARC network plus */
#define IFT_ATM		0x25		/* ATM network */
#define IFT_MIO25	0x26		/* MIOX25 (RFC 1461) */
#define IFT_SONET	0x27		/* SONET/ SDH */
#define IFT_X25PLE	0x28		/* X.25 packet level (RFC 1382)
#define IFT_ISO88022LLC 0x29		/* 802 logical link Control */
#define IFT_LOCALTALK	0x2a		
#define IFT_SMDSDXI	0x2b		/* SMDS DXI	*/ 
#define IFT_FRAMERELAYS 0x2c		/* Frame Relay DCE */
#define IFT_V35		0x2d		/* V.35 */
#define IFT_HSSI	0x2e		/* HSSI */
#define IFT_HPPI	0x2f		/* HPPI */
#define IFT_MODEM	0x30		/* "generic modem" */
#define IFT_AAL5	0x31		/* AAl5 over ATM */
#define IFT_SONETPATH	0x32	
#define IFT_SOBETVI	0x33		
#define IFT_SMDSICIP	0x34		/* SMDS InterCarrier Interface proto */
#define IFT_PROPVIRT	0x35		/* Proprietary Virtual/Internal */
					/* Interface	*/
#define IFT_PROPMULTI	0x36		/* Propietary muli-link interface */
#define IFT_IEEE80212	0x37		/* 100Base VG */
#define IFT_FIBRECHAN	0x38		/* Fibre Channel	*/
#define IFT_HPPI_I	0x39		/* HIPPI Interface */
#define IFT_FRAMEREALYI 0x3a		/* Interconnect over FR (RFC 1490) */
#define	IFT_LANE8023	0x3b		/* ATM LAN Emulation for 802.3 */
#define IFT_LANE8025	0x3c		/* ATM LAN Emulation for 802.5 */
#define IFT_ATMECIR	0x3d		/* ATM Emulatated Circuit */
#define IFT_FASTETHER	0x3e		/* Fast Ethernet (100BaseT) */
#define IFT_ISDNX25	0x3f		/* ISDN over X.25 (RFC 1356) */
#define IFT_V11		0x40		/* CCITT V/11/X.21 */
#define IFT_V36		0x41		/* CCITT V.36 */
#define	IFT_G70364K	0x42		/* CCITT G703 @ 64Kbps */
#define IFT_G7022MB	0x43		/* CCITT G703 @ 2Mbps */
#define IFT_QLLC	0x44		/* SNA QLLC */

/* non standard (non IANA) types start at 200 (decimal) */

#define IFT_WANDD       0xc8		/* Wide Area Network Device Driver */
#define	IFT_RM		0xc9		/* Memory Channel (Reflective Memory) */
#define IFT_SYNC	0xca		/* Synchronous communications */

#endif
