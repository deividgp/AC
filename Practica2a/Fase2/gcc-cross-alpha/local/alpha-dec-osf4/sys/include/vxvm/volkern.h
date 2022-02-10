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

#pragma	ident	"@(#)$RCSfile: volkern.h,v $ $Revision: 1.1.8.5 $ (DEC) $Date: 1995/12/05 18:45:24 $"

/* @(#)src/common/uts/io/vxvm/volkern.h	6.7 30 May 1993 22:09:39 - Copyright (c) 1993 VERITAS Software Corp. */
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
 * sys/volkern.h - volume manager kernel only header file
 */

#ifndef _SYS_VOLKERN_H
#define _SYS_VOLKERN_H

struct voltab {
	struct volume	*vt_vp;		/* 0x00 current volume */
	ulong_t		vt_flags;	/* 0x04 lock flags */
	ulong_t		vt_active;	/* 0x08 active count */
	ulong_t		vt_operation;	/* 0x0c operations count */
	struct vollogcb	*vt_logcb;	/* 0x10 control block for logio */
	struct volspin	vt_spin;	/* 0x14 spin lock */
	struct volsync	vt_dlock_sync;	/* 0x20 data lock */
	struct volsync	vt_config_sync;	/* 0x28 config sync lock */
	struct volsync	vt_logiod_sync;	/* 0x30 sync lock for logging daemon */
};					/* 0x38 */

#define	VT_DLOCK	0x01		/* data lock held */
#define	VT_DLOCK_WANT	0x02		/* data lock wanted */
#define VT_SERIALIZE	0x04		/* volume is serializing */
#define VT_KACTWAIT	0x08		/* kernel action being serialized */
#define VT_LOGD_EXIST	0x10		/* logging I/O daemon exists */
#define VT_LOGD_WAIT	0x20		/* waiting for logging I/O daemon */
#define VT_LOGD_DIE	0x40		/* logging I/O daemon not needed */
#define VT_LOGD_LOGGING	0x80		/* logging is active for this vol */

/*
 * This structure wraps around a vol_io structure to provide extra
 * fields needed by the kernel.
 */

struct volio {
	struct volio	*vi_next;	/* 0x00 next volio structure */
	struct volio	*vi_prev;	/* 0x04 previous volio structure */
	int		vi_cmd;		/* 0x08 volio ioctl command */
	caddr_t		vi_kbuf1;	/* 0x0c kernel buffer 1 */
	caddr_t		vi_kbuf2;	/* 0x10 kernel buffer 2 */
	struct plx_ent	*vi_ksrcplex;	/* 0x14 kernel source plex array */
	struct plx_ent	*vi_kdestplex;	/* 0x18 kernel destination plex array */
	int		vi_errflag;	/* 0x1c error flag */
	struct vol_io	vi_volio;	/* 0x20 volio structure */
	struct volsync	vi_sync;	/* 0x3c synclock for spec interlock */
};					/* 0x44 */

/*
 * The following actions represent configuration changes that can be initiated
 * by the kernel.  These will be used in support of volume manager utilities.
 * One example is the "sync and detach plex" operation the VERITAS File
 * System will support.  This will be used to get clean copies of the file
 * system while it is active.
 */

#define	OFFPLEX		1	/* Action for kernel DISABLING a plex */
#define	OFFVOL		2	/* Action for kernel DISABLING a volume */
#define	DETPLEX		3	/* Action for kernel DETACHING a plex */
#define	DETVOL		4	/* Action for kernel DETACHING a volume */

#define	V_OFLAGS	(FREAD|FWRITE)	/* flags passed to driver open and close routines */

/*
 * These flags are used on all volume objects.
 */
#define V_MIRRORED	0x00000001	/* volume has >1 enabled plex */
#define	V_INTERLOCK	0x00000002	/* an I/O interlocked on the volume */
#define	V_SPECIALIO	0x00000004	/* doing volume ioctl or plex dev I/O */
#define	V_STRATIO	0x00000010	/* doing read/write volume I/O */
#define	V_REREAD	0x00000020	/* doing reread after a failed read */
#define	V_WRITEBACK	0x00000040	/* doing writeback after a reread */
#define V_RWBACK	0x00000080	/* read/writeback mode plex recovery */
#define V_WCPYBUF	0x00000100	/* unstable write buffer so copy it */
#define V_RCPYBUF	0x00000200	/* unstable read buffer so copy it */
#define V_SYNC		0x00000400	/* perform I/O synchronously */
#define	V_READDONE	0x00001000	/* read error recovery is finished */
#define	V_ERROR		0x00002000	/* current request has had an error */
#define	V_BUSY		0x00004000	/* I/O is active against this request */
#define	V_LOG		0x00008000	/* subdisk is a log, not plex space */
#define	V_LOGIO		0x00010000	/* state flag for vcb's when logging */
#define V_DELETED	0x00040000	/* vol has been marked for deletion */
#define V_REPLACE	0x00080000	/* vol is being replaced in xaction */
#define	V_FAKE		0x00100000	/* volume is a rootability fake */
/*
 * DEC defines
 */
