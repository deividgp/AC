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

#pragma	ident	"@(#)$RCSfile: vollocal.h,v $ $Revision: 1.1.8.3 $ (DEC) $Date: 1995/03/24 18:47:26 $"

/* @(#)src/common/uts/io/vxvm/vollocal.h	1.2 03 Sep 1993 15:55:52 -  */
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
 * Alpha change log
 *
 * 09-29-93	Wai Yim
 * Merged alpha port with vxvm1.2.1 source.
 *
 * 09-30-93	Wai Yim
 * Merged 1.2.1.1mp code
 */

/*
 * sys/vollocal.h - volume manager localization macros
 */
#ifdef SVR4_0
/* Partition identification tags */

#define V_UNUSED        0x00            /* Unused slice */
#define V_ALTSCTR       0x0d            /* alternate sector slice */

#if     (_SYSTEMENV == 4)
#define SC_HAN(dev)     ((getminor(dev) >> 5) & 0x07)
#define SC_TCN(dev)     ((getminor(dev) >> 2) & 0x07)
#define SC_LUN(dev)     ((getminor(dev) & 0x03))
#else
#define SC_HAN(dev)     ((minor(dev) >> 5) & 0x07)
#define SC_TCN(dev)     ((minor(dev) >> 2) & 0x07)
#define SC_LUN(dev)     ((minor(dev) & 0x03))
#endif	/* _SYSTEMENV */

/* Reset a buffer after completed I/O so it can be used again.
 */
#define bioreset(bp) \
{\
        (bp)->b_flags &= ~(B_DONE|B_ERROR); \
        if ((bp)->b_flags & B_KERNBUF) \
                (bp)->b_error = 0; \
        (bp)->b_oerror = 0; \
}
#endif /* SVR4_0 */

#ifndef _SYS_VOLLOCAL_H
#define _SYS_VOLLOCAL_H

#ifdef __alpha
/*
 * disk_parms structure translated from from SVR4 vtoc.h.
 */
struct  disk_parms {
        u_long  dp_secsiz;      /* sector size; was uchar in SVR4 */
        u_char  dp_ptag;        /* partition tag; was ushort in SVR4 */
        u_long  dp_pnumsec;     /* #of sectors in partition */
};

#define VOL_PUB_SLICE_TAG       FS_LSMpubl
#define VOL_PRIV_SLICE_TAG      FS_LSMpriv
#define VOL_SIMPLE_TAG		FS_LSMsimp
#else /* !__alpha */
#define VOL_PUB_SLICE_TAG	0xe
#define VOL_PRIV_SLICE_TAG	0xf
#endif /* __alpha */

#ifdef _KERNEL

#ifdef __alpha
#define PAGEOFFSET CLOFSET
#endif /* __alpha */

/*
 * system-dependent feature enables
 */
#if !defined(NO_VXVM_LOADABLE) && !defined(VXVM_LOADABLE)
#ifdef __alpha
#define NO_VXVM_LOADABLE	/* default is set to not loadable */
#else /* !__alpha */
#define VXVM_LOADABLE		/* include SVR4.2 loadable module wrappers */
#endif /* __alpha */
#endif	/* !NO_VXVM_LOADABLE */

/*
 * The following macros are for the kernel memory allocation routines used
 * by the Volume Manager.  They are switchable between DDI versions and
 * TED debugging versions.
 */
#ifdef __alpha
#define	_VOLMEMALLOC(sz)		osf_kmem_alloc(sz, KM_SLEEP, 0)
#define	_VOLMEMZALLOC(sz)		osf_kmem_alloc(sz, KM_SLEEP, 1)
#define	_VOLMEMALLOC_NOSLEEP(sz) 	osf_kmem_alloc(sz, KM_NOSLEEP, 0)
#define	_VOLMEMZALLOC_NOSLEEP(sz) 	osf_kmem_alloc(sz, KM_NOSLEEP, 1)
#define	_VOLMEMFREE(ptr, sz)		osf_kmem_free(ptr, sz)
#else /* !__alpha */
#define	_VOLMEMALLOC(sz)		kmem_alloc(sz, KM_SLEEP)
#define	_VOLMEMZALLOC(sz)		kmem_zalloc(sz, KM_SLEEP)
#define	_VOLMEMALLOC_NOSLEEP(sz) 	kmem_alloc(sz, KM_NOSLEEP)
#define	_VOLMEMZALLOC_NOSLEEP(sz) 	kmem_zalloc(sz, KM_NOSLEEP)
#define	_VOLMEMFREE(ptr, sz)		kmem_free(ptr, sz)
#endif /* __alpha */

