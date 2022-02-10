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
 *	@(#)$RCSfile: devdriver.h,v $ $Revision: 1.2.203.8 $ (DEC) $Date: 1999/03/16 21:49:57 $
 */ 
/*
 */
/*
 * OSF/1 Release 1.0
 */
/* 
 * New in OSF/1
 */

/*
 * Abstract:
 *	This module contains the definitions for the various data structures
 *	used by device drivers and configuration code.
 *
 * Revision History
 *
 *	25-Jan-1991	Mark Parenti (map)
 *		Original Version
 */

#ifndef DEVDRIVER_HDR
#define DEVDRIVER_HDR
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>


/* forward declarations for C++ */
#ifdef __cplusplus
struct bus;
struct controller;
struct port;
struct bus_framework;
struct device;
struct driver;
struct proc;
struct tc_info;
#endif

struct bus_ctlr_common {
	u_long *mbox;
	struct bus *bus_hd;
        u_long pad1;
        u_long pad2;
        u_long pad3;
        int    type;
};

typedef struct bus_ctlr_common * bus_ctlr_common_t;

#ifdef KERNEL
#include <io/common/handler.h>	
#include <sys/proc.h>
#include <mach/machine/vm_types.h>
#endif /* KERNEL */

#ifdef KERNEL
extern struct bus       *system_bus;    /* Pointer to nexus bus structure */
#endif /* KERNEL */
/*
 * Define the MP lock macros for the hardware topology tree created
 * with the structures defined in the header file.  This lock is
 * intended to protect the entire topology tree since access to the
 * tree will most likely be very seldom.  Also, static initialization
 * of the tree need not get the lock since we are known to be single
 * threaded (not multi-user).
 */
#ifdef KERNEL
extern lock_data_t topology_tree_lock;
#define LOCK_TOPOLOGY_TREE	lock_write(&topology_tree_lock)
#define UNLOCK_TOPOLOGY_TREE	lock_done(&topology_tree_lock)
#endif /* KERNEL */

/* bus structure - 
 *
 *	The bus structure is used to describe a bus entity. A bus is an entity
 *	(real or imagined) to which other buses or controllers are logically
 *	attached. All systems have at least one bus, the system bus.
 */

struct	bus {
	u_long		*bus_mbox;
	struct bus	*nxt_bus;	/* next bus			*/
	struct controller *ctlr_list;	/* controllers connected to this bus */
	struct bus	*bus_hd;	/* pointer to bus this bus connected to */
	struct bus	*bus_list;	/* buses connected to this bus */
	int		bus_type;	/* bus type			*/
	char		*bus_name;	/* bus name 			*/
	int		bus_num;	/* bus number			*/
	int		slot;		/* node or slot number		*/
	char		*connect_bus;	/* bus connected to		*/
	int		connect_num;	/* bus num connected to		*/
	int		(*confl1)();	/* Level 1 configuration routine */
	int		(*confl2)();	/* Level 2 configuration routine */
	char		*pname;		/* port name, if needed		*/
	struct port	*port;		/* pointer to port structure	*/
	int		(**intr)();	/* interrupt routine(s) for this bus */
	int		alive;		/* See bit definitions below	*/
	struct bus_framework *framework; /* Bus rtns for loadable drivers*/
	char            *driver_name;   /* Name of controlling driver */
#ifndef __cplusplus
	void		*private[8];	/* Reserved for this bus use	*/
#else
	void		*bprivate[8];	/* "private" is reserved word in C++ */
#endif
	void		*conn_priv[8];	/* Reserved for connected bus use */
        void            *bus_bridge_dma;/* Field used to signify Hardware DMA */  
	void		*bus_sw;	/* Bus-(hw-)specific switch table */
	void		*bus_slot;	/* Bus slot table		  */
	void		*rsvd[5];	/* Reserved for future expansion */
};

typedef	unsigned long	io_handle_t;

/* bus info structure
 *
 *	The bus info structure is used to pass certain information between
 *	a bus and another bus or an adapter connected in an hierarchical
 *	manner. The flow of information is from parent to child. 
 *	Typically the bus info structure is parent bus specific, i.e. it
 *	contains information the parent bus knows about and wants to pass
 *	on to its children. It does not contain information specific to
 *	the child. Since the information contained in the structure is
 *	specific to the parent bus its format is defined by that bus
 *	and will most likely vary from bus to bus. However there is a
 *	common set of data that all busses will know and will want to
 *	pass to there children. This information is contained in the
 *	common_bus_info structure defined below. The first element of
 *	every bus info structure should be a pointer to this
 *	common_bus_info structure.
 *	
 *	+----------------------------------------+
 *	|  Pointer to common info block  	 |
 *	|  (this is a struct common_bus_info *)  |
 *	+----------------------------------------|
 *	|  Bus specific data block elements      |
 *	|		    :			 |
 *	|		    :			 |
 *	+----------------------------------------+
 *
 *	Those busses that do not have any bus specific data can use
 *	the bus_info_hdr structure defined below as their bus info
 *	structure.
 */

struct	common_bus_info 
        {
	int		(**intr)();	/* Intr. routine for the child bus */
					/* adapter. 			   */
	io_handle_t	sparse_io_base; /* Base address of child's bus-io */
					/* space.  			  */
	io_handle_t	sparse_mem_base;/* Base address of child's */
					/* bus-memory space.       */ 
	vm_offset_t	dense_mem_base;	/* Base address of child's */
					/* bus-memory  space.      */
	};

struct	bus_info_hdr
   {
   struct  common_bus_info	*common_infop;
   };


typedef	char	*bus_addr_t;

/*
 * DMA window info data structure
 */
struct dma_map_info {
		vm_offset_t    phys_base;  /* phys. mem. window maps to */
		bus_addr_t     ba_base;	   /* base bus addr of DMA window */
		u_int          map_size;   /* size of window in Mbytes */
		u_int	       type;	   /* SG or DIRECT */
		struct dma_map_info *next; /* next in linked list */
};

typedef struct dma_map_info *dma_map_info_t;

#define DMA_WINDOW_TYPE_DIRECT	  0x01
#define DMA_WINDOW_TYPE_SG	  0x02
#define DMA_WINDOW_TYPE_64BIT     0x10

/* bus function table
 *
 *	Table of bus specific functions used by device drivers. This table
 *	is loaded by the bus configuration code and is then attached to the
 *	bus' bus structure at private[0]. The wrapper functions (in
 *	driver_support.c), which all have a device's controller function as
 *	an argument, follow the bus_hd pointer to get to the bus structure
 *	and then to the correct function for the bus they are attached to.
 */

struct	bus_funcs
   {
   void	(*do_config)();		/* Function to initialize option. */
   int	(*get_config)();	/* Function to get config info for option */
   void	(*enable_option)();	/* Function for enabling option interrupts */
   void	(*disable_option)();	/* Function for disabling option interrupts */
   io_handle_t (*busphys_to_iohandle)(); /* Function to generate an io handle
					     from a bus physical address */
   dma_map_info_t (*dma_get_maps)(); /* Function to get dma window info */
   };

/*
 *	Location in ctlr.conn_priv[] where we plug in the pointer to the
 *	bus function table.
 */
#define	busfuncs	private[0]


/* controller structure - 
 *
 *	The controller structure is used to describe a controller entity. A
 *	controller is an entity which connects logically to a bus. A controller
 *	may control devices which are directly connected, such as disks or
 *	tapes, or may perform some other controlling operation such as 
 *	network interface.
 */

struct	controller {
	u_long		*ctlr_mbox;
	struct controller *nxt_ctlr;	/* pointer to next ctlr on this bus */
	struct device	*dev_list;	/* devices connected to this ctlr */
	struct bus	*bus_hd;	/* pointer to bus for this ctlr   */
	struct driver	*driver;	/* pointer to driver structure for */
					/* this controller 		   */
	int		ctlr_type;	/* controller type		*/
	char		*ctlr_name;	/* controller name		*/
	int		ctlr_num;	/* controller number		*/
	char		*bus_name;	/* bus name			*/
	int		bus_num;	/* bus number connected to 	*/
	int		rctlr;		/* remote controller number	*/
					/* e.g. ci node or scsi id	*/
	int		slot;		/* node or slot number		*/
	int		alive;		/* See bit definitions below	*/
	char		*pname;		/* port name			*/
	struct port	*port;		/* port structure		*/
	int		(**intr)();	/* interrupt routine(s) for this ctlr */
	caddr_t		addr;		/* virtual address of controller */
	caddr_t		addr2;		/* virtual address of second ctlr */
					/* register space		  */
	int		flags;		/* flags from config line	*/
	int		bus_priority;	/* bus priority from from config */
	int		ivnum;		/* interrupt vector number	*/
	int		priority;	/* system ipl level		*/
	int		cmd;		/* cmd for go routine		*/
	caddr_t		physaddr;	/* physical address of addr	*/
	caddr_t		physaddr2;	/* physical address of addr2	*/
#ifndef __cplusplus
	void		*private[8];	/* Reserved for ctlr use	*/
#else
	void		*cprivate[8];	/* "private" is reserved word in C++ */
#endif
	void		*conn_priv[8];	/* Reserved for connected bus use */
	void		*rsvd[8];	/* reserved for future expansion */
};

/* device structure -
 *
 *	The device structure is used to describe a device entity. A device
 *	is an entity that connects to, and is controlled by, a controller.
 */

struct	device {
	struct device	*nxt_dev;/* pointer to next dev on this ctlr */
	struct controller *ctlr_hd;	/* pointer to ctlr for this device */
	char		*dev_type;	/* device type			*/
	char		*dev_name;	/* device name			*/
	int		logunit;	/* logical unit	number		*/
	int		unit;		/* physical unit number		*/
	char		*ctlr_name;	/* controller name connected to */
	int		ctlr_num;	/* controller number for this device */
	int		alive;		/* See bit definitions below	*/
#ifndef __cplusplus
	void		*private[8];	/* reserved for device use	*/
#else
	void		*dprivate[8];	/* "private" is reserved word in C++ */
#endif
	void		*conn_priv[8];	/* Reserved for connected controller use */
	void		*rsvd[8];	/* reserved for future expansion */
};

/* Defines for device private structures */
#define perf private[1]

/* port structure - 
 *
 *	The port structure is used to contain information about a port.  A port
 *	is ??
 */

struct	port {
	int	(*conf)();		/* config routine for this port */
};

/* driver structure - 
 *
 *	The driver structure contains information about driver entry points
 *	and other driver-specific information.
 */

struct	driver {
	int	(*probe)();		/* see if a driver is really there */
	int	(*slave)();		/* see if a slave is there */
	int	(*cattach)();		/* controller attach routine */
	int	(*dattach)();		/* device attach routine */
	int	(*go)();		/* fill csr/ba to start transfer */
	caddr_t	*addr_list;		/* device csr addresses */
	char	*dev_name;		/* name of device which connects to */
					/* this controller		    */
	struct	device **dev_list;	/* backpointers to driver structs */
					/* indexed with device logunit    */
	char	*ctlr_name;		/* name of controller */
	struct	controller **ctlr_list;	/* backptrs to controller structs */
					/* indexed with controller number */
	short	xclu;			/* want exclusive use of bdp's */
	int	addr1_size;		/* size of first csr area */
        int	addr1_atype;	 	/* address space of first csr area */
	int	addr2_size;		/* size of second csr area */
        int	addr2_atype;	 	/* address space of second csr area */
	int	(*ctlr_unattach)();	/* controller unattach routine */
	int	(*dev_unattach)();	/* device unattach routine */
};

struct console_device {
	char	protocol[20];
	int	hose;
	int	slot;
	int	channel;
	int	remote_addr;
	int	unit;
	char	*boot_dev_type;
	char	*ctlr_dev_type;
};

struct dev_root {
	struct console_device *consdevice;
	int	unit;
};


#define DEV_CONSPROTO_LEN	40	/* length of console protocol name */
#define DEV_CONSUNIT_LEN	16	/* length of console "unit" name   */

typedef struct dev_console {
    struct device	*device;
    char                protocol[DEV_CONSPROTO_LEN];    /* protocol name */
    char                unitnm[DEV_CONSUNIT_LEN];       /* "unit" name */
    u_int               remoteid;           /* RemoteId specifier        */
    u_int               unit;               /* Unit specifier            */
} dev_console_t;

typedef struct {
    struct controller   *ctlr;
    char                protocol[DEV_CONSPROTO_LEN];    /* protocol name */
    char                unitnm[DEV_CONSUNIT_LEN];       /* "unit" name */
    u_int               remoteid;           /* RemoteId specifier        */
    u_int               unit;               /* Unit specifier            */
} ctlr_console_t;

struct protocol_struct 
{
    char protocol_name[16];		/* Name of protocol (ie. SCSI) */
    char disk_name[8];			/* What we call the device (ie. rz,ra,re) */
    uint major;				/* Major number for this device */
    int  flags;				/* Flags */
    struct protocol_struct *next_protocol; /* Next protocol struture that is supported */
    
};

/* Define flags for protocol_struct flags field */

#define	PP_NOIOCTL	0x00000001	/* Device does not have an ioctl routine */
#define	PP_NETBOOT	0x00000002	/* Device used for network booting */

/*
 * Structure argument for xxdump routines.
 */
struct dump_request {
	vm_offset_t	vaddr;		/* Address of data */
	struct	device	*device;	/* Where we get all our device info */
	daddr_t		part_offset;	/* Offset (blocks) into unit of partition start */
	daddr_t		part_size;	/* Size (blocks) of partition */
	dev_t		dev;		/* Current dump device */
	/*
	 * WARNING: Any device placed here must be able to be checked
	 * and opened (with interviening closes) multiple times with
	 * consistant results.  E.g.; if the volume manager functions
	 * substitute into the device field, subsequently opening
	 * either the original dev_t or the substitute must behave the
	 * same way.  On the other hand, such substitutions as can be
	 * made should be made, to aid in detection of multiple
	 * instances of the same partition in the dump list.
	 */
	u_int		count;		/* Number of blocks to write */
	u_int		blk_offset;	/* Offset into the partition at which to write */
	u_int		limit;		/* Max offset for this piece */
	u_int		remoteid;	/* RemoteId specifier for this device */
	u_int		unit;		/* Unit specifier for this device */
	u_short		command;	/* Control and state information */
	u_char		cur_piece;	/* Index in dumpinfo.piece of current partition */
	u_char		pri_piece;	/* Index in dumpinfo.piece of primary swap partition, or -1 */
	char		device_name[80];/* String to pass to prom open */
	char		protocol[40];	/* What type of protocol, SCSI, MSCP, MOP ect */
};
/* dump_request.command values */
#define DUMPREQ_BAD	0x0		/* Raise the alarm if dump_request used without further setup */
#define DUMPREQ_CHECK	0x1		/* Confirm that device is appropriate, alive, etc. */
#define DUMPREQ_OPEN	0x2		/* Device should be opened if device requires such */
#define DUMPREQ_WRITE	0x3		/* Device must have already been opened (in case appropriate) */
#define DUMPREQ_CLOSE	0x4		/* Close the device (if meaningful) */

/*
 * These are request for info calls through the cpusw function get_info.
 * This allows kernel code that needs system specfic code to request the 
 * info in a generic way without refering to cpu type.
 * CAUTION: documented device driver and kernel API; see comments below.
 */
	
struct item_list {
	u_long		function;		/* Function code for this item; see below for supported codes */
	u_int		out_flags;    		/* Flags for output data */
	u_int		in_flags;		/* Flags for input data */
	u_long		rtn_status;		/* Status for the function code */
	struct item_list *next_function;	/* Pointer to next function request */
	u_long		input_data;		/* Pointer to input data */
	u_long		output_data;		/* Pointer to output data */
};	

/*
 * Type of info that can be requested 
 *
 * CAUTION: documented device driver and kernel API; see comments below.
 */
#define NOT_SUPPORTED   0x0000				/* This request type is not supported or getinfo call is not */
#define INFO_RETURNED   0x0001				/* This request type is supported and returned data */
#define IN_LINE		0x0001				/* The data is contained in the item list structure */

/* CAUTION:
 *	get_info is a documented device driver and kernel layered product API.
 *	See comments after the last fucntion code.
 */
#define	TEGC_SWITCH	0x0001				/* return the address of the sw table for the TEGC driver */
#define	FBUS_INTREQ_REG	0x0002				/* return the address of the int request register for the machine */
#define MOP_SYSID	0x0003				/* MOP SYSID for a system */
#define GET_TC_SPEED	0x0004				/* Get the system Turbo-Channel speed */
#define CONSOLE_2_DEV	0X0005				/* Translate console boot device string into controller ect for us */
#define DEV_2_CONSOLE	0x0006				/* Compose dump string for console from our io data structures */
#define DEV_2_USER	0x0007				/* Return a the string a user would enter at the console to boot */
#define GET_810_SPEED	0x0008				/* Return 810 SCLK speed for known 810s */
#define GET_SLU_SPEED	0x0009				/* return clock speed for SLU devices */
#define GET_FLAGS	0x000a		/* Return system specific flags		*/
#define GET_UNIQUE_SYSID 0x000b		/* Return unique sysid			*/
#define CONSOLE_2_CTLR	0x000c				/* return controller struct for console device */
#define SECONDARY_CACHE_SIZE 0x000d			/* return secondary cache size */
#define	PWRMGR_CAPABLE 	0x000e				/* return Power Management capable */
#define	BYTEWORD_IO_CAPABLE 0x000f			/* platform supports byte/word IO and it's enabled */
#define MP_EV_NEEDED	0x0010				/* platform needs save_env executed on all processors */
#define GET_SYS_TEMP		0x0011			/* return system operating temperature */
#define GET_FAN_STATUS		0x0012			/* return system fan status */
#define GET_PS_STATUS		0x0013			/* return power supply status */
#define HIGH_TEMP_THRESHOLD	0x0014			/* return upper operating system temperature threshold */
#define VERIFY_CONSOLE_EV	0x0015	/* does this platform explicitly support the console EV you are  trying to access? */
#define OS_POWERDOWN            0x0016                  /* perform an o.s. powerdown */
#define	GET_SG_FLUSHPTR		0x0017			/* SG TLB flush function */
#define GET_SGMAP_CTL		0x0018			/* get scatter gather map control struct */
#define GET_HW_BUGS		0x0019			/* return bitmask of hardware bugs */
#define GET_FIRMWARE_REV	0x001a			/* return firmware revision information */
#define GET_PALCODE_REV		0x001b			/* return palcode revision information */
#define CHECK_MOTHERBOARD_SLOT	0x001c			/* on-board legacy ide? */
#define CTLR_2_CONSOLE		0x001d			/* compose dump string for console from out io data structures */
#define PLATFORM_IO_BIT		0x001e			/* return physical address bit used to denote I/O space by a platform */

#define MEM_ADDR_ALIGN          0x001f          /* memory address alignment */
#define SW_INTERLEAVE_REQUIRED  0x0020          /* platform requires software interleaving */
#define GET_MEM_BANK_COUNT      0x0021          /* return number of memory banks */
#define GET_MEM_BANK_SIZE       0x0022          /* return size (# MB) of a particular memory bank */
#define GET_MEM_BANK_BASE_PA    0x0023          /* return base phys addr of memory bank */

#define GET_BAD_PAGE_LIST	0x0024		/* return list of bad pages,  */
						/* (memory double bit ECC)    */
#define GET_PLATFORM_RESET_PTR	0x0025		/* return pointer to platform */
						/* hardware reset function.   */
#define GET_HALT_AFTER_PANIC	0x0026		/* return hardware platform's */
						/* halt_after_panic flag.     */
#define CHECK_IDE_LIMITS        0x0027          /* check if platform requires */
                                                /*  IDE speed throttling      */ 

/************************************************************************/
/* CAUTION: get_info is a documented device driver and kernel API.	*/
/*	Function codes must remain constant across OS releases.		*/
/*	Deleted codes must be marked RESERVED and not re-used.		*/
/*	V4.# stream - use codes 0x000 - 0x0ff.				*/
/*	V5.# stream - use codes 0x100 - 0x???.				*/
/************************************************************************/

/*
 * defines for CHECK_MOTHERBOARD_SLOT return data.
 */
#define CONFIG_MB_PCI_IDE		1
#define DONT_CONFIG_MB_PCI_IDE		0

/*
 * defines for CHECK_IDE_LIMITS return data
 *
 *      NOTE: These values are chosen to match
 *      the encoding used in sim_ata.h. If new
 *      IDE DMA rate values are added to the sim_ata
 *      driver, then they should also be reflected
 *      in this header file as well.
 */
#define IDE_PIO_0                       0x08
#define IDE_PIO_1                       0x09
#define IDE_PIO_2                       0x0a
#define IDE_PIO_3                       0x0b
#define IDE_PIO_4                       0x0c

#define IDE_SDMA_0                      0x10
#define IDE_SDMA_1                      0x11
#define IDE_SDMA_2                      0x12

#define IDE_MDMA_0                      0x20
#define IDE_MDMA_1                      0x21
#define IDE_MDMA_2                      0x22

#define IDE_UDMA_0                      0x40
#define IDE_UDMA_1                      0x41
#define IDE_UDMA_2                      0x42

/*
 * Macro to verify an input parameter that is
 * supposed to specify a valid IDE DMA rate.
 */
#define CHECK_IDE_DMA_RATE( rate )      \
   ( ((rate >= IDE_PIO_0)  && (rate <= IDE_PIO_4))  || \
     ((rate >= IDE_SDMA_0) && (rate <= IDE_SDMA_2)) || \
     ((rate >= IDE_MDMA_0) && (rate <= IDE_MDMA_2)) || \
     ((rate >= IDE_UDMA_0) && (rate <= IDE_UDMA_2)) )


/*
 * constants defined for BUGS reported by GET_HW_BUGS
 * start at bit 0 (1)  and then is a mask up to bit 63 (0x8000000000000000)
 */
#define HWBUG_NEED_EDGE 1

#ifdef _KERNEL
/*
 * Structure used to return MEM_ADDR_ALIGN information
 */
typedef struct mem_addr_align {
        vm_offset_t     ni_align;       /* QUAD-P memory alignment */
        int             ni_nodes;       /* number of QUAD-Ps */
} mem_addr_align_t;
#endif

/*
 * constants related to GET_810_SPEED function
 * (speeds are specified in terms of MHz * 100)
 */

#define PSIOP_810_SCLK_25MHz		2500
#define PSIOP_810_SCLK_32MHz		3200
#define PSIOP_810_SCLK_33MHz		3300
#define PSIOP_810_SCLK_40MHz		4000

/*
 * The PSIOP_810_BURST_DISABLE bit is passed in conjunction with the PSIOP 
 * clock speed as defined above as part of the GET_810_SPEED platform call
 * on certain platforms.  By default, the bit will be clear on platforms
 * that do not need to disable bursting on the on-board 810 device.
 */

#define PSIOP_810_BURST_DISABLE         0x100000000L

/*
 * constants related to GET_SLU_SPEED function
 */

#define SLU_SCC_PCLK_16Mhz		16*1000*1000	/* speed for scc devices clocked via PCLK at 16 Mhz */


#ifdef KERNEL
/*
 * These routines provide dynamic extensions to bus functionality.  They
 * are used to configure in loadable drivers and to register interrupt
 * handlers.
 */
struct bus_framework {
	int		(*ctlr_configure)();	/* Ctlr configure routine     */
	int		(*ctlr_unconfigure)();	/* Ctlr unconfigure routine   */
	int		(*adp_unattach)();	/* Bus remove adapter routine */
	int		(*config_resolver)();	/* Autoconfig bus resolver    */
        ihandler_id_t   (*adp_handler_add)();	/* Register interrupt	      */
        int             (*adp_handler_del)();   /* De-register interrupt      */
        int             (*adp_handler_enable)(); /* Enable interrupt handler  */
        int             (*adp_handler_disable)(); /* Disable interrupt handler*/
        int             (*badaddr_access)();    /* Bus specific badaddr routine */
        int             (*controller_configure)();      /* 4.0 driver configuration     */
        int             (*controller_unconfigure)();    /* 4.0 driver unconfigure       */
	int		(*request_resource)();	/* Request I/O resource		*/
	int		(*release_resource)();	/* Release I/O resource		*/
	caddr_t		rsvd[3];		/* Rsvd for future expansion  */
	caddr_t		private[8];		/* Reserved for driver use    */
};
#endif /* KERNEL */

/*
 * Loadable driver configuration data structure:
 *
 * After the stanza entry has been parsed to produce a bus, controller and
 * device lists, the elements of these lists are packaged up and passed down
 * to the kernel via setsysinfo.  In order to have a single form of setsysinfo
 * command the following structure is used to represent all of the different
 * types.  It consists of the structures themselves with an identifying type
 * and name fields.  The name field is needed so that you could have kernel
 * bus, ctlr, dev lists with these entries for different drivers.
 *
 * The bus, controller and device structures conatin pointers to names.  Such
 * as connecting bus name, connecting controller name, or port name.  In order
 * to make it easy to pass this structure to the kernel via setsysinfo, the
 * name fields will be copied into this structure and then the name pointers
 * within the bus/controller/device structures will be setup in the kernel
 * to point to these strings.
 */
#define MAX_NAME        100     	/* Maximum name length          */
struct config_entry {
	struct  config_entry *e_next;	/* Next entry in linked list    */
	char 	e_name[MAX_NAME];	/* Driver name 			*/
	int	e_type;			/* type = bus, ctlr, dev        */
	union {
		struct bus		e_bus;
		struct controller	e_controller;
		struct device		e_device;
	} e_str;
	char 	e_nm_1[MAX_NAME];	/* Name string			*/
	char 	e_nm_2[MAX_NAME];	/* Name string			*/
	char 	e_nm_3[MAX_NAME];	/* Name string			*/
	char 	e_nm_4[MAX_NAME];	/* Name string			*/
};

/* Bus type definitions	*/

#define	BUS_IBUS	1
#define	BUS_TC		2
#define	BUS_XMI		3
#define	BUS_BI		4
#define	BUS_UNIBUS	5
#define	BUS_QBUS	6
#define	BUS_VME	  	7
#define BUS_MSI		8
#define BUS_CI		9
#define BUS_LSB		10		/* laser system bus */
#define BUS_IOP		11		/* laser I/O adapter */
#define BUS_LAMB	12		/* laser to xmi adapter */
#define BUS_FLAG	13		/* laser to future bus adapter */
#define BUS_LBUS	14		/* cobra local I/O bus */
#define BUS_FBUS	15		/* future bus */
#define BUS_ISA		16		/* ISA bus. */
#define BUS_EISA	17		/* EISA bus. */
#define BUS_SCSI	18		/* SCSI buses */
#define BUS_PCI		19		/* PCI bus. */
#define BUS_PCMCIA	20		/* PCMCIA bus */
#define BUS_MCBUS	21		/* DEC4100 System Mem. bus */
#define BUS_USB		22		/* Universal Serial Bus */
#define BUS_I2O		23		/* I2O Subsystem */

/*
 * CTLR_TYPE is a bit field in the controller and bus structure's "type" field.
 * It is used as a flag in the badaddr routines (TC machines) that determines
 * the type of structure that is requesting the probe. Currently, the ptr passed into
 * the kn1xaa_badaddr routines is typecast to a bus or a controller before use.
 *             0 = Bus structure    1 = Controller Structure
 */
#define CTLR_TYPE       0x80000000      /* Not the bus, its a controller */


/* for the ADU */
#define BUS_TV          99


/* Access type definitions used for EISA and PCI bus */
#define	BUS_MEMORY	0
#define BUS_IO		1
#define DENSE_MEMORY    2

/* Alive field bit definitions */

#define	ALV_FREE	0x00000000	/* Device not yet processed  */
#define ALV_ALIVE	0x00000001	/* Device present and configured */
#define	ALV_PRES	0x00000002	/* Device present but no configed */
#define	ALV_NOCNFG	0x00000004	/* Device not to be configured	*/
#define	ALV_WONLY	0x00000008	/* Device is write-only		*/
#define	ALV_RONLY	0x00000010	/* Device is read-only		*/
#define ALV_LOADABLE	0x00000020	/* Device resolved by loadable */
#define ALV_NOSIZER	0x00000040	/* Sizer should ignore this item */
#define ALV_STATIC	0x00000080	/* Generate config_driver line	*/

/* Define various constants used in configuring of loadable drivers */

#define	NEXUS_NUMBER		(-1)

/* These are defined to configure 3.0 Loadable drivers */
#define LDBL_WILDNAME	"*"			/* Char field wildcard */
#define LDBL_WILDNUM		(-99)		/* Int field wildcard */

/* These are defined to configure a 1Binary 4.0 device driver */
#define DRIVER_WILDNAME	LDBL_WILDNAME
#define DRIVER_WILDNUM	LDBL_WILDNUM

/*
 * Module types.
 */
#define BOGUS_TYPE	0x0		/* Invalid type			  */
#define BUS_TYPE	0x1		/* Bus type			  */
#define CONTROLLER_TYPE	0x2		/* Controller type		  */
#define DEVICE_TYPE	0x4		/* Device type			  */

/*----------------------------------------------------*/
/* Defines and function prototypes for bus functions. */
/*----------------------------------------------------*/
#define	RES_MEM		0
#define	RES_IRQ		1
#define	RES_DMA		2
#define	RES_PORT	3

extern	void  do_config (struct controller *ctlr_p);
extern	int   get_config(struct controller *ctlr_p, uint_t config_item,
			 char *func_type, void *data_p, int handle);
extern	void  enable_option (struct controller *ctlr_p);
extern	void  disable_option(struct controller *ctlr_p);
extern io_handle_t busphys_to_iohandle(u_long addr, int flags, struct controller *ctlr_p);


/**********************************************/
/* Function prototypes for io access routines */
/**********************************************/

#define HANDLE_BYTE	0x1
#define HANDLE_WORD	0x2
#define HANDLE_LONGWORD 0x4
#define HANDLE_QUADWORD 0x8
#define HANDLE_TRIBYTE  0x10
#define HANDLE_DENSE_SPACE	0x80000000
#define HANDLE_SPARSE_SPACE	0x40000000
#define HANDLE_BUSPHYS_ADDR     0x20000000  
#define HANDLE_LINEAR_SPACE     0x10000000  

extern int io_copyin(io_handle_t src, vm_offset_t dst, u_long length);
extern int io_copyout(vm_offset_t src, io_handle_t dst, u_long length);
extern int io_copyio(io_handle_t src, io_handle_t dst, u_long length);
extern int io_zero(io_handle_t dst, u_long length);
extern u_long iohandle_to_phys(io_handle_t io_handle, long flags);
extern io_handle_t busphys_to_iohandle(u_long addr, int flags, struct controller *ctlr_p);
extern long read_io_port(io_handle_t dev_addr, int width, int type);
extern void write_io_port(io_handle_t dev_addr, int width, int type, long data);

/**********************************************/
/* Function prototypes for read/write_io_port */
/**********************************************/
/* extern	unsigned long read_io_port(vm_offset_t dev_addr, int width, int type); */
extern	void write_io_port(vm_offset_t dev_addr, int width, int type, long data);

/*----------------------*/
/* Macros for io access */
/*----------------------*/

#define READ_BUSIO_D8(a)   ((unsigned char)(read_io_port(a, 1, BUS_IO)))
#define READ_BUSIO_D16(a)  ((unsigned short)(read_io_port(a, 2, BUS_IO)))
#define READ_BUSIO_D32(a)  ((unsigned int)(read_io_port(a, 4, BUS_IO)))
#define READ_BUSIO_D64(a)  ((unsigned long)(read_io_port(a, 8, BUS_IO)))
#define READ_BUSMEM_D8(a)  ((unsigned char)(read_io_port(a, 1, BUS_MEMORY)))
#define READ_BUSMEM_D16(a) ((unsigned short)(read_io_port(a, 2, BUS_MEMORY)))
#define READ_BUSMEM_D32(a) ((unsigned int)(read_io_port(a, 4, BUS_MEMORY)))
#define READ_BUSMEM_D64(a) ((unsigned long)(read_io_port(a, 8, BUS_MEMORY)))
#define WRITE_BUSIO_D8(a,d)   ((void)(write_io_port(a, 1, BUS_IO, d)))
#define WRITE_BUSIO_D16(a,d)  ((void)(write_io_port(a, 2, BUS_IO, d)))
#define WRITE_BUSIO_D32(a,d)  ((void)(write_io_port(a, 4, BUS_IO, d)))
#define WRITE_BUSIO_D64(a,d)  ((void)(write_io_port(a, 8, BUS_IO, d)))
#define WRITE_BUSMEM_D8(a,d)  ((void)(write_io_port(a, 1, BUS_MEMORY, d)))
#define WRITE_BUSMEM_D16(a,d) ((void)(write_io_port(a, 2, BUS_MEMORY, d)))
#define WRITE_BUSMEM_D32(a,d) ((void)(write_io_port(a, 4, BUS_MEMORY, d)))
#define WRITE_BUSMEM_D64(a,d) ((void)(write_io_port(a, 8, BUS_MEMORY, d)))

/* io_handle_t versions */
#define READ_BUS_D8(a)   ((unsigned char) (read_io_port(a, 1, 0)))
#define READ_BUS_D16(a)  ((unsigned short)(read_io_port(a, 2, 0)))
#define READ_BUS_D32(a)  ((unsigned int)  (read_io_port(a, 4, 0)))
#define READ_BUS_D64(a)  ((unsigned long) (read_io_port(a, 8, 0)))
#define WRITE_BUS_D8(a,d)   ((void)(write_io_port(a, 1, 0, d)))
#define WRITE_BUS_D16(a,d)  ((void)(write_io_port(a, 2, 0, d)))
#define WRITE_BUS_D32(a,d)  ((void)(write_io_port(a, 4, 0, d)))
#define WRITE_BUS_D64(a,d)  ((void)(write_io_port(a, 8, 0, d)))


/* DMA SUPPORT -- structures, typedefs, define's	*/

/* bus-address/byte-count pair structure		*/
/* io bus addr. can be up to 64-bits, and byte-specific */
/* the byte count is signed 64-bits 			*/
struct	sg_entry {
	bus_addr_t	ba;	/* bus address                          */
	u_long		bc;	/* byte count from ma that contiguous
				   addresses are valid on the bus 	*/
};

typedef	struct sg_entry	*sg_entry_t;

/*
 * The sglist structure contains the control structure to access a
 * page of bus_address-byte_count pairs. The pointer to this structure
 * is passed back to drivers from dma_map_alloc() & dma_map_load().
 */
/*
 * If hw-sg resources are attached to a DMA transfer, they are found 
 * through the hw_sg_table_control struct.
 * The private field is used to hold the data used by dma_get/put_private. 
 */

 /*
  *	+----------------------------------+
  *	|               sgp		   |
  *	+----------------+-----------------+
  *	|   num_ents     |     val_ents    |   -> each line 64-bits
  *	+----------------+-----------------+   -> 80 bytes cache block
  *	|      flags     |      index      |   -> critical data in 1st
  *	+----------------+--------+--------+   -> 64 bytes (two 32-byte
  *	|		next		   |   -> cache blocks)
  * .---+----------------------------------+------------.
  * |	|		cntrlrp		   |   		V
  * V	+----------------------------------+    this section only added to
  *	|		va		   |	first sglist of babc list.
  *	+----------------+-----------------+      *** a struct ovrhd{} ***
  *	|       num      |      index      | \
  *	+----------------+-----------------+  > hw_sg_table_control struct
  *	|             table_base           | /
  *	+----------------------------------+
  *	|	     private_data   	   |	
  *	+----------------+-----------------+
  *	|		procp		   |
  *	+----------------------------------+
  *
  * So, a page of sglist's (256 structs) with assoc. pages of sg_entry's 
  * (512 per page, 8KB per pair, min.) will be able to describe 1GB (min.).
  */

struct	sglist	{
	sg_entry_t	sgp;	  /* ptr. to ba-bc pair (struct of)	 */
	int		val_ents; /* number of ba-bc pairs in babc list  */
	int		num_ents; /* loaded/valid ba-bc pairs in list    */
	int		index;	  /* last ba-bc pair read		 */
	int		flags;	  /* copy of flags from alloc/load	 */
	struct	sglist	*next;	  /* ptr. to next struct in linked list	 */
};

/*
 * This structure is used to contain information about allocated
 * hardware scatter/gather recources. The address of the table, the
 * index and the number of entries allocated live here. It is placed
 * in the ovrhd struct of a super-sglist structure. (See diagram above).
 */
struct hw_sg_table_control {
	u_int		index;		/* Index of allocated space in hw_sg table */
	u_int		num;		/* number of entries allocated */
	vm_offset_t	table_base;	/* base address of table */
};

struct ovrhd {
	struct  controller *cntrlrp;	/* requesting controller	*/
	vm_offset_t	    va;		/* saved va on dma_map_load	*/
	struct hw_sg_table_control hw_sg; /* hw sg control struct	*/
	u_long private_data;		/* used by dma_put/get_private  */
	struct	proc	   *procp;	/* proc ptr on dma_map_load	*/
};

/* Typedef for return value defs */
typedef	struct	sglist	*sglist_t;
typedef	struct	sglist	*dma_handle_t;

#ifdef KERNEL
/*
 * The dma_callsw structure contains pointers to the platform-dependent
 * functions that support drivers for DMA devices. The structure
 * is initialized by the platform-specific init function during bootstrap
 * (e.g., kn121_init() on JENSEN).
 * The generic functions are defined in locore.s and uses this jump
 * table (for now) to get to the platform-specific interfaces for these
 * functions.
 */

struct	dma_callsw	{
	u_long	(*hal_dma_map_alloc)();	  /* ptr to HAL's dma_map_alloc    */
	u_long	(*hal_dma_map_load)();	  /* ptr to HAL's dma_map_load     */
	int	(*hal_dma_map_unload)();  /* ptr to HAL's dma_map_unload   */
	int	(*hal_dma_map_dealloc)(); /* ptr to HAL's dma_map_dealloc  */
	int	(*hal_dma_min_bound)();   /* ptr to HAL's dma_min_boundary */
};
/*
 * dma_callsw defined in driver_support.c;
 * need this declaration for cpu-specific init modules-functions 
 */
extern	struct	dma_callsw	dma_callsw;

/*
 * The bus_bridge_dma_callsw structure contains pointers to the
 * bus bridge dma hardware mapping functionality used to do bus
 * mapping.
 */
struct  bus_bridge_dma_callsw      {
   unsigned long    (*dma_alloc)();
   unsigned long    (*dma_load)();
   int              (*dma_unload)();
   int              (*dma_dealloc)();
};



#endif	/* KERNEL */

/*
 * values for "flags" field in function calls, structures 
 */
#define	DMA_SLEEP	0x0001	/* SLEEP on dma_alloc/load call 	 */
#define DMA_RSVD_0002	0x0002	/* Reserved place holder		 */
#define DMA_RSVD_0004	0x0004  /* Reserved place holder		 */
#define DMA_HW_SG	0x0008  /* Hardware/Scatter gather alloacted	 */
#define DMA_GUARD_UPPER 0x0010  /* Add GUARD page at end of sg list	 */
#define DMA_GUARD_LOWER 0x0020  /* Add GUARD page at beg. of sg list	 */
#define DMA_ALL		0x0040  /* Get all resources req. or rtn failure */
#define DMA_RSVD_0080  	0x0080  /* Reserved place holder		 */
#define DMA_IN		0x0100	/* device to main/system/core data xfer	 */
#define DMA_OUT		0x0200	/* main/system/core mem. to device xfer  */
#define DMA_ADDR_LIMIT  0x0400  /* Address limited dma flag		 */
#define DMA_RSVD_0800   0x0800  /* Reserved place holder		 */
#define DMA_DEALLOC	0x1000	/* dealloc. resources on unload		 */
#define DMA_CONTIG      0x2000  /* Return only contiguous		 */
#define DMA_RSVD_4000   0x4000  /* Reserved place holder		 */
#define DMA_RSVD_PLTFRM 0x4000	/* i.d. that previous flag is used by
				   platform-specific dma code		 */
#define DMA_DIRECT_MAP	0x8000  /* bus bridge flag "sglist chain"        */
#define DMA_64BIT       0x10000 /* 64bit capable                         */

/*
 * Prototype defs for drivers
 */
/* the following are implemented in locore.s (for performance reasons) */
extern	u_long	dma_map_alloc(u_long bc, struct controller *cntrlrp, 
				dma_handle_t *dma_handle_p, int flags);
extern	u_long	dma_map_load(u_long bc, vm_offset_t va, struct proc *procp, 
	struct controller *cntrlrp, dma_handle_t *dma_handle_p, 
			              u_long max_bc, int flags);
extern	int	dma_map_unload(int flags, dma_handle_t dma_handle);
extern	int	dma_map_dealloc(dma_handle_t dma_handle);
extern	int	dma_min_boundary(struct controller *cntrlrp);
/* the following are in driver_support.c */
extern	sg_entry_t	dma_get_next_sgentry(dma_handle_t dma_handle);
extern	sg_entry_t	dma_get_curr_sgentry(dma_handle_t dma_handle);
extern	int		dma_put_prev_sgentry(dma_handle_t dma_handle, sg_entry_t sg_entryp);
extern	int		dma_put_curr_sgentry(dma_handle_t dma_handle, sg_entry_t sg_entryp);
extern	vm_offset_t	dma_kmap_buffer(dma_handle_t dma_handle, u_long offset);
extern	int		dma_get_private(dma_handle_t dma_handle, int index, 
						u_long *data);
extern	int		dma_put_private(dma_handle_t dma_handle, int index,
						u_long data);
extern	dma_map_info_t  dma_get_maps(struct bus *busp);
extern	int		dma_get_sgentry_reset(dma_handle_t dma_handle);
extern	int		dma_get_num_val_sgentrys(dma_handle_t dma_handle);
extern	void		drvr_shutdown();
extern	void		drvr_register_shutdown(void (*callback)(), 
					       caddr_t param, 
					       int flags);

extern	void		drvr_saveterm();
extern	void		drvr_register_saveterm(void (*callback)(), 
					       caddr_t param, 
					       int flags);
extern	void		drvr_flush();
extern	void		drvr_register_flush(void (*callback)(), caddr_t param, 
					       int flags);
extern struct device * get_device_next( struct device *);
extern struct controller * get_controller_next( struct controller *);
extern struct bus * get_bus_next( struct bus *);


/*
 * DMA Map support macros
 */
#define	DMA_MAP_BUF(A,B,C,D,E,F,G)	((u_long)dma_map_load(A, B, C, D, E, F, G))
#define	DMA_UNMAP_BUF(A)		((int)dma_map_dealloc(A))

#ifdef KERNEL
/************************************************************************/
/*									*/
/* Generic I/O Resource Management -- structures, typedefs, define's 	*/
/*  									*/
/************************************************************************/

/* 
 * Request/Release  I/O or memory space parameter structure
 */

struct io_mem_req_t {
    io_handle_t		baseaddr;	/* I/O port base address or memory */
					/* space base address		   */
					 
    u_long		numbytes;	/* Number of contiguous bytes	   */ 
					/* requested for I/O or Mem space  */
					 
    u_long		alignment;	/* alignment requirement flag      */

    caddr_t		bus_param;	/* Bus-specific parameter if necessary 	*/

    void		*reserved;	/* Reserved for future expansion	*/
}; 

/* 
 * Request/Release interrupt parameter structure
 */

struct intr_req_t {
    long	       	intr_num;	/* assigned INTR number being returned 	*/

    u_long		req_intr;	/* requested INTR or INTR bit mask 	*/
                                        /* indicating multiple choice INTR 	*/
                                        /* selection				*/
    u_long		intr_flags;	/* Bit flags field to indicate 		*/
                                        /* interrupt request options		*/
    caddr_t		bus_param;	/* Bus-specific parameter if necessary  */
};

/* 
 * Handle type for opaque use with machine dependent I/O resource
 * management routines -- this field is returned by the resource
 * management routine to the client and used as input to the resource
 * release routine to release a particular resource instance.
 */
typedef char * res_handle_t;

/* 
 * This structure is used as an argument/parameter block to be passed to
 * the resource management function interface.  Depending on the resource 
 * type being requested, different fields are utilized.  The beginning 
 * part of the structure is used for common fields for all types.
 */
struct resource_blk {

    /* common fields for all resource types */

    u_long	resource_type;		/* Type of resource requested		*/
    caddr_t	bus_ctlr_p;	    	/* Pointer to bus/controller struct    	*/
    u_int 	caller_type;	    	/* Caller type, BUS or CTLR            	*/
    u_int	flags;		    	/* bit flags field to indicate options 	*/
    struct bus  *busptr;		/* Bus ptr to use in dispatching calls  */

    caddr_t	req_param;		/* Generic pointer to a resource-type	*/
                                        /* specific request structure		*/

    res_handle_t resource_handle;	/* handle ID returned by resource mgmt	*/
                                        /* routine(s)				*/
    void	*reserved[8];	    	/* Reserved for future expansion 	*/
       
};

/* Defines for caller type */
#define RES_BUS_TYPE			0x01
#define RES_CONTROLLER_TYPE		0x02

/* 
 * Defines for "flags" field -- flags field is used to indicate
 * various options for the function call
 */
#define RES_SHARABLE	0x00000001	/* This resource may be shared 		*/

/* 
 * This is a special flag indicating that the resource being requested
 * is a permanent/static one which is never deallocated.
 * This flag is used for I/O resources for static devices that are
 * probed during the boot.
 */
#define RES_PERMANENT	0x80000000	

/*
 * Defines for interrupt request flags field
 */
#define RES_INTR_MASK	0x00000001	/* INTR requested is specified as bit mask */

/*
 * Defines for alignment field 
 */
#define RES_NO_ALIGN		0x0000		/* No alignment requirement */
#define RES_ALIGN_BYTE		0x0001		/* Byte alignment */
#define RES_ALIGN_WORD		0x0002		/* Word alignment */
#define RES_ALIGN_LONGWORD	0x0004		/* Longword alignment */
#define RES_ALIGN_QUADWORD	0x0008		/* Quadword alignment */
#define RES_ALIGN_OCTAWORD	0x0010		/* Octaword alignment */
#define RES_ALIGN_4K		0x1000		/* 4K alignment */
#define RES_ALIGN_8K		0x2000		/* 8K alignment */
#define RES_ALIGN_16K		0x4000		/* 16K alignment */
#define RES_ALIGN_32K		0x8000		/* 32K alignment */
#define RES_ALIGN_64K		0x10000		/* 64K alignment */
#define RES_ALIGN_PAGE		0xffffffff 	/* Alpha-page alignment */


/*
 * Defines for IRQ request bit mask
 */
#define RES_IRQ0		0x0001	
#define RES_IRQ1		0x0002
#define RES_IRQ2		0x0004
#define RES_IRQ3		0x0008
#define RES_IRQ4		0x0010
#define RES_IRQ5		0x0020
#define RES_IRQ6		0x0040
#define RES_IRQ7		0x0080
#define RES_IRQ8		0x0100
#define RES_IRQ9		0x0200
#define RES_IRQ10		0x0400
#define RES_IRQ11		0x0800
#define RES_IRQ12		0x1000
#define RES_IRQ13		0x2000
#define RES_IRQ14		0x4000
#define RES_IRQ15		0x8000

/*
 * Defines for resource types -- use the same defines as the ones
 * defined for bus functions above
 *
 * #define	RES_MEM		0      	 Memory space block 
 * #define	RES_IRQ		1	 Interrupt number 
 * #define	RES_DMA		2	 DMA resource  -- TBD 
 * #define	RES_PORT	3	 I/O space block 
 */

/*
 * Defines for return code
 */
#define RES_SUCCESS		0x00	/* Successful operation */
#define RES_FAILURE		0x01   	/* Failed operation */
#define RES_INV_PARAM		0x02   	/* Invalid parameter passed */
#define RES_IN_USE		0x03   	/* Requested resource already in use */
#define RES_EXHAUSTED		0x04   	/* Out of resource for the specified type */
#define RES_NO_SHARE		0x05   	/* This resource cannot be shared */
#define RES_NOT_SUPPORTED 	0x06	/* This request/feature is not supported */


/*
 * Resource handle ID structure
 *
 * (Note: We may want to put this struct in a separate .h file ????)
 *
 * This structure is allocated when a new I/O resource is reserved via
 * request_resource() call.  The purpose of this structure is to contain
 * all the information needed to dispatch off to the bus specific implementation
 * of release_resource().  The bus pointer is needed to get to the
 * correct routine pointed to by the bus framework.  
 */

struct resource_key {
    struct resource_key	*next;		/* Pointer to next entry */
    struct resource_key *prev;		/* Pointer to prev entry */
    struct bus		*bus;		/* Pointer to bus structure */
    res_handle_t	bus_res_id;	/* Bus specific resource handle */
    lock_data_t		lock;		/* MP lock */
};


/*
 * Function prototypes
 */

extern int request_resource(struct resource_blk *info_ptr);
extern int release_resource(res_handle_t resource_handle);




/*
 * I/O resource linked lists to keep track of used and unused resources
 * in the system at any given time.
 *
 * Each system should declare one global lock for each type of system
 * resources.  Within a linked list of resource elements, there is one
 * lock for each element.
 *
 * Each system should also declare one used list head for each I/O resource type.
 */

struct res_handle_list {
        struct res_handle_list	*next;		/* Pointer to the next resource handle if */
	                                        /* this is a shared resource		  */
	                                        /* NULL if not a shared resource, or if	  */
	                                        /* this is the last shared entry	  */
	caddr_t		resource_ptr;		/* Pointer to this resource's entry in the*/
	                                        /* linked list of resources		  */

	u_long		resource_type;		/* Indicates which resource list to look  */
};

struct io_mem_list {
        struct io_mem_list	*next;		/* Pointer to next I/O or memory element  */
        struct io_mem_list	*prev;		/* Pointer to prev.I/O or memory element */
	io_handle_t		baseaddr;	/* starting address of I/O or memory blk */
	u_long			numbytes;	/* Number of contiguous bytes in this blk */
	u_int			is_shared;	/* 1 if this resource is shared */
	int			count;		/* Number of currently sharing clients, */
	                                        /* defaults to 1			   */
	struct res_handle_list	*res_handle;	/* client handle ID linked list for this resource */ 
        lock_data_t		lock;		/* MP lock 			   */
};

struct intr_list {
       struct intr_list		*next;		/* Pointer to next INTR element 	*/
       struct intr_list		*prev;		/* Pointer to prev. INTR element */
       int			intr;		/* INTR number 			*/
       u_int			is_shared;	/* 1 if this INTR is shared	*/
       int			count;		/* Number of currently sharing clients, */
                                                /* defaults to 1		   */

       int			reserved;	/* place holder for alignment 	*/
       struct res_handle_list	*res_handle;	/* client handle ID linked list for this resource */ 
       lock_data_t		lock;		/* MP lock			*/
};

/*
 * Defines for the "is_shared" field 
 */
/* defined earlier in this file */
/* #define RES_SHARABLE	0x1	*/
/* #define RES_PERMANENT 0x80000000 */

#define RES_IS_SHARED	0x2	/* This resource is shared currently */

/*
 * generic lock MACROs for I/O resource locks
 */
#define LOCK_RSRC(lock)		   lock_write(&lock)
#define UNLOCK_RSRC(lock) 	   lock_done(&lock)

#define LOCK_RSRC_ENTRY(entry)     lock_write(&(entry->lock))
#define UNLOCK_RSRC_ENTRY(entry)   lock_done(&(entry->lock))

#define INIT_RSRC_ENTRY(entry, lockinfo) lock_setup(&(entry->lock),\
					            lockinfo, TRUE)
