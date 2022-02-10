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
 * @(#)$RCSfile: xcr_port.h,v $ $Revision: 1.1.25.2 $ (DEC) $Date: 1996/04/11 20:06:30 $
 */

#ifndef _XCR_PORT_H_
#define _XCR_PORT_H_

#define SUCCESS 0
#define FAILURE -1

/*
 * Bottom end defines for the SHXCR controllers. The X represents
 * both the EISA version and maybe the PCI version.
 */

#define MAXIO	64*1024		/* Max I/O size			*/

#define SWXCR_5	0x70009835	/* 5 Channel version DAC960-5	*/
#define SWXCR_3 0x72009835	/* 3 Channel Version DAC960-3	*/
#define SWXCR_2 0x73009835	/* 1 Channel Version DAC960-2	*/

#define CONF_0_SHFT 0 		/* Shift value for config0 regs	*/
#define CONF_1_SHFT 8 		/* Shift value for config1 regs	*/
#define CONF_2_SHFT 16 		/* Shift value for config2 regs	*/
#define CONF_3_SHFT 24 		/* Shift value for config3 regs	*/

/* 
 * EISA ID Address offsets 
 */

#define EISA_CONFIG0 0xC80	/* For EISA ID 0 		*/
#define EISA_CONFIG1 0xC81	/* For EISA ID 1 		*/
#define EISA_CONFIG2 0xC82	/* For EISA ID 2 		*/
#define EISA_CONFIG3 0xC83	/* For EISA ID 3 		*/
#define EISA_SYS_INTR 0xC89	/* System Interrupt enable reg	*/
#define EISA_LDBELL  0xC8D	/* Local Doorbell register 	*/
#define EISA_SYS_DB_ENA 0xC8E   /* Eisa System Doorbell enable reg */
#define EISA_DBELL   0xC8F	/* Eisa System Doorbell register*/


#define XCR_MBXOFFSET 0xC90	/* offset from base		*/

/* Mail Box offsets from XCR_MBXOFFSET */

#define XCR_MBX0 XCR_MBXOFFSET + 0x00	/* Command Code			*/
#define XCR_MBX1 XCR_MBXOFFSET + 0x01	/* Command ID.			*/
#define XCR_MBX2 XCR_MBXOFFSET + 0x02	/* Block count,Chn,Testno etc   */
#define XCR_MBX3 XCR_MBXOFFSET + 0x03 	/* Tgt,Pas,bytecount		*/
#define XCR_MBX4 XCR_MBXOFFSET + 0x04 	/* State,Chnx			*/
#define XCR_MBX5 XCR_MBXOFFSET + 0x05
#define XCR_MBX6 XCR_MBXOFFSET + 0x06
#define XCR_MBX7 XCR_MBXOFFSET + 0x07 	/* Drive			*/
#define XCR_MBX8 XCR_MBXOFFSET + 0x08 	/* Paddr			*/
#define XCR_MBX9 XCR_MBXOFFSET + 0x09 	/* Paddr			*/
#define XCR_MBXA XCR_MBXOFFSET + 0x0A 	/* Paddr			*/
#define XCR_MBXB XCR_MBXOFFSET + 0x0B 	/* Paddr			*/
#define XCR_MBXC XCR_MBXOFFSET + 0x0C 	/* Scatter/Gather type		*/
#define XCR_MBXD XCR_MBXOFFSET + 0x0D 	/* Command ID Passed in MBX1	*/
#define XCR_MBXE XCR_MBXOFFSET + 0x0E 	/* Status			*/
#define XCR_MBXF XCR_MBXOFFSET + 0x0F 	/* Status			*/

/* 
 * PCI ID Address offsets 
 */

#define PCI_SYS_INTR 0x43	/* System Interrupt enable reg	*/
#define PCI_LDBELL  0x40	/* PCI Local Doorbell register 	*/
#define PCI_DBELL   0x41	/* PCI System Doorbell register*/

/* Mail Box offsets for PCI RAID (from io_base) */

#define XCR_P_MBX0 0x00	        /* Command Code		        */
#define XCR_P_MBX1 0x01	        /* Command ID.			*/
#define XCR_P_MBX2 0x02	        /* Block count,Chn,Testno etc   */
#define XCR_P_MBX3 0x03 	/* Tgt,Pas,bytecount		*/
#define XCR_P_MBX4 0x04 	/* State,Chnx			*/
#define XCR_P_MBX5 0x05
#define XCR_P_MBX6 0x06
#define XCR_P_MBX7 0x07 	/* Drive			*/
#define XCR_P_MBX8 0x08 	/* Paddr			*/
#define XCR_P_MBX9 0x09 	/* Paddr			*/
#define XCR_P_MBXA 0x0A 	/* Paddr			*/
#define XCR_P_MBXB 0x0B 	/* Paddr			*/
#define XCR_P_MBXC 0x0C 	/* Scatter/Gather type		*/
#define XCR_P_MBXD 0x0D 	/* Command ID Passed in MBX1	*/
#define XCR_P_MBXE 0x0E 	/* Status			*/
#define XCR_P_MBXF 0x0F 	/* Status			*/

#define XCR_INTR_ENABLE 0x01	/* System interrupt enable	*/
#define XCR_DB_INTR	0x01	/* Dbell interrupt enable	*/

#define XCR_CMDIN	0x01	/* Cmd in box bit		*/
#define XCR_CMDIN_FREE  0x00    /* Cmd in box free		*/
#define XCR_INTERRUPT	0x01	/* The EISA interrupt Bit for this cntrl */
#define XCR_STATUS_ACK  0x02	/* Tell the controller it can post again */

/*
 * Increase the spin count for those cases (ie. rebuild) where the
 * spec. says it can take a LOT longer to get the mailbox register.
 */
#define XCR_MAXSPIN	(0xfff * 500)	/* Number of times we spin	*/
/* 
 * Controller restart specific defines
 */
#define XCR_MESG_AVAIL	0x4	/* Message available		*/
#define XCR_DRV_SEQ	0x8	/* Drives are sequenceing	*/

#define XCR_MAX_CMDS 64
#define XCR_MAX_NOR_CMDS 60	/* Read/write etc...		*/
#define XCR_MAX_SPEC_CMDS 4	/* Config and passthru		*/

#define XCR_SCSI_REGS		0xf03
#define XCR_DIR_REGS		0xff
#define XCR_ALL8_REGS		0xff
#define XCR_VAL_REG0		0x03
#define XCR_DMA_REGS		0xf00
#define XCR_UNIT_CMD		0x83
#define XCR_DMA_UNIT_CMD	0xf83
#define XCR_SCATTER_REG		0x1000


/*
 * Controller message defines (restaring the controller)
 */
#define XCR_SCSI_TO		0x0	/* SCSI Drive select T/O */
#define XCR_FIRM_CHK		0x2	/* Firmware Checksum	*/
#define XCR_CONFIG_CHK		0x3	/* Config Checksum	*/
#define XCR_BMIC		0x4	/* BMIC failed (EISA)	*/
#define XCR_PCU			0x4	/* PCU failed (PCI)	*/
#define XCR_CONFIG_MIS		0x5	/* Config Mismatch	*/
#define XCR_MIRROR_ERR		0x6	/* ERR mirroe race recov */
#define XCR_MIRROR_RACE		0x7	/* Mirror RACE inprog	*/
#define XCR_MEMORY		0x8	/* Memory failure	*/
#define XCR_UNID_DRIVE		0x9	/* Unidentified drive	*/
#define XCR_INSTALL_ABORT	0xa	/* Installation aborted */
#define XCR_MIRROR_CRIT		0xb	/* Mirror race on critical*/
#define XCR_MEM_PARITY		0xf	/* Memory Parity Error	*/




#define PROBE_FAIL 0
#define PROBE_SUCCESS 1

#define HOT_START		0x01	/* Restart hung controller */
#define XCR_FAIL		-1	/* Failure		   */
#define XCR_SUCCESS 		0	/* Success		   */

/*
 * Controller slots
 */

typedef struct cmd_que {
    struct cmd_que *cmd_flink;	/* Forward pointer in the chain		*/
    struct cmd_que *cmd_blink;	/* Backward pointer in the chain	*/
    U32 flags;			/* FLAGS				*/
    int	seconds;		/* Seconds from time (entry on queue)	*/
    struct cntrl_ws *cmd_cmd;	/* The pointer to the real cmd struct.	*/
    u_char cmd_ref;		/* Our index into the world 		*/
}CMD_QUE;

/*
 * Slot flags
 */

#define SLOT_CMD_ACTIVE		0x00000001	/* Cmd active		*/
#define SLOT_TIMO_1		0x10000000	/* Timeout pass 1	*/
#define SLOT_TIMO_2		0x20000000      /* Timeout pass 2	*/
#define SLOT_TIMEOUT		0x40000000      /* Timed out restart	*/
#define TIMEOUT_1_MASK 		0x70000000	/* First one		*/
#define TIMEOUT_2_MASK 		0x20000000	/* First one		*/
#define TIMEOUT_1_MASK 		0x70000000	/* First one		*/

/*
 * Controller Softc 
 */
typedef struct xcr_softc {
    u_char *sc_bus_name;	/* Bus name ESIA/PCI			*/
    int sc_cntrl_num;		/* Our controller number		*/
    U32 sc_cntrl_type;		/* What version of the controller	*/
    struct controller *sc_ctrl;	/* Ptr to controller struct		*/
    U64 sc_iohandle;		/* Our I/O Handle			*/
    U32 sc_flags;		/* Our flags restarting etc...		*/
    U32 sc_reg_off;		/* Offset to first cntrl reg.		*/
    U32 sc_max_act;		/* Number of normal cmds active		*/
    U32 sc_spec_act;		/* Number of special cmds act (start)	*/
    U32 sc_cmds_act;		/* Number of cmd slots active		*/
    CMD_QUE *sc_act_flink; 	/* Forward pointer to active commands   */
    CMD_QUE *sc_act_blink; 	/* Backward pointer to active commands  */
    U32 sc_cmds_pending;	/* Number of cmds on the pending list   */
    struct cntrl_ws *sc_pend_flink;/* Forward pointer to cmds waiting	*/
    struct cntrl_ws *sc_pend_blink;/* Backward pointer to cmds waiting	*/
    CMD_QUE *sc_free_flink; 	/* Forward pointer to free slots   	*/
    CMD_QUE *sc_free_blink; 	/* Backward pointer to free slots  	*/
    U32 sc_free_cmd_slots;	/* Number of cmd slots available	*/
    CMD_QUE sc_cmd_que[XCR_MAX_CMDS]; /* The cmd que itself		*/
    CMD_QUE *sc_reissue_flink;	/* Temp storage for restarts		*/
    CMD_QUE *sc_reissue_blink;	/* Temp storage for restarts            */
    int (*sc_restartptr)();    /* Pointer to controller restart routine*/
    void (*sc_do_cmdptr)();     /* Pointer to controller do cmd routine */
    simple_lock_data_t sc_softc_lk;/* The lock struct for the softc	*/
    simple_lock_data_t sc_reg_lk;  /* The lock struct for the registers */
}XCR_SOFTC;

#define XCR_SOFTC_VERSION 2	/* Struct version number 		*/

/*
 * XCR_SOFTC flags
 */
#define XCR_RESTARTING	    0x00000001	/* Restarting controller */
#define XCR_RESTART_NEEDED  0x00000002  /* Needs to be restarted */
#define XCR_CNTRL_DEAD	    0x00000004	/* Controller is dead	 */




/*
 * Controller string name
 */
#define SWXCR_STR "SWXCR"


#define XCR_FREE_SLOT(sc,cmd_slot){				\
    enqueue_tail( &(sc)->sc_free_flink, (cmd_slot));		\
    (sc)->sc_free_cmd_slots++;					\
}

