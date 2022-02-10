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
#pragma ident "@(#)$RCSfile: cam_data.c,v $ $Revision: 1.1.120.3 $ (DEC) $Date: 1998/12/03 23:45:48 $"

/* ---------------------------------------------------------------------- */

/* cam_data.c			Version 1.25		Dec. 11, 1991 */

/* The CAM data file.  This file contains the system setable parameters and
static data arrays needed for the CAM subsystem.

Modification History

	Version	  Date		Who	Reason

	1.00	03/27/91	jag	Creation date, from xpt_data.c. 
	1.01	04/10/91	dallas	Added device descriptor tables
					and supporting structures
					Incrmented the CCB pool size defines.
	1.02	06/03/91	jag	Fixed the N_cam_conftbl calc.
	1.03	06/07/91	maria	Changed alll NCAM references to
					NASC.
					Added DTYPE_SHIFT in device
					descriptor table entries.
					Added the default_scsiid
					declaration.
	1.04	06/19/91	dallas  Added max record size to the dev desc.
					This gives the user/operator the
					ability to match the device.
					Fixed TZK10 density table to write
					1 file mark on close.
					Fixed comment line for tz07
					Added descriptions on how to add
					a device.
	1.05	07/03/91	rps	Added sii defines.

	1.06	07/09/91	janet	Fixed "sim.h" include to be "sii.h"

	1.07	07/17/91	maria	Added SZ_NO_DISC, SZ_TRY_SYNC bits
					and removed SCSI2 for device descriptor
					flags.

	1.08	07/31/91	dallas	Fixed density tables to correspond
					to old major/minor pairs.. For
					compat until OSF.

	1.09	08/02/91	rln	Added () to NCAM

	1.10	08/21/91	dallas	Added TZ85 and TLZ04 to the
					device tables.
					
	1.11	09/03/91	maria	Added unknown device descriptor
					entries for all types of devices.
					
	1.12	09/11/91	maria	Changed SZ_TRY_SYNC flag to
					SZ_NOSYNC in device descrptor
					table entries.  Synchronous
					will not be attempted on: RRD40,
					RRD42, RZ23, TK50, TZ30, TZ05.
					Added entry RWZ01.

	1.13	09/12/91	jag	Added the CDrv EDT scan INQUIRY
					retry count.

	1.14	09/13/91	dallas	Added compression for tlz06.

	1.15	09/16/91	maria	Added RWZ01 partition table.

	1.16	09/19/91	maria	Removed the prevent/allow media
					removal optional command for RRD40.

	1.17	10/24/91	maria 	Updated the RZ58 queue size to
					its full size of 32 and disabled
					tagged queueing for RZ58 (SZ_NO_TAGS).
	1.18	11/19/91	dallas  Added densities for tapes and new
					updated rz58 partition sizes..
					Fixed unknown tape entry to reflect
					default density. Added error log
					limits for device drivers..
	1.19	11/20/91	janet	Merged in sim_data.c and xpt_data.c
	1.20	11/20/91	dallas  Deleted the use of the tzk08_dens
					table for the exabyte. It seems 
					that the device does not like 
					anything other then 0's for the
					density setting..
	1.21	11/22/91	dallas  Added the sending of the vendor
					unique data on open for the TKZ08.
					This disables odd byte disconnects for
					the TKZ08 which fixes the 3min problem.
	1.22	12/04/91	dallas	Changed the tzk10_dens table for 
					TZK10's. The unit will reject the 
					QIC-24 density setting.. Now we 
					will send a default setting.
	1.23	12/09/91	maria	Added SZ_NO_TAG for UNKNOWN disk
					device descriptor entry to turn
					off tagged queueing.
	1.24	12/11/91	maria	Added common buf struture pool
	1.25	12/11/91	jag	Added the global EDT scanning wait
					variable for the CDrv.
					size variables.

	NOTES:

*/

/* ---------------------------------------------------------------------- */

#include <io/common/iotypes.h>
#include <sys/types.h>			/* system level types */
#include <sys/time.h>			/* system level time defs */
#include <sys/param.h>			/* system level parameter defs */

#include <io/cam/dec_cam.h>		/* DEC CAM include file */
#include <mach/vm_param.h>
#include <io/cam/cam_debug.h>		/* debug structures for the CAM code */

#include <io/cam/cam.h>			/* General CAM include file */
#include <io/common/devio.h>
#include <io/cam/scsi_all.h>		/* SCSI 2 defines (structs) */
#include <io/cam/scsi_direct.h>		/* SCSI 2 defines (structs) */
#include <io/cam/scsi_sequential.h>	/* SCSI 2 defines (structs) */
#include <io/common/kds.h>		/* Kernel database structures */
#include <io/cam/camdb.h>		/* Cam database structures */
#include <io/cam/pdrv.h>		/* General PDrv include file */
#include <io/cam/cam_tape.h>
#include <io/cam/sim_target.h>		/* Target mode defines and macros */
#include <io/cam/sim_cirq.h>		/* Circular Q defines and macros */
#include <io/cam/dme.h>			/* DME include file */
#include <io/cam/sim.h>			/* SIMs include file */
#include <io/cam/sim_94.h>		/* SIM94 include file */
#include <io/cam/ccfg.h>		/* Configuration driver include file */
#include <io/cam/uagt.h>		/* UAgt include file */
#include <io/cam/xpt.h>			/* XPT include file */
#include <io/cam/tcds_adapt.h>		/* TCDS include file */
#include <io/cam/ata/sim_ata.h>		/* ATA/EIDE include file */
#include <io/cam/siop/psiopdefs.h>	/* psiop include file */

#include "asc.h"			/* Config generated defines file */
#include "tcds.h"			/* Config generated defines file */
#include "tza.h"                        /* Config generated defines file */
#include "pza.h"                        /* Config generated defines file */

#ifdef __alpha
#include "xza.h"		/* Defines # of config'ed XZA SCSI busses */
#include "siop.h"
#include "psiop.h"		/* PCI - SIOP's, NCR 53c810 */
#include "aha.h"
#include "ata.h"
#include "isp.h"
#include "itpsa.h"
#else
#define NXZA 0
#define NSIOP 0
#define NAHA 0
#define NATA 0
#define NISP 0
#define NITPSA 0
#endif

#include "scsi.h"			/* Total Number of SCSI controllers
					 * connected to the above "buses"
					 */