/*
 * Define the data structures that the platform code fills in which
 * allows the common init code to properly reserve the required space
 * and IRQs for platform.
 */

struct mapout_address
    {
	long start;
	long size;
    };

struct mapout_info
    {
	u_long intr_mask;
	struct mapout_address *mapout_io;
	struct mapout_address *mapout_mem;
    };

/*
 * Define the constants the the platform code uses to tell the common
 * code which bus type the request is being nade for
 */
#define RESOURCE_ISA 0
#define RESOURCE_PCI 1

#endif	/* KERNEL */ 


/* Defines for server management's environmental monitor return status 
** from the platform's get_info() interface
*/
#define ENV_STATUS_OK   0
#define ENV_STATUS_FAIL 1
#define ENV_TEMP_STATUS_OK   -1
#define ENV_TEMP_STATUS_FAIL -2


/* Structure for driver shutdown/flush routine callback */
struct drvr_shut {
	struct drvr_shut	*next;
	void			(*callback)();	/* callback routine */
	caddr_t			param;
};
	
#define	DRVR_REGISTER	0x00000001	/* register a callback routine */
#define	DRVR_UNREGISTER	0x00000002	/* de-register a callback routine */

/* Driver Configuration defines for 4.0 support */
#define CTLR_CONFIG_REVISION 0     /* devdriver.h */
#define DEVICE_CONFIG_REVISION 0   /* devdriver.h */
#define CTLR_INDEX 1024
#define BUS_INDEX 32
#define DEVICE_INDEX 300
#define MAX_BUS_INDEX (BUS_INDEX -1)
#define MAX_CTLR_INDEX (CTLR_INDEX -1)
#define MAX_DEVICE_INDEX (DEVICE_INDEX -1)
#define NAME_SIZE_REG 30

