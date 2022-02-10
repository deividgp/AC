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
#pragma ident "@(#)$RCSfile: if_tu_data.c,v $ $Revision: 1.1.42.4 $ (DEC) $Date: 1997/07/31 19:37:54 $"
*/

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/vmmac.h>
#include <vm/vm_kern.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>  /* Needed for nonsymmetric drivers. us */

#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h> 
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/if_ether.h>
#include <net/ether_driver.h>
#include <io/common/devdriver.h>
#include <hal/cpuconf.h>
#include <io/dec/eisa/eisa.h>
#include <io/dec/pci/pci.h>
#include <io/dec/netif/if_tureg.h>
#include <io/dec/netif/lan_common.h>

/*
 * Each interface is referenced by a network interface structure,
 * is_if, which the routing code uses to locate the interface.
 */
#define	is_if	is_ac.ac_if		/* network-visible interface 	*/
#define	is_addr	is_ac.ac_enaddr		/* hardware Ethernet address 	*/

/*
 * Limits for the transmit and receive ring entries/descriptors.
 */
#define	TU_NRRING	16
#define	TU_NTRING	16

#define	TU_TRING_SIZE 	(TU_NTRING * sizeof(TUDESC))
#define	TU_RRING_SIZE 	(TU_NRRING * sizeof(TUDESC))

/*
 * Definitions for Multicast and setup frames
 */
#define TU_PMULTI	14		/* Max perfect multicast addresses */
#define TU_NMULTI	512		/* Max hashed multi-cast addresses */

#define TU_SETUP_SIZE 	192		/* Size of Setup Frame 		*/

struct tu_multi {
	u_char	tu_multi_char[6];
};

struct tu_setup {
	u_char  tu_setup_char[12];
};

struct tuflags {
	u_int aui_mode: 1;	/* Set if AUI-10Base5 selected 	*/
	u_int bnc_mode: 1;	/* Set if BNC-10Base2 selected 	*/
	u_int fast_speed: 1;	/* Set if speed = 100 Mb/sec 	*/
	u_int full_duplex: 1;	/* Set if Full-Duplex Enabled 	*/
	u_int ce_resolve: 1;	/* Set if Capture Effect enabled*/
	u_int auto_tr: 1;	/* Set if Tx Threshold in auto mode */
	u_int sf_mode: 1;	/* Set if Tx Store-Forward mode is on */
	u_int rx_or_tx: 1;	/* Set if RX/TX ok (for auto negotiation) */
	u_int timer_on: 1;	/* Set if soft timer (for auto SM) is running */
	u_int auto_enabled: 1;	/* Set if auto negotiation is enabled */
	u_int auto_capable: 1;	/* Set if auto negotiation capable */
	u_int overflow_bug: 1;	/* Set if chip has the receive overflow bug */
	u_int dc21040: 1;	/* Set if DECchip 21040 */
	u_int dc21041: 1;	/* Set if DECchip 21041 */
	u_int dc2104x: 1;	/* Set if DECchip 21040 or 21041 */
	u_int dc21140: 1;	/* Set if DECchip 21140 */
	u_int dc21142: 1;	/* Set if DECchip 21142 */
	u_int dc21143: 1;	/* Set if DECchip 21143 */
    	u_int fx_mode: 1;	/* Set if 100BaseFX */
};

/*
 * Struct for creating init values for SIA Registers for various ports
 * across all the chip variants (21040, 21041, 21142, etc.)
 */
struct tu_sia_init_data {
	u_short csr13[5];
	u_short csr14[5];
	u_short csr15[5];
};

