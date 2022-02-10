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
 *     @(#)$RCSfile: ypclnt.h,v $ $Revision: 4.2.9.4 $ (DEC) $Date: 1995/06/15 17:38:57 $ 
 */
/*
 */


/* 
 * Copyright (c) 1988,1990 by Sun Microsystems, Inc.
 *	 1.12 86/12/19 
 */


/*
 * ypclnt.h
 * This defines the symbols used in the c language
 * interface to the NIS client functions.  A description of this interface
 * can be read in ypclnt(3N).
 */

#ifndef _RPCSVC_YPCLNT_H_
#define _RPCSVC_YPCLNT_H_

#include <standards.h>

/*
 * Failure reason codes.  The success condition is indicated by a functional
 * value of "0".
 */
#define YPERR_BADARGS 1			/* Args to function are bad */
#define YPERR_RPC 2			/* RPC failure */
#define YPERR_DOMAIN 3			/* Can't bind to a server which serves
					 *   this domain. */
#define YPERR_MAP 4			/* No such map in server's domain */
#define YPERR_KEY 5			/* No such key in map */
#define YPERR_YPERR 6			/* Internal NIS server or client
					 *   interface error */
#define YPERR_RESRC 7			/* Local resource allocation failure */
#define YPERR_NOMORE 8			/* No more records in map database */
#define YPERR_PMAP 9			/* Can't communicate with portmapper */
#define YPERR_YPBIND 10			/* Can't communicate with ypbind */
#define YPERR_YPSERV 11			/* Can't communicate with ypserv */
#define YPERR_NODOM 12			/* Local domain name not set */
#define YPERR_BADDB 13			/* NIS data base is bad */
#define YPERR_VERS 14			/* NIS version mismatch */
#define YPERR_ACCESS 15			/* Access violation */
#define YPERR_BUSY 16			/* Database is busy */

/*
 * Types of update operations
 */
#define YPOP_CHANGE 1			/* change, do not add */
#define YPOP_INSERT 2			/* add, do not change */
#define YPOP_DELETE 3			/* delete this entry */
#define YPOP_STORE  4			/* add, or change */
 
 

/*           
 * Data definitions
 */

/*
 * struct ypall_callback * is the arg which must be passed to yp_all
 */

struct ypall_callback {
        /* Return non-0 to stop getting called */
	int (*foreach) __((int, char *, int, char *, int, char *));
	char *data;			/* Opaque pointer for use of callback
					 *   function */
};

/* forward decl for ANSI/C++ */
struct dom_binding;

/*
 * External NIS client function references. 
 */
_BEGIN_CPLUSPLUS
extern int yp_bind __((char *));
extern int _yp_dobind __((char *, struct dom_binding **));
extern void yp_unbind __((char *));
extern int yp_get_default_domain __((char **));
extern int yp_match __((char *, char *, char *, int, char **, int *));
extern void __yp_match_flush __((char *, char *, char *, int));
extern int yp_first __((char *, char *, char **, int *, char **, int *));
extern int yp_next __((char *, char *, char *, int, char **, int *, char **, int *));
extern int yp_master __((char *, char *, char **));
extern int yp_order __((char *, char *, unsigned int *));
extern int yp_all __((char *, char *, struct ypall_callback *));
extern char *yperr_string __((int));
extern int ypprot_err __((unsigned int));
_END_CPLUSPLUS

/*
 * Global NIS data structures
 */
#endif /* _RPCSVC_YPCLNT_H_ */