#define XCR_REM_ACT_QUE(sc, cmd_slot)				\
{								\
    remque((void *)(cmd_slot));					\
    --(sc)->sc_cmds_act;					\
}

/* 
 * get a free command slot
 */
#define XCR_GET_SLOT(sc, ws)					\
{								\
    --(sc)->sc_free_cmd_slots;					\
    ws->cntrl_cmd_slot = (sc)->sc_free_flink;			\
    ws->cntrl_cmd_slot->flags = 0;				\
    ws->cntrl_cmd_slot->cmd_cmd = ws;				\
    remque((void *)(sc)->sc_free_flink);			\
}

#define XCR_REM_PND( sc, ws )					\
{								\
    (ws) = (CNTRL_WS *)dequeue_head(&(sc)->sc_pend_flink);	\
    --(sc)->sc_cmds_pending;					\
}

#define XCR_INSERT_REISSUE( sc, what)				\
{								\
    enqueue_tail(&(sc)->sc_reissue_flink, (what)); 		\
}

#define XCR_INSERT_ACT( sc, what)				\
{								\
    ++(sc)->sc_cmds_act;					\
    enqueue_tail(&(sc)->sc_act_flink, (what)); 		\
}

#define XCR_INSERT_PND_HD( sc, ws )				\
{								\
    enqueue_head(&(sc)->sc_pend_flink, (ws)); 			\
    ++(sc)->sc_cmds_pending;					\
}

