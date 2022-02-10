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

#pragma	ident	"@(#)$RCSfile: volkint.h,v $ $Revision: 1.1.6.5 $ (DEC) $Date: 1995/12/20 16:14:44 $"

/* @(#)src/common/uts/io/vxvm/volkint.h	6.6 02 Jun 1993 07:03:19 - Copyright (c) 1993 VERITAS Software Corp. */
/*
 * Copyright(C)1993 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 * 
 *               RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *               VERITAS SOFTWARE
 * 4800 GREAT AMERICA PARKWAY, SANTA CLARA, CA 95054
 */
/*
 * Alpha change log
 *
 * 09-28-93	Wai Yim
 * Merged alpha port with vxvm1.2.1 source.
 *
 */

/*
 * volkint.h -- volume configuration driver,  kernel interface
 *
 */

/* defined reletive to VOLIOC in volkern.h
 * !!! defined from 105 for dev. only...will start from 3 in final version
 */

#ifndef	_SYS_VOLKINT_H
#define	_SYS_VOLKINT_H

#define VOL_RESET_KERNEL	(VOLIOC | 111)

#define VOL_GET_KMEM		(VOLIOC | 112)
#define VOL_SET_KMEM		(VOLIOC | 113)

#define VOL_KTRANS		(VOLIOC | 114)
#define VOL_ABORT_KTRANS	(VOLIOC | 115)
#define VOL_GET_KTRANS_STATE	(VOLIOC | 117)

#define VOL_NEW_GROUP		(VOLIOC | 118)
#define VOL_CHANGE_GROUP	(VOLIOC | 119)
#define VOL_DELETE_GROUP	(VOLIOC | 120)
#define VOL_DUMP_GROUPS		(VOLIOC | 121)
#define VOL_GET_GROUPS		(VOLIOC | 122)

#define VOL_NEW_DISK		(VOLIOC | 123)
#define VOL_CHANGE_DISK		(VOLIOC | 124)
#define VOL_DELETE_DISK		(VOLIOC | 125)
#define VOL_DUMP_DISKS		(VOLIOC | 126)
#define VOL_GET_DISKS		(VOLIOC | 127)

#define VOL_GET_VOLUMES		(VOLIOC | 128)
#define VOL_DUMP_VOLUMES	(VOLIOC | 129)
#define VOL_DUMP_PLEXES		(VOLIOC | 130)
#define VOL_GET_PLEXES		(VOLIOC | 131)
#define VOL_DUMP_SUBDISKS	(VOLIOC | 132)
#define VOL_GET_SUBDISKS	(VOLIOC | 133)
#define VOL_GET_VOLUME_DEV	(VOLIOC | 143)
#define VOL_GET_PLEX_DEV	(VOLIOC | 144)

/*
 * Start of transaction ioctl's, these require the kernel stransaction
 * state to be VOL_KTRANS_PENDING.
 */

#define VOL_MIN_TRANS_IOC	(VOLIOC | 134)

#define VOL_COMMIT_KTRANS	(VOLIOC | 134)
#define VOL_NEW_VOLUME		(VOLIOC | 135)
#define VOL_CHANGE_VOLUME	(VOLIOC | 136)
#define VOL_DELETE_VOLUME	(VOLIOC | 137)
#define VOL_LOAD_PLEX		(VOLIOC | 138)
#define VOL_LOAD_SUBDISK	(VOLIOC | 139)
#define VOL_ASSERT_VOLUME	(VOLIOC | 140)
#define VOL_ASSERT_PLEX		(VOLIOC | 141)
#define VOL_ASSERT_SUBDISK	(VOLIOC | 142)

#define VOL_MAX_TRANS_IOC	(VOLIOC | 142)

/*
 * Kernel Logging ioctls. Used to initialize logging areas and sizes. Also
 * used to query logging errors etc.
 */
#define	VOL_KLOG_SETDGLOGSZ	(VOLIOC | 150)	/* Set disk group's log size */
#define VOL_KLOG_GETDGLOGSZ	(VOLIOC | 151)	/* Get disk group's log size */
#define	VOL_KLOG_SETLOG		(VOLIOC | 152)	/* Upload logging areas */
#define	VOL_KLOG_GETLOG		(VOLIOC | 153)	/* Dump out logging areas */
#define	VOL_KLOG_FREELOG	(VOLIOC | 154)	/* Free logging areas */
#define	VOL_KLOG_DGERRLIST	(VOLIOC | 155)	/* Return disk group logging
							errors */