struct	tu_softc {
	struct  ether_driver is_ed;	/* Ethernet driver common part 	*/
#define is_ac   is_ed.ess_ac    	/* Ethernet common part         */
#define ctrblk  is_ed.ess_ctrblk	/* Counter block	        */
#define ztime   is_ed.ess_ztime         /* Time counters last zeroed    */
	TUDESC	*rring;			/* Receive ring desc. addresses */
	TUDESC	*tring;			/* Transmit ring desc. addresses*/
	u_long	rring_phys;		/* Receive ring desc. phys addr */
	u_long	tring_phys;		/* Transmit ring desc. phys addr*/
	sglist_t tsglp[TU_NTRING];	/* Transmit dma mapping sglist ptrs */
	sglist_t rsglp[TU_NRRING];	/* Receive dma mapping sglist ptrs */
	struct mbuf *smbuf[TU_NTRING];	/* Saved transmit mbuf chains	*/ 
	struct mbuf *rmbuf[TU_NRRING];	/* Receive mbufs 		*/
	struct tu_setup *setup_bufr;	/* Buffer for setup-frame	*/
	struct controller *tu_ctlr;	/* Controller reference		*/
	int	ntinuse;		/* Transmit descriptors in use 	*/
	int	ntpendg;		/* Transmits pending in the ring*/
	int	itindex;		/* Next input transmit index	*/
	int	otindex;		/* Next output Transmit index	*/
	int	rindex;			/* Next in/out Receive index	*/
	int	tu_sysid_type;		/* TULIP SysId Type (EISA/PCI)	*/
	u_int	tu_revision;		/* TULIP Revision number  	*/
	u_int	tu_vendor_id;		/* TULIP Vendor-ID (DEC)	*/
	u_int	tu_device_id;		/* TULIP Device-ID (Tulip!)	*/
	u_long  tu_csr_base;		/* TULIP CSR base value		*/
	u_long	tu_csr[16];		/* TULIP CSRs 0..15 io-handles	*/
	u_long	tu_cfid;		/* TULIP Conf Id Reg io-handle	*/
	u_long	tu_cfcs;		/* TULIP Conf Cmd/Stat io-handle*/
	u_long	tu_cfrv;		/* TULIP Conf Rev Reg io-handle	*/
	u_long	tu_cflt;		/* TULIP Conf Latency io-handle	*/
	u_long	tu_cbio;		/* TULIP Conf BaseIO io-handle	*/
	u_long	tu_cfda;		/* TULIP Conf DrvArea io-handle	*/
	struct tuflags tu_flags;	/* Flags galore: see tuflags def*/
	u_int	tu_tr;			/* Tx Threshold value selected	*/
	u_int	actual_ccount;		/* Actual collision count	*/
	u_int	ec_reque_count;		/* # of Exessive collisions reque'd */
	char 	tu_port_selection[80];	/* Set by media sensing routine */
	u_char	tu_rom_addr[6];		/* Enet ROM Address saved here	*/
	simple_lock_data_t lk_tu_softc; /* SMP lock for tu_softc        */
	struct	tu_multi is_multi[TU_NMULTI]; /* Multicast address list	*/
	u_char	is_muse[TU_NMULTI];	/* Multicast address reference count */
	u_int	is_nmulti;		/* Number of active Multicasts */
	ihandler_id_t	*hid;		/* ihander_id_t rtn from handler_add */
	u_char	mii_phyaddr;		/* Address (0-31) of PHY device */
	int	tu_auto_state;		/* Current state of Auto-Negotiation */
	int	tu_auto_ticks;		/* Time in current state (tick=500ms)*/
	u_short tu_auto_ability;	/* Our ability that we advertise */
	u_char tu_srom_data[128];	/* Copy of SROM: 21041, 2114x */
	u_char *tu_srom_leaf_info;	/* Pointer to leaf0 info in SROM */
	struct tu_sia_init_data *tu_sia_init;
        int	tu_setup_frame_reset;	/* True if reset called from setup_f */
};

#ifdef BINARY
extern	struct	tu_softc tu_softc[];
extern	struct	controller *tuinfo[];
#else

#include "tu.h"

struct	tu_softc  tu_softc[NTU];
struct	controller *tuinfo[NTU];
#endif
