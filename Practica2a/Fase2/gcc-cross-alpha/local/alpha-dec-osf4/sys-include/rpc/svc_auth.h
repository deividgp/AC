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
 *	@(#)$RCSfile: svc_auth.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1994/03/29 18:38:46 $
 */
/*
 */


/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 */


/*
 * Service side of rpc authentication.
 */

#ifndef _rpc_svc_auth_h
#define	_rpc_svc_auth_h

#include <standards.h>
#include <rpc/auth.h>
#include <rpc/svc.h>
#include <rpc/rpc_msg.h>

_BEGIN_CPLUSPLUS
extern enum auth_stat _authenticate __((struct svc_req *, struct rpc_msg *));
_END_CPLUSPLUS

#endif /*!_rpc_svc_auth_h*/
