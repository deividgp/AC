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
 * @(#)$RCSfile: re.h,v $ $Revision: 1.1.22.2 $ (DEC) $Date: 1996/04/11 20:06:00 $
 */

#ifndef _RE_H_
#define _RE_H_

/* 
 * Struct definitions
 */

/*
 * The RE Specific Struct
 */
typedef struct re_specific {
    struct buf *rs_bufhd;       /* Anchor for requests which come 	*/
				/* into strategy that cannot be 	*/
				/* started due to resources 		*/
    int rs_dkn;              	/* Used for system statistics 		*/
    U32 rs_unit_reported;	/* Is this unit config'ed in the cntrl	*/
    U32 rs_block_size;		/* Units block size			*/
    U32 rs_tot_size;		/* Units total block count		*/
    u_char rs_status;		/* Device status			*/
    u_char rs_raid_level;	/* The raid label			*/
    struct pt rs_pt;            /* Partition structure 			*/
    U32 rs_wlabel;           	/* Write enable label 			*/
    struct disklabel rs_label;	/* The label				*/
}RE_SPECIFIC;


typedef struct xd_list {
	PD_WS *flink;
	PD_WS *blink;
}XD_LIST;


/*
 * The RE Device Struct
 */
typedef struct re_device {
    XD_LIST re_active;		/* Forward active pointer of cmds sent	*/
    U32 re_num_act;		/* Number of cmds sent			*/
    U32 re_dev;			/* major/minor number 			*/
    U32 re_ctrl;		/* Controller number			*/
    U32 re_unit;		/* Unit Number				*/
    U32 re_log_unit;		/* Our Logical Unit Number		*/
    U32 re_soft_errs;		/* Number of Soft errors		*/
    U32 re_hard_errs;		/* Number of Hard errors		*/
    U32 re_flags;		/* Specific to peripheral drivers	*/
    U32 re_state;		/* Specific to peripheral drivers	*/
    caddr_t re_specific;	/* Pointer to device specific info 	*/
    u_short re_spec_size;   	/* Size of device specific info 	*/
    U32 re_openpart;         	/* Bit mask of open parts 		*/
    U32 re_bopenpart;        	/* No of block opens 			*/
    U32 re_copenpart;        	/* No of char opens 			*/
    U32 re_read_count;      	/* Number of reads to device 		*/
    U32 re_write_count;    	/* Number of writes to device 		*/
    U32 re_read_bytes;     	/* Number of bytes read from device 	*/
    U32 re_write_bytes;     	/* Number of bytes written to device 	*/
    dev_t re_bmajor;        	/* Block major number for loadables 	*/
    dev_t re_cmajor;        	/* Char major number for loadables 	*/
    simple_lock_data_t re_device_lk;/* The lock struct			*/
}RE_DEVICE;

/*
 * RE_DEVICE FLAGS
 */
#define RE_ONLINE	0x00000001	/* Device is online		*/
#define RE_OFFLINE	0x00000002	/* Device is offline		*/
#define RE_NODEVICE	0x00000004	/* No device			*/
#define RE_OPENRAW	0x00000008	/* Open raw			*/



/*
 * The Unit Table element struct
 */
typedef struct re_table_elem {
    RE_DEVICE *el_device;	/* Ptr to device struct			*/
    U32 el_flags;		/* Flags opening closing modifing	*/
    U32 el_opens;		/* Opens against device			*/
    U16 el_type;		/* Device type disk tape etc.		*/
    u_char el_excluse;		/* Exclusive use indicator		*/
    simple_lock_data_t el_elem_lk;/* The lock struct                    */
}RE_TABLE_ELEM;

/*
 * el_flags
 */
#define EL_OPENING	0x0000001	/* Opening unit			*/
#define EL_CLOSING	0x0000002	/* Closing unit			*/
#define EL_WAITING	0x0000004	/* Something is waiting on prev	*/


#define RE_CLR_OPENING( ute )						\
{									\
    (ute)->el_flags &= ~EL_OPENING;					\
    wakeup(&rte->el_flags);						\
}
#define RE_CLR_CLOSING( ute )						\
{									\
    (ute)->el_flags &= ~EL_CLOSING;					\
    wakeup(&ute->el_flags);						\
}

/*
 * Flags for re_open_unit()
 */
#define RE_EXCLUSIVE		0x000000001
#define RE_SEMI_EXCLUSIVE	0x000000002
/*
 * Reserved			0x000000004
 *				0x000000008
 */
#define	RE_DO_PART		0x000000010	/* Do partition acct */
#define RE_FORCE		0x000000020	/* Force open if no device */

#define MINOR_SPEC_SHFT 6
#define UNIT_CTRL_MASK  0x7	/* Max number of units/controller */
#define CNTRL_SHIFT	0x3	/* SHIFTS down over unit	*/

/* New minor number format for Pluto II has changed the number
 * of bits in the controller field from 11 to 7.  
 * Number of controllers supported has increased from 6 to 8.
 */
#define CNTRL_MASK      0x7F    /* Controller field mask */

#define RE_UNIT_TO_DEV(xxunit)	((xxunit) << MINOR_SPEC_SHFT)

/*
 * Convert a device struct unit number to a controller
 * and unit number
 */
#define RE_DEV_TO_UNIT(dev) 		GETUNIT((dev))

#define RE_DEV_CTRL_UNIT(dev)	(GETUNIT((dev)) & 0x7)

#define GET_UBA_DEV(attach) makedev( 0, (RE_UNIT_TO_DEV((attach)->unit)))


#define RE_UNIT_TO_CNTRL(dev)						\
	((RE_DEV_TO_UNIT((dev)) >> CNTRL_SHIFT) & CNTRL_MASK)

#define GET_RE_DEVICE(dev) re_unit_table[GETUNIT((dev))].el_device


#define RE_GET_TAB_ELEM( dev )					\
	(RE_TABLE_ELEM *)&re_unit_table[GETUNIT((dev))]

#define RE_GET_PART( dev )	((GETDEVS(dev)) & 0x03F)


/*
 * Lock Macros
 */

/*
 * locking macros.
 */
#define RE_LOCK_IT(lk, flags) usimple_lock((lk))
#define RE_UNLOCK_IT(lk) usimple_unlock((lk))
#define RE_SLEEP_UNLOCK_IT(chan, pri, lk) \
    mpsleep(chan, pri, "Zzzzzz", 0, (void *)lk, (MS_LOCK_NO_RELOCK|MS_LOCK_SIMPLE))
/* HW2
#define RE_LOCK_IT(lk, flags)
#define RE_UNLOCK_IT(lk)
#define RE_SLEEP_UNLOCK_IT(chan, pri, lk)				\
	mpsleep(chan, pri, "Zzzzzz", 0, (void *)0, 0)
*/

#define RE_TABLE_LK_INIT( ute )						\
{									\
    usimple_lock_setup( (simple_lock_t )&((ute)->el_elem_lk), re_table_li ); \
}

#define RE_ELEM_LK( ute, lk_type, saveipl )				\
{									\
	saveipl= splbio();						\
	RE_LOCK_IT( (simple_lock_t )&((ute)->el_elem_lk), (lk_type) );	\
}

#define RE_ELEM_UNLK( ute, saveipl )					\
{									\
	RE_UNLOCK_IT( (simple_lock_t )&((ute)->el_elem_lk) );		\
	(void)splx(saveipl);						\
}

#define RE_ELEM_SLEEPUNLOCK( chan, pri, ute )				\
	RE_SLEEP_UNLOCK_IT((chan), (pri), (simple_lock_t )&((ute)->el_elem_lk));	\
    
    


#define RE_INIT_LOCK( rpd )						\
{ 									\
    usimple_lock_setup((simple_lock_t )&((rpd)->re_device_lk), re_device_li ); \
}

#define RE_LK_DEVICE( rpd, lk_type, saveipl )				\
{									\
    (saveipl) = splbio();						\
    RE_LOCK_IT(((simple_lock_t)&(rpd)->re_device_lk), (lk_type));	\
}

#define RE_UNLK_DEVICE( rpd, saveipl )					\
{									\
	RE_UNLOCK_IT((simple_lock_t )&((rpd)->re_device_lk) );		\
	(void)splx(saveipl);						\
}

#define RE_SMP_SLEEPUNLOCK( chan, pri, rpd )				\
    RE_SLEEP_UNLOCK_IT((chan),(pri),(simple_lock_t )&((rpd)->re_device_lk)); 

#define RE_SMP_LOCK( rpd )						\
{									\
	RE_LOCK_IT( (simple_lock_t )&((rpd)->re_device_lk), LK_RETRY );	\
}

#define RE_LOWER_IPL( spl )						\
{									\
	splx( (spl) );							\
}


/*
 * Allocate a communication struct
 */
#define XCR_ALLOC_COM()		re_alloc_com()

/*
 * Free a a communication struct
 */
#define XCR_FREE_COM( comm )		re_free_com((comm))
    

/*
 * do generic setup of the com blk
 * args XCR_COM *, RE_DEVICE *, &completion function
 */
#define RE_SETUP_COM(comm,pdrv,done)					\
{									\
    (comm)->xcr_cntrl = (pdrv)->re_ctrl;				\
    (comm)->xcr_unit = (pdrv)->re_unit;					\
    (comm)->xcr_cbfcnp = (done);					\
    (comm)->xcr_pdrv_ws->rws_device = (u_char *)pdrv;			\
    (comm)->xcr_complete = 0;						\
}

/*
 * set up a local transfer using the XCR_COM area for data storage
 * Args XCR_COM *, struct buf *, transfer len.
 */
#define RE_COM_XFR_LOC( comm, buf, len )				\
{									\
    (comm)->xcr_bp = buf;						\
    (comm)->xcr_dxfer_len = len;					\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= XCR_LOC_DATA_BUF;				\
    (comm)->xcr_data_ptr = (u_char *)(comm)->xcr_cmd_data;		\
}

#define RE_DIRECTXFR_COM( comm, buf, len )				\
{									\
    (comm)->xcr_bp = (struct buf *)NULL;				\
    (comm)->xcr_dxfer_len = len;					\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= XCR_SPEC_CMD;					\
    (comm)->xcr_data_ptr = (u_char *)(buf);				\
}

#define RE_DIRECTSCSI_COM( comm, buf, len )				\
{									\
    (comm)->xcr_bp = (struct buf *)NULL;				\
    (comm)->xcr_dxfer_len = len;					\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= (XCR_SPEC_CMD | XCR_SCSI_CMD);			\
    (comm)->xcr_data_ptr = (u_char *)(buf);				\
}

#define RE_COM_XFRSG_BP(comm, scat, num_scat , buf, len)		\
{									\
    (comm)->xcr_bp = (buf);						\
    (comm)->xcr_dxfer_len = (len);					\
    (comm)->xcr_data_ptr = (u_char *)scat;				\
    (comm)->xcr_sg_num = (num_scat);					\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= XCR_SCATTER_BUF;				\
}

#define RE_COM_XFR_BP(comm, bp)						\
{									\
    (comm)->xcr_bp = (bp);						\
    (comm)->xcr_data_ptr = (u_char *)(bp)->b_un.b_addr;			\
    (comm)->xcr_dxfer_len = (bp)->b_bcount;				\
    (comm)->xcr_resid = 0;						\
    (comm)->xcr_flags |= XCR_BUF;					\
}
    

/* 
 * Fill in CMD info
 * Args XCR_COM *, CMD, Timeout seconds, block number
 */

#define RE_CMD(comm, cmd, timo, blk, flags)				\
{									\
    (comm)->xcr_command = cmd;						\
    (comm)->xcr_timeout = timo;						\
    (comm)->xcr_blk_nu = blk;						\
    (comm)->xcr_flags |= flags;						\
}

#define RE_CLEAR_COM( com )						\
{									\
    (com)->xcr_status = 0;						\
    (com)->xcr_adap_status = 0;						\
    (com)->xcr_complete = 0;						\
    (com)->xcr_resid = 0;						\
}
/*
 * Increase the timeout value since Mylex states that they will service
 * requests within 60 seconds.
 */
#define RE_IOTIME	60	/* I/O timeout value */
#define RE_DEF_TIMO	60	/* Non I/O timeout value */

/*
 * Insert into tail of active queue and ++ the active count
 * MUST BE DONE locked....
 */
#define RE_INSERT_Q( comm, pdrv )					\
    enqueue_tail(&(pdrv)->re_active, (comm)->xcr_pdrv_ws);		\
    (pdrv)->re_num_act++;

/*
 * Remove for the upper driver queues
 * Args XCR_COM * , RE_DEVICE *
 */
#define RE_REMOVE_Q( comm, pdrv )					\
    remque((void *)(comm)->xcr_pdrv_ws);				\
    (pdrv)->re_num_act--;


#define RE_IO_STRATEGY_ERR(bp, err) {		\
    bp->b_flags |= B_ERROR;			\
    bp->b_resid = bp->b_bcount;			\
    bp->b_error = err;				\
    (void) biodone(bp);				\
}

	

