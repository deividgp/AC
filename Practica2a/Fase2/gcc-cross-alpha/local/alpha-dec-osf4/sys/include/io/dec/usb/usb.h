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
 * @(#)$RCSfile: usb.h,v $ $Revision: 1.1.14.3 $ (DEC) $Date: 1998/11/29 14:18:13 $
 */

#ifndef _USB_H_
#define _USB_H_

#include <io/dec/usb/usbdi_os.h>

/*
 * The information in this file is based on the Universal Serial Bus
 * Specification Rev 1.0.
 *
 * This file will be distributed as source.
 */

/*
 * Maximum USB device ID
 */
#define USB_MAX_DEVICE_ID 127

/*
 * USB Device Requests - All USB devices respond to requests from the host
 * on the device's default pipe.  These requests are made using control
 * transfers.  The request and the request's parameters are sent to the
 * device in the setup packet.  The host is responsible for establishing
 * the values passed in the following fields.  Every setup packet has eight
 * bytes.
 */
struct usb_device_request {
    U8  request_type;
#define TYPE_HOST_TO_DEVICE		0x00
#define TYPE_DEVICE_TO_HOST		0x80
#define TYPE_STANDARD_TYPE		0x00
#define TYPE_CLASS_TYPE			0x20
#define TYPE_VENDOR_TYPE		0x40
#define TYPE_DEVICE_RECIPIENT		0x00
#define TYPE_INTERFACE_RECIPIENT	0x01
#define TYPE_ENDPOINT_RECIPIENT		0x02
#define TYPE_OTHER_RECIPIENT		0x03

    U8  request;  /* Specific request (refer to Table 9-2) */
#define REQUEST_GET_STATUS		0
#define REQUEST_CLEAR_FEATURE		1
#define REQUEST_GET_STATE		2
#define REQUEST_SET_FEATURE		3
#define REQUEST_SET_ADDRESS		5
#define REQUEST_GET_DESCRIPTOR		6
#define REQUEST_SET_DESCRIPTOR		7
#define REQUEST_GET_CONFIGURATION	8
#define REQUEST_SET_CONFIGURATION	9
#define REQUEST_GET_INTERFACE		10
#define REQUEST_SET_INTERFACE		11
#define REQUEST_SYNCH_FRAME		12

    U16 value;    /* Word-sized field that varies according to request */
#define DEVICE_REMOTE_WAKEUP	1
#define ENDPOINT_STALL		0

    U16 index;    /* Word sized field that varies according to
		   * request - typically used to pass an index or offset
		   */
    U16 length;   /* Number of bytes to transfer if there is a data phase */
};

/* 
 * Descriptor Types
 */
#define USB_DESCRIPTOR_TYPE_DEVICE		0x01
#define USB_DESCRIPTOR_TYPE_CONFIGURATION	0x02
#define USB_DESCRIPTOR_TYPE_STRING		0x03
#define USB_DESCRIPTOR_TYPE_INTERFACE		0x04
#define USB_DESCRIPTOR_TYPE_ENDPOINT		0x05
#define USB_DESCRIPTOR_TYPE_HID			0x21
#define USB_DESCRIPTOR_TYPE_REPORT		0x22
#define USB_DESCRIPTOR_TYPE_PHYSICAL		0x23
#define USB_DESCRIPTOR_TYPE_HUB			0x29

/*
 * Device Descriptor - A device descriptor describes general information
 * about a USB device.  It includes information that applies globally to
 * the device and all of the device's configurations.  A USB device has
 * only one device descriptor.
 *
 * All USB devices have an endpoint zero used by the default pipe.  The
 * maximum packet size of a device's endpoint zero is described in the device
 * descriptor.  Endpoints specific to a configuration and its interface(s)
 * are described in the configuration descriptor.  A configuration and its
 * interface(s) do not include an endpoint descriptor for endpoint zero.
 * Other than the maximum packet size, the characteristics of endoint zero
 * are defined by the USB specificiation and are the same for all USB devices.
 */
struct usb_device_descriptor {
    U8 Length;			/* Numeric expression specifying the size of
				 * this descriptor
				 */
    U8 DescriptorType;		/* Device descriptor type (assigned by USB) */
    U16 bcdUSB;			/* binary-coded decimal specification # */
    U8 DeviceClass;		/* Class code (assigned by USB).  Note that 
				 * the HID class is defined in the Interface
				 * descriptor 
				 */
#define HUB_DEVICE_CLASS 0x09
    U8 DeviceSubClass;		/* Subclass code (assigned by USB).  These
				 * codes are qualified by the value of the
				 * DeviceClass field.
				 */
#define HUB_DEVICE_SUB_CLASS 0x01
    U8 DeviceProtocol;		/* Protocol code.  These codes are qualified
				 * by the value of the DeviceSubClass field.
				 */
    U8 MaxPacketSize;		/* Maximum packet size for endpoint zero (only
				 * 8, 16, 32, or 4 are valid).
				 */
    U16 idVendor;		/* Vendor ID (assigned by USB) */
    U16 idProduct;		/* Product ID (assigned by manufacturer) */
    U16 bcdDevice;		/* Device release number */
    U8 iManufacturer;		/* Index of String desc describing manufact */
    U8 iProduct;		/* Index of string desc describing product */
    U8 iSerialNumber;		/* Index of String desc describing serial # */
    U8 NumConfigurations;	/* Number of possible configurations */
};

/*
 * Configuration Descriptor - The configuration descriptor describes
 * information about a specific device configuration.  The descriptor
 * contains a ConfigurationValue field with a value that, when used as
 * a parameter to the Set Configuration request, causes the device to
 * assume the described configuration.
 *
 * The descriptor describes the number of interfaces provided by the
 * configuration.  Each interface may operate independently.  For example,
 * an ISDN device might be configured with two interfaces, each providing
 * 64kBs bi-directional channels that have separate data sources or sinks
 * on the host.  Another configuration might present the ISDN device as
 * a single interface, bonding the two channels into one 128 kBs
 * bi-directional channel.
 *
 * When the host requests the configuration descriptor, all related
 * interface and endpoint descriptors are returned.
 *
 * A USB device has one or more configuration descriptors.  Each
 * configuration has one or more interface and each interface has one or
 * more endpoints.  An endpoint is not shared among interface within a
 * single configuration unless the endpoint is used by alternate settings
 * of the same interface.  Endpoints may be shared among interface that are
 * part of different configurations without this restriction.
 *
 * Once configured, devices may support limited adjustments to the
 * configuration.  If a particular interface has alternate settings, an
 * alternate may be slected after configuration.  Within an interface,
 * an isochronous endpoint's maximum packet size may also be adjusted.
 */
struct usb_configuration_descriptor {
    U8 Length;			/* Size of this descriptor in bytes */
    U8 DescriptorType;		/* Configuration (assigned by USB) */
    U16 TotalLength;		/* Total length of data returned for this
				 * configuration.  Includes the combined
				 * length of all returned descriptors
				 * (configuration, interface, endpoint, and
				 * HID) returned for this configuration.  This
				 * value includes the HID descriptor but none
				 * of the other HID class descriptors (report
				 * or designator).
				 */
    U8 NumInterfaces;		/* Number of interfaces supported by this
				 * configuration.
				 */
    U8 ConfigurationValue;	/* Value to use as an argument to Set
				 * Configuration to select this configuration
				 */
    U8 iConfiguration;		/* Index of string descriptor describing this
				 * configuration.
				 */
    U8 bmAttributes;		/* Configuration characteristics */
#define CONFIG_BUS_POWERED   0x80
#define CONFIG_SELF_POWERED  0x40
#define CONFIG_REMOTE_WAKEUP 0x20

    U8 MaxPower;		/* Maximum power consumption of USB device
				 * from bus in this specific configuration
				 * when the device is fully operational.
				 * Expressed in 2mA units -- for example,
				 * 50 = 100mA.
				 */
};

/*
 * Interface Descriptor - This descriptor describes a specific interface
 * provided by the associated configuration.  A configuration provides one
 * or more interfaces, each with its own endpoint descriptors describing
 * a unique set of endpoints within the configuration.  When a configuration
 * supports more than one interface, the endoints for a particular interface
 * immediately follow the interface descriptor in the data returned by the
 * Get Configuration request.  An interface descriptor is always returned
 * as part of a configuration descriptor.  It cannot be directly accessed
 * with a Get or Set Descriptor request.
 *
 * An interface may include alternate settings that allow the endoints and/or
 * their characteristics to be varied after the device has been configured.
 * The default setting for an interface is always alternate setting zero.
 * The Set Interface request is used to select an alternate setting or to
 * return to the default setting .  The Get Interface request returns the
 * selected alternate setting.
 *
 * Alternate settings allow a portion of the device configuration to be
 * varied while other interfaces remain in operation.  If a configuration
 * has alternate settings for one or more of its interfaces, a spearate
 * interface descriptor and its associated endpoints are included for each
 * setting.
 *
 * If a device configuration supported a single interface with two alternate
 * settings, the configuration descriptor would be followed by an interface
 * descriptor with the IntefaceNumber and AlternaSetting fields set to zero
 * and then the endoint descriptors for that setting, followed by another
 * interface descriptor and its associated endpoint descriptors.  The second
 * interface descriptor's InterfaceNumber field would also be set to zero,
 * but the AlternateSetting field of the second interface descriptor would
 * be set to one.
 *
 * If an interface only uses endpoint zero, no endpoint descriptors follow
 * the interface descriptor and the interface identifies a request interface
 * that uses the default pipe attached to endpoint zero.  In this case the
 * NumEndpoints field shall be set to zero.
 *
 * An interface descriptor never includes endpoint zero in the number of
 * endpoints.
 */
struct usb_interface_descriptor {
    U8 Length;			/* Size of this descriptor in bytes */
    U8 DescriptorType;		/* Interface descriptor type */
    U8 InterfaceNumber;		/* Number of interface.  Zero-based value
				 * identifying the index in the array of
				 * concurrent interfaces supported by this
				 * configuration
				 */
    U8 AlternateSetting;	/* Value used to select alternate setting
				 * for the interface identified in the prior
				 * field.
				 */
    U8 NumEndpoints;		/* Number of endpoints used by this interface
				 * (excluding endpoint zero).  If this value
				 * is zero, this interface only uses endpoint
				 * zero.
				 */
    U8 InterfaceClass;		/* Class code */
#define INTERFACE_CLASS_HID			0x03
#define INTERFACE_CLASS_PRINTER			0x07
#define INTERFACE_CLASS_HUB			0x09
#define INTERFACE_CLASS_VENDOR_SPECIFIC		0xff

    U8 InterfaceSubClass;	/* Subclass code */
#define INTERFACE_SUBCLASS_NO_SUBCLASS		0x00
#define INTERFACE_SUBCLASS_BOOT_INTERFACE	0x01
#define INTERFACE_SUBCLASS_PRINTER		0x01

    U8 InterfaceProtocol;	/* Protocol code */
#define INTERFACE_PROTOCOL_NONE				0x00
#define INTERFACE_PROTOCOL_KEYBOARD			0x01
#define INTERFACE_PROTOCOL_MOUSE			0x02
#define INTERFACE_PROTOCOL_PRINTER_UNIDIRECTIONAL	0x01
#define INTERFACE_PROTOCOL_PRINTER_BIDIRECTIONAL	0x02
#define INTERFACE_PROTOCOL_VENDOR_SPECIFIC		0xff

    U8 iInterface;		/* Index of string descriptor describing this
				 * interface
				 */
};

/*
 * Endpoint Descriptor - Each endpoint used for an interface has its own
 * descriptor.  This descriptor contains the information required by the
 * host to determine the bandwidth requirements of each endpoint.  An endpoint
 * descriptor is always returned as part of a configuration descriptor.  It
 * cannot be directly accessed with a Get or Set Descriptor request.  There
 * is never an endpoint descriptor for endpoint zero.
 */
struct usb_endpoint_descriptor {
    U8 Length;			/* Size of this descriptor in bytes */
    U8 DescriptorType;		/* Endpoint descriptor type (assigned by USB)*/
    U8 EndpointAddress;		/* The address of the endpoint on the USB
				 * device described by this descriptor.  The
				 * address is encoded as follows:
				 *    Bit 0..3  The endpoint number
				 *    Bit 4..6  Reserved, reset to zero
				 *    Bit 7     Direction, ignored for Control
				 *              endpoints: 0 - OUT endpoint,
				 *              1 - IN endpoint
				 */
    U8 Attributes;		/* This field describes the endpoint's
				 * attributes when it is configured using the
				 * Configuration Value.
				 *    Bit 0..1  Transfer type:
				 *    00        Control
				 *    01        Isochronous
				 *    10        Bulk
				 *    11        Interrupt
				 *    All other bits are reserved
				 */
#define	USB_CONTROL_ENDPOINT	 0
#define	USB_ISOCHRONOUS_ENDPOINT 1
#define	USB_BULK_ENDPOINT	 2
#define	USB_INTERRUPT_ENDPOINT	 3
#define USB_ATTRIBUTE_MASK       3

    U8 maxpacket_lo;
    U8 maxpacket_hi;		/* Maximum packet size this endpoint is
				 * capable of sending or receiving when this
				 * configuration is selected.  For interrupt
				 * endpoints, this value is used to reserve
				 * the bus time in the schedule, required for
				 * the per frame data payloads.  Smaller data
				 * payloads may be sent, but will terminate
				 * the transfer and thus require intervention
				 * to restart.
				 */
    U8 Interval;		/* Interval for polling endpoint for data
				 * transfers.  Expressed in milliseconds.
				 */
};

/*
 * String Descriptor - String descriptors are optional.  If a device does
 * not support string descriptors, all references to string descriptors
 * within device, configuration, and interface descriptors must be reset
 * to zero.
 *
 * String descriptors use UNICODE encodings as defiend by The Unicode
 * Standard, Worldwide Character Encoding, Version 1.0, Volumes 1 and 2.
 * The strings in a USB device may support multiple languages.  When
 * requesing a string descriptor, the requester specifies the desired
 * language using a sixteen-bit language ID.  String index 0 for all
 * languages returns an array of two-byte codes supported by the device.
 * A USB device may omit all string descriptors. 
 *
 * The UNICCODE string descriptor is not NULL terminated.  The string
 * length is computed by subtracting two from the value of the first byte
 * of the descriptor.
 */
struct usb_string_descriptor {
    U8 Length;			/* Length of descriptor in bytes */
    U8 DescriptorType;		/* Descriptor Type */
    U8 String;
};

/*
 * Hub Descriptor
 */
struct usb_hub_descriptor {
    U8 bDescLength; /* Number of bytes in this descriptor,
		     * including this byte. */
    U8 bDescriptorType;
    U8 bNbrPorts; /* Number of downstream ports that this hub supports. */
    U8 HubCharacteristics_low;
#define HUB_POWER_SWITCHING_MASK		0x03
#define HUB_GANGED_POWER_SWITCHING		0x00
#define HUB_INDIVIDUAL_PORT_POWER_SWITCHING	0x01
#define HUB_NO_POWER_SWITCHING			0x02
#define HUB_IS_COMPOUND_DEVICE			0x04
#define HUB_OVER_CURRENT_MASK			0x18
#define HUB_GLOBAL_OVER_CURRENT			0x00
#define HUB_INDIVIDUAL_PORT_OVER_CURRENT	0x08
#define HUB_NO_OVER_CURRENT			0x10

    U8 HubCharacteristics_hi;
    U8 bPwrOn2PwrGood;
    U8 bHubContrCurrent;

    /*
     * One bit for each possible port (255 ports plus 1 for the hub) for
     * each the DeviceRemovable field and the PortPwrCtrlMask.  Thats a
     * total of 512bits or 64 bytes.
     */
    U8 DeviceRemovable_PortPwrCtrlMask[64];
};

/*
 * Hub definations and structures
 */
#define USB_HUB_CONFIGURATION_ENDPOINT	0
#define USB_HUB_STATUS_CHANGE_ENDPOINT	0x81

/*
 * Hub Class specific Requests
 */
#define CLEAR_HUB_FEATURE	(TYPE_CLASS_TYPE)
#define CLEAR_PORT_FEATURE	(TYPE_CLASS_TYPE | \
				 TYPE_ENDPOINT_RECIPIENT | \
				 TYPE_INTERFACE_RECIPIENT)
