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
 * @(#)$RCSfile: dn.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1993/11/02 15:27:57 $
 */
/*
 *
 * Copyright (C) 1985, 1988 by
 * Digital Equipment Corporation, Maynard, Mass.
 *
 * This software is furnished under a license and may be used and copied
 * only  in  accordance  with  the  terms  of such  license and with the
 * inclusion of the above copyright notice. This software or  any  other
 * copies thereof may not be provided or otherwise made available to any
 * other person. No title to and ownership of  the  software  is  hereby
 * transferred.
 *
 * The information in this software is subject to change without  notice
 * and  should  not be  construed  as  a commitment by Digital Equipment
 * Corporation.
 *
 * Digital assumes no responsibility for the use or  reliability  of its
 * software on equipment which is not supplied by Digital.
 *
 *
 * Networks & Communications Software Engineering
 *
 * EDIT HISTORY
 *
 * 000	10-Jul-1985
 *	Created
 *      DECnet-ULTRIX   V1.0
 *
 * 001	18-Feb-1988	jmm
 *	Added extern definition for getnodename()
 *
 * 002	28-Feb-1988	jmm
 *	Added extern definition for proxy_requested (for use w/dnet_conn())
 */

/*	@(#)dn.h	14.2		7/31/93	*/

#ifndef _NETDNET_DN_H
#define	_NETDNET_DN_H

#ifdef KERNEL
extern struct domain decnetdomain;
#endif

/*
 * Definitions relating to the DECnet socket interface
 */

#define DNPROTO_NSP	1			/* NSP protocol number */
#define DNPROTO_ROU	2			/* Routing protocol number */
#define DNPROTO_NML	3			/* Net mgt protocol number */
#define DNPROTO_EVL	4			/* Evl protocol number (usr) */
#define DNPROTO_EVR	5			/* Evl protocol number (evl) */
#ifdef DNTRACE
#define DNPROTO_TRACE 	6			/* Trace protocol number */

#define DNBUFF_TRACE	16384			/* Trace default socket buffering */
#endif

#define SDF_WILD	 01			/* wild card object */
#define SDF_PROXY	 02			/* address eligible for proxy */
#define SDF_UICPROXY	 04			/* use uic-based proxy */
#define SDF_COTS	010			/* Use OSI Transport (vs. NSP)*/
#define	SDF_V3		020			/* V3 Session Control */

#define DN_MAXADDL	20			/* max size of DECnet address */

/*
 * DECnet address format
 */
	struct dn_naddr {
		unsigned short	a_len;		/* length of address */
		unsigned char a_addr[DN_MAXADDL]; /* address as bytes */
	    };

/*
 * DECnet socket address format
 * do first 2 bytes like sockaddr_in.
 */
	struct sockaddr_dn {
#if __osf__ && (defined(_SOCKADDR_LEN) || defined(_KERNEL))
		unsigned char	sdn_len;	/* length of sockaddr */
		unsigned char	sdn_family;	/* AF_DECnet */
#else
		unsigned short	sdn_family;	/* AF_DECnet */
#endif
		unsigned char	sdn_flags;	/* flags */
		unsigned char	sdn_objnum;	/* object number */
		unsigned short	sdn_objnamel;	/* size of object name */
		char	sdn_objname[16];	/* object name */
		struct dn_naddr  sdn_add;	/* node address */
	};

#define sdn_nodeaddrl	sdn_add.a_len		/* node address length */
#define sdn_nodeaddr	sdn_add.a_addr 		/* node address */

#define LL_INACTIVE		0		/* logical link inactive */
#define LL_CONNECTING		1		/* logical link connecting */
#define LL_RUNNING		2		/* logical link running */
#define LL_DISCONNECTING	3		/* logical link disconnecting */

/*
 * DECnet logical link information structure
 */
	struct linkinfo_dn {
		unsigned short	idn_segsize;	/* segment size for link */
		unsigned char	idn_linkstate;	/* logical link state */
	};
/*
 * Ethernet address format (for DECnet)
 */
	union etheraddress {
		unsigned char	dne_addr[6];	/* full ethernet address */
		struct {
			unsigned char dne_hiord[4];   /* DECnet HIORD prefix */
			unsigned char dne_nodeaddr[2];/* DECnet node address */
		} dne_remote;
	};
/*
 * DECnet physical socket address format
 */
	struct dn_addr {
		unsigned short	dna_family;	/* AF_DECnet */
		union etheraddress dna_netaddr;	/* DECnet ethernet address */
	};
/*
 * DECnet NSP level socket options (setsockopt/getsockopt)
 */
#define DSO_CONDATA	1	/* set/get connect data */
#define DSO_DISDATA	2	/* set/get disconnect data */
#define DSO_CONACCESS	3	/* set/get connect access data */
#define DSO_ACCEPTMODE	4	/* set/get accept mode */
#define DSO_CONACCEPT	5	/* accept deferred connection */
#define DSO_CONREJECT	6	/* reject deferred connection */
#define DSO_LINKINFO	7	/* set/get link information */
#define DSO_STREAM	8	/* set socket type to stream */
#define DSO_SEQPACKET	9	/* set socket type to sequenced packet */
#define	DSO_NODENAME	10	/* tempoary XXX */

#define DSO_MAX		10	/* highest option defined */

/*
 * DECnet set/get DSO_ACCEPTMODE values
 */
#define ACC_IMMED	0			/* accept immediately */
#define ACC_DEFER	1			/* defer acceptance */

/*
 * DECnet set/get DSO_CONDATA, DSO_DISDATA (optional data) structure
 */
	struct optdata_dn {
		unsigned short	opt_status;	/* extended status return */
		unsigned short	opt_optl;	/* length of user data */
		unsigned char	opt_data[16];	/* user data */
	};

/*
 * DECnet set/get DSO_CONACCESS access (control data) structure
 */
	struct accessdata_dn {
		unsigned short	acc_accl;	/* length of account string */
		unsigned char	acc_acc[40];	/* account string */
		unsigned short	acc_passl;	/* length of password string */
		unsigned char	acc_pass[40];	/* password string */
		unsigned short	acc_userl;	/* length of user string */
		unsigned char	acc_user[40];	/* user string */
	};

/*
 * Define DECnet objects as strings (used as argument to dnet_conn).
 */
#define DNOBJ_FAL	"#17"			/* file access listener */
#define DNOBJ_NICE	"#19"			/* NICE */
#define DNOBJ_DTERM	"#23"			/* DECnet remote terminals */
#define DNOBJ_MIRROR	"#25"			/* DECnet mirror */
#define DNOBJ_EVR	"#26"			/* DECnet event receiver */
#define DNOBJ_MAIL11	"#27"			/* mail service */
#define DNOBJ_PHONE	"#29"			/* DECnet phone utility */
#define DNOBJ_CTERM	"#42"			/* DECnet command terminals */
#define DNOBJ_DTR	"#63"			/* DECnet test receiver */
#define DNOBJ_P5EVL	"#82"			/* Phase V EVL */

/*
 * Define DECnet object numerically.
 */
#define DNOBJECT_FAL	17			/* file access listener */
#define DNOBJECT_NICE	19			/* NICE */
#define DNOBJECT_DTERM	23			/* DECnet remote terminals */
#define DNOBJECT_MIRROR	25			/* DECnet mirror */
#define DNOBJECT_EVR	26			/* DECnet event receiver */
#define DNOBJECT_MAIL11	27			/* mail service */
#define DNOBJECT_PHONE	29			/* DECnet phone utility */
#define DNOBJECT_CTERM	42			/* DECnet command terminals */
#define DNOBJECT_DTR	63			/* DECnet test receiver */
#define DNOBJECT_P5EVL	82			/* Phase V EVL */

#if !defined(KERNEL) && !defined(_KERNEL)
#if defined(_NO_PROTO)
#ifndef DNET_CONST
#define	DNET_CONST
#endif
extern struct dn_naddr *dnet_addr();
extern struct dn_naddr *getnodeadd();
extern int dnet_conn();
extern int dnet_eof();
extern char *dnet_getalias();
extern char *dnet_htoa();
extern char *dnet_ntoa();
extern char *dnet_otoa();
extern char *getnodename();
#elif defined(__STDC__) || defined(__cplusplus)
#if defined(__cplusplus)
extern "C" {
#endif
#ifndef DNET_CONST
#define	DNET_CONST	const
#endif
extern struct dn_naddr *dnet_addr(DNET_CONST char *);
extern struct dn_naddr *getnodeadd(void);
extern int dnet_conn(DNET_CONST char *, DNET_CONST char *, int,
		     DNET_CONST unsigned char *, int,
		     unsigned char *, int *);
extern int dnet_eof(int);
extern char *dnet_getalias(DNET_CONST char *);
extern char *dnet_htoa(DNET_CONST struct dn_naddr *);
extern char *dnet_ntoa(DNET_CONST struct dn_naddr *);
extern char *dnet_otoa(DNET_CONST struct sockaddr_dn *);
extern char *getnodename(void);
extern void nerror(DNET_CONST char *);
#if defined(__cplusplus)
}
#endif
#endif

/* dnet_conn() uses the following */
extern char proxy_requested;
#endif
#endif /* _NETDNET_DN_H */
