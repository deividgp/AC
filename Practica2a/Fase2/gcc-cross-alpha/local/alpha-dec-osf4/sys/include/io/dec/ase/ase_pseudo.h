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
 * @(#)$RCSfile: ase_pseudo.h,v $ $Revision: 1.1.3.2 $ (DEC) $Date: 1995/12/21 19:23:49 $
 */
/*
 * Support for LSM devices that are under control of DECsafe ASE.
 *
 * DECsafe needs file systems' devices to have identical dev_t's on all hosts
 * in the ASE.  Since LSM doesn't guarantee that /dev/vol/dgfoo/volbar
 * will have the same major,minor numbers on host_A and host_B, ASE crates
 * pseudodevices /dev/ase_XXX (which *do* have like dev_t's) and provides a
 * driver for them, /dev/ase, to implement a mapping between an LSM file
 * system and its pseudodevice.  Only LSM devices that belong to an ASE
 * are mapped.
 *
 * ASE creates (destroys) map entries with the CONFIG (DECONFIG) calls when
 * it starts (stops) a service on a host.  To see which LSM device (if any)
 * the pseudodevice /dev/ase_015 is mapped to, open /dev/ase in the usual way
 * and load /dev/ase_015's dev_t into a struct ase_config, then pass this in
 * an ioctl using ASE_ASE2LSM_CMD.  If the result is ESUCCESS, the
 * corresponding LSM device's dev_t will have been copied into the map_dev
 * field of your struct.
 */

#ifndef __ASE_PSEUDO_H__
#define __ASE_PSEUDO_H__

typedef struct ase_config {
    dev_t    ase_dev; /* an ASE pseudodevice */
    dev_t    map_dev; /* an LSM volume */
} ASE_CONFIG;


/*
 * The ioctl commands.
 */
#define ASE_CONFIG_CMD      _IOWR('a', 1, struct ase_config)
#define ASE_DECONFIG_CMD    _IOWR('a', 2, struct ase_config)
#define ASE_ASE2LSM_CMD     _IOWR('a', 3, struct ase_config)
#define ASE_LSM2ASE_CMD     _IOWR('a', 4, struct ase_config)

#endif
