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

#pragma	ident	"@(#)$RCSfile: vol.h,v $ $Revision: 1.1.11.6 $ (DEC) $Date: 1995/12/20 16:08:58 $"

/* @(#)src/common/uts/io/vxvm/vol.h	6.3 13 May 1993 20:36:14 - Copyright (c) 1993 VERITAS Software Corp. */
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

#ifndef _SYS_VOL_H
#define _SYS_VOL_H

/*
 * sys/vol.h - volume manager header file
 *
 * A volume consists of one or more replications of data stored on
 * plexes of the same size.  A plex consists of one or more subdisks 
 * concatenated or striped into one plex address space.
 *
 * The name structure class name convention is as follows:
 *
 *	X_tmp  - common elements that go away on reboot
 *	X_perm - common elements that persist across reboots
 *
 * NOTE: The only elements changing via the change bit mask method are
 *	 the elements are NOT marked with a  P  comment.
 */

/*
 * Turn on root/swap support.
 */
#define ROOTABILITY 	1
/*
 * global constants
 */

#ifdef	__alpha
#define	MIN_VOL		32		/* minimum number of volumes allowed */
#define	DEF_MAX_VOL	1024		/* soft maximum number of volumes allowed */
#define	MAX_VOL		4096		/* maximum number of volumes allowed */
#else /* !__alpha */
#define	MAX_VOL		256		/* maximum number of volumes allowed */
#define	MAX_PLEX	256		/* maximum number of plexes allowed */
#endif /* __alpha */
#define NAME_LEN	14		/* bytes in a name */
#define UTIL_LEN	14		/* chars in a utility defined field */
#define UTIL_NUM	3		/* number of utility defined fields */
#define COMMENT_LEN	40		/* chars in a comment field */
#define STATE_LEN	14		/* chars per utility state field */
#define FSTYPE_LEN	8		/* max length of fstype string */
#define PLEX_NUM	8		/* max number of plexes in a volume */
#ifdef	__alpha
#define SUBDISK_NUM	4096		/* max number of subdisks per plex */
#else /* !__alpha */
#define SUBDISK_NUM	256		/* max number of subdisks per plex */
#endif /* __alpha */
#define DK_PATH_LEN	32		/* chars in a disk /dev pathname */
#define SD_PATH_LEN	DK_PATH_LEN	/* chars in a subdisk /dev pathname */
#define V_STOPTS_LEN	32		/* chars of volume start options */
#define VOL_UUID_LEN	64		/* chars in a unique identifier */
#define DA_TYPE_LEN	14		/* disk device type len */
#define DA_INFO_LEN	128		/* disk device type-specific info len */
#define NAME_SZ		(NAME_LEN + 1)	/* bytes in a name field */
#define UTIL_SZ		(UTIL_LEN + 1)	/* bytes per utility defined field */
#define COMMENT_SZ	(COMMENT_LEN+1)	/* bytes in a comment field */
#define	FSTYPE_SZ	(FSTYPE_LEN+1)	/* size of fstype field */
#define STATE_SZ	(STATE_LEN + 1)	/* bytes per utility state field */
#define SD_PATH_SZ	(SD_PATH_LEN+1)	/* bytes per subdisk /dev pathname */
#define DK_PATH_SZ	(DK_PATH_LEN+1)	/* bytes per disk /dev pathname */
#define V_STOPTS_SZ	(V_STOPTS_LEN+1) /* bytes per volume start args */
#define VOL_UUID_SZ	(VOL_UUID_LEN+1) /* bytes in unique identifier */
#define DA_TYPE_SZ	(DA_TYPE_LEN+1)	/* bytes in disk device type */
#define DA_INFO_SZ	(DA_INFO_LEN+1)	/* bytes in disk device info */

#ifdef __alpha
typedef int voff_t;			/* device offsets and lengths */
typedef unsigned int uvoff_t;		/* unsigned version */
#else /* !__alpha */
typedef long voff_t;			/* device offsets and lengths */
typedef unsigned long uvoff_t;		/* unsigned version */
#endif /* __alpha */

/* the following two defines assume that voff_t is signed, twos-complement,
 * and that chars are eight bits */
#define VOFF_T_MAX	\
	((voff_t)(((voff_t)1 << (sizeof(voff_t) * 8 - 2)) + \
		  (((voff_t)1 << (sizeof(voff_t) * 8 - 2)) - (voff_t)1)))
#define VOFF_T_MIN	((voff_t)(-VOFF_T_MAX - (voff_t)1))

/*
 * VOFF_T_QUAD - is the voff_t type more than 32 bits
 *	Set VOFF_T_QUAD to 1 if voff_t is a 64 bit type
 */

#if !defined(VOFF_T_QUAD)
#define VOFF_T_QUAD	0
#endif

/* protocol version number of vold/kernel interface */
#define VOL_KERNEL_VERSION	4

#ifndef VOL_BIG_ENDIAN
#if defined(i386) || defined(vax)
#define VOL_BIG_ENDIAN	0
#else
#define VOL_BIG_ENDIAN	1
#endif
#endif

struct volseqno {
#if VOL_BIG_ENDIAN
	unsigned long seqno_hi;
	unsigned long seqno_lo;
#else
	unsigned long seqno_lo;
	unsigned long seqno_hi;
#endif
};
typedef struct volseqno volseqno_t;
typedef volseqno_t volrid_t;

#define VOLSEQNO_EQ(seq1, seq2)	\
	((seq1).seqno_lo == (seq2).seqno_lo &&		\
	 (seq1).seqno_hi == (seq2).seqno_hi)
#define VOLSEQNO_LT(seq1, seq2)	\
	((seq1).seqno_hi < (seq2).seqno_hi ||		\
	 ((seq1).seqno_hi == (seq2).seqno_hi && 	\
	  (seq1).seqno_lo < (seq2).seqno_lo))
#define VOLSEQNO_GT(seq1, seq2)	\
	((seq1).seqno_hi > (seq2).seqno_hi ||		\
	 ((seq1).seqno_hi == (seq2).seqno_hi && 	\
	  (seq1).seqno_lo > (seq2).seqno_lo))
#define VOLSEQNO_GE(seq1, seq2)	(! VOLSEQNO_LT((seq1), (seq2)))
#define VOLSEQNO_LE(seq1, seq2)	(! VOLSEQNO_GT((seq1), (seq2)))
#define VOLSEQNO_INC(seq)	\
	((seq).seqno_lo == 0xffffffff?			\
	 ((seq).seqno_lo = 0, (seq).seqno_hi++):	\
	 (seq).seqno_lo++)
