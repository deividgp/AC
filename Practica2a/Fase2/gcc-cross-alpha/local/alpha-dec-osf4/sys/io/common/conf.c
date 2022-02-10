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
 * @(#)$RCSfile: conf.c,v $ $Revision: 1.2.268.7 $ (DEC) $Date: 1998/08/27 20:40:02 $
 */

/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/* 
 * derived from conf.c	2.1 16:11:28 4/20/90 SecureWare 
 */
/*
 * Modification History:
 *
 *  04-Nov-91	Tom Tierney
 *	Modified LVM strategy return type to be int like all others (one
 *	day all driver entrypoints that return no value will be "void").
 * 
 *  3-Nov-91	Fred Canter
 *	Fixed configuration of memory driver (NMD -> NMEMD).
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)conf.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/presto.h>
#include <sys/sysconfig.h>
#include <sys/errno.h>
#include <kern/lockdev.h>
/*
 * pick up appropriate headers so that we know which subsystems are being
 * statically linked
 */
#include "bba.h"
#include "dlb.h"
#include "dlpi.h"
#include "lat.h"
#include "ldtty.h"
#include "pckt.h"
#include "rpty.h"
#include "streams.h"
#include "strifnet.h"
#include "strkinfo.h"
#include "svvs.h"
#include "timod.h"
#include "tirdwr.h"
#include "xtiso.h"

#include <io/dec/uba/ubavar.h>
#include <io/common/devdriver.h>
#include <io/dec/scs/sca.h>
#if defined(SVR4_COMPAT)
#	include <dec/svr4_defines.h>
#endif


int	nulldev();
int	nodev();


/*
 * /etc/config notes: etc/config will produce a .h for each controller
 * in the system named "(two char controller name).h".  Each of these
 * .h's will contain two defines, "(two char controller name)C" which
 * indicates the number of controllers of this type, and
 * "(two char controller name)S" which indicates the number of slaves
 * possibly attached to this set of controllers.
 */

/*
 * #################### TAKE NOTE ######################
 *
 * The following set of declarations & definitions are for
 * MIPSCO MSERIES systems.  They have been commented out
 * in an effort to clean up the (DEC) switch table.
 *
 */
#ifdef	notdef
/*
 * Sample tape entry
 * Integrated Solutions 1/4" Streaming Tape
 */
#include <ts.h>
#if NTS > 0
int	tsopen(),tsclose(),tsstrategy(),tsread(),tswrite();
int	tsioctl(),tsdump(),tsreset();
#else
#define	tsopen		nodev
#define	tsclose		nodev
#define	tsstrategy	nodev
#define	tsread		nodev
#define	tswrite		nodev
#define	tsioctl		nodev
#define	tsdump		nodev
#define	tsreset		nodev
#endif	/* NTS */

/*
 * Ciprico Tapemaster 3000 9-track tape driver.
 */

#include <tthu.h>
#if NTTHU > 0
int	tthopen(),tthclose(),tthstrategy(),tthread(),tthwrite();
int	tthioctl();
#else
#define	tthopen		nodev
#define	tthclose	nodev
#define	tthstrategy	nodev
#define	tthread		nodev
#define	tthwrite	nodev
#define	tthioctl	nodev
#define tthsize		0
#endif	/* NTTHU */

/*
 * ram-disk
 */
#include <rd.h>
#if NRD > 0
int	rdopen(),rdstrategy(),rdread(),rdwrite(),rddump(),rdioctl(),rdsize();
#else
#define	rdopen		nodev
#define	rdstrategy	nodev
#define	rdread		nodev
#define	rdwrite		nodev
#define	rddump		nodev
#define	rdioctl		nodev
#define	rdsize		0
#endif	/* NRD */

/*
 * Interphase SMD/3200 disk controller
 */
#include <dkip.h>
#if NDKIP > 0
int	dkipopen(),dkipstrategy(),dkipread(),dkipwrite(),dkipdump();
int	dkipioctl(),dkipsize();
#else
#define dkipopen	nodev
#define dkipstrategy	nodev
#define dkipread	nodev
#define dkipwrite	nodev
#define dkipdump	nodev
#define dkipioctl	nodev
#define dkipsize	0
#endif	/* NDKIP */

/*
 * Integrated Solutions Intelligent Communications Processor
 */
#include <cp.h>
#if NCP == 0
#define cpopen	nodev
#define cpclose nodev
#define cpread	nodev
#define cpwrite nodev
#define cpioctl nodev
#define cpstop	nodev
#define cpreset nulldev
#define cp_tty	0
#else
int	cpopen(),cpclose(),cpread(),cpwrite(),cpioctl(),cpstop(),cpreset();
extern struct	tty cp_tty[];
#endif	/* NCP */
#endif	/* notdef */



/*
 * Definitions for bdevsw
 */

/* SAS/RAM disk device */			/* Pmax devices */
#include <memd.h>
#if NMEMD > 0
int	mdopen(), mdstrategy(), md_size(), mdioctl();
#else
#define mdopen		nodev
#define mdstrategy	nodev
#define md_size 	nodev
#define mdioctl 	nodev
#endif

#include <asc.h>
#include <tcds.h>
#include <tza.h>
#include <scsi.h>

#ifdef __alpha
#include <siop.h>
#include <aha.h>
#else
#define NSIOP	0
#define NAHA	0
#endif

#ifdef __mips__
#include "vba.h"
#if	NVBA == 0
xviaconf() {}	/* make tc_option_data.c happy */
#endif
#endif /* __mips__ */

/* LAT driver */
#if LAT > 0
dev_t lat_cdev = makedev(5,0);
#endif

/* VxVM vol driver pseudo-device */
#include <lsm.h>

/*
 * NLSM=0 means it is off. define bogus volinit() to
 * resolve machdep.o symbols.
 */
#if NLSM == 0
int	volinit() {}
long maxvol;
int vol_rootdev_is_volume;
#endif /* NLSM == 0 */

#if NLSM > 0
int     volopen(), volclose();
int     PRvolstrategy();
int     volread(), volwrite();
int	volioctl(), voldump();
int     volsize();
int	tedopen(), tedclose();
int	tedioctl();

/* VxVM volspec driver pseudo-device */
int     volsopen_real(), volsclose_real();
int     volsioctl_real();

/* VxVM plex pseudo-device */
int     plexopen_real(), plexclose_real();
int     plexread_real(), plexioctl_real(), plexwrite_real();

#else /* LSM not configured */

#define volopen           nodev
#define volclose          nodev
#define PRvolstrategy     nodev
#define volread           nodev
#define volwrite          nodev
#define volioctl          nodev
#define voldump           nodev
#define volsize		  0

#define	tedopen		 nodev
#define	tedclose	 nodev
#define	tedioctl	 nodev

#define volsopen_real	 nodev
#define volsclose_real	 nodev
#define volsioctl_real	 nodev

#define plexopen_real	 nodev
#define plexclose_real	 nodev
#define plexread_real	 nodev
#define plexioctl_real	 nodev
#define plexwrite_real	 nodev

#endif /* NLSM > 0 */

/* Logical Volume Manager pseudo-device */
#include <lv.h>
#include <presto.h>
int lv_nlv = NLV;
#if	NLV > 0
#include <lvm/lvmd.h>
int	lv_open(), lv_close();
int	lv_strategy();
int	lv_read(), lv_ioctl(), lv_write();
struct volgrp lv_volgrp[NLV];
#else
int	lvprobe(){}
#endif

#if	NLV > 0
#if	NPRESTO > 0
/* declare Prestoserve NVRAM psuedo-driver interface routines and structs */
int lv_open0(), lv_close0();
int lv_strategy0();
int lv_read0(), lv_write0();
#define lv_ioctl0	lv_ioctl
#define	lv_volgrp0	((struct tty *)&lv_volgrp[0])
#else
#define	lv_open0	lv_open
#define	lv_close0	lv_close
#define	lv_strategy0	(int (*)())lv_strategy
#define	lv_read0	lv_read
#define	lv_write0	lv_write
#define	lv_ioctl0	lv_ioctl
#define	lv_volgrp0	((struct tty *)&lv_volgrp[0])
#endif	/* NPRESTO > 0 */

#else
#define	lv_open0	nodev
#define	lv_close0	nodev
#define	lv_strategy0	nodev
#define	lv_read0	nodev
#define	lv_write0	nodev
#define	lv_ioctl0	nodev
#define lv_volgrp0	0
#endif	/* NLV > 0 */

#if	NLV > 1
#if	NPRESTO > 0
/* declare Prestoserve NVRAM psuedo-driver interface routines and structs */
int lv_open1(), lv_close1();
int lv_strategy1();
int lv_read1(), lv_write1();
#define lv_ioctl1	lv_ioctl
#define	lv_volgrp1	((struct tty *)&lv_volgrp[1])
#else
#define	lv_open1	lv_open
#define	lv_close1	lv_close
#define	lv_strategy1	(int (*)())lv_strategy
#define	lv_read1	lv_read
#define	lv_write1	lv_write
#define	lv_ioctl1	lv_ioctl
#define	lv_volgrp1	((struct tty *)&lv_volgrp[1])
#endif	/* NPRESTO > 0 */

#else
#define	lv_open1	nodev
#define	lv_close1	nodev
#define	lv_strategy1	nodev
#define	lv_read1	nodev
#define	lv_write1	nodev
#define	lv_ioctl1	nodev
#define lv_volgrp1	0
#endif	/* NLV > 1 */

#if	NLV > 2
#if	NPRESTO > 0
/* declare Prestoserve NVRAM psuedo-driver interface routines and structs */
int lv_open2(), lv_close2();
int lv_strategy2();
int lv_read2(), lv_write2();
#define lv_ioctl2	lv_ioctl
#define	lv_volgrp2	((struct tty *)&lv_volgrp[2])
#else
#define	lv_open2	lv_open
#define	lv_close2	lv_close
#define	lv_strategy2	(int (*)())lv_strategy
#define	lv_read2	lv_read
#define	lv_write2	lv_write
#define	lv_ioctl2	lv_ioctl
#define	lv_volgrp2	((struct tty *)&lv_volgrp[2])
#endif	/* NPRESTO > 0 */

#else
#define	lv_open2	nodev
#define	lv_close2	nodev
#define	lv_strategy2	nodev
#define	lv_read2	nodev
#define	lv_write2	nodev
#define	lv_ioctl2	nodev
#define lv_volgrp2	0
#endif	/* NLV > 2 */

#if	NLV > 3
error Need to add more declarations to conf.c to configure this many LVMs.
#endif


#include <tc.h>
#if NTC == 0
struct	tc_slot		*tc_slot;
struct	tc_slotaddr	*tc_slotaddr;
struct	tc_sw		*tc_sw;
u_int			*tc_romoffset;
tc_init()	{}
tc_where_option()	{}
tc_disable_option()	{}
tc_enable_option()	{}
tc_isolate_memerr()	{}
tc_addr_to_name()	{}
tc_option_control()	{}
tc_get_unit_num()	{}
tc_slot_to_name()	{}
tc_slot_to_ctlr_name()	{}
tc_slot_to_addr()	{}
tc_func_used()		{}
#endif /* NTC TURBO Channel routines */

#include <eisa.h>
#if NEISA == 0
char * eisa_slot_to_name()	{}
char * eisa_slot_to_ctlr_name() {}
int     eisa_get_unit_num()     {}
int	eisa_get_config()	{}
#endif

#include <isa.h>
#if NISA == 0
char * isa_slot_to_name()	{return((char *)-1);}
char * isa_slot_to_driver()	{return((char *)-1);}
int isacfg_find_isa_slot()	{return(-1);}
int isa_slot_to_console()	{return(-1);}
#endif

#include <pcmcia.h>
#if NPCMCIA == 0
int pcmcia_config_cont()	{return(1);}
#endif

#if NASC == 0 && NTCDS == 0
ascprobe() {}
ascintr() {}
#endif

#if NSCSI > 0

int     cdisk_open(), cdisk_close(), cdisk_strategy(), cdisk_read();
int	cdisk_write(), cdisk_dump(), cdisk_ioctl(), cdisk_size();
int     ctape_open(), ctape_close(), ctape_strategy(); 
int	ctape_read(), ctape_write(), ctape_ioctl(), ctape_size();

#if	NSCSI > 0
int	uagtopen(), uagtclose(), uagtioctl();
#else
#define uagtopen	nodev
#define uagtclose	nodev
#define uagtioctl	nodev
#endif
#if	NSCSI == 0
void scsiisr_init() {}
#endif

#if	NPRESTO > 0
/* declare presto NVRAM pseudo-driver interface routines and structs */
int   	RZbopen(), RZbclose(), RZstrategy();
int   	RZread(), RZwrite();
#else
	/* assume that nobody in their right mind is gonna use Presto
	 * with the SAS kernel
	 */
#if NSCSI == 0
#define	cdisk_open	nodev
#define	cdisk_close 	nodev
#define	cdisk_strategy	nodev
#define	cdisk_read	nodev
#define	cdisk_write	nodev
#define cdisk_dump	nodev
#define	cdisk_ioctl	nodev
#define	cdisk_size	0
#define	ctape_open	nodev
#define	ctape_close	nodev
#define	ctape_strategy	nodev
#define	ctape_read	nodev
#define	ctape_write	nodev
#define	ctape_ioctl	nodev
#define	ctape_size	0
#endif

#define	RZbopen		cdisk_open
#define	RZbclose	cdisk_close
#define	RZstrategy	cdisk_strategy
#define	RZread		cdisk_read
#define	RZwrite		cdisk_write

#endif /* NPRESTO > 0 */

#else

#define	cdisk_open	nodev
#define	cdisk_close 	nodev
#define	cdisk_strategy	nodev
#define	cdisk_read	nodev
#define	cdisk_write	nodev
#define cdisk_dump	nodev
#define	cdisk_ioctl	nodev
#define	cdisk_size	0
#define	ctape_open	nodev
#define	ctape_close	nodev
#define	ctape_strategy	nodev
#define	ctape_read	nodev
#define	ctape_write	nodev
#define	ctape_ioctl	nodev
#define	ctape_size	0
#define uagtopen	nodev
#define uagtclose	nodev
#define uagtioctl	nodev
/* declare other CAM related stubs */
void scsiisr_init() {}
char *szinfo() { return( (char*) NULL ); }
/* declare stubs for presto interface routines */
#define	RZbopen		nodev
#define	RZbclose	nodev
#define	RZstrategy	nodev
#define	RZread		nodev
#define	RZwrite		nodev
#endif	/* NSCSI > 0 */

#include <fdi.h>

#if NFDI == 0
# define fd_bopen        nodev
# define fd_bclose       nodev
# define fd_bread        nodev
# define fd_bwrite       nodev
# define fd_open         nodev
# define fd_close        nodev
# define fd_read         nodev
# define fd_write        nodev
# define fd_ioctl        nodev
# define fd_psize        0
# define fd_bstrategy    nodev
/* declare other FDI related stubs */
char *fdinfo() { return( (char*) NULL ); }
#else
int fd_bopen(),fd_bclose(),fd_bread(),fd_bwrite(),fd_ioctl(),fd_psize();
int fd_open(),fd_close(),fd_read(),fd_write();
int fd_bstrategy();
#endif

extern int sysdev_open(), sysdev_close(), sysdev_mmap();

/* 
 *	DSA IO conf setups 
 */
#include "uba.h"
/*
#include "kdb.h"
#include "klesib.h"
#include "kdm.h"
#include "msi.h"
 */
#include "ci.h"
#include "uq.h"
#include "mscp.h"
#include "hsc.h"
#include "dssc.h"
/*
#include "msdup.h"
 */

#if NUBA == 0 && NUQ == 0
struct uba_hd uba_hd[1];
ubaerror () {}
ubainitmaps () {}
uballoc () {}
ubarelse () {}
ubareset () {}
#endif

#if NUQ > 0
extern struct driver uqdriver;
int uq_reset();
#else
#define uq_reset        nulldev
int nNUQ = 0;
#endif

#include <kdebug.h>
#if KDEBUG > 0
extern long kdebug_entry();
long (*kdebug_handler)() = kdebug_entry;
#else
long (*kdebug_handler)() = NULL;
int ddb_init() { return 0; }
void db_cnopen() { return; }
int kdb_trap() { return 0; }
#endif
boolean_t db_active = 0;
boolean_t db_enable = KDEBUG;
boolean_t db_stop_on_panic = 0;
 
#if NHSC == 0
hscdriver() {}
#endif

#if NDSSC == 0
dsscdriver() {}
#endif

#if NCI == 0
CIISR ci_isr;
void tcciconf() {};
int (*ciint0[])() = { 0 };
int nNCI = 0;
u_short ci_first_port = 0;
#endif

#if NCI == 0 &&  NUQ == 0
void dsaisr_init() { /* make init_main.c happy */ }
scs_start_sysaps () { /* make startup.c happy */ }
mscp_poll_wait () { /* make startup.c happy */ }
mscp_info() { return(0); /* cmu_syscalls.c happy */ }
int do_mscp_poll_wait; /* make init_main.c happy */
int dsa_physical_bg = 0; /* make mips_init.c happy */
int dsa_physical_end = 0; /* make mips_init.c happy */
#endif
 
#if NCI > 0 || NUQ > 0
int     mscp_bopen(), mscp_copen(), mscp_bclose();
int     mscp_cclose(), mscp_strategy(), mscp_read();
int     mscp_write(), mscp_dump(), mscp_ioctl(), mscp_size();

#if  NPRESTO > 0 
/* declare presto NVRAM pseudo-driver interface routines and structs */
int     MSCP_bopen(), MSCP_bclose(), MSCP_strategy();
int     MSCP_read(), MSCP_write();
#else
#define MSCP_bopen      mscp_bopen
#define MSCP_bclose     mscp_bclose
#define MSCP_strategy   mscp_strategy
#define MSCP_read       mscp_read
#define MSCP_write      mscp_write
#endif /* NPRESTO > 0 */
#else
#define mscp_bopen      nodev
#define mscp_copen      nodev
#define mscp_bclose     nodev
#define mscp_cclose     nodev
#define mscp_strategy   nodev
#define mscp_read       nodev
#define mscp_write      nodev
#define mscp_ioctl      nodev
#define mscp_size       0
#define mscp_dump	nodev
/* declare stubs for presto interface routines and structs */
#define MSCP_bopen      nodev
#define MSCP_bclose     nodev
#define MSCP_strategy   nodev
#define MSCP_read       nodev
#define MSCP_write      nodev
#endif /* NCI > 0 || NUQ > 0 */

#if NCI > 0 || NUQ > 0
int     tmscpopen(), tmscpclose(), tmscpstrategy(), tmscpread(),
        tmscpwrite(), tmscpioctl(), tmscpsize();
#else
#define tmscpopen       nodev
#define tmscpclose      nodev
#define tmscpstrategy   nodev
#define tmscpread       nodev
#define tmscpwrite      nodev
#define tmscpioctl      nodev
#define tmscpdump       nodev
#endif 

#if NMSCP == 0
int nulldev();
struct driver mscpdriver; int (*mscpint0[])() = { nulldev, 0 };  /* no mscpdriver */
#endif /* NMSCP */

#include "xcr.h"

#if NXCR > 0 

int     re_open(), re_close(), re_strategy(), re_read();
int	re_write(), re_dump(), re_ioctl(), re_size();

#if NPRESTO > 0

/* declare presto NVRAM pseudo-driver interface routines and structs */
int   	REbopen(), REbclose(), REstrategy();
int   	REread(), REwrite();

#else

#define	REbopen		re_open
#define	REbclose	re_close
#define	REstrategy	re_strategy
#define	REread		re_read
#define	REwrite		re_write

#endif /* NPRESTO > 0 */

#else

#define	re_open		nodev
#define	re_close 	nodev
#define	re_strategy	nodev
#define	re_read		nodev
#define	re_write	nodev
#define re_dump		nodev
#define	re_ioctl	nodev
#define	re_size	0

/* declare other XCR related stubs */
char *re_info() { return( (char*) NULL ); }

/* declare stubs for presto interface routines */
#define	REbopen		nodev
#define	REbclose	nodev
#define	REstrategy	nodev
#define	REread		nodev
#define	REwrite		nodev
#endif	/* NXCR > 0 */

/* declare snmpinfo interface routines */
#include "snmpinfo.h"
#if SNMPINFO > 0
int snmpopen(), snmpclose(), snmpioctl();
#else
#define	snmpopen	nodev
#define	snmpclose	nodev
#define	snmpioctl	nodev
#endif

#include "lta.h"
#if NLTA == 0
void otto_fakesnmp_rcv() {}
#endif


/*
 * NOTE: this must match conf/devices
 */

/*
 *      Block Device Switch static declaration and initialization
 */

/*
 * The user may specify a different b/cdevsw size in the config file.
 * MAX_BDEVSW will have a default and a minimum that matches the cdevsw
 * value.  This is done by hardcoding the same values used below for the
 * cdevsw table.
 */
#ifdef	MAX_BDEVSW
#if	MAX_BDEVSW < 90
#define	MAX_BDEVSW	90
#endif	/* MAX_BDEVSW < 90 */
#else	/* MAX_BDEVSW needs defining */
#define	MAX_BDEVSW	140
#endif	/* MAX_BDEVSW */

dswlock_t       bdevlock[MAX_BDEVSW];           /* bdevsw lock structure */
struct lockinfo	*bdev_lockinfo;

/*
%%% BEGIN BDEVSW TABLE (first 3 chars of this line must be %%%
*/
struct bdevsw   bdevsw[MAX_BDEVSW] =
{
	{ nodev,	nodev,		nodev,		nodev,		/*0*/
	  nodev,	0,		nodev,		DEV_FUNNEL },
	/* SAS/RAM disk device */
	{ mdopen,	nulldev,	mdstrategy,	nodev,		/*1*/
	  md_size,	0,		nodev		,DEV_FUNNEL },
	/* swap, defunct */
	{ nodev,	nodev,		nodev,		nodev,		/*2*/
	  0,		0,		nodev		,DEV_FUNNEL },
	/* sable, defunct */
	{ nodev,	nodev,		nodev,		nodev,		/*3*/
	  nodev,	0,		nodev		,DEV_FUNNEL },

	/* Unused entry (4) */
	{ nodev,	nodev,		nodev,		nodev,		/*4*/
	  nodev,	0,		nodev,		DEV_FUNNEL },

	/* Unused entry (5) */
	{ nodev,	nodev,		nodev,		nodev,		/*5*/
	  nodev,	0,		nodev,		DEV_FUNNEL },

	/* Unused entry (6) */
	{ nodev,	nodev,		nodev,		nodev,		/*6*/
	  0,		0,		nodev		,DEV_FUNNEL },

	/* Unused entry (7) */
	{ nodev,	nodev,		nodev,		nodev,		/*7*/
	  0,		0,		nodev		,DEV_FUNNEL },

	/* DEC SCSI disk devices */
	/*
	 * Insert presto NVRAM pseudo-driver interface routines (RZ...).
	 * Warning: If these device major numbers change, then
	 *          data/presto_data.c must be modified.
	 */
	{ RZbopen,      RZbclose,       RZstrategy,     cdisk_dump,     /*8*/
	  cdisk_size,	0,		cdisk_ioctl	,DEV_FUNNEL_NULL },

	/* DEC SCSI tape devices (old major number) */
	{ ctape_open,	ctape_close,	ctape_strategy,	nodev,		/*9*/
	  0,		B_TAPE,		nodev		,DEV_FUNNEL_NULL },

	/* Unused entry (10) */
	{ nodev,	nodev,		nodev,		nodev,		/*10*/
	  0,		0,		nodev		,DEV_FUNNEL },

	/* RE/XCR entry (11) */
	{ REbopen,	REbclose,	REstrategy,	re_dump,	/*11*/
	  re_size,	0,		re_ioctl	,DEV_FUNNEL_NULL },

	/* Unused entry (12) */
	{ nodev,	nodev,		nodev,		nodev,		/*12*/
	  0,		0,		nodev		,DEV_FUNNEL },

	/* Unused entry (13) */
	{ nodev,	nodev,		nodev,		nodev,		/*13*/
	  0,		0,		nodev		,DEV_FUNNEL },

        /* Floppy Disk Controller */
        { fd_bopen,     fd_bclose,      fd_bstrategy,   nodev,          /*14*/
          fd_psize,     0,              fd_ioctl        ,DEV_FUNNEL },

	/* DSA tmscp tape devices */
	{ tmscpopen,	tmscpclose,	tmscpstrategy,	nodev,		/*15*/
	  0,		B_TAPE,		nodev,		DEV_FUNNEL },

	/* Logical Volume Manager - cmajor and bmajor must match */
	{ lv_open0,	lv_close0,	lv_strategy0,	nodev,		/*16*/
	  0,		0,		lv_ioctl0	,DEV_FUNNEL },

	/* Unused entry (17) */
	{ nodev,	nodev,		nodev,		nodev,		/*17*/
	  0,		0,		nodev		,DEV_FUNNEL },

	/* Unused entry (18) */
	{ nodev,	nodev,		nodev,		nodev,		/*18*/
	  0,		0,		nodev		,DEV_FUNNEL },

	/* Logical Volume Manager - cmajor and bmajor must match */
	{ lv_open1,	lv_close1,	lv_strategy1,	nodev,		/*19*/
	  0,		0,		lv_ioctl1	,DEV_FUNNEL },

	/* Logical Volume Manager - cmajor and bmajor must match */
	{ lv_open2,	lv_close2,	lv_strategy2,	nodev,		/*20*/
	  0,		0,		lv_ioctl2	,DEV_FUNNEL },

	/* Unused entry (21) */
	{ nodev,	nodev,		nodev,		nodev,		/*21*/
	  0,		0,		nodev		,DEV_FUNNEL },
 
	/* Unused entry (22) */
	{ nodev,	nodev,		nodev,		nodev,		/*22*/
	  0,		0,		nodev		,DEV_FUNNEL },
 
        /* DSA mscp disk devices */
        /*
         * Insert presto NVRAM pseudo-driver interface routines (MSCP_...).
         * Warning: If these device major numbers changes, then
         *          data/presto_data.c must be modified.
         */
        { MSCP_bopen,   MSCP_bclose,    MSCP_strategy,  mscp_dump,	/*23*/
	  mscp_size,	0,		mscp_ioctl,	DEV_FUNNEL },

        /* Unused entry (24) */
        { nodev,        nodev,          nodev,          nodev,          /*24*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (25) */
        { nodev,        nodev,          nodev,          nodev,          /*25*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (26) */
        { nodev,        nodev,          nodev,          nodev,          /*26*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (27) */
        { nodev,        nodev,          nodev,          nodev,          /*27*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (28) */
        { nodev,        nodev,          nodev,          nodev,          /*28*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (29) */
        { nodev,        nodev,          nodev,          nodev,          /*29*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (30) */
        { nodev,        nodev,          nodev,          nodev,          /*30*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (31) */
        { nodev,        nodev,          nodev,          nodev,          /*31*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (32) */
        { nodev,        nodev,          nodev,          nodev,          /*32*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (33) */
        { nodev,        nodev,          nodev,          nodev,          /*33*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (34) */
        { nodev,        nodev,          nodev,          nodev,          /*34*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (35) */
        { nodev,        nodev,          nodev,          nodev,          /*35*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (36) */
        { nodev,        nodev,          nodev,          nodev,          /*36*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (37) */
        { nodev,        nodev,          nodev,          nodev,          /*37*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (38) */
        { nodev,        nodev,          nodev,          nodev,          /*38*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (39) */
        { nodev,        nodev,          nodev,          nodev,          /*39*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        { volopen,   	volclose,    	PRvolstrategy, 	voldump,     	/*40*/
          volsize,      B_DDIDKI,       volioctl        ,DEV_FUNNEL_NULL },

        /* Unused entry (41) */
        { nodev,        nodev,          nodev,          nodev,          /*41*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (42) */
        { nodev,        nodev,          nodev,          nodev,          /*42*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (43) */
        { nodev,        nodev,          nodev,          nodev,          /*43*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (44) */
        { nodev,        nodev,          nodev,          nodev,          /*44*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (45) */
        { nodev,        nodev,          nodev,          nodev,          /*45*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (46) */
        { nodev,        nodev,          nodev,          nodev,          /*46*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (47) */
        { nodev,        nodev,          nodev,          nodev,          /*47*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

	/* DEC SCSI disk devices */
	/*
	 * Insert presto NVRAM pseudo-driver interface routines (RZ...).
	 * Warning: If these device major numbers change, then
	 *          data/presto_data.c must be modified.
	 */
	{ RZbopen,      RZbclose,       RZstrategy,     cdisk_dump,     /*48*/
	  cdisk_size,	0,		cdisk_ioctl	,DEV_FUNNEL_NULL },

        /* Unused entry (49) */
        { nodev,        nodev,          nodev,          nodev,          /*49*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

        /* Unused entry (50) */
        { nodev,        nodev,          nodev,          nodev,          /*50*/
          nodev,        0,              nodev,          DEV_FUNNEL_NULL },

	/* DEC SCSI tape devices (new major number) */
	{ ctape_open,	ctape_close,	ctape_strategy,	nodev,		/*51*/
	  0,		B_TAPE,		nodev		,DEV_FUNNEL_NULL },

};
/*
%%% END BDEVSW TABLE (first 3 chars of this line must be %%%
*/
int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

/*
 * Definitions for cdevsw
 */

int	cnopen(),cnclose(),cnread(),cnwrite(),cnioctl(),cnselect(),cnmmap();

int	ncons;
#define	cnntty	(&ncons)

int	syopen(),syread(),sywrite(),syioctl(),syselect();

int 	mmread(),mmwrite(),mmmap();

#include <sas.h>

#if 	SAS > 0
/* don't include /dev/zero if SAS kernel */
#define dzopen		nodev
#define	dzclose		nodev
#define dzread		nodev
#define dzwrite		nodev
#define	dzmmap		nodev
#define dzsegmap	NULL

/* use syscall stubs for SAS kernel */
swapctl()	{return(ENOSYS);}
memcntl()	{return(ENOSYS);}
#else
int     dzopen(),dzclose(),dzsegmap(),dzmmap(),dzread(),dzwrite();
#endif /*SAS > 0*/

#include <pty.h>
#if	NPTY > 0
int	ptsopen(),ptsclose(),ptsread(),ptswrite(),ptsstop();
int	ptcopen(),ptcclose(),ptcread(),ptcwrite(),ptcselect();
int	ptsselect(), ptyioctl();

int	npty;
#define	ptsntty	(&npty)

#else
#define ptsopen		nodev
#define ptsclose	nodev
#define ptsread		nodev
#define ptswrite	nodev
#define ptcopen		nodev
#define ptcclose	nodev
#define ptcread		nodev
#define ptcwrite	nodev
#define	ptsselect	nodev
#define ptyioctl	nodev
#define	ptcselect	nodev
#define	ptsstop		nulldev
#define	ptsntty		0
pty_initialization() { }
#endif	/* NPTY > 0 */

#if     RPTY
dev_t pts_cdev = makedev(6,0);
int ptropen(), ptrclose(), ptrread(), ptrwrite(), ptrioctl(), ptrselect();
#else
#define ptropen		nodev
#define ptrclose	nodev
#define ptrread		nodev
#define ptrwrite	nodev
#define	ptrselect	nodev
#define ptrioctl	nodev
#endif /* RPTY > 0 */
dev_t consdev = makedev(0,0);

/* binary event logger */
int    binlog_open(),binlog_close(),binlog_read(),binlog_write();
int    binlog_ioctl(), binlog_select();

/*  syslog  */
int	logopen(),logclose(),logread(),logioctl(),logselect();

int	ttselect(), seltrue(), asyncsel();


#ifdef __mips__
#include <dc.h>
#else
#define NDC 0
#endif

#if NDC == 0
#define dcopen 	nodev
#define dcclose	nodev
#define dcread 	nodev
#define dcwrite	nodev
#define dcioctl	nodev
#define dcstop 	nodev
#define dcselect nodev
#define dc_tty	0
struct tty cons[2];
#else /* NDC */
int	dcopen(),dcclose(),dcread(),dcwrite(),dcioctl(),dcstop(), dcselect();
extern struct	tty dc_tty[];
extern struct tty cons[];
#endif /* NDC */

#ifdef __mips__
#include <dhu.h>
#else
#define NDHU 0
#endif

#if NDHU == 0
#define dhuopen nodev
#define dhuclose nodev
#define dhuread nodev
#define dhuwrite        nodev
#define dhuioctl        nodev
#define dhustop         nodev
#define dhu11   0
#else /* NDHU */
int     dhuopen(),dhuclose(),dhuread(),dhuwrite(),dhuioctl(),dhustop();
extern struct   tty dhu11[];
#endif /* NDHU */

#include <scc.h>

#if NSCC == 0
#define sccopen         nodev
#define sccclose        nodev
#define sccread         nodev
#define sccwrite        nodev
#define sccioctl        nodev
#define sccstop         nodev
#define sccselect       nodev
#define sccmmap		nodev
#define scc_tty 0
#else
int     sccopen(),sccclose(),sccread(),sccwrite(),sccioctl(),sccstop(),
sccselect(), sccmmap();
extern struct   tty scc_tty[];
#endif

#include <ace.h>
#if NACE == 0
#define aceopen         nodev
#define aceclose        nodev
#define aceread         nodev
#define acewrite        nodev
#define aceioctl        nodev
#define acestop         nodev
#define aceselect       nodev
#define ace_tty 0
u_long	aceintr_addr;
io_handle_t ace_regbase;
#else
int     aceopen(),aceclose(),aceread(),acewrite(),aceioctl(),acestop(),
aceselect();
extern struct   tty ace_tty[];
extern 	int aceintr();
u_long	aceintr_addr = (u_long)&aceintr;
io_handle_t ace_regbase = 0;
#endif

#include <iscc.h>
#if NISCC == 0
#define iscc_open       nodev
#define iscc_close      nodev
#define iscc_read       nodev
#define iscc_write      nodev
#define iscc_ioctl      nodev
#define iscc_stop       nodev
#define iscc_select     nodev
#define iscc_mmap	nodev
#define iscc_tty 0
#else
int     iscc_open(),iscc_close(),iscc_read(),iscc_write(),iscc_ioctl(),iscc_stop(),
iscc_select(),iscc_mmap();
extern struct tty iscc_tty[];
#endif

#include <dec_audit.h>
#if	DEC_AUDIT > 0
int	auditopen(), auditclose(), auditread();
int	auditioctl(), auditsel(), auditmmap();
#else
#define auditopen	nodev
#define auditclose	nodev
#define auditread	nodev
#define auditioctl	nodev
#define auditsel	nodev
#define auditmmap	nodev
#endif

#include <spd.h>
#if	NSPD > 0
int	spdopen(),spdclose(),spdread(),spdwrite(),spdioctl();
#else
#define spdopen		nodev
#define spdclose	nodev
#define spdread		nodev
#define spdwrite	nodev
#define spdioctl	nodev
#endif

/*
 * Define presto NVRAM pseudo-driver device control routines
 */
/* Defined for LVM -- change if the presto cdevsw position changes */
int     pr_maj_devnum = 22;
#if	NPRESTO > 0
int	propen(), prioctl();
#else
#define propen		nodev
#define prioctl		nodev
int presto_init() { /* dummy */ }
int presto_reboot() { /* dummy */ }
int prbounceio()  { /* dummy */ }
int prunbounceio()  { /* dummy */ }
int prdirectio()  { /* dummy */ }
int prenabled()  { /* dummy */ }
int presto_bprtab_add()  { /* dummy */ }
int presto_bprtab_del()  { /* dummy */ }
int presto_cprtab_add()  { /* dummy */ }
int presto_cprtab_del()  { /* dummy */ }
int PRclose_ddi()  	 { /* dummy */ }
int PRread_ddi()  	 { /* dummy */ }
int PRwrite_ddi()  	 { /* dummy */ }
int PRstrategy()  	 { /* dummy */ }
void presto_smp_init() { /* dummy */ }
struct presto_interface presto_interface0; /* dummy */
struct nvram_battery_info nvram_batteries0; /* dummy */
int prattached = 0; /* dummy */
int prsize = 0; /* dummy */
struct lockinfo *presto_lockinfo; /* dummy */
#endif /* NPRESTO > 0 */

#include <lp.h>
#if NLP > 0
int lpopen(),lpclose(),lpwrite();
#else
#define lpopen		nodev
#define lpclose		nodev
#define lpwrite		nodev
#endif

#include "streams.h"
#if	STREAMS != 0 || TIMOD || SVVS || STRKINFO || STRIFNET || XTISO || DLB || DLPI || LDTTY || RPTY || PCKT || LAT || TIRDWR || NBBA || PPP
int streams_loaded = 1;
#else
int streams_sigexit(){/* dummy */ }
int ext_freeb(){/* dummy */ }
int pse_init(){/* dummy */ }
int streams_loaded = 0;
#endif /* STREAMS != 0 ......... */
extern int	clone_open();
dev_t clonedev = makedev(32,0);

#include <ws.h>
#if NWS > 0
int	wsopen(),wsclose(),wsstop(),wsselect(),wsioctl();
#else
#define wsopen		nodev
#define wsclose		nodev
#define wsstop		nodev
#define	wsselect	nodev
#define wsioctl		nodev
void pcxa_init_sw(void){}
#endif

#ifdef	__alpha
/*
 * Alpha performance monitor
 */
#include <pfm.h>
#if NPFM > 0
int	pfmopen(),pfmclose(),pfmread(),pfmioctl();
#else
#define pfmopen		nodev
#define pfmclose	nodev
#define pfmread		nodev
#define pfmioctl	nodev
#endif
#else
#define pfmopen		nodev
#define pfmclose	nodev
#define pfmread		nodev
#define pfmioctl	nodev
#endif /* __alpha */

#include "packetfilter.h"
#if PACKETFILTER > 0
int     Pfilt_open(), Pfilt_close(), Pfilt_read(), Pfilt_write(), Pfilt_ioctl(),
Pfilt_select();
#else
#define Pfilt_open nodev
#define Pfilt_close nodev
#define Pfilt_read nodev
#define Pfilt_write nodev
#define Pfilt_ioctl nodev
#define Pfilt_select nodev
/* define stubs for kernels without packetfilter */
int pfactive=0;
struct mbuf *pfilt_filter(ifp, m, ehp, a, b, c)
	struct ifnet *ifp;
	struct mbuf *m;
	struct ether_header *ehp;
	int a, b, c;
{ return((struct mbuf *)m); }
pfilt_attach() { return(0); };
pfilt_newaddress() { return(0); };
pf_mcopym() { return(NULL); };
#endif /* PACKETFILTER */

#include <prf.h>
#if NPRF > 0
/* Kernel Profiling */
#define prfopen		nulldev
int	prfread(), prfwrite(), prfioctl();
#else
#define prfopen		nodev
#define prfread		nodev
#define prfwrite	nodev
#define prfioctl	nodev
#endif /* NPRF */

#include <mlog.h>
#if NMLOG > 0
/* Memory allocation/free logger */
int	mlogopen(), mlogclose(), mlogread(), mlogioctl();
#else
#define mlogopen	nodev
#define mlogclose	nodev
#define mlogread	nodev
#define mlogioctl	nodev
#endif /* NMLOG */

#include <atm.h>
#if ATM > 0
extern atm_cmm_ioctl();
extern atm_cmm_open();
extern atm_cmm_close();
#define Atm_Cmm_Open	atm_cmm_open
#define Atm_Cmm_Close	atm_cmm_close
#define Atm_Cmm_Ioctl 	atm_cmm_ioctl
#else
#define Atm_Cmm_Open	nodev
#define Atm_Cmm_Close	nodev
#define Atm_Cmm_Ioctl 	nodev

/* Supply stubs for ATM device driver entry points so that drivers can
 * be configured without the ATM infrastructure (for putting the driver
 * in the generic kernel so sizer can find it).
 */
atm_cmm_receive() { return 256; }
atm_cmm_register_dd() { return 0; }
atm_cmm_error() { return 256; }
atm_cmm_oam_receive() { return 256; }
long atm_cmm_cr2grain() { return 0; }
long atm_cmm_grain2cr() { return 0; }
long atm_cmm_grain2mod() { return 0; }
long atm_cmm_maxvccr() { return 0; }
long atm_cmm_get_time() { return 0; }
atm_cmm_register_ilmi_esc() { return 0; }
atm_cmm_unregister_ilmi_esc() { return 0; }    
#endif

/*
 *      Character Device Switch static declaration and initialization
 */
/*
 * The user may specify a different cdevsw size in the config file.
 * MAX_CDEVSW will have a default of 140 and a minimum of 90.
 */
#ifdef	MAX_CDEVSW
#if	MAX_CDEVSW < 90
#define	MAX_CDEVSW	90
#endif	/* MAX_CDEVSW < 90 */
#else	/* MAX_CDEVSW needs defining */
#define	MAX_CDEVSW	140
#endif	/* MAX_CDEVSW */

dswlock_t       cdevlock[MAX_CDEVSW];           /* cdevsw lock structure */
struct lockinfo	*cdev_lockinfo;
/*
%%% BEGIN CDEVSW TABLE (first 3 chars of this line must be %%%
*/
struct cdevsw   cdevsw[MAX_CDEVSW] =
{
	{ cnopen,	cnclose,	cnread,		cnwrite,	/*0*/
	cnioctl,	nulldev,	nulldev,	cons,
	cnselect,	cnmmap,		DEV_FUNNEL, NULL, NULL },

	{ syopen,	nulldev,	syread,		sywrite,	/*1*/
	syioctl,	nulldev,	nulldev,	0,
	syselect,	nodev,		DEV_FUNNEL_NULL, NULL, NULL },

	/* this must agree with mem_no! */
	{ nulldev,	nulldev,	mmread,		mmwrite,	/*2*/
	nodev,		nulldev,	nulldev,	0,
	seltrue,	mmmap,		DEV_FUNNEL_NULL, NULL, NULL },

#ifdef	MSERIES
	{ dkipopen,	nulldev,	dkipread,	dkipwrite,	/*3*/
	dkipioctl,	nulldev,	nodev,		0,
	seltrue,	nodev,		DEV_FUNNEL, NULL, NULL },
#else
	/* conflict: Error log device on Ultrix */
	{ logopen,	logclose,	logread,	nodev,		/*3*/
	logioctl,	nodev,		nulldev,	0,
	logselect,	nodev,		DEV_FUNNEL_NULL, NULL, NULL },
#endif

	/* this is /dev/drum */
	{ nulldev,	nulldev,	nodev,		nodev,		/*4*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	/* Reserved for STREAMS-based LAT */
	{nodev,		nodev,		nodev,		nodev,		/*5*/
	nodev,		nodev,		nodev,		0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

#if     (!defined(RPTY) || (RPTY == 0))
	{ ptsopen,	ptsclose,	ptsread,	ptswrite,	/*6*/
	ptyioctl,	ptsstop,	nodev,		0,
	ptsselect,	nodev,		DEV_FUNNEL, NULL, NULL },

#else
        /* Streams-based pty slave */
        {nodev,             nodev,          nodev,          nodev,       /*6*/
        nodev,          nodev,          nodev,          0,
        nodev,          nodev,          DEV_FUNNEL_NULL, NULL, NULL },

#endif  /* (!defined(RPTY) || (RPTY == 0)) */

#if     (!defined(RPTY) || (RPTY == 0))
	{ ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*7*/
	ptyioctl,	nulldev,	nodev,		0,
	ptcselect,	nodev,		DEV_FUNNEL, NULL, NULL},
#else
        /* New BSD master */
        { ptropen,      ptrclose,       ptrread,        ptrwrite,       /*7*/
          ptrioctl,     nodev,          nodev,          0,
          ptrselect,    nodev,          DEV_FUNNEL_NULL, NULL, NULL },
#endif  /* (!defined(RPTY) || (RPTY == 0)) */

#ifdef	MSERIES
	{ cpopen, 	cpclose,	cpread, 	cpwrite,	/*8*/
	cpioctl,	cpstop, 	cpreset,	cp_tty,
	ttselect,	nodev,		DEV_FUNNEL, NULL, NULL },
#else
	/* SCSI disk devices */
	/*
	 * Insert presto NVRAM pseudo-driver interface routines (RZ...).
	 * Warning: If these device major numbers change, then
	 *          data/presto_data.c must be modified.
	 */

        { cdisk_open,	cdisk_close,	RZread,		RZwrite,	/*8*/
	cdisk_ioctl,	nodev,		nulldev,	0,
	asyncsel,	nodev		,DEV_FUNNEL_NULL, NULL, NULL },
#endif

#ifdef	MSERIES
	{ logopen,	logclose,	logread,	nodev,		/*9*/
	logioctl,	nodev,		nulldev,	0,
	logselect,	nodev,		DEV_FUNNEL_NULL, NULL, NULL },
#else
	/* SCSI tape devices (old major number) */
	{ ctape_open,	ctape_close,	ctape_read,	ctape_write,	/*9*/
	ctape_ioctl,	nodev,		nulldev,	0,
	asyncsel,	nodev		,DEV_FUNNEL_NULL, NULL, NULL },
#endif

#ifdef	MSERIES
	{ tthopen,	tthclose,	tthread,	tthwrite,	/*10*/
	tthioctl,	nodev,		nulldev,	0,
	seltrue,	nodev,		DEV_FUNNEL, NULL, NULL },
#else
	{ nodev,	nodev,		nodev,		nodev,		/*10*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },
#endif

	/* This is the "trace" device on Pmax */
	{ nulldev,	nulldev,	nodev,		nodev,		/*11*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	/* This is now taken to reserve a major device number for
         * FDFS.  If this changes, also change the definition of
         * fdfs_major at the end of this file.  It's value is used
         * in kernel/svr4/fdfs_vnops.c
         * This was the vice fs device slot
         */
        { nulldev,      nulldev,        nodev,          nodev,          /*12*/
        nodev,          nodev,          nulldev,        0,
        nodev,          nodev,          DEV_FUNNEL, NULL, NULL },


	/* This was cmupty */
	{ Pfilt_open,	Pfilt_close,	Pfilt_read,	Pfilt_write,	/*13*/
	Pfilt_ioctl,	nodev,		nulldev,	0,
	Pfilt_select,	nodev,		DEV_FUNNEL, NULL, NULL },

        /* fdi */
        { fd_open,      fd_close,       fd_read,        fd_write,     /*14*/
        fd_ioctl,       nodev,		nulldev,	0,
        nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	{ sysdev_open,	sysdev_close,	nodev,		nodev,		/*15*/
	nodev,		nodev,		nulldev,	0,
	nodev,		sysdev_mmap,	DEV_FUNNEL_NULL, NULL, NULL },

	/* Logical Volume Manager device - cmajor and bmajor must match */
	{ lv_open0,	lv_close0,	lv_read0,	lv_write0,	/*16*/
	lv_ioctl0,	nodev,		nulldev,	lv_volgrp0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	/* DEC audit device */
	{ auditopen,	auditclose,	auditread,	nodev,  	/*17*/
	auditioctl,	nodev,		nulldev,	0,
	auditsel,	auditmmap,	DEV_FUNNEL_NULL, NULL, NULL },

	/* Security policy message passing device */
	{ spdopen,	spdclose,	spdread,	spdwrite,	/*18*/
	spdioctl,	nodev,		nulldev,	0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	/* Logical Volume Manager device - cmajor and bmajor must match */
	{ lv_open1,	lv_close1,	lv_read1,	lv_write1,	/*19*/
	lv_ioctl1,	nodev,		nulldev,	lv_volgrp1,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	/* Logical Volume Manager device - cmajor and bmajor must match */
	{ lv_open2,	lv_close2,	lv_read2,	lv_write2,	/*20*/
	lv_ioctl2,	nodev,		nulldev,	lv_volgrp2,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	/* dc7085 serial line driver */
	{ dcopen,	dcclose,	dcread,		dcwrite,	/*21*/
	dcioctl,	dcstop,		nulldev,	dc_tty,
	dcselect,	nodev,		DEV_FUNNEL, NULL, NULL },

	/* presto NVRAM pseudo-driver control "device" */
	{ propen,         nulldev,        nulldev,	nulldev,        /*22*/
        prioctl,        nulldev,        nulldev,        0,
        nodev,          nodev,		DEV_FUNNEL, NULL, NULL },

	/*
	 * Mouse Device:  /dev/mouse  
	 */
	{ wsopen,	wsclose,	nodev,		nodev,		/*23*/
	wsioctl,	wsstop,		nulldev,	0,
	wsselect,	nodev,		DEV_FUNNEL, NULL, NULL },

	/* scc serial line driver */
	{ sccopen,        sccclose,     sccread,        sccwrite, 	/*24*/
        sccioctl,       sccstop,        nulldev,        scc_tty,
        sccselect,      sccmmap,        DEV_FUNNEL, NULL, NULL },

	/*
	 * Keyboard Device:  /dev/keyboard 
	 */
	{ wsopen,	wsclose,	nodev,		nodev,		/*25*/
	wsioctl,	wsstop,		nulldev,	0,
	wsselect,	nodev,		DEV_FUNNEL, NULL, NULL },


	/* Alpha performance monitor */
	{ pfmopen,	pfmclose,	pfmread,	nodev,		/*26*/
	pfmioctl,	nodev,		nulldev,	0,
	nodev,		nodev,		DEV_FUNNEL_NULL, NULL, NULL },

        /* DSA tmscp tape devices */
        { tmscpopen,     tmscpclose,	tmscpread,      tmscpwrite,    /*27*/
          tmscpioctl,    nodev,		uq_reset,       0,
          asyncsel,      nodev,		DEV_FUNNEL, NULL, NULL },

	/* DEC MSCP disk devices ???!!!TEMPORARILY!!!??? */
        { mscp_copen,     mscp_cclose,	MSCP_read,      MSCP_write,   /*28*/
          mscp_ioctl,     nodev,	nulldev,                0,
          asyncsel,       nodev,	DEV_FUNNEL, NULL, NULL },

 	/* dhu serial line driver */
        { dhuopen,        dhuclose,	dhuread,        dhuwrite,	/*29*/
        dhuioctl,       dhustop,	nulldev,        dhu11,
        nodev,          nodev,		DEV_FUNNEL, NULL, NULL },

	/*
	 * The CAM User Agent Driver.
	 */
	{ uagtopen,	uagtclose,	nodev,		nodev,		/*30*/
	uagtioctl,	nodev,		nodev,		0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

        /* binary event logger */
	{ binlog_open,    binlog_close, binlog_read,    binlog_write,	/*31*/
	binlog_ioctl,   nodev,          nulldev,          0,
	binlog_select,  nodev,          DEV_FUNNEL_NULL, NULL, NULL },

	{ clone_open,   nodev,          nodev,          nodev,          /*32*/
	nodev,          nodev,          nodev,          0,
	nodev,          nodev,		DEV_FUNNEL_NULL, NULL, NULL },

	/*
	 * Workstation Device:  /dev/ws
	 */
	{ wsopen,	wsclose,	nodev,		nodev,		/*33*/
	wsioctl,	wsstop,		nulldev,	0,
	wsselect,	nodev,		DEV_FUNNEL, NULL, NULL },

	/* parallel printer port driver */
	{ lpopen,	lpclose,	nodev,		lpwrite,	/*34*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	/* ace serial line driver */
	{ aceopen,      aceclose,       aceread,        acewrite, 	/*35*/
        aceioctl,       acestop,        nulldev,        ace_tty,
        aceselect,      nodev,        	DEV_FUNNEL, NULL, NULL },

	/* Sound Board */
	{ nodev,	nodev,		nodev,		nodev,		/*36*/
	nodev,		nodev,		nodev,		0,
	nodev,		nodev,		DEV_FUNNEL_NULL, NULL, NULL },

	/* kernel profiling psuedo device driver */
	{ prfopen,	nulldev,	prfread,	prfwrite,	/*37*/
	prfioctl,	nodev,		nodev,		0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

        /* this is the /dev/zero driver */
	{ dzopen,	dzclose,	dzread,		dzwrite,	/*38*/
	nodev,		nodev,		nulldev,	0,
        nodev,          dzmmap,         DEV_FUNNEL_NULL, dzsegmap, C_DDIDKI },

        /* this is the /dev/mlog driver */
        { mlogopen,     mlogclose,      mlogread,       nulldev,        /*39*/
        mlogioctl,      nodev,          nulldev,        0,
        nodev,          nodev,          DEV_FUNNEL_NULL, NULL, NULL },

        { volopen, 	volclose,  	volread,    	volwrite, 	/*40*/
        volioctl,       nodev,          nulldev,        0,
        nodev,          nodev,          DEV_FUNNEL_NULL, NULL, C_DDIDKI },

        { volsopen_real,volsclose_real, nodev,          nodev,          /*41*/
        volsioctl_real, nodev,          nulldev,        0,
        nodev,          nodev,          DEV_FUNNEL_NULL, NULL, C_DDIDKI },

        { plexopen_real,plexclose_real, plexread_real,  plexwrite_real, /*42*/
        plexioctl_real, nodev,          nulldev,        0,
        nodev,          nodev,          DEV_FUNNEL_NULL, NULL, C_DDIDKI },

        { tedopen,      tedclose,       nodev,          nodev,          /*43*/
        tedioctl,       nodev,          nulldev,        0,
        nodev,          nodev,          DEV_FUNNEL_NULL, NULL, C_DDIDKI },

	/* this is the re_driver/xcr_port */
        { re_open,	re_close,	REread,		REwrite,	/*44*/
	re_ioctl,	nodev,		nulldev,	0,
	asyncsel,	nodev		,DEV_FUNNEL_NULL, NULL, NULL },

	{ lockdev_open,	lockdev_close,	lockdev_read,	nodev,		/*45*/
	lockdev_ioctl,	nodev,		nulldev,	0,
	nodev,		nodev,		DEV_FUNNEL_NULL, NULL, NULL },

	{ nodev,	nodev,		nodev,		nodev,		/*46*/
	nodev,		nodev,		nulldev,	0,
	nodev,		nodev,		DEV_FUNNEL_NULL, NULL, NULL },

	/* this is the ATM management interface */
	{ Atm_Cmm_Open, Atm_Cmm_Close,	nodev,		nodev,		/*47*/
	Atm_Cmm_Ioctl,	nodev,		nodev,		0,
	nodev,		nodev,		DEV_FUNNEL, NULL, NULL },

	/* cam_disk major for new device special files */
        { cdisk_open,	cdisk_close,	RZread,		RZwrite,	/*48*/
	cdisk_ioctl,	nodev,		nulldev,	0,
	asyncsel,	nodev		,DEV_FUNNEL_NULL, NULL, NULL },

	/* SNMP info driver */
	{ snmpopen,	snmpclose,	nodev,	nodev,			/*49*/
	snmpioctl,	nodev,		nodev,		0,
	nodev,		nodev,	DEV_FUNNEL_NULL, NULL, NULL },

	/* ISA scc serial line driver */
	{ iscc_open,    iscc_close,     iscc_read,      iscc_write, 	/*50*/
        iscc_ioctl,     iscc_stop,      nulldev,        iscc_tty,
        iscc_select,    iscc_mmap,      DEV_FUNNEL_NULL, NULL, NULL },

	/* SCSI tape devices (new major number) */
	{ ctape_open,	ctape_close,	ctape_read,	ctape_write,	/*51*/
	ctape_ioctl,	nodev,		nulldev,	0,
	asyncsel,	nodev		,DEV_FUNNEL_NULL, NULL, NULL },
};
/*
%%% END CDEVSW TABLE (first 3 chars of this line must be %%%
*/
int	nchrdev = sizeof (cdevsw) / sizeof (cdevsw[0]);

dev_t	sydev = makedev(1, 0);	/* device number for indirect tty */

int	mem_no = 2; 	/* major device number of memory special file */

/*
 * This variable lets processor config routines know if presto is config'ed
 */
int npresto_configured = NPRESTO ;

/*
 * Since DCEDFS is the default (i.e. BINARY and BINARY.ext), we need to
 * define a runtime state whether DCEDFS is actually configured.
 * The use of "#ifdef DCEDFS" is not valid (e.g. within ufs/ufs_inode.c),
 * and instead should be replaced by "if (dcedfs)" constructs.
 */
#include "dcedfs.h"
int     dcedfs = DCEDFS;

                                                                 
int     fdfs_major = FDFS_MAJOR; /* major device number of FDFS entries */

/*
 * pwrmgr subsystem stubs
 */
#include <pwrmgr_enabled.h>
#if (!PWRMGR_ENABLED)
#include <sys/sysconfig.h>
pwrmgr_register_device() { return(CFG_FRAME_EEXISTS); }
pwrmgr_deregister_device() { return(CFG_FRAME_EEXISTS); }
pwrmgr_get_devinfo() { return(CFG_FRAME_EEXISTS); }
pwrmgr_set_devinfo() { return(CFG_FRAME_EEXISTS); }
pwrmgr_power_down() { return(CFG_FRAME_EEXISTS); }
pwrmgr_power_up() { return(CFG_FRAME_EEXISTS); }
pwrmgr_battery_low() { return(CFG_FRAME_EEXISTS); }
pwrmgr_thermal_meltdown() { return(CFG_FRAME_EEXISTS); }
pwrmgr_subsys_state() { return(CFG_FRAME_EEXISTS); }
pwrmgr_notify_event() { return(CFG_FRAME_EEXISTS); }
#endif