#define V_DUMP		0x20000000	/* Indicates this entry was already */
					/* used for dump purposes */
#define V_ROOT_NEEDSYNC 0x40000000	/* indicates that there was a write */
					/* to rootvol before vold ran */
#define V_PRESTO	0x80000000	/* indicates that presto had to */
					/* be disabled for the volume */

/*
 * These flags are used to synchronize start/stop of log
 * voliod's in voliodflags.
 */
#define VOLIOD_DIE	0x1
#define	VOLIOD_EXIST	0x2

/*
 * The volcb structure acts as a control block for each I/O request.  It
 * is used to link all the resources used in satisfying an I/O request.
 */
struct volcb {
	struct volcb	*fw;		/* 0x00 interlock chain ptr */
	struct volcb	*bk;		/* 0x04 interlock chain ptr */
	struct volcb	*next;		/* 0x08 next volcb in list */
	struct volume	*volp;		/* 0x0c volume for this request */
	struct volio	*viop;		/* 0x10 volio data for plex device
						or volume ioctl operations */
	struct buf	*reqp;		/* 0x14 I/O request passed to 
						volume manager */
	int		state;		/* 0x18 current state of request 
						(volcb flags) */
	int		success;	/* 0x1c could request be
						successfully completed */
	enum vol_except	exception;	/* 0x20 exception recognized during 
						request */
	int		bcount;		/* 0x24 number of bytes in request */
	int		active;		/* 0x28 active I/O against request */
	int		reqcnt;		/* 0x2c total I/Os generated by
						request */
	int		errcnt;		/* 0x30 I/Os that generated an error
 						in current state */
	int		oerrcnt;	/* 0x34 I/Os that generated errors 
						in previous states */
	clock_t		start;		/* 0x38 start time of I/O for stats*/
	long            req_id;		/* 0x3c unique req id for tracing */
	struct volbuf	*actbuf;	/* 0x40 list of active buffers */
	struct volbuf	*oldbuf;	/* 0x44 list of inactive buffers */
	long		actplex;	/* 0x48 plexes with active I/O */
	long		errplex;	/* 0x4c plexes with errors */
	long		detplex;	/* 0x50 plexes to be detached */
	struct blogent	*logp;		/* 0x54 log slot to clear */
	struct volcb	*iolist;	/* 0x58 list of i/o to start after */
					/*	logging */
	struct buf      *orig_reqp;	/* 0x5c saved reqp for chunking */
	int             chunkoff;	/* 0x60 offset in chunk */
	struct volcb	*parent_vcb;	/* 0x64 pointer to the whole */
	int 		refcnt;		/*
					 * Updated once for startegy() and 
					 * again for voliocleanup(). refcnt used 
					 * to determine when to free volcb.
					 * Freed either at end of volstrategy0() 
					 * or in voliocleanup(). 
					 */
					/*
					 * Following locks must occur last in
					 * struct because everything before
					 * them is cleared in volcb_alloc
					 */
	struct volspin	spin;		/* 0x68 spinlock for struct */
	struct volsync	sync;		/* 0x74 synclock for I/O completions */
};					/* 0x7c */

/*
 * a minimal volcb-like structure for interlock chaining
 */
struct volcbhdr {
	struct volcb	*fw;			/* 0x0 interlock chaining ptr */
	struct volcb	*bk;			/* 0x4 interlock chaining ptr */
};						/* 0x8 */

/*
 * This is the kernel's internal volume structure.
 */

