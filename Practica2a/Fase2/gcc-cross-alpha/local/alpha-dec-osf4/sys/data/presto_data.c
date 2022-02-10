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
#pragma ident "@(#)$RCSfile: presto_data.c,v $ $Revision: 1.2.32.7 $ (DEC) $Date: 1995/12/04 15:41:53 $"

/*
 *	Portions of this software have been licensed to 
 *	Digital Equipment Company, Maynard, MA.
 *	Copyright (c) 1990 Legato Systems, Inc.  ALL RIGHTS RESERVED.
 */

#include "presto.h"
#if NPRESTO > 0		/* Presto configured */

#include <sys/prestoioctl.h>

struct prtab *bprtabs[MAX_BPRTABS];
struct prtab *cprtabs[MAX_CPRTABS];

/* Do RZ class disks */
#include "scsi.h"

#if NSCSI > 0

/*
 * presto - to - SCSI disk driver interface routines
 */

extern int cdisk_open(), cdisk_close(), cdisk_strategy(), cdisk_read(), cdisk_write();
int nulldev();
int RZready();

/*
 * Define presto NVRAM pseudo-driver per-device structures.
 * NOTE:
 *	These data structures are heavily tied to the device major
 *	numbers defined in conf.c; if those change, these must
 *	also change.
 */
#define FIRST_RZ_MAJOR 8

struct prtab RZprtab0 = {
	(dev_t) FIRST_RZ_MAJOR,
	cdisk_strategy,
	RZready,
	cdisk_close,
	NULL
};
/*
 * Changes for Device naming
 */
#define NEW_SCSI_MAJOR 48

struct prtab RZprtab1 = {
	(dev_t) NEW_SCSI_MAJOR,
	cdisk_strategy,
	RZready,
	cdisk_close,
	NULL
};

/*
 * Is device ready to be opened during presto crash recovery?
 * Presto crash recovery normally happens before we get to single user mode.
 * Some drivers (e.g. shadowing) may want opens deferred until they can
 * get at their configuration data.
 */
int
RZready(dev)
	dev_t dev;
{
	return (1);	/* always ready to be opened */
}

int
RZbopen(dev, flag, fmt)
	dev_t dev;
	int flag, fmt;
{
	return (cdisk_open(dev, flag, fmt));
}

int
RZbclose(dev, flag, fmt)
	dev_t dev;
	int flag, fmt;
{

	return (PRclose(dev, flag, fmt, cdisk_close, bprtabs[major(dev)]));
}

RZstrategy(bp)
	struct buf *bp;
{

	PRstrategy(bp, cdisk_strategy);
}

int
RZread(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (PRread(dev, uio, cdisk_read, cprtabs[major(dev)]));
}

int
RZwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (PRwrite(dev, uio, cdisk_write, cprtabs[major(dev)]));
}
#endif /* NSCSI > 0 */


/* Do UQ class disks */
#include "uq.h"
#include "ci.h"

#if NCI>0 || NUQ >0

/*
 * presto - to - MSCP disk driver interface routines
 */

extern int mscp_strategy(), mscp_read(), mscp_write(),
	mscp_bopen(), mscp_bclose();
int MSCP_ready();

/*
 * Define presto NVRAM pseudo-driver per-device structures.
 * NOTE:
 *	These data structures are heavily tied to the device major
 *	numbers defined in conf.c; if those change, these must
 *	also change.
 */
#define FIRST_UQ_MAJOR 23

struct prtab UQprtab0 = {
	(dev_t) FIRST_UQ_MAJOR,
	mscp_strategy,
	MSCP_ready,
	mscp_bclose,
	NULL
};

/*
 * Is device ready to be opened during presto crash recovery?
 * Presto crash recovery normally happens before we get to single user mode.
 * Some drivers (e.g. shadowing) may want opens deferred until they can
 * get at their configuration data.
 */
int
MSCP_ready(dev)
	dev_t dev;
{
	return (1);	/* always ready to be opened */
}

int
MSCP_bopen(dev, flag, fmt)
	dev_t dev;
	int flag, fmt;
{
	return (mscp_bopen(dev, flag, fmt));
}

int
MSCP_bclose(dev, flag, fmt)
	dev_t dev;
	int flag, fmt;
{

	return (PRclose(dev, flag, fmt, mscp_bclose, bprtabs[major(dev)]));
}

MSCP_strategy(bp)
	struct buf *bp;
{

	PRstrategy(bp, mscp_strategy);
}

int
MSCP_read(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (PRread(dev, uio, mscp_read, cprtabs[major(dev)]));
}

int
MSCP_write(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (PRwrite(dev, uio, mscp_write, cprtabs[major(dev)]));
}

#endif /* NCI>0 || NUQ >0 */


/* LVM logical devices */

#include <lv.h>

#if NLV > 0

/* Logical Volume Manager - cmajor and bmajor must match */

/* define Presto-to-LVM interface routines */
#include <lvm/lvmd.h>
extern int	lv_open(), lv_close();
extern int	lv_strategy();
extern int	lv_read(), lv_write();
extern int	lv_ready();

