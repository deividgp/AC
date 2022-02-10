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
 * @(#)$RCSfile: camdb.h,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 1996/12/18 17:31:29 $
 */

#ifndef _CAM_DB_INCL_
#define _CAM_DB_INCL_

/*
 * The type of data structure (a field in the data structure header) is a
 * numeric value.  The values that can be placed in this field for the SCSI
 * database data structures are described next.
 */

#define SCSI_DS_SCSI		0x01	/* Main SCSI data structure */
#define SCSI_DS_PDRIVER		0x02	/* Peripheral driver data structure */
#define SCSI_DS_BUS		0x03	/* SCSI bus data structure */
#define SCSI_DS_DIDDB		0x04	/* SCSI device ID database d.s. */
#define SCSI_DS_PATH		0x05	/* SCSI path data structure */
#define SCSI_DS_MAX		0x05	/* Maximum SCSI ds number */

/*
 * The translation of the device ID (which is retrieved from the minor
 * number of the dev_t) needs to be quick.  To make it quick, we will have
 * an array of device ID data structures.  But since we may need 0 to 1000s
 * of these, we will have a two tiered array design.  There will be an
 * array of pointers in the SCSI database data structure.  These pointers
 * will each point to an array of device ID data structures.  The following
 * constant is used to define the size of the second level array.
 */

#define SCSI_DID_PER_ARR	64	/* Number of SCSI_DID data
					   structures in each array */
#define SCSI_DID_ARR_SHF	6	/* Number of bits to shift down */

/*
 * The number of different SCSI device types we currently support.
 */

/* abc - Increase the number of valid peripheral driver types to 32. */

#define SCSI_NUM_DTYPE 16		/* Number of SCSI device types */

/* ---------------------------------------------------------------------- */

/*
 * SCSI path data structure.  This data structure will store a physical
 * address of a SCSI device.  The physical address of a SCSI device is its
 * bus number, target number, and LUN.
 *
 * For some devices, there may be multiple paths.  If so, multiple of these
 * path data structures will be available for that device.
 */

typedef struct scsi_path
{
  DS_HDR path_hdr;			/* Data structure header */
  long   bus;				/* SCSI bus number */
  u_long target;			/* Target number on bus */
  u_long lun;				/* SCSI logical unit number */
  long   spare;				/* Spare to keep alignment */
} SCSI_PATH;

/* ---------------------------------------------------------------------- */

/*
 * SCSI driver lock data structure.  This data structure is used to keep
 * track of each peripheral driver that is using a particular device.
 * These data structures are not part of the on-disk database.  They are
 * allocated when a driver does its first xpt_lock_unit on a device.  They
 * are attached to the SCSI_DID structure for the device.  They are
 * deallocated when the driver issues an xpt_unlock_unit.  The number of
 * opens by this driver on this device is kept in this structure.
 */

typedef struct scsi_drvlock
{
  struct scsi_drvlock* flink;		/* Forward pointer */
  struct scsi_drvlock* blink;		/* Backward pointer */
  u_int  drv_reg_num;			/* Driver registration number */
} SCSI_DRVLOCK;

/* ---------------------------------------------------------------------- */

/*
 * Device ID data structure.  This data structure will store the information
 * required to translate a SCSI device ID (which is retrieved from the minor
 * number of a dev_t) to a SCSI physical address (bus, target, lun); also
 * known as a path.  This translation information must be preserved across
 * boots so that the device special files (which hold the dev_t value) will
 * continue to function across boots.
 *
 * There may be multiple paths that can be used to access a device.  This
 * structure allows for the multiple paths to be available.  For each device
 * ID, there is a primary path and zero to many alternate paths.
 *
 * Note that this data structure does not contain the standard database
 * header (DS_HDR).  This is because this data structure will be contained
 * within a larger data structure.  And that larger data structure will
 * contain the standard database header.
 *
 * Certain fields are only valid at certain times.  The validity of the
 * fields are explained in the comments below.
 */

typedef struct scsi_did
{

  /*
   * The following fields are always valid.  When the database is copied
   * from the file, the assigned flag is the only flag that is valid, all
   * other flags are cleared (set to zero).
   */

  union {
    u_int rflags;			/* Run-time flags */
    struct {
      unsigned assigned  : 1;		/* This device ID is assigned */
      unsigned inuse     : 1;		/* This device ID is being used */
      unsigned new       : 1;		/* This device ID is newly assigned
					   and needs to be passed to the
					   management utility */
      unsigned changed   : 1;		/* The device type has changed and
					   needs to be passed to the
					   management utility */
      unsigned exclusive : 1;		/* Exclusive use flag */
    } rflags_st;
  } rflags_un;
  u_int   device_id;			/* Device ID */
  lock_data_t
          did_lock;			/* Lock structure for this did */

  /*
   * The following field is always valid.  This field is left preserved
   * at all times to allow some context to be kept across multiple uses
   * of the device.  It is assumed that the structure pointed to by this
   * field does not have device-specific information.
   */

  caddr_t cam_ptr;			/* CAM-defined pointer */

  /*
   * The following fields are only valid if assigned = 1.  These fields are
   * owned by camdb.  The xpt/common software may read these fields; but
   * may not write to them.
   */

  u_int   dev_type;			/* Type of device (current) */
  u_int   dev_flags;			/* Device flags */
  u_int   num_path;			/* Number of paths in the list */
  u_int   spare1;			/* Spare to maintain alignment */
  SCSI_PATH				/* List of paths, the first (which */
          pathq;			/* is embedded) is the primary */

  /*
   * The following fields are used only by the utility.
   */

  u_int   old_type;			/* Type of device (previous) */

  /*
   * The following fields are only valid if inuse = 1.  These fields are
   * owned by the XPT layer.
   */

  /*
   * Driver state field.  This field represents the state of the peripheral
   * driver for this device.  If this field is non-zero, everyone will stall
   * by sleeping on the address of the field.
   */

  u_int   drv_state;			/* Driver state (opening, closing,
					   error recovery, etc) */
  SCSI_DRVLOCK*				/* Forward pointer to driver lock */
          flink;			/* for this b/t/l */
  SCSI_DRVLOCK*				/* Backward pointer to driver lock */
          blink;			/* for this b/t/l */
  u_int   tot_opens;			/* Total number of opens on this
					   device */
  u_int   single_open;			/* Set if only one open is allowed */
  SCSI_PATH*				/* path currently in use */
          cur_path_ptr;
  SCSI_PATH*				/* Where we started from for path */
          start_path_ptr;		/* switch */
  u_int   path_failures;		/* Number of consecutive path
					   failures */
  u_int   reserved[11];			/* Reserved for expansion */
} SCSI_DID;

/*
 * Flags for SCSI_DID.dev_flags
 */

#define SCSI_DEV_FLOPPY     0x01	/* Device is a floppy */

/*
 * Flags for SCSI_DID.drv_state
 */

#define SCSI_DID_OPENING    0x01	/* Opening device */
#define SCSI_DID_CLOSING    0x02	/* Closing */
#define SCSI_DID_GEN_STALL  0x04	/* General stall */
#define SCSI_DID_NEW_PATH   0x08	/* New path forming */
#define SCSI_DID_PATH_ACT   0x10	/* Path Switch for this device active*/

/* ---------------------------------------------------------------------- */

/*
 * Device ID array data structure.  This data structure is an array of
 * device ID structures.  The first instance of this array will be for
 * device IDs 0 through 63.  The second instance of this array will be
 * for device IDs 64 through 127.  The cam sub-system will allocate a new
 * device ID array when all the existing arrays are full and another
 * device needs to be included in the database.
 *
 * These arrays are used to hold the information about a SCSI device.
 * The information in these arrays is what is used to translate a SCSI
 * device ID (which is retrieved from the minor number of a dev_t) to a
 * SCSI physical address (bus, target, lun); also known as a path.  This
 * translation information must be preserved across boots so that the
 * device special files (which hold the dev_t value) will continue to
 * function across boots.
 *
 * If there are multiple paths that can be used to access a device, this
 * structure allows for the multiple paths to be available.  For each device
 * ID, there is a primary path and zero to many alternate paths.
 *
 * Note that this data structure does not contain the standard database
 * header (DS_HDR).  This is because this data structure will be contained
 * within a larger data structure.  And that larger data structure will
 * contain the standard database header.
 */

typedef struct scsi_didarr
{
  SCSI_DID				/* Array of device IDs */
         did[SCSI_DID_PER_ARR];
} SCSI_DIDARR;

/* RK01
 * To facilitate fast translation from physical to logical ID additional
 * structure is defined. Structure points to SCSI_DID record based on
 * T_L nexus. One table exists for each possible SCSI bus. Pointers to
 * SCSI_DID_PTR_TABLE are stored in global array camdb_TL_ptr_table.
 * SCSI_DID_PTR_TABLE is allocated dynamically for each existing SCSI bus
 * in the system.
 */

#define CAMDB_TARGETS	 8
#define CAMDB_LUNS	 8
#define CAMDB_BUSSES	64

typedef struct scsi_did_ptr_table {
    SCSI_DID	*did_ptr[CAMDB_TARGETS][CAMDB_LUNS];
} SCSI_DID_PTR_TABLE;

/* ---------------------------------------------------------------------- */

/*
 * Device ID database data structure.  This data structure will contain the
 * device ID array data structure.  And it will also include the standard
 * database header and an array of pointers (one for the path pointer in
 * each device ID entry in the device ID array).
 *
 * The device ID array and this structure are separately defined because
 * the device ID array (within this data structure) will be pointed to by
 * an array.  This is done for quick access to the device entries.
 * However, since these device ID arrays still need to be in the on-disk
 * database, we need to also have a standard database header.  So this
 * data structure is the real data structure; it is the one that will
 * exist in the on-disk database and will exist in the in-memory database.
 * But the array (SCSI_DIDARR) data structure that is embedded within this
 * data structure will NOT be accessed through this data structure.
 * Instead, the array will be accessed through the array of pointers.
 *
 * A series of picture is supplied for an easier explanation.
 *
 * When the database is brought in from the disk and connected together to
 * form the in-memory database, it will look like the following.  For this
 * example, there are two SCSI_DIDDB data structures in this database.  We
 * could have many of these data structures, but at this time in this
 * example we only have two.  These two SCSI_DIDDB data structures (at this
 * time) are in a linked list that starts at the scsi_ptr_diddb field of
 * the SCSI database.  Remember that the SCSI_DIDDB data structures each
 * have a SCSI_DIDARR data structure embedded in them.
 *
 *         SCSI_DATABASE
 *         +--------+
 *         |        |
 *         |        |
 *         |        |
 *         |        |           SCSI_DIDDB
 *  scsi_ptr_diddb ----------->+-----------+          SCSI_DIDDB
 *         |        |          |   ----------------->+-----------+
 *         |        |          |           |         |     0     |
 *         |        |          |SCSI_DIDARR|         |           |
 *         |        |          |           |         |SCSI_DIDARR|
 *         +--------+          |           |         |           |
 *                             +-----------+         |           |
 *                                                   +-----------+
 *
 * After the in-memory database has been connected (as shown above), the
 * SCSI database code will further initialize the database.  Part of this
 * initialization is to allocate and initialize an array of pointers to
 * each of the SCSI_DIDARR structures that are in each of the SCSI_DIDDB
 * data structures.  This is done for quick access to these arrays.  Once
 * this initialization is done, the database will look like the following.
 *
 *         SCSI_DATABASE
 *         +--------+
 *         |        |
 *         |        |
 *         |        |
 *         |        |           SCSI_DIDDB
 *  scsi_ptr_diddb ----------->+-----------+          SCSI_DIDDB
 *         |        |          |   ----------------->+-----------+
 *         |        |          |           |         |     0     |
 *         |        |   +----->|SCSI_DIDARR|         |           |
 *         +--------+   |      |           |   +---->|SCSI_DIDARR|
 *                      |      |           |   |     |           |
 *                      |      +-----------+   |     |           |
 * camdb_didarr_ptr     |                      |     +-----------+
 *         +--------+   |                      |
 *     [0] |    --------+                      |
 *     [1] |    -------------------------------+
 *     [2] |    0   |
 *         |   etc  |
 *         |        |
 *         +--------+
 *
 * The SCSI database code will need to get to an entry in the correct
 * SCSI_DIDARR data structure quickly and often.  So the SCSI database code
 * will use the camdb_didarr_ptr array to get the correct SCSI_DIDARR
 * structure.  The linked list of SCSI_DIDDB structures will not be used
 * by the SCSI database code very often.
 */

typedef struct scsi_diddb
{
  DS_HDR did_hdr;			/* Data structure header */
  int    path_off[SCSI_DID_PER_ARR];	/* Offset to the path pointer in
					   each SCSI_DID entry */
  SCSI_DIDARR	didarr;			/* Array of device IDs */
} SCSI_DIDDB;

/* ---------------------------------------------------------------------- */

/*
 * SCSI database data structure.  There will only be one of these data
 * structures in memory (or in the on-disk copy of the database) at any
 * given time.  This is the main SCSI data structure.  From this one data
 * structure, the entire SCSI database can be reached.
 */

typedef struct scsi_database
{
  DS_HDR scsi_hdr;			/* Data structure header */
  u_int  scsi_off_pdrv[SCSI_NUM_DTYPE];	/* Offset to scsi_ptr_pdrv */
  u_int  scsi_off_bus;			/* Offset to scsi_ptr_bus */
  u_int  scsi_off_didarr2;		/* Offset to scsi_ptr_didarr */
  u_int  scsi_off_prvt;			/* Offset to scsi_ptr_prvt */
  u_int  scsi_prvt_flags;		/* Flags for the SCSI manager */
  u_int  scsi_spare1;			/* Spare to maintain alignment */

  /* abc lock */
  DS_PTR scsi_ptr_pdrv[SCSI_NUM_DTYPE];	/* Array of SCSI_PDRIVER structure
					   pointers - one list per SCSI
					   device type */
  DS_PTR scsi_ptr_bus;			/* List of SCSI_BUS structures; to
					   preserve the SCSI bus numbers
					   as they are assigned */
  DS_PTR scsi_ptr_diddb;		/* List of SCSI_DIDDB structures; to
					   preserve the device IDs used in
					   the minor numbers */
  DS_PTR scsi_ptr_prvt;			/* List of SCSI manager private data
					   structures */
} SCSI_DATABASE;

/* ---------------------------------------------------------------------- */

/*
 * Peripheral driver data structure.  This data structure will represent
 * a SCSI peripheral driver/device type pair.  Each peripheral driver will
 * use one of these data structures for each device type it supports.
 * Typically, a peripheral driver supports only one device type.  In this
 * case, the peripheral driver will use only one of these data structures.
 * If a peripheral driver supports more than one device type, then it will
 * use more than one of these data structures (one per device type
 * supported).
 */

#define PDRV_NAME_LEN 32

typedef struct scsi_pdriver
{
  DS_HDR driver_hdr;			/* Data structure header */
  char driver_name[PDRV_NAME_LEN];	/* Name of driver */
  int dev_type;				/* Type of device supported */
  int b_major;				/* Driver's block major number */
  int c_major;				/* Driver's char  major number */
  int changed;				/* Flag to indicate a change */
  int spare1;				/* Maintain alignment (init to 0) */
  int spare2;				/* Maintain alignment (init to 0) */
  void (*request)();			/* Address of request routine */
} SCSI_PDRIVER;

/* ---------------------------------------------------------------------- */

/*
 * SCSI bus data structure.  This data structure will represent a SCSI
 * bus number that has been assigned.  There is one bus number for each
 * SCSI cable instance on a system.  The SIM drivers request a bus number
 * as they detect a SCSI adapter.  Some SCSI adapters have more than one
 * SCSI bus per adapter.  For these, the SIM driver will request one bus
 * number for each SCSI bus on the SCSI adapter.  Once the bus number is
 * assigned, the SIM driver will store information in this data structure
 * so that the same SCSI bus number can be re-acquired on subsequent boots.
 */

#define SIM_NAME_LEN 32

typedef struct scsi_bus
{
  DS_HDR bus_hdr;			/* Data structure header */
  char sim_name[SIM_NAME_LEN];		/* Name of the SIM driver */
  int  bus_number;			/* Bus number assigned */
  int  k0;				/* Key 0 */
  int  k1;				/* Key 1 */
  int  k2;				/* Key 2 */
  int  k3;				/* Key 3 */
  int  registered;			/* Flag to detect that this bus
					   has registered on this boot */
} SCSI_BUS;

/* ---------------------------------------------------------------------- */

/*
 * SCSI translation structure.  This data structure is used to register
 * devices and to translate device information.  It can be used to
 * translate from a bus/target/lun to a device id or it can be used to
 * translate from a device id to a bus/target/lun.
 *
 * This data structure is not part of the scsi database.  It used used
 * as a parameter in certain calls between xpt and camdb.
 *
 * The bus field is a signed long because some routines set that field
 * to -1 to signal an error.
 */

typedef struct scsi_trans
{
  long     bus;				/* Bus number/error indicator */
  u_long   target;			/* Target number */
  u_long   lun;				/* Logical unit number */
  u_long   dev_type;			/* SCSI device type */
  u_long   dev_flags;			/* SCSI device flags */
  u_long   logical_id;			/* Device's assigned logical id */
  SCSI_DID *scsi_did;			/* Pointer to our scsi_did struct */

  /*
   * The following fields are used only by the drivers.
   */

  u_long   num_alts;			/* Number of alternate paths */
  void     *pdrv;			/* Pointer to PDRV_DEVICE3 */
  void     *specific;			/* Driver specific pointer */
} SCSI_TRANS;

/* ---------------------------------------------------------------------- */

/*
 * This section described which fields in the SCSI request data structures
 * are initialized by the SCSI Utility (U) and the SCSI Database (D).
 *
 *             0       flags
 *             1       d_id    d_sflags   d_type   num_alt   ppath   apath
 *             2       bus     target
 *             3       ds_num  ptr_num                       ds
 *             4       devt    drv_op
 *             type
 * -----------------------------------------------------------------------
 * GETINFO     0       D
 * ADDDEV      1       D       U          U        U         U       U
 * DELDEV      1       U                  U
 * ADDPATH     1       U                           U                 U
 * DELPATH     1       U                           U                 U
 * GETNDEV     1       D       D          D        D         D
 * ACKNDEV     1       U       U          U        U         U
 * GETCDEV     1       D       D          D
 * ACKCDEV     1       U       U          U
 * GETDFLAG    1       U       D          U
 * ACKDFLAG    1       U       U          U
 * SCANALL     2
 * SCANBUS     2       U
 * SCANADR     2       U       U
 * GETBUS      3       D       D                             D(BUS)
 * ACKBUS      3       U       U                             U(BUS)
 * DELBUS      3                                             U(BUS)
 * GETDRV      3       D       D                             D(DRIVER)
 * ACKDRV      3       U       U                             U(DRIVER)
 * DELDRV      3                                             U(DRIVER)
 * GETCDRV     3                                             D(DRIVER)
 * ACKCDRV     3                                             U(DRIVER)
 * DRVREQ      4       U       U
 */

/* ---------------------------------------------------------------------- */

/*
 * SCSI datbase request function codes.  These function codes will be used
 * by the SCSI management utility when making requests to the SCSI kernel
 * database.
 */

#define SCSI_FC_GETINFO		0	/* Get information */
#define SCSI_FC_ADDDEV		1	/* Add a device */
#define SCSI_FC_DELDEV		2	/* Delete a device */
#define SCSI_FC_ADDPATH		3	/* Add an alternate path */
#define SCSI_FC_DELPATH		4	/* Delete an alternate path */
#define SCSI_FC_GETNDEV		5	/* Get new device */
#define SCSI_FC_ACKNDEV		6	/* Ack new device */
#define SCSI_FC_GETCDEV		7	/* Get changed device */
#define SCSI_FC_ACKCDEV		8	/* Ack changed device */
#define SCSI_FC_GETDFLAG	9	/* Get device flags */
#define SCSI_FC_SETDFLAG	10	/* Set device flags */
#define SCSI_FC_SCANBUS		11	/* Scan a bus */
#define SCSI_FC_SCANADR		12	/* Scan an address */
#define SCSI_FC_GETBUS		13	/* Get new bus */
#define SCSI_FC_ACKBUS		14	/* Ack new bus */
#define SCSI_FC_DELBUS		15	/* Delete bus */
#define SCSI_FC_GETNDRV		16	/* Get new driver */
#define SCSI_FC_ACKNDRV		17	/* Ack new driver */
#define SCSI_FC_GETCDRV		18	/* Get changed driver */
#define SCSI_FC_ACKCDRV		19	/* Ack changed driver */
#define SCSI_FC_DELDRV		20	/* Delete driver */
#define SCSI_FC_PRINT		21	/* Print your database */
#define SCSI_FC_DRVREQ		22	/* Driver-specific request */
#define SCSI_FC_SCANALL		23	/* Scan all buses */

#define SCSI_FC_MAX		23	/* Maximum legal function code */

/* ---------------------------------------------------------------------- */

/*
 * SCSI request data structures.  These data structures will be used to pass
 * information between the SCSI kernel database and the SCSI management
 * utility.  There are multiple data structure formats here for the different
 * types of requests.
 */

typedef struct scsi_req0
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  int flags;				/* Flags */
  int spare1;				/* Reserved for future (init to 0) */
  int spare2;				/* Reserved for future (init to 0) */
  int spare3;				/* Reserved for future (init to 0) */
  int spare4;				/* Reserved for future (init to 0) */
  int spare5;				/* Reserved for future (init to 0) */
} SCSI_REQ0;