/* Driver Configuration support for registering Hardware Topology
 * structures in the kernel.
 */


/*
 * bus_config structure's field definitions
 *
 * Revision  - is the version of the bus_config structure. The defines
 *             a device driver developer would use here are defined in devdriver.h
 *             by digital.
 * subsystem_name - is the configuration name of the driver. This is the name that
 *                  is used to configure identify and name the .mod.
 * bus_name  - is the name of the bus this driver can be configured into. This will
 *             be wild carded in the initial design. Since subsystem names of
 *             device drivers are unique across  busses, bus autoconfiguration by
 *             definition will not configure this bus unless one is
 *             found.
 * confl1()  - Pointer to adapter's confl1 configuration interface
 * confl2()  - Pointer to adapter's confl2 configuration interface
 */
struct bus_config {
       long    revision;
       char    subsystem_name[NAME_SIZE_REG];
       char    bus_name[NAME_SIZE_REG];
       int     (*confl1)();
       int     (*confl2)();
};

/*
 * device_config structure's field definitions
 *
 * Revision  - is the version of the device_config structure. The #defines
 *             a device driver developer would use here are defined in devdriver.h
 *             by digital.
 * subsystem_name - is the configuration name of the driver. This is the name that
 *                  is used to configure identify and name the .mod.
 * bus_name  - is the name of the bus this driver can be configured into. This will
 *             be wild carded in the initial design. Since subsystem names of
 *             device drivers are unique across  busses, bus autoconfiguration by
 *             definition will not configure this device into a bus unless one is
 *             found.
 * devdriver - is a pointer to the driver's devdriver structure.
 */
