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
 * @(#)$RCSfile: emx_data.h,v $ $Revision: 1.1.4.5 $ (DEC) $Date: 1999/01/26 14:49:58 $
 */

/* ----------------------------------------------------------------------
 *
 * emx_data.h - EMX driver data structures for emx_data.c file
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

#ifndef _EMX_DATA_H_
#define _EMX_DATA_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Record containing an Adapter Instance Attribute
 */

/* Attribute definitions */
#define EMX_ATTRIB_LINK_TYPE            0x01
#define EMX_ATTRIB_E_D_TOV              0x02
#define EMX_ATTRIB_R_A_TOV              0x03
#define EMX_ATTRIB_ARB_TOV              0x04
#define EMX_ATTRIB_R_T_TOV              0x05
#define EMX_ATTRIB_AL_TOV               0x06
#define EMX_ATTRIB_C_R_TOV              0x07
#define EMX_ATTRIB_C_I_TOV              0x08

typedef struct {
    unsigned int        instance;
    unsigned int        attribute_number;
    unsigned int        attribute_value;
} EMX_ATTRIBUTE_RECORD;

/*
 * Record containing SCSI ID to FC Port mappings
 */

#define NUM_SHORTS_IN_64BITS            4

typedef struct {
    unsigned int        instance;
             int        cam_tgt_id;
    unsigned short      port_name[NUM_SHORTS_IN_64BITS];
    unsigned short      node_name[NUM_SHORTS_IN_64BITS];
} EMX_FCPID_RECORD;

/*
 * 
 * NOTE: the 16bit FC Port Name and Node Name values are byte-swapped due
 *   to endian-ness of the machine (ex: 0x0050 is actually byte values
 *   50 followed by 00). Thus, when comparing with values with those
 *   reported by the HSG80, the following node names are equivalent:
 *       from HSG80:           5000-1fe1-0000-0770
 *       from emx.info: { ...  0x0050, 0xe11f, 0x0000, 0x7007 },
 */

/* instance number that indicates end of array */
#define TERMINAL_INSTANCE_NUMBER        0xFFFFFFFF

/*
 * NOTE:
 *   A cam_tgt_id value that is negative indicates that the corresponding
 *   FC Port Name and Node Name entry id mapping should be deleted from the
 *   persistent database.
 */

/*
 * these are the arrays being compiled at kernel build time
 * into emx_data.o
 */
extern EMX_ATTRIBUTE_RECORD     emx_attribute_records[];
extern EMX_FCPID_RECORD         emx_fcpid_records[];


#ifdef __cplusplus
}
#endif


#endif /* _EMX_DATA_H_ */

