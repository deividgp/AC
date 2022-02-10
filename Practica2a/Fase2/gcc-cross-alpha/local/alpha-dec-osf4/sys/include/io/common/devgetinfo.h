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
 * @(#)$RCSfile: devgetinfo.h,v $ $Revision: 1.1.7.2 $ (DEC) $Date: 1998/09/08 18:47:29 $
 */

#ifndef _DEVGETINFO_H_
#define _DEVGETINFO_H_

#ifdef __cplusplus
extern "C" {
#endif


/*
 * supporting structures for device_info_t
 */


/*
 * Device-Specific info structures
 */

#define DEV_ARCH_LEN        32  /* length of "unknown" architecture data */
                                /* align on quadword (8-byte) boundry    */

/* values for disk "class" */
#define DKDEV_CLS_UNKNOWN           0x0000
#define DKDEV_CLS_HARDDISK          0x0001
#define DKDEV_CLS_FLPY_GENERIC      0x0002  /* Floppy - no known density    */
#define DKDEV_CLS_FLPY_3_DD2S       0x0003  /* 3.5"  720KB  DD 2side  9sect */
#define DKDEV_CLS_FLPY_3_HD2S       0x0004  /* 3.5"  1.44MB HD 2side 18sect */
#define DKDEV_CLS_FLPY_3_ED2S       0x0005  /* 3.5"  2.88MB ED 2side 36sect */
#define DKDEV_CLS_FLPY_5_LD2S       0x0006  /* 5.25" 360KB  LD 2side  9sect */
#define DKDEV_CLS_FLPY_5_DD1S       0x0007  /* 5.25" 400KB  DD 1side 10sect */
#define DKDEV_CLS_FLPY_5_DD2S       0x0008  /* 5.25" 720KB  DD 2side  9sect */
#define DKDEV_CLS_FLPY_5_HD2S       0x0009  /* 5.25" 1.2MB  HD 2side 15sect */
#define DKDEV_CLS_CDROM             0x000A
#define DKDEV_CLS_WORM              0x000B

/* values for disk "status" */
#define DKDEV_READY         0x00000001      /* Device online and ready   */
#define DKDEV_OFFLINE       0x00000002      /* Device not ready          */
#define DKDEV_WRTPROT       0x00000004      /* Write protected           */
#define DKDEV_RDONLY        0x00000008      /* Read Only device (cdrom)  */
#define DKDEV_WRTCACHING    0x00000010      /* Write Caching Enabled     */
#define DKDEV_RAID          0x00000020      /* RAID device               */
#define DKDEV_REMOVABLE     0x00000040      /* Device has removable media */
#define DKDEV_BOOT          0x00000080      /* Device has boot support    */

/* values for disk "arch.scsi.flags" */
#define DKDEV_ASF_BBR       0x00000001      /* Auto Bad Block Recovery   */

#define DISK_CLASS_LEN      32  /* Length of disk class string           */
                                /* Align on quadword (8-byte) boundry    */

typedef struct v1_disk_dev_info {
    ulong_t  status;                        /* Device status             */
    ulong_t  capacity;                      /* Number blks on device     */
    ulong_t  blocksz;                       /* Number bytes per blk      */
#ifdef __cplusplus
    uchar_t  class_disk;                    /* Disk class.               */
#else
    uchar_t  class;                         /* Disk class.               */
#endif
    uchar_t  part_num;                      /* Partition #               */
    uchar_t  raid_level;                    /* Raid Level of media,      */
                                            /* valid only if DKDEV_RAID. */
    uchar_t  pad0;
    ushort_t media_changes;                 /* # of times media has chgd */
                                            /* valid if DKDEV_REMOVABLE  */
    ushort_t pad1;
    union {
        struct {                            /* SCSI-specific data */
            uchar_t density_code;              /* Only if RDONLY device  */
            uchar_t flags;                     /* misc SCSI flags        */
        } scsi;
        uchar_t archdata[DEV_ARCH_LEN];     /* "Unknown" architecture    */
    } arch;
} v1_disk_dev_info_t;

/* values for tape "class" */
#define TPDEV_CLS_UNKNOWN           0x0000
#define TPDEV_CLS_DLT               0x0001
#define TPDEV_CLS_TK                TPDEV_CLS_DLT  /* older name for DLT */
#define TPDEV_CLS_RDAT              0x0002
#define TPDEV_CLS_9TRK              0x0003
#define TPDEV_CLS_QIC               0x0004
#define TPDEV_CLS_8MM               0x0005
#define TPDEV_CLS_3480              0x0006

/* values for tape "media_status" */
#define TPDEV_BOM           0x00000001      /* Beginning-of-medium (BOM) */
#define TPDEV_EOM           0x00000002      /* End-of-medium (EOM)       */
#define TPDEV_RESERVED1     0x00000004      /*       reserved            */
#define TPDEV_WRTPROT       0x00000008      /* Write protected           */
#define TPDEV_BLANK         0x00000010      /* Blank media               */
#define TPDEV_WRITTEN       0x00000020      /* Written since opened      */
#define TPDEV_RESERVED2     0x00000040      /*       reserved            */
#define TPDEV_SOFTERR       0x00000080      /* Device soft error         */
#define TPDEV_HARDERR       0x00000100      /* Device hard error         */
#define TPDEV_DONE          0x00000200      /* Operation complete/Online */
#define TPDEV_RETRY         0x00000400      /* Retry                     */
#define TPDEV_ERASED        0x00000800      /* Erased                    */
#define TPDEV_TPMARK        0x00001000      /* Unexpected tape mark      */
#define TPDEV_SHRTREC       0x00002000      /* Short record              */
#define TPDEV_RDOPP         0x00004000      /* Read opposite             */
#define TPDEV_RWDING        0x00008000      /* Rewinding                 */
#define TPDEV_POS_VALID     0x00010000      /* tape position info valid  */

/* values for tape "unit_status" */
#define TPDEV_READY         0x00000001      /* Device online and ready   */
#define TPDEV_OFFLINE       0x00000002      /* Device not ready          */
#define TPDEV_NO_EOM        0x00000004      /* No warning on EOM         */
#define TPDEV_HAS_LOADER    0x00000008      /* Device has integral ldr   */
#define TPDEV_1FM_ONCLOSE   0x00000010      /* Writes 1 FM (!2) on close */
#define TPDEV_REW_ONCLOSE   0x00000020      /* Rewind on close           */
#define TPDEV_COMPACTING    0x00000040      /* Density is Compacted      */
#define TPDEV_COMPRESSING   0x00000080      /* Compression Enabled       */
#define TPDEV_BUFFERED      0x00000100      /* Device is Buffering data  */


#define TPDEV_CLASS_LEN     32  /* Length of tape class string           */
                                /* Align on quadword (8-byte) boundry    */

typedef struct v1_tape_dev_info {
    uint_t  media_status;                   /* Status of the media       */
    uint_t  unit_status;                    /* Status of the unit        */
    long    recordsz;                       /* Record size (0=variable)  */
    long    density_bpi;                    /* Current density           */
    long    density_bpi_wrt;                /* Density used when writing */
    /* next 2 items valid only if TPDEV_POS_VALID */
    long    position;                       /* # records past last fm    */
    long    fm_cnt;                         /* # fm seen since BOT       */
#ifdef __cplusplus
    uchar_t class_tape;                     /* Tape class                */
#else
    uchar_t class;                          /* Tape class                */
#endif
    uchar_t pad[7];
    union {
        struct {                            /* SCSI-specific data */
                                            /*   see "struct density" in */
                                            /*   io/cam/pdrv.h           */
            uint_t  blocking_factor;
            uchar_t valid_flags;
            uchar_t density_code;
            uchar_t buffered_mode;
            uchar_t speed;
            uchar_t compression_code;
        } scsi;
        uchar_t archdata[DEV_ARCH_LEN];     /* "Unknown" architecture    */
    } arch;
} v1_tape_dev_info_t;


#define DEV_TYPE_LEN       256  /* Length of "unknown" device type data  */
                                /* Align on quadword (8-byte) boundry    */

typedef union v1_devtype_info {
    v1_disk_dev_info_t    disk;
    v1_tape_dev_info_t    tape;
    uchar_t               devdata[DEV_TYPE_LEN];
} v1_devtype_info_t;



/*
 * Bus-Specific info structures
 */

/* values for scsi "flags" */
#define SCSIBUS_NO_DISCON       0x00000001  /* Disconnects Disabled      */
#define SCSIBUS_CMD_REORDER     0x00000002  /* Cmd Reordering Enabled    */
#define SCSIBUS_SYNC_XFR        0x00000004  /* Synchronous Xfrs In Use   */
#define SCSIBUS_WIDE_16         0x00000008  /* Wide (16bit) In Use       */

#define DEV_SCSI_INQ_SZ         36          /* Top Portion of Inq Data   */

typedef struct v1_scsi_bus_info {
    ulong_t  bus_num;                       /* SCSI Bus Number           */
    ulong_t  tgt_id;                        /* SCSI Target Id Number     */
    ulong_t  lun;                           /* SCSI Lun Number           */
    ulong_t  flags;                         /* misc scsi flags           */
    ushort_t sync_period;                   /* negot sync period (ns)    */
    uchar_t  sync_offset;                   /* negot sync offset         */
    uchar_t  tag_q_depth;                   /* tagged que depth          */
    uchar_t  inq_data[DEV_SCSI_INQ_SZ];     /* 1st 36 bytes of Inq Data  */
} v1_scsi_bus_info_t;


#define DEV_BUS_LEN        128  /* length of "unknown" bus data          */
                                /* align on quadword (8-byte) boundry    */

/*
 * Values for all "general" information are identical to those
 * used previously for the DEVIOCGET ioctl and struct devget in devio.h
 */
typedef struct v1_bustype_info {
    /* general connection info */
    int     adpt_num;                       /* Adapter number            */
    int     nexus_num;                      /* Nexus/node on adapter no. */
    int     bus_num;                        /* Bus number                */
    int     ctlr_num;                       /* Controller number         */
    int     rctlr_num;                      /* Remote controller number  */
    int     slave_num;                      /* Plug or line number       */
    int     unit_num;                       /* device unit number        */
    int     pad0;
    /* now bus-specific connection */
    union {
        v1_scsi_bus_info_t    scsi;
        uchar_t               busdata[DEV_BUS_LEN];
    } bus;
} v1_bustype_info_t;


#define DEV_STRING_SIZE     24  /* length of device info strings         */
                                /* align on quadword (8-byte) boundry    */

#define DEV_PRIVATE_LEN    128  /* length of "private" device data       */
                                /* align on quadword (8-byte) boundry    */

/*
 * Values for the following fields are identical to those used previously
 * for the DEVIOCGET ioctl and struct devget in devio.h
 *      category, bus, interface, device, dev_name, soft_count, hard_count.
 */
/* Structure for DEVGETINFO ioctl - device get status command */
/* structure optimized for alignment */
typedef struct v1_device_info  {
    int                version;             /* version ( = VERSION_1) */
    short              category;            /* Category               */
    short              bus;                 /* Bus                    */
    char               interface[DEV_STRING_SIZE]; /* Interface (string) */
    char               device[DEV_STRING_SIZE];    /* Device (string)    */
    char               dev_name[DEV_STRING_SIZE];  /* device pneumonic   */
    ulong_t            soft_count;          /* soft error count       */
    ulong_t            hard_count;          /* hard error count       */
    v1_devtype_info_t  devinfo;             /* Category-specific data */
    v1_bustype_info_t  businfo;             /* bus-specific data      */
#ifdef __cplusplus
    uchar_t            private_dev[DEV_PRIVATE_LEN]; /* private device data */
#else
    uchar_t            private[DEV_PRIVATE_LEN]; /* private device data */
#endif
} v1_device_info_t;


/*
 * We allow hooks for bus/device information to be expanded by
 * allowing future versions of the structures to be identified
 * via the "version" field at the top of the device info structure.
 */

#define VERSION_1       1

/*
 * The data argument for the ioctl.
 * An even 1k of data is allocated, even though each version may
 * not map this much information (version 1 is 576 bytes).
 * This is so that the ioctl, which embeds the size of the data
 * argument into the "cmd" value, will stay consistent even if we
 * have to modify the data argument structure.
 */
typedef union device_info {
    int              version;
    v1_device_info_t v1;
    /* only VERSION1 is currently supported */
    uchar_t          pad[1024];
} device_info_t;


/*
 * Conversion routine from device_info_t datastructure to struct devget
 * datastructure (used in conjunction with DEVGETINFO and DEVIOCGET
 * compatibility areas).
 */
#ifdef KERNEL
extern int devgetinfo_2_devio(device_info_t *, struct devget *);
#else /* not KERNEL */
extern int devgetinfo_2_devio __((device_info_t *, struct devget *));
#endif /* not KERNEL */


#ifdef __cplusplus
}
#endif

#endif /* not _DEVGETINFO_H_ */


