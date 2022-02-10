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
 *	@(#)$RCSfile: proto_net.h,v $ $Revision: 4.3.43.2 $ (DEC) $Date: 1998/10/02 17:41:13 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0.1
 */
/*
 *	Revision History:
 *
 * 10-Oct-91	Heather Gray
 *	add if_isfull()
 *
 * 5-June-91	Heather Gray
 *	OSF 1.0.1 patches
 *
 */
#ifndef _PROTO_NET_H_
#define _PROTO_NET_H_

# define	P(s) s
/* Avoid scoping problems */
typedef union {
	struct sockaddr		*p1;
	struct socket		*p2;
	struct sockproto	*p3;
	struct mbuf		*p4;
	struct ifnet		*p5;
	struct ifqueue		*p6;
	struct ifaddr		*p7;
	struct ether_header	*p8;
	struct tty		*p9;
	struct slcompress	*p10;
	struct ip		*p11;
	struct in_addr		*p12;
	struct arpcom		*p13;
	struct domain		*p14;
	struct netisr		*p15;
	struct radix_node	*p16;
	struct radix_node_head	*p17;
	struct rawcb		*p18;
	struct route		*p19;
	struct rtentry		*p20;
	struct rt_metrics	*p21;
	struct sl_softc		*p22;
	struct arptab		*p23;
	struct screen_data	*p24;
	struct ifreq       	*p25;
	struct ether_driver   	*p26;
	struct endevp   	*p27;
} proto_net_union_t;

/* gw_screen.c */
int	screen_control P((struct socket *, int, caddr_t));
void	gw_forwardscreen P((struct mbuf *, int, int, void (*)(), void (*)(), struct route *, int));
void	gw_screen_init P((void));
void	screen_bufenter P((struct mbuf *, int, int, void (*)(), void (*)(), struct route *, int));
int	screen_getnext P((struct screen_data *));
void	screen_disposition P((u_int, int));
void	screen_purgeold P((void));
void	screen_cacheflush P((void));
void	screen_cacheinit P((void));
void	screen_cacheadd P((struct mbuf *, int, int, int));
int	screen_cachelookup P((struct mbuf *, int, int, int *));

/* if.c */
void	ifinit P((void));
void	ifubareset P((int));
void	ifreset P((int));
void	if_attach P((struct ifnet *));
void	if_sphysaddr P((struct ifnet *, struct ifreq *));
struct 	ifaddr *ifa_ifwithaddr P((struct sockaddr *));
struct	ifaddr *ifa_ifwithdstaddr P((struct sockaddr *));
struct	ifaddr *ifa_ifwithnet P((struct sockaddr *));
struct	ifaddr *ifa_ifwithaf P((int));
struct	ifaddr *ifaof_ifpforaddr P((struct sockaddr *, struct ifnet *));
void	ifa_addifa P((struct ifnet *, struct ifaddr *, int));
int	ifa_delifa P((struct ifnet *, struct ifaddr *));
void	link_rtrequest P((int, struct rtentry *, struct sockaddr *));
void	if_down P((struct ifnet *));
void	if_qflush P((struct ifqueue *));
int	if_isfull P((struct ifnet *));
void	if_slowtimo P((void));
struct	ifnet *ifunit P((char *));
int	ifioctl P((struct socket *, unsigned int, caddr_t));
int	ifconf P((unsigned int, caddr_t));

/* if_ethersubr.c */
int	ether_output P((struct ifnet *, struct mbuf *, struct sockaddr *,
			struct rtentry *));
void	ether_input P((struct ifnet *, struct ether_header *, struct mbuf *));
void	arpwhohas P((struct arpcom *, struct in_addr *));
int	arpioctl P((unsigned int, caddr_t));
int	arpresolve P((struct arpcom *, struct mbuf *, struct sockaddr *,
				u_char *, int *));
char	*ether_sprintf P((u_char *));
char 	*inet_ntoa P((struct in_addr, char *));
int	if_addmulti P((struct ifnet *, struct ifreq *));
int	if_delmulti P((struct ifnet *, struct ifreq *));

/* if_loop.c */
void	loinit P((void));
void	loattach P((void));
int	looutput P((struct ifnet *, struct mbuf *, struct sockaddr *,
			struct rtentry *));
int	loioctl P((struct ifnet *, unsigned int, caddr_t));

/* if_sl.c */
void	slattach P((void));
int	slopen P((dev_t, struct tty *));
void	slclose P((struct tty *));
int	sltioctl P((struct tty *, unsigned int, caddr_t, int));
int	sloutput P((struct ifnet *, struct mbuf *, struct sockaddr *,
			struct rtentry *));
void	slstart P((struct tty *));
void	slinput P((int, struct tty *));
int	slioctl P((struct ifnet *, unsigned int, caddr_t));

/* slcompress.c */
void	sl_compress_init P((struct slcompress *));
int	sl_compress_tcp P((struct mbuf *, struct ip *,struct slcompress *,int));
int	sl_uncompress_tcp P((u_char **, int, int, struct slcompress *));

/* netisr.c */
void	netinit P((int));
void	netisrinit P((void));
struct	netisr *netisr_lookup P((int));
int	netisr_add P((int, void (*)(void), struct ifqueue *, struct domain *,
			int));
int	netisr_del P((int));
int	netisr_input P((int, struct mbuf *, caddr_t, int));
int	netisr_af P((int));
void	netisr_timeout P((caddr_t));
void	Netintr P((void));
void	netisr_thread P((void));

/* netaf_config.c */
void	netinit_domains P((void));

/* radix.c */
struct	radix_node *rn_search P((caddr_t, struct radix_node *));
struct	radix_node *rn_search_m P((caddr_t, struct radix_node *, caddr_t));
#if SEC_NET
struct	radix_node *rn_match P((caddr_t, struct radix_node *, struct mbuf *, int *));
#else
struct	radix_node *rn_match P((caddr_t, struct radix_node *));
#endif
struct	radix_node *rn_match1 P((caddr_t, struct radix_node *, struct ifnet *,
			caddr_t));
struct	radix_node *rn_newpair P((caddr_t, int, struct radix_node *));
struct	radix_node *rn_insert P((caddr_t, struct radix_node *, int *,
			struct radix_node *));
struct	radix_node *rn_addmask P((caddr_t, int, int));
struct	radix_node *rn_addroute P((caddr_t, caddr_t, struct radix_node *,
			struct radix_node *));
struct	radix_node *rn_addroute1 P((caddr_t, caddr_t, struct radix_node *,
			struct rtentry *));
struct	radix_node *rn_delete P((caddr_t, caddr_t, struct radix_node *));
struct	radix_node *rn_delete1 P((caddr_t, caddr_t, struct radix_node *,
			struct ifnet *, caddr_t));
int	rn_inithead P((struct radix_node_head **, int, int));

/* raw_cb.c */
int	raw_attach P((struct socket *, int));
void	raw_detach P((struct rawcb *));
void	raw_disconnect P((struct rawcb *));
int	raw_bind P((struct socket *, struct mbuf *));

/* raw_usrreq.c */
void	raw_init P((void));
int	raw_input P((struct mbuf *, struct sockproto *,
			struct sockaddr *, struct sockaddr *));
void	raw_ctlinput P((int, struct sockaddr *, caddr_t));
int	raw_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
			struct mbuf *));

