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
 * @(#)$RCSfile: sim_ata.h,v $ $Revision: 1.1.9.6 $ (DEC) $Date: 1999/03/17 23:22:50 $
 */
#ifndef _SIM_ATA_
#define _SIM_ATA_

#include <io/cam/cdrom.h>

/* ------------------------------------------------------------------------- */
/* 
 * Bus Master Status Register fields
 */
#define DMA_INTR        0x4
#define DMA_ERR         0x2
#define DMA_ACTIVE      0x1

/*
 * values in the sync_period field - PIO mode and DMA mode.
 */
#define PIO_FIELD_SIZE  8
#define PIO_SPEED_MASK  0x7

#define DMA_FIELD_SIZE  8
#define DMA_SPEED_MASK  0xf

/*
 * BITS in the sync_period field - PIO mode and DMA mode.
 */
#define SDMA_BIT	(FEAT_SINGLE_DMA << PIO_FIELD_SIZE)
#define MDMA_BIT	(FEAT_MULTI_DMA << PIO_FIELD_SIZE)
#define UDMA_BIT	(FEAT_ULTRA_DMA << PIO_FIELD_SIZE)

typedef struct ata_dispatch {
  struct bus *bus_hd;
  io_handle_t cfg_base;
  io_handle_t dma_base;
  struct dmaeng *dmaeng[2];
  U32 (*pci_info)();
  U32 (*pci_name)();
  U32 (*pci_set_mode)();
  U32 (*ata_dma_attach)();
  U32 (*ata_dma_init)();
  U32 (*ata_dma_setup)();
  U32 (*ata_dma_start1)();
  U32 (*ata_dma_start2)();
  U32 (*ata_dma_intr)();
  U32 (*ata_dma_end)();
  U32 (*ata_dma_probe)();
} ATA_DISPATCH;

/* where in the bus the dispatch table lives */
#define bus_dispatch         rsvd[0]

/* in the it_nexus and softc */
#define pio_mode	sync_period
#define	multi_io	sync_offset

/*
 * sync_period in the softc contains 2 limiting fields.
 * The low 4 bits are the adapters minimum PIO mode.
 *	some adapters can't clock slow enough to do low PIO modes.
 * The next 8 bits contain the maximum DMA field.
 *	some platforms have really BAD signal integrity and
 *	so we need to reduce their speed to compensate.
 *	It would have been nice to fix the H/W, but.....
 */
#define MIN_PIO( sc )	 	((sc)->sync_period & 0xf)
#define SET_MIN_PIO( sc, pio ) 	{					\
				(sc)->sync_period &= ~0xf;		\
			 	(sc)->sync_period |= ((pio) & 0xf);	\
}
#define MAX_DMA( sc ) 		(((sc)->sync_period & 0xff0) >> 4)
#define SET_MAX_DMA( sc, dma ) 	{					\
				(sc)->sync_period &= ~0xff0;		\
				(sc)->sync_period |= (((dma) & 0xff) << 4);\
}

#define DMA_ENABLE           sync_period & ((FEAT_SINGLE_DMA | FEAT_MULTI_DMA | FEAT_ULTRA_DMA)<<PIO_FIELD_SIZE)

/* Bus master register set */
typedef struct dmaeng {
  io_handle_t command;
  io_handle_t status;
  io_handle_t prd;
} DMAENG;

/*
 * Max hardware scatter/gather elements
 * Max supported single DMA xfer 
 * Max count argument for dma_map_load()
 */
#define PRD_XFER 	0x2000			 /* 8 kB */ 
#define PRD_EDT_BIT  0x80000000			 /* End of Xfer bit	*/

/*
 * PRDE - DMA physical region descriptor table entry
 */
typedef struct prde {
        U32     physaddr;
        U16     count;
	U16              : 15,
	        edt      : 1;
} PRDE;

/*
 * ATA_JOB - complete job descriptor for a single IO
 * !NOTE! Due to the hardware access mapping must be
 * allocated within the page boundary. 
 */

typedef struct ata_job {
    SIM_WS              *ata_sim_ws;    /* SIM working set for request  */
    struct controller	*ata_ctlr;	/* bus adapter reference        */
    dma_handle_t	ata_dma_job;	/* ATA_JOB mapping handle	*/
    dma_handle_t        ata_dma_data;   /* dma handle (chain) for the data  */
    io_handle_t	        ata_prd_physad;	/* Physical address of the ata_prd  */
    U32                 ata_dma_active; /* did we turn the engine on?   */
    U32                 ata_err;        /* error code                   */
    U32			ata_slots;	/* Number of slots in the table	*/
    PRDE                ata_prd[1];     /* Physical region descriptor table.
    					   Must be last - occupies the rest
					   of the page sized buffer	*/
} ATA_JOB;

