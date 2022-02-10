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
 * @(#)$RCSfile: clnt.h,v $ $Revision: 1.1.18.2 $ (DEC) $Date: 1999/02/05 21:22:54 $
 */
/*	@(#)clnt.h	1.3 90/07/19 4.1NFSSRC SMI	*/

/* 
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *  1.31 88/02/08 SMI  
 */


/*
 * clnt.h - Client side remote procedure call interface.
 */

#ifndef _rpc_clnt_h
#define	_rpc_clnt_h
#include <kern/queue.h>		/* Need for cl_link, etc. */

#undef RPC_SUCCESS

/*
 * Rpc calls return an enum clnt_stat.  This should be looked at more,
 * since each implementation is required to live with this (implementation
 * independent) list of errors.
 */
enum clnt_stat {
	RPC_SUCCESS=0,			/* call succeeded */
	/*
	 * local errors
	 */
	RPC_CANTENCODEARGS=1,		/* can't encode arguments */
	RPC_CANTDECODERES=2,		/* can't decode results */
	RPC_CANTSEND=3,			/* failure in sending call */
	RPC_CANTRECV=4,			/* failure in receiving result */
	RPC_TIMEDOUT=5,			/* call timed out */
	RPC_INTR=18,                    /* call interrupted */
	/*
	 * remote errors
	 */
	RPC_VERSMISMATCH=6,		/* rpc versions not compatible */
	RPC_AUTHERROR=7,		/* authentication error */
	RPC_PROGUNAVAIL=8,		/* program not available */
	RPC_PROGVERSMISMATCH=9,		/* program version mismatched */
	RPC_PROCUNAVAIL=10,		/* procedure unavailable */
	RPC_CANTDECODEARGS=11,		/* decode arguments error */
	RPC_SYSTEMERROR=12,		/* generic "other problem" */

	/*
	 * callrpc & clnt_create errors
	 */
	RPC_UNKNOWNHOST=13,		/* unknown host name */
	RPC_UNKNOWNPROTO=17,		/* unkown protocol */

	/*
	 * _ create errors
	 */
	RPC_PMAPFAILURE=14,		/* the pmapper failed in its call */
	RPC_PROGNOTREGISTERED=15,	/* remote program is not registered */
	/*
	 * unspecified error
	 */
	RPC_FAILED=16

};

/*
 * Error info.
 */
struct rpc_err {
	enum clnt_stat re_status;
	union {
		int RE_errno;		/* realated system error */
		enum auth_stat RE_why;	/* why the auth error occurred */
		struct {
			u_int low;	/* lowest verion supported */
			u_int high;	/* highest verion supported */
		} RE_vers;
		struct {		/* maybe meaningful if RPC_FAILED */
			int s1;
			int s2;
		} RE_lb;		/* life boot & debugging only */
	} ru;
#define	re_errno	ru.RE_errno
#define	re_why		ru.RE_why
#define	re_vers		ru.RE_vers
#define	re_lb		ru.RE_lb
};

/*
 * Client rpc handle.
 * Created by individual implementations, see e.g. rpc_udp.c.
 * Client is responsible for initializing auth, see e.g. auth_none.c.
 */
typedef struct client {
	union {
		queue_head_t cl_u_link;		/* Sometimes we want double */
		struct client *cl_u_next;	/* sometimes single */
	} cl_u;
	struct tcp_sock *cl_tsp; /* NFS dynamically attaches tcp sockets */
	AUTH	*cl_auth;			/* authenticator */
	struct clnt_ops {
		enum clnt_stat	(*cl_call)();	/* call remote procedure */
		void		(*cl_abort)();	/* abort a call */
		void		(*cl_geterr)();	/* get specific error code */
		bool_t		(*cl_freeres)();/* frees results */
		void		(*cl_destroy)();/* destroy this structure */
		bool_t          (*cl_control)();/* the ioctl() of rpc */
	} *cl_ops;
	caddr_t			cl_private;	/* private stuff */
	sigset_t		cl_sigmask;	/* Interruptible or not */
} CLIENT;

#define cl_link cl_u.cl_u_link
#define cl_next cl_u.cl_u_next

/*
 * client side rpc interface ops
 *
 * Parameter types are:
 *
 */

/*
 * enum clnt_stat
 * CLNT_CALL(rh, proc, xargs, argsp, xres, resp, timeout)
 * 	CLIENT *rh;
 *	u_int proc;
 *	xdrproc_t xargs;
 *	caddr_t argsp;
 *	xdrproc_t xres;
 *	caddr_t resp;
 *	struct timeval timeout;
 */
#define	CLNT_CALL(rh, proc, xargs, argsp, xres, resp, secs)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, secs))
#define	clnt_call(rh, proc, xargs, argsp, xres, resp, secs)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, secs))

/*
 * void
 * CLNT_ABORT(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_ABORT(rh)	((*(rh)->cl_ops->cl_abort)(rh))
#define	clnt_abort(rh)	((*(rh)->cl_ops->cl_abort)(rh))

/*
 * struct rpc_err
 * CLNT_GETERR(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_GETERR(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))
#define	clnt_geterr(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))


/*
 * bool_t
 * CLNT_FREERES(rh, xres, resp);
 * 	CLIENT *rh;
 *	xdrproc_t xres;
 *	caddr_t resp;
 */
#define	CLNT_FREERES(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))
#define	clnt_freeres(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))

/*
 * bool_t
 * CLNT_CONTROL(cl, request, info)
 *      CLIENT *cl;
 *      u_int request;
 *      char *info;
 */
#define	CLNT_CONTROL(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in))
#define	clnt_control(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in))

/*
 * control operations that apply to both udp and tcp transports
 * (Not all are implemented in the kernel.)
 */
#define CLSET_TIMEOUT       1   /* set timeout (timeval) */
#define CLGET_TIMEOUT       2   /* get timeout (timeval) */
#define CLGET_SERVER_ADDR   3   /* get server's address (sockaddr) */
#define	CLGET_FD	    6   /* get connections file descriptor */
#define	CLSET_FD_CLOSE	    8   /* close fd while clnt_destroy */
#define	CLSET_FD_NCLOSE	    9   /* Do not close fd while clnt_destroy */
#define CLSET_XID	   10	/* Set xid for next request */
#define CLSET_CRED	   11	/* Set credentials for next request */
#define CLSET_SERVER_ADDR  12   /* Set server's address (sockaddr) */
#define CLGET_BUFBUSY      13   /* Return I/O in progress flag */

/*
 * udp only control operations
 */
#define CLSET_RETRY_TIMEOUT 4   /* set retry timeout (timeval) */
#define CLGET_RETRY_TIMEOUT 5   /* get retry timeout (timeval) */

/*
 * void
 * CLNT_DESTROY(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_DESTROY(rh)	((*(rh)->cl_ops->cl_destroy)(rh))
#define	clnt_destroy(rh)	((*(rh)->cl_ops->cl_destroy)(rh))


/*
 * RPCTEST is a test program which is accessable on every rpc
 * transport/port.  It is used for testing, performance evaluation,
 * and network administration.
 */

#define RPCTEST_PROGRAM		((u_int)1)
#define RPCTEST_VERSION		((u_int)1)
#define RPCTEST_NULL_PROC	((u_int)2)
#define RPCTEST_NULL_BATCH_PROC	((u_int)3)

/*
 * By convention, procedure 0 takes null arguments and returns them
 */

#define NULLPROC ((u_int)0)

/*
 * Timers used for the pseudo-transport protocol when using datagrams
 */
struct rpc_timers {
	u_short		rt_srtt;	/* smoothed round-trip time */
	u_short		rt_deviate;	/* estimated deviation */
	u_int		rt_rtxcur;	/* current (backed-off) rto */
};

/*
 * Feedback values used for possible congestion and rate control
 */
#define	FEEDBACK_REXMIT1	1	/* first retransmit */
#define	FEEDBACK_OK		2	/* no retransmits */

#define	UDPMSGSIZE	8800	/* rpc imposed limit on udp msg size */
#define	RPCSMALLMSGSIZE	400	/* a more reasonable packet size */

/*
 * Below are the client handle creation routines for the various
 * implementations of client side rpc.  They can return NULL if a 
 * creation failure occurs.
 */

/*
 * Copy error message to buffer.
 */
char *clnt_sperrno(/* enum clnt_stat num */);	/* string */


#ifdef KERNEL
/* UDP based RPC and common code used by TCP */
u_int		alloc_xid(void);
int		bindresvport(struct socket *);
enum clnt_stat	clntkudp_callit_addr(CLIENT *, u_int, xdrproc_t, caddr_t,
				     xdrproc_t, caddr_t, struct timeval,
				     struct sockaddr_in *, int);
CLIENT		*clntkudp_create(struct sockaddr_in *, u_int, u_int, int,
				 struct ucred *);
void		clntkudp_init(CLIENT *, struct sockaddr_in *,int,
			      struct ucred *);

unsigned int	clntkudp_settimers(CLIENT *, struct rpc_timers *,
				   struct rpc_timers *, unsigned int,
				   void (*)(), caddr_t, u_int);
void		rpcinit(void);

/* TCP based RPC */
struct tcp_sock   *clntktcp_checksock(CLIENT *, struct tcp_sock **);
enum   clnt_stat   clntktcp_connect(CLIENT *, struct sockaddr_in *);
CLIENT            *clntktcp_create(u_int, u_int);
enum   clnt_stat   clntktcp_freesock(struct tcp_sock *);
int                clntktcp_timeout(struct tcp_sock *, int, struct tcp_sock **);

/* Common code */
struct mbuf *mclgetx(void (*)(), caddr_t, caddr_t, int, int);

/*
 * Private data per rpc handle.  This structure is allocated by
 * clntkudp_create, and freed by cku_destroy.
 */
struct cku_private {
	u_int			 cku_flags;	/* see below */
	CLIENT			 cku_client;	/* client handle */
	int			 cku_retrys;	/* request retrys */
	struct socket		*cku_sock;	/* open udp socket */
	struct sockaddr_in	 cku_addr;	/* remote address */
	struct rpc_err		 cku_err;	/* error status */
	XDR			 cku_outxdr;	/* xdr routine for output */
	XDR			 cku_inxdr;	/* xdr routine for input */
	u_int			 cku_outpos;	/* position of in output mbuf */
	caddr_t			 cku_outbuf;	/* output buffer */
	char			*cku_inbuf;	/* input buffer */
	struct mbuf		*cku_inmbuf;	/* input mbuf */
	struct ucred		*cku_cred;	/* credentials */
	struct rpc_timers	*cku_timers;	/* for estimating RTT */
	struct rpc_timers	*cku_timeall;	/* for estimating RTT */
	void			(*cku_feedback)();
	caddr_t			cku_feedarg;	/* argument for feedback func */
	u_int			cku_xid;	/* current XID */
	udecl_simple_lock_data(,cku_lk_outbuf) 	/* SMP lock for mbuf data */
};
udecl_simple_lock_info(extern, cku_lk_outbuf_info) /* SMP stats */
/* MP locking macros associated with the cku_lk_outbuf member of cku_private. */
#define RPC_OUTBUF_LOCKINIT(cku_p)	\
			  usimple_lock_setup(&(cku_p)->cku_lk_outbuf, \
					      cku_lk_outbuf_info)
#define RPC_OUTBUF_LOCK(cku_p)     usimple_lock(&(cku_p)->cku_lk_outbuf)
#define RPC_OUTBUF_UNLOCK(cku_p)   usimple_unlock(&(cku_p)->cku_lk_outbuf)

#endif

#endif /*!_rpc_clnt_h*/
