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
 * @(#)$RCSfile: usbd.h,v $ $Revision: 1.1.10.3 $ (DEC) $Date: 1998/11/29 14:18:21 $
 */
#ifndef _USBD_H_
#define _USBD_H_

#include <sys/malloc.h>
#include <io/common/devdriver.h>
#include <io/dec/usb/usb.h>
#include <io/dec/usb/usbdi.h>

/*
 * This file contains structures and defines used by the USBD, HCI, and HUB
 * modules of the Universal Serial Bus Driver for DIGITAL UNIX.
 * 
 * This file will not be available as source.
 */

/*
 * Allows identificaton of USBDI Handles
 */
typedef enum usbd_handle_type {
    USBD_UNINITIALIZED_HANDLE_TYPE,
    USBD_BUS_HANDLE_TYPE,
    USBD_DEVICE_HANDLE_TYPE,
    USBD_INTERFACE_HANDLE_TYPE,
    USBD_PIPE_HANDLE_TYPE,
    USBD_REQUEST_HANDLE_TYPE,
    USBD_ENDPOINT_HANDLE_TYPE,
    USBD_HUB_HANDLE_TYPE,
    USBD_FUNCTION_HANDLE_TYPE
} USBD_HANDLE_TYPE;

/*
 * Doubly linked list
 */
typedef struct list_entry {
    struct list_entry *flink;
    struct list_entry *blink;
} LIST_ENTRY;

/*
 * Generic array descriptor.
 */
typedef struct usbd_array_descriptor {
    int sizeof_struct;
    void **array;
    LIST_ENTRY available;
    LIST_ENTRY used;
    int available_count;
    int used_count;
    int increment_count;
    lock_data_t lock;
} USBD_ARRAY_DESCRIPTOR;

/*
 * usbd_descriptor_header must be included first
 * in all structures which use the usbd_array_descriptor
 * above.
 */
typedef struct usbd_descriptor_header {
    LIST_ENTRY l;
    struct usbd_array_descriptor *array_desc;
    U32 index;
    U32 flags;
#define USBD_DESC_AVAILABLE 0x0
#define USBD_DESC_USED      0x1
} USBD_DESCRIPTOR_HEADER;


/*
 * struct usbd_sw - defines the interface between the USBD and the HCI
 */
struct usbd_sw {
    void (*enable_option)();    /* Func for enabling option interrupts  */
    void (*disable_option)();   /* Func for disabling option interrupts */

#ifdef notdef
    io_handle_t sparse_io_base; /* io_handle for sparse io base address */
    io_handle_t sparse_mem_base;/* io_handle for sparse memory base address */
    io_handle_t dense_mem_base; /* io_handle for dense memory base address  */
#endif
    vm_offset_t (*busphys_to_iohandle)(); /* Fnc to return io handle    */

    int (*adpt_config)();       /* bus-adapter config routine           */
    int (*confl1)();            /* adapter-specific confl1 routine      */
    int (*confl2)();            /* adapter-specific confl2 routine      */

    int (*request_resource)();  /* Request I/O resource routine         */
    int (*release_resource)();  /* Release I/O resource routine         */

    ihandler_id_t (*handler_add)(); /* Function for installing an ISR   */
    int (*handler_enable)();    /* Function for enabling an interrupt   */
    int (*handler_disable)();   /* Function for disabling an interrupt  */
    int (*handler_del)();       /* Function for removing an ISR         */
    dma_map_info_t (*dma_get_maps)();   /* Function to get dma windows info */

    USBD_STATUS (*resume_endpoint)(); /* Resume endpoint after an error */
    USBD_STATUS (*start_endpoint)(); /* Start endpoint (after stop_endpoint)*/
    USBD_STATUS (*stop_endpoint)();  /* Stop an endpoint */

    /* Get the state of the endpoint */
    USBD_STATUS (*get_endpoint_state)();

    USBD_STATUS (*abort_request)();  /* Abort a request */
    USBD_STATUS (*abort_pipe)();     /* Abort all requests queued to a pipe */
    USBD_STATUS (*clear_stall)();    /* Clear a stall condition */
    USBD_STATUS (*close_endpoint)(); /* Close an endpoint, remove it from
                                      * the schedule */

    USBD_STATUS (*queue_to_interrupt_endpoint)();
    USBD_STATUS (*queue_to_bulk_endpoint)();
    USBD_STATUS (*queue_to_control_endpoint)();
    USBD_STATUS (*queue_to_isochronous_endpoint)();
};

/*
 * Callback queue struct
 */
struct usbd_callback_queue {
    struct usbd_super_request *flink;
    struct usbd_super_request *blink;
    int flags;
    int count;
};

/*
 * struct usbd_bus - One for each USB bus
 */
typedef struct usbd_bus {
    USBD_HANDLE_TYPE struct_type; /* USBD_BUS_HANDLE_TYPE */

    /*
     * Lock for everything in this structure including the callback
     * thread and the root hub thread.
     */
    simple_lock_data_t lock;

    /*
     * Host Controller Interface softc struct
     */
    void *hci_sc;

    /*
     * Callback thread fields
     */
    LIST_ENTRY callback_thread_queue;
    int callback_thread_state;
#define USBD_THREAD_IDLE	0x0000
#define USBD_THREAD_SCHED	0x0001
#define USBD_THREAD_ACTIVE	0x0002
#define USBD_THREAD_WAKEUP	0x8000
    int callback_thread_count;
    thread_t callback_thread;

    /*
     * Roothub softc
     */
    struct usbd_hub *root_hub;

    /*
     * Hub thread pointers
     */
    LIST_ENTRY hub_thread_queue;
    int hub_thread_state;	/* See defs above for callback_thread_state */
    thread_t hub_thread;

    /*
     * Connected USB devices are allocated a USBD_DEVICE structure
     * (this includes the root hub).  This structure contains the USB address
     * which will be assigned to the device.  This address is also the
     * index into the "device_array" (below) for that structure.  All
     * structures  which have been assigned to a device will be included
     * in the "used" list of the device_array.  All available usbd_device
     * structs will be in the "available" list.  See USBD_ARRAY_DESCRIPTOR
     * in usbd.h
     */
    struct usbd_array_descriptor device_array;

    io_handle_t csr;    /* Address for the HC register base (BAR) */
    struct bus *bus;    /* Parent bus (PCI) */
    int adpnum;         /* Unique bus number */

} USBD_BUS;

/*
 * The usbd_device structure.  There is one of these for each USB
 * device on the bus.  The usbd_device structure is contained by the
 * usbd_hub struct and the usbd_function struct found below.
 */
typedef struct usbd_device {
    /* Used by the USBD_ARRAY_DESCRIPTOR */
    USBD_DESCRIPTOR_HEADER desc_header;
    USBD_HANDLE_TYPE struct_type; /* USBD_DEVICE_HANDLE_TYPE */

    /*
     * Lock for this structure
     */
    lock_data_t lock;

    U32 device_state;
    U32 next_device_state;
    U8 port_number; /* Upstream port number device is connected to */
    U8 speed;       /* Device speed, zero for full speed, 1 for low speed */
    U8 tier_level;  /* The root hub is at tier zero */
    U8 usb_address; /* USB address of the device, once it has been addressed */
    int flags;
#define DEVICE_CONNECT_INPROGRESS  0x00000001 /* Set during 100ms delay after
					       * a connect is detected.
					       */
#define DEVICE_DECONFIG_INPROGRESS 0x00000002
#define DEVICE_READ_DEVICE_DESC1   0x00000004
#define DEVICE_NOT_OHCI_COMPLIANT  0x00000080
#define DEVICE_CONFIG_DEVICE       0x00000100 /* Load one driver per device */
#define DEVICE_CONFIG_INTERFACE    0x00000200 /* Load one driver per inter */
    struct usbd_pipe *default_pipe; /* Default pipe for this device */
    struct usbd_bus *usb_bus;       /* Bus this device is connected to */
    struct usbd_hub *upstream_hub;  /* Hub this device is connected to, NULL if
				     * this usbd_device is for the root hub */

    LIST_ENTRY default_pipe_requests; /* Requests queued to the default pipe */

    /*
     * Device driver configuration information.  The following
     * three fields are only used if configuration is per device
     * and not on an interface basis.  Each interface will be 
     * configured using the device_config routine.
     */
    int (*device_config)();
    int (*device_deconfig)();
    char device_driver_name[CFG_ATTR_NAME_SZ];

    /*
     * The device descriptor for this device
     */
    const struct usb_device_descriptor device_desc; 

    /*
     * Array of configuration descriptors
     */
    const struct usb_configuration_descriptor **config_desc_array;
    int config_desc_count; /* # of config descriptors */

    /*
     * Pointer to configuration descriptor which the device
     * is currently using.  This may be set before the device
     * driver performs a "set_configuration."
     */
    const struct usb_configuration_descriptor *active_config_desc;

    /*
     * Array of usbd_interface structures.  One for each
     * interface supported by the device.  This includes all
     * default interfaces (AlternateSetting is zero) and all
     * alternate interfaces.
     */
    struct usbd_interface *interface_array;

    /*
     * Array of default usbd_interface structs.  default_interface_count
     * is the number of interfaces with an AlternateSetting of zero.
     */
    struct usbd_interface **default_interface_array;
    int default_interface_count;

    /*
     * Array of usbd_endpoint structures. One for each endoint
     * supported by the device.
     */
    struct usbd_endpoint *endpoint_array;

    /*
     * Number of interface descriptors supplied by the device.  This
     * is also the total number of interfaces.
     */
    int interface_desc_count;

    /*
     * Number of endpoint descriptors supplied by the device.  This
     * is also the total number of endpoints.
     */
    int endpoint_desc_count;

    /*
     * Device's current configuration value.
     */
    U16 config_value;

} USBD_DEVICE;

/*
 * struct usbd_hub - One of these is assigned to each hub including the
 * root hub.
 *
 * Note that Hubs have two locks, one within the USBD_DEVICE and one
 * within the USBD_HUB. USBD_HUB lock is only used to lock the
 * "down_stream_devices."
 */
typedef struct usbd_hub {
    USBD_DEVICE device;  /* usbd_device struct above */
    USBD_HANDLE_TYPE struct_type; /* USBD_HUB_HANDLE_TYPE */
    struct usb_hub_descriptor hub_desc; /* The USB hub descriptor */
    U8 status_change_endpoint;	       /* Endpoint number of the hub's
					* status change endpoint
					*/
    USBD_PIPE_HANDLE status_change_pipe; /* Handle to the Hub's status
					  * change pipe (see USB spec)
					  */
    LIST_ENTRY status_change_requests; /* List of requests outstanding 
					* to the status change pipe
					*/
    int number_of_ports;               /* Number of ports on this hub.  This
					* value is taken from the hub
					* descriptor 
					*/
    U8 port_status[255];	       /* Port status (see USB spec) for
					* each port.  JANET - allocate this



					* for the supported ports, get rid
					* of the "255"
					*/
#define USBD_HUB_PORT_NEED_POWER     0x01
    int flags;				/* Hub related flags */
#define USBD_HUB_NEED_REQUEST_STATUS 0x01
    int port_power_count;		/* Count of number of ports with an
					 * outstanding "power port" request.
					 * Used during hub initialization
					 */

    /* 
     * Array of pointers to usb_hub_softc, usb_function_softc, or NULL
     * if nothing is connected to that port.
     */
    union usbd_device_union **down_stream_devices;

    /*
     * Lock for this structure.
     */
    lock_data_t lock;

    /*
     * This structure is locked via the lock in USBD_DEVICE
     */

} USBD_HUB;

/*
 * usbd_function - One for all devices which aren't hubs
 */
typedef struct usbd_function {
    USBD_DEVICE device;
    USBD_HANDLE_TYPE struct_type; /* USBD_FUNCTION_HANDLE_TYPE */

    /*
     * This structure is locked via the lock in USBD_DEVICE
     */

} USBD_FUNCTION;

/*
 * USBD device union.  A device is a hub or a function.
 */
typedef union usbd_device_union {
    USBD_FUNCTION function;
    USBD_HUB hub;
} USBD_DEVICE_UNION;

/*
 * struct usbd_interface - One for each interface supported 
 * by the device
 */
typedef struct usbd_interface {
    USBD_HANDLE_TYPE struct_type;  /* USBD_INTERFACE_HANDLE_TYPE */
    int flags; /* Future */
    int state; /* USBD_INTERFACE_ACTIVE, USBD_INTERFACE_STALLED, and
		* USBD_INTERFACE_IDLE defined in usbdi.h */
#define USBD_INTERFACE_CONFIG  0x8000 /* Set when the "device_config" routine
				       * routines TRUE when the interface
				       * has been configured.
				       */
#define USBD_INTERFACE_DECONFIG_INPROG		0x0100
#define USBD_INTERFACE_DECONFIG_COMPLETE	0x0200

    /* Associated device header */
    struct usbd_device *device;

    /* Not used if configuration is per device */
    /* Interface configuration routine */
    int (*interface_config)();
    int (*interface_deconfig)();
    char interface_driver_name[CFG_ATTR_NAME_SZ];

    /*
     * Alternate interface info.  The USBD_INTERFACE struct for the
     * default interface will have the live active_interface value and
     * will also contain an accurate value for interface_count.
     * The active_interface value for alternate interfaces is
     * undefined.  Alternate interfaces may access the default interface
     * via the default_interface pointer.
     */
    struct usbd_interface *default_interface;
    struct usbd_interface *interface_array;
    int interface_count;
    int active_interface; /* AlternateSetting from active interface desc */

    /* Interface descriptor */
    const struct usb_interface_descriptor *interface_desc;

    /* Endpoint(s) associated with this interface */
    struct usbd_endpoint **endpoint_array;
    int endpoint_count;

    /* Field reserved for use by the interface driver */
    USBD_PRIVATE_HANDLE private_handle;

    /*
     * Lock for the interface and for all associated usbd_endpoint's
     */
    lock_data_t lock;

} USBD_INTERFACE;

/*
 * struct usbd_pipe - Pipes are allocated dynamically when the
 * interface driver needs to communicate with an endpoint.  A pipe
 * connects the interface to the endpoint.
 */
typedef struct usbd_pipe {
    USBD_HANDLE_TYPE struct_type; /* USBD_PIPE_HANDLE_TYPE */
    U16 usb_address      :7,  /* USB address of the device */
        endpoint_number  :4,  /* From the endpoint's descriptor */
        direction        :2,  /* From the endpoint's descriptor */
        speed            :1,  /* From the endpoint's descriptor */
        sKip             :1,  /* From the endpoint's descriptor */
        Format           :1;  /* From the endpoint's descriptor */

    /*
     * Maximum data transfer size for this pipe.  From the endpoint
     * descriptor
     */
    U16 MaximumPacketSize:11,
                         : 5;
    U32 flags; /* See usbd.h */

    U32 ref_count;  /* Reference count for this pipe */
    U32 open_count; /* Open count, incremented by usbd_open_pipe() */
    U32 state;      /* USBD_PIPE_ACTIVE/STALLED/IDLE */

    struct usbd_bus *usb_bus;       /* Pointer to USBD_BUS */
    struct usbd_device *device;	    /* Pointer to USBD_DEVICE */
    struct usbd_endpoint *endpoint; /* Pointer to the USB_ENDPOINT */

    /* Endpoint type: Isochronous, Interrupt, Control, Bulk */
    U8 type;

    /*
     * OHCI specific data - JANET - Get this out of here, make its own
     * structure and create a union
     */

    /* HCI specific endpoint descriptor which is scheduled. */
    void *ED;

    /* This is the requested polling rate for an interrupt endpoint,
     * the actual rate used is indicated by ListIndex.
     */
    U8 Rate;

    /* For isochronous or interrupt endpoints, this value represents the
     * amount of bandwidth which is required for the endpoint when it's
     * opened.  For control or bulk endpoints, this value represents the
     * maximum packet size to be transferred to or from the endpoint in any
     * one packet.
     */
    U16 Bandwidth;

    /*
     * Lock for this structure
     */
    lock_data_t lock;

} USBD_PIPE;

/*
 * struct usbd_endpoint - One for each endpoint.
 * Modify this structure only if its associated interface
 * is locked.
 */
typedef struct usbd_endpoint {
    USBD_HANDLE_TYPE struct_type; /* USBD_ENDPOINT_HANDLE_TYPE */

    /* Associated device header */
    struct usbd_device *device;

    /* Associated interface softc */
    USBD_INTERFACE *interface;

    /* Associated endpoint descriptor */
    const struct usb_endpoint_descriptor *endpoint_desc;
    U8 endpoint_number;  /* Set from the endpoint_desc */

    /* Handle to the opened pipe, NULL if pipe isn't opened */
    struct usbd_pipe *pipe;

} USBD_ENDPOINT;

/*
 * struct usbd_request - Request structure used to communicate between
 * the Interface drivers/USBD/HCI
 *
 * This structure is contained in the usbd_super_request below.
 */
typedef struct usbd_request {

    USBD_HANDLE_TYPE struct_type; /* USBD_REQUEST_HANDLE_TYPE */

    /*
     * Chained request is used to chain requests which can't be put
     * on the ED all at once.  When a request completes, just before
     * the callback, the chained_request field will be checked.  If
     * this value in not NULL the chained_request will be started
     * just before the callback.
     */
    struct usbd_request *chained_request;

    /* Endpoint handle */
    USBD_PIPE *pipe;

    /* Associated class driver's private handle */
    USBD_PRIVATE_HANDLE private_handle;

    /* Number of times this request has been retried by usbd_retry_request() */
    U8 retry_count;

    /* Saved buffer length for retries */
    U32 start_buflen;

    /* Pointer to data to be transferred */
    char *Buffer;
    sglist_t buffer_sg;

    /* Length of data buffer in bytes */
    U32 BufferLength;

    /* Maximum allowable delay from completion to completion
     * notification to USBD.
     */
    U32 MaxIntDelay;

    /* Data for setup packet (control endpoints only) */
    struct usb_device_request device_request;
    sglist_t device_request_sg;

    /* Callback function to the interface driver */
    void (*usbd_callback)();

    /* 
     * Flags may be USBD_XFER_SETUP, USBD_XFER_OUT, USBD_XFER_IN,
     * USBD_SHORT_XFER_OK, USBD_REQUEST_WAIT (defined in usbdi.h)
     */
    U32 flags;
#define USBD_XFER_MASK			0x03
#define USBD_SETUP_HAS_BEEN_DONE	0x10
#define USBD_STATUS_HAS_BEEN_DONE	0x20
#define USBD_DATA_HAS_BEEN_DONE		0x40
#define USBD_NON_OHCI_COMPLIANT		0x80


    /* Completion status from HCD to USBD */
    U32 status;
#define USBD_CALLBACK_COMPLETE	0x80000000

} USBD_REQUEST;

/*
 * If this structure is changed, be sure to change the access macros
 * below.
 */
struct usbd_super_request {
    
    LIST_ENTRY USBDlist;	/* Used by the USBD */
    LIST_ENTRY HCDlist;		/* Used by the HCD */
    USBD_REQUEST request;	/* The request structure which class drivers
				 * work with.
				 */

    /*
     * Functional queue for tracing the request during driver debug.
     */
#ifdef USB_FUNCQ
    int funcq_index;
#define USB_REQUEST_FUNCQ 256
    char *funcq_buf[USB_REQUEST_FUNCQ];
#endif

};

/*
 * Hub request wrapper
 */
typedef struct hub_request {
    LIST_ENTRY l;
    USBD_BUS *usb_bus;
    USBD_REQUEST_HANDLE request_handle;
    void *argument;
    U32 flags;
#define HUB_REQUEST_PENDING	0x0001
#define HUB_REQUEST_WAKEUP_DONE	0x0002
#define HUB_REQUEST_SLEEPING    0x0004
} HUB_REQUEST;

/*
 * Hub thread entry.
 */
struct hub_thread_entry {
    LIST_ENTRY l;
    USBD_BUS *usb;
    U64 argument;
    void (*callback)();
};

#define USB_REQUEST2SUPER(usbrequest) \
((struct usbd_super_request *)(((char *)(usbrequest)) - (sizeof(LIST_ENTRY) * 2)))

#define USB_REQUEST2HCDlist(usbrequest) \
(&(((struct usbd_super_request *)(((char *)(usbrequest)) - (sizeof(LIST_ENTRY) * 2)))->HCDlist))

#define InsertTailList(list, entry) \
    insque((void *)(entry), (void *)(list)->blink)
#define RemoveListEntry(entry) remque((void *)(entry))
#define IsListEmpty(list) ((list)->flink == (list)->blink ? 1 : 0)

/*
 * JANET - need to go through and decide where to use wait and
 *         where to use no-wait
 */
#define USBD_MALLOC_WAIT(where, size); \
   MALLOC_VAR(((char *)(where)), char *, (long)(size), M_USB, M_ZERO);

#define USBD_MALLOC(where, size); \
   MALLOC_VAR(((char *)(where)), char *, (long)(size), M_USB, M_NOWAIT|M_ZERO);

#define USBD_MALLOC_FIXED(where, size); \
   MALLOC(((char *)(where)), char *, (long)(size), M_USB, M_ZERO);

#define USBD_FREE(where) FREE((char *)(where), M_USB); ((char *)(where)) = (char *)NULL;


/*
 * Access to the private area of "struct bus"
 */
#define usb_ptr private[4]

#define USB_LOCK_INIT(lk, info) lock_setup(&(lk), info, TRUE)
#define USB_LOCK_DEINIT(lk) lock_terminate(&(lk))
#define USB_READ_LOCK(lk, s) { (s) = splbio(); lock_read(&(lk)); }
#define USB_WRITE_LOCK(lk, s) { (s) = splbio(); lock_write(&(lk)); }
#define USB_UNLOCK(lk, s) { lock_done(&(lk)); splx(s); }
#define USB_READ_TO_WRITE_LOCK(lk) lock_read_to_write(&(lk))
#define USB_WRITE_TO_READ_LOCK(lk) lock_write_to_read(&(lk))

#define USB_SIMPLE_LOCK_INIT(lk, info); {usimple_lock_setup(&(lk), info);}
#define USB_IPL_LOCK(lk, s); { (s) = splbio(); usimple_lock(&(lk)); }
#define USB_IPL_UNLOCK(lk, s); { usimple_unlock(&(lk)); splx(s); }

#define USB_IS_LIST_EMPTY(list) \
    (((LIST_ENTRY *)list)->flink == (LIST_ENTRY *)(list) ? TRUE : FALSE)
#define USB_LIST_INIT(list); \
    ((LIST_ENTRY *)list)->flink = ((LIST_ENTRY *)list)->blink = (LIST_ENTRY *)list;
#define USB_LIST_INSERT(entry, where) insque((void *)(entry), (void *)(where))
#define USB_LIST_REMOVE(entry) remque((void *)(entry))

#endif /* _USBD_H_ */