#define VOLSEQNO_EQ_ZERO(seq)	((seq).seqno_hi == 0 && (seq).seqno_lo == 0)
#define VOLSEQNO_RESET(seq)	((seq).seqno_hi = 0, (seq).seqno_lo = 0)
#define VOLSEQNO_SET(seq, hi, lo)	\
	((seq).seqno_hi = (hi),		\
	 (seq).seqno_lo = (lo))
#define VOLSEQNO_HI(seq)	((seq).seqno_hi)
#define VOLSEQNO_LO(seq)	((seq).seqno_lo)

#define VOLRID_EQ(rid1, rid2)	(VOLSEQNO_EQ((rid1), (rid2)))
#define VOLRID_EQ_ZERO(rid)	(VOLSEQNO_EQ_ZERO((rid)))
#define VOLRID_RESET(rid)	(VOLSEQNO_RESET((rid)))
#define VOLRID_HASH(rid, mod)	((rid).seqno_lo % (ulong_t)(mod))
#define VOLRID_SET(rid, hi, lo)	(VOLSEQNO_SET((rid), (hi), (lo)))
#define VOLRID_HI(rid)		(VOLSEQNO_HI(rid))
#define VOLRID_LO(rid)		(VOLSEQNO_LO(rid))

/*
 * maximum alignment requirements for this machine
 *
 * VOL_ALIGN_SIZE	- size of largest C data type used in volume manager
 * VOL_ALIGN(p)		- return the pointer rounded up to an alignment boundary
 */

#define VOL_ALIGN_SIZE	(sizeof(union _vol_align))
union _vol_align {
	voff_t v;
	long l;
	ulong_t ul;
	int i;
#ifdef __alpha
	/*
	 * The reference to 'u' is mistaken for a u-area reference. If
	 * the 'u' field of this union is referenced, the reference needs
	 * to be changed.
	 */
	unsigned vol_align_u;
#else /* !__alpha */
	unsigned u;
#endif /* __alpha */
};
#define VOL_ALIGN(p)	\
	((VOID *)(((ulong_t)(p) + VOL_ALIGN_SIZE - 1) & ~(VOL_ALIGN_SIZE - 1)))

/* size in bytes of kernel information buffer available for use by vold */
#define VOLDINFO_SIZE		2048

/* encoding for high order bytes of volume manager ioctls */


#ifdef __alpha
/*
 * On alpha, _IO translate to no param list copy in and out.  This will cause the
 * callers arg pointer to be passed to the lower ioctl call.  vol* ioctl expects
 * this behavior.
 */
#include <sys/ioctl.h>
#define VOLIOC _IO(('V'), 0)
#else /* !__alpha */
#define VOLIOC  (('V' << 24) | ('O' << 16) | ('L' << 8))
#endif /* __alpha */

/* ioctl commands for any volume manager device */

#define	GET_DAEMON		(VOLIOC | 1)
#define	GET_VOLINFO		(VOLIOC | 2)

/* ioctls for /dev/rvol and /dev/plex devices */

#define	ATOMIC_COPY		(VOLIOC | 50)
#define	PLEX_READ		(VOLIOC | 51)
#define	PLEX_WRITE		(VOLIOC | 52)
#define	PLEX_DEV_READ		(VOLIOC | 53)
#define	PLEX_DEV_WRITE		(VOLIOC | 54)
#define	VERIFY_READ		(VOLIOC | 55)
#define	VERIFY_WRITE		(VOLIOC | 56)
#define VOL_LOG_WRITE		(VOLIOC | 58)
#define	PLEX_DETACH		(VOLIOC | 59)
#define VOL_READ		(VOLIOC | 60)
#define VOL_WRITE		(VOLIOC | 61)

/* ioctls for /dev/volevent device */

#define	VOL_TRACE_SET		(VOLIOC | 70)
#define	VOL_TRACE_GET		(VOLIOC | 71)
#define	VOL_EVENT_NUM		(VOLIOC | 72)
#define	VOL_GET_EVENT		(VOLIOC | 73)

/* ioctl for /dev/volinfo device */

#define VOL_GET_STATS		(VOLIOC | 75)
#define VOL_CLR_STATS		(VOLIOC | 76)
#define VOL_INDIRECT_IOCTL	(VOLIOC | 77)
#define VOL_GET_SDI_INFO	(VOLIOC | 78)

#if defined(TED_ACTIVE) || defined(__alpha)
#define VOL_SET_VOLINFO		(VOLIOC | 79)
#endif /* TED_ACTIVE || __alpha */

/* ioctls for /dev/voliod device */

#define	VOL_IO_DAEMON		(VOLIOC | 80)
#define VOL_IO_DAEMON_KILL	(VOLIOC | 81)
#define	VOL_IO_DAEMON_CNT	(VOLIOC | 82)
#define VOL_LOG_IO_DAEMON	(VOLIOC | 83)
#define	VOL_LOGIOD_WAIT		(VOLIOC | 84)
#define	VOL_LOGIOD_KILL		(VOLIOC | 85)
#define	VOL_LOGIOD_CHECK	(VOLIOC | 86)

/* ioctls for use by file systems */
#define VOL_FREEZE		(VOLIOC | 100)	/* stop file system activity */
#define VOL_THAW		(VOLIOC | 101)	/* restart file system */
/*
 * DEC ioctls.
 */
#define VOL_RDONLY_ROOT		(VOLIOC | 251)	/* Set root to read only */
						/* when booting from a plex */
#define VOL_ROOT_WRITTEN	(VOLIOC | 252)
#define VOL_UNSET_ROOT		(VOLIOC | 253)
#define VOL_SET_SWAP_PREF	(VOLIOC | 254)
#define VOL_UNSET_SWAP_PREF	(VOLIOC | 255)

/*
 * kernel information structure
 */

struct volinfo {
	long	version;		/* 0x00 kernel version number */
	long	voldinfo_sz;		/* 0x04 size of voldinfo area */
	major_t	volbmajor;		/* 0x08 volume blk dev major number */
	major_t	volcmajor;		/* 0x0c volume char dev major number */
	major_t	plexmajor;		/* 0x10 plex device major number */
	long	maxvol;			/* 0x14 max # of volumes supported */
	long	maxplex;		/* 0x18 max # of associated plexes */
	long	plexnum;		/* 0x1c max plexes per volume */
	long	sdnum;			/* 0x20 max subdisks per plex */
	long	max_ioctl;		/* 0x24 max size of ioctl data */
	long	max_specio;		/* 0x28 max size of ioctl I/O op */
	long	max_io;			/* 0x2c max size of I/O operation */
	long	max_ilocksleep;		/* 0x30 max sleeps on ilock */ 
	long	dflt_iodelay;		/* 0x34 default I/O delay for utils */
	long	max_freebuf;		/* 0x38 max number of volbufs to keep */
	long	max_freevcb;		/* 0x3c max number of volcbs to keep */
	long	max_parallelio;		/* 0x40 max # voldios allowed */
	long	volinfo_spare[15];	/* 0x44 unused - reserved for later */
};					/* 0x80 */

