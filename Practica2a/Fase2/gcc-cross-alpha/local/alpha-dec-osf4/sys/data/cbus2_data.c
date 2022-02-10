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
#pragma ident "@(#)$RCSfile: cbus2_data.c,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 1995/06/22 19:18:40 $"

#include <sys/types.h>
#include <machine/pmap.h>
#include <machine/machparam.h>

/*
 * Include files for structure definitions
 */

#include <hal/kn450.h>
#include <hal/kn470.h>
#include <hal/cbus2_pci.h>

PCI_csrp_t	cbus2_pci_PCI_regs[2] = {
  	(PCI_csrp_t)PCI0_BASE,
	(PCI_csrp_t)PCI1_BASE
	};

sable_cpu_csrp_t	kn450_Cpu_regs[CBUS2_MAX_CPU_SLOTS] = {
        (sable_cpu_csrp_t)CPU0_BASE, 
        (sable_cpu_csrp_t)CPU1_BASE,
        (sable_cpu_csrp_t)CPU2_BASE,
        (sable_cpu_csrp_t)CPU3_BASE
        };

gamma_cpu_csrp_t	kn470_Cpu_regs[CBUS2_MAX_CPU_SLOTS] = {
        (gamma_cpu_csrp_t)CPU0_BASE, 
        (gamma_cpu_csrp_t)CPU1_BASE,
        (gamma_cpu_csrp_t)CPU2_BASE,
        (gamma_cpu_csrp_t)CPU3_BASE
        };

mem_csrp_t      cbus2_pci_Mem_regs[CBUS2_MEM_SLOTS] = {
        (mem_csrp_t)MEM0_BASE, 
        (mem_csrp_t)MEM1_BASE, 
        (mem_csrp_t)MEM2_BASE, 
        (mem_csrp_t)MEM3_BASE
        };

u_short         Cbus2_cpu_modules_alive;
u_short         Cbus2_mem_modules_alive;