/* NSCSI currently covers NASC, NTZA, and NPZA, and NSIOP
 */
#define NCAM	(NSCSI)

/*
 * Define the total number of SIMport adapters.  This is used for
 * calculating SIMport common resource pool variable values.
 */
#define NSIMPORT (NTZA + NPZA)


/* ---------------------------------------------------------------------- */

/*
 * The system's SCSI bus id.
 */
int default_scsiid = DEFAULT_SCSIID;

/* ---------------------------------------------------------------------- */

/* The CAM CCB pool parameters.  These settings define the initial size, 
hi/low water marks and increment values.  These settings are used by the
XPT module. */

/* Moved to param.c; Configured via /etc/sysconfigtab. */
/*U32 cam_ccb_pool_size = 200;*/
/*U32 cam_ccb_high_water = 1000;	NOT USED */
/*U32 cam_ccb_low_water = 100;*/
/*U32 cam_ccb_increment = 50;*/

/*
 * The SIMport resource pool parameters. These settings define the initial
 * size, low watermarks and increment values.  These settings are used by
 * the SIMport module.
 */

U32 spo_car_pool_size = 400;		
U32 spo_car_low_water = 50;
U32 spo_car_increment = 50;

U32 spo_bsm_pool_size = 50;
U32 spo_bsm_low_water = 10;
U32 spo_bsm_increment = 20;


/* ---------------------------------------------------------------------- */
/* The CAM CDrv EDT scanning parameters.  These settings help to define
the scanning behavior when the CDrv is filling in or updating the EDT
data structures. */

U32 ccfg_inquiry_retry_limit = 3;
U32 ccfg_use_sdtr_inquiry = CAM_TRUE;
U32 ccfg_wait_delay_loop = CCFG_WAIT_DELAY_LOOP;

/* ---------------------------------------------------------------------- */

/* JAG: These two arrays need to reference the BUS count. */

EDT *edt_dir[ NCAM ]; 		/* ptrs for EDT grid per HBA */

unsigned long N_edt_dir = (sizeof(edt_dir)/sizeof(EDT *));

/* ---------------------------------------------------------------------- */

CAM_SIM_ENTRY *cam_conftbl[ NCAM ];

U32 N_cam_conftbl = (sizeof(cam_conftbl)/sizeof(CAM_SIM_ENTRY *));

/* ---------------------------------------------------------------------- */
/*
 * CAM SIM data.
 */
#ifdef CAMDEBUG
/*
 * Camdbg_flag and camdbg_id are only used during debug.  The shipped
 * source files will not use them.
 */
U32 camdbg_flag = (U32)0;
U32 camdbg_id = (U32)0;
#endif  /* CAMDEBUG */

/*
 * Used to identify a CAM controller structure.
 */
char cam_ctlr_string[] = { "CAM" };

/*
 * Configuration structures.
 */
int nNHBA94 = NASC + (2 * NTCDS);
int nNTZA = NTZA;
int nNPZA = NPZA;
int nNSIMPORT = NSIMPORT;
int nCAMBUS = NCAM;
struct device *camdinfo[NCAM*NDPS_16*NLPT_8];
struct controller *camminfo[NCAM];
SIM_SOFTC *softc_directory[NCAM];

#if NPSIOP > 0
int psiop_bus_table[NPSIOP];
#endif	/* NPSIOP */

#if NTZA > 0
int tza_bus_table[NTZA];
U32 kztsa_cntrs_enable = 0;
#endif /* NTZA */

#if NPZA > 0
int pza_bus_table[NPZA];
U32 pza_cntrs_enable = 0;
#endif /* NPZA */

#if NSIMPORT > 0
void *simport_softc_directory[NSIMPORT];
#endif

#if NASC > 0 || NTCDS > 0
int asc_bus_table[NASC + (2 * NTCDS)];
#endif /* NASC || NTCDS */

#if NAHA > 0
int aha_bus_table[NAHA];
#endif /* NAHA */

#if NATA > 0
ATA_BUS ata_bus_table[NATA];
#endif /* NATA */

#if NISP > 0
    /*
     * NOTE:
     *
     *    The boot flag "isp_fw_load" specified on the 
     *    command line during interactive boot takes
     *    precedence because kernargs are handled after
     *    configure. Here, isp_fw_load is set to a default
     *    value of 1. This means that the Qlogic sim driver
     *    will attempt to load a firmware image file from
     *    the root filesystem if it is present.
     *
     *    Since isp_fw_load is extern'd in kernargs.c, it
     *    must be defined whether or not there is a QLogic
     *    option present in the kernel configuration.
     */
    long isp_fw_load = 1;
    int isp_bus_table[NISP];
#else
    long isp_fw_load = 0;
#endif /* NISP */

#if NTCDS > 0
TCDS_BUS tcds_bus_table[NTCDS];

/*
 * sim94_fast_enable is only here to quickly and easily turn OFF all fast
 * buses.  The driver now examines the H/W state flags in the V3.0 console
 * eeprom, or in the PMAZC-AA option rom to determine which buses are fast.
 *
 * The tcds_inter_loop_limit value determines the number of scsi bus
 * interrupts that can be handled during 1 interrupt cycle before forcing
 * an exit.  The lower the value, the better the interrupt latency for
 * other devices (at the same priority).  The higher the value, the lower
 * the scsi interrupt overhead is.
 */
U32 sim94_fast_enable = 1;

#ifdef RT_PREEMPT_OPT
U32 tcds_inter_loop_limit = 1;
#else
U32 tcds_inter_loop_limit = 4;
#endif
#endif

/*
 * sim810_fast_enable is here to allow the psiop (810 chip) to run in
 * slow mode.  This would be needed if a long bus cable (over 3 meters)
 * is attached to the controller.  The default is fast - since the normal
 * system will use the internal cable only.  If a cable is added that
 * causes it to become "long" then set this to 0 to disable fast mode
 * (and therefore allow cable lengths of up to 6 meters).
 *
 * Supply the value of 40MHz for the default 810 SCLK speed. The default
 * speed will be used for any 810 not recognized by the system.
 *
 * The pci_script_space is loaded with script code during initialization;
 * this is where the NCR script processor executes from.
 *
 * The pci_local_space is a general r/w area for the NCR'810 processor.
 *
 * The psiop_min_selection_timeout specifies a minimum value (in 
 * microseconds (us)) for selection timeout. As the values available to
 * the chip are based on the SCLK frequency as well as a multiplier that
 * doubles for each of 15 possible selections, we cannot guarantee that
 * this will be the exact timeout value. Rather, we will select the first
 * value that is greater than or equal to the minimum timeout. If we exhaust
 * all 15 selections and still cannot exceed the minimum timeout, we
 * will use the last (largest) selection. The SCSI-2 specification
 * recommends a value of 250ms.
 */
