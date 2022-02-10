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
 * @(#)$RCSfile: otto_flow.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1997/03/27 13:27:34 $
 */
#if !defined(_OTTO_FLOW_H_)
#define _OTTO_FLOW_H_

/* fc: Interface to perform AN2 flow control (FLOWmaster) credit
   resynchronization.

   It is intended that this interface be used by a network device driver,
   which is referred to as "the driver" below.

   In the following description, "[a, b]" denotes an inclusive range
   from a to b */

/* There should be one "struct fc_state" per network interface that does
   flow control.
   The structure is opaque to the driver.   It's allocated by fc_init.
   The driver is responsible for keeping the pointer to the structure,
   and passing it to other routines in this interface when they are called. */
struct fc_state;

/* This is needed only because the MIPS C compiler is broken
   with repect to function prototypes in procedure-valued struct fields. */
#ifdef __STDC__
#define _(x) x
#else
#define _(x) ()
#endif


typedef int fc_locktmp_t;	/* The return value of the locking routine.
				   See "lock" procedure in 
				   "struct fc_controller_state" below. */

#define FC_INFINITE_MS	((unsigned) ~0)	/* an infinite number of milliseconds */
#define FC_LASTVC	(OTTO_MAXVC-1)	/* the last VC that can be in a range */

/* This data is allocated by the "fc" implementation and is available
  for use by the driver's "mstowait" procedure to keep state between
  calls to mstowait for the same credit synchronization request. */
#define FC_NACKSTATEWORDS 4
struct fc_ackstate {
	union {
		void *ptr;
		unsigned long ulng;
	} uu[FC_NACKSTATEWORDS];
};

/* LOCKING
   Every procedure in this interface, and all the callbacks in the 
   "struct fc_controller_state" record below (with the exception of
   "lock") require that they be called under a mutual exclusion lock
   provided by the driver.   Normally, this will be the "softc lock" of
   the network interface; this allows the driver to operate on the
   interface's data structures when it is called back.

   The lock is called the "fcs lock" in the rest of this interface.
   */


/* This record should be filled in by the driver, and passed to fc_init
   when it is called for this network interface.

   The procedures in the record may be called back by the implementation
   of the fc interface.     */
struct fc_controller_state {
	void *arg;
	/* This pointer is passed as first argument to all the callbacks
	   below.  The driver should use it to store its context for
	   the callbacks. */

	fc_locktmp_t (*lock) _((void *arg));
	/* "lock" should acquire the fcs lock.   It may return
	   a value of type fc_locktmp_t, which will be passed to unlock
	   when the fc implementation releases the lock.  See the
	   section on LOCKING above. */

   	void (*unlock) _((void *arg, fc_locktmp_t s));
	/* "unlock" should release the fcs lock.   The value "s"
	   was the value returned by the last call to "lock" with the
	   argument "arg".  See the section on LOCKING above. */

	unsigned (*mstowait) _((void *arg, unsigned first, unsigned last,
			unsigned firstcall, struct fc_ackstate *as));
	/* "mstowait" should return the number of milliseconds before
	   the network interface will have sent all outstanding ACKs
	   for flow controlled VCs in the range [first, last].   If the
	   driver cannot compute such a delay, it should return 0 if
	   there are no outstanding ACKs for the VCs, and
	   FC_INFINITE_MS if there are.  The fc implementation can then
	   poll the driver by calling mstowait until it returns 0 (note
	   however that it may time out the request, so the driver may
	   not assume that it will be called back.)   "firstcall" will
	   be true iff this is the first call of mstowait for a given
	   credit resync request.   If "firstcall" is true, "*as" has
	   undefined contents.  Otherwise, "*as" has the same contents
	   as it had after the last call to mstowait for this credit
	   resync request.  Called with the fcs lock held.  See the
	   section on LOCKING above. */

	void (*stopcircuits) _((void *arg, unsigned first, unsigned last));
        /* "stopcircuits" should cause flow controlled VCs in the range
           [first,last] to stop sending cells temporarily.  The VCs 
           will be restarted by a subsequent call to startcircuits.
           After this call, if the network interface is called on to transmit
           a packet with "send" (below), that packet must follow any 
           cells on VCs in [first,last] that the interface commited to 
           sending before the call to stopcircuits.
	   Called with the fcs lock held.  See the section on LOCKING above. */

	void (*startcircuits) _((void *arg, unsigned first, unsigned last,
		unsigned adjustcredits));
	/* "startcircuits" should allow VCs in the range [first,last]
	   that were previously stopped by a call to stopcircuits to
	   send cells once more.  If "adjustcredits" is no-zero, the credits
	   for the circuits shouod be set to their initial values.
	   Called with the fcs lock held.  See the section on LOCKING above. */

	void (*send) _((void *arg, unsigned char *p, unsigned l));
	/* "send" should send the "l" byte of data starting at address "p"
	   on the flow control resync VC (which is founf from the DEC MIB)
	   with null encapsulation.
	   Called with the fcs lock held.  See the section on LOCKING above. */

	void (*zaplink) _((void *arg));
	/* "zaplink" should cause the driver to drop carrier on the link
	   for long enough for the far end to notice, then restore it.
	   This will cause the connected switch to drop cells in its input
	   buffers.   This is called as an emergency measure when several
	   attempts to resync credits have failed, in case the network
	   is deadlocked.
	   Called with the fcs lock held.  See the section on LOCKING above. */
};

/* "fc_init" initializes the flow control resync data structures for
   a network interface and returns a pointer to a "struct fc_state",
   or returns the nil pointer indicating an error.
   On success, the pointer returned should be passed to all other
   routines in the fc interface when they are called on behalf of this
   network interface.

   "*fccs" should be a filled-in by the driver prior to the call of fc_init.
   The value of "*fccs" (rather than the value of "fccs") will be
   copied by fc_init.

   fc_init should be called only once per network interface.  
   It is guaranteed to trigger no resync requests, and no callbacks to
   the driver.  It leaves flow control disabled.  It can be enabled
   with "fc_enable".
   Called with the fcs lock held.   See the section on LOCKING above. */
struct fc_state *fc_init (struct fc_controller_state *fccs);

/* "fc_restart" resets the flow control state machine to the same state
   that it was in just after fc_init() returned "fcs", except that old
   tokens are not reused in new packets.

   This operation should be called by the driver when the link loses carrier.
   It causes the fc module to beleive that flow control is disabled on the link.
   Called with the fcs lock held.   See the section on LOCKING above. */
void fc_restart (struct fc_state *fcs);

/* "fc_receive" should be called by the driver each time a packet is
   received on the flow control resynchronization VC (whose identity
   can be found via SNMP from the DEC MIB).  The packet must be in the
   "len" contiguous bytes starting with "*pkt".
   Called with the fcs lock held.   See the section on LOCKING above. */
void fc_receive (struct fc_state *fcs, unsigned char *pkt, unsigned len);

/* "fc_resync" initiates a flow control resynchronization for the VC
   range [first, last], or for some larger range that includes [first,
   last].   If "both" is non-zero, the peer is requested to resynchronize
   its end of the virtual circuits too.

   "fc_resync" may cause VCs to be stopped and restarted via
   the call backs provided to the fc_init procedure.  Credit
   resynchronization may not have completed when the procedure returns,
   but may proceed asynchronously; requests are said to be outstanding
   from the time that fc_resync is called and the time that the request
   completes.  The driver should be prepared to honour callbacks at any
   time, therefore.   If the driver makes additional calls to fc_resync
   for ranges that are already included by outstanding
   resynchronization requests, the new requests are ignored---the VCs
   will be resynchronizaed by the outstanding requests.

   This routine should be called by the driver on all VCs when carrier is
   regained on a link and on individual VCs or ranges when an outgoing
   VC is suspected to have lost credits (perhaps because it shows poor
   performance)
   Called with the fcs lock held.   See the section on LOCKING above. */
void fc_resync (struct fc_state *fcs, unsigned first, unsigned last,
	unsigned both);

/* "fc_enable" is used by the driver to indicate that the link 
   currently supports flow control.  
   The "fc" module will not send resync messages on links that do not
   support flow control.
   Called with the fcs lock held.  See the section on LOCKING above. */
void fc_enable (struct fc_state *fcs);

/* data set retrieved by get1, basically they are data from ad group  */
struct get1_data {
    char g1d_adUID[6];
    int g1d_adEscapeSupport;
    int g1d_adFlowMaster;
    int g1d_adRVC;
    int g1d_adObjectId;
    int g1d_adObjectSubId;
    int g1d_adNumPorts;
};

/* data set retrieved by get2, basically they are data from adPortTable group */
struct get2_data {
    int g2d_adpType;
    int g2d_adpSubType;
    int g2d_adpFlowMaster;
    int g2d_adpCreditResync;
    int g2d_adpResyncVCI;
    int g2d_adpReceiveBuffer;
    int g2d_adpPVCMin;
    int g2d_adpPVCMax;
    int g2d_adpSVCMin;
    int g2d_adpSVCMax;
    int g2d_adpRVCMin;
    int g2d_adpRVCMax;
    int g2d_adpBroadcastVCI;
    int g2d_adpArpVCI;
    int g2d_adpHomeVCI;
    int g2d_adpMaxReceiveBufferCounter;
};

#endif

