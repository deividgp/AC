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
 * @(#)$RCSfile: latsys.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 1995/08/18 23:07:05 $
 */
/* @(#)latsys.h 1.2 12/21/92 MTC_SRC; from MTC 6.4 11/20/92 */
/*-----------------------------------------------------------------------
    latsys		(h) LAT system and configuration definitions

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

#ifndef LATSYS_H
#define LATSYS_H	0	/* Indicate file has been read	 */

#include <lat/engine/mtcdef.h>
#include <sys/types.h>

/*----------------------------------------------------------------------
    Define LAT configuration options. Set option to 1 to enable the
    feature, zero to disable.
 -----------------------------------------------------------------------*/
#define LE_HOST		1	/* Support host sessions	 */
#define LE_HOST_AS	1	/* Support host AS  messages	 */

#define	LE_SERVER	1	/* Support server sessions	 */
#define LE_SERVER_LS	1	/* Support server LS  messages	 */
#define LE_SERVER_AGENT	1	/* Support agent solicitation	 */

#define LE_SUBJECT_HIC	1	/* Support subject HIC messages	 */
#define LE_OBJECT_HIC	1	/* Support object  HIC messages	 */

#define LE_OBJECTS	1	/* Supports objects 		 */
#define LE_HS_STATS	1	/* Support host statistics	 */
#define LE_ND_STATS	1	/* Support node statistics	 */
#define LE_UPPER	1	/* Store strings in upper	 */

#define LE_TSM_SOLICIT	1	/* Support TSM TEST LAT in T/S  */

#define LE_ERR_NOTIFY	0	/* Notify environment of certain
				   engine error conditions	*/
 
/*----------------------------------------------------------------------
    If the following two configuration options are selected, they may be
    disabled at run-time by setting the global variables le_del_ack and
    le_del_disc to zero.
 
    Notes:  For terminal server implementations that are primarily
	    intended to support interactive terminal sessions, LE_DEL_ACk
	    and LE_DEL_DISC should be set to zero.  Delayed acknowledgement
	    is normally used in conjunction with Service Class 3 and 4
	    (X-Window) terminal sessions to provide more efficient use
	    of bandwidth.  When used with service Class 1 interactive
	    sessions, there may be objectionable delays in keystroke
	    echoing when connected to some hosts that support delayed	
	    acknowledgements.
 
    	    If LE_DEL_ACK is set to zero, code is not compiled to support
    	    delayed acknowledgements and the global variables le_del_ack
    	    and le_del_disc are not defined.

	    If le_del_ack is set to one and le_del_disc is set to zero
	    and delayed acknowledgement is not successfully negotiated
	    between two nodes, delayed acknowledgement will not be used
	    on that virtual circuit.  This may not be desireable for some
	    implementations such as an X-Window server.

 -----------------------------------------------------------------------*/
#define LE_DEL_ACK	0		/* Support host node delayed
					   acknowledgement		*/
#define LE_DEL_DISC	0		/* Set to one to disconnect
					   circuit when delayed ack is
					   not successfully negotiated	*/
 
/*----------------------------------------------------------------------
    The following two configuration options may be disabled at run-time
    if they are selected by setting the global values le_nd_retain and
    le_ls_dups to zero.

    Notes, if the options are not selected, they may not be enabled at
    runtime.
 -----------------------------------------------------------------------*/
#define LE_ND_RETAIN	1	/* Retain node/services		 */
#define	LE_LS_DUPS	1	/* Allow duplicate ls servces	 */

/*----------------------------------------------------------------------
    The following option is normally contained in a SuperLAT header file
    named latcp.h.  Due to a conflict with /usr/sbin/latcp, this file
    is not maintained as part of the SuperLAT engine source in the 
    Digital UNIX LAT implementation - and it's contents are reproduced
    here.  LE_COPY_CHECK is enabled for special processing needed for
    "SuperLAT for NT" site licencse distributions.  It is not used in
    the Digital UNIX LAT implementation.

 ----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
#define LE_COPY_CHECK
 ----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
   Define CME compiler options.  CME_STRUC controls the usage and some
   flags fields defined in the SuperLAT ob structure.  CME_DATAB controls
   the DATA-B fields in the SuperLAT ob and sb structures.
 -----------------------------------------------------------------------*/
#define		CME_STRUC	0	/* Use CM Environment (CME)	 */
#define		CME_DATAB	0	/* Use CM for DATA-B attributes	 */

/*----------------------------------------------------------------------
    Define views of the LAT engine structures.
 -----------------------------------------------------------------------*/
#define CB_VIEW(x)	*(x)	/* Circuit block		 */
#define SB_VIEW(x)	*(x)	/* Session block		 */
#define	AS_VIEW(x)	*(x)	/* Service, advertised 		 */
#define LS_VIEW(x)	*(x)	/* Service, learned		 */
#define ND_VIEW(x)	*(x)	/* Node structure		 */
#define OB_VIEW(x)	*(x)	/* Object block			 */
#define HI_VIEW(x)	*(x)	/* Host-initiated block		 */
#define QR_VIEW(x)	*(x)	/* Queued request		 */
#define ADP_VIEW(x)     *(x)    /* Adapter structure             */
#if !COMMON_ETHER_DEFS
#define IF_VIEW(x)	*(x)	/* LAT input  frame		 */
#define OF_VIEW(x)	*(x)	/* LAT output frame		 */
#endif

/*----------------------------------------------------------------------
    Define macro to correctly orient word fields in LAT message. Little
    endian machines (808x, VMS, etc) should define macro as a null.
 -----------------------------------------------------------------------*/
#if NET_ORDER
#define	swap(x)	((word)((((x) >> 8) & 0xff) + ((x) << 8)))
#else
#define	swap(x)		(x)
#endif

#define	swap_es(x)	((word)((((x) >> 8) & 0xff) + ((x) << 8)))

/*----------------------------------------------------------------------
    Define message byte pointers and the output frame buffer.
 -----------------------------------------------------------------------*/
#define	DLL_MAX		1500	/* Maximum message output size	 */
#define	INP_MAX		1500	/* Maximum message input  size	 */

#if !COMMON_ETHER_DEFS

typedef byte    IF_VIEW(if_byte);	/* Pointer to input  frames	 */
typedef byte    OF_VIEW(of_byte);	/* Pointer to output frames	 */

typedef struct of {
	struct of       OF_VIEW(of_link);	/* Internal rexmit queue
						 * (eng)	 */
	struct of       OF_VIEW(of_i_o);	/* Ethernet output queue
						 * (env)	 */
	struct msgb    *of_msgb;/* Backpointer to message block */
	of_byte         of_data;/* Pointer to output data	 */
	int             of_size;/* Size of output frame		 */
	word            of_dst[3];	/* Destination address		 */
	struct adp	ADP_VIEW(of_adapter);	/* Pointer to adp structure */
}               of_node, OF_VIEW(of_ptr);

#endif				/* !COMMON_ETHER_DEFS */

/*----------------------------------------------------------------------
    Define interface name size 
 -----------------------------------------------------------------------*/
#define PPA_NAME_SIZE   20              /* Max size of LAT adapter name     */

/*----------------------------------------------------------------------
    Define LAT external data types.
 -----------------------------------------------------------------------*/
typedef int     aid_type;	/* Advertised service ident	 */
typedef minor_t     oid_type;	/* Object  identifer		 */
typedef minor_t     sid_type;	/* Session identifer		 */

#define AID_NULL	(aid_type)(~0)	/* Null advertised service id	 */
#define SID_NULL	(sid_type)(~0)	/* Null session identifer	 */
#define OID_NULL	(oid_type)(~0)	/* Null object  identifier	 */

/*----------------------------------------------------------------------
    Define timer constants for system.
 -----------------------------------------------------------------------*/
#define MSEC_TIC	10	/* 10ms between tic_elapse */
#define SECS_TOC	60	/* System uses 60 second SAM interval	 */

/*----------------------------------------------------------------------
    Define maximums for various structures. The CB_MAXIMUM is used at
    compile time to define the maximum number of circuits. The other
    values are initial maximums and may be changed at runtime. A value
    of zero means the engine does not enforce a maximum.
 -----------------------------------------------------------------------*/
#define CB_MAXIMUM	0	/* Maximum circuit blocks	 */
#define SB_MAXIMUM	0	/* Maximum session blocks	 */
#define AS_MAXIMUM	0	/* Maximum advertised services	 */
#define LS_MAXIMUM	100	/* Maximum learned services	 */
#define ND_MAXIMUM	0	/* Maximum remote nodes		 */
#define OB_MAXIMUM	0	/* Maximum objects		 */
#define HI_MAXIMUM	0	/* Maximum HIC requests		 */
#define QR_MAXIMUM	32	/* Maximum queued requests	 */

/*----------------------------------------------------------------------
    Define circuit constants for system.
 -----------------------------------------------------------------------*/
#define	CB_VC_MSEC	80	/* Circuit interval    (msec)	 */
#define CB_HD_MSEC	5	/* Circuit host delay  (msec)	 */
#define CB_KA_SECS	20	/* Keep-alive interval (secs)	 */
#define CB_PROGRESS	60	/* Host progress interval (s)	 */
#define CB_R1_UNIT	4	/* Retransmit, first pass (vc)	 */
#define CB_DEF_TRY	8	/* Default circuit retries	 */
#define CB_MAX_SES	255	/* Maximum sessions/circuit	 */
#define CB_S_RCV_EXTRA	0	/* Extra receive buffers (S)	 */
#define CB_H_RCV_EXTRA	0	/* Extra receive buffers (H)	 */

/*----------------------------------------------------------------------
    Define session constants for system.
 -----------------------------------------------------------------------*/
#define	SB_MAX_DATA	0xff	/* Maximum DATA-A slot		 */
#define SB_MAX_ATTN	0xff	/* Maximum ATTENTION slot	 */

#define SB_REJECTS	16	/* Maximum pending rejects	 */

/*----------------------------------------------------------------------
    Define host-initiated constants for this system.
 -----------------------------------------------------------------------*/
#define HI_STS_SEC	60	/* Default status interval	 */
#define HI_CMD_SEC	1	/* Default SI/CMD interval	 */
#define HI_DEF_TRY	2	/* Default HIC attempts		 */

/*----------------------------------------------------------------------
    Define advertised service constants for system.
 -----------------------------------------------------------------------*/
#define AS_MC_SEC	SECS_TOC	/* Default multicast interval	 */

/*----------------------------------------------------------------------
    Define learned service constants for system.
 -----------------------------------------------------------------------*/
#define LS_UPDATES	5	/* Multicast multiplier for ls	 */
#define LS_MC_DEF	256	/* Default mc for permanent ls	 */
#define LS_AGENT	0	/* Default: server node is  not
				    a solicitation agent         */

/*----------------------------------------------------------------------
    Define remote node constants for system. Note the age maximum
    cannot exceed 10 hours. Set to zero if no maximum.
 -----------------------------------------------------------------------*/
#define ND_AGE_MAX	(60 * 60 * 5)	/* Maximum age of node  (sec)	 */
#define ND_INTERVAL	(60 * 30)	/* Purge interval       (sec)	 */

/*----------------------------------------------------------------------
    Define LAT dimensions.
 
    CB_TABLES is a compile time constant which defines the size of
    hs_cb_table array and hence is the absolute maximum of circuits.
    Define as one greater than the maximum number of circuits which
    will be allowed.
 
    CB_FACTOR is a compile time constant used to generate unique circuit
    block identifiers (IDs).  2 raised to the power CB_FACTOR must be
    equal to or greater than CB_TABLES.  Furthermore, CB_FACTOR must be
    equal to or greater than 8 and must be less than 16.  The maximum
    recommended value of CB_FACTOR is 12, which will accomodate 4095
    virtual circuits.
 
    AS_OBJECTS is a compile time constant which defines the maximum
    number of objects which can be defined or associated with an
    advertised circuit.
 -----------------------------------------------------------------------*/
#define CB_TABLES	(128+1)		/* Maximum number of circuits + 1 */
#define CB_FACTOR	8		/* CB identifier scaling factor	*/
 
#define ENCODE_CB_ID(N,CB)	((word)((N) << CB_FACTOR) | (CB))
#define EXTRACT_CB_NUM(ID)	((ID) & ((1 << CB_FACTOR) - 1))
#define CB_UNIQUE_MASK		((1 << (16 - CB_FACTOR)) - 1)
 
#define AS_OBJECTS	5001		/* Maximum objects w/as_node	*/
 
#define ND_HASHES	16		/* Depth of nd hash in common	*/
#define nd_hash(x)	((x) % ND_HASHES)
 
#define SB_HASHES	32		/* Depth of sb hash in cb	*/
#define sb_hash(x)	((x) % SB_HASHES)

/*----------------------------------------------------------------------
    Define the various LAT name strings. The first byte is a count
    of the remaining characters.
 -----------------------------------------------------------------------*/
#define SC_STR		2	/* Service classes		 */
#define	ND_STR		17	/* Node name			 */
#define SV_STR		17	/* Service name			 */
#define OB_STR		17	/* Object  name			 */
#define	ID_STR		65	/* Identification		 */

/*----------------------------------------------------------------------
    Define the maximum field size for groups. Groups are handled in
    same fashion as name strings, i.e. first byte is count.
 -----------------------------------------------------------------------*/
#define GP_STR		33	/* Process groups codes	0-255	 */

/*----------------------------------------------------------------------
    Define the masks and data_b structure for DATA-B processing in
    the engine.  Both objects and sessions use this information as
    objects refer to local port configurations, and sessions refer
    to remote port configurations, local and remote transparency modes,
    and local and remote status/break conditions.
 -----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
    Define the XON/XOFF characters.
 -----------------------------------------------------------------------*/
#define	DB_XON		0x011	/* ^Q				 */
#define DB_XOFF		0x013	/* ^S				 */

/*----------------------------------------------------------------------
    Define the data-b data fields.
 -----------------------------------------------------------------------*/
#define DB_E_PARITY	0x02	/* db_char_parity valid		 */
#define DB_E_RECV	0x04	/* db_baud_recv   valid		 */
#define DB_E_XMIT	0x08	/* db_baud_xmit   valid		 */
#define DB_E_BELL	0x10	/* db_bell_mode   valid		 */
#define DB_E_MODE	0x20	/* db_char_mode   valid		 */
#define DB_E_STATUS	0X40	/* sb_xxx_data_b_ valid		 */

#define DB_E_PORT	DB_E_PARITY | DB_E_RECV | DB_E_XMIT | DB_E_BELL | DB_E_MODE

/*----------------------------------------------------------------------
    Define the data-b structure.  This structure is used in the ob and
    sb structures if CME_SLAT is disabled.  Otherwise, this structure
    is used as a global "dummy" structure to pass information from the
    environment to the engine and visa versa in sb1inp.c and sb1out.c
 -----------------------------------------------------------------------*/
     typedef struct
     {
	int	db_flags;		/* Enabled field flags		*/
	byte	db_type;		/* Object type flags		*/
	byte	db_config;		/* Configuration flags		*/
	byte	db_char_parity;		/* Character size, parity	*/
	byte	db_bell_mode;		/* Mode for handling bell	*/
	word	db_baud_out;		/* Output speed (server->tt)	*/
	word	db_baud_in;		/* Input speed (tt->server)	*/
    } data_b, db_node, *db_ptr;
 
#endif				/* LATSYS_H */
