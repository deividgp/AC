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
 * @(#)$RCSfile: otto_fakesnmp.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1997/03/27 13:27:30 $
 */
/* This is the packet exchanged on an AN2 SNMP VC (VCI=16) when SNMP hasn't
   been implemented yet.

The packets described below are exchanged between the two ends of the
link.

Packets are of two types: "request" and "reply".  Both packet
types contain the same fields.

A reply is sent only in response to a request, and should be sent
promptly in reponse to the request.

If the link is down (i.e. the physical layer is reporting
loss of connection), requests should either not be sent at all,
or should be sent infrequently (e.g. more than 10s between requests).

Otherwise, if a request or reply has been received recently and since
the link came up, new requests should be sent infrequently (e.g. more
than 10s between requests).  If no request or reply has been received
recently (e.g. in tens of seconds) new requests should be sent
infrequently (e.g. more than 10s between requests).   

If the link came up very recently, or if the far end failed to
respond to the last request promptly having responded to previous 
requests promptly, the sender may send new requests frequently
(e.g. 0.2s between requests).   

On byte order
-------------
   u_word8 is an unsigned 8-bit quantity.
   u_word16 is an unsigned 16-bit quantity.
   u_word32 is an unsigned 32-bit quantity.

   All instances of u_word16 and u_word32 are in big-endian byte-order
   on the wire.
   That is, the first byte to appear in the packet is the most-significant
   byte of the integer being represented.

   The 48-bit UID appears in normal, Ethernet-style order.  That is, the
   "multicast bit" is bit 0 of byte 0.

In the comments below:
		"A"   means must be filled in correctly always.
		"R"   means must be filled in correctly with non-zero 
		      values if "rcvsupport==1".
	        "D"   means that the value used on the link should be the 
	              value in the packet sent by the dominant endpoint.
		      On a switch-host link, the switch is the dominant
		      endpoint.  On a host-host link or a switch-switch
		      link, the endpoint with the lower UID is dominant.
		      These fields are ignored in packets received by
		      the dominant endpoint.
	        "F"   means must be filled in correctly with non-zero
	              values if "fmsupport==1".
	        "O"   means optional.  The field should either contain
	              the correct value, or should contain zero.
		      If both sender and receiver give VC ranges in the
		      optional fields, and the ranges do not agree, the
		      intersection of each range is used.
 */

#define u_word8 unsigned char   /* one byte */
#define u_word16 unsigned short /* two bytes, bigendian on the wire */
#define u_word32 unsigned int   /* four bytes, bigendian on the wire */

#define OTTO_FS_VCI 16		/* VCI these packets go on */
#define OTTO_RESYNC_VCI 2	/* Default VCI for credit resync */
#define OTTO_FS_ESCAPE 0x55	/* first byte */
#define OTTO_FS_VERSION 1	/* version number */
#define OTTO_FS_REQUEST 1	/* indicates a request */
#define OTTO_FS_REPLY 2		/* indicates a reply */
#define OTTO_FS_SWITCH 3	/* indicates a DEC switch */
#define OTTO_FS_HOST 4		/* indicates a DEC host */

/* The packet is as follows.  In the wire representation, there are no
   gaps between fields. */
struct otto_fakesnmp {
        u_word8 escape;      /*A = 0x55 "this is not an SNMP packet" */
        u_word8 version;     /*A = 1    version number of this packet */
        u_word16 pkttype;    /*A 1=request, 2=reply */

        u_word32 type;       /*A sender type (3=DEC switch, 4=DEC host) */
        u_word32 subtype;    /*A sender subtype (AN2=3, AN3=4, OTTO=0) */
        u_word32 maxvcibits; /*A Max VCI bits supported at sender */
        u_word8  uid[6];     /*A 48-bit UID of sender */
        u_word8  pad[2];     /*A padding (sender set to 0, receiver ignore) */
        u_word32 fmsupport;  /*A sender supports flowmaster (0=no, 1=yes) */
        u_word32 rvcsupport; /*A sender supports RVCs (0=no, 1=yes) */

        u_word32 bcastVCIout;/*RD RVC VCI for receiver to send broadcasts to */
        u_word32 bcastVCIin; /*RD RVC VCI for broadcasts arriving at receiver */
        u_word32 arpVCIout;  /*RD RVC VCI for receiver to send ARPs to */
        u_word32 arpVCIin;   /*RD RVC VCI for ARPs arriving at receiver */
        u_word32 homeVCI;    /*R  RVC home VCI of receiver (if it's a host)*/

        u_word32 resyncVCI;  /*FD FM resync VCI to be used by receiver */
        u_word32 abrbuffers; /*F total ABR buffers available at sender */
        u_word32 abrbufpervc;/*F maximum ABR buffers available per VC */

        u_word32 minrvcVCI;  /*O minimum RVC VCI that sender supports */
        u_word32 maxrvcVCI;  /*O maximum RVC VCI that sender supports */
        u_word32 minsvcVCI;  /*O minimum SVC VCI that sender supports */
        u_word32 maxsvcVCI;  /*O maximum SVC VCI that sender supports */
        u_word32 minpvcVCI;  /*O minimum PVC VCI that sender supports */
        u_word32 maxpvcVCI;  /*O maximum PVC VCI that sender supports */
};

#undef u_word8
#undef u_word16
#undef u_word32
