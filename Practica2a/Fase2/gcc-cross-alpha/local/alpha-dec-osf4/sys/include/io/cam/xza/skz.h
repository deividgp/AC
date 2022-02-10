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
#if !defined(SKZ_INCLUDE)
#define SKZ_INCLUDE

/************************************************************************
 *									*
 * File:	skz.h							*
 * Date:	November 6, 1991					*
 * Author:	Ron Hegli						*
 *									*
 * Description:								*
 *	This file contains skz driver structures and definitions for    *
 *	the XZA/SCSI							*
 *									*
 ************************************************************************/

#include <io/cam/xza/skz_target.h>

/*
** Basic masks
*/
#define XZA_CHAN_0		0x00000001
#define XZA_CHAN_1		0x00000002
#define XZA_BOTH_CHANNELS	0x00000003

#define	SKZ_ALL_LUNS		0xff

/*
** SKZ Flags
*/
#define SKZ_EEPROM_DATA_UPDATED		0x00000001L /* EEPROM up-to-date */
#define SKZ_RESET_NEEDED		0x00000002L /* bus reset required */
#define SKZ_BUS_RESET_IN_PROGRESS	0x00000004L /* bus reset in progress */
#define SKZ_PROBE			0x00000010L /* Probe flag */
#define SKZ_THREADS_ACTIVE		0x00000020L /* Threads Initialized */
#define SKZ_DUP_VA			0x00000040L /* Kernel mapped uva's */
#define SKZ_SG				0x00000080L /* SG array alloc'ed */
#define SKZ_ADAPT_RESET_IN_PROGRESS	0x00000100L /* adapter reset */
#define SKZ_RESP_TH			0x00000200L /* Resp thread init */
#define SKZ_ERROR_TH			0x00000400L /* Error thread init */
#define SKZ_ALIVE			0x00000800L /* Chan alive flag */
#define SKZ_BUS_RESET_DONE              0x00001000L /* Bus reset sent */
#define SKZ_HBA_INIT_DONE               0x00002000L /* HBA init is complete */
#define SKZ_REINIT_DONE                 0x00004000L /* Reinit is complete */
#define SKZ_INTERRUPT_ENABLE		0x00008000L /* Enable interrupts  */
#define SKZ_STATE_WAIT                  0x00010000L /* Waiting for Interrupt */
#define SKZ_RESP_WAIT                   0x00020000L /* Waiting on resp thread*/
#define SKZ_ENABLE_LUN_NEEDED           0x00040000L /* Reenable LUN befor
						       ss_reset_detected */
/*
** XZA SCSI Target Structure
*/
typedef struct xza_scsi_target {
	unsigned long		purgqs;		/* outstanding PURGQ cmds */
} XZA_SCSI_TARGET;


/* The XZA_REG_CMD_QUEUE data structure is used to keep a register
   write histogram. This will be helpfull in the event of a
   Invalid Register Emilation interrupt (new w/ Rev 5.0).
*/

typedef struct xza_reg_cmd_queue {
  struct xza_reg_cmd_queue *flink;   /* front link to next cmd */
  struct xza_reg_cmd_queue *blink;   /* back link to previous cmd */
  u_int                     cmd;   /* present register emulation command */
} XZA_REG_CMD_QUEUE;

#define SKZ_REG_CMD_QUEUE_SIZE 10       /* Keep 10 former states around */

#define SKZ_PUT_REG_CMD(command,ptr) {   \
  (ptr) = (ptr)->flink;                  \
  (ptr)->cmd = (command);                \
}

/* The SKZ_TGT_REGS data structure is used to save the target mode status
   registers at interrupt time.  Since sharing this data structure could
   present synchronization problems each ISR incarnation will keep its own
   copy of this data structure;  allowing us to acknowledge the interrupt 
   and liberate HBA resources ASAP.

*/

/* Flags definitions */

#define SKZ_TGT_REG_VALID        0x1      /* struct contains valid data */
#define SKZ_TGT_REG_INUSE        0x10     /* This struct is currently in use */
#define SKZ_TGT_REG_WAKE_THREAD  0x1000   /* Tell target_sm to wake target 
                                             thread to complete interrupt */

#define SKZ_TGT_INTR_QUEUE_SIZE 10        /* Handle up to 10 interrupts */

typedef struct skz_tgt_regs {
  ASR_REG                   asr;  /* Saved asr register */
  TGT_AFAR0_REG           afar0;  /* Saved afar0 register */
  TGT_AFAR1_REG           afar1;  /* Saved afar1 register */
  XZA_LUN_STATE           state;  /* from the ase.amacc */
  struct xza_channel      *chan;  /* Saved pointer to channel */
  int                     flags;  /* Flags inidicating vaild/invalid, etc */
} SKZ_TGT_REGS;

/* The XZA_TGT_INTR_QUEUE data structure is used to pass register
   data to the Target Mode interrupt thread.
*/

typedef struct xza_tgt_intr_queue {
  struct xza_tgt_intr_queue *flink;   /* front link to next structure */
  struct xza_tgt_intr_queue *blink;   /* back link to previous structure */
  SKZ_TGT_REGS                 reg;   /* registers from last intr */
} XZA_TGT_INTR_QUEUE;

#define SKZ_GET_NEXT_TGT_INTR(intr,ptr) \
(intr) = &(ptr)->reg;                   \
(ptr) = (ptr)->flink