/*
 * configuration id numbers
 */
struct vol_id {
	long	config_id;		/* kept for source compatibility */
	time_t	config_epoch;		/* kept for source compatibility */
	volseqno_t config_tid;		/* last committed transaction ID */
};

/* values for state element of volconfig structure */
#define VOL_READY	    1	/* configuration ready to accept transaction */
#define VOL_COMMIT_START    2	/* commit has been started */
#define VOL_COMMIT_PHASE1   3	/* commit has reached phase 1 commit point */

/* values for resolution element of volconfig structure */
#define VOL_NONE	0	/* no transaction has been attempted */
#define START_ABORTED	1	/* tid was aborted out of COMMIT_START state */
#define START_TIMEOUT	2	/* tid was aborted due to datalock timeout in
				   the COMMIT_START state */
#define PHASE1_ABORTED	3	/* tid was aborted out of COMMIT_PHASE1 state */
#define PHASE1_TIMEOUT	4	/* tid was aborted due to datalock timeout in
				   the COMMIT_PHASE1 state, any volumes that
				   were data locked have been disabled and the
				   V_DLOCKTIMEOUT flag was set on them */
#define COMMITTED	5	/* tid was successfully committed */
#define INPROGRESS	6	/* tid is currently in progress */

/* values for flags element of volconfig structure */
#define	KERNEL_LOADED	0x01	/* set on a K_CONFIG_LOADED ioctl call */
#define	PENDING_CLEARED	0x02	/* set when the pending configuration records
				   have been cleared to match the active
				   records */

/*
 * configuration state
 */

struct volconfig {
	long	state;		/* 0x00 state of kernel transaction engine */
	long	tid;		/* 0x04 current or previous transaction id */
	long	resolution;	/* 0x08 status of transaction */
	long	flags;		/* 0x0c flags for configuration */
	long	verrno;		/* 0x10 status of last volconfig ioctl */
	struct vol_id  conf_id;	/* 0x14 config id for configuration */
	struct vol_id  cur_id;	/* 0x24 config id for transaction */
};				/* 0x34 */

/*
 * volume manager database summary
 */

struct vol_summary {
	size_t	vs_v_cnt;		/* number of volumes */
	size_t	vs_pl_cnt;		/* number of plexes */
	size_t	vs_sd_cnt;		/* number of subdisks */
	size_t	vs_pl_n_cnt;		/* number of non-associated plexes */
	size_t	vs_sd_n_cnt;		/* number of non-associated subdisks */
	size_t	vs_dm_cnt;		/* number of disk media records */
	size_t	vs_da_cnt;		/* number of disk access records */
	size_t	vs_host_cnt;		/* number of hosts */
	size_t	vs_info_cnt;		/* number of info records */
};

/*
 * structure used for volume device I/O ioctls
 */

struct plx_ent {
	char	pe_name[NAME_SZ];
	int	pe_errno;
};

struct vol_io {
	voff_t		vi_offset;	/* 0x00 offset on plex */
	size_t		vi_len;		/* 0x04 amount of data to read/write */
	caddr_t		vi_buf;		/* 0x08 ptr to buffer */
	size_t		vi_nsrcplex;	/* 0x0c number of source plexes */
	size_t		vi_ndestplex;	/* 0x10 number of destination plexes */
	struct plx_ent	*vi_plexptr;	/* 0x14 ptr to array of plex entries */
	ulong_t		vi_flag;	/* 0x18 flags associated with op */
};					/* 0x1c */

/* flags stored in vol_io.vi_flag */
#define	VI_LOGIO	0x00000001	/* perform operation to log area */

struct vol_rdwr {
	ulong_t		vrw_flags;	/* flags */
	voff_t		vrw_off;	/* offset in volume (sectors) */
	size_t		vrw_size;	/* number of sectors to Xfer */
	caddr_t		vrw_addr;	/* user address for Xfer */
};

#define	VRW_ASNC	0x1		/* Do writes asynchronously */
#define VRW_RWBACK	0x2		/* read-writeback read loop I/O */

/*
 * Structure used to request an ioctl to another device.  Utilities
 * can use this to ioctl devices that don't have device nodes, or where
 * the device nodes can't be trusted to be correct.
 */
struct vol_indirect_ioctl {
	dev_t			vioc_dev;	/* 0x00 raw device number */
	int			vioc_cmd; 	/* 0x04 ioctl to issue */
	caddr_t			vioc_arg; 	/* 0x08 ioctl argument */
};						/* 0x0c */

/*
 * structure used by vold to get information about the sdi device
 * driver.  This structure may be specific to the i386 releases of
 * SVR4.0 and SVR4.2.
 */
#define VOL_SD01_MAX		16
struct vol_sdi_info {
	size_t	sdi_ndiskpermajor;		/* # of disks per major */
	size_t	sdi_npart;			/* # of partitions per disk */
	size_t	sdi_nmajor;			/* # of major devices */
	major_t	*sdi_cmajors;			/* char majors for sd01 */
	major_t	*sdi_bmajors;			/* block majors for sd01 */
};

/*
 * volume - one or more replicated plex data sets
 */

/* volume enums */
enum vol_r_pol {			/* type of volume read policy */
	MIN_VOL_R_POL,			/* sentinel value, must be first */
	V_ROUND,			/* round robin */
	V_PREFER,			/* use a preferred plex */
	V_R_POL_SELECT,			/* select based on plex layouts */
	MAX_VOL_R_POL			/* sentinel value, must be last */
};
enum vol_kstate {			/* volume kernel state */
	MIN_VOL_KSTATE,			/* sentinel value, must be first */
	V_DISABLED,			/* volume is offline */
	V_DETACHED,			/* volume is detached */
	V_ENABLED,			/* volume is enabled */
	MAX_VOL_KSTATE			/* sentinel value, must be last */
};
enum vol_except {			/* what to do in case of an error */
	MIN_VOL_EXCEPT,			/* sentinel value, must be first */
	V_NO_OP,			/* no additional action required */
	V_FAIL_OP,			/* fail the operation */
	V_DET_PL,			/* just detach plex */
	V_FAIL_DET_PL,			/* fail operation and detach plex */
	V_DET_VOL,			/* just detach volume */
	V_FAIL_DET_VOL,			/* fail operation and detach volume */
	V_GEN_DET,			/* detach plex, or volume if 
					   no complete plexes would remain */
	V_GEN_DET_SPARSE,		/* detach plex, or all incomplete
					   plexes if no complete plexes would
					   remain*/
	V_GEN_FAIL,			/* detach plex and volume and fail */
	V_GEN_DET2,			/* detach plex, or volume if no two
					   complete plexes would remain */
	MAX_VOL_EXCEPT			/* sentinel value, must be last */
};

