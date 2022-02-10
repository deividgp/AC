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
#pragma ident "@(#)$RCSfile: steal_mem.c,v $ $Revision: 1.1.36.2 $ (DEC) $Date: 1997/05/16 20:35:36 $"

/************************************************************************
 *									*
 *			Copyright (c) 1991, 1993, 1994 by		*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any	other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or	reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

#include <sys/param.h>
#include <hal/cpuconf.h>
#include <machine/cpu.h>
#include <mach/vm_param.h>
#include <mach/kern_return.h>
#include <sys/types.h>
#include <sys/malloc.h>

/*
 * Config-generated headers
 */
/* [DEC Include BEGIN] */
/* [DEC-PV Include BEGIN */
#include "pv.h"
/* [DEC-PV Include END] */
/* [DEC-PVL Include BEGIN */
#include "pvl.h"
/* [DEC-PVL Include END] */
/* [DEC-TE Include BEGIN */
#include "te.h"
#include <io/dec/netif/if_tereg.h>
/* [DEC-TE Include END] */
/* [DEC Include END] */

/*
 * External definitions
 */
/* [DEC ExternalDeclarations BEGIN] */
/* [DEC ExternalDeclarations END] */

/*
 * Common
 */
/* [DEC ExternalDefinitions BEGIN] */
vm_offset_t ws_eventQueue;
vm_offset_t ws_heap_start = (vm_offset_t) NULL;
vm_offset_t ws_heap_end = (vm_offset_t) NULL;
vm_offset_t ws_heap_at = (vm_offset_t) NULL;
size_t ws_heap_size = (size_t) 0;
/* [DEC ExternalDefinitions END] */

/*
 * Versioning information
 */
/* [DEC Version BEGIN] */
/* [DEC-PV Version 1.0.0] */
/* [DEC-PVL Version 1.0.0] */
/* [DEC Version END] */

/*
 * Various data definitions
 */
/* [DEC DataDefinition BEGIN] */

/* [DEC-PV DataDefinition BEGIN] */
/*
 * PV memory descriptors
 */
#if NPV > 0
vm_offset_t pv_mem_bot;
vm_offset_t pv_mem_top;
vm_offset_t pv_page_table_0;		/* for PV device */
vm_offset_t pv_page_table_1;		/* for GCP device */
vm_offset_t pv_buffers;			/* ring buffs, infos, misc */
size_t pv_buffer_size;
size_t pv_page_table_0_size;
size_t pv_page_table_1_size;
#endif /* NPV */
/* [DEC-PV DataDefinition END] */

/* [DEC-PVL DataDefinition BEGIN] */
/*
 * PVL memory descriptors
 */
#if NPVL > 0
vm_offset_t pvl_mem_bot;
vm_offset_t pvl_mem_top;
vm_offset_t pvl_page_table_0;
vm_offset_t pvl_ring_buffers;
vm_offset_t pvl_misc_buffers;
size_t pvl_ring_buffer_size;
size_t pvl_page_table_0_size;
#endif /* NPVL */
/* [DEC-PVL DataDefinition END] */

/* [DEC-TE DataDefinition BEGIN] */
#if NTE > 0
vm_offset_t te_bufptr[NTE];
#endif /* NTE */
/* [DEC-TE DataDefinition END] */

/* [DEC DataDefiniition END] */

extern	int	cpu;

