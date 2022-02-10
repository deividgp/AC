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
 * @(#)$RCSfile: crdfilter.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/05/30 18:36:52 $
 */

/*
 * When CRD_INTERVAL_COUNT errors occure in CRD_INTERVAL_LENGTH amount
 * of time, the event is logged with binlog.
 */
#define CRD_INTERVAL_LENGTH (24 * 60) /* Interval length in minutes */
#define CRD_INTERVAL_COUNT  50 /* CRD count per interval before CRD is logged*/
#define CRD_INTERVAL_INCREMENT 100
				      
/*
 * Generic CRD footprint.  A footprint is defined by its node number
 * and error syndrom bits.  It specifies an address range which have
 * seen CRD errors with the same node and syndrom bits.
 */
struct crd_footprint {
    int version;
#define CRD_FOOTPRINT_VERSION 0x01
    time_t first_time;		/* First time (ever) CRD was seen */
    time_t last_time;		/* Last time CRD was seen */
    time_t interval_start_time; /* Time interval was started */
    time_t last_log_time;       /* Last time CRD was logged with binlogd */
    time_t boot_time;		/* Time system was booted */
    ulong addr_range_high;	/* Highest address in the range of this
				 * footprint */
    ulong addr_range_low;	/* Lowest address in the range of this
				 * footprint */
    int node;			/* Failing node */
    int spare1;
    int spare2;
    int error_synd0;		/* Error syndrome bits */
    int error_synd1;		/* Error syndrome bits */
    int error_synd2;		/* Error syndrome bits */
    int error_synd3;		/* Error syndrome bits */
    int spare3;
    int spare4;
    int life_time_count;	/* Total number of times this CRD footprint
				 * has been seen, ever.
				 */
    int interval_count;		/* Total number of times this CRD footprint
				 * has been seen during this interval
				 */
    int next_log_count;		/* Number of times footprint must be seen
				 * during the current interval before it is
				 * next logged.
				 */
    int runtime_count;		/* Number of errors seen since last boot */
    int logged_count;		/* Number of times CRD has been logged with
				 * binlogd during this boot.
				 */
    int spare5;
    int spare6;
};