/* volume structure */
struct v_tmp {			/* volume items that go away on reboot */
	char	v_tutil[UTIL_NUM][UTIL_SZ];	/* 'in kernel' utility field */
	ulong_t	v_tflag;			/* temp flags for volume */
  /*P*/ long	v_rec_lock;			/* 1 => record locked */
  /*P*/ long	v_data_lock;			/* 1 => volume data locked */
  /*P*/ long	v_lasterr;			/* last volume error or 0 */
	enum vol_kstate v_kstate;		/* relation to file space */
	enum vol_except v_r_all;		/* if all plex reads fail */
	enum vol_except v_r_some;		/* if some plex reads fail */
	enum vol_except v_w_all;		/* if all plex writes fail */
	enum vol_except v_w_some;		/* if some plex writes fail */
	enum vol_r_pol v_current_read_pol;	/* current read policy */
  /*P*/	dev_t	v_bdev;				/* block dev for volume */
  /*P*/	dev_t	v_cdev;				/* char dev for volume */
	size_t	v_iosize;			/* minimum size for raw I/Os */
	voff_t	v_rwback_offset;		/* read/write-back offset */
	long	v_log_serial_lo;		/* log serial number/low part */
	long	v_log_serial_hi;		/* log serial number/hi part */
	char	v_tspare[20];			/* room for expansion */
};
struct v_perm {			/* volume items that exist after reboot */
  /*P*/ char	v_name[NAME_SZ];		/* volume name */
	char	v_putil[UTIL_NUM][UTIL_SZ];	/* 'on disk' utility field */
	char	v_comment[COMMENT_SZ];		/* comment field */
	char	v_state[STATE_SZ];		/* utility state of volume */
  /*P*/ char	v_use_type[NAME_SZ];		/* volume usage type name */
	char	v_fstype[FSTYPE_SZ];		/* guess of volumes fstype */
	char	v_pref_name[NAME_SZ];		/* plex name if V_PREPER */
	char	v_start_opts[V_STOPTS_SZ];	/* volume start options */
  /*P*/	volrid_t v_rid;				/* unique identifier */
  /*P*/ volrid_t v_pref_plex_rid;		/* preferred plex record ID */
  /*P*/	volseqno_t v_update_tid;		/* trans id of last update */
  /*P*/	volseqno_t v_detach_tid;		/* trans id of kernel detach */
	enum vol_r_pol v_read_pol;		/* method of plex selection */
	ulong_t	v_pflag;			/* perm flags for volume */
	minor_t	v_minor;			/* minor number in disk group */
	uid_t	v_uid;				/* owner of /dev/vol/name */
	gid_t	v_gid;				/* group of /dev/vol/name */
	mode_t	v_mode;				/* mode of /dev/vol/name */
  /*P*/ long	v_pl_num;			/* associated plex count */
	voff_t	v_len;				/* byte length of volume */
	voff_t	v_log_len;			/* length of log area */
	char	v_pspare[8];			/* room for expansion */
};

#define v_config_id v_update_tid.seqno_lo
#define v_config_epoch v_update_tid.seqno_hi

struct volrec {
	struct v_tmp	v_tmp;		/* items that go away on reboot */
	struct v_perm	v_perm;		/* items that remain after reboot */
};

/*
 * volume temp flag bits, high order 12 bits are reserved for kernel
 * to pass back information about the kernel state of a record, see
 * sys/volkern.h for information about those bits
 */

#define V_TFLAG_MASK	  0x000007	/* mask for volume tflag */
#define V_TFLAG_RMASK	  0x000700	/* read-only volume tflag bits */
#define V_TFLAG_READ	  0x000001	/* volume is shared readable */
#define V_TFLAG_WRITE	  0x000002	/* volume is shared writable */
#define V_TFLAG_RWBACK    0x000004	/* write back after reads */
#define V_TFLAG_KRWBACK   0x000100	/* kernel still in RWBACK state */
#define V_TFLAG_INVALID	  0x000200	/* volume is unusable */
#define V_TFLAG_LOGGING   0x000400	/* volume requires logging */

/*
 * The kernel uses the high order 12 bits of the tflag element to pass
 * information about the kernel state of a record to users.  This group
 * of flags applies to the subdisk, plex, and volume tflag elements.
 */

#define VK_OPEN		0x01000000	/* volume, plex, or subdisk is open */
#define VOL_TFLAG_KMASK	0xfff00000	/* mask of bits reserved for kernel */

/* NOTE:  See PL_TFLAG_VOLATILE for plex-specific kernel flag bit */
/* NOTE:  See SD_TFLAG_IS_LOG for subdisk-specific kernel flag bit */

/* volume perm flag bits */
#define V_PFLAG_MASK	  0x0003ff	/* mask for volume pflag */
#define V_PFLAG_RMASK	  0x000000	/* read-only volume pflag bits */
#define V_PFLAG_WRITEBACK 0x000001	/* writeback error enabled */
#define V_PFLAG_WRITECOPY 0x000002	/* log block numbers being changed */
#define V_PFLAG_ACTIVE	  0x000004	/* kernel logged activity on volume */
#define V_PFLAG_FORCEMINOR 0x00008	/* force use of specified minor
					 * used for root and swap vols */
#define V_PFLAG_LOGTYPE	  0x0000f0	/* mask for log type */
#define V_PFLAG_LOGUNDEF  0x000000	/* no logging on volume, can default */
#define V_PFLAG_LOGNONE	  0x000010	/* no logging on volume */
#define V_PFLAG_LOGBLKNO  0x000020	/* log block numbers being changed */
#define V_PFLAG_BADLOG	  0x000100	/* volume activity log failed */
#define V_PFLAG_SPECIFY_WRITECOPY 0x200	/* set if writecopy was specified
					 * explicitly, off to use default */

/* volume structure change bits */

