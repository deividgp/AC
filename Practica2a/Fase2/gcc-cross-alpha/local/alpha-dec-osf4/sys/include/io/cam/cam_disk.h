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
 * @(#)$RCSfile: cam_disk.h,v $ $Revision: 1.1.87.9 $ (DEC) $Date: 1999/03/16 17:54:59 $
 */
#ifndef _CAM_DISK_
#define _CAM_DISK_

/************************************************************************
 *
 *  cam_disk.h		Version 1.00 			April 18, 1991
 *
 *  This file contains the definitions and data structures for the 
 *  CAM disk driver.
 *
 *  MODIFICATION HISTORY:
 *
 *  VERSION  DATE	WHO	REASON
 *
 *  1.00     01/26/91	maria	Created from Disk Driver Func. Spec.
 *
 *  1.01     07/29/91	maria	Added rz wrapper mapping macros.
 *				Added ds_dkn for logging statistical info.
 *				Removed soft/hard error counters.
 *
 *  1.02     07/31/91   dallas  Added Version numbers to the structures
 *                              for the error logger
 *
 *  1.03     08/13/91   maria	Incrmented the CD_RETRY_RECOVERY define.
 *
 *  1.04     09/03/91   maria	Added OSF specific fields to disk
 *				specific structure.
 *				Added per partition open counter.
 *
 *  1.05     09/05/91   maria	Removed OSF specific fields from disk
 *				specific structure.
 *				Name changes for defines.
 *
 *  1.06     09/16/91   maria	Fixed wrapper macros for 4th
 *				controller.
 *
 *  1.07     11/19/91   maria	Moved peripheral flags and BBR defines
 *				from cam_disk.c.
 *
 *  1.08     12/16/91   maria	Added start unit retry count define.
 *
 ************************************************************************/

/* explicitly include power management headers */
#include <dec/pwrmgr/pwrmgr.h>

/*
 * Define of BLOCK MAJOR number
 */
#define CDISK_BMAJOR_COMPAT 8
/*
 * New major number
 */
#define CDISK_BMAJOR 48

#define CD_NUM_PARTITIONS 	8

#define CD_REC_TUR_RETRY	52 	/* 1/4 seconds retry or 13 secs. */
#define CD_RETRY_RECOVERY	10	/* Retry count for CCBs during the */
					/* recovery process. */
#define CD_RETRY_MODE_SEL 	5	/* Retry count for each mode */
					/* select page */
#define CD_RETRY_START_UNIT 	3	/* Retry count for start unit cmd */
#define CD_RETRY_MODE_SEN 	2	/* Retry count for mode sense cmd */
#define CD_RETRY_READ_CAP	2	/* Retry count for read capacity cmd */
#define CD_RETRY_IO		5	/* Retry for read and write cmds */
#define CD_RETRY_QUEFULL	80	/* Retry for I/O Quefull status	 */
#define CD_SWNORM_RETRY		1	/* Number of times we try for normal
					 * device path failure switch */
#define CD_SWRAID_RETRY		10	/* Number of times we try for RAID
					 * device path failure switch */
#define CD_PATH_LIMIT_RETRY	2	/* Number of times we retry a path
					 * fail type error before we try
					 * a path switch
					 */
/*
 * Setting for subsystem cam_disk, attribute disk_busy_timeout (sysconfig)
 */
#define CD_CA_BUSY_TMO_MIN	5	/* Min wait for busy status due to CA */
#define CD_CA_BUSY_TMO_DEF	10	/* Default wait for busy status due to CA */
#define CD_CA_BUSY_TMO_MAX	60	/* Max wait for busy status due to CA */

/*
 * Settings for cam_disk IO barrier code - sysconfig attributes
 * disk_iob_aptpl = Persistent Reservation `Auto Preserve Through Power Loss'
 */ 
#define CD_IOB_RETRY       3      /* Default of three */
#define CD_IOB_RETRY_MAX  20      /* Hi limit */
#define CD_IOB_RETRY_MIN   1      /* Low limit */
#define CD_IOB_APTPL_OFF   0            
#define CD_IOB_APTPL_ON    1

#define CD_IOB_CONSOLE_KEY_PREEMPT_OFF ((ulong) -1)
#define CD_IOB_CONSOLE_KEY_MIN 0
#define CD_IOB_CONSOLE_KEY_MAX CD_IOB_CONSOLE_KEY_PREEMPT_OFF

/*
 * Number of times we wait for the active que to clear before reseting
 * device
 */
#define CDISK_RECTIMER_LIMIT    24

#define CDISK_DEFAULT_TIMES             0xffffffff /* Use driver defaults */

/*
 * The device response queue (device alive)
 */

typedef struct cdisk_response_queue {
	struct ds_resp_que       *flink;
	struct ds_resp_que       *blink;
	u_long 			 mon_count;
	struct ds_resp_que       *act_flink;
	struct ds_resp_que       *act_blink;
	u_long 			 act_count;
	U64    flags;  		/* cdisk_response_thread flags */
	U64    act_flags;  	/* cdisk_act_mon_thread flags */
	U32    init;   		/* Has it been inited */
	int    lock_spl;	/* Lock stores the spl value.....*/
	simple_lock_data_t  resq_lck;
} CDISK_RESPONSE_QUEUE;

/* flags for CDISK_RESPONSE_QUEUE */
#define CDISK_RESP_ACTIVE	0x01 /* Response thread active */
#define CDISK_ACTMON_ACTIVE	0x02 /* Actively monitoring a device */



typedef struct ds_async {
	long	bus;
	u_long  target;
	u_long  lun;
} DS_ASYNC;
    
/* 
 * Our recovery que in the disk specific struct
 */
typedef struct ds_recover_que {
	PDRV_WS *flink;
	PDRV_WS *blink;
	U64	count;
} DS_RECOVER_QUE;


/*
 * Our device monitoring quesue
 */ 
typedef struct ds_resp_que {
	struct ds_resp_que *flink; 
	struct ds_resp_que *blink;
	struct disk_specific *ds_dsptr;
} DS_RESP_QUE;


/*
 * CCB's that are handled by timeouts()
 */
typedef struct ds_timeout_que {
	PDRV_WS *flink;
	PDRV_WS *blink;
	U64	count;
} DS_TIMEOUT_QUE;



/* 
 * ds_response_flags defines
 */
#define    DS_START_RESP	0x01    /* Indicates that we have started
					   active monitoring of LUN       */
#define    DS_TUR_RESP		0x02	/* Indicates that a TUR has been
					   formed for the LUN		  */
#define    DS_TUR_INFLT_RESP	0x04	/* A TUR is in flight (sent to 
					   lun				  */
#define    DS_TUR_NO_RESP	0x08	/* Indicates that we have had no
					   response from the TUR as of
					   yet....			  */
#define    DS_TUR_ERR_RESP	0x10	/* This device has been declared
					   as not responding erroring it
					   out 				  */
#define    DS_STARVATION_REPORTED 0x20  /* Starvation has been reported this
					   time around */
#define	   DS_TUR_TIMEO		10	/* Give this ccb 5 seconds to complete */

#define    CDISK_DEF_DEV_STARVATION     25  /* Number of seconds before we
					       report a possible device 
					       starvation problem 
					       (I/O Loading) */


/*
 * Bad Block Recovery Block Descriptor
 *
 * For each bad block that has to be reassigned, one of these structures
 * is allocated to track the state of the block.
 */
typedef struct bbr_block {
	struct bbr_block *bbrbd_next;	/* Pointer to the next BBR_BLOCK */
	u_char	  *bbrbd_data_test;	/* Pointer to the test data */
	u_char	  *bbrbd_data_good;	/* Pointer to the good data */
	DIR_DEFECT_DESC			/* Logical block number of the */
		  bbrbd_lbn_disk;	/* bad block in disk format */
	U32	  bbrbd_lbn_long;	/* Logical block number of the */
					/* bad block in longword format */
	U32	  bbrbd_listed;		/* Flag - block has been listed */
	U32	  bbrbd_reassigned;	/* Flag - block has been reassigned */
	U32	  bbrbd_written;	/* Flag - block has been written */
} BBR_BLOCK;

/*
 * Bad Block Recovery Status Block
 *
 * When BBR starts, one of these structures is allocated to track the
 * entire BBR process.  The information in this structure is specific to
 * the BBR process.
 */
typedef struct bbr_status {
	BBR_BLOCK  *bbrsb_block;	/* Pointer to the first BBR_BLOCK */
	BBR_BLOCK  *bbrsb_current;	/* Pointer to the current BBR_BLOCK */
	U32	   bbrsb_write_io;	/* Flag = 1 if original I/O write */
					/*      = 0 if original I/O read */
	U32	   bbrsb_need_data;	/* Flag = 1 if we need the data */
					/*      = 0 if we don't need data */
	U32	   bbrsb_q_frozen;	/* Flag = 1 sim queue is frozen */
					/*      = 0 sim queue isn't frozen */
	U32	   bbrsb_retry_cnt;	/* The number of bbr retries */
	U32	   bbrsb_state;		/* The current BBR state */
	U32	   bbrsb_opr_cnt;	/* Number of operations in current */
					/* state */
	U32	   bbrsb_err_cnt;	/* Number of errors in current state */
	U32	   bbrsb_suc_cnt;	/* Number of successful tests */
	U32	   bbrsb_no_spares;	/* Flag - no spare blocks available */
	U32	   bbrsb_read_fail;	/* Flag - unable to read */
	U32	   bbrsb_reas_fail;	/* Flag - unable to reassign */
	U32	   bbrsb_def_cnt;	/* Number of entries in defect list */
	U32	   bbrsb_dlist_size;	/* Size of the defect list buffer */
	U32	   bbrsb_spare0;	/* Maintain alignment */
	DIR_DEFECT_LIST
		   *bbrsb_dlist;	/* Points to defect list buffer */
	CCB_SCSIIO *bbrsb_trw_ccb;	/* Test/read/write ccb */
	CCB_SCSIIO *bbrsb_reas_ccb;	/* Reassign ccb */
} BBR_STATUS;


/*
 * Power management defines and data structures
 */

typedef struct cdisk_power {
	struct disk_specific	*ds;	     /* pointer to ourselves */
	struct cdisk_power	*forw;	     /* power mgmt queue */
	struct cdisk_power	*back;
        u_long			last_access; /* time at last access */
	int			flags;	     /* power mgmt state flags */
	int			dwell;	     /* number of minutes of inactivity
					      * at which we should spin down
					      * the device.
					      */
	int			failed_cnt;  /* how many successive times it
					      * failed to spin down.
					      */
	pwrmgr_devinfo_t	pwrdev;	     /* power manager intf struct */
} cdisk_power_t;

/*
 * flags for power management
 */
#define DS_PWR_SPNDWN_OPEN	0x0000001	/* Spindown opened the device */
#define DS_PWR_SPNDWN_OPEN_OLD	0x0000002	/* xpt open on old reg_nu */
#define DS_PWR_SPNDWN_RETRY	0x0000004	/* Retrying Spindown cmd */
#define DS_PWR_QUEUED		0x0000100	/* On pwr managed queue */


#define MAX_SPINDOWN_ATTEMPTS	5   /* # spindown attempts till we give up */

#define	CDISK_PWR_LOCKINIT				\
		simple_lock_setup(&cdisk_pwr_lock, cdisk_pwr_lockinfo)
#define	CDISK_PWR_LOCK			simple_lock(&cdisk_pwr_lock)
#define	CDISK_PWR_UNLOCK		simple_unlock(&cdisk_pwr_lock)
#define	CDISK_PWR_LOCK_HOLDER		simple_lock_holder(&cdisk_pwr_lock)
#define CDISK_PWR_LOCK_ADDR		(void *)simple_lock_addr(cdisk_pwr_lock)

/* return codes for some of the spindown/spinup routines */
#define CDISK_SPNOP_INPROG	0
#define CDISK_SPNOP_RETRY	1
#define CDISK_SPNOP_FAILED	2

/* What dwell time from the power manager do we look at */
#define CDISK_SPINDOWN_DWELL	0

#define CURRENT_TIME		(u_long)time.tv_sec

/*
 * calculate "dwelled" time
 *
 * who cares if our second counter wraps, as it would take several years
 */
#define CALC_DWELL_TIME(now,last,dwell)					\
	if ((now) < (last)) {						\
		/* just a later access (or counter wrap) */		\
		(dwell) = 0;						\
	} else {							\
		(dwell) = (u_int)(((now) - (last))/(u_long)60);		\
	}



/*
 * Disk Specific Structure Definition:
 */
typedef struct disk_specific  {
	struct disk_specific *flink;	/* Linkage into recovery que */
	struct disk_specific *blink;    /* Linkage into recovery que */
	SCSI_DID *scsi_did;		/* Pointer to the SCSI_DID struct */
	PDRV_DEVICE3 *ds_pd;		/* Pointer to our prdv_device3 */
    struct buf *ds_bufhd;		/* Anchor for requests which come */
					/* into strategy that cannot be */
					/* started due to error recovery */
					/* in progresss. */
	CCB_SCSIIO *ds_bbr_origccb;	/* Original ccb that invoked bbr */
	BBR_STATUS *ds_bbrsb;		/* Pointer to bbr status block */
	PDRV_WS	   *ds_bbr_wait_list;	/* List of ccbs waiting for bbr */
	int	   ds_dkn;		/* Used for system statistics */
	U32	   ds_bbr_active;	/* BBR active flag */
	U32	   ds_bbr_count;	/* Number of times bbr was invoked */
	U32	   ds_bbr_multiple;	/* Number of bad blocks bbr found */
	U32	   ds_bbr_success;	/* Number of bbr successes */
	U32	   ds_bbr_failure;	/* Number of bbr failures */
	CCB_SCSIIO *ds_tur_ccb;		/* SCSI I/O CCB for tur cmd */
					/* during recovery */
	CCB_SCSIIO *ds_start_ccb;	/* SCSI I/O CCB for start unit */
					/* cmd during recovery */
	CCB_SCSIIO *ds_stop_ccb;	/* SCSI I/O CCB for stop unit */
					/* cmd during power management */
	CCB_SCSIIO *ds_mdsel_ccb;	/* SCSI I/O CCB for mode select */
					/* cmd during recovery */
	CCB_SCSIIO *ds_rdcp_ccb;	/* SCSI I/O CCB for read capacity */
					/* cmd during recovery */
	CCB_SCSIIO *ds_read_ccb;	/* SCSI I/O CCB for Read cmd */
					/* during recovery */
	CCB_SCSIIO *ds_prev_ccb;	/* SCSI I/O CCB for Prevent */
					/* Media Removal cmd during recovery */
	CCB_SCSIIO *ccb_started_recovery;/* ccb that started recovery */ 
	U32	   ds_block_size;	/* This units block size */
	U32	   ds_tot_size;		/* Total disk size in blocks */
	U32	   ds_media_changes;	/* Number of times media was
					 * changed - removables */
        U32	   ds_cam_flags;        /* Used to hold the default 
					 * settings for the cam_flags 
					 * field in CCBs 
					 */
    struct pt	   ds_pt;		/* Partition structure */
	U32	   ds_openpart;		/* Bit mask of open parts */
	U32	   ds_bopenpart;	/* Bit mask of block opens */
	U32	   ds_copenpart;	/* Bit mask of char opens */
	U32	   ds_wlabel;		/* Write enable label */
    struct	   disklabel ds_label;

	U32	   ds_tag_action;       /* Used to hold the default settings 
					 * for the cam_tag_action field of 
					 * the SCSI I/O CCB 
					 */
	U32        ds_flags;            /* peripheral drivers flags */
	U32	   ds_state;            /* peripheral drivers - can */
					/* be used for recovery 
					*/
	U32	   ds_recovery_cnt; 	/* Error Recovery count which can 
					 * go on in the background Async 
					 * notification 
					 */
	U32	   ds_fatal_rec;	/* Indication that we had fatal 
					 * recovery errors
					 */
	U32	   ds_read_count;	/* Number of reads to device */
	U32	   ds_write_count;	/* Number of writes to device */
	U32	   ds_read_bytes;	/* Number of bytes read from device */
	U32	   ds_write_bytes;	/* Number of bytes written to device*/
	U32			junk;
	dev_t	   ds_bmajor;		/* Block major number for loadables */
	dev_t	   ds_cmajor;		/* Char major number for loadables */
	DS_ASYNC   ds_async;		/* What path we have registered on */
	U32	   ds_raid_level;	/* RAID level (-1 can't determine) */
	U32	   ds_rec_timer;	/* Number of times the recovery 
					 * routine been around without 
					 * the active que empty
					 */
	DS_RECOVER_QUE ds_recover_que;  /* CCB's that are awaiting recovery
					 * completion (resets, etc)
					 */
	DS_TIMEOUT_QUE ds_timeout_que; 	/* CCB's that are being handled
					 * by timeouts
					 */
	DS_RESP_QUE ds_mon_resp_que;    /* Linkage onto the que. */
	DS_RESP_QUE ds_actmon_resp_que; /* Linkage onto the que. */
	U64        ds_response;         /* Response indicator (not seltimo)*/
	U64        ds_response_flags;   /* Response flags */
	U64        ds_response_try;     /* Number of times we have tried to
					 * get a response from the unit
					 */
	U64     ds_resp_firsttime;      /* First time noticed no response */
	CCB_SCSIIO *ds_response_ccb;    /* Where we keep the response ccb */
	int        ds_response_io_time;
	U32        ds_tur_resp_timo;
	/* the following is the start of our policy values. */
        U32     ds_starvation_time;     /* number of seconds to wait            */
                                        /* for a device response before         */
                                        /* reporting a possible starvation.     */
	struct timeval ds_selection_time;/* Marks start of a SCSI seltion timeouts */
	U32	   ds_newmajor;		/* Major number flag.  set if new
					 * major number was used on first
					 * open to this disk.  clear if old
					 * major number was used
					 */
	void    (*ds_recov_hand)();	/* used to point to the recovery */
					/* handler for the device */
	SCSI_TRANS ds_scsi_trans;	/* a local copy of our translation
					 * struct */
	caddr_t    ds_ident_ptr;	/* Pointer to some memory that
					 * Further Identifies device */
	cdisk_power_t   ds_pwr;      	/* Power Mgmt structure */
	struct timeval	ds_busy_start;	/* Marks start of a SCSI BUSY status */
	CCB_SCSIIO 	*ds_busy_ccb;   /* 1st ccb with busy status	  */
    	u_long 	ds_exclusive;		/* Indicator of exclusive use.
					   CD-ROM/DVD only  only for now.... */
	u_long        ds_saved_iob_key; /* Saved Persistent Reservation key */
#define CDISK_IOB_PR_UNKNOWN     0x0
#define CDISK_IOB_PR_CAPABLE     0x1
#define CDISK_IOB_PR_NOTSUP      0x2
	int           ds_iob_support;   /* Is this device PR capable ? */
        u_long	ds_use_native_blksize;	/* Flag to signify that for the current
					   open, the driver should not perform
					   512 byte re-blocking.
					   CD-ROM/DVD only  only for now.... */
} DISK_SPECIFIC;

#define DISK_SPECIFIC_VERS      0x0B	/* Please remember to increment the
					 * version number when you change
					 * the structure
					 */
/*
 * The recovery thread que struct
 */
typedef struct cdisk_rec_que {
    DISK_SPECIFIC	*flink;
    DISK_SPECIFIC       *blink;
    U32			count;	/* Number of disk specifics linked */
    U32			flags;  /* Thread flags */
    U32			init;	/* Has it been inited */
    simple_lock_data_t  recq_lck;
}CDISK_REC_QUE;

/*
 * Flags for the cdisk_rec_que struct
 */
#define CDISK_RECQ_ACTIVE	0x01
#define CDISK_RECQ_SCHED	0x02

#define CDISK_RECQ_LOCK_INIT(recq)					\
{									\
usimple_lock_setup((simple_lock_t)&(recq)->recq_lck, cam_recq_lock_li);	\
}

#define CDISK_RECQ_LOCK( recq_ptr, saveipl)				\
{									\
	saveipl= splbio();						\
	CAM_SPINLOCK((simple_lock_t)&((recq_ptr)->recq_lck));		\
}
#define CDISK_RECQ_UNLOCK( recq_ptr, saveipl)				\
{									\
	CAM_SPINUNLOCK((simple_lock_t)&((recq_ptr)->recq_lck));		\
	(void)splx(saveipl);						\
}

/*
 * In order to minimize number of locks taken/released, the lock structure
 * in DISK_SPECIFIC was removed and PDRV_DEVICE3 is used instead. Macros
 * CDISK_INIT_LOCK, CDISK_LOCK and CDISK_UNLOCK are not used.
 */

/**********************************************
#define CDISK_INIT_LOCK( ds_ptr )

#define CDISK_LOCK( ds_ptr, saveipl )                         		\
	PDRV3_LOCK ((ds_ptr)->ds_pd, saveipl)

#define CDISK_UNLOCK( ds_ptr, saveipl )                       		\
	PDRV3_UNLOCK ((ds_ptr)->ds_pd, saveipl)
***********************************************/

#define CDISK_RECQ_INS_TAIL(ds_ptr, ccb_ptr)				\
{									\
    enqueue_tail(&(ds_ptr)->ds_recover_que, (ccb_ptr)->cam_pdrv_ptr);	\
    (ds_ptr)->ds_recover_que.count++;					\
}

#define CDISK_TIME_QUE( ds_ptr, ccb_ptr)				\
{									\
    enqueue_tail(&(ds_ptr)->ds_timeout_que, (ccb_ptr)->cam_pdrv_ptr);	\
    (ds_ptr)->ds_timeout_que.count++;					\
}

#define CDISK_RECQ_REM( recq_ptr)					\
{									\
	DISK_SPECIFIC *spec_ptr;					\
	spec_ptr = (recq_ptr)->flink;					\
	remque((void *)((recq_ptr)->flink));				\
	(spec_ptr)->flink = (DISK_SPECIFIC *)NULL;			\
	(spec_ptr)->blink = (DISK_SPECIFIC *)NULL;			\
	cdisk_rec_que.count--;						\
}

/*
 * Please note that this macro takes the rec_que lock and will
 * schedule the wakeup on the thread
 */
#define CDISK_RECQ_ADD( spec_ptr, wake_up_time )			\
{									\
int recq_spl;								\
	CDISK_RECQ_LOCK( &(cdisk_rec_que), recq_spl);			\
	if( (spec_ptr)->flink == (DISK_SPECIFIC *)NULL){		\
		enqueue_tail(&cdisk_rec_que, (spec_ptr));		\
		cdisk_rec_que.count++;					\
	}								\
	if((wake_up_time)){						\
	    if(( cdisk_rec_que.flags & (CDISK_RECQ_ACTIVE |		\
			CDISK_RECQ_SCHED)) == 0){			\
		cdisk_rec_que.flags |= CDISK_RECQ_SCHED;		\
	        timeout( wakeup, &cdisk_recovery_thread, 		\
						(wake_up_time));	\
	    }								\
	}								\
	else {								\
	    wakeup( &cdisk_recovery_thread );				\
	}								\
	CDISK_RECQ_UNLOCK( &(cdisk_rec_que), recq_spl);			\
}



/* 
 * Extension for device response detections
 */

#define CDISK_CHK_RESPONSE( ccb_ptr, ds_ptr)				\
{									\
struct timeval timenow_resp;						\
if((CAM_STATUS(ccb_ptr) == CAM_REQ_CMP) ||				\
		(CAM_STATUS(ccb_ptr) == CAM_REQ_CMP_ERR) || 		\
		(CAM_STATUS(ccb_ptr) == CAM_DATA_RUN_ERR) ||		\
		(CAM_STATUS(ccb_ptr) == CAM_AUTOSENSE_FAIL) ||		\
		(CAM_STATUS(ccb_ptr) == CAM_MSG_REJECT_REC)){		\
	(ds_ptr)->ds_response++;					\
	(ds_ptr)->ds_selection_time.tv_sec = 0;				\
}									\
else{									\
    if( (CAM_STATUS((ccb_ptr)) == CAM_SEL_TIMEOUT) || 			\
		(CAM_STATUS((ccb_ptr)) == CAM_NO_HBA)){			\
	TIME_READ(timenow_resp);					\
    	if( (ds_ptr)->ds_selection_time.tv_sec == 0){			\
	    (ds_ptr)->ds_selection_time.tv_sec = timenow_resp.tv_sec;	\
	}								\
	else {								\
	    if(( timenow_resp.tv_sec - 					\
			(ds_ptr)->ds_selection_time.tv_sec) >=		\
			cdisk_no_resp_time){				\
		((PDRV_WS *)((ccb_ptr)->cam_pdrv_ptr))->pws_flags	\
						|= PWS_FATAL_ERR;	\
		if( (ds_ptr)->ds_flags & DS_REC_INPROG){		\
		    (ds_ptr)->ds_flags |= DS_FATAL_RECOVERY;		\
		}							\
		else{							\
		    (ds_ptr)->ds_flags |= (DS_FATAL_RECOVERY |		\
				DS_REC_INPROG);				\
		    CDISK_RECQ_ADD( (ds_ptr), (hz/4));			\
		}							\
	    }								\
	}								\
    }									\
}									\
}


#define CDISK_RESP_LOCK_INIT( que_ptr )					\
{									\
usimple_lock_setup((simple_lock_t) &(que_ptr)->resq_lck, cam_resp_que_li);\
}

#define CDISK_RESP_LOCK(que_ptr)					\
{									\
	int saved_spl;							\
	saved_spl = splbio();						\
	CAM_SPINLOCK((simple_lock_t)&((que_ptr)->resq_lck));		\
	(que_ptr)->lock_spl = saved_spl;				\
}

#define CDISK_RESP_UNLOCK(que_ptr)					\
{									\
	 CAM_SPINUNLOCK((simple_lock_t)&((que_ptr)->resq_lck));		\
	 (void)splx((que_ptr)->lock_spl);				\
}

#define CDISK_ADD_MONITOR( ds_ptr, pd_ptr )				\
{									\
if( (ds_ptr)->ds_actmon_resp_que.ds_dsptr  == (DISK_SPECIFIC *)NULL){	\
    (ds_ptr)->ds_mon_resp_que.ds_dsptr = ds_ptr;			\
    (ds_ptr)->ds_actmon_resp_que.ds_dsptr = ds_ptr;			\
    (ds_ptr)->ds_pd = (pd_ptr);						\
    (ds_ptr)->ds_response = 0;						\
    enqueue_tail(&cdisk_resp_que.flink, &((ds_ptr)->ds_mon_resp_que.flink));\
    cdisk_resp_que.mon_count++;						\
}									\
}

#define CDISK_REM_MONITOR(ds_ptr)					\
{									\
if((ds_ptr)->ds_actmon_resp_que.ds_dsptr  != (DISK_SPECIFIC *)NULL){	\
	remque((void *)&((ds_ptr)->ds_mon_resp_que.flink));		\
	(ds_ptr)->ds_actmon_resp_que.ds_dsptr = (DISK_SPECIFIC *)NULL;	\
	cdisk_resp_que.mon_count--;					\
}									\
}	

#define CDISK_ADD_ACT_RESP_MON( ds_ptr )				\
{									\
enqueue_tail(&(cdisk_resp_que.act_flink),				\
			&((ds_ptr)->ds_actmon_resp_que));		\
cdisk_resp_que.act_count++;						\
(ds_ptr)->ds_response_try = 0;						\
}

#define CDISK_REM_ACT_RESP_MON(ds_ptr)					\
{									\
	remque((void *)&(ds_ptr)->ds_actmon_resp_que.flink);		\
	(ds_ptr)->ds_response_flags = 0;				\
	(ds_ptr)->ds_response = 0;					\
	cdisk_resp_que.act_count--;					\
	wakeup(&((ds_ptr)->ds_response_flags));				\
}	



/*
 * Peripheral device structure ds_flag bit definitions used by this
 * driver.
 */
#define DS_NO_DEVICE	0x01	/* Indicates device was opened with */
				/* F_NODELAY and the open failed */
#define DS_ONLINE	0x02	/* Indicates device ready and online */
 				/* ie partition table has been read */
#define DS_REC_INPROG	0x04	/* Indicates that the device has */
				/* encountered an error condition & */
				/* error recovery is in progress. */
#define DS_REC_START	0x08	/* Indicate recovery has started ie */
				/* first recovery ccb has been sent */
#define DS_REC_PEND	0x10	/* Indicates that recovery must be */
				/* restarted during the recovery */
				/* process. ie an error condition has */
				/* occurred during recovery processing */
				/* which requires recovery to restart */
#define DS_REC_TIMEOUT	0x20	/* Indicates that a timeout was issued */
				/* to retry a ccb during the recovery */
				/* process */
#define DS_OPENRAW	0x40	/* No part info, therefore open raw 
				 * (part a) */
#define DS_SYNCH	0x80	/* Indicates that we have sent a cmd */
				/* to initiate synchronous - set on */
				/* very first open */
#define DS_OFFLINE	0x100	/* Indicates device ready but not online */
				/* ie no floppy inserted into drive */
#define DS_PATH_SWITCH_REQ  0x200   /* Indicates that we are atempting a */
				/* Path switch */
#define DS_SWITCH_START 0x400   /* Indicates that we are bringing the unit
				 * to a usable state after a valid path
				 * switch */
#define DS_PATH_FAIL	0x800	/* Path Switch Failure */

/*
 * The following defines are used to indicate the recovery states seen.
 */
#define DS_REC_TUR		0x01000
#define DS_REC_ST_UNIT		0x02000
#define DS_REC_MODE_SEL		0x04000
#define DS_REC_READ_CAP		0x08000
#define DS_REC_READ		0x10000
#define DS_REC_PREV_ALLOW	0x20000
#define DS_REC_BUSY_CA		0x40000		/* Device reports busy, possibly */
						/* due to unresolved CA		 */
/*
 * Device is in maint. mode (RAID)
 */
#define DS_MAINT 		0x100000	/* RAID LUN in maint mode. */

/*
 * The following flag indicates to the cdisk_recovery routine
 * it is ok to start recovery.  This flag prevents a race
 * condition where we have a reset detected by SIM and have
 * not deleted the asyc_callback but are closing down the device.
 * Once the close happens we free up structs and then the recovery
 * starts the the async callback..
 */
#define DS_ASYNC_REGISTERED	0x200000	/* Indicates that asyc_callback 
						 * is enabled 
						 */
/*
 * The following flags are used to streamline error state checking
 * in cdisk_strategy()
 */
#define DS_RECOVERY_COUNT	0x400000	/* Indicates that recovery
						 * count limit was reached
						 */
#define DS_FATAL_RECOVERY	0x800000	/* Indicates that recovery failed
						 */
#define DS_SIZE_NULL		0x1000000	/* Indicates that either the block
						 * size or max LBN is reported
						 * as 0 by SCSI read capacity
						 */
/*
 * Device disabled via MUNSA event notification.
 * Flag blocks device from being brought online agaim
 */
#define DS_DEV_DISABLED		0x2000000

/* 
 * The following flag indicate that we don't monitor the device
 * when a start command has been send to the device.
 */
#define DS_REC_START_HOLDOFF	0x4000000


/*
 * The following are the defines used for Bad Block Recovery.
 */
#define CD_BBR_UNKNOWN		0x00	/* BBR unknown state */
#define CD_BBR_TEST		0x01	/* BBR test state */
#define CD_BBR_READ		0x02	/* BBR read state */
#define CD_BBR_REASSIGN		0x04	/* BBR reassigning state */
#define CD_BBR_WRITE		0x08	/* BBR write */
#define CD_BBR_RETRY		4	/* Number of BBR retries */
#define CD_BBR_TEST_SUC		3	/* Good block = this many successes */
#define CD_BBR_MAX_READ		10	/* Maximum read/test retries */
#define CD_BBR_MAX_REASSIGN	5	/* Maximum reassign retries */
#define CD_BBR_MAX_WRITE	5	/* Maximum write retries */
#define CD_BBR_MAX_RETRY	4	/* Maximum BBR retries */
#define CD_BBR_NOOP		0	/* BBR did nothing */
#define CD_BBR_FAIL		1	/* BBR failed */
#define CD_BBR_SUCCESS		2	/* BBR succeeded */

#define CD_ASC_RECOVERED	0x18	/* Additional sense code for */
					/* recovered data */
#define CD_ASC_NOSPARES		0x32	/* Additional sense code for no */
					/* more spares available */
#define CD_ASC_NOMEDIA		0x3a	/* Additional sense code for no */
					/* media present */
/*
 * Retrieve the partition number from the major/minor number
 */
#define CD_GET_PARTITION(dev)	((GETDEVS(dev)) & 0x03F)

#define RAID_MINOR	0xfffff		/* Special for raid */

#define CDISK_CHECK_RECOVERY_QUE(ds_ptr)				\
{									\
 if( (ds_ptr)->ds_recover_que.flink == (PDRV_WS *)NULL){		\
    (ds_ptr)->ds_recover_que.flink = (PDRV_WS *)&(ds_ptr)->ds_recover_que;\
    (ds_ptr)->ds_recover_que.blink = (PDRV_WS *)&(ds_ptr)->ds_recover_que;\
    (ds_ptr)->ds_timeout_que.flink = (PDRV_WS *)&(ds_ptr)->ds_timeout_que;\
    (ds_ptr)->ds_timeout_que.blink = (PDRV_WS *)&(ds_ptr)->ds_timeout_que;\
 }									\
}

#define   HSZ40_PID	    "HSZ40"

typedef struct hsz40_inq_data{
	ALL_INQ_DATA common_inq;   /* First 36 bytes of Inquiry Data */
        u_char this_ser[10];
        u_char other_ser[10];
        u_char reserved[40];
        u_char other_target : 4,  /* other target number */
               other_stat   : 1,  /* Status of the other controller */
                            : 2, 
               lun_32       : 1;  /* 32 bit LUN support */
        u_char lun0  :1,
               lun1  :1,
               lun2  :1,
               lun3  :1,
               lun4  :1,
               lun5  :1,
               lun6  :1,
               lun7  :1;
        u_char lun8  :1,
               lun9  :1,
               lun10 :1,
               lun11 :1,
               lun12 :1,
               lun13 :1,
               lun14 :1,
               lun15 :1;
        u_char lun16 :1,
               lun17 :1,
               lun18 :1,
               lun19 :1,
               lun20 :1,
               lun21 :1,
               lun22 :1,
               lun23 :1;
        u_char lun24 :1,
               lun25 :1,
               lun26 :1,
               lun27 :1,
               lun28 :1,
               lun29 :1,
               lun30 :1,
               lun31 :1;
}HSZ40_INQ_DATA;

/*
 * This data structure and the following symbols are used for debugging
 * the bad block recovery code.
 */

/*
 * Bad Block Recovery Debug Entry
 *
 * This structure defines one entry in the BBR debug table.  The symbols
 * below provide a short explanation of how the table works.
 */
typedef struct bbr_debele {
	U32	   type;		/* The type of entry */
	U32	   code;		/* The code for this entry */
	U32	   value1;		/* The value for this entry */
	U32	   value2;		/* The value for this entry */
}BBR_DEBELE;

/* Symbolic values for the TYPE field */

#define BBRT_ET			0	/* End of table */
#define BBRT_TS			1	/* Testing can start */
#define BBRT_TB			2	/* Test begin */
#define BBRT_TE			3	/* Test end */
#define BBRT_FC			4	/* Force code */
#define BBRT_FS			5	/* Force status */
#define BBRT_FK			6	/* Force sensekey */
#define BBRT_FB			7	/* Force bad block */
#define BBRT_VC			8	/* Verify code */
#define BBRT_VS			9	/* Verify status */
#define BBRT_VV			10	/* Verify value */
#define BBRT_WO			11	/* Wait for opcode */
#define BBRT_EM			12	/* Enable messages */
#define BBRT_DM			13	/* Disable messages */
#define BBRT_TD			14	/* Testing done */

/* Symbolic values for the CODE field (sorted by type) */

/* FORCE CODE values */

#define BBRC_FC_START		1	/* Force code in bbr_start */
#define BBRC_FC_RDR		2	/* Force code in bbr_read */
#define BBRC_FC_REQ		3	/* Force code in bbr_request */
#define BBRC_FC_WRK		4	/* Force code in bbr_work */

/* FORCE STATUS/FORCE KEY values */

#define BBRC_FS_COMPLETE	1	/* Force status in cdisk_complete */
#define BBRC_FS_WRK		2	/* Force status in bbr_work */

/* VERIFY CODE values - bbr routine start and finish points */

#define BBRC_VC_REQ_STR		1	/* Start  request routine */
#define BBRC_VC_REQ_FIN		2	/* Finish request routine */
#define BBRC_VC_STR_STR		3	/* Start  start routine */
#define BBRC_VC_STR_FIN		4	/* Finish start routine */
#define BBRC_VC_WRK_STR		5	/* Start  work routine */
#define BBRC_VC_WRK_FIN		6	/* Finish work routine */
#define BBRC_VC_RDR_STR		7	/* Start  read routine */
#define BBRC_VC_RDR_FIN		8	/* Finish read routine */
#define BBRC_VC_RDD_STR		9	/* Start  read done routine */
#define BBRC_VC_RDD_FIN		10	/* Finish read done routine */
#define BBRC_VC_RAR_STR		11	/* Start  reassign routine */
#define BBRC_VC_RAR_FIN		12	/* Finish reassign routine */
#define BBRC_VC_RAD_STR		13	/* Start  reassign done routine */
#define BBRC_VC_RAD_FIN		14	/* Finish reassign done routine */
#define BBRC_VC_WRR_STR		15	/* Start  write routine */
#define BBRC_VC_WRR_FIN		16	/* Finish write routine */
#define BBRC_VC_WRD_STR		17	/* Start  write done routine */
#define BBRC_VC_WRD_FIN		18	/* Finish write done routine */
#define BBRC_VC_DON_STR		19	/* Start  done routine */
#define BBRC_VC_DON_FIN		20	/* Finish done routine */

/* VERIFY CODE values - bbr routine special exit paths to verify */

#define BBRC_VC_STR_FIN_BD	21	/* Finish w/ bbr disabled */
#define BBRC_VC_STR_FIN_NC	22	/* Finish w/ not correctable */
#define BBRC_VC_STR_FIN_DR	23	/* Finish w/ device replaced block */
#define BBRC_VC_RDD_FIN_DE	24	/* Finish w/ device error */
#define BBRC_VC_RDD_FIN_TI	25	/* Finish w/ test impossible */
#define BBRC_VC_RDD_FIN_GD	26	/* Finish w/ got data */
#define BBRC_VC_RDD_FIN_BO	27	/* Finish w/ block okay */
#define BBRC_VC_RDD_FIN_RT	28	/* Finish w/ retry */
#define BBRC_VC_RDD_FIN_ET	29	/* Finish w/ exhaust test */
#define BBRC_VC_RDD_FIN_ER	30	/* Finish w/ exhaust read */
#define BBRC_VC_RAD_FIN_DE	31	/* Finish w/ device error */
#define BBRC_VC_RAD_FIN_NS	32	/* Finish w/ no spares available */
#define BBRC_VC_RAD_FIN_NB	33	/* Finish w/ new bad block */
#define BBRC_VC_RAD_FIN_RD	34	/* Finish w/ reassigns done */
#define BBRC_VC_RAD_FIN_RT	35	/* Finish w/ retry */
#define BBRC_VC_RAD_FIN_ER	36	/* Finish w/ exhaust reassign */
#define BBRC_VC_WRR_FIN_W2	37	/* Finish w/ re-write */
#define BBRC_VC_WRR_FIN_W1	38	/* Finish w/ first write */
#define BBRC_VC_WRR_FIN_AF	39	/* Finish w/ reassign fail */
#define BBRC_VC_WRR_FIN_RF	40	/* Finish w/ read fail */
#define BBRC_VC_WRR_FIN_NS	41	/* Finish w/ no spares */
#define BBRC_VC_WRR_FIN_EB	42	/* Finish w/ exhaust bbr */
#define BBRC_VC_WRR_FIN_EW	43	/* Finish w/ exhaust write */
#define BBRC_VC_WRD_FIN_DE	44	/* Finish w/ device error */

/* VERIFY CODE values - bbr routine special points to verify */

#define BBRC_VC_REQ_QE		45	/* Request - Queue is empty */
#define BBRC_VC_REQ_AC		46	/* Request - Active is clear */
#define BBRC_VC_STR_AS		47	/* Start - Allocate bbrsb */
#define BBRC_VC_STR_WI		48	/* Start - Write I/O */
#define BBRC_VC_STR_AB		49	/* Start - Allocate bbrbd */
#define BBRC_VC_STR_DT		50	/* Start - Deallocate test buffer */
#define BBRC_VC_IOC_QF		51	/* I/O comp - SIM queue frozen */
#define BBRC_VC_RDR_FR		52	/* Read req - First request */
#define BBRC_VC_RDR_AT		53	/* Read req - Allocate test buffer */
#define BBRC_VC_RDR_AI		54	/* Read req - Allocate I/O ccb */
#define BBRC_VC_RDD_TG		55	/* Read done - Copied test to good */
#define BBRC_VC_RDD_AT		56	/* Read done - Allocate test */
#define BBRC_VC_RAR_DL		57	/* Reas req - Deallocate list */
#define BBRC_VC_RAR_AL		58	/* Reas req - Allocate list */
#define BBRC_VC_RAR_AR		59	/* Reas req - Allocate reas ccb */
#define BBRC_VC_RAD_PR		60	/* Reas done - Partial reassign */
#define BBRC_VC_RAD_RB		61	/* Reas done - Repeat bad block */
#define BBRC_VC_RAD_AB		62	/* Reas done - Allocate bbrbd */
#define BBRC_VC_WRD_RE		63	/* Write done - Recovered error */
#define BBRC_VC_DON_DT2		64	/* Done - Deallocate 2nd test buffer */
#define BBRC_VC_DON_DG2		65	/* Done - Deallocate 2nd good buffer */
#define BBRC_VC_DON_DB2		66	/* Done - Deallocate 2nd bbrbd */
#define BBRC_VC_DON_DG		67	/* Done - Deallocate good buffer */
#define BBRC_VC_DON_RT		68	/* Done - Retry original I/O */
#define BBRC_VC_DON_DT		69	/* Done - Deallocate test buffer */
#define BBRC_VC_DON_DB		70	/* Done - Deallocate bbrbd */
#define BBRC_VC_DON_DL		71	/* Done - Deallocate list */
#define BBRC_VC_DON_DI		72	/* Done - Deallocate I/O ccb */
#define BBRC_VC_DON_DR		73	/* Done - Deallocate reas ccb */
#define BBRC_VC_DON_DS		74	/* Done - Deallocate bbrsb */

#define BBRC_VC_MAX		74	/* Maximum VC code */

/* VERIFY VALUE values */

#define BBRC_VV_RAR_BN		1	/* Reas req - block number */
#define BBRC_VV_RAD_RBN		2	/* Reas done - reassigned BN */
#define BBRC_VV_RAD_NBN		3	/* Reas done - new BN */

/***************************************************************************
 *
 *                      CAM_IOB_REQ definition
 * 
 * opcode   - functional operation code
 *
 *   CAM_IOB_REG - Register & Reserve each device in the dev_list
 *                 with the provided Reservation Key.  The key_list
 *                 contains a single `unique' Reservation Key.
 *
 *   CAM_IOB_PREEMPT - Issue a Preempt & Clear (type=WERO, scope=LUN)
 *                     to each device in the dev_list with the provided
 *                     Reservation Keys.  The key_list contains a list
 *                     of `unique' Reservation Keys.
 *
 *   CAM_IOB_BARRIER - Register, Reserve, and then Preempt & Clear each
 *                     device in the dev_list.  To implement this operation
 *                     the cdisk_io_barrier() routine will: 1) Register with
 *                     the provided Reservation Key, 2) issue a Reservation
 *                     (type=WERO and scope=LUN), 3) Read the existing
 *                     Reservation Keys in the device, and 3) Preempt and
 *                     Clear all Reservation Keys not matching the provided
 *                     Reservation Key.  The key_list contains a single
 *                     `common' Reservation Key.
 * 
 *      Note: When either the CAM_IOB_PREEMENT or CAM_IOB_BARRIER opcodes 
 *      are sent, a BUS RESET is issued to any device that does not support
 *      Persistent Reservations.  This is to maintain backwards
 *      compatibility with the ccmn_io_barrier() interface.
 * 
 * dev_list & dev_cnt - describe an array of dev_t records
 * 
 *   The dev_list parameter is an array of local dev_ts.  The dev_cnt
 *   parameter contains the `count' or number of dev_ts in the array.
 * 
 *   Note: in PT the caller will guarantee that each device in that list
 *   is open before calling cdisk_io_barrier.  In STEEL the caller will
 *   not guarantee that the devices described by these dev_ts are open.
 *
 *   Note: in Steelos the caller will produce this  dev_t list with
 *   the assistance of a HWID to dev_t conversion routine provided
 *   by the UHS-IO group.
 *
 * key_list & key_cnt - describe an array of Reservation Keys
 *
 *   The key_list parameter is an array of Reservation Keys. The key_cnt
 *   parameter contains the `count' or number of Reservation Keys in
 *   the array.  The key_list is further interpreted by the `opcode'.
 *   
 * timeo - Time Limit
 *
 *   The timeo parameter specifies the number of seconds allowed for the
 *   IO-Barrier operation to complete.  If all of the requested work
 *   cannot be completed in `timeo' seconds, cdisk_io_barrier will giveup
 *   and return an ETIMEDOUT status to the caller.
 *
 *   Note: the DEVRCI timeout value is calculated by dividing the
 *   provided `timeo' value by the cdisk_iob_retry value.  This
 *   number, put in the rci `timeo' field, determines the amount of
 *   time DEVRCI will allow for a single request to be completed - a
 *   `per-device' timeout.  (A single DEVRCI request may be comprised
 *   of multiple CAM IO requests; more at `cdisk_iob_retry'.)
 *
 * eei - DEV_EEI_STATUS output.
 *
 *   Upon encounting a device related error, cdisk_io_barrier will fill
 *   in the caller's DEV_EEI_STATUS structure at the address provided
 *   by `eei'.  If the caller does not want to receive EEI status 
 *   information, the eei parameter should be set to NULL.
 *
 * flags - functional flags
 *   
 *   CAM_IOB_FL_NORESET - CAM_IOB_BARRIER modifier
 *
 *     Don't do Bus Resets (old fashion IO barriers).  Only send
 *     Persistent Reserves to those devices support them.  Ignore
 *     those that don't.
 *
 *   CAM_IOB_FL_NOPRES - CAM_IOB_BARRIER modifier
 *
 *     Don't do Persistent Reservations (new IO barriers).  Only send
 *     Bus Resets to those devices that do not support Persitent Reserve.
 *     (Vis. only use old fashion IO barriers).
 *            
 *   CAM_IOB_NOT_MATCHING - CAM_IOB_PREEMPT modifer
 * 
 *     The provided key list contains the valid keys.  Any keys not
 *     matching these should be preempted.  Otherwise, when
 *     CAM_IOB_NOT_MATCHING is clear, the key list contains the
 *     invalid keys; the keys that should be preempted.
 *
 * rsvrd1  - reserved for future use.
 * 
 ***************************************************************************/

typedef struct cam_iob_req {
	  int    opcode;          /* Operation Code                       */
#define CAM_IOB_REG      0x1     
#define CAM_IOB_PREEMPT  0x2
#define CAM_IOB_BARRIER  0x4
        dev_t  *dev_list;       /* Device list pointer                  */
        int    dev_cnt;         /* Device list size                     */
	ulong  *key_list;       /* Reservation Key list                 */
        int    key_cnt;         /* Key list size                        */
        time_t timeo;           /* Time limit - in seconds              */
        DEV_EEI_STATUS *eei;    /* EEI status output - after an error   */
        int flags;              /* Functional Flags                     */
#define CAM_IOB_FL_NORESET   0x1   /* modifier for CAM_IOB_BARRIER */
#define CAM_IOB_FL_NOPRES    0x2   /* modifier for CAM_IOB_BARRIER */
#define CAM_IOB_NOT_MATCHING 0x4   /* modifier for CAM_IOB_PREEMPT */
        int rsvrd1;
} CAM_IOB_REQ;

extern int cdisk_io_barrier(CAM_IOB_REQ *);

/*
 * CAM DISK STATISTICS MACROS
 * 
 * This timeline diagram illustrates the meaning of the time-related
 * statistics that are kept for the CAM disk driver.
 * 
 *      S1      S2      S3              C1      C3      C2	Idle
 *      |       |       |       |       |       |       |	|
 *      |<---------------t1------------>|       |       |	|
 *      |       |<-------------t2---------------------->|	|
 *      |       |       |<-----------t3-------->|       |	|
 *      |       |       |       |       |       |       |	|
 * 	|<------------------di_time-------------------->|	|
 * 	|_______|_______|_______|_______|_______|_______|_______|__timeline
 * 
 *      S1 = start I/O #1       C1 = complete I/O #1
 *      S2 = start I/O #2       C2 = complete I/O #2
 *      S3 = start I/O #3       C3 = complete I/O #3
 * 
 *      t1,t2,t3 = time on the active and pending queues
 * 
 *      di_avque  = current number of outstanding i/o requests
 *      di_xfer   = total number of completed i/o requests
 *      di_avserv = (t1+t2+t3) = total i/o time spent
 *      di_wds    = total number of 64-bit longwords transferred
 * 	di_time	  = (C2 - S1) = total time disk was busy with i/o
 * 
 * (PDRV_WS *)pws	pointer to Peripheral Driver Working Set
 * (DISK_SPECIFIC *)ds	pointer to Disk Specific Struct
 */
#define CURRENT_USEC(t, t_usec) {			\
    extern struct timeval time;				\
    TIME_READ(t);					\
    t_usec = t.tv_sec * 1000000L + t.tv_usec;		\
}
#define CAM_STATS_START(pws, ds) {			\
    if (pws != (PDRV_WS *)NULL &&			\
        ds != (DISK_SPECIFIC *)NULL &&			\
	(ds->ds_flags & DS_ONLINE)) {			\
	struct timeval now;				\
	long now_usec;					\
	int index = ds->ds_dkn;				\
							\
	if (index != -1) {				\
	    CURRENT_USEC(now, now_usec)			\
	    pws->start_time = now_usec;			\
	    if (dk_avque[index]++ == 0L) {		\
		dk_initial_busy[index] = now_usec;	\
	    }						\
	}						\
    }							\
}
#define MAXLONG 0x7fffffffffffffff		/* account for wrapping */
#define CAM_STATS_FINISH(pws, ds) {					\
    if (pws != (PDRV_WS *)NULL &&					\
	ds != (DISK_SPECIFIC *)NULL &&					\
	(ds->ds_flags & DS_ONLINE)) {					\
	struct timeval now;						\
	long now_usec;							\
	long delta;							\
	int index = ds->ds_dkn;						\
									\
	if (index != -1 &&						\
	    pws->start_time != 0L) {					\
	    CURRENT_USEC(now, now_usec)					\
	    delta = now_usec - pws->start_time;				\
	    if (delta < 0L)						\
	        delta = (MAXLONG - pws->start_time) + now_usec;		\
	    dk_time_dev_busy_serv[index] += delta;			\
	    if (--dk_avque[index] == 0L) {				\
		delta = now_usec - dk_initial_busy[index];		\
		if (delta < 0L)						\
		    delta = (MAXLONG - dk_initial_busy[index]) + now_usec; \
		dk_time[index] += delta;				\
	    }								\
	}								\
    }									\
}

#endif /* _CAM_DISK_ */
