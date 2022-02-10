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
 * @(#)$RCSfile: xpt.h,v $ $Revision: 1.1.16.3 $ (DEC) $Date: 1995/08/22 20:24:40 $
 */
#ifndef _XPT_INCL_
#define _XPT_INCL_

/* ---------------------------------------------------------------------- */

/* xpt.h		Version 1.09			Nov. 16, 1991 */

/*  This file contains the definitions and data structures for the Transport
    Layer, XPT, in the CAM subsystem.  This layer is responsible for 
    the CCB resource allocation, and the routing of CCB requests about
    the subsystem.

Modification History

	Version	  Date		Who	Reason

	1.00	06/28/90	jag	Creation date.
	1.01	09/13/90	jag	Added the DEC CAM packet definition.
	1.02	09/13/90	jag	Updated with the needs of xpt.c.
	1.03	12/10/90	jag	Moves some defines to cam.h.
	1.04	02/06/91	janet	Added additional comment above the
					DEC_CAM_PKT structure definition.
	1.05	03/29/91	jag	Changes for the Lock structures and 
					the PDrv structures.
	1.06	04/07/91	jag	Added the Q head lock init macro.
	1.07	06/04/91	jag	Added struct labels, Path Inq id, the 
					ifdef/define/endif include protection.
	1.08	07/03/91	jag	Added the defines for the cam_conftbl[]
					control structures, and the ASYNC
					wildcard define.
	1.09	11/16/91	jag	Added the structure version defines.
*/

/* ---------------------------------------------------------------------- */

/* This data structure is used by the XPT layer to keep free and busy
CCB structures w/in the allocation pool.  The XPT working set. */

typedef struct xpt_ws
{
    struct xpt_ws *x_flink;		/* forward pointer in the chain */
    struct xpt_ws *x_blink;		/* backward pointer in the chain */
    U32 xpt_flags;			/* flags for the status of this CCB */
    CCB_HEADER *xpt_ccb;		/* pointer to the CCB */
    U32 xpt_nfree;			/* # of times on the free side. */
    U32 xpt_nbusy;			/* # of times on the busy side. */
} XPT_WS;

#define	XPT_WS_VERS	2		/* please incr if XPT_WS changes */

/* ---------------------------------------------------------------------- */

/* The XPT Queue Header structure.  This structure contains a XPT
working set structure and a lock structure.  The XPT working set is used
to allow the Q walking code to use a consistant pointer for the queue. */

typedef struct xpt_qhead
{
    XPT_WS xws;			/* the Q head working set */
    U32 xpt_wait_cnt;		/* # of processes waiting */
    U32 xpt_times_wait;
    U32 xpt_ccb_limit;		/* # of ccb's maximum we can have */
    U32 xpt_ccbs_total;		/* Total number of ccbs held	*/
    simple_lock_data_t x_lk_qhead;	/* for locking on the control struct */
} XPT_QHEAD;

#define	XPT_QHEAD_VERS	2	/* please incr if XPT_QHEAD changes */

/* The IPL/SMP locking Macros for the Q head structure. */

#define XQHEAD_INIT_LOCK( qp )                         			\
{                                                      			\
    usimple_lock_setup( &((qp)->x_lk_qhead), cam_x_qhead_li ); 		\
}

#define XQHEAD_IPLSMP_LOCK( saveipl, qp )              			\
{                                                      			\
    (saveipl) = splbio();                              			\
    CAM_SPINLOCK( &((qp)->x_lk_qhead) ); 		  		\
}

#define XQHEAD_IPLSMP_UNLOCK( saveipl, qp )            			\
{                                                      			\
    CAM_SPINUNLOCK( &((qp)->x_lk_qhead) );  				\
    splx(saveipl);                                     			\
}

/* ---------------------------------------------------------------------- */

/* The XPT control structure is use for various functions w/in the XPT.
It is the common locking point for the cam_conftbl[] accesses.  Because the
cam_conftbl[] is not a "static" sized structure it can not be included in
a structure declaration.  So a seperate data structure is needed to contain
the misc flags/locks used with the cam_conftbl[]. */

typedef struct xpt_ctrl
{
    U32 xconf_flags;		/* controlling flags */
    simple_lock_data_t x_lk_ctrl;	/* for locking on the control struct */
} XPT_CTRL;

/* The IPL/SMP locking Macros for the control structure. */

#define XCTRL_INIT_LOCK( xp )                          			\
{                                                      			\
    usimple_lock_setup( &((xp)->x_lk_ctrl), cam_x_ctrl_li );  		\
}

#define XCTRL_IPLSMP_LOCK( saveipl, xp )               			\
{                                                      			\
    (saveipl) = splbio();                              			\
    CAM_SPINLOCK( &((xp)->x_lk_ctrl) );		        		\
}

#define XCTRL_IPLSMP_UNLOCK( saveipl, xp )             			\
{                                                      			\
    CAM_SPINUNLOCK( &((xp)->x_lk_ctrl) ); 	                        \
    splx(saveipl);                                     			\
}

/* ---------------------------------------------------------------------- */

/* This is the declaration for the header/CCB packet resource controlled 
by the XPT.  This structure contains the three headers used by the XPT, 
PDrvss, and the SIMs, followed by the CCB space.  It is expected that accesses
to this structure will be used via casting the XPT header pointer and 
some form of address arithmetic using the CCB pointers.

Note:  It is MANDITORY that the XPT working set be at the start of the packet.
Within the CAM code this knowledge is used in changing pointers by the 
routines that deal with the CCB pool.

Note:  It is MANDITORY that the SIM working set (SIM_WS) be just before the
CCB.  Within the SIM layer this knowledge is used to determine the SIM_WS
pointer. */

typedef struct dec_cam_pkt
{
    XPT_WS	xws;			/* XPT working set */
    PDRV_WS	pws;			/* PDrv working set */
    SIM_WS	sws;			/* SIM working set */
    CCB_SIZE_UNION ccb_un;		/* The CCB union for all CCBs */
} DEC_CAM_PKT;

/* ---------------------------------------------------------------------- */
/* This typedef is for the CCB opcode lookup table. */

typedef U32( *CCB_CMD_ENTRY )() ;		/* K&R p141 (future ref) */

/* ---------------------------------------------------------------------- */

/*
 * Peripheral driver access flags for a device.
 */

#define XPT_SHARED	0x00		/* Not exclusive (bit 0 is 0) */
#define XPT_EXCLUSIVE   0x01		/* Driver wants exclusive use */

/*
 * Priority of the cam callback routine.  It must be higher than the kds
 * callback so that the cam callback is called after the kds callback.
 */

#define XPT_PRIORITY    KDS_PRIORITY + 100

/* Misc defines used within the XPT code. */

#define XPT_PHEAD	0x80000000	/* signal the pool HEAD structure */
#define XPT_UPDIP	0x40000000	/* signal a pool update in progress */
#define XPT_ALLOC_SCHED 0x00000001	/* Scheduled the pool alloc to run */
#define XPT_ALLOC_ACT	0x00000002	/* The pool alloc is active */
#define XPT_RESOURCE_WAIT 0x00000004	/* We have a resource wait condition */
#define XPT_ALLOC_CALL	0x00000008	/* Has the allocator run	*/

#define XPT_BUSY	0x00000002	/* a busy packet in use */
#define XPT_FREE	0x00000001	/* a free packet for use */

/* ---------------------------------------------------------------------- */

#define XPT_PATH_INQ_ID 0xFF		/* XPT ID for a Path Inquiry CCB */
#define ASYNC_WILDCARD	-1		/* wildcard value in async callback */

#define XPT_ISR_CONTEXT	2		/* signal a call in interrupt context */

/*
 * Callback structure defines and locks
 */
typedef struct xpt_complete_que {
    XPT_WS *flink;
    XPT_WS *blink;
    U32 flags;
    U32 initialized;
    U32 count;
    simple_lock_data_t cplt_lock;
}XPT_COMPLETE_QUE;

#define XPT_CB_ACTIVE		0x00000001
#define XPT_CB_SCHED		0x00000002


#define XPT_CB_LOCK_INIT(ptr); {					\
    usimple_lock_setup( &((ptr)->cplt_lock), cam_cplt_li );		\
}
#define XPT_CB_LOCK(cb, spl); {						\
    spl = splbio();							\
    CAM_SPINLOCK( &((cb)->cplt_lock) );			 		\
}
#define XPT_CB_UNLOCK(cb, spl); {					\
    CAM_SPINUNLOCK( &((cb)->cplt_lock)); 				\
    splx(spl);								\
}

