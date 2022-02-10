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
 * @(#)$RCSfile: xti.h,v $ $Revision: 4.2.23.3 $ (DEC) $Date: 1997/08/29 19:55:59 $
 */ 

/** Copyright (c) 1989  Mentat Inc.
 ** xti.h 1.1, last change 4/14/90
 **/

#ifndef _XTI_H
#define _XTI_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_KERNEL
#include <standards.h>
#endif  /* ifndef _KERNEL */

/* 
 * To get the SPEC1170 or XPG4 XTI compliance the macro _XOPEN_SOURCE
 * must be defined.
 * 
 * MIGRATION NOTE:
 * If you want to maintain the XTI compatibility at XPG3 level, while getting
 * the SPEC1170 or XPG4 functionality for other subsystems, then XTI_XPG3 macro 
 * can be defined to override the _XOPEN_SOURCE for XTI at 
 * compile-time. 
 */
#if defined(XTI_SPEC1170) && !defined(_XOPEN_SOURCE)
#define _XOPEN_SOURCE
#endif

/*
 * The following are the error codes needed by both the kernel
 * level transport providers and the user level library.
 */

#define	TBADADDR	1	/* incorrect addr format		*/
#define	TBADOPT		2	/* incorrect option format		*/
#define	TACCES		3	/* incorrect permissions		*/
#define	TBADF		4	/* illegal transport fd			*/
#define	TNOADDR		5	/* couldn't allocate addr		*/
#define	TOUTSTATE	6	/* out of state				*/
#define	TBADSEQ		7	/* bad call sequence number		*/
#define TSYSERR		8	/* system error				*/
#define	TLOOK		9	/* event requires attention		*/
#define	TBADDATA	10	/* illegal amount of data		*/
#define	TBUFOVFLW	11	/* buffer not large enough		*/
#define	TFLOW		12	/* flow control				*/
#define	TNODATA		13	/* no data				*/
#define	TNODIS		14	/* discon_ind not found of queue	*/
#define	TNOUDERR	15	/* unitdata error not found		*/
#define	TBADFLAG	16	/* bad flags				*/
#define	TNOREL		17	/* no ord rel found on queue		*/
#define	TNOTSUPPORT	18	/* primitive not supported		*/
#define	TSTATECHNG	19	/* state is in process of changing	*/
#define	TNOSTRUCTYPE	20	/* unsupported struct-type requested	*/
#define TBADNAME	21	/* invalid transport provider name	*/
#define	TBADQLEN	22	/* qlen is zero				*/
#define	TADDRBUSY	23	/* address in use			*/

#if   defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
#define TINDOUT		24	/* outstanding connection indications	*/
#define TPROVMISMATCH	25	/* transport provider mismatch		*/
#define TRESQLEN	26	/* resfd specified to accept w/ qlen>0	*/
#define TRESADDR	27	/* resfd not bound to same addr as fd	*/
#define TQFULL		28	/* incoming connection queue full	*/
#define TPROTO		29	/* XTI protocol error			*/
#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

/*
 * The following are the events returned from t_look()
 */

#define	T_LISTEN	0x0001	/* connection indication received	*/
#define	T_CONNECT	0x0002	/* connect conformation received	*/
#define	T_DATA		0x0004	/* normal data received			*/
#define	T_EXDATA	0x0008	/* expedited data received		*/
#define	T_DISCONNECT	0x0010	/* disconnect received			*/
#define	T_UDERR		0x0040	/* datagram error indication		*/
#define	T_ORDREL	0x0080	/* orderly release indication		*/
#define	T_GODATA	0x0100	/* sending normal data is again possible*/
#define	T_GOEXDATA	0x0200	/* sending expedited data in again possible */
#define	T_EVENTS	0x0400

/*
 * The following are the flag definitions needed by the
 * user level library routines.
 */

#define	T_MORE		0x001	/* more data				*/
#define	T_EXPEDITED	0x002	/* expedited data			*/
#define	T_NEGOTIATE	0x004	/* set opts				*/
#define	T_CHECK		0x008	/* check opts				*/
#define	T_DEFAULT	0x010	/* get default opts			*/
#define T_SUCCESS	0x020	/* successful				*/
#define	T_FAILURE	0x040	/* failure				*/

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
#define T_CURRENT	0x080	/* get current options			*/
#define T_PARTSUCCESS	0x100	/* partial success			*/
#define T_READONLY	0x200	/* read-only				*/
#define T_NOTSUPPORT	0x400	/* not supported			*/
#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

/*
 * Protocol-specific service limits
 */

struct t_info {
	long	addr;		/* max size of transport protocol	*/
				/* address				*/
	long	options;	/* max number of bytes of protocol-	*/
				/* specific options			*/
	long	tsdu;		/* max size of a transport service data */
				/* unit 				*/
	long	etsdu;		/* max size of expedited transport 	*/
				/* service data				*/
	long	connect;	/* max amount of data allowed on	*/
				/* connection establishment functions	*/
	long	discon;		/* max data allowed on t_snddis and	*/
				/* t_rcvdis functions			*/
	long	servtype;	/* service type supported by transport	*/
				/* provider				*/
#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
	long	flags;		/* other info about the transport	*/
				/* provider				*/
#endif /* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */
};

/*
 * Service types defines
 */

#define T_COTS		01	/* Connection-oriented transport	*/
				/* service				*/
#define	T_COTS_ORD	02	/* Connection-oriented with orderly	*/
				/* release				*/
#define	T_CLTS		03	/* Connectionless transport service	*/

/*
 * Flags defines (other info about the transport provider).
 */

#define T_SENDZERO	0x001	/* supports 0-length TSDUs		*/
#define T_XPG4_1        0x100  /* XPG4 and higher */



/*
 * netbuf structure
 */

struct netbuf {
	unsigned int	maxlen;
	unsigned int	len;
	char *		buf;
};

/*
 * t_opthdr structure
 */

struct t_opthdr {
	unsigned long	len;	/* total length of option; i.e.		*/
				/* sizeof(struct t_opthdr) + length of	*/
				/* option value in bytes		*/
	unsigned long	level;	/* protocol value in bytes		*/
	unsigned long	name;	/* option name				*/
	unsigned long	status;	/* status value				*/
	/* followed by the option value(s)				*/
};

/*
 * t_bind - format of the address and options arguments of bind
 */

struct t_bind {
	struct netbuf	addr;
	unsigned	qlen;
};

/*
 * Options management structure
 */

struct t_optmgmt {
	struct netbuf	opt;
	long		flags;
};

/*
 * Disconnect structure
 */

struct t_discon {
	struct netbuf	udata;		/* user data			*/
	int		reason;		/* reason code			*/
	int		sequence;	/* sequence number		*/
};

/*
 * Call structure
 */

struct t_call {
	struct netbuf	addr;		/* address			*/
	struct netbuf	opt;		/* options			*/
	struct netbuf	udata;		/* user data			*/
	int		sequence;	/* sequence number		*/
};

/*
 * Datagram structure
 */

struct t_unitdata {
	struct netbuf	addr;		/* address			*/
	struct netbuf	opt;		/* options			*/
	struct netbuf	udata;		/* user data			*/
};

/*
 * Unitdata error structure
 */

struct t_uderr {
	struct netbuf	addr;		/* address			*/
	struct netbuf	opt;		/* options			*/
	long		error;		/* error code			*/
};

/*
 * The following are structure types used when dynamically
 * allocating the above structure via alloc().
 */

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)