struct volume {
	struct volkvol	v_kv;		/* 0x000 external volume struct */
	struct diskgroup *v_dg;		/* 0x064 disk group */
	struct volume	*v_next;	/* 0x068 next vol in list */
	struct plex	*v_plex;	/* 0x06c list of plexes */
	struct plex	*v_prefplex;	/* 0x070 preferred plex for reading */
	struct plex	*v_readplex;	/* 0x074 current plex for reading */
        struct volcbhdr	v_busypri;	/* 0x078 Priority wait queue */
        struct volcbhdr	v_busy;		/* 0x080 I/O interlock queue */
	int		v_flags;	/* 0x088 volume flags */
	int		v_opencnt[OTYPCNT];	 /* 0x08c # of each open type */
	struct volcb	*v_pending;	/* 0x0a0 list of requests waiting for
						 serialization */
	long		v_trmask;	/* 0x0a4 trace mask for volume */
	struct vol_stat	v_stats;	/* 0x0a8 I/O stats for volume */
	struct volio	v_volio;	/* 0x10c volio header for special I/O
						 interlock */
	struct volkvol_assert *v_kvap;	/* 0x150 assert values for commit */
	struct voltab	*v_vtp;		/* 0x154 pointer to struct voltab */
	int		v_pl_num;	/* 0x158 number of plexes in volume */
        struct volcb    *v_clean;       /* 0x15c cleanup following serialize */
        int             v_nclean;       /* 0x160 number of things to clean */
	struct volspin	v_spin;		/* 0x15c volume spin lock */
	struct volsync	v_active_sync;	/* 0x168 activity sync lock */
	struct volsleep	v_open_sleep;	/* 0x170 sleep lock for opens */
	struct volsleep	v_firstw_sleep;	/* 0x17c sleep lock for 1st write op */
	struct volsleep	v_kaction_sleep;/* 0x188 kernel action sleeplock */
	struct volsync	v_kaction_sync;	/* 0x194 kernel action synclock */
	int		v_klogoff;	/* 0x19c klog offset of vol record */
};					/* 0x1a0 */

#define	vc_name			v_kv.kv_name
#define	vc_rid			v_kv.kv_rid
#define	vc_minor		v_kv.kv_dev
#define	vc_dev			v_kv.kv_dev
#define	vc_len			v_kv.kv_len
#define	vc_read_pol		v_kv.kv_read_pol
#define vc_pref_plex		v_kv.kv_pref_plex
#define	vc_r_all		v_kv.kv_r_all
#define	vc_r_some		v_kv.kv_r_some
#define	vc_w_all		v_kv.kv_w_all
#define	vc_w_some		v_kv.kv_w_some
#define	vc_kstate		v_kv.kv_kstate
#define	vc_kflag		v_kv.kv_kflag
#define	vc_sflag		v_kv.kv_sflag
#define	vc_lasterr		v_kv.kv_lasterr
#define vc_detach_id		v_kv.kv_detach_id
#define	vc_log_serial_lo	v_kv.kv_log_serial_lo
#define	vc_log_serial_hi	v_kv.kv_log_serial_hi
#define vc_rwbackoff		v_kv.kv_rwbackoff

/*
 * This structure forms an extended buffer header used for volume I/O.
 * The volbuf structure contains a pointer to the actual buf.  The
 * b_back field of the buf structure contains a pointer back to the
 * volbuf structure.  The b_forw field of the buf structure contains
 * a pointer to active buffers.
 */

struct volbuf {
	struct buf		vb_buf;		/* 0x00 buffer for disk I/O */
	struct volbuf		*vb_next;	/* 0x64 next volbuf in list */
	struct volcb		*vb_volcb;	/* 0x68 volcb struct for buf */
	struct plex		*vb_plex;	/* 0x6c plex I/O is going to */
	struct subdisk		*vb_sd;		/* 0x70 subdisk for I/O */
	struct voldio_region	*vb_regp;	/* 0x74 region for voldio */
	int			vb_baseoff;	/* 0x78 base offset in blks */
};						/* 0x7c */

/*
 * This is the kernel's internal plex structure.
 */

struct plex {
	struct volkplex	pl_kpl;			/* 0x00 external plex struct */
	struct plex	*pl_next;		/* 0x60 next plex associated
							with volume */
	struct plex	*pl_prev;		/* 0x64 previous plex associated
							with volume */
	struct volume	*pl_vol;		/* 0x68 volume this plex is 
							associated with */
	struct subdisk	*pl_sd;			/* 0x6c list of subdisks
							associated with plex */
	int		pl_volklog;		/* 0x70 detach log ent offset */
	daddr_t		pl_len;			/* 0x74 length of this plex */
	long		pl_plexflag;		/* 0x78 number of this plex in
							volume */
	int		(*pl_strat)();		/* 0x7c plex specific strategy
							routine */
	int		pl_flags;		/* 0x80 kernel flags for plex */
	int		pl_opencnt[OTYPCNT];	/* 0x84 open counts for plex */
	int		pl_compact;		/* 0x98 !!! mv from temp rec */
	int		pl_sd_num;		/* 0x9c number of subdisks */
	struct pl_stat	pl_stats;		/* 0xa0 I/O stats for plex */
	struct volkplex_assert *pl_kplap;	/* 0xc0 commit assert values */
	struct volspin	pl_spin;		/* 0xc4 spinlock for struct */
	struct volsleep	pl_open_sleep;		/* 0xd0 sleep lock for opens */
};						/* 0xdc */

