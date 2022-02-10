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
 * @(#)$RCSfile: dnetdb.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1993/11/02 15:28:31 $
 */
/*
 *
 * Copyright (C) 1985, 1989 by
 * Digital Equipment Corporation, Maynard, Mass.
 *
 * This software is furnished under a license and may be used and copied
 * only  in  accordance  with  the  terms  of such  license and with the
 * inclusion of the above copyright notice. This software or  any  other
 * copies thereof may not be provided or otherwise made available to any
 * other person. No title to and ownership of  the  software  is  hereby
 * transferred.
 *
 * The information in this software is subject to change without  notice
 * and  should  not be  construed  as  a commitment by Digital Equipment
 * Corporation.
 *
 * Digital assumes no responsibility for the use or  reliability  of its
 * software on equipment which is not supplied by Digital.
 *
 *
 * Networks & Communications Software Engineering
 *
 * IDENT HISTORY:
 *
 * 1.00 10-Jul-1985
 *      DECnet-ULTRIX   V1.0
 *
 * 1.01 08-Aug-1985
 *      DECnet-ULTRIX   V1.1
 *
 */

/*	@(#)dnetdb.h	14.2			7/31/93	*/

#ifndef _NETDNET_DNETDB_H
#define _NETDNET_DNETDB_H

/*
 * Structures returned by DECnet network
 * data base library.  All addresses
 * are in host order.
 */

struct	nodeent {
	char	*n_name;		/* name of node */
	char	*n_synonym;		/* node synonym */
	int	n_addrtype;		/* node address type */
	int	n_numaddrs;
	struct nodeentaddr {
		int na_length;
		char *na_addr;
	} *n_addrlist;
#define	n_length n_addrlist[0].na_length
#define	n_addr   n_addrlist[0].na_addr
	unsigned char	*n_params;	/* node parameters */
};


#define ND_MAXNODE	6		/* max length of node name */
#define ND_VOLATILE	0		/* use the volatile database */
#define ND_PERMANENT	1		/* use the permanent database */
#define ND_VERSION	1		/* database version number */

/*
 * Additional node parameters can be placed after dnet_nodeent structure.
 * The format is as follows:
 *	parameter type code = 2 byte
 *	length = 2 bytes
 *	parameter data = variable number of bytes
 */
struct dnet_nodeent {
	unsigned short	dn_esiz; /* size of node entry i.e., structure + parameters */
	unsigned short	dn_addr; /* node address */	
	char	dn_name[ND_MAXNODE]; /* node name */
};

struct db_version {
	unsigned short	vs_esiz; 	/* size of version entry */
	unsigned short	vrsn_number; 	/* version number */	
	unsigned short	reserved; 	/* reserved */	
};


struct objectent {
	unsigned short	o_flags;	/* object flags */
	unsigned char	o_objnum;	/* object number */
	char		*o_objname;	/* pointer to object name */
	char		*o_defuser;	/* default user to run program under */
	char		*o_file;	/* execute file name */
};

#define OF_DEFER	0x01		/* deferred connection */
#define OF_STREAM	0x02		/* stream socket */

#define OB_MAXFILE	128		/* max length of file name */
#define OB_MAXNAME	16		/* max length of object name */
#define OB_MAXUSER	20		/* max length of user name */

struct dnet_objectent {
	unsigned short	do_flags;	/* object flags */
	unsigned char	do_objnum;	/* object number */
	char		do_objname[OB_MAXNAME+1];
	char		do_defuser[OB_MAXUSER+1];
	char		do_file[OB_MAXFILE+1];
};

#ifdef _NO_PROTO
#ifndef DNET_CONST
#define	DNET_CONST
#endif
extern struct objectent *getobjectbyname();
extern struct objectent *getobjectbynumber();

extern struct nodeent *getnodebyname();
extern struct nodeent *getnodebyaddr();
extern struct nodeent *getnodeent();
extern int setnodeent();
extern void endnodeent();

extern struct nodeent *OLDgetnodebyname();
extern struct nodeent *OLDgetnodebyaddr();
extern struct nodeent *OLDgetnodeent();
extern int OLDsetnodeent();
extern void OLDendnodeent();
#elif defined(__STDC__) || defined(__cplusplus)
#if defined(__cplusplus)
extern "C" {
#endif
#ifndef DNET_CONST
#define	DNET_CONST	const
#endif
extern struct objectent *getobjectbyname(DNET_CONST char *);
extern struct objectent *getobjectbynumber(int);

extern struct nodeent *getnodebyname(DNET_CONST char *);
extern struct nodeent *getnodebyaddr(DNET_CONST char *, int, int);
extern struct nodeent *getnodeent(void);
extern int setnodeent(int);
extern void endnodeent(void);

extern struct nodeent *OLDgetnodebyname(DNET_CONST char *);
extern struct nodeent *OLDgetnodebyaddr(DNET_CONST char *, int, int);
extern struct nodeent *OLDgetnodeent(void);
extern int OLDsetnodeent(int);
extern void OLDendnodeent(void);
#if defined(__cplusplus)
}
#endif
#endif

#endif /* _NETDNET_DNETDB_H */