/*
** XZA Channel Specific Structure
*/
typedef struct xza_channel {
	XZA_SCSI_TARGET		target[NDPS_8];
	XZA_STATE		state;
	
	SCSI_ID			scsi_id;
	u_char			chan_num;
	u_int			bus_num;

	vm_offset_t		xza_softc;
	SIM_SOFTC*		sim_softc;

	u_long			flags;

	ASR_REG			asr;

	u_long			commands_sent;
	u_long                  outstanding_ios;

	/* Data Structures for target mode operation
	   (Enabled LUNs) on the KZMSA */

	int tgt_intr_count;                /* Number of interrupts on queue */
	XZA_TGT_INTR_QUEUE *target_intr_head; /* Remove interrupts here */   
	XZA_TGT_INTR_QUEUE *target_intr_tail; /* Insert interrupts here */

	XZA_REG_CMD_QUEUE    *last_reg_cmd; /* Pointer into Histogram queue */ 
	XZA_TGT_LUN              lun[NLPT_8]; /* Number Luns Per Target = 8 */
	long             num_enabled_luns;  /* Number of Enabled LUNS */
	long           shutdown_registered; /* Register shutdown routine ? */

	/* Register emulation Histogram data & Target Interrupt Queue */

	XZA_REG_CMD_QUEUE reg_cmd_queue[SKZ_REG_CMD_QUEUE_SIZE];
	XZA_TGT_INTR_QUEUE tgt_intr_queue[SKZ_TGT_INTR_QUEUE_SIZE];

	simple_lock_data_t	lock;

} XZA_CHANNEL;

/*
** XZA Softc structure
*/
typedef struct xza_softc {

	caddr_t			csr;			/* XZA base_addr */
        vm_offset_t		xza_base;		/* ditto */

	XDEV_REG		xdev;			/* saved XDEV reg */

	XZA_REG_ADDRS		xza_reg_addrs;		/* Reg addresses */

	XZA_CHANNEL		channel[XZA_CHANNELS];

	AB*			ab;			/* adapter block */
	QB*			np_qb_pool;		/* q_buffer pool */
	CARRIER*		np_carrier_pool;	/* carrier pool  */

	SKZ_DME_SG_DSC*		dme_sg_dsc_pool;
	CARRIER*		dme_sg_dsc_car_pool;

	SKZ_ERR_BUF*		err_buf_pool;		/* error buffer pool */
	CARRIER*		err_buf_car_pool;	/* err buf carriers */

 	vm_offset_t		ampb_ptr;		/* virtual ampb ptr */
	CQIB*			cqib;			/* que insert block */
	u_int			ampb_size;		/* requested pages */

	NP_Q			ddfq;			/* driver free queue */
	NP_Q			ddsgq;	
	NP_Q			ddeq;			/* driver error que */
	NP_Q			ddefq;			/* error free que */
	
	unsigned short		xza_xmi_node;
	unsigned short		lamb_xmi_node;
	struct bus*		xza_bus;	/* CHECK!! ( controller?? */

	unsigned short		c0_misc_intr_vector;
	unsigned short		c1_misc_intr_vector;
	unsigned short		c0_tgt_intr_vector;
	unsigned short		c1_tgt_intr_vector;
	unsigned short		resp_intr_vector;

    	/*
	** Threads
	*/
	thread_t		resp_th;
	thread_t		error_th;

	NEXUS_ENTRY		setnex_mask;	/* mask field for SETNEX */
	EEPROM_FCN		eeprm_fcn;	/* EEPROM param settings */

	unsigned long		flags;

	simple_lock_data_t	lock;
} XZA_SOFTC;


/*
** Directories of controlling data structures, used for later lookup
** based on controller/bus number
*/
extern SIM_SOFTC* softc_directory[];

#define THIS_PAGE_ADDR( addr ) trunc_page ( addr )
#define NEXT_PAGE_ADDR( addr ) round_page ( addr + 1 )	/* always *next* page */

/*
** virtual to physical translations
*/
#define kvtop(kva,pa) svatophys(kva,pa)


/*
** Timing!!
*/
extern int hz;

/*
** Macros to help deal with threads
*/
#define skz_thread_wakeup(event,result) \
	thread_wakeup_prim((event), TRUE, (result))
#define skz_clear_wait(thread,result) \
	clear_wait((thread), (result), TRUE)

#define SKZ_IDLE_THREAD	(current_thread()->state & TH_IDLE)
#define SKZ_CHAN_THREADS_ACTIVE(xza_chan) (xza_chan->flags & SKZ_THREADS_ACTIVE)

#define SKZ_ALREADY_WAITING (current_thread()->wait_event != 0)

#define SKZ_SAVE_WAIT {					\
	wait_event = current_thread()->wait_event; 	\
	if ( wait_event != 0 )				\
		clear_wait(current_thread(), THREAD_INTERRUPTED, TRUE);	\
}

#define SKZ_RESTORE_WAIT {				\
	if ( wait_event != 0 )				\
		assert_wait((vm_offset_t)wait_event, TRUE );	\
}

/* Macro used to indicate polled operation is true */

#define SKZ_IN_POLLED_MODE(xza_softc) (!(xza_softc->flags & SKZ_INTERRUPT_ENABLE) || shutting_down)

/*
** Locking macros - handle IPL and SMP locks
*/
#define SPLMISC	SPLBIO
#define SPLRESP SPLBIO

#define SKZ_LOCK_INIT(lock) usimple_lock_setup ( &lock, cam_xza_target_li )

#define SKZ_LOCK(lock, s) { 		\
	s = splbio();			\
	simple_lock ( &lock );		\
}

#define SKZ_UNLOCK(lock, s) { 		\
	simple_unlock ( &(lock) );	\
	splx(s);			\
}

#endif /* SKZ_INCLUDE */






