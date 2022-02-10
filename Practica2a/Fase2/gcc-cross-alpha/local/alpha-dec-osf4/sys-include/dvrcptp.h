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
/* @(#)$RCSfile: dvrcptp.h,v $ $Revision: 4.2.3.2 $ (DEC) $Date: 1992/04/15 08:31:01 $     */
#ifndef _dvr_cc_ptp_
#define _dvr_cc_ptp_
/*
**++
**
**  COPYRIGHT (c) 1989, 1992 BY
**  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.
**  ALL RIGHTS RESERVED.
**
**  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND  COPIED
**  ONLY  IN  ACCORDANCE  WITH  THE  TERMS  OF  SUCH  LICENSE AND WITH THE
**  INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR  ANY  OTHER
**  COPIES  THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY
**  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE  IS  HEREBY
**  TRANSFERRED.
**
**  THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE  WITHOUT  NOTICE
**  AND  SHOULD  NOT  BE  CONSTRUED  AS  A COMMITMENT BY DIGITAL EQUIPMENT
**  CORPORATION.
**
**  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE OR  RELIABILITY  OF  ITS
**  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.
**
**  ABSTRACT:
**	This file contains function prototype definitions for the DVR
**	character cell viewer callable routines.
**
**--
**/

#ifndef _cdatyp_
#include <cdatyp.h>
#endif

#ifndef CC_VIEW_TYPES
typedef struct cc_viewer_context_struct {int opaque;} CC_VIEWER_CONTEXT_STRUCT;
#endif

PROTO(  CDAstatus CDA_APIENTRY DvrCCGetPage, (CC_VIEWER_CONTEXT_STRUCT * *,
				    CDAsize *, CDAenvirontext ***, CDAsize **));
PROTO(  CDAstatus CDA_APIENTRY DvrCCDeletePage, (CC_VIEWER_CONTEXT_STRUCT * *,
						 CDAenvirontext ***));
PROTO(  CDAstatus CDA_APIENTRY DvrCCEnd, (CC_VIEWER_CONTEXT_STRUCT **));
PROTO(  CDAstatus CDA_APIENTRY DvrCCInitialize, (CDAflags, CDAitemlist *, CDAitemlist *,
	CDAsize, CDAsize, CC_VIEWER_CONTEXT_STRUCT **));
#endif
