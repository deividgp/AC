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
 * @(#)$RCSfile: vba_generic.h,v $ $Revision: 1.1.11.2 $ (DEC) $Date: 1998/10/30 18:44:11 $
 */
/*
 * HISTORY
 *
 *	March XX, 1994	Debby Haeck
 *		rename file (used to be gen_bus_adapt.h) and 
 *		submit to OSF base system (V3.0) as a truly "generic"
 *		VME interface.
 */

#ifndef _VBA_BUS_ADAPT_H
#define _VBA_BUS_ADAPT_H

#include <sys/types.h>
#include <io/dec/vme/vbareg.h>

/*
 * Generic bus adapter structure.
 * note:  This is an opaque data structure; do not depend on it remaining the
 *        same!
 */

#define	MAX_SHOEBOX	32

#define VBA_EMBEDDED_VME      0
#define VBA_NO_EMBEDDED_VME   1
#define VBA_EMBEDDED_VME_MSK  1

#define VBA_AUTO_VEC          0
#define VBA_NO_AUTO_VEC       2
#define VBA_AUTO_MSK          2

struct	vba_bus_adapt {
        lock_data_t     shoebox_lk;        /* complex shoebox resource lock  */
        lock_data_t     adapt_c_lk;        /* complex adapter resource lock  */
        decl_simple_lock_data(,adapt_s_lk) /* simple adapter resource lock   */
	caddr_t         binfo;
	struct  bus     *bus;		   /* parent of vba_bus_adapt struct */
	unsigned int    bus_timeout;	   /* DELAY timeout value for probe  */
	int	        adptnum;	   /* internal number of adapter per */
                                           /* bus type                       */
	io_handle_t     ioh;		   /* csr iohandle_t of bus adapter  */
	void           *intr_dispatch_tbl; /* pseudo scb interrupt vectors   */
	caddr_t	        adapt_regs;        /* ptr to adapter registers	     */
	caddr_t	        adapt_vars;	   /* ptr to adapter variables       */
	caddr_t	        bus_vars;	   /* ptr to bus specific variables  */
	short	        bus_want;	   /* used to wait on bus resources  */

	                                     /* adapter specific interfaces  */
	int	        (*confl2)();	     /* bus confl2 interface         */
	io_handle_t     (*map_csr)();	     /* map csr (for pio)            */
	void	        (*unmap_csr)();	     /* unmap csr (for pio)          */
	vme_addr_t      (*get_bus_addr)();   /* get VMEbus address           */
	vme_atype_t     (*get_bus_addr_am)();/* get VMEbus address modifier  */
	int	        (*errors)();	     /* Error routine for adapter    */
	unsigned int	(*post_irq)();	     /* post VMEbus interupt request */
	boolean_t	(*clear_irq)();	     /* clear VMEbus interupt request*/
	int	        *irq_to_spl_tblptr;  /* vme irq to spl table pointer */

	unsigned int	shoebox_want;        /* used by vba_set_dma_addr and */
	unsigned long	shoebox[MAX_SHOEBOX];/* vba_get_dma_addr interfaces  */
					     /* to pass and retrieve bus data*/
	void            *vhp_private[8];
	void            *vhp_reserved[8];
};

#define vbahd private[4]   /* entry of the VME switch table in bus structure */

#define VBA_MAX_DISPATCH_ENTRIES 6

typedef	struct	Vba_dispatch {
	int	(*confl1)();
	int	bus_type;
} Vba_dispatch;

typedef struct Box {
	vme_addr_t      addr;
	unsigned int    flag;
} Box;

extern	struct vba_bus_adapt	*vhp_ptr[];

/*********************************************************/
/* VBA option data structure which contains information  */
/* on VMEbus options that may be installed on a system.	 */
/* The options are listed in /etc/sysconfigtab database. */
/*********************************************************/

#define MANUFACT_NAMELEN    31
#define PRODUCT_NAMELEN	    31
#define DRIVER_NAMELEN	    15

struct vba_option {
    u_char 	manufact_name[MANUFACT_NAMELEN+1]; /* Manufacturer name      */
    u_char	product_name[PRODUCT_NAMELEN+1];   /* Product name           */
    u_int	bus_instance;		           /* Bus instance number    */
    u_char	driver_name[DRIVER_NAMELEN+1];     /* Driver name            */
    u_int	drv_instance;		           /* Driver instance number */
    u_long      drv_addr;                          /* Driver CSR 1           */
    u_long      drv_addr2;                         /* Driver CSR 2           */
    u_int       drv_vector;                        /* Driver interrupt vector*/
    u_int       drv_bus_priority;                  /* Driver IRQ Level       */
    char	type;			           /* Driver type, C = ctlr, */
                                                   /* A = Adapter, D = Device*/
    int		(*adpt_config)();	           /* Adapter config routine */
};

/****************************************************************************
 *  The following structure is used by the platform to fill in
 *  adapter/platform specific interrupt "handler_xxx" routines and
 *  other pertinent information for VME
 ***************************************************************************/

struct vp_vme_sw {
  int              (*handler_add)();
  int              (*handler_del)();
  int              (*handler_enable)();
  int              (*handler_disable)();
  int              (*read_intrsel)();
  unsigned long    (*intr_mask_enabl)();
  unsigned long    (*intr_mask_dsabl)();
  int              irq_to_spl_tbl[8];
  unsigned int     adapt_blk_spl;
  unsigned int     adapt_mblt_access;
  unsigned long    support;
  /*
   * The vp_vme_sw structure and above entries were originally located in
   * the io/dec/vme/ebv10_vme.h file. The structure was used by the embedded
   * VIP/VIC64 VME platforms. The structure will now be used between the
   * VIP/VIC64 and Tundra's Universe II embedded VME platforms. Additonal
   * entries to this structure appear below.
   */
  int              (*vme_reset_check)();
  int              (*flush_sg_tlb)();
  unsigned long    (*platform_rsv1)();
  void             *vp_sw_private[8];
  void             *vp_sw_reserved[8];
};


#endif /* _VBA_BUS_ADAPT_H */



