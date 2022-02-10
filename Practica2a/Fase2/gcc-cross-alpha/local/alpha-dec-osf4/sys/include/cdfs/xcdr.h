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
 * @(#)$RCSfile: xcdr.h,v $ $Revision: 1.1.3.2 $ (DEC) $Date: 1993/08/11 19:29:36 $
 */
#ifndef	_CDFS_XCDR_INCLUDE
#define	_CDFS_XCDR_INCLUDE	1
/*
 * X/OPEN CD-ROM Support Component (XCDR), preliminary specification (1991)
 */
#include <sys/types.h>
#include <sys/mode.h>

#define _STDID_SZ 5
#define _SYSID_SZ 32
#define _VOLID_SZ 32
#define _ROOTDIR_SZ 34
#define _VSID_SZ 128
#define _PUBID_SZ 128
#define _DTPRE_SZ 128
#define _APPID_SZ 128
#define _FILID_SZ 37
#define _APPUSE_SZ 512
#define _RES2_SZ 653
#define _SYSUSE_SZ 64
#define _DIRID_SZ 31
#define _DR_SYSUSE_SZ 218

#define _ISO_DTLEN 17

/*
 * iso9660_pvd is used by cd_pvd()
 */
struct iso9660_pvd {
	unsigned char	voldestype;	/* Volume Descriptor Type */
	unsigned char	std_id[_STDID_SZ]; /* Standard Identifier */
	unsigned char	voldesvers;	/* Volume Descriptor Version */
	unsigned char	not_used_1;
	unsigned char	sys_id[_SYSID_SZ];	/* System Identifier */
        unsigned char	vol_id[_VOLID_SZ];	/* Volume Identifier */
        unsigned char	not_used_2[8];
	unsigned int	volspcsize;	/* Volume Space Size (logical blocks) */
	unsigned short	volsetsize;	/* Volume Set Size */
	unsigned short	volseqno;	/* Volume Sequence Number */
	unsigned short	lblksize;	/* Logical Block Size (bytes) */
	unsigned int	ptsize;		/* Path Table Size (bytes) */
	unsigned int	locpt_l;	/* Location of Type L Path Table */
	unsigned int	locptopt_l;	/* Location of opt. Type L Path Table */
	unsigned int	locpt_m;	/* Location of Type M Path Table */
	unsigned int	locptopt_m;	/* Location of opt. Type M Path Table */
	unsigned char	rootdir[_ROOTDIR_SZ]; /* Directory Record for Root Dir */
	unsigned char	volset_id[_VSID_SZ];	/* Volume Set Identifier */
	unsigned char	pub_id[_PUBID_SZ];	/* Publisher Identifier */
	unsigned char	dtpre_id[_DTPRE_SZ];	/* Data Preparer Identifier */
	unsigned char	app_id[_APPID_SZ];	/* Application Identifier */
	unsigned char	cpfile_id[_FILID_SZ];	/* Copyright File Identifier */
	unsigned char	abfile_id[_FILID_SZ];	/* Abstract File Identifier */
	unsigned char	bgfile_id[_FILID_SZ];	/* Bibliographic File Identifier */
	time_t		cre_time;	/* Volume Creation Date and Time */
	time_t		mod_time;	/* Volume Modification Date and Time */
	time_t		exp_time;	/* Volume Expiration Date and Time */
	time_t		eff_time;	/* Volume Effective Date and Time */
	unsigned char	filestrver;	/* File Structure Version */
	unsigned char	res1;		/* Reserved (byte pos 883) */
	unsigned char	appuse[_APPUSE_SZ];	/* Application Use */
	unsigned char	res2[_RES2_SZ];	/* Reserved (byte pos 1396-2048) */
}; /* 2048 bytes long */

#define CD_PVDLEN	2048	/* Length of pvd */



/*
 * iso9660_xar is used by cd_xar()
 */
struct iso9660_xar {
	unsigned short	own_id;		/* Owner Identification */
	unsigned short	grp_id;		/* Group Identification */
	unsigned short	permissions;	/* Permissions (see below) */
	time_t		cre_time;	/* File Creation Date and Time */
	time_t		mod_time;	/* File Modification Date and Time */
	time_t		exp_time;	/* File Expiration Date and Time */
	time_t		eff_time;	/* File Effective Date and Time */
	unsigned char	rec_form;	/* Record Format */
	unsigned char	rec_attr;	/* Record Attributes */
	unsigned short	rec_len;	/* Record Length */
	unsigned char	sys_id[_SYSID_SZ]; /* System Identifier */
	unsigned char	sys_use[_SYSUSE_SZ]; /* System Use */
	unsigned char	xar_vers;	/* XAR Version */
	unsigned char	esc_len;	/* Length of Escape Sequences */
	unsigned char	resv[64];	/* Reserved */
	unsigned char	appuse_len;	/* Length of Application Use */
	unsigned char	*app_use;	/* Pointer to Application Use field */
	unsigned char	*esc_seq;	/* Pointer to Escape Sequences field */
};

#define CD_XARFIXL	250	/* Length of fixed part of XAR */

/* permissions */

#define CD_RSYS	0x0001		/* read permission, system class */
#define CD_XSYS	0x0004		/* execute permission, system class */
#define CD_RUSR	0x0010
#define CD_XUSR	0x0040
#define CD_RGRP	0x0100
#define CD_XGRP	0x0400
#define CD_ROTH	0x1000
#define CD_XOTH	0x4000



/*
 * iso9660_drec is used by cd_drec()
 */
struct iso9660_drec {
	unsigned char	drec_len;	/* Length of Directory Record (bytes) */
	unsigned char	xar_len;	/* XAR Length (logical blocks) */
	unsigned int	locext;		/* Location of Extent */
	unsigned int	data_len;	/* Data Length */
	time_t		rec_time;	/* Recording Date and Time */
	unsigned char	file_flags;	/* File Flags (see below) */
	unsigned char	file_usize;	/* File Unit Size */
	unsigned char	ileav_gsize;	/* Interleave Gap Size */
	unsigned short	volseqno;	/* Volume Sequence Number */
	unsigned char	fileid_len;	/* Length of File Identifier */
	unsigned char	file_id[_FILID_SZ];	/* File Identifier */
	unsigned char	sysuse_len;	/* Length of System Use */
	unsigned char	sys_use[_DR_SYSUSE_SZ];	/* System Use */
};

#define CD_MAXDRECL	255	/* Maximum Length of Directory Record */

/* file_flags */
#define CD_EXIST	0x01
#define CD_DIR		0x02
#define CD_ASSOFILE	0x04
#define CD_RECORD	0x08
#define CD_PROTEC	0x10
#define CD_MULTIEXT	0x80

/*
 * iso9660_ptrec is used by cd_ptrec()
 */
struct iso9660_ptrec {
	unsigned char	dirid_len;	/* Length of Directory Ident. (bytes) */
	unsigned char	xar_len;	/* XAR Length (logical blocks) */
	unsigned int	loc_ext;	/* Location of Extent */
	unsigned short	pdirno;		/* Parent Directory Number */
	unsigned char	dir_id[_DIRID_SZ]; /* Directory Identifier */
};

#define CD_MAXPTRECL	40	/* Maximum Length of Path Table Record */

struct _cd_cptrec {
    unsigned char di_len;
    unsigned char xar_len;
    unsigned char extent[4];
    unsigned char parent[2];
    unsigned char dir_id[2];		/* includes pad; may extend
					   to total size of CD_MAXPTRECL */
};

#define PTRECLEN(ptrec) (8 + (ptrec)->di_len + (((ptrec)->di_len&0x1) ? 1 : 0))

/*
 * cd_type() function returns:
 */
#define CD_ISO9660	ISO_9660	/* CD-ROM is recorded according to
					   ISO 9660 */
#define CD_HSG		ISO_HSG		/* CD-ROM is recorded according to
					   High Sierra Group */
#define CD_RRIP		ISO_RRIP	/* CD-ROM is recorded according to
					   ISO 9660 + Rock Ridge */

/*
 * cd_defs() 'cmd' argument:
 */
#define CD_SETDEFS	1	/* Set default values */
#define CD_GETDEFS	2	/* Get default values */

struct cd_defs {
	uid_t		def_uid;	/* Default User ID */
	gid_t		def_gid;	/* Default Group ID */
	mode_t		def_fperm;	/* Default File Permissions */
	mode_t		def_dperm;	/* Default Directory Permissions */
	int		dirsperm;	/* Directory search permissions */
};

#define CD_DIRXAR	1	/* execute permission:  use xar */
#define CD_DIRRX	2	/* execute permission:  if xar has read-perm */


/*
 * cd_idmap() 'cmd' argument:
 */
#define CD_SETUMAP	0x01	/* Set User ID mapping */
#define CD_SETGMAP	0x02	/* Set Group ID mapping */
#define CD_GETUMAP	0x11	/* Get User ID mapping */
#define CD_GETGMAP	0x12	/* Get Group ID mapping */

struct cd_idmap {
	unsigned short	from_id;/* Owner on CD_ROM */
	uid_t		to_uid;	/* Owner ID in XSI file hierarchy */
	gid_t		to_gid;	/* Group ID in XSI file hierarchy */
};

#define CD_MAXUMAP	50	/* Maximum UMAP */
#define CD_MAXGMAP	50	/* Maximum GMAP */



/*
 * cd_nmconv() function 'cmd' argument:
 */
#define CD_SETNMCONV	1	/* Set file name conversion */
#define CD_GETNMCONV	2	/* Get file name conversion */

#define CD_NOCONV	0x00	/* no conversion */
#define CD_LOWER	0x01	/* convert to lowercase, drop null suffix */
#define CD_NOVERSION	0x02	/* drop version suffix (and ";") */

struct _cd_cxar_getarg {
    int fsec;
    char *xar;
    int xarlen, retlen;
};

struct _cd_cdrec_getarg {
    int fsec;
    char *drec;
};

struct _cd_idmap_getarg {
    int cmd;
    struct cd_idmap *maps;
    int nmaps;
};

struct _cd_nmconv_getarg {
    int cmd;
    int flag;
};

struct _cd_getptblock {
    char block[CD_MAXPTRECL];
};

/*
 * XCDR ioctl commands:
 */
/* cf. <cdfs/rrip.h> values */
/* ioctl() does not handle input/output args greater than 128,
   so for large structures we must pass pointers and use copyout() */
#define CDIO_XCDR_CPVD	_IOW('C', 127, char *) /* cd_cpvd() */
#define CDIO_XCDR_CXAR	_IOWR('C', 126, struct _cd_cxar_getarg) /* cd_cxar() */
#define CDIO_XCDR_CDREC	_IOWR('C', 125, struct _cd_cdrec_getarg) /* cd_cdrec() */
#define CDIO_XCDR_PTREC	_IOR('C', 124, struct iso9660_ptrec) /* cd_ptrec() */
#define CDIO_GET_PTREC	_IOR('C', 123, struct _cd_getptblock) /* cd_cptrec() */
#define CDIO_XCDR_TYPE	_IOR('C', 122, int) /* cd_type() */

/* this is GET mappings only; set happens through mount with M_UPDATE */
#define	CDIO_XCDR_GMAP	_IOWR('C', 118, struct _cd_idmap_getarg) /* cd_idmap() */

/* cd_defs() is handled solely through mount() and statfs() */
/* cd_nmconv() is handled solely through mount() and statfs() */

#ifndef _KERNEL
extern int cd_pvd(char *, struct iso9660_pvd *);
extern int cd_cpvd(char *, char *);
extern int cd_xar(char *, int, struct iso9660_xar *, int, int);
extern int cd_cxar(char *, int, char *, int);
extern int cd_drec(char *, int, struct iso9660_drec *);
extern int cd_cdrec(char *, int, char *);
extern int cd_ptrec(char *, struct iso9660_ptrec *);
extern int cd_cptrec(char *, char *);
extern int cd_type(char *);

extern int cd_defs(char *, int, struct cd_defs *);
extern int cd_idmap(char *, int, struct cd_idmap *, int *);
extern int cd_nmconv(char *, int, int *);

#endif /* _KERNEL */
#endif /* _CDFS_XCDR_INCLUDE */