#if	defined(TED_ACTIVE)

#define	volmemalloc(sz)		Xvolmemalloc(__LINE__, __FILE__, sz)
#define	volmemzalloc(sz)	Xvolmemzalloc(__LINE__, __FILE__, sz)
#define	volmemalloc_nosleep(sz) Xvolmemalloc_nosleep(__LINE__, __FILE__, sz)
#define	volmemzalloc_nosleep(sz) Xvolmemzalloc_nosleep(__LINE__, __FILE__, sz)
#define	volmemfree(ptr, sz)	Xvolmemfree(__LINE__, __FILE__, ptr, sz)

#else

#define	volmemalloc(sz)			_VOLMEMALLOC(sz)			
#define	volmemzalloc(sz)		_VOLMEMZALLOC(sz)		
#define	volmemalloc_nosleep(sz) 	_VOLMEMALLOC_NOSLEEP(sz) 	
#define	volmemzalloc_nosleep(sz) 	_VOLMEMZALLOC_NOSLEEP(sz) 	
#define	volmemfree(ptr, sz)		_VOLMEMFREE(ptr, sz)		

#endif /* TED_ACTIVE */

/*
 * Following macros are for calls out to lower level driver bdevsw entries.
 */
#if	defined(TED_ACTIVE)

#ifdef	__alpha 
#define VOL_DEV_STRATEGY(bp)						\
		do {							\
			TED_TRIG_IOSTRAT(bp);				\
			if ((bp)->b_flags & B_ERROR) {			\
				biodone(bp);				\
			} else {					\
				int ret;				\
				BDEVSW_STRATEGY(getmajor((bp)->b_edev),(bp),ret);\
			}						\
		} while (0)
#else /* !__alpha */
#define VOL_DEV_STRATEGY(bp)						\
		do {							\
			TED_TRIG_IOSTRAT(bp);				\
			if ((bp)->b_flags & B_ERROR) {			\
				biodone(bp);				\
			} else {					\
				(*bdevsw[getmajor((bp)->b_edev)].d_strategy)\
					(bp);				\
			}						\
		} while (0)
#endif /* __alpha */

#else /* !defined(TED_ACTIVE) */

#ifdef	__alpha 
#define VOL_DEV_STRATEGY(bp)						\
		{							\
			int ret;					\
			BDEVSW_STRATEGY(getmajor((bp)->b_edev), (bp), ret);\
		}
	
#else /* !__alpha */
#define VOL_DEV_STRATEGY(bp)						\
		(*bdevsw[getmajor((bp)->b_edev)].d_strategy)(bp)
#endif /* __alpha */

#endif /* defined(TED_ACTIVE) */

#ifdef	__alpha
#define VOL_DEV_OPEN(dev, cred_p, ret, priv)				\
	{								\
		int ddi_flag; 						\
		BDEVSW_FLAGS(getmajor((dev)), ddi_flag);		\
		if (!(ddi_flag & B_DDIDKI))				\
			BDEVSW_OPEN(getmajor((dev)), (dev), V_OFLAGS,	\
				OTYP_LYR, (ret), (cred_p), &(priv));	\
		else							\
			BDEVSW_DDI_OPEN(getmajor((dev)),(dev), V_OFLAGS,\
					OTYP_LYR, (cred_p), (ret));	\
	}
			
#else /* !__alpha */
#define VOL_DEV_OPEN(dev, cred_p)					\
		(*bdevsw[getmajor(dev)].d_open)(&(dev), V_OFLAGS, 	\
					       OTYP_LYR, cred_p)
#endif /* __alpha */

#ifdef __alpha
#define VOL_CDEV_CHECK(dev) \
		(cdevsw[getmajor(dev)].d_open ? 1 : 0)
#endif /* __alpha */

#ifdef	__alpha
#define VOL_CDEV_OPEN(dev, cred_p, ret, priv)				\
	{								\
		int ddi_flag; 						\
		CDEVSW_FLAGS(getmajor((dev)), ddi_flag);		\
		if (!(ddi_flag & C_DDIDKI))				\
			CDEVSW_OPEN(getmajor((dev)), (dev), V_OFLAGS,	\
			OTYP_LYR, &(dev), (ret), (cred_p), &(priv));	\
		else							\
			CDEVSW_DDI_OPEN(getmajor((dev)), (dev), V_OFLAGS,	\
					OTYP_LYR, (cred_p), (ret));	\
	}
