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
 * @(#)$RCSfile: lan_common.h,v $ $Revision: 1.1.12.3 $ (DEC) $Date: 1996/10/03 13:44:21 $
 */

#ifndef _IO_DEC_NETIF_LAN_COMMON_
#define _IO_DEC_NETIF_LAN_COMMON_

#include <kern/lock.h>

#ifdef _KERNEL
#include <net/if.h>
#endif

/*
 * Definitions/macros that are common to all LAN interface drivers.
 */

/*
 * M E D I A    D E F I N I T I O N S 
 * ==================================
 */

/*
 * Medium structure to put in driver's softc structure.
 */
struct lan_media {
    unsigned long lan_media_mode; /* see media_types enum for values */
    unsigned long lan_media_state;/* valid if media_mode = autosense */
    unsigned long lan_media;	  /* valid if media_mode = determined */
};

/*
 * Media definitions.  For drivers that support them.  Most good hardware 
 * determines media automagically, but there are a few implementations
 * that do not figure it out.
 */
enum media_types {
      LAN_MEDIA_UTP=1,			/* Unshielded Twisted Pair */
      LAN_MEDIA_BNC,			/* Thinwire */
      LAN_MEDIA_STP,			/* Shielded Twisted Pair */
      LAN_MEDIA_FIBER,			/* Any Fiber based media */
      LAN_MEDIA_AUI,			/* Attachment Unit Interface */
      LAN_MEDIA_4PAIR,			/* Four Pair */
      LAN_MEDIA_MAX
};

/*
 * Media modes.  These are the same as media_types except for the autosense
 * case.
 */
enum media_modes {
      LAN_MODE_AUTOSENSE=0xFF
};

/*
 * Autosense mode definitions.
 */
enum autosense_types {
      LAN_AUTOSENSE_ENABLE=1,
      LAN_AUTOSENSE_DISABLE=2
};

/*
 * Full duplex types.
 */
enum fdx_types {
      LAN_FDX_ENABLE=1,
      LAN_FDX_DISABLE=2
};

/* 
 * Media STATE definitions.  This is used when media mode is autosensing.
 */
#define LAN_MEDIA_STATE_SENSING		1 	/* Currently auto sensing */
#define LAN_MEDIA_STATE_DETERMINED 	0 	/* Media is determined */

/*
 * M U L T I C A S T    S U P P O R T
 * ==================================
 * 
 * Important NOTE:  The broadcast address should always be enabled 
 * on LAN Device Drivers.   This will not be a requirement if IP changes
 * to actually enable the broadcast address by itself.
 */

/*
 * The number of multicasts to support.  This is a ballpark figure 
 * with, at this time, no demand for this number of multicasts.
 */
#define LAN_NMULTI 512

#ifdef _KERNEL

/*
 * The multicast tracking structure.  This is included in a LAN driver's
 * softc structure if they wish to use the common multicast support.
 */
struct lan_multi {
    struct {			/* The table of multicast addresses */
	unsigned char maddr[6];
	unsigned short muse;
    } lan_mtable[LAN_NMULTI];
    unsigned int lan_nmulti;	/* The number of active entries */
    unsigned int lan_index;	/* Next available index */
};

/*
 * Common routines for manipulating the multicast table.
 */
extern void lan_zer_multi(struct lan_multi *);
extern int  lan_add_multi(struct lan_multi *, unsigned char *);
extern int  lan_del_multi(struct lan_multi *, unsigned char *);

#endif /* _KERNEL */

/*
 * Return Status for common routines and filtering macros.
 */
enum lan_multi_status {
      LAN_MULTI_FAILED,
      LAN_MULTI_FOUND,
      LAN_MULTI_NOT_FOUND,
      LAN_MULTI_CHANGED,
      LAN_MULTI_NOT_CHANGED
};

#ifdef _KERNEL

/*
 * LAN_FIND_MULTI
 * 	For devices which don't perform perfect filtering, the following
 * 	macro will check to see if a given multicast is enabled on the given 
 * 	softc.  This macro is also used by the common routines.
 * 
 * Arguments:
 * 	lm_p	lan multicast table pointer
 * 	mc_p	multicast to check
 * 	ind_v	index variable
 * 	stat_v	status variable
 * 
 * Return Values:
 * 	stat_v	LAN_MULTI_FOUND if found, otherwise LAN_MULTI_NOT_FOUND
 * 	ind_v	table index of matching multicast table
 */
#define LAN_FIND_MULTI(lm_p, mc_p, ind_v, stat_v) \
	for ((ind_v) = 0; (ind_v)<(lm_p)->lan_index; (ind_v)++) \
	   if (bcmp((lm_p)->lan_mtable[(ind_v)].maddr, (mc_p), 6) == 0) \
	      break; \
	if ((ind_v) == (lm_p)->lan_index) \
	   (stat_v) = LAN_MULTI_NOT_FOUND; \
	else \
	   (stat_v) = LAN_MULTI_FOUND

/*
 * LAN_GET_MULTI
 * 	Returns a pointer to the next enabled multicast address.  To use
 * 	this to go through the multicast list, you'd do something like the
 * 	following
 * 
 * 	int i, j;
 * 	unsigned char *maddr;
 * 
 * 	j = 0;
 * 	for (i=0; i<lmt->lan_nmulti; i++) {
 *         LAN_GET_MULTI(lmt, maddr, j);
 *         if (maddr != NULL)    ---   maddr should never be null in this case
 *           printf("Multicast %s enabled\n", ether_sprintf(maddr));
 *      }
 * 
 * Arguments:
 * 	lmt	pointer to the lan multicast table.
 * 	mc_p	pointer to hold the multicast address pointer
 * 	ind_v	index value 
 *
 * Return Values:
 * 
 */
#define LAN_GET_MULTI(lm_p, mc_p, ind_v) \
	for (; (ind_v) < (lm_p)->lan_index; (ind_v)++) \
	  if ((lm_p)->lan_mtable[(ind_v)].muse != 0) \
	    break; \
	if ((ind_v) >= (lm_p)->lan_index) \
	   (mc_p) = NULL; \
	else { \
	   (mc_p) = (lm_p)->lan_mtable[(ind_v)].maddr; \
	   (ind_v)++; \
	}

/*
 * C O U N T E R     S U P P O R T
 * ===============================
 */

/*
 * ifnet and ctrblk counter manipulation.   The ctrblk counters are only 32 
 * bit counters so we have to watch for wrap.   All take ifp & softc pointer 
 * and size as input.
 * 
 * These macros increment the packet (block) count, and then adjust the
 * byte count.
 */
#define ADD_XMIT_PACKET(if_p, sc_p, siz_v) \
	(if_p)->if_opackets++; \
	if ((sc_p)->ctrblk.est_bloksent != 0xffffffff) \
	   (sc_p)->ctrblk.est_bloksent++; \
	if (((sc_p)->ctrblk.est_bytesent + (siz_v)) >  \
	    ((sc_p)->ctrblk.est_bytesent)) \
	   (sc_p)->ctrblk.est_bytesent += (siz_v); \
	else \
	   (sc_p)->ctrblk.est_bytesent = 0xffffffff
#define ADD_XMIT_MPACKET(if_p, sc_p, siz_v) \
	if ((sc_p)->ctrblk.est_mbloksent != 0xffffffff) \
	   (sc_p)->ctrblk.est_mbloksent++; \
	if (((sc_p)->ctrblk.est_mbytesent + (siz_v)) >  \
	    ((sc_p)->ctrblk.est_mbytesent)) \
	   (sc_p)->ctrblk.est_mbytesent += (siz_v); \
	else \
	   (sc_p)->ctrblk.est_mbytesent = 0xffffffff
#define ADD_RECV_PACKET(if_p, sc_p, siz_v) \
	(if_p)->if_ipackets++;\
	if ((sc_p)->ctrblk.est_blokrcvd != 0xffffffff) \
	   (sc_p)->ctrblk.est_blokrcvd++; \
	if (((sc_p)->ctrblk.est_bytercvd + (siz_v)) >  \
	    ((sc_p)->ctrblk.est_bytercvd)) \
	   (sc_p)->ctrblk.est_bytercvd += (siz_v); \
	else \
	   (sc_p)->ctrblk.est_bytercvd = 0xffffffff
#define ADD_RECV_MPACKET(if_p, sc_p, siz_v) \
	if ((sc_p)->ctrblk.est_mblokrcvd != 0xffffffff) \
	   (sc_p)->ctrblk.est_mblokrcvd++; \
	if (((sc_p)->ctrblk.est_mbytercvd + (siz_v)) >  \
	    ((sc_p)->ctrblk.est_mbytercvd)) \
	   (sc_p)->ctrblk.est_mbytercvd += (siz_v); \
	else \
	   (sc_p)->ctrblk.est_mbytercvd = 0xffffffff

/*
 * E X T E R N S   /    P R O T O T Y P E S
 * ========================================
 */

extern char *lan_media_strings_10[LAN_MEDIA_MAX];
extern char *lan_media_strings[LAN_MEDIA_MAX];
extern int lan_common_version;

#endif /* _KERNEL */

#endif /* ifndef _IO_DEC_NETIF_LAN_COMMON_ */
