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

#ifndef _GPC_H_
#define _GPC_H_

#include <io/dec/ws/pcxas.h>
#include <io/dec/ws/pcxal.h>

#ifdef _KERNEL

/* Don't need these due to switch table? */
/* extern ws_pointer  pcxas_mouse;
extern ws_hardware_type pcxas_softc[];
*/

/* Extern declarations for gpc driver functions */
extern int gpc_ctl_getcode(void);
extern int gpc_output(int c);

extern int gpc_input(void);
extern int gpc_ctl_input(void);
extern int gpc_output_noverify(int c);

extern void gpc_ctl_cmd(int c);
extern void gpc_ctl_output(int d);
extern void gpc_set_leds(int new_leds);

extern int gpc_init_keyboard(void);
extern int gpc_null(void);

#endif /* _KERNEL */

#endif /*_PCXAS_H_*/