#define	VOL_KLOG_ERRLIST	(VOLIOC | 156)	/* Return disk logging errors */
#define VOL_KLOG_DUMPENT	(VOLIOC | 157)	/* Dump out active logents */

/*
 * ioclts for voldio.
 * NOTE: VOL_VOLD_IOCTL and VOL_VOLD_SDI_INFO are preserved for compatibility
 *	 with beta releases of VxVM 1.2.
 */
#define VOL_VOLDIO_READ		(VOLIOC | 160)	/* read ioctl */
#define VOL_VOLDIO_WRITE	(VOLIOC | 161)	/* write ioctl */
#define VOL_VOLD_IOCTL		(VOLIOC | 162)	/* same as VOL_INDIRECT_IOCTL */
#define VOL_VOLD_SDI_INFO	(VOLIOC | 163)	/* same as VOL_GET_SDI_INFO */

/* ioctls for setting subdisk flags */

#define	VOL_SD_NULLWR		(VOLIOC | 170)

/* ioctls against /dev/volconfig to support rootability */

#define	VOL_REPLACE_VOLUME	(VOLIOC | 180)

/*
 * These ioctls are only available for debugging
 */
#define VOL_SET_ROOTDEV		(VOLIOC | 181)
#define VOL_SET_SWAPDEV		(VOLIOC | 182)
#define VOL_MODIFY_DG		(VOLIOC | 185)
#define VOL_SET_BOOTARGS	(VOLIOC | 186)
#define VOL_CLEAR_BOOTARGS	(VOLIOC | 187)
#define	VOL_CLEAR_ROOTFLAG	(VOLIOC | 188)
#define	VOL_CLEAR_SWAPFLAG	(VOLIOC | 189)

/*
 * Limits for ioctl's that allocate kernel memory
 */

#define VOL_MAX_GETSTRUCT	1024		/* !!! should be tunable */

/*
 * Number of vold/kernel private memory areas
 */

#define VOL_PRIVMEM_MAX_ID	256		/* !!! should be a tunable */
#define	VOL_PRIVMEM_CHUNK	16		/* granularity of allocation */
#define VOL_PRIVMEM_MAX_KMEM	1024*1024	/* limit of 1M in buffers */

/*
 * End of transaction ioctl's
 */


struct volkdg {
	char		kdg_uuid[VOL_UUID_SZ];	/* 0x00 diskgroupID */
	volrid_t	kdg_rid;		/* 0x44 record ID */
	char		kdg_name[NAME_SZ];	/* 0x4c local name */
	ulong_t		kdg_kflag;		/* 0x5c perm flags */
	ulong_t		kdg_vflag;		/* 0x60 vold-private flags */
	volseqno_t	kdg_config_tid;		/* 0x64 last commit */
};						/* 0x6c */

/*
 * Kernel flags set by vold
 */
#define DG_KFLAG_RDONLY	0x1			/* read only disk group */

struct volkdg_dump {
	size_t		kdgd_cnt;		/* 0x0 number of structs */
	struct volkdg	*kdgd_ptr;		/* 0x4 ptr to structs */
};						/* 0x8 */

struct volkdisk {
	char		kd_devname[NAME_SZ];	/* 0x00 /dev name */
	char		kd_name[NAME_SZ];	/* 0x0f admin. name */
	volrid_t	kd_rid;			/* 0x20 record ID */
	volrid_t	kd_dgrid;		/* 0x28 disk group ID */
	volrid_t	kd_dmrid;		/* 0x30 dm record ID **/
	ulong_t		kd_kflag;		/* 0x38 perm flag */
	ulong_t		kd_sflag;		/* 0x3c status flag */
	ulong_t		kd_vflag;		/* 0x40 vold flag */
	dev_t		kd_pub_dev;		/* 0x44 public partition */
	dev_t		kd_priv_dev;		/* 0x48 private partition */
	voff_t		kd_pub_len;		/* 0x4c public length */
	voff_t		kd_priv_len;		/* 0x50 private length */
	char		kd_type[DA_TYPE_SZ];	/* 0x54 disk type */
	char		kd_info[DA_INFO_SZ];	/* 0x63 type-specific info */
#ifdef __alpha
        char            kd_pub_path[DK_PATH_SZ];        /* 0xe4 */
        char            kd_priv_path[DK_PATH_SZ];       /* 0x105 */
                                                        /* 0x126 */
#else /* !__alpha */
						/* 0xe4 */
#endif /* __alpha*/
};