#if NPSIOP > 0
U32 sim810_fast_enable = 1;
int default_810_clk_speed = PSIOP_810_SCLK_40MHz;  /* NOTE!: Units are MHz * 100 */
char pci_script_space[NPSIOP][PSIOP_SCRIPT_RAM_SIZE];	/* script area */
char pci_local_space [NPSIOP][PSIOP_LOCAL_RAM_SIZE];	/* local area */
int psiop_min_selection_timeout = 250000;               /* 250ms timeout */
#endif

#if NITPSA > 0
int     itpsa_patchable_scsiids[] = {
        -1,             /* 0 */
        -1,             /* 1 */
        -1,             /* 2 */
        -1,             /* 3 */
        -1,             /* 4 */
        -1,             /* 5 */
        -1,             /* 6 */
        -1,             /* 7 */
        -1,             /* 8 */
        -1,             /* 9 */
        -1,             /* 10 */
        -1,             /* 11 */
        -1,             /* 12 */
        -1,             /* 13 */
        -1,             /* 14 */
        -1,             /* 15 */
        -1,             /* 16 */
        -1,             /* 17 */
        -1,             /* 18 */
        -1,             /* 19 */
        -1,             /* 20 */
        -1,             /* 21 */
        -1,             /* 22 */
        -1,             /* 23 */
        -1,             /* 24 */
        -1,             /* 25 */
        -1,             /* 26 */
        -1,             /* 27 */
        -1,             /* 28 */
        -1,             /* 29 */
        -1,             /* 30 */
        -1,             /* 31 */
};
int     itpsa_npatchable_scsiids = sizeof(itpsa_patchable_scsiids) /
                                   sizeof(int);
/*
 * Flags.
 */
int     itpsa_wide_enable = TRUE;
int     itpsa_ultra_enable = TRUE;
int     itpsa_ultra2_enable = TRUE;
#endif

#if NXZA > 0
void* xza_softc_directory[NXZA];
#endif

/*
 * One state machine queue is kept for all controllers.
 */
U32 sm_queue_sz = SM_QUEUE_SZ * NCAM;
SIM_SM_DATA sm_data[SM_QUEUE_SZ * NCAM];
SIM_SM sim_sm;

/*
 * If scsi_bus_reset_at_boot is set to CAM_TRUE, a SCSI bus reset
 * will be performed at boot time.  This should not be set to
 * CAM_TRUE unless you are SURE that it is necessary for your device
 * to operate.
 */
I32 scsi_bus_reset_at_boot = CAM_FALSE;

/*
 * The SIM default value.  This value is initially SIM_DEFAULT_TIMEOUT
 * which is 5 seconds.  This shouldn't be changed unless you are SURE
 * that it is necessary for you device to operate.
 */
I32 sim_default_timeout = SIM_DEFAULT_TIMEOUT;

/*
 * The SIM will perform I/O reordering if the CCB's "cam_sort" value
 * is non-zero.  In a busy system it is possible that certain I/O's
 * will have to wait a while if reordering is allowing a lot of other
 * I/O to go first.  "sim_sort_age_time" is the maximum number of
 * microseconds that an I/O is allowed to sit and wait.
 *
 * The default is 2 sec (2000000 usec).
 */
U32 sim_sort_age_time = 2000000;
U32 sim_allow_io_sorting = 1;
U32 sim_allow_io_priority_sorting = 0;
U32 sim_min_sort_depth = 3;

/* ---------------------------------------------------------------------- */

/*
 * The prihperal driver unit table.
 */
PDRV_UNIT_ELEM pdrv_unit_table[(NCAM) * NDPS_8 * NLPT_8];
PDRV_UNIT_INFO pdrv_unit_info[(NCAM) * NDPS_8 * NLPT_8];

/*
 * The following are the variables used for the buf structure pool.
 */
U32 ccmn_bp_pool_size = 50;
U32 ccmn_bp_high_water = 90;
U32 ccmn_bp_low_water = 10;
U32 ccmn_bp_increment = 50;


/*
 * Error limits for the disk and tape drivers... Once the limits
 * are reached on a per device basis no more errlog entries will
 * be seen. A reboot clears...
 */

U32 cam_harderr_limit = 1000;
U32 cam_softerr_limit = 1000;

/*
 * The following allows changing the base timeout values for tape's
 * PLEASE NOTE ALL TIMES ARE IN SECONDS
 *
 * ctape_io_base_timo is the base timeout value for reads and write's.
 * For every 10000 bytes request a second is added to the base for the
 * timeout value.
 *
 * ctape_move_timo is the timeout value for a tape movement operations
 * that does not involve reads or writes.
 *
 * ctape_wfm_base_timo is the base value for writing filemarks. For
 * each filemark to be written 1 second is added.
 */
u_long ctape_io_base_timo = 300; 	/* 5 minutes			*/
u_long ctape_move_timo = 3600; 		/* 60 minutes			*/
u_long ctape_wfm_base_timo = 300;	/* 5 minutes Buffer flushes	*/

/*
 * For machines that don't issue a bus reset on boot issue a BDR to 
 * every tape drive seen. This is needed so when the machine boots
 * we can do our setups of the device. This will change once policy 
 * is determined for multi-initiator tapes.
 */
u_long ctape_boot_bdr = 1;		/* Issue a Bus device reset (tapes) */

/* 
 * Changable disk driver timeouts. cdisk_to_def for non read/write
 * commands to the disks (test unit ready, mode select etc.)
 * cdisk_io_def Hard fixed disk timeout value for i/o, and
 * cdisk_io_rmb for removable media disks since they are slow.
 */
u_long cdisk_to_def = 10;		/* 10 seconds			*/
u_long cdisk_io_def = 60;		/* 60 seconds (Tagged commands)	*/
u_long cdisk_io_rmb = 120;		/* 120 seconds (slow removables */

