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
 * @(#)$RCSfile: usb_hid.h,v $ $Revision: 1.1.11.4 $ (DEC) $Date: 1999/01/12 13:11:31 $
 */

/*
 * Forward declarations
 */
#ifndef _USB_HID_H_
#define _USB_HID_H_

#include <sys/types.h>
#include <io/common/iotypes.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/dec/usb/usbd.h>

struct collection;

struct hid_descriptor {
    U8 Length;			/* Size of this descriptor in bytes */
    U8 DescriptorType;		/* HID descriptor type (assigned by USB) */
    U16 bcdHID;			/* HID Class Specification release number
				 * in binary-coded decimal */
    U8 CountryCode;		/* Hardware target country */
    U8 NumDescriptors;		/* Number of HID class descriptors to follow */
    U8 ReportDescriptorType;	/* Report descriptor type */
    U8 DescriptorLength1;	/* Total length of report descriptor */
    U8 DescriptorLength2;	/* Total length of report descriptor */
};

/*
 * JANET - add optional HID descriptor structures.
 */

/*
 * The structure hid_field defines how to access a certain
 * data field of a HID report.  The following macro,
 * HID_GET_FIELD() does the actual extraction of the data
 * from the given report "buf".
 */
struct hid_field {
    U8 flags;
    U8 byte_offset;
    U8 bit_offset;
    U8 size;
};
#define HID_GET_FIELD(buf, hid)						\
    ((((char *)(buf))[(hid)->byte_offset] >> (hid)->bit_offset) &	\
        ((1 << (hid)->size) - 1))

typedef struct hid_softc {
    USBD_DESCRIPTOR_HEADER desc_header;
    int softc_type;
    int flags;
#define HID_DECONFIG_DEVICE		0x0001

    U64 interface_handle;
    U64 device_handle;

    struct usb_configuration_descriptor *config_desc;
    struct usb_interface_descriptor *interface_desc;

    struct hid_descriptor *hid_desc;
    char *report_desc;
    char *physical_desc;
    U32 report_size;
    U8 endpoint_count;
    USBD_PIPE_HANDLE *endpoint_pipes;

    struct collection *collection;
    U32 collection_count;

    void *device_interface;
    void (*register_device)();
    void (*deregister_device)();
    int (*process_interrupt)();

} HID_SOFTC;

/*
 * Used to link into the Digital UNIX ws-mouse interface
 */
typedef struct hid_mouse_interface {
    ws_hardware_type hardware_type;  /* This must be first */
    ws_pointer pointer;
    int device_num;
    U64 interface_handle;
    HID_SOFTC *hid_sc;

    /*
     * How to decode the reports from the mouse.
     */
    U8 report_id;
    U8 button_count;
    U8 relative;
    struct hid_field left;
    struct hid_field right;
    struct hid_field middle;
    struct hid_field xcord;
    struct hid_field ycord;
    struct hid_field wheel;

} HID_MOUSE_INTERFACE;

/*
 * Used to link into the Digital UNIX ws-keyboard interface
 */
typedef struct hid_keyboard_interface {
    int device_num;
    int hid_attached_keyboards_index;
    U64 interface_handle;
    HID_SOFTC *hid_sc;

    /*
     * How to decode the reports from the keyboard.
     */
    int keycode_count;
    struct hid_field *keycodes;
    struct hid_field modifiers;

    char *last_leds;
    struct hid_field leds;

    char *last_report;
    int report_size;

} HID_KEYBOARD_INTERFACE;

/*
 * The short item format packs the item size, type, and tag into the first
 * byte.  The first bute may be followed by 0, 1, 2, or 4 optional data
 * bytes depending on the size of the data.
 *
 * A short item tag doesn't have an explicit value for "size" associated
 * with it.  Instead, the value of the item data part determines the size of
 * the item.  That is, if the item data can be represented in one byte, then
 * the data part can be specified as 1 byte, although this is not required.
 *
 * If a large data item is expected, it can still be abbreviated if all of
 * its high-order bits are zero.  For example, a 32-bit part in which bytes
 * 1, 2, and 3 are all 0 can be abbreviated as a single byte.
 *
 * There are three categores of short items tags:  main, global, and local.
 * The "type" specifies the tag category and consequently the item's behavior.
 */
struct short_item {
    U8 size	:2,  /* size of data, 0=0 bytes, 1=1 byte,
			2=2 bytes, 3=4 bytes */
       type     :2,  /* numberic expression identifying type of item:
			0=main, 1=global, 2=local, 3=reserved */
       tag      :4;  /* numeric expression specifying function of item */
    U8 data[4];      /* Could be 0, 1, 2, or 4 depending on "size" */
};

/*
 * Like the short item format, the long item format packs the item size, 
 * type, and tag into the first byte.  The long item format uses a 
 * special item tag value to indicate that it is a long item.  The long
 * item size and long item tag are each 8-bit quantities.  The item data
 * may contain up to 255 bytes of data.
 */
#define LONG_ITEM_TYPE 0xfe
struct long_item {
    U8 type;       /* Must be LONG_ITEM_TYPE */
    U8 size;       /* Number of bytes in data */
    U8 tag;        /* long item tag */
    U8 data;       /* optional data items [255] */
};

/*
 * Report descriptor defines (Short item types)
 */
#define MAIN_ITEM_TYPE		0
#define GLOBAL_ITEM_TYPE	1
#define LOCAL_ITEM_TYPE		2
#define RESERVED_ITEM_TYPE	3

/*
 * Main Item tags
 */
#define INPUT_ITEM_TAG		0x8
#define OUTPUT_ITEM_TAG		0x9
#define FEATURE_ITEM_TAG	0xb
#define COLLECTION_ITEM_TAG	0xa
#define END_COLLECTION_ITEM_TAG	0xc

/*
 * Parts of INPUT, OUTPUT, and FEATURE items.
 */
#define ITEM_PART_DATA			0x0000
#define ITEM_PART_ARRAY			0x0000
#define ITEM_PART_ABSOLUTE		0x0000
#define ITEM_PART_NOWRAP		0x0000
#define ITEM_PART_LINEAR		0x0000
#define ITEM_PART_PREFERRED_STATE	0x0000
#define ITEM_PART_NO_NULL_POSITION	0x0000
#define ITEM_PART_NONVOLATILE		0x0000
#define ITEM_PART_BIT_FIELD		0x0000
#define ITEM_PART_CONSTANT		0x0001
#define ITEM_PART_VARIABLE		0x0002
#define ITEM_PART_RELATIVE		0x0004
#define ITEM_PART_WRAP			0x0008
#define ITEM_PART_NONLINEAR		0x0010
#define ITEM_PART_NO_PREFERRED		0x0020
#define ITEM_PART_NULL_STATE		0x0040
#define ITEM_PART_VOLATILE		0x0080
#define ITEM_PART_BUFFERED_BYTES	0x0100


/*
 * Global item tags
 */
#define NGLOBAL_TAGS 12
enum global_item_tags {
    USAGE_PAGE_TAG,		/* Unsigned integer specifying the current
				 * Usage Page.  Since there are more than
				 * 256 usages, the Usage Page determines
				 * which set of usages are relevant.  The
				 * Usage Tag points to a particular usage
				 * on a given Usage Page.
				 */
    LOGICAL_MIN_TAG,		/* Extent value in logical units.  This is
				 * the minimum value that a variable or
				 * array item will report.  For example, a
				 * mouse reporting X position values from
				 * 0 to 128 would have a Logical Minimum
				 * of 0 and a Logical Maximum of 128.
				 */
    LOGICAL_MAX_TAG,		/* Extent value in logical units.  This is
				 * the maximum value that a variable or
				 * array item will report.
				 */
    PHYSICAL_MIN_TAG,		/* Minimum value for the physical extent
				 * of a variable item.  This represents the
				 * Logical minimum with units applied to it
				 */
    PHYSICAL_MAX_TAG,		/* Maximum value for the physical extent
				 * of a variable item.
				 */
    UNIT_EXPONENT_TAG,		/* Value of the unit exponent in base 10.
				 */
    UNIT_TAG,			/* Unit values */
    REPORT_SIZE_TAG,		/* Unsigned integer specifying the size of
				 * the report fields in bits.  This allows 
				 * the parser to build an item map for the
				 * report handler to use
				 */
    /*
     * REPORT_ID_TAG - Specifies the Report ID.  If a Report ID tag is used
     * anywhere in Report Descriptor, all data reports for the device are
     * preceded by a single byte ID field.  All items succeeding the first
     * Report ID tag but preceding a second Report ID tag are included in a
     * report prefixed by a 1-byte ID.  All items succeeding the second but
     * preceding a third Report ID tag are included in a second report
     * prefixed by a second ID, and so on.
     *
     * This Report ID value indicates the prefix added to a particular report.
     * For example, a Report descriptor could define a 3-tyte report with a
     * Report ID of 01.  This device would generate a 4 byte data report in
     * which the first byte is 01.  The device may also generate other
     * reports, each with a unique ID.  This allows the host to distinguish
     * different types of reports arriving over a single interrupt pipe.
     * Report ID zero is reserved and should not be used.
     */
    REPORT_ID_TAG,
    REPORT_COUNT_TAG,		/* Unsigned integer specifying the number
				 * of data fields for the item; determines
				 * how many fields are included in the
				 * report for this particular item (and
				 * consequently how many bits are added to
				 * the report).
				 */
    PUSH_TAG,			/* Places a copy of the global item state
				 * table on the stack.
				 */
    POP_TAG			/* Replaces the item state table with the
				 * top structure from the stack
				 */
};

/*
 * Local item tags.
 */
#define NLOCAL_TAGS 11
enum local_item_tags {
    USAGE_TAG,			/* Usage index for an item usage;
				 * represents a suggested usage for the
				 * item or collection.  In the case where
				 * an item represents multiple controls, a
				 * usage tag may suggest a usage for every
				 * variable or element in an array.
				 */
    USAGE_MIN_TAG,		/* Defines the starting usage associated
				 * with an array or bitmap.
				 */
    USAGE_MAX_TAG,		/* Defines the ending usage associated
				 * with an array or bitmap.
				 */
    DESIGNATOR_INDEX_TAG,	/* Determines the body part used for a
				 * control.  Index points to a designator
				 * in the Physical descriptor.
				 */
    DESIGNATOR_MIN_TAG,		/* Defines the index of the starting
				 * designator associated with an array
				 * or bitmap.
				 */
    DESIGNATOR_MAX_TAG,		/* Defines the index of the ending
				 * designator associated with an array
				 * or bitmap.
				 */
    UNUSED_LOCAL_TAG,
    STRING_INDEX_TAG,		/* String index for a string descriptor;
				 * allows a string to be associated with
				 * a particular item or control.
				 */
    STRING_MIN_TAG,		/* Specifies the first string index when
				 * assigning a group of sequential strings
				 * to controls in an array or bitmap.
				 */
    STRING_MAX_TAG,		/* Specifies the last string index when
				 * assigning a group of sequential strings
				 * to controls in an array or bitmap.
				 */
    SET_DELIMITER_TAG		/* Defines the beginning or end of a set
				 * of local items, 1=open set, 0=close set
				 */
};

/*
 * Either a global or a local item
 */
struct hid_item {
    struct hid_item *flink;
    struct hid_item *blink;
    U16 type;		/* GLOBAL_ITEM_TYPE or LOCAL_ITEM_TYPE */
    U16 tag;
    I32 value;
};

struct global_stack {
    struct global_stack *flink;
    struct global_stack *blink;
    LIST_ENTRY global_list;
};

struct main_item {
    /* Used to link together main_items in a collection */
    struct main_item *flink;
    struct main_item *blink;

    /*
     * Main item description.
     */
    U8 tag;
    U8 data;

    LIST_ENTRY items; /* List of global and local items describing this
		       * main item 
		       */

    struct collection *collection; /* Points to collection main_item is a
				    * member of
				    */
};

struct collection {

    /* Used to link collections which are members of other collections */
    struct collection *flink;
    struct collection *blink;

    U8 data;	/* What type of data is contained in this collection? */
#define PHYSICAL_PART		0x00 /* Physical (group of axes) */
#define APPLICATION_PART	0x01 /* Application (mouse, keyboard) */
#define LOGICAL_PART		0x02 /* Logical (interrelated data) */

    struct collection *parent;	/* Parent collection, NULL if none */

    LIST_ENTRY main_items; /* List of struct main_item */
    int main_item_count;

    LIST_ENTRY collections; /* Collections contained by this collection */

    LIST_ENTRY items; /* List of global and local items describing this
		       * collection.
		       */
};

/*
 * Main item tags
 */

/*
 * Usage page defines (data of GLOBAL_ITEM_TYPE:USAGE_PAGE_TAG)
 */
#define UNDEFINED_USAGE_PAGE			0x00 
#define GENERIC_DESKTOP_CONTROLS_USAGE_PAGE	0x01
#define KEYBOARD_USAGE_PAGE			0x07
#define LED_USAGE_PAGE				0x08
#define BUTTON_USAGE_PAGE			0x09

/*
 * Generic Desktop Page (0x01) usage ID's
 */
#define POINTER_USAGE_ID			0x01
#define MOUSE_USAGE_ID				0x02
#define JOYSTICK_USAGE_ID			0x04
#define GAME_PAD_USAGE_ID			0x05
#define KEYBOARD_USAGE_ID			0x06
#define KEYPAD_USAGE_ID				0x07
#define X_USAGE_ID				0x30
#define Y_USAGE_ID				0x31
#define Z_USAGE_ID				0x32
#define Rx_USAGE_ID				0x33
#define Ry_USAGE_ID				0x34
#define Rz_USAGE_ID				0x35
#define SLIDER_USAGE_ID				0x36
#define DIAL_USAGE_ID				0x37
#define WHEEL_USAGE_ID				0x38
#define HAT_SWITCH_USAGE_ID			0x39
#define STYLUS_USAGE_ID				0x3a
#define PEN_PRESSURE_USAGE_ID			0x3b

/*
 * LED Page (0x08) usage IDs
 */
enum led_page_usage_ids {
    UNDEFINED_LED_USAGE_ID,
    NUM_LOCK_LED_USAGE_ID,
    CAPS_LOCK_LED_USAGE_ID,
    SCROLL_LOCK_LED_USAGE_ID,
    COMPOSE_LED_USAGE_ID,
    KANA_LED_USAGE_ID,
    POWER_LED_USAGE_ID,
    SHIFT_LED_USAGE_ID,
    DO_NOT_DISTURB_LED_USAGE_ID,
    MUTE_LED_USAGE_ID,
    TONE_ENABLE_LED_USAGE_ID,
    HIGH_CUT_FILTER_LED_USAGE_ID,
    LOW_CUT_FILTER_LED_USAGE_ID,
    EQUALIZER_ENABLE_LED_USAGE_ID,
    SOUND_FIELD_ON_LED_USAGE_ID,
    SURROUND_FIELD_ON_LED_USAGE_ID,
    REPEAT_LED_USAGE_ID,
    STEREO_LED_USAGE_ID,
    SAMPLING_RATE_DETECT_LED_USAGE_ID,
    SPINNING_LED_USAGE_ID,
    CAV_LED_USAGE_ID,
    CLV_LED_USAGE_ID,
    RECORDING_FORMAT_DETECT_LED_USAGE_ID,
    OFF_HOOK_LED_USAGE_ID,
    RING_LED_USAGE_ID,
    MESSAGE_WAITING_LED_USAGE_ID,
    DATA_MODE_LED_USAGE_ID,
    BATTERY_OPERATION_LED_USAGE_ID,
    BATTERY_OK_LED_USAGE_ID,
    BATTERY_LOW_LED_USAGE_ID,
    SPEAKER_LED_USAGE_ID,
    HEAD_SET_LED_USAGE_ID,
    HOLD_LED_USAGE_ID,
    MICROPHONE_LED_USAGE_ID,
    COVERAGE_LED_USAGE_ID,
    NIGHT_MODE_LED_USAGE_ID,
    SEND_CALLS_LED_USAGE_ID,
    CALL_PICKUP_LED_USAGE_ID,
    CONFERENCE_LED_USAGE_ID,
    STAND_BY_LED_USAGE_ID,
    CAMERA_ON_LED_USAGE_ID,
    CAMERA_OFF_LED_USAGE_ID,
    ON_LINE_LED_USAGE_ID,
    OFF_LINE_LED_USAGE_ID,
    BUSY_LED_USAGE_ID,
    READY_LED_USAGE_ID,
    PAPER_OUT_LED_USAGE_ID,
    PAPER_JAM_LED_USAGE_ID,
    REMOTE_LED_USAGE_ID,
    FORWARD_LED_USAGE_ID,
    REVERSE_LED_USAGE_ID,
    STOP_LED_USAGE_ID,
    REWIND_LED_USAGE_ID,
    FAST_FORWARD_LED_USAGE_ID,
    PLAY_LED_USAGE_ID,
    PAUSE_LED_USAGE_ID,
    RECORD_LED_USAGE_ID,
    ERROR_LED_USAGE_ID
};

/*
 * Button Page (0x09) usage IDs
 */
#define PRIMARY_BUTTON_USAGE_ID 0x01
#define SECONDARY_BUTTON_USAGE_ID 0x02
#define TERTAIRY_BUTTON_USAGE_ID 0x03


/*
 * HID Class Specific Requests ("request" field of device_request)
 */
#define HID_GET_REPORT		0x01
#define HID_GET_IDLE		0x02
#define HID_GET_PROTOCOL	0x03
#define HID_SET_REPORT		0x09
#define HID_SET_IDLE		0x0a
#define HID_SET_PROTOCOL	0x0b

/*
 * Report format for array items
 */
#define MODIFIER_KEY_LEFT_CTRL		0x01
#define MODIFIER_KEY_LEFT_SHIFT		0x02
#define MODIFIER_KEY_LEFT_ALT		0x04
#define MODIFIER_KEY_LEFT_GUI		0x08
#define MODIFIER_KEY_RIGHT_CTRL		0x10
#define MODIFIER_KEY_RIGHT_SHIFT	0x20
#define MODIFIER_KEY_RIGHT_ALT		0x40
#define MODIFIER_KEY_RIGHT_GUI		0x80

/********** Make new file hid_keyboard.h **************************/

/* first, the top row */
#define KEY_ESC			0x08
#define KEY_F1			0x09	/* remap of raw 0x07 */
#define KEY_F2			0x0f
#define KEY_F3			0x17
#define KEY_F4			0x1f
#define KEY_F5			0x27
#define KEY_F6			0x2f
#define KEY_F7			0x37
#define KEY_F8			0x3f
#define KEY_F9			0x47
#define KEY_F10			0x4f
#define KEY_F11			0x56
#define KEY_F12			0x5e
#define KEY_F13			0x18	/* LK411 only - remap of raw 0x09 */
#define KEY_F14			0x0a	/* LK411 only */
#define KEY_HELP		0x0b	/* LK411 only */
#define KEY_DO			0x0c	/* LK411 only */
#define KEY_F17			0x10	/* LK411 only */
#define KEY_PRINT_SCREEN	0x57	/* LK411 F18 */
#define KEY_SCROLL_LOCK		0x5f	/* LK411 F19 */
#define KEY_PAUSE		0x62	/* LK411 F20 */

/* editing keypad */
#define KEY_INSERT		0x67
#define KEY_HOME		0x6e
#define KEY_PAGE_UP		0x6f
#define KEY_DELETE		0x64
#define KEY_END			0x65
#define KEY_PAGE_DOWN		0x6d

/* numeric keypad */
#define KEY_KP_0		0x70
#define KEY_KP_PERIOD		0x71
#define KEY_KP_ENTER		0x79
#define KEY_KP_1		0x69
#define KEY_KP_2		0x72
#define KEY_KP_3		0x7a
#define KEY_KP_4		0x6b
#define KEY_KP_5		0x73
#define KEY_KP_6		0x74
#define KEY_KP_PLUS		0x7c	/* LK411 KP_COMMA */
#define KEY_KP_7		0x6c
#define KEY_KP_8		0x75
#define KEY_KP_9		0x7d
#define KEY_KP_NUMLOCK		0x76	/* LK411 KP_F1 */
#define KEY_KP_SLASH		0x77	/* LK411 KP_F2 */
#define KEY_KP_STAR		0x7e	/* LK411 KP_F3 */
#define KEY_KP_HYPHEN		0x84	/* LK411 KP_F4 */

/* arrow (cursor) keys */
#define KEY_LEFT		0x61
#define KEY_RIGHT		0x6a
#define KEY_UP			0x63
#define KEY_DOWN		0x60

/* modifier keys */
#define KEY_SHIFT_L		0x12
#define KEY_SHIFT_R		0x59
#define KEY_ALT_L		0x19
#define KEY_ALT_R		0x39
#define KEY_CTRL_L		0x11
#define KEY_CTRL_R		0x58	/* LK411 COMPOSE_R */
#define KEY_CAPS_LOCK		0x14
#define KEY_COMPOSE_L		0x28	/* LK411 only */

/* misc keys */
#define KEY_BACKSPACE		0x66
#define KEY_ENTER		0x5a
#define KEY_TAB			0x0d

/* typewriter keys - top row */
#define KEY_TILDE		0x0e
#define KEY_TILDE_102J		0x53
#define KEY_TR_1		0x16
#define KEY_TR_2		0x1e
#define KEY_TR_3		0x26
#define KEY_TR_4		0x25
#define KEY_TR_5		0x2e
#define KEY_TR_6		0x36
#define KEY_TR_7		0x3d
#define KEY_TR_8		0x3e
#define KEY_TR_9		0x46
#define KEY_TR_0		0x45
#define KEY_UBAR		0x4e
#define KEY_UBAR_J		0x51
#define KEY_PLUS		0x55

/* typewriter keys - 2nd row */
#define KEY_Q			0x15
#define KEY_W			0x1d
#define KEY_E			0x24
#define KEY_R			0x2d
#define KEY_T			0x2c
#define KEY_Y			0x35
#define KEY_U			0x3c
#define KEY_I			0x43
#define KEY_O			0x44
#define KEY_P			0x4d
#define KEY_LBRACE		0x54
#define KEY_RBRACE		0x5b
#define KEY_VBAR		0x5c
#define KEY_VBAR_J		0x5d
#define KEY_VBAR_102		0x13

/* typewriter keys - 3rd row */
#define KEY_A			0x1c
#define KEY_S			0x1b
#define KEY_D			0x23
#define KEY_F			0x2b
#define KEY_G			0x34
#define KEY_H			0x33
#define KEY_J			0x3b
#define KEY_K			0x42
#define KEY_L			0x4b
#define KEY_SEMICOLON		0x4c
#define KEY_QUOTE		0x52

/* typewriter keys - 4th row */
#define KEY_Z			0x1a
#define KEY_X			0x22
#define KEY_C			0x21
#define KEY_V			0x2a
#define KEY_B			0x32
#define KEY_N			0x31
#define KEY_M			0x3a
#define KEY_COMMA		0x41
#define KEY_PERIOD		0x49
#define KEY_QMARK		0x4a

/* typewriter keys - bottom row */
#define KEY_SPACE		0x29

/* Japanese keyboard (PCXAJ-AA) support */
#define KEY_MUHENKAN		0x85
#define KEY_HENKAN		0x86
#define KEY_HIRAGANA		0x87



/*
 * HID interface functions
 */

/*
 * Function: hid_set_protocol()
 *
 * Description:
 *   Set the protocol to the given value.  Allowed values are
 *   HID_BOOT_PROTOCOL and HID_REPORT_PROTOCOL.
 */
USBD_STATUS
hid_set_protocol(HID_SOFTC *hid_sc, U16 protocol);

#define HID_BOOT_PROTOCOL	0
#define HID_REPORT_PROTOCOL	1

/*
 * Function: hid_set_report()
 *
 * Description:
 *   Send the report described by report_type, report_id, report_length
 *   and report to the HID interface associated with hid_sc.
 */
USBD_STATUS hid_set_report(HID_SOFTC *hid_sc,
			   U8 report_type,
			   U8 report_id,
			   U16 report_length,
			   char *report);

#define HID_REPORT_TYPE_INPUT		0x01
#define HID_REPORT_TYPE_OUTPUT		0x02
#define HID_REPORT_TYPE_FEATURE		0x03

#endif /* _USB_HID_H_ */
