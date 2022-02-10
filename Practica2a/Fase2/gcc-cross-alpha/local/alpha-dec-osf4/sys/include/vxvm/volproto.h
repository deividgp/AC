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

#pragma	ident	"@(#)$RCSfile: volproto.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1995/01/31 20:43:59 $"

/* @(#)src/common/uts/io/vxvm/volproto.h	1.2 03 Sep 1993 15:55:57 -  */
/*
 * Copyright(C)1993 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 * 
 *               RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *               VERITAS SOFTWARE
 * 4800 GREAT AMERICA PARKWAY, SANTA CLARA, CA 95054
 */
/*
 * 10-13-93	Wai Yim
 * Merged with 1.2.1.1 mp code.
 *
 */


/*
 * sys/volproto.h - volume manager kernel prototype file
 */

#ifndef	SYS_VOLPROTO_H
#define	SYS_VOLPROTO_H

#ifdef	__STDC__
typedef int 		VOID;
#ifndef __alpha
/*
 * Functions from the kernel that have no existing prototypes in any
 * included header files.
 */
extern void		bp_mapin(struct buf *);
extern void		fshadbad(dev_t, daddr_t);
extern ulong		kmem_avail();
#endif /* !__alpha */

/*
 * Functions from vol.c
 */
extern int		volinit();
extern int		volopen(dev_t *, int, int, struct cred *);
extern int		volclose(dev_t, int, int, struct cred *);
extern int		volread(dev_t, struct uio *, struct cred *);
extern int		volwrite(dev_t, struct uio *, struct cred *);
extern int		volprint(dev_t, char *);
extern int		volsize(dev_t);
extern int		volstrategy(struct buf *);
extern void		vol_breakup(void (*)(), buf_t *, long);
extern VOID             voliodone(struct buf *);
extern void		voliocleanup(struct volcb *);
extern int		volexcept(struct volcb *, int);
extern int		volkdetach(dev_t, char *, int);
extern struct volbuf	*volbuf_alloc();
extern struct volcb	*volcb_alloc();
extern void		volcb_free(struct volcb *);
extern void		volsetinterlock(struct volcb *);
extern void		volfreeinterlock(struct volcb *);
extern void		vollock(struct voltab *);
extern void		volunlock(struct voltab *);
extern void		volactive(struct voltab *);
extern void		volinactive(struct voltab *);
extern void		volreactive(struct voltab *);
extern struct volio	*volfindvolio(struct volume *, struct buf *);
extern struct plex	*volfindplex(struct volume *, caddr_t);
extern struct subdisk	*volfindsub(struct volume *, caddr_t);
#ifdef	__alpha 
extern void		voliod_error();
#else	/* !__alpha */
extern int		voliod_error();
#endif /* __alpha */
extern void		vold_signal();

/*
 * Functions from volblog.c
 */
#ifdef	__alpha 
extern void		voliod_log(dev_t);
#else	/* !__alpha */
extern int		voliod_log(dev_t);
#endif /* __alpha */
extern int		vollogstart(struct volcb *);
extern int		vollogio(struct volume *, struct volcb *, int, int, int);
extern int		vollogstrategy(struct buf *, struct volcb *,
				struct plex *, int);
extern void		vollogiodone(struct volcb *);

/*
 * Functions from volioctl.c
 */
extern int		volioctl(dev_t, int, caddr_t, int, struct cred *,
				 int *);
extern void		volspecsetlock(struct volume *, struct volio *);
extern void		volspecfreelock(struct volume *, struct volio *);
extern void		volspecialbreakup(struct buf *);
extern void		volspecialbigbreakup(struct buf *);
extern void		volspecialiodone(struct volcb *);

/*
 * Functions from volklog.c
 */
extern int		volklog(int, struct diskgroup *, union volklogent *,
				int, int);
extern int		volklog_dgalloc(struct diskgroup *, long);
extern int		volklog_dgsize(struct diskgroup *);
extern int		volklog_alloc(struct voldisk *, int,
				struct volklogarea *, int);
extern int		volklog_free(struct voldisk *, int);
extern int		volklog_dgerrlist(struct diskgroup *, 
				struct voldg_errlist *, int);