/* route.c */
void	rtinithead P((int, int, void (*)(struct sockaddr *,struct sockaddr *)));
void	rtalloc P((struct route *));
struct	rtentry *rtalloc1 P((struct sockaddr *, int));
struct	rtentry *rtalloc2 P((struct sockaddr *, int, struct ifnet *,
			struct sockaddr *));
void	rtallocNL P((struct route *));
struct	rtentry *rtallocNL1 P((struct sockaddr *, int));
struct	rtentry *rtallocNL2 P((struct sockaddr *, int, struct ifnet *,
			struct sockaddr *));
void	rtfree P((struct rtentry *));
void	rtfreeNL P((struct rtentry *));
void	rtredirect P((struct sockaddr *, struct sockaddr *, struct sockaddr *,
			int, struct sockaddr *, struct rtentry **));
int	rtioctl P((struct socket *, unsigned int, caddr_t));
struct	ifaddr *ifa_ifwithrouteifp P((int, struct sockaddr *, struct sockaddr *,
			struct ifnet *));
int	rtrequest P((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, int, struct rtentry **));
int	rtrequest1 P((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, int, struct rtentry **,
			struct ifnet *));
void	rt_maskedcopy P((struct sockaddr *, struct sockaddr *,
			struct sockaddr *));
int	rtinit P((struct ifaddr *, int, int));
void	rtscrub P((struct ifnet *, struct ifaddr *, u_char));

#if SEC_NET
/* SEC_NET route.c with data accreditation */
int	rtalloc_with_accred P((struct route *, struct mbuf *));
struct	rtentry *rtalloc1_with_accred P((struct sockaddr *, int, struct mbuf *, int*));
#endif

/* rtsock.c */
int	route_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
			struct mbuf *));
int	route_output P((struct mbuf *, struct socket *));
void	rt_setmetrics P((u_long, struct rt_metrics *, struct rt_metrics *));
void	m_copyback P((struct mbuf *, int, int, caddr_t));
void	rt_missmsg P((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, struct sockaddr *, int, int));
int	route_configure P((void));

/* pfilt.c */
struct	mbuf *pfilt_filter P((struct ether_driver *, struct mbuf *,
			struct ether_header *, int, unsigned short, int));
int	pfilt_attach P((struct ifnet *, struct endevp *));
int	pfilt_newaddress P((int, u_char *));
struct	mbuf *pf_mcopym P((struct mbuf *, int, int, int));

#undef P

#endif