#define	T_BIND		1	/* struct t_bind			*/
#define T_OPTMGMT	2	/* struct t_optmgmt			*/
#define	T_CALL		3	/* struct t_call			*/
#define	T_DIS		4	/* struct t_discon			*/
#define	T_UNITDATA	5	/* struct t_unitdata			*/
#define	T_UDERROR	6	/* struct t_uderr			*/
#define	T_INFO		7	/* struct t_info			*/

#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

#define	T_BIND_STR	1	/* struct t_bind			*/
#define T_OPTMGMT_STR	2	/* struct t_optmgmt			*/
#define	T_CALL_STR	3	/* struct t_call			*/
#define	T_DIS_STR	4	/* struct t_discon			*/
#define	T_UNITDATA_STR	5	/* struct t_unitdata			*/
#define	T_UDERROR_STR	6	/* struct t_uderr			*/
#define	T_INFO_STR	7	/* struct t_info			*/


/*
 * The following bits specify which fields of the above
 * structures should be allocated by t_alloc().
 */

#define	T_ADDR		0x01	/* address				*/
#define	T_OPT		0x02	/* options				*/
#define	T_UDATA		0x04	/* user data				*/
#define	T_ALL		0xffff	/* all the above fields supported	*/

/*
 * The following are the states for the user.
 */