#define EDIT_V_MASK		0x00ffffff
#define EDIT_V_TUTIL		0x00000001	/* v_tutil */
#define EDIT_V_KSTATE		0x00000002	/* v_kstate */
#define EDIT_V_R_ALL		0x00000004	/* v_r_all */
#define EDIT_V_R_SOME		0x00000008	/* v_r_some */
#define EDIT_V_W_ALL		0x00000010	/* v_w_all */
#define EDIT_V_W_SOME		0x00000020	/* v_w_some */
#define EDIT_V_TFLAG		0x00000040	/* v_tflag */
#define EDIT_V_FSTYPE		0x00000080	/* v_fstype */
#define EDIT_V_COMMENT		0x00000100	/* v_comment */
#define EDIT_V_PUTIL		0x00000200	/* v_putil */
#define EDIT_V_STATE		0x00000400	/* v_state */
#define EDIT_V_PFLAG		0x00000800	/* v_pflag */
#define EDIT_V_PREFPLEX		0x00001000	/* v_pref_name */
#define EDIT_V_READ_POL		0x00002000	/* v_read_pol */
#define EDIT_V_UID		0x00004000	/* v_uid */
#define EDIT_V_GID		0x00008000	/* v_gid */
#define EDIT_V_MODE		0x00010000	/* v_mode */
#define EDIT_V_LEN		0x00020000	/* v_len */
#define EDIT_V_USE_TYPE		0x00040000	/* v_use_type */
#define EDIT_V_LOG_LEN		0x00080000	/* v_log_len */
#define EDIT_V_LOG_SERIAL	0x00100000	/* v_log_serial */
#define EDIT_V_START_OPTS	0x00200000	/* v_start_opts */
#define EDIT_V_PREFPLEX_RID	0x00400000	/* v_pref_plex_rid */
#define EDIT_V_RWBACK_OFFSET	0x00800000	/* v_rwback_offset */

/* 
 * plex - one or more subdisks, replication of volume data
 */

/* plex enum */
enum plex_layout {		/* type of plex subdisk order */
	MIN_PLEX_LAYOUT,	/* sentinel value, must be first */
	PL_STRIPE,		/* stripe subdisks */
	PL_CONCAT,		/* concatenate subdisks */
	MAX_PLEX_LAYOUT		/* sentinel value, must be last */
};
enum plex_kstate {	/* plex kernel state */
	MIN_PLEX_KSTATE,	/* sentinel value, must be first */
	PL_DISABLED,		/* plex is offline */
	PL_DETACHED,		/* plex is detached */
	PL_ENABLED,		/* plex is enabled */
	MAX_PLEX_KSTATE		/* sentinel value, must be last */
};

/* plex structure */
struct pl_tmp {			/* plex items that go away on reboot */
	char	pl_tutil[UTIL_NUM][UTIL_SZ];	/* 'in mem' utility field */
	ulong_t	pl_tflag;			/* flag, see PL_TFLAG_XXX */
  /*P*/ long	pl_lock;			/* 1 => record locked */
  /*P*/ long	pl_lasterr;			/* last plex error or 0 */
	enum plex_kstate pl_kstate;		/* relation to volume */
  /*P*/ long	pl_compact;			/* 1 => plex has no holes */
  /*P*/ minor_t	pl_minor;			/* minor number of plex dev */
  /*P*/ voff_t	pl_len;				/* byte length of plex */
  /*P*/	voff_t	pl_contig_len;			/* contiguous len from start */
  /*P*/	dev_t	pl_dev;				/* plex device number */
	char	pl_tspare[24];			/* room for expansion */
};
struct pl_perm {		/* plex items that exist after reboot */
  /*P*/ char	pl_name[NAME_SZ];		/* plex name */
	char	pl_putil[UTIL_NUM][UTIL_SZ];	/* 'on disk' utility field */
	char	pl_comment[COMMENT_SZ];		/* comment field */
  /*P*/ char	pl_v_name[NAME_SZ];		/* volume name or \0 */
	char	pl_state[STATE_SZ];		/* utility state of plex */
  /*P*/	volrid_t pl_rid;			/* unique identifier */
  /*P*/	volrid_t pl_vol_rid;			/* record ID for volume */
  /*P*/	volrid_t pl_log_sd_rid;			/* record ID of log subdisk */
  /*P*/	volseqno_t pl_update_tid;		/* trans id of last update */
  /*P*/	volseqno_t pl_detach_tid;		/* trans id of kernel detach */
	enum plex_layout pl_layout;		/* layout of subdisks */
	voff_t	pl_st_width;			/* stripe width if PL_STRIPE */
	ulong_t	pl_pflag;			/* flag, see PL_FLAG_XXX */
  /*P*/ long	pl_sd_num;			/* number of associated sds */
	char	pl_log_sd[NAME_SZ];		/* name of log subdisk */
};

#define pl_config_id pl_update_tid.seqno_lo
#define pl_config_epoch pl_update_tid.seqno_hi

struct plexrec {
	struct pl_tmp pl_tmp;		/* items that go away on reboot */
	struct pl_perm pl_perm;		/* items that remain after reboot */
};

/*
 * plex memory flag bits, the high order 12 bits are reserved for the kernel
 * to pass information back about the kernel state of the plex, see the
 * file sys/volkern.h for interpretation of these bits
 */

#define PL_TFLAG_MASK	  0x000f	/* mask for plex tflag */
#define PL_TFLAG_RMASK	  0x0700	/* mask for plex read-only tflag bits */
#define PL_TFLAG_READ	  0x0001	/* 1=>read ops are allowed */
#define PL_TFLAG_WRITE	  0x0002	/* 1=>write ops are allowed */
#define PL_TFLAG_LOG	  0x0004	/* do update plex's log area */
#define PL_TFLAG_COMPLETE 0x0008	/* plex is complete w.r.t. volume */
#define PL_TFLAG_VOLATILE 0x0100	/* an associated disk is volatile */
#define PL_TFLAG_REMOVED  0x0200	/* a disk device for plex is removed */
#define PL_TFLAG_NODAREC  0x0400	/* expected physical disk not found */

/* plex disk bits */
#define PL_PFLAG_MASK	  0x0007	/* mask for plex pflag */
#define PL_PFLAG_RMASK	  0x0000	/* mask for plex read-only pflag bits */
#define PL_PFLAG_NOERROR  0x0001	/* 0=>participate in errors,
					 * 1=>don't participate */
#define PL_PFLAG_STALE	  0x0002	/* plex needs recovery */
#define PL_PFLAG_KDETACH  0x0004	/* kernel logged a detach */

/* plex structure change bits */

