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
 * @(#)$RCSfile: execargs.h,v $ $Revision: 1.1.5.4 $ (DEC) $Date: 1995/01/25 18:50:59 $
 */

#ifndef _SYS_EXECARGS_H_
#define _SYS_EXECARGS_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/auxv.h>
#include <mach/alpha/vm_types.h>

/*
 * Argument block structure
 */
struct execargs {
	vm_offset_t	argsmem;/* pointer to memory allocated for args */
	vm_offset_t	args;	/* pointer to arg/env space */
	int		na;	/* number of args */
	int		ne;	/* number of env variables */
	unsigned	nc;	/* character count (aligned) */
	int		ni;	/* number of interpreter args */
	int		cc;	/* arg space left */
	char		*ufile;	/* location of program name in `args' */
	char		*loader; /* location of loader in `args' */
	char		*interp; /* location of interpreter info in `args' */
	kauxv_t		*auxv;	/* auxv structure */
	vm_offset_t	envp;	/* pointer to env space */
	unsigned	nac;	/* char count for args */
};

/*
 * Arg operations
 */
#define EXARG_PREPEND		0x1
#define EXARG_APPEND		0x2
#define EXARG_MOD		0x4

/*
 * Arg pieces to operate on
 */
#define EXARG_ARGS		0x10
#define EXARG_ENV		0x20
#define EXARG_UFILE		0x40
#define EXARG_LOADER		0x80
#define EXARG_SHELL		0x100
#define EXARG_SHARGS		0x200

/*
 * Auxv operations
 */
#define EXARG_AUXADD		0x1000
#define EXARG_AUXDEL		0x2000
#define EXARG_AUXMOD		0x4000

/*
 * Maximum number of auxv elements an exec can use.
 */
#define	MAX_EXEC_AUXV		5

/*
 * Prototypes for execargs manipulation functions.
 */

extern int exec_args_copyin(
	char *,			/* fname */
	char **,		/* uargp */
	char **,		/* uenvp */
	char *,			/* uloader */
	struct execargs *);	/* argbkp */
extern int exec_args_copyout(
	struct execargs *,	/* argbkp */
	char *,			/* loader */
	int);			/* flags */
extern vm_offset_t exec_args_allocate(void);
extern void exec_args_free(struct execargs *);
extern kauxv_t *exec_auxv_alloc(void);
extern void exec_auxv_dealloc(kauxv_t *);
extern int exec_auxv_operate(
	struct execargs *,	/* argbkp */
	int,			/* op */
	int,			/* type */
	union auxv_data *);	/* data */
extern int exec_copystr(
	char *,		/* src */
	char **,	/* destp */
	int *,		/* maxlengthp */
	unsigned *,	/* lencopiedp */
	unsigned *);	/* ncp */
extern int exec_copyinstr(
	caddr_t,	/* user_src */
	char **,	/* kernel_destp */
	int *,		/* maxlengthp */
	unsigned *,	/* lencopiedp */
	unsigned *);	/* ncp */
extern int exec_copyoutstr(
	char **,	/* kernel_srcp */
	caddr_t,	/* user_dest */
	int *,		/* maxlengthp */
	unsigned *,	/* lencopiedp */
	unsigned *);	/* ncp */
extern int interp_copyout(
	struct execargs *,	/* argbkp */
	caddr_t *,		/* user argpp */
	caddr_t *,		/* user bufferp */
	int *,			/* maxlengthp */
	unsigned *);		/* lencopiedp */

#ifdef __cplusplus
}
#endif
#endif /* _SYS_EXECARGS_H_ */
