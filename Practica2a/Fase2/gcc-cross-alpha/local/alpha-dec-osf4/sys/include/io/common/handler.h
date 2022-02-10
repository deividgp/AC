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
 * @(#)$RCSfile: handler.h,v $ $Revision: 1.1.26.3 $ (DEC) $Date: 1998/05/11 19:14:39 $
 */

#ifndef _SYS_HANDLER_H_
#define _SYS_HANDLER_H_

#include <kern/lock.h>
#include <sys/types.h>

/* 
 * id type for opaque
 * use with machine dependent id functions:
 * handler_del, handler_enable, handler_disable.
 *
 * This field is used to represent the specific interrupt to be acted upon
 * as a result of handler_{del, enable, disable} calls.  The value of this
 * field is set from the handler_add call.  
 */
typedef char * ihandler_id_t;               

/*
 * The define for ihandler_id_t is needed prior to inclusion of devdriver.h.
 */
#include <io/common/devdriver.h>

/* 
 * Interrupt handler structure.
 *
 * This model of interrupt dispatching is based on the BUS as being the
 * means of interrupt dispatching for all drivers.  For this reason all
 * of the information needed to register an interrupt is considered to be
 * bus specific rather than attempting to represent all possible permutations
 * within the ihandler_t structure itself.  
 *
 * The original fields of the OSF version of this structure have been removed
 * to prevent against their accidental usage.  This was deemed perferable to
 * leaving "stale" fields around to allow a driver to compile but not actually
 * function. 
 */
typedef struct ihandler {
	ihandler_id_t	ih_id;			/* unique id */
        struct bus      *ih_bus;                /* Driver's bus struct */
	char 		*ih_bus_info;		/* Bus registration info */
} ihandler_t;

/*
 * Handler key structure.  
 *
 * This structure is allocated when a handler is
 * added via handler_add.  The purpose of this structure is to contain all
 * the information needed to dispatch off to the bus specific implementations
 * of handler_{del,enable,disable}.  To do this the main pieces of information
 * are the bus pointer which is used to find pointers to the bus specific
 * of handler_{del,enable,disable} routines and the bus_id_t field which 
 * allows the bus to identify which particular interrupt to act upon.
 */
struct handler_key {
	struct handler_key	*next;	   /* Pointer to next handler entry */
	struct handler_key	*prev;	   /* Pointer to prev handler entry */
	struct bus		*bus;	   /* Pointer to bus structure      */
	ihandler_id_t		bus_id_t;  /* Bus specific unique key       */
        unsigned int            state;     /* state info 		    */
	ihandler_id_t		key;	   /* Unique key for this entry     */
	lock_data_t		lock;	   /* MP lock			    */
};

/*
 * Allowable values of the "state" field of the handler_key structure:
 */
#define IH_STATE_ENABLED        0x01                    /* enable/disable */

/*
 * handler_intr_info structure.
 *
 * This generic structure is used to help improve cross-bus driver
 * independence, by defining an interrupt-info structure passed
 * in the ihandler_t structure at handler_add() time that has a format
 * that contains all the necessary information to add an intr. handler/isr
 * at driver configuration time.
 *
 * This structure and the associated call of handler_add() can be done
 * by static drivers as well as loadable drivers.  By using the
 * handler_add() interface, static drivers benefit by removing a code 
 * dependency in the sizer utility to generate a proper (target kernel) 
 * config file (since the driver isr name does not have to be known).
 *
 * Assumption(s): Controller- and/or bus-specific information not provided
 *		  in this data structure is contained in the controller-
 *		  or bus-specific data structure (or attached bus-specific
 *		  data structure) that the bus-specific handler_add*() 
 *		  function can extract to configure the isr properly.
 * 
 * Note: This data structure is a direct copy of the Turbo-Channel 
 * 	 tc_intr_info structure which provides binary compatibility with
 *	 legacy TC drivers, and source code compatibility across TC, PCI, &
 * 	 EISA drivers.
 */
struct handler_intr_info {
        caddr_t configuration_st;       /* Pointer to bus/controller struct */
        int (*intr)();                  /* Interrupt handler 		    */
        caddr_t param;                  /* param for interrupt handler      */
        unsigned int config_type;       /* Driver type, ADPT(bus) or CTLR   */
};
	
#define CONTROLLER_CONFIG_TYPE 0x01
#define ADAPTER_CONFIG_TYPE    0x03
#define SHARED_INTR_CAPABLE    0x100
#define DIST_INT_CLASS_MASK    0xfc000
#define DIST_INT_CLASS_ALL     0xfc000
#define CONFIG_TYPE_MASK       (0x3)
#define GET_CONFIG_TYPE(c)     ((c) & CONFIG_TYPE_MASK)
/*
 * The following are return values for interrupt service
 * routines that support sharing. Values are strange to
 * avoid accidental match from a driver that really doesn't
 * support interrupt sharing.
 */
#define INTR_SERVICED		(0x0ace)
#define INTR_NOT_SERVICED	(0x0123)

/*
 * defines for distributed interrupt classes.
 *
 * use bits 7:2 if config_type field.
 */

#define DRIVER_INT_CLASS_SHIFT 14 

/*
 * classes to be used by device drivers.
 * Appropriate class should be or'd in with
 * the configuration_st field of the intr_infop
 * structure before handler_add is called.
 *
 * By or'ing in one of these values, the driver
 * is indicating to the bus adapter code that
 * the interrupts for this device can be distributed
 * across multiple processors on an smp system.
 * This is an indication that the interrupt service
 * routine is smp safe.
 */
#define DIST_INT_CLASS_CAM 	(0x1 << DRIVER_INT_CLASS_SHIFT)
#define DIST_INT_CLASS_NETWORK 	(0x2 << DRIVER_INT_CLASS_SHIFT)
#define DIST_INT_CLASS_ATM	(0x3 << DRIVER_INT_CLASS_SHIFT)
#define DIST_INT_CLASS_INPUT	(0x4 << DRIVER_INT_CLASS_SHIFT)
#define DIST_INT_CLASS_GRAPHICS (0x5 << DRIVER_INT_CLASS_SHIFT)
#define DIST_INT_CLASS_USB      (0x6 << DRIVER_INT_CLASS_SHIFT)
#define DIST_INT_CLASS_RTC	(0x7 << DRIVER_INT_CLASS_SHIFT)
#define DIST_INT_CLASS_RESERVED (0x3f << DRIVER_INT_CLASS_SHIFT)

/*
 * Function prototypes
 */
extern ihandler_id_t * handler_add(ihandler_t *ih);
extern int	handler_del(ihandler_id_t *id);
extern int	handler_enable(ihandler_id_t *id);
extern int	handler_disable(ihandler_id_t *id);
#endif /* _SYS_HANDLER_H_ */