#define EDIT_PL_MASK		0x000001ff
#define EDIT_PL_TUTIL		0x00000001	/* pl_tmp */
#define EDIT_PL_TFLAG		0x00000002	/* pl_tmp */
#define EDIT_PL_KSTATE		0x00000004	/* pl_tmp */
#define EDIT_PL_COMMENT		0x00000008	/* pl_perm */
#define EDIT_PL_PUTIL		0x00000010	/* pl_perm */
#define EDIT_PL_PFLAG		0x00000020	/* pl_perm */
#define EDIT_PL_LAYOUT		0x00000040	/* pl_perm */
#define EDIT_PL_ST_WIDTH	0x00000080	/* pl_perm */
#define EDIT_PL_STATE		0x00000100	/* pl_perm */

/* 
 * subdisk - physical component of a plex
 */

/* subdisk structure */
struct sd_tmp {			/* subdisk items that go away on reboot */
	char	sd_tutil[UTIL_NUM][UTIL_SZ];	/* 'in mem' utility field */
  /*P*/	char	sd_da_name[NAME_SZ];		/* disk access name */
	char	sd_dm_name[NAME_SZ];		/* disk media name */
	char	sd_device_tag[NAME_SZ];		/* device tag */
	ulong_t	sd_tflag;			/* temp flags for subdisk */
  /*P*/ long	sd_lock;			/* 1 => record locked */
  /*P*/	dev_t	sd_dev;				/* block device of subdisk */
	char	sd_tspare[16];			/* room for expansion */
};
struct sd_perm {		/* subdisk items that exist after reboot */
  /*P*/ char	sd_name[NAME_SZ];		/* subdisk record name */
  /*P*/ char	sd_path[SD_PATH_SZ];		/* subdisk block device path */
  /*P*/ char	sd_pl_name[NAME_SZ];		/* associated plex name or \0 */
	char	sd_comment[COMMENT_SZ];		/* comment field */
	char	sd_putil[UTIL_NUM][UTIL_SZ];	/* 'on disk' utility field */
  /*P*/	volrid_t sd_rid;			/* unique identifier */
  /*P*/	volrid_t sd_plex_rid;			/* record ID of plex */
  /*P*/	volrid_t sd_dm_rid;			/* disk media record ID */
  /*P*/	volseqno_t sd_update_tid;		/* trans id of last update */
	ulong_t	sd_pflag;			/* flag, see SD_FLAG_XXX */
  /*P*/ voff_t	sd_dev_offset;			/* offset within bdev */
  /*P*/	voff_t	sd_pl_offset;			/* offset of subdisk in plex */
  /*P*/	voff_t	sd_dm_offset;			/* offset relative to disk */
	voff_t	sd_len;				/* byte length of subdisk */
	char	sd_tspare[16];			/* room for expansion */
};

#define sd_config_id sd_update_tid.seqno_lo
#define sd_config_epoch sd_update_tid.seqno_hi
#define sd_offset sd_dm_offset

struct sdrec {
	struct sd_tmp sd_tmp;		/* items that go away on reboot */
	struct sd_perm sd_perm;		/* items that remain after reboot */
};

/*
 * subdisk temp flag bits, high order 12 bits are reserved for kernel
 * to pass back information about the kernel state of a record, see
 * sys/volkern.h for information about those bits
 */

#define SD_TFLAG_MASK	  0x0000	/* mask for subdisk tflag */
#define SD_TFLAG_RMASK	  0x0100	/* mask for sd read-only tflag bits */
#define SD_TFLAG_IS_LOG	  0x0100	/* subdisk is used as a log area */

/* subdisk permanent flag bits */
#define SD_PFLAG_MASK	  	0x0200	/* mask for subdisk pflag */
#define SD_PFLAG_RMASK	  	0x0100	/* mask for read-only sd pflag bits */
#define SD_PFLAG_VOLATILE 	0x0100	/* sd contents do not survive reboot */
#define SD_PFLAG_IGNORE_WRITES	0x0200	/* sd is read-only but write ops */
					/*  return successfully */

/*
 * NOTE: read-only pflag flags are kept in the pflag field for historical
 * reasons.  These flags are not really persistent.  The VOLATILE flag is
 * computed from the VOLATILE flag for the disk, which is a property of
 * the physical disk represented by the disk access record.
 */

/* subdisk structure change bits */

#define EDIT_SD_MASK	0x0000003f
#define EDIT_SD_TUTIL	0x00000001	/* sd_tmp.sd_tutil */
#define EDIT_SD_TFLAG	0x00000002	/* sd_tmp.sd_tflag */
#define EDIT_SD_COMMENT	0x00000004	/* sd_perm.sd_comment */
#define EDIT_SD_PUTIL	0x00000008	/* sd_perm.sd_putil */
#define EDIT_SD_LEN	0x00000010	/* sd_perm.sd_len */
#define EDIT_SD_PFLAG	0x00000020	/* sd_perm.sd_pflag */

/*
 * dmrec - disk media interface structure
 */

struct dmrec {

	/* temporary part */

	char	dm_tutil[UTIL_NUM][UTIL_SZ];	/* non-persistent util fields */
  /*P*/	char	dm_da_name[NAME_SZ];		/* disk access name */
  /*P*/	char	dm_device_tag[NAME_SZ];		/* component of this device */
  /*P*/	char	dm_da_type[DA_TYPE_SZ];		/* type from diskdev record */
  /*P*/	char	dm_pub_bpath[DK_PATH_SZ];	/* path of public block dev */
  /*P*/	char	dm_priv_bpath[DK_PATH_SZ];	/* path of private block dev */
  /*P*/	char	dm_pub_cpath[DK_PATH_SZ];	/* path of public raw dev */
  /*P*/	char	dm_priv_cpath[DK_PATH_SZ];	/* path of private raw dev */
	ulong_t	dm_tflag;			/* temp flags for disk */
  /*P*/	long	dm_lock;			/* 1 => record locked */
  /*P*/	dev_t	dm_pub_bdev;			/* dev of public partition */
  /*P*/	dev_t	dm_priv_bdev;			/* dev of private partition */
  /*P*/	voff_t	dm_pub_offset;			/* offset of public region */
  /*P*/	voff_t	dm_priv_offset;			/* offset of private region */
  /*P*/	voff_t	dm_pub_len;			/* length of public partition */
  /*P*/	voff_t	dm_priv_len;			/* len of private partition */
  /*P*/	size_t	dm_atomic_iosize;		/* minimum I/O size */
	long	dm_sd_num;			/* cnt of subdisks using disk */
	char	dm_tspare[32];			/* room for expansion */

	/* persistent part */