#define GET_BUS_STATE		(TYPE_DEVICE_TO_HOST | \
				 TYPE_CLASS_TYPE | \
				 TYPE_ENDPOINT_RECIPIENT | \
				 TYPE_INTERFACE_RECIPIENT)
#define GET_HUB_DESCRIPTOR	(TYPE_DEVICE_TO_HOST | TYPE_CLASS_TYPE)
#define GET_HUB_STATUS		(TYPE_DEVICE_TO_HOST | TYPE_CLASS_TYPE)
#define GET_PORT_STATUS		(TYPE_DEVICE_TO_HOST | \
				 TYPE_CLASS_TYPE | \
				 TYPE_ENDPOINT_RECIPIENT | \
				 TYPE_INTERFACE_RECIPIENT)
#define SET_HUB_DESCRIPTOR	(TYPE_CLASS_TYPE)
#define SET_HUB_FEATURE		(TYPE_CLASS_TYPE)
#define SET_PORT_FEATURE	(TYPE_CLASS_TYPE | \
				 TYPE_ENDPOINT_RECIPIENT | \
				 TYPE_INTERFACE_RECIPIENT)

/*
 * Hub Class Feature Selectors
 */
#define C_HUB_LOCAL_POWER	0
#define C_HUB_OVER_CURRENT	1
#define PORT_CONNECTION		0
#define PORT_ENABLE		1
#define PORT_SUSPEND		2
#define PORT_OVER_CURRENT	3
#define PORT_RESET		4
#define PORT_POWER		8
#define PORT_LOW_SPEED		9
#define C_PORT_CONNECTION	16
#define C_PORT_ENABLE		17
#define C_PORT_SUSPEND		18
#define C_PORT_OVER_CURRENT	19
#define C_PORT_RESET		20

#endif /* _USB_H_ */
