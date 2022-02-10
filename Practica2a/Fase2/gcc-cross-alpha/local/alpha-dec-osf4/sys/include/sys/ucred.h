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
 *	@(#)$RCSfile: ucred.h,v $ $Revision: 4.2.18.2 $ (DEC) $Date: 1997/01/31 18:25:54 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *

 */

#ifndef _SYS_UCRED_H_
#define	_SYS_UCRED_H_

/*
 * Credentials.
 *
 * By convention, credentials are never modified, only copied.
 * Thus, it is always possible to examine a credential entry
 * without holding the ucred structure locked. A simple lock, taken
 * only by standard subroutines and invisible here, protects
 * getting a reference on the structure.  Note that originally, the
 * field "cr_ref" was used to hold the ucred reference count.  This was
 * too small (a short), so a new reference field (long) was added to the 
 * "hidden" part of the ucred structure (see bsd/kern_prot.c for details).
 * A reference to a ucred structure is gotten by a call to crhold() 
 * and freed by a call to crfree().  A reference on a cred structure ensures
 * that it will not be freed, before the reference is released.
 *
 * Credentials in the u-area are changed by building a new
 * credentials structure and substituting it for the old one
 * pointed to by the proc structure's p_rcred field.
 */
struct ucred {
	u_short	cr_ref;			/* Obsolete reference count */
	u_short	cr_ngroups;		/* number of additional groups */
	uid_t	cr_uid;			/* effective user id */
	gid_t	cr_gid;			/* effective group id */
	u_long	cr_pag;			/* process authentication group (DFS) */
	long	cr_sia_proc_cred_val;	/* DASS proc-wide auth value */
	gid_t	cr_groups[NGROUPS];	/* additional groups */
	uid_t   cr_ruid;		/* Copy of real user id from p_ruid */
/*
 * The next four fields were added to support SVR4 style credentials.
 */
	uid_t	_cr_ruid;		/* real user id*/
	gid_t	_cr_rgid;		/* real group id*/
	uid_t	_cr_suid;		/* saved user id*/
	gid_t	_cr_sgid;		/* saved group id*/
};
#define	NOCRED	((struct ucred *) -1)
#define	NOUID	((uid_t) -1)
#define	NOGID	((gid_t) -1)

#ifdef	_KERNEL

/*
 * Uid's or gid's which are negative or greater than UID_MAX are
 * not permitted (note there is no GID_MAX).
 * The first part of the following macros becomes a no-op if
 * uid_t/gid_t is unsigned, while the second part becomes a
 * no-op if UID_MAX is maximal for its type.
 *
 * Some system calls and operations provide for a NOUID/NOGID
 * wildcard.  This must be explicitly checked before invoking
 * these macros.
 */
#ifdef _XOPEN_SOURCE_EXTENDED
#define	INVALID_UID(uid) ((uid_t)(uid) < 0 || (uid_t)(uid) > (uid_t)uid_max)
#else
#define	INVALID_UID(uid) ((uid_t)(uid) > (uid_t)uid_max)
#endif
#define	INVALID_GID(gid) ((gid_t)(gid) > (gid_t)uid_max)
extern uid_t	uid_max;

extern struct ucred *crget(void);
extern void crhold(struct ucred *);
extern struct ucred *crcopy(struct ucred *);
extern struct ucred *crdup(struct ucred *);
extern void crfree(struct ucred *);
extern int groupmember(gid_t, struct ucred *);
typedef struct flag_field *ucred_flag_field;	/* XXX circular with user.h */
extern int suser(struct ucred *, struct flag_field *);
#endif

#endif /* _SYS_UCRED_H_ */