#define T_UNINIT	0	/* uninitialized state			*/
#define	T_UNBND		1	/* unbound				*/
#define	T_IDLE		2	/* idle					*/
#define	T_OUTCON	3	/* outgoing connection pending		*/
#define	T_INCON		4	/* incoming connection pending		*/
#define	T_DATAXFER	5	/* data transfer			*/
#define	T_OUTREL	6	/* outgoing orderly release		*/
#define	T_INREL		7	/* incoming orderly release		*/

/* General purpose defines */

#define	T_YES		1
#define	T_NO		0
#define	T_UNUSED	(-1)
#define	T_NULL		0
#define	T_ABSREQ	0x8000

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
#define T_INFINITE	(-1)	/* values for t_info			*/
#define T_INVALID	(-2)	/* values for t_info			*/

/*
 * General definitions for option management
 */

#define T_UNSPEC	(~0-2)	/* applicable to u_long, long, char,..	*/
#define T_ALLOPT	0

#define T_ALIGN(p)	(((unsigned long)(p) + sizeof (long) - 1) \
					       & ~(sizeof (long) - 1))
#define OPT_NEXTHDR(pbuf, buflen, popt)	\
			(struct t_opthdr *) \
			 (((char *)(popt) + T_ALIGN((popt)->len) <  \
				(char *)(pbuf) + (buflen)) ? \
			 ((char *)(popt) + T_ALIGN((popt)->len)) : \
			 0)

/*
 * XTI-level Options
 */

#define XTI_GENERIC	0xffff

#define XTI_DEBUG	0x0001	/* enable debugging			*/
#define XTI_LINGER	0x0080	/* linger on close if data present	*/
#define XTI_RCVBUF	0x1002	/* receive buffer size			*/
#define XTI_RCVLOWAT	0x1004	/* receive low-water mark		*/
#define XTI_SNDBUF	0x1001	/* send buffer size			*/
#define XTI_SNDLOWAT	0x1003	/* send low-water mark			*/

/*
 * Structure used with linger option
 */

struct t_linger {
	long	l_onoff;	/* option on/off			*/
	long	l_linger;	/* linger time				*/
};
#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */


	/* SPECIFIC ISO OPTIONS AND MANAGEMENT PARAMETERS */

/* Definition of the ISO transport classes */

#define	T_CLASS0	0
#define	T_CLASS1	1
#define	T_CLASS2	2
#define	T_CLASS3	3
#define	T_CLASS4	4

/* Definition of the priorities */

#define	T_PRITOP	0
#define	T_PRIHIGH	1
#define	T_PRIMID	2
#define	T_PRILOW	3
#define	T_PRIDFLT	4

/* Definition of the protection levels */

#define	T_NOPROTECT		1
#define	T_PASSIVEPROTECT	2
#define	T_ACTIVEPROTECT		4

/* Default value for the length of TPDU's */

#define	T_LTPDUDFLT	128

/* 
 * rate structure
 */

struct rate {
	long	targetvalue;	/* target value				*/
	long	minacceptvalue;	/* value of minimum acceptable quality	*/
};

/*
 * reqvalue structure
 */

struct reqvalue {
	struct rate	called;		/* called rate			*/
	struct rate	calling;	/* calling rate			*/
};

/*
 * throughput structure
 */

struct thrpt {
	struct reqvalue	maxthrpt;	/* maximum throughput		*/
	struct reqvalue	avgthrpt;	/* average throughput		*/
};

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
/*
 * transdel structure
 */

struct transdel {
	struct reqvalue	maxdel;		/* maximum transist delay	*/
	struct reqvalue	avgdel;		/* average transist delay	*/
};

/*
 * Protocol Levels
 */

#define ISO_TP	0x0100

/*
 * Options for Quality of Service and Expedited Data (ISO 8072:1986)
 */