typedef struct ata_bus {
    U32 ctlr_num[2];			/* each ports controller #	   */
    I32 enabled[2];			/* each ports enable flag	   */
    U32 mode[2];			/* each ports operating mode	   */
    U32 saved_ARTIM23;			/* saved value for ARTTIM2	   */
    U32 unused;				/* Unused			   */
    U32 min_cmd_mode;			/* chips minimum command timing	   */
    U32 min_tim_23;			/* unit 2/3 minimum speeds	   */
    io_handle_t config_addr;		/* PCI chips config address	   */
    io_handle_t cs_ptr;			/* an extra chip specific pointer  */
} ATA_BUS;

struct ata_pci_info {
    U32 io_size;		/* 1,2,4 bytes per data buffer access	   */
    U32 num_ports;		/* Number of ports on this adapter	   */
    U32 ports_per_inter;	/* Number of ports with the same interrupt */
    U32 num_func;		/* Function number of this part		   */
};

/*
 * controller csr's
 *
 * The first drive on the Primary controller uses addresses
 * 0x1F0-0x1F7 and 0x3F0-0x3F7.  The Secondary controller uses
 * addresses 0x170-0x177 and 0x370-0x377
 */

#define ATA_PRIMARY_CTLR	0x1f0
#define ATA_SECONDARY_CTLR	0x170

#define outb(port, val)         mb(); WRITE_BUS_D8((port), (val))
#define inb(port)               READ_BUS_D8((port))
#define outw(port, val)         mb(); WRITE_BUS_D16((port), (val))
#define inw(port)               READ_BUS_D16((port))
#define outl(port, val)         WRITE_BUS_D32((port), (val))
#define inl(port)               READ_BUS_D32((port))

/*
 * From (section 6.2), "I/O register descriptions."
 * These csr's are defined as offsets from the controller's
 * base address.
 */
/*
 * the command block registers
 */
#define PORT_DATA(addr)			(0x0+(addr))
#define PORT_ERROR(addr)		(0x1+(addr))
#define PORT_FEATURES(addr)		(0x1+(addr))	/* old precomp reg */
#define PORT_NSECTOR(addr)		(0x2+(addr))
#define PORT_SECTOR(addr)		(0x3+(addr))
#define PORT_CYLINDERLOW(addr)		(0x4+(addr))
#define PORT_CYLINDERHIGH(addr)		(0x5+(addr))
#define PORT_DRIVE_HEAD(addr)		(0x6+(addr))
#define PORT_STATUS(addr)		(0x7+(addr))
#define PORT_COMMAND(addr)		(0x7+(addr))

/*
 * the control block registers
 */
#define PORT_ALTSTAT(addr)	((addr)+(uint)sc->rambuf)
#define PORT_DEVCTL(addr)	((addr)+(uint)sc->rambuf)

/*
 * the offset in legacy mode applications
 */
#define ALTSTAT_LEGACY		(0x206)		/* alternate status, read    */
#define DEVCTL_LEGACY		(0x206)		/* device control, write     */

/*
 * the offset in PCMCIA (or native PCI) applications using 16 byte
 * register space.
 */
#define ALTSTAT_NATIVE		(0x0e)		/* alternate status, read    */
#define DEVCTL_NATIVE		(0x0e)		/* device control, write     */

/*
 * Device control register bit definitions (from 6.2.6)
 */
#define DEVCTL_NIEN	0x2		/* interrupt disable (0 == enabled)   */
#define DEVCTL_SRST	0x4		/* host software reset		     */
#define DEVCTL_ONE	0x8		/* this bit must always be written   */

/*
 * Drive/head register (from section 6.2.8)
 */
#define DH_HEAD		0xf		/* bitmask for head to be selected   */
#define DH_DRV		0x10		/* drive select, 0 == drive 0	     */
#define DH_LBA		0x40		/* address mode, 0 == CHS, 1 == LBA  */
#define DH_FIXEDBITS	0xa0		/* these bits must be written as ones*/

