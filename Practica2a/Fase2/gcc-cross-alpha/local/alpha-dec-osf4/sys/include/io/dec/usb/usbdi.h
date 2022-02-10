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
 * @(#)$RCSfile: usbdi.h,v $ $Revision: 1.1.10.2 $ (DEC) $Date: 1998/09/25 14:23:56 $
 */
#ifndef _USBDI_H_
#define _USBDI_H_

#include <io/dec/usb/usbdi_os.h>
#include <io/dec/usb/usb.h>

/*
 * This file contains defines and declarations needed to communicate
 * with the USBDI.
 *
 * This file will be distributed as source.
 */


/*
 * Status returned by USBDI functions.
 *
 * JANET - Update this list
 * 
 * JANET - document exactly how/when each of these errors may be returned.
 */
typedef enum usbd_status {
    USBD_NORMAL_COMPLETION,		/* Normal, no error           */
    USBD_INPROGRESS,			/* The request is in progress */
    USBD_NOT_DONE,			/* Request has not yet completed */
    USBD_CANCELING,
    USBD_CANCELED,
    USBD_INVALID_BUS,
    USBD_INVALID_DEVICE,
    USBD_INVALID_INTERFACE,
    USBD_INVALID_PIPE,
    USBD_INVALID_ENDPOINT,
    USBD_INVALID_REQUEST,
    USBD_INVALID_VALUE,
    USBD_INVALID_INDEX,
    USBD_DEVICE_BUSY,
    USBD_PIPE_RESET,
    USBD_CRC_ERROR,
    USBD_BITSTUFFING_ERROR,
    USBD_DATATOGGLEMISMATCH_ERROR,
    USBD_STALL_ERROR,
    USBD_DEVICENOTRESPONDING_ERROR,
    USBD_PIDCHECKFAILURE_ERROR,
    USBD_UNEXPECTEDPID_ERROR,
    USBD_DATAOVERRUN_ERROR,
    USBD_DATAUNDERRUN_ERROR,
    USBD_BUFFEROVERRUN_ERROR,
    USBD_BUFFERUNDERRUN_ERROR,
    USBD_BAD_CONTROLLER_NUMBER,
    USBD_IDLE_PIPE,
    USBD_PIPE_ALREADY_INUSE,
    USBD_BAD_BUFFERLENGTH,
    USBD_DECONFIG_INPROGRESS,
    USBD_NO_MEMORY,
    USBD_DMA_MAPPING_ERROR,
    USBD_UNABLE_TO_ABORT,
    USBD_ABORT_INPROG,
    USBD_RESET_INPROG,
    USBD_PENDING_REQUESTS,
    USBD_NO_BANDWIDTH,
    USBD_TIMEOUT,
    USBD_NOT_IMPLEMENTED,
    USBD_UNKNOWN_ERROR
} USBD_STATUS;

/*
 * Handles used by the usbd interface
 */
typedef USBD_HANDLE USBD_BUS_HANDLE;
typedef USBD_HANDLE USBD_DEVICE_HANDLE;
typedef USBD_HANDLE USBD_INTERFACE_HANDLE;
typedef USBD_HANDLE USBD_PIPE_HANDLE;
typedef USBD_HANDLE USBD_REQUEST_HANDLE;
typedef USBD_HANDLE USBD_PRIVATE_HANDLE;

/*
 * Useful macros
 */
#define USBD_ASSERT(ex)                                             \
   if (!(ex)) {                                                     \
      printf("Assertion failed: file: \"%s\", line: %d test: %s\n", \
             __FILE__, __LINE__, # ex );                            \
      panic("assertion failure");                                   \
   }

/* 
 * Function: usbd_open_pipe()
 *
 * Description:
 *   usbd_open_pipe() is used to associate a pipe to a device's endpoint.
 *   This function will return a USBD_PIPE_HANDLE which may then be
 *   used by other USBDI functions such as usbd_transfer().
 */
USBD_STATUS
usbd_open_pipe(USBD_INTERFACE_HANDLE interface_handle /* In  */,
	       U8 endpoint_address                    /* In  */,
	       U16 flags                              /* In  */,
	       USBD_PIPE_HANDLE *pipe_handle          /* Out */);
/* Flags for usbd_open_pipe */
#define USBD_EXCLUSIVE_USE	0x001


/*
 * Function: usbd_close_pipe()
 *
 * Description:
 *   Close a pipe which was opened with usbd_open_pipe().  Before a
 *   pipe may be closed all requests must be completed or aborted.
 */
USBD_STATUS
usbd_close_pipe(USBD_PIPE_HANDLE pipe_handle /* In */);

/* 
 * Function: usbd_transfer()
 *
 * Description:
 *   Queue the request described by its USBD_REQUEST_HANDLE to its
 *   associated pipe.  Request handles are obtained from usbd_alloc_request().
 *   The actual request is setup with usbd_setup_request() and
 *   usbd_setup_device_request().  It is important to check the return value
 *   from this function.  Only a return value of USBD_INPROGRESS signifies
 *   that the request was actually queued to the pipe and a callback to the
 *   request's callback function will be performed.  To restate, a callback
 *   to the interface driver will only be performed if the return value from
 *   this function is USBD_INPROGRESS.  Note that this function only queues
 *   the request, the state of the pipe must be USBD_PIPE_ACTIVE for the
 *   request to be delivered to the pipe's endpoint.
 */
USBD_STATUS
usbd_transfer(USBD_REQUEST_HANDLE request_handle /* In */);

/*
 * Function: usbd_alloc_request()
 *
 * Description:
 *    Return a handle to a request.  This request would then typically be
 *    setup by usbd_setup_request() then transfered to the device by
 *    calling usbd_transfer().  Call usbd_free_request() when done with it.
 */
USBD_REQUEST_HANDLE
usbd_alloc_request(void);

/*
 * Function:  usbd_free_request()
 *
 * Description:
 *    Free the request described by the given request_handle.
 */
USBD_STATUS
usbd_free_request(USBD_REQUEST_HANDLE request_handle /* In */);

/*
 * Function: usbd_setup_request()
 *
 * Description:
 *   This function should be used for interrupt and bulk transfer requests.
 *   It may also be used to setup a control request for endpoints other
 *   than the default.  In this case, the function usbd_setup_device_request()
 *   should also be called to setup the device request fields.
 *
 *   If instead of using a callback on completion the usbd_request_wait()
 *   function is going to be called then the flag USBD_REQUEST_WAIT must
 *   be set and the argument of callback must be NULL.
 */
USBD_STATUS
usbd_setup_request(USBD_REQUEST_HANDLE request_handle, /* In */
		   USBD_PIPE_HANDLE pipe_handle,       /* In */
		   USBD_PRIVATE_HANDLE private_handle, /* In */
		   char *buffer,                       /* In */
		   U32 buffer_length,                  /* In */
		   U32 flags,                          /* In */
		   void (*callback)()                  /* In */ );
/* Flags for usbd_setup_request() */
#define USBD_XFER_SETUP		0
#define USBD_XFER_OUT		1
#define USBD_XFER_IN		2
#define USBD_SHORT_XFER_OK	4 
#define USBD_REQUEST_WAIT	8


/*
 * Function: usbd_setup_device_request()
 *
 * Description:
 *    Setup the given request described by request_handle with the given
 *    device request fields.  This function should only be used for control
 *    endpoints other than endpoint 0 and should be used in conjunction with
 *    usbd_setup_request().
 */
USBD_STATUS
usbd_setup_device_request(USBD_REQUEST_HANDLE request_handle, /* In */
			  struct usb_device_request *dev_req  /* In */ );

/*
 * Function: usbd_setup_control_request()
 *
 * Description:
 *   Setup the USBD_REQUEST_HANDLE as a control request for the default
 *   endpoint using the supplied device request fields.  This function
 *   does NOT require the use of usbd_setup_request().
 */
USBD_STATUS
usbd_setup_control_request(USBD_REQUEST_HANDLE request_handle,     /* In */
			   USBD_DEVICE_HANDLE device_handle,       /* In */
			   USBD_PRIVATE_HANDLE private_handle,     /* In */
			   struct usb_device_request *dev_req,     /* In */
			   char *buffer,                           /* In */
			   U32 buffer_length,                      /* In */
			   U32 flags,                              /* In */
			   void (*callback)()                      /* In */ );
/* See usbd_setup_request() for flags defines */

/*
 * Function: usbd_request_wait()
 *
 * Description:
 *   This function will sleep until the request specified for
 *   request_handle completes.  This function should only be
 *   used if the request was setup with a flags value of
 *   USBD_REQUEST_WAIT.
 *
 * Return Value:
 *   This function will return USBD_NORMAL_COMPLETION if the
 *   request completes (with or without error).
 */
USBD_STATUS
usbd_request_wait(USBD_REQUEST_HANDLE request_handle, int wait_time);

/*
 * Function: usbd_get_request_status()
 *
 * Description:
 *    Return the status of the given request and return the associated
 *    private driver handle.  This routine should always be called after
 *    a request completes to verify its status.
 */
USBD_STATUS
usbd_get_request_status(USBD_REQUEST_HANDLE request_handle,  /* In  */
			USBD_PRIVATE_HANDLE *private_handle, /* Out */
			char **buffer,                       /* Out */
			U32 *buffer_count,                   /* Out */
			USBD_STATUS *request_status          /* Out */);

/*
 * Function: usbd_get_device_data()
 *
 * Description:
 *   Return the device request data from the USBD_REQUEST_HANDLE.  This
 *   routine may be called by the interface driver's callback function when
 *   a request had been setup as a device request with
 *   usbd_setup_device_request() or usbd_setup_control_request().
 */
USBD_STATUS
usbd_get_device_data(USBD_REQUEST_HANDLE request_handle, /* In  */
		     struct usb_device_request *dev_req  /* Out */);


/*
 * Come up with a different name for this function
 * or get rid of it.  It can be used for any control request
 * (right now data in only but that could be fixed with a
 * direction flag), not just a "get descriptor".
 * This is just a convience function which does the calls
 * to usbd_setup_control_request(), usbd_transfer(), and
 * usbd_request_wait().
 */
USBD_STATUS
usbd_read_descriptor(USBD_DEVICE_HANDLE device_handle   /* IN  */,
		     struct usb_device_request *dev_req /* IN  */,
		     char *buffer                       /* OUT */);

/*
 * Function: usbd_get_configuration_descriptor
 *
 * Description:
 *   This function will return a const char pointer to the configuraiton
 *   descriptor indicated by index.  The index is the same value which
 *   would be passed to the device in the lower byte of the "value"
 *   field of the device request.  The default index is zero for device's
 *   with only one configuration.
 *
 *   Important:  This function returns a read-only pointer which should
 *   not be modified in anyway by the interface driver!
 */
const struct usb_configuration_descriptor *
usbd_get_configuration_descriptor(USBD_DEVICE_HANDLE device_handle /* In  */,
				  U8 index                         /* In  */);

/*
 * Function: usbd_get_interface_descriptor
 *
 * Description:
 *   Used to retrieve interface descriptors given the interface handle
 *   and alternate interface index value.  Use usbd_get_interface to
 *   determine current active interface and number of alternate 
 *   interfaces supported by the interface described by interface_handle.
 *
 *   Important:  This function returns a read-only pointer which should
 *   not be modified in anyway by the interface driver!
 */
const struct usb_interface_descriptor *
usbd_get_interface_descriptor(USBD_INTERFACE_HANDLE interface_handle /* In */,
			      U8 alternate_interface_index           /* In */);

/*
 * Function: usbd_get_descriptor
 *
 * Description:
 *   When the configuration driver (hub class driver) initially reads
 *   in the configuration descriptor the device returns the configuration
 *   descriptor along with all interface descriptors, endpoint descriptors,
 *   and some class specific descriptors.  Usbd_get_descriptor()
 *   should be used to retrieve a read-only pointer to any of these
 *   descriptors and also to the device descriptor.  Use
 *   usbd_interface2endpoint_descriptor() to retrieve endpoint descriptors. 
 *   Instance is the "instance" of the descriptor as they are found
 *   sequentially in the configuration descriptor.  Use an instance of
 *   1 to get the first one found.
 *
 *   Important:  This function returns a read-only pointer which should
 *   not be modified in anyway by the interface driver!
 */
const char *
usbd_get_descriptor(USBD_INTERFACE_HANDLE interface_handle, /* In */
		    U8 desc_type,                           /* In */
		    U8 instance                             /* In */);

/*
 * Function: usbd_interface2endpoint_descriptor()
 *
 * Description:
 *    Return a pointer to a usb_endpoint_descriptor structure (defined by
 *    the USB spec) which is associated with the given interface_handle and
 *    index value starting with 0.  This index value has no association with
 *    the endpoint address.
 *
 *    Valid endpoint_index values are 0 to (NumEndpoints - 1).
 *
 *    NumEndpoints is the number of endpoints associated with this
 *    interface as defined by the interface descriptor (See usb.h).
 */
const struct usb_endpoint_descriptor *
usbd_interface2endpoint_descriptor(USBD_INTERFACE_HANDLE interface_handle,
				   U8 endpoint_index);

/*
 * Function: usbd_set_configuration()
 *
 * Description:
 *   Devices which support multiple configurations may have their
 *   configuration changed to a supported value.  The device descriptor
 *   defines the number of configurations supported.
 *
 *   Before this function is called, all pipes, for all interfaces
 *   associated with the current configuration must be closed.
 */
USBD_STATUS
usbd_set_configuration(USBD_DEVICE_HANDLE device_handle, /* In */
		       U8 config_value                   /* In */);

/* 
 * Function: usbd_retry_request()
 *
 * Description:
 *    Retry queue a request to its associated endpoint after an error.  This
 *    routine willmove the pipe's state to USBD_PIPE_ACTIVE after
 *    queuing the request.
 */
USBD_STATUS
usbd_retry_request(USBD_REQUEST_HANDLE request_handle, /* In */
		   U32 retry_count                     /* In */);

/*
 * Function: usbd_abort_request()
 *
 * Description:
 *   The request identified by its USBD_REQUEST_HANDLE will be aborted
 *   and returned to the interface driver via its callback function with
 *   a status of USBD_CANCELED.  The pipe may be in any state when this
 *   function is called, although during the abort processing the pipe
 *   will be briefly idle.  Requests received by the USBD during this
 *   period will be returned with a status of USBD_ABORT_INPROG.  The
 *   state of the pipe will be left unchanged by this function.
 */
USBD_STATUS
usbd_abort_request(USBD_REQUEST_HANDLE request_handle /* In */);

/*
 * Function: usbd_abort_pipe()
 *
 * Description:
 *   All requests queued for the pipe described by USBD_PIPE_HANDLE
 *   will be returned to the interface driver via the request's
 *   callback function with a status of USBD_CANCELED.  The pipe may
 *   be in any state when this function is called, although during the
 *   abort processing the pipe will be briefly idle.  Requests received
 *   by the USBD during this period will be returned with a status of
 *   USBD_ABORT_INPROG.  The state of the pipe will be left unchanged
 *   by this function.
 */
USBD_STATUS
usbd_abort_pipe(USBD_PIPE_HANDLE pipe_handle /* In */);

/*
 * Function: usbd_abort_interface()
 *
 * Description:
 *   All requests queued to all pipes of the interface are returned to
 *   the interface driver via the request's callback function with a
 *   status of USBD_CANCELED.  The interface may be in any state when
 *   this function is called but will briefly be idle during the abort
 *   processing.  During this time, requests sent to any of the
 *   interface's pipes will be returned with a status of USBD_ABORT_INPROG.
 *   The state of the interface and associated pipes are left unchanged
 * by this function.
 */
USBD_STATUS
usbd_abort_interface(USBD_INTERFACE_HANDLE interface_handle /* In */ );

/*
 * Function: usbd_reset_pipe()
 *
 * Description:
 *   All requests queued to the pipe will be returned to the interface
 *   driver via its callback function with a status of USBD_CANCELED.
 *   The pipe may be in any state before this function is called, although
 *   during the reset processing the pipe will be briefly idle.  Requests
 *   received by the USBD during this period will be returned with a status
 *   of USBD_RESET_INPROG.  The state of the pipe on completion of this
 *   function will be USBD_PIPE_ACTIVE.
 */
USBD_STATUS
usbd_reset_pipe(USBD_PIPE_HANDLE pipe_handle /* In */ );

/*
 * Function: usbd_reset_interface()
 *
 * Description:
 *   All requests queued to all pipes associated with the interface
 *   described by USBD_INTERFACE_HANDLE will be returned to the
 *   interface driver via the request's callback function with a
 *   status of USBD_CANCELED.  The interface may be in any state
 *   before this function is called, although during the reset
 *   processing the interface's state will briefly be USBD_INTERFACE_IDLE.
 *   Any requests which are queued to the interface's pipe during reset
 *   processing will be returned with a status of USBD_RESET_INPROG.
 *   The status of the interface and pipes will be set to active at
 *   completion of this function.
 */
USBD_STATUS
usbd_reset_interface(USBD_INTERFACE_HANDLE interface_handle /* In */);

/*
 * Function: usbd_clear_endpoint_stall()
 *
 * Description:
 *   Clear a stall condition on the endpoint attached to the pipe
 *   described by USBD_PIPE_HANDLE.
 */
USBD_STATUS
usbd_clear_endpoint_stall(USBD_PIPE_HANDLE pipe_handle /* In */);

/*
 * Function: usbd_set_pipe_state()
 *
 * Description:
 *   A pipe may be set to one of the folloing three states:
 *      USBD_PIPE_ACTIVE - The pipe will accept requests bo be queued
 *                       and will send requests to the pipe's endpoint.
 *      USBD_PIPE_STALLED - The pipe will accept requests to be queued
 *                       but will not send requests to the pipe's endpoint.
 *      USBD_PIPE_IDLE - The pipe will not accept requests to be queued
 *                       and will not send requests to the endpoint.
 */
USBD_STATUS
usbd_set_pipe_state(USBD_PIPE_HANDLE pipe_handle, /* In */
                    U32 pipe_state                /* In */ );
#define USBD_PIPE_ACTIVE  0x0001
#define USBD_PIPE_STALLED 0x0002
#define USBD_PIPE_IDLE    0x0003

/*
 * Function: usbd_get_pipe_state()
 *
 * Description:
 *   The state of the pipe described by USBD_PIPE_HANDLE will be returned.
 *   The pipe's state is described by its host-side state and its reflected
 *   endpoint state as defined by the USB specification.  This function
 *   will also return the number of requests which are queued for the pipe.
 */
USBD_STATUS
usbd_get_pipe_state(USBD_PIPE_HANDLE pipe_handle, /* In  */
		    U32 *pipe_state,              /* Out */
		    U32 *endpoint_state,          /* Out */
		    U32 *request_count            /* Out */ );
#define USBD_ENDPOINT_STATE   0x0005
#define USBD_ENDPOINT_ACTIVE  0x0001           
#define USBD_ENDPOINT_STALLED 0x0002     /* After an error on the endpoint */
#define USBD_ENDPOINT_IDLE    0x0004     /* Idle state is set by the USBDI */

/*
 * Function: usbd_set_default_pipe_state()
 *
 * Description:
 *   Set the devices's default pipe to USBD_PIPE_ACTIVE, USBD_PIPE_STALLED,
 *   or USBD_PIPE_IDLE (see usbd_set_pipe_state())
 */
USBD_STATUS
usbd_set_default_pipe_state(USBD_DEVICE_HANDLE device_handle, /* In */
			    U32 pipe_state                    /* In */ );

/*
 * Function: usbd_get_default_pipe_state()
 *
 * Description:
 *   The state of the device's default pipe will be returned (see
 *   usbd_get_pipe_state()).
 */
USBD_STATUS
usbd_get_default_pipe_state(USBD_DEVICE_HANDLE device_handle, /* In  */
			    U32 *pipe_state,                  /* Out */
			    U32 *endpoint_state,              /* Out */
			    U32 *request_count                /* Out */ );

/*
 * Function: usbd_set_interface_state()
 *
 * Description:
 *   The state of the interface may be one of the following:
 *      USBD_INTERFACE_ACTIVE - The interface will allow ipes to be opened
 *           and closed.  The state of pipes contained by the interface
 *           may not be USBD_PIPE_ACTIVE when the state of the interface
 *           is active when retreived with usbd_get_interface_state().
 *           When the interface's state is set to USBD_INTERFAE_ACTIVE all
 *           pipes associated with the interface will be placed in the
 *           USBD_PIPE_ACTIVE state.
 *      USBD_INTERFACE_STALLED - All associated pipes are moved to the
 *           USBD_PIPE_STALLED state.  The pipe's state may not be modified
 *           by usbd_set_pipe_state(), usbd_abort_pipe(), or usbd_reset_pipe()
 *           while the interface is in the USBD_INTERFACE_STALLED state.
 *      USBD_INTERFACE_IDLE - All associated pipes are moved to the
 *           USBD_PIPE_IDLE state.  The pipe's state may not be modified by
 *           usbd_set_pipe_state(), usbd_abort_pipe(), or usbd_reset_pipe()
 *           while the state of the interface is USBD_INTERFACE_IDLE.
 */
USBD_STATUS
usbd_set_interface_state(USBD_INTERFACE_HANDLE interface_handle, /* In */
			 U32 interface_state                     /* In */ );
#define USBD_INTERFACE_ACTIVE     0x0001
#define USBD_INTERFACE_STALLED    0x0002
#define USBD_INTERFACE_IDLE       0x0003
#define USBD_INTERFACE_STATE_MASK 0x0005


/*
 * Function: usbd_get_interface_state()
 * 
 * Description:
 *   Return the state of the interface described by USBD_INTERFACE_HANDLE.
 */
USBD_STATUS
usbd_get_interface_state(USBD_INTERFACE_HANDLE interface_handle, /* In  */
			 U32 *interface_state                    /* Out */ );

/*
 * Function: usbd_get_interface()
 *
 * Description:
 *   Return the current active interface and the number of alternate
 *   interface settings (does not include the default interface).  An
 *   active_interface of zero means that the default interface is
 *   currently in effect.  This function will setup and issue a
 *   GET_INTERFACE device request.
 */
USBD_STATUS
usbd_get_interface(USBD_INTERFACE_HANDLE interface_handle /* In  */,
		   U8 *active_interface                   /* Out */,
		   U8 *alternate_interface_count          /* Out */);

/*
 * Function: usbd_set_interface()
 *
 * Description:
 *   Change the alternate setting for an interface.  This function
 *   will setup a SET_INTERFACE device request and issue it to
 *   the device.  The new_interface_handle will be in effect if
 *   this routine returns USBD_NORMAL_COMPLETION.  The original
 *   interface_handle should not be used by the calling driver
 *   once this routine returns USBD_NORMAL_COMPLETION.
 */
USBD_STATUS
usbd_set_interface(USBD_INTERFACE_HANDLE interface_handle      /* In  */,
		   U8 alternate_interface                      /* In  */,
		   USBD_INTERFACE_HANDLE *new_interface_handle /* Out */);

/*
 * Function: usbd_get_device_state()
 *
 * Description:
 *   Return the current state of the device defined by 
 *   USBD_DEVICE_ATTACHED, USBD_DEVICE_POWERED, USBD_DEVICE_DEFAULT,
 *   USBD_DEVICE_ADDRESSED, USBD_DEVICE_CONFIGURED, and USBD_SUSPENDED.
 */
USBD_STATUS
usbd_get_device_state(USBD_DEVICE_HANDLE device_handle, /* In  */
		      U32 *device_state                 /* Out */ );
#define USBD_DEVICE_ATTACHED   0x0001
#define USBD_DEVICE_POWERED    0x0002
#define USBD_DEVICE_DEFAULT    0x0004
#define USBD_DEVICE_ADDRESSED  0x0008
#define USBD_DEVICE_CONFIGURED 0x0010
#define USBD_DEVICE_SUSPENDED  0x8000


/*
 * Function: usbd_set_device_state()
 *
 * Description:
 *   Set the state of the device descried by USBD_DEVICE_HANDLE to
 *   "device_state" which may be a combination of USBD_DEVICE_ATTACHED,
 *   USBD_DEVICE_POWERED, USBD_DEVICE_DEFAULT, USBD_DEVICE_ADDRESSED,
 *   USBD_DEVICE_CONFIGURED, and USBD_SUSPENDED.
 */
USBD_STATUS
usbd_set_device_state(USBD_DEVICE_HANDLE device_handle, /* In */
		      U32 device_state                  /* In */ );

/*
 * Function:  usbd_get_device_address()
 *
 * Description:
 *    Return the USB address of the device described by USBD_DEVICE_HANDLE.
 */
USBD_STATUS
usbd_get_device_address(USBD_DEVICE_HANDLE device_handle, /* In  */
			U8 *device_address                /* Out */ );

/*
 * Function: usbd_get_endpoint_number()
 *
 * Description:
 *    Return the endpoint number of the endpoint described by the given
 *    pipe handle.
 */
USBD_STATUS
usbd_get_endpoint_number(USBD_PIPE_HANDLE pipe_handle, /* In  */
			 U8 *endpoint_number           /* Out */ );

/*
 * Function: usbd_get_endpoint_count()
 *
 * Description:
 *   Return the number of endpoints contained by the interface described
 *   by USBE_INTERFACE_HANDLE.
 */
USBD_STATUS
usbd_get_endpoint_count(USBD_INTERFACE_HANDLE interface_handle, /* In  */
			U8 *endpoint_count                      /* Out */ );

/* 
 * Function: usbd_get_interface_count()
 *
 * Description:
 *   Return the number of default interfaces which the device described by
 *   USBD_DEVICE_HANDLE supports.
 */
USBD_STATUS
usbd_get_interface_count(USBD_DEVICE_HANDLE device_handle, /* In  */
			 U8 *ninterface                    /* Out */ );

/*
 * Function: usbd_get_usb_count()
 *
 * Description:
 *   Return the number of USB's which are currently configured on the system.
 */
U8
usbd_get_usb_count(void);

/*
 * Function: usbd_get_usb_handle()
 *
 * Description:
 *   Return the USBD_BUS_HANDLE associated with the supplied
 *   usb_index (zero based).
 */
USBD_STATUS
usbd_get_usb_handle(U32 usb_index,              /* In  */
		    USBD_BUS_HANDLE *bus_handle /* Out */ );

/*
 * Function: usbd_get_root_hub()
 *
 * Description:
 *   Return the device handle for the root hub associated with the
 *   given USBD_BUS_HANDLE handle.
 */
USBD_STATUS
usbd_get_root_hub(USBD_BUS_HANDLE bus_handle,       /* In  */
		  USBD_DEVICE_HANDLE *device_handle /* Out */ );

/*
 * Function: usbd_get_port_count()
 *
 * Description:
 *   Return the number of ports supported by the hub described by
 *   the USBD_DEVICE_HANDLE
 */
USBD_STATUS
usbd_get_port_count(USBD_DEVICE_HANDLE device_handle, /* In  */
		    U8 *nports                        /* Out */ );

/*
 * Function: usbd_hub2device_handle()
 *
 * Description:
 *   Return a handle for the device attached to the hub described by
 *   hub_handle and port number hub_port (starting with '1').
 */
USBD_STATUS
usbd_hub2device_handle(USBD_DEVICE_HANDLE hub_handle,    /* In  */
		       U8 hub_port,                      /* In  */
		       USBD_DEVICE_HANDLE *device_handle /* Out */ );

/*
 * Function: usbd_request2pipe_handle()
 *
 * Description:
 *   Return the USBD_PIPE_HANDLE associated with the given
 *   USBD_REQUEST_HANDLE.
 */
USBD_STATUS
usbd_request2pipe_handle(USBD_REQUEST_HANDLE request_handle, /* In  */
			 USBD_PIPE_HANDLE *pipe_handle       /* Out */ );

/*
 * Function: usbd_pipe2interface_handle()
 *
 * Description:
 *   Return the USBD_INTERFACE_HANDLE associated with the given
 *   USBD_PIPE_HANDLE.
 */
USBD_STATUS
usbd_pipe2interface_handle(USBD_PIPE_HANDLE pipe_handle,           /* In  */
			   USBD_INTERFACE_HANDLE *interface_handle /* Out */ );

/*
 * Function: usbd_interface2device_handle()
 *
 * Description:
 *    Return the USBD_DEVICE_HANDLE which is associated with the given
 *    USBD_INTERFACE_HANDLE handle.
 */
USBD_STATUS
usbd_interface2device_handle(USBD_INTERFACE_HANDLE interface_handle, /* In */
			     USBD_DEVICE_HANDLE *device_handle       /* Out*/);

/*
 * Function: usbd_device2bus_handle()
 *
 * Description:
 *   Return the USBD_BUS_HANDLE associated with the given USBD_DEVICE_HANDLE.
 */
USBD_STATUS
usbd_device2bus_handle(USBD_DEVICE_HANDLE device_handle, /* In  */
		       USBD_BUS_HANDLE *bus_handle       /* Out */ );

/*
 * Function: usbd_device2interface_handle()
 *
 * Descriptrion:
 *   Return the default USBD_INTERFACE_HANDLE associated with the
 *   supplied USBD_DEVICE_HANDLE and interface number (zero based).
 */
USBD_STATUS
usbd_device2interface_handle(USBD_DEVICE_HANDLE device_handle,       /* In */
			     U8 interface,                           /* In */
			     USBD_INTERFACE_HANDLE *interface_handle /* Out*/);

/*
 * Function: usbd_set_interface_private_handle()
 *
 * Description:
 *   Associate the given private interface driver handle with the
 *   specified USBD_INTERFACE_HANDLE.
 */
USBD_STATUS
usbd_set_interface_private_handle(USBD_INTERFACE_HANDLE interface_handle,
				  USBD_PRIVATE_HANDLE private_handle);

/*
 * Function: usbd_interface2private_handle()
 *
 * Description:
 *   Return the interface driver's private handle which is assocaited
 *   with the given USBD_INTERFACE_HANDLE.  The private handle is
 *   assocaited with the USBD_INTERFACE_HANDLE by the function
 *   usbd_set_interface_private_handle().
 */
USBD_STATUS
usbd_interface2private_handle(USBD_INTERFACE_HANDLE interface_handle,/* IN */
			      USBD_PRIVATE_HANDLE *private_handle    /* Out*/);

/*
 * Function: usbd_request2private_handle()
 *
 * Description:
 *   Return the private interface handle associated with the given
 *   request handle.  The private handle which is returned was assigned
 *   to the request at the time the request was setup by
 *   usbd_setup_request().
 */
USBD_STATUS
usbd_request2private_handle(USBD_REQUEST_HANDLE request_handle, /* In  */
			    USBD_PRIVATE_HANDLE *private_handle /* Out */ );

/*
 * Function: usbd_reference_pipe()
 *
 * Description:
 *   Increase the reference count for the pipe
 */
USBD_STATUS
usbd_reference_pipe(USBD_PIPE_HANDLE pipe_handle /* In */);

/*
 * Function: usbd_dereference_pipe()
 *
 * Description:
 *   Decrement the interface's reference count.
 */
USBD_STATUS
usbd_dereference_pipe(USBD_PIPE_HANDLE pipe_handle /* In */);

/*
 * Function: usbd_add_filter()
 *
 * Description:
 *   Add an interface filter driver.  The caller of this functio should
 *   load and configure the interface driver which sits ontop of the
 *   filter.  All transfers performed by the drivers above the filter
 *   will be "filtered" through the supplied functions.
 * 
 * This function is for future support.
 */
USBD_STATUS
usbd_add_filter(USBD_INTERFACE_HANDLE interface_handle, /* In */
		USBD_STATUS (*xfer_func)()              /* In */ );

#endif /* _USBDI_H_ */

