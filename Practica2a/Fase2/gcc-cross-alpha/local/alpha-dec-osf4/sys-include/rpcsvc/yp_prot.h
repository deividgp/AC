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
 *      @(#)$RCSfile: yp_prot.h,v $ $Revision: 4.2.4.3 $ (DEC) $Date: 1994/03/29 18:52:06 $ 
 */
/*
 */

/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 *  1.13 86/07/16 Copyr 1985 Sun Microsystems, Inc 
 */


/*
 * This file contains symbols and structures defining the rpc protocol
 * between the NIS clients and the NIS servers.  The servers
 * are the NIS database servers, and the NIS binders.  
 */

/*
 * The following procedures are supported by the protocol:
 * 
 * YPPROC_NULL() returns () takes nothing, returns nothing.  This indicates
 * that the NIS server is alive.
 * 
 * YPPROC_DOMAIN (char *) returns (bool_t) TRUE.  Indicates that the
 * responding NIS server does serve the named domain; FALSE indicates no
 * support.
 * 
 * YPPROC_DOMAIN_NONACK (char *) returns (TRUE) if the NIS server does serve
 * the named domain, otherwise does not return.  Used in the broadcast case.
 * 
 * YPPROC_MATCH (struct ypreq_key) returns (struct ypresp_val).  Returns the
 * right-hand value for a passed left-hand key, within a named map and
 * domain.
 * 
 * YPPROC_FIRST (struct ypreq_nokey) returns (struct ypresp_key_val).
 * Returns the first key-value pair from a named domain and map.
 * 
 * YPPROC_NEXT (struct ypreq_key) returns (struct ypresp_key_val).  Returns
 * the key-value pair following a passed key-value pair within a named
 * domain and map.
 *
 * YPPROC_XFR (struct ypreq_xfr) returns nothing.  Indicates to a server that
 * a map should be updated.
 *
 * YPPROC_CLEAR	takes nothing, returns nothing.  Instructs a NIS server to
 * close the current map, so that old versions of the disk file don't get
 * held open.
 * 
 * YPPROC_ALL (struct ypreq_nokey), returns
 * 	union switch (bool more) {
 *		TRUE:	(struct ypresp_key_val);
 *		FALSE:	(struct) {};
 *	}
 *
 * YPPROC_MASTER (struct ypreq_nokey), returns (ypresp_master)
 *
 * YPPROC_ORDER (struct ypreq_nokey), returns (ypresp_order)
 *
 * YPPROC_MAPLIST (char *), returns (struct ypmaplist *)
 */
#ifndef _RPCSVC_YP_PROT_H_
#define _RPCSVC_YP_PROT_H_

#include <standards.h>
#include <rpc/xdr.h>
#include <rpc/clnt.h>
#include <rpcsvc/ypclnt.h>

#ifndef BOOL_DEFINED
typedef unsigned int bool;
#define BOOL_DEFINED
#endif

/* Program and version symbols, magic numbers */

#define YPPROG		100004
#define YPVERS		2
#define YPVERS_ORIG	1
#define YPMAXRECORD	1024
#define YPMAXDOMAIN	64
#define YPMAXMAP	64
#define YPMAXPEER	256

/* byte size of a large NIS packet */
#define YPMSGSZ		1600

#ifndef DATUM
typedef struct {
	char	*dptr;
	int	dsize;
} datum;
#define DATUM
#endif

struct ypmap_parms {
	char *domain;			/* Null string means not available */
	char *map;			/* Null string means not available */
	unsigned int ordernum;		/* 0 means not available */
	char *owner;			/* Null string means not available */
};

/*
 * Request parameter structures
 */

struct ypreq_key {
	char *domain;
	char *map;
	datum keydat;
};

struct ypreq_nokey {
	char *domain;
	char *map;
};

struct ypreq_xfr {
	struct ypmap_parms map_parms;
	unsigned int transid;
	unsigned int proto;
	unsigned short port;
};
#define ypxfr_domain map_parms.domain
#define ypxfr_map map_parms.map
#define ypxfr_ordernum map_parms.ordernum
#define ypxfr_owner map_parms.owner

/*
 * Response parameter structures
 */

struct ypresp_val {
	unsigned int status;
	datum valdat;
};

struct ypresp_key_val {
	unsigned int status;
	datum keydat;
	datum valdat;
};

struct ypresp_master {
	unsigned int status;
	char *master;
};

struct ypresp_order {
	unsigned int status;
	unsigned int ordernum;
};

struct ypmaplist {
	char ypml_name[YPMAXMAP + 1];
	struct ypmaplist *ypml_next;
};

struct ypresp_maplist {
	unsigned int status;
	struct ypmaplist *list;
};

/*
 * Procedure symbols.  YPPROC_NULL, YPPROC_DOMAIN, and YPPROC_DOMAIN_NONACK
 * must keep the same values (0, 1, and 2) that they had in the first version
 * of the protocol.
 */

#define YPPROC_NULL	0
#define YPPROC_DOMAIN	1
#define YPPROC_DOMAIN_NONACK 2
#define YPPROC_MATCH	3
#define YPPROC_FIRST	4
#define YPPROC_NEXT	5
#define YPPROC_XFR	6
#define YPPROC_CLEAR	7
#define YPPROC_ALL	8
#define YPPROC_MASTER	9
#define YPPROC_ORDER	10
#define YPPROC_MAPLIST	11

/* Return status values */

#define YP_TRUE	 	1		/* General purpose success code */
#define YP_NOMORE 	2		/* No more entries in map */
#define YP_FALSE 	0		/* General purpose failure code */
#define YP_NOMAP 	-1		/* No such map in domain */
#define YP_NODOM 	-2		/* Domain not supported */
#define YP_NOKEY 	-3		/* No such key in map */
#define YP_BADOP 	-4		/* Invalid operation */
#define YP_BADDB 	-5		/* Server data base is bad */
#define YP_YPERR 	-6		/* NIS server error */
#define YP_BADARGS 	-7		/* Request arguments bad */
#define YP_VERS		-8		/* NIS server version mismatch - server
					 *   can't supply requested service. */
#define YP_ACCESS	-9		/* Access violation */

/*
 * Domain binding data structure, used by ypclnt package and ypserv modules.
 * Users of the ypclnt package (or of this protocol) don't HAVE to know about
 * it, but it must be available to users because _yp_dobind is a public
 * interface.
 */

struct dom_binding {
	struct dom_binding *dom_pnext;
	char dom_domain[YPMAXDOMAIN + 1];
	struct sockaddr_in dom_server_addr;
	unsigned short int dom_server_port;
	int dom_socket;
	CLIENT *dom_client;
	unsigned short int dom_local_port;
	int dom_vers;
};


/*
 *		Protocol between clients and NIS binder servers
 */

/*
 * The following procedures are supported by the protocol:
 *
 * YPBINDPROC_NULL() returns ()
 * 	takes nothing, returns nothing
 *
 * YPBINDPROC_DOMAIN takes (char *) returns (struct ypbind_resp)
 *
 * YPBINDPROC_SETDOM takes (struct ypbind_setdom) returns nothing
 */
 
/* Program and version symbols, magic numbers */

#define YPBINDPROG		100007
#define YPBINDVERS		2
#define YPBINDVERS_ORIG		1

/* Procedure symbols */

#define YPBINDPROC_NULL		0
#define YPBINDPROC_DOMAIN	1
#define YPBINDPROC_SETDOM	2
/*
 * Response structure and overall result status codes.  Success and failure
 * represent two separate response message types.
 */

enum ypbind_resptype {YPBIND_SUCC_VAL = 1, YPBIND_FAIL_VAL = 2};

struct ypbind_binding {
	struct in_addr ypbind_binding_addr;	/* In network order */
	unsigned short int ypbind_binding_port;	/* In network order */
};
struct ypbind_resp {
	enum ypbind_resptype ypbind_status;
	union {
		unsigned int ypbind_error;
		struct ypbind_binding ypbind_bindinfo;
	} ypbind_respbody;
};


/* Detailed failure reason codes for response field ypbind_error*/

#define YPBIND_ERR_ERR 1		/* Internal error */
#define YPBIND_ERR_NOSERV 2		/* No bound server for passed domain */
#define YPBIND_ERR_RESC 3		/* System resource allocation failure */

/*
 * Request data structure for ypbind "Set domain" procedure.
 */
struct ypbind_setdom {
	char ypsetdom_domain[YPMAXDOMAIN + 1];
	struct ypbind_binding ypsetdom_binding;
	unsigned short ypsetdom_vers;
};
#define ypsetdom_addr ypsetdom_binding.ypbind_binding_addr
#define ypsetdom_port ypsetdom_binding.ypbind_binding_port

/*
 *		Protocol between clients (ypxfr, only) and yppush
 *		yppush speaks a protocol in the transient range, which
 *		is supplied to ypxfr as a command-line parameter when it
 *		is activated by ypserv.
 */
#define YPPUSHVERS		1
#define YPPUSHVERS_ORIG		1

/* Procedure symbols */

#define YPPUSHPROC_NULL		0
#define YPPUSHPROC_XFRRESP	1

struct yppushresp_xfr {
	unsigned int transid;
	unsigned int status;
};

/* Status values for yppushresp_xfr.status */

#define YPPUSH_SUCC	1		/* Success */
#define YPPUSH_AGE	2		/* Master's version not newer */
#define YPPUSH_NOMAP 	-1		/* Can't find server for map */
#define YPPUSH_NODOM 	-2		/* Domain not supported */
#define YPPUSH_RSRC 	-3		/* Local resouce alloc failure */
#define YPPUSH_RPC 	-4		/* RPC failure talking to server */
#define YPPUSH_MADDR	-5		/* Can't get master address */
#define YPPUSH_YPERR 	-6		/* NIS server/map db error */
#define YPPUSH_BADARGS 	-7		/* Request arguments bad */
#define YPPUSH_DBM	-8		/* Local dbm operation failed */
#define YPPUSH_FILE	-9		/* Local file I/O operation failed */
#define YPPUSH_SKEW	-10		/* Map version skew during transfer */
#define YPPUSH_CLEAR	-11		/* Can't send "Clear" req to local
					 *   ypserv */
#define YPPUSH_FORCE	-12		/* No local order number in map -
					 *   use -f flag. */
#define YPPUSH_XFRERR	-13		/* ypxfr error */
#define YPPUSH_REFUSED	-14		/* Transfer request refused by ypserv */

/* moved function decls to end to get struct definitions above */

_BEGIN_CPLUSPLUS
extern bool xdr_datum __((XDR *, datum *));
extern bool xdr_ypdomain_wrap_string __((XDR *, char **));
extern bool xdr_ypmap_wrap_string __((XDR *, char **));
extern bool xdr_ypreq_key __((XDR *, struct ypreq_key *));
extern bool xdr_ypreq_nokey __((XDR *, struct ypreq_nokey *));
extern bool xdr_ypreq_xfr __((XDR *, struct ypreq_xfr *));
extern bool xdr_ypresp_val __((XDR *, struct ypresp_val *));
extern bool xdr_ypresp_key_val __((XDR *, struct ypresp_key_val *));
extern bool xdr_ypbind_resp __((XDR *, struct ypbind_resp *));
extern bool xdr_ypbind_setdom __((XDR *, struct ypbind_setdom *));
extern bool xdr_yp_inaddr __((XDR *, struct in_addr *));
extern bool xdr_ypmap_parms __((XDR *, struct ypmap_parms *));
extern bool xdr_ypowner_wrap_string __((XDR *, char **));
extern bool xdr_yppushresp_xfr __((XDR *, struct yppushresp_xfr *));
extern bool xdr_ypresp_order __((XDR *, struct ypresp_order *));
extern bool xdr_ypresp_master __((XDR *, struct ypresp_master *));
extern bool xdr_ypall __((XDR *, struct ypall_callback *));
extern bool xdr_ypresp_maplist __((XDR *, struct ypresp_maplist *));
_END_CPLUSPLUS


#endif /* _RPCSVC_YP_PROT_H_ */