/*
 * Error register (from section 6.2.9)
 * Valid only when the low-bit is set in the status register,
 * or after a "execute diagnostic" command is completed,
 * or after a power-on, or a reset
 */
#define ERROR_AMNF	0x1		/* address mark not found	     */
#define ERROR_TK0NF	0x2		/* track zero not found		     */
#define ERROR_ABORT	0x4		/* aborted command		     */
#define ERROR_MCR	0x8		/* media change request		     */
#define ERROR_IDNF	0x10		/* ID not found			     */
#define ERROR_MC	0x20		/* media changed		     */
#define ERROR_UNC	0x40		/* uncorrectable media error	     */
#define ERROR_BBK	0x80		/* bad block mark detected on a sector*/

/*
 * Diagnostic codes, from 9.7 table 10 (section 8.8 table 10)
 */
#define ERROR_NONE	0x1		/* No error detected		     */
#define ERROR_FORMAT	0x2		/* formatter device error	     */
#define ERROR_BUFFER	0x3		/* sector buffer error		     */
#define ERROR_ECC	0x4		/* ECC circuitry error		     */
#define ERROR_CTLR	0x5		/* controlling microprocessor error  */
#define ERROR_DRIVE1	0x80		/* set for errors on drive 1	     */

/*
 * Features register, from 9.22 table 12 (section 8.32 table 15)
 */
#define FEAT_8BIT_ON	0x1		/* set 8-bit data transfers	     */
#define FEAT_WCACHE_ON	0x2		/* enable write cache (vendor unique)*/
#define FEAT_STM	0x3		/* set transfer mode		     */
#define FEAT_ARE	0x4		/* Automatic reallocation on error   */
#define FEAT_RETRY_OFF	0x33		/* disable retry (vendor unique)     */
#define FEAT_ECC	0x44		/* ECC length for read/write long    */
#define FEAT_CACHE_CTL	0x54		/* set cache segments (vendor unique)*/
#define FEAT_RAHEAD_OFF	0x55		/* disable read look-ahead	     */
#define FEAT_DEF_OFF	0x66		/* don't revert to power-on defaults */
#define FEAT_ECC_OFF	0x77		/* disable ECC (vendor unique)       */
#define FEAT_8BIT_OFF	0x81		/* disable 8-bit data transfers	     */
#define FEAT_WCACHE_OFF	0x82		/* disable write cache (vendor...)   */
#define FEAT_ARE_OFF	0x84		/* disable Automatic reallocation    */
#define FEAT_ECC_ON	0x88		/* enable ECC (vendor unique)	     */
#define FEAT_RETRY_ON	0x99		/* enable retries (vendor unique)    */
#define FEAT_MAX_POWER	0x9a		/* Set device maximum current draw   */
#define FEAT_RAHEAD_ON	0xaa		/* enable read look-ahead	     */
#define FEAT_PREFETCH	0xab		/* maximum prefectch value (vendor..)*/
#define FEAT_4ECC	0xbb		/* 4 bytes of ECC for read/write long*/
#define FEAT_DEF_ON	0xcc		/* go to power-on defaults on reset  */

/*
 * sector count register values for the Set Transfer Mode feature
 */
#define FEAT_BLOCK	0x0		/* block transfers		     */
#define FEAT_FAST_PIO	0x8		/* PIO mode x			     */
#define FEAT_SINGLE_DMA	0x10		/* single word DMA mode x	     */
#define FEAT_MULTI_DMA	0x20		/* multiword DMA mode x		     */
#define FEAT_ULTRA_DMA	0x40		/* ultra DMA mode x		     */

/*
 * Status register bit definitions (from section 6.2.13)
 */
#define STAT_ERR	0x1		/* error on command (err reg valid)  */
#define STAT_INDEX	0x2		/* this is set once per revolution   */
#define STAT_CORR	0x4		/* corrected data error on last cmd  */
#define STAT_DRQ	0x8		/* drive is ready to transfer data   */
#define STAT_DSC	0x10		/* drive seek cmplt (latches w/err)  */
#define STAT_DWF	0x20		/* drive write fault (latches w/err) */
#define STAT_DRDY	0x40		/* drive is ready for a command	     */
#define STAT_BUSY	0x80		/* drive owns the command block regs */


/*
 * ATA commands (from section 8 table 9)
 */
