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
 * @(#)$RCSfile: kinfo.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/01/28 13:04:54 $
 */


/*
 * kinfo module ID
 */
#define KINFO_ID             5020
#define KINFO_NAME           "kinfo"
#define KINFO_VERSION        1


/*
 * Block off 100-199 for STREAMS ioctls
 */
#define KINFO_GET_STR_CFG    100
#define KINFO_GET_ID	     101
#define KINFO_GET_STR_STATS  102          /* Get STREAMS stats information */

/*
 * kinfo limits
 */
#define MAX_KBUF	     4096
#ifndef MAX_KINFO_BUF
#define MAX_KINFO_BUF MAX_KBUF
#endif
#define KINFO_HI_MARK        2048
#define KINFO_LO_MARK        128


/*
 ****** Structure for kinfo id - used by streams configuration program. ****
 */
typedef struct _id_blk {
        char name[100];
	int  version;
} id_blk;


/*
 * STREAMS kernel 'stuff' - wca
 */

/*
 ********  Structure which holds STREAMS configuration data for one entry ***
 */
typedef struct _str_cfg_blk {
	dev_t	scb_device;
#define SADF_DEVICE	0x00000001
#define SADF_MODULE	0x00000002
#define SADF_CLONE	0x00000004
	int	scb_flags;
	short	scb_mid;
	char	scb_name[FMNAMESZ+1];
} STR_CFG, str_cfg_blk;

typedef struct _sad_hdr {
	int	sad_cnt;
	dev_t	sad_clonedev;
} SAD_HDR, sad_hdr;

typedef struct _sad_blk {
	SAD_HDR	sad_blkhdr;
	STR_CFG sad_cfg[ (MAX_KBUF/sizeof(STR_CFG)) - 1 ];
} SAD, sad_blk;

