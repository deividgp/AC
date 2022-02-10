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
 *	@(#)$RCSfile: mount.h,v $ $Revision: 4.3.144.4 $ (DEC) $Date: 1999/01/28 12:57:22 $	
 */ 
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
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

#ifndef	_SYS_MOUNT_H_
#define _SYS_MOUNT_H_

#include <standards.h>
#include <sys/types.h>
#include <sys/unix_defs.h>
#include <kern/lock.h>
#include <sys/secdefines.h>
#if	SEC_ARCH
#include <sys/security.h>
#endif 
#ifdef	_KERNEL
#include <ser_compat.h>
#endif

#ifndef _KERNEL
#if defined(_NO_PROTO) || defined(__SVID__)
extern int mount();
extern int umount();
#else /* _NO_PROTO || __SVID__ */
_BEGIN_CPLUSPLUS
extern int mount( int, char *, int, caddr_t );
extern int umount( char *, int );
_END_CPLUSPLUS
#endif /* _NO_PROTO */
#endif /* _KERNEL */

/*
 * File system types.
 *
 * WARNING:
 *	These constants serve as indexes for the filesystem name in the
 *	mnt_names[] array in sys/fs_types.h.  Any changes to these
 *	constants should be reflected in the definition of the mnt_names[]
 *	array in this file so that the filesystem name is always indexed
 *	by the associated constant.
 */
#define	MOUNT_NONE	0
#define	MOUNT_UFS	1
#define	MOUNT_NFS	2
#define MOUNT_MFS	3
#define	MOUNT_PC	4
#define MOUNT_S5FS	5
#define MOUNT_CDFS	6
#define MOUNT_DFS       7         /* DCE DFS */
#define MOUNT_EFS       8         /* DCE Episode FS */
#define MOUNT_PROCFS	9
#define	MOUNT_MSFS	10
#define MOUNT_FFM       11
#define MOUNT_FDFS	12	/* Generic file system type */
#define MOUNT_ADDON	13
#define MOUNT_NFS3	14	/* NFS v3 */
#define MOUNT_DVDFS	15
#define MOUNT_MAXTYPE	16

#define MNAMELEN 90	/* length of buffer for returned name */

typedef quad fsid_t;	/* file system id type */

/*
 * File identifier (fid).
 * These are unique per filesystem on a single machine.
 * There is a length restriction imposed by the NFS version 2 file handle size
 * of 32 bytes. It is possible to extend this restriction with NFS version 3
 * where file handles can reach 64 byte sizes.
 * There is, as yet, no support for extended fids.
 *
 * Work backwards from the V2 restriction:
 */

/*
 * Size of an NFS fhandle (V2) in bytes
 */
#define	NFS_FHSIZE	32

/*
 * File access handle
 * This structure is the DEC/OSF NFS server representation of a file.
 * It is handed out by a server for the client to use in further
 * file transactions. It must contain a file system ID and two fids.
 */

/*
 * This struct is only used to find the maximum size of the data field in the
 * fhandle structure below.
 */
struct nfsfhsize {
	fsid_t	f1;
	u_short	f2;
	u_short	f3;
	char	f4[4];
	u_short	f5;
	u_short	f6;
	char	f7[4];
};

/* Warning!    
 *      NFS_FHMAXDATA   MUST! be a multiple of 4 bytes (32 bits)
 * This allows fs code that gets a fid_t pointer to stuff ints without
 * getting unaligned access traps.
 */
#define	NFS_FHMAXDATA	((NFS_FHSIZE - sizeof (struct nfsfhsize) + 8) / 2)

struct fid {
	u_short		fid_len;		 /* length of data in bytes */
	u_short		fid_reserved;		 /* force 32 bit alignment */
	char		fid_data[NFS_FHMAXDATA]; /* data (variable length) */
	/* MUST END ON A 4-byte BOUNDARY */
};

typedef struct fid fid_t;

struct svcfh{
	fsid_t	fh_fsid; /* filesystem id */
	fid_t   fh_fid;  /* Id of file */
	fid_t   fh_efid; /* Id of export granting directory */
};

struct nfssvcfh {
	union nfssvcfh_u {
		struct	svcfh svcfh_i;
		u_char	data[NFS_FHSIZE];
	} svcfh_u;
};

typedef struct nfssvcfh fhandle_t;

#define	fh_fsid	svcfh_u.svcfh_i.fh_fsid
#define	fh_fid	svcfh_u.svcfh_i.fh_fid	
#define	fh_efid	svcfh_u.svcfh_i.fh_efid
#define	fh_data svcfh_u.data

/* fid support stuff */
#define fsid_equal(fsid1,fsid2) \
(bcmp((caddr_t)(fsid1), (caddr_t)(fsid2), sizeof(fsid_t))==0)  

#define fid_equal(fid1,fid2) \
((fid1)->fid_len == (fid2)->fid_len &&\
bcmp(&(fid1)->fid_reserved, &(fid2)->fid_reserved, (fid1)->fid_len - sizeof(short))==0)

#define fid_copy(fid1,fid2) \
if ((fid1)->fid_len > sizeof(fid_t) || (fid1)->fid_len < 2*sizeof(short) )\
	panic("improper fid size");\
bcopy((caddr_t)(fid1), (caddr_t)(fid2), (fid1)->fid_len);

#define fsid_copy(fsid1,fsid2) \
bcopy((caddr_t)(fsid1), (caddr_t)(fsid2), sizeof(fsid_t))  

#define fsid_print(fs) \
printf("%x,%x\n", *(int *)(fs), *((int *)(fs)+1))

#define fid_print(fid) \
if ((fid)) { \
int i; \
printf("len %d, reserved %x, data", (fid)->fid_len, (fid)->fid_reserved); \
for (i = 0; i < NFS_FHMAXDATA; i++)  \
	printf(" %x",(fid)->fid_data[i]); \
printf("\n"); \
} else printf("can not print null fid\n");

/*
 * Arguments to mount UFS
 */
struct ufs_args {
        char    *fspec;         /* block special device to mount */
        int     exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
};

/*
 * Arguments to mount AdvFS (via mount(2))
 */
struct advfs_args {
        char		*fspec;         /* block special device to mount */
	int		exflags;        /* export related flags */
        uid_t		exroot;         /* mapping for root uid */
	unsigned int	fsid;		/* Potential file set id/dev */
};

typedef struct map_id {
	ushort  old_id; /* 16b value */
	uid_t   new_id; /* 32b value */
} map_id;

#define	CDFS_EXTENDED_ARGS_VERSION	1

/*
 * Arguments to mount CDFS
 */
struct cdfs_args {
        char    *fspec;         /* block special device to mount */
        int     exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
	int	flags;		/* CDFS mount options */
	int	version;	/* M_EXTENDED_ARGS: version of struct */
	uid_t	default_uid;	/* M_DEFUID: default uid if no xar */
	gid_t	default_gid;	/* M_DEFGID: default gid if no xar */
	mode_t	default_fmode;	/* M_DEFFMODE: default file mode if no xar */
	mode_t	default_dmode;	/* M_DEFDMODE: default dir mode if no xar */
	int	map_uid_ct;	/* M_MAPUID: #map_uids */
	map_id	*map_uid;	/* ptr to map_uid 2D array */
	int	map_gid_ct;	/* M_MAPGID: #map_gids */
	map_id	*map_gid;	/* ptr to map_gid 2D array */
};

/*
 * Arguments to mount DVDFS
 */
struct dvdfs_args {
        char    *fspec;         /* block special device to mount */
        uint_t  exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
	int	flags;		/* CDFS mount options */
        int     reserved;       /* don't know yet */
};

/*
 * Arguments to mount System V file system
 */
struct s5fs_args {
        char    *fspec;         /* block special device to mount */
        int     exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
};

/*
 * Arguments to mount MFS
 */
struct mfs_args {
        char    *name;          /* name to export for statfs */
        caddr_t base;           /* base address of file system in memory */
        long    size;           /* size of file system */
};

/*
 * Arguments to mount /proc file system
 */
struct procfs_args {
        char    *fspec;         /* block special device to mount */
        int     exflags;        /* export related flags */
        uid_t   exroot;         /* mapping for root uid */
};

/* Arguments for file-on-file mount */
struct ffm_args {
	int   ffm_flags;                      /* operational flags */
	union {
	    char    *ffm_pname;             /* pathname to mount */
	    int     ffm_fdesc;              /* file descriptor to mount */
        } f_un;
};

#define ffm_pathname f_un.ffm_pname     /* shorthand */
#define ffm_filedesc f_un.ffm_fdesc     /* shorthand */

#define FFM_FD          0x000000001     /* file descriptor supplied */
#define FFM_CLONE       0x000000002     /* clone should be performed */

/*
 * File Handle (32 bytes for version 2), variable up to 1024 for version 3
 */
union nfsv2fh {
        fhandle_t       fh_generic;
        u_char          fh_bytes[32];
};
typedef union nfsv2fh nfsv2fh_t;

/* forward decls for ANSI & C++ */
struct sockaddr_in;
struct pathcnf;

/*
 * Arguments to mount NFS
 */
struct nfs_args {
        struct sockaddr_in      *addr;          /* file server address */
        caddr_t 		fh;		/* File handle to be mounted */
        int                     flags;          /* flags */
        int                     wsize;          /* write size in bytes */
        int                     rsize;          /* read size in bytes */
        int                     timeo;          /* initial timeout in .1 secs */
        int                     retrans;        /* times to retry send */
        int                     maxtimo;        /* retransmission timeout */
        char                    *hostname;      /* server's name */
        int                     acregmin;       /* min secs for file attrcache*/
        int                     acregmax;       /* max secs for file attrcache*/
        int                     acdirmin;       /* min secs for dir attrcache */
        int                     acdirmax;       /* max secs for dir attrcache */
        char                    *netname;       /* server's netname */
	struct pathcnf		*pathconf;	/* static pathconf kludge */
};

/*
 * NFS mount option flags
 */
#define NFSMNT_SOFT     0x001   /* soft mount (hard is default) */
#define NFSMNT_WSIZE    0x002   /* set write size */
#define NFSMNT_RSIZE    0x004   /* set read size */
#define NFSMNT_TIMEO    0x008   /* set initial timeout */
#define NFSMNT_RETRANS  0x010   /* set number of request retrys */
#define NFSMNT_HOSTNAME 0x020   /* set hostname for error printf */
#define NFSMNT_INT      0x040   /* allow interrupts on hard mount */
#define NFSMNT_NOCONN   0x080   /* no connect on mount - any responder */
#define NFSMNT_NOAC     0x0100  /* don't cache attributes */
#define NFSMNT_ACREGMIN 0x0200  /* set min seconds for file attr cache  */
#define NFSMNT_ACREGMAX 0x0400  /* set max seconds for file attr cache  */
#define NFSMNT_ACDIRMIN 0x0800  /* set min seconds for dir attr cache   */
#define NFSMNT_ACDIRMAX 0x01000 /* set max seconds for dir attr cache   */
#define NFSMNT_NOCTO    0x02000  /* don't freshen attributes on open */
#define NFSMNT_POSIX	0x04000	/* static pathconf kludge info */
#define NFSMNT_AUTO	0x08000	/* automount file system */
#define NFSMNT_SEC      0x010000 /* MLS+ secure mount */
#define NFSMNT_TCP	0x020000 /* TCP transport, not UDP */
#define NFSMNT_PROPLIST 0x040000 /* allow property list operations */
#define NFSMNT_MAXTIMO	0x0100000 /* retransmission timeout */

/*                   
 * MSFS - mountinfo
 */                  
                                                               /* msfs */
struct msfs_id {                                               /* msfs */
    int id1;                                                   /* msfs */
    int id2;                                                   /* msfs */
    int tag;                                                   /* msfs */
};                                                             /* msfs */
                                                               /* msfs */
struct msfs_args {                                             /* msfs */
    struct msfs_id id;                                         /* msfs */
};                                                             /* msfs */

/*
 * file system statistics
 */

union mount_info {		/* mount options */
	struct ufs_args ufs_args;
	struct nfs_args nfs_args;
	struct mfs_args mfs_args;
	struct cdfs_args cdfs_args;
	struct dvdfs_args dvdfs_args;
	struct procfs_args procfs_args;
        struct msfs_args msfs_args;                     /* msfs */
	struct ffm_args ffm_args;			/* ffm */
};

struct statfs {		
	short	f_type;			/* type of filesystem (see below) */
	short	f_flags;		/* copy of mount flags */
	int	f_fsize;		/* fundamental filesystem block size */
	int	f_bsize;		/* optimal transfer block size */
	int	f_blocks;		/* total data blocks in file system, */
					/*  note: may not represent fs size. */
	int	f_bfree;		/* free blocks in fs */
	int	f_bavail;		/* free blocks avail to non-su */
	int	f_files;		/* total file nodes in file system */
	int	f_ffree;		/* free file nodes in fs */
	fsid_t	f_fsid;			/* file system id */
	int	f_spare[9];		/* spare for later */
	char	f_mntonname[MNAMELEN];	/* directory on which mounted */
	char	f_mntfromname[MNAMELEN];/* mounted filesystem */
	union mount_info mount_info;	/* mount options */
};


/*
 * Limit on length of pathname arguments for mounting
 *
*/
#define MAX_MNT_PATHLEN MNAMELEN

/*
 *  Note that changes to the nstatfs structure from f_spare onward will
 *  require a corresponding change to the nstatfs_overlay structure.
 */
struct nstatfs {
	short	f_type;			/* type of filesystem (see below) */
	short	f_flags;		/* copy of mount flags */
	int	f_fsize;		/* fundamental filesystem block size */
	int	f_bsize;		/* optimal transfer block size */
	int	f_blocks;		/* total data blocks in file system, */
					/*  note: may not represent fs size. */
	int	f_bfree;		/* free blocks in fs */
	int	f_bavail;		/* free blocks avail to non-su */
	int	f_files;		/* total file nodes in file system */
	int	f_ffree;		/* free file nodes in fs */
	fsid_t	f_fsid;			/* file system id */
	long	f_spare[3];		/* for use later -- must be longs */
					/* to ensure quad alignment */
					/* for copying of below components */
					/* from kernel to user space */
#ifdef	_KERNEL
	char	*f_mntonname;		/* pointer to directory mounted on */
	char	*f_mntfromname;		/* pointer to mounted filesystem */
#else
	char	f_mntonname[MAX_MNT_PATHLEN];  /* directory on which mounted */
	char	f_mntfromname[MAX_MNT_PATHLEN];/* mounted filesystem */
#endif /* _KERNEL */
	union mount_info mount_info;	/* mount options */	
};


#ifdef _KERNEL
/*
 * The nstatfs_overlay struct is for calculating offsets in the user
 * statfs structure when copying the kernel nstatfs structure to user space.
 * It must be changed if the nstatfs structure changes.
 */

struct nstatfs_overlay {
	long	f_spare[3];		/* for use later -- must be longs */
					/* to ensure quad alignment */
					/* for copying of below components */
					/* from kernel to user space */
	char	f_mntonname[MAX_MNT_PATHLEN];   /* directory on which mounted */
	char	f_mntfromname[MAX_MNT_PATHLEN];/* mounted filesystem */
	union mount_info mount_info;	/* mount options */
};
#endif /* _KERNEL */

/* forward decls for ANSI & C++ */
struct vfsops;
struct mount;
struct vnode;
struct nameidata;

/*
 * Structure per mounted file system.
 * Each mounted file system has an array of
 * operations and an instance record.
 * The file systems are put on a doubly linked list.
 */
struct mount {
	udecl_simple_lock_data(,m_lock)		/* multiprocessor exclusion */
	int		m_flag;			/* flags */
	int		m_funnel;		/* serial code compatibility */
	struct mount	*m_next;		/* next in mount list */
	struct mount	*m_prev;		/* prev in mount list */
	struct vfsops	*m_op;			/* operations on fs */
	struct vnode	*m_vnodecovered;	/* vnode we mounted on */
	struct vnode	*m_mounth;		/* list of vnodes this mount */
	udecl_simple_lock_data(,m_vlist_lock)	/* protect vnode list */
	uid_t		m_exroot;		/* exported mapping for uid 0 */
	uid_t		m_uid;			/* uid that performed mount */
	struct nstatfs	m_stat;			/* cache of fs stats */
	qaddr_t		m_data;			/* private data */
	/* information used to control NFS server console error messages */
	struct {
		int n_noexport;	/* # of no export messages */
		int last_noexport;	/* secs. since last no export msg */
		int n_stalefh;	/* # of stale fh messages */
		int last_stalefh;	/* secs. since last stale fh msg */
	} m_nfs_errmsginfo;
#if	SEC_ARCH
	tag_t		m_tag[SEC_TAG_COUNT];	/* for unlabeled filesystems */
#endif
	lock_data_t	m_unmount_lock;		/* pathname/unmount synch */
};

/*
 * Mount flags.
 */
#define	M_RDONLY	0x00000001	/* read only filesystem */
#define	M_SYNCHRONOUS	0x00000002	/* file system written synchronously */
#define	M_NOEXEC	0x00000004	/* can't exec from filesystem */
#define	M_NOSUID	0x00000008	/* don't honor setuid bits on fs */
#define	M_NODEV		0x00000010	/* don't interpret special files */
#define	M_NOATIMES	0x00000040	/* don't update access time on read */
#define	M_GRPID		0x00004000	/* new files get parent dir's group */
#define	M_MLSD		0x00000400	/* fs uses multi-level secure dirs */
#define	M_SECURE	0x00000800	/* file system is labeled */

/*
 * exported mount flags.
 */
#define	M_EXPORTED	0x00000100	/* file system is exported */
#define	M_EXRDONLY	0x00000200	/* exported read only */
#define M_EXRDMOSTLY    0x00000400      /* exported ro to most */
/*
 * Flags set by internal operations.
 */
#define	M_LOCAL		0x00001000	/* filesystem is stored locally */
#define	M_QUOTA		0x00002000	/* quotas are enabled on filesystem */
/*
 * Mask of flags that are visible to statfs()
 */
#define	M_VISFLAGMASK	0x0000ffff
/*
 * filesystem control flags.
 */
#define	M_UPDATE	0x00010000	/* not a real mount, just an update */
#define	M_MPBUSY	0x00020000	/* sync/unmount in progress */
#define M_FMOUNT	0x00040000	/* forcibly mount, even if not clean */
#define M_DUAL  	0x02000000	/* dual mount of split mirror */
#if	MACH
/*
 * MACH swap info
 */
#define	M_SWAP_PREFER	0x00080000	/* prefer to swap here */
#define	M_SWAP_NEVER	0x00100000	/* never swap here */
#endif
#define M_IOERROR	0x00200000	/* I/O error */
#define M_PRECIOUS	0x00400000	/* tell unmount to not deallocate */
#define	M_NEWRDDIR	0x00800000	/* uses new readdir style */
#define M_MPWANT	0x01000000	/* someone waiting for busy vfs */


/* 
 * SVR3 and SVID-3 flags
 */

#define MS_DATA		0x000000020	/* called with 6 arguments */
#define MS_RDONLY	M_RDONLY
#define MS_NOSUID	M_NOSUID
#define MS_REMOUNT	M_UPDATE

/* 
 * Maximum length of a filesystem name within the vfssw table.
 */
#define MAX_VFSOPS_FSNAME  16

struct vfsops_with_fsname {
	struct vfsops  *vops_ptr;
	char   fsname[MAX_VFSOPS_FSNAME];
};

/*
 * Used with mount system call to determine specific index of a filesystem
 * name within the vfssw table.
 */
struct vfsops_fsname_args {
	char  fsname[MAX_VFSOPS_FSNAME];
	int   ret_index;
};


/*
 * Operations supported on mounted file system.
 */
struct vfsops {
	int	(*vfs_mount) __((struct mount *, char *, caddr_t, struct nameidata *));
	int	(*vfs_start) __((struct mount *, int flags));
	int	(*vfs_unmount) __((struct mount *, int));
	int	(*vfs_root) __((struct mount *, struct vnode **));
	int	(*vfs_quotactl) __((struct mount *, int, uid_t, caddr_t));
	int	(*vfs_statfs) __((struct mount *));
	int	(*vfs_sync) __((struct mount *, int));
	int	(*vfs_fhtovp) __((struct mount *, struct fid *, struct vnode **));
	int	(*vfs_vptofh) __((struct vnode *, struct fid *));
	int	(*vfs_init) ();
	int	(*vfs_mountroot) __((struct mount *, struct vnode **));
	int	(*vfs_swapvp) ();
};

#ifdef	_KERNEL

#if SER_COMPAT
#define	MOUNT_FUNNEL(mp)	((mp)->m_funnel)
#else
#define	MOUNT_FUNNEL(mp)	(0)
#endif

#define _VFSOP_(f,mp,args,ret)						\
MACRO_BEGIN								\
	if (!MOUNT_FUNNEL(mp)) {					\
		(ret) = (*(mp)->m_op->f)args;				\
	} else {							\
		unix_master();						\
		(ret) = (*(mp)->m_op->f)args;				\
		unix_release();						\
	}								\
MACRO_END

#define	_VFSOPV_(f,vp,args,ret)						\
MACRO_BEGIN								\
	if (!MOUNT_FUNNEL((vp)->v_mount)) {				\
		(ret) = (*((vp)->v_mount->m_op->f))args;		\
	} else {							\
		unix_master();						\
		(ret) = (*((vp)->v_mount->m_op->f))args;		\
		unix_release();						\
	}								\
MACRO_END

#define VFS_MOUNT(M,P,D,N,r)		_VFSOP_(vfs_mount,(M),((M),(P),(D),(N)),(r))
#define	VFS_START(MP,FL,r)		_VFSOP_(vfs_start,(MP),((MP),(FL)),(r))
#define	VFS_UNMOUNT(MP,F,r)		_VFSOP_(vfs_unmount,(MP),((MP),(F)),(r))
#define	VFS_ROOT(MP,VPP,r)		_VFSOP_(vfs_root,(MP),((MP),(VPP)),(r))
#define	VFS_QUOTACTL(MP,C,U,A,r)	_VFSOP_(vfs_quotactl,(MP),((MP),(C),(U),(A)),r)
#define	VFS_STATFS(MP,r)		_VFSOP_(vfs_statfs,(MP),(MP),(r))
#define	VFS_SYNC(MP,WF,r)		_VFSOP_(vfs_sync,(MP),((MP),(WF)),(r))
#define	VFS_FHTOVP(MP,FP,VP,r)		_VFSOP_(vfs_fhtovp,(MP),((MP),(FP),(VP)),(r))
#define	VFS_VPTOFH(VP,FIDP,r)		_VFSOPV_(vfs_vptofh,(VP),((VP),(FIDP)),(r))
#define	VFS_MOUNTROOT(MP,VPP,r)		_VFSOP_(vfs_mountroot,(MP),((MP),(VPP)),(r))
#define	VFS_SWAPVP(MP,VPP,r)		_VFSOP_(vfs_swapvp,(MP),((MP),(VPP)),(r))
#endif	/* _KERNEL */

/*
 * forcibly flags for vfs_umount().
 * waitfor flags to vfs_sync() and getfsstat()
 */
#define MNT_FORCE	0x1
#define MNT_NOFORCE	0x2
#define	MNT_SKIPSYSTEM	0x4
#define MNT_WAIT	0x1
#define MNT_NOWAIT	0x2

#ifdef	_KERNEL
/*
 * Mount structure locking constraints.
 *	Field		Constraint
 *	-----		----------
 *	m_next		mountlist_lock
 *	m_prev		mountlist_lock
 *	m_op		m_lock
 *	m_vnodecovered	read-only?	XXX
 *	m_mounth	m_vlist_lock
 *	m_flag		m_lock
 *	m_exroot	m_lock
 *	m_stat		m_lock
 *	m_data		read-only
 #ifdef SEC_ARCH
 *	m_tag		read_only!
 #endif
 *
 * Additional mount synchronization constraints.  [XXX]
 */

/*
 * The mount lock protects the contents of the mount structure from
 * other processors.  Only needed for NCPUS > 1.
 */
udecl_simple_lock_info(extern, mount_lockinfo)
#define	MOUNT_LOCK(mp)		usimple_lock(&(mp)->m_lock)
#define	MOUNT_UNLOCK(mp)	usimple_unlock(&(mp)->m_lock)
#define	MOUNT_LOCK_INIT(mp)	usimple_lock_setup(&(mp)->m_lock,mount_lockinfo)
#define	MOUNT_LOCK_HOLDER(mp)	SLOCK_HOLDER(&(mp)->m_lock)

/*
 * The mount vnode list lock guards the list of vnodes associated
 * with a mount point.  Only needed for NCPUS > 1.
 */
udecl_simple_lock_info(extern, mount_vlist_lockinfo)
#define	MOUNT_VLIST_LOCK(mp)	usimple_lock(&(mp)->m_vlist_lock)
#define	MOUNT_VLIST_UNLOCK(mp)	usimple_unlock(&(mp)->m_vlist_lock)
#define	MOUNT_VLIST_LOCK_INIT(mp) usimple_lock_setup(&(mp)->m_vlist_lock,\
						     mount_vlist_lockinfo)