#define CMD_ACK_MC	0xdb	/* ack media change	Optional    Class 1  */
#define CMD_ATAPI_RESET	0x08	/* ATAPI Soft Reset	Mandatory	     */
#define CMD_BOOT_PRE	0xdc	/* Boot - pre boot	Optional    Class 1  */
#define CMD_BOOT_POST	0xdd	/* Boot - post boot	Optional    Class 1  */
#define CMD_CHK_PWRMODE	0xe5	/* check power mode	Optional    Class 1  */
#define CMD_DOOR_LOCK	0xde	/* door lock		Optional    Class 1  */
#define CMD_DOOR_UNLOCK	0xdf	/* door unlock		Optional    Class 1  */
#define CMD_DIAGNOSTIC	0x90	/* execute diagnostic	Mandatory   Class 1  */
#define CMD_FMT_TRACK	0x50	/* format track		Mandatory   Class 2  */
#define CMD_IDENT_DMA   0xee    /* identify drive dma   Optional             */
#define CMD_IDENT_DRIVE	0xec	/* identify drive	Optional    Class 1  */
#define CMD_IDLE	0xe3	/* Idle			Optional    Class 1  */
#define CMD_IDLE_IMMED	0xe1	/* idle immediate	Optional    Class 1  */
#define CMD_INIT_PARAMS	0x91	/* Initialize parms	Mandatory   Class 1  */
#define CMD_MODE_SENSEL	0xf0	/* mode sense/select	Vendor	    Class 1  */
#define CMD_MEDIA_EJECT 0xed	/* media eject		Optional    Class    */
#define CMD_NOP		0x0	/* NOP			Optional    Class 1  */
#define CMD_READ_BUFFER	0xe4	/* read buffer		Optional    Class 1  */
#define CMD_READ_DMA	0xc8	/* read DMA		Optional    Class 1  */
#define CMD_READ_MULTI	0xc4	/* read multiple	Optional    Class 1  */
#define CMD_READ_SECTORS 0x20	/* read sectors		Mandatory   Class 1  */
#define CMD_READ_VERIFY	0x40	/* read verify sectors	Mandatory   Class 1  */
#define CMD_RECAL	0x10	/* recalibrate		Mandatory   Class 1  */
#define CMD_RESTORE_DRV	0xea	/* restore drive state	Optional    Class 1  */
#define CMD_SEEK	0x70	/* seek			Mandatory   Class 1  */
#define CMD_SET_FEAT	0xef	/* set features		Optional    Class 1  */
#define CMD_SET_MULTI	0xc6	/* set multiple mode	Optional    Class 1  */
#define CMD_SLEEP	0xe6	/* sleep		Optional    Class 1  */
#define CMD_STANDBY	0xe2	/* standby		Optional    Class 1  */
#define CMD_STBY_IMMED	0xe0	/* standby immediate	Optional    Class 1  */
#define CMD_WRITE_BUF	0xe8	/* write buffer		Optional    Class 2  */
#define CMD_WRITE_DMA	0xca	/* write DMA		Optional    Class 3  */
#define CMD_WRITE_MULTI	0xc5	/* write multiple	Optional    Class 3  */
#define CMD_WRITE_SAME	0xe9	/* write same		Optional    Class 3  */
#define CMD_WRITE_SECTORS 0x30	/* write sectors	Mandatory   Class 2  */
#define CMD_WRITE_VERIFY 0x3c	/* write verify		Optional    Class 3  */

/*
 * Old versions of power mangement in case a device supports these, but
 * doesn't yet support the new ones.
 */
#define CMD_IDLE_OLD		0x97	/* Idle			Class 1  */
#define CMD_IDLE_IMMED_OLD	0x95	/* idle immediate	Class 1  */
#define CMD_SLEEP_OLD		0x99	/* sleep		Class 1  */
#define CMD_STANDBY_OLD		0x96	/* standby		Class 1  */
#define CMD_STBY_IMMED_OLD	0x94	/* standby immediate	Class 1  */

#define RW_RETRY	0x1	/* retry bit for read and write commands     */
#define RW_LONG		0x2	/* long bit for read and write commands	     */

/*
 * ATAPI commands from section 8.1 of ATAPI spec.
 */
#define	CMD_ATAPI_IDENT	0xa1	/* identify drive	Mandatory	     */
#define CMD_ATAPI_PKT	0xa0	/* send packet command	Mandatory	     */

/*
 * ATAPI Magic numbers to help determine ATA vs ATAPI.
 */