#define XPT_WS_REMOVE(xpt_ptr) remque((void *)(xpt_ptr))
#define XPT_WS_INSERT(xpt_ptr, where) insque((void *)(xpt_ptr), (void *)(where))

#define XPT_CB_WS_REMOVE(xpt_ptr) remque((void *)(xpt_ptr))
#define XPT_CB_WS_INSERT(xpt_ptr, where) insque((void *)(xpt_ptr), (void *)(where))

#define XPT_GET_WS_ADDR( ch ) (XPT_WS *)(((vm_offset_t )(ch)) - (((U32)sizeof(XPT_WS)) + ((U32)sizeof(PDRV_WS)) + ((U32)sizeof(SIM_WS))));

#define XPT_WAIT( q_ptr ); {						\
    thread_t thread = current_thread();					\
    (q_ptr)->xpt_wait_cnt++;						\
    assert_wait((vm_offset_t)&(q_ptr)->xpt_wait_cnt, FALSE);		\
    XQHEAD_IPLSMP_UNLOCK( s, q_ptr);					\
    thread_block();							\
    XQHEAD_IPLSMP_LOCK( s, q_ptr);					\
    (q_ptr)->xpt_wait_cnt--;						\
}

/*
 * Macros to translate logical IDs to/from physical addresses
 */

#define XPT_GET_LOG( st_ptr )						\
    camdb_trnpth(st_ptr)

#define XPT_GET_PHYS( st_ptr )						\
    camdb_trndid(st_ptr)

#endif /* _XPT_INCL_ */
