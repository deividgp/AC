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
#pragma ident "@(#)$RCSfile: if_lpa_platform.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1997/08/28 16:25:42 $"

#ifndef _IF_LPA_PLATFORM_H_
#define _IF_LPA_PLATFORM_H_

/* platform dependencies should go here, if possible */

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
#include <sys/mman.h>
#include <vm/vm_mmap.h>
#include <hal/kn15aa.h>

#define PHYS_TO_K1(x) PHYS_TO_KSEG(x)
#define PHYS_TO_K0(x) PHYS_TO_KSEG(x)
#define wbflush()       mb()

/* caches don't need software cleaning on Alphas */
#define LPA_CLEAN_DCACHE(sc, t, addr,len)

extern vm_offset_t  LPA_SVTOPHY ();/* routine to convert virtual to physical */

#if 0

/* The OSF allocator ignores flags.  This means we can't allocate a 
   contiguous memory region dynamically.  */
#define KM_ALLOC(addr, type, length, f1, f2) ((addr) = \
	(type) kmem_alloc(kernel_map, length))
#define NO_CONTIGUOUS_MALLOC

#endif

typedef unsigned char ETHER_ADDR[6];

/* MBUF handling */
#define _LPAMGETW(m,w)	do { MGETHDR((m), (w), MT_DATA); \
		if (m) {(m)->m_len=MHLEN;} } while (0)
#define _LPAMCLGETW(m,w) do { \
		_LPAMGETW(m,w); \
		if ((m)) { \
			MCLGET((m), (w)); \
			if (((m)->m_flags & M_EXT) == 0) { \
				LPAMFREEM((m)); \
				(m) = (struct mbuf *)NULL; \
			} else { \
				(m)->m_len=MCLBYTES; \
			} \
		} \
	} while (0)

#define LPAMLEN MHLEN


#define LPA_IFF_MULTICAST 0
#define LPA_IFF_DYNPROTO 0
#define M_CLUSTERSZ MCLBYTES

/* MBUF handling */
#define LPAMFREE(mx,n)       MFREE(mx,n)
#define LPAMFREEM(m)   m_freem(m)
#define LPAMGET(m)     _LPAMGETW (m, M_DONTWAIT)
#define LPAMGETWAIT(m) _LPAMGETW (m, M_WAIT)
#define LPAMCLGET(m)	_LPAMCLGETW (m, M_DONTWAIT)
#define LPAMCLGETWAIT(m)	_LPAMCLGETW (m, M_WAIT)

#define LPA_IFSTART(ifp)	lpa_ifstart ((ifp)->if_unit)

#include <atm/sys/atm_osf.h>
#include <atm/sys/atm.h>
#include <atm/sys/atm_adi.h>

//pwl 418+
//#if 0
//pwl 418+

#define	LPA_PIOR(_a)    READ_BUS_D32 ((io_handle_t)(_a))	/* 32 bit PIO read */
#define	LPA_PIOW(_a,_d) WRITE_BUS_D32 ((io_handle_t)(_a), (_d))	/* 32 bit PIO write */

//pwl 418+
//#endif
//pwl 418+

#endif	/* _IF_LPA_PLATFORM_H_ */