#define ATAPI_MAGIC_1	0x14	/* cylinder low magic number		     */
#define ATAPI_MAGIC_2	0xeb	/* cylinder high magic number		     */
/*
 * bits for format track command, from section 9.8
 */
#define FMT_SECTOR_GOOD	0x0	/* format sector as good		     */
#define FMT_DEASSIGN	0x20	/* deassign alternate location for this sector*/
#define FMT_REASSIGN	0x40	/* assign this sector to an alternate location*/
#define FMT_SECTOR_BAD	0x80	/* format this sector as bad		     */

/*
 * bits for the Identify Drive command, from table 11
 */
/*
 * General configuration bit-significant information
 * bits 0 and 15 are reserved
 */
#define GCONFIG_HARD	0x2	/* hard-sectored			     */
#define GCONFIG_SOFT	0x4	/* soft-sectored			     */
#define GCONFIG_NOT_MFM	0x8	/* disk is not MFM-encoded		     */
#define GCONFIG_SWITCH	0x10	/* head switch time is >15us		     */
#define GCONFIG_MOTOR	0x20	/* spindle motor control is implemented	     */
#define GCONFIG_FIXED	0x40	/* fixed drive				     */
#define GCONFIG_REMOVE	0x80	/* removable cartridge drive		     */
#define GCONFIG_SLOW	0x100	/* transfer rate is <= 5Mbps		     */
#define GCONFIG_MEDIUM	0x200	/* transfer rate is > 5Mbps and <= 10Mbps    */
#define GCONFIG_FAST	0x400	/* transfer rate is > 10Mbps		     */
#define GCONFIG_SLOPPY	0x800	/* rotational speed tolerance is > 0.5%	     */
#define GCONFIG_DSTROFF	0x1000	/* data strobe offset option available	     */
#define GCONFIG_TRKOFF	0x2000	/* track offset option available	     */
#define GCONFIG_GAPREQ	0x4000	/* format speed tolerance gap required	     */
/*
 * These bits come from the gen_config field for ATAPI identify drive commands
 */
#define GC_ATAPI_P_TYPE		0xc000	/* protocol type field		     */
#define GC_ATAPI_DEV_TYPE	0x1f00	/* device type field		     */
#define GC_ATAPI_DRQ_TYPE	0x0060	/* command DRQ type field	     */
#define	GC_ATAPI_PKT_SIZE	0x0003	/* Command packet size used	     */
/*
 * Bits associated with the above type masks.
 */
#define PROTOCOL_ATAPI		0x8000	/* ATAPI protocol type		     */
#define DRQ_MICRO		0x0000	/* Micro-Processor DRQ (3ms)	     */
#define DRQ_INTERRUPT		0x0020	/* Interrupt on DRQ		     */
#define DRQ_FAST		0x0040	/* Fast DRQ assertion (50us)	     */
#define DRQ_RESERVED		0x0060	/* Unknown DRQ type - reserved	     */

/*
 * word 20, buffer type
 */
#define BUF_TYPE_UNKNOWN	0x0	/* buffer type not specified	     */
#define BUF_TYPE_SPSS		0x1	/* single port, single sector	     */
#define BUF_TYPE_DPMS		0x2	/* dual port, multi sector	     */
#define BUF_TYPE_DPMS_CACHE	0x3	/* dual port, multi sector, caching  */
/*
 * word 49, capabilities
 */
#define CAP_DMAOK	0x100	/* DMA supported (bit 8)		     */ 
#define CAP_LBAOK	0x200	/* LBA supported (bit 9)		     */ 
#define CAP_NOFLOW	0x400	/* IORDY flow control can be disabled	     */
#define CAP_FLOWOK	0x800	/* IORDY flow control is supported	     */

/*
 * word 59, multiple sector support
 */
#define MULTI_VALID	0x100	/* Multiple sector setting is valid	     */

