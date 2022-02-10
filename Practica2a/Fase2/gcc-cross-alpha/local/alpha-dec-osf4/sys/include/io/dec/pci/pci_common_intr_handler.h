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
 * @(#)$RCSfile: pci_common_intr_handler.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1998/04/23 12:47:49 $
 */

/*
 * External functions used for interrupt handling
 */

extern ihandler_id_t	pci_intline_handler_add(int slot, 
					       u_int intr_mask, 
					       struct handler_intr_info *intr_infop, 
					       struct bus *busp);

extern int	pci_intline_handler_del(shared_intr_info_t *sip, 
				       struct bus *busp);

extern int	pci_intline_handler_enable(shared_intr_info_t *sip, 
					  struct bus *busp);

extern int	pci_intline_handler_disable(shared_intr_info_t *sip, 
					   struct bus *busp);

extern int 	pci_intline_option_enable(int intr_num);

extern int 	pci_intline_option_disable(int intr_num);


extern ihandler_id_t	pic_handler_add(int (*function)(), 
					int isa_irq_level, 
					caddr_t param,
					struct bus *busp);

extern int	pic_handler_del(shared_intr_info_t *sip);

extern int	pic_handler_enable(shared_intr_info_t *sip);

extern int	pic_handler_disable(shared_intr_info_t *sip);

extern int	pic_option_enable(shared_intr_info_t *sip);

extern int	pic_option_disable(shared_intr_info_t *sip);

extern int	pic_this_is_an_isa_handle(ihandler_id_t int_handler);