/*
 * The unmount lock synchronizes pathname translation (crossing
 * of mount points) with filesystem unmounting.  It is acquired for
 * reading by namei() and getvfs(), and acquired for writing by
 * unmount().
 * NOTE: these could be optimized for the root FS (to do nothing)
 *	 since the root cannot be unmounted.
 */

extern struct lockinfo *unmount_lockinfo;
#define	UNMOUNT_TRY_READ(mp)      lock_try_read_assert(&(mp)->m_unmount_lock)
#define	UNMOUNT_TRY_READ_NOSLP(mp) lock_try_read(&(mp)->m_unmount_lock)
#define	UNMOUNT_WRITE_LOCK(mp)	  lock_write(&(mp)->m_unmount_lock)
#define	UNMOUNT_WRITE_UNLOCK(mp)  lock_write_done(&(mp)->m_unmount_lock)
#define	UNMOUNT_READ_UNLOCK(mp)	  lock_read_done(&(mp)->m_unmount_lock)
#define	UNMOUNT_LOCK_INIT(mp)	  lock_setup(&(mp)->m_unmount_lock,\
					   unmount_lockinfo, TRUE)

/*
 * Mount list lock operations.
 */
udecl_simple_lock_info(extern, mountlist_lockinfo)
#define	MOUNTLIST_LOCK()	usimple_lock(&mountlist_lock)
#define	MOUNTLIST_UNLOCK()	usimple_unlock(&mountlist_lock)
#define	MOUNTLIST_LOCK_INIT()	usimple_lock_setup(&mountlist_lock,\
						  mountlist_lockinfo)