#pragma pack    (2)			/* IDE is 16 bit aligned */
typedef struct ata_id {
	ushort	gen_config; 		/*				  [0]*/
	ushort	cylinders;		/*				  [1]*/
	ushort	spec_config;		/*				  [2]*/
	ushort	heads;			/* fixed heads, cartridge heads   [3]*/
	ushort	unused1;		/* unformatted bytes per track	  [4]*/
	ushort	unused2;		/* unformatted bytes per sector	  [5]*/
	ushort	sectors_per_track;	/*				  [6]*/
	ushort	unused3;		/* bytes for the gap areas	  [7]*/
	ushort	unused4;		/* Minimum bytes for PLO	  [8]*/
	ushort	unused5;		/* Number of VU status bytes	  [9]*/
	char	serial_number[20];	/*			      [10-19]*/
	ushort	buffer_type;		/*				 [20]*/
	ushort	buffer_size;		/* in 512 byte increments	 [21]*/
	ushort	ecc;			/* number of ECC bytes		 [22]*/
	char	revision[8];		/*			      [23-26]*/
	char	model[40];		/* 			      [27-46]*/
	ushort	sectors_per_int;	/* low byte = # of sectors per int   */
	ushort	unused6;		/* old doubleword I/O stuff	 [48]*/
	ushort	capabilities;		/*				 [49]*/
	ushort	capabilities1;		/*				 [50]*/
	ushort	pio_timing;		/*				 [51]*/
	ushort	dma_timing;		/*				 [52]*/
	ushort	advanced_flags;		/* bytes 54-58/64-70 valid flags [53]*/
	ushort	current_cylinders;	/*				 [54]*/
	ushort	current_heads;		/*				 [55]*/
	ushort	current_sectors;	/*				 [56]*/
	uint	current_capacity;	/* in sectors		      [57-58]*/
	ushort	multi_sector_flags;	/*				 [59]*/
	uint	total_sectors;		/* in LBA mode only	      [60-61]*/
	ushort	single_DMA_modes;	/*				 [62]*/
	ushort	multi_DMA_modes;	/*				 [63]*/
	ushort	advanced_PIO_modes;	/*				 [64]*/
					/* following 4 times are in nsec     */
	ushort	min_multi_DMA_time;	/* min multi-DMA cycle time	 [65]*/
	ushort	mfr_multi_DMA_time;	/* recommended multi-DMA cycle time  */
	ushort	min_PIO_time;		/* min PIO cycle time w/o IORDY	 [67]*/
	ushort	min_PIO_flow;		/* min PIO cycle time w/IORDY	 [68]*/
	ushort	unused8;		/* reserved			 [69]*/
	ushort	unused9;		/* reserved			 [70]*/
	ushort	rel_after_cmd_time;	/* release time for overlapped cmd   */
	ushort	rel_after_sel_time;	/* release time after service cmd    */
	uint	unused10;		/* reserved		      [73-74]*/
	ushort	queue_depth;		/* Queue Depth			 [75]*/
	uint	unused11;		/* reserved		      [76-77]*/
	uint	unused12;		/* reserved		      [78-79]*/
	ushort	major_rev;		/* major revision number	 [80]*/
	ushort	minor_rev;		/* minor revision number	 [81]*/
	ushort	cmd_set1;		/* Command set supported	 [82]*/
	ushort	cmd_set2;		/* Command set supported	 [83]*/
	ushort	cmd_feat_ext;		/* Command set extensions	 [84]*/
	ushort	cmd_feat_enable1;	/* Command features enabled	 [85]*/
	ushort	cmd_feat_enable2;	/* Command features enabled	 [86]*/
	ushort	cmd_feat_defaults;	/* Command features defaults	 [87]*/
	ushort	ultra_mode;		/* Ultra modes supported	 [88]*/
	ushort	security_erase_time;	/* Time for security erase	 [89]*/
	ushort	enhance_sec_erase_time;	/* Enhanced security erase time	 [90]*/
	ushort	adv_pwr_mgmt;		/* Advanced power management #	 [91]*/
	ushort	master_pwd_code;	/* Master password revision code [92]*/
	ushort	hw_reset_result;	/* H/W reset result		 [93]*/
	char	unused13[32];		/* reserved		     [94-126]*/
	ushort	removable_features;	/* Removable features supported	[127]*/
	ushort	security_status;	/* Security status	       	[128]*/
} ATA_ID;
#pragma pack ()				/* back to standard alignment now */

typedef struct emu {
	union {
	    struct mode {
		uchar *s_ptr;		/* saved pointer		*/
		int s_count;		/* saved count			*/
	    } mode;
	    struct toc {
		uchar s_r;		/* a reserved field		*/
		uchar s_M;		/* starting minute		*/
		uchar s_S;		/* staring second		*/
		uchar s_F;		/* staring frame		*/
		uchar e_track;		/* ending track			*/
		uchar e_index;		/* ending index			*/
	    } toc;
	} un;
} ATA_EMU;

