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
 *	@(#)$RCSfile: pmap_rmt.h,v $ $Revision: 4.2.5.2 $ (DEC) $Date: 1994/03/29 18:34:29 $
 */
/*
 */


/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *	1.2 88/02/08 SMI	
 */


/*
 * Structures and XDR routines for parameters to and replies from
 * the portmapper remote-call-service.
 */

#ifndef _rpc_pmap_rmt_h
#define	_rpc_pmap_rmt_h

#include <standards.h>
#include <sys/types.h>
#include <rpc/types.h>
#include <rpc/xdr.h>

struct rmtcallargs {
	u_int prog, vers, proc, arglen;
	caddr_t args_ptr;
	xdrproc_t xdr_args;
};

_BEGIN_CPLUSPLUS
bool_t xdr_rmtcall_args __((XDR *, struct rmtcallargs *));
_END_CPLUSPLUS

struct rmtcallres {
	u_int *port_ptr;
	u_int resultslen;
	caddr_t results_ptr;
	xdrproc_t xdr_results;
};

_BEGIN_CPLUSPLUS
bool_t xdr_rmtcallres __((XDR *, struct rmtcallres *));
_END_CPLUSPLUS

#endif /*!_rpc_pmap_rmt_h*/