  /*P*/	char	dm_name[NAME_SZ];		/* disk name for disk group */
	char	dm_comment[COMMENT_SZ];		/* comment field */
	char	dm_putil[UTIL_NUM][UTIL_SZ];	/* persistent util fields */
  /*P*/	char	dm_diskid[VOL_UUID_SZ];		/* unique ID for disk */
  /*P*/	char	dm_last_da_name[NAME_SZ];	/* last associated DA record */
  /*P*/	volrid_t dm_rid;			/* record ID */
	volseqno_t dm_update_tid;		/* trans id of last update */
	ulong_t	dm_pflag;			/* persistent flags */
	char	dm_pspare[32];			/* room for expansion */
};

/*
 * disk temp flag bits.  The high-order 12 bits are reserved for use
 * by kernel-defined flags
 */

#define	DM_TFLAG_MASK		0x0000	/* mask for disk tflag */
#define	DM_TFLAG_RMASK		0x1f00	/* mask of read-only flags */
#define DM_TFLAG_PRIVATE	0x0100	/* disk has a private region */
#define DM_TFLAG_COMPONENT	0x0200	/* component of another device */
#define DM_TFLAG_VOLATILE	0x0400	/* disk contents don't survive reboot */
#define DM_TFLAG_NODAREC	0x0800	/* disk not found on reboot */
#define DM_TFLAG_AUTOCONFIG	0x1000	/* da record was auto-configured */

/* disk persistent flag bits */
#define DM_PFLAG_MASK	  0x00000001	/* mask of modifiable pflag bits */
#define DM_PFLAG_RESERVE  0x00000001	/* disk is reserved for special uses */
#define DM_PFLAG_RMASK	  0x00000100	/* mask of read-only pflag bits */
#define DM_PFLAG_REMOVED  0x00000100	/* disk is currently inaccessible */

/* disk structure change bits */

#define EDIT_DM_MASK	0x0000001f
#define EDIT_DM_TUTIL	0x00000001	/* dm_tutil */
#define EDIT_DM_TFLAG	0x00000002	/* dm_tflag */
#define EDIT_DM_COMMENT	0x00000004	/* dm_comment */
#define EDIT_DM_PUTIL	0x00000008	/* dm_putil */
#define EDIT_DM_PFLAG	0x00000010	/* dm_pflag */

/*
 * dgrec - disk group interface structure
 */

struct dgrec {

	/* temporary part */

	char	dg_tutil[UTIL_NUM][UTIL_SZ];	/* non-persistent util fields */
	char	dg_name[NAME_SZ];		/* import name (maybe alias) */
	ulong_t	dg_tflag;			/* non-persistent flags */
  /*P*/	long	dg_lock;			/* 1 => record locked */
  /*P*/	volrid_t dg_import_id;			/* non-persistent import ID */
	char	dg_tspare[32];			/* room for expansion */

	/* persistent part */

  /*P*/	char	dg_real_name[NAME_SZ];		/* name stored in disk group */
	char	dg_comment[COMMENT_SZ];		/* comment field */
	char	dg_putil[UTIL_NUM][UTIL_SZ];	/* persistent utility fields */
  /*P*/	char	dg_dgid[VOL_UUID_SZ];		/* unique ID for disk group */
  /*P*/	volrid_t dg_rid;			/* record ID in disk group */
	volseqno_t dg_update_tid;		/* trans id of last update */
	ulong_t	dg_pflag;			/* persistent flags */
	char	dg_pspare[32];			/* room for expansion */
};

/*
 * disk group temp flag bits.  The high-order 12 bits are reserved for
 * use by kernel-defined flags
 */

#define DG_TFLAG_MASK	  0x000000	/* mask for disk group tflag */
#define DG_TFLAG_RMASK	  0x000100	/* read-only disk group tflag bits */
#define DG_TFLAG_DISABLED 0x000100	/* disk group is disabled */

/* disk group persistent flag bits */
#define DG_PFLAG_MASK	  0x000000	/* mask for disk pflag */
#define DG_PFLAG_RMASK	  0x000000	/* read-only disk group tflag bits */

/* disk structure change bits */

#define EDIT_DG_MASK	0x0000001f
#define EDIT_DG_TUTIL	0x00000001	/* dg_tutil */
#define EDIT_DG_TFLAG	0x00000002	/* dg_tflag */
#define EDIT_DG_COMMENT	0x00000004	/* dg_comment */
#define EDIT_DG_PUTIL	0x00000008	/* dg_putil */
#define EDIT_DG_PFLAG	0x00000010	/* dg_pflag */

/*
 * darec - disk access interface structure
 */

struct darec {

	/* temporary part */

  /*P*/	char	da_dm_name[NAME_SZ];		/* media name in disk group */
  /*P*/	char	da_dg_name[NAME_SZ];		/* disk group name, if any */
  /*P*/	char	da_device_tag[NAME_SZ];		/* part of this device */
  /*P*/	char	da_pub_bpath[DK_PATH_SZ];	/* path of public block dev */
  /*P*/	char	da_priv_bpath[DK_PATH_SZ];	/* path of private block dev */
  /*P*/	char	da_pub_cpath[DK_PATH_SZ];	/* path of public raw dev */
  /*P*/	char	da_priv_cpath[DK_PATH_SZ];	/* path of private raw dev */
  /*P*/	ulong_t	da_tflag;			/* temp flags for disk dev */
  /*P*/	long	da_lock;			/* 1 => record locked */
  /*P*/	volrid_t da_dg_import_id;		/* disk group import ID */
  /*P*/	volrid_t da_dm_rid;			/* media record rid */
  /*P*/	dev_t	da_pub_bdev;			/* dev of public partition */
  /*P*/	dev_t	da_priv_bdev;			/* dev of private partition */
  /*P*/	long	da_fail_code;			/* failed operation */
  /*P*/	long	da_fail_errno;			/* error number for failure */
	char	da_tspare[32];			/* room for expansion */

	/* persistent part */

  /*P*/	char	da_name[NAME_SZ];		/* device name */
	char	da_comment[COMMENT_SZ];		/* comment field */
	char	da_type[DA_TYPE_SZ];		/* disk device type */
	char	da_info[DA_INFO_SZ];		/* type-specific info */
  /*P*/	volrid_t da_rid;			/* record ID in root config */
  /*P*/	volseqno_t da_update_tid;		/* trans id of last update */
	ulong_t	da_pflag;			/* persistent flags */
	char	da_pspare[32];			/* room for expansion */
};

/* operations in da_fail_code */
#define DA_FAIL_ONLINE		1	/* implicit online operation failed */
#define DA_FAIL_JOIN		2	/* implicit join operation failed */

/*
 * disk device temp flag bits.  The high-order 12 bits are reserved for
 * use by kernel-defined flags
 */