typedef struct simata_softc {
#define SIMATA_SOFTC_VERS 2
    ATA_DISPATCH *dispatch; 
                        /* one per bus; i.e., same as in bus            */
    U32 target;		/* Target command was issued to			*/
    U32 lun;		/* LUN command was issued to			*/
    U32 state;		/* Next expected state				*/
    I32 status;		/* Copy of current status register from chip	*/
    U32 error;		/* Copy of current error register from chip	*/
    U32 flags;		/* Some information flags			*/
    U32 last_command;	/* place to keep the last command issued	*/
    U32 ata_intr_state;	/* Keep track of ata interrupt state		*/
    U16 set_feat_req;	/* Keep track of last set feature command	*/
    U16 set_feat_sub;	/* Keep track of last set feature value		*/
    U32 atapi_state;	/* Keep track of atapi state			*/
    U32 bdr_retry;	/* retry count so BDR's don't last for ever	*/
    ATA_JOB *ata_job[2];/* dma map load structure                       */
    char id_buf[2][DEV_BSIZE]; 
                        /* identify buffer                              */
    ATA_ID *ata_id[2];	/* pointer to each per unit id data		*/
    struct toc_single_entry *tocbuf[2];
			/* TOC data -> for ATAPI play index emulation	*/
    ALL_MODE_DATA10 *modebuf[2];
			/* MODE data -> for (6)->(10) translation	*/
    ATA_EMU emu_info[2];/* saved data for command emulation		*/
    U32 u_flags1[2];	/* unit flags for some per unit data		*/
    U32 u_flags2[2];	/* unit flags for some per unit data		*/
    U32 sense_key;	/* preset value for sense key			*/
    U32 ascq;		/* preset value for asc/ascq			*/
    U32 issued_count;	/* Count issued during operation		*/
    U32 saved_status;	/* Copy of STATUS register from chip		*/
    U32 saved_error;	/* Copy of ERROR register from chip		*/
    U32 saved_block;	/* Copy of block where error occured		*/
    U32 saved_count;	/* Copy of count during operation that failed	*/
    uchar saved_remain;	/* Copy of NSECTOR register at failure		*/
    uchar saved_sec;	/* Copy of SECTOR register at failure		*/
    uchar saved_cyll;	/* Copy of CYLINDERLOW register	at failure	*/
    uchar saved_cylh;	/* Copy of CYLINDERHIGH register at failure	*/
    uchar saved_dh;	/* Copy of DRIVE_HEAD register at failure	*/
    uchar saved_reg5;	/* Copy of ..unused.. at failure		*/
    uchar saved_reg6;	/* Copy of ..unused.. at failure		*/
    uchar saved_reg7;	/* Copy of ..unused.. at failure		*/
    U32	last_atapi_reason; /* last entry to atapi_pkt_sm		*/
    /* 
     * LOCKING
     */
    simple_lock_data_t	ata_lock;	/* smp locking */

} SIMATA_SOFTC;

/*
 * ata sim information flags
 */
#define ATA_SENSE_SET		0x01	/* sense data set by S/W	*/
#define ATA_STATUS_SAVED	0x02	/* status/error saved by S/W	*/
#define ATA_MDMA_CAPABLE	0x04    /* indicates MDMA supported	*/
#define ATA_SDMA_CAPABLE	0x08	/* indicates SDMA supported	*/
#define ATA_UDMA_CAPABLE	0x10	/* Ultra DMA driver support	*/
#define ATA_U2MA_CAPABLE	0x20	/* Ultra2 DMA driver support	*/
#define ATA_ADMA_CAPABLE	(ATA_MDMA_CAPABLE | ATA_SDMA_CAPABLE |	\
				 ATA_UDMA_CAPABLE | ATA_U2MA_CAPABLE)
					/* Any DMA capability		*/

/*
 * unit flags (for u_flags1)
 */
#define ATAPI_DEV		0x001	/* It's an ATAPI device		*/
#define ATA_NO_UNIT		0x002	/* No unit found at probe	*/
#define ATA_ERROR_RETRY		0x004	/* Single I/Os for error retry	*/
#define ATA_STOPPED		0x008	/* Unit has been stopped	*/
#define ATA_ARE			0x010	/* ARE enable worked		*/
#define ATA_CORR_ERROR		0x020	/* A Correctable error occured	*/
#define ATA_USE_SW_SCOUNT	0x040	/* Use S/W sector count instead */
					/*   of the H/W register	*/
