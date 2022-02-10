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
 * 
 * HINT: set tabstops to 4 
 *
 */
/*
 * HISTORY
 */
#pragma ident "@(#)$RCSfile: emx_data.c,v $ $Revision: 1.1.8.5 $ (DEC) $Date: 1999/01/26 14:49:54 $"


/* ----------------------------------------------------------------------
 *
 * emx_data.c - EMX driver data.c file
 *
 * Contains data structures used to pass static configuration data to
 * the EMX driver. This data primarily maps FC port names to CAM target
 * id assignments. It also allow the capability to provide per-instance
 * tuneable attributes.
 *
 * There are 2 types of data passed to the kernel.
 *    An attribute values that apply to a particular instance of an
 *      adapter (instance is 0 for emx0, 1 for emx1, etc).
 *    A CAM target ID assignment to FC Port mapping that applies to
 *      a port attached to a particular instance of an adapter.
 *
 * An array of each type of data is passed to the kernel.
 *  
 * ---------------------------------------------------------------------- */

/*
 * Pick up the definition of whether the driver is configured into
 * the kernel
 */
#include <emx.h>

/* This is being included by the kernel compilation process */
#if (NEMX > 0)


#include <io/cam/emx/emx_data.h>


EMX_ATTRIBUTE_RECORD        emx_attribute_records[] = {

    /* Insert records below here */

/*emx?  attribute_number        attribute_value */


    /* Insert records above here */

    /* end of array marker */
    TERMINAL_INSTANCE_NUMBER,
};





EMX_FCPID_RECORD            emx_fcpid_records[] = {

    /* Insert records below here */

/*emx? tgtid  FC Port Name                     FC Node Name */


    /* Insert records above here */

    /* end of array marker */
    TERMINAL_INSTANCE_NUMBER,
};


#endif /* (NEMX > 0) */