#define	pc_name		pl_kpl.kpl_name
#define	pc_log_sd	pl_kpl.kpl_log_sd_name
#define	pc_minor	pl_kpl.kpl_dev
#define	pc_dev		pl_kpl.kpl_dev
#define pc_rid		pl_kpl.kpl_rid
#define pc_volrid	pl_kpl.kpl_volrid
#define pc_log_sd_rid	pl_kpl.kpl_log_sd_rid
#define	pc_kflag	pl_kpl.kpl_kflag
#define	pc_sflag	pl_kpl.kpl_sflag
#define	pc_kstate	pl_kpl.kpl_kstate
#define	pc_layout	pl_kpl.kpl_layout
#define	pc_st_width	pl_kpl.kpl_st_width
#define pc_detach_id	pl_kpl.kpl_detach_id
#define	pc_lasterr	pl_kpl.kpl_lasterr

/*
 * This is the kernel's internal subdisk structure.
 */

struct subdisk {
	struct volksd	sd_ksd;		/* 0x00 */
	struct voldisk	*sd_disk;	/* 0x48 disk subdisk is associated
						with  !!! */
	struct subdisk	*sd_next;	/* 0x4c next subdisk associated with
						plex */
	struct subdisk	*sd_prev;	/* 0x50 previous subdisk associated
						with plex */
	struct volume	*sd_vol;	/* 0x54 volume subdisk's plex is 
						associated with */
	struct plex	*sd_plex;	/* 0x58 plex subdisk is associated 								with */
	int		sd_flags;	/* 0x5c kernel flags for subdisk */
	daddr_t		sd_end;		/* 0x60 end of subdisk within plex */
	struct sd_stat	sd_stats;	/* 0x64 I/O stats for subdisk */
	struct volksd_assert *sd_ksdap;	/* 0x84 assert values for commit */
};					/* 0x88 */

#define	sc_name		sd_ksd.ksd_name
#define	sc_rid		sd_ksd.ksd_rid
#define	sc_drid		sd_ksd.ksd_drid
#define	sc_plrid	sd_ksd.ksd_plrid
#define	sc_volrid	sd_ksd.ksd_volrid

#define	sc_dev		sd_disk->dc_pub_dev

#define	sc_kflag	sd_ksd.ksd_kflag
#define	sc_sflag	sd_ksd.ksd_sflag

#ifdef sd_offset				/* tmp: until vol.c is clean */
#undef sd_offset
#endif

#define	sc_offset	sd_ksd.ksd_offset
#define	sd_offset	sd_ksd.ksd_offset	/* tmp: obsolete member */

#define	sc_pl_offset	sd_ksd.ksd_pl_offset
#define	sd_pl_offset	sd_ksd.ksd_pl_offset	/* tmp: obsolete member */

#define	sc_len		sd_ksd.ksd_len
#define	sd_len		sd_ksd.ksd_len		/* tmp: obsolete member */

#define	MAXVSPEC	4			/* number of special volume
						   manager devices */
#define	VOLCONFIG	0			/* minor number for 
						   /dev/volconfig */
#define	VOLEVENT	1			/* minor number for
						   /dev/volevent */
#define	VOLIODAEMON	2			/* minor number for
						   /dev/volerrdaemon */
#define VOLINFO		3			/* minor number for 
						   /dev/volinfo */

#define volbuf_free(vbp)					\
		do {						\
			VOL_SPINLOCK(volbuf_spin);		\
			(vbp)->vb_next = vol_bfreelist;		\
			vol_bfreelist = (vbp);			\
			vol_nfreebuf++;				\
			VOL_UNSPINLOCK(volbuf_spin);		\
		} while (ZERO)

struct volspec {
	int	vs_flags;			/* 0x00 flags for special volume
							manager devices */
	struct volsleep	vs_open_sleep;		/* 0x04 open/close sleeplock */
	int		vs_opencnt[OTYPCNT];	/* 0x10 open counts */
};						/* 0x24 */

#define	VOLSPEC_OPEN	0x1			/* device is open */

/*
 * This structure controls a transaction in the kernel.
 */