extern int		volklog_errlist(struct voldisk *, 
				struct voldisk_errlist *, int);
extern int		volklog_listents(struct diskgroup *,
				union volklogent *, int);

#ifndef __alpha
#ifdef ROOTABILITY
/*
 * Functions from volroot.c
 */
extern int	vol_rootable_open(dev_t *, int, int, struct cred *);
extern int	vol_vrfy_replace(struct volume *, struct volume *);
extern int	vol_replace_volume(caddr_t);
extern int	vol_cmt_replace(struct volume *, struct volume *);
extern void	vol_clear_bootargs();
extern void	vol_set_bootargs(char *);
#endif / * ROOTABILITY */
#endif / * __alpha */

/*
 * Functions from volted.c
 */
#if defined(TED_ACTIVE)

extern _VOID	*Xvolmemalloc(ulong_t, char *, int);
extern _VOID	*Xvolmemzalloc(ulong_t, char *, int);
extern _VOID	*Xvolmemalloc_nosleep(ulong_t, char *, int);
extern _VOID	*Xvolmemzalloc_nosleep(ulong_t, char *, int);
extern void		Xvolmemfree(ulong_t, char *,_VOID *, int);
extern struct plex	*_ted_volfindplex(struct volume *, caddr_t);
extern int	_ted_volfindvolio(struct volume *, struct volio *, long);
extern int	_ted_volcb_interlk(struct volcb *, struct volume *);
extern int	_ted_findvolcb(struct volcb *, struct volcb *);
extern int	_ted_findvolbuf(struct volbuf *, struct volbuf *);
extern int	_ted_plexfindsd(struct subdisk *, struct plex *);
extern int	_ted_spinlockheld(int);
extern int	_ted_setpri(int, int);
extern void	_vol_sp_putholdq(struct volspin *, struct volted_pinfo *);
extern void	_vol_sp_getholdq(struct volspin *, struct volted_pinfo *);
extern void	_vol_sl_putholdq(struct volsleep *, struct volted_pinfo *);
extern void	_vol_sl_getholdq(struct volsleep *, struct volted_pinfo *);
extern void	_vol_sl_putwantq(struct volted_pinfo *, struct volsleep *);
extern void	_vol_sl_getwantq(struct volted_pinfo *, struct volsleep *);
extern void	_vol_sy_putwantq(struct volted_pinfo *, struct volsync *);
extern void	_vol_sy_getwantq(struct volted_pinfo *, struct volsync *);
extern void	_vol_allocspinlock(ulong_t, char *, struct volspin *, int);
extern void	_vol_freespinlock(ulong_t, char *, struct volspin *);
extern void	_vol_spinlock(struct volspin *);
extern void	_vol_unspinlock(struct volspin *);
extern void	_vol_allocsleeplock(ulong_t, char *, struct volsleep *);
extern void	_vol_freesleeplock(ulong_t, char *, struct volsleep *);
extern void	_vol_sleeplock(struct volsleep *);
extern void	_vol_unsleeplock(struct volsleep *);
extern void	_vol_trysleeplock(struct volsleep *, int *);
extern void	_vol_allocsync(ulong_t, char *, struct volsync *);
extern void	_vol_freesync(ulong_t, char *, struct volsync *);
extern void	_vol_syncwait(struct volsync *, struct volspin *);
extern void	_vol_syncwaitsig(struct volsync *, struct volspin *, int *);
extern void	_vol_syncsig(struct volsync *);

#endif /* TED_ACTIVE */

/*
 * Functions from volspec.c
 */
extern int		volsopen_real(dev_t *, int, int, struct cred *);
extern int		volsclose_real(dev_t, int, int, struct cred *);
extern int		volsread_real(dev_t, struct uio *, struct cred *);
extern int		volswrite_real(dev_t, struct uio *, struct cred *);
extern int		volsioctl_real(dev_t, int, caddr_t, int, struct cred *,
				int *);
