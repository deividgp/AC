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
 * @(#)$RCSfile: shared_intr.h,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 1997/06/23 13:10:57 $
 */

#ifndef	_HAL_SHARED_INTR_H
#define _HAL_SHARED_INTR_H

#include <io/common/handler.h>

/*
 * Structure to control shared interrupts
 *
 * Elements are:
 *	next, prev	- queue pointers used by handler_add and handler_delete
 *	active		- queue pointer for active ISRs (used by handler_enable,
 *			handler_disable and shared interrupt dispatching).
 * 	startp		- pointer to ISR to begin shared interrupt dispatching.
 *	basep		- pointer to initial element on a queue.
 *	count		- number of active ISRs on queue
 *	flags		- status information
 *	intr		- ISR to call
 *	param  		- argument ot ISR
 *	level		- platform specific info (post may use it)
 *	scb_vec		- scb vector for this interrupt
 *	post		- rouinte to call after dispatch (platform supplies)
 */

struct shared_intr_info {
	struct shared_intr_info *startp;	/* starting dispatch point */
	struct shared_intr_info *activef;	/* queue of active ISRs on chain */
	struct shared_intr_info *activeb;	/* queue of active ISRs on chain */
	decl_simple_lock_data(, intr_act)	/* lock to protect active queue, count */
	int	(*intr)();			/* device isr to call */
	caddr_t	param;				/* device parameter */
	void	(*post)();			/* routine to call after dispatch */
	u_int	count;				/* number on active queue */
	caddr_t	level;				/* platform dependent (not used by the
						   shared_intr common code) */
	u_int	scb_vec;			/* scb vector */
	u_int	flags;				/* flags: see below */
	struct shared_intr_info *basep;		/* pointer to base of chain */
	struct shared_intr_info *next;		/* queue of ISR's sharing this chain */
	struct shared_intr_info *prev;		/* queue of ISR's sharing this chain */
	decl_simple_lock_data(, intr_add)	/* lock to protect next/prev queue */
};

/* defines */
#define	SHARED_INTR_FAILURE		(-1)
#define	SHARED_INTR_SUCCESS		(0)
#define	SHARED_INTR_FIRST_ENABLE	(1)
#define	SHARED_INTR_LAST_DISABLE	(1)

/* flags */
#define	INTR_SHARABLE	0x100
#define INTR_INUSE	0x200
#define	ISR_BAD_RETURN	0x400

/* macros */
#define IS_SHARABLE(s)	((s)->flags & INTR_SHARABLE)

typedef struct shared_intr_info shared_intr_info_t;

/* function prototypes */
extern shared_intr_info_t *shared_intr_init( u_int num_intr );
extern shared_intr_info_t *shared_intr_add( shared_intr_info_t *shared_intr,
		u_int index, caddr_t level, int scb_vec,
	        struct handler_intr_info *intr_infop, void (*post)());
extern int shared_intr_enable(shared_intr_info_t *sip);
extern int shared_intr_disable(shared_intr_info_t *sip);
extern int shared_intr_delete(shared_intr_info_t *sip);

#endif	/* _HAL_SHARED_INTR_H */