struct voltrans {
	struct voltrans	*next;			/* 0x00 next structure in doubly
							linked list */
	struct voltrans	*prev;			/* 0x04 prev structure in doubly
							linked list */
	long		tid;			/* 0x08 transaction id for this
							transaction */
	int		tmid;			/* 0x0c timeout value returned
							by data locks call */
	int		timeout;		/* 0x10 length of timeout */
	int		flags;			/* 0x14 kernel flags for
							transact */
};						/* 0x18 */

/*
 * Structures for block change logging
 */

struct vollogcb {
	int		lc_flags;	/* 0x00  flags for vollogcb */
#ifndef __alpha
	short		lc_busy;	/* 0x04 log busy flag */
	short		lc_driver_busy;	/* 0x06 "real" busy flag */
#endif /* !__alpha */
	int		lc_logcnt;	/* 0x08 number of log slots used */
	struct volcb	*lc_rdyq;	/* 0x0c list of real i/o vcb's */
	struct volcb	*lc_logq;	/* 0x10 list of real i/o vcb's */
	struct volcb	*lc_logvcp;	/* 0x14 volcb for log control */
	struct volbuf	*lc_logbuf;	/* 0x18 buffer for log i/o */
	struct volblog	*lc_blog;	/* 0x1c block change log */
	struct volblog	*lc_tmplog;	/* 0x20 stable cpy of log for log i/o */
	struct volspin	lc_spin;	/* 0x24 spinlock for logcb */
	struct volsync	lc_sync;	/* 0x30 sync lock for log I/O */
	struct volsync	lc_logwork_sync;/* 0x38 sync lock for log daemon */
};					/* 0x3c */

/*
 * Flags for vollogcb.
 */
#define LC_BCL_DISABLED		0x01		/* BCL error */
#define LC_BCL_LOGIOBUSY	0x02		/* logio call doing work */
#ifdef __alpha
#define LC_BCL_SYNC		0x04		/* synchronous log write */
#endif /* __alpha */


#define	VOL_BLOG(vp) \
	(((vp)->vc_kflag & V_KFLAG_LOGTYPE) == V_KFLAG_LOGBLKNO && \
	 (vp)->vc_sflag & V_SFLAG_LOG_IO_NEED)

typedef struct volblog volblog_t;
typedef struct vollogcb vollogcb_t;

#define VOLHASH			32		/* number of name hash buckets,
						   must be power of 2 */
#define	VOLTRACE_SIZE		1024		/* number of events in voltrace
						   buffer */
#define VOL_CPYBUF_HIWATER	(1536 * 1024)	/* default high water mark for
						   kmem space used for buffer
						   copying */
/* CHECKTHIS
 * This is defined in vol.h as (0).  Why is this redefined here??
 */
#ifdef __alpha
#define VOL_PAGEPROC	(0)
#else /* !__alpha */
#define VOL_PAGEPROC	(u.u_procp == proc_pageout || u.u_procp == proc_sched)
#endif /* __alpha */

#if !defined(DDI_COMPLIANT)

/*
 * These defines for the calls to the I/O mapping functions from
 * pio_breakup are necessary if drivers other than DMA drivers are
 * supported on a SVR4.2 system.
 */
#define		VOL_NPGS(base, count)	\
		((count) + ((int)(base) & PAGEOFFSET) + NBPC - 1) >> BPCSHIFT

extern caddr_t		mappio();
extern int		unmappio();

#endif /* DDI_COMPLIANT */

extern int		vol_nbufalloc;		/* number of buffer headers to
						   allocate at a time */
extern int		vol_maxfreebuf;		/* max number of free buffer
						   headers */
extern int		vol_nfreebuf;		/* number of free buffer
						   headers */
extern int		vol_vb_lowater;		/* low water mark of free
						   buffers below which only
						   the pager process can go */
extern struct volbuf	*vol_bfreelist;		/* list of free buffer
						   headers */
extern int		vol_nvcballoc;		/* number of volcb structs to
						   allocate at a time */
extern int		vol_maxfreevcb;		/* max number of free volcb
						   structs */
extern int		vol_nfreevcb;		/* number of free volcb
						   structs */
extern int		vol_vcb_lowater;	/* low water mark of free
						   volcb structs below which
						   only pager process can go */
extern struct volcb	*vol_vcbfreelist;	/* list of free volcb structs */
extern char		vol_cpybuf_reserve[];	/* buffer reserved for pager to
						   do cpybuf ops. */
extern int		vol_cpybuf_used;	/* count of bytes of copy buffer
						   space in use */
extern int		vol_cpybuf_hiwater;	/* max copy buffer space to
						   allocate */
extern long		voltrmask;		/* trace mask for system */
extern long		vol_init_trmask;	/* initial trace mask for
						   system */