#define TCO_THROUGHPUT		0x0001
#define TCO_TRANSDEL		0x0002
#define TCO_RESERRORRATE	0x0003
#define TCO_TRANSFFAILPROB	0x0004
#define TCO_ESTFAILPROB		0x0005
#define TCO_RELFAILPROB		0x0006
#define TCO_ESTDELAY		0x0007
#define TCO_RELDELAY		0x0008
#define TCO_CONNRESIL		0x0009
#define TCO_PROTECTION		0x000a
#define TCO_PRIORITY		0x000b
#define TCO_EXPD		0x000c

#define TCL_TRANSDEL		0x000d
#define TCL_RESERRORRATE	TCO_RESERRORRATE
#define TCL_PROTECTION		TCO_PROTECTION
#define TCL_PRIORITY		TCO_PRIORITY

/*
 * Management Options
 */

#define TCO_LTPDU		0x0100
#define TCO_ACKTIME		0x0200
#define TCO_REASTIME		0x0300
#define TCO_EXTFORM		0x0400
#define TCO_FLOWCTRL		0x0500
#define TCO_CHECKSUM		0x0600
#define TCO_NETEXP		0x0700
#define TCO_NETRECPTCF		0x0800
#define TCO_PREFCLASS		0x0900
#define TCO_ALTCLASS1		0x0a00
#define TCO_ALTCLASS2		0x0b00
#define TCO_ALTCLASS3		0x0c00
#define TCO_ALTCLASS4		0x0d00

#define TCL_CHECKSUM		TCO_CHECKSUM
	
		/* INTERNET SPECIFIC ENVIRONMENT */

/*
 * TCP Level
 */

#define INET_TCP	0x6

/*
 * TCP-level Options
 *
 * First two names collide with netinet/tcp.h - values must be equivalent.
 */

#define TCP_NODELAY	0x1	/* don't delay packets to coalesce	*/
#define TCP_MAXSEG	0x2	/* get maximum segment size		*/
#define TCP_KEEPALIVE	8	/* check, if connections are alive	*/

/*
 * Structure used with TCP_KEEPALIVE option.
 */

struct t_kpalive {
	long	kp_onoff;	/* option on/off			*/
	long	kp_timeout;	/* timeout in minutes			*/
};

#define T_GARBAGE	0x02

/*
 * UDP level
 */

#define INET_UDP	0x11

/*
 * UDP-level Options
 */

#define UDP_CHECKSUM	TCO_CHECKSUM	/* checksum computation		*/

/*
 * IP level
 */

#define INET_IP		0x0

/*
 * IP-level Options
 *
 * First three names collide with netinet/in.h - values must be equivalent.
 */

#define IP_OPTIONS	1	/* IP per-packet options		*/
#define IP_TOS		3	/* IP per-packet type of service	*/
#define IP_TTL		4	/* IP per-packet time to live		*/
#define IP_REUSEADDR	16	/* allow local address reuse		*/
#define IP_DONTROUTE	17	/* just use interface addresses		*/
#define IP_BROADCAST	18	/* permit sending of broadcast msgs	*/

#else	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */
/*
 * management structure
 */

struct management {
	short	dflt;		/* T_YES: the following parameters	*/
				/* are ignored, default vales are used;	*/
				/* T_NO: the following parameters	*/
				/* are used				*/
	int	ltpdu;		/* maximum length of TPDU (in octets)	*/
	short	reastime;	/* reassignment time (in seconds)	*/
#ifndef __cplusplus
	char	class;		/* preferred class;			*/
				/* value: T_CLASS - TCLASS4		*/
#else
	char	tclass;		/* "class" is reserved word in C++	*/
#endif
	char	altclass;	/* alternative class			*/
	char	extform;	/* extended format: T_YES or T_NO	*/
	char	flowctrl;	/* flow control: T_YES or T_NO		*/
	char	checksum;	/* checksum (cl. 4): T_YES or T_NO	*/
	char	netexp;		/* network expedited data: T_YES or T_NO*/
	char	netrecptcf;	/* receipt confirmation: T_YES or T_NO	*/ 
};

/*
 * ISO connection-oriented options
 */

