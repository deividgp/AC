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
 *	@(#)$RCSfile: xtiso_config.h,v $ $Revision: 4.2.11.4 $ (DEC) $Date: 1995/11/15 19:31:01 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _XTISO_CONFIG_H
#define _XTISO_CONFIG_H
/*
 * Configuration structures for XTI-over-SOcket driver.
 */

/*
 * Protocol Information Structure
 */
struct xtiproto { 
	int	 xp_dom;		/* socket domain		*/
	int	 xp_type;		/* socket type  		*/
	int	 xp_proto;		/* socket protocol		*/
	int	 xp_servtype;		/* service type supported	*/
	long	 xp_tsdulen;		/* max TSDU size		*/
	long	 xp_etsdulen;		/* max ETSDU size		*/
	long	 xp_disconlen;		/* max disconnection data size	*/
	long	 xp_connectlen;		/* max connection data size 	*/
	long	 xp_addrlen;		/* max protocol addr size	*/
	long	 xp_optlen;		/* max protocol option size 	*/
	long	 xp_tidulen;		/* max trans protocol i/f size  */
        struct xtiso_options	 
		 *xp_options;		/* Options block so{get,set}opt supp */
	int	(*xti_optmgmt_atom)();	/* Per protocol handler for      */
					/* a single option item          */
	int	 xp_flags;		/* See below */
};

#define XTI_NO_OPTS	0		/* There are no setopts/getopts */
#define XTI_NS		-2L		/* Not supported */

/*
 * Values of xp_flags
 * (Bit mapped)
 *
 */
#define XTI_NOFLAGS		0x0	/* No flags */
#define XTI_BEHAVIOR1170	0x1	/* SPEC1170 and beyond implementation */
#define XTI_SNDZERO		0x2	/* implies that SENDZERO is supported */
#define XTI_URGENT		0x4	/* URGENT DATA (like tcp urgent data) */
#define XTI_SAMEADDR		0x8	/* address must be same or unbound
					   for accept of fd and resfd         */


/* Useful macros */
#define ProtoSPEC1170(xp)	(xp->xp_flags & XTI_BEHAVIOR1170)
#define IsSPEC1170(xtip)	(xtip->xti_proto.xp_flags & XTI_BEHAVIOR1170)
#define IsURGENT(xtip)		(xtip->xti_proto.xp_flags & XTI_URGENT)
#define SAMEADDR(xtip)		(xtip->xti_proto.xp_flags & XTI_SAMEADDR)

/*
 * Following options mapping block is required because transport level
 * options may have different option names (& numbers) supporting the
 * functionality needed by XTI, ie. Names/numbers used by OSI transport
 * level options could be completely different from other hypothetical
 * transport implementation
 *
 */
struct xtiso_options {
	int	 xo_level;	/* protocol level for so{get,set}opt         */
        int	 xo_getinfo;	/* name for t_getinfo supp                   */
        int	 xo_mgmtneg;	/* name for t_optmgmt/T_NEGOTIATE            */
        int	 xo_mgmtchk;	/* name for t_optmgmt/T_CHECK                */
        int	 xo_mgmtdef;	/* name for t_optmgmt/T_DEFAULT              */
        int	 xo_condata;	/* name for passing connect data             */
        int	 xo_conopts;	/* name for setting connect options          */
        int	 xo_discondata;	/* name for getting disconnect data          */
        int	 xo_disconreas;	/* name for getting disconnect reason        */
        int	 xo_accept;	/* name for accepting deferred incoming conn */
};

#define xp_opt_level		xp_options->xo_level
#define xp_getinfo		xp_options->xo_getinfo
#define xp_mgmtneg		xp_options->xo_mgmtneg
#define xp_mgmtchk		xp_options->xo_mgmtchk
#define xp_mgmtdef		xp_options->xo_mgmtdef
#define xp_condata		xp_options->xo_condata
#define xp_conopts		xp_options->xo_conopts
#define xp_discondata		xp_options->xo_discondata
#define xp_disconreas		xp_options->xo_disconreas
#define xp_accept		xp_options->xo_accept

#define OSF_XTISO_CONFIG_10	0x01091790

/*
 * Input data structure from configuration manager via kmodcall()
 */
typedef struct {
	str_config_t		sc;		/* standard stream config */
	struct xtiproto         proto;		/* xtiso protocol info    */
} xtiso_inadm_t;

/*
 * Output data structure from configuration manager via kmodcall()
 */
typedef struct {
	str_config_t		sc;
} xtiso_outadm_t;


#endif	/* _XTISO_CONFIG_H */
