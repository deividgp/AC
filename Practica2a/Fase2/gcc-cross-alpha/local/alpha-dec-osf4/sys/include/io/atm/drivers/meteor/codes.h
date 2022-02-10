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
#pragma ident "@(#)$RCSfile: codes.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/28 16:25:25 $"

#ifndef _CODES_H_
#define _CODES_H_

/*
* Module Name:
*   codes.h
*   
* Abstract:
*   This module defines return and error codes.
*
* Authors:
*   DMW - Douglas M. Washabaugh
*
* Modification History:
*   Date       Name  Description 
*   08-Aug-94  DMW   Created.
*   28-Sep-94  TLR   Added _ATM_RESOURCES and _NO_PRIVILEGE
*   24-Oct-94  TLR   Added _PENDING
*   15-Dec-94  TLR   Added _CONGESTED
*   20-Feb-95  TLR   Added _NOT_IMPLEMENTED
*   21-Feb-95  TLR   Added _INSUFFICIENT_DATA and _SIGNALING_ERROR
*   07-Mar-95  DMW   Added _NOT_READY and _BUFFER_TOO_SMALL
*   28-Nov-95  TLR   Added _NOT_SUPPORTED
*
* Description:
*   A collection of common return codes.
--*/

/* Define argument errors first, so that value matches argument number. */

#define STATUS_K_SUCCESS             0
#define STATUS_K_ARG_1_BAD           1
#define STATUS_K_ARG_2_BAD           2
#define STATUS_K_ARG_3_BAD           3
#define STATUS_K_ARG_4_BAD           4
#define STATUS_K_ARG_5_BAD           5
#define STATUS_K_ARG_6_BAD           6
#define STATUS_K_ARG_7_BAD           7
#define STATUS_K_ARG_8_BAD           8
#define STATUS_K_ARG_9_BAD           9
#define STATUS_K_ARG_10_BAD          10
#define STATUS_K_ARG_11_BAD          11
#define STATUS_K_ARG_12_BAD          12
#define STATUS_K_ARG_13_BAD          13
#define STATUS_K_ARG_14_BAD          14
#define STATUS_K_ARG_15_BAD          15
#define STATUS_K_ARG_16_BAD          16
#define STATUS_K_ARG_17_BAD          17
#define STATUS_K_ARG_18_BAD          18
#define STATUS_K_ARG_19_BAD          19
#define STATUS_K_ARG_20_BAD          20
#define STATUS_K_ARG_21_BAD          21
#define STATUS_K_ARG_22_BAD          22
#define STATUS_K_ARG_23_BAD          23
#define STATUS_K_ARG_24_BAD          24
#define STATUS_K_ARG_25_BAD          25
#define STATUS_K_ARG_26_BAD          26
#define STATUS_K_ARG_27_BAD          27
#define STATUS_K_ARG_28_BAD          28
#define STATUS_K_ARG_29_BAD          29
#define STATUS_K_ARG_30_BAD          30

/* Leave undefined values for future expansion. Start at a round hex value. */

#define STATUS_K_FAILURE             32
#define STATUS_K_NOT_OPEN            33
#define STATUS_K_ALREADY_OPEN        34
#define STATUS_K_NOT_CLOSED          35
#define STATUS_K_ALREADY_CLOSED      36
#define STATUS_K_BUSY                37
#define STATUS_K_RESOURCES           38
#define STATUS_K_ATM_RESOURCES       39
#define STATUS_K_TIMEOUT             40
#define STATUS_K_ARGS_INCONSISTENT   41
#define STATUS_K_SW_FAULT            42
#define STATUS_K_HW_FAULT            43
#define STATUS_K_CONFIG_BAD          44
#define STATUS_K_NOT_FOUND           45
#define STATUS_K_NO_WORK_TO_DO       46
#define STATUS_K_NO_PRIVILEGE        47
#define STATUS_K_PENDING             48
#define STATUS_K_CONGESTED           49
#define STATUS_K_NOT_IMPLEMENTED     50
#define STATUS_K_INSUFFICIENT_DATA   51
#define STATUS_K_SIGNALING_ERROR     52
#define STATUS_K_NOT_READY           53
#define STATUS_K_BUFFER_TOO_SMALL    54
#define STATUS_K_MISMATCH            55
#define STATUS_K_REJECT              56
#define STATUS_K_NOT_SUPPORTED       57
#define STATUS_K_OUT_OF_RANGE        58
#define STATUS_K_NOT_ALIGNED         59
#define STATUS_K_READ_ONLY           60
#define STATUS_K_WRITE_ONLY          61
#define STATUS_K_INVALID_VC          62
#define STATUS_K_EEROM_ERROR         63

#endif	/* _CODES_H_ */
