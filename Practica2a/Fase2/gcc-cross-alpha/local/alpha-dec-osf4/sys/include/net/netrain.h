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
 * @(#)$RCSfile: netrain.h,v $ $Revision: 1.1.8.3 $ (DEC) $Date: 1998/08/19 17:37:20 $
 */

#ifndef _NETRAIN_H_
#define _NETRAIN_H_

/* Misc definitions */

#define  NIT_UP           1
#define  NIT_DOWN         2
#define  NIT_DONT_KNOW    3
#define  RETURN_SUCCESS   0
#define  RETURN_FAILURE   1
#define  RETURN_WARNING   2

/* States */

#define  NR_STATE_INIT     1
#define  NR_STATE_READY    2
#define  NR_STATE_RETRY    3
#define  NR_STATE_FAILED   4
#define  NR_STATE_READY_T  5
#define  NR_STATE_RETRY_T  6
#define  NR_STATE_FAILED_T 7
#define  NR_STATE_DOWN     8

/* Change state macro. This macro moves the new state into the
 * low byte of the state field (int). The shift operation is to
 * save the last 3 states for debugging. The mask strips the previous
 * states out of the state field.
 */
#define NR_NEW_STATE(instance,state) instance->nr_state = (instance->nr_state << 8) | state
#define NR_STATE_MASK 0xFF

/* NetRAIN device name prefix. */
#define NR_NAME_PREFIX "nr"

/* Netrain device counts. */
#define NR_MAXDEV 512            /* Max */
#define NR_DEVICES 128           /* Default - overridden in sysconfigtab */

/* Local MAC address bit. This bit is set in the high order nibble of
 * an ethernet MAC address to indicate that it is a locally administered
 * address. 
 */
#define NR_LOCAL_MAC_BIT 2

/* Undefined device type. */
#define NR_TYPE_UNKNOWN 0

struct nr_instance * get_instance(struct ifnet*);

/* Flags:
 * The MONITOR flag indicates that monitoring on this interface
 * was explicitly requested via the SIOCIFMONITOR command. If
 * The interface is being monitored and is NOT a member of a 
 * NetRAIN set, the NetRAIN unit number is set to NR_UNIT_NOTMEMBER
 */

#define  NR_FLAGS_MONITOR  1
#define  NR_UNIT_NOTMEMBER -1

/* Timeout Values 
 *
 * The first three values are counters which per interface based on their
 * state. Each time the isr routine runs it decrements this count. When
 * the count reaches 0, a test is performed on the interface.
 *
 * NR_TIMEOUT         This is the time the test procedure waits between
 *                    reading counters.
 * NR_TIMEOUT_SUCCESS This is the time between tests when the previous test
 *                    succeeded.
 * NR_TIMEOUT_RETRY   This is the timeout between tests when the previous
 *                    test failed but hasn't failed NR_MAX_RETRY times.
 * NR_TIMEOUT_FAILED  This is the timeout between tests when the previous
 *                    NR_MAX_RETRY tests have failed.
 * NR_TIMEOUT_ISR     This is the timeout for the interrupt service routine
 *                    which handles all the timers. The other timers are really
 *                    Counts loaded into the timeout field of an interfaces
 *                    instance block. On each pass of the interrupt service
 *                    routine, the count is decremented. When the count reaches
 *                    zero, a new test is initiated for that interface.
 * NR_MAX_RETRY       Number of times the operational test must fail before
 *                    the state of the interface is changed from NR_STATE_RETRY
 *                    to NR_STATE_FAILED and the failover process is started.
 */
#define  NR_TIMEOUT          1
#define  NR_TIMEOUT_SUCCESS  3
#define  NR_TIMEOUT_RETRY    1
#define  NR_TIMEOUT_FAILED   5
#define  NR_TIMEOUT_DOWN     10
#define  NR_TIMEOUT_ISR      1000            /* Default netrain_isr timeout */
#define  NR_MAX_TIMEOUT      2147483647      /* Max netrain_isr timeout */
#define  NR_MAX_RETRIES      2147483647      /* Maximum number of retries */
#define  NR_RETRIES          4               /* Default number of retries. */


ndecl_lock_data(extern, nrlist_lock)
#define NRLIST_LOCKINIT()   ulock_setup(&nrlist_lock,  nrlist_li, TRUE)
#define NRLIST_READ_LOCK()  ulock_read(&nrlist_lock)
#define NRLIST_WRITE_LOCK() ulock_write(&nrlist_lock)
#define NRLIST_UNLOCK()     ulock_done(&nrlist_lock)
#define NRLIST_ISLOCKED()   (lockmode==0||lock_holder(&nrlist_lock))

/* NetRAIN softc definition */

struct nr_softc {
    struct      ether_driver is_ed;     /* driver */
#define is_ac   is_ed.ess_ac            /* common part */
#define ztime   is_ed.ess_ztime         /* Time since last zeroed */
#define is_if   is_ac.ac_if             /* network-visible interface */
#define is_addr is_ac.ac_enaddr         /* hardware address */

    decl_simple_lock_data(, nr_softc_lock)
};

/* Interface instance structure */

struct nr_instance {
    struct   nr_instance *nr_next;      /* Next netrain instance */
    int      nr_flags;                  /* Flags field */
    int      nr_state;                  /* Current state of this interface */
    struct   ifnet *nr_ifp;             /* Ifnet pointer */
    int      nr_unit;                   /* Unit number for netrain set */
    int      nr_retries;                /* Number of failed retries */
    int      nr_tmo;                    /* Timeout period for this interface */
    int      nr_status;                 /* Previous known status */
    int      nr_timeout;                /* Timeout between reading counters */
    int      nr_timeout_success;        /* Timeout between tests when previous was success */
    int      nr_timeout_retry;          /* Timeout between tests when previous failed */
    int      nr_timeout_failed;         /* Timeout between tests when previous 
	        			   max_retry failed */
    int      nr_timeout_down;           /* Timeout between tests when interface marked down */
    int      nr_autotmo;                /* Autofail timeout */
    int      nr_autofail;               /* Autofail timer value */
    struct nr_cntrs_data *nr_data;      /* Pointer to nr_cntrs_data */
};


/*
 * Private data for instance of the Network Interface Test class.
 */
struct nr_cntrs_data {
	struct in_addr	intaddr;	/* Address of interface.	*/
	struct in_addr	netmask;	/* Netmask for network.		*/
	struct in_addr	addrToPing;	/* A suggestion for target to ping*/
	char		int_name[24];	/* name of interface		*/
	struct ctrreq	*before_cntrs;
	struct ctrreq	*after_cntrs;
	struct ifdevea	hwaddr;
	char            name[IFNAMSIZ]; /* Device name "ln"             */
	short           unit;           /* Unit #                       */
	struct socket	*xid_sock;	/* Socket for xid sends		*/
	int		use_icmp;	/* If on ICMP pings only.	*/
	struct timer_request *trp;	/* For timing things.		*/
	int		registered;	/* Indicates if registered with */
					/* icmp object			*/
	struct retry_data *retry_data;
	int		num_active_hosts;/* Number of hosts in 		*/
					/* active_hosts queue.		*/
	int		num_clients;	/* Number of hosts in clients 	*/
					/* queue.			*/
	int		num_waiting;	/* Number of hosts in 		*/
					/* active_hosts queue.		*/
	int		refcount;	/* Number of objects in clients */
					/* list.			*/
	int		retries;	/* How many retries have we done*/
					/* so far.			*/
	int		last_status;	/* Last status sent to clients.	*/
	int		nlist_ok;	/* Found arp table in kernel	*/
	int		cannot_zero;	/* Set if can't zero interface  */
					/* counters.			*/
};


/* Function prototype */

void   netraininit();
int    netrain_ioctl(struct socket *, unsigned int, caddr_t);
void   netrain_isr(void);
int    nr_xid_send(struct ifnet *, struct nr_instance **);
void   nr_xid_disc(struct ifnet *, struct nr_instance *);
int    nr_xid_conn(struct ifnet *, struct nr_instance **);
int    nr_get_cntrs(struct ctrreq *, int, int *, struct ifnet *);
int    nr_cntrs_wrapped(struct ctrreq *);
int    nr_cmp_cntrs(struct ctrreq *, struct ctrreq *, int *);
void   netrain_cntrs_destroy(struct nr_instance *);
int    netrain_add_device(struct ifnet *, int);
int    netrain_delete_device(struct ifnet *, int);
int    nr_failed_device(struct nr_instance *);
int    nr_get_unit(register char *);
void   netrain_event(struct ifnet *);
struct nr_instance *nr_get_instance(struct ifnet *);
int    netrain_switch(struct ifnet*);
int    nr_relock_nrlist(struct ifnet*, struct nr_instance**);

struct ifnet *nr_init_softc(int);
void   nr_init(int);
int    nr_start_locked(struct nr_softc*, struct ifnet*);
void   nr_start(register struct ifnet*);
void   nr_watch(int);
void   nr_reset(int, int);
void   nr_reset_locked(struct nr_softc*, struct ifnet*, int);
int    nr_ioctl(register struct ifnet*, register u_int, register caddr_t);


#endif
