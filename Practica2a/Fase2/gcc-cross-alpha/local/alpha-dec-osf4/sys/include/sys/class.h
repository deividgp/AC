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
#pragma ident "@(#)$RCSfile: class.h,v $ $Revision: 1.1.4.4 $ (DEC) $Date: 1997/07/14 22:16:15 $"

#include <sys/msg.h>

#define MAX_NUM_CLASSES		128
#define MAX_NUM_MEMBERS		(128 * 20)

/*
 * class_sched_status codes.
 */
#define CL_STATE_DISABLED		0
#define CL_STATE_ENABLED		1

/*
 * classcntl() opcodes.
 */

#define CL_OP_ENABLE		0
#define CL_OP_DISABLE		1
#define CL_OP_GET_CLASS_LIST	2
#define CL_OP_ADD_TO_CLASS	3
#define CL_OP_DEL_FROM_CLASS	4
#define CL_OP_SET_CLASS_LIST	5
#define CL_OP_DAEMON_ALIVE	6
#define CL_OP_UNUSED		7
#define CL_OP_IS_ENABLED	8
#define CL_OP_GET_PID_CLASS	9

/* 
 * class member type codes.
 */
#define CL_TYPE_RESERVED	0
#define CL_TYPE_GID		1
#define CL_TYPE_UID		2
#define CL_TYPE_UNUSED		3
#define CL_TYPE_ALL		4
#define CL_TYPE_PGRP		5
#define CL_TYPE_SESS		6
#define CL_TYPE_PID		7
#define CL_TYPE_HIGHEST		7

#ifndef _KERNEL

#define NAME_LEN		20
#define AVAIL			0

#define DEFAULT_DAEMON_RATE	1
#define CLASS_FILE_NAME		"/etc/class"
#define CLASS_FILE_ID		'a'
#define CLASS_DAEMON_NAME	"/usr/sbin/class_daemon"

#define CLASS_AVAIL   "available"
#define CLASS_DEFAULT "default"
#define CLASS_DEFAULT_INDEX 	1
 
struct class_member {
	short 	type;		/* group, user, session etc. */
	short	external;	/* entry made by other than the admin program */
	int 	id;
	int	next_member;
	int	prev_member;
};
 
struct class_member_info {
	short 	type;		/* group, user, session etc. */
	int 	id;
};

struct class {
	char	name[NAME_LEN];
	int	target_percent;
	int	actual_percent;
	int	num_members;
	int	first_member;
	int	last_member;
};

struct class_info {
	char	name[NAME_LEN];
	int	target_percent;
	int	actual_percent;
	int	num_members;
};

struct class_head {
	int all_threads;
	int daemon_rate;
        int first_class_in_use;
        int enforce_when_idle;
	int dirty;
	int first_empty;
	int last_empty;
	int reserved[5];			/* future expansion */
	struct class class[MAX_NUM_CLASSES];
	struct class_member	member[MAX_NUM_MEMBERS];
};

struct msg_buf {
	mtyp_t mtype;
	struct mtext {
		int type;	/* CL_TYPE_GID or CL_TYPE_UID */
		long value;
		pid_t pid;
	}mtext;
};


/* ask_yes_no() return codes */
#define ANSWER_NO		0
#define ANSWER_YES		1
#define ANSWER_UNCHANGED	2

/* class_xxx option codes (bit mask) */
#define OPT_DONT_FORCE	1
#define OPT_FORCE	2
#define OPT_EXTERNAL	4

/* function prototypes */

int 	class_add(char *, int, int, int);
int	class_change(char *, int, int *);
int	class_create(char *, int, int *);
int 	class_init(void);
int 	class_close(void);
int 	class_configure(int, int, int);
int	class_get_config_stats(int *, int *, int *);
int	class_delete(char *, int, int);
int	class_delete_entry(struct class_head *, int, int);
int	class_destroy(char *, int);
int	class_disable(void);
int	class_enable(void);
int 	class_save_database(void);
int	class_restore_database(void);
int	class_change_name(char *, char *);
int	class_database_file_exists(void);
int	class_database_modified(void);
int	class_scheduling_enabled(void);
int	class_open(void);
int	class_get_classes(struct class_info *);
int	class_get_class_members(char *, struct class_member_info *);
int	class_notify_kernel(void);
void	class_database_lock(void);
void	class_database_unlock(void);
void	class_error(char *, int);

/*
 * libclass error codes
 * The library (libclass) has strings to go with the -error codes.
 *	extern char *class_err_string[];
 */

#define CLASS_SUCCESS			0
#define CLASS_FILE_FAILURE		-1
#define CLASS_SHARED_MEM_FAILURE	-2
#define CLASS_SEMAPHORE_FAILURE		-3
#define CLASS_NO_DATABASE		-4
#define CLASS_CLASS_NOT_EXIST		-5
#define CLASS_CLASS_NOT_EMPTY		-6
#define CLASS_MEMBER_ALREADY_IN_CLASS	-7
#define CLASS_MEMBER_IN_OTHER_CLASS	-8
#define CLASS_MEMBER_NOT_IN_CLASS	-9
#define CLASS_NO_SPACE			-10
#define CLASS_TOO_HIGH_PERCENT		-11
#define CLASS_NAME_IN_USE		-12
#define CLASS_NAME_INVALID		-13
#define CLASS_ALREADY_ENABLED		-14
#define CLASS_NOT_ENABLED		-15
#define CLASS_DAEMON_FAIL		-16
#define CLASS_NOT_INITIALIZED		-17
#define CLASS_NOT_SUSER			-18
#define CLASS_MSG_SETUP_FAIL		-19
#define CLASS_MSG_RCV_FAIL		-20
#define CLASS_DEFAULT_CLASS_OP		-21
#define CLASS_LAST_ERROR		-21

#endif /* !_KERNEL */