#define D_SFLAG_MASK	0x1		/* disk sflag mask */
#define D_SFLAG_SDOPEN	0x1		/* subdisk on this disk is open */

struct volkdisk_dump {
	volrid_t	kdd_dgrid;	/* 0x00 disk group ID */
	size_t		kdd_cnt;	/* 0x08 number of structs */
	struct volkdisk	*kdd_ptr;	/* 0x0c pointer to structs */
};					/* 0x10 */

struct volprivmem {
	ulong_t		pm_id;		/* 0x00 mem ID */
	size_t		pm_size;	/* 0x04 bytes */
	caddr_t		pm_ptr;		/* 0x08 contents */
};					/* 0x0c */

struct volktrans {
	volrid_t	kt_dgrid;	/* 0x00 diskgroup record ID */
	volseqno_t	kt_pendtid;	/* 0x08 pending trans ID */
};					/* 0x10 */

enum vol_ktrans_state {
	VOL_MIN_KTRANS_STATE,
	VOL_KTRANS_COMMITTED,	/* trans commited */
	VOL_KTRANS_ABORTED,	/* trans aborted */
	VOL_KTRANS_PENDING,	/* trans is current */
	VOL_MAX_KTRANS_STATE	
};

struct volktranstate {
	struct volktrans	kts_trans;	/* 0x00 current trans */
	enum vol_ktrans_state	kts_state;	/* 0x10 state */
	volseqno_t		kts_curtid;	/* 0x14 last commited tid */
	int			kts_abort_err;	/* 0x1c reason for abort */
	volrid_t		kts_abort_rid;	/* 0x20 abort record ID */
};						/* 0x28 */

/*
 * defines for kts_abort_err
 */
#define VKE_INVAL	1	/* invalid parameter in configuration */
#define VKE_ASSERT	2	/* assertion failed during commit */
#define VKE_REQUEST	3	/* abort requested via ioctl */
#define VKE_KLOGFAIL	4	/* klog of transaction commit failed */

struct volkvol {
	char			kv_name[NAME_SZ];	/* 0x00 */
	volrid_t		kv_rid;			/* 0x10 */
	dev_t			kv_dev;			/* 0x18 */
	voff_t			kv_len;			/* 0x1c */
	enum vol_r_pol		kv_read_pol;		/* 0x20 */
	volrid_t		kv_pref_plex;		/* 0x24 */
	enum vol_except		kv_r_all;		/* 0x2c */
	enum vol_except		kv_r_some;		/* 0x30 */
	enum vol_except		kv_w_all;		/* 0x34 */
	enum vol_except		kv_w_some;		/* 0x38 */
	enum vol_kstate		kv_kstate;		/* 0x3c */
	ulong_t			kv_kflag;		/* 0x40 */
	ulong_t			kv_sflag;		/* 0x44 */
	ulong_t			kv_vflag;		/* 0x48 */
	volseqno_t		kv_detach_tid;		/* 0x4c */
	ulong_t			kv_lasterr;		/* 0x54 */
	long			kv_log_serial_hi;	/* 0x58 */
	long			kv_log_serial_lo;	/* 0x5c */
	voff_t			kv_rwbackoff;		/* 0x60 read/writeback
								offset */
};							/* 0x64 */

/*
 * kernel flags set by vold
 */

#define V_KFLAG_MASK		0x0000ff	/* mask for volume pflag */
#define V_KFLAG_WRITEBACK	0x000001	/* writeback error enabled */
#define V_KFLAG_WRITECOPY	0x000002	/* log blk #s being changed */
#define V_KFLAG_RWBACK		0x000004	/* read/writeback mode */
#define V_KFLAG_LOG		0x000008	/* volume requires logging */
#define V_KFLAG_LOGTYPE		0x0000f0	/* mask for log type */
#define V_KFLAG_LOGUNDEF	0x000000	/* default logging on volume */
#define V_KFLAG_LOGNONE		0x000010	/* no logging on volume */
#define V_KFLAG_LOGBLKNO	0x000020	/* log block #s being changed */
#define V_KFLAG_LOGCLEAR	0x000100	/* detached log record should 
							be cleared */