/* define presto NVRAM psuedo-driver per-device structures.
 * NOTE:
 *	These data structures are heavily tied to the device major
 *	numbers defined in conf.c;  if those change, these must
 *	also change.
 */

#define FIRST_LVM_MAJOR	16

struct prtab LVMprtab0 = {
    (dev_t) FIRST_LVM_MAJOR,
    lv_strategy,
    lv_ready,
    lv_close,
    NULL
};

int
lv_open0(dev, flag, fmt)
    dev_t dev;
    int flag, fmt;
{
    return (lv_open(dev, flag, fmt));
}

int
lv_close0(dev, flag, fmt)
    dev_t dev;
    int flag, fmt;
{
    return (PRclose(dev, flag, fmt, lv_close, bprtabs[major(dev)]));
}

lv_strategy0(bp)
    struct buf *bp;
{
    PRstrategy(bp, lv_strategy);
}

int
lv_read0(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    return (PRread(dev, uio, lv_read, cprtabs[major(dev)]));
}

int
lv_write0(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    return (PRwrite(dev, uio, lv_write, cprtabs[major(dev)]));
}

#endif /* NLV > 0 */

#if NLV > 1

#define SECOND_LVM_MAJOR	19

struct prtab LVMprtab1 = {
    (dev_t) SECOND_LVM_MAJOR,
    lv_strategy,
    lv_ready,
    lv_close,
    NULL
};

int
lv_open1(dev, flag, fmt)
    dev_t dev;
    int flag, fmt;
{
    return (lv_open(dev, flag, fmt));
}

int
lv_close1(dev, flag, fmt)
    dev_t dev;
    int flag, fmt;
{
    return (PRclose(dev, flag, fmt, lv_close, bprtabs[major(dev)]));
}

lv_strategy1(bp)
    struct buf *bp;
{
    PRstrategy(bp, lv_strategy);
}

int
lv_read1(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    return (PRread(dev, uio, lv_read, cprtabs[major(dev)]));
}

int
lv_write1(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    return (PRwrite(dev, uio, lv_write, cprtabs[major(dev)]));
}

#endif /* NLV > 1 */

#if NLV > 2

#define THIRD_LVM_MAJOR	20

struct prtab LVMprtab2 = {
    (dev_t) THIRD_LVM_MAJOR,
    lv_strategy,
    lv_ready,
    lv_close,
    NULL
};

int
lv_open2(dev, flag, fmt)
    dev_t dev;
    int flag, fmt;
{
    return (lv_open(dev, flag, fmt));
}

int
lv_close2(dev, flag, fmt)
    dev_t dev;
    int flag, fmt;
{
    return (PRclose(dev, flag, fmt, lv_close, bprtabs[major(dev)]));
}

lv_strategy2(bp)
    struct buf *bp;
{
    PRstrategy(bp, lv_strategy);
}

int
lv_read2(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    return (PRread(dev, uio, lv_read, cprtabs[major(dev)]));
}

int
lv_write2(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    return (PRwrite(dev, uio, lv_write, cprtabs[major(dev)]));
}

#endif /* NLV > 2 */


#include "xcr.h"
#if NXCR > 0 

/*
 * presto - to - EISA RAID disk driver interface routines
 */

extern int re_open(), re_close(), re_strategy(), re_read(), re_write();
int nulldev();
int REready();

/*
 * Define presto NVRAM pseudo-driver per-device structures.
 * NOTE:
 *	These data structures are heavily tied to the device major
 *	numbers defined in conf.c; if those change, these must
 *	also change.
 */
#define FIRST_RE_MAJOR 11

struct prtab REprtab0 = {
	(dev_t) FIRST_RE_MAJOR,
	re_strategy,
	REready,
	re_close,
	NULL
};

/*
 * Is device ready to be opened during presto crash recovery?
 * Presto crash recovery normally happens before we get to single user mode.
 * Some drivers (e.g. shadowing) may want opens deferred until they can
 * get at their configuration data.
 */
int
REready(dev)
	dev_t dev;
{
	return (1);	/* always ready to be opened */
}

int
REbopen(dev, flag, fmt)
	dev_t dev;
	int flag, fmt;
{
	return (re_open(dev, flag, fmt));
}

int
REbclose(dev, flag, fmt)
	dev_t dev;
	int flag, fmt;
{

	return (PRclose(dev, flag, fmt, re_close, bprtabs[major(dev)]));
}

REstrategy(bp)
	struct buf *bp;
{

	PRstrategy(bp, re_strategy);
}

int
REread(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (PRread(dev, uio, re_read, cprtabs[major(dev)]));
}

int
REwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{

	return (PRwrite(dev, uio, re_write, cprtabs[major(dev)]));
}
#endif /* XCR > 0 */


/*
 * Define presto NVRAM pseudo-driver per-device control array.
 * NOTE:
 *	These data structures are heavily tied to the device major
 *	numbers defined in conf.c; if those change, this must
 *	also change.
 *
 *	This table is sized to correspond to the maximun number of bdevsw[]
 *	entries in conf.c.  Notice that there are unused entries at the 
 *	end of the table.  This allows for the insertion of entrypoints for
 *	drivers whose major number is dynamically allocated.
 */