extern int		nvoltrace;		/* # of events in trace
						   buffer */
extern struct volevent	voltrace[];		/* voltrace buffer */

extern pid_t		voldpid;		/* pid of vold process or 0
						   if no vold */
extern proc_t		*voldprocp;		/* proc ptr for vold if !NULL */

#ifdef	__alpha
extern struct voltab	*voltab;		/* pointer to mapping array of
						   volumes to minor numbers */
extern struct voltab	**plextab;		/* pointer to pointers of
						   plexes to minor numbers */
#else /* !__alpha */
extern struct voltab	voltab[];		/* pointer to mapping array of
						   volumes to minor numbers */
extern struct voltab	*plextab[];		/* pointer to mapping array of
						   plexes to minor numbers */
#endif /* __alpha */
/* This was defined in volSpace.c, but not used. Hence being commented out */
#ifndef	__alpha
extern int		voliodflags[];		/* Flags for killing/starting
						   log voliod's */
#endif /* __alpha */

extern struct volcb	*volerrqueue;		/* list of volcb structures
						   waiting for error handling */
extern int		volerractive;		/* count of active error
						   daemons */
extern int		max_volerrq;		/* max # of err daemons */

extern struct voltrans	voltrans;		/* list of active transacts */

#if defined(MP)
extern struct page	*getnextpg();		/* DDI routine for page walk */
#endif /* MP */

extern struct volsleep	vollogiod_sleep;	/* sleep log for log daemon */
extern struct volsleep	volcfg_sleep;	/* sleep lock for config driver */
extern struct volspin	voltrace_spin;	/* spinlock for tracing mechanism */
extern struct volsync	voltrace_sync;	/* synclock for tracing mechanism */
extern struct volspin	volbuf_spin;
extern struct volspin	volerrq_spin;
extern struct volsync	volerrq_sync;
extern struct volsync	volerrq_die_sync;
extern struct volspin	voldpid_spin;


extern struct volinfo	volinfo;		/* general vm info structure */
extern struct vol_sdi_info vol_sdi_info;	/* SCSI disk information */

extern struct volspec	volspec[];		/* array of special volume 
						   manager device structures */

extern int		voldevflag;		/* driver flags for volume 
						   virtual disk devices */
extern int		plexdevflag;		/* driver flags for plex 
						   virtual disk devices */
extern int		volsdevflag;		/* driver flags for special 
						   volume manager devices */

extern int		vol_disabled;		/* flag set when driver is 
						   disabled */
extern long		request_id;		/* unique req id for tracing */
extern unsigned long	volklog_seqno;		/* sequence number for unique
						   log block identification */

extern dev_t		vol_rootvol_dev;	/* underlying root volume dev */
extern dev_t		vol_swapvol_dev;	/* underlying swap volume dev */

/*
 * Declaration of plex layout switch table. For each plex layout
 * the routines in the switch table are used to do plex layout
 * specific functions.
 */

struct plexsw {
	int	(*pl_strategy)();	/* 0x0 */
	int	(*pl_mapped)();		/* 0x4 */
};					/* 0x8 */

extern struct plexsw	plexsw[];	/* plex layout specific switch table */

extern int		nulldev();
extern int		nodev();

/*
 * The following are error returns from the volcheck function used as part
 * of the TED instrumented testing.
 */
#if defined(TED_ACTIVE)

#define	TED_NOVOL	0x0000001	/* couldn't find volume */
#define	TED_NOTVOL	0x0000002	/* couldn't find temp volume */
#define	TED_VHASHLNK	0x0000004	/* volume hash linkage error */
#define	TED_PVLNK	0x0000008	/* plex to volume linkage error */
#define	TED_PPREV	0x0000010	/* previous plex error */
#define	TED_PHASHLNK	0x0000020	/* plex hash linkage error */
#define	TED_PNUM	0x0000040	/* plex number error */
#define	TED_SVLNK	0x0000080	/* subdisk to volume linkage error */
#define	TED_SPLNK	0x0000100	/* subdisk to plex linkage error */
#define	TED_SHASHLNK	0x0000200	/* subdisk hash linkage error */
#define	TED_STOOLONG	0x0000400	/* subdisk exceeds end of volume */
#define	TED_SLEN	0x0000800	/* subdisk length inconsistancy */
#define	TED_SOVRLP	0x0001000	/* subdisk overlap error */
#define	TED_LSPOS	0x0002000	/* logging subdisk positional error */
#define	TED_SPNAM	0x0004000	/* incorrect subdisk plex name */
#define	TED_PSCNT	0x0008000	/* plex subdisk count incorrect */
#define	TED_SFEW	0x0010000	/* insufficient subdisks for striping */
#define	TED_PSPARSE	0x0020000	/* sparse striping plex */
#define	TED_PWIDTH	0x0040000	/* invalid plex stripe width */
#define	TED_SWIDTH	0x0080000	/* subdisk not stripe width multiple */
#define	TED_PENASCNT	0x0100000	/* too few subdisks for enabled plex */
#define	TED_LVSCNT	0x0200000	/* logging vol with no log subdisks */
#define	TED_PTOOMUCH	0x0400000	/* excessive plexes */
#define	TED_STOOMUCH	0x0800000	/* excessive subdisks */

