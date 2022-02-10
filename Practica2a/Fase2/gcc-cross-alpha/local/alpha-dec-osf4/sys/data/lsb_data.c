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
#pragma ident "@(#)$RCSfile: lsb_data.c,v $ $Revision: 1.2.21.2 $ (DEC) $Date: 1997/06/27 17:26:41 $"

#include <io/dec/lsb/tlsbreg.h>

/*
 * Modification History: ./dec/data/lsb_data.c
 *
 * Sep-91	jac: created this file for lsb support of Laser/Ruby
 *
 */

#ifdef ALPHARUBY
int lsb_iopint();
int lsb_memint();
int lsb_mplepint();
#else
#define lsb_iopint lsbnotconf
#define lsb_memint lsbnotconf
#define lsb_mplepint lsbnotconf
#endif /* ALPHARUBY */

#include "eisa.h"
#if NEISA == 0
unsigned long isp_base;
unsigned long eisa_sw;
int eisa_expansion_slots;
int isp_dma_init(){return 0;}
int isp_dma_config(){return 0;}
int isp_dma_alloc(){return 0;}
int isp_dma_dealloc(){return 0;}
int isp_dma_load(){return 0;}
int isp_dma_unload(){return 0;}
int eisa_config_cont(){return 0;}
int gpc_cons_init(){return 0;}
#endif

#include "fbus.h"
#if NFBUS == 0
fbus_mbox_cmd(){ return 0; }
flagconfl1(){ return 1; }
fbusconfl1(){ return 1; }
fbusconfl2(){ return 1; }
#endif /* NFBUS */

#include "xmi.h"
#if NXMI == 0
lambconfl1(){ return 1; }
lambconfl2(){ return 1; }
xmiconfl1(){ return 1; }
xmiconfl2(){ return 1; }
log_lamberror(){ return 1;}
log_tlamberror(){ return 1;}
tlamberror(){ return 1; }
xmidev_vec(){ return 1;}
#endif /* NXMI */

#include "pci.h"
#if NPCI == 0
pciaconfl1(){ return 1; }
tlaser_pci_clr_err(){ return 1;}
fill_pcia_subp(){ return 1; }
elr_get_pcislot_count(int bus_num) { return 0; }
elr_fill_pci_bus_snap(char *errlog_ptr, struct bus *busp) { return 0; }
unsigned long pcia_ctl_li;
#ifdef DEC21000
long read_io_port() { return 1; }
void write_io_port() { return; }
#endif
#endif /* NPCI */

#include "presto.h"
#if NPRESTO == 0
unsigned long prflags;
#endif /* NPRESTO */

int
nolsbreset()
{
return(0);
}

int
lsb_iopint()
{
return(0);
}

int (*lsb_iopprobes[])() = {  lsb_iopint, 0};
int (*lsb_memprobes[])() = {  lsb_memint, 0};
int (*lsb_lepprobes[])() = {  lsb_mplepint, 0};

struct lsbsw lsbsw [] =
{
  { LSB_IOP,      "iop",          lsb_iopprobes,     nolsbreset,
          LSBF_NOCONF},
  { TLSB_ITIOP,   "itiop",        lsb_iopprobes,     nolsbreset,
          LSBF_NOCONF},
  { LSB_MEM,      "mem",          lsb_memprobes ,     nolsbreset,
          LSBF_NOCONF},
  { TLSB_MEM,      "tmem",        lsb_memprobes ,     nolsbreset,
          LSBF_NOCONF},
  { LSB_BBMEM,      "ms7bb",          lsb_memprobes ,     nolsbreset,
          LSBF_NOCONF},
  { LSB_LEP,      "lep",          lsb_lepprobes ,     nolsbreset,
          LSBF_NOCONF},
  { LSB_PROCESSOR,      "lep",          lsb_lepprobes ,     nolsbreset,
          LSBF_NOCONF},
  { 0 }
};

int nlsbtypes = sizeof (lsbsw) / sizeof (lsbsw[0]);

