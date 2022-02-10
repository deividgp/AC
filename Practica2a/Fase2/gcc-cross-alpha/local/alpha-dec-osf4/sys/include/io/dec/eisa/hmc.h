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
 * @(#)$RCSfile: hmc.h,v $ $Revision: 1.1.10.2 $ (DEC) $Date: 1997/01/24 18:50:18 $
 */


#ifndef __HMC_H__
#define __HMC_H__


/* do not turn on debugging */

/* #define DEBUG */

/* define special debugging stuff */

#ifdef DEBUG
#define DEBUG_BUMP(x)   (x++);
#define Dprintf         printf
#define XDprintf	if (alphabook1_debug_print_mask == -1) printf
#define DBG(bit)	if (alphabook1_debug_print_mask & bit)
#else
#define DEBUG_BUMP(x)
#define Dprintf
#define XDprintf
#define DBG(bit)	if (0)
#endif

/* end of debugging definitions */

/* used to control printing based on "print level" */
#define PLVL(n)   if (alphabook1_print_level >= n)

/*
 * Register address and offsets
 */
#define H8_BASE_ADDR                   0x170            /* default, if no ISACFG data supplied */
#define H8_STATUS_REG_OFF              0x4              
#define H8_CMD_REG_OFF                 0x4
#define H8_DATA_REG_OFF                0x0

/*
 * I/O Macros for register reads and writes.
 */
#define H8_READ(a)              read_io_port((a), 1, 0)
#define H8_WRITE(a, d)          write_io_port((a), 1, 0, (d)); mb()

#define H8_GET_STATUS   H8_READ((sc->base) + H8_STATUS_REG_OFF)
#define H8_READ_DATA    H8_READ((sc->base) + H8_DATA_REG_OFF)
#define WRITE_DATA(d)   H8_WRITE((sc->base) + H8_DATA_REG_OFF, d)
#define WRITE_CMD(d)    H8_WRITE((sc->base) + H8_CMD_REG_OFF, d)

/* H8 register bit definitions */
/* status register */
#define H8_OFULL                       0x01              /* output data register full */
#define H8_IFULL                       0x02              /* input data register full */
#define H8_CMD                         0x08              /* command / not data */

#define H8_INTR                        0xfa
#define H8_NACK                        0xfc
#define H8_BYTE_LEVEL_ACK              0xfd
#define H8_CMD_ACK                     0xfe
#define H8_SYNC_BYTE                   0xff

/* 
 * H8 commands -- in tabular format

Code Symbolic Name                 Verbal Description from H8 spec
---- ---------------------         -------------------------------
0x00 H8_SYNC                       Synchronize
0x01 H8_RD_SN                      Read Serial Number
0x02 H8_RD_ENET_ADDR               Read Ethernet Address
0x03 H8_RD_HW_VER                  Read Hardware Version
0x04 H8_RD_MIC_VER                 Read Microcontroller Version
0x05 H8_RD_MAX_TEMP                Read Maximum Temperature
0x06 H8_RD_MIN_TEMP                Read Minimum Temperature
0x07 H8_RD_CURR_TEMP               Read Current Temperature
0x08 H8_RD_SYS_VARIANT             Read System Variant
0x09 H8_RD_PWR_ON_CYCLES           Read Power-on Cycles
0x0a H8_RD_PWR_ON_SECS             Read Power-on Seconds
0x0b H8_RD_RESET_STATUS            Read Reset Status
0x0c H8_RD_PWR_DN_STATUS           Read Power-down Status
0x0d H8_RD_EVENT_STATUS            Read Event Status
0x0e H8_RD_ROM_CKSM                Read Microcontroller ROM Checksum
0x0f H8_RD_EXT_STATUS              Read External Status
0x10 H8_RD_USER_CFG                Read User Configuration Area
0x11 H8_RD_INT_BATT_VOLT           Read Internal Battery Voltage
0x12 H8_RD_DC_INPUT_VOLT           Read DC Input Voltage
0x13 H8_RD_HORIZ_PTR_VOLT          Read Horizontal Pointer Voltage
0x14 H8_RD_VERT_PTR_VOLT           Read Vertical Pointer Voltage
0x15 H8_RD_EEPROM_STATUS           Read EEPROM Status
0x16 H8_RD_ERR_STATUS              Read Error Status
0x17 H8_RD_NEW_BUSY_SPEED          Read New Busy Speed
0x18 H8_RD_CONFIG_INTERFACE        Read Configuration Interface
0x19 H8_RD_INT_BATT_STATUS         Read Internal Battery Status
0x1a H8_RD_EXT_BATT_STATUS         Read External Battery Status
0x1b H8_RD_PWR_UP_STATUS           Read Power-Up Status
0x1c                               Undefined
0x1d                               Undefined
0x1e                               Undefined
0x1f                               Undefined
0x20                               Undefined
0x21 H8_DEVICE_CONTROL             Device Control
0x22 H8_CTL_TFT_BRT_DC             Control TFT Screen Brightness (DC)
0x23 H8_CTL_WATCHDOG               Control Watchdog Timer
0x24 H8_CTL_MIC_PROT               Control Microcontroller Protection Setting
0x25 H8_CTL_INT_BATT_CHG           Control Internal Battery Charge Rate
0x26 H8_CTL_EXT_BATT_CHG           Control External Battery Charge Rate
0x27 H8_CTL_MARK_SPACE             Control Mark/Space Ratio
0x28 H8_CTL_MOUSE_SENSITIVITY      Control Mouse Sensitivity
0x29 H8_CTL_DIAG_MODE              Control Diagnostic Mode
0x2a H8_CTL_IDLE_AND_BUSY_SPDS     Control Idle and Busy Speeds
0x2b H8_CTL_TFT_BRT_BATT           Control TFT Screen Brightness (Battery)
0x2c H8_CTL_UPPER_TEMP             Control Upper Thermal Threshold
0x2d H8_CTL_LOWER_TEMP             Control Lower Thermal Threshold
0x2e H8_CTL_TEMP_CUTOUT            Control Thermal Cutout
0x2f H8_CTL_WAKEUP                 Control Wakeup Conditions
0x30 H8_CTL_CHG_THRESHOLD          Control Charge Threshold
0x31 H8_CTL_TURBO_MODE             Control Turbo Mode Voltage
0x32 H8_CTL_EMU_BITPORT            Control EMU Bitport
0x33                               Undefined
0x34                               Undefined
0x35                               Undefined
0x36                               Undefined
0x37                               Undefined
0x38                               Undefined
0x39                               Undefined
0x3a                               Undefined
0x3b                               Undefined
0x3c                               Undefined
0x3d                               Undefined
0x3e                               Undefined
0x3f                               Undefined
0x40 H8_SET_DIAG_STATUS            Set Diagnostic Status
0x41 H8_SOFTWARE_RESET             Perform Software Reset
0x42 H8_RECAL_PTR                  Recalibrate Pointing Stick
0x43 H8_SET_INT_BATT_PERCENT       Set Internal Battery Percentage
0x44                               Undefined
0x45 H8_WRT_CFG_INTERFACE_REG      Write Configuration Interface Register
0x46 H8_ENTER_POST_MODE            Enter POST Mode
0x47 H8_EXIT_POST_MODE             Exit POST Mode
0x48                               Undefined
0x49                               Undefined
0x4a                               Undefined
0x4b                               Undefined
0x4c                               Undefined
0x4d                               Undefined
0x4e                               Undefined
0x4f                               Undefined
0x50 H8_RD_EEPROM                  Read EEPROM
0x51 H8_WRT_EEPROM                 Write EEPROM
0x52 H8_WRT_TO_STATUS_DISP         Write to Status Display
0x53 H8_DEFINE_SPC_CHAR            Define Special Character
0x54                               Undefined
0x55                               Undefined
0x56 H8_RD_EVENT_STATUS_MASK       Read Event Status Mask
0x57 H8_WRT_EVENT_STATUS_MASK      Write Event Status Mask
0x58                               Undefined
0x59                               Undefined
0x5a                               Undefined
0x5b                               Undefined
0x5c                               Undefined
0x5d                               Undefined
0x5e                               Undefined
0x5f                               Undefined
0x60 H8_DEFINE_TABLE_STRING_ENTRY  Define String Table Entry
0x61                               Undefined
0x62                               Undefined
0x63                               Undefined
0x64                               Undefined
0x65                               Undefined
0x66                               Undefined
0x67                               Undefined
0x68                               Undefined
0x69                               Undefined
0x6a                               Undefined
0x6b                               Undefined
0x6c                               Undefined
0x6d                               Undefined
0x6e                               Undefined
0x6f                               Undefined
0x70 H8_PERFORM_EMU_CMD            Perform EMU Command
0x71 H8_EMU_RD_REG                 EMU Read Register
0x72 H8_EMU_WRT_REG                EMU Write Register
0x73 H8_EMU_RD_RAM                 EMU Read RAM
0x74 H8_EMU_WRT_RAM                EMU Write RAM
0x75 H8_BQ_RD_REG                  BQ Read Register
0x76 H8_BQ_WRT_REG                 BQ Write Register
0x77                               Undefined
0x78                               Undefined
0x79                               Undefined
0x7a                               Undefined
0x7b                               Undefined
0x7c                               Undefined
0x7d                               Undefined
0x7e                               Undefined
0x7f                               Undefined
0x80 H8_PWR_OFF                    Power Off

*/

#define H8_MAX_COMMAND_CODE	0x80

/*
 * H8 command definitions
 */
/* System info commands */
#define H8_SYNC                         0x00
#define H8_RD_SN                        0x01
#define H8_RD_ENET_ADDR                 0x02
#define H8_RD_HW_VER                    0x03
#define H8_RD_MIC_VER                   0x04
#define H8_RD_MAX_TEMP                  0x05
#define H8_RD_MIN_TEMP                  0x06
#define H8_RD_CURR_TEMP                 0x07
#define H8_RD_SYS_VARIANT               0x08
#define H8_RD_PWR_ON_CYCLES             0x09
#define H8_RD_PWR_ON_SECS               0x0a
#define H8_RD_RESET_STATUS              0x0b
#define H8_RD_PWR_DN_STATUS             0x0c
#define H8_RD_EVENT_STATUS              0x0d
#define H8_RD_ROM_CKSM                  0x0e
#define H8_RD_EXT_STATUS                0x0f
#define H8_RD_USER_CFG                  0x10
#define H8_RD_INT_BATT_VOLT             0x11
#define H8_RD_DC_INPUT_VOLT             0x12
#define H8_RD_HORIZ_PTR_VOLT            0x13
#define H8_RD_VERT_PTR_VOLT             0x14
#define H8_RD_EEPROM_STATUS             0x15
#define H8_RD_ERR_STATUS                0x16
#define H8_RD_NEW_BUSY_SPEED            0x17
#define H8_RD_CONFIG_INTERFACE          0x18
#define H8_RD_INT_BATT_STATUS           0x19
#define H8_RD_EXT_BATT_STATUS           0x1a
#define H8_RD_PWR_UP_STATUS             0x1b
#define H8_RD_EVENT_STATUS_MASK         0x56

/* Read/write/modify commands */
#define H8_CTL_EMU_BITPORT              0x32
#define H8_DEVICE_CONTROL               0x21
#define H8_CTL_TFT_BRT_DC               0x22
#define H8_CTL_WATCHDOG                 0x23
#define H8_CTL_MIC_PROT                 0x24
#define H8_CTL_INT_BATT_CHG             0x25
#define H8_CTL_EXT_BATT_CHG             0x26
#define H8_CTL_MARK_SPACE               0x27
#define H8_CTL_MOUSE_SENSITIVITY        0x28
#define H8_CTL_DIAG_MODE                0x29
#define H8_CTL_IDLE_AND_BUSY_SPDS       0x2a
#define H8_CTL_TFT_BRT_BATT             0x2b
#define H8_CTL_UPPER_TEMP               0x2c
#define H8_CTL_LOWER_TEMP               0x2d
#define H8_CTL_TEMP_CUTOUT              0x2e
#define H8_CTL_WAKEUP                   0x2f
#define H8_CTL_CHG_THRESHOLD            0x30
#define H8_CTL_TURBO_MODE               0x31
#define H8_SET_DIAG_STATUS              0x40
#define H8_SOFTWARE_RESET               0x41
#define H8_RECAL_PTR                    0x42
#define H8_SET_INT_BATT_PERCENT         0x43
#define H8_WRT_CFG_INTERFACE_REG        0x45
#define H8_WRT_EVENT_STATUS_MASK        0x57
#define H8_ENTER_POST_MODE              0x46
#define H8_EXIT_POST_MODE               0x47

/* Block transfer commands */
#define H8_RD_EEPROM                    0x50
#define H8_WRT_EEPROM                   0x51
#define H8_WRT_TO_STATUS_DISP           0x52
#define H8_DEFINE_SPC_CHAR              0x53
 
/* Generic commands */
#define H8_DEFINE_TABLE_STRING_ENTRY    0x60

/* Battery control commands */
#define H8_PERFORM_EMU_CMD              0x70
#define H8_EMU_RD_REG                   0x71
#define H8_EMU_WRT_REG                  0x72
#define H8_EMU_RD_RAM                   0x73
#define H8_EMU_WRT_RAM                  0x74
#define H8_BQ_RD_REG                    0x75
#define H8_BQ_WRT_REG                   0x76

/* System admin commands */
#define H8_PWR_OFF                      0x80

/*
 * H8 command related definitions
 */

/* device control argument bits */
#define H8_ENAB_EXTSMI                  0x01
#define H8_DISAB_IRQ                    0x02
#define H8_ENAB_FLASH_WRT               0x04
#define H8_ENAB_THERM                   0x08
#define H8_ENAB_INT_PTR                 0x10
#define H8_ENAB_LOW_SPD_IND             0x20
#define H8_ENAB_EXT_PTR                 0x40
#define H8_DISAB_PWR_OFF_SW             0x80

/* H8 read event status bits */
#define H8_DC_CHANGE                    0x0001
#define H8_INT_BATT_LOW                 0x0002
#define H8_INT_BATT_CHARGE_THRESHOLD    0x0004
#define H8_INT_BATT_CHARGE_STATE        0x0008
#define H8_INT_BATT_STATUS              0x0010
#define H8_EXT_BATT_CHARGE_STATE        0x0020
#define H8_EXT_BATT_LOW                 0x0040
#define H8_EXT_BATT_STATUS              0x0080
#define H8_THERMAL_THRESHOLD            0x0100
#define H8_WATCHDOG                     0x0200
#define H8_DOCKING_STATION_STATUS       0x0400
#define H8_EXT_MOUSE_OR_CASE_SWITCH     0x0800
#define H8_KEYBOARD                     0x1000
#define H8_BATT_CHANGE_OVER             0x2000
#define H8_POWER_BUTTON                 0x4000
#define H8_SHUTDOWN                     0x8000

#define H8_INT_BATT_EVENT (H8_INT_BATT_LOW|H8_INT_BATT_CHARGE_THRESHOLD|H8_INT_BATT_STATUS|H8_INT_BATT_CHARGE_STATE|H8_BATT_CHANGE_OVER)
#define H8_EXT_BATT_EVENT (H8_EXT_BATT_LOW|H8_EXT_BATT_CHARGE_STATE|H8_EXT_BATT_STATUS|H8_BATT_CHANGE_OVER)

/* H8 read external status bits */
#define H8_DC_AVAILABLE			0x0001
#define H8_INT_BATT_ATTACHED		0x0002
#define H8_EXT_BATT_ATTACHED		0x0004
#define H8_DOCKING_STATION_ATTACHED	0x0008
/* reserved				0x0010 */
#define H8_EXTERNAL_MOUSE_ATTACHED	0x0020
#define H8_MICROSWITCH_CLOSED_LID_DOWN	0x0040
#define H8_INT_BATT_IS_CHARGING		0x0080
#define H8_EXT_BATT_IS_CHARGING		0x0100
#define H8_INT_BATT_DISCHARGING		0x0200
#define H8_EXT_BATT_DISCHARGING		0x0400

/* H8 control idle and busy speeds */
#define H8_SPEED_LOW                    0x01
#define H8_SPEED_MED                    0x02
#define H8_SPEED_HI                     0x03
#define H8_SPEED_LOCKED                 0x80

#define MAX_H8_CMD_SIZE                 16	/* use a multiple of 4 */      
#define H8_Q_ALLOC_AMOUNT               32	/* for secondary allocations */

/* H8 state machine state codes */
#define H8_INIT                         0	/* initializing */
#define H8_IDLE                         1	/* ready to send a command */
#define H8_XMIT                         2	/* transmitting command & data */
#define H8_RCV                          3	/* receiving command output */
#define H8_SHUT				4	/* shutting down/powering off */

/* Mask values for control functions */
#define DEFAULT_THERMAL_WINDOW      	5	/* lower is upper - window */
#define DEFAULT_UTHERMAL_THRESHOLD  	115	/* normal operating mode */
#define MAXIMUM_UTHERMAL_THRESHOLD	130	/* turbo or user set max */

/* cpu speeds and clock divisor values */
#define MHZ_14		5
#define MHZ_28          4
#define MHZ_57          3
#define MHZ_115         2
#define MHZ_155		1
#define MHZ_230         0 

/* codes used in H8 command print routine */
#define H8_CMD_START	0
#define H8_CMD_DEFER	1
#define H8_CMD_FINIS	2
#define H8_CMD_REQUE	3
#define H8_CMD_ABORT	4

/*
 * H8 data (actually unused for performance reasons)
 */
struct h8_data {
        u_int           ser_num;
        u_char          ether_add[6];
        u_short         hw_ver;
        u_short         mic_ver;
        u_short         max_tmp;
        u_short         min_tmp;
        u_short         cur_tmp;
        u_int           sys_var;
        u_int           pow_on;
        u_int           pow_on_secs;
        u_char          reset_status;
        u_char          pwr_dn_status;
        u_short         event_status;
        u_short         rom_cksm;
        u_short         ext_status;
        u_short         u_cfg;
        u_char          ibatt_volt;
        u_char          dc_volt;
        u_char          ptr_horiz;
        u_char          ptr_vert;
        u_char          eeprom_status;
        u_char          error_status;
        u_char          new_busy_speed;
        u_char          cfg_interface;
        u_short         int_batt_status;
        u_short         ext_batt_status;
        u_char          pow_up_status;
        u_char          event_status_mask;
};

/*
 * H8 soft controller structure
 */
typedef struct h8_softc {
        u_long                  base;           /* Base address of unit registers */
        struct controller       *ctlr;          /* Address of controller struct   */
        ihandler_id_t           *hid;           /* handler_id */
        int                     state;          /* state of the h8 */
        int                     index;          /* index in active command */
        queue_chain_t           actq;           /* double linked list */
        queue_chain_t           cmdq;           /* double linked list */
        queue_chain_t           freeq;          /* double linked list */
        pwrmgr_devinfo_t        *dvinfo;        /* power manager devinfo ptr */
} h8_softc_t;

/*
 * H8 command buffers
 */
typedef struct h8_cmd_q {
        queue_chain_t   link;           /* double linked list */
        int             ncmd;           /* number of bytes in command */
        int             nrsp;           /* number of bytes in response */
        int             cnt;            /* number of bytes sent/received */
        int             acks;           /* number of byte level acks */
        int             nacks;          /* number of time command was NACKed */
        u_char          cmdbuf[MAX_H8_CMD_SIZE];        /* buffer to store command */
        u_char          rcvbuf[MAX_H8_CMD_SIZE];        /* buffer to store response */
} h8_cmd_q_t;

#define H8_MAX_NACKS 3	/* 3 strikes and you're out */

union   intr_buf {
        u_char  byte[2];
        u_int   word;
};

union   h8_quad_byte {
	u_char	byte[4];
	u_int	word;
};

#endif /* __HMC_H_ */