#endif /* TED_ACTIVE */


/*
 * Following structures are moral equivalents for the volcb and volbuf structs.
 * volklogcb is the I/O control block for all logging operations. Only one 
 * instance of this structure exists since all logging operations are performed
 * synchronously. The volklogbuf structure is the wrapper for a buf
 * structure so the interrupt routine can find its way back to the volklogcb
 * structure.
 */
struct volklogcb {
	int			vkb_active;	/* 0x00 active I/O count */
	struct volklogbuf	*vkb_actbuf;	/* 0x04 active I/O list */
	int			vkb_errors;	/* 0x08 count of I/O errors */
	struct volspin		vkb_spin;	/* 0x0c spinlock for struct */
	struct volsync		vkb_sync;	/* 0x18 synclock for struct */
};						/* 0x20 */

struct volklogbuf {
	struct buf		vk_buf;		/* 0x00 buffer for disk I/O */
	struct volklogbuf	*vk_next;	/* 0x64 next volbuf in list */
	struct volklogcb	*vk_volkcb;	/* 0x68 volklogcb struct */
	struct volklogcopy	*vk_vlcp;	/* 0x6c vollogcopy struct */
	struct volklogarea	*vk_klap;	/* 0x70 log area for this buf */
};						/* 0x74 */


/*
 * This is the kernel's internal disk-group structure
 */
struct diskgroup {
	struct volkdg		dg_kdg;		/* 0x00 external group struct */
	struct diskgroup 	*dg_next;	/* 0x6c diskgroup disk list */
	struct voldisk		*dg_disks;	/* 0x70 list of group's disks */
	struct volume		*dg_pendvol;	/* 0x74 pending volumes list */
	struct volume		*dg_curvol;	/* 0x78 current volumes list */
	struct volkdglog	*dg_klog;	/* 0x7c log control structure */
	int			dg_nklog;	/* 0x80 number of log sectors */
	struct volklogcb	dg_volkcb;	/* 0x84 logging control blk */
	int			dg_commit_off;	/* 0xa4 commit record offset */
	struct volsleep		dg_klog_sleep;	/* 0xa8 logging sleep lock */
	struct volspin		dg_spin;	/* 0xb4 diskgroup spin lock */
};						/*  */

#define	dgc_uuid	dg_kdg.kdg_uuid
#define	dgc_rid		dg_kdg.kdg_rid
#define	dgc_name	dg_kdg.kdg_name
#define	dgc_kflag	dg_kdg.kdg_kflag
#define	dgc_config_tid	dg_kdg.kdg_config_tid

/*
 * This is the kernel's internal disk structure
 */

struct voldisk {
	struct volkdisk		d_kd;		/* 0x000 external disk struct */
	struct voldisk		*d_next;	/* 0x0e4 next global disklist */
	struct diskgroup 	*d_dg;		/* 0x0e8 assoc disk group */
	ulong_t			d_flags;	/* 0x0ec disk flags */
	uint			d_opencnt;	/* 0x0f0 # of open subdisks */
	uint			d_refcnt;	/* 0x0f4 # of referenced sd's */
	struct volklogcopy	*d_logtab;	/* 0x0f8 ptr to log area tbl */
	int			d_nlogtab;	/* 0x0fc # d_logtab entries */
	struct volspin		d_spin;		/* 0x100 spinlock for disk */
	struct disk_stat	d_stats;	/* 0x10c stats for disk */
#ifdef __alpha
	struct vnode 		*d_pub_vp;	/* 0x12c disk pub vp */
	struct vnode 		*d_priv_vp;	/* 0x130 disk priv vp */
};						/* 0x134 */
#else /* !__alpha */
};						/* 0x12c */
#endif /* __alpha */

