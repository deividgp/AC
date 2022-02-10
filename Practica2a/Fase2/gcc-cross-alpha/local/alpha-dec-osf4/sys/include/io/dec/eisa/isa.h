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
 * @(#)$RCSfile: isa.h,v $ $Revision: 1.1.4.4 $ (DEC) $Date: 1994/04/19 21:58:12 $
 */

/* isa.h
 *
 *  definitions for the isa bus
 *
 *
 *  Modification History
 *
 *   04-Sep-91   Joe Notarangelo
 *               created this file
 */

#include	<io/dec/eisa/eisa.h>

#ifndef __ISA_H__
#define __ISA_H__

/* interrupt levels for isa bus */


#define ISA_L15    15
#define ISA_L14    14
#define ISA_L13    13
#define ISA_L12    12
#define ISA_L11    11
#define ISA_L10    10
#define ISA_L9      9
#define ISA_L8      8
#define ISA_L7      7
#define ISA_L6      6
#define ISA_L5      5
#define ISA_L4      4
#define ISA_L3      3
#define ISA_L1      1
#define ISA_L0      0

struct isa_config_struct{
  char *isa_name;
  int   isa_unit;
  int   isa_level;
  int   isa_channel;
  int   isa_csr;
};

/* Macros for I/O. */

#define MGL(x)  ( (((long) (x) & 1) << 30) | \
    (((long) (x) & 0xe) << 26) | \
    (((long) (x) & 0xffff0) << 1) ) 

#define MGLW(x)  ( (((long) (x) & 0xe) << 26) | (((long) (x) & 0xffff0) << 1)) 

/* pc interrupt channel definitions */

/* combo chip interrupts */
#define PC_UART_INTR   0x0
#define PC_LPR_INTR    0x1
#define PC_KB_MS_INTR  0x2
/* dma interrupts */
#define PC_ICW2_INTR        0x5
#define PC_DMA_CHAIN_INTR   0x4
#define PC_DMA_TCOUNT_INTR  0x7
/* isa interrupts */
#define PC_ISA3_INTR       0xe
#define PC_ISA4_INTR       0xf
#define PC_ISA5_INTR       0x10
#define PC_ISA6_INTR       0x11
#define PC_ISA7_INTR       0x12
#define PC_ISA9_INTR       0x14
#define PC_ISA10_INTR      0x15
#define PC_ISA11_INTR      0x16
#define PC_ISA12_INTR      0x17
#define PC_ISA14_INTR      0x19
#define PC_ISA15_INTR      0x1a

#define PC_IRQMAX   PC_ISA15_INTR

#endif /*__ISA_H__*/

/* #ifdef notdef burnsfix */

#define	ISA_NAMELEN	8	/* Length of driver, ctrl etc names. */
#define	ISA_IDNAMELEN	7	/* Length of driver, ctrl etc names. */
#define ISA_FUNCLEN	16	/* Length of function string. */


/* #endif	 notdef */

/*
 * The simple struct below is used by platforms supporting the
 * isa bus to provice information to the isa code on configuration
 * data that need to be compressed into a single slot structure.
 * The actual structure needs to be null terminated. The character
 * strings are those used by the firmware. Data represented by string
 * data1 and data2 come together in a single slot structure. Example
 * usage is to provice keyboard/mouse configuration data to the gpc
 * driver:
 *	data would look like this
 *	  struct isa_slot_merge_data[] = {
 *	  	{"MOUSE", "KBD"},
 *		{"", ""},
 *	  };
 * The platform code stuffs the address of it's table into the
 * global isa_platform_slot_data. If non-null the ISA code operates
 * upon the data.
 */
struct isa_slot_merge_data {
    char	*data1;
    char	*data2;
};


/*
 * Below are 3 structure definitions provided by firmware to
 * describe the saved isa configuration data.
 */

/*
 * Firmware created isa config table header.
 */
struct isa_config_table_header {
    char identifier[8];
    char major_version[2];
    char minor_version[2];
    char reserved[4];
    u_int num_entries;
    u_int first_entry_offset;
    u_int table_checksum;
    u_int header_checksum;
};

/*
 * Firmware created isa config table header.
 */
#define	MAX_PORTS_PER_DEVICE		6
#define	MAX_MEM_RANGES_PER_DEVICE	3
#define	MAX_IRQS_PER_DEVICE		4
#define	MAX_DMA_CHAN_PER_DEVICE		4
#define	ISA_LONG_FIELD_NOT_IN_USE	0x8000000000000000
#define	ISA_INT_FIELD_NOT_IN_USE	0x80000000

struct	mem_range_desc {
    u_long	addr;
    u_long	size;
};

union isa_dma {
	u_int	dma_info;
	struct {
	    uint_t	dma_chan : 8;
	    unit_t	dma_rsvd : 16;
	    uint_t	dma_mode : 7;
	    uint_t	dma_rsvd2 : 1;
	} dma_fields;
};

struct isa_config_table_entry {
    u_int entry_type;
    u_int reserved0;
    u_int isa_slot;
    u_int reserved1;
    u_int dev_num;
    u_int reserved2;
    u_int total_devices;   
    u_int reserved3;
    u_long io_base_addr[MAX_PORTS_PER_DEVICE];
    struct mem_range_desc mem_range_desc[MAX_MEM_RANGES_PER_DEVICE];
    u_long rom_base_addr;
    u_long rom_length;
    u_int device_enable;
    u_int reserved4;
    union isa_dma isa_dma[MAX_DMA_CHAN_PER_DEVICE];
    u_int irq_assignment[MAX_IRQS_PER_DEVICE];
    char handle[16];
};

/*
 * Frimware created isa config table
 */
struct isa_config_table {
    struct isa_config_table_header 	header;
    struct isa_config_table_entry	device[24];
};



