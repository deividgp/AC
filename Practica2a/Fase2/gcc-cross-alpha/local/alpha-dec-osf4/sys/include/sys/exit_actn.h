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
 * @(#)$RCSfile: exit_actn.h,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 1995/03/01 18:45:28 $
 */

#ifndef	_SYS_EXIT_ACTN_H_
#define _SYS_EXIT_ACTN_H_

#ifdef _KERNEL

/*
 *	The exit_actn struct.
 *	These structures are dynamically allocated and chained onto
 *	the u area to indicate kernel functions to be called before
 *	process exit and exec. See ../bsd/kern_exit.c & kern_exec.c.
 */
struct exit_actn {
	struct exit_actn *xa_next;
	void 		 (*xa_func)();
	void		 *xa_arg;
	int		 xa_flags;
};

/*
 * Kernel Exit/Exec handler flags.
 */
#define XA_EXIT   0x1	/* call on EXIT */
#define XA_EXEC   0x2	/* call on EXEC */
#define XA_KOE	  0x4	/* keep on EXEC */
#define XA_ABORT  0x8	/* abort EXEC call */
#define XA_NOWAIT 0x10 	/* don't sleep on memory allocation */
#define XA_SYSTEM 0x20	/* call for every process exit */

#define XA_LOCK_WRITE()	lock_write(&sys_exitp_lock)
#define XA_LOCK_READ()	lock_read(&sys_exitp_lock)
#define XA_UNLOCK()	lock_done(&sys_exitp_lock)

extern lock_data_t sys_exitp_lock;
extern struct exit_actn *xa_handler_register(void *, void *, int);
extern int xa_handler_unregister(void *, void *, int);
extern int xa_handler_callout(int);
extern void *xa_handler_lookup(void *, void *, int, void *);
extern void xa_lock_init(void);

#endif /* _KERNEL */
#endif	/* _SYS_EXIT_ACTN_H_ */

