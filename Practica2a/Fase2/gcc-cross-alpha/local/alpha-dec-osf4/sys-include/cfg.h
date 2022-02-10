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
 * @(#)$RCSfile: cfg.h,v $ $Revision: 1.1.6.3 $ (DEC) $Date: 1995/10/17 14:02:16 $
 */

#ifndef _CFG_H_
#define _CFG_H_

#include <sys/sysconfig.h>
#include <sys/param.h>
#include <userpw.h>
#include <nlist.h>

/*
 * Connection initialization packet.
 */
typedef struct {
    int			proto_version;
    char		username[PW_NAMELEN];
    unsigned int        flags;
    char		reserved[296-PW_NAMELEN];
} cfg_init_pack_t;

/*
 * Request header packet.
 */
typedef struct {
    char		subsys[CFG_SUBSYS_NAME_SZ];
    int			operation;
    cfg_status_t	result;
    long		data_size;
} cfg_pack_t;

/*
 * Connection handle.
 */
typedef struct {
    char		host[MAXHOSTNAMELEN + 1];
    int			in_fd;
    int			out_fd;
    int                 pid;
    char		reserved[40];
} cfg_handle_t;

/*
 * Protocol versions.
 */
#define CFG_PROTO_V1		1
#define CFG_PROTO_V2		2     /* add security check and debug option */
#define CFG_PROTO_VERSION	CFG_PROTO_V2

/*
 * Bit flags for the flags argument in cfg_connect().
 */
#define    CFG_FLAG_NOFLAGS        0x0
#define    CFG_FLAG_VERBOSE        0x1

/*
 * Functions in libcfg.a.
 */

cfg_status_t cfg_connect( caddr_t  host, cfg_handle_t  *handle, uint  flags );

cfg_status_t cfg_disconnect( cfg_handle_t  *handle );

cfg_status_t cfg_subsys_config( cfg_handle_t  *handle, caddr_t  subsys );

cfg_status_t cfg_subsys_unconfig( cfg_handle_t  *handle, caddr_t  subsys );

cfg_status_t cfg_subsys_reconfig( cfg_handle_t  *handle, caddr_t  subsys,
                                  cfg_attr_t  *attributes, int  nattributes );

cfg_status_t cfg_subsys_query( cfg_handle_t  *handle, caddr_t  subsys,
                               cfg_attr_t  *attributes, int  nattributes );

cfg_status_t cfg_subsys_query_all( cfg_handle_t  *handle, caddr_t  subsys,
                                   cfg_attr_t  **attributes, int  *nattributes );

cfg_status_t cfg_subsys_op( cfg_handle_t  *handle, caddr_t  subsys, cfg_op_t  op,
                            caddr_t  indata,  ulong  indata_size, 
                            caddr_t  outdata, ulong  outdata_size );

cfg_status_t cfg_subsys_state( cfg_handle_t  *handle, caddr_t  subsys, uint  *state );

cfg_status_t cfg_subsys_list( cfg_handle_t  *handle, caddr_t  **subsys,
                              uint  **state, int  *nsubsys );

cfg_status_t cfg_subsys_defaults( cfg_handle_t  *handle, caddr_t  subsys,
                                  cfg_attr_t  *attributes, int  nattributes );

cfg_status_t cfg_subsys_defaults_all( cfg_handle_t  *handle, caddr_t  subsys,
                                      cfg_attr_t  **attributes, int  *nattributes );

#endif /* _CFG_H_ */