#define dc_devname	d_kd.kd_devname
#define dc_name		d_kd.kd_name
#define dc_rid		d_kd.kd_rid
#define dc_dgrid	d_kd.kd_dgrid
#define dc_dmrid	d_kd.kd_dmrid
#define dc_kflag	d_kd.kd_kflag
#define dc_sflag	d_kd.kd_sflag
#define dc_vflag	d_kd.kd_vflag
#define dc_pub_dev	d_kd.kd_pub_dev
#define dc_priv_dev	d_kd.kd_priv_dev
#define dc_pub_len	d_kd.kd_pub_len
#define dc_priv_len	d_kd.kd_priv_len
#define dc_type		d_kd.kd_type
#define dc_info		d_kd.kd_info
#ifdef __alpha
#define dc_pub_path	d_kd.kd_pub_path
#define dc_priv_path	d_kd.kd_priv_path
#endif /* __alpha */

extern struct diskgroup		*voldghead;	/* disk group list */
extern struct volspin		voldghead_spin;	/* disk group list spin lock */
extern struct volktranstate	volkstate;	/* transaction state */
extern struct volspin		volkstate_spin;	/* trans state spin lock */
extern struct diskgroup		*trans_dgp;	/* dg for transaction */
extern struct diskgroup		nulldg;		/* the null disk group */
extern int			vol_config_loaded; /* config loaded flag */

#define	VOLFIND_PEND	1	/* lookup pending configuration */
#define VOLFIND_CUR	2	/* lookup current configuration */

/*
 * The following are the structures for kernel logging
 */

#define VOL_KLOG_ALLOCSLOT	-1	/* A new log slot needs to be
					   allocated */
#define VOL_KLOG_NO_OFFSET	-1	/* The offset is not valid */
#define VOL_KLOG_LOGERR		-1	/* The log is full, or no valid
					   offset is available */
#define VOL_KLOGOP_LOG		0x01	/* log entry */
#define VOL_KLOGOP_CLEAR	0x02	/* clear log entry */
#define VOL_KLOGOP_FLUSH	0x04	/* flush all dirty entries in the log */
#define VOL_KLOGOP_FLUSHALL	0x08	/* flush all entries in the log */
#define VOL_KLOGOP_ASYNC	0x80	/* do not write out changed log */

/*
 * The following union forms the content of each entry in the disk log.
 * This union is used for the interface between the caller of the logging
 * code and the internal code. Once the entry has been passed into the logging
 * routine, then it is converted into the network independant format as it will
 * be stored on disk.
 */
union volklogent {
	char		le_logtype;		/* 0x00 type of log entry */
	struct {
		char		rle_logtype;	/* 0x00 type of log entry */
		volrid_t	rle_rid;	/* 0x04 object ID */
		volseqno_t	rle_config_id;	/* 0x08 config ID of op */
	}		le_record;		/* 0x0c */
	struct {
		char		cle_logtype;	/* 0x00 type of log entry */
		volseqno_t	cle_old_conf_id; /* 0x04 old configuration ID */
		volseqno_t	cle_new_conf_id; /* 0x08 new configuration ID */
	}		le_commit;		/* 0x0c */
	char		le_filleur[24];		/* 0x00 size of each entry */
};

#define le_rid		le_record.rle_rid
#define le_config_id	le_record.rle_config_id
#define le_oconfig_id	le_commit.cle_old_conf_id
#define le_nconfig_id	le_commit.cle_new_conf_id

struct volkdglog {
	struct volkdglog	*dgl_next;	/* 0x000 next log blk in list */
	struct volkdglog	*dgl_prev;	/* 0x004 prev log blk in list */
	int			dgl_dirty;	/* 0x008 dirty status flag */
	int			dgl_nused;	/* 0x00c # of in-use entries */
	unsigned char		dgl_blk[NBPSCTR]; /* 0x010 The log block */
};						/* 0x210 */

/*
 * The following states are the values that are valid for the dl_state
 * element of the voldisklog structure that follows.
 */
enum volcpystate {
	VOL_KLOG_NOLOG,		/* no log copy allocated here */
	VOL_KLOG_VALID,		/* log is valid */
	VOL_KLOG_IOERR		/* log has had an I/O error */
};

/*
 * An array of the following structures is pointed to by each disk
 * structure.
 * The structure contains a description of each instance or copy of the
 * log on disk.
 */
struct volklogcopy {
	struct volklogarea	*vl_klogareap;	/* 0x00 ptr to log area table */
	int			vl_nklogarea;	/* 0x04 size of table */
	enum volcpystate	vl_state;	/* 0x08 state of the log */
	struct volklogbuf	vl_vklb;	/* 0x0c buffer for log ops */
};						/* 0x80 */

#endif 	/* _SYS_VOLKERN_H */
