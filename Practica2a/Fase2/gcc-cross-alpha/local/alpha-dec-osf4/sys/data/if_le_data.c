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
#ifndef lint
static char *rcsid = "@(#)$RCSfile: if_le_data.c,v $ $Revision: 1.1.9.2 $ (DEC) $Date: 1995/10/26 18:02:33 $";
#endif
*/

/*
 * Digital LeMAC NI
 */

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/syslog.h>
#include <vm/vm_kern.h>

#include <net/if.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/if_ether.h>
#include <net/ether_driver.h>
#include <io/common/devdriver.h>
#include <io/dec/netif/if_lereg.h>
#include <io/dec/uba/ubavar.h>
#include <io/dec/eisa/eisa.h>

/*
 * Ethernet multicast address
 *
 * LeMAC hashes a multicast address into a 512-bit array in page zero
 * of local memory.  If that bit is set then the packet is accepted
 * by the MAC.
 *
 * We count the number of times that we've been requested to add a given
 * address to the multicast table (muse), and the hash corresponding to
 * that address (offset).  If muse goes to zero then the node describing
 * the multicast address is removed.  The list is searched again and if
 * no other address hashes to the same place then that bit is turned off
 * in page zero.
 */

#define NMULTI 512
struct le_multi {
	struct le_multi *next;
	struct le_multi *prev;
	int offset;
	u_char	multi_char[6];
	short muse;
};
#define MULTISIZE sizeof(struct le_multi)

#define MINDATA 60

typedef struct le_tx_queue {
    int entry[64];
    int lastin;
    int firstout;
} le_tx_queue;

/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * is_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 */
#define	is_if	is_ac.ac_if		/* network-visible interface 	*/
#define	is_addr	is_ac.ac_enaddr		/* hardware Ethernet address 	*/

struct	le_softc {

        struct  ether_driver is_ed;     /* Ethernet driver common part    */
#define is_ac   is_ed.ess_ac            /* Ethernet common part */

#define ctrblk  is_ed.ess_ctrblk        /* Counter block		*/
#define ztime   is_ed.ess_ztime         /* Time counters last zeroed      */
	struct le_multi *le_mp;		/* list of multicast address */
	int callno;			/* lninit called */
	struct  mbuf *tmbuf[64];    /* Xmt mbuf chains (freed on xmt) */
	struct  mbuf *rmbuf[64];    /* Receive mbuf chains  */
	struct ledebug { 
		unsigned int trfull;	/* transmit side called lnwatch */
		int le_showmulti; 	/* debug: show multicast add/delete */
		int le_bablcnt;		/* transmitter timeout counter */
		int le_misscnt;		/* missed packet counter */
		int le_merrcnt;		/* memory error counter */
		int le_restarts;	/* number of times chip was restarted */
	} le_debug;
	vm_offset_t csrbase;		/* Controller CSR base address */
	vm_offset_t membase;		/* Controller MEM base address */
	vm_offset_t memsize;		/* Controller MEM size */
	int 	isa_irq;		/* IRQ for DEPCA */
	u_int	is_int_addr[6];		/* Saved station address - as u_ints */
	le_tx_queue *le_tx_queue;	/* private stash of transmitter buffers */
	ihandler_id_t   *hid;           /* ihander_id_t rtn from handler_add */
};

#define leshowmulti sc->le_debug.le_showmulti
#define lebablcnt sc->le_debug.le_bablcnt
#define lemisscnt sc->le_debug.le_misscnt
#define lemerrcnt sc->le_debug.le_merrcnt
#define lerestarts sc->le_debug.le_restarts

#ifdef BINARY

extern	struct	le_softc *le_softc[];
extern	struct	controller *leinfo[];

#else

#include "le.h"

/*
 * added multiple support to softc. Also, the ln_initb blocks will be
 * directly accessed in the local RAM buffers
 */
struct	le_softc  *le_softc[NLE];
struct	controller *leinfo[NLE];

#endif
