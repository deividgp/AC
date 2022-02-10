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
 * @(#)$RCSfile: sysaio.h,v $ $Revision: 1.1.31.2 $ (DEC) $Date: 1998/08/25 19:34:58 $
 */

#ifndef _SYS_SYSAIO_H_
#define _SYS_SYSAIO_H_

#include <standards.h>

#include <sys/types.h>
#include <sys/signal.h>
#include <sys/limits.h>
#include <sys/time.h>
#include <sys/buf.h>
#ifdef _KERNEL
#include <sys/siginfo.h>
#include <kern/thread.h>
#include <kern/lock.h>
#endif

/*
 * Define the blocking lock around the checking and setting of
 * aio_init_done for thread safety at initialization.
 */
struct aiolock {
	int semstate;	/* State of the lock -- locked or unlocked */
	int semncnt;	/* Number of processes blocked waiting for */
};             		/* the lock */

typedef struct aiolock aiolock_t;

/*
 * define the AIO/LIO constants
 */

#define AIO_CANCELED 	0	/* all operations cancelled */
#define AIO_NOTCANCELED 1	/* not all operations cancelled */
#define AIO_ALLDONE 	2	/* all operations were completed */

#define LIO_WAIT 	1	/* wait for all operations to complete */
#define LIO_SUSPEND 	2	/* wait for any to complete, no signal */
#define LIO_NOWAIT 	3	/* don't wait for completion, signal */

#define LIO_READ 	4
#define LIO_WRITE 	5
#define LIO_GROUP 	6	/* wait for group completion */
#define LIO_FDATASYNC   7       /* aio_fsync() with O_DSYNC */
#define LIO_FSYNC       8       /* aio_fsync() with O_SYNC */
#define LIO_NOP 	0

/*
 * Macros to pack and unpack aio key values
 */
#define AIO_SET_IDX(key, idx) (key) = \
	((int)((unsigned)(key) & 0xFFFF0000) | (short)(idx))
#define AIO_SET_SEQ(key, seq) (key) = \
	((int)((unsigned)(key) & 0x0000FFFF) | ((short)(seq) << 16))
#define AIO_GET_IDX(key) 	((int)(0x0000FFFF & (unsigned)(key)))
#define AIO_GET_SEQ(key)	((int)((unsigned)(key) >> 16))

/*
 * aio key type
 */
typedef unsigned int aio_key_t;	/* key/id for an aio */

#ifdef _KERNEL

#define AIO_SOCK_LOCK_INIT(abp)	simple_lock_setup(&(abp)->ab_lock, \
							aio_socket_lockinfo)
/*
 * aio socket specific macros also used by uipc_socket.c.
 */
extern decl_simple_lock_data(,aio_socket_lock)
extern decl_simple_lock_info(,aio_socket_info)
#define AIO_SOCK_LOCK_INIT(abp) simple_lock_setup(&(abp)->ab_lock, \
							aio_socket_lockinfo)
#define AIO_SOCK_LOCK(bp)	simple_lock(&(abp)->ab_lock)
#define AIO_SOCK_UNLOCK(bp)	simple_unlock(&(abp)->ab_lock)

typedef struct aio_buf {
        struct buf      	ab_buf;
        size_t            	ab_requested;
	struct aio_superbuf 	*ab_sbuf;
	struct file		*ab_fp;
        aio_key_t       	ab_key;
	decl_simple_lock_data(,ab_lock)
} aio_buf_t;

/*
 * aiocb: represents one AIO request at the user level
 */
typedef struct aiocb_old {
	int 		aio_fildes;
	off_t 		aio_offset;
	volatile void 	*aio_buf;
	size_t 		aio_nbytes;
	int  		aio_reqprio;
	sigevent_event_t aio_sigevent;
	int 		aio_lio_opcode;
  	/* implementation extensions */
  	struct aiocb 	*aio_next;
	aio_key_t	aio_key;	
	int		aio_reserved[8];
} aiocb_old_t;

#endif /* _KERNEL */

typedef struct aiocb {
	int 		aio_fildes;
	aio_key_t	aio_key;
	off_t 		aio_offset;
	volatile void 	*aio_buf;
	size_t 		aio_nbytes;
	int  		aio_reqprio;
	int 		aio_lio_opcode;
  	/* begin implementation extensions */
  	struct aiocb 	*aio_next;
	long		aio_reserved;
  	/* end implementation extensions */
	struct sigevent aio_sigevent;
} aiocb_t;

typedef struct aio_completion {
	struct aiocb 	*aio_aiocb;
	ssize_t		aio_result;
	int		aio_error;
} aio_completion_t;

/*
 * aio_result_block:
 *	the list of result blocks is double mapped between user and
 *	kernel space. There is one result block for each outstanding
 *	aio request. The block is allocated by aio_read/write and
 *	released by aio_return.
 */
typedef struct aio_result_block {
	int			rb_idx;
	volatile aio_key_t	rb_key;
	int			rb_fd;
	pid_t			rb_pid;
	volatile int		rb_errno;
	volatile size_t		rb_result;
#ifdef _KERNEL
	sigqueue_t		rb_sigqueue;
	aiocb_t			*rb_aiocb;
#else
	long			pad[2];
#endif
	int			rb_driver;
	unsigned int		rb_time;
#ifdef _KERNEL
        struct proc		*rb_proc;
	struct aio_test		*rb_test_list;
	struct aio_test_hdr	*rb_thdr;
#else
        void			*rb_proc;
	void			*rb_test_list;
	void			*rb_thdr;
#endif
} *aio_result_t;

typedef union {
	int		_preempt[2];
	long		_preempt_long;
} aio_preempt_t;

typedef struct aio_group {
	union {
		aio_preempt_t	_preempt_un;
		char		_pad1[64];
	} _aio_preempt_un;
	union {
		volatile int	_kindex;
		char		_pad1[64];
	} _aio_unk;
	union {
		struct {
			volatile int	_uindex;
			volatile int	_ugen;
		} _aio_unu_s;
		volatile long	_udata;
		char		_pad2[64];
	} _aio_unu;
	aio_completion_t	aio_results[1];
} aio_group_t;

#define aio_preempt_off _preempt[0]
#define aio_yield _preempt[1]
#define aio_preempt_long _preempt_long
#define aio_preempt _aio_preempt_un._preempt_un._preempt_long

#define aio_kindex _aio_unk._kindex
#define aio_uindex _aio_unu._aio_unu_s._uindex
#define aio_ugen _aio_unu._aio_unu_s._ugen
#define aio_udata _aio_unu._udata

#define AIOG_HDRSIZE (sizeof(aio_group_t) - sizeof(aio_completion_t))

#endif /* _SYS_SYSAIO_H_ */