extern int		vols_volinfo(int, caddr_t, int, struct cred *, int *);
extern void		vol_event_init();
extern int		vol_log_event(struct volevent *);
extern int		volstrcmp(char *, char *);
extern int		vol_vrfy_new(struct volume *);
extern struct diskgroup	*volfinddg(volrid_t);
extern struct voldisk	*volfindd(volrid_t);
extern struct voldisk	*volfinddm(struct diskgroup *, volrid_t);
extern struct volume	*volfindvol(struct volume *, volrid_t);
extern struct volume	*volfindvol_dev(struct volume *, dev_t);
extern struct plex	*volfindpl(struct volume *, volrid_t);
extern struct plex	*volfindplmin(struct volume *, minor_t);
extern struct subdisk	*volfindsd(struct volume *, volrid_t);
extern void		volsd_open(struct subdisk *);
extern void		volsd_close(struct subdisk *);
extern void		volsd_ref(struct subdisk *);
extern void		volsd_unref(struct subdisk *);
extern int		voldisk_open(struct voldisk *, struct cred *);
extern void		voldisk_close(struct voldisk *, struct cred *);
extern void		volstrcpy(char *, char *);

/*
 * Functions from plex.c
 */
extern int	plexopen_real(dev_t *, int, int, struct cred *);
extern int	plexclose_real(dev_t, int, int, struct cred *);
extern int	plexread_real(dev_t, struct uio *, struct cred *);
extern int	plexwrite_real(dev_t, struct uio *, struct cred *);
extern int	plexioctl_real(dev_t, int, caddr_t, int, struct cred *, int *);

#ifdef __alpha
/*
 * Functions from dki_osf.c
 */
extern void		vol_biodone(struct buf *);
extern int		drv_getparm(ulong_t, ulong_t);
extern void		*osf_kmem_alloc(unsigned int, int, int);
extern void		osf_kmem_free(void, unsigned int);
extern struct buf	*getrbuf(long);
extern void		freerbuf(struct buf *);
extern int		vol_osf_mincnt(struct buf *);
extern int		physiock(void, struct buf *, dev_t, int, daddr_t, struct uio *);
extern int		otype_valid(int);
extern void		otype_increment(int *, int);
extern void		otype_decrement(int *, int);
extern void		otype_set(int *, int, int);
extern int		otype_get(int *, int);
#endif /* __alpha */

#else	/* __STDC__ */

typedef	void		VOID;
#ifndef __alpha
/*
 * Functions from the kernel that have no existing prototypes in any
 * included header files.
 */
extern void		bp_mapin();
extern void		fshadbad();
extern ulong		kmem_avail();
#endif /* !__alpha */

/*
 * Functions from vol.c
 */
extern int		volinit();
extern int		volopen();
extern int		volclose();
extern int		volread();
extern int		volwrite();
extern int		volprint();
extern int		volsize();
extern int		volstrategy();
extern void		vol_breakup();
extern VOID		voliodone();
extern void		voliocleanup();
extern int		volexcept();
extern int		volkdetach();
extern struct volbuf	*volbuf_alloc();
extern struct volcb	*volcb_alloc();
extern void		volcb_free();
extern void		volsetinterlock();
extern void		volfreeinterlock();
extern void		vollock();
extern void		volunlock();
extern void		volactive();
extern void		volinactive();
extern void		volreactive();
extern struct volio	*volfindvolio();
extern struct plex	*volfindplex();
extern struct subdisk	*volfindsub();
#ifdef	__alpha 
extern void		voliod_error();
#else	/* !__alpha */
extern int		voliod_error();
#endif	/* __alpha */
extern void		vold_signal();

/*
 * Functions from volblog.c
 */
#ifdef	__alpha 
extern void		voliod_log();
#else	/* !__alpha */
extern int		voliod_log();
#endif /* __alpha */
extern int		vollogstart();
extern int		vollogio();
extern int		vollogstrategy();
extern void		vollogiodone();

/*
 * Functions from volioctl.c
 */
extern int		volioctl();
extern void		volspecsetlock();
extern void		volspecfreelock();
extern void		volspecialbreakup();
extern void		volspecialbigbreakup();
extern void		volspecialiodone();

/*
 * Functions from volklog.c
 */