#else /* !__alpha */
#define VOL_CDEV_OPEN(dev, cred_p)					\
		(*cdevsw[getmajor(dev)].d_open)(&(dev), V_OFLAGS, 	\
					       OTYP_LYR, cred_p)
#endif /* __alpha */

#ifdef	__alpha
#define VOL_DEV_CLOSE(dev, cred_p, ret, priv)			   	\
	{								\
		int ddi_flag; 						\
		BDEVSW_FLAGS(getmajor((dev)), ddi_flag);		\
		if (!(ddi_flag & B_DDIDKI))				\
			BDEVSW_CLOSE(getmajor((dev)), (dev), V_OFLAGS,  \
				OTYP_LYR, (ret), (cred_p), &(priv));	\
		else							\
			BDEVSW_DDI_CLOSE(getmajor((dev)), (dev), V_OFLAGS,  \
				OTYP_LYR, (cred_p), (ret));		\
	}
#else /* !__alpha */
#define VOL_DEV_CLOSE(dev, cred_p)					\
		(*bdevsw[getmajor(dev)].d_close)((dev), V_OFLAGS, 	\
					       OTYP_LYR, cred_p)
#endif /* __alpha */

#ifdef	__alpha
#define VOL_CDEV_CLOSE(dev, cred_p, ret, priv)				\
	{								\
		int ddi_flag; 						\
		CDEVSW_FLAGS(getmajor((dev)), ddi_flag);		\
		if (!(ddi_flag & C_DDIDKI))				\
			CDEVSW_CLOSE(getmajor((dev)), (dev), V_OFLAGS,  \
				OTYP_LYR, (ret), (cred_p), &(priv));	\
		else							\
			CDEVSW_DDI_CLOSE(getmajor((dev)), (dev), V_OFLAGS,  \
				OTYP_LYR, (cred_p), (ret));		\
	}
#else /* !__alpha */
#define VOL_CDEV_CLOSE(dev, cred_p)					\
		(*cdevsw[getmajor(dev)].d_close)((dev), V_OFLAGS, 	\
					OTYP_LYR, (ret), (cred_p))
#endif /* __alpha */

#ifdef	__alpha
#define VOL_CDEV_IOCTL(dev, cmd, arg, cred_p, rval_p, priv, err)	\
	{								\
		int ddi_flag; 						\
		CDEVSW_FLAGS(getmajor((dev)), ddi_flag);		\
		if (!(ddi_flag & C_DDIDKI))				\
			CDEVSW_IOCTL(getmajor((dev)), (dev), (cmd), (arg), 	\
				 V_OFLAGS, (err), (cred_p), &(priv), (rval_p));  \
		else							\
			CDEVSW_DDI_IOCTL(getmajor((dev)), (dev), (cmd), (arg), 	\
				 V_OFLAGS, (cred_p), (rval_p), (err));   \
	}
#else /* !__alpha */
#define VOL_CDEV_IOCTL(dev, cmd, arg, cred_p, rval_p)			\
		(*cdevsw[getmajor(dev)].d_ioctl)((dev), (cmd), (arg),	\
					V_OFLAGS, (cred_p), (rval_p))
#endif /* __alpha */

#ifdef __alpha
#define VOL_DEV_SIZE_FN(dev)						\
		(bdevsw[getmajor(dev)].d_psize)
#else /* !__alpha */
#define VOL_DEV_SIZE_FN(dev)						\
		(bdevsw[getmajor(dev)].d_size)
#endif __alpha

#ifdef __alpha

#ifdef MP
#define SPLHI spldevhigh
#define VOL_CREATE_DAEMON()     spldevhigh()
#define VOL_EXIT_DAEMON()       return (0)
#else /* MP */
#define VOL_CREATE_DAEMON()
#define VOL_EXIT_DAEMON()       return(0)
#endif /* MP */

#else /* !__alpha */
/*
 * The following macros control the creation and deletion of daemon
 * processes.  These macros are VERY NON DDI/DKI compliant and so are
 * reduced to NULL if we are trying to be DDI compliant.
 * 
 * The p_exec pointer in the proc structure points to the held vnode for
 * the exec'd file.  Since we are becoming daemon kernel processes there
 * is no need to keep this vnode so we release it.  If we later exit,
 * then a check will be made before re-releasing the vnode so no problem
 * should occur with the exit.  If the system is brought down without
 * the process exiting, then the vnode will not be held and so the
 * shutdown will not be delayed.
 */