#define	ATA_SWAP_LBA_SIZE	0x080	/* broken device swap flag	*/
#define	ATA_NO_ULTRA		0x100	/* broken device no ultra flag	*/
/*
 * ata sim state values.
 */
#define ATA_NOSTATE	0x0	/* No expected state			*/
#define ATA_INTERRUPT	0x1	/* An interrupt should happen next	*/
#define ATA_READ_CAP	0x2	/* Read Capacity processing		*/
#define ATA_MODE_SENSE	0x3	/* Mode Sense processing		*/
#define ATA_TUR		0x4	/* Test Unit Ready processing		*/
#define ATA_REQ_SENSE	0x5	/* Request Sense processing		*/
#define ATA_START_STOP	0x6	/* Start/Stop processing		*/
#define ATA_COMPLETE	0x7	/* Simply complete the request		*/
#define ATA_ATAPI_RESET	0x8	/* Process the ATAPI_RESET completion	*/
#define ATA_COMPLETE_ERR 0x9	/* Complete request with error          */
#define ATA_INIT_STATE	0xa	/* Do device check/initialization	*/
#define	ATA_SHUTDOWN	0x10	/* shutting down			*/

/*
 * ata general state values.  Used by the interrupt service routine to
 * decide what to do next (if multiple steps are necessary).
 */
#define	ATA_INTR_NOSTATE	0x0	/* nothing more to do		*/
#define	ATA_INTR_CMP		0x1	/* complete without error	*/
#define	ATA_INTR_CMP_ERR	0x2	/* complete with error		*/
#define ATA_INTR_STO		0x3	/* select timeout error		*/
#define ATA_INTR_SET_PARAMS	0x4	/* Set Paramaters cmd required	*/
#define	ATA_INTR_SET_MULTI	0x5	/* Set multi command required	*/
#define ATA_INTR_REISSUE	0x6	/* Reissue the current command	*/

/*
 * atapi state values.
 */
#define ATAPI_NOSTATE	0x0	/* Nothing more to do - complete cmd	*/
#define ATAPI_PLAY_TI_1	0x1	/* Play track index step 1		*/
#define ATAPI_PLAY_TI_2 0x2	/* Play track index step 2		*/
#define ATAPI_MODE_SEL6_1 0x3	/* Mode Select(6) command		*/
#define ATAPI_MODE_SENSE6_1 0x4	/* Mode Sense(6) command		*/
#define ATAPI_INQUIRY	0x5	/* Inquiry command completion process	*/
#define ATAPI_READ_CAP	0x6	/* Read Capacity completion process	*/

/*
 * generic ata locking
 */
#define ATA_LOCK_INIT( lockname ) { 					\
	usimple_lock_setup( &lockname->ata_lock, cam_ata_li );	       	\
}	

#define ATA_LOCK(s, ata_sc) {						\
    s = splbio();							\
    CAM_SPINLOCK( &((ata_sc)->ata_lock) );			        \
}

#define ATA_UNLOCK(s, ata_sc) {					        \
    CAM_SPINUNLOCK( &((ata_sc)->ata_lock) );				\
    splx(s);								\
}

/* ----------------------------------------------------------------------------
 * function declarations 
 */
U32 ata_reset( SIM_SOFTC * );
U32 ata_pci_set_mode(SIM_SOFTC *, SIM_WS *, I32, 
		     int (*pci_speed_setup)(U32, U32, U32));

/*
 * DMA functions prototypes
 */

U32	ata_setup_PRD_table( SIM_WS *, ATA_JOB *);
void	ata_free_dma_resources(ATA_JOB *);
ATA_JOB *ata_alloc_job(struct controller *);
void	ata_free_job(ATA_JOB *);

/*
 * common dma function prototypes
 */
U32 ata_pci_dma_attach(SIM_SOFTC *);
U32 ata_pci_dma_init(SIM_SOFTC *, int);
U32 ata_pci_dma_setup(ATA_DISPATCH *, ATA_JOB *, DMAENG *, SIM_WS *);
U32 ata_pci_dma_start1(SIM_WS *, SIM_SOFTC *, int);
U32 ata_pci_dma_start2(DMAENG *);
U32 ata_pci_dma_intr(SIM_SOFTC *, SIM_WS *);
U32 ata_pci_dma_end(SIM_SOFTC *, SIM_WS *);

#endif /* _SIM_ATA_ */

