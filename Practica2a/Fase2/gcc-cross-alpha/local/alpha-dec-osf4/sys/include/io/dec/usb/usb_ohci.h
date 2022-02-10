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
 * @(#)$RCSfile: usb_ohci.h,v $ $Revision: 1.1.5.3 $ (DEC) $Date: 1998/06/12 17:49:40 $
 */
#ifndef _USB_OHCI_H_
#define _USB_OHCI_H_

struct hcd_endpoint_desc;

/*
 * Index values for the different interrupt list types.
 */
#define ED_ISOCHRONOUS		0  /* same as 1ms list */
#define ED_INTERRUPT_1ms	0  /*  1 of these */
#define ED_INTERRUPT_2ms	1  /*  2 of these */
#define ED_INTERRUPT_4ms	3  /*  4 of these */
#define ED_INTERRUPT_8ms	7  /*  8 of these */
#define ED_INTERRUPT_16ms	15 /* 16 of these */
#define ED_INTERRUPT_32ms	31 /* 32 of these */
#define ED_CONTROL		63 /*  1 control list */
#define ED_BULK			64 /*  1 bulk list */
#define ED_LIST_COUNT		65 /* 65 lists    */
#define NO_NEXT_ENDPOINT	0xff

/*
 * Host Controller Communications Area
 */
typedef struct ohci_hcca {
    /*
     * Physical Pointers to interrupt Eds.
     */
#define HCCA_TABLE_COUNT 32
    volatile U32 HccaInterruptTable[HCCA_TABLE_COUNT];

    /*
     * Contains the current frame number.  This value is updated by
     * the HC before it begins processing the periodic lists for the frame.
     */
    volatile U16 HccaFrameNumber;

    /*
     * When the HC updates HccaFrameNumber, it sets this word to 0.
     */
    volatile U16 HccaPad1;

    /*
     * When the HC reaches the end of a frameand its deferred interrupt
     * register is 0, it writes the current value of its HcDoneHead to this
     * location and generates an interrupt if interrupts are enabled.  This
     * location is not written by the HC again until software clears the WD
     * bit in the HcInterruptStatus register.  The LSb of this entry is set
     * to 1 to indicate whether an unmasked HcInterruptStatus was set when
     * HccaDoneHead was written.
     */
    volatile U32 HccaDoneHead;

    /* Reserved fo use by HC */
    U32 reserved[29];

} OHCI_HCCA;

/*
 * Each Host Controller Endpoint Descriptor is also doubly linked
 * into a list tracked by HCD.
 * Each ED queue is managed via an HCD_ED_LIST
 */
typedef struct hcd_ed_list {

    /*
     * List of attached ED
     */
    LIST_ENTRY EDlist;

    /*
     * Head disabled ED, Null if there isn't one.
     */
    struct hcd_endpoint_desc *headED;

    /* Address of location to put the physicalhead pointer when it changes. */
    vm_offset_t *PhysicalHead;

    /* Allocated bandwidth on this timeslice.  Bandwidth is allocated on
     * a per HCD_ENDPOINT_DESC basis, so this value may exceed the bandwidth
     * scheduled in the ED list.
     */
    U16 Bandwidth;

    /* Index to the next HCD_ED_List for this timeslice */
    U8 Next;

    /* Flags */
    U8 flags;
#define HCD_ED_LIST_REG_WRITE 1

} HCD_ED_LIST;

/*
 * Possible number of root hub ports
 */
#define OHCI_NDP 32

/*
 * This structure is locked by locking the associated USBD_BUS struct
 */
typedef struct ohci_regs {
    vm_offset_t HcRevision;
    vm_offset_t HcControl;
    vm_offset_t HcCommandStatus;
    vm_offset_t HcInterruptStatus;
    vm_offset_t HcInterruptEnable;
    vm_offset_t HcInterruptDisable;
    vm_offset_t HcHCCA;
    vm_offset_t HcPeriodCurrentED;
    vm_offset_t HcControlHeadED;
    vm_offset_t HcControlCurrentED;
    vm_offset_t HcBulkHeadED;
    vm_offset_t HcBulkCurrentED;
    vm_offset_t HcDoneHead;
    vm_offset_t HcFmInterval;
    vm_offset_t HcFmRemaining;
    vm_offset_t HcFmNumber;
    vm_offset_t HcPeriodicStart;
    vm_offset_t HcLSThreshold;
    vm_offset_t HcRhDescriptorA;
    vm_offset_t HcRhDescriptorB;
    vm_offset_t HcRhStatus;
    vm_offset_t HcRhPortStatus[OHCI_NDP];
} OHCI_REGS;

/*
 * This structure is locked by locking the associated USBD_BUS struct
 */
typedef struct ohci_softc {

    USBD_BUS *usb;

    /* Pointer to the HC operational registers.  See section 7 */
    OHCI_REGS *regs;

    /* Pointer to the shared memory HCCA block.  See section 4.4 */
    OHCI_HCCA *hcca;
    U32 hcca_phys;
    sglist_t hcca_sg;

    U32 HcRevision;

    /* Root hub related fields */
    U32 root_hub_device_address;
    U8 number_of_ports;
    LIST_ENTRY status_change_requests;

    /*
     * List of connected endpoints, linked via HCD_ENDPOINT_DESC, in FIFO
     * order.  These must have an associated USB_ENDPOINT structure.
     */
    LIST_ENTRY connected_endpoints;

    /*
     * List of free HCD_ENDPOINT_DESC structures.  These do NOT have an
     * associated USB_ENDPOINT structure.
     */
    LIST_ENTRY free_EDs;
    int free_ED_count;

    /*
     * List of free and used HCD_TRANSFER structures.
     */
    LIST_ENTRY free_TDs;
    int free_TD_count;

    /*
     * Used_TDs links hcd_doneTD structs which are processed
     * by ohci_process_done_queue.
     */
    LIST_ENTRY used_TDs;
    int used_TD_count;

    /*
     * List of HCD_ENDPOINT_DESC structures which are to be freed once
     * the HC list processing is suspended.
     */
    LIST_ENTRY stalled_EDs;

    /*
     * List of HCD_ENDPOINT_DESC structures which are to be freed
     * based on their reclamation_frame.
     */
    LIST_ENTRY running_EDs;

    /*
     * List of HCD_ENDPOINT_DESC structures which are to be restarted
     * after cancelled HCD_TRANSFER structures are removed.
     */
    LIST_ENTRY paused_EDs;
     
    /*
     * There are a total of 63 lists, one control list, and
     * one bulk list.
     */
    HCD_ED_LIST EDlists[ED_LIST_COUNT];

    /* Upper bits of 32-bit fram number */
    U32 FrameHighPart;

    /* Total bandwidth supported by this HC */
    U32 available_bandwidth;

    /* Total bandwidth inuse */
    U32 used_bandwidth;
      
    /* Schedule Overrun count */
    U32 SOCount;

    /* Schedule Overrun for Stall count starts at this frame */
    U32 SOStallFrame;

    /* Schedule Overrun for bandwidth limit adjust starts at this frame */
    U32 SOLimitFrame;

    /* Schedule Overrun for a limit condition was hit */
    U8 SOLimitHit;

    /* Schedule Overrun for a stall condition was hit */
    U8 SOStallHit;

} OHCI_SOFTC;

/*
 * Host Controller Endpoint Descriptor, refer to Section 4.2,
 * Endpoint Descriptor 
 */
typedef struct hc_endpoint_desc {
    U16 usb_address      :7,	/* USB address of the function containing
				 * the endpoint that this ED controls */
        endpoint_number  :4,	/* USB address of the endpoint within the fn */
        direction        :2,	/* Direction of data flow */
        speed            :1,
        sKip             :1, 
        Format           :1;
    U16 MaximumPacketSize:11,
                         :5;
    U32			 :4,
        TailP		 :28;
    U32 Halted           :1,
        toggleCarry      :1,
                         :2,
        HeadP            :28;   /* Points to next TD to be processed */
    U32 NextED;                 /* If nonzero, points to next ED on list */
} HC_ENDPOINT_DESC;

/*
 * Host Controller Transfer Descriptor, refer to Section 4.3,
 * Transfer Descriptors
 */
typedef struct hc_transfer_desc {
    U16 resv;
    U8                 :2,
        BufferRounding :1,
        Direction_PID  :2,
#define SETUP_TO_ENDPOINT 0
#define OUT_TO_ENDPOINT   1
#define IN_FROM_ENDPOINT  2
        DelayInterrupt :3;
    U8  DataToggle     :2,
        ErrorCount     :2,
        ConditionCode  :4;
    U32 CBP; /* Current Buffer Pointer - Contains the physical address of
		the next memory location that will be accessed for transfer
		to/from the endpoint.  A value of 0 indicates a zero length
		data packet or that all bytes have been transferred */
    volatile U32 NextTD; /* phys ptr to HC_TRANSFER_DESC */
    U32 BE; /* Buffer End - Contains physical address of the last byte in
	       the buffer for this TD */
} HC_TRANSFER_DESC;

/*
 * HCD Transfer Descriptor
 */
typedef struct hcd_transfer_desc {

    /* Links to other HCD_TRANSFER_DESCs associated with
     * the same UsbdRequest
     */
    LIST_ENTRY TD_list;

    /* Status of this TD, includes PENDING, COMPLETED, CANCELED,
     * and NOTFILLED (indicates the dummy TD at the end of the endpoint's
     * queue; no other fields are valid)
     */
    U8 TDStatus;
#define TD_COMPLETED	0
#define TD_PENDING	1
#define TD_CANCELED	2
#define TD_NOTFILLED	3

    /* True if the UsbdRequest has been canceled and this TD is
     * waiting for cleanup.
     */
    U8 CancelPending;

    U16 pad1;

    /*
     * Used to link the used TD's in the controller's used_TDs list
     * which is used to process completing TD's.  Note that the following
     * three fields (usedTD, virtual_address, and PhysicalAddress) must
     * remain in this order.  See hcd_done_TD structure below.
     */
    LIST_ENTRY usedTD;
    
    /*
     * Virtual address of this TD.  Used to convert the following
     * PCI address (JANET - change the name) to the virtual address.
     */
    struct hcd_transfer_desc *VirtualAddress;

    /* 32bit Physical address of HcTD */
    U32 PhysicalAddress;
    sglist_t sg;

    /* Virtual pointer to next HCD_TRANSFER_DESC on
     * the endpoint's queue.
     */
    struct hcd_transfer_desc *nextTD;

    /* Pointer to the transfer request at the USBDI for which the
     * transfer was created.
     */
    USBD_REQUEST *request;

    /* Pointer to the ED to which the transfer is queued. */
    struct hcd_endpoint_desc *ED;

    /* Total number of bytes queued for this transfer. */
    U32 TransferCount;

    U8 pad2[4];
    struct hc_transfer_desc HcTD;
} HCD_TRANSFER_DESC;

/*
 * HCD Endpoint Descriptor
 */
typedef struct hcd_endpoint_desc {
    /* A doubly-linked list.  While the ED is on a HC list, this link
     * is used to shadow the hardware list to some level.  As an ED is
     * being removed from a HC list, this link is used to move the
     * HCD_ENDPOINT_DESC through various states finally ending on
     * the free list.
     */
    struct hcd_endpoint_desc *flink;
    struct hcd_endpoint_desc *blink;

    /* Isochronous, Interrupt, Control, Bulk */
    U8 type;

    /* Index into device data EDlist.  This is the identifier of
     * which list this ED is inserted.
     */
    U8 EDlist_index;

    /* Nonzero if ED is queued on PausedEDRestart list */
    U8 PausedFlag;

    U8 endpoint_state; /* USBD_ENDPOINT_ACTIVE or USBD_ENDPOINT_STALLED */

    /* 32bit Physical address of HcED */
    U32 PhysicalAddress;
    sglist_t sg;

    /* USBD's pipe structure for this ED */
    USBD_PIPE *pipe;

    /* Pointer to first HCD_TRANSFER_DESC on this endpoint's queue */
    HCD_TRANSFER_DESC *headTD;

    /* 
     * Pointer to last HCD_TRANSFER_DESC on this endpoint's queue, unless
     * it is in the process of being filled in, this is a dummy structure.
     */
    HCD_TRANSFER_DESC *tailTD;

    /* Used during the removal process of an ED from an HC list to track
     * what time an ED can safely be considered freed from the HC.  Used
     * for running reclamation only.
     */
    U32 ReclamationFrame;

    U32 request_count;

    /* A doubly-linked list.  While the ED is paused and awaiting
     * restart this link is used.
     */
    LIST_ENTRY PausedLink;

    /*
     * When the device is non-ohci compliant and can't handle multiple
     * requests per fram, the last_request point is used to chain
     * requests when they are queued to the endpoint.
     */
    struct usbd_request *last_request;

    char pad3[8];

    /* HC Endpoint Descriptor */
    struct hc_endpoint_desc HcED;

} HCD_ENDPOINT_DESC;

typedef struct hcd_done_TD {

    LIST_ENTRY l;
    
    /*
     * Virtual address of the TD
     */
    struct hcd_transfer_desc *VirtualAddress;

    /* 32bit PCI bus address of the TD */
    U32 PhysicalAddress;

} HCD_DONE_TD;

#define CAN_NOT_COMMIT_BANDWIDTH 10

#define CC_NOERROR				0x0
#define CC_CRC					0x1
#define CC_BITSTUFFING				0x2
#define CC_DATATOGGLEMISMATCH			0x3
#define CC_STALL				0x4
#define CC_DEVICENOTRESPONDING			0x5
#define CC_PIDCHECKFAILURE			0x6
#define CC_UNEXPECTEDPID			0x7
#define CC_DATAOVERRUN				0x8
#define CC_DATAUNDERRUN				0x9
#define CC_BUFFEROVERRUN			0xc
#define CC_BUFFERUNDERRUN			0xd
#define CC_NOTACCESSED				0xe

/*
 * Convert OHCI Transfer Descriptor Condition Code to a
 * USBD_REQEUST Status code.
 */
U32 USBD_CC_Table[] = {
    USBD_NORMAL_COMPLETION,	/* CC_NOERROR			*/
    USBD_CRC_ERROR,		/* CC_CRC			*/
    USBD_BITSTUFFING_ERROR,	/* CC_BITSTUFFING		*/
    USBD_DATATOGGLEMISMATCH_ERROR, /* CC_DATATOGGLEMISMATCH	*/
    USBD_STALL_ERROR,		/* CC_STALL			*/
    USBD_DEVICENOTRESPONDING_ERROR,/* CC_DEVICENOTRESPONDING	*/
    USBD_PIDCHECKFAILURE_ERROR,	/* CC_PIDCHECKFAILURE		*/
    USBD_UNEXPECTEDPID_ERROR,	/* CC_UNEXPECTEDPID		*/
    USBD_DATAOVERRUN_ERROR,	/* CC_DATAOVERRUN		*/
    USBD_DATAUNDERRUN_ERROR,	/* CC_DATAUNDERRUN		*/
    USBD_UNKNOWN_ERROR,		/* 0xa				*/
    USBD_UNKNOWN_ERROR,		/* 0xb				*/
    USBD_BUFFEROVERRUN_ERROR,	/* CC_BUFFEROVERRUN		*/
    USBD_BUFFERUNDERRUN_ERROR,	/* CC_BUFFERUNDERRUN		*/
    USBD_NOT_DONE,		/* CC_NOTACCESSED		*/
};

/*
 * OHCI register offsets
 */
#define OHCI_HcRevision			0x00
#define OHCI_HcControl			0x04
#define OHCI_HcCommandStatus		0x08
#define OHCI_HcInterruptStatus		0x0c
#define OHCI_HcInterruptEnable		0x10
#define OHCI_HcInterruptDisable		0x14
#define OHCI_HcHCCA			0x18
#define OHCI_HcPeriodCurrentED		0x1c
#define OHCI_HcControlHeadED		0x20
#define OHCI_HcControlCurrentED		0x24
#define OHCI_HcBulkHeadED		0x28
#define OHCI_HcBulkCurrentED		0x2c
#define OHCI_HcDoneHead			0x30
#define OHCI_HcFmInterval		0x34
#define	OHCI_HcFmRemaining		0x38
#define OHCI_HcFmNumber			0x3c
#define OHCI_HcPeriodicStart		0x40
#define OHCI_HcLSThreshold		0x44
#define OHCI_HcRhDescriptorA		0x48
#define OHCI_HcRhDescriptorB		0x4c
#define OHCI_HcRhStatus			0x50
#define OHCI_HcRhPortStatus0		0x54
#define OHCI_HcRhPortStatus1		0x58
#define OHCI_HcRhPortStatus2		0x5c
#define OHCI_HcRhPortStatus3		0x60
#define OHCI_HcRhPortStatus4		0x64
#define OHCI_HcRhPortStatus5		0x68
#define OHCI_HcRhPortStatus6		0x6c
#define OHCI_HcRhPortStatus7		0x70
#define OHCI_HcRhPortStatus8		0x74
#define OHCI_HcRhPortStatus9		0x78
#define OHCI_HcRhPortStatus10		0x7c
#define OHCI_HcRhPortStatus11		0x80
#define OHCI_HcRhPortStatus12		0x84
#define OHCI_HcRhPortStatus13		0x88
#define OHCI_HcRhPortStatus14		0x8c
#define OHCI_HcRhPortStatus15		0x90
#define OHCI_HcRhPortStatus16		0x94
#define OHCI_HcRhPortStatus17		0x98
#define OHCI_HcRhPortStatus18		0x9c
#define OHCI_HcRhPortStatus19		0xa0
#define OHCI_HcRhPortStatus20		0xa4
#define OHCI_HcRhPortStatus21		0xa8
#define OHCI_HcRhPortStatus22		0xac
#define OHCI_HcRhPortStatus23		0xb0
#define OHCI_HcRhPortStatus24		0xb4
#define OHCI_HcRhPortStatus25		0xb8
#define OHCI_HcRhPortStatus26		0xbc
#define OHCI_HcRhPortStatus27		0xc0
#define OHCI_HcRhPortStatus28		0xc4
#define OHCI_HcRhPortStatus29		0xc8
#define OHCI_HcRhPortStatus30		0xcc
#define OHCI_HcRhPortStatus31		0xd0

unsigned char OHCI_HcRhPortStatus[OHCI_NDP] = {
    OHCI_HcRhPortStatus0, OHCI_HcRhPortStatus1, OHCI_HcRhPortStatus2,
    OHCI_HcRhPortStatus3, OHCI_HcRhPortStatus4, OHCI_HcRhPortStatus5,
    OHCI_HcRhPortStatus6, OHCI_HcRhPortStatus7, OHCI_HcRhPortStatus8,
    OHCI_HcRhPortStatus9, OHCI_HcRhPortStatus10, OHCI_HcRhPortStatus11,
    OHCI_HcRhPortStatus12, OHCI_HcRhPortStatus13, OHCI_HcRhPortStatus14,
    OHCI_HcRhPortStatus15, OHCI_HcRhPortStatus16, OHCI_HcRhPortStatus17,
    OHCI_HcRhPortStatus18, OHCI_HcRhPortStatus19, OHCI_HcRhPortStatus20,
    OHCI_HcRhPortStatus21, OHCI_HcRhPortStatus22, OHCI_HcRhPortStatus23,
    OHCI_HcRhPortStatus24, OHCI_HcRhPortStatus25, OHCI_HcRhPortStatus26,
    OHCI_HcRhPortStatus27, OHCI_HcRhPortStatus28, OHCI_HcRhPortStatus29,
    OHCI_HcRhPortStatus30, OHCI_HcRhPortStatus31
};

/*
 * HcRevision bits
 */
#define HcRevision_REV 0xff;

/*
 * HcControl Register - The HcControl register defines the operating modes
 * for the Host Controller.  Most of the fields is this register are
 * modified only by the Host Controller Driver, except
 * HostControllerFunctionalState and RemoteWakeupConnected.
 */
/* ControlBulkServiceRatio - This specifies the service ratio between
 * Control and Bulk EDs.  Before processing any of the nonperiodic lists,
 * HC must compare the ratio specified with its internal count on how may
 * nonempty Control EDs have been processed, in determining whether to
 * continue serving another Control ED or switching to Bulk EDs.  The
 * internal count will be retained when crossing the frame boundary.
 * In case of reset, HCD is responsible for restoring this value.
 */
#define HcControl_CBSR 0x00000003

/* PeriodicListEnable - This bit is set to enable the processing of the
 * periodic list in the next Frame.  If cleared by HCD, processing of the
 * periodic list does not occur after the next SOF.  HC must check this bit
 * before it starts processing the list.
 */
#define HcControl_PERIODIC_LIST_ENABLE 0x00000004

/* IsochronousEnable - This bit is used by HCD to enable/disable processing
 * of isochronous EDs.  While processing the periodic list in a Frame, HC
 * checks the status of this bit when it finds an Isochronous ED (F=1).  If
 * set (enabled), HC continues processing the EDs.  If cleared (disabled),
 * HC halts processing of the periodic list (which now contains only
 * isochronous EDs) and begins processing the Bulk/Control lists.  Setting
 * this bit is guaranteed to take effect in the next Frame (not the current
 * Frame).
 */
#define HcControl_ISOCHRONOUS_ENABLE 0x00000008

/* ControlListEnable - This bit is set to enable the processing of the
 * Control list in the next Frame.  If cleared by HCD, processing of the
 * Control list does not occur after the next SOF.  HC must check this bit
 * whenever it determines to process the list.  When disabled, HCD may
 * modify the list.  If HcControlCurrentED is pointing to an ED to be
 * removed, HCD must advance the pointer by updating HcControlCurrentED
 * before re-enabling the processing of the list.
 */
#define HcControl_CONTROL_LIST_ENABLE 0x00000010

/* BulkListEnable - This bit is set to enable the processing of the Bulk
 * list in the next Frame.  If cleared by HCD, processing of the Bulk list
 * does not occur after the next SOF.  HC checks this bit whenever it
 * determines to process the list.  When disabled, HCD may modify the list.
 * If HcBulkCurrentED is pointing to an ED to be removed, HCD must advance
 * the pointer by updating HcBulkCurrentED before re-enabling processing
 * of the list.
*/
#define HcControl_BULK_LIST_ENABLE 0x00000020

/* HostControllerFunctionalState for USB - A transition to UsbOperational
 * from another state causes SOF generation to begin 1 ms later.  HCD may
 * determine whether HC has begun sending SOFs by reading the StartofFrame
 * field of HcInterruptStatus.  This field may be changed by HC only when
 * in the UsbSuspend state.  HC may move from the UsbSuspend state to the
 * UsbResume state after detecting the resume signaling from a downstream
 * port.  HC enters UsbSuspend after a software reset, whereas it enters
 * UsbReset after a hardware reset.  The latter also resets the Root Hub
 * and asserts subsequent reset signaling to downstream ports.
 */
#define HcControl_HCFS			0x000000c0
#define HcControl_HCFS_RESET		0x00000000
#define HcControl_HCFS_RESUME		0x00000040
#define HcControl_HCFS_OPERATIONAL	0x00000080
#define HcControl_HCFS_SUSPEND		0x000000c0

/* InterruptRouting - This bit determines the routing of interrupts
 * generated by events registered in HcInterruptStatus.  If clear, all
 * interrupts are routed to the normal host bus interrupt mechanism.  If
 * set, interrupts are routed to the System Management Interrupt.  Hcd
 * clears this bit upon a hardware reset, but it does not alter this bit
 * upon a software reset.  HCD uses this bit as a tag to indicate the
 * ownership of HC.
 */
#define HcControl_IR 0x00000100

/* RemoteWakeupConnected - This bit indicates whether HC supports remote
 * wakeup signaling.  If remote wakeup is supported and used by the system
 * it is the responsibility of system firmware to set this bit during POST.
 * HC clears the bit upon a hardware reset but does not alter it upon a
 * software reset.  Remote wakeup signaling of the host system is
 * host-bus-specific and is not described in this specification.
 */
#define HcControl_RWC 0x00000200

/* RemoteWakeupEnable - This bit is used by HCD to enable or disable
 * the remote wakeup feature upon the detection of upstream resume signaling.
 * When this bit is set and the ResumeDetected bit in HcInterruptStatus
 * is set, a remote wakeup is signaled to the host system.  Setting this
 * bit has no impact on the generation of hardware interrupt.
 */
#define HcControl_RWE 0x00000400


/*
 * HcCommandStatus Register - The HcCommandStatus register is used by the
 * Host Controller to receive commands issued by the Host Controller Driver
 * as well as reflecting the current status of the Host Controller.  To the
 * Host Controller Driver, it appears to be a "write to set" register.  The
 * Host Controller must ensure that bits written as '1' become set in the
 * register while bits written as '0' remain unchanged in the register.  The
 * Host Controller Driver may issue multiple distinct commands to the Host
 * Controller without concern for corrupting previously issued commands.
 * The Host Controller Driver has normal read access to all bits.
 */
/*
 * HostControllerReset - This bit is set by HCD to initiate a software
 * reset of HC.  Regardless of the functional state of HC, it moves to
 * the UsbSuspend state in which most of the operational registers are
 * reset except those stated otherwise; e.g., the InterruptRouting field
 * of HcControl, and no Host bus accesses are allowed.  This bit is cleared
 * by HC upon the completion of the reset operation.  The reset operation
 * must be completed within 10us.  This bit, when set, should not cause a
 * reset to the Root Hub and no subsequent reset signaling should be asserted
 * to its downstream ports.
 */
#define HcCommandStatus_HCR 0x00000001

/* ControlListFilled - This bit is used to indicate whether there are
 * any TDs on the Control list.  It is set by HCD whenever it adds a TD
 * to an ED in the Control list.  When HC begins to process the head of
 * the Control list, it checks CLF.  As long as ControlListFilled is 0,
 * HC will not start processing the Control list.  If CF is 1, HC will
 * start processing the Control list and will set ControlListFilled to 0.
 * If HC finds a TD on the list, then HC will set ControlListFilled to 1
 * causing the Control list processing to continue.  If no TD is found on
 * the control list, and if the HCD does not set ControlListFilled, then
 * ControlListFilled will still be 0 when HC completes processing the
 * Control list and Control list processing will stop. 
 */
#define HcCommandStatus_CLF 0x00000002

/* BulkListFilled - This bit is used to indicate whether there are any
 * TDs on the Bulk list.  It is set by HCD whenever it adds a TD to an
 * ED in the Bulk list.  When HC begins to process the head of the Bulk
 * list, it checks BF.  As long as BulkListFilled is 0, HC will not start
 * processing the Bulk list.  If BulkListFilled is 1, HC will start
 * processing Bulk list and will set BF to 0.  If HC finds a TD on the
 * list, then HC will set BulkListFilled to 1 causing the Bulk list
 * processing to continue.  If no TD is found on the Bulk list, and if
 * HCD does not set BulkListFilled, then BulkListFilled will still be 0
 * when HC completes processing the Bulk list and Bulk list processing
 * will stop. 
 */
#define HcCommandStatus_BLF 0x00000004

/* OwnershipChangeRequest - This bit is set by an OS HCD to request a
 * change of control of the HC.  When set HC will set the OwnershipChange
 * field in HcInterruptStatus.  After the change over, this bit is
 * cleared and remains so until the next request from OS HCD.
 */
#define HcCommandStatus_OCR 0x00000008

/* SchedulingOverrunCount - These bits are incremented on each scheduling
 * overrun error.  It is initialized to 00b and wraps around at 11b this
 * will be incremented when a scheduling overrun is detected even if
 * SchedulingOverrun in HcInterruptStatus has already been set.  This is
 * used by HCD to monitor any persistent scheduling problems.
 */
#define HcCommandStatus_SOC 0x00030000

/*
 * HcInterruptStatus Register - This register provides status on various
 * events that cause hardware interrupts.  When an event occurs, Host
 * Controller sets the corresponding bit in this register.  When a bit
 * becomes set, a hardware interrupt is generated if the interrupt is
 * enabled in the HcInterruptEnable register and the MasterInterruptEnable
 * bit is set.  The Host Controller Driver may clear specific bits in
 * this register by writing '1' to bit positions to be cleared.  The
 * Host Controller Driver may not set any of these bits.  The Host
 * Controller will never clear the bit.
 */
/* SchedulingOverrun - This bit is set when the USB schedule for the
 * current Frame overruns and after the update of HccaFrameNumber.  A
 * scheduling overrun will also cause the SchedulingOverrunCount of
 * HcComm and Status to be incremented.
 */
#define HC_SCHEDULING_OVERRUN 0x00000001

/* WritebackDoneHead - This bit is set immediately after HC has
 * written HcDoneHead to HccaDoneHead.  Further updates of the
 * HccaDoneHead will not occur until this bit has been cleared.
 * HCD should only clear this bit after it has saved the content
 * of HccaDoneHead.
 */
#define HC_WRITEBACK_DONE_HEAD 0x00000002

/* StartofFrame - This bit is set by HC at each start of a frame and
 * after the update of HccaFrameNumber.  HC also generates a SOF token
 * at the same time.
 */
#define HC_SOF 0x00000004

/* ResumeDetected - This bit is set when HC detects that a device on
 * the USB is asserting resume signaling.  It is the transition from
 * no resume signaling to resume signaling causing this bit to be set.
 * This bit is not set when HCD sets the USBRESUME state.
 */
#define HC_RESUME_DETECTED 0x00000008

/* UnrecoverableError - This bit is set when HC detects a system error
 * not related to USB.  HC should not proceed with any processing nor
 * signaling before the system error has been corrected.  HCD clears
 * this bit after HC has been reset.
 */
#define HC_UNRECOVERABLE_ERROR 0x00000010

/* FrameNumberOverflow - This bit is set when the MSb of HcFmNumber
 * (bit 15) changes value, from 0 to 1 or from 1 to 0, and after
 * HccaFrameNumber has been updated.
 */
#define HC_FRAME_NUMBER_OVERFLOW 0x00000020

/* RootHubStatusChange - This bit is set when the content of HcRhStatus
 * or the content of any of HcRhPortStatus[NumberofDownstreamPort]
 * has changed.
 */
#define HC_ROOT_HUB_STATUS_CHANGE 0x00000040

/* OwnershipChange - This bit is set by HC when HCD sets the
 * OwnershipChangeRequest field in HcCommandStatus.  This event, when
 * unmasked, will always generate an System Management Interrupt (SMI)
 * immediately.  This bit is tied to 0b when the SMI pin is not implemented.
 */
#define HC_OWNERSHIP_CHANGE 0x40000000

/*
 * HcInterruptEnable Register - Each enable bit in the HcInterruptEnable
 * register corresponds to an associated interrupt bit in the
 * HcInterruptStatus register.  The HcInterruptEnable register is used to
 * control which events generate a hardware interrupt.  When a bit is set
 * in the HcInterruptStatus register AND the corresponding bit in the
 * HcInterruptEnable register is set AND the MasterInterruptEnable bit is
 * set, then a hardware interrupt is requested on the host bus.
 *
 * Writing a '1' to a bit in this register sets the corresponding bit, 
 * wheras writing a '0' to a bit in this register leaves the corresponding
 * bit unchanged.  On read, the current value of this register is returned.
 */
/* 0 - Ignore
 * 1 - Enable interrupt generation due to Scheduling Overrun
 */
#define HcInterruptEnable_SO	0x00000001

/* 0 - Ignore
 * 1 - Enable interrupt generation due to HcDoneHead Writeback.
 */
#define HcInterruptEnable_WDH	0x00000002

/* 0 - Ignore
 * 1 - Enable interrupt generation due to Start of Frame.
 */
#define HcInterruptEnable_SF	0x00000004

/* 0 - Ignore
 * 1 - Enable interrupt generation due to Resume Detect.
 */
#define HcInterruptEnable_RD	0x00000008

/* 0 - Ignore
 * 1 - Enable interrupt generation due to Unrecoverable Error.
 */
#define HcInterruptEnable_UE	0x00000010

/* 0 - Ignore 
 * 1 - Enable interrupt generation due to Fram Number Overflow.
 */
#define HcInterruptEnable_FNO	0x00000020
 
/* 0 - Ignore
 * 1 - Enable interrupt generation due to Root Hub Status Change.
 */
#define HcInterruptEnable_RHSC	0x00000040

/* 0 - Ignore
 * 1 - Enable interrupt generation due to Ownership Change.
 */
#define HcInterruptEnable_OC	0x40000000

/* A '0' written to this field is ignored by HC.  A '1' written to
 * this field enable interrupt generation due to events specified in the
 * otherbits of this register.  This is used by HCD as a Master 
 * Interrupt Enable.
 */
#define HC_MASTER_INTERRUPT_ENABLE	0x80000000

/*
 * HcInterruptDisable Register - Each disable bit in the HcInterruptDisable
 * register corresponds to an associated interrupt bit in the
 * HcInterruptStatus register.  The HcInterruptDisable register is coupled
 * with the HcInterruptEnable register.  Thus, writing a '1' to a bit in
 * this register clears the corresponding bit in the HcInterruptEnable
 * register, whereas writing a '0' to a bit in this register leaves the
 * corresponding bit in the HcInterruptEnable register unchanged.  On read,
 * the current value of the HcInterruptEnable register is returned.
 */
/* 0 - Ignore
 * 1 - Disable interrupt generation due to Scheduling Overrun.
 */
#define HcInterruptDisable_SO	0x00000001

/* 0 - Ignore
 * 1 - Disable interrupt generation due to HcDoneHead Writeback.
 */
#define HcInterruptDisable_WDH	0x00000002

/* 0 - Ignore
 * 1 - Disable interrupt generation due to Start of Frame.
 */
#define HcInterruptDisable_SF	0x00000004

/* 0 - Ignore
 * 1 - Disable interrupt generation due to Resume Detect.
 */
#define HcInterruptDisable_RD	0x00000008

/* 0 - Ignore
 * 1 - Disable interrupt generation due to Unrecoverable Error.
 */
#define HcInterruptDisable_UE	0x00000010

/* 0 - Ignore
 * 1 - Disable interrupt generation due to Fram Number Overflow.
 */
#define HcInterruptDisable_FNO	0x00000020

/* 0 - Ignore
 * 1 - Disable interrupt generation due to Root Hub Status Change.
 */
#define HcInterruptDisable_RHSC	0x00000040

/* 0 - Ignore
 * 1 - Disable interrupt generation due to Ownership Change.
 */ 
#define HcInterruptDisable_OC	0x40000000

/* A '0' written to this field is ignored by HC.  A '1' written to this
 * field disables interrupt generation due to events specified in the
 * other bits of this register.  This field is set after a hardware or
 * software reset.
 */
#define HcInterruptDisable_MIE	0x80000000

/*
 * HcHCCA Register - The HcHCCA register contains the physical address of
 * the Host Controller Communication Area.  The Host Controller Driver
 * determines the alignment restrictions by writing all 1s to HcHCCA and
 * reading the content of HcHCCA.  The alignment is evaluated by examining
 * the number of zeroes in the lower order bits.  The minimum alignment is
 * 256 bytes; therefore, bits 0 through 7 must always return '0' when read.
 * Detailed description can be found in Chapter 4.  This area is used to
 * hold the control structures and the Interrupt table that are accessed
 * by both the Host Controller and the Host Controller Driver.
 */
/* #define HcHCCA 0xffffff00 */

/*
 * HcPeriodCurrentED Register - The HcPeriodCurrentED register contains
 * the physical address of the current Isochronous or Interrupt Endpoint
 * Descriptor.
 */
/* PeriodCurrentED - This is used by HC to point to the head of one of the
 * Periodic lists which will be processed in the current Frame.  The content
 * of this register is updated by HC after a periodic ED has been processed.
 * HCD may read the content in determining which ED is currently being
 * processed at the time of reading.
 */
#define HcPeriodCurrentED_PCED 0xfffffff0

/*
 * HcControlHeadED Register - The HcControlHeadED register contains the
 * physical address of the first Endpoint Descriptor of the Control list.
 */
/* ControlHeadED - HC traverses the Control list starting with the
 * HcControlHeadED pointer.  The Content is loaded from HCCA during the
 * initialization of HC.
 */
#define HcControlHeadED_CHED 0xfffffff0

/*
 * HcControlCurrentED register - The HcControlCurrentED register contains
 * the physical address of the current Endpoint Descriptor of the Control list.
 */
/* ControlCurrentED - This pointer is advanced to the next ED after serving
 * the present one.  HC will continue processing the list from where it left
 * off in the last Frame.  When it reaches the end of the Control list, HC
 * checks the ControlListFilled of in HcCommandStatus.  If set, it copies
 * the content of HcControlHeadED to HcControlCurrentED and clears the bit.
 * If not set, it does nothing.  HCD is allowed to modify this register only
 * when the ControlListEnable of HcControl is cleared.  When set, HCD only
 * reads the instantaneous value of this register.  Initially, this is set
 * to zero to indicate the end of the Control list.
 */
#define HcControlCurrentED_CCED 0xfffffff0

/*
 * HcBulkHeadED Register - The HcBulkHeadED register contains the physical
 * address of the first Endpoint Descriptor of the Bulk list.
 */
/* BulkHeadED - HC traverses the Bulk list starting with the HcBulkHeadED
 * pointer.  The content is loaded from HCCA during the initialization of HC.
 */
#define HcBulkHeadED_BHED 0xfffffff0

/*
 * HcBulkCurrentEd Register - The HcBulkCurrentED register contains the
 * physical address of the current endpoint of the Bulk list.  As the Bulk
 * list will be served in a round-robin fashion, the endpoints will be
 * ordered according to their insertion to the list.
 */
/* BulkCurrentED - This is advanced to the next ED after the HC has served
 * the present one.  HC continues processing the list from where it left
 * off in the last Frame.  When it reaches the end of the Bulk list, HC
 * checks the ControlListFilled of HcControl.  If set, it copies the content
 * of HcBulkHeadED to HcBulkCurrentED and clears the bit if it is not set,
 * it does nothing.  HCD is only allowed to modify this register when the
 * BulkListEnable of HcControl is cleared.  When set the HCD only reads the
 * instantaneous value of this register.  This is initially set to zero to
 * indicate the end of the Bulk list.
 */
#define HcBulkCurrentED_BCED 0xfffffff0

/* 
 * HcDoneHead Register - The HcDoneHead register contains the physical
 * address of the last completed Transfer Descriptor that was added to
 * the Done queue.  In normal operation, the Host Controller Driver
 * should not need to read this register as its content is periodically
 * written to the HCCA.
 */
/* DoneHead - When a TD is completed, HC writes the content of HcDoneHead
 * to the NextTD field of the TD.  HC then overwrites the content of
 * HcCondHead with the address of this TD.  This is set to zero whenever
 * HC writes the content of this register to HCCA.  It also sets the
 * WritebackDoneHead of HcInterruptStatus.
 */
#define HcDoneHead_DH 0xfffffff0

/*
 * HcFmInterval Register - The HcFmInterval register contains a 14-bit value
 * which indicates the bit time inverval in a Frame, (i.e., between two
 * consecutive SOFs), and a 15-bit value indicating the Full Speed maximum
 * packet size that the Host Controller may transmit or receive without
 * causing scheduling overrun.  The Host Controller Driver may carry out
 * minor adjustment on the FrameInterval by writing a new value over the
 * present one at each SOF.  This provides the programmability necessary for
 * the Host Controller to synchronize with an external clocking resource
 * and to adjust any unknown local clock offset.
 */
/* FrameInterval - This specifies the interval between two consecutive SOFs
 * in bit times.  The nominal value is set to be 11,999.  HCD should store
 * the current value of this field before resetting HC.  By setting the
 * HostControllerReset field of HcCommandStatus as this will cause the HC
 * to reset this field to its nominal value.  HCD may choose to restore the
 * stored value upon the completion of the Reset sequence.
 */
#define HcFmInterval_FI		0x00003fff

/* FSLargestDataPacket - This field specifies a value which is loaded into
 * the Largest Data Packet Counter at the beginning of each frame.  The
 * counter value represents the largest amount of data in bits which can be
 * sent or received by the HC in a single transaction at any given time
 * without causing scheduling overrun.  The field value is calculated by
 * the HCD.
 */
#define HcFmInterval_FSMPS	0x7fff0000

/* FrameIntervalToggle - HCD toggles this bit whenever it loads a new
 * value to FrameInterval.
 */
#define HcFmInterval_FIT	0x80000000

/*
 * HcFmRemaining Register - The HcFmRemaining register is a 14-bit
 * down counter showing the bit time remaining in the current Frame.
 */
/* FrameRemaining - This counter is decremented at each bit time.  When it
 * reaches zero, it is reset by loading the FrameInterval value specified
 * in HcFmInterval at the next bit time boundary.  When entering the
 * USBOPERATIONAL state, HS re-loads the content with the FrameInterval
 * of HcFmInterval and uses the updated value from the next SOF.
 */
#define HcFmRemaining_FR	0x00003fff

/* FrameRemainingToggle - This bit is loaded from the FrameIntervalToggle
 * field of HcFmInterval whenever FrameRemaining reaches 0.  This bit is
 * used by HCD for the synchronization between FrameInterval and
 * FrameRemaining.
 */
#define HcFmRemaining_FRT	0x80000000

/*
 * HcFmNumber Register - The HcFmNumber register is a 16-bit counter.  It
 * provides a timing reference among events happening in the Host Controller
 * and the Host Controller Driver.  The Host Controller Driver may use the
 * 16-bit value specified in this register and generate a 32-bit frame number
 * without requiring frequent access to the register.
 */
/* FrameNumber - This is incremented when HcFmRemaining is re-loaded.  It
 * will be rolled over to 0h after ffffh.  When entering the USBOPERATIONAL
 * state, this will be incremented automatically.  The content will be
 * written to HCCA after HC has incremented the FrameNumber at each frame
 * boundary and sent a SOF but before HC reads the first ED in that Frame.
 * After writing to HCCA, HC will set the StartofFrame in HcInterruptStatus.
 */
#define HcFmNumber_FN 0x0000ffff

/*
 * HcPeriodicStart Register - The HcPeriodicStart register has a 14-bit
 * programmable value which determines when is the earliest time HC should
 * start processing the periodic list
 */
/* PeriodicStart - After a hardware reset, this field is cleared.  This is
 * then set by HCD during the HC initialization.  The value is calculated
 * roughly as 10% off from HcFmInterval.  A typical value will be 3E67h.
 * When HcFmRemaining reaches the value specified, processing of the
 * periodic lists will have priority over Control/Bulk processing.  HC will
 * therfore start processing the Interrupt list after completing the
 * current Control or Bulk transation that is in progress.
 */
#define HcPeriodicStart_PS 0x00003fff

/*
 * HcLSThreshold Register - The HcLSThreshold register contains an 11-bit
 * value used by the Host Controller to determine whether to commit to the
 * transfer of a maximum of 8-byte LS packet before EOF.  Neither the Host
 * Controller nor the Host Controller Driver are allowed to change this value.
 */
/* LSThreshold - This field contains a value which is compared to the
 * FrameRemaining field prior to initiating a Low Speed transaction.  The
 * transaction is started only if FrameRemaining >= this field.  The value
 * is calculated by HCD with the consideration of transmission and setup
 * overhead.
 */
#define HcLSThreshold_LST 0x00000fff

/*
 * Root Hub Partition - All registers included in this partition are
 * dedicated to the USB Root Hub which is an integral part of the Host
 * Controller though still a functionally separate entity.  The HCD emulates
 * USBD accesses to the Root Hub via a register interface.  The HCD maintains
 * many USB-defined hub features which are not required to be supported in
 * hardware.  For example, the Hub's Device, Configuration, Interface, and
 * Endpoint Descriptors are maintained only in the HCD as well as some static
 * fields of the Class Descriptor.  The HCD also maintains and decodes the
 * RootHub's device address as well as other trivial operations which are
 * better suited to software than hardware.
 *
 * The Root Hub register interface is otherwise developed to maintain
 * similarity of bit organization and operation to typical hubs which are
 * found in the system.  Below are four register definitions:
 * HcRhDescriptorA, HcRhDescriptorB, HcRhStatus, and HcRhPortStatus[1:NDP].
 * Each register is read and written as a Dword.  These registers are only
 * written during initialization to correspond with the system implementation.
 * The HcRhDescriptorA and HcRhDescriptorB registers should be implemented
 * such that they are writeable regardless of the HC USB state.  HcRhStatus
 * and HcRhPortStatus must be writeable during the USBOPERATIONAL state.
 */
/*
 * HcRhDescriptorA Register - The HcRhDescriptorA register is the first
 * register of two describing the characteristics of the Root Hub.  Reset
 * values are implementation-specific.  The descriptor length (11),
 * descriptor type (TBD), and hub controller current (0) fields of the
 * hub Class Descriptor are emulated by the HCD.  All other fields are
 * located in the HcRhDescriptorA and HcRhDescriptorB registers.
 */
/* NumberDownstreamPorts - These bits specify the number of downstream
 * ports supported by the Root Hub.  It is implementation-specific.  The
 * minimum number of ports is 1.  The maximum number of ports supported
 * by OpenHCI is 15.
 */
#define HcRhDescriptorA_NDP	0x000000ff

/* PowerSwitchingMode - This bit is used to specify how the power switching
 * of the Root Hub ports is controlled.  It is implementation-specific.
 * This field is only valid if the NoPowerSwitching field is cleared.
 *   0: all ports are powered at the same time.
 *   1: each port is powered individually.  This mode allows port power to
 *      be controlled by either the global switch or per-port switching.  If
 *      the PortPowerControlMask bit is set, the port responds only to port
 *      power commands (Set/ClearPortPower).  If the port mask is cleared,
 *      then the port is controlled only by the global power switch
 *      (Set/ClearGlobalPower).
 */
#define HcRhDescriptorA_PSM	0x00000100

/* NoPowerSwitching - These bits are used to specify whether power
 * switching is supported or ports are always powered.  It is
 * implementation-specific.  When this bit is cleared, the
 * PowerSwitchingMode specifies global or per-port switching.
 * 0: Ports are power switched
 * 1: ports are always powered on when the HC is powered on
 */
#define HcRhDescriptorA_NPS	0x00000200

/* DeviceType - This bit specifies that the Root Hub is not a compound
 * device.  The Root Hub is not permitted to be a compound device.  This
 * field should always read/write 0.
 */
#define HcRhDescriptorA_DT	0x00000400

/* OverCurrentProtectionMode - This bit describes how the overcurrent
 * status for the RootHub ports are reported.  At reset, this field
 * should reflect the same mode as PowerSwitchingMode.
 */
#define HcRhDescriptorA_OCPM	0x00000800

/* NoOverCurrentProtection - This bit describes how the overcurrent status
 * for the Root Hub ports are reported.  When this bit is cleared, the
 * OverCurrentProtectionMode field specifies global or per-port reporting.
 * 0: Over-current status is reported collectively for all downstream ports.
 * 1: No overcurrent protection supported.
 */
#define HcRhDescriptorA_NOCP	0x00001000

/* PowerOnToPowerGoodTime - This byte specifies the duration HCD has to wait
 * before accessing a powered-on port of the Root Hub.  It is
 * implementation-specific.  The unit of time is 2ms.  The duration
 * is calculated as POTPGT * 2ms.
 */
#define HcRhDescriptorA_POTPGT	0xff000000

/*
 * HcRhDescriptorB Register - The HcRhDescriptorB register is the second
 * register of two describing the characteristics of the Root Hub.  These
 * fields are written during initialization to correspond with the system
 * implementation.  Reset values are implementation-specific.
 */
/* DeviceRemovable - Each bit is dedicated to a port of the Root Hub.
 * When cleared, the attached device is removable.  When set, the attached
 * device is not removable.
 * bit0:  Reserved
 * bit1:  Device attached to Port #1
 * bit2:  Device attached to Port #2 
 * ...
 * bit15: Device attached to Port #15
 */
#define HcRhDescriptorB_DR	0x0000ffff

/* PortPowerControlMast - Each bit indicates if a port is affected by a
 * global power control command when PowerSwitchingMode is set.  When set,
 * the port's power state is only affected by per-port power control
 * (Set/ClearPortPower).  When cleared, the port is controlled by the
 * global power switch (Set/ClearGlobalPower).  If the device is configured
 * to global switching mode (PowerSwitchingMode=0), this field is not valid.
 * bit0:  Reserved
 * bit1:  Ganged-power mask on port#1
 * bit2:  Ganged-power mask on port#2
 * ...
 * bit15: Ganged-power mask on port#15
 */
#define HcRhDescriptorB_PPCM	0xffff0000

/*
 * HcRhStatus Register - The HcRhStatus register is divided into two
 * parts.  The lower word of a Dword represents the Hub Status field and
 * upper word represents the Hub Status Change field.  Reserved bits
 * should always be written '0'.
 */
/* (read)LocalPowerStatus - The Root Hub does not support the local power
 * status feature; thus, this bit is always read as '0'.
 *
 * (write)ClearGlobalPower - In global power mode (PowerSwitchingMode=0).
 * This bit is written to '1' to turn off power to all ports (clear
 * PortPowerStatus).  In per-port power mode, it clears PortPowerStatus
 * only on ports whose PortPowerControlMask bit is not set.  Writing a '0'
 * has no effect.
 */
#define HcRhStatus_LPS		0x00000001

/* OverCurrentIndicator - This bit reports overcurrent conditions when
 * the global reporting is implemented.  When set, an overcurrent condition
 * exists.  When cleared, all power operations are normal.  If per-port
 * overcurrent protection is implemented this bit is always '0'.
 */
#define HcRhStatus_OCI		0x00000002

/* (read)DeviceRemoteWakeupEnable - This bit enables a ConnectStatusChange
 * bit as a resume event, causing a USBSUSPEND to USARESUME state transition
 * and setting the ResumeDetected interrupt.
 * 0 = ConnectStatusChange is not a remote wakeup event.
 * 1 = ConnectStatusChange is a remote wakeup event
 *
 * (write)SetRemoteWakeupEnable - Writing a '1' sets
 * DeviceRemoveWakeupEnable.  Writing a '0' has no effect.
 */
#define HcRhStatus_DRWE		0x00008000

/* (read)LocalPowerStatusChange - The Root Hub does not support the
 * local power status feature; thus, this bit is always read as '0'.
 *
 * (write)SetGlobalPower - In global power mode (PowerSwitchingMode=0).
 * This bit is written to '1' to turn on power to all ports (clear
 * PortPowerStatus).  In per-port power mode, it sets PortPowerStatus
 * only on ports whose PortPowerControlMask bit is not set.  Writing a
 * '0' has no effect.
 */
#define HcRhStatus_LPSC		0x00010000

/* OverCurrentIndicatorChange - This bit is set by hardware when a change
 * has occurred to the OCI field of this register.  The HCD clears this
 * bit by writing a '1'.  Writing a '0' has no effect.
 */
#define HcRhStatus_OCIC		0x00020000

/* (write)ClearRemoteWakeupEnable - Writing a '1' clears
 * DeviceRemoveWakeupEnable.  Writing a '0' has no effect.
 */
#define HcRhStatus_CRWE		0x80000000

/*
 * HcRhPortStatus[1:NDP] Register - The HcRhPortStatus[1:NDP] register is
 * used to control and report port events on a per-port basis.
 * NumberDownstreamPorts represents the number of HcRhPortStatus registers
 * that are implemented in hardware.  The lower word is used to reflect
 * the port status, whereas the upper word reflects the status change bits.
 * Some staus bits are implemented with special write behavior (see below).
 * If a transaction (token through handshake) is in progress when a write
 * to change port status occurs, the resulting port status change must be
 * postponed until the transaction completes.  Reserved bits should always
 * be written '0'.
 */
/* (read)CurrentConnectStatus - This bit reflects the current state of
 * the downstream port. 0 = no device connected; 1 = device connected
 *
 * (write)ClearPortEnable - the HCD writes a '1' to this bit to clear
 * the portEnableStatus bit.  Writing a '0' has no effect.  The
 * CurrentConnectStatus is not affected by any write.
 *
 * Note:  This bit is always read '1b' when the attached device is
 * nonremovable (DeviceRemovable[NDP]).
 */
#define HcRhPortStatus_CCS	0x00000001

/* (read)PortEnableStatus - This bit indicates whether the port is enabled
 * or disabled.  The Root Hub may clear this bit when an overcurrent
 * condition, disconnect event, switched-off power, or operational bus
 * error such as babble is detected.  This change also causes
 * PortEnabledStatusChange to be set.  HCD sets this bit by writing
 * SetPortEnable and clears it by writing ClearPortEnable.  This bit
 * cannot be set when CurrentConnectStatus is cleared.  This bit is also
 * set, if not already, at the completion of a port reset when
 * resetStatusChange is set or port suspend when SuspendStatusChange is
 * set.  0 = port is disabled; 1 = port is enabled.
 *
 * (write)SetPortEnable - The HCD sets PortEnableStatus by writing a '1'.
 * Writing a '0' has no effect.  If CurrentConnectStatus is cleared, this
 * write does not set PortEnableStatus, but instead sets ConnectStatusChange.
 * This informs the driver that it attempted to enable a disconnected port.
 */
#define HcRhPortStatus_PES	0x00000002

/* (read)PortSuspendStatus - This bit indicates the port is suspended or
 * in the resume sequence.  It is set by a SetSuspendState write and
 * cleared when PortSuspendStatusChange is set at the end of the resume
 * interval.  This bit cannot be set if CurrentConnectStatus is cleared.
 * This bit is also cleared when PortResetStatusChange is set at the end
 * of the port reset or when the HC is placed in the USBRESUME state.  If
 * an upstream resume is inprogress, it should propagate to the HC.
 * 0 = port is not suspended; 1 = port is suspended.
 * 
 * (write)SetPortSuspend - The HCD sets the PortSuspendStatus bit by
 * writing a '1' to this bit.  Writing a '0' has no effect.  If
 * CurrentConnectStatus is cleared, this write does not set
 * PortSuspendStatus; instead it set ConnectStatusChange.  This informs
 * the driver that it attempted to suspend a disconnected port.
 */
#define HcRhPortStatus_PSS	0x00000004

/* (read)PortOverCurrentIndicator - This bit is only valid when the Root
 * Hub is configured in such a way that overcurrent conditions are reported
 * on a per-port basis.  If per-port overcurrent reporting is not supported,
 * this bit is set to 0.  If cleared, all power operations are normal for
 * this port.  If set, an overcurrent condition exists on this port.  This
 * bit always reflects the overcurrent input signal.
 * 0 = no overcurrent condition; 1 = overcurrent condition detected.
 *
 * (write)ClearSuspendStatus - The HCD writes a '1' to initiate a resume.
 * Writing a '0' has no effect.  A resume is initiated only if
 * PortSuspendStatus is set.
 */
#define HcRhPortStatus_POCI	0x00000008

/* (read)PortResetStatus - When this bit is set by a write to SetPortReset,
 * port reset signaling is asserted.  When reset is completed, this bit
 * is cleared when PortResetStatusChange is set.  This bit cannot be set if
 * CurrentConnectStatus is cleared.
 * 0 = port reset signal is not activie; 1 = port reset signal is active.
 * 
 * (write)SetPortReset - The HCD sets the port reset signaling by writing
 * a '1' to this bit.  Writing a '0' has no effect.  If CurrentConnectStatus
 * is cleared, this write does not set PortResetStatus, but instead sets
 * ConnectStatusChange.  This informs the driver that it attempted to reset
 * a disconnected port.
 */
#define HcRhPortStatus_PRS	0x00000010

/* (read)PortPowerStatus - This bit reflects the port's power status,
 * regardless of the type of power switching implemented.  This bit is
 * cleared if an overcurrent condition is detected.  HCD sets this bit by
 * writing SetPortPower or SetGlobalPower.  HCD clears this bit by writing
 * ClearPortPower or ClearGlobalPower.  Which power control switches are
 * enabled is determined by PowerSwitchingMode and PortControlMask[NDP].
 * In global switching mode (PowerSwitchingMode=0), only Set/Clear
 * GlobalPower controls this bit in per-port power switching
 * (PowerSwitchingMode=1), if the PortPowerControlMask[NDP] bit for the
 * port is set, only Set/ClearPortPower commands are enabled.  If the
 * mask is not set, only Set/ClearGlobalPower commands are enabled.  When
 * port power is disabled, CurrentConnectStatus, PortEnableStatus,
 * PortSuspendStatus, and PortResetStatus should be reset.
 * 0 = port power is off; 1 = port power is on
 *
 * (write)SetPortPower - The HCD writes a '1' to set the PortPowerStatus bit.
 * Writing a '0' has no effect.
 *
 * Note:  This bit always reads '1b' if power switching is not supported.
 */
#define HcRhPortStatus_PPS	0x00000100

/* (read)LowSpeedDeviceAttached - This bit indicates the speed of the device
 * attached to this port.  When set, a Low Speed device is attached to this
 * port.  When clear, a Full Speed device is attached to this port.  This
 * field is valid only when the CurrentConnectStatus is set.
 * 0 = full speed device attached; 1 = low speed device attached
 *
 * (write)ClearPortPower - The HCD clears the PortPowerStatus bit by
 * writing a '1' to this bit.  Writing a '0' has no effect.
 */
#define HcRhPortStatus_LSDA	0x00000200

/* ConnectStatusChange - This bit is set whenever a connect or disconnect
 * event occurs.  The HCD writes a '1' to clear this bit.  Writing a '0'
 * has no effect.  If CurrentConnectStatus is cleared when a SetPortReset,
 * SetPortEnable, or SetPortSuspend write occurs, this bit is set to force
 * the driver to re-evaluate the connection status since these writes should
 * not occur if the port is disconnected.
 * 0 = no change in CurrentConnectStatus;  1 = change in CurrentConnectStatus
 *
 * Note: If the DeviceRemovable[NDP] bit is set, this bit is set only after
 * a Root Hub reset to inform the system that the device is attached.
 */
#define HcRhPortStatus_CSC	0x00010000

/* PortEnableStatusChange - This bit is set when hardware events cause
 * the PortEnableStatus bit to be cleared.  Changes from HCD writes do not
 * set this bit.  The HCD writes a '1' to clear this bit.  Writing a '0' has
 * no effect.
 * 0 = no change in PortEnableStatus; 1 = change in PortEnableStatus.
 */
#define HcRhPortStatus_PESC	0x00020000

/* PortSuspendStatusChange - This bit is set when the full resume sequence
 * has been completed.  This sequence includes the 10s resume pulse, LS EOP,
 * and 3ms resychronization delay.  The HCD writes a '1' to clear this bit.
 * Writing a '0' has no effect.  This bit is also cleared when
 * ResetStatusChange is set.
 * 0 = resume is not completed; 1 = resume completed.
 */
#define HcRhPortStatus_PSSC	0x00040000

/* PortOverCurrentIndicatorChange - This bit is valid only if overcurrent
 * conditions are reported on a per-port basis.  This bit is set when Root
 * Hub changes the PortOverCurrentIndicator bit.  The HCD writes a '1' to
 * clear this bit.  Writing a '0' has not effect.
 * 0 = no change in PortOverCurrentIndicator
 * 1 = PortOverCurrentIndicator has changed
 */
#define HcRhPortStatus_OCIC	0x00080000

/* PortResetStatusChange - This bit is set at the end of the 10-ms port
 * reset signal.  The HCD writes a '1' to clear this bit.  Writing a '0'
 * has no effect.
 * 0 = port reset is not complete
 * 1 = port reset is complete
 */
#define HcRhPortStatus_PRSC	0x00100000

#endif /* _USB_OHCI_H_ */