/*
 * (CAM_log_label_info):
 * Setting this flag to a non-zero value will cause informational
 * messages about disk labels to be logged to the syslog when an open
 * occurs for a SCSI/CAM disk.  This flag can be used to help debug
 * problems moving from ULTRIX disks to OSF/1 labelled disks.
 *
 * NOTE: When enabled, informational messages are always logged to
 * syslog (see /usr/adm/syslog.dated/<date>/kern.log for any messages).
 */
int CAM_log_label_info = 0;



/*
 * ************************************************************************* *
 * ************************************************************************* *
 * ************************************************************************* *
 *
 *                 FOR ALL INFORMATION THAT FOLLOWS:
 *
 * AS OF V4.0:
 *
 * The device information that has previously been added to this file
 * has been replaced by the Dynamic Device Recognition (DDR) Subsystem
 * and its database. This new subsystem's database contains device
 * information "exceptions" that patch a device type's "defaults" to create
 * an entry with the appropriate information. Please refer to the "ddr_config"
 * utility man page and associated documentation (referenced in the man page).
 *
 * To provide a path of backward compatibility, we will continue to
 * support the addition of device information to this file. However,
 * this support will terminate in a future release. Documentation on the
 * DDR subsystem includes migration information and pointers to tools
 * to aid in the migration.
 *
 * Please note that all future device support will *NOT* be added to this
 * file, but rather will utilize the DDR database.
 *
 * ************************************************************************* *
 * ************************************************************************* *
 * ************************************************************************* *
 */