#define DA_TFLAG_MASK		0x0000	/* mask for disk group tflag */
#define DA_TFLAG_RMASK		0xff00	/* mask of read-only flags */
#define DA_TFLAG_PRIVATE	0x0100	/* disk has a private region */
#define DA_TFLAG_COMPONENT	0x0200	/* device is part of a disk */
#define DA_TFLAG_VOLATILE	0x0400	/* disk is volatile */
#define DA_TFLAG_BADTYPE	0x0800	/* disk type is unknown */
#define DA_TFLAG_READY		0x1000	/* disk is accessible */
#define DA_TFLAG_INVALID	0x2000	/* configuration error */
#define DA_TFLAG_AUTOCONFIG	0x4000	/* generated DA record, not stored */
#define DA_TFLAG_RESERVE	0x8000	/* reserved bit is set in DM record */
#ifdef	__alpha
#define DA_TFLAG_MODDB		0x10000	/* indiactes DA record is being modified */
#endif /* __alpha */

/* disk group persistent flag bits */
#define DA_PFLAG_MASK		0x0000	/* mask for disk pflag */
#define DA_PFLAG_RMASK		0x0100	/* mask of read-only flags */
#define DA_PFLAG_ONLINE		0x0100	/* disk should be made accessible */

/* disk group structure change bits */

#define EDIT_DA_MASK		0x00000007
#define EDIT_DA_COMMENT		0x00000001	/* da_comment */
#define EDIT_DA_TFLAG		0x00000002	/* da_tflag */
#define EDIT_DA_PFLAG		0x00000004	/* da_pflag */

/*
 * NOTE:  The constants below are all configurable parameters that can
 *	  be changed at kernel configuration time.  In most cases, the
 *	  GET_VOLINFO ioctl should be used to get these configuration
 *	  parameters, rather than using these constants.
 */

#define	VOL_MAXSPECIALIO	128	/* Max size of an I/O ioctl (sectors) */
#define	VOL_MAXIO		128	/* Max I/O size in sectors */
#define	VOL_MAXIOCTL		32768	/* Max size of ioctl data (bytes) */
#define	VOL_MAXILOCKSLEEP	5	/* max times to block on I/O interlock
					   before getting priority */
#define VOL_DEFAULT_IODELAY	250	/* dflt I/O delay for vol_copy */
#ifdef __alpha
#define VOL_MAXFREEBUF		8	/* max number of volbufs to keep */
#define VOL_MAXFREEVCB		8	/* max number of volcbs' to keep */
#else /* !__alpha */
#define VOL_MAXFREEBUF		max(8, ((ptob(2)) / sizeof (struct volbuf)))
					/* max number of volbufs to keep */
#define VOL_MAXFREEVCB		max(8, ((ptob(2)) / sizeof (struct volcb)))
					/* max number of volcbs' to keep */
#endif /* __alpha */
#define VOL_MAXPARALLELIO	256	/* max # voldios allowed at one time */

#define	VOL_ROOTVOL_MINOR	0x00	/* minor 0 */
#define VOL_SWAPVOL_MINOR	0x01	/* minor 1 */


/*
 * OSF kernel definitions
 */

/*
 * Debug
 */
extern int voldebug;	/* Debug Flag */
#define PRTDBG	if (voldebug) printf
#if defined(DEBUG) || defined(OSF)
#define STATIC
#else 
#define STATIC static
#endif

/*
 * vxvm specifics
 */
#undef VOL_PAGEPROC
#define VOL_PAGEPROC	(0)

#ifdef _KERNEL

/*
 * Redefine the sleep macro.  In alpha osf/1 v1.2, sleep is defined as
 * (void)mpsleep(...).  Sleep should return a status in case it is
 * a signal that wakes the process up.  It is redefined here.  The
 * calling syntax is copied from src/kernel/sys/param.h and the (void)
 * removed.
 */
#ifdef sleep
#undef sleep
#define sleep(chan, pri) mpsleep(chan, pri, "Zzzzzz", 0, (void *)NULL, 0)
#else
#define sleep(chan, pri) mpsleep(chan, pri, "Zzzzzz", 0, (void *)NULL, 0)
#endif

/*
 * Define from stddef.h.
 */
#ifdef __alpha
#define offsetof(s_name, s_member) \
        ((size_t)((char *)&((s_name *)0L)->s_member - (char *)0L))
#endif /* __alpha */

/*
 * alpha smp switch
 */
#ifdef __alpha
#if NCPUS > 1
#define MP
#endif /* NCPUS > 1 */
#endif /* __alpha */

#endif /* KERNEL */

/* 
 * SVR4 to OSF Conversion
 */

#define _VOID void

#define DEV_DEV_COMPARE(dev1, dev2) ((dev1) == (dev2))
#define CONFIG_OK       0
#define CONFIG_BAD      1

/* 
 * Definitions for drv_getparm()
 */
#define	LBOLT	4
#define	UPROCP	2
#define	PPID	11

/*
 * b_start is defined in buf.h when exl is defined. b_start needs
 * to be redefined otherwise it overwrites b_pmap.
 */
#ifndef exl
#define b_start         b_driver_un_2.timevalue
#endif

#define cred ucred

#define getmajor major
#define getminor minor
#define makedevice makedev

typedef struct uio	uio_t;
typedef struct iovec	iovec_t;
typedef struct proc	proc_t;
typedef struct buf	buf_t;

#undef	b_edev		/* Defined in <sys/buf.h>, avoids warning messages. */
#define b_edev	b_dev

/*
 * OTYP are defined in sys/open.h.  But only BLK|CHR|MNT|LYR
 * are defined.  So, define OTYP_SWP and OTYPCNT here.
 */
#define OTYPCNT         5
#define OTYP_SWP        3

#define VXVM_OTYPCNT    5
#define VXVM_OTYP_BLK   0
#define VXVM_OTYP_CHR   1
#define VXVM_OTYP_MNT   2
#define VXVM_OTYP_SWP   3
#define VXVM_OTYP_LYR   4

#define	SCTRSHFT	DEV_BSHIFT
#define	NBPSCTR		DEV_BSIZE

#define SIGCLD		SIGCHLD

#define	getemajor(dev)			major(dev)
#define	etoimajor(major)		(major)

#define	geteminor(dev)			minor(dev)

#define cmpdev(dev)			dev


#define drv_priv(cred)		(suser(u.u_cred, &u.u_acflag))

/*
 * kmem_alloc emulation
 */
#define KM_SLEEP	0
#define KM_NOSLEEP	1

/*
 * alpha define
 */
/* -- Turn off TED
#ifndef TED_ACTIVE
#define TED_ACTIVE=1
#endif
*/

#endif /* _SYS_VOL_H */
