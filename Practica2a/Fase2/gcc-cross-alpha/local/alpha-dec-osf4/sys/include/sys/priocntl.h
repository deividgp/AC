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
 * @(#)$RCSfile: priocntl.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1995/03/23 18:42:26 $
 */

#ifndef _SYS_PRIOCNTL_H_
#define _SYS_PRIOCNTL_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#if (defined(__STDC__) || defined (__cplusplus)) && !defined(_KERNEL)
#include <sys/procset.h>
#endif

#define	PC_CLNULL	(-1)	/* used for getting information about just
				   a single process with PC_GETPARMS */

#define	PC_CLNMSZ	8	/* maximum size for a scheduling class name */
#define	PC_CLINFOSZ	8	/* size of the class-specific information
				   buffer (in longs) */
#define	PC_CLPARMSZ	8	/* size of the class-specific parameters
				   buffer (in longs) */

typedef struct 
{
	id_t		pc_cid;			/* Class id */
	char		pc_clname[PC_CLNMSZ];	/* Class name */
	long		pc_clinfo[PC_CLINFOSZ];	/* Class information */
} pcinfo_t;

typedef struct
{
	id_t		pc_cid;			/* Process class */
	long		pc_clparms[PC_CLPARMSZ]; /* Class-specific params */
} pcparms_t;

/*
 * priocntl() commands
 */
#define	PC_GETCID	1
#define	PC_GETCLINFO	2
#define	PC_SETPARMS	3
#define	PC_GETPARMS	4
#define PC_ADMIN	5

#ifndef _KERNEL
extern long priocntl __((idtype_t, id_t, int, ...));
extern long priocntlset __((procset_t *, int, ...));
#else
struct proc;  /* stub to avoid warnings */
extern id_t class_id __((struct proc *));
extern int class_valid __((id_t));
extern int is_class_member __((struct proc *, int));
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif
#endif /* _SYS_PRIOCNTL_H_ */