/*
 * volume status flags set by kernel
 */

#define V_SFLAG_MASK		0x0000000f	/* volume sflag mask */
#define V_SFLAG_OPEN		0x00000001	/* volume is open */
#define V_SFLAG_KDETACH		0x00000002	/* volume has been detached */
#define V_SFLAG_RWBACK		0x00000004	/* read/writeback mode */
#define V_SFLAG_LOGDETACH	0x00000008      /* logging for the volume has
							been disabled */


/* volume structure change bits */
struct volkvol_dump {
	volrid_t	kvd_dgrid;		/* 0x00 disk group */
	size_t		kvd_cnt;		/* 0x08 struct count */
	struct volkvol	*kvd_ptr;		/* 0x0c user buf */
};						/* 0x10 */
struct volkvol_assert {
	volrid_t	kva_rid;		/* 0x00 */
	enum vol_kstate	kva_kstate;		/* 0x08 */
	ulong_t		kva_sflag;		/* 0x0c */
	ulong_t		kva_lasterr;		/* 0x10 */
};						/* 0x14 */
struct volkplex {
	char			kpl_name[NAME_SZ];		/* 0x00 */
	char			kpl_log_sd_name[NAME_SZ];	/* 0x0f */
	dev_t			kpl_dev;			/* 0x20 */
	volrid_t		kpl_rid;			/* 0x24 */
	volrid_t		kpl_volrid;			/* 0x2c */
	volrid_t		kpl_log_sdrid;			/* 0x34 */
	ulong_t			kpl_kflag;			/* 0x3c */
	ulong_t			kpl_sflag;			/* 0x40 */
	ulong_t			kpl_vflag;			/* 0x44 */
	enum plex_kstate	kpl_kstate;			/* 0x48 */
	enum plex_layout	kpl_layout;			/* 0x4c */
	voff_t			kpl_st_width;			/* 0x50 */
	volseqno_t		kpl_detach_tid;			/* 0x54 */
	ulong_t			kpl_lasterr;			/* 0x5c */
};								/* 0x60 */

/*
 * kernel plex flags set by vold
 */

#define PL_KFLAG_MASK		0x1f		/* mask for plex tflag */
#define PL_KFLAG_READ		0x01		/* 1=>read ops are allowed */
#define PL_KFLAG_WRITE		0x02		/* 1=>write ops are allowed */
#define PL_KFLAG_LOG		0x04		/* do update plex's log area */
#define PL_KFLAG_COMPLETE	0x08		/* plex is complete w.r.t. vp */
#define PL_KFLAG_NOERROR	0x10		/* 0=>participate in errors,
						 * 1=>don't participate */
#define PL_KFLAG_LOGCLEAR	0x20		/* klog entry for plex to be
						 * cleared */
#ifdef __alpha
#define PL_KFLAG_MODPLEX	0x40		/* kflag has been modified for
						 * dump only */
#endif /* __alpha */

#define PL_SFLAG_MASK		0x07	/* plex sflag mask */
#define PL_SFLAG_OPEN		0x01	/* plex is open */
#define	PL_SFLAG_KDETACH	0x02	/* plex has been detached */
#define PL_SFLAG_LOG		0x04	/* plex is logging */

struct volkplex_dump {
	volrid_t	kpld_dgrid;		/* 0x00 */
	size_t		kpld_cnt;		/* 0x08 */
	struct volkplex	*kpld_ptr;		/* 0x0c */
};						/* 0x10 */
struct volkplex_assert {
	volrid_t		kpla_rid;	/* 0x00 */
	volrid_t		kpla_volrid;	/* 0x08 */
	enum plex_kstate	kpla_kstate;	/* 0x10 */
	ulong_t			kpla_sflag;	/* 0x14 */
	ulong_t			kpla_lasterr;	/* 0x18 */
};						/* 0x1c */
struct volksd {
	char			ksd_name[NAME_SZ];		/* 0x00 */
	volrid_t		ksd_rid;			/* 0x10 */
	volrid_t		ksd_drid;			/* 0x18 */
	volrid_t		ksd_plrid;			/* 0x20 */
	volrid_t		ksd_volrid;			/* 0x28 */
	ulong_t			ksd_kflag;			/* 0x30 */
	ulong_t			ksd_sflag;			/* 0x34 */
	ulong_t			ksd_vflag;			/* 0x38 */
	voff_t			ksd_offset;			/* 0x3c */
	voff_t			ksd_pl_offset;			/* 0x40 */
	voff_t			ksd_len;			/* 0x44 */
								/* 0x48 */
};

