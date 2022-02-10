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
 * @(#)$RCSfile: dpmsstr.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/10/26 14:10:36 $
 */


#define X_DPMSGetVersion	0
#define X_DPMSCapable		1
#define X_DPMSGetTimeouts	2
#define X_DPMSSetTimeouts	3
#define X_DPMSEnable		4
#define X_DPMSDisable		5
#define X_DPMSForceLevel       	6
#define X_DPMSInfo       	7

#define DPMSNumberEvents	0

#define DPMSNumberErrors	0

#define DPMSMajorVersion	1
#define DPMSMinorVersion	1

#define DPMSExtensionName	"DPMS"

typedef struct {
    CARD8	reqType;	/* always DPMSCode */
    CARD8	dpmsReqType;	/* always X_DPMSGetVersion */
    CARD16	length B16;
    CARD16	majorVersion B16;
    CARD16	minorVersion B16;
} xDPMSGetVersionReq;
#define sz_xDPMSGetVersionReq 8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad0;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	majorVersion B16;
    CARD16	minorVersion B16;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xDPMSGetVersionReply;
#define sz_xDPMSGetVersionReply 32

typedef struct {
    CARD8	reqType;	/* always DPMSCode */
    CARD8	dpmsReqType;	/* always X_DPMSCapable */
    CARD16	length B16;
} xDPMSCapableReq;
#define sz_xDPMSCapableReq 4

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad0;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    BOOL	capable;
    CARD8	pad1;
    CARD16	pad2 B16;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
    CARD32	pad7 B32;
} xDPMSCapableReply;
#define sz_xDPMSCapableReply 32

typedef struct {
    CARD8	reqType;	/* always DPMSCode */
    CARD8	dpmsReqType;	/* always X_DPMSGetTimeouts */
    CARD16	length B16;
} xDPMSGetTimeoutsReq;
#define sz_xDPMSGetTimeoutsReq 4

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad0;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	standby B16;
    CARD16	suspend B16;
    CARD16	off B16;
    CARD16	pad1 B16;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xDPMSGetTimeoutsReply;
#define sz_xDPMSGetTimeoutsReply 32

typedef struct {
    CARD8	reqType;	/* always DPMSCode */
    CARD8	dpmsReqType;	/* always X_DPMSSetTimeouts */
    CARD16	length B16;
    CARD16	standby B16;
    CARD16	suspend B16;
    CARD16	off B16;
    CARD16	pad0 B16;
} xDPMSSetTimeoutsReq;
#define sz_xDPMSSetTimeoutsReq 12

typedef struct {
    CARD8	reqType;	/* always DPMSCode */
    CARD8	dpmsReqType;	/* always X_DPMSEnable */
    CARD16	length B16;
} xDPMSEnableReq;
#define sz_xDPMSEnableReq 4

typedef struct {
    CARD8	reqType;	/* always DPMSCode */
    CARD8	dpmsReqType;	/* always X_DPMSDisable */
    CARD16	length B16;
} xDPMSDisableReq;
#define sz_xDPMSDisableReq 4

typedef struct {
    CARD8	reqType;	/* always DPMSCode */
    CARD8	dpmsReqType;	/* always X_DPMSForceLevel */
    CARD16	length B16;
    CARD16	level B16;	/* power level requested */
    CARD16	pad0 B16;
} xDPMSForceLevelReq;
#define sz_xDPMSForceLevelReq 8

typedef struct {
    CARD8	reqType;	/* always DPMSCode */
    CARD8	dpmsReqType;	/* always X_DPMSInfo */
    CARD16	length B16;
} xDPMSInfoReq;
#define sz_xDPMSInfoReq 4

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad0;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	power_level B16;
    BOOL	state;
    CARD8	pad1;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xDPMSInfoReply;
#define sz_xDPMSInfoReply 32