#ifdef MP

#define _VOL_CREATE_DAEMON()	(void)splhi()
#ifdef SVR4_0
#define _VOL_EXIT_DAEMON()	return 0
#else
#define _VOL_EXIT_DAEMON()	(return 0)
#endif /* SVR4_0 */

#else /* !MP */

#if defined(DDI_COMPLIANT)

#define _VOL_CREATE_DAEMON()
#define _VOL_EXIT_DAEMON()	exit(CLD_EXITED, 0)

#else /* !DDI_COMPLIANT */

#ifdef SYSV_4_0

#define _VOL_CREATE_DAEMON()						\
	do {								\
		proc_t		*cprocp;				\
									\
		drv_getparm(UPROCP, (ulong_t *)&cprocp);		\
		if (cprocp->p_exec) {					\
			VN_RELE(cprocp->p_exec);			\
			cprocp->p_exec = NULLVP;			\
		}							\
		relvm(u.u_procp);					\
	} while (0)

#else /* !SYSV_4_0 */

#define _VOL_CREATE_DAEMON()						\
	do {								\
		proc_t		*cprocp;				\
									\
		drv_getparm(UPROCP, (ulong_t *)&cprocp);		\
		if (cprocp->p_exec) {					\
			VN_RELE(cprocp->p_exec);			\
			cprocp->p_exec = NULLVP;			\
		}							\
		relvm(u.u_procp, 1);					\
	} while (0)

#endif /* SYSV_4_0 */

#define _VOL_EXIT_DAEMON()						\
	do {								\
		proc_t		*cprocp;				\
									\
		drv_getparm(UPROCP, (ulong_t *)&cprocp);		\
		cprocp->p_cursig = 0;					\
		if (cprocp->p_curinfo != NULL) {			\
			kmem_free((_VOID *)cprocp->p_curinfo,		\
				  sizeof (*cprocp->p_curinfo));		\
			cprocp->p_curinfo = NULL;			\
		}							\
		exit(CLD_EXITED, 0);					\
	} while (0)

#endif /* DDI_COMPLIANT */

#endif /* MP */

#if defined(lint)

#define VOL_CREATE_DAEMON()	((void)splhi())
#define VOL_EXIT_DAEMON()	((void)splhi())

#else /* lint */

#define VOL_CREATE_DAEMON()	_VOL_CREATE_DAEMON()
#define VOL_EXIT_DAEMON()	_VOL_EXIT_DAEMON()

#endif /* lint */
#endif /* __alpha */

/*
 * The following defines provide a portable method for OEMs to replace
 * the SVR4.2 cmn_err calls with their own variety of messaging and/or
 * logging schemes.
 */
#ifdef __alpha
#include	<dec/binlog/binlog.h>
#define VOL_NOTE_MSG1(a)		{ log(LOG_NOTICE, a); \
		vol_note_log1(a); }
#define VOL_NOTE_MSG2(a,b)		{ log(LOG_NOTICE, a,b); \
		vol_note_log2(a,b); }
#define VOL_NOTE_MSG3(a,b,c)		{ log(LOG_NOTICE, a,b,c); \
		vol_note_log3(a,b,c); }
#define VOL_NOTE_MSG4(a,b,c,d)		{ log(LOG_NOTICE, a,b,c,d); \
		vol_note_log4(a,b,c,d); }
#define VOL_NOTE_MSG5(a,b,c,d,e)	{ log(LOG_NOTICE, a,b,c,d,e); \
		vol_note_log5(a,b,c,d,e); }
#define VOL_NOTE_MSG6(a,b,c,d,e,f)	{ log(LOG_NOTICE, a,b,c,d,e,f); \
		vol_note_log6(a,b,c,d,e,f); }
#define VOL_NOTE_MSG7(a,b,c,d,e,f,g)	{ log(LOG_NOTICE, a,b,c,d,e,f,g); \
		vol_note_log7(a,b,c,d,e,f,g); }
#define VOL_WARN_MSG1(a)		{ log(LOG_WARNING, a); \
		vol_warn_log1(a); }
#define VOL_WARN_MSG2(a,b)		{ log(LOG_WARNING, a,b); \
		vol_warn_log2(a,b); }
#define VOL_WARN_MSG3(a,b,c)		{ log(LOG_WARNING, a,b,c); \
		vol_warn_log3(a,b,c); }
