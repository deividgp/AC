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
 * @(#)$RCSfile: devsw.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1995/11/14 19:00:44 $
 */
#ifndef _DEVSW_INCL_
#define _DEVSW_INCL_

/*
 * Device switch database data structures
 *
 * The device switch database is comprised of a base data structure (so we
 * always have a minimum of one data structure) and a queue of major number
 * reservation data structures.  So there are only two data structures.
 *
 * Each major number reservation data structure represents a driver/instance
 * request to reserve a device switch table entry.  A driver can request
 * multiple entries in the same table by calling the registration routine
 *  multiple times with different instance numbers.
 */

/*
 * Define a unique data structure number for each data structure in the
 * device switch database.
 */

#define DEVSW_DS_MAIN  0x01		/* ds# for main data structure */
#define DEVSW_DS_RES   0x02		/* ds# for reservation structure */
#define DEVSW_DS_MAX   0x02		/* maximum data structure number */

#define DEVSW_NAME_LEN 32		/* size of a driver name */

typedef struct devsw_main {
  DS_HDR main_hdr;			/* data structure header */
  int dsres_off;			/* Offset to dsres_ptr */
  int version;				/* version of this database */
  int spare1;				/* Reserved for future (init to 0) */
  int spare2;				/* Reserved for future (init to 0) */
  DS_PTR dsres_ptr;			/* Pointer to devsw_res structures */
} DEVSW_MAIN;

typedef struct devsw_res {
  DS_HDR res_hdr;			/* data structure header */
  char driver_name[DEVSW_NAME_LEN];	/* driver name */
  int rinstance;			/* reservation instance from this
					   driver */
  int major_res;			/* reserved major number */
  int dsent_init;			/* 1 = devsw entry is initialized
					   0 = devsw entry not initialized */
  int requests;				/* number of requests made on this
					   entry during this boot */
  int spare1;				/* Reserved for future (init to 0) */
  int spare2;				/* Reserved for future (init to 0) */
} DEVSW_RES;

/*
 * The initialization callback must be called after kds is available,
 * so we set the priority of this callback to be higher than the kds
 * callback.
 */

#define DEVSW_INIT_PRIORITY KDS_PRIORITY+10

/*
 * This section describes which fields in the devsw request data structures
 * are initialized by the device switch utility (U) and the device switch
 * kernel code (K).
 *
 *             0       flags  bmajcnt cmajcnt
 *             1       handle name    instance major  init
 *             type
 * -----------------------------------------------------------------------
 * GETINFO     0       K      K       K
 * GETMAJ      1       U/K    U/K     U/K      K      K
 * GETDRV      1       -      K       K        -      K
 * RELMAJ      1       -      U       U        K      -
 */

/* ---------------------------------------------------------------------- */

/*
 * Device switch database request function codes.  These function codes
 * will be used by the device switch utility when making requests to the
 * device switch kernel database.
 */

#define DEVSW_FC_GETINFO	0	/* Get information */
#define DEVSW_FC_GETMAJ		1	/* Get major number */
#define DEVSW_FC_GETDRV		2	/* Get driver/instance */
#define DEVSW_FC_RELMAJ		3	/* Release major number */

#define DEVSW_FC_MAX		3	/* Maximum legal function code */

/* ---------------------------------------------------------------------- */

/*
 * Device switch request data structures.  These data structures will be
 * used to pass information between the device switch kernel database and
 * the device switch  utility.  There are multiple data structure formats
 * defined here for the different types of requests.
 */

typedef struct devsw_req0
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  int flags;				/* Flags */
  int devsw_size;			/* number of major numbers */
  int spare1;				/* Reserved for future (init to 0) */
  int spare2;				/* Reserved for future (init to 0) */
} DEVSW_REQ0;

/*
 * These are the flag values for devsw_req0.flags.
 */

#define DEVSW_GI_INITED		1	/* device switch db is initialized */
#define DEVSW_GI_DBPRIM		2	/* Database read from primary file */
#define DEVSW_GI_DBBACK		4	/* Database read from backup file */

typedef struct devsw_req1
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  long handle;				/* last/current reservation handle */
  char name[DEVSW_NAME_LEN];		/* driver name */
  int instance;				/* driver instance */
  int major_res;			/* reserved major number */
  int dsent_init;			/* device switch entry initialized */
  int spare1;				/* Reserved for future (init to 0) */
} DEVSW_REQ1;

#endif /* _DEVSW_INCL_ */