struct device_config {
       long    revision;
       char    device_type[NAME_SIZE_REG];
       char    device_name[NAME_SIZE_REG];
       char    controller_name[NAME_SIZE_REG];
       int     phys_unit_num;
       int     logical_unit_number;
       int     controller_num;
};


/*
 * Controller_config structure's field definitions
 *
 * Revision  - is the version of the controller_config structure. The defines
 *             a device driver developer would use here are defined in devdriver.h
 *             by digital.
 * subsystem_name - is the cfgmgr configuration name of the driver. This is the name that
 *                  is used to configure identify and name the .mod. This name
 *                  should match the driver name in the option data entry for a
 *                  device driver.
 * bus_name  - is the name of the bus this driver can be configured into. This will
 *             be wild carded in the initial design. Since subsystem names of
 *             device drivers are unique across  busses, bus autoconfiguration by
 *             definition will not configure this device into a bus unless one is
 *             found.
 * devdriver - is a pointer to the driver's devdriver structure.
 */
struct controller_config {
       long    revision;
       char    subsystem_name[NAME_SIZE_REG];
       char    bus_name[NAME_SIZE_REG];
       struct  driver * devdriver;
};




/* External routine definitions */

#ifdef KERNEL
extern struct bus 		*get_sys_bus();
extern struct bus 		*get_bus();
extern struct bus 		*get_bus_by_name();
extern struct bus 		*bus_search();
extern struct controller	*get_ctlr();
extern struct controller	*ctlr_search();
extern struct device		*get_device();
extern void			conn_ctlr();
extern void			conn_device();
extern void	 		conn_bus();
/* in Alpha at least, these are macros */
#ifndef __alpha
extern int			BADADDR();
extern int			DELAY();
#endif /* __alpha */
/* DMA memory allocation support routines */
extern	sg_entry_t	dma_alloc(unsigned int size, int flags);
extern	sglist_t	dma_alloc_super_sglist(int flags);
extern	sglist_t	dma_alloc_sglist(int flags);
extern	sglist_t	dma_struct_alloc(long num_ents, int flags);
extern	void		dma_free(unsigned int size, sg_entry_t addr, int flags);
extern	void		dma_free_super_sglist(sglist_t addr);
extern	void		dma_free_sglist(sglist_t addr);
/* Disk "default" partition map routine */
#include <io/common/devio.h>
#include <sys/disklabel.h>
extern	int		get_def_partitionmap(register DEVGEOMST *geom,
                               register struct pt_tbl *pmap);
#endif /* KERNEL */

/* WBFLUSH define. */
#ifdef __alpha
#      define WBFLUSH()  mb()
#      define MB()       mb()
#else
#  ifdef __mips
#      define WBFLUSH()  wbflush()
#      define MB()       ;
#  else
#      define WBFLUSH()  ;
#      define MB()       ;
#  endif /* __mips */
#endif /* __alpha */


#ifdef __cplusplus
}
#endif
#endif /* DEVDRIVER_HDR */
