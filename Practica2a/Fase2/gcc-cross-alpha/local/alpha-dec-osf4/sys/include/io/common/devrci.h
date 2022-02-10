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
#ifndef _DEVRCI_H_
#define _DEVRCI_H_
/*
 * HISTORY
 */

#pragma ident "@(#)$RCSfile: devrci.h,v $ $Revision: 1.1.11.2 $ (DEC) $Date: 1998/08/26 20:58:27 $"

#include <sys/types.h>
#include <io/common/deveei.h>
#include <io/cam/scsi_all.h>

/*             
 * DEVice Reservation Control Interface
 *
 * DEVRCI is an abstract interface designed to support a hardware or
 * architecture specific device `Reservation' mechanism in the ASE and
 * TruClusters environments.  
 *
 * This interface should be implemented by device drivers that intend
 * to support `shared' devices in those environments.
 *
 * This interface returns the following errno statuses :
 *  
 *  ESUCCESS     - Operation was Successful
 *  EIO          - I/O related error, check additional status info. 
 *  ENXIO        - No path to this device exists.
 *  EINVAL 	 - Invalid parameter, opcode, or flag.
 *  ENOMEM 	 - Cannot allocate kernel buffer.
 *  EFAULT 	 - Problem copying to user space.
 *  EINTR        - Signal caught, interrupted. 
 *  EFAIL        - Request failed/incomplete.
 *  ETIMEDOUT    - I/O request timed out. 
 *  EOPNOTSUPP   - Illegal Request for this device/driver.
 *  ECONNREFUSED - Reservation Conflict enountered.
 *  ENODEV       - Device not there.
 *  ENOENT	 - Internal Error.
 *  EBUSY        - Device is busy.
 */

/* DEVRCI opcodes - (opcode) located in dev_rci_info struct */

#define RCI_PING_CMD       0x1   /* Returns architecture specific data     */
#define RCI_REGISTER_CMD   0x2   /* Register event callback function       */
#define RCI_DEREGISTER_CMD 0x3   /* DeRegister event callback function     */
#define RCI_PRESIN_CMD     0x4   /* Persistent Reservation IN              */
#define RCI_PRESOUT_CMD    0x5   /* Persistent Reservation OUT             */
#define RCI_GETEEI_CMD     0x6   /* Report driver specific EEI status      */ 
#define RCI_RESERVE_CMD    0x7   /* Uses RESERVE(6)                        */
#define RCI_RELEASE_CMD	   0x8   /* Uses RELEASE(6)                        */
#define RCI_GETSTATUS_CMD  0x10  /* Get Reservation Status (TUR)           */

/* DEVRCI flags - (flags) located in dev_rci_info struct */

#define RCI_OPFLAGS_MASK   0xFF   /* Opcode Flags or Qualifiers           */ 
#define RCI_FORCE_RESERVE  0x1    /* Force a "Reservation" on the device  */
#define RCI_FORCE_RESET    0x2    /* Reset before applying "Reservation"  */
#define RCI_EXTENDED_REQ   0x4    /* Use command extensions (e.g. ERM)    */
#define RCI_EXTENDED_REQ2  0x10   /* More command extensions              */


/* DEVRCI PRESIN/OUT Actions - (action) located in dev_rci_info struct */

#define RCI_ACT_REG    ALL_PROUT_REGISTER /* Read/Register a key	 */
#define RCI_ACT_RES    ALL_PROUT_RESERVE  /* Read/Create a reservation */
#define RCI_ACT_REL    ALL_PROUT_RELEASE  /* Release a reservation     */
#define RCI_ACT_CLR    ALL_PROUT_CLEAR    /* Clear all keys & reserves */
#define RCI_ACT_PRE    ALL_PROUT_PREEMPT  /* Preempt all keys & reserves */
#define RCI_ACT_PRECLR ALL_PROUT_PREEMPT_CLR   /* Preempt all keys & rserves */

/* DEVRCI PRESIN/OUT parameters - described by RCI_PRES_DATA struct */

typedef	u_long RCI_PRES_KEY;    /* Reservation Keys are 64 bit entities */

typedef struct rci_pres_type {
	u_char	aptpl;	        /* Persist through power loss 1 = on */
	u_char  type	:4,	/* Type	 */
#define RCI_TYP_RS    ALL_PROUT_READ_SHARED  /* Read Shared access  */
#define RCI_TYP_WE    ALL_PROUT_WRITE_EXC    /* Write Exclusive access */
#define RCI_TYP_RE    ALL_PROUT_READ_EXC     /* Read Exclusive access */
#define RCI_TYP_EA    ALL_PROUT_BOTH_EXC     /* Exclusive Access */
#define RCI_TYP_SA    ALL_PROUT_BOTH_SHARED  /* Shared Access */
#define RCI_TYP_WERO  ALL_PROUT_WRITE_EXC_RO /* Write Excl Registrants Only */
#define RCI_TYP_EARO  ALL_PROUT_BOTH_EXC_RO  /* Excl Access Registrants Only */
	        scope	:4;	/* Scope */
#define RCI_SC_LUN      ALL_PROUT_LU	  /* Applies to full logical unit  */
#define RCI_SC_EXTENT   ALL_PROUT_EXTENT  /* Applies to specified extent   */
#define RCI_SC_ELEMENT  ALL_PROUT_ELEMENT /* Applies to specified element  */
} RCI_PRES_TYPE;

typedef	struct rci_presin_hdr {
	u_int generation;		/* Generation number */
	u_int add_length;		/* Additional length */
} RCI_PRESIN_HDR;

typedef	struct rci_presin_reserve {
	RCI_PRES_KEY key;	/* 8 byte Key value */
	u_int   address;        /* Extent of Element address */
	RCI_PRES_TYPE ptype;	/* u_char: Reserved, u_char: Type & Scope */
	u_short	extent_len;	/* Extent length */
} RCI_PRESIN_RESERVE;

typedef	struct rci_presout_param {
	RCI_PRES_KEY key;	/* 8 byte Key value */
	RCI_PRES_KEY sa_key;	/* Service Action Key */
	u_int	address;	/* Extent  or Element address */
	RCI_PRES_TYPE ptype;	/* u_char: aptpl, u_char: Type & Scope */
	u_short	extent_len;	/* Extent length  */
} RCI_PRESOUT_PARAM;