/*
 * Lock operations on the vfssw.  Used for addition/deletion of
 * file systems.
 */
extern struct lockinfo *vfssw_lockinfo;

#define VFSSW_READ_LOCK()	lock_read(&vfssw_lock);
#define VFSSW_WRITE_LOCK()	lock_write(&vfssw_lock);
#define VFSSW_WRITE_UNLOCK()	lock_done(&vfssw_lock);
#define VFSSW_READ_UNLOCK()	lock_done(&vfssw_lock);
#define VFSSW_LOCK_INIT()	lock_setup(&vfssw_lock, vfssw_lockinfo, TRUE)

#define NULLMOUNT	((struct mount *) 0)
#define DEADMOUNT	(&dead_mount)

/*
 * exported vnode operations and globals
 */
_BEGIN_CPLUSPLUS
extern void	vfs_remove();                        /* remove a vfs from mount list */
extern struct	mount *getvfs __((fsid_t *));        /* return vfs given fsid */
extern int	vfs_busy __((struct mount *, int));  /* mark filesystem busy */
extern void	vfs_unbusy __((struct mount *));     /* mark filesystem not busy */
extern struct	mount *rootfs;		/* ptr to root mount structure */
extern struct	mount dead_mount; 	/* dead mount structure */
extern struct	vfsops_with_fsname vfssw[]; /* mount filesystem type switch */
extern lock_data_t vfssw_lock;		/* guard vfssw */
udecl_simple_lock_data(extern,mountlist_lock)	/* guard mount list */
_END_CPLUSPLUS

extern int	nmount;			/* number of ufs mount structs */
extern int      nmount_max;             /* number of entries in mount_zone */

#endif	/* _KERNEL */
#endif	/* _SYS_MOUNT_H_ */