struct isoco_options {
	struct thrpt	throughput;	/* throughput			*/
	struct reqvalue	transdel;	/* transit delay		*/
	struct rate	reserrorrate;	/* residual error rate		*/
	struct rate	transffailprob;	/* transfer failure problem	*/
	struct rate	estfailprob;	/* connection establishment failure */
	struct rate	relfailprob;	/* connection release failure	*/
	struct rate	estdelay;	/* connection establishment delay */
	struct rate	reldelay;	/* connection release delay	*/
	struct netbuf	connresil;	/* connection resilience	*/
	unsigned short	protection;	/* protection			*/
	short		priority;	/* priority			*/
	struct management mngmt;	/* management parameters	*/
	char		expd;		/* expedited data: T_YES or T_NO*/
};

/*
 * ISO connectionless options
 */

struct isocl_options {
	struct rate	transdel;	/* transit delay		*/
	struct rate	reserrorrate;	/* residual error rate		*/
	unsigned short	protection;	/* protection			*/
	short		priority;	/* priority			*/
};

#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

/*
 * IP_TOS precedence levels
 */

#define	T_ROUTINE	0
#define	T_PRIORITY	1
#define	T_IMMEDIATE	2
#define	T_FLASH		3
#define	T_OVERRIDEFLASH	4
#define	T_CRITIC_ECP	5
#define	T_INETCONTROL	6
#define	T_NETCONTROL	7

#if defined(_XOPEN_SOURCE) && !defined(XTI_XPG3)
/*
 * IP_TOS type of service
 */

#define T_NOTOS		0
#define T_LDELAY	(1 << 4)
#define T_HITHRPT	(1 << 3)
#define T_HIREL		(1 << 2)

#define SET_TOS(prec, tos)	(((prec) & 0x7) << 5 | ((tos) & 0x1c))

#else	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */

/*
 * TCP security options structure
 */

struct secoptions {
	short	security;	/* security fiedl			*/
	short	compartment;	/* compartment				*/
	short	handling;	/* handling restrictions		*/
	long	tcc;		/* transmission control code		*/
};

/*
 * TCP options
 */

struct tcp_options {
	short		precedence;	/* precedence			*/
	long		timeout;	/* abort timeout		*/
	long		max_seg_size;	/* maximum segment size		*/
	struct secoptions secopt;	/* TCP security options		*/
};
#endif	/* defined(_XOPEN_SOURCE) && !defined(XTI_XPG3) */


#ifndef	_KERNEL

/* 
 * XTI error return
 */

extern	int	*_terrno();
#define t_errno (*_terrno())
extern	char *	t_errlist[];
extern	int	t_nerr;


extern	int	t_accept __((int, int, struct t_call *));
extern	char *	t_alloc __((int, int, int));
extern	int	t_bind __((int, struct t_bind *, struct t_bind *));
extern	int	t_blocking __((int));
extern	int	t_close __((int));
extern	int	t_connect __((int, struct t_call *,struct t_call *));
extern	int	t_error __((char *));
extern	int	t_free __((char *, int));
extern	int	t_getinfo __((int, struct t_info *));
extern	int	t_getprotaddr __((int, struct t_bind *, struct t_bind *));
extern	int	t_getstate __((int));
extern	int	t_listen __((int, struct t_call *));
extern	int	t_look __((int));
extern	int	t_nonblocking __((int));
extern	int	t_open __((char *, int, struct t_info *));
extern	int	t_optmgmt __((int, struct t_optmgmt *, struct t_optmgmt *));
extern	int	t_rcv __((int, char *, unsigned, int *));
extern	int	t_rcvconnect __((int, struct t_call *));
extern	int	t_rcvdis __((int, struct t_discon *));
extern	int	t_rcvrel __((int));
extern	int	t_rcvudata __((int, struct t_unitdata *, int *));
extern	int	t_rcvuderr __((int, struct t_uderr *));
extern	int	t_snd __((int, char *, unsigned, int));
extern	int	t_snddis __((int, struct t_call *));
extern	int	t_sndrel __((int));
extern	int	t_sndudata __((int, struct t_unitdata *));
extern	char *	t_strerror __((int));
extern	int	t_sync __((int));
extern	int	t_unbind __((int));
#endif  /* !_KERNEL */

#ifdef __cplusplus
}
#endif
#endif
