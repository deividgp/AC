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
 * @(#)$RCSfile: security.h,v $ $Revision: 4.2.19.10 $ (DEC) $Date: 1995/09/20 17:03:02 $
 */
/*
 * (c) Copyright 1990, 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0.1
 */
/* @(#)security.h	6.4 07:57:07 2/18/91 SecureWare */
/*
 * Copyright (c) 1987-1990 SecureWare, Inc.  All rights reserved.
 *
 * Based on:
 *	@(#)security.h	2.8.2.3 14:28:20 12/27/89 SecureWare
 */
#ifndef __SECURITY__
#define __SECURITY__

#include <sys/secdefines.h>
#include <sys/param.h>
#include <sys/unix_defs.h>
#include <sys/acl.h>

/*
 * System calls that share the security() interface to the kernel.
 * If these are reordered, you must also reorder the function table
 * in sec_calls.c.
 */

#define	SEC_STOPIO		1
#define	SEC_GETLUID		2
#define	SEC_SETLUID		3
#define	SEC_STATPRIV		4
#define	SEC_CHPRIVSYS		5


#define	SEC_EACCESS		6

#define	SEC_MKMULTDIR		7
#define	SEC_RMMULTDIR		8
#define	SEC_ISMULTDIR		9

#define	SEC_GETLABEL		10
#define	SEC_SETLABEL		11
#define	SEC_LMOUNT		12
#define SEC_ISLABELEDFS		13

#define	SEC_SWITCH_CALL		19

#if SEC_BASE

#define	SEC_CPASS_CTL_CALL	20
/*
 * The following are subfunctions of SEC_CPASS_CTL_CALL.
 */
#define	SEC_CPASS_SET		0x53L	/* 'S' */
#define	SEC_CPASS_CLEAR		0x63L	/* 'c' */
#define	SEC_CPASS_QUERY		0x51L	/* 'Q' */
#define	SEC_CPASS_NUM_FAIL	0x4EL	/* 'N' */
#define	SEC_CPASS_ZERO_FAIL	0x7AL	/* 'z' */
#endif /* SEC_BASE */

#define SEC_EPROPLIST		21

/* SEC_SWITCH options */
#define	SEC_SWITCH_STAT		0L
#define	SEC_SWITCH_ON		1L
#define	SEC_SWITCH_OFF		2L
#define	SEC_SWITCH_CONF		3L

/*
 * SEC_SWITCH_CONF returns a bitmap taken from SEC_CONF_bits when
 * successful (see <sys/secdefines.h>)
 */

typedef	ulong_t	priv_t;		/* used for priv masks */
typedef	ulong_t	mask_t;		/* used for sec masks */
typedef	uint_t	tag_t;		/* used for policy tags */

/*
 * PORT NOTE:
 * 
 * The security software assumes definitions of the uid_t, gid_t, mode_t,
 * dev_t, and pid_t typedefs.  If the underlying system does not have
 * definitions for them, you must include definitions in this file
 * that match the corresponding definitions assumed in the base source.
 */

/*
 * Union of various kinds of object identifiers.
 */

typedef union obj {
	caddr_t	o_file;		/* Pathname */
	pid_t	o_pid;		/* Process ID */
	int	o_semid;	/* Semaphore ID */
	int	o_shmid;	/* Shared Memory ID */
	int	o_msgid;	/* Message Queue ID */
	int	o_fdes;		/* Open File Descriptor */
} obj_t;

/*
 * Type representing an object's normal Unix DAC
 * attributes that can be modified.
 */

typedef struct {
	uid_t	uid;		/* Owner user ID */
	gid_t	gid;		/* Owner group ID */
	mode_t	mode;		/* Permission bits */
} dac_t;


#define SEC_TAG_COUNT	8	/* number of tags in tag pools */

/*
 * Structure used by getlabel(2) and setlabel(2) for passing internal
 * representations of labels between user and kernel space
 */

typedef struct {
	uchar_t	code;		/* function/return code value */
	ushort_t ir_length;	/* length of internal representation */
	caddr_t	ir;		/* internal representation pointer */
} attr_t;

/* Values for the code field of an attr_t structure */

#define SEC_WILDCARD_TAG	2	/* Wildcard Tag Value */
#define SEC_ACTUAL_TAG		3	/* Mapped Tag Value */

/*
 * Type for indicating whether an attribute (IR or tag) is associated
 * with a subject or an object.
 */

typedef short attrtype_t;	/* distinguish subject vs object attributes */

/* Values for variables of type attrtype_t */

#define SEC_SUBJECT	1	/* for subject attributes */
#define SEC_OBJECT	2	/* for object attributes */
#define SEC_IPC		3	/* an IPC object */

/*
 * Type representing a subject's attributes that are
 * significant to a DAC policy.
 */

typedef struct {
	uid_t	uid;		/* User Id */
	gid_t	gid;		/* Group Id */
#if SEC_GROUPS
	gid_t	groups[SEC_GROUPS];	/* Supplementary Group Ids */
#endif
} dacid_t;

/*
 * Type representing an object's normal Unix DAC attributes
 */

typedef struct {
	uid_t	cuid;		/* Creator user ID */
	gid_t	cgid;		/* Creator group ID */
	uid_t	uid;		/* Owner user ID */
	gid_t	gid;		/* Owner group ID */
	mode_t	mode;		/* UNIX permission bits */
} udac_t;


/* 
 * Type representing an object's creating Unix Dac attributes.
 */

typedef struct {
	uid_t	cuid;		/* Creator user ID */
	gid_t	cgid;		/* Creator group ID */
} cdac_t;


/* 
 * Type representing an object's effiective Unix Dac attributes
 */

typedef struct {
	uid_t	euid;		/* Effective user ID */
	gid_t	egid;		/* Effective group ID */
} edac_t ;

/*
 * Value of UNIX user/group IDs that are used to specify that an object
 * does not recognize the concept of "creator".
 */

#define SEC_NOCREATOR_UID	((uid_t) -3)
#define SEC_NOCREATOR_GID	((gid_t) -3)

/*
 * Bit flags representing individual components of Unix DAC information.
 */

#define	SEC_NEW_UID	0x1
#define	SEC_NEW_GID	0x2
#define	SEC_NEW_MODE	0x4
#define	SEC_NEW_GROUPS	0x8

#ifdef KERNEL
#if SEC_MAC
#define SP_OBJECT_CREATE(process,object,parent,attrtype, dac, umask) \
  (security_is_on ? sp_object_create(process,object,parent,attrtype,dac,umask) : 0)
#else
#define SP_OBJECT_CREATE(process,object,parent,attrtype, dac) \
        paclcreate(process,object,parent,attrtype, dac)
#define SP_ACCESS(subject,object,objtype,mode,udac,results) \
	results = paclaccess(subject,object,objtype,mode,udac)
#endif
#endif

/*
 * Access check modes recognized by SP_ACCESS().
 */

#if SEC_ARCH
#define	SP_IOCTLACC	00001000	/* for performing ioctl functions */
#define	SP_MOUNTACC	00002000	/* for checking fs root and mount dir */
#define	SP_STATACC	00004000	/* for stat(2)ing a file descriptor */
#endif
#define	SP_DELETEACC	00010000	/* for deleting an object */
#define	SP_CREATEACC	00020000	/* for checking directory create */
#if SEC_ARCH
#define	SP_LINKACC	00040000	/* for checking object and target dir */
#define	SP_SETATTRACC	00100000	/* for changing object attributes */
#define	SP_KILLACC	00200000	/* for kill(2)ing another process */
#define	SP_MLSDACC	00400000	/* create/write operation for a MLSD
					 * similar to SP_WRITEACC but requires 
					 * subject domination. */

/*
 * The following are used by the discretionary policy module to make access
 * decisions.  There is a dependency in the aclaccess() routine on the
 * values of these #defines.  They must match the definitions of IREAD, etc.
 * in the underlying system, and the discretionary module access function
 * must change to accommodate differences in the values appearing there.
 */

#define	SP_READACC	0400	/* for checking read access */
#define	SP_WRITEACC	0200	/* for checking write access */
#define	SP_EXECACC	0100	/* for checking execute access */

#endif /* SEC_ARCH */

/* These macros are for the manipulation of the ulong_t type. */

#define	BITS_PER_BYTE		8
#define	SEC_MASK_BITS		(sizeof(ulong_t) * BITS_PER_BYTE)
#define	WORD_OF_BIT(bit)	((bit) / SEC_MASK_BITS)
#define	BIT_IN_WORD(bit)	(((ulong_t)1) << ((bit) % SEC_MASK_BITS))

/*
 * Macros to add, remove, and test bits in a multi-word bit mask
 * MP Note: Must do locking at a higher level
 */

#define ADDBIT(m,b)	m[WORD_OF_BIT(b)] |= BIT_IN_WORD(b)
#define RMBIT(m,b)	m[WORD_OF_BIT(b)] &= ~BIT_IN_WORD(b)
#if !defined(_KERNEL) || SEC_PRIV
#define ISBITSET(m,b)	((m[WORD_OF_BIT(b)] & BIT_IN_WORD(b)) != 0)
#endif


/*
 * Definitions for system privileges. 
 */

enum {
	SecSuspendAudit,	/* Process does its own auditing */
	SecConfigAudit,		/* Process to configure audit */
	SecWriteAudit,		/* Process can write audit records */
	SecExecSUID,		/* Process can exec SUID programs */
	SecChmodSUGID,		/* Permit setting of SUID/SGID bits */
	SecChown,		/* Permit giving away files */
	SecAcct,		/* acct() system call */
	SecLimit,		/* Resource limit override */
	SecLock,		/* Lock process parts in core */
	SecLinkDir,		/* Link directories */
	SecMknod,		/* mknod() system call */
	SecMount,		/* Mount, unmount, swap space */
	SecSysAttr,		/* Set system attributes */
	SecProcIdent,		/* Change real ID */
	SecChroot,		/* chroot() system call */
	SecDebug,		/* Kernel debugging activities */
	SecShutdown,		/* Shutdown, reboot, remount */
	SecFilesys,		/* Configure disk */
	SecRemote,		/* Perform network administration */
	SecKill,		/* Kill any process */
	SecOwner,		/* Change file attributes */
	SecChpriv,		/* Set file privileges */
	SecAllowDAC,		/* Override DAC constraints */
	SecSUCompat,		/* Enable superuser compatibility */
	SecSUPropagate,		/* Enable propagation of SecSUCompat */
	SecDowngrade,		/* Downgrade file attributes */
	SecWriteupClrnce,	/* Upgrade info to clearance */
	SecWriteupSyshi,	/* Upgrade info to any level */
	SecMultdir,		/* View all of multilevel dir. */
	SecAllowMAC,		/* Override MAC constraints */
	SecAllowILB,		/* Override ILB constraints */
	SecILNoFloat,		/* Don't float information labels */
	SecAllowTpathAccess,	/* Override trusted path */
	SecObjReuseOverride,	/* Override object reuse */
	SecPrivSessionMgmt,	/* Privilege session management */
	SecAllowWinDevAccess,	/* window device access */
	SecUseMach,		/* Allowed to use Mach interfaces */
        SecNetNoAuth,           /* not currently implemented */
        SecNetPrivAddr,         /* validate binding to well-known port */
        SecNetBroadcast,        /* allows use of broadcast address */
        SecNetRawAccess,        /* allows creation of a raw socket */
        SecNetSetId,            /* set security attributes on outgoing data */
        SecNetPrivSession,      /* TCB to TCB communications */
        SecNetAllowNetAccess,   /* sum of all net privs */

	SecMaxPriv		/* Must be last element of enum */
};

/*
 * The code uses the defined constants rather than the enumerated
 * constants since most C compilers don't seem to allow the latter
 * to be used in arithmetic expressions.
 */

#define	SEC_SUSPEND_AUDIT	((int) SecSuspendAudit)
#define SEC_CONFIG_AUDIT	((int) SecConfigAudit)
#define SEC_WRITE_AUDIT		((int) SecWriteAudit)
#define	SEC_EXECSUID		((int) SecExecSUID)
#define	SEC_CHMODSUGID		((int) SecChmodSUGID)
#define	SEC_CHOWN		((int) SecChown)
#define	SEC_ACCT		((int) SecAcct)
#define	SEC_LIMIT		((int) SecLimit)
#define	SEC_LOCK		((int) SecLock)
#define	SEC_LINKDIR		((int) SecLinkDir)
#define	SEC_MKNOD		((int) SecMknod)
#define	SEC_MOUNT		((int) SecMount)
#define	SEC_SYSATTR		((int) SecSysAttr)
#define	SEC_SETPROCIDENT	((int) SecProcIdent)
#define	SEC_CHROOT		((int) SecChroot)
#define	SEC_DEBUG		((int) SecDebug)
#define	SEC_SHUTDOWN		((int) SecShutdown)
#define	SEC_FILESYS		((int) SecFilesys)
#define	SEC_REMOTE		((int) SecRemote)
#define	SEC_KILL		((int) SecKill)
#define	SEC_OWNER		((int) SecOwner)
#define	SEC_CHPRIV		((int) SecChpriv)
#define	SEC_ALLOWDACACCESS	((int) SecAllowDAC)
#define	SEC_SUCOMPAT		((int) SecSUCompat)
#define	SEC_SUPROPAGATE		((int) SecSUPropagate)
#define	SEC_DOWNGRADE		((int) SecDowngrade)
#define	SEC_WRITEUPCLEARANCE	((int) SecWriteupClrnce)
#define	SEC_WRITEUPSYSHI	((int) SecWriteupSyshi)
#define	SEC_MULTILEVELDIR	((int) SecMultdir)
#define	SEC_ALLOWMACACCESS	((int) SecAllowMAC)
#define	SEC_ALLOWILBACCESS	((int) SecAllowILB)
#define	SEC_ILNOFLOAT		((int) SecILNoFloat)
#define SEC_ALLOWTPATHACCESS	((int) SecAllowTpathAccess)
#define SEC_OBJREUSEOVERRIDE	((int) SecObjReuseOverride)
#define SEC_PRIVSESSIONMGMT	((int) SecPrivSessionMgmt)
#define SEC_ALLOWWINDEVACCESS	((int) SecAllowWinDevAccess)
#define	SEC_USE_MACH		((int) SecUseMach)
#define SEC_NETNOAUTH           ((int) SecNetNoAuth)
#define SEC_NETPRIVADDR         ((int) SecNetPrivAddr)
#define SEC_NETBROADCAST        ((int) SecNetBroadcast)
#define SEC_NETRAWACCESS        ((int) SecNetRawAccess)
#define SEC_NETSETID            ((int) SecNetSetId)
#define SEC_NETPRIVSESSION      ((int) SecNetPrivSession)
#define SEC_ALLOWNETACCESS      ((int) SecNetAllowNetAccess)

#define	SEC_MAX_SPRIV		((int) SecMaxPriv - 1)

/*  The following are derived from the definitions above.
 *  New Network privileges should be added after SEC_ALLOWNETACCESS
 *  and the SEC_LAST_NET_PRIV modified appropriately
 */
#define SEC_FIRST_NET_PRIV      SEC_NETNOAUTH
#define SEC_LAST_NET_PRIV       SEC_ALLOWNETACCESS
#define SEC_MAX_TNET_PRIVS      (SEC_LAST_NET_PRIV - SEC_FIRST_NET_PRIV + 1)

/* Number of ulong_t words required to hold a privilege vector */

#define	SEC_SPRIVVEC_SIZE	(WORD_OF_BIT(SEC_MAX_SPRIV) + 1)

typedef ulong_t	privvec_t[SEC_SPRIVVEC_SIZE];


/*  some default file mode settings */

#define	SEC_DEFAULT_MODE	0700

/*
 *  The different kinds of privilege vectors.
 */

#define	SEC_EFFECTIVE_PRIV	1
#define	SEC_KERNEL_AUTHS	2
#define	SEC_MAXIMUM_PRIV	SEC_KERNEL_AUTHS	/* historical */
#define	SEC_BASE_PRIV		3
#define	SEC_POTENTIAL_PRIV	4
#define	SEC_GRANTED_PRIV	5

#if SEC_FSCHANGE

/*  Bits in the type flag word in the secure disk inode. */

#define	SEC_I_MLD		0x1
#define	SEC_I_MLDCHILD		0x2

#endif /* SEC_FSCHANGE */

#if SEC_MAC

/*  Codes for handling of multilevel directory path components. */

#define	SEC_MLD_PASS		0
#define	SEC_MLD_DIVERT		1
#define	SEC_MLD_ERROR		2
#define	SEC_MLD_DOTDOT		3


/*  Minimum PID number not created by the system at init time */

#define	SEC_MINPID		3	/* PID 2 is vhand */

#endif /* SEC_MAC */

/* Definitions of types of attributes that can be passed through sockets
 * using the "access rights" mechanism.  These values are chosen to be
 * large negative numbers to facilitate distinguishing an expanded rights
 * buffer from an old-style array of file descriptors.  An expanded rights
 * buffer is a series of entries, each beginning with a 16 bit type flag
 * followed by a 16 bit length followed by the actual attribute consisting
 * of the specified number of bytes.
 */

#define	SEC_RIGHTS_FDS		((ushort_t) 0xACC0)
#define	SEC_RIGHTS_PRIVS	((ushort_t) 0xACC1)
#if SEC_ILB
#define	SEC_RIGHTS_ILB		((ushort_t) 0xACC2)
#endif
#define	SEC_EXTENDED_RIGHTS	((ushort_t) 0xACC3)


#ifdef _KERNEL
/*
 * The following macros protect various SIP attributes.  This is a
 * system-wide lock for now, since various system calls access
 * attributes for other processes.  Deadlocks might happen with
 * finer granularity locking, and the locks are never held for
 * very long.  Hopefully the collision rate won't be high enough
 * to worry about.
 * If you add locks here, don't forget to change sec_init() to
 * call simple_lock_init() on them.
 */

#ifndef _KERN_LOCK_H_
#include <kern/lock.h>
#endif

#if SEC_BASE
decl_simple_lock_data (extern, sip_attr_lock)
decl_simple_lock_data (extern, sip_audit_lock)
decl_simple_lock_data (extern, sip_audit_flag_lock)

#define SIP_ATTR_LOCK()		simple_lock(&sip_attr_lock);
#define SIP_ATTR_UNLOCK()	simple_unlock(&sip_attr_lock);
#endif /* SEC_BASE */

#endif	/* _KERNEL */

/* Kernel Security Event Definitions
 *
 * The values defined below are used to set, test, and clear the
 * contents of the security event history mask in the security_info
 * struct.
 */
enum {
	SEDACChange,		/* DAC changed for obj */
	SEDACFail,		/* DAC rejected access to obj */
	SEPrivUsed,		/* Use of privilege */
	SEPrivFail,		/* Use of priv not held failed */
	SESLSet,		/* SL set */
	SEMACFail,		/* MAC rejected access to obj */
	SESubjILFloat,		/* Subject IL floated */
	SEObjILFloat,		/* Object IL Floated */
	SEObjILReset,		/* Object IL reset */
	SESymLinkUsed		/* Symbolic link used */
} ;

#define SE_DAC_CHANGE		((int) SEDACChange)
#define SE_DAC_FAIL		((int) SEDACFail)
#define	SE_PRIV_USED		((int) SEPrivUsed)
#define	SE_PRIV_FAIL		((int) SEPrivFail)
#define	SE_SL_SET		((int) SESLSet)
#define SE_MAC_FAIL		((int) SEMACFail)
#define	SE_SUBJ_IL_FLOAT	((int) SESubjILFloat)
#define	SE_OBJ_IL_FLOAT		((int) SEObjILFloat)
#define	SE_OBJ_IL_RESET		((int) SEObjILReset)
#define SE_SYM_LINK_USED	((int) SESymLinkUsed)

#define	SE_MAX_EVENT SE_SYM_LINK_USED

typedef ulong_t sec_eventvec_t[(WORD_OF_BIT(SE_MAX_EVENT) + 1)];
					/* kernel security event vector */
#if SEC_BASE
/*
 * Security relevant process state information.
 * This structure contains state information that spans system calls.
 * The security_info structure contains security-related fields that
 * might normally be in the user structure.  However, putting them there
 * would require various utilities (ps, etc.) that read from kernel
 * memory to be different depending on whether security is/isn't configured
 * into the kernel, and what options (SEC_ILB, etc.) were used to build the
 * kernel.
 *
 * SIP is always a pointer to the security_info structure for the currently
 * running process. The security_info structures for other processes may be
 * accessed through the secinfo array.  Unfortunately, this is done more often
 * than we might like in the MP world.  For this reason, MP locks are
 * organized such that each lock protects a field (or fields) of *all*
 * security_info structures, rather than having a per-structure lock.
 *
 * Unless otherwise noted, locks are system-wide spin locks.  No other locks
 * may be taken after taking one of these locks. None of these locks is
 * intended to be held for a long time, so lock contention hopefully won't
 * make system-wide locking a problem.
 * 
 * In general, fields on each line of the table below must be protected by
 * the same lock, while fields on different lines could be protected by
 * different locks if lock contention is ever a problem.
 *
 *	lock name		protects
 *
 *	SIP_ATTR_LOCK		si_bpriv, si_epriv, si_mpriv, si_spriv
 * 	SIP_ATTR_LOCK		si_diversion, si_pslevel
 *	SIP_ATTR_LOCK		si_privs_used, si_last_fail_priv
 *	SIP_ATTR_LOCK		si_last_fail_priv_syscall, si_sec_event_hist
 *	SIP_ILB_LOCK		si_pilevel, si_subjnum, si_subj_bits
 *	SIP_NCAV_LOCK		si_pncav
 *	SIP_TAG_LOCK		si_tag
 *
 * As of 7/25/90, locking of these is believed complete except for
 * SIP_NCAV_LOCK (not supported in OSF/1) and SIP_TAG_LOCK.
 * ILB support has known races between ilb_check_float() and ilb_do_float().
 */

struct security_info {
	/*
	 * These fields are part of the base secure system, providing
	 * support for process privileges, and process-specific selection
	 * of event types to be audited.
	 */
	privvec_t	si_epriv;	/* effective privileges */
	/*
	 * These fields provide storage for the additional privilege sets
	 * associated with processes for the sake of checking discrete
	 * privileges in lieu of superuser checks.
	 */
	privvec_t	si_mpriv;	/* kernel authorizations */
	privvec_t	si_bpriv;	/* base privileges */
	privvec_t	si_spriv;	/* potential privs of current image */

#if SEC_PRIV
	privvec_t	si_privs_used;	/* history of privileges used */
	ushort		si_last_fail_priv;
	int		si_last_fail_priv_syscall;
					/* last priv that failed and the
					 * syscall that it failed in. */
#endif /* SEC_PRIV */
#if defined(SEC_PRIV) || defined(SEC_ACL) || defined(SEC_MAC)
	sec_eventvec_t	si_sec_event_hist;
					/* recent security event history
					 * mask.  flag bits accessed using
					 * SE_ symbols as offsets.  */
#endif

#if SEC_ARCH
	/*
	 * These fields support the security policy architecture.
	 */
	tag_t	si_tag[SEC_TAG_COUNT];	/* process security tags */

#if SEC_MAC
#define	SI_DIVERSION_SIZE 15	/* Multilevel directory diversion dir name */
	char	si_diversion[SI_DIVERSION_SIZE];/* diversion name for MLD */
#endif	/* SEC_MAC */

#if SEC_ILB
	/*
	 * MP Note:
	 * Be extra careful about holding SIP_ILB_LOCK before reading
	 * si_subjnum.  There is a brief window in secinfo_dup() where
	 * si_subjnum is wrong.  Without the lock, you may hit it.
	 */

	int		si_subjnum;	/* subject number */
	mask_t		*si_subj_bits;	/* bitmap of objects for ILB maint */
#endif	/* SEC_ILB */

#endif	/* SEC_ARCH */
};
#endif /* SEC_BASE */

/*
 * The si_error field further discriminates the reason for a security failure.
 * On return from a system call, the bits defined by SEC_ERRNO_MASK are
 * filled with the contents of the si_error field.  The value of
 * SEC_ERRNO_SHIFT tells how to shift si_error into the return value.
 * When adding a new error here be sure to correspondingly update sec_errlst.c
 * and libsec.msg in libsecurity.
 */

#define SEC_ERRNO_MASK		 0xff00	/* mask for security error */
#define SEC_ERRNO_SHIFT		 8	/* how far to shift si_error */

#define ESEC_MAC_CONFIG_FAILURE  1	/* MAC configuration file error */
#define ESEC_WILDCARD_TAG	 2	/* operation fails on wildcard tag */
#define ESEC_ACL_CONFIG_FAILURE	 3	/* ACL configuration file error */
#define ESEC_WILD_SUBJ_SL	 4	/* subject has wildcard SL */
#define ESEC_WILD_DIR_SL	 5	/* directory has wildcard SL */
#define ESEC_MAC_NOT_EQUAL	 6	/* subject and object SLs not equal */
#define ESEC_MAC_NEED_PRIVILEGE	 7	/* no privilege for operation */
#define ESEC_NO_DECISION	 8	/* no decision available from daemon */
#define ESEC_MAC_SDOM		 9	/* Subject does not dominate */
#define ESEC_MAC_ODOM		10	/* Object does not dominate */
#define ESEC_MAC_NO_CLEARANCE	11	/* Setting SL and clearance not set */
#define ESEC_MAC_DOM_CLEARANCE	12	/* Setting SL higher than clearance */
#define ESEC_MAC_NO_SL		13	/* Can't change CL/IL if SL not set */
#define ESEC_MAC_UP_CLEARANCE	14	/* Can't raise clearance */
#define ESEC_MAC_IL_RELATION	15	/* Violation of SL/IL relationship */
#define ESEC_MAC_FS_RELATION	16	/* Violation of increasing tree */
#define ESEC_MAC_NO_WRITE	17	/* Need write access for operation */
#define ESEC_NOT_OWNER		18	/* Must be owner of object */
#define ESEC_IS_MLD		19	/* Operation invalid on multilvl dir */
#define ESEC_DIR_NOT_EMPTY	20	/* Operation invalid (non-empty dir) */
#define ESEC_MAC_IL_NOCOMB	21	/* Cannot combine information labels */
#define ESEC_UNEXT_FS		22	/* Not extended filesystem format */
#define ESEC_NOT_REG		23	/* File is not regular file */
#define ESEC_SETATTR_FAIL	24	/* Cannot set file attributes */
#define ESEC_INVALID_IR		25	/* Cannot map internal rep to tag */
#define ESEC_NCAV_CONFIG_FAILURE 26	/* NCAV configuration file error */
#define	ESEC_NOT_MLD		27	/* Directory is not multilevel */
#define	ESEC_EXT_FS		28	/* Operation invalid on extended fs */
#define ESEC_MAX_ERRNO		28


extern struct security_info *secinfo;
extern int check_privileges;
extern int check_luid;
#ifdef KERNEL
extern int security_is_on;
#endif
extern uid_t sec_priv_gid;

#if SEC_BASE
#define SEC_UID 0
#define SEC_SUSER(_u,_g)    ((_u == SEC_UID) || (_g == sec_priv_gid))
#endif


/*
 * Declare pointers to the security_info and audit_info structures
 * for the currently running entity.  These are automatically
 * switched at context-switch time.  SIP is a per-process pointer.
 */

#define SIP 	(&secinfo[(current_task())->proc_index])


#if SEC_ARCH
#ifdef KERNEL

#include <sys/ipc.h>

/*
 * OSF code uses the "BM" (bogus memory) macro to attempt to provide support
 * for machines on which word operations aren't guaranteed atomic.
 * This adds needless clutter to the code, and increases the risk of
 * bugs related to lock/unlock mismatches.  For now, we'll try to do
 * the equivalent thing in a simpler way. The macros here are for
 * "normal" systems.  BM equivalents of the macros are in sec/sec_subrs.c.
 */

#include <bogus_memory.h>

#ifndef BOGUS_MEMORY
#define	vnode_type(vp)		((vp)->v_type)
#endif /* BOGUS_MEMORY */

/*
 * Define some macros to check file types.
 * The basic idea here is that we can hide some of the differences
 * between vnode-based file systems and inode-based file systems
 * in macros instead of littering the code with conditionals.
 */
 
#define IS_REG_FILE(vp)		(vnode_type((vp)) == VREG)
#define IS_DIRECTORY(vp)	(vnode_type((vp)) == VDIR)
#define IS_BLOCK_DEV(vp)	(vnode_type((vp)) == VBLK)
#define IS_CHAR_DEV(vp)		(vnode_type((vp)) == VCHR)
#define IS_SYMLINK(vp)		(vnode_type((vp)) == VLNK)
#define IS_SOCKET(vp)		(vnode_type((vp)) == VSOCK)
#define IS_FIFO(vp)		(vnode_type((vp)) == VFIFO)

/*
 * spd_misc.c
 */
extern int	sp_object_create(tag_t * process,
				 tag_t * object,
				 tag_t * parent,
				 attrtype_t attrtype,
				 dac_t * dac,
				 mode_t umask);
extern int	SP_DELETE(tag_t * object,
			  int objtype);
extern int	SP_ACCESS(tag_t * subject,
			  tag_t * object,
			  int mode,
			  udac_t * udac);
extern int	sec_ipcaccess(struct ipc_perm * perm,
			      tag_t * tags,
			      int mode);
extern void	sp_clear_tags(void);
extern int	sp_maptag(int policy,
			  attrtype_t attrtype,
			  int tagnum,
			  attr_t * attr,
			  udac_t * udac,
			  tag_t * new_tag,
			  int ir_space);
extern mask_t *	sp_bitmap_alloc(int nbits,
				int init);
extern void	sp_bitmap_free(mask_t * map,
			       int nbits);
extern int	sp_alloc_object(tag_t * obj_tag);
extern void	sp_free_object(tag_t * obj_tag);
extern void	sp_set_il_bits(struct security_info * sip,
			       int obj);
extern void	sp_init_subj_bits(struct security_info * sip);
extern void	set_sip_subj_bits(struct security_info * sip);
extern void	sp_init_obj_bits(tag_t * obj_tag);
extern void	sec_svipc_object_create(tag_t * tags);
extern struct ipc_perm *	sec_ipc_slot(struct ipc_perm * entries,
					     int entry_size,
					     int num_entries);

#else

#include <sys/secpolicy.h>

/*
 * tag_cache.c
 */
extern int	set_tag_cache_size(unsigned int n);
extern int	tag_cache_enter(int policy, attrtype_t type, attr_t * ir, tag_t tag);
extern int	tag_cache_lookup(int policy, attrtype_t type, attr_t * ir, tag_t * tag);
extern int	tag_cache_invalidate(int policy, attrtype_t type, attr_t * ir, tag_t tag);

/*
 * dec_cache.c
 */
extern int	set_decision_cache_size(unsigned int n);
extern int	decision_cache_enter(int policy, tag_t subject, tag_t object, dec_t * decision);
extern int	decision_cache_lookup(int policy, tag_t subject, tag_t object, dec_t * decision);
extern int	decision_cache_invalidate(int policy, tag_t subject, tag_t object, dec_t * decision);

#endif /* KERNEL */
#endif /* SEC_ARCH */

#endif /* __SECURITY__ */