/*
 * These are the flag values for scsi_req0.flags.
 */

#define SCSI_GI_INITED		1	/* CAM is initialized */
#define SCSI_GI_OOMODE		2	/* Running in old-only mode */
#define SCSI_GI_DBPRIM		4	/* Database read from primary file */
#define SCSI_GI_DBBACK		8	/* Database read from backup file */

typedef struct scsi_req1
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  int d_id;				/* Device ID */
  int d_sflags;				/* Device special flags */
  int d_type;				/* Device type (0 to 15) */
  int num_alt;				/* Number of alternate paths */
  int spare4;				/* Reserved for future (init to 0) */
  int spare5;				/* Reserved for future (init to 0) */
} SCSI_REQ1;

typedef struct scsi_req2
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  long   bus;				/* Bus number */
  u_long target;			/* Target number */
  int    spare4;			/* Reserved for future (init to 0) */
  int    spare5;			/* Reserved for future (init to 0) */
} SCSI_REQ2;

typedef struct scsi_req3
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  int ds_num;				/* Data structure number */
  int ptr_num;				/* Pointer number */
  int spare2;				/* Reserved for future (init to 0) */
  int spare3;				/* Reserved for future (init to 0) */
  int spare4;				/* Reserved for future (init to 0) */
  int spare5;				/* Reserved for future (init to 0) */
} SCSI_REQ3;

typedef struct scsi_req4
{
  KDS_REQ kdsreq;			/* KDS generic fields */
  dev_t devt;				/* Dev_t of a character device for
					   the driver to get this request */
  int drv_op;				/* Operation code for the driver */
  int spare2;				/* Reserved for future (init to 0) */
  int spare3;				/* Reserved for future (init to 0) */
  int spare4;				/* Reserved for future (init to 0) */
  int spare5;				/* Reserved for future (init to 0) */
} SCSI_REQ4;

/* ---------------------------------------------------------------------- */

/*
 * Function prototypes
 */

void camdb_init();
void camdb_reinit();
void camdb_func(SCSI_REQ1*, int);
int camdb_addpath_k(int, SCSI_TRANS*, int);
int camdb_busreg(SCSI_BUS*);
int camdb_checkpaths(SCSI_DID*);
int camdb_devreg(SCSI_TRANS*);
int camdb_drvreg(SCSI_PDRIVER*);
int camdb_trndid(SCSI_TRANS*);
int camdb_trnpth(SCSI_TRANS*);

#endif /* _CAM_DB_INCL_ */
