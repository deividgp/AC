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
 *	@(#)$RCSfile: disklabel.h,v $ $Revision: 4.3.28.3 $ (DEC) $Date: 1999/02/11 20:53:59 $
 */
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1987, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef	_DISKLABEL_
#define _DISKLABEL_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/*
 * Disk description table, see disktab(5)
 */
#define	DISKTAB		"/etc/disktab"

/*
 * Each disk has a label which includes information about the hardware
 * disk geometry, filesystem partitions, and drive specific information.
 * The label is in block 0 or 1, possibly offset from the beginning
 * to leave room for a bootstrap, etc.
 */

#define LABELSECTOR	0			/* sector containing label */
#define LABELOFFSET	64			/* offset of label in sector */

#define DISKMAGIC	((u_int) 0x82564557)	/* The disk magic number */
#ifndef MAXPARTITIONS
#define	MAXPARTITIONS	8
#endif

/* moved struct out of disklabel struct so partinfo struct can access it */
struct	partition {		/* the partition table */
	u_int	p_size;		/* number of sectors in partition */
	u_int	p_offset;	/* starting sector */
	u_int	p_fsize;	/* filesystem basic fragment size */
	u_char	p_fstype;	/* filesystem type, see below */
	u_char	p_frag;		/* filesystem fragments per block */
	u_short	p_cpg;		/* filesystem cylinders per group */
};

#ifndef LOCORE
struct disklabel {
	u_int	d_magic;		/* the magic number */
	short	d_type;			/* drive type */
	short	d_subtype;		/* controller/d_type specific */
	char	d_typename[16];		/* type name, e.g. "eagle" */
	/*
	 * d_packname contains the pack identifier and is returned when
	 * the disklabel is read off the disk or in-core copy.
	 * d_boot0 and d_boot1 are the (optional) names of the
	 * primary (block 0) and secondary (block 1-15) bootstraps
	 * as found in /usr/mdec.  These are returned when using
	 * getdiskbyname(3) to retrieve the values from /etc/disktab.
	 */
#if defined(KERNEL) || defined(STANDALONE)
	char	d_packname[16];			/* pack identifier */
#else
	union {
		char	un_d_packname[16];	/* pack identifier */
		struct {
			char *un_d_boot0;	/* primary bootstrap name */
			char *un_d_boot1;	/* secondary bootstrap name */
		} un_b;
	} d_un;
#define d_packname	d_un.un_d_packname
#define d_boot0		d_un.un_b.un_d_boot0
#define d_boot1		d_un.un_b.un_d_boot1
#endif	/* ! KERNEL or STANDALONE */
			/* disk geometry: */
	u_int	d_secsize;		/* # of bytes per sector */
	u_int	d_nsectors;		/* # of data sectors per track */
	u_int	d_ntracks;		/* # of tracks per cylinder */
	u_int	d_ncylinders;		/* # of data cylinders per unit */
	u_int	d_secpercyl;		/* # of data sectors per cylinder */
	u_int	d_secperunit;		/* # of data sectors per unit */
	/*
	 * Spares (bad sector replacements) below
	 * are not counted in d_nsectors or d_secpercyl.
	 * Spare sectors are assumed to be physical sectors
	 * which occupy space at the end of each track and/or cylinder.
	 */
	u_short	d_sparespertrack;	/* # of spare sectors per track */
	u_short	d_sparespercyl;		/* # of spare sectors per cylinder */
	/*
	 * Alternate cylinders include maintenance, replacement,
	 * configuration description areas, etc.
	 */
	u_int	d_acylinders;		/* # of alt. cylinders per unit */

			/* hardware characteristics: */
	/*
	 * d_interleave, d_trackskew and d_cylskew describe perturbations
	 * in the media format used to compensate for a slow controller.
	 * Interleave is physical sector interleave, set up by the formatter
	 * or controller when formatting.  When interleaving is in use,
	 * logically adjacent sectors are not physically contiguous,
	 * but instead are separated by some number of sectors.
	 * It is specified as the ratio of physical sectors traversed
	 * per logical sector.  Thus an interleave of 1:1 implies contiguous
	 * layout, while 2:1 implies that logical sector 0 is separated
	 * by one sector from logical sector 1.
	 * d_trackskew is the offset of sector 0 on track N
	 * relative to sector 0 on track N-1 on the same cylinder.
	 * Finally, d_cylskew is the offset of sector 0 on cylinder N
	 * relative to sector 0 on cylinder N-1.
	 */
	u_short	d_rpm;			/* rotational speed */
	u_short	d_interleave;		/* hardware sector interleave */
	u_short	d_trackskew;		/* sector 0 skew, per track */
	u_short	d_cylskew;		/* sector 0 skew, per cylinder */
	u_int	d_headswitch;		/* head switch time, usec */
	u_int	d_trkseek;		/* track-to-track seek, usec */
	u_int	d_flags;		/* generic flags */
#define NDDATA 5
	u_int	d_drivedata[NDDATA];	/* drive-type specific information */
#define NSPARE 5
	u_int	d_spare[NSPARE];	/* reserved for future use */
	u_int	d_magic2;		/* the magic number (again) */
	u_short	d_checksum;		/* xor of data incl. partitions */

			/* filesystem and partition information: */
	u_short	d_npartitions;		/* number of partitions in following */
	u_int	d_bbsize;		/* size of boot area at sn0, bytes */
	u_int	d_sbsize;		/* max size of fs superblock, bytes */
	struct partition d_partitions[MAXPARTITIONS];	/* actually may be more */
#ifdef __alpha
#if defined(KERNEL) || defined(STANDALONE)
	u_int	d_xxx;			/* to make struct = for all def's */
#endif
#endif
};
#else /* LOCORE */
	/*
	 * offsets for asm boot files.
	 */
	.set	d_secsize,40
	.set	d_nsectors,44
	.set	d_ntracks,48
	.set	d_ncylinders,52
	.set	d_secpercyl,56
	.set	d_secperunit,60
#ifdef __alpha
	.set	d_end_,280		/* size of disk label */
#else
	.set	d_end_,276		/* size of disk label */
#endif /* __alpha */
#endif /* LOCORE */

/* d_type values: */
#define	DTYPE_SMD		1		/* SMD, XSMD; VAX hp/up */
#define	DTYPE_MSCP		2		/* MSCP */
#define	DTYPE_DEC		3		/* other DEC (rk, rl) */
#define	DTYPE_SCSI		4		/* SCSI */
#define	DTYPE_ESDI		5		/* ESDI interface */
#define	DTYPE_ST506		6		/* ST506 etc. */
#define DTYPE_IDE		9		/* EIDE */
#define	DTYPE_FLOPPY		10		/* floppy */
#define DTYPE_SWXCR		11		/* StorageWorks RAID */

#ifdef DKTYPENAMES
static char *dktypenames[] = {
	"unknown",
	"SMD",
	"MSCP",
	"old DEC",
	"SCSI",
	"ESDI",
	"type 6",
	"type 7",
	"type 8",
	"EIDE",
	"floppy",
	"SWXCR",
	0
};
#define DKMAXTYPES	(sizeof(dktypenames) / sizeof(dktypenames[0]) - 1)
#endif

/*
 * Filesystem type and version.
 * Used to interpret other filesystem-specific
 * per-partition information.
 */
#define	FS_UNUSED	0		/* unused */
#define	FS_SWAP		1		/* swap */
#define	FS_V6		2		/* Sixth Edition */
#define	FS_V7		3		/* Seventh Edition */
#define	FS_SYSV		4		/* System V */
#define	FS_V71K		5		/* V7 with 1K blocks (4.1, 2.9) */
#define	FS_V8		6		/* Eighth Edition, 4K blocks */
#define	FS_BSDFFS	7		/* 4.2BSD fast file system */
/* OSF will reserve 16--31 for vendor-specific entries */
#define	FS_ADVFS	16		/* Digital Advanced File System */
#define	FS_LSMpubl	17		/* Digital Log. Storage public region  */
#define	FS_LSMpriv	18		/* Digital Log. Storage private region */
#define	FS_LSMsimp	19		/* Digital Log. Storage simple disk    */
#define FS_LSMnopriv	20		/* Digital Log. Storage */
#define FS_DB		21		/* Application Database*/
#define FS_RAW		22		/* Raw Data */
#define FS_DRD		23		/* Distributed Raw Disk - DRD*/
#define FS_CDFS         25              /* CDFS file system */

#ifdef	DKTYPENAMES
static char *fstypenames[] = {
	"unused",
	"swap",
	"Version 6",
	"Version 7",
	"System V",
	"4.1BSD",
	"Eighth Edition",
	"4.2BSD",
	"resrvd8",
	"resrvd9",
	"resrvd10",
	"resrvd11",
	"resrvd12",
	"resrvd13",
	"resrvd14",
	"resrvd15",
	"AdvFS",
	"LSMpubl",
	"LSMpriv",
	"LSMsimp",
	"LSMnoprv",
	"database",
	"raw",
	"DRD",
        "cnx",
        "CDFS",
	0
};
#define FSMAXTYPES	(sizeof(fstypenames) / sizeof(fstypenames[0]) - 1)
#endif

/*
 * flags shared by various drives:
 */
#define		D_REMOVABLE	0x01		/* removable media */
#define		D_ECC		0x02		/* supports ECC */
#define		D_BADSECT	0x04		/* supports bad sector forw. */
#define		D_RAMDISK	0x08		/* disk emulator */
#define		D_CHAIN		0x10		/* can do back-back transfers */
/*
 * A dynamic geometry device is a device which may have its underlying
 * characteristics change, depending on how the device is configured
 * (a RAID device, for example).
 */
#define		D_DYNAM_GEOM	0x20		/* dynamic geometry device */
/*
 * An invented geometry is created from the disk capacity when no geometry
 * information is available from the device (i.e.: ns = nt = nc = 0 )
 */
#define         D_INVENT_GEOM   0x40            /* geometry invented */

/*
 * Drive data for SMD.
 */
#define	d_smdflags	d_drivedata[0]
#define		D_SSE		0x1		/* supports skip sectoring */
#define	d_mindist	d_drivedata[1]
#define	d_maxdist	d_drivedata[2]
#define	d_sdist		d_drivedata[3]

/*
 * Drive data for ST506.
 */
#define d_precompcyl	d_drivedata[0]
#define d_gap3		d_drivedata[1]		/* used only when formatting */

#ifndef LOCORE
/*
 * Structure used to perform a format
 * or other raw operation, returning data
 * and/or register values.
 * Register identification and format
 * are device- and driver-dependent.
 */
struct format_op {
	char	*df_buf;
	int	df_count;		/* value-result */
	daddr_t	df_startblk;
	int	df_reg[8];		/* result */
};

/*
 * Structure used internally to retrieve
 * information about a partition on a disk.
 */
struct partinfo {
	struct disklabel *disklab;
	struct partition *part;
};

/*
 * This partition structure is returned when getting the current
 * partition (DIOCGCURPT) or the default partition (DIOCGDEFPT),
 * for a device.  Note that unlike other disklabel functions, these
 * ioctl's return default or current partition tables, regardless of
 * whether a valid disklabel exists on the specified disk.
 */
struct pt_tbl {
	struct partition d_partitions[MAXPARTITIONS];
};

/*
 * Disk-specific ioctls.
 */
		/* get and set disklabel; DIOCGPART used internally */
#define DIOCGDINFO	_IOR('d', 101, struct disklabel)/* get */
#define DIOCSDINFO	_IOW('d', 102, struct disklabel)/* set */
#define DIOCWDINFO	_IOW('d', 103, struct disklabel)/* set, update disk */
#define DIOCGPART	_IOW('d', 104, struct partinfo)	/* get partition */

/* do format operation, read or write */
#define DIOCRFORMAT	_IOWR('d', 105, struct format_op)
#define DIOCWFORMAT	_IOWR('d', 106, struct format_op)

#define DIOCSSTEP	_IOW('d', 107, int)	/* set step rate */
#define DIOCSRETRIES	_IOW('d', 108, int)	/* set # of retries */
#define DIOCWLABEL	_IOW('d', 109, int)	/* write en/disable label */

#define DIOCSBAD	_IOW('d', 110, struct dkbad)	/* set kernel dkbad */

#define DIOCGDEFPT	_IOR('d', 111, struct pt_tbl)	/* get default pt */
#define DIOCGCURPT	_IOR('d', 112, struct pt_tbl)	/* get current pt */

/* return mask of open partitions	*/
#define DIOCGPARTMASK	_IOW('d', 113, U32)	/* get open partition mask */

#endif /* LOCORE */

#if !defined(KERNEL) && !defined(LOCORE)

extern struct disklabel *getdiskbyname __((char *));
extern struct disklabel *creatediskbyname __((char *));
#ifdef	_THREAD_SAFE
extern int getdiskbyname_r __((char *, struct disklabel *, char *, int));
extern int creatediskbyname_r __((char *, struct disklabel *));
#endif	/* _THREAD_SAFE */
extern int createlabel __((char *, char *, struct disklabel *, char *, int));

#endif	/* !KERNEL && !LOCORE */

#ifdef _KERNEL 
#define OV_BADPATH    1
#define OV_UNUSED     2
#define OV_BADFS      3
#define OV_VOL        4
#define OV_FAIL       5
#endif /* KERNEL */


#ifdef __cplusplus
}
#endif
#endif	/* _DISKLABEL_ */