/* ---------------------------------------------------------------------- */
/*
 * How to add "your own" SCSI (disk/tape/cdrom) device:
 *
 *
 *    For those who would like to connect their own (non-DEC) devices to the
 *    SCSI bus the ULTRIX CAM driver allows the addition and definition of new
 *    devices in the "cam_data.c" file supplied with every binary or
 *    source license.
 *
 *    A good starting place would be to review the table before reading
 *    this description.
 *    A new entry should be added to cam_devdesc_tab describing the new device.  
 *    An example disk and tape entry might look like the following:
 *
 *    DEV_DESC  cam_devdesc_tab[] = {
 *
 *    {"DEC     RZ55", 12, DEV_RZ55, (ALL_DTYPE_DIRECT << DTYPE_SHFT) | SZ_HARD_DISK, 
 *    (struct pt_info *)ccmn_rz55_sizes, 512, DEC_MAX_REC, NO_DENS_TAB, NO_MODE_TAB, 
 *    SZ_BBR, 
 *    NO_OPT_CMDS, SZ_READY_DEF, SZ_NO_QUE, DD_REQSNS_VAL | DD_INQ_VAL ,
 *    36, 64
 *    },
 *
 *    {"DEC     TZK10", 13, DEV_TZK10, (ALL_DTYPE_SEQUENTIAL << DTYPE_SHFT) | SZ_QIC_CLASS,
 *    (struct pt_info *)ccmn_null_sizes, SZ_NO_BLK, DEC_MAX_REC, &tzk10_dens, &tzk10_mod,
 *    SZ_NO_FLAGS,
 *    NO_OPT_CMDS, SZ_READY_DEF, SZ_NO_QUE, DD_REQSNS_VAL | DD_INQ_VAL,
 *    36, 64
 *    },
 *
 *    { 0 },
 *
 *    };
 *
 *    The first field is the vendor returned string identifying the drive.
 *    This string is composed of the vendor id (first 8 chars) followed by
 *    the product id.
 *
 *    The second field is the length of the string, the total string returned 
 *    by the unit is what we match on.
 *
 *    The third field is the ULTRIX name for the device (DEV_RZ55 for this
 *    disk, DEV_TZK10 for this tape. For disk devices that are not from DIGITAL
 *    a generic name of DEV_RZxx should be used. For tapes a couple of generic
 *    categories are supplied. DEV_TZQIC (Quarter inch cartridge tape unit), 
 *    DEV_TZ9TRK (9 Track tape unit), DEV_TZ8MM ( 8 millimeter tape units),
 *    DEV_TZRDAT ( RDAT tape units), DEV_TZ3480 ( 3480 tape units), and
 *    for tape devices that do not fit into any of the above generic 
 *    classifications DEV_TZxx should be used.
 *
 *
 *    The fourth field is the class of SCSI device and sub_class. The upper
 *    4 bits are the class of the device. Please refer to 
 *    /usr/sys/h/scsi_all.h for a complete list of defines. The lower 28
 *    bits are the sub class. 
 *    Currently for disks the sub classes are:
 *    SZ_HARD_DISK	Normal disk unit.
 *    SZ_FLOP_3		Floppy disk 3.5"
 *    SZ_FLOP_5		Floppy disk 5.25"
 *
 *    For tapes the sub classes are:
 *    SZ_TK_CLASS	TK50 and TK30 Class tape.
 *    SZ_RDATE_CLASS	TLZ04, RDAT Class tape.
 *    SZ_9TRK_CLASS	9 Track Class tape.
 *    SZ_QIC_CLASS	Quarter inch Class tape.
 *    SZ_8MM_CLASS	8 Millimeter Class tape.
 *    SZ_3480_CLASS	3480 Cartridge Class tape.
 *    SZ_LOADER		Is there a loader tied to the unit that does not
 *			have a separate id. (Not implemented as of yet ).
 *    These defines can be found in /usr/sys/h/pdrv.h
 *    
 *    The fifth field is the partition table entry.  Tape units should use
 *    sz_null_sizes.  Disk devices may use sz_rzxx_sizes.  The sz_rzxx_sizes
 *    assumes that the disk is at least 48Mb.  DO NOT MODIFY sz_rzxx_sizes!
 *    To create your own partition table, you must make an entry in the
 *    "size" struct below.
 *
 *    The sixth field is the block/sector size of the unit. This field is
 *    used for disks and cdroms. The field is the number of bytes in a
 *    sector/block that the unit uses. Refer to the technical manual of 
 *    your device to get that number.
 *    
 *    The sixth field is the block/sector size of the unit is now being phased
 *    out. The cam_disk driver will get the block size from the device now.
 *    The field is being reused for RAID boxes. Since each SCSI RAID box
 *    is different the lower byte is used to tell the driver which page
 *    contains the RAID level for this LUN, the next byte is the offset
 *    within the page that contains the RAID level. The upper 2 bytes 
 *    the size of the page to request.
 *
 *    The seventh field is the maximun record size the unit can do in a single
 *    transfer. This field is used for raw transfers only and not nbuf/io.
 *    The field allows for single raw transfers to be allowed up the number
 *    of bytes defined by the field. Primarily used for tapes that contain
 *    seimic data which can have hugh record sizes. Please note that if your
 *    machine does not have the physical memory or the unit can not do the size
 *    transfer requested, errors will be a result.
 *    
 *    The eighth field is used for tapes only. The entry is a pointer to the
 *    tape units density structure. Please refer to the density structure 
 *    write up below.
 *
 *    The ninth field is a pointer to a mode select table. If the field
 *    is filled in the disk/tape/cdrom drivers will do mode selects
 *    for each page defined in the table on initial opens of the device.
 *    this field is optional and is Not recommended to be set up unless
 *    it is truely needed. Please refer to the write up for the mode select
 *    table write up below.
 *
 *    The tenth field are flags which direct the disk/tape/cdrom drivers
 *    on how to treat the device. Current flags are:
 *    SZ_NO_FLAGS	No flags defined.
 *    SZ_BBR		Device allows bad block replacement (disks only).
 *    SZ_NOSYNC		Device does not allow synchronous data transfer.
 *    SZ_NO_DISC	Device does not allow disconnects.
 *    SZ_NO_TAG		Do not use tagged queueing even though device
 *			supports it.
 *    SZ_REORDER	Allow the SIM to reorder specific CCB's.
 *    SZ_DISPERSE_QUE   Allow the queue depth to be spread across all
 *			LUNS connected to the device.
 *
 *    The eleventh field are optional commands. Some devices support a
 *    larger command set then just the mandatory ones defined for the
 *    device defined by the SCSI specs. Currently the optional command
 *    that are recognized by the disk/tape/cdrom drivers are:
 *    NO_OPT_CMDS	Device does not support optional commands
 *    SZ_RW10 		Device supports 10 byte CDB's for read and write.
 *    SZ_PREV_ALLOW     Device supports prevent/allow media removal commnad
 *    SZ_EXT_RESRV	Device supports extended reserve/release command.
 *
 *    The twelfth field is maximun ready time is seconds. For disks this
 *    field represents powerup/spinup time combined. For tape it represents
 *    powerup/load/rewind from End of Tape. This is the maximun amount of
 *    time in seconds the disk/tape/cdrom drivers will wait for a unit to
 *    become ready.
 *
 *    The thirteenth field is tag queue depth. If the device supports tag
 *    queuing this field represents the depth of the queue the device 
 *    supports. Refer to your device manual to see if your device supports
 *    tag queuing and the depth of the queue.
 *
 *    The fourteenth field are valid flags for the inquirey data lenght 
 *    and request sense data lenght. Indicates which fields are valid.
 *    Defines are:
 *    DD_REQSNS_VAL	Request Sense lenght is valid.
 *    DD_INQ_VAL	Inquirey lenght is valid.
 *
 *    The fifteenth is the inquirey data lenght for the device.
 *    Must be used in conjunction with the DD_INQ_VAL flag.
 *
 *    The sixteenth field is the request sense data lenght for 
 *    the device. Must be used in conjuction with DD_REQSNS_VAL flag.
 *
 *    Below is the structure definition for the struct dev_desc 
 * 
 *
 *    Device Descriptor Structure
 *    There will be a device descriptor structure entry for each
 *    specific device supported by DEC.  A user may supply a new
 *    entry to the device descriptor table by adding it to TBD and
 *    relinking the kernel or by sending it via an ioctl() call
 *    (TBD).  The following describes an entry in the device
 *    descriptor table:
 *
 *    typedef struct dev_desc {
 *	   u_char	dd_pv_name[IDSTRING_SIZE];  
 *	   u_char  	dd_length;
 *	   u_char	dd_dev_name[DEV_NAME_SIZE];	
 *	   u_long  	dd_device_type;
 *	   struct  	pt_info *dd_def_partition;
 *	   u_long  	dd_block_size;
 *	   u_long	dd_max_record;
 *	   DENSITY_TBL *dd_density_tbl;
 *	   MODESEL_TBL *dd_modesel_tbl;
 *	   u_long  dd_flags;
 *	   u_long  dd_scsi_optcmds;
 *	   u_long  dd_ready_time;
 *	   u_short dd_que_depth;
 *	   u_char  dd_valid;
 *	   u_char  dd_inq_len; 
 *	   u_char  dd_req_sense_len;
 *    }DEV_DESC;
 *
 *
 *    The density table allows the definition of eight densities
 *    for each type of tape unit. The current method of writing
 *    a particular density is by selection of the units minor 
 *    numbers lower 3 bits. Please refer to the units technical
 *    manual for the density/compression codes and blocking factors
 *    for each density. Each density is made up of 
 *    the following:
 *    	The first field are valid flags which signify which 
 *	of the following fileds for this density are valid.
 *	Flags are
 *	DENS_VALID              Is the structure valid 
 *	ONE_FM                  Write 1 filemark on close QIC
 *	DENS_SPEED_VALID        Speed setting valid. Multi speed
 *	DENS_BUF_VALID		Run in buffered mode (cache)
 *	DENS_COMPRESS_VALID 	Compression code if supported
 *
 *	The second field is the scsi density code for this density.
 *
 *	The third field is the scsi compression code for this density
 *	if the unit supports compression.
 *
 *	The fourth field is the setting speeding for this density.
 *	Some units are varible speed for certain densities.
 *
 *	The fifth field buffer control setting. 
 *
 *	The sixth field is the blocking factor for this density
 *	Certain units (QIC) will only write data in fixed lenght
 *	blocks to the tape. This field is the number of bytes in
 *	it's blocking factor. The field is NULL if this density
 *	blocking factor is variable.
 *
 *	Below is the TZK10's density table. Please note that this
 *	unit supports both fix and variable records.
 *
 *   DENSITY_TBL 
 *   tzk10_dens = {
 *       { Minor 00 or rmtXl 
 *
 *       Flags 
 *       DENS_VALID | DENS_BUF_VALID |ONE_FM ,
 *
 *       Density code	Compression code	Speed setting
 *       SEQ_QIC120,		NULL,			NULL,
 *
 *       Buffered setting	Blocking		
 *       1,			512
 *       },
 *       { Minor 01 or rmtXh 
 *
 *       Flags 
 *       DENS_VALID | DENS_BUF_VALID |ONE_FM ,
 *
 *       Density code	Compression code	Speed setting	
 *       SEQ_QIC320,		NULL,			NULL,
 *
 *       Buffered setting	Blocking				
 *       1,			512
 *       },
 *       { Minor 02 or rmtXm 
 *
 *       Flags 
 *       DENS_VALID | DENS_BUF_VALID |ONE_FM ,
 *
 *       Density code	Compression code	Speed setting	
 *       SEQ_QIC150,		NULL,			NULL,
 *
 *       Buffered setting	Blocking				
 *       1,			512
 *       },
 *       { Minor 03 or rmtXa 
 *
 *       Flags 
 *       DENS_VALID | DENS_BUF_VALID  |ONE_FM,
 *
 *       Density code	Compression code	Speed setting	
 *       SEQ_8000R_BPI,		NULL,			NULL,
 *
 *       Buffered setting	Blocking				
 *       1,			512
 *       },
 *       { Minor 04 
 *
 *       Flags 
 *       DENS_VALID | DENS_BUF_VALID |ONE_FM ,
 *
 *       Density code	Compression code	Speed setting	
 *       SEQ_QIC150,		NULL,			NULL,
 *
 *       Buffered setting	Blocking				
 *       1,			512
 *       },
 *       { Minor 05 
 *
 *       Flags 
 *       DENS_VALID | DENS_BUF_VALID |ONE_FM ,
 *
 *       Density code	Compression code	Speed setting	
 *       SEQ_QIC320,		NULL,			NULL,
 *
 *       Buffered setting	Blocking				
 *       1,			1024
 *       },
 *       { Minor 06 
 *
 *       Flags 
 *       DENS_VALID | DENS_BUF_VALID |ONE_FM ,
 *
 *       Density code	Compression code	Speed setting	
 *       SEQ_QIC320,		NULL,			NULL,
 *
 *       Buffered setting	Blocking				
 *       1,			1024
 *       },
 *       { Minor 07 
 *
 *       Flags 
 *       DENS_VALID | DENS_BUF_VALID |ONE_FM ,
 *
 *       Density code	Compression code	Speed setting	
 *       SEQ_QIC320,		NULL,			NULL,
 *
 *       Buffered setting	Blocking				
 *       1,			NULL
 *       }
 *   };	end of tzk10_dens 
 *
 *    Below is the structure definition for the density_tbl
 *
 *    typedef struct density_tbl {
 *    	struct density{
 *    	   u_char    den_flags;		
 *    	   u_char    den_density_code;
 *    	   u_char    den_compress_code;
 *    	   u_char    den_speed_setting;
 *    	   u_char    den_buffered_setting; 
 *    	   u_long    den_blocking;	
 *    	}density[MAX_TAPE_DENSITY]; MAX_TAPE_DENSITY defined as 8 
 *    }DENSITY_TBL;
 *
 *    The mode select table allows up to 8 mode selects to be
 *    done for a device type on initial open of a unit.
 *    The mode select table for a device consists of 8 entries.
 *    Each entry has the following format:
 *    
 *    The first field is the SCSI page number for that device
 *    type. If the device is a tape and you want to set the
 *    device configuration page for tapes, the page number
 *    would be a hex 10.
 *
 *    The second field is the pointer to the mode select data.
 *    You must set up the page data and place the address
 *    of the page structure in this field.
 *
 *    The third field is the lenght of the page. This is the
 *    number of bytes of the page size you want sent to the 
 *    device.
 *
 *    The fourth field are flags for the mode select cdb the
 *    driver formats. Bit 0 a zero don't save page , a one
 *    save the page. Bit 1 a zero SCSI 1 device, a one 
 *    means a SCSI 2 device.
 *
 *    Below you will find the the following:
 *    1. Mode select table struct definition
 *    2. An example filled out mode select table for a TZK10 
 *    3. An filled out page definition for page hex 10 for
 *       the TZK10.
 *    
 *
 *     Mode Select Table Structure Definition:
 *
 *     typedef struct modesel_tbl {
 *     	   struct ms_entry{
 *     	       u_char  ms_page;	
 *     	       u_char  *ms_data;
 *     	       u_char  ms_data_len;
 *     	       u_char  ms_ent_sp_pf;
 *     	   }ms_entry[MAX_OPEN_SELS]; MAX_OPEN_SELS defined as 8
 *     }MODESEL_TBL;
 *
 *    MODESEL_TBL
 *    tzk10_mod = {
 *    	{ MODE PAGE ENTRY 1	
 *
 *    	Page number		The data pointer		
 *    	0x02,			(u_char *)&tzk10_page2,
 *
 *    	Data len		SCSI2??				
 *    	   28,			0x2
 *    	},
 *    	{ MODE PAGE ENTRY 2	
 *
 *    	Page number		The data pointer		
 *    	0x10,			(u_char *)&tzk10_page10,
 *
 *    	Data len		SCSI2??				
 *    	   28,			0x2
 *    	},
 *    	{ MODE PAGE ENTRY 3	
 *
 *    	Page number		The data pointer		
 *    	NULL,			(u_char *)NULL,
 *
 *    	Data len		SCSI2??				
 *    	NULL,			NULL
 *    	},
 *    	{ MODE PAGE ENTRY 4	
 *
 *    	Page number		The data pointer		
 *    	NULL,			(u_char *)NULL,
 *
 *    	Data len		SCSI2??				
 *    	NULL,			NULL
 *    	},
 *    	{ MODE PAGE ENTRY 5	
 *
 *    	Page number		The data pointer		
 *    	NULL,			(u_char *)NULL,
 *
 *    	Data len		SCSI2??				
 *    	NULL,			NULL
 *    	},
 *    	{ MODE PAGE ENTRY 6	
 *
 *    	Page number		The data pointer		
 *    	NULL,			(u_char *)NULL,
 *
 *    	Data len		SCSI2??				
 *    	NULL,			NULL
 *    	},
 *    	{ MODE PAGE ENTRY 7	
 *
 *    	Page number		The data pointer		
 *    	NULL,			(u_char *)NULL,
 *
 *    	Data len		SCSI2??				
 *    	NULL,			NULL
 *    	},
 *    	{ MODE PAGE ENTRY 8	
 *
 *    	Page number		The data pointer		
 *    	NULL,			(u_char *)NULL,
 *
 *    	Data len		SCSI2??				
 *    	NULL,			NULL
 *    	},
 *    };
 *
 *    SEQ_MODE_DATA6
 *    tzk10_page10 = {
 *    
 *    	{ Parameter header 
 *
 *    	mode_len	medium type	speed	
 *    	NULL,		NULL,		NULL,
 *
 *    	Buf_mode	wp		blk_desc_len	
 *    	0x01,		NULL,		sizeof(SEQ_MODE_DESC)
 *    	},
 *    	{ Mode descriptor 
 *
 *    	Density	num_blks2	num_blks1	
 *    	NULL,		NULL,		NULL,
 *
 *    	num_blks0	reserved	blk_len2	
 *    	NULL,				NULL,
 *
 *    	blk_len1	blk_len0			
 *    	NULL,		NULL
 *    	},
 *    	{
 *    	Page data for page 0x2 			
 *
 *    	PAGE header 
 *    	byte0	byte1				
 *    	   0x10,	0x0e,
 *
 *    	byte2    byte3    byte4    byte5    byte6	
 *    	   0x00,    0x00,    40,      40,      NULL,
 *
 *    	byte7    byte8    byte9    byte10   byte11	
 *    	   NULL,    0xe0,    NULL,    0x38,    NULL,
 *
 *    	byte12   byte13   byte14   byte15   		
 *    	   NULL,    NULL,    NULL,    NULL
 *    	}
 *     };
 *
 *********************************************************************/

