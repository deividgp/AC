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
 * @(#)$RCSfile: pwrmgr.h,v $ $Revision: 1.1.2.3 $ (DEC) $Date: 1995/11/16 14:52:25 $
 */

#ifndef _DEC_PWRMGR_PWRMGR_H_
#define _DEC_PWRMGR_PWRMGR_H_
/*
 *	pwrmgr.h
 */
#include <sys/sysconfig.h>		/* subsystem definitions */
/*
 * Power Management Commands supported by Power Manager 
 */
#define PWRMGR_GET_SUMMARY		(CFG_OP_SUBSYS_MIN+0)
#define PWRMGR_GET_DEVINFO		(CFG_OP_SUBSYS_MIN+1)
#define PWRMGR_SET_DEVINFO		(CFG_OP_SUBSYS_MIN+2)
#define PWRMGR_REGISTER_DEVICE		(CFG_OP_SUBSYS_MIN+3)
#define PWRMGR_DEREGISTER_DEVICE	(CFG_OP_SUBSYS_MIN+4)
#define PWRMGR_POWER_DOWN		(CFG_OP_SUBSYS_MIN+5)
#define PWRMGR_POWER_UP			(CFG_OP_SUBSYS_MIN+6)
#define PWRMGR_BATTERY_LOW		(CFG_OP_SUBSYS_MIN+7)
#define PWRMGR_THERMAL_MELTDOWN		(CFG_OP_SUBSYS_MIN+8)

/*
 * NOTE ... you need to update this if you add a new subsystem
 * specfic operation
 */
#define PWRMGR_MAX_OP	PWRMGR_THERMAL_MELTDOWN
#define PWRMGR_MAX_FUNC ((PWRMGR_MAX_OP-CFG_OP_SUBSYS_MIN)+1)

/*
 * Power Management Handler capabilities
 */
#define PWRHND_SET_DEVINFO		0x1
#define PWRHND_GET_DEVINFO		0x2
#define PWRHND_POWER_UP			0x4
#define PWRHND_POWER_DOWN		0x8
#define PWRHND_NOTIFY_BATTERY		0x10
#define PWRHND_NOTIFY_THERMAL		0x20
#define PWRHND_NOTIFY_PWRUP		0x40
#define PWRHND_NOTIFY_PWRDN		0x80
#define PWRHND_NOTIFY_REGISTER		0x100
#define PWRHND_NOTIFY_DEREGISTER	0x200
#define PWRHND_USER_SPACE		0x400

/*
 * Power Management Device Types
 */
#define PWRMGR_DEV_CPU			0x1
#define PWRMGR_DEV_DISK			0x2
#define PWRMGR_DEV_TAPE			0x4
#define PWRMGR_DEV_GRAPHICS		0x8
#define PWRMGR_DEV_NETWORK		0x10
#define PWRMGR_DEV_MULTIMEDIA		0x20
#define PWRMGR_DEV_THERMAL		0x40
#define PWRMGR_DEV_BATTERY		0x80
#define PWRMGR_DEV_UI			0x100
#define PWRMGR_DEV_XSERVER		0x200

/*
 * Power Management power states
 */
#define MAX_POWER_STATE 3
#define PWRMGR_MAX_NAME 16
#define MAX_PRIVATE 1
/*
 * pwrmgr_devinfo data structure
 *
 *	Some fields are for use by the power manager (MGR), others by the
 *	clients (CLI). Non-tagged fields are used by both.
 */

#define PWRMGR_DEVINFO_VERSION 1
#define PWRMGR_SET_VERSION()

typedef struct pwrmgr_devinfo {
	struct pwrmgr_devinfo *next;	/* MGR: Linked list */
	struct pwrmgr_devinfo *previous;/* MGR: Linked list */
	char device_name[PWRMGR_MAX_NAME];/* CLI: unique name  */
	int device_type;		/* Defined device types:PWRMGR_DEV_* */
	int event_mask;			/* Events to notify handler about */
	int (*handler)();		/* Client's power management handler */
	caddr_t private[MAX_PRIVATE];	/* CLI: Client's private data */
	int global_enable;               /* Global Power management enable */
	int dev_enable;			/* Device's Power Management enable*/
	int power_state;		/* CLI: current power status of the client */
	int dwell_time[MAX_POWER_STATE];/* CLI: timing parameter */
	struct pwrmgr_devinfo *handle;	/* MGR: */
	u_long count;			/* CLI: client tracks it's changes  */
	int deregistered;		/* MGR: set to a 1 on deregistration */
} pwrmgr_devinfo_t;

/*
 * pwrmgr_dev_handles data structure
 */
struct pwrmgr_dev_handles {
	int count;
	caddr_t handles;
};



/*
 * functional prototypes for pwrmgr functions 
 */

#ifdef _KERNEL

cfg_status_t 
pwrmgr_get_summary(caddr_t indata,
		   ulong indata_size,
		   caddr_t outdata,       
		   ulong outdata_size);
cfg_status_t 
pwrmgr_get_devinfo(caddr_t indata,
		   ulong indata_size,
		   caddr_t outdata,       
		   ulong outdata_size);
cfg_status_t 
pwrmgr_set_devinfo(caddr_t indata,
		   ulong indata_size,
		   caddr_t outdata,       
		   ulong outdata_size);


cfg_status_t 
pwrmgr_register_device(caddr_t indata,
		       ulong indata_size,
		       caddr_t outdata,       
		       ulong outdata_size);

cfg_status_t 
pwrmgr_deregister_device(caddr_t indata,
			 ulong indata_size,
			 caddr_t outdata,       
			 ulong outdata_size);

cfg_status_t 
pwrmgr_power_down(caddr_t indata,
		  ulong indata_size,
		  caddr_t outdata,       
		  ulong outdata_size);

cfg_status_t 
pwrmgr_power_up(caddr_t indata,
		ulong indata_size,
		caddr_t outdata,       
		ulong outdata_size);

cfg_status_t 
pwrmgr_battery_low(caddr_t indata,
		   ulong indata_size,
		   caddr_t outdata,       
		   ulong outdata_size);

cfg_status_t 
pwrmgr_thermal_meltdown(caddr_t indata,
			ulong indata_size,
			caddr_t outdata,       
			ulong outdata_size);

#endif /* _KERNEL */

#endif /* _DEC_PWRMGR_PWRMGR_H_ */

