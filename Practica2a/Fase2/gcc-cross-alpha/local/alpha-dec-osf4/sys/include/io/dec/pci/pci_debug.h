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
 * @(#)$RCSfile: pci_debug.h,v $ $Revision: 1.1.15.5 $ (DEC) $Date: 1997/03/31 16:52:40 $
 */
#ifndef __PCI_DEBUG_H__
#define __PCI_DEBUG_H__

/************************************************************************/
/*									*/
/* pci_debug.h								*/
/*									*/
/* h file to enable and define debugging printf statements for 		*/
/* PCI bus configuration.						*/
/*									*/
/************************************************************************/

extern	u_int	_pci_developer_debug;

/* To remove/add all debug printfs */
#define PCIDEBUG

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * _pci_developer_debug.
 */


/* The following defines are used for the flag bits in the printf macro. */

#define	PCID_INOUT	0x00000001	/* routine entry and exit 	*/

/* Configuration Header info 						*/
#define PCID_CONFIG	0x00000004	/* PCI config phase flow 	*/
#define PCID_CNFG_RD	0x00000008	/* Config reads			*/
#define PCID_CNFG_SLOT	0x00000010	/* Cnfg per-slot i.d.		*/
#define PCID_CNFG_HDR_S 0x00000020	/* Cnfg Hdr element		*/
#define PCID_CNFG_HDR_A 0x00000040	/* CNFG Hdr all			*/
#define PCID_CNFG_PLAT	0x00000080	/* Platform specific prints	*/
#define PCID_OPTION	0x00000100	/* Sysconfigtab, Option table	*/
#define PCID_MO_1	0x00000200	/* Match-on code info, lvl-1	*/
#define PCID_MO_2	0x00000400	/* Match-on code info, lvl-2	*/

/* Driver entry, configuration info					*/
#define PCID_PROBE	0x00001000	/* Driver-probe info		*/
#define PCID_ATTACH	0x00002000	/* Driver-attach config info	*/
#define PCID_SLAVE	0x00004000	/* Driver-slave config. info	*/

/* Resource managment info						*/
#define PCID_RSRC_MGMT	0x00100000	/* Resource mgmt info		*/

/* PCI bus-level info							*/
#define PCID_IO_HANDLES 0x01000000	/* PCI IO,Mem,Config iohandles	*/
#define PCID_DMA_MAPS	0x02000000	/* PCI DMA Windows attributes	*/

/* New, testing PCI bus-support debug printfs				*/
#define PCID_NOT_YET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */
extern char * _Pinout;
extern char * _Pconfig;
extern char * _Pcnfg_rd;
extern char * _Pcnfg_slot;
extern char * _Pcnfg_hdr_s;
extern char * _Pcnfg_hdr_a;
extern char * _Pcnfg_plat;
extern char * _Poption;
extern char * _Pmo_1;
extern char * _Pmo_2;
extern char * _Pprobe;
extern char * _Pattach;
extern char * _Pslave;
extern char * _Prsrc_mgmt;
extern char * _Pio_handles;
extern char * _Pdma_maps;
extern char * _Pnot_yet	;


/*
 * printf expansion that PCIPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _Pxxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

#ifdef PCIDEBUG
#   define _PCID_INOUT(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_INOUT )  {	\
	    /* VARARGS */			\
            printf (_Pinout); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_CONFIG(X)			\
    {						\
	/* NOSTRICT */				\
         if( _pci_developer_debug & PCID_CONFIG ) {	\
	    /* VARARGS */			\
            printf (_Pconfig); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_CNFG_RD(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_CNFG_RD )  {	\
	    /* VARARGS */			\
            printf (_Pcnfg_rd); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_CNFG_SLOT(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_CNFG_SLOT )  {	\
	    /* VARARGS */			\
            printf (_Pcnfg_slot); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_CNFG_HDR_S(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_CNFG_HDR_S )  {	\
	    /* VARARGS */			\
            printf (_Pcnfg_hdr_s); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_CNFG_HDR_A(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_CNFG_HDR_A )  {	\
	    /* VARARGS */			\
            printf (_Pcnfg_hdr_a); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_CNFG_PLAT(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_CNFG_PLAT )  {	\
	    /* VARARGS */			\
            printf (_Pcnfg_plat); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_OPTION(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_OPTION )  {	\
	    /* VARARGS */			\
            printf (_Poption); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_MO_1(X)				\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_MO_1 )  {	\
	    /* VARARGS */			\
            printf (_Pmo_1); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_MO_2(X)				\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_MO_2 )  {	\
	    /* VARARGS */			\
            printf (_Pmo_2); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_PROBE(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_PROBE )  {	\
	    /* VARARGS */			\
            printf (_Pprobe); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_ATTACH(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_ATTACH )  {	\
	    /* VARARGS */			\
            printf (_Pattach); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_SLAVE(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_SLAVE )  {	\
	    /* VARARGS */			\
            printf (_Pslave); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_RSRC_MGMT(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_RSRC_MGMT )  {	\
	    /* VARARGS */			\
            printf (_Prsrc_mgmt); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_IO_HANDLES(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_IO_HANDLES )  {	\
	    /* VARARGS */			\
            printf (_Pio_handles); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_DMA_MAPS(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_DMA_MAPS )  {	\
	    /* VARARGS */			\
            printf (_Pdma_maps); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _PCID_NOT_YET(X)			\
    {						\
	/* NOSTRICT */				\
        if( _pci_developer_debug & PCID_NOT_YET )  {	\
	    /* VARARGS */			\
            printf (_Pnot_yet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * _pci_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * PCID_CNFG_HDR_S | PCID_CNFG_HDR_A
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define PCIPRINTF(F, X)	_##F(X)

#else  /* !PCIDEBUG */
#   define PCIPRINTF(F, X)
#endif /* PCIDEBUG */

#endif /* __PCI_DEBUG_H__ */