#define VOL_WARN_MSG4(a,b,c,d)		{ log(LOG_WARNING, a,b,c,d); \
		vol_warn_log4(a,b,c,d); }
#define VOL_WARN_MSG5(a,b,c,d,e)	{ log(LOG_WARNING, a,b,c,d,e); \
		vol_warn_log5(a,b,c,d,e); }
#define VOL_WARN_MSG6(a,b,c,d,e,f)	{ log(LOG_WARNING, a,b,c,d,e,f); \
		vol_warn_log6(a,b,c,d,e,f); }
#define VOL_WARN_MSG7(a,b,c,d,e,f,g)	{ log(LOG_WARNING, a,b,c,d,e,f,g); \
		vol_warn_log7(a,b,c,d,e,f,g); }
/*
 * For continuation messages use the LOG_INFO message type.
 */
#define VOL_CONT_MSG1(a)		{ log(LOG_INFO, a); \
		vol_cont_log1(a); }
#define VOL_CONT_MSG2(a,b)		{ log(LOG_INFO, a,b); \
		vol_cont_log2(a,b); }
#define VOL_CONT_MSG3(a,b,c)		{ log(LOG_INFO, a,b,c); \
		vol_cont_log3(a,b,c); }
#define VOL_CONT_MSG4(a,b,c,d)		{ log(LOG_INFO, a,b,c,d); \
		vol_cont_log4(a,b,c,d); }
#define VOL_CONT_MSG5(a,b,c,d,e)	{ log(LOG_INFO, a,b,c,d,e); \
		vol_cont_log5(a,b,c,d,e); }
#define VOL_CONT_MSG6(a,b,c,d,e,f)	{ log(LOG_INFO, a,b,c,d,e,f); \
		vol_cont_log6(a,b,c,d,e,f); }
#define VOL_CONT_MSG7(a,b,c,d,e,f,g)	{ log(LOG_INFO, a,b,c,d,e,f,g); \
		vol_cont_log7(a,b,c,d,e,f,g); }
#define VOL_PANIC_MSG1(a)	{ log(LOG_EMERG, a); \
		vol_panic_log1(a); }
#define VOL_PANIC_MSG2(a,b)	{ log(LOG_EMERG, a,b); \
		vol_panic_log2(a,b); }
#define VOL_PANIC_MSG3(a,b,c)	{ log(LOG_EMERG, a,b,c); \
		vol_panic_log3(a,b,c); }
#define VOL_PANIC_MSG4(a,b,c,d)	{ log(LOG_EMERG, a,b,c,d); \
		vol_panic_log4(a,b,c,d); }
#define VOL_PANIC_MSG5(a,b,c,d,e)	{ log(LOG_EMERG, a,b,c,d,e); \
		vol_panic_log5(a,b,c,d,e); }
#define VOL_PANIC_MSG6(a,b,c,d,e,f)	{ log(LOG_EMERG, a,b,c,d,e,f); \
		vol_panic_log6(a,b,c,d,e,f); }
#define VOL_PANIC_MSG7(a,b,c,d,e,f,g)	{ log(LOG_EMERG, a,b,c,d,e,f,g); \
		vol_panic_log7(a,b,c,d,e,f,g); }
