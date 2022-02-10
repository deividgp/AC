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
 * @(#)$RCSfile: dvdfs.h,v $ $Revision: 1.1.2.4 $ (DEC) $Date: 1999/01/29 20:45:50 $
 */
#ifndef	_DVDFS_FS_H_
#define _DVDFS_FS_H_


#pragma environment_save
#pragma pack 1

#include <sys/types.h>
#include <sys/param.h>

#define DVDFS_IOBLOCKSIZE	2048



/*
 * OSTA UDF definitions
 */

/*
 * type declarations
 */

typedef	unsigned char		byte;
typedef	unsigned char		uchar8;
typedef unsigned char		uint8;
typedef unsigned short int	uint16;
typedef unsigned int		uint32;
typedef unsigned long int	uint64;

/* 
 * dstring is a null-terminated string of length n, where d is the count of
 * characters in the string; d is recorded at byte offset n-1, the characters
 * are recorded starting with the first byte of the field, and #00 is
 * recorded at byte offset d+1 through n-2, inclusive.  OSTA 2.00 2.1.3
 */
typedef byte			dstring;

/*
 * misc defines
 */
#define XX 4
#define ANCHOR_LOC		256	/* location of anchor vol des ptr */
#define DVD_SECSIZE		2048

/*
 * on-disk structures
 */


struct charspec {	/* OSTA 2.00 2.1.2 */
	uint8	charset_type;		/* 0 (zero) (CS0 coded char set) */
	byte	charset_info[63];	/* "OSTA Compressed Unicode" */
};

struct timestamp {	/* OSTA 2.00 2.1.4 */
	uint16	type_timezone;	/* 4 MSB type; 12 LSB timezone       */
				/* type must be 1 (one) (local time) */
				/* timezone indicates +/- minutes    */
				/* from Coordinated Universal Time   */
				/* or -2047 if not supported         */
	uint16	year;
	uint8	month;
	uint8	day;
	uint8	hour;
	uint8	minute;
	uint8	second;
	uint8	csecs;		/* centiseconds */
	uint8	husecs;		/* hundreds of microseconds */
	uint8	usecs;		/* microseconds */
};

struct lb_addr {		/* ECMA 167 4/7.1 */
	uint32          lbn;
	uint16          partno;
};

struct short_ad {		/* ECMA 167 4/14.14.1 */
	uint32          extentlen;
	uint32          location;         /* logical block address */
};

struct long_ad {		/* ECMA 167 4/14.14.2 */
	uint32		extent_length;
	struct lb_addr	extent_location;
	byte		implementation_use[6];
};

struct ext_ad {			/* ECMA 167 4/14.14.3 */
	uint32		extent_length;
	uint32		recorded_length;
	uint32		information_length;
	struct lb_addr	extent_location;
	byte		implementation_use[2];
};

struct extent_ad {
	uint32	length;
	uint32	location;
};

struct entity_id {	/* OSTA 2.00 2.1.5 */
	uint8	flags;		/* must be 0 (zero) */
	char	id[23];		/* implementation id of last modifier */
				/* sequence of bytes (not a dstring) */
	char	idsfx[8];	/* suffix: Domain, UDF or Implementation */
};

struct domain_idsfx {	/* Domain Identifier Suffix */
	uint16	udf_rev;	/* UDF revision */
#define UDF_REVISION 0x0200
	uint8	domain_flags;
#define HARD_WRITE_PROTECT 0x01
#define SOFT_WRITE_PROTECT 0x02
	byte	reserved[5];	/* null */
};

struct udf_idsfx {	/* UDF Identifier Suffix */
	uint16	udf_rev;	/* UDF revision */
	uint8	os_class;	/* OSTA 2.00 6.3 */
#define OS_UNDEFINED		0
#define OS_DOS			1
#define OS_OS_2			2
#define	OS_MACINTOSH		3
#define	OS_UNIX			4
#define	OS_WIN_95		5
#define	OS_WIN_NT		6	/* values 7-255 reserved */
	uint8	od_id;		/* OSTA 2.00 6.3 */
#define ID_WIN_3X		0
#define ID_OS_2			0
#define ID_SYSTEM7		0
#define ID_UNIX_GENERIC		0
#define ID_IBM_AIX		1
#define ID_SUNOS_SOLARIS	2
#define ID_HP_UX		3
#define ID_SG_IRIX		4
#define ID_LINUX		5
#define ID_MKLINUX		6
#define ID_FREE_BSD		7
#define ID_WIN_95		8
#define ID_WIN_NT		9
	byte	reserved[4];	/* null */
};

struct implementation_idsfx {	/* Implementation Identifier Suffix */
	uint8	os_class;	/* OSTA 2.00 6.3 */
	uint8	os_id;		/* OSTA 2.00 6.3 */
	byte	implementation_use[6];
};

struct tag {		/* OSTA 2.00 2.2.1, 2.3.1 */
	uint16	tag_id;
	uint16	descriptor_version;
	uint8	tag_cs;
	byte	reserved;
	uint16	tag_sn;		/* set at re-init to primary_vd.tag_sn+1 */
	uint16	descriptor_crc; /* descriptor_size - descriptor_tag_length */
	uint16	dcrc_length;
	uint32	tag_location;
};

struct regid {			/* ECMA 167 1/7.4 */
	uint8		flags;
	byte		id[23];
	byte		idsfx[8];
};

/* tag id's for ISO/IEC 13346 structures */

#define TAGID_NONE             0   /* no tag */
#define TAGID_PVD              1   /* primary volume desc */
#define TAGID_ANCHOR           2   /* anchor desc */
#define TAGID_POINTER          3   /* pointer desc */
#define TAGID_IUD              4   /* implementation use desc */
#define TAGID_PD               5   /* volume partition desc */
#define TAGID_LVD              6   /* logical volume desc */
#define TAGID_USD              7   /* unallocated volume space desc */
#define TAGID_TERM_DESC        8   /* terminator desc */
#define TAGID_LVID             9   /* logical volume integrity desc */
#define TAGID_FSD              256  /* file set desc */
#define TAGID_FILE_ID          257  /* file identifier desc */
#define TAGID_ALLOC_EXTENT     258  /* Allocation extent desc */
#define TAGID_INDIRECT         259  /* Indirect entry */
#define TAGID_TERM_ENTRY       260  /* Terminal entry */
#define TAGID_FILE_ENTRY       261  /* File entry */
#define TAGID_EXT_ATTR         262  /* Extended attribute desc */
#define TAGID_UNALLOC_SP_ENTRY 263  /* Unallocated space entry (WORM)*/
#define TAGID_SPACE_BMAP       264  /* Space bitmap desc */
#define TAGID_PART_INTEGRITY   265  /* Partition integrity desc */

struct primary_vd {	/* OSTA 2.00 2.2.2 */
	struct tag	descriptor_tag;
	uint32		vd_seqno;
	uint32		pvd_no;
	dstring		volid[32];
	uint16		vseqno;
	uint16		max_vseqno;
	uint16		intchlvl;		/* 3: multi-vol set; 2: not */
	uint16		max_intchlvl;		/* 3 */
	uint32		charsetlist;		/* CSO only */
	uint32		max_charsetlist;	/* 1 (CSO) */
	dstring		vsetid[128];		/* 8-byte timestamp + 
						/* 8-byte implement-specific +
						/* ID */
	struct charspec	dcharset;		/* for volid & volsetid */
	struct charspec	echarset;		/* for volabst & volcopyrt */
	struct extent_ad volabstract;
	struct extent_ad volcopyright;
	struct entity_id application_id;
	struct timestamp recordtime;
	struct entity_id implementation_id;	/* "*DevID"+Implementation */
	byte		implementation_use[64];
	uint32		predecessorvd_seqloc;
	uint16		flags;
	byte		reserved[22];
};

struct anchor_vdp {	/* OSTA 2.00 2.2.3 */	/* at Logical Sector 256 */
	struct tag	descriptor_tag;
	struct extent_ad mainvd_seqext;		/* min length 16 log sectors */
	struct extent_ad reservevd_seqext;	/* min length 16 log sectors */
	byte		reserved[480];
};

struct logical_vd {	/* OSTA 2.00 2.2.4 */
	struct tag	descriptor_tag;
	uint32		vd_seqno;
	struct charspec	dcharset;		/* for lvolid */
	dstring		lvolid[128];
	uint32		lbs;			/* equal to lss for vol set */
	struct entity_id domain_id;	    /* "*OSTA UDF Compliant"+Domain */
	byte		lvol_contentuse[16];	/* FileSet descrip locator */
	uint32		maptablelen;
	uint32		num_partmaps;
	struct entity_id implementation_id;	/* "*DevID"+Implementation */
	byte		implementation_use[128];
	struct extent_ad integrity_seqext;
	byte		partmaps[XX];		/* Type 1 or Type 2 */
};

struct unallocsp_d {	/* OSTA 2.00 2.2.5 */
	struct tag	descriptor_tag;
	uint32		vd_seqno;
	uint32		num_allocation_descrip;	/* could be zero */
	struct extent_ad allocation_descrip[XX];
};

/*
 * OSTA 2.00 3.2.1.1 UniqueID
 * UniqueID is initialized to 16, and monotonically increases
 * with each assignment.  Whenever the lower 32-bits of this
 * value reach 0xFFFFFFFF, the upper 32-bits are incremented by 1,
 * but the lower 32-bits "wrap" up to 16.
 */
#define init_uniqueid() 16
#define inc_uniqueid(id) \
    (((id & 0xffffffff) ^ 0xffffffff) ? (id + 1) : (id + 1 + 16))

struct lv_headerdesc {	/* OSTA 2.00 3.2.1 */
	uint64		uniqueid;
	byte		reserved[24];
};

struct lvid_iu {	/* OSTA 2.00 2.2.6.4 */
	struct entity_id implementation_id;	/* last mod of vol or descr */
	uint32		num_files;
	uint32		num_directories;	/* root dir included */
	uint16		min_udfreadrev;		/* required in order to read */
	uint16		min_udfwriterev;	/* required in order to write*/
	uint16		max_udfwriterev;	/* max rev of vol modifiers */
	byte		implementation_use[XX];	/* unique to implementor */
};

struct lv_integrity_d {	/* OSTA 2.00 2.2.6 */	/* write with each vol mod */
	struct tag	descriptor_tag;
	struct timestamp recordtime;
	uint32		integrity_type;
	struct extent_ad next_integrity_ext;
	byte		lvol_contentuse[32];	/* lv_headerdesc */
	uint32		num_parts;
	uint32		implementation_use_len;
	uint32		freespace_table[XX];	/* free space or 0xFFFFFFFF */
	uint32		size_table[XX];		/* part size or 0xFFFFFFFF */
	byte		implemtation_use[XX];
};

struct lv_information {	/* OSTA 2.00 2.2.7.2 */
	struct charspec	lvi_charset;		/* for lv_id & lv_info */
	dstring		lv_identifier[128];
	dstring		lv_info1[36];		/* addit'l identifying info */
	dstring		lv_info2[36];
	dstring		lv_info3[36];
	struct entity_id implementation_id;	 /* "*DevID"+Implementation */
	byte		implementation_use[128]; /* implementation specific */
};

struct implementuse_vd {	/* OSTA 2.00 2.2.7 */
	struct tag	descriptor_tag;
	uint32		vd_seqno;
	struct entity_id implementation_id;	/* "*UDF LV Info"+UDF */
	byte		implemtation_use[460];
};

struct partition_d {		/* ECMA 167 3/10.5 */
	struct tag	descriptor_tag;
	uint32		vd_seqno;
	uint16		flags;
	uint16		number;
	struct regid	contents;
	byte		contentuse[128];
	uint32		access_type;
	uint32		partition_start;
	uint32		partition_length;
	struct regid	implementation_id;
	byte		implementation_use[128];
	byte		reserved[156];
};

/* 
 * to be defined:
 * 2.2.8  Virtual Partition Map
 * 2.2.9  Sparable Partition Map
 * 2.2.10 Virtual Allocation Table
 * 2.2.11 Sparing Table
 */

/* Allocation Descriptor Implementation Use of struct long_ad */
struct ad_impuse {		/* OSTA 2.00 2.3.10.1 */
	uint16		flags;
#define EXT_ERASED	0x01	/* extent is erased */
	byte		implementation_use[4];
};

/* File Descriptor Implementation Use of struct long_ad */
struct fd_impuse {		/* OSTA 2.00 2.3.4.3 */
	byte		reserved[2];		/* null */
	uint32		uniqueid;		/* ?? refer to 3.2.1 ?? */
						/* ?? this is a 64-bit value */
};

struct fileset_d {		/* OSTA 2.00 2.3.2 */
	struct tag	descriptor_tag;
	struct timestamp recordtime;
	uint16		intchlvl;		/* 3 */
	uint16		max_intchlvl;		/* 3 */
	uint32		charsetlist;		/* CSO only */
	uint32		max_charsetlist;	/* supported char sets (1) */
	uint32		fileset_no;
	uint32		fileset_dno;
	struct charspec	lvid_charset;		/* for lv_id */
	dstring		lv_identifier[128];
	struct charspec	fs_charset;		/* for dstrings in struct */
	dstring		fileset_id[32];
	dstring		copyright_fid[32];
	dstring		abstract_fid[32];
	struct long_ad	rootdir_icb;
	struct entity_id domain_id;	    /* "*OSTA UDF Compliant"+Domain */
	struct long_ad	next_extent;
	struct long_ad	streamdir_icb;
	byte		reserved[32];
};

struct parthead_d {		/* OSTA 2.00 2.3.3 */
	struct short_ad	unallocsp_tab;
	struct short_ad	unallocsp_bmap;
	struct short_ad	partinteg_tab;		/* not used, null */
	struct short_ad	freedsp_tab;
	struct short_ad	freedsp_bmap;
	byte		reserved[88];
};

struct fileid_d {		/* OSTA 2.00 2.3.4, 3.3.1 */
	struct tag	descriptor_tag;
	uint16		file_vernum;		/* one version only allowed */
	uint8		file_characteristics;
	uint8		fileid_len;
	struct long_ad	icb;
	uint16		impuse_len;
	byte		implementation_use[XX];	/* last modifier of struct */
	char		file_identifier[XX];
	byte		padding[XX];
};
/* file_characteristics */
#define FC_HIDDEN	0x01		/* hidden file (normal file in UNIX) */
#define FC_DIRECTORY	0x02		/* directory */
#define FC_DELETED	0x04		/* deleted file */
#define FC_ICBISPARENT	0x08		/* if set, the ICB identifies parent */

struct icbtag {		/* OSTA 2.00 2.3.5, 3.3.2 */
	uint32		priordirects;
	uint16		strategytype;		/* type 4 or 4096 (WORM) */
	uint16		strategyparm;
	uint16		num_entries;
	uint8		reserved;
	uint8		filetype;
	struct lb_addr	parent_icbloc;
	uint16		flags;
};

#define FT_UNSPECIFIED          0	/* valid for OSTA 2.00 ?? */
#define FT_UNALLOC_SP_ENTRY     1
#define FT_PARTITION_INTEGRITY  2
#define FT_INDIRECT_ENTRY       3
#define FT_DIRECTORY            4
#define FT_RAW                  5	/* regular file */
#define FT_BDEV                 6
#define FT_CDEV                 7
#define FT_EXT_ATTR             8
#define FT_FIFO                 9
#define FT_SOCKET              10
#define FT_TERMINAL_ENTRY      11
#define FT_SYMLINK             12
/* Bits 0,1,2 - Allocation Descriptor Type */
#define ADTYPEMASK	0x0007		/* allocation descriptor type */
#define ADGENERIC	0x2000		/* internal use ONLY */
#define ADSHORT		0x00		/* short ADs */
#define ADLONG		0x01		/* long ADs */
#define ADEXTENDED	0x02		/* extended ADs */
#define ADNONE		0x03		/* data replaces ADs */
#define valid_adtype(x) ((x)==ADSHORT||(x)==ADLONG||(x)==ADEXTENDED)
/* Bits 3-9 : Miscellaneous */
#define SORTED_DIRECTORY	0x0008
#define NON_RELOCATABLE		0x0010
#define CONTIGUOUS		0x0200
#define TANSFORMED		0x0800
#define MULTIVERS		0x1000

struct file_entry {		/* OSTA 2.00 2.3.6, 3.3.3 */
	struct tag	descriptor_tag;
	struct icbtag	icb_tag;
	uint32		uid;		/* (2**32-1) is invalid */
	uint32		gid;		/* (2**32-1) is invalid */
	uint32		permissions;
	uint16		filelinkcnt;
	uint8		record_format;
	uint8		record_dattributes;
	uint32		record_len;
	uint64		info_len;
	uint64		lb_recorded;
	struct timestamp accesstime;
	struct timestamp modtime;
	struct timestamp attributetime;
	uint32		checkpoint;
	struct long_ad	extattrib_icb;
	struct regid	implementation_id;
	uint64		uniqueid;
	uint32		extendedattribs_len;
	uint32		allocdescriptors_len;
	byte		extendedattribs[1];
	byte		allocdescriptors[1];
};

/*
 * Definitions of permissions: (3.3.3.3)
 * Bit     For a File                  For a Directory
 * ------- --------------------------  -------------------------
 * EXECUTE May execute file            May search directory
 * WRITE   May change file contents    May create and delete files
 * READ    May examine file contents   May list files in directory
 * CHATTR  May change file attributes  May change dir attributes
 * DELETE  May delete file             May delete directory
 */
#define OTHER_EXECUTE		0x00000001
#define OTHER_WRITE		0x00000002
#define OTHER_READ		0x00000004
#define OTHER_CHATTR		0x00000008
#define OTHER_DELETE		0x00000010
#define GROUP_EXECUTE		0x00000020
#define GROUP_WRITE		0x00000040
#define GROUP_READ		0x00000080
#define GROUP_CHATTR		0x00000100
#define GROUP_DELETE		0x00000200
#define OWNER_EXECUTE		0x00000400
#define OWNER_WRITE		0x00000800
#define OWNER_READ		0x00001000
#define OWNER_CHATTR		0x00002000
#define OWNER_DELETE		0x00004000


struct unallocsp_entry {	/* OSTA 2.00 2.3.7 */
	struct tag	descriptor_tag;
	struct icbtag	icb_tag;
	uint32		allocdescriptors_len;
	byte		allocdescriptors[XX];
};

struct space_bmap {		/* OSTA 2.00 2.3.8 */
	struct tag	descriptor_tag;
	uint32		num_bits;
	uint32		num_bytes;
	byte		bitmap[XX];
};

struct partinteg_entry {	/* OSTA 2.00 2.3.9 */
	struct tag	desriptor_tag;
	struct icbtag	icb_tag;
	struct timestamp recordtime;
	uint8		integrity_type;
	byte		reserved[175];
	struct entity_id implementation_id;
	byte		implementation_use[256];
};

struct allocationextent_d {	/* OSTA 2.00 2.3.11 */
	struct tag	descriptor_tag;
	uint32		prev_aeloc;
	uint32		allocd_len;
};

struct pathcomponent {		/* OSTA 2.00 2.3.12.1 */
	uint8		component_type;
	uint8		component_id_len;
	uint16		component_fileversion;
	char		component_id[XX];
};

/* Extended Attribute Header Descriptor */
struct eaheader_d {		/* OSTA 2.00 3.3.4.1 */
	struct tag	descriptor_tag;
	uint32		implementationattr_loc;	/* 0xffffffff => DNE */
	uint32		applicationattr_loc;	/* 0xffffffff => DNE */
};

/* Alternate Permissions Extended Attribute */
struct alternateperm_ea {	/* OSTA 2.00 3.3.4.2 */
	uint32		attributetype;
	uint8		attributesubtype;
	byte		reserved[3];
	uint32		attributelen;
	uint16		ownerid;
	uint16		groupid;
	uint16		permission;
};

/* File Times Extended Attribute */
struct filetimes_ea {		/* OSTA 2.00 3.3.4.3 */
	uint32		attributetype;
	uint8		attributesubtype;
	byte		reserved[3];
	uint32		attributelen;
	uint32		datalen;
	uint32		filetimeexistence;
	byte		filetimes;
};

/* Device Specification Extended Attribute */
struct devicesp_ea {		/* OSTA 2.00 3.3.4.4 */
	uint32		attributetype;
	uint8		attributesubtype;
	byte		reserved[3];
	uint32		attributelen;
	uint32		implementation_use_len;
	uint32		major_devid;
	uint32		minor_devid;
	byte		implementation_use[XX];	/* len spec'ed above */
};


/* Implementation Use Extended Attribute */
struct implementation_use_ea {	/* OSTA 2.00 3.3.4.5 */
	uint32		attributetype;
	uint8		attributesubtype;
	byte		reserved[3];
	uint32		attributelen;
	uint32		implementation_use_len;
	struct entity_id implementation_id;
	byte		implementation_use[XX];	/* len spec'ed above */
};

/* 
 * FreeEASpace Implementation Use Extended Attribute
 * implementation_id.id = "*UDF FreeEASpace"
 */
struct free_easpace {		/* OSTA 2.00 3.3.4.5.1.1 */
	uint16		header_cs;		/* C-source in appendix */
	byte		free_easpace;		/* iu_len-1 (?-2) */
};

/*
 * DVD Copyright Management Information Implementation Use Extended Attribute
 * implementation_id.id = "*UDF DVD CGMS Info"
 */
struct dvd_cgms_info {		/* OSTA 2.00 3.3.4.5.1.2 */
	uint16		header_cs;		/* C-source in appendix */
	byte		cgms_info;
	uint8		datastruct_type;
	byte		protect_sysinfo[4];
};

/* Application Use Extended Attribute */
struct applicationuse_ea {	/* OSTA 2.00 3.3.4.6 */
	uint32		attributetype;
	uint8		attributesubtype;
	byte		reserved[3];
	uint32		attributelen;
	uint32		attribute_use_len;
	struct entity_id application_id;
	byte		application_use[XX];	/* len spec'ed above */
};

/* 
 * FreeAppEASpace Application Use Extended Attributes
 * application_id.id = "*UDF FreeAppEASpace"
 */
struct freeapp_easpace {	/* OSTA 2.00 3.3.4.6.1 */
	uint16		header_cs;		/* C-source in appendix */
	byte		free_easpace;		/* iu_len-1 (?-2) */
};

struct implEntityId {
    uchar8 uFlags        ;
    uchar8 aID[23]       ;
    uchar8 uOSClass      ;
    uchar8 uOSIdentifier ;
    uchar8 uDescVersion  ;
    uchar8 uLibrVersion  ;
    uint16 uImplRegNo    ;
    uchar8 uImplVersion  ;
    uchar8 uImplRevision ;
};

/*
 * Contents of mount point buf.
 */

struct dvdfs
{
	struct	fs *fs_link;		/* linked list of file systems */
	struct	fs *fs_rlink;		/* used for incore super blocks */
	char	fs_ronly;		/* Read only ? */
	int	fs_ibsize;			/* File system block size */
	ino_t	rootino;
	uint32	root_fileset;		/* lbn of start of fileset */
	struct	anchor_vdp avd;
	struct	primary_vd pvd;
	struct	implementuse_vd iuvd;
	struct	partition_d partd;
	struct	logical_vd lvd;
	struct	unallocsp_d uspd;
	struct	file_entry dvdfs_root_dir;
#ifdef _KERNEL
	udecl_simple_lock_data(,fsu_lock) /* see notes below */
#endif /* _KERNEL */
};

#define	fs_lock		fsu_lock

udecl_simple_lock_info(extern, dvdfs_lockinfo)

#define FS_LOCK(fs)		usimple_lock(&(fs)->fs_lock)
#define	FS_UNLOCK(fs)		usimple_unlock(&(fs)->fs_lock)
#define	FS_LOCK_INIT(fs)	usimple_lock_setup(&(fs)->fs_lock,cdfs_lockinfo)
#define	FS_LOCK_HOLDER(fs)	SLOCK_HOLDER(&(fs)->fs_lock)

#define	TAG(X)		((struct tag *) ((X)->b_un.b_addr))
#define	TAGID(X)	TAG(X)->tag_id


extern int dvdfs_reclaim(register struct vnode * );


#pragma environment_restore
#endif	/* _DVDFS_FS_H_ */
