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
 * @(#)$RCSfile: error_event.h,v $ $Revision: 1.1.9.4 $ (DEC) $Date: 1997/07/10 21:08:14 $
 */
/*
 *
 *  FILE:	error_event.h
 *
 *  DESCRIPTION:
 * 	Contains the defines and data structure definitions 
 *	used by the kernel error event functions.
 *
 */

#ifndef _ERROR_EVENT_H_
#define _ERROR_EVENT_H_

#define EVENT_REFERENCE(ep) (ep)->reference++
#define EVENT_DEREFERENCE(ep) event_free(ep)

/*
 * Event entry created when registering a device and fucntion to be called
 * whenever the event_notify() routine indicates an error occurred for
 * the registered device.
 */
typedef struct event_entry {
	struct event_entry *flink;		/* forward link to next entry */
	struct event_entry *blink;		/* back link to next entry */
	dev_t 		   ee_dev;		/* dev_t for device to watch */
						/* only uses UNIT number */
	int                reference;           /* reference count */
	U32 		   ee_event_flags;	/* action flags */
	void 		   (*ee_error_func)();	/* function to be called when */
						/* an error occurs on dev */
	U32		   ee_reg_type;		/* registered type, see below */
						/* allows for deregistration */
						/* based on regsitered type. */
} EVENT_ENTRY;

/*
 * ee_event_flags definitions
 */
#define EV_DESTROY_EVENT 0x1 

/*
 * Event control structure - acts as anchor for event entries.
 */
typedef struct event_cntrl  {
	EVENT_ENTRY 	*ec_flink;	/* forward link to event entry */
	EVENT_ENTRY 	*ec_blink;	/* back link to event entry */
	lock_data_t     ec_lk_event;	/* lock structure */
} EVENT_CNTRL;

/*
 * The following is a list of the possible registered types.
 */
#define EV_AVAIL_MANAGER	0x01	/* Availability Manager driver */
					/* used for ASE */
#define EV_RCI_MANAGER          0x02    /* CAM RCI interface */
#define	EV_DTM_MANAGER		0x03	/* DT Mirror Interface */

/*
 * The following lists the possible return values from the error event
 * functions.
 */
#define EV_FAILURE 	0
#define EV_SUCCESS	1

/*
 * FIND_EVENT_ENTRY - searches from start_ptr to find an event entry for dev.
 */
#define FIND_EVENT_ENTRY(dev, start_ptr, event_ptr)	\
{							\
	find_event_entry(dev, start_ptr, event_ptr);	\
}

/*
 * ADD_EVENT_ENTRY - adds the event_ptr event entry at location event_loc.
 */
#define ADD_EVENT_ENTRY(event_ptr, event_loc)		\
{							\
	insque(event_ptr, event_loc);			\
}

/*
 * REMOVE_EVENT_ENTRY - removes the links to the event_ptr event entry.
 */
#define REMOVE_EVENT_ENTRY(event_ptr)			\
{							\
	remque(event_ptr);				\
}

/*
 * The following are locking macros for the error event control structure.
 *
 */


#define LOCK_IT(lk)	  			\
{						\
    if( !shutting_down ) usimple_lock((simple_lock_t)(lk)); \
}

#define UNLOCK_IT(lk)				\
{						\
    if( !shutting_down )  usimple_unlock((simple_lock_t)(lk)); \
}						\

#define LOCK_INIT() 							\
{		                                                        \
        usimple_lock_setup((simple_lock_t)&lk_event_cntrl, event_cntrl_li); \
}		

#define EVENT_INIT_LOCK()				\
{							\
    LOCK_INIT();					\
 }

#define EVENT_LOCK(saveipl)                		\
{                                                       \
    saveipl = splbio();                                 \
    LOCK_IT(&lk_event_cntrl);		         	\
}

#define EVENT_UNLOCK(saveipl)                       	\
{                                                       \
    UNLOCK_IT(&lk_event_cntrl);                     	\
    (void)splx(saveipl);                                \
}

#endif   /* _ERROR_EVENT_H_ */