#else /* !__alpha */
#define VOL_NOTE_MSG1(a)		cmn_err(CE_NOTE, a);
#define VOL_NOTE_MSG2(a,b)		cmn_err(CE_NOTE, a,b);
#define VOL_NOTE_MSG3(a,b,c)		cmn_err(CE_NOTE, a,b,c);
#define VOL_NOTE_MSG4(a,b,c,d)		cmn_err(CE_NOTE, a,b,c,d);
#define VOL_NOTE_MSG5(a,b,c,d,e)	cmn_err(CE_NOTE, a,b,c,d,e);
#define VOL_NOTE_MSG6(a,b,c,d,e,f)	cmn_err(CE_NOTE, a,b,c,d,e,f);
#define VOL_NOTE_MSG7(a,b,c,d,e,f,g)	cmn_err(CE_NOTE, a,b,c,d,e,f,g);
#define VOL_WARN_MSG1(a)		cmn_err(CE_WARN, a);
#define VOL_WARN_MSG2(a,b)		cmn_err(CE_WARN, a,b);
#define VOL_WARN_MSG3(a,b,c)		cmn_err(CE_WARN, a,b,c);
#define VOL_WARN_MSG4(a,b,c,d)		cmn_err(CE_WARN, a,b,c,d);
#define VOL_WARN_MSG5(a,b,c,d,e)	cmn_err(CE_WARN, a,b,c,d,e);
#define VOL_WARN_MSG6(a,b,c,d,e,f)	cmn_err(CE_WARN, a,b,c,d,e,f);
#define VOL_WARN_MSG7(a,b,c,d,e,f,g)	cmn_err(CE_WARN, a,b,c,d,e,f,g);
#define VOL_CONT_MSG1(a)		cmn_err(CE_CONT, a);
#define VOL_CONT_MSG2(a,b)		cmn_err(CE_CONT, a,b);
#define VOL_CONT_MSG3(a,b,c)		cmn_err(CE_CONT, a,b,c);
#define VOL_CONT_MSG4(a,b,c,d)		cmn_err(CE_CONT, a,b,c,d);
#define VOL_CONT_MSG5(a,b,c,d,e)	cmn_err(CE_CONT, a,b,c,d,e);
#define VOL_CONT_MSG6(a,b,c,d,e,f)	cmn_err(CE_CONT, a,b,c,d,e,f);
#define VOL_CONT_MSG7(a,b,c,d,e,f,g)	cmn_err(CE_CONT, a,b,c,d,e,f,g);
#define VOL_PANIC_MSG1(a)		cmn_err(CE_PANIC, a);
#define VOL_PANIC_MSG2(a,b)		cmn_err(CE_PANIC, a,b);
#define VOL_PANIC_MSG3(a,b,c)		cmn_err(CE_PANIC, a,b,c);
#define VOL_PANIC_MSG4(a,b,c,d)		cmn_err(CE_PANIC, a,b,c,d);
#define VOL_PANIC_MSG5(a,b,c,d,e)	cmn_err(CE_PANIC, a,b,c,d,e);
#define VOL_PANIC_MSG6(a,b,c,d,e,f)	cmn_err(CE_PANIC, a,b,c,d,e,f);
#define VOL_PANIC_MSG7(a,b,c,d,e,f,g)	cmn_err(CE_PANIC, a,b,c,d,e,f,g);
#endif /* __alpha */

/*
 * The following macros are for debugging purposes and if compiled in using
 * the OEM_DEBUG define, will cause some additional error messages to be
 * generated as appropriate under certain error conditions.  These messages
 * are NOT intended to replace the functionality of the TED_ASSERT
 * instrumentation but are provided as a simple mechanism for turning on
 * additional debugging information.
 *
 * Each message level represents the number of arguments supplied.
 */

#if defined(OEM_DEBUG)

#ifdef __alpha
#define VOL_DBG_MSG1(a)			log(LOG_DEBUG, a)
#define VOL_DBG_MSG2(a,b)		log(LOG_DEBUG, a,b)
#define VOL_DBG_MSG3(a,b,c)		log(LOG_DEBUG, a,b,c)
#define VOL_DBG_MSG4(a,b,c,d)		log(LOG_DEBUG, a,b,c,d)
#define VOL_DBG_MSG5(a,b,c,d,e)		log(LOG_DEBUG, a,b,c,d,e)
#define VOL_DBG_MSG6(a,b,c,d,e,f)	log(LOG_DEBUG, a,b,c,d,e,f)
#else /* !__alpha */
#define VOL_DBG_MSG1(a)			cmn_err(CE_WARN, a)
#define VOL_DBG_MSG2(a,b)		cmn_err(CE_WARN, a,b)
#define VOL_DBG_MSG3(a,b,c)		cmn_err(CE_WARN, a,b,c)
#define VOL_DBG_MSG4(a,b,c,d)		cmn_err(CE_WARN, a,b,c,d)
#define VOL_DBG_MSG5(a,b,c,d,e)		cmn_err(CE_WARN, a,b,c,d,e)
#define VOL_DBG_MSG6(a,b,c,d,e,f)	cmn_err(CE_WARN, a,b,c,d,e,f)
#endif /* __alpha */

#else /* OEM_DEBUG */

#define VOL_DBG_MSG1(a)
#define VOL_DBG_MSG2(a,b)
#define VOL_DBG_MSG3(a,b,c)
#define VOL_DBG_MSG4(a,b,c,d)
#define VOL_DBG_MSG5(a,b,c,d,e)
#define VOL_DBG_MSG6(a,b,c,d,e,f)

#endif /* OEM_DEBUG */

#endif	/* _KERNEL */

#endif 	/* _SYS_VOLLOCAL_H */
