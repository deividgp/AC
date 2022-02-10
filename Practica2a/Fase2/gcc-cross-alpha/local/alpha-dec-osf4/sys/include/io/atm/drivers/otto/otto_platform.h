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
 * @(#)$RCSfile: otto_platform.h,v $ $Revision: 1.1.21.2 $ (DEC) $Date: 1999/02/05 13:24:11 $
 */
/* platform dependencies should go here, if possible */
/* So far this has been tested only for MIPS Ultrix */

#ifdef __osf__
/* OSF */

#define cprintf printf		/* osf doesn't distinguish printf and cprintf */

#include <machine/endian.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/vmmac.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
#include <vm/vm_kern.h>
#include <sys/proc.h>
#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>
#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/if_ether.h>
#include <net/ether_driver.h>
#include <netinet/if_fddi.h>
#include <machine/cpu.h>
#include <machine/scb.h>
#include <io/common/devdriver.h>
#include <io/dec/uba/ubavar.h>
#include <io/dec/tc/tc.h>
#include <io/dec/pci/pci.h>

#include <sys/types.h>
#include <arch/alpha/hal/cpuconf.h>
#include <sys/user.h>
#include <sys/ipc.h>
#include <net/if_llc.h>
#include <sys/vnode.h>
#include <sys/mman.h>
#include <vm/vm_mmap.h>


#ifdef __alpha
/* ALPHA OSF */
#include <hal/kn15aa.h>

#define PHYS_TO_K1(x) PHYS_TO_KSEG(x)
#define PHYS_TO_K0(x) PHYS_TO_KSEG(x)
#define wbflush()       mb()

/* caches don't need software cleaning on Alphas */
#define OTTO_CLEAN_DCACHE(sc, t, addr,len)
#endif

extern vm_offset_t  OTTO_SVTOPHY ();/* routine to convert virtual to physical */
struct otto_dma_handle;
struct otto_data;


extern unsigned long otto_dma_alloc (caddr_t address, unsigned len,
        struct otto_data *od, struct otto_dma_handle **phandle);
/* Return a DMA address from a virtual address.   Must be called
   with softc lock held.  A struct otto_dma_handle is prepended to the linked
   list whose head is "*phandle".   This struct should be freed by
   a subsequent call to otto_dma_free.  */


extern void otto_dma_free (struct otto_data *od,
	struct otto_dma_handle **phandle, int num);
/* Free DMA resources allocated by otto_dma_alloc. Must be called
   with softc lock held.   The first "num" otto_dma_handle structs
   on the linked list whose head is "*phandle" are freed and removed
   from the list.  If "num" is -1, or if "num" exceeds the number of
   entries in the list, all the entries in the list are freed and removed
   from the list. */


/* The OSF allocator ignores flags.  This means we can't allocate a 
   contiguous memory region dynamically.  */
#define KM_ALLOC(addr, type, length, f1, f2) ((addr) = \
	(type) kmem_alloc(kernel_map, length))
#define NO_CONTIGUOUS_MALLOC

struct ether_addr {
        u_char  ether_addr_octet[6];
};


#define CONTROLLER_STRUCT	controller
#define DRIVER_STRUCT	driver
#define STD_TYPE caddr_t
#define UNIT_NUM ctlr_num

/* MBUF handling */
#define _OTTOMGETW(m,w)	do { MGETHDR((m), (w), MT_DATA); \
		if (m) {(m)->m_len=MHLEN;} } while (0)
#define _OTTOMCLGETW(m,w) do { \
		_OTTOMGETW(m,w); \
		if ((m)) { \
			MCLGET((m), (w)); \
			if (((m)->m_flags & M_EXT) == 0) { \
				OTTOMFREEM((m)); \
				(m) = (struct mbuf *)NULL; \
			} else { \
				(m)->m_len=MCLBYTES; \
			} \
		} \
	} while (0)

#define OTTOMLEN MHLEN

#else
/* ULTRIX */

#include "../machine/pte.h"

#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/buf.h"
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/vmmac.h"
#include "../h/ioctl.h"
#include "../h/errno.h"
#include "../h/time.h"
#include "../h/kernel.h"
#include "../h/kmalloc.h"
#include "../h/proc.h"

