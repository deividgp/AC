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
 * @(#)$RCSfile: platform.h,v $ $Revision: 1.1.2.4 $ (DEC) $Date: 1995/12/15 14:41:45 $
 */

#include	<sys/types.h>
#include	<machine/rpb.h>
#include	<sys/sysconfig.h>
#include	<sys/errno.h>
#include	<mach/machine.h>
#include	<hal/cpuconf.h>
#include	<io/common/devdriver.h>


/* from arch/alpha/hal/cpusw.c */
extern	u_long          no_dma_map_alloc();
extern	u_long          no_dma_map_load();
extern	int	        no_dma_map_unload();
extern	int             no_dma_map_dealloc();
extern 	int             no_dma_min_bound();
extern	int             no_machcheck();
extern	int             no_harderr_intr();
extern	int             no_softerr_intr();
extern	int             no_memenable();
extern	int             no_config();
extern	int             no_badaddr();
extern	int             no_readtodr();
extern	int             no_writetodr();
extern	int             no_ring_bell();
extern	boolean_t       no_testpage();
extern	int             no_config_secondary();
extern	int             no_init_secondary();
extern	int             no_trans_dumpdev();
extern	int             no_get_info();
extern	int             no_init();
extern	long            no_read_io_port();
extern	void            no_write_io_port();
extern	u_long          no_iohandle_to_phys();
extern	int 	        no_io_copyin();
extern	int             no_io_copyout();
extern	int             no_io_zero();
extern	int             no_io_copyio();

/* from arch/alpha/hal/console.c */
extern	void	hal_pci_cons2dev(struct item_list *, struct bus *);
extern	void	hal_pci_cons2ctl(struct item_list *, struct bus *);
extern	void	hal_pci_dev2cons(struct item_list *, int);
extern	void	hal_pci_dev2user(struct item_list *);
extern	void	hal_pci_dump_dev(struct dump_request *, int);
extern	void	hal_pci_cons_devstr(int, char *, struct device *,
			char *, u_int, u_int);


#ifdef  _MULTI_PLATFORM
#define ROUTINE_ENTRYPT(name, param)    PLATFORM()##_##name param
#else
#define ROUTINE_ENTRYPT(name, param)    name param
#endif
