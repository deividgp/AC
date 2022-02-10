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
 *	@(#)$RCSfile: resolv.h,v $ $Revision: 4.2.33.2 $ (DEC) $Date: 1998/10/21 18:02:42 $
 */ 
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/*
 * Copyright (c) 1983, 1987, 1989, 1993
 *    The Regents of the University of California.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 * 	This product includes software developed by the University of
 * 	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 *	resolv.h	8.1 (Berkeley) 6/2/93
 *	resolv.h,v 8.5 1995/12/22 10:20:27 vixie
 */

#ifndef _RESOLV_H_
#define _RESOLV_H_

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/nameser.h>

/*
 * revision information.  this is the release date in YYYYMMDD format.
 * it can change every day so the right thing to do with it is use it
 * in preprocessor commands such as "#if (__RES > 19931104)".  do not
 * compare for equality; rather, use it to determine whether your resolver
 * is new enough to contain a certain feature.
 */

#define __RES   19951031

/*
 * Resolver configuration file.
 * Normally not present, but may contain the address of the
 * inital name server(s) to query and the domain search list.
 */

#ifndef _PATH_RESCONF
#define _PATH_RESCONF        "/etc/resolv.conf"
#endif

/*
 * Global defines and variables for resolver stub.
 */
#define	MAXNS			3	/* max # name servers we'll track */
#define MAXDFLSRCH		3	/* # default domain levels to try */
#define MAXDNSRCH		6	/* max # domains in search path */
#define	LOCALDOMAINPARTS	2	/* min levels in name that is "local" */

#define	RES_TIMEOUT		5	/* min. seconds between retries */
#define	MAXRESOLVSORT		10	/* number of net to sort on */
#define	RES_MAXNDOTS		15	/* should reflect bit field size */

struct __res_state {
	int	retrans;	 	/* retransmition time interval */
	int	retry;			/* number of times to retransmit */
	u_long	options;		/* option flags - see below. */
	int	nscount;		/* number of name servers */
	struct sockaddr_in
		nsaddr_list[MAXNS];	/* address of name server */
#define	nsaddr	nsaddr_list[0]		/* for backward compatibility */
	u_short	id;			/* current packet id */
	char	defdname[256];		/* default domain */
	char	*dnsrch[MAXDNSRCH+1];	/* components of domain to search */
	u_long	pfcode;			/* RES_PRF_ flags - see below. */
	unsigned ndots:4;		/* threshold for initial abs. query */
	unsigned nsort:4;		/* number of elements in sort_list[] */
	char	unused[3];
	struct {
		struct in_addr	addr;
		u_int		mask;
	} sort_list[MAXRESOLVSORT];
/*        char    pad[72];*/            /* On an i38this means 512b total. */
};

#ifdef _RES_STRUCT_STATE
struct state {
	int	retrans;	 	/* retransmition time interval */
	int	retry;			/* number of times to retransmit */
	long	options;		/* option flags - see below. */
	int	nscount;		/* number of name servers */
	struct	sockaddr_in
		nsaddr_list[MAXNS];	/* address of name server */
#define	nsaddr	nsaddr_list[0]		/* for backward compatibility */
	u_short	id;			/* current packet id */
	char	defdname[MAXDNAME];	/* default domain */
	char	*dnsrch[MAXDNSRCH+1];	/* components of domain to search */
};
#endif

/*
 * Resolver options (keep these in synch with res_debug.c, please)
 */
#define RES_INIT	0x00000001	/* address initialized */
#define RES_DEBUG	0x00000002	/* print debug messages */
#define RES_AAONLY      0x00000004      /* authoritative answers only (!IMPL)*/
#define RES_USEVC	0x00000008	/* use virtual circuit */
#define RES_PRIMARY     0x00000010      /* query primary server only (!IMPL) */
#define RES_IGNTC	0x00000020	/* ignore trucation errors */
#define RES_RECURSE	0x00000040	/* recursion desired */
#define RES_DEFNAMES	0x00000080	/* use default domain name */
#define RES_STAYOPEN	0x00000100	/* Keep TCP socket open */
#define RES_DNSRCH	0x00000200	/* search up local domain tree */
#define RES_INSECURE1	0x00000400	/* type 1 security disabled */
#define RES_INSECURE2	0x00000800	/* type 2 security disabled */
#define RES_NOALIASES   0x00001000      /* shuts off HOSTALIASES feature */
#define RES_NOSYSLOG	0x01000000	/* syslog messages disabled */

#define RES_DEFAULT	(RES_RECURSE | RES_DEFNAMES | RES_DNSRCH)

/*
 * Resolver "pfcode" values.  Used by dig.
 */
#define RES_PRF_STATS	0x00000001
/*			0x00000002	*/
#define RES_PRF_CLASS   0x00000004
#define RES_PRF_CMD	0x00000008
#define RES_PRF_QUES	0x00000010
#define RES_PRF_ANS	0x00000020
#define RES_PRF_AUTH	0x00000040
#define RES_PRF_ADD	0x00000080
#define RES_PRF_HEAD1	0x00000100
#define RES_PRF_HEAD2	0x00000200
#define RES_PRF_TTLID	0x00000400
#define RES_PRF_HEADX	0x00000800
#define RES_PRF_QUERY	0x00001000
#define RES_PRF_REPLY	0x00002000
#define RES_PRF_INIT    0x00004000
/*			0x00008000	*/

/* hooks are still experimental as of 4.9.2 */
typedef enum { res_goahead, res_nextns, res_modified, res_done, res_error }
	res_sendhookact;

typedef res_sendhookact (*res_send_qhook)__((struct sockaddr_in * const *ns,
					      const u_char **query,
					      int *querylen,
					      u_char *ans,
					      int anssiz,
					      int *resplen));

typedef res_sendhookact (*res_send_rhook)__((const struct sockaddr_in *ns,
					      const u_char *query,
					      int querylen,
					      u_char *ans,
					      int anssiz,
					      int *resplen));

struct res_sym {
	int	number;		/* Identifying number, like T_MX */
	char *	name;		/* Its symbolic name, like "MX" */
	char *	humanname;	/* Its fun name, like "mail exchanger" */
};

extern struct __res_state _res;
extern const struct res_sym __p_class_syms[];
extern const struct res_sym __p_type_syms[];

_BEGIN_CPLUSPLUS
extern int 	dn_comp		__((const char *, u_char *, int, u_char **,
					u_char **));
extern int 	dn_expand	__((const u_char *, const u_char *,
					const u_char *, char *, int));
extern int	dn_skipname	__((const u_char *, const u_char *));
extern void	fp_nquery	__((const u_char *, int, FILE *));
extern void	fp_query	__((const u_char *, FILE *));
extern void	fp_resstat	__((struct __res_state *, FILE *));
#if defined(_REENTRANT) || defined(_THREAD_SAFE)
extern int	hostalias_r 	__((const char *, char *, int));
#else
extern char *	hostalias 	__((const char *));
#endif	/* _REENTRANT || _THREAD_SAFE */
extern u_int 	inet_nsap_addr 	__((const char *, u_char *, int));
extern char *	inet_nsap_ntoa 	__((int, const u_char *, char *));
extern const u_char * p_cdname	__((const u_char *, const u_char *, FILE *));
extern const u_char * p_cdnname	__((const u_char *, const u_char *, int,
					FILE *));
extern const char *   p_class 	__((int));
extern const u_char * p_fqname	__((const u_char *, const u_char *, FILE *));
extern const u_char * p_fqnname __((const u_char *, const u_char *,
					int, char *, int));
extern const char *   p_option	__((u_long));
extern void	      p_query	__((const u_char *));
extern const u_char * p_rr	__((const u_char *, const u_char *, FILE *));
extern char *	      p_time 	__((u_int));
extern const char *   p_type 	__((int));
extern void	putlong		__((u_int, u_char *));
extern void	putshort	__((u_short, u_char *));
extern void	res_close	__((void));
extern int	res_dnok	__((const char *));
extern int	res_hnok	__((const char *));
extern int 	res_init 	__((void));
extern int      res_isourserver __((const struct sockaddr_in *));
extern int	res_mailok	__((const char *));
extern int	res_mkquery	__((int, const char *, int, int, const u_char *,
					int, const u_char *, u_char *, int));
extern int	res_nameinquery __((const char *, int, int, const u_char *,
					const u_char *));
extern int	res_ownok	__((const char *));
extern int	res_queriesmatch __((const u_char *, const u_char *,
					const u_char *, const u_char *));
extern int 	res_query 	__((const char *, int, int, u_char *, int));
extern int 	res_querydomain __((const char *, const char *, int, int,
					u_char *, int));
extern u_int	res_randomid	__((void));
extern int 	res_search 	__((const char *, int, int, u_char *, int));
extern int 	res_send 	__((const u_char *, int, u_char *, int));
extern const char *   sym_ntop	__((const struct res_sym *, int, int *));
extern const char *   sym_ntos	__((const struct res_sym *, int, int *));
extern int	      sym_ston	__((const struct res_sym *, char *, int *));
_END_CPLUSPLUS
 
#endif /* _RESOLV_H_ */
