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
 * @(#)$RCSfile: usb_debug.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1998/04/27 21:28:48 $
 */
#ifndef _USB_DEBUG_H
#define _USB_DEBUG_H

/*
 * USB_FUNCQ turns on function level tracing.
 */
/*
#define USB_FUNCQ
*/

/*
 * Uncomment USB_DEBUG to turn on debug.  JANET - Change this
 * to use sysconfigtab
 */
/*
#define USB_DEBUG
*/

#if defined(USB_DEBUG)
#define USB_DPRINT printf
#else
#define USB_DPRINT
#endif

#define USB_FUNCTION(usb_fn_name) static char *usb_func = "usb_fn_name"

#ifdef USB_FUNCQ
#define USB_TRACE_REQUEST(request, string) {				\
    struct usbd_super_request *super_req = USB_REQUEST2SUPER(request);   \
    super_req->funcq_buf[super_req->funcq_index++] = (string);		\
    if (super_req->funcq_index == USB_REQUEST_FUNCQ)			\
        super_req->funcq_index = 0;					\
}
#else
#define USB_TRACE_REQUEST(request, string);
#endif

#endif /* _USB_DEBUG_H */
