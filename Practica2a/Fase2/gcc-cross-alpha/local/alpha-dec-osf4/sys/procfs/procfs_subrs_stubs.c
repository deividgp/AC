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
#pragma ident "@(#)$RCSfile: procfs_subrs_stubs.c,v $ $Revision: 1.1.6.4 $ (DEC) $Date: 1997/09/12 15:52:56 $"

#include <kern/thread.h>
#include <kern/task.h>
#include <procfs/procfs_l.h>

/*
 * Prototypes for the routines below are in procfs_l.h.
 */

/*ARGSUSED*/
void
procfs_child_inherit(task_t task1, task_t task2, thread_t th, boolean_t flag)
{
}

/*ARGSUSED*/
void
procfs_exit(task_t task, int rv)
{
}

/*ARGSUSED*/
void
procfs_release(task_t task)
{
	if(task->procfs.pr_exvp != NULLVP) {
		vrele(task->procfs.pr_exvp);
		task->procfs.pr_exvp = NULLVP;
	}
}
    
/*ARGSUSED*/
void
procfs_exec_trace(struct proc *p, struct vnode  *vp, int flag)
{
}

/*ARGSUSED*/
void
procfs_trace_signals(struct proc *p, int *lock_freed, int sig)
{
}

/*ARGSUSED*/
int
procfs_new_thread(thread_t new_thread, task_t parent_task, int *th_create_stop)
{
	return(KERN_SUCCESS);
}

/*ARGSUSED*/
void
procfs_stop_new_thread(task_t parent_task, thread_t new_thread)
{
}

/*
 * Called fron thread_terminate().
 */
/*ARGSUSED*/
void
procfs_thread_terminate(task_t cur_task, thread_t thread)
{
}

/*ARGSUSED*/
int
procfs_syscall_start(thread_t t, task_t task, u_long code,
		     int nargs, long *args, boolean_t indirect_syscall)
{
	return(0);
}

/*ARGSUSED*/
int
procfs_syscall_finish(thread_t t, task_t task, u_long code)
{
	return(0);
}

/*ARGSUSED*/
int
procfs_trap(task_t task, thread_t t, u_long code,
	    u_long exc_subcode, k_siginfo_t *sip)
{
	return(0);
}

/*ARGSUSED*/
void
procfs_ast_stop(void)
{
	return;
}

/*ARGSUSED*/
boolean_t
procfs_trace_busy(task_t task, boolean_t nowait)
{
	return TRUE;
}

/*ARGSUSED*/
void
procfs_trace_free(task_t task)
{
}

/*ARGSUSED*/
void
procfs_trace_event(procfs_event_t event,
		   task_t target_task,
		   thread_t target_thread,
		   void *extra)
{
}
