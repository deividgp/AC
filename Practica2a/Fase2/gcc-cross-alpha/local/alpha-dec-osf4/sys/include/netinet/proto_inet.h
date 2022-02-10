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
 *	@(#)$RCSfile: proto_inet.h,v $ $Revision: 4.3.52.3 $ (DEC) $Date: 1998/06/26 04:11:13 $
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
 *	add ip_dealloc()
 *
 * 5-June-91	Heather Gray
 *	OSF 1.0.1 patches.
 *
 */
#ifndef _PROTO_INET_H_
#define _PROTO_INET_H_

# define	P(s) s
/* Avoid scoping problems */
typedef union {
	struct arpcom		*p1;
	struct arptab		*p2;
	struct mbuf		*p3;
	struct ifnet		*p4;
	struct route		*p5;
	struct sockaddr		*p6;
	struct sockaddr_in	*p7;
	struct socket		*p8;
	struct in_addr		*p9;
	struct in_ifaddr	*p10;
	struct inpcb		*p11;
	struct ipq		*p12;
	struct ip		*p13;
	struct tcpcb		*p14;
	struct tcpiphdr		*p15;
	struct ipasfrag		*p16;
	struct ipoption		*p17;
	struct in_multi 	*p18;
	struct ip_moptions 	*p19;
	struct trn_header	*p20;
	struct icmp		*p21;
	struct in_afilt	 *p22;
	struct __inpcb_hashbucket *p23;
} proto_inet_union_t;

/* The tcp_seq typedef is a problem. Better to cast or rearrange? */
#define proto_tcp_seq	u_int

/* if_ether.c */
void	arpinit P((void));
void	arptimer P((void));
void	arpintr P((void));
void	arptfree P((struct arptab *));
void	arpoutput P((struct arpcom *, struct mbuf *, u_char *, u_short));
struct	arptab *arptnew P((struct in_addr *, struct ifnet *));
char	*arp_sprintf P((char *, u_char *, int));
void	arpinput P((struct arpcom *, struct mbuf *));
void	in_arpinput P((struct arpcom *, struct mbuf *, struct trn_header *));

/* igmp.c */
void	igmp_init P((void));
void	igmp_input P((struct mbuf *, int));
void    igmp_joingroup P((struct in_multi *));
void    igmp_leavegroup P((struct in_multi *));
void	igmp_fasttimo P((void));
void	igmp_slowtimo P((void));

/* ip_mroute.c */
void	ipip_input P((struct mbuf *, int));

/* in.c */
struct	in_addr in_makeaddr P((u_int, u_int));
u_int	in_netof P((struct in_addr));
void	in_sockmaskof P((struct in_addr, struct sockaddr_in *));
u_int	in_lnaof P((struct in_addr));
int	in_localaddr P((struct in_addr));
int	in_canforward P((struct in_addr));
int	in_control P((struct socket *, unsigned int, caddr_t, struct ifnet *));
void	in_ifscrub P((struct ifnet *, struct in_ifaddr *));
int	in_ifinitia P((struct ifnet *, struct in_ifaddr *, struct sockaddr_in *,
				int));
int	in_ifinitrt P((struct ifnet *, struct in_ifaddr *));
void	in_linkia P((struct ifnet *, struct in_ifaddr *, int));
struct	in_ifaddr *in_iaonnetof P((u_int));
int	in_broadcast P((struct in_addr));
struct	in_multi *in_addmulti P((struct in_addr *, struct ifnet *));
int	in_delmulti P((struct in_multi *));
void	inifaddr_hint P((void));
int	insert_inifaddrh P((struct in_addr, struct ifnet *, u_short));
void	remove_inifaddrh P((struct in_addr));

/* in_cksum.c or machine dependent */
int	in_cksum P((struct mbuf *, int));

/* in_pcb.c */
int	in_pcballoc P((struct socket *, struct inpcb *));
int	in_pcbbind P((struct inpcb *, struct mbuf *));
int	in_pcbconnect P((struct inpcb *, struct mbuf *));
int	in_pcbsnapconnect P((struct inpcb *, struct mbuf *, struct route *, struct sockaddr_in *));
int	in_fastpcbconnect P((struct inpcb *inp, struct sockaddr_in *sin));
void	in_pcbdisconnect P((struct inpcb *));
void	in_pcbdetach P((struct inpcb *));
void	in_pcbfree P((struct inpcb *));
void	in_pcbinsque P((struct inpcb *,	struct __inpcb_hashbucket *, struct inpcb *)) ;
void	in_pcbremque P((struct inpcb *)) ;

void	in_setsockaddr P((struct inpcb *, struct mbuf *));
void	in_setpeeraddr P((struct inpcb *, struct mbuf *));
void	in_pcbnotify P((struct inpcb *, struct sockaddr *, u_short,
				struct in_addr, u_short, int, void (*)()));
void	in_losing P((struct inpcb *));
void	in_rtchange P((struct inpcb *));
struct	inpcb *in_pcblookup P((struct inpcb *, struct in_addr,
				u_short, struct in_addr, u_short, int,
				struct __inpcb_hashbucket *));
struct	inpcb *in_pcbmatch P((struct inpcb *, struct in_addr,
				u_short, struct in_addr, u_short,
				struct __inpcb_hashbucket *));
struct	__inpcb_hashbucket *in_pcbhashalloc P((int));

/* in_proto.c */
int	inet_config ();		/* No prototypes here */

/* ip_icmp.c */
void	icmp_error P((struct mbuf *, int, int, struct in_addr));
void	icmp_input P((struct mbuf *, int));
void	icmp_reflect P((struct mbuf *));
struct	in_ifaddr *ifptoia P((struct ifnet *));
void	icmp_send P((struct mbuf *, struct mbuf *, int));
n_time	iptime P((void));

/* ip_input.c */
void	ip_init P((void));
void	ipintr P((struct ifqueue *));
struct	mbuf *ip_reass P((struct mbuf *, struct ipq *));
void	ip_dealloc P((struct mbuf *));
void	ip_freef P((struct ipq *));
void	ip_enq P((struct ipasfrag *, struct ipasfrag *));
void	ip_deq P((struct ipasfrag *));
void	ip_slowtimo P((void));
void	ip_reastimo P((struct ipq *));
void	ip_drain P((void));
int	ip_dooptions P((struct mbuf *));
struct	in_ifaddr *ip_rtaddr P((struct in_addr));
void	save_rte P((u_char *, struct in_addr));
struct	mbuf *ip_srcroute P((void));
void	ip_stripoptions P((struct mbuf *, struct mbuf *, struct ipoption *));
void	ip_forward P((struct mbuf *, int));
void	ip_forwardscreen P((struct mbuf *, int));
void	ip_outputscreen P((struct mbuf *, int, struct route *, int));
int     ip_accessfilter P((struct in_afilt *, struct ip *, struct mbuf *));

/* ip_output.c */
int	ip_output P((struct mbuf *, struct mbuf *, struct route *, 
				int, struct ip_moptions *));
struct	mbuf *ip_insertoptions P((struct mbuf *, struct mbuf *, int *));
int	ip_optcopy P((struct ip *, struct ip *));
int	ip_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int	ip_pcbopts P((struct mbuf **, struct mbuf *));
void	ip_mloopback P((struct ifnet *, struct mbuf *, 
				struct sockaddr_in *, int));

/* ip_screen.c */
void	ip_gwbounce P((struct mbuf *, int));
int	ip_cachesize P((void));
int	ip_cacheadd P((struct mbuf *, char *, int *));
int	ip_cachecmp P((char *, char *));

/* pmtu.c */

void	pmtu_init P((void));
void	pmtu_slowtimo P((void));
void	pmtu_dgtb_rcvd P((struct icmp *, struct sockaddr_in *));
void	tcp_rtchange P((struct inpcb *));
int	tcp_mss_send P((struct tcpcb *, struct rtentry *));
void	tcp_dgtb_rcvd P((struct inpcb *));

/* raw_ip.c */
void	rip_input P((struct mbuf *));
int	rip_output P((struct mbuf *, struct socket *));
int	rip_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int	rip_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
				struct mbuf *));