#define SD_KFLAG_MASK		0x00000003	/* subdisk kflag mask */
#define SD_KFLAG_LOG		0x00000001	/* subdisk is a log subdisk */
#define SD_KFLAG_IGNORE_WRITES	0x00000002	/* sd is read-only but write */
						/*  ops return success */

#define SD_SFLAG_MASK		0x00000003	/* subdisk sflag mask */
#define SD_SFLAG_LOG		0x00000001	/* subdisk is used as a log */
#define SD_SFLAG_OPEN		0x00000002	/* subdisk is open */

struct volksd_dump {
	volrid_t	ksdd_dgrid;		/* 0x00 */
	size_t		ksdd_cnt;		/* 0x08 */
	struct volksd	*ksdd_ptr;		/* 0x0c */
};						/* 0x10 */
struct volksd_assert {
	volrid_t	ksda_rid;		/* 0x00 */
	volrid_t	ksda_volrid;		/* 0x08 */
	ulong_t		ksda_sflag;		/* 0x10 */
	ulong_t		ksda_lasterr;		/* 0x14 */
};						/* 0x18 */

/*
 * The following structures define the structures passed as part of the ioctl
 * interface for the kernel logging functions.
 */

/*
 * This structure for the VOL_KLOG_DGLOGSZ ioctl call that will resize the
 * log for a disk group.
 */
struct volklog_dglogsz {
	volrid_t	dlz_dgrid;	/* 0x0 Disk group */
	long		dlz_size;	/* 0x8 New log length */
};					/* 0xc */

/* 
 * The following structure contains a description of a logging area on
 * disk. The area is defined by the device and offset on the disk device.
 * The log offset represented by this area is dependant on the logging
 * area's position in the table of logareas pointed to by the disk
 * structure.
 */
struct volklogarea {
	int	lr_flags;	/* 0x0 flags controlling the log area */
	int	lr_error;	/* 0x4 dev returned an error and is disabled */
	voff_t	lr_off;		/* 0x8 offset into logging device */
};				/* 0xc */

/*
 * Flags for lr_flags.
 */
#define VOL_LR_PRIVREGION	0x1	/* dev for log area is private region */
#define VOL_LR_PUBREGION	0x2	/* dev for log area is public region */

/*
 * This structure is for the VOL_KLOG_SETLOG ioctl that sets up a specified
 * log copy for a specified disk.
 */
struct volklog_setlog {
	volrid_t		sl_drid;	/* 0x00 disk in group */
	long			sl_logcpy;	/* 0x08 which log copy */
	struct volklogarea	*sl_logareap;	/* 0x0c table of log areas */
	int			sl_nlogarea;	/* 0x10 # of log areas */
};						/* 0x14 */

/*
 * This structure is used for the VOL_KLOG_DGERRLIST, VOL_KLOG_ERRLIST, and
 * VOL_KLOG_DUMPENT ioctl calls. It defines the disk group and optionally
 * the disk to restrict the search for the data to. It also defines the user
 * address where the returned data is to be stored, and the number of structures
 * of the appropriate type that the memory has space to hold.
 */
struct volklog_getlist {
	volrid_t	gl_dgrid;	/* 0x00 disk group */
	volrid_t	gl_disk;	/* 0x08 disk */
	caddr_t		gl_addr;	/* 0x10 user address for copyout */
	long		gl_size;	/* 0x14 number of structs to copy */
};					/* 0x18 */

/*
 * The following identifies a failing log for a specific disk group.
 */
struct voldg_errlist {
	volrid_t	vdg_disk;	/* 0x0 disk with a failed log copy */
	int		vdg_copy;	/* 0x8 copy number of log in disk */
};					/* 0xc */

/*
 * The following identifies a failing log block on a specific disk.
 * This structure is generated solely for the interface to vold. 
 */