/*
 * ************************************************************************* *
 * ************************************************************************* *
 * ************************************************************************* *
 *
 * AS OF V4.0:
 *
 * The Dynamic Device Recognition (DDR) subsystem is replacing the
 * following table.
 *
 * Please refer to the "ddr_config" utility man page and associated
 * documentation (referenced in the man page) for further information.
 *
 * ************************************************************************* *
 * ************************************************************************* *
 * ************************************************************************* *
 */

DENS_TBL_ENTRY   density_table[] = {
	0,		NULL,		/* 0x00 - Default density.	*/
};
int density_entrys = sizeof(density_table) / sizeof(struct dens_tbl_entry);


/*
 * The density structures for the known devices. You can
 * added your own at the bottom
 */
DENSITY_TBL 
def_dens = {
    {
    { /* Minor 00  or rmtXl*/
    /* Flags */ 
    DENS_VALID | DENS_BUF_VALID ,
    /* Density code	Compression code	Speed setting	*/
    SEQ_DEF_BPI,		NULL,			NULL,
    /* Buffered setting	Blocking				*/
    1,			NULL 
    },
    { /* Minor 01 or rmtXh */
    /* Flags */ 
    DENS_VALID | DENS_BUF_VALID,
    /* Density code	Compression code	Speed setting	*/
    SEQ_DEF_BPI,		NULL,			NULL,
    /* Buffered setting	Blocking				*/
    1,			NULL
    },
    { /* Minor 02 or rmtXm*/
    /* Flags */ 
    DENS_VALID | DENS_BUF_VALID ,
    /* Density code	Compression code	Speed setting	*/
    SEQ_DEF_BPI,		NULL,			NULL,
    /* Buffered setting	Blocking				*/
    1,			NULL
    },
    { /* Minor 03  or rmtXa*/
    /* Flags */ 
    DENS_VALID | DENS_BUF_VALID ,
    /* Density code	Compression code	Speed setting	*/
    SEQ_DEF_BPI,		NULL,			NULL,
    /* Buffered setting	Blocking				*/
    1,			NULL
    },
    { /* Minor 04 */
    /* Flags */ 
    DENS_VALID | DENS_BUF_VALID ,
    /* Density code	Compression code	Speed setting	*/
    SEQ_DEF_BPI,		NULL,			NULL,
    /* Buffered setting	Blocking				*/
    1,			NULL
    },
    { /* Minor 05 */
    /* Flags */ 
    DENS_VALID | DENS_BUF_VALID ,
    /* Density code	Compression code	Speed setting	*/
    SEQ_DEF_BPI,		NULL,			NULL,
    /* Buffered setting	Blocking				*/
    1,			NULL
    },
    { /* Minor 06 */
    /* Flags */ 
    DENS_VALID | DENS_BUF_VALID ,
    /* Density code	Compression code	Speed setting	*/
    SEQ_DEF_BPI,		NULL,			NULL,
    /* Buffered setting	Blocking				*/
    1,			NULL
    },
    { /* Minor 07 */
    /* Flags */ 
    DENS_VALID | DENS_BUF_VALID ,
    /* Density code	Compression code	Speed setting	*/
    SEQ_DEF_BPI,		NULL,			NULL,
    /* Buffered setting	Blocking				*/
    1,			NULL
    }
    }
}; /* end of def_dens */
/* End density structures.. Please extend the table
 * for your own tape drives.. The table is designed
 * to allow for flexibility and customer selections
 */