#define XCR_INSERT_PND( sc, ws )				\
{								\
    enqueue_tail(&(sc)->sc_pend_flink, (ws));			\
    ++(sc)->sc_cmds_pending;					\
}
/*
 * Special insert for a list walked we insert to the middle
 * of the pending list after all specials 
 */
#define XCR_INSERT( last_spec, ws)				\
{								\
    enqueue_head((last_spec), (ws));				\
    ++(ws)->cntrl_softc->sc_cmds_pending;			\
}

#define BLK_TO_REG3( blknu )    ((((blknu) >> 24) & 0x3 ) << 6)

#define BLK_TO_REG4( blknu )	((blknu) & 0xff )

#define BLK_TO_REG5( blknu )    (((blknu) >> 8) & 0xff )

#define BLK_TO_REG6( blknu )    (((blknu) >> 16) & 0xff )


#define XCR_CHK_PATH( comm )						\
{									\
    if(xcr_directory[ (comm)->xcr_cntrl ] == (XCR_SOFTC *)NULL){	\
	(comm)->xcr_status = XCR_INVAL_PATH;				\
    }									\
}

#define XCR_CHK_CALLBACK( comm )					\
{									\
    if((comm)->xcr_cbfcnp == (void *)NULL) {				\
	(comm)->xcr_status = XCR_INVAL_PARM;				\
    }									\
}

