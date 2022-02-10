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
 * @(#)$RCSfile: fifonode.h,v $ $Revision: 1.1.9.3 $ (DEC) $Date: 1995/12/18 22:56:51 $
 */
/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#ifndef _SYS_FIFONODE_H_
#define _SYS_FIFONODE_H_

#ifdef	_KERNEL

struct fifonode {
	udecl_simple_lock_data(,fn_fifo_lock)
	struct fifo_bufhdr *fn_buf;	/* ptr to first buffer */
	struct fifo_bufhdr *fn_bufend;	/* ptr to last buffer */
	struct vnode	*fn_vp;		/* ptr to vnode */
	union { /* process selecting read/write */
		struct proc *fifo_selproc;        /* UNIX */
		struct fifoselque {               /* MACH */
			struct fifoselque *next, *prev;
		} fifo_selque;
	} fifo_select;
	u_long		fn_flag;	/* (see fifo.h) */
	int		fn_wtimer;	/* Write timer is set */
	int		fn_rtimer;	/* Read timer is set */
	boolean_t	fn_wbadbolt;
	boolean_t	fn_rbadbolt;
	long		fn_wlbolt;	/* Number of ticks between lbolts */
	long		fn_rlbolt;	/* Number of ticks between lbolts */
	off_t		fn_wworksize_sv;
	off_t		fn_rworksize_sv;
	off_t		fn_wworksize;
	off_t		fn_rworksize;
	pid_t		fn_rpgrp;       /* process group of read side */
        pid_t		fn_wpgrp;       /* process group of write side */
	off_t		fn_size;	/* number of bytes in fifo */
	off_t		fn_wptr;	/* write offset */
	off_t		fn_rptr;	/* read offset */
	u_long		fn_nbuf;	/* number of buffers allocated */
	lock_data_t     fn_rdio_lock;     /* reading/writing fifo's contents */
	int		fn_write_gate_closed;
	struct pipenode {
		struct timeval  atime;       /* time of last access */
		struct timeval  mtime;       /* time of last modification */
		struct timeval  ctime;       /* time file changed */
	} pipenode;
	int		fn_fileid;	/* Used by stat */
};

#define fn_sel          fifo_select.fifo_selproc
#define fn_selq         fifo_select.fifo_selque
#define pn_atime	pipenode.atime
#define pn_mtime	pipenode.mtime
#define pn_ctime	pipenode.ctime

/* bits in fn_flag in fifonode */
#define FIFO_RBLK	0x00001	/* blocked readers */
#define FIFO_WBLK	0x00002	/* blocked writers */
#define FIFO_WASYNC	0x00010	/* SIGIO enabled for write side */
#define FIFO_RASYNC	0x00020	/* SIGIO enabled for read side */
#define FIFO_SPARE1	0x00040	/* Spare */
#define FIFO_SPARE2	0x00080	/* Spare */
#define FIFO_RDLEARN	0x00100	/* Read learn mode */
#define FIFO_WRLEARN	0x00200	/* Write learn mode */
#define FIFO_RDNOPROG	0x00400	/* Read learn mode - No progress */
#define FIFO_WRNOPROG	0x00800	/* Write learn mode - No progress */
#define PIPE_UPD	0x01000	/* pipe has been modified */
#define PIPE_ACC	0x02000	/* pipe access time to be updated */
#define PIPE_CHG	0x04000	/* pipe has been changed */
#define PIPE_SPARE1	0x08000	/* Spare */
#define PIPE_WGATE_WAIT	0x10000 /* waiting for write gate to open */


#define PIPE_TIMES(fn)	{ \
		 if ((fn)->fn_flag & PIPE_ACC) { \
			 (fn)->pn_atime.tv_sec = time.tv_sec; \
			 (fn)->pn_atime.tv_usec = time.tv_usec; \
		 } \
		 if ((fn)->fn_flag & PIPE_UPD) { \
			 (fn)->pn_mtime.tv_sec = time.tv_sec; \
			 (fn)->pn_mtime.tv_usec = time.tv_usec; \
		 } \
		 if ((fn)->fn_flag & PIPE_CHG) { \
			 (fn)->pn_ctime.tv_sec = time.tv_sec; \
			 (fn)->pn_ctime.tv_usec = time.tv_usec; \
		 } \
		 (fn)->fn_flag &= ~(PIPE_ACC|PIPE_UPD|PIPE_CHG); \
	  }

/* Locks */

/*
 * The fn_io_lock sleep lock allows multiple readers in the fifo_read()
 * routine, although only one reader can be active at a time. (fifo
 * semantics). This locks also provides exclusive access to the fifo
 * for writers in fifo_write().
 */

extern struct lockinfo *fifo_rdio_lockinfo;

#define FIFO_RDIO_LOCK_INIT(fn)     lock_setup(&(fn)->fn_rdio_lock,\
					      fifo_rdio_lockinfo, TRUE)

/*
 * Note : The structure of these locks allow one reader and one
 *	  writer to operate on a fifo at the same time.
 */
#define FIFO_READ_LOCK(fn)        lock_write(&(fn)->fn_rdio_lock)
#define FIFO_READ_UNLOCK(fn)      lock_write_done(&(fn)->fn_rdio_lock)

/*
 * The fn_fifo_lock spin lock protects all fields in the fifonode
 * structure.
 */
udecl_simple_lock_info(extern, fifo_lockinfo)

#define FIFO_LOCK_INIT(fn)        usimple_lock_setup(&(fn)->fn_fifo_lock,\
						    fifo_lockinfo)

#define FIFO_LOCK(fn)             usimple_lock(&(fn)->fn_fifo_lock)
#define FIFO_UNLOCK(fn)           usimple_unlock(&(fn)->fn_fifo_lock)


/*
 * Convert between fifonode, snode, and vnode pointers
 */
#define VTOF(vp)        ((struct fifonode *)(vp)->v_fifonode)

#endif	/* _KERNEL */
#endif	/* _SYS_FIFONODE_H_ */
