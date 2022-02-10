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
 *	@(#)$RCSfile: wsdevice.h,v $ $Revision: 4.2.31.3 $ (DEC) $Date: 1998/06/26 19:21:53 $
 */ 
/*
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */
/************************************************************************
 *									*
 *			Copyright (c)  1989 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/
#ifndef _WSDEVICE_H_
#define _WSDEVICE_H_

#ifdef _KERNEL
#include <machine/hal/console.h>
#endif /* _KERNEL */

/*
 *  ws_graphics flag values for
 *  overriding graphics
 *  configuration thru bootflags
 *
 *  attributes for sysconfigtab
 *  are identical execept for 
 *  being lower-case matching 
 *  strings. The ws attribute is
 *  ws_graphics_flag
 */
#define DEFAULT_GRAPHICS     1       /* no change to expected behavior */
#define FORCE_NO_GRAPHICS    2       /* tell ws to override sizer -gt */
#define FORCE_GENERIC_CONS   3       /* tell ws to not register screens */
#define USE_GENERIC_VGA      4       /* tell svga drivers to use generic vga */
#define FORCE_CALLBACK_CONS  5       /* tell ws to use generic w/callbacks */


/*
 * This file defines the interface that all 
 * workstation devices must use to register themselves with the kernel
 * workstation subsystem (ws driver).  
 *
 * It allows new devices to be added without having to modify other drivers,
 * with large code sharing among screens or devices (cursor chips, LUTs)
 * of like types.  New graphics devices should be able to run without
 * modification of the X server to support them.
 *
 */


/*
 *  ws globals for drivers
 */
extern long ws_graphics;               /* global flag for graphics failsafe */
extern int vt100_emulation;            /* indicates term emulation in-use */



/*****************************************************************************
 *
 *             workstation subsystem kernel interfaces
 *
 ****************************************************************************/

/*
 *  screen registration data structs
 */

/* Note on handles (were "closures"):
 *
 * Each function will always be called with a handle (historically called
 * a closure in the original code) to increase flexibility for writing
 * graphics code. The handle is merely a private pointer that can be used
 * to pass information specific to the set of functions being implelmented.
 *
 * While a single handle would work, one for each grouping was originally
 * defined to increase code sharing, so details of a single driver would
 * not be visible in various device specific routines, like position cursor,
 * which really only needs the coordinates and the address of the cursor
 * chip. This mechanisim allows seperate drivers to exist for components
 * of a graphics adapter, such as RAMDACs or cursor chips.
 */

typedef struct {
	caddr_t (*init_colormap_handle)(); /* init ptr to cmap driver info */
	int (*init_color_map)();           /* set up color map */
	int (*load_color_map_entry)();     /* load a color map entry */
        void(*clean_color_map)();          /* clean the color map */
	int (*video_on)();                 /* Turn screen on */
	int (*video_off)();	           /* blank screen */	
	caddr_t colormap_handle;           /* pointer to colormap driver info*/
	int (*cmap_private)();             /* Reserved */
} ws_color_map_functions;

typedef struct {
	caddr_t (*init_cursor_handle)(); /* init ptr to cursor driver info */
	int (*load_cursor)();            /* load cursor map */
	int (*recolor_cursor)();         /* recolor cursor */
	int (*set_cursor_position)();    /* position cursor */
	int (*cursor_on_off)();          /* Turn cursor on/off */
	caddr_t cursor_handle;           /* pointer to cursor driver info */
	int (*cursor_private)();         /* Reserved */
} ws_cursor_functions;

typedef struct {
	caddr_t (*init_screen_handle)(); /* init ptr to screen driver info */
	int (*init_screen)();            /* initialize screen */
	int (*clear_screen)();           /* clear screen contents */
        int (*scroll_screen)();          /* console scroll function */
	int (*blitc)();		         /* console putc function */
	int (*map_unmap_screen)();       /* memory mapping function */
	int (*ioctl)();                  /* optional adapter ioctl function */
	void (*close)();                 /* close back to console function*/
	caddr_t screen_handle;           /* pointer to screen driver info */
	int (*set_get_power_level)();    /* DPMS power management */
	int (*screen_private)();         /* Reserved */
	int (*screen_private2)();        /* Reserved */
} ws_screen_functions;

/* a screen has a screen, a color map, and a cursor */
typedef struct {
        ws_screen_descriptor *sp;
        ws_visual_descriptor *vp;
        ws_depth_descriptor *dp;
        ws_screen_functions *f;
        ws_color_map_functions *cmf;
        ws_cursor_functions *cf;
        ws_screen_box adj_screens;
	struct controller *ctlr;
} ws_screens;

#ifdef _KERNEL
/********************************************************************
 *
 *   ws_register_screen
 *   ws_register_console
 *
 *       Used to register display and the 
 *       console screen respectively. 
 *
 *   RETURN VALUES
 *
 *       SUCCESS: screen number
 *       FAILURE: -1
 *
 *
 *   NOTE:
 *         console's screen number will be
 *         WS_CONSOLE_SCREEN if it has different
 *         screen descriptor than its matching 
 *         graphics screen.  If the exact same
 *         driver code is used for both console
 *         and graphics screen, then it will
 *         be the graphics screen number.
 *
 ********************************************************************/

extern int 
ws_register_screen(ws_screen_descriptor *sp, 
		   ws_visual_descriptor *vp, 
		   ws_depth_descriptor *dp, 
		   ws_screen_functions *f, 
		   ws_color_map_functions *cmf, 
		   ws_cursor_functions *cf, 
		   struct controller *ctlr);

extern int 
ws_register_console(ws_screen_descriptor *sp, 
		    ws_visual_descriptor *vp, 
		    ws_depth_descriptor *dp, 
		    ws_screen_functions *f, 
		    ws_color_map_functions *cmf, 
		    ws_cursor_functions *cf, 
		    struct controller *ctlr);


/*************************************************
 *
 *  ws_map_region interface
 *
 *       Interface used to map I/O addresses into
 *       user space.  Typically used to map frame
 *       buffer and some register space for DDX
 * 
 *  RETURN VALUES  
 *
 *        SUCCESS:  low order bits of mapped result
 *        FAILURE:  NULL
 *
 *************************************************/ 

extern caddr_t 
ws_map_region(caddr_t kaddr,         /* kernel addr of memory to map */
	      caddr_t uaddr,         /* try to put in curproc addr */
	      register int nbytes,   /* it is this many bytes big */
	      int how,               /* ULTRIX-style protection arg */
	      int *erroraddr         /* errno addr (NULL to discard value) */
	      );


/*************************************************
 *
 *  ws_get_screen interface
 *
 *       returns pointer to ws_screen struct 
 *       for a given screen number
 * 
 *  RETURN VALUES  
 *
 *        SUCCESS:  pointer to screen_descriptor
 *        FAILURE:  NULL
 *
 *************************************************/ 

/*
 *  special ws_get_screen defines
 */
#define WS_CONSOLE_SCREEN 99           /* gets console screen struct */
#define WS_SCREEN_MATCHING_CONSOLE 98  /* gets display screen that has 
					  the same ctlr struct as the 
					  console_screen */

extern ws_screens * 
ws_get_screen(short screen_number);



/**************************************************
 *
 *  ws_regster_emulation interface
 *
 *        register basic terminal emulation
 *        functions for graphics console support
 *
 *  RETURN VALUES
 *
 *   SUCCESS: 0 (ESUCCESS)
 *   FAILURE: -1 indicates vt100 emulation will not
 *            be used, ususally because not all 
 *            functions were supplied.
 *
 **************************************************/

/* 
 *  structure containing entry points for terminal emulation support
 *  All entries are necessary for emulation to be registered 
 */
typedef struct {
	int  (*charput)();		/* put char */
	int  (*charclear)();		/* clear chars */
	int  (*charmvup)();		/* move chars up */
	int  (*charmvdown)();		/* move chars down */
	int  (*charattr)();		/* set char attribute */
} ws_emulation_functions;

/* 
 * defines for "charattr" function 
 */
#define ATTR_NORMAL	0
#define ATTR_REVERSE	1

extern int 
ws_register_emulation_functions(ws_emulation_functions *efp);

/**************************************************
 *
 *  ws_is_mouse_on interface
 *
 *        Check if X server has opened /dev/ws
 *
 *  RETURN VALUES
 *
 *   TRUE:  1   (X is up) 
 *   FALSE: 0   (X is not running)
 *
 **************************************************/
extern int 
ws_is_mouse_on(void);

/*********************************************************************
 *
 *  ws_set_graphics_console
 *
 *  Interface to allow a device driver to indicate it will be
 *  a graphics console driver in the case that this controller does
 *  not have a display screen that will register with X.
 *
 *  ARGS:
 *           ctlr = device driver's controller structure
 *           info, flags = Not used -- reserved for future use
 *  RETURNS:
 *           SUCCESS =  1
 *           FAILURE = -1
 *
 *******************************************************************/
extern int
ws_set_graphics_console(struct controller *ctlr,
                        caddr_t info,
                        unsigned int flags);


/********************************************************************
 *
 *   ws_register_screen_with_ehm interface
 *
 *       Used to register each graphics controller (i.e. display) with 
 *	 the Enhanced Hardware Manager.
 *
 *   RETURN VALUES - 
 *			0 if success
 *		       -1 if failure	
 *
 *   NOTE:
 *
 ********************************************************************/

/*
 *      Structure used during Enhanced HW Management registration
 */
struct ws_ehm_screen_info
{
        char *name;
        char *sub_category;
        int  power_mgmt_capable;
        char *mem_size;
        int  num_planes;
        int  num_colors;
        int  X_resolution;
        int  Y_resolution;
};

/* 	Structure used to hold callback routine when keyboard driver
 *	registers with EHM.
 */
struct ws_kbd_callback {
	void (*callback)();
	struct ws_kbd_callback *next;
};

extern int
ws_register_screen_with_ehm (struct ws_ehm_screen_info *sp,  
			     struct controller *ctlr);

#endif /*_KERNEL*/

/*
 *  This defines the number of supported display screens
 *  by the workstation subsystem.  It controls the number
 *  of times ws_register_screen can be called and sizes
 *  kernel data structures.  However, the sizer command
 *  graphics switches are currently limited to 3 screens.
 */
#define NUMSCREENS 16

/*
 * flags to load_{cursor,colormap} specifying whether to use
 * vblank synchronization.
 */
#define VSYNC   1
#define NOSYNC  0

/*
 *  Power Management definitions
 *  for DPMS support
 */
#define DPMS_ON            0x0   /* Hsync = 1  Vsync = 1 */
#define DPMS_STANDBY       0x1   /* Hsync = 0  Vsync = 1 */
#define DPMS_SUSPEND       0x2   /* Hsync = 1  Vsync = 0 */
#define DPMS_OFF           0x3   /* Hsync = 0  Vsync = 0 */
#define WS_SHUTDOWN        0x4   /* Hsync = 0  Vsync = 0 & Logic Shutdown */

#define DPMS_NOT_SUPPORTED  -1   /* return value */
#define DPMS_STATE_ON        1   /* DPMS active */
#define DPMS_STATE_OFF       0   /* DPMS disabled */

/* ctlr structure private field used to hold pointer to pwrmgr_devinfo
 * structure that's created on a per screen basis.
 */
#define devinfop                private[7]

/*
 * Event Management related definitions - each WS event will be
 * 	represented by an integer 
 */

#define WS_NOTIFY_KBD_HOT_SWAP       0
#define WS_NOTIFY_MOUSE_HOT_SWAP     1


/************************************************************************
 *
 *	Input device interface to WS
 *
 ************************************************************************/

/* number of input device possible */
#define NUMINPUTDEVICES 4

/* 
/* The next three structures are all part of a 'union' in 
 *  	the ws_devices structure
 */
typedef struct {
	int  hardware_type;
	int axis_count;			/* only used by extension devices */
	caddr_t device_handle;
	char *name;
	int  (*ioctl)();
	void (*init_device)();
	void (*reset_device)();
	void (*enable_device)();
	void (*disable_device)();
	void (*set_device_mode)();
	void (*get_device_info)();
} ws_input_device;	


typedef struct {
	int  hardware_type;
	int axis_count;			/* not used */
	caddr_t keyboard_handle;
	char *name;
    caddr_t (*init_keyboard_handle)();
	int  (*ioctl)();
	void (*init_keyboard)();
	void (*reset_keyboard)();
	void (*enable_keyboard)();
	void (*disable_keyboard)();
	int  (*set_keyboard_control)();
	void (*get_keyboard_info)();
	void (*ring_bell)();
	void (*process_keyboard_event)();
	void (*process_keyboard_char)(caddr_t,unsigned short);
	ws_keyboard_control control;
	ws_keyboard_definition *definition;
	ws_keycode_modifiers *modifiers;
	unsigned int *keysyms;
	unsigned char *keycodes;
	int  (*keyboard_private)();		/* Reserved */
	caddr_t private1; 		/* Reserved for future use e.g.EHM */
	caddr_t private2; 		/* Reserved for future use */
	int unused;			/* Reserved for future use */
} ws_keyboard;

typedef struct {
	int  hardware_type;
	int axis_count;			/* not used */
	caddr_t pointer_handle;
	char *name;
    caddr_t (*init_pointer_handle)();
	int  (*ioctl)();
	int  (*init_pointer)();
	void (*reset_pointer)();
	void (*enable_pointer)();
	void (*disable_pointer)();
	void (*set_pointer_mode)();
	void (*get_pointer_info)();
	void (*get_position_report)();
	int  (*process_tablet_event)();
	int  (*process_mouse_event)();
	void (*set_tablet_overhang)();
	int mswitches;			/* current pointer switches     */
#if 0
	int num_buttons;		/* number of phys buttons	*/
	int rel_abs_mode;		/* relative or absolute mode    */ 
#endif
	ws_pointer_control pr;		/* pointer rates		*/
	ws_cursor_position position;	/* current pointer position	*/
        ws_cursor_data cursor;          /* for cursor tracking          */
	ws_pointer_box suppress;	/* suppress motion when inside  */
					/* this box.			*/
	ws_pointer_box constrain;	/* prevent cursor from leaving	*/
	int tablet_scale_x;		/* scale factors for tablet pointer */
	int tablet_scale_y;
	unsigned int tablet_overhang;
        short tablet_max_x;
        short tablet_max_y;
        char tablet_x_axis;             /* 0=left, 1=right */
        char tablet_y_axis;             /* 0=bottom, 1=top */
        char tablet_new_screen;         /* 1=just entered new screen */
	int  (*pointer_private)();	/* Reserved */
	caddr_t private1; 		/* Reserved for future use (e.g.EHM)*/
	caddr_t private2; 		/* Reserved for future use */
	int unused;			/* Reserved for future use */
} ws_pointer;

typedef struct {
        int device_type;
        union {
          ws_input_device *dp;
          ws_keyboard *kp;
          ws_pointer *pp;
        } p;
} ws_devices;

/* Pointer report structure definition  - contains state information */
typedef struct {
        char state;                     /* buttons and sign bits        */
        short dx;                       /* delta X since last change    */
        short dy;                       /* delta Y since last change    */
        char bytcnt;                    /* mouse report byte count      */
} ws_pointer_report;
	
/*
 * "state" field definitions for ws_pointer_report
 *	RIGHT_BUTTON	- set if right MB is set
 *	MIDDLE_BUTTON	- set if middle MB is set
 *	LEFT_BUTTON	- set if left MB is set
 *	Y_SIGN		- set if dy is NEGATIVE
 *	X_SIGN		- set if dx is NEGATIVE
 */
#define WSPR_RIGHT_BUTTON	0x01
#define WSPR_MIDDLE_BUTTON	0x02
#define WSPR_LEFT_BUTTON	0x04
#define WSPR_Y_SIGN		0x10
#define WSPR_X_SIGN		0x20

typedef struct {
    int (*(kb_getc))(unsigned int data);
    int (*(kb_putc))(char c);
    short timeout;		/* autorepeat timeout */
    short interval;		/* autorepeat interval */
    ws_keyboard *kp;		/* keyboard associated with this device */
    int device_number;          /* device number assoc. with 'devices' array */
    unsigned int status;	/* flags */
    unsigned int keys[8];	/* current state of keys */
    ws_pointer  *p;
    ws_event_queue *queue;
    short last;
    short comp_count;
    u_short comp_chars[2];
    int reserved;               /* reserved for future use */
    caddr_t private1;           /* reserved for future use */
} ws_keyboard_state;

/* "status" field flag bit definitions for ws_keyboard_state struct */
#define KB_STATUS_SHIFT		(1<<0)
#define KB_STATUS_SHIFT_L	(1<<0)
#define KB_STATUS_CNTRL		(1<<1)
#define KB_STATUS_CNTRL_L	(1<<1)
#define KB_STATUS_CAPSLOCK	(1<<2)
#define KB_STATUS_HOLD		(1<<3)
#define KB_STATUS_NUMLOCK	(1<<4)
#define KB_STATUS_INRESET	(1<<5)
#define KB_STATUS_UPDNMODE	(1<<6)
#define KB_STATUS_REPEATING	(1<<7)
#define KB_STATUS_PREFIX	(1<<8)
#define KB_STATUS_ALT		(1<<9)
#define KB_STATUS_ALT_L		(1<<9)
#define KB_STATUS_WAIT		(1<<10)
#define KB_STATUS_COMPOSE	(1<<11)
#define KB_STATUS_COMPOSE_L	(1<<11)

/* second key constants */
#define KB_STATUS_SHIFT_R	(1<<12)
#define KB_STATUS_CNTRL_R	(1<<13)
#define KB_STATUS_ALT_R		(1<<14)
#define KB_STATUS_COMPOSE_R	(1<<15)

/* Tadpole keyboard */
/* additional prefix characters */
#define KB_STATUS_PREFIX1	(1<<16)
#define KB_STATUS_PREFIX2	(1<<17)

/* group constants */
#define KB_STATUS_SHIFT_ANY	(KB_STATUS_SHIFT_L     | KB_STATUS_SHIFT_R    )
#define KB_STATUS_CNTRL_ANY	(KB_STATUS_CNTRL_L     | KB_STATUS_CNTRL_R    )
#define KB_STATUS_ALT_ANY	(KB_STATUS_ALT_L       | KB_STATUS_ALT_R      )
#define KB_STATUS_COMPOSE_ANY	(KB_STATUS_COMPOSE_L   | KB_STATUS_COMPOSE_R  )

/* macros for testing status */
/* NOTE: some test all related keys; ie SHIFT does both left and right */
#define KB_IS_SHIFT(lp)		((lp)->status & KB_STATUS_SHIFT_ANY)
#define KB_IS_CNTRL(lp)		((lp)->status & KB_STATUS_CNTRL_ANY)
#define KB_IS_CAPSLOCK(lp)	((lp)->status & KB_STATUS_CAPSLOCK)
#define KB_IS_HOLD(lp)		((lp)->status & KB_STATUS_HOLD)
#define KB_IS_NUMLOCK(lp)	((lp)->status & KB_STATUS_NUMLOCK)
#define KB_IS_INRESET(lp) 	((lp)->status & KB_STATUS_INRESET)
#define KB_IS_UPDNMODE(lp)	((lp)->status & KB_STATUS_UPDNMODE)
#define KB_IS_REPEATING(lp)	((lp)->status & KB_STATUS_REPEATING)
#define KB_IS_PREFIX(lp)	((lp)->status & KB_STATUS_PREFIX)

/* Tadpole keyboard */
#define KB_IS_PREFIX1(lp)	((lp)->status & KB_STATUS_PREFIX1)
#define KB_IS_PREFIX2(lp)	((lp)->status & KB_STATUS_PREFIX2)

#define KB_IS_ALT(lp)		((lp)->status & KB_STATUS_ALT_ANY)
#define KB_IS_ALT_L(lp)		((lp)->status & KB_STATUS_ALT_L)
#define KB_IS_ALT_R(lp)		((lp)->status & KB_STATUS_ALT_R)
#define KB_IS_WAIT(lp)		((lp)->status & KB_STATUS_WAIT)
#define KB_IS_COMPOSE(lp)	((lp)->status & KB_STATUS_COMPOSE_ANY)

/* macros for setting status */
#define KB_SET_SHIFT(lp)	((lp)->status |= KB_STATUS_SHIFT)
#define KB_SET_SHIFT_L(lp)	((lp)->status |= KB_STATUS_SHIFT_L)
#define KB_SET_SHIFT_R(lp)	((lp)->status |= KB_STATUS_SHIFT_R)
#define KB_SET_CNTRL(lp)	((lp)->status |= KB_STATUS_CNTRL)
#define KB_SET_CNTRL_L(lp)	((lp)->status |= KB_STATUS_CNTRL_L)
#define KB_SET_CNTRL_R(lp)	((lp)->status |= KB_STATUS_CNTRL_R)
#define KB_SET_CAPSLOCK(lp)	((lp)->status |= KB_STATUS_CAPSLOCK)
#define KB_SET_HOLD(lp)		((lp)->status |= KB_STATUS_HOLD)
#define KB_SET_NUMLOCK(lp)	((lp)->status |= KB_STATUS_NUMLOCK)
#define KB_SET_INRESET(lp) 	((lp)->status |= KB_STATUS_INRESET)
#define KB_SET_UPDNMODE(lp)	((lp)->status |= KB_STATUS_UPDNMODE)
#define KB_SET_REPEATING(lp)	((lp)->status |= KB_STATUS_REPEATING)
#define KB_SET_PREFIX(lp)	((lp)->status |= KB_STATUS_PREFIX)

/* Tadpole keyboard */
#define KB_SET_PREFIX1(lp)	((lp)->status |= KB_STATUS_PREFIX1)
#define KB_SET_PREFIX2(lp)	((lp)->status |= KB_STATUS_PREFIX2)

#define KB_SET_ALT(lp)		((lp)->status |= KB_STATUS_ALT)
#define KB_SET_ALT_L(lp)	((lp)->status |= KB_STATUS_ALT_L)
#define KB_SET_ALT_R(lp)	((lp)->status |= KB_STATUS_ALT_R)
#define KB_SET_WAIT(lp)		((lp)->status |= KB_STATUS_WAIT)
#define KB_SET_COMPOSE(lp)	((lp)->status |= KB_STATUS_COMPOSE)
#define KB_SET_COMPOSE_L(lp)	((lp)->status |= KB_STATUS_COMPOSE_L)
#define KB_SET_COMPOSE_R(lp)	((lp)->status |= KB_STATUS_COMPOSE_R)

/* macros for clearing status */
/* NOTE: these clear all related keys; ie SHIFT does both left and right */
#define KB_CLR_SHIFT(lp)	((lp)->status &= ~KB_STATUS_SHIFT_ANY)
#define KB_CLR_SHIFT_L(lp)	((lp)->status &= ~KB_STATUS_SHIFT_L)
#define KB_CLR_SHIFT_R(lp)	((lp)->status &= ~KB_STATUS_SHIFT_R)
#define KB_CLR_CNTRL(lp)	((lp)->status &= ~KB_STATUS_CNTRL_ANY)
#define KB_CLR_CNTRL_L(lp)	((lp)->status &= ~KB_STATUS_CNTRL_L)
#define KB_CLR_CNTRL_R(lp)	((lp)->status &= ~KB_STATUS_CNTRL_R)
#define KB_CLR_CAPSLOCK(lp)	((lp)->status &= ~KB_STATUS_CAPSLOCK)
#define KB_CLR_HOLD(lp)		((lp)->status &= ~KB_STATUS_HOLD)
#define KB_CLR_NUMLOCK(lp)	((lp)->status &= ~KB_STATUS_NUMLOCK)
#define KB_CLR_INRESET(lp) 	((lp)->status &= ~KB_STATUS_INRESET)
#define KB_CLR_UPDNMODE(lp)	((lp)->status &= ~KB_STATUS_UPDNMODE)
#define KB_CLR_REPEATING(lp)	((lp)->status &= ~KB_STATUS_REPEATING)
#define KB_CLR_PREFIX(lp)	((lp)->status &= ~KB_STATUS_PREFIX)

/* Tadpole keyboard */
#define KB_CLR_PREFIX1(lp)	((lp)->status &= ~KB_STATUS_PREFIX1)
#define KB_CLR_PREFIX2(lp)	((lp)->status &= ~KB_STATUS_PREFIX2)

#define KB_CLR_ALT(lp)		((lp)->status &= ~KB_STATUS_ALT_ANY)
#define KB_CLR_ALT_L(lp)	((lp)->status &= ~KB_STATUS_ALT_L)
#define KB_CLR_ALT_R(lp)	((lp)->status &= ~KB_STATUS_ALT_R)
#define KB_CLR_WAIT(lp)		((lp)->status &= ~KB_STATUS_WAIT)
#define KB_CLR_COMPOSE(lp)	((lp)->status &= ~KB_STATUS_COMPOSE_ANY)
#define KB_CLR_COMPOSE_L(lp)	((lp)->status &= ~KB_STATUS_COMPOSE_L)
#define KB_CLR_COMPOSE_R(lp)	((lp)->status &= ~KB_STATUS_COMPOSE_R)

/* macros for toggling status */
#define KB_TGL_SHIFT(lp)	((lp)->status ^= KB_STATUS_SHIFT)
#define KB_TGL_SHIFT_L(lp)	((lp)->status ^= KB_STATUS_SHIFT_L)
#define KB_TGL_SHIFT_R(lp)	((lp)->status ^= KB_STATUS_SHIFT_R)
#define KB_TGL_CNTRL(lp)	((lp)->status ^= KB_STATUS_CNTRL)
#define KB_TGL_CNTRL_L(lp)	((lp)->status ^= KB_STATUS_CNTRL_L)
#define KB_TGL_CNTRL_R(lp)	((lp)->status ^= KB_STATUS_CNTRL_R)
#define KB_TGL_CAPSLOCK(lp)	((lp)->status ^= KB_STATUS_CAPSLOCK)
#define KB_TGL_HOLD(lp)		((lp)->status ^= KB_STATUS_HOLD)
#define KB_TGL_NUMLOCK(lp)	((lp)->status ^= KB_STATUS_NUMLOCK)
#define KB_TGL_INRESET(lp) 	((lp)->status ^= KB_STATUS_INRESET)
#define KB_TGL_UPDNMODE(lp)	((lp)->status ^= KB_STATUS_UPDNMODE)
#define KB_TGL_REPEATING(lp)	((lp)->status ^= KB_STATUS_REPEATING)
#define KB_TGL_PREFIX(lp)	((lp)->status ^= KB_STATUS_PREFIX)
#define KB_TGL_ALT(lp)		((lp)->status ^= KB_STATUS_ALT)
#define KB_TGL_ALT_L(lp)	((lp)->status ^= KB_STATUS_ALT_L)
#define KB_TGL_ALT_R(lp)	((lp)->status ^= KB_STATUS_ALT_R)
#define KB_TGL_WAIT(lp)		((lp)->status ^= KB_STATUS_WAIT)
#define KB_TGL_COMPOSE(lp)	((lp)->status ^= KB_STATUS_COMPOSE)
#define KB_TGL_COMPOSE_L(lp)	((lp)->status ^= KB_STATUS_COMPOSE_L)
#define KB_TGL_COMPOSE_R(lp)	((lp)->status ^= KB_STATUS_COMPOSE_R)


/* define for default cursor and its data */
#define DEFAULT_CURSOR	0,16,16,0,0,cdata,cdata
extern unsigned int	cdata[];


#define TOP_EDGE	0x1
#define BOTTOM_EDGE	0x2
#define LEFT_EDGE	0x4
#define RIGHT_EDGE	0x8

#define TOY ((time.tv_sec * 1000) + (time.tv_usec / 1000))

/*
 * constants for identifying "special_keys" in kernel keymaps
 */
#define SPEC_MASK	0x100
#define NPAD_MASK	0x200

/*
 * constants for managing foreign languages
 */
#define MAX_LANGS	18
#define MIN_LANG_CODE	0x30
#define MAX_LANG_CODE	0x52

/*
 * modifier key encoding contants for kernel keymaps
*/
#define MOD_MASK	(0x80)
#define MOD_MIN		(0x80)
#define MOD_MAX		(0x9f)

#define MOD_ALT_L	(MOD_MASK | 0x00)
#define MOD_ALT_R	(MOD_MASK | 0x01)
#define MOD_CTRL_L	(MOD_MASK | 0x02)
#define MOD_CTRL_R	(MOD_MASK | 0x03)
#define MOD_SHFT_L	(MOD_MASK | 0x04)
#define MOD_SHFT_R	(MOD_MASK | 0x05)
#define MOD_COMP_L	(MOD_MASK | 0x06)
#define MOD_COMP_R	(MOD_MASK | 0x07)
#define MOD_CAPS	(MOD_MASK | 0x08)
#define MOD_NUML	(MOD_MASK | 0x09)
#define MOD_SCROLL	(MOD_MASK | 0x0a)
/* NOTE: must *NOT* exceed 0x1f, since ISO LATIN-1 printables start at 0xa0 */

/* Some Key Defs */
/* Function keys */

/*
   NOTE: use SPEC_MASK in the keymap tables
   to indicate special scancodes like function
   keys, editing keys, numeric keypad keys.
   Also, try to keep the same special key indices
   for all the keyboard types, when
   possible. This means there are some holes
   in the indices defined below...

   The indices refer to entries in the
   "special_keys" table in data/ws_data.c.

   Original entries are in the range 0x01-0x2d
   Start new entries at offset 0x30
*/

#define MAKE_CNTRL(x) ((x) & 0x1f)

#define	F1		(SPEC_MASK|0x01)
#define	F2		(SPEC_MASK|0x02)
#define	F3		(SPEC_MASK|0x03)
#define	F4		(SPEC_MASK|0x04)
#define	F5		(SPEC_MASK|0x05)
#define	F6		(SPEC_MASK|0x06)
#define	F7		(SPEC_MASK|0x07)
#define	F8		(SPEC_MASK|0x08)
#define	F9		(SPEC_MASK|0x09)
#define	F10		(SPEC_MASK|0x0a)

#define LK_F11		(0x1b)			/* Escape like LK401 */
#define LK_F12		(0x08)			/* BackSpace like LK401 */
#define LK_F13		(0x0a)			/* LineFeed like LK401 */

#define F14		(SPEC_MASK|0x0b)
#define HELP		(SPEC_MASK|0x0c)
#define DO		(SPEC_MASK|0x0d)
#define F17		(SPEC_MASK|0x0e)
#define F18		(SPEC_MASK|0x0f)
#define F19		(SPEC_MASK|0x10)
#define F20		(SPEC_MASK|0x11)

#define FIND		(SPEC_MASK|0x12)

#define	INS		(SPEC_MASK|0x13)	/* insert */
#define	REMOVE		(SPEC_MASK|0x14)	/* remove */
#define	END		(SPEC_MASK|0x15)	/* select */
#define	PGUP		(SPEC_MASK|0x16)	/* prev */
#define	PGDWN		(SPEC_MASK|0x17)	/* next */

#define	SELECT		(SPEC_MASK|0x15)	/* LK */
#define	PREV		(SPEC_MASK|0x16)	/* LK */
#define	NEXT		(SPEC_MASK|0x17)	/* LK */

#define KP_PF1		(SPEC_MASK|0x18)	/* PF1 */
#define KP_PF2		(SPEC_MASK|0x19)	/* PF2 */
#define KP_PF3		(SPEC_MASK|0x1a)	/* PF3 */
#define KP_PF4		(SPEC_MASK|0x1b)	/* PF4 */

#define	LEFT		(SPEC_MASK|0x1c)
#define	RIGHT		(SPEC_MASK|0x1d)
#define	DOWN		(SPEC_MASK|0x1e)
#define	UP		(SPEC_MASK|0x1f)

#define KP_0		(SPEC_MASK|0x20)
#define KP_PERIOD	(SPEC_MASK|0x21)
#define KP_ENTER	(SPEC_MASK|0x22)
#define KP_1		(SPEC_MASK|0x23)
#define KP_2		(SPEC_MASK|0x24)
#define KP_3		(SPEC_MASK|0x25)
#define KP_4		(SPEC_MASK|0x26)
#define KP_5		(SPEC_MASK|0x27)
#define KP_6		(SPEC_MASK|0x28)
#define KP_COMMA	(SPEC_MASK|0x29)
#define KP_7		(SPEC_MASK|0x2a)
#define KP_8		(SPEC_MASK|0x2b)
#define KP_9		(SPEC_MASK|0x2c)
#define KP_MINUS	(SPEC_MASK|0x2d)

#define	DELE		(0x7f)			/* not special */

/* New Keys for PCXAL */
#define	F11		(SPEC_MASK|0x30)	
#define	F12		(SPEC_MASK|0x31)

#define	HOME		(SPEC_MASK|0x32)
#define	MIDDLE		(SPEC_MASK|0x33)

/* Others */
#define	PRTSC		(SPEC_MASK|0x34)
#define	PAUSE		(SPEC_MASK|0x35)

/* numeric keypad keys */
#define HOME_NPAD	(NPAD_MASK|HOME)
#define UP_NPAD		(NPAD_MASK|UP)
#define PGUP_NPAD	(NPAD_MASK|PGUP)
#define LEFT_NPAD	(NPAD_MASK|LEFT)
#define MIDDLE_NPAD	(NPAD_MASK|MIDDLE)
#define RIGHT_NPAD	(NPAD_MASK|RIGHT)
#define END_NPAD	(NPAD_MASK|END)
#define DOWN_NPAD	(NPAD_MASK|DOWN)
#define PGDWN_NPAD	(NPAD_MASK|PGDWN)
#define INS_NPAD	(NPAD_MASK|INS)
#define DELE_NPAD	(NPAD_MASK|DELE)

/*
 * data types for keymap and diffs/altgrs tables, and compose sequences
 */
typedef struct {
        short	unshifted;
        short	shifted;
} xlate_t;

typedef struct {
        short	keycode;
        short	unshifted;
        short	shifted;
} xkey_t;

typedef struct {
	char char1, char2;
	short result;
} xcomp_t;


#endif /* _WSDEVICE_H_ */
