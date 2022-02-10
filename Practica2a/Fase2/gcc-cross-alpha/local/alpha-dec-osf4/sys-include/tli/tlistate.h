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
 *	@(#)$RCSfile: tlistate.h,v $ $Revision: 4.2.23.2 $ (DEC) $Date: 1998/10/19 15:02:13 $
 */ 

/** Copyright (c) 1990  Mentat Inc.
 ** tlistate.h 1.1, last change 4/14/90
 **/

#ifndef	_TLISTATE_
#define	_TLISTATE_
#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

struct tli_st {
	struct	tli_st	*tlis_next;
	int	tlis_fd;
	int	tlis_state;		/* state */
	int	tlis_servtype;		/* server type */
	int	tlis_flags;		/* flag bits definition below */
	long    tlis_etsdu_size;	/* Transport service data unit size */
	long    tlis_tsdu_size;		/* Transport service data unit size */
	long    tlis_tidu_size;		/* Transport individual data unit size*/
	char	*tlis_proto_buf;
	void	*tlis_lock;
	int	tlis_ocnt;		/* outstanding connections */
	int	tlis_getmsg_ret;	/* ret. value from saved proto's getmsg */
};

/* Flags! */
#define	TLIS_DATA_STOPPED	0x0001
#define	TLIS_EXDATA_STOPPED	0x0002
#define TLIS_SAVED_PROTO        0x0004
#define TLIS_MORE_RUDATA	0x0008
#define TLIS_MORE_DATA		0x0010
#define TLIS_SPEC1170		0x0020
#define TLIS_LISTENDONE		0x0040

#define IOSTATE_VERIFY  	0x0001
#define IOSTATE_SYNC		0x0002
#define IOSTATE_KSYNC		0x0003
#define IOSTATE_FREE		0x0004


extern  struct tli_st * iostate_sw __( (int, int) );

#ifdef XTI_SPEC1170
#define ISSPEC1170(tli) ((tli)->tlis_flags & TLIS_SPEC1170 )
#endif


#ifdef __cplusplus
}
#endif
#endif	/*_TLISTATE_*/
