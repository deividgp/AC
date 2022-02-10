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
 * @(#)$RCSfile: inputdriver.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1998/06/26 19:21:28 $
 */

#ifndef _INPUTDRIVER_H_
#define _INPUTDRIVER_H_

#include <sys/param.h>
#include <sys/errno.h>
#include <sys/buf.h>
#include <kern/queue.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devio.h>
#include <io/common/devdriver.h>
#include <io/dec/ws/vsxxx.h>	
#include <io/dec/ws/slu.h>	
#include <sys/keysyms.h>
#include <sys/sysconfig.h>

extern ws_keyboard 	keyboard;
extern ws_pointer	mouse;
extern ws_hardware_type mouse_closure;

extern struct slu	slu;  
extern ws_pointer_report current_rep;
extern u_short		pointer_id;
extern char		*special_keys[];
extern int		special_keys_size;

/* This switch table is defined here for all PC (e.g. gpc driver)
 * keyboard/mouse devices. It is required when gpc is present in
 * system, but ws is not (e.g. Turbolaser). It will be initialized
 * with null values by gpc, and overwritten with actual function
 * pointers when pcxal/pcxas module configure routine is called.
 */

struct input_sw {
  int     (*register_kbd_device)(struct controller *ctlr); /* register kbd
															  with WS */
  int     (*register_pointer_device)(struct controller *ctlr); /* register
												  _pointer with WS*/
  int     (*register_kbd_ehm)(struct controller *ctlr); /* register kbd w/
														   ehm */
  int     (*register_pointer_ehm)(struct controller *ctlr); /* register po
															   inter w/ ehm */
  int     (*input_intr)(int ch);                     /* ws_input_intr */
  int     (*pointer_intr)(int status, int data);     /* mouse interrupt */
  void    (*init_keyboard)(ws_keyboard_state *lp);   /* init_keyboard */
  void    (*disable_keyboard)(void);                 /* disable_keyboard */
  int     (*init_pointer)(caddr_t handle);           /* init_pointer */
  void    (*enable_pointer)(caddr_t handle);         /* enable_pointer */
  int     (*enter_hot_swap_event)(    /* enter_hot_swap_event on Xqueue*/
								  int type, int device_num);
  cfg_status_t (*notify_evm_event)(    /* notify Event Mgr. of event */
								   caddr_t *handle, int event);
  ws_keyboard_state *kbd_softc;           /* keyboard softc structure */
  ws_hardware_type *mouse_softc;          /* mouse softc structure */
  ws_keyboard *kbd_device;                /* ws_keyboard definition */
  ws_pointer  *mouse_device;              /* ws_pointer definition */
  int  (*reserved_func)(void);            /* Reserved */
  caddr_t private1;                       /* Reserved for future use (e.g.
											 USB) */
  caddr_t private2;                       /* Reserved for future use */
};

/* These entry points are used by the keyboard/mouse interface layer */
extern int 	(*v_consputc)();
extern int 	(*v_consgetc)();
extern int 	(*vs_gdopen)();
extern int 	(*vs_gdclose)();
extern int 	(*vs_gdread)();
extern int 	(*vs_gdwrite)();
extern int 	(*vs_gdselect)();
extern int 	(*vs_gdkint)();		/* keyboard interrupt */
extern int 	(*vs_gdpint)();		/* pointer interrupt */
extern int	(*vs_gdmmap)();
extern int 	(*vs_gdioctl)();
extern int 	(*vs_gdstop)();

extern char *language_names[];
extern xcomp_t comp_seq[];

#endif /* _INPUTDRIVER_H_ */

