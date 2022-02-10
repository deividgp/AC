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
 * @(#)$RCSfile: utmpx.h,v $ $Revision: 1.1.4.6 $ (DEC) $Date: 1995/12/12 19:04:08 $
 */
#ifndef _UTMPX_H_
#define _UTMPX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#include <sys/types.h>  /* for pid_t, time_t */
#include <sys/time.h>

/*
 * Structure of utmpx.
 *
 */

struct utmpx {
        char    ut_user[32];            /* User login name */
        char    ut_id[14];              /* /etc/inittab id- IDENT_LEN in init */
        char    ut_line[32];            /* device name (console, lnxx) */
        pid_t   ut_pid;                 /* process id */
        short   ut_type;                /* type of entry */
        struct 	timeval ut_tv;		/* Time entry was made */
        struct  {
            short	ut_termination;	/* Process termination status */
            short	ut_exit;	/* Process exit status */
        } ut_exit;			    /* The exit status of a process
                                 * marked as DEAD_PROCESS.
                                 */
        char	ut_host[64];		/* host name same as MAXHOSTNAMELEN */
};


/* Definitions for ut_type                                              */

#define EMPTY           0	/* no valid user accounting information */
#define RUN_LVL         1
#define BOOT_TIME       2	/* time of system boot */
#define OLD_TIME        3	/* time when the system time clock changed */
#define NEW_TIME        4	/* time after system clock changed */
#define INIT_PROCESS    5       /* Process spawned by "init" */
#define LOGIN_PROCESS   6       /* A "getty" process waiting for login */
#define USER_PROCESS    7       /* A user process */
#define DEAD_PROCESS    8	/* a session leader who has exited */

#ifdef _OSF_SOURCE
#define ACCOUNTING      9
#endif

extern struct utmpx     *getutxent __((void));
extern struct utmpx     *getutxid __((const struct utmpx *));
extern struct utmpx     *getutxline __((const struct utmpx *));
extern struct utmpx     *pututxline __((const struct utmpx *));
extern void             setutxent __((void));
extern void             endutxent __((void));

#ifdef __cplusplus
}
#endif

#endif  /* _UTMPX_H_ */
