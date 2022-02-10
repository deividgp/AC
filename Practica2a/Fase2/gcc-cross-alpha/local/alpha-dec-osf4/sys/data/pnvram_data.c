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
 * @(#)$RCSfile: pnvram_data.c,v $ $Revision: 1.1.20.2 $ (DEC) $Date: 1998/08/07 12:40:42 $
 */

/*
 * Digital PCI non-voltile RAM driver  (ZEPHYR)
 */

#include <vm/vm_kern.h>
#include <sys/presto.h>
#include <io/common/devdriver.h>
#include <io/dec/pci/pci.h>
#include <machine/rpb.h>
#include <io/dec/pci/pnvram_reg.h>

					
/*
 * Define the softc for the PCI NVRAM driver
 */
struct	pnvram_softc {

    simple_lock_data_t pnv_lock;  /* softc lock                         */
    io_handle_t	csr_base;	  /* io-handle for PCI mem-space CSRs 	*/

    /*
     * DMA control
     */
    volatile u_int  dma_in_progress;  /* If DMA is completed or not 	*/
    dma_handle_t dma_p;		  /* handle to dma resources		*/
    struct controller *ctlr;	  /* pointer to nvram controller struct	*/

    vm_offset_t cache_phys_start; /* CPU-physical address of NVRAM cache */
    vm_offset_t	cache_base;	  /* base address of NVRAM on PCI bus 
				     that controller is attached to	*/
    vm_offset_t	cache_kseg_start; /* KSEG addr of the presto cache	*/
    u_int       cache_size;	  /* size of NVRAM cache 		*/
    u_int       cache_offset;	  /* Offset from cache_base		*/
    u_int	diag_status;	  /* If the board passed diags or not 	*/
    ihandler_id_t   *hid;	  /* ihander_id_t rtn from handler_add 	*/
    u_int       access_mode;      /* dense / sparse register accesses */
    u_int       chip_rev;         /* hw rev of PINK chip */
};


#ifdef BINARY
extern struct 	pnvram_softc *pnvram_softc;
extern struct	controller *pnvram_info[];
#else
#include "pnvram.h"
struct 	pnvram_softc *pnvram_softc;
struct	controller *pnvram_info[NPNVRAM];
#endif