extern int		volklog();
extern int		volklog_dgalloc();
extern int		volklog_dgsize();
extern int		volklog_alloc();
extern int		volklog_free();
extern int		volklog_dgerrlist();
extern int		volklog_errlist();
extern int		volklog_listents();

/*
 * Functions from volroot.c
 */
extern int	vol_rootable_open();
extern int	vol_vrfy_replace();
extern int	vol_replace_volume();
extern int	vol_cmt_replace();
extern void	vol_set_bootargs();
extern void	vol_clear_bootargs();

/*
 * Functions from volted.c
 */
#if defined(TED_ACTIVE)

extern _VOID	*Xvolmemalloc();
extern _VOID	*Xvolmemzalloc();
extern _VOID	*Xvolmemalloc_nosleep();
extern _VOID	*Xvolmemzalloc_nosleep();
extern struct plex	*_ted_volfindplex();
extern int	_ted_volfindvolio();
extern int	_ted_volcb_interlk();
extern int	_ted_findvolcb();
extern int	_ted_findvolbuf();
extern int	_ted_plexfindsd();
extern int	_ted_spinlockheld();
extern int	_ted_setpri();
extern void	_vol_sp_putholdq();
extern void	_vol_sp_getholdq();
extern void	_vol_sl_putwantq();
extern void	_vol_sl_getwantq();
extern void	_vol_sy_putwantq();
extern void	_vol_sy_getwantq();
extern void	_vol_allocspinlock();
extern void	_vol_freespinlock();
extern void	_vol_spinlock();
extern void	_vol_unspinlock();
extern void	_vol_allocsleeplock();
extern void	_vol_freesleeplock();
extern void	_vol_sleeplock();
extern void	_vol_unsleeplock();
extern void	_vol_trysleeplock();
extern void	_vol_allocsync();
extern void	_vol_freesync();
extern void	_vol_syncwait();
extern void	_vol_syncwaitsig();
extern void	_vol_syncsig();

#endif /* TED_ACTIVE */

/*
 * Functions from volspec.c
 */
extern int		volsopen_real();
extern int		volsclose_real();
extern int		volsread_real();
extern int		volswrite_real();
extern int		volsioctl_real();
extern int		vols_volinfo();
extern void		vol_event_init();
extern int		vol_log_event();
extern int		volstrcmp();
extern int		vol_vrfy_new();
extern struct diskgroup	*volfinddg();
extern struct voldisk	*volfindd();
extern struct voldisk	*volfinddm();
extern struct volume	*volfindvol();
extern struct volume	*volfindvol_dev();
extern struct plex	*volfindpl();
extern struct plex	*volfindplmin();
extern struct subdisk	*volfindsd();
extern void		volsd_open();
extern void		volsd_close();
extern void		volsd_ref();
extern void		volsd_unref();
extern int		voldisk_open();
extern void		voldisk_close();
extern void		volstrcpy();

/*
 * Functions from plex.c
 */

extern int	plexopen_real();
extern int	plexclose_real();
extern int	plexread_real();
extern int	plexwrite_real();
extern int	plexioctl_real();

#ifdef __alpha
/*
 * Functions from dki_osf.c
 */
extern void		vol_biodone();
extern int		drv_getparm();
extern void		*osf_kmem_alloc();
extern void		osf_kmem_free();
extern struct buf	*getrbuf();
extern void		freerbuf();
extern int		vol_osf_mincnt();
extern int		physiock();
extern int		otype_valid();
extern void		otype_increment();
extern void		otype_decrement();
extern void		otype_set();
extern int		otype_get();
#endif /* __alpha */

#endif	/* __STDC__ */
/*
 * The following definitions are used to compile out the instrumentation
 * from the code used in testing.
 */
#if defined(TED_ACTIVE)

extern int ipl;

#else /* TED_ACTIVE */

#define	TED_ASSERT(name, cond)
#define	TED_CHECKPOINT(name)
#define	TED_COMMENT(stuff)
#define	TED_IOFAIL(name, dev, start, len, rdwr)
#define	TED_TRIG_IODONE(bp)

#endif /* TED_ACTIVE */

#endif	/* SYS_VOLPROTO_H */