#define XCR_DO_CMD(softc, cmd_slot, ws)	((softc)->sc_do_cmdptr)((cmd_slot),(ws))

	

/*
 * Locking MACROs 
 */ 

#define XCR_LOCK_IT(lk, flags) usimple_lock(lk)
#define XCR_UNLOCK_IT(lk) usimple_unlock(lk)
#define XCR_SLEEP_UNLOCK_IT(chan, pri, lk) 			\
        mpsleep(chan, pri, "xcrZzz", 0, (void *)lk, (MS_LOCK_NO_RELOCK|MS_LOCK_SIMPLE))

/* hw2
#define XCR_LOCK_IT(lk, flags)
#define XCR_UNLOCK_IT(lk)
#define XCR_SLEEP_UNLOCK_IT(chan, pri, lk) 			\
	mpsleep(chan, pri, "Zzzzzz", 0, (void *)0, 0)
*/

#define XCR_LOCK_INIT(lock, lockinfo) {				\
	simple_lock_setup( &lock, lockinfo );	\
}

#define XCR_LCK_SC( sc, lk_type, saveipl )                   \
{                                                                       \
	saveipl= splbio();                                              \
	XCR_LOCK_IT( &((sc)->sc_softc_lk), (lk_type) );                \
}

#define XCR_UNLCK_SC( sc, saveipl )                          \
{                                                                       \
	XCR_UNLOCK_IT( &((sc)->sc_softc_lk) );                          \
	(void)splx(saveipl);                                            \
}

#define XCR_LCK_REG( sc, lk_type, saveipl )                   \
{                                                                       \
	saveipl= splbio();                                              \
	XCR_LOCK_IT( &((sc)->sc_reg_lk), (lk_type) );                \
}

#define XCR_UNLCK_REG( sc, saveipl )                          \
{                                                                       \
	XCR_UNLOCK_IT( &((sc)->sc_reg_lk) );                          \
	(void)splx(saveipl);                                            \
}

/*
 * Callback structure defines and locks
 */
typedef struct xcr_complete_que {
    struct cntrl_ws *flink;
    struct cntrl_ws *blink;
    U32 flags;
    U32 initialized;
    U32 count;
    simple_lock_data_t cplt_lock;
}XCR_COMPLETE_QUE;

#define XCR_CB_ACTIVE		0x00000001
#define XCR_CB_SCHED		0x00000002


#define XCR_CB_LOCK_INIT(ptr); {					\
    simple_lock_setup( &((ptr)->cplt_lock), xcr_cb_li );		\
}
#define XCR_CB_LOCK(cb, spl); {					\
    spl = splbio();							\
    XCR_LOCK_IT( &((cb)->cplt_lock), LK_RETRY );				\
}
#define XCR_CB_UNLOCK(cb, spl); {					\
    XCR_UNLOCK_IT( &((cb)->cplt_lock));					\
    splx(spl);								\
}
#define XCR_WS_REMOVE(xcr_ptr) remque((void *)(xcr_ptr))
#define XCR_WS_INSERT(xcr_ptr, where) enqueue_tail((where),(xcr_ptr))
		    

#define XCR_CB_WS_REMOVE(xcr_ptr) remque((void *)(xcr_ptr))
#define XCR_CB_WS_INSERT(xcr_ptr, where) 				\
{									\
    insque((void *)(xcr_ptr), (void *)(where));         		\
}

#endif /* _XCR_PORT_H_ */
