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
 *	@(#)$RCSfile: proto_uipc.h,v $ $Revision: 4.2.36.3 $ (DEC) $Date: 1998/06/26 04:10:09 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */

#ifndef _PROTO_UIPC_H_
#define _PROTO_UIPC_H_

# define	P(s) s
/* Avoid scoping problems */
typedef union {
	struct file	*p1;
	struct uio	*p2;
	struct ucred	*p3;
	struct stat	*p4;
	struct proc	*p5;
	struct socket	*p6;
	struct sockbuf	*p7;
	struct mbuf	*p8;
	struct msghdr	*p9;
	struct unpcb	*p10;
	struct domain	*p11;
	struct msgb	*p12;
} proto_uipc_union_t;

/* sys_socket.c */
int	soo_read P((struct file *, struct uio *, struct ucred *));
int	soo_write P((struct file *, struct uio *, struct ucred *));
int	soo_ioctl P((struct file *, unsigned int, caddr_t));
#ifdef __alpha
int	soo_select P((struct file *, int *, int *, int));
#else
int	soo_select P((struct file *, short *, short *, int));
#endif /* __alpha */
int	soo_stat P((struct socket *, struct stat *));
int	soo_close P((struct file *));

/* uipc_domain.c */
void	domaininit P((void));
int	domain_add P((struct domain *));
int	domain_del P((struct domain *));
struct	protosw *pffindtype P((int, int));
struct	protosw *pffindtype1 P((int, int, int *));
struct	protosw *pffindproto P((int, int, int));
struct	protosw *pffindproto1 P((int, int, int, int *));
void	pfctlinput P((int, struct sockaddr *));
void	pfreclaim P((void));
void	pfslowtimo P((void));
void	pffasttimo P((void));

/* uipc_mbuf.c */
void	mbinit P((void));
caddr_t	m_clalloc P((int, int));
caddr_t	m_clalloc2 P((struct mbuf *, int));
caddr_t	m_clalloc8 P((struct mbuf *, int));
void	mbufintr P((void));
struct	mbuf *m_retry P((int, int));
struct	mbuf *m_retryhdr P((int, int));
struct	mbuf *m_get P((int, int));
struct	mbuf *m_gethdr P((int, int));
struct	mbuf *m_getclr P((int, int));
struct	mbuf *m_free P((struct mbuf *));
void	m_freem P((struct mbuf *));
int	m_leadingspace P((struct mbuf *));
int	m_trailingspace P((struct mbuf *));
int	m_length P((struct mbuf *));
struct	mbuf *m_prepend P((struct mbuf *, int, int));
struct	mbuf *m_copym P((struct mbuf *, int, int, int));
void	m_copydata P((struct mbuf *, int, int, caddr_t));
void	m_cat P((struct mbuf *, struct mbuf *));
void	m_adj P((struct mbuf *, int));
struct	mbuf *m_pullup P((struct mbuf *, int));
struct	mbuf *m_pullup_exact P((struct mbuf *, int));
struct	msgb *mbuf_to_mblk P((struct mbuf *, int));
struct	mbuf *mblk_to_mbuf P((struct msgb *, int));

/* uipc_proto.c */
int	uipc_configure P((void));

/* uipc_socket.c */
int	socreate P((int, struct socket **, int, int));
int	sobind P((struct socket *, struct mbuf *));
int	solisten P((struct socket *, int));
void	sofree P((struct socket *));
void	solockpair P((struct socket *, struct socket *));
void	solock P((struct socket *));
void	solock1 P((struct socket *));
int	solocktry P((struct socket *));
int	solocktrynoassert P((struct socket *));
void	sounlock P((struct socket *));
void	sounlock1 P((struct socket *));
int	soclose P((struct socket *));
int	soabort P((struct socket *));
int	soaccept P((struct socket *, struct mbuf *));
int	soconnect P((struct socket *, struct mbuf *));
int	soconnect2 P((struct socket *, struct socket *));
int	sodisconnect P((struct socket *));
int	sosend P((struct socket *, struct mbuf *, struct uio *,
				struct mbuf *, struct mbuf *, int));
int	soreceive P((struct socket *, struct mbuf **, struct uio *,
				struct mbuf **, struct mbuf **, int *));
int	soshutdown P((struct socket *, int));
void	sorflush P((struct socket *));
void	sopriv P((struct socket *));
int	sosetopt P((struct socket *, int, int, struct mbuf *));
int	sogetopt P((struct socket *, int, int, struct mbuf **));
void	sohasoutofband P((struct socket *));
int	sodequeue P((struct socket *, struct socket **, struct mbuf **, int));
int	sogetaddr P((struct socket *, struct mbuf **, int, int));

/* uipc_socket2.c */
void	soisconnecting P((struct socket *));
void	soisconnected P((struct socket *));
void	soisdisconnecting P((struct socket *));
void	soisdisconnected P((struct socket *));
struct	socket *sonewsock P((struct socket *, int));
struct	socket *sonewsocknolock P((struct socket *, int, caddr_t*));
int	soqmvque P((struct socket *, int, int));
void	soqinsque P((struct socket *, struct socket *, int));
int	soqremque P((struct socket *, int));
void	socantsendmore P((struct socket *));
void	socantrcvmore P((struct socket *));
int	sosblock P((struct sockbuf *, struct socket *));
void	sbunlock P((struct sockbuf *));
int	sosbwait P((struct sockbuf *, struct socket *));
int	sosleep P((struct socket *, caddr_t, int, int));
void	sowakeup P((struct socket *, struct sockbuf *));
int	sbwakeup P((struct socket *, struct sockbuf *, int));
int	sbpoll P((struct socket *, struct sockbuf *));
int	soreserve P((struct socket *, u_int, u_int));
int	sbreserve P((struct sockbuf *, u_int));
void	sbrelease P((struct sockbuf *));
void	sbappend P((struct sockbuf *, struct mbuf *));
void	sbappendrecord P((struct sockbuf *, struct mbuf *));
void	sbinsertoob P((struct sockbuf *, struct mbuf *));
int	sbappendaddr P((struct sockbuf *, struct sockaddr *,
				struct mbuf *, struct mbuf *));
int	sbappendcontrol P((struct sockbuf *, struct mbuf *, struct mbuf *));
void	sbcompress P((struct sockbuf *, struct mbuf *, struct mbuf *));
void	sbflush P((struct sockbuf *));
void	sbdrop P((struct sockbuf *, int));
void	sbdroprecord P((struct sockbuf *));
int	lock_socheck P((struct socket *));
int	unlock_socheck P((struct socket *));
int	lock_sbcheck P((struct sockbuf *));
int	unlock_sbcheck P((struct sockbuf *));

/* uipc_syscalls.c */
int	socket P((struct proc *, void *, long *));
int	bind P((struct proc *, void *, long *));
int	listen P((struct proc *, void *, long *));
int	accept P((struct proc *, void *, long *));
int	oaccept P((struct proc *, void *, long *));
int	connect P((struct proc *, void *, long *));
int	socketpair P((struct proc *, void *, long *));
int	sendto P((struct proc *, void *, long *));
int	osend P((struct proc *, void *, long *));
int	osendmsg P((struct proc *, void *, long *));
int	sendmsg P((struct proc *, void *, long *));
int	recvfrom P((struct proc *, void *, long *));
int	orecvfrom P((struct proc *, void *, long *));
int	orecv P((struct proc *, void *, long *));
int	orecvmsg P((struct proc *, void *, long *));
int	recvmsg P((struct proc *, void *, long *));
int	shutdown P((struct proc *, void *, long *));
int	setsockopt P((struct proc *, void *, long *));
int	getsockopt P((struct proc *, void *, long *));
int	pipe P((struct proc *, void *, long *));
int	getsockname P((struct proc *, void *, long *));
int	ogetsockname P((struct proc *, void *, long *));
int	getpeername P((struct proc *, void *, long *));
int	ogetpeername P((struct proc *, void *, long *));
int	sendit P((int, struct msghdr *, int, long *));
int	recvit P((int, struct msghdr *, caddr_t, long *));
#ifdef	COMPAT_43
int	accept1 P((struct proc *, void *, long *, int));
int	recvfrom1 P((int));
int	getsockname1 P((struct proc *, void *, long *, int));
int	getpeername1 P((struct proc *, void *, long *, int));
#endif
void	sockaddr_new P((struct mbuf *));
void	sockaddr_old P((struct mbuf *));
int	sockargs P((struct mbuf **, caddr_t, int, int));
struct	file *getsock P((int, int *));

/* uipc_usrreq.c */
void	uipc_init P((void));
int	uipc_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
				struct mbuf *));
int	unp_attach P((struct socket *));
void	unp_detach P((struct unpcb *));
int	unp_bind P((struct unpcb *, struct mbuf *));
int	unp_connect P((struct socket *, struct mbuf *));
int	unp_connect2 P((struct socket *, struct socket *));
void	unp_disconnect P((struct unpcb *));
void	unp_abort P((struct unpcb *));
void	unp_shutdown P((struct unpcb *));
void	unp_drop P((struct unpcb *, int));
void	unp_drain P((void));
int	unp_externalize P((struct mbuf *));
int	unp_internalize P((struct mbuf *));
void	unp_gc P((void));
void	unp_dispose P((struct mbuf *));
void	unp_scan P((struct mbuf *, void (*)(struct file *)));
void	unp_mark P((struct file *));
void	unp_discard P((struct file *));

#undef P

#endif
