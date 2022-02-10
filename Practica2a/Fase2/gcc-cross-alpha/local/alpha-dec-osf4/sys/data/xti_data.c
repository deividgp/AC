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
#pragma ident "@(#)$RCSfile: xti_data.c,v $ $Revision: 1.1.8.5 $ (DEC) $Date: 1994/05/31 22:14:17 $"


/* STREAMS include files */
#include <sys/stream.h>
#include <sys/stropts.h>
#include <sys/strstat.h>
#include <sys/strlog.h>

#include <net/net_globals.h>
#include <sys/socket.h>
#include <sys/socketvar.h>

#include <streamsm/xti.h>
#include <streamsm/xtiso.h>
#include <streamsm/xtiso_config.h>

#include <sys/socket.h>
#include <sys/socketvar.h>

#include <sys/un.h>
#include <netinet/in.h>
#include <netns/ns.h>


xtiso_inadm_t xti_proto_info[] = {
/* UDP */
	{ 
	  { OSF_STREAMS_CONFIG_11, 0, "xtisoUDP", NODEV },
	  { AF_INET, SOCK_DGRAM, 0, T_CLTS,
	    	/* The ti[ts]dulen should be the same as udp_sendspace (9K) */
		9216, XTI_NS, XTI_NS, XTI_NS,
		sizeof(struct sockaddr_in), XTI_NS, 9216, 
		XTI_NO_OPTS
	  }
	}
/* TCP */
	,
	{ 
	  { OSF_STREAMS_CONFIG_11, 0, "xtisoTCP", NODEV },
	  { AF_INET, SOCK_STREAM, 0, T_COTS_ORD,
	   	/* The tsdulen should be the same as max stream msgsz (12K) */
		0, 1024, XTI_NS, XTI_NS,
		sizeof(struct sockaddr_in), XTI_NS, 12288, 
		XTI_NO_OPTS
	  } 
	}
/* End Marker for xti_proto_info                   [Don't move or modify] */
};

/* The following is temporary, can be removed */
#define XTI_NOSTATICS	(sizeof xti_proto_info / sizeof xti_proto_info[0])

int xti_nprotos = XTI_NOSTATICS;