struct voldisk_errlist {
	int	vd_copy;	/* 0x0 copy number of failed log in disk */
	int	vd_blkoff;	/* 0x4 block offset of failure in log */
};				/* 0x8 */

/*
 * Structure defining a disk region to perform I/O to.
 */
struct voldio_region {
	ulong_t		vdior_flags;	/* 0x00 flags */
	int		vdior_errno;	/* 0x04 errno for failed ops */
	volrid_t	vdior_drid;	/* 0x08 disk rid */
	voff_t		vdior_offset;	/* 0x10 offset on device */
};					/* 0x14 */

#define VOL_VOLDIO_REG_PUB	0x1
#define VOL_VOLDIO_REG_PRIV	0x2

/*
 * Structure used by vold to request parallel I/O operations from the kernel.
 */
struct voldio {
	ulong_t			vdio_flags;	/* 0x00 flags */
	caddr_t			vdio_buf;	/* 0x04 ptr to I/O buffer */
	size_t			vdio_len;	/* 0x08 length of buffer */
	size_t			vdio_nregion;	/* 0x0c # of region structs */
	struct voldio_region	vdio_regions[1];/* 0x10 I/O regions */
};						/* 0x24 */

/*
 * extended reason codes for commit failures -- set in volreason
 */
#define	VR_COMMIT_KLOG		1
#define	VR_OPEN_VOLUME		2
#define	VR_NO_VP		3
#define	VR_PREFPLEX		4
#define	VR_STRIPE_COMPACT	5
#define	VR_STRIPE_NO_SD		6
#define	VR_STRIPE_LIMIT		7
#define	VR_STRIPE_GRAIN		8
#define	VR_STRIPE_SD_LEN	9
#define	VR_ASSERT_VOLUME	10
#define	VR_ASSERT_PLEX		11
#define	VR_ASSERT_SD		12

/* Use these values for testing rootability */

#define	VOL_ROOT_DEVICE		NODEV
#define VOL_SWAP_DEVICE		NODEV

#define VOL_RID_SPECIAL_HI	0	/* high long of special rids */

#define	VOL_ROOTDG_SPECIAL_RID	0x01	/* special rid for root disk group */
#define VOL_ROOTDG_SPECIAL_NAME	"ROOTDG" /* name for special root dg */

#define	VOL_ROOTDISK_SPECIAL_RID 0x02	/* special rid for root disk */
#define	VOL_ROOTDISK_SPECIAL_NM	"ROOT"	/* special name for root disk */
#define	VOL_ROOTDISK_SPECIAL_ANM "ROOTDISK" /* speical admin name */

#define	VOL_ROOTVOL_SPECIAL_NAME "ROOTVOL" /* name for root volume */
#define VOL_ROOTVOL_SPECIAL_RID	0x10	/* special rid for root volume */

#define VOL_ROOTPLEX_SPECIAL_RID 0x11	/* special rid for plex of root vol */
#define	VOL_ROOTPLEX_SPECIAL_NAME "ROOTPLEX" /* name for root plex */

#define	VOL_ROOTSD_SPECIAL_RID	0x12	/* special rid for sd of root plex */
#define VOL_ROOTSD_SPECIAL_NAME	"ROOTSD" /* name of root subdisk */

#define	VOL_SWAPDISK_SPECIAL_RID 0x03	/* special rid for swap disk */
#define	VOL_SWAPDISK_SPECIAL_NM	"SWAP"	/* special name for swap disk */
#define	VOL_SWAPDISK_SPECIAL_ANM "SWAPDISK" /* special admin name */

#define	VOL_SWAPVOL_SPECIAL_NAME "SWAPVOL" /* name for swap volume */
#define	VOL_SWAPVOL_SPECIAL_RID	0x20	/* special rid for swap volume */

#define	VOL_SWAPPLEX_SPECIAL_NAME "SWAPPLEX" /* name for swap plex */
#define VOL_SWAPPLEX_SPECIAL_RID 0x21	/* special rid for plex of swap vol */

#define	VOL_SWAPSD_SPECIAL_NAME	"SWAPSD" /* name of swap subdisk */
#define	VOL_SWAPSD_SPECIAL_RID	0x22	/* special rid for sd of swap plex */

#endif /* _SYS_VOLKINT_H */