int
steal_mem()
{
    /*
     * Binary logger needs a page aligned page to map shared 
     * screen control info.
     */

    ws_eventQueue = (vm_offset_t) contig_malloc(PAGE_SIZE, PAGE_SIZE, 0,
							   M_WS, M_NOWAIT);
    if( ws_eventQueue == NULL ) 
	    printf("steal_mem: Couldn't allocate memory for ws_eventQueue.\n");
    ws_eventQueue = KSEG_TO_PHYS(ws_eventQueue);

    /*
     * Grab an additional page which will be used for various info
     * areas.  These will often be mapped into a server process.
     */

    ws_heap_at = (vm_offset_t) contig_malloc(PAGE_SIZE, PAGE_SIZE, 0, M_WS,
								 M_NOWAIT);
    if( ws_heap_at == NULL ) 
	    printf("steal_mem: Couldn't allocate memory for ws_heap.\n");
    ws_heap_start = ws_heap_at = KSEG_TO_PHYS(ws_heap_at);

    ws_heap_end = ws_heap_start + PAGE_SIZE;
    ws_heap_size = PAGE_SIZE;


/* [DEC CodeDefinition BEGIN] */

/* [DEC-PV CodeDefinition BEGIN] */
#if NPV > 0

    /*
     * PV memory allocation
     *
     * Needed:
     *
     * 128KB ring buffer per module
     * 4K entry shadow page table for PV per module
     * 8K entry shadow page table for GCP per module
     * 1 page clip data buffer per module
     * 1 page private packet area
     * 1 page for overrun and dead data
     * 1 page for info structs
     *
     */

    {
	unsigned long skipped;

	/*
	 * For PVA, shadow page table must be aligned to a quantity
	 * equivalent to the page table size.
	 */
#define _128KB		(1<<17)
#define	_4KEntry	((1<<12) * sizeof(int *))
#define	_4KTotal	(NPV*_4KEntry)
#define	_8KEntry	((1<<13) * sizeof(int *))
#define	_8KTotal	(NPV*_8KEntry)
#define _PVBuffs	( _128KB * NPV + (3 + NPV) * NBPG )

    	pv_page_table_1 = (vm_offset_t) contig_malloc(_8KTotal, _8KEntry,
						 	0, M_WS, M_NOWAIT);
    	pv_page_table_0 = (vm_offset_t) contig_malloc(_4KTotal, 0, 0, M_WS,
								 M_NOWAIT);
    	pv_buffers = (vm_offset_t) contig_malloc(_PVBuffs, 0, 0, M_WS,
								 M_NOWAIT);
#ifdef notanymore
	if( pv_page_table_1 == NULL || pv_page_table_0 == NULL ||
					 pv_buffers == NULL) {
	    printf("steal_mem: Couldn't allocate memory for PV[G] support.  ");
	    printf("steal_mem: PV[G] options will not be enabled.\n");
	}
#endif
	pv_page_table_1 = KSEG_TO_PHYS(pv_page_table_1);
	pv_page_table_0 = KSEG_TO_PHYS(pv_page_table_0);
	pv_buffers = KSEG_TO_PHYS(pv_buffers);

	pv_buffer_size = _PVBuffs;
	pv_page_table_0_size = _4KEntry;
	pv_page_table_1_size = _8KEntry;
#undef      _128KB
#undef      _4KEntry
#undef	    _4KTotal
#undef      _8KEntry
#undef	    _8KTotal
#undef      _PVBuffs
    }

#endif /* NPV > 0 */
/* [DEC-PV CodeDefinition END] */

/* [DEC-PVL CodeDefinition BEGIN] */
#if NPVL > 0

    /*
     * PVL memory allocation
     *
     * Needed:
     *
     * 128KB ring buffer per module
     * 4K entry shadow page table for PV per module
     * 1 page clip data buffer per module
     * 1 page private packet area
     * 1 page for overrun and dead data
     * 1 page for info structs
     *
     */

    {
        unsigned long skipped;

	/*
	 * For PVA, shadow page table must be aligned to a quantity
	 * equivalent to the page table size.
	 */
#define _4KB		( 4*1024 )
#define _64MB		(64*1024*1024)
#define _128KB		( 128*1024 )
#define	_4KEntry	((1<<12) * sizeof(int *))
#define	_4KTotal	(NPVL*_4KEntry)
#define	_PVLRingBuffs	( _128KB * NPVL )
#define _PVLBuffs	( (3 + NPVL) * NBPG )

    	pvl_page_table_0 = (vm_offset_t) contig_malloc(_4KTotal, _4KEntry,
						       _64MB, M_WS, M_NOWAIT);
    	pvl_ring_buffers = (vm_offset_t) contig_malloc(_PVLRingBuffs, _4KB,
						       _64MB, M_WS, M_NOWAIT);
    	pvl_misc_buffers = (vm_offset_t) contig_malloc(_PVLBuffs, 0,
						       _64MB, M_WS, M_NOWAIT);
#ifdef notanymore
	if( pvl_page_table_0 == NULL || pvl_ring_buffers == NULL ||
					 pvl_misc_buffers == NULL) {
	    printf("steal_mem: Couldn't allocate memory for PVL[G] support.  ");
	    printf("steal_mem: PVL[G] options will not be enabled.\n");
	}
#endif
	pvl_page_table_0 = KSEG_TO_PHYS(pvl_page_table_0);
	pvl_ring_buffers = KSEG_TO_PHYS(pvl_ring_buffers);
	pvl_misc_buffers = KSEG_TO_PHYS(pvl_misc_buffers);

	pvl_ring_buffer_size = _PVLBuffs;
	pvl_page_table_0_size = _4KEntry;
#undef	    _4KB
#undef	    _64MB
#undef      _128KB
#undef      _4KEntry
#undef	    _4KTotal
#undef	    _PVLRingBuffs
#undef      _PVLBuffs
    }

#endif /* NPVL > 0 */
/* [DEC-PVL CodeDefinition END] */

    /* 
     * TGEC (Cobra Ethernet device) driver buffer allocations: the requirement 
     * here is that all addresses specified to the device be within the first 
     * Gbyte (30-bits) of the physical address space. Individual buffers are
     * carved up in the driver; all we need to do here is get a big chunck 
     * that's at least octaword-aligned. Since we are doing this stealing
     * rather early, and since we are already page-aligned, both requirements
     * can be met easily.
     */
#if NTE > 0

    {
    register u_int bytes_required = TE_BUFFER_REQ; /* if_tereg.h */
    register u_int i=0;

    	for (i=0; i<NTE; i++) {
    		te_bufptr[i] = (vm_offset_t) contig_malloc( bytes_required,
				 0, ((1 << 30) -1), M_TGEC, M_WAITOK|M_ZERO);
		if(te_bufptr[i] == NULL)
			printf("steal_mem: failed to allocate memory for tgec\n");
    	}
    }

#endif
/* [DEC CodeDefinition END] */

    /* 
     * done
     */
    return (0);
}
