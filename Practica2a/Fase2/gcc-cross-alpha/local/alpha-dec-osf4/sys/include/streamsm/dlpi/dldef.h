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
 * @(#)$RCSfile: dldef.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1998/12/01 22:31:45 $
 */

/*---------------------------------------------------------------------------*
 * Microsoft datalink driver
 * @(#)dldef.h	1.4	24 Jul 1992 
 *
 *	Structures for configurable datalink parameters.
 *---------------------------------------------------------------------------*/
struct dl_defaults_struct {
	unsigned int	upq_lowat;
	unsigned int	upq_hiwat;
	unsigned int	loq_lowat;
	unsigned int	loq_hiwat;
	unsigned int	maxdlcbs;
	unsigned int	maxmacs;
	unsigned int	retry_count;
	unsigned int	pkts2adapt;
#ifdef __osf__
	int		T1_value;
	int		T2_value;
        unsigned int    poll_freq;
#else
        long            T1_value;
        long            T2_value;
#endif
};

struct dlmac_info_struct {
	char	*mac_name;
#ifdef __osf__
	int	set_multicast_ioctl;
	int	del_multicast_ioctl;
	int	bind_sap;
#else
        long    set_multicast_ioctl;
        long    del_multicast_ioctl;
        long    bind_sap;
#endif
	char	destroys_udreq;
	char	adjust_maxsdu;
	char	srcdest_reversed;
	char	dlpi_mac;
#ifdef __osf__
	int	udind_from_interrupt;
#else
        long    udind_from_interrupt;
#endif
} ;

