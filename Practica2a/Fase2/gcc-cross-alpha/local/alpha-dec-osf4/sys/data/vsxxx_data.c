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
 * @(#)$RCSfile: vsxxx_data.c,v $ $Revision: 1.1.10.2 $ (DEC) $Date: 1998/06/26 19:21:08 $
 */
/************************************************************************
 *									*
 *			Copyright (c) 1990 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

/************************************************************************
 * Modification History
 * 3-March-93 -- Jay Estabrook
 *	       Created from ws_data.c for isolation of vsxxx info.
 *
 ************************************************************************/
#define _VSXXX_DATA_C_

#include <sys/param.h>
#include <sys/errno.h>
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devio.h>
#include <sys/buf.h>

#include <io/dec/ws/vsxxx.h>

#ifdef BINARY

extern ws_hardware_type		vsxxx_mouse_closure;
extern ws_pointer		vsxxx_mouse;


#else /*BINARY*/

/* vsxxx-specific public pointer data */
/* the *real* pointer stuff is copied from here */
/* during console initialization early in boot-up, */
/* by the hardware-specific console init code; */
/* for example, the vsxxx pointer particulars are */
/* copied during scc_cons_init processing on flamingo */

ws_hardware_type vsxxx_mouse_closure = {
    0,
    MS_VSXXX,
    3
};

extern ws_hardware_type mouse_closure;

/* FIXME FIXME - NULL function pointers should point to do_nothing routine */
extern void scc_enable_pointer(); /* to enable pointer interrupts */
#endif BINARY