/* 
 * Mode Select issued to CD-ROM devices to set block length to 512 bytes.
 */
DIR_MODE_DATA6
cdrom_page0 = {

	{ /* Parameter header */
	/* mode_len	medium type	dpofua */
	0,		0,		0,
	/* wp	blk_desc_len	*/
	0,	sizeof(DIR_MODE_DESC)
	},
	{ /* Mode descriptor */
	/* Density	num_blks2	num_blks1	*/
	0,		0,		0,
	/* num_blks0	reserved	blk_len2	*/
	0,				00,
	/* blk_len1	blk_len0			*/
	0x2,		00
	},
};


SEQ_MODE_DATA6
dummy_seq_mode_data = {
	{ /* Parameter header */
	/* mode_len	medium type	speed	*/
	NULL,		NULL,		NULL,
	/* Buf_mode	wp		blk_desc_len	*/
	0x01,		NULL,		sizeof(SEQ_MODE_DESC)
	},
	{ /* Mode descriptor */
	/* Density	num_blks2	num_blks1	*/
	NULL,		NULL,		NULL,
	/* num_blks0	reserved	blk_len2	*/
	NULL,		0,		NULL,
	/* blk_len1	blk_len0			*/
	NULL,		NULL
	},
	{
	/* Page data since scsi 1 vendor unique	*/
	/* byte0	byte1		byte2		*/
	0x06,		0x00,		0x80,		
	/* byte3	byte4				*/
	0x80,		0x07
	}
	
};


/* 
 * Mode select tables
 */