typedef struct rci_pres_data {
  int length;       /* input  : .length : size of input/output buffer */
  int retlen;       /* output : .retlen : number of bytes returned */
  int number;       /* in/out : .number : number of descriptors input/output */
  caddr_t addr;     /* output : .addr   : address of i/o buffer */ 
} RCI_PRES_DATA;

/* The rci_data struct : data descriptor */

typedef struct rci_data {  
  int length;       /* input  : .length : size of input/output buffer */
  int retlen;       /* output : .retlen : number of bytes returned */
  caddr_t addr;     /* ouput  : .addr   : address of i/o buffer */ 
} RCI_DATA;

/* The rci_reg struct : data descriptor. 

   The term `port' refers to the rci_reg struct callback address.
   Each unique callback routine also registers for error notification
   with the event_register() function.  

*/

typedef struct rci_reg {   
  u_int type;            /* Input : `port' specific event type */
  void (*callback) ();   /* Input : Address of callback routine */
} RCI_REG;

/*  The DEVRCI ioctl data structure */

#define RCI_VERSION  0x02     /* DEVRCI data structure version changes   */ 

typedef struct dev_rci_info {
  u_int version;
  u_int opcode;           /* input        : IOCTL Function (sub-command) */    
  u_int flags;	          /* input        : Functional flags (modifier)  */
  u_int action;           /* input        : PresIN/OUT: Service Action   */
  time_t timeo;           /* input        : Timeout value in seconds     */
  u_int retry;            /* input        : Number of retrys allowed     */
  dev_t dev;              /* input        : The device's dev_t           */
  u_int reserved[2];      /* Reserved for Steel HW-ID */
  union {
    struct rci_reg reg;   /* input        : RCI_REG descriptor           */
    struct rci_data data; /* input/output : RCI_DATA descriptor          */
    struct rci_pres_data pres; /* in/out  : RCI_PRES_DATA descriptor     */
    u_long unknown[8];    /*              : Room to grow                 */
  } cmd;
  DEV_EEI_STATUS *eei;    /* output       : (DEV_EEI_STATUS *) NULL      */
} DEV_RCI_INFO;

/*
 * ioctl entry point to set/maintain device "Reservations" 
 */
#define DEVRCI	_IOWR('v', 1, DEV_RCI_INFO)

