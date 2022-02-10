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
 * @(#)$RCSfile: overlap.h,v $ $Revision: 1.1.5.5 $ (DEC) $Date: 1995/08/22 22:36:41 $
 */
#ifndef __OVERLAP_H
#define __OVERLAP_H
#include <sys/disklabel.h>



struct dec_partid {
	dev_t lvm_or_lsm_dev;		/* lvm/lsm device		*/
	short bus;			/* Bus				*/
	short adpt_num;			/* Adapter number		*/
	short nexus_num;		/* Nexus or node on adapter no.	*/
	short bus_num;			/* Bus number			*/
	short ctlr_num;			/* Controller number		*/
	short rctlr_num;		/* Remote controller number	*/
	short slave_num;		/* Plug or line number		*/
	short unit_num;			/* Ultrix device unit number	*/
	long  category_stat;		/* Category specific mask	*/
	struct partid_pt {
		long part_blkoff;	/* Beginning partition sector	*/
		long part_nblocks;	/* Number of sectors in partition */
		int part_fstype;	/* file system type; see <sys/disklabel.h> */
	} pt_part[MAXPARTITIONS];
};

/* Unchanged functions */
char *fsl_rawname(const char *, char *);
char *fsl_unrawname(const char *, char *);
int fsl_swap_part_name(dev_t, char *);

/* New functions defined for overlap checks. */
int swap_part_name(dev_t, char *);
int check_usage(const char *, int);
int set_usage(const char *, int, int);

#define OV_CHECK_ALL    0
#define OV_CHECK_EXACT  1

#define FSL_DEV_NAME_LSM	"LSM"
#define FSL_DEV_NAME_LVM	"LVM"

#define	FSL_LSM_CDEV		"rvol"
#define	FSL_LSM_CDEV_LEN	4
#define	FSL_LSM_BDEV		"vol"
#define	FSL_LSM_BDEV_LEN	3

/*
 * Device naming disk directory names.
 */
#define	FSL_DVNMDSK_CDEV	"rdisk"
#define	FSL_DVNMDSK_CDEV_LEN	5
#define	FSL_DVNMDSK_BDEV	"disk"
#define	FSL_DVNMDSK_BDEV_LEN	4

#define OV_ERR_OPEN_OVERLAP	-1	/* Specified partition or an 
				 	 * overlapping partition is open. 
					 */
#define OV_ERR_INVALID_DEV	-2	/* Specified device is invalid 
				 	 * overlapping partition is open. 
					 */
#define OV_ERR_FSTYPE_OVERLAP	256	/* Overlapping partition(s) has fstype 
				 	 * field set. Could be more than one 
					 * partition. 
					 */
#define OV_ERR_MULT_FSTYPE_OVERLAP  257	/* Specified partition and Overlapping 
                        		 * partition(s) has fstype 
				 	 * field set. Could be more than one 
					 * partition. 
					 */
#define OV_ERR_INVALID_DSKLBL	258	/* Disklabel not found or is 
				 	 * corrupted. 	
					 */
#define OV_ERR_ADVFS_CHECK	259	/* Failure when checking overlap 
				 	 * with AdvFS domains. Either 
					 * /etc/fdmns or /etc/fdmns/<dom>
					 * for an active domain does not 
					 * exist. 
					 */
#define OV_ERR_SWAP_CHECK	260	/* Failure when checking overlap 
				 	 * with active swap devices. The 
					 * special device files associated 
					 * with active swap devices are 
					 * invalid. 
					 */

#define OV_ERR_DSKLBL_UPD	261	/* Could not update the disklabel */ 
#define OV_ERR_MAX		OV_ERR_DSKLBL_UPD

#endif /* !__OVERLAP_H */