/* tcp_debug.c */
void	tcp_trace P((int, int, struct tcpcb *, struct tcpiphdr *, int));

/* tcp_input.c */
int	tcp_reass P((struct tcpcb *, struct tcpiphdr *, struct mbuf *));
void	tcp_input P((struct mbuf *, int));
void	tcp_dooptions P((struct tcpcb *, caddr_t, int, struct tcpiphdr *, int*, unsigned int *));
void	tcp_pulloutofband P((struct socket *, struct tcpiphdr *,
				struct mbuf *));
void	tcp_xmit_timer P((struct tcpcb *));
int	tcp_mss P((struct tcpcb *, u_short));

/* tcp_output.c */
int	tcp_output P((struct tcpcb *));
void	tcp_setpersist P((struct tcpcb *));

/* tcp_subr.c */
void	tcp_init P((void));
void	tcb_init P((struct inpcb*));
void	tcp_template P((struct tcpcb *));
void	tcp_respond P((struct tcpcb *, struct tcpiphdr *, struct mbuf *,
				proto_tcp_seq, proto_tcp_seq, int));
struct	tcpcb *tcp_newtcpcb P((struct inpcb *));
struct	tcpcb *tcp_drop P((struct tcpcb *, int));
struct	tcpcb *tcp_close P((struct tcpcb *));
void	tcp_drain P((void));
void	tcp_notify P((struct inpcb *, int));
void	tcp_ctlinput P((int, struct sockaddr *, caddr_t));
void	tcp_quench P((struct inpcb *));

/* tcp_timer.c */
void	tcp_fasttimo P((void));
void	tcp_slowtimo P((void));
void	tcp_canceltimers P((struct tcpcb *));
struct	tcpcb *tcp_timers P((struct tcpcb *, int));

/* tcp_usrreq.c */
int	tcp_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
				struct mbuf *));
int	tcp_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int	tcp_attach P((struct socket *));
struct	tcpcb *tcp_disconnect P((struct tcpcb *));
struct	tcpcb *tcp_usrclosed P((struct tcpcb *));

/* udp_usrreq.c */
void	udp_init P((void));
void	udp_input P((struct mbuf *, int));
struct	mbuf *udp_saveopt P((caddr_t, int, int));
void	udp_notify P((struct inpcb *, int));
void	udp_ctlinput P((int, struct sockaddr *, caddr_t));
int	udp_output P((struct inpcb *, struct mbuf *, struct mbuf *,
				struct mbuf *));
int	udp_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
				struct mbuf *));
#undef P

#endif

