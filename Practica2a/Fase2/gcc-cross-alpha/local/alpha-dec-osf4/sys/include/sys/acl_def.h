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
 * @(#)$RCSfile: acl_def.h,v $ $Revision: 1.1.3.2 $ (DEC) $Date: 1995/07/05 15:57:44 $
 */

#ifndef ACL_DEF
#define ACL_DEF

/*
 * Define the attr bit number for each type of ACL.
 */

#define ACL_TYPE_ACC  0
#define ACL_TYPE_DEF  1
#define ACL_TYPE_DEF_DIR 2
#define NUM_ACL_IR_TYPES (ACL_TYPE_DEF_DIR+1)	/* Number of ACLs */

#define ACL_TYPE_ACC_MASK  (1 << ACL_TYPE_ACC)
#define ACL_TYPE_DEF_MASK  (1 << ACL_TYPE_DEF)
#define ACL_TYPE_DEF_DIR_MASK (1 << ACL_TYPE_DEF_DIR)
#endif /* ACL_DEF */
