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
 * @(#)$RCSfile: pcxas_data.c,v $ $Revision: 1.1.10.2 $ (DEC) $Date: 1998/06/26 19:21:06 $
 */

#define _PCXAS_DATA_C_

#include <sys/param.h>
#include <sys/errno.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devio.h>
#include <sys/buf.h>

#include <io/dec/ws/pcxas.h>
#include <io/dec/ws/pcxal.h>

#ifdef BINARY

extern ws_hardware_type pcxas_mouse_closure;
extern ws_pointer pcxas_mouse;

#else /*BINARY*/

/* PCXAS-specific public pointer data */
/* the *real* pointer stuff is copied from here */
/* during console initialization early in boot-up, */
/* by the hardware-specific console init code; */
/* for example, the vsxxx pointer particulars are */
/* copied during scc_cons_init processing on flamingo */

ws_hardware_type pcxas_mouse_closure = {
    0,
    MS_PCXAS,
    3
};

/* FIXME FIXME - temporary entries */
int pcxas_do_nothing_int();
void pcxas_do_nothing_void();
/* FIXME FIXME - temporary entries */

extern ws_hardware_type mouse_closure;

/* FIXME - probably will need a tablet name someday... */
#endif BINARY
