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
 *	@(#)$RCSfile: pnprpc.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1994/03/29 18:44:05 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */

/*
 * Portions of this software have been licensed to
 * Digital Equipment Company, Maynard, MA.
 * Copyright (c) 1988 by Sun Microsystems, Inc.
 */

#ifndef _RPCSVC_PNPRPC_H_
#define _RPCSVC_PNPRPC_H_

#include <standards.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/clnt.h>

#define PNP_POLLTIME 20
#define PNP_MISSEDPOLLS 6
#define MAX_ARCHLEN 5
#define MAX_MACHINELEN 256
#define MAX_DOMAINLEN 256
#define MAX_ENVSTRING 128

enum pnp_errcode {
	pnp_success = 0,
	pnp_failure = 0 + 1,
	pnp_wrong_address = 0 + 2,
	pnp_no_software = 0 + 3,
	pnp_no_diskspace = 0 + 4,
	pnp_nomore_clients = 0 + 5,
	pnp_do_bootserver = 0 + 6,
	pnp_do_askuser = 0 + 7,
	pnp_do_bootclient = 0 + 8,
	pnp_do_localboot = 0 + 9,
	pnp_busy_retry = 0 + 10,
	pnp_in_progress = 0 + 11,
	pnp_wait = 0 + 12,
	pnp_unknown_client = 0 + 13,
	pnp_database_error = 0 + 14
};
typedef enum pnp_errcode pnp_errcode;
_BEGIN_CPLUSPLUS
bool_t xdr_pnp_errcode __((XDR *, pnp_errcode *));
_END_CPLUSPLUS

enum net_type {
	ethernet = 0,
	ieee802_16 = 1,
	ptp = 2,
	atalk = 3
};
typedef enum net_type net_type;
_BEGIN_CPLUSPLUS
bool_t xdr_net_type __((XDR *, net_type *));
_END_CPLUSPLUS

struct hw_addr {
	net_type hw;
	union {
		char enetaddr[6];
		char lanaddr[2];
		char *nbpid;
	} hw_addr_u;
};
typedef struct hw_addr hw_addr;
_BEGIN_CPLUSPLUS
bool_t xdr_hw_addr __((XDR *, hw_addr *));
_END_CPLUSPLUS

struct pnp_whoami_arg {
	hw_addr linkaddr;
	long inetaddr;
};
typedef struct pnp_whoami_arg pnp_whoami_arg;
_BEGIN_CPLUSPLUS
bool_t xdr_pnp_whoami_arg __((XDR *, pnp_whoami_arg *));
_END_CPLUSPLUS

typedef char *env_string;
_BEGIN_CPLUSPLUS
bool_t xdr_env_string __((XDR *, env_string *));
_END_CPLUSPLUS

struct pnp_whoami_ret {
	pnp_errcode status;
	char *name;
	char *domain;
	struct {
		u_int extension_len;
		env_string *extension_val;
	} extension;
};
typedef struct pnp_whoami_ret pnp_whoami_ret;
_BEGIN_CPLUSPLUS
bool_t xdr_pnp_whoami_ret __((XDR *, pnp_whoami_ret *));
_END_CPLUSPLUS

enum how_to_boot {
	b_diskless = 0,
	b_diskful = 1,
	b_diskful_client = 2,
	b_boot_server = 3,
	b_gateway = 4,
	b_tellme = 5,
	b_install_disk = 6
};
typedef enum how_to_boot how_to_boot;
_BEGIN_CPLUSPLUS
bool_t xdr_how_to_boot __((XDR *, how_to_boot *));
_END_CPLUSPLUS

struct pnp_acquire_arg {
	hw_addr linkaddr;
	long inetaddr;
	char *arch;
	how_to_boot how;
	long memsize;
	long disksize;
	char *hostid;
};
typedef struct pnp_acquire_arg pnp_acquire_arg;
_BEGIN_CPLUSPLUS
bool_t xdr_pnp_acquire_arg __((XDR *, pnp_acquire_arg *));
_END_CPLUSPLUS

struct pnp_setup_arg {
	pnp_acquire_arg pa;
	char *name;
	char *keydata;
};
typedef struct pnp_setup_arg pnp_setup_arg;
_BEGIN_CPLUSPLUS
bool_t xdr_pnp_setup_arg __((XDR *, pnp_setup_arg *));
#define	ps_linkaddr	pa.linkaddr
#define	ps_inetaddr	pa.inetaddr
#define	ps_arch		pa.arch
#define	ps_how		pa.how
#define	ps_memsize	pa.memsize
#define	ps_disksize	pa.disksize
#define	ps_hostid	pa.hostid

#define PNPD_PROG ((u_long)100041)
#define PNPD_VERS ((u_long)2)
#define PNP_WHOAMI ((u_long)1)
extern pnp_whoami_ret *pnp_whoami_2 __((pnp_whoami_arg *, CLIENT *));
#define PNP_ACQUIRE ((u_long)2)
extern pnp_errcode *pnp_acquire_2 __((pnp_acquire_arg *, CLIENT *));
#define PNP_SETUP ((u_long)3)
extern pnp_errcode *pnp_setup_2 __((pnp_setup_arg *, CLIENT *));
#define PNP_POLL ((u_long)4)
extern pnp_errcode *pnp_poll_2 __((pnp_setup_arg *, CLIENT *));
_END_CPLUSPLUS

#endif /* _RPCSVC_PNPRPC_H_ */