/*---------------------------------------------------------------------
 *
 * Event Registration (RCI_REGISTER_CMD / RCI_DEREGISTER_CMD) :
 *
 *   The DEVRCI Event Registration mechanism (RCI_REGISTER_CMD) is
 *   used to register a callback function with DEVRCI.  This callback
 *   is used to notify the consumer (other drivers or kernel
 *   components) of asynchronous or out of band `error events' that
 *   occur on the device.
 *
 *   The implementation of this mechanism is driver dependent and
 *   usually achieved via the use of one or more I/O subsystem or
 *   architecture specific callback mechanisms (e.g., CAM async and
 *   function complete callbacks.).  This means that a registered
 *   callback function will be called with an ARCHITECTURE SPECIFIC
 *   parameter that describes the device in question and the error
 *   that has occurred (e.g. a CAM ccb).  In order to write a callback
 *   function, agreement as to what this parameter is must be reached
 *   between the driver writer and the consumer (the DEVRCI agent).
 *
 *   The following table describes the implemented architectures and
 *   their callback function parameters:
 *
 *   Architecture:   Callback parameters:         Mechanism used: 
 *   =============   ====================         ===============
 *       CAM         callback(dev_t, eei_status)  event_register(dev_t..)
 * 
 *   NOTE : It should also be noted that the DEVRCI Registration
 *          mechanism is not supported from user space.  All callback
 *          functions, parameters and data must reside in kernel
 *          space.  A callback function located in SEG0_VA space will
 *          result in an EINVAL status.
 *
 * Event Notification :
 *
 *   To support DEVRCI Event Registration, each driver will have to
 *   integrate an Error Event notification mechanism into its I/O
 *   completion process.  This means that, as agreed to by the writer
 *   of the callback function, the DEVRCI/device driver writer will
 *   have to call the registered callback function every time a device
 *   error is encountered.  This way the DEVRCI agent will be called
 *   every time an error occurs, regardless of who originated the I/O.
 *
 *   The following table describes the Event Notification mechanisms
 *   implemented for each supported architecture.
 *
 *   Architecture:    Mechanism used:    
 *   =============    ===============    
 *       CAM          event_notify(dev_t)
 * 
 *   Note: The event_register() and event notify() functions are a
 *   part of the common Error Event notification subsystem
 *   (error_event.c).  The routines in this module provide the basic
 *   registration mechanisms needed to dynamically register and
 *   deregister callback functions.  
 *
 *   For more information about Error Event notification please see
 *   <io/common/error_event.c>
 *
 * ---------------------------------------------------------------------
 *                         General Requirements
 *
 * General Device Driver Requirements for all DEVRCI I/O operations :
 *
 *  The General Device Driver Requirements for DEVRCI I/O operations
 *  fall into two catagoreis: all DEVRCI I/O operations must be
 *  interruptible, and executed synchonously (Synchonous and
 *  Interruptible Operation); and all DEVRCI I/O operations must be
 *  callable before the device has been Opened (Promiscuous Open)
 *  
 *  Synchronous and Interruptible operation :
 *
 *   All DEVRCI I/O operations are synchronous and interruptible: this
 *   requirement does not mean that the device driver cannot sleep
 *   while waiting for I/O's to complete.  Rather, this means that -
 *   unless a timeout or interrupt condition is encountered - I/O's
 *   done on behalf of DEVRCI must be completed immediately, and
 *   processed in the context of the caller.  The driver can not treat
 *   a DEVRCI Reserve or Release operation as an asynchronous request
 *   to be completed at its own convenience; putting it on a queue to
 *   be processed later, after, e.g., error recovery.  This rule also
 *   precludes the use of asynchronous hardware mechanisms [e.g. the
 *   immediate bit in SCSI-2 (if it where ever supported with a SCSI
 *   Reserve CDB)].
 *
 *   The use of mpsleep, timeout and abort :
 *
 *   In order to implement the DEVRCI interrupt/timeout mechanism,
 *   DEVRCI must be well integrated into the driver.  Any sleeps done
 *   by the driver must be interruptible and subject to the timeout
 *   mechanism implemented to support the DEV_RCI_INFO timeo
 *   parameter.  If an I/O operation times out then the operation is
 *   aborted and a failing status is returned immediately, without
 *   waiting for the abort to complete.  Under such circumstances the
 *   driver is expected to cleanup the aborted I/O, independent of the
 *   callers thread.
 *
 *   Caller specific Timeouts & Retrys (timeo / retrys) :
 *
 *   For all I/O related DEVRCI operations timeouts and retrys are
 *   controlled by the caller provided `timeo' and `retry' parameters.
 *   The `timeo' parameter is value in seconds used determine the
 *   maximum amount of time a single I/O can take before timing out.
 *   The `retry' parameter is a number used to determine how many
 *   times the driver is allowed to retry the operation when a
 *   non-critical error is encountered (e.g. a bus busy condition).
 *   This gives the caller maximum control over what the driver will
 *   do.
 *
 *   The maximum time an DEVRCI I/O call can take, in seconds, is
 *   determined by the equation `timeout = (timeo * (retry + 1))'.
 *
 *   A timeo value of zero will result in an implicit DEVRCI request
 *   with a returned status.  This means the requested operation will
 *   be performed, by a call to the driver, without doing any device
 *   access.
 * 
 *   DEVRCI requests that timeout will return an ETIMEDOUT status.  
 *
 *   Signals :
 *
 *   All I/O operations are interruptible (with SIGINT) and DEVRCI
 *   calls that have been interrupted in this manner should return an
 *   EINTR status.
 *
 *  Promiscuous Open :
 *
 *   All DEVRCI I/O operations must be callable _before_ the device is
 *   Opened.  This is because, aside from being called via the
 *   standard ioctl interface, DEVRCI is also called by a number of
 *   Kernel interfaces, some requiring access to the device before it
 *   has actually been opened.  Taken together with the other General
 *   Device Driver Requirements, this requirement means that the
 *   implementation of DEVRCI in a given driver may require additional
 *   work in its open flows.  Some sort of a `benign' or `promiscuous'
 *   open operation may be needed to preserve device state information
 *   and facilitate DEVRCI requests while the device is closed.  
 * 
 *   What this usually means is, in the driver specific ioctl routine,
 *   where DEVRCI is usually implemented, work must be done to insure
 *   that the ioctl entry point can be called before the device has
 *   been opened.  This is often already the case since other kernel
 *   facilities (e.g. getsysinfo()) already do this... however, with
 *   DEVRCI, care must be taken, in order to meet the aforementioned
 *   Synchronous and Interruptible Operation requirement.
 *   
 * ---------------------------------------------------------------------
 *                    Function and Data Descriptions
 *
 *  Extended Request Mechanism (RCI_EXTENDED_REQ & RCI_EXTENDED_REQ2) : 
 *
 *   The Extended Request Mechanism (ERM) is intended to support both
 *   architecture specific extensions to the PING, RESERVE, RELEASE
 *   and GETSTATUS commands [e.g., Reservation Extents with SCSI disks
 *   and Element Reservations with SCSI media changes], and command
 *   specific semantics with the Persistent Reservation IN/OUT
 *   commands.  
 *
 *   To use the ERM mechanism simply enable the RCI_EXTENDED_REQ/REQ2
 *   flags in the ioctl data `flags' field.  For more information, see
 *   the Opcode descriptions of this flag for each command below.
 *
 *  Opcodes, Flags, Data and Status (DEV_RCI_INFO) : 
 *
 *   Each DEVRCI opcode is implemented as a separate sub-command and
 *   returns its own errno status.  If desired, addition status
 *   information can be reported with EEI statuses in the `eei'
 *   variable.  In order to obtain an EEI status simply allocate a
 *   DEV_EEI_INFO structure and insert its address into the `eei'
 *   field of the DEV_RCI_INFO structure.  
 * 
 *   See </usr/include/sys/deveei.h> or <.io/common/deveei.h>
 *   for more information about EEI statuses.
 *
 *   Note: If an ioctl call fails with an ENXIO or EOPNOTSUPP status,
 *         this could indicates that the driver/architecture is
 *         unsupported (the DEVRCI ioctl has not been implemented for
 *         the requested device or driver).
 *
 *   For each DEVRCI opcode, the following flags, parameters and
 *   status apply:
 *
 *  Command data (RCI_DATA) :
 * 
 *   Some DEVRCI commands return data.  For these commands, the RCI_DATA
 *   structure is used to describe the return data.  To use this
 *   descriptor the address of the consumers data buffer is put in the
 *   `addr' field, and its size into the `length' field.
 *   
 *   If no `addr' is provided (addr == NULL) then the
 *   operation is completed with only a status returned.  The data is
 *   discarded.  If a valid `addr' is provided and the `length'
 *   field is invalid [<= 0] an EINVAL status is returned.  
 *
 *   Both KSEG or SEG0 data buffer addresses can be used.
 *
 *  Persistent Reserve Command data (RCI_PRES_DATA) :
 * 
 *   The DEVRCI RCI_PRESIN_CMD & RCI_PRESOUT_CMD commands require both
 *   data in and data out support.  For these commands, the
 *   RCI_PRES_DATA structure is used to describe the input/output
 *   data.  To use this descriptor the address of the callers data
 *   buffer is put in the `addr' field, and its size into the `length'
 *   field.  The number of bytes read is retuned in the `retlen'
 *   field, and the number of reservation descriptors or keys is
 *   returned in the `number' field.  The `number' field is also used
 *   as input to describe the number of (RCI_PRESIN_RESERVE)
 *   reservation descriptors provided for a Persisent Reservation
 *   Extended Request (more at Opcode : RCI_PRESOUT_CMD).
 *  
 *   If no `addr' is provided (addr == NULL) an EINVAL staus is returned. 
 *   
 *   Both KSEG or SEG0 data buffer addresses can be used.
 *
 * ---------------------------------------------------------------------
 *                   Command Specific Requirements
 * 
 *  Device Reservations (RCI_RESERVE_CMD / RCI_RELEASE_CMD) :
 *
 *  Not all devices support a concept of device `Reservations' at the
 *  hardware level.  If a device/driver cannot implement such a
 *  function an EOPNOTSUPP error status should be returned for the
 *  DEVRCI Reserve and Release functions.  Otherwise, upon
 *  implementation of DEVRCI, it will be incumbent upon the device
 *  driver writer to enforce the following rules in the device
 *  driver:
 *
 *   1) Reservations shall be persistent between close and open.
 *
 *   2) Device Reservations or re-Reservations (i.e. automatic or
 *      transparent Reservations) shall not be done by the driver.
 *
 *   3) Between Reserve and Release, media access shall not be allowed
 *      unless a device Reservation is in force (i.e. applied).
 *
 *   4) Between Open and Close, media access shall not be allowed
 *      after a `Reservation Conflict' has been detected.
 *
 *  The Device Reservation model :
 *
 *   In order to understand how to implement DEVRCI, the DEVRCI
 *   Reserve/Release operation (ioctl call) should be thought of as an
 *   implicit `assert/deassert' instruction with an explicit
 *   `apply/remove' operation.  That is to say, a DEVRCI Reserve
 *   request implicitly asserts a `Reserved state' in the driver and
 *   explicitly applies a `Reservation' to the device.  If the
 *   Reservation cannot be applied to the device synchronously, within
 *   the context of the DEVRCI ioctl call, a error status is returned
 *   to the caller but the `Reservation' is still considered to be
 *   asserted, in the driver.  While the device driver maintains the
 *   asserted Reservation state for the device, it never, in and of
 *   its self, applies a Reservation to the device.  Reservations are
 *   only applied explicitly, as a part of the DEVRCI Reserve
 *   operation.  Once a Reservation has been asserted in the driver,
 *   the driver must insure that the media access rules (4 & 5) are
 *   enforced; unless and until a DEVRCI operation either deasserts or
 *   applies the Reservation.
 * 
 *  Reservation persistence :
 *
 *   Once a Reservation has been asserted by DEVRCI, the Reserve
 *   `state' in the driver must be preserved between closes and opens.
 *   This is because the device driver's `Reservation state' is
 *   controlled and maintained by DEVRCI exclusively; regardless of
 *   whether the device is open or not.  
 *
 *  No automatic re-Reservation :
 *
 *   Once the DEVRCI is implemented, the device driver should never,
 *   in and of itself, apply a Reservation to the device.
 *   Reservations are applied explicitly as a part of the DEVRCI
 *   Reserve operation.  If a Reservation is `lost', for any reason,
 *   it is the responsibility of the DEVRCI agent to re-apply the
 *   Reservation.  Reservations are lost due to changes in the device
 *   state brought about by events such as bus resets, device resets
 *   and/or other hardware specific failures.  Under such conditions
 *   the DEVRCI agent is notified of the lost Reservation via the
 *   Event Notify mechanism and is expected to either re-Reserve or
 *   Release the device, according to its own policy.
 *
 *  No media access unless a device Reservation is applied :
 *
 *   Upon receiving a DEVRCI Reserve request the device driver shall
 *   enforce a state where media access is only allowed as long as
 *   there is a Reservation `applied' to the device.  Immediately
 *   following a DEVRCI Reserve request, if no Reservation is applied
 *   to the device, or if the Reservation is lost, the device driver
 *   shall restrict access to the media by either stalling or failing
 *   I/Os.  One example of this would be when a Reservation is lost
 *   because of a reset condition.  Another example would be when a an
 *   implicit DEVRCI Reservation request (a Reserve request with a
 *   timeo value of zero) asserts a Reservation without applying one
 *   to the device.  Under such conditions, the device driver shall
 *   not allow any read or write operations to the device unless and
 *   until a DEVRCI Reserve or Release request clears the condition.
 *      
 *  No media access after a Reservation Conflict (Fast-stop/fail):
 *  
 *   Upon detecting a Reservation Conflict condition, the device
 *   driver shall restrict access to the device media unless and until
 *   the device is closed and the condition is cleared by a DEVRCI
 *   Reserve/Release operation.  Reservation Conflicts are considered
 *   `lost' Reservations and are treated, according to the rules, as a
 *   condition to be handled by the DEVRCI agent (which is notified of
 *   the condition via Event Notification).
 *
 *   It should be noted that, with Reservation Conflicts treated as
 *   lost Reservations, while the `Reservation Conflict' condition is
 *   cleared by close, access to the device media is still determined
 *   by the Reservation state of the device.  An example of this would
 *   be a Reservation Conflict encountered by a write operation after
 *   a DEVRCI Reserve.  If, after the application closes and re-opens
 *   the device, the DEVRCI agent has not re-applied the device
 *   Reservation, media access is disallowed.  Then again, if, after
 *   being notified of the Reservation Conflict (via Event Notify),
 *   the DEVRCI agent Releases the device, media access is still not
 *   granted until the application closes and re-opens the device.
 *
 *   Note: The behaivor described above has sometimes been refered to
 *         as a Fast-stop/fail policy.  To wit, upon encountering a 
 *         Reservation Conflict, the driver should Stop immediately,
 *         and Fail all of its I/O until told to do otherwise.
 *
 * ---------------------------------------------------------------------
 * 
 *  Persistent Reservations (RCI_PRESIN_CMD / RCI_PRESOUT_CMD) :
 *
 *   As of Digital Unix V4.0e support has been added to the DEVRCI
 *   interface for SCSI-3 Persistent Reservations (PR).  Because
 *   Persistent Reservations are so unique, less of an attempt has
 *   been made to abstract them from the caller.  Also, because PRs
 *   differ significantly in their application and use, this section
 *   has been added to compare and contrast the Persistent Reservation
 *   functional requirements with the Device Reservation requirements.
 *
 *   If a device or driver has not implemented support for Persistent
 *   Reservations an EOPNOTSUPP error status should be returned for
 *   the DEVRCI Persistent Reserve IN and Persistent Reserve OUT.
 *
 *  The Persistent Reservation model :
 * 
 *   The DEVRCI Peristent Reservation model differs from the Device
 *   Reservation model significantly.  Firstly, there is no idea of a
 *   an implicit `assert/deassert' or explicit `apply/remove' anymore.
 *   This is mostly because, given the SCSI-3 functionality itself,
 *   this kind of functionality, in the driver, is not needed.  It
 *   takes multiple calls to effectively Register, Read and Preempt a
 *   Persistent Reservation, and many of the synchronization issues
 *   addressed by the `assert/deassert' model are taken into account
 *   in the SCSI-3 Persistent Reservation design and specification
 *   itself.  Futhremore, many of the functional requirements of the
 *   Device Reservation model are now being achieved with DRD (the
 *   main consumer of Persistent Reservations) by using funtions like
 *   event_notify and CAM_MUNSA_REJECT.  And These functions will be
 *   leveraged to implement support for Persistent Resevations
 *   (e.g. Reservation Conflicts, Unit Attentions, etc., as well as
 *   Bus Resets to implement Fast-stop/fail policies) in DRD.
 *
 *   Unlike the Device Reservation model, the DEVRCI Persistent
 *   Reservation model looks like a standard I/O interface; along with
 *   the guarantees provided by the General Device Driver Requirements
 *   (cf. General Requirements).  It will be up to the caller to
 *   explicitly manage the Persistent Reservation, and to deal with
 *   any and all synchronization issues, on a device by device basis.
 * 
 *  General Requirements for Persistent Reserve operations :
 *
 *   The General Requirements for Persistent Reservation do not differ
 *   from the General Requirements for all DEVRCI I/O operations.
 *
 *   In summary:
 *    
 *     All mpsleeps done by the driver on behalf of the PR operation
 *     must be interruptible.
 * 
 *     All PR operations should honor the Timeout & Retry requirements
 *     and insure the callers context will not be "stolen" to do other
 *     work.
 *
 *        Note: This also means that any memory allocation done in the
 *        context of the caller should use the NO_WAIT flag - unless a
 *        suitable memory allocation mechanism is implemented in the
 *        driver, honoring the callers Timeout.
 * 
 *     In cases where memory cannot be obtained in a timely manner
 *     ENOMEM should be returned.
 *
 *     In cases where the Timeout quantum expires, the driver should
 *     abort any outstanding IO and immediately return ETIMEDOUT,
 *     freeing the callers context as soon as possible.  (I/O rundown
 *     for the aborted I/O should be handled by the driver, in
 *     interrupt context.)
 *  
 *   Please refer to the General Requirements section above for more
 *   information.
 * 
 *  Reservation persistence :
 *
 *   Reservation Persistence is now provided by the device.  That is
 *   to say, with Persistent Reservations access to the device is
 *   explicitly enforced by the SCSI device itself.  Furthermore,
 *   since Persistent Reservations cannot be inadvertently cleared or
 *   lost (by a Bus Reset), the requirements upon the device driver to
 *   preserve the reservation "State" of the device have been laxed.
 *
 *  No automatic re-Reservation :
 *
 *   As with Device Reservations, Persistent Reservations are managed
 *   completely by the caller.  No automatic re-Reservations should be
 *   done by the driver.  This should be a noop.
 *
 *  No media access unless a device Reservation is applied :
 *   
 *   As described above, these guarantees have been supplied by the
 *   device with Persistent Reservations, therefore the requrements
 *   upon the driver are laxed (modulo the requrements of
 *   CAM_MUNSA_REJECT, etc.)
 *      
 *  No media access after a Reservation Conflict (Fast-stop/fail):
 *  
 *   Same as above.  Although a Fast-stop/fail policy may need to be
 *   implemented in driver to support this requirement in the ioctl,
 *   the current DRD implementation will use other means to achieve
 *   these ends (i.e. CAM_MUNSA_REJECT).
 *
 * ---------------------------------------------------------------------
 *                       Opcode Descriptions
 * 
 *  Opcode : RCI_PING_CMD
 *
 *      The RCI_PING_CMD will do a non-intrusive `ping' of the device
 *      and return architecture specific data in the RCI_DATA buffer.
 *
 *    Flags :  RCI_EXTENDED_REQ
 *
 *      With the RCI_EXTENEDED_REQ flag set the `ping' function will
 *      return a "unique" device id string.  If no such device id
 *      string is supported an EOPNOTSUPP status will be returned.
 *
 *    Timeo & Retry : Supported.
 *
 *    Cmd : RCI_DATA descriptor (input/output).
 * 
 *    Return Status : 
 *
 *      ESUCCESS     
 *	EINVAL 	     - Invalid parameter, opcode, or flag.
 *	ENXIO        - No path to this device exists.
 *	ENOMEM 	     - Cannot allocate kernel buffer.
 *	EFAULT 	     - Problem copying to user space (EEI or RCI_DATA).
 *      EINTR        - Signal caught, interrupted. 
 *      ETIMEDOUT    - I/O request timed out. 
 *      EOPNOTSUPP   - Illegal Request for this device.
 *      ENODEV       - Device not there (selection timeout).
 *      ENOENT	     - Internal Error (e.g. failed to setup async callback).
 *      EBUSY        - Device is busy (e.g. SCSI Busy status received).
 *
 *    EEI status : supported
 *
 * ---------------------------------------------------------------------
 *
 *  Opcode : RCI_REGISTER_CMD
 * 
 *      The RCI_REGISTER_CMD will register an architecture specific
 *      event callback function with the DEVRCI.
 *
 *    Flags :  None
 *
 *    Timeo & Retry : Not Supported.
 *
 *    Cmd : RCI_REG descriptor (input).
 *
 *    Return Status : 
 *
 *      ESUCCESS     
 *	EINVAL 	     - Invalid parameter, opcode, or flag.
 *	ENOMEM 	     - Cannot allocate kernel buffer.
 *      ENOENT	     - Internal Error (e.g. failed to setup async callback).
 *      ENXIO        - No path to this device exists.
 *
 *    EEI status : Not supported
 * 
 * ---------------------------------------------------------------------
 *
 *  Opcode : RCI_DEREGISTER_CMD
 *
 *      The RCI_DEREGISTER_CMD is used to de-register event callback
 *      functions.
 *
 *    Flags :  RCI_RESET
 *
 *    Timeo & Retry : Not Supported.
 *
 *    Cmd : RCI_REG descriptor (input).
 *
 *    Return Status : 
 *
 *      ESUCCESS     
 *	EINVAL 	     - Invalid parameter, opcode, or flag.
 *	ENOMEM 	     - Cannot allocate kernel buffer.
 *      ENOENT	     - Internal Error (e.g. failed to setup async callback).
 *      ENXIO        - No path to this device exists.
 *
 *    EEI status : Not supported
 *
 * ---------------------------------------------------------------------
 *
 *  Opcode : RCI_PRESIN_CMD
 *
 *      RCI_PRESIN_CMD will `Read' the Keys or Reservations currently
 *      active on the device.
 *
 *    Timeo & Retry : Supported.
 *
 *    Cmd : (output) RCI_PRES_DATA descriptor (see structure definition).
 *
 *    Action : RCI_ACT_REG & RCI_ACT_RES
 *     
 *      With the `action' field set to RCI_ACT_REG, a RCI_PRESIN_HDR
 *      structure (described by the RCI_PRES_DATA structure) is
 *      returned, followed by a list of RCI_PRES_KEY structures
 *      describing the Registered Keys in the device.
 *
 *      With the `action' field set to RCI_ACT_RES, a RCI_PRESIN_HDR
 *      structure (described by the RCI_PRES_DATA structure) is
 *      returned, followed by a list of RCI_PRESIN_RESERVE structures
 *      describing the Reservations in the device.
 *       
 *    Flags :  None.
 *
 *    Return Status : 
 *
 *      ESUCCESS     - Operation was Successful
 *	EINVAL 	     - Invalid parameter, opcode, or flag.
 *	ENOMEM 	     - Cannot allocate kernel buffer.
 *      EINTR        - Signal caught, interrupted 
 *      ETIMEDOUT    - I/O request timed out      
 *	ENXIO        - No path to this device exists.
 *      ENODEV       - Device not there (i.e. Selection Timeout).
 *      EIO          - I/O related error, check additional status info. 
 *      EOPNOTSUPP   - Illegal Request for this device.
 *      ECONNREFUSED - Reservation Conflict encountered.
 *      EBUSY        - Device is busy (e.g. SCSI Busy status received).
 *      ENOENT	     - Internal Error (e.g. failed to setup async callback).
 *
 *    EEI status : supported
 *
 * 	EFAULT - Problem copying either EEI output or RCI_PRES_DATA input.
 *               (Reservation state unknown).
 * 
 * ---------------------------------------------------------------------
 *
 *  Opcode : RCI_PRESOUT_CMD
 *
 *      RCI_PRESOUT_CMD will `Write' the provided RCI_PRESOUT_PARAM
 *      descriptor (described by the RCI_PRES_DATA structure) to the
 *      device.  The Action describes the PR Action to be acomplished.
 *
 *      For more information please refer directly to the SCSI-3 SPC-2
 *      specification.
 *
 *    Timeo & Retry : Supported.
 *
 *    Cmd : (input) RCI_PRES_DATA descriptor (see structure definition).
 *
 *    Action : RCI_ACT_REG, RCI_ACT_RES, RCI_ACT_REL, RCI_ACT_CLR,
 *             RCI_ACT_PRE, and RCI_ACT_PRECLR 
 *      
 *      All Action codes require a valid RCI_PRESOUT_PARAM descriptor,
 *      filled in by the caller.  The caller fills in this descriptor
 *      to describe the SCSI-3 Persistent Reserve Key, Service Action
 *      Key, Scope, Type, APTPL bit, and (if needed) Extent address
 *      and length.  
 *
 *      RCI_ACT_REG     - Register a key
 *      RCI_ACT_RES     - Create a Reservation
 *      RCI_ACT_REL     - Release a Reservation    
 *      RCI_ACT_CLR     - Clear all Keys/Reservations
 *      RCI_ACT_PRE     - Preempt all Keys/Reservations
 *      RCI_ACT_PRECLR  - Preempt & Clear all Keys/Reservations 
 *
 *    Flags :  RCI_EXTENDED_REQ  & RCI_EXTENDED_REQ2
 *
 *      When no `flags' are set, the RCI_PRES_DATA descriptor
 *      describes a single RCI_PRESOUT_PARAM structure, filled in by
 *      the caller.  (This is always true, for every possible
 *      combination of RCI_PRESOUT_CMD Actions and Flags).
 *
 *      When RCI_EXTENDED_REQ is set the driver will interpret the
 *      input data as a list of descriptors to be processed
 *      consecutively, on the same device.  When this flag is set the
 *      caller should provide a single RCI_PRESOUT_PARAM structure (or
 *      descriptor) followed by a list of RCI_PRESIN_RESERVE
 *      descriptors.  All descriptors must be filled in with valid
 *      data and the total number RCI_PRESOUT_PARAM and
 *      RCI_PRESIN_RESERVE descriptors written into the
 *      RCI_PRESOUT_PARAM `number' field.  This way, with a single
 *      RCI_PRESOUT_CMD call, multiple Persistent Reservation
 *      operations can occur.
 *
 *      When RCI_EXTENDED_REQ2 is set the driver will interpret the
 *      input data as a RCI_PRESOUT_PARAM structure, followed by a
 *      list of RCI_PRES_KEYs.
 *      
 *      Note: in the RCI_PRESOUT_PARAM structure, the RCI_PRES_TYPE
 *            substructure is used to describe the Scope, Type, and
 *            APTPL bit.  Additionally, the RCI_PRESIN_RESERVE input
 *            structure is used in the RCI_PRES_TYPE structure.  These
 *            structures are defined in such a way as to allow the
 *            caller to make efficient us of the `Read' and `Preempt
 *            and Clear' Reservation operations.  To wit, after
 *            `reading' the Reservations in the device, the caller can
 *            (by overlaying the RCI_PRESIN_HDR and the first
 *            RCI_PRESIN_RESERVE structures with a RCI_PRESOUT_PARAM
 *            structure) use the same list of RCI_PRESIN_RESERVE
 *            structures to Prempt and Clear all of the Reservations
 *            in the device.  All that would need to be done is to
 *            fill in the RCI_PRESOUT_PARAM `key' (overlaying the
 *            RCI_PRESIN_HDR) and the RCI_PRES_TYPE `aptpl' value in
 *            all of the returned RCI_PRESIN_RESERVE structures.
 * 
 *    Return Status : 
 *
 *      ESUCCESS     - Operation was Successful
 *	EINVAL 	     - Invalid parameter, opcode, or flag.
 *	ENOMEM 	     - Cannot allocate kernel buffer.
 *      EINTR        - Signal caught, interrupted 
 *      ETIMEDOUT    - I/O request timed out      
 *	ENXIO        - No path to this device exists.
 *      ENODEV       - Device not there (i.e. Selection Timeout).
 *      EIO          - I/O related error, check additional status info. 
 *      EOPNOTSUPP   - Illegal Request for this device.
 *      ECONNREFUSED - Reservation Conflict encountered.
 *      EBUSY        - Device is busy (e.g. SCSI Busy status received).
 *      ENOENT	     - Internal Error (e.g. failed to setup async callback).
 *
 *    EEI status : supported
 *
 * 	EFAULT - Problem copying either EEI output or RCI_PRES_DATA input.
 *               (Reservation state unknown).
 * 
 * ---------------------------------------------------------------------
 *
 *  Opcode : RCI_RESERVE_CMD
 *
 *      RCI_RESERVE_CMD will `Reserve' the device, at the hardware
 *      level, by means of an architecture specific mechanism.
 *
 *    Flags :  RCI_EXTENDED_REQ, RCI_FORCE_RESERVE, RCI_FORCE_RESET
 * 
 *      The RCI_EXTENEDED_REQ flag modifies the `Reserve' function to
 *      use a device driver specific mechanism described by the
 *      dev_t device specific or `partition' bits in the dev_t.
 *
 *        This flag is intended to support architecture specific
 *        extensions to the Reservation command.  Since RCI is
 *        considered a part of the driver, each driver will implement
 *        support for the RCI_EXTENEDED_REQ flag differently.  Setting
 *        this flag, by definition, tells the `Reserve' function to
 *        consider the device specific bits in the dev_t while
 *        asserting & applying the Reservation.
 * 
 *        Support of the RCI_EXTENEDED_REQ flag is implementation
 *        specific.  If this flag is not supported by a specific
 *        implementation an EOPNOTSUPP status will be returned.
 *
 *      The RCI_FORCE_RESERVE flag modifies the Reserve function to
 *      clear any Reservation Conflict encountered AFTER attempting to
 *      Reserve the device.
 *    
 *      The RCI_RESET_RESET flag modifies the Reserve function to
 *      `reset' the device (thereby clearing any Reservation Conflict
 *      condition) BEFORE Reserving the device.
 *
 *      Note: RCI_FORCE_RESET and RCI_FORCE_RESERVE can result in the
 *            loss of all existing `Extended Reservations'.
 *
 *    Timeo & Retry : Supported.
 *
 *    Cmd : None.
 * 
 *    Return Status : 
 *
 *      ESUCCESS     - Operation was Successful
 *	EINVAL 	     - Invalid parameter, opcode, or flag.
 *	ENOMEM 	     - Cannot allocate kernel buffer.
 *      EINTR        - Signal caught, interrupted 
 *      ETIMEDOUT    - I/O request timed out      
 *	ENXIO        - No path to this device exists.
 *      ENODEV       - Device not there (i.e. Selection Timeout).
 *      EIO          - I/O related error, check additional status info. 
 *      EOPNOTSUPP   - Illegal Request for this device.
 *      ECONNREFUSED - Reservation Conflict encountered.
 *      EBUSY        - Device is busy (e.g. SCSI Busy status received).
 *      ENOENT	     - Internal Error (e.g. failed to setup async callback).
 *      EFAIL        - Reset done but request incomplete. (The Reservation 
 *                     state is unknown).
 *
 *    EEI status : supported
 *
 *	EFAULT 	     - Problem copying EEI information to user space.
 *                     (Reservation state unknown).
 * 
 * ---------------------------------------------------------------------
 *
 *  Opcode : RCI_RELEASE_CMD
 *
 *      The RCI_RELEASE_CMD command is the counter part for the
 *      `Reserve' command.  RCI_RELEASE_CMD will `Release' the device,
 *      at the hardware level, by means of an architecture specific
 *      mechanism.
 *
 *    Flags :  RCI_EXTENDED_REQ
 * 
 *      The RCI_EXTENEDED_REQ flag modifies the `Release' function.
 *      This flag instructs the `Release' function to consider the
 *      device specific or partition bits in the dev_t while releasing
 *      the device.  Support of the RCI_EXTENEDED_REQ flag is
 *      implementation specific.  If this flag is not supported by a
 *      specific implementation an EOPNOTSUPP status will be returned.
 *
 *    Timeo & Retry : Supported.
 *
 *    Cmd : None.
 * 
 *    Return Status : 
 *
 *      ESUCCESS     - Operation was Successful
 *	EINVAL 	     - Invalid parameter, opcode, or flag.
 *	ENOMEM 	     - Cannot allocate kernel buffer.
 *      EIO          - I/O related error, check additional status info. 
 *	ENXIO        - No path to this device exists.
 *      EINTR        - Signal caught, interrupted.
 *      ETIMEDOUT    - I/O request timed out.
 *      EOPNOTSUPP   - Illegal Request for this device.
 *      ECONNREFUSED - Reservation Conflict encountered.
 *      ENODEV       - Device not there (i.e. Selection Timeout).
 *      ENOENT	     - Internal Error (e.g. failed to setup async callback).
 *      EBUSY        - Device is busy (e.g. SCSI Busy status received).
 *
 *    EEI status : supported
 *
 *	EFAULT 	     - Problem copying EEI information to user space.
 * 
 * ---------------------------------------------------------------------
 *
 *  Opcode : RCI_GETSTATUS_CMD
 *
 *      The RCI_GETSTATUS_CMD will do a intrusive `get status' of the
 *      device and return an errno status and/or an amount of
 *      architecture specific data in the RCI_DATA buffer.
 *
 *      Support of the RCI_GETSTATUS_CMD opcode is implementation
 *      specific.  If this opcode is not supported by a specific
 *      implementation an EOPNOTSUPP status will be returned.
 *
 *    Flags :  RCI_EXTENDED_REQ
 *
 *      The RCI_EXTENDED_REQ flag instructs the `get status' function
 *      to consider the device specific or `partition' bits in the dev_t
 *      while accessing the device.
 *
 *      Support of the RCI_EXTENEDED_REQ flag is implementation
 *      specific.  If this flag is not supported by a specific
 *      implementation an EOPNOTSUPP status will be returned.
 *
 *    Timeo & Retry : Supported.
 *
 *    Cmd : RCI_DATA descriptor (input/output).
 * 
 *      Support of return data is implementation specific If return
 *      data is not supported by a specific implementation an
 *      EOPNOTSUPP status will be returned.
 *  
 *    Return Status : 
 *
 *      ESUCCESS     
 *	EINVAL 	     - Invalid parameter, opcode, or flag.
 *	ENXIO        - No path to this device exists.
 *	ENOMEM 	     - Cannot allocate kernel buffer.
 *	EFAULT 	     - Problem copying to user space (EEI or RCI_DATA).
 *      EINTR        - Signal caught, interrupted. 
 *      ETIMEDOUT    - I/O request timed out. 
 *      EOPNOTSUPP   - Illegal Request for this device.
 *      ENODEV       - Device not there (selection timeout).
 *      ENOENT	     - Internal Error (e.g. failed to setup async callback).
 *      EBUSY        - Device is busy (e.g. SCSI Busy status received).
 *
 *    EEI status : supported
 *
 * ---------------------------------------------------------------------
 *
 * Examples:
 *
 *  The DEVRCI ioctl can be called both from inside of the kernel, via
 *  the bdevsw/cdevsw switch tables, and from application space, via
 *  an open file descriptor.  The following are examples of how both
 *  kernel mode and user mode calls are made.
 *
 * ---------------------------------------------------------------------
 *
 * Kernel examples:
 *
 * ---------------------------------------------------------------------
 * 
 *  The following example does an `Extended Ping' which returns an
 *  architecture specific 256 byte `unique' device id if successful,
 *  or an errno status if unsuccessful.
 *
 *   static char dev_id[256]; 
 *   DEV_RCI_INFO *rci; 
 *   MALLOC(rci, DEV_RCI_INFO*, sizeof(DEV_RCI_INFO), M_TEMP, M_NOWAIT|M_ZERO);
 *
 *   rci->opcode = RCI_PING_CMD;
 *   rci->flags = RCI_EXTENEDED_REQ;
 *   rci->timout = 10;
 *   rci->retry = 15;
 *   rci->cmd.data.length = 256;
 *   rci->cmd.data.addr = (caddr_t) &dev_id[0];
 *   rci->dev = devt;
 *
 *   status = (*bdevsw[major(devt)].d_ioctl)(devt, DEVRCI, rci, 0);
 *
 * ---------------------------------------------------------------------
 *
 *  The following example does an `Extended Reserve' which returns an EEI
 *  status, as well as an errno status.
 *
 *   DEV_EEI_INFO *eei;
 *   DEV_RCI_INFO *rci;
 *   MALLOC(rci, DEV_RCI_INFO *, sizeof(DEV_RCI_INFO), M_TEMP, M_NOWAIT);
 *   MALLOC(eei, DEV_EEI_INFO *, sizeof(DEV_EEI_INFO), M_TEMP, M_NOWAIT);
 *   bzero(rci, sizeof(DEV_RCI_INFO);
 *   bzero(eei, sizeof(DEV_EEI_INFO);
 *
 *   rci->opcode = RCI_RESERVE_CMD;
 *   rci->flags = RCI_EXTENEDED_REQ;
 *   rci->timout = 30;
 *   rci->retry = 1;
 *   rci->eei = &eei;
 *   rci->dev = devt;
 *
 *   status = (*bdevsw[major(devt)].d_ioctl)(devt, DEVRCI, rci, 0);
 *
 * ---------------------------------------------------------------------
 *
 *  The following example does a `Register' operation which returns an
 *  errno status upon error.
 *
 *   extern void event_handler();
 *   DEV_RCI_INFO *rci; 
 *   MALLOC(rci, DEV_RCI_INFO *, sizeof(DEV_RCI_INFO), M_TEMP, M_NOWAIT);
 *   bzero(rci, sizeof(DEV_RCI_INFO));
 *
 *   rci->opcode = RCI_REGISTER_CMD;
 *   rci->cmd.reg.flags = (event_handler_flags);
 *   rci->cmd.reg.callback = event_handler;
 *   rci->dev = devt;
 *
 *   status = (*bdevsw[major(devt)].d_ioctl)(devt, DEVRCI, rci, 0);
 *
 * ---------------------------------------------------------------------
 *
 * User Example:
 *
 *  Note: The RCI_REGISTER_CMD & RCI_DEREGISTER_CMD's are not
 *        supported from user space.
 *
 * ---------------------------------------------------------------------
 *
 *  The following example does a `Reserve' with a 3 second timeout
 *  (3 * 0), through an open file descriptor, which returns an errno
 *  status.
 *   
 *   DEV_RCI_INFO rci = { RCI_VERSION, RCI_RESERVE_CMD, 0, 3, 0, 0,
 *                        {{0,0}}, (DEV_EEI_STATUS *) NULL };
 * 
 *   rci.dev = dev;
 *   if (ioctl(fd, DEVRCI, &rci) <= 0)
 *       printf("Can't Reserve device, errno %d\n", errno);
 *
 * ---------------------------------------------------------------------
 *
 *  The following example does a `Release' through an open file
 *  descriptor, which returns an errno status and an EEI status.
 *  with a 10 second timeout (3 * 5).
 *
 *   DEV_EEI_INFO eei;
 *   DEV_RCI_INFO rci = { RCI_VERSION, RCI_RELEASE_CMD, 0, 3, 5, 0,
 *                        {{0,0}}, &eei };
 *
 *   rci.dev = dev;
 *   if (ioctl(fd, DEVRCI, &rci) <= 0) {
 *       printf("Can't Reserve device, errno %d, eei %x\n", errno, eei.status);
 *         */

#endif /* not _DEVRCI_H_ */












