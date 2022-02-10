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
 * @(#)$RCSfile: latioc.h,v $ $Revision: 1.1.6.6 $ (DEC) $Date: 1995/09/07 16:24:02 $
 */
/* @(#)latioc.h 1.1 11/23/92 MTC_SRC; from MTC 6.3 11/20/92 */
/*----------------------------------------------------------------------
    latioc		(h) LAT STREAMS multiplexing controls

    This Software and Related Documentation are Proprietary to
    Meridian Technology Corporation.

    Copyright 1992 Meridian Technology Corporation, St. Louis, MO
    Unpublished -
    All Rights Reserved Under the Copyright Laws of the United States.

    Restricted Rights Legend:  Use, Duplication, or Disclosure by
    the Government is Subject to Restrictions as Set Forth in
    Paragraph (c)(1)(ii) of the Rights in Technical Data and
	Computer Software Clause at DFARS 252.227-7013.  Meridian
	Technology Corporation.
 -----------------------------------------------------------------------*/

#ifndef	LATIOC_H
#define	LATIOC_H	0	/* Indicate file has been read	 */


#include <lat/streams/latsys.h>

/*----------------------------------------------------------------------
    Define maximum name lengths as length+1. Note, these may not be
    changed without corresponding change to LAT multiplexor sources.
 -----------------------------------------------------------------------*/
#define	NA_MAX		17	/* Maximum name  length		 */
#define	ID_MAX		65	/* Maximum ident length		 */

/*----------------------------------------------------------------------
    Define the T_BIND address structures. Four different bindings
    are possible:

	1) NULL     - Outbound connection endpoint. A default object created
		      by LAT stream.
		
	2) L_CLIENT - Outbound connection endpoint, object specified in the
		      L_client structure.
		.
	3) L_SERVER - Inbound  connection endpoint for the named service
		      in L_service structure. A default object created by
		      LAT stream. LAT stream puts no limit on number of
		      incoming connections.
		
	4) L_OBJECT - Inbound  connection endpoint, with port name. One
    		      connection is allowed at a time.
 -----------------------------------------------------------------------*/
#define	L_CLIENT	2	/* Outbound connection endpoint	 */
#define L_SERVER	3	/* Inbound  connection endpoint	 */
#define	L_OBJECT	4	/* Inbound with objects		 */

typedef struct {
	int             BIND_type;	/* Type of address binding	 */
	char            BIND_port[NA_MAX];	/* External port name		 */
}               L_client;

typedef struct {
	int             BIND_type;	/* Type of address binding	 */
	int             BIND_rating;	/* Service rating		 */
	char            BIND_service[NA_MAX];	/* Service offering		 */
	char            BIND_ident[ID_MAX];	/* Service identification	 */
	char            BIND_password[NA_MAX];	/* Service password		 */
}               L_server;

typedef struct {
	int             BIND_type;	/* Type of address binding	 */
	int             BIND_rating;	/* Service rating		 */
	char            BIND_service[NA_MAX];	/* Service offering		 */
	char            BIND_ident[ID_MAX];	/* Service identification	 */
	char            BIND_password[NA_MAX];	/* Service password		 */
	int             BIND_queue;	/* Requests may be queued	 */
	char            BIND_port[NA_MAX];	/* External port name		 */
}               L_object;

typedef union {
	int             type;	/* Type of address binding	 */
	L_client        client;	/* Client			 */
	L_server        srver;	/* Server			 */
	L_object        object;	/* Object			 */
}               L_bind;

/*----------------------------------------------------------------------
    Define the LAT connect/listen data buffer.
 -----------------------------------------------------------------------*/
#define	L_SESSION	1	/* Standard session connect	 */
#define L_HIC		2	/* Host-initiated connection	 */

typedef struct {
	int             CONN_type;	/* Connect type			 */
	char            CONN_service[NA_MAX];	/* Service name			 */
	char            CONN_port[NA_MAX];	/* Remote port name		 */
	char            CONN_node[NA_MAX];	/* Remote node name		 */
	char            CONN_password[NA_MAX];	/* Service password		 */
}               L_connect;

/*----------------------------------------------------------------------
    Define the LAT stream I/O controls.
 -----------------------------------------------------------------------*/
#define	LIOC		('L'<<8)/* LAT I/O control		 */
#define LIOC_FNC	0x00ff	/* Function number		 */

/*----------------------------------------------------------------------
    Define the local host functions.
 -----------------------------------------------------------------------*/
#define	LIOC_HS_INIT	(LIOC | 1)	/* Initialize LAT stream	 */
#define	LIOC_HS_KILL	(LIOC | 2)	/* Shutdown   LAT stream	 */
#define	LIOC_HS_SET	(LIOC | 3)	/* Set  LAT stream parameters	 */
#define	LIOC_HS_SHOW	(LIOC | 4)	/* Show LAT stream parameters	 */

typedef struct {
	char            hs_node[NA_MAX];	/* Local node name  string	 */
	char            hs_ident[ID_MAX];	/* Local node ident string 	 */
	int		hs_enabled;	/* State of LAT (on/off) (read-only) */
	int             hs_ether_type;	/* Type of Ethernet		 */
	int             hs_multi_on;	/* Multicast enabled		 */

	int             hs_le_nd_retain;/* Retain remote nodes		 */
	int             hs_le_ls_dups;	/* Allow duplicate names	 */
	int             hs_ls_agent;	/* LAT 5.2 agent enabled	 */

	int             hs_hertz;	/* Local clock ticks		 */
	int             hs_tu_msec_tic;	/* Milliseconds/tic		 */
	int             hs_tu_secs_toc;	/* Seconds/toc			 */

	int             hs_credits;	/* Credits for each session	 */

	uint8           hs_host_addr[6];/* Local host address		 */
	uint8           hs_multicast[6];/* LAT multicast address	 */
	uint8           hs_slave_mc[6];	/* LAT slave mc address		 */
	uint16          hs_ptype;	/* Ethernet protocol number	 */
	uint8           hs_prot_hi;	/* LAT protocol, high version	 */
	uint8           hs_prot_lo;	/* LAT protocol, low  version	 */
	uint8           hs_prot_ver;	/* LAT protocol version		 */
	uint8           hs_prot_eco;	/* LAT protocol ECO		 */
	uint16          hs_facility;	/* Facility number		 */
	uint8           hs_prod_code;	/* Product code			 */
	uint8           hs_prod_ver;	/* Product version		 */

	int             hs_cb_maximum;	/* Maximum number of circuits	 */
	int             hs_sb_maximum;	/* Maximum number of sessions	 */
	int             hs_as_maximum;	/* Maximum advertised services	 */
	int             hs_ls_maximum;	/* Maximum learned services	 */
	int             hs_nd_maximum;	/* Maximum remote nodes		 */
	int             hs_hi_maximum;	/* Maximum HIC requests		 */
	int             hs_ob_maximum;	/* Maximum # objects		 */
	int             hs_qr_maximum;	/* Maximum # queue entries	 */

	int             hs_cb_current;	/* Current number of circuits	 */
	int             hs_sb_current;	/* Current number of sessions	 */
	int             hs_as_current;	/* Current advertised services	 */
	int             hs_ls_current;	/* Current learned services	 */
	int             hs_nd_current;	/* Current remote nodes		 */
	int             hs_hi_current;	/* Current HIC request		 */
	int             hs_ob_current;	/* Current # objects		 */
	int             hs_qr_current;	/* Current # queue entries	 */

	int             hs_cb_highest;	/* Highest number of circuits	 */
	int             hs_sb_highest;	/* Highest number of sessions	 */
	int             hs_as_highest;	/* Highest advertised services	 */
	int             hs_ls_highest;	/* Highest learned services	 */
	int             hs_nd_highest;	/* Highest remote nodes		 */
	int             hs_hi_highest;	/* Highest HIC request		 */
	int             hs_ob_highest;	/* Highest # objects		 */
	int             hs_qr_highest;	/* Highest # queue entries	 */

	uint16          hs_dll_max;	/* Maximum datalink output size	 */
	uint16          hs_inp_max;	/* Maximum datalink input  size	 */
	uint16          hs_status;	/* Current host status		 */

	uint8           hs_cb_max_ses;	/* Maximum sessions/circuit	 */
	uint8           hs_cb_s_rcv_extra;	/* Maximum extra receives (S)	 */
	uint8           hs_cb_h_rcv_extra;	/* Maximum extra receives (H)	 */
	uint8           hs_cb_retries;	/* Default circuit retries	 */
	uint8           hs_cb_vc_timer;	/* Default circuit timer   (ms)	 */
	uint8           hs_cb_hd_timer;	/* Default host delay      (ms)	 */
	uint8           hs_cb_ka_timer;	/* Default keep-alive timer (s)	 */
	uint8           hs_cb_progress;	/* Host progress interval   (s) */

	uint8           hs_sb_max_data;	/* Maximum data slot size	 */
	uint8           hs_sb_max_attn;	/* Maximum attention slot size	 */

	uint16          hs_hi_sts_timer;	/* HIC status  timer (s)	 */
	uint16          hs_hi_cmd_timer;	/* HIC command timer (h)	 */
	uint16          hs_hi_cmd_retries;	/* HIC command retries		 */

	uint8           hs_as_timer;	/* Current AS multicast timer	 */

	int             hs_nd_age_max;	/* Maximum remote node age	 */
	int             hs_nd_interval;	/* Interval to purge nodes	 */

    uint8           hs_ser_no[8];
    uint8           hs_key[13];

}               lats_hs;

/*----------------------------------------------------------------------
    Define the host counter functions.
 -----------------------------------------------------------------------*/
#define	LIOC_CO_COUNT	(LIOC | 5)	/* Get LAT host counters	 */
#define	LIOC_CO_STATS	(LIOC | 6)	/* Get LAT host statistics	 */
#define LIOC_CO_ERROR   (LIOC | 7)	/* Get LAT protocol errors	 */
#define	LIOC_CO_ZERO	(LIOC | 8)	/* Zero LAT host counts/stats	 */

typedef struct {
	uint32          co_seconds;	/* Seconds since zeroed		 */
	uint32          co_msgs_recv;	/* Total run messages received	 */
	uint32          co_msgs_xmit;	/* Total run messages transmit	 */
	uint32          co_slot_recv;	/* Total slots received		 */
	uint32          co_slot_xmit;	/* Total slots transmitted	 */
	uint32          co_byte_recv;	/* Total bytes received		 */
	uint32          co_byte_xmit;	/* Total bytes transmitted	 */
	uint32          co_duplicates;	/* Total duplicate messages	 */
	uint32          co_fwd_seq;	/* Total fwd. out of seq. msgs.  */
	uint32          co_retransmit;	/* Total retransmitted messages	 */
	uint32          co_msgs_bad;	/* Total bad circuit messages	 */
	uint32          co_slot_bad;	/* Total bad circuit slots	 */
	uint32          co_solicit_accept;	/* Total accepted
						 * host-initiate	 */
	uint32          co_solicit_reject;	/* Total rejected
						 * host-initiate	 */
	uint32          co_multiple_node;	/* Total multiple nodes seen	 */
}               lats_count;

typedef struct {
	uint32          ch_total_circuits;	/* Total circuits created	 */
	uint32          ch_total_sessions;	/* Total sessions created	 */
	uint32          ch_total_recv;	/* Total frames received	 */
	uint32          ch_total_xmit;	/* Total frames transmited	 */
	uint32          ch_total_illegal;	/* Total illegal frames		 */
	uint32          ch_total_timeouts;	/* Total circuit timeouts	 */
	uint32          ch_svc_xmit;	/* Total service messages xmit.	 */
	uint32          ch_svc_recv;	/* Total service messages recv.	 */
	uint32          ch_svc_used;	/* Total service messages used	 */
}               lats_stats;

typedef struct {
	uint16          ch_err_masks[9];	/* Message error masks		 */
	int             ch_err_type;	/* Last error type		 */
	int             ch_err_size;	/* Size of error message	 */
	uint8           ch_err_source[6];	/* Last error source address	 */
	uint8           ch_err_frame[128];	/* First 128 bytes of message	 */
}               lats_error;

/*-----------------------------------------------------------------------
    Define ch_err_masks indexes.
 -----------------------------------------------------------------------*/
#define E_MSG_OTHER	0	/* Other errors			 */
#define E_CIR_S_ERROR	1	/* Circuit start message	 */
#define E_CIR_R_ERROR	2	/* Circuit run   message	 */
#define E_CIR_H_ERROR	3	/* Circuit halt  message	 */
#define E_SVC_A_ERROR	4	/* Service annoucement message	 */
#define E_HIC_SI_ERROR	5	/* HIC solicit message 		 */
#define E_HIC_RI_ERROR	6	/* HIC reponse message		 */
#define E_HIC_CMD_ERROR	7	/* HIC command message 		 */
#define E_HIC_STS_ERROR	8	/* HIC status  message		 */

/*-----------------------------------------------------------------------
    Define ch_err_masks generic message field errors.
 -----------------------------------------------------------------------*/
#define	E_MSG_LENGTH	0x0001	/* Illegal message length	 */
#define E_FIELD_SLOTS	0x0002	/* Illegal # slots		 */
#define E_FIELD_CIR_ID	0x0004	/* Illegal circuit ID		 */
#define E_FIELD_GROUP	0x0008	/* Illegal group field		 */
#define E_FIELD_NODE	0x0010	/* Illegal node name		 */
#define E_FIELD_SERVICE	0x0020	/* Illegal service name		 */
#define E_FIELD_PORT	0x0040	/* Illegal port name		 */
#define E_FIELD_CLASS	0x0080	/* Illegal service class	 */

/*-----------------------------------------------------------------------
    Define errors specific to MSG_OTHER.
 -----------------------------------------------------------------------*/
#define E_FIELD_TYPE	0x8000	/* Illegal message type		 */

/*-----------------------------------------------------------------------
    Define errors specific to CIR_S_ERROR.
 -----------------------------------------------------------------------*/
#define E_FIELD_VC_TIMER 0x8000	/* Illegal circuit timer	 */

/*-----------------------------------------------------------------------
    Define errors specific to CIR_R_ERROR
 -----------------------------------------------------------------------*/
#define E_SLOT_TYPE	0x8000	/* Illegal slot, slot type	 */
#define E_SLOT_DST_ID	0x4000	/* Illegal slot, destination	 */
#define E_SLOT_SRC_ID	0x2000	/* Illegal slot, source		 */
#define E_SLOT_CREDITS	0x1000	/* Illegal slot, no credit	 */

/*----------------------------------------------------------------------
    Define the advertised service functions.
 -----------------------------------------------------------------------*/
#define	LIOC_AS_CREATE	 (LIOC | 9)	/* Create advertised service	 */
#define	LIOC_AS_MODIFY	 (LIOC | 10)	/* Modify advertised service	 */
#define	LIOC_AS_DELETE	 (LIOC | 11)	/* Delete advertised service	 */
#define	LIOC_AS_RESET	 (LIOC | 12)	/* Delete all services		 */
#define	LIOC_AS_SHOW	 (LIOC | 13)	/* Show named service		 */
#define	LIOC_AS_LIST	 (LIOC | 14)	/* List next  service		 */

#define LIOC_AS_SET_PORT   (LIOC | 15)	/* Set   port mapping		 */
#define LIOC_AS_CLEAR_PORT (LIOC | 16)	/* Clear port mapping		 */
#define LIOC_AS_SHOW_PORT  (LIOC | 17)	/* Return port mapping(s)	 */

typedef struct {
	uint8           groups[GP_STR];	/* Group bit mask		 */
}               lats_groups;

typedef struct {
	char            as_service[NA_MAX];	/* Service name  string		 */
	char            as_ident[ID_MAX];	/* Service ident string		 */
	char            as_password[NA_MAX];	/* Password string		 */
	uint8           as_flags;	/* Service flag mask		 */
	uint8           as_rating;	/* Static service rating	 */
	uint8		as_type;	/* Service type			 */
#define INFO_AS_TYPE_UBIS	0x0024	/* Unbound Interactive Service 	 */
#define INFO_AS_TYPE_BIS	0x0025	/* Bound Interactive Service 	 */
#define INFO_AS_TYPE_DOS	0x0026	/* Dedicated/Optional Service 	 */
        lats_groups	as_groups;	/* Service groups		 */
}               lats_as;

typedef struct {
	char            as_service[NA_MAX];	/* Service name  string		 */
	int             as_port;/* Port definitions		 */
}               lats_as_port;

typedef struct {
	int             as_value;	/* Rating, # users		 */
}               lats_as_rate;

#define AS_OFFERED	0x01	/* Service is multicast		 */
#define AS_DYNAMIC	0x02	/* Service has a dynamic rating	 */
#define AS_CLIENT	0x04	/* Dynamic rating from client	 */
#define AS_ENABLED	0x20	/* Service connections enabled	 */
#define AS_QUEUED	0x40	/* Service can be queued	 */
#define AS_FLAGS	(AS_OFFERED | AS_DYNAMIC | AS_CLIENT | AS_ENABLED | AS_QUEUED)

#define AS_RATING	255	/* Maximum rating allowed       */

/*----------------------------------------------------------------------
    Define the learned service functions.
 -----------------------------------------------------------------------*/
#define	LIOC_LS_CREATE	 (LIOC | 18)	/* Create learned service	 */
#define	LIOC_LS_DELETE	 (LIOC | 19)	/* Delete learned service	 */
#define	LIOC_LS_RESET	 (LIOC | 20)	/* Delete all services		 */
#define	LIOC_LS_SHOW	 (LIOC | 21)	/* Show named service		 */
#define	LIOC_LS_LIST	 (LIOC | 22)	/* List next  service		 */
#define	LIOC_LS_SCAN	 (LIOC | 23)	/* Scan next  service		 */

typedef struct {
	char            ls_service[NA_MAX];	/* Service name  string		 */
	char            ls_ident[ID_MAX];	/* Service ident string		 */
	char            ls_node[NA_MAX];	/* Node offering service	 */
	uint8           ls_dest[6];	/* Node ethernet address	 */
	uint16          ls_flags;	/* Service flags		 */
	uint8           ls_rating;	/* Service rating		 */
	uint8           ls_seq;	/* Sequence number		 */
}               lats_ls;

#define LS_UNKNOWN	0x40	/* Service is unknown		 */
#define LS_UNREACH	0x80	/* Service is unreachable	 */
#define LS_FLAGS	(LS_UNKNOWN | LS_UNREACH)

/*----------------------------------------------------------------------
    Define the remote node functions.
 -----------------------------------------------------------------------*/
#define	LIOC_ND_PURGE	 (LIOC | 24)	/* Purge aged remote nodes	 */
#define	LIOC_ND_SHOW	 (LIOC | 25)	/* Show named remote node	 */
#define	LIOC_ND_LIST	 (LIOC | 26)	/* List next  remote node	 */
#define	LIOC_ND_ZERO	 (LIOC | 27)	/* Zero remote node counters	 */

typedef struct {
	char            nd_node[NA_MAX];	/* Node name  string		 */
	char            nd_ident[ID_MAX];	/* Node ident string		 */
	uint8           nd_acl[32];	/* Groups for this entry	 */
	uint8           nd_host_addr[6];	/* Remote host address		 */
	int             nd_usage;	/* Entry usage counter		 */
	uint16          nd_flags;	/* Node state flags		 */
	uint16          nd_dll_max;	/* Maximum message size		 */
	uint8           nd_prot_ver;	/* LAT protocol version		 */
	uint8           nd_prot_eco;	/* LAT protocol ECO		 */
	uint16          nd_facility;	/* Remote facility number	 */
	uint8           nd_prod_code;	/* Remote product code		 */
	uint8           nd_prod_ver;	/* Remote product version	 */
	lats_count      nd_stats;	/* Node statistics		 */
}               lats_nd;

#define ND_UNKNOWN	0x40	/* Node is unknown		 */
#define ND_UNREACH	0x80	/* Node is unreachable		 */
#define ND_FLAGS	(ND_UNKNOWN | ND_UNREACH)

/*----------------------------------------------------------------------
    Define the queued request functions.
 -----------------------------------------------------------------------*/
#define	LIOC_QR_DELETE	 (LIOC | 28)	/* Delete queued request	 */
#define	LIOC_QR_LIST	 (LIOC | 29)	/* List queued request		 */

typedef struct {
	char            qr_service[NA_MAX];	/* Service name  string		 */
	char            qr_port[NA_MAX];	/* Port name string		 */
	char            qr_node[NA_MAX];	/* Node name string		 */
	uint16          qr_ident;	/* Queue request  number	 */
	uint16          qr_seq;	/* Queue sequence number	 */
}               lats_qr;

/*----------------------------------------------------------------------
    Define the DATA-B (port parameters) functions.
 -----------------------------------------------------------------------*/
#define LIOC_DB_SIGNAL	  (LIOC | 30)	/* Set signal for SET data-b	 */
#define LIOC_DB_SET_MODE  (LIOC | 31)	/* Set  transparency mode	 */
#define LIOC_DB_ACK_MODE  (LIOC | 32)	/* Ack  transparency mode	 */
#define LIOC_DB_SHOW_MODE (LIOC | 33)	/* Show transparency mode	 */

typedef struct {
	uint8           mode;
}               lats_mode;

#define SB_INTERACTIVE	0	/* Interactive session		 */
#define SB_PASSALL	1	/* 8-bit			 */
#define SB_PASSTHRUU	2	/* 8-bit (except XON/XOFF	 */

/*----------------------------------------------------------------------
    Define the ACL/IDL functions.
 -----------------------------------------------------------------------*/
#define	LIOC_ACL_SET	 (LIOC | 34)	/* Set ACL group		 */
#define	LIOC_ACL_CLEAR	 (LIOC | 35)	/* Clear ACL group		 */
#define	LIOC_ACL_SHOW	 (LIOC | 36)	/* Show ACL groups		 */

#define	LIOC_IDL_SET	 (LIOC | 37)	/* Set IDL group		 */
#define	LIOC_IDL_CLEAR	 (LIOC | 38)	/* Clear IDL group		 */
#define	LIOC_IDL_SHOW	 (LIOC | 39)	/* Show IDL groups		 */

#define	LIOC_TRC_SET	 (LIOC | 40)	/* Set trace group		 */
#define	LIOC_TRC_CLEAR	 (LIOC | 41)	/* Clear trace group		 */
#define	LIOC_TRC_SHOW	 (LIOC | 42)	/* Show trace groups		 */

typedef struct {
	int             group_no;	/* Group number to set/clear	 */
}               lats_group_no;

#define	GROUP_ALL	-1	/* Set/clear all groups		 */

/*----------------------------------------------------------------------
    Define the bind functions.
 -----------------------------------------------------------------------*/
#define	LIOC_BIND	(LIOC | 43)	/* Bind service point		 */
#define	LIOC_UNBIND	(LIOC | 44)	/* Unbind device		 */
#define	LIOC_UNBIND_ALL	(LIOC | 45)	/* Unbind all			 */

struct lats_bind_port {
	char            port_name[NA_MAX];	/* Port name			 */
	char            port_service[NA_MAX];	/* Service offering		 */
	char            port_ident[ID_MAX];	/* Service identification	 */
	char            port_password[NA_MAX];	/* Service password		 */
	int             port_rating;	/* Service rating		 */
};

typedef struct lats_bind_port lats_port;


struct lats_bind_conn {
        char            conn_lcl_port[NA_MAX];  /* Local port name               */
	char            conn_service[NA_MAX];	/* Service name			 */
	char            conn_port[NA_MAX];	/* Remote port name		 */
	char            conn_node[NA_MAX];	/* Remote node name		 */
	char            conn_password[NA_MAX];	/* Service password		 */
	uint8           conn_queueing;          /* Queueing flag(SUCCESS/FAILURE)*/
};

typedef struct lats_bind_conn lats_conn;

typedef struct {
	minor_t		bind_minor;		/* Port (device) minor number */
	uint8		bind_type;		/* INFO_TOUCH_PORT, HIC|CONN  */
	uint8		bind_permanence;	/* TRANSIENT or PERMANENT     */
#define	BIND_UNBOUND	0x00
#define	BIND_TRANSIENT	0x01
#define	BIND_PERMANENT	0x02
	union {
		struct lats_bind_port	lbp;
		struct lats_bind_conn	lbc;
	} bind_u;
#define	bind_PORT	bind_u.lbp
#define	bind_CONN	bind_u.lbc
}	lats_bind_info;

/*----------------------------------------------------------------------
    Define the information functions.
 -----------------------------------------------------------------------*/
#define	LIOC_INFO_SHOW	(LIOC | 46)	/* Get session/port information	 */
#define	LIOC_INFO_LIST	(LIOC | 47)	/* Get session/port information	 */
#define	LIOC_INFO_FD	(LIOC | 48)	/* Get session/port information	 */

typedef struct {
	int             info_dev;	/* LAT stream index		 */
	int             info_type;	/* Port type			 */
	int             info_permanence;/* Port bind permanence		 */
	int             info_status;	/* Port status 			 */

	char            lcl_service[NA_MAX];	/* Local service name		 */
	char            lcl_port[NA_MAX];	/* Local port name		 */

	char            rmt_service[NA_MAX];	/* Remote service name		 */
	char            rmt_port[NA_MAX];	/* Remote port name		 */
	char            rmt_node[NA_MAX];	/* Remote node name		 */
}               lats_info;

#define INFO_UNUSED	0x0000	/* LAT stream device unused	 */
#define INFO_OPEN	0x0001	/* LAT stream device opened	 */

#define INFO_TLI	0x0010	/* TLI bound			 */
#define INFO_TLI_NULL	0x0011	/* TLI bound, null		 */
#define	INFO_TLI_CLIENT	0x0012	/* TLI bound, client		 */
#define	INFO_TLI_SERVER	0x0013	/* TLI bound, server		 */
#define	INFO_TLI_OBJECT	0x0014	/* TLI bound, object		 */

#define INFO_TOUCH	0x0020	/* Touch n'go 			 */
#define INFO_TOUCH_PORT	0x0021	/* Touch n'go service port	 */
#define	INFO_TOUCH_CONN	0x0022	/* Touch n'go connect device	 */
#define	INFO_TOUCH_HIC	0x0023	/* Touch n'go HIC device	 */

#define INFO_STS_IDLE	0	/* Idle port			 */
#define INFO_STS_SES_S	1	/* Active session (server)	 */
#define INFO_STS_SES_H	2	/* Active session (host)	 */
#define INFO_STS_HIC	3	/* HIC request outstanding	 */

#define	LIOC_SB_STOP	(LIOC | 49)	/* Get session/port information	 */

#define	LIOC_TOC_ELAPSE	(LIOC | 50)	/* call toc_elapse() function	*/


/*----------------------------------------------------------------------
    Define the adapter functions.
 -----------------------------------------------------------------------*/
#define	LIOC_ADD_ADAPTER (LIOC | 51)	/* add a LAT adapter		*/
#define	LIOC_DEL_ADAPTER (LIOC | 52)	/* delete a LAT adapter		*/
#define	LIOC_GET_ADAPTER (LIOC | 53)	/* get a LAT adapter		*/
#define	LIOC_ADP_SHOW (LIOC | 53)	/* get LAT adapter information same as get_adapter */
#define	LIOC_ADP_LIST (LIOC | 54)	/* get LAT adapter information */
#define	LIOC_ADP_SET	 (LIOC | 55)	/* set LAT adapter information */

typedef struct {
	ulong   ppa_id;			/* LAT adapter id	*/
#define INVALID_ADAPTER -1L             /* Bad interface or PPA ID not found */
	char	ppa_name[PPA_NAME_SIZE];	/* LAT adapter name	*/	
        int     ppa_muxid;                      /* LAT adapter muxid    */
#define INVALID_MUXID   -2              /* Initial value for muxid field     */
        minor_t linking_minor;          /* minor # reqsting PLINK */
        char    ppa_flag;          	/* ppa state  */
        word    ppa_host_addr[3];       /* host address associated w/adapter */
} lats_ppa_t;

/*----------------------------------------------------------------------
    Define the ppa_flag values.  (Moved from engine/latadp.h)
    The ADP_DELETE flag will be used to specify that this adp will be
    deleted when the adapter has been successfully unlinked.
 -----------------------------------------------------------------------*/
#define UNLINK          0x0000          /* adp is unlinked; init value  */
#define PLINK_wait_ACK  0x0001          /* waiting for PHYS_ADDR_ACK to ack */
#define PLINK           0x0002          /* adp is plinked      */
#define ADP_DELETE      0x0040          /* delete adp after unlink      */

#define LIOC_INFO_BIS_PORT (LIOC | 56)  /* get ports bound to BISs      */

#define	LIOC_LS_LOOK	 (LIOC | 57)	/* Look for ls in hold list	 */

#define	LIOC_LS_LIST_HOLD (LIOC | 58)	/* return next ls in hold list	 */

/*----------------------------------------------------------------------
    Define the virtual circuit stats functions.
 -----------------------------------------------------------------------*/
#define	LIOC_VC_SHOW	 (LIOC | 59)	/* show virtual circuit info	 */

typedef struct {
	char            vc_node[NA_MAX];	/* Node name  string		 */
	int             vc_num_circuits;	/* Num of virtual circuits 	 */
}               lats_vc;

#define LIOC_MAX	60	/* Highest function number + 1	 */

/*----------------------------------------------------------------------
    Define some initial values.
 -----------------------------------------------------------------------*/
#define LAT_MINOR_MAX	(AS_OBJECTS - 2)	/* maximum minor number */
#define LAT_SESS_MAX	(LAT_MINOR_MAX + 1)	/* maximum number of sessions */
#define TEMPLATE	AS_OBJECTS		/* template object id */

#endif
