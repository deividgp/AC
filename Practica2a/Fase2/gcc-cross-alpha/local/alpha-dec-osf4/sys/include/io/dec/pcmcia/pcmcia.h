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
 * @(#)$RCSfile: pcmcia.h,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 1996/09/05 19:15:39 $
 */

#ifndef _PCMCIA_H_
#define _PCMCIA_H_

/****************************************************************/
/*								*/
/* MODULE NAME: pcmcia.h					*/
/*								*/
/* LOCATION:  /src/kernel/io/dec/pcmcia				*/
/*								*/
/* DESCRIPTION:							*/
/* 	Contains common definitions for the PCMCIA bus adapter	*/
/*	interface.						*/
/*								*/
/* STRUCTURES:							*/
/*	pcmcia_sw	PCMCIA switch table for hardware 	*/
/*			dependent functions			*/
/*								*/
/*	pcmcia_bus_adapt 	PCMCIA adapter specific 	*/
/*				data structure			*/
/****************************************************************/

#include <sys/types.h>
#include <io/common/handler.h>		/* for handler_* decl's */
#include <io/common/devdriver.h>	/* for I/O resource mgmt decl's */


/************************************************************************/
/* Maximum number of sockets per adapter and adapters per system	*/
/*									*/ 
/* Although theoretically max. number of PCMCIA adapters can be 255	*/
/* (byte count size), we will limit it to 2 for now.  Similarly,	*/
/* we will limit the number of sockets per adapter to be 4 for now.	*/
/* The theoretical maximum is 16 sockets per adapter.			*/
/*									*/
/* IF WE EVER NEED TO INCREASE THESE NUMBERS, change the definitions	*/
/* below.								*/
/************************************************************************/

#define PCMCIA_MAX_ADAPTERS	2
#define PCMCIA_MAX_SOCKETS	4


/* Common serial line COM port addresses */

#define COM1	0x3f8
#define COM2	0x2f8
#define COM3	0x3e8
#define COM4	0x2e8
#define COM_IOSIZE 8		/* length of I/O block in COM port */

/* window into attribute memory space to read Card Information Structure data */
#define CFSIZE 4096		/* size of buffer to hold CIS data */

/*
 * common defines for PCMCIA routines
 */
#define PCMCIA_SUCCESS	0
#define PCMCIA_FAILURE	1

/****************************************************************/
/* PC Card option data structure which contains information     */
/* on PC Card options that may be installed on a system.	*/
/* The options are listed in /etc/sysconfigtab database.	*/
/****************************************************************/

#define MANUFACT_NAMELEN    31
#define PRODUCT_NAMELEN	    31
#define DRIVER_NAMELEN	    15

#define CALL_HANDLER 0x1		/* call handler flag */


struct pcmcia_option {
    u_char 	manufact_name[MANUFACT_NAMELEN+1];
                                        /* Manufacturer name string 	*/
    u_char	product_name[PRODUCT_NAMELEN+1];
                                        /* Product name string		*/
    u_short	manufact_ID;		/* Manufacturer ID in Manufacture ID tuple */
    u_short	card_revision;		/* Card's revision/part # found in Manufacture ID tuple */
    u_int	func_code;		/* Card function code, found in Function ID tuple */
    u_char	driver_name[DRIVER_NAMELEN+1];
                                        /* Card driver's name		*/
    u_char	loadable_flag;		/* If set, driver is loadable 	*/
    u_char	unload_flag;		/* If set, driver should be unloaded 	*/
                                        /* when the corresponding PC Card is 	*/
                                        /* ejected from the socket.  This field */
                                        /* is valid only for loadable driver	*/
    u_char	intr_handler_flag;	/* Call interrupt handler flag */
    char	type;			/* Driver type, C = ctlr, 	*/
                                        /* A = Adapter, D = Device	*/  
    int		(*adpt_config)();	/* Adapter config routine to call */
    
    u_char	man_name_mo_flag;	/* Match-on flag for Manufacturer name field */
    u_char	prd_name_mo_flag;	/* Match-on flag for Product name field */
    u_char	mid_mo_flag;		/* Match-on flag for Manufacturer ID field */
    u_char	card_rev_mo_flag;	/* Match-on flag for Card revision field */

};


/*********************************************************/
/* PCMCIA Switch Table for hardware dependent functions. */
/*********************************************************/

struct	pcmcia_sw {
    void (*enable_option)();	/* Func for enabling option interrupts  */
    void (*disable_option)();	/* Func for disabling option interrupts */

    io_handle_t sparse_io_base; /* io_handle for sparse io base address */ 
    io_handle_t sparse_mem_base;/* io_handle for sparse memory base address */
    io_handle_t dense_mem_base; /* io_handle for dense memory base address  */
    vm_offset_t (*busphys_to_iohandle)(); /* Fnc to return io handle    */

    int	(*adpt_config)();	/* bus-adapter config routine     	*/
    int (*confl1)();		/* adapter-specific confl1 routine	*/
    int (*confl2)();		/* adapter-specific confl2 routine	*/

    int (*request_resource)();	/* Request I/O resource routine		*/
    int (*release_resource)();	/* Release I/O resource routine		*/
    
    ihandler_id_t (*handler_add)(); /* Function for installing an ISR	*/
    int (*handler_enable)();	/* Function for enabling an interrupt	*/
    int (*handler_disable)();	/* Function for disabling an interrupt	*/
    int (*handler_del)();	/* Function for removing an ISR		*/
    dma_map_info_t (*dma_get_maps)();	/* Function to get dma windows info */

    /* Socket Services Function Entry Points starts here */

    int (*setup_io_window)();		/* Set up I/O window */
    int (*setup_mem_window)();		/* Set up memory window */
    int (*disable_io_window)();		/* Disable I/O window */
    int (*disable_mem_window)();	/* Disable memory window */
    int (*reset_socket)();		/* Reset socket */
    int (*setup_socket)();		/* Set up socket */
    int (*enable_scint)();		/* Enable status change interrupt */
    int (*disable_scint)();		/* Disable status change interrupt */
    int (*enable_fnc_irq)();		/* Enable PC Card functional interrupt */
    int (*disable_fnc_irq)();		/* Disable PC Card functional interrupt */
    int (*read_cis)();			/* Read the card's CIS structure */
    int (*map_attribute_memory)();	/* Map the card's attribute memory */
   
};


/********************************************************/
/* PCMCIA adapter specific data structure -- 		*/
/*							*/
/* 	There is one instance of this structure for 	*/
/*	each PCMCIA adapter.				*/
/*	The bus structure will be pointing to this	*/
/*	structure via 'private[4]' field.		*/
/********************************************************/

#define pcmcia_ptr	private[4]

struct pcmcia_bus_adapt {

    struct bus	*bus;			/* bus struct of this adapter */
    int		adpnum;			/* PCMCIA adapter number */
    int		num_sockets;		/* number of sockets in this adapter */
    struct socket_info *socket_list;	/* pointer to sockets connected to this adapter */

    io_handle_t io_addr;		/* I/O base address of adapter */ 
    io_handle_t mem_base;		/* sparse memory space base address */
    
    ihandler_id_t     *handler_key;	/* management interrupt handler key */ 
    void *adp_private[8];		/* adapter private data area */
    void *	handler_ptrs;		/* Holds pointer to our handlers */
    int         irq_info;               /* Holds our IRQ information */
};


/****************************************************************/
/* Socket information structure --				*/
/*								*/
/*	This structure contains information about a socket	*/
/* 	in a PCMCIA adapter.  					*/
/****************************************************************/
struct pcm_callback {
			struct pcm_callback *next;	/* forward pointer */
			int event;
			void (*function)();
			unsigned long argument;
			int callback_seen; /* facilitates generating card detect callbacks */
					/* for cards which are present when callback */
					/* is registered */
			int is_ccm;	/* registered by the ccm */
			int scanning_flag;	/* 1=callback scanned in current scan */
};

#define	EVENT_LIST_SIZE	10

#define socket_info_ptr	conn_priv[0]		/* in controller structure 		*/
#define handler_id	conn_priv[1]		/* in controller structure 		*/
#define card_info_ptr	conn_priv[2]		/* in controller structure, used to	*/
                                                /* info about the card to card driver   */ 


struct socket_info {

    struct controller *ctlr;		/* ptr. to card's controller struct */
    struct socket_info *nxt_socket;	/* ptr. to next socket on this adapter */
    struct pcmcia_bus_adapt *adapt;	/* ptr. to the adapter structure */
    struct pcmcia_option *card_option;	/* ptr. to the card option struct. */
    
    int		card_in;		/* a card is in the socket flag */
    int		card_devtype;		/* device type of current card in socket */
    int		card_func;		/* function code of current card */    
    int		socket_pnum;		/* real socket # unique to this adapter */
    int		socket_vnum;		/* virtual socket # unique to the system */
    int		socket_state;		/* current state of the socket		*/
    
    u_long	config_reg_addr;	/* configuration register base address */

    u_long	io_addr[2];		/* start address of I/O block */
    int		io_length[2];		/* length of the card's I/O block */ 
    int		irq_num;		/* IRQ # being used for current card */
    int		socket_irq;		/* IRQ # used for socket mgmt interrupts */
    int		mem_size;		/* Size of the memory space used */
    u_long	mem_start_addr;		/* Start of ISA memory space used for this card */

    long	com_mem_size[2];	/* Size of the Common Memory Space mapped */
    u_long	com_mem_start_addr[2];	/* Start of the Common Memory Space mapped */

    ihandler_id_t *handler_key;		/* handler key returned for this card */

    res_handle_t attr_resource_key;	/* Attribute Memory resource key returned for this socket */
    res_handle_t irq_resource_key;	/* IRQ resource key returned for this card */

    res_handle_t io_resource_key[2];	/* I/O port resource key returned for this card */

    res_handle_t mem_resource_key[2];	/* Memory resource key returned for this card */
    
    u_char	*cis_data;		/* pointer to the CIS data for current card */
    
    decl_simple_lock_data(,callback_queue_lock)
    decl_simple_lock_data(,event_queue_lock)
    decl_simple_lock_data(,register_lock)
    struct pcm_callback *callback_queue;	/* event callback requests */
    int next_event_to_process;
    int next_event_to_fill;
    int events[EVENT_LIST_SIZE];	/* event_list is a circular list */
					/* an entry is considered empty iff event # is 0. */
					/* EVENT_LIST_SIZE -1 to 0; */
					/* empty when event[next_process]==0 */
					/* full when event[next_fill] != 0 */
};

/*
 * Data structure passed to the PC Card's driver's probe() via 
 * controller->conn_priv[2] field (== card_info_ptr)
 */

struct card_info {
    int		socket_vnum;		/* Virtual socket # unique in the system */
    int		irq_num;		/* IRQ # being used for current card	 */
    int		io_length[2];		/* length of the card's I/O port block	 */
    u_long	io_addr[2];		/* start address of I/O port block	 */
    long	com_mem_size[2];	/* size of the Common Memory Space mapped*/
    u_long	com_mem_start_addr[2];	/* start of the Common Memory Space mapped */
    u_long	config_reg_addr;	/* configuration register base address   */
};

/*
 * DEFINES for socket info structure fields 
 */
#define CARD_IN		0x1		/* card is in the socket */
#define CARD_OUT	0x0		/* socket is empty */

/* 
 * DEFINES for generic IRQ #s
 */
#define PCMCIA_IRQ0	0		/* IRQ 0 */
#define PCMCIA_IRQ1	1		/* IRQ 1 */
#define PCMCIA_IRQ2	2		/* IRQ 2 */
#define PCMCIA_IRQ3	3		/* IRQ 3 */
#define PCMCIA_IRQ4	4		/* IRQ 4 */
#define PCMCIA_IRQ5	5		/* IRQ 5 */
#define PCMCIA_IRQ6	6		/* IRQ 6 */
#define PCMCIA_IRQ7	7		/* IRQ 7 */
#define PCMCIA_IRQ8	8		/* IRQ 8 */
#define PCMCIA_IRQ9	9		/* IRQ 9 */
#define PCMCIA_IRQ10	10		/* IRQ 10 */
#define PCMCIA_IRQ11	11		/* IRQ 11 */
#define PCMCIA_IRQ12	12		/* IRQ 12 */
#define PCMCIA_IRQ13	13		/* IRQ 13 */
#define PCMCIA_IRQ14	14		/* IRQ 14 */
#define PCMCIA_IRQ15	15		/* IRQ 15 */


struct pcmcia_function_switch {
	int (*  register_event_callback)();
	int (*unregister_event_callback)();
	int (*get_first_tuple)();
	int (*get_next_tuple)();
	int (*get_tuple_data)();
	int (*tuple_parse)();
	int (*map_common_memory_window)();
	int (*read_configuration_register)();
	int (*write_configuration_register)();
	int (*request_common_memory_window)();
	int (*release_common_memory_window)();
};

#define CARD_REMOVAL_EVENT 1
#define CARD_INSERTION_EVENT 2
#define CARD_READY_EVENT 3

#endif	/* _PCMCIA_H_ */