MODESEL_TBL
cdrom_mode_sel = {
	{
	{ /* MODE PAGE ENTRY 1	*/
	/* Page number		The data pointer		*/
	00,			(u_char *)&cdrom_page0,
	/* Data len		SCSI2??				*/
	12,			NULL
	},
	{ /* MODE PAGE ENTRY 2	*/
	/* Page number		The data pointer		*/
	NULL,			(u_char *)NULL,
	/* Data len		SCSI2??				*/
	NULL,			NULL
	}
	}
};


/*
 * Default partition tables to be used if the
 * disk does not contain a parition table.
 */
struct size {
	daddr_t	nblocks;
	int	blkoffs;
}  ccmn_rzxx_sizes[8] = {
	131072,	0,		/* A=blk 0 thru 131071        (64Mb)     */
	262144, 131072,         /* B=blk 131072 thru 393215   (128Mb)    */
	-1,	0,		/* C=blk 0      thru ??????   (???Mb/Gb) */
	0,	0,
	0,	0,
	0,	0,
	-1, 	393216,         /* G=blk 393216 thru end (?)             */
	0,	0,
}, ccmn_rrd40_sizes[8] = {
	-1,	0,              /* A=blk 0 thru end (CDROM size variable) */
	0,	0,
	-1,	0,		/* C=blk 0 thru end (CDROM size variable) */
	0,	0,
	0,	0,
	0,	0,
	0,	0,
	0,	0,
}, ccmn_null_sizes[8] = {		/* Dummy for tapes */
	0,	0,
	0,	0,
	0,	0,
	0,	0,
	0,	0,
	0,	0,
	0,	0,
	0,	0,
};


/*
 * ************************************************************************* *
 * ************************************************************************* *
 * ************************************************************************* *
 *
 * AS OF V4.0:
 *
 * The following table will no longer be used. The Dynamic Device
 * Recognition (DDR) subsystem will provide the defaults.
 *
 * Please refer to the "ddr_config" utility man page and associated
 * documentation (referenced in the man page) for further information.
 *
 * ************************************************************************* *
 * ************************************************************************* *
 * ************************************************************************* *
 */

/*
 * This is the unknown device table. If a device is not in the
 * the cam_devdesc_tab[] then we default it to this table based
 * on device type found in the inquiry data.
 * Do Not change this table or the order of the entries.
 */
DEV_DESC dev_desc_unknown[] = {

/* UNKNOWN DISK */
{"UNKNOWN", 7, DEV_RZxx, (ALL_DTYPE_DIRECT << DTYPE_SHFT) | SZ_HARD_DISK, 
  (struct pt_info *)ccmn_rzxx_sizes, 512, DEC_MAX_REC, NO_DENS_TAB, NO_MODE_TAB,
  (SZ_BBR | SZ_NO_TAG | SZ_REORDER),
  NO_OPT_CMDS, SZ_READY_DEF, SZ_NO_QUE, DD_REQSNS_VAL | DD_INQ_VAL,
  36, 64
},
/* UNKNOWN TAPE */
{"UNKNOWN", 7, DEV_TZxx, (ALL_DTYPE_SEQUENTIAL << DTYPE_SHFT) | SZ_9TRK_CLASS, 
  (struct pt_info *)ccmn_null_sizes, NULL, (DEC_MAX_REC - 1), &def_dens, 
  NO_MODE_TAB, SZ_NO_FLAGS,
  NO_OPT_CMDS, SZ_READY_DEF, SZ_NO_QUE, DD_REQSNS_VAL | DD_INQ_VAL,
  36, 64
},

/* UNKNOWN Printer */
{"\0", 0, "\0", 0, 0, 0, 0, 0, 	
 0, 0, 0, 0, 0, 0, 0, 0},	

/* UNKNOWN Processor */
{"\0", 0, "\0", 0, 0, 0, 0, 0, 	
 0, 0, 0, 0, 0, 0, 0, 0},	

/* UNKNOWN WORM */
{"\0", 0, "\0", 0, 0, 0, 0, 0, 	
 0, 0, 0, 0, 0, 0, 0, 0},	

/* UNKNOWN cd-rom */
{"UNKNOWN", 7, DEV_RRDxx, (ALL_DTYPE_RODIRECT << DTYPE_SHFT) , 
  (struct pt_info *)ccmn_rrd40_sizes, 512, DEC_MAX_REC, NO_DENS_TAB,
  &cdrom_mode_sel, SZ_NO_FLAGS,
  SZ_PREV_ALLOW, 80, SZ_NO_QUE, DD_REQSNS_VAL | DD_INQ_VAL,
  36, 64
},
/* UNKNOWN Scanner */
{"\0", 0, "\0", 0, 0, 0, 0, 0, 	
 0, 0, 0, 0, 0, 0, 0, 0},	

/* UNKNOWN Optical */
{"\0", 0, "\0", 0, 0, 0, 0, 0, 	
 0, 0, 0, 0, 0, 0, 0, 0},	

/* UNKNOWN Medium Changer */
{"\0", 0, "\0", 0, 0, 0, 0, 0, 	
 0, 0, 0, 0, 0, 0, 0, 0},	

/* UNKNOWN Communication*/
{"\0", 0, "\0", 0, 0, 0, 0, 0, 	
 0, 0, 0, 0, 0, 0, 0, 0},	

};

/*
 * Number of valid unknown descriptors (size of table)
 */
I32 num_unknown_dev_desc = sizeof(dev_desc_unknown)/sizeof(DEV_DESC);

/*
 * ************************************************************************* *
 * ************************************************************************* *
 * ************************************************************************* *
 *
 * AS OF V4.0:
 *
 * The Dynamic Device Recognition (DDR) subsystem database is replacing
 * all information previously provided by the following table. DDR will
 * provide backward compatibility by searching for entries in this table
 * first before attempting to create an entry based on its database.
 *
 * HOWEVER: The information and interface provided by this table will be
 * removed in a future release.
 *
 * Please refer to the "ddr_config" utility man page and associated
 * documentation (referenced in the man page) for further information.
 *
 * ************************************************************************* *
 * ************************************************************************* *
 * ************************************************************************* *
 */

/*
 * CAM SCSI device descriptor information table.
 */
			/* DO NOT CHANGE MAX_DEVICE_DESC */
/* there should not be more than MAX_DEVICE_DESC entries */
DEV_DESC cam_devdesc_tab[] = {
{ 0 }
};


/*
 * Number of valid descriptors (size of table)
 */
I32 num_dev_desc = sizeof(cam_devdesc_tab)/sizeof(DEV_DESC);

/* END OF FILE */
/* ---------------------------------------------------------------------- */