#include "../net/net/if.h"
#include "../net/net/netisr.h"
#include "../net/net/route.h"
#include "../net/netinet/in.h"
#include "../net/netinet/in_var.h"
#include "../net/netinet/in_systm.h"
#include "../net/netinet/ip.h"
#include "../net/netinet/ip_var.h"
#include "../net/netinet/if_ether.h"
#include "../net/net/ether_driver.h"
#include "../net/netinet/if_fddi.h"
#include "../machine/cpu.h"
#include "../machine/scb.h"
#include "../io/uba/ubavar.h"
#include "../io/tc/tc.h"

#include "packetfilter.h"       /* NPACKETFILTER */
#include "../h/types.h"
#include "../h/errlog.h"
#include "../../machine/common/cpuconf.h"
#include "../h/user.h"
#include "../h/ipc.h"
#if     NPACKETFILTER > 0
#include "../net/net/pfilt.h"
#endif
#include "../net/net/if_llc.h"

#ifdef mips
/* MIPS ULTRIX */

/* caches need software cleaning on MIPS */
#define OTTO_CLEAN_DCACHE(sc, t, addr,len) otto_clean_dcache (sc, t, addr, len)

#endif

#define CONTROLLER_STRUCT	uba_device
#define DRIVER_STRUCT	uba_driver
#define STD_TYPE u_short
#define UNIT_NUM ui_unit
#define OTTO_IFTYPE IFT_ETHER

/* MBUF handling */
#define _OTTOMGETW(m, w)     do { MGET((m), (w), MT_DATA); } while (0)
#define _OTTOMCLGETW(m, w) do { \
		struct mbuf *p; \
		_OTTOMGETW(m, M_DONTWAIT); \
		if ((m)) { \
			MCLGET((m), p); \
			if (p == 0) { \
				OTTOMFREEM((m)); \
				(m) = (struct mbuf *)NULL; \
			} \
		} \
	} while (0)

#define OTTO_SVTOPHY svtophy
#endif	/* ultrix */

#ifdef IFF_MULTICAST
#define OTTO_IFF_MULTICAST IFF_MULTICAST
#else
#define OTTO_IFF_MULTICAST 0
#endif
#ifdef IFF_DYNPROTO
#define OTTO_IFF_DYNPROTO IFF_DYNPROTO
#else
#define OTTO_IFF_DYNPROTO 0
#endif

#ifndef M_CLUSTERSZ
#define M_CLUSTERSZ MCLBYTES
#endif 


#ifdef PFWD
#include "pfwd.h"
#endif PFWD

#if (NPFWD > 0)
#include "../pfwd/if_pfwd.h"
#include "../pfwd/if_pfwddefs.h"
#endif

/* MBUF handling */
#define OTTOMFREE(mx,n)       MFREE(mx,n)
#define OTTOMFREEM(m)   m_freem(m)
#define OTTOMGET(m)     _OTTOMGETW (m, M_DONTWAIT)
#define OTTOMGETWAIT(m) _OTTOMGETW (m, M_WAIT)
#define OTTOMCLGET(m)	_OTTOMCLGETW (m, M_DONTWAIT)
#define OTTOMCLGETWAIT(m)	_OTTOMCLGETW (m, M_WAIT)

#define OTTO_IFSTART(ifp)	otto_ifstart ((ifp)->if_unit)

/* 
 * ATM subsets are optional so the generic kernel will not
 * necessarily have them available when trying to build the
 * OPPO driver.  When building the driver, use the ATM header
 * files.  When just building the if_otto_data.c file for the
 * kernel, however, don't use these files and instead use
 * equivalently sized placeholders.
 */
#ifdef BINARY			/* building the driver */
#include <atm/sys/atm_osf.h>
#include <atm/sys/atm.h>
#include <atm/sys/atm_adi.h>
#else				/* building if_otto_data.c */
typedef void *atm_vc_p;
typedef void *atm_drv_handle_t;
typedef void *atm_drv_params_p;
#endif

#include <io/atm/drivers/otto/if_ottoreg.h>
#include <io/atm/drivers/otto/if_ottomaint.h>
#include <io/atm/drivers/otto/otto_fakesnmp.h>
#include <io/atm/drivers/otto/if_ottodefs.h>

struct  otto_softc {
        struct otto_lock lk_otto_softc;
	struct otto_data data;
};

#include <io/atm/drivers/otto/ottoexec.h>
#include <io/atm/drivers/otto/suni.h>
#include <io/atm/drivers/otto/otto_flow.h>

#define	OTTO_PIOR(_a)    READ_BUS_D32 ((io_handle_t)(_a))	/* 32 bit PIO read */
#define	OTTO_PIOW(_a,_d) WRITE_BUS_D32 ((io_handle_t)(_a), (_d))	/* 32 bit PIO write */
