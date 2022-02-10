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
 * @(#)$RCSfile: bootio_net.h,v $ $Revision: 1.1.2.5 $ (DEC) $Date: 1995/10/18 14:22:50 $
 */

/*
 * Minimal IP header for use with bootp and tftp
 * see RFC
 */
typedef struct{
  unsigned char ip_hl : 4;		/* Header Length */         
  unsigned char ip_v  : 4;		/* Version */               
  unsigned char ip_tos;			/* Type of service */       
  short ip_len;  			/* Total length */          
  unsigned short ip_id;			/* Identification */        
  short  ip_off;	         	/* Fragment offset field */ 
  unsigned char ip_ttl;			/* Time to live */          
  unsigned char ip_p;			/* Protocol */              
  unsigned short ip_sum;		/* Checksum */              
  unsigned int   ip_src;		/* IP source address */     
  unsigned int   ip_dst;		/* IP destination address */
} ip_hdr_t;

#define DODIP_PROTOCOL 0x0800
#define ARP_PROTOCOL   0x0806
#define IP_DF 0x4000		/* Don't fragment flag */
#define IP_MF 0x2000		/* More fragments flag */
#define IP_FRAGS 0x3fff         /* frag offset | more frags */
#define IPVERSION 4
#define STDTTL 32               /* recommended value; see RFC 1060 p 23 */

#define IP_UDP_PROTOCOL 17
#define IP_ICMP_PROTOCOL 1
#define INADDR_BROADCAST -1

#define TFTP_DEF_TRIES 3        /* try for about 12 seconds */
#define BOOTP_DEF_TRIES 3       /* try for about 12 seconds */
#define ARP_DEF_TRIES 3         /* try for about 12 seconds */

/*
 * Ethernet / [FDDI / Token-Ring (encapsulated ethernet)] header.
 */
typedef struct {
  unsigned char dst[6];
  unsigned char src[6];
  unsigned short protocol;
} eth_hdr_t;

/*
 * UDP header
 */
typedef struct {
  unsigned short udp_sport;	/* Source port */
  unsigned short udp_dport;	/* Destination port */
  unsigned short udp_len;	/* UDP length */
  unsigned short udp_sum;	/* UDP checksum */
} udp_hdr_t;

/*
 * UDP pseudo-header
 */
typedef union {
  struct {
    int src_iaddr;
    int dst_iaddr;
    char zero;
    char proto;
    unsigned short len;
  } st;
  unsigned short shorts[6];
} udp_pseudo_hdr_t;

/*
 * packet format for bootp
 * see RFC 951
 */
typedef struct {
  char op;		/*   1 byte   --  1=BOOTREQUEST, 2=BOOTREPLY */
  char htype;		/*   1 byte   --  hardware address type; see ARP */
			                /* section in assigned numbers */
  char hlen;		/*   1 byte   --  hardware address length */
  char hops;		/*   1 byte   --  client=0; used by gateways */
  int xid;		/*   4 bytes  --  transaction id (random number) */
  short secs;		/*   2 bytes  --  secs since client started booting */
  short unused;		/*   2 bytes */
  int ciaddr;		/*   4 bytes  --  client IP address */
  int yiaddr;		/*   4 bytes  --  'your' (client) address */
  int siaddr;		/*   4 bytes  --  server IP address */
  int giaddr;		/*   4 bytes  --  gateway IP address */
  char chaddr[16];	/*  16 bytes  --  client hardware address */
  char sname[64];	/*  64 bytes  --  server host name (null term str)*/
  char file[128];	/* 128 bytes  --  boot file name (null term str) */
  char vend[64];	/*  64 bytes  --  vendor specific options */
} bootp_pkt_t;

#define BOOTPREQUEST	1
#define BOOTPREPLY	2
#define HTYPE_ETHER10	1
#define HLEN_ETHER10 	6
#define HTYPE_IEEE8025	6		/* Token Ring: IEEE 802.5 */
#define PLEN_DODIP	4

/*
 * bootp vendor specific data - see  RFC 1533
 * This list is not complete.
 */
#define SUBNET_MASK     1
#define ROUTER_OPTION   3
#define ROOT_PATH       17
#define END_OPT         255

#define MAXBPROUTER     4

#define TFTPRRQ   1
#define TFTPWRQ   2
#define TFTPDATA  3
#define TFTPACK   4
#define TFTPERROR 5

#define ARP_REQUEST   1
#define ARP_RESPONSE  2
#define RARP_REQUEST  3
#define RARP_RESPONSE 4

#define BOOTPSERVER 67          /* well known port numbers - RFC 1060 p 10 */
#define BOOTPCLIENT 68
#define TFTPSERVER 69

#define htons(x) ((((x)<<8)&0xff00)|(((x)>>8)&0xff))
#define htonl(x) ((((x)<<24)&0xff000000)|\
                 (((x)<< 8)&0x00ff0000)|\
                 (((x)>> 8)&0x0000ff00)|\
                 (((x)>>24)&0x000000ff))
#define ntohs(x) htons(x)
#define ntohl(x) htonl(x)

/*
 * tftp per-request information
 * one of these for each open tftp
 */
typedef struct tftp_struct {
  int direction;                  /* read == 1, write = 2 */
  unsigned short xid;             /* unique trans id, also local udp port */
  unsigned short rem_port;        /* remote udp port */
  int rem_iaddr;                  /* ip addr we're talking to */
  int block;                      /* current block number */
  char *base;                     /* next byte in buffer packet */
  char *offset;                   /* next byte in buffer packet */
  int remain;                     /* bytes remaining in buffer packet */
  int last;                       /* TRUE if pkt is last (had < 512 bytes) */
  int error;                      /* tftp error code + 1 on error; o/w 0 */
  int tries;                      /* number of attempts to transmit packets */
  unsigned int reads;		  /* number of reads done */
} tftp_t;

typedef struct {
  unsigned short op;
  unsigned short param;
} tftp_hdr_t;

typedef struct {
  unsigned short op;
  unsigned short block;
} tftp_ack_t;
  
typedef struct {
  int valid;
  int iaddr;
  char haddr[16];
} arp_cache_t;

/*
 * arp packets - hardwired for ethernet
 */
typedef struct {
  unsigned short	ar_hrd;		/* format of hardware address */
  unsigned short	ar_pro;		/* format of protocol address */
  unsigned char	ar_hln;			/* length of hardware address */
  unsigned char	ar_pln;			/* length of protocol address */
  unsigned short	ar_op;		/* one of: */
/*
 * The remaining fields are variable in size,
 * according to the sizes above.
 */
/*  unsigned char	ar_sha[];	   sender hardware address */
/*  unsigned char	ar_spa[];	   sender protocol address */
/*  unsigned char	ar_tha[];	   target hardware address */
/*  unsigned char	ar_tpa[];	   target protocol address */
  unsigned char		address[20];
} arp_pkt_t;

/* For indexing into arbitrary ha/pa ARP headers */
#define AR_SHA(ah)	((u_char *)((ah)->address))
#define AR_SPA(ah)	(AR_SHA(ah)+(ah)->ar_hln)
#define AR_THA(ah)	(AR_SPA(ah)+(ah)->ar_pln)
#define AR_TPA(ah)	(AR_THA(ah)+(ah)->ar_hln)

/*
 * iovec for passing data buffers
 */

#define MAX_IOVEC 6
typedef struct {
  void *iov_base;
  int iov_len;
} iovec_t;

/*
 * Network hardware adapter types.
 */
#define HW_ETHERNET	'1'
#define HW_FDDI		'2'
#define HW_TOKEN_RING	'3'