/*
 * Insert into tail of queue (tracking ) as send it on down
 * Args XCR_COM *, RE_DEVICE *
 */
#define RE_SEND_CMD( comm, pdrv, ret_stat)				\
{									\
    int spl_sav;							\
    RE_LK_DEVICE( (pdrv),(LK_RETRY), (spl_sav));			\
    (void)RE_INSERT_Q((comm),(pdrv));					\
    RE_UNLK_DEVICE((pdrv), (spl_sav));					\
    *ret_stat = xcr_action((comm));					\
}


#define MAX_UNITS_CNTRL 8	/* Max number of systems drives per cntrl */
#define RE_NUM_PARTITIONS 8	/* Number of disk partitons		  */
/*
 * Status definitions for re_sysunit_info 
 */

#define RS_ONLINE	0x3 	/* No drives down in set		*/
#define RS_CRITICAL	0x4	/* A drive down in the set		*/
#define RS_OFFLINE	0xff	/* Configed unit but dead.		*/

/* 
 * Information returned per unit for the Get system drive info cmd
 */
typedef struct re_sysunit_info {
    U32 su_size;	    /* SIZE in sectors			*/
    u_char su_status; 	    /* 03h = ONLINE, 04h = CRITICAL, 0FFh=OFFLINE */
    u_char su_raidlevel;    /* RAID Level of device			*/
    U16 su_reserved;
}RE_SYSUNIT_INFO;

/*
 * Info returned for all drives for Get system drive info cmd
 */
typedef struct re_sysdrvs_info {
    RE_SYSUNIT_INFO sd_drvs[MAX_UNITS_CNTRL];
}RE_SYSDRVS_INFO;

/* 
 * Default partition size struct 
 */
typedef struct re_size {
	int          nblocks;
	daddr_t      blkoff;
}RE_DEF_SIZE;

/* defines for re_complete() */
#define	RE_IO_FAILURE	0x1
#define	RE_IO_DONE	0x2
#define RE_IO_RETRY	0x3


/*
 * Since the unit doesn't retrun any geometry info we must make it
 * up.. These are the defines to do so.
 */
#define RE_MAXHEADS 128		/* HEADS */
#define RE_SECPTRK  32		/* Sectors per track */
#define RE_SECSIZE  512		/* Number of bytes per sector */

/*
 * Since scatter gather is not on all machines
 * Max ioctl io size is 8k
 */
#define MAX_IOCTL_IO (1024 * 8)

#endif /* _RE_H_ */