struct prtab *bprtabs[MAX_BPRTABS] = {
	0,	/*0*/
	0,	/*1*/
	0,	/*2*/
	0,	/*3*/
	0,	/*4*/
	0,	/*5*/
	0,	/*6*/
	0,	/*7*/
#if NSCSI > 0
	&RZprtab0,	/*8*/	/* first scsi block device (same as char) */
#else
	0,	/*8*/
#endif
	0,	/*9*/
	0,	/*10*/
#if NXCR > 0 
	&REprtab0,      /*11*/   /* Only EISA Raid block device */
#else
	0,      /*11*/
#endif
	0,	/*12*/
	0,	/*13*/
	0,	/*14*/
	0,	/*15*/
#if NLV > 0
	&LVMprtab0,	/*16*/	/* LVM logical devices -- VG 1 */
#else
	0,	/*16*/
#endif
	0,	/*17*/
	0,	/*18*/
#if NLV > 1
	&LVMprtab1,	/*19*/	/* LVM logical devices -- VG 2 */
#else
	0,	/*19*/
#endif
#if NLV > 2
	&LVMprtab2,	/*20*/	/* LVM logical devices -- VG 3 */
#else
	0,	/*20*/
#endif
	0,	/*21 */
	0,	/*22*/
#if NCI > 0 || NUQ >0
	&UQprtab0,	/*23*/  /* first mscp (uq) block device */
#else
	0,	/*23*/
	0,	/*24*/
	0,	/*25*/
	0,	/*26*/
	0,	/*27*/
	0,	/*28*/
	0,	/*29*/
	0,	/*30*/
	0,	/*31*/
	0,	/*32*/
	0,	/*33*/
	0,	/*34*/
	0,	/*35*/
	0,	/*36*/
	0,	/*37*/
	0,	/*38*/
	0,	/*39*/
	0,	/*40*/
	0,	/*41*/
	0,	/*42*/
	0,	/*43*/
	0,	/*44*/
	0,	/*45*/
	0,	/*46*/
	0,	/*47*/
#if NSCSI > 0
	&RZprtab1,	/*48*/	/* new (device naming) scsi block device 
				 * (same as char) */
#else
	0,	/*48*/
#endif
#endif

};

/* maximum block device major number that can be "prestoized" */
int pr_nprbdev = sizeof (bprtabs) / sizeof (bprtabs[0]) - 1;

/*
 *	This table is sized to correspond to the maximun number of cdevsw[]
 *	entries in conf.c.  Notice that there are unused entries at the 
 *	end of the table.  This allows for the insertion of entrypoints for
 *	drivers whose major number is dynamically allocated.
 */

struct prtab *cprtabs[MAX_CPRTABS] = {
	0,	/*0*/
	0,	/*1*/
	0,	/*2*/
	0,	/*3*/
	0,	/*4*/
	0,	/*5*/
	0,	/*6*/
	0,	/*7*/
#if NSCSI > 0
	&RZprtab0,	/*8*/	/* first scsi char device (same as block) */
#else
	0,	/*8*/
#endif
	0,	/*9*/
	0,	/*10*/
	0,	/*11*/
	0,	/*12*/
	0,	/*13*/
	0,	/*14*/
	0,	/*15*/
#if NLV > 0
	&LVMprtab0,	/*16*/	/* LVM logical devices -- VG 1 */
#else
	0,	/*16*/
#endif
	0,	/*17*/
	0,	/*18*/
#if NLV > 1
	&LVMprtab1,	/*19*/	/* LVM logical devices -- VG 2 */
#else
	0,	/*19*/
#endif
#if NLV > 2
	&LVMprtab2,	/*20*/	/* LVM logical devices -- VG 3 */
#else
	0,	/*20*/
#endif
	0,	/*21 */
	0,	/*22*/
	0,	/*23*/
	0,	/*24*/
	0,	/*25*/
	0,	/*26*/
	0,	/*27*/
#if NCI > 0 || NUQ > 0
	&UQprtab0,	/*28*/  /* first mscp (uq) raw device */
#else
	0,	/*28*/
#endif
	0,	/*29*/
	0,	/*30*/
	0,	/*31*/
	0,	/*32*/
	0,	/*33*/
	0,	/*34*/
	0,	/*35*/
	0,	/*36*/
	0,	/*37*/
	0,	/*38*/
	0,	/*39*/
	0,	/*40*/
	0,	/*41*/
	0,	/*42*/
	0,	/*43*/
#if NXCR > 0 
	&REprtab0,	/*44*/  /* Only EISA Raid block device */
#else
	0,	/*44*/
#endif
	0,	/*45*/
	0,	/*46*/
	0,	/*47*/
#if NSCSI > 0
	&RZprtab1,	/*48*/	/* new (device naming) scsi char device 
				 * (same as block) */
#else
	0,	/*48*/
#endif
};

/* maximum character device major number that can be "prestoized" */
int pr_nprcdev = sizeof (cprtabs) / sizeof (cprtabs[0]) - 1;

#else /* Presto not configured */

long prmetaonly = 0; /* dummy */

#endif /* NPRESTO > 0 */

