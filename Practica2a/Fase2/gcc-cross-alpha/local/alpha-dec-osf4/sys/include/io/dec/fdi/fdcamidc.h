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
#pragma ident "@(#)$RCSfile: fdcamidc.h,v $ $Revision: 1.1.5.3 $ (DEC) $Date: 1994/05/24 22:58:21 $"
*/

/************************************************************************
 *
 * File:        fdcamidc.h
 * Date:        12-Aug-1991
 * Author:      Roger Morris
 *
 * Description:
 *      FDCAMIDC --  Floppy Driver Common Access Method,
 *                   Implementation-Dependent Constants
 *
 * Modification History:
 *    Version     Date          Who     Reason
 *
 *      1.00    12-Aug-91       rsm     Creation date.  
 *
 */

#ifndef FDCAMIDC_INCLUDE
#define FDCAMIDC_INCLUDE   1


#define FDCAM_STATUS_BLOCK_PRIVATE \
    long dma_retry_wait;               /* Number of ticks in .8 disk         */\
                                       /*  revolutions.                      */\
    long half_spin;                    /* Nulber of ticks in .5 disk revs.   */\
    long id1;                          /* Device-ID information.             */\
    long id2;                          /* Other implementation-specific info.*/\
    long lun_id;                       /* implementation-specific ID for the */\
                                       /*  specified drive.                  */\
    char rwv_pause;                    /* Used to return additional info     */\
                                       /*  from ll_rwv().  If ll_rwv() was   */\
                                       /*  successful, this will be set to   */\
                                       /*  0 if all was normal, 1 if retries */\
                                       /*  took place.                       */\



/* ************************************************************************* */
/*                                  Values assigned to fsb.additional_status */
/* ************************************************************************* */
/* Note, the symbols defined within each of the following enums may not be   */
/*  the same from implementation to implementation.  It is expected that     */
/*  the following will be used primarily for debugging of the device driver. */
/*                                                                           */
#define fdcam_PEC_MASK 0x08
enum fdcam_prog_err_code
    {
    FDCAM_PEC_xxxxx
    };

#define fdcam_ISC_MASK 0x08
enum fdcam_invalid_spec_code
    {
    FDCAM_ISC_xxxxx
    };

#define fdcam_FFC_MASK 0x08
enum fdcam_foreign_fmt_code
    {
    FDCAM_FFC_xxxxx
    };

#define fdcam_HEC_MASK 0x08
enum fdcam_hardware_err_code
    {
    FDCAM_HEC_xxxxx
    };


#endif /* FDCAMIDC_INCLUDE */
