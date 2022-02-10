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
 * @(#)$RCSfile: isp1020.h,v $ $Revision: 1.1.122.3 $ (DEC) $Date: 1998/12/04 20:14:28 $
 */
#ifndef _ISP1020_INCL_
#define _ISP1020_INCL_

#endif	/* _ISP1020_INCL_ */

/*
 * isp1020.h - Intelligent SCSI Processor DEC OSF/1 definitions 
 *
 * Created: January 25, 1994
 * Author:  Brian G. Nadeau
 *
 */

#define ISP_ERROR( sim_softc, text ) 				\
    CAM_ERROR (							\
	module,							\
	text,							\
	SIM_LOG_PRISEVERE,					\
	sim_softc,						\
	sim_softc->hba_sc,					\
	NULL 							\
    )
	
#if !defined( ISP_INCLUDE )
#define ISP_INCLUDE

/************************************************************************/
/************************************************************************/

#define ISP_MAX_TARGETS 16
#define ISP_MAX_LUNS 8
#define TM_SUPPORTED

/*
 * isp structs
 */

typedef struct isp_reg {
/* RISC Registers */
    vm_offset_t r_acc;
    vm_offset_t r_r1;
    vm_offset_t r_r2;
    vm_offset_t r_r3;
    vm_offset_t r_r4;
    vm_offset_t r_r5;
    vm_offset_t r_r6;
    vm_offset_t r_r7;
    vm_offset_t r_r8;
    vm_offset_t r_r9;
    vm_offset_t r_r10;
    vm_offset_t r_r11;
    vm_offset_t r_r12;
    vm_offset_t r_r13;
    vm_offset_t r_r14;
    vm_offset_t r_r15;
    vm_offset_t r_psr;
    vm_offset_t r_ivr;
    vm_offset_t r_pcr;
    vm_offset_t r_rar0;
    vm_offset_t r_rar1;
    vm_offset_t r_lcr;
    vm_offset_t r_pc;
    vm_offset_t r_mtr;
    vm_offset_t r_emb;
    vm_offset_t r_sp;
    vm_offset_t r_hrl;
    vm_offset_t r_hccr;
    vm_offset_t r_pb0;
    vm_offset_t r_pb1;
    vm_offset_t r_tcr;
    vm_offset_t r_tmr;

/* PCI Registers */
    vm_offset_t p_idlow;
    vm_offset_t p_idhigh;
    vm_offset_t p_icon0;
    vm_offset_t p_icon1;
    vm_offset_t p_icr;
    vm_offset_t p_isr;
    vm_offset_t p_semaphore;
    vm_offset_t p_nvram;
    vm_offset_t p_cdc_config;
    vm_offset_t p_cdc_control;
    vm_offset_t p_cdc_status;
    vm_offset_t p_cdc_fifostat;
    vm_offset_t p_cdc_trlow;
    vm_offset_t p_cdc_addrlow;
    vm_offset_t p_cdc_addrhigh;
    vm_offset_t p_ddc_config;
    vm_offset_t p_ddc_control;
    vm_offset_t p_ddc_status;
    vm_offset_t p_ddc_fifostat;
    vm_offset_t p_ddc_trlow;
    vm_offset_t p_ddc_trhigh;
    vm_offset_t p_ddc_addrlow;
    vm_offset_t p_ddc_addrhigh;
    vm_offset_t p_cfap;
    vm_offset_t p_dfap;

/* SXP Registers */
    vm_offset_t s_pic;
    vm_offset_t s_conf1;
    vm_offset_t s_conf2;
    vm_offset_t s_ip;
    vm_offset_t s_ra;
    vm_offset_t s_command;
    vm_offset_t s_interrupt;
    vm_offset_t s_sequence;
    vm_offset_t s_error;
    vm_offset_t s_exenable;
    vm_offset_t s_override;
    vm_offset_t s_lbase;
    vm_offset_t s_uflags;
    vm_offset_t s_bp;
    vm_offset_t s_scsiid;
    vm_offset_t s_devconf1;
    vm_offset_t s_devconf2;
    vm_offset_t s_phaseptr;
    vm_offset_t s_bufptr;
    vm_offset_t s_bufcnt;
    vm_offset_t s_buf;
    vm_offset_t s_bufbyte;
    vm_offset_t s_bufword;
    vm_offset_t s_bufwordtr;
    vm_offset_t s_q;
    vm_offset_t s_qstatus;
    vm_offset_t s_qtr;
    vm_offset_t s_qbr;
    vm_offset_t s_xreg;
    vm_offset_t s_tclow;
    vm_offset_t s_tchigh;
    vm_offset_t s_tcrlow;
    vm_offset_t s_arbdata;
    vm_offset_t s_conpins;
    vm_offset_t s_datapins;
    vm_offset_t s_diffpins;

/* Mailbox Registers */
    vm_offset_t mbox_in[6];
    vm_offset_t mbox_out[6];
} ISP_REG; 

typedef struct  isp_nvram
{
    U8		id[4];                          	/* "ISP " */
    U8        	version;
    U8        	fifo_threshold                  :2;     /* 0,1 */
    U8        	bios_disable                    :1;     /* 2 */
    U8        	host_adapter_enable             :1;     /* 3 */
    U8        	initiator_scsi_id               :4;     /* 4,5,6,7 */
    U8        	bus_reset_delay;
    U8        	retry_count;
    U8        	retry_delay;
    U8        	async_data_setup_time           :4;     /* 0,1,2,3 */
    U8        	req_ack_active_negation         :1;     /* 4 */
    U8        	data_line_active_negation       :1;     /* 5 */
    U8        	data_dma_burst_enable           :1;     /* 6 */
    U8        	command_dma_burst_enable        :1;     /* 7 */
    U8        	tag_age_limit;
    U8        	low_term_enable                 :1;     /* 0 */
    U8        	hi_term_enable                  :1;     /* 1 */
    U8        	pcmc_burst_enable               :1;     /* 2 */
    U8        	enable_60_mhz                   :1;     /* 3 */
    U8        	scsi_reset_disable              :1;     /* 4 */
    U8        	enable_auto_term                :1;     /* 5 */
    U8        	fifo_threshold_128              :1;     /* 6 */
    U8        	auto_term_support               :1;     /* 7 */
    U16       	selection_timeout;
    U16       	max_queue_depth;
    U8          scsi_bus_size                   :1;     /* 0 */
    U8          scsi_bus_type                   :1;     /* 1 */
    U8          adapter_clock_speed             :1;     /* 2 */
    U8          software_term_support           :1;     /* 3 */
    U8          flash_on_board                  :1;     /* 4 */
    U8          oem_field                       :3;     /* 5,6,7 */

    U8          apple_connector_1               :1;     /* 0 */
    U8          apple_connector_2               :1;     /* 1 */
    U8          apple_connector_3               :1;     /* 2 */
    U8          apple_unused                    :5;     /* 3,4,5,6,7 */
    U16         subsystem_id_lsw;
    U16         subsystem_id_msw;
    U16         fast_memory_timing_enable       :1;     /* 0 */
    U16         system_parameter_unused         :15;    /* 1 - 15 */

    U16        	pad[2];       

    struct
    {
        U8          renegotiate_on_error    :1;     /* 0 */
        U8          stop_queue_on_check     :1;     /* 1 */
        U8          auto_request_sense      :1;     /* 2 */
        U8          tagged_queuing          :1;     /* 3 */
        U8          sync_data_transfers     :1;     /* 4 */
        U8          wide_data_transfers     :1;     /* 5 */
        U8          parity_checking         :1;     /* 6 */
        U8          disconnect_allowed      :1;     /* 7 */
        U8          execution_throttle;
        U8          sync_period;
        U8          sync_offset             :4;     /* 0,1,2,3 */
        U8          device_enable           :1;     /* 4 */
	U8          lun_disable             :1;     /* 5 */
        U8          not_used                :2;     /* 6,7 */

        U8          available0;
        U8          available1;
    } target[16];

    U8        pad1[3];        
    U8        check_sum;
} ISP_NVRAM;

/* driver specific queue handling */

#define DAIP isp_softc->request_info.ip
#define DAOP isp_softc->request_info.op
#define ADIP isp_softc->response_info.ip
#define ADOP isp_softc->response_info.op

typedef struct isp_queue_info {
    int			depth;		/* max entries */
    int			ip;		/* in-pointer (index) */
    int			op;		/* out-pointer (index) */
    dma_handle_t	dmahandle; 	/* dma handle */
    sg_entry_t		sgentry;  	/* only 1 entry (must be contig) */
} ISP_QUEUE_INFO;

#define ISP_DMA_MAX_SEGMENTS 128	/* 1 MB @ 8192 bytes per seg */

typedef struct isp_job_q {
    struct isp_job *	flink;
    struct isp_job *	blink;
} ISP_JOB_Q;

#define ISP_MAX_DMA_HANDLES 128

typedef struct more_isp_dma_handles {
    long		flags;
    dma_handle_t	isp_dma_handle[ISP_MAX_DMA_HANDLES];
} MORE_ISP_DMA_HANDLES;

typedef struct isp_job {
    struct isp_job *		flink;
    struct isp_job *		blink;
    U32				handle;
    U32				flags;
    SIM_WS *			sws;
    long			lbolt;
    dma_handle_t		single_isp_dma_handle;
    MORE_ISP_DMA_HANDLES *	multiple_isp_dma_handles;
} ISP_JOB;

#define ISP_SETUP_JOB( job, addr, lbolt ) {			\
    (job)->flink 	= (struct isp_job *)0;			\
    (job)->blink 	= (struct isp_job *)0;			\
    (job)->handle	= (U32)0;				\
    (job)->flags	= (U32)0;				\
    (job)->sws		= (SIM_WS *)(addr);			\
    (job)->lbolt	= (long)(lbolt);			\
    (job)->single_isp_dma_handle    = (dma_handle_t)0;		\
    (job)->multiple_isp_dma_handles = (MORE_ISP_DMA_HANDLES *)0;\
}

typedef struct isp_free_memory {
    struct isp_free_memory *	flink;
    struct isp_free_memory *	blink;
    char	           *	addr;
    u_int			size;
} ISP_FREE_MEMORY;

typedef struct isp_free_memory_q {
    struct isp_free_memory *	flink;
    struct isp_free_memory *	blink;
} ISP_FREE_MEMORY_Q;

typedef struct isp_mail {
    U16	cmd_reg[6];
    U16	status_reg[6];
    int nreg_in;
    int nreg_out;
    long initial_delay; /* microseconds to delay before initial read */
    long delay;		/* microseconds to delay between reads */
    long start_lbolt;
    long end_lbolt;
    long start_rpcc;
    long end_rpcc;
} ISP_MAIL;

#define ISP_MAXSPARE 20
typedef struct isp_softc {
    /* 
     * Driver specific 
     */
    SIM_SOFTC *		sim_softc;	/* pointer to that other softc */
    int 		flags;		/* isp flags */
    int 		state;		/* isp state */
    int                 rq_process_signal;
    int                 abort_process_signal;
    int                 fm_process_signal;
    int			fm_count;	/* number of free memory queue entries */
    ISP_FREE_MEMORY_Q   free_memory;    /* list of free memory blocks to be deallocated */
    ISP_JOB_Q 		jobs;		/* outstanding requests */
    ISP_JOB *		jspare[ISP_MAXSPARE];
    int			spares;
    int			reinits;
    int			reinit_code;
    struct pci_config_hdr * pci_cnfg_hdr;
    struct controller * isp_ctlr;	/* saved for dma mapping */
    struct bus *	isp_bus;	/* pointer to our bus info */

    /*
     * ISP queue handling 
     */
    struct isp_queue * 	request_queue;	/* New requests to chip */
    struct isp_squeue *	response_queue; /* Responses from chip */
    struct isp_queue_info request_info; 	/* Request Queue Information */
    struct isp_queue_info response_info; 	/* Response Queue Information */
    U32			next_handle;	/* next handle ID */

    /*
     * PCI/DMA/INTERRUPT
     */
    ISP_REG		isp_reg;	/* PCI Register Addresses */
    vm_offset_t		isp_base;	/* PCI Base Address */
    vm_offset_t		pci_base;	/* PCI Base Address */
    ihandler_id_t	*hid;		/* interrupt handler id */
    u_long		maxiosize;	/* max dma size */
    dma_handle_t	*dma_handle_p;	/* dma handle */
    int			dma_flags;	/* dma flags */
    int			cache_line_size;

    /*
     * firmware loading
     */
    dma_handle_t        fw_dmahandle;
    sg_entry_t          fw_sg;


    /*
     * isp statistics 
     */
    long		reset_stats;
    long		num_io_completed;
    long		lbolt_total;
    long		interrupts;
    long		abort_count;
    long		setup_failures;
    long		async_events_received;
    long		last_async_event;
    long                bogus_response_count;

    /*
     * nvram (should be aligned on U16 boundry)
     */
    ISP_NVRAM		nvram;

    /*
     * Mailbox handling
     */
    int                 mailbox_semaphore;
    int                 mailbox_status;
    int                 mailbox_errors;
    ISP_MAIL            mail;

    /*
     * Path Inquiry info
     */
    int                 firmware_major;
    int                 firmware_minor;
    int                 firmware_version;

    /*
     * Abort failure retry mitigation.
     */
    ISP_JOB_Q 		abort_queue;		/* jobs to be aborted */
    SIM_WS *            last_sws_aborted;
    int                 abort_retry_count;

    /* 
     * LOCKING
     */
    simple_lock_data_t	chiplock;	/* smp locking */
    simple_lock_data_t	abort_lock;	/* smp locking */

} ISP_SOFTC;

#define ISP_SEND( isp_softc, mail ) {					\
    int i;								\
    for( i=0; i < mail->nreg_in; i++ ) {				\
	Qprintf2("mbox[%d] = 0x%x\n", i, mail->cmd_reg[i]); 		\
	ISP_WCSR16( isp_softc->isp_reg.mbox_in[i], mail->cmd_reg[i] );	\
    }									\
    mb();								\
}

#define ISP_RECEIVE( isp_softc, mail) {					\
    int i;								\
    for( i=0; i < 6; i++ ) {	                         		\
	mail->status_reg[i] = ISP_RCSR16( isp_softc->isp_reg.mbox_out[i] );   	\
	Qprintf2("mbox[%d] = 0x%x\n", i, mail->status_reg[i]); 		\
    }									\
    mb();								\
}

/*
 * isp dma settings
 */
#define ISP_MAX_TRANSFER_SIZE 1024*1024

/*						     v debug         v debug   */
#define ISP_DMA_FLAGS (DMA_IN|DMA_OUT|DMA_ALL)

/*
 * isp flags
 */
#define ISP_INTERRUPT_ENABLE	0x00000001
#define ISP_NO_RETURN           0x00000002
#define ISP_TARGET_ENABLED	0x00000004
#define ISP_QUEUES_INITIALIZED  0x00000008
#define ISP_BOGUS_RESPONSE      0x00000010
#define ISP_NO_REINIT           0x00000020
#define ISP_DIFFERENTIAL        0x00000040
#define ISP_FAST20_CAPABLE      0x00000080
#define ISP_BUSTED_FIFO         0x00000100
#define ISP_PROBE               0x00000200
#define ISP_SHARED_INTERRUPTS   0x00000400
#define ISP_NVRAM_INVALID       0x00000800

/*
 * isp state
 */
#define ISP_ALIVE               0x00000001
#define CHIP_RESET_IN_PROG      0x00000002
#define BUS_RESET_IN_PROG       0x00000004
#define DEVICE_RESET_IN_PROG    0X00000008
#define ENABLE_TARGET_IN_PROG	0x00000010  /* Set if ISP has been
					     * enabled for selections
					     */
#define CMD_RING_LOCK           0x00000020
#define ABORT_IN_PROG           0x00000040
#define FM_THREAD_RUNNING       0x00000080
#define REINIT_SCHEDULED        0x00000100
#define RQ_THREAD_RUNNING       0x00000200
#define ABORT_THREAD_RUNNING    0x00000400
#define W4_CONTINUE		0x00000800  /* Waiting for "continue" CCB
					       to complete */

/*
 * isp job flags
 */
#define JOB_INVALIDATED		0x00000001
 
/*
 * driver routine return values 
 *
 */
#define ISP_SUCCESS		0x00000000
#define ISP_BUSY 		0x00000001
#define ISP_MBOXEMPTY		0x00000002
#define ISP_DRIVERERROR		0x00000003
#define ISP_MEMALLOCFAIL        0x00000004
#define ISP_FAILURE		0x0000ffff

/*
 * generic isp locking
 *
 */

#define ISP_LOCK_INIT( lockname ) { 					\
	usimple_lock_setup( &lockname, cam_isp_li );			\
}									\

#define ISP_LOCK_FAST( lockname ) {					\
	usimple_lock( &lockname );					\
}									\

#define ISP_LOCK( lockname, s ) {					\
	s = splbio();							\
	usimple_lock( &lockname );					\
}									\

#define ISP_UNLOCK_FAST( lockname ) {					\
	usimple_unlock( &lockname );					\
}									\

#define ISP_UNLOCK( lockname, s ) {					\
	usimple_unlock( &lockname );					\
	splx( s );							\
}									\

#endif

/*
 * Intelligent SCSI Processor chip ISP1020 definitions 
 *
 * Created: January 25, 1994
 * Author:  Brian G. Nadeau
 *
 */

/*
 * Index:
 *
 * PART 1 - Registers, Bit Masks
 *    RISC Registes
 *    PCI Registers
 *    SXP Registers
 *
 * PART 2 - Firmware Interface
 *    Mailbox Commands Directory
 *    Mailbox Flags
 *    Queue Definitions
 *
 * PART 3 - Firmware Image
 */

#define BIT0	0x00000001
#define BIT1	0x00000002
#define BIT2	0x00000004
#define BIT3	0x00000008
#define BIT4	0x00000010
#define BIT5	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9	0x00000200
#define BIT10	0x00000400
#define BIT11	0x00000800
#define BIT12	0x00001000
#define BIT13	0x00002000
#define BIT14	0x00004000
#define BIT15	0x00008000
#define BIT16	0x00010000
#define BIT17	0x00020000
#define BIT18	0x00040000
#define BIT19	0x00080000
#define BIT20	0x00100000
#define BIT21	0x00200000
#define BIT22	0x00400000
#define BIT23	0x00800000
#define BIT24	0x01000000
#define BIT25	0x02000000
#define BIT26	0x04000000
#define BIT27	0x08000000
#define BIT28	0x10000000
#define BIT29	0x20000000
#define BIT30	0x40000000
#define BIT31	0x80000000

/************************************************************************/
/* PART 1
/************************************************************************/

/*
 * RISC Register File - PCI Base Address Offsets
 *
 * Block 1 (00-0F) - General Purpose (GP)
 * Block 2 (10-1F) - Hardware Control (HC)
 * Block 3 (20-22) - Host Configuration and Control
 *
 */
/* Block 1 - Definitions for bank0, bank1, bank2, bank3 */
#define RISC_ACC  0x080	/* Accumulator 			Register 0x00 */
#define RISC_R1   0x082	/* General Purpose 		Register 0x01 */
#define RISC_R2   0x084	/* General Purpose 		Register 0x02 */
#define RISC_R3   0x086	/* General Purpose 		Register 0x03 */
#define RISC_R4   0x088	/* General Purpose 		Register 0x04 */
#define RISC_R5   0x08a	/* General Purpose 		Register 0x05 */
#define RISC_R6   0x08c	/* General Purpose 		Register 0x06 */
#define RISC_R7   0x08e	/* General Purpose 		Register 0x07 */
#define RISC_R8   0x090	/* General Purpose 		Register 0x08 */
#define RISC_R9   0x092	/* General Purpose 		Register 0x09 */
#define RISC_R10  0x094	/* General Purpose 		Register 0x0a */
#define RISC_R11  0x096	/* General Purpose 		Register 0x0b */
#define RISC_R12  0x098	/* General Purpose 		Register 0x0c */
#define RISC_R13  0x09a	/* General Purpose 		Register 0x0d */
#define RISC_R14  0x09c	/* General Purpose 		Register 0x0e */
#define RISC_R15  0x09e	/* General Purpose 		Register 0x0f */

/* Block 2 */
#define RISC_PSR  0x0a0	/* Processor Status		Register 0x10 */
#define RISC_IVR  0x0a2	/* Interrupt Vector		Register 0x11 */
#define RISC_PCR  0x0a4	/* Processor Control		Register 0x12 */
#define RISC_RAR0 0x0a6	/* RAM Address 0		Register 0x13 */
#define RISC_RAR1 0x0a8	/* RAM Address 1		Register 0x14 */
#define RISC_LCR  0x0aa	/* Loop Count			Register 0x15 */
#define RISC_PC   0x0ac	/* Program counter		Register 0x16 */
#define RISC_MTR  0x0ae	/* Memory Timing		Register 0x17 */
#define RISC_EMB  0x0b0	/* External Memory Boundary 	Register 0x18 */
#define RISC_SP   0x0b2	/* Stack Pointer		Register 0x19 */
			/* Reserved Space Start		Register 0x1a */
			/* Reserved Space End		Register 0x1e */
#define RISC_HRL  0x0be	/* Hardware Revision Level	Register 0x1f */

/* Block 3 */
#define RISC_HCCR 0xc0  /* Host Command and control V3 */
#define RISC_PB0  0xc2	/* Processor Breakpoint 0 */
#define RISC_PB1  0xc4	/* Processor Breakpoint 1 */
#define RISC_TCR  0xc6	/* Test Control */
#define RISC_TMR  0xc8	/* Test Mode */


/* Register Bit Fields */
/* PSR */

#define PSR_ALWAYS_TRUE			BIT15
#define PSR_LOOP_COUNT_DONE		BIT14
#define PSR_RISC_INTERRUPT		BIT13
#define PSR_TIMER_ROLLOVER_FLAG		BIT12
#define PSR_ALU_OVERFLOW		BIT11
#define PSR_ALU_MSB			BIT10
#define PSR_ALU_CARRY			BIT9
#define PSR_ALU_ZERO			BIT8
#define PSR_RESERVED			(BIT7|BIT6)
#define PSR_60MHZ_ENABLE                BIT5
#define PSR_DMA_INTERRUPT_STATUS 	BIT4
#define PSR_SCSI_INTERRUPT_STATUS	BIT3
#define PSR_HOST_INTERRUPT_STATUS	BIT2
#define PSR_INTERRUPT_PENDING		BIT1
#define PSR_ALWAYS_FALSE		BIT0

typedef struct psr_reg {
	U16	false		: 1;
	U16	int_pending	: 1;
} PSR_REG;

/* PCR */
#define PCR_COMMAND_FIELD		(BIT15|BIT14|BIT13|BIT12)
#define PCR_RESERVED1			(BIT11|BIT10)
#define PCR_REGISTER_FILE_BANK_SELECT	(BIT9|BIT8)
#define PCR_CONTROL_BIT			BIT7
#define PCR_RESERVED2			(BIT6|BIT5|BIT4)
#define PCR_INTERRUPT_ENABLES		(BIT3|BIT2|BIT1|BIT0)

/* LCR */
#define LCR_0				BYTE1
#define LCR_LOOP_COUNT			BYTE0

/* MTR */
#define MTR_WRITE_TIMING_1		(BIT15|BIT14|BIT13|BIT12) 
#define MTR_READ_TIMING_1		(BIT11|BIT10|BIT9|BIT8)
#define MTR_WRITE_TIMING_0		(BIT7|BIT6|BIT5|BIT4)
#define MTR_READ_TIMING_0		(BIT3|BIT2|BIT1|BIT0)

/* HCCR */
#define HCCR_COMMAND_FIELD		(BIT15|BIT14|BIT13|BIT12)
#define HCCR_RESET_RISC			(HCCR_COMMAND_FIELD&(1 << 12))
#define HCCR_PAUSE_RISC			(HCCR_COMMAND_FIELD&(2 << 12))
#define HCCR_RELEASE_RISC		(HCCR_COMMAND_FIELD&(3 << 12))
#define HCCR_SINGLE_STEP_RISC		(HCCR_COMMAND_FIELD&(4 << 12))
#define HCCR_SET_HOST_INTERRUPT		(HCCR_COMMAND_FIELD&(5 << 12))
#define HCCR_CLEAR_HOST_INTERRUPT	(HCCR_COMMAND_FIELD&(6 << 12))
#define HCCR_CLEAR_RISC_INTERRUPT	(HCCR_COMMAND_FIELD&(7 << 12))
#define HCCR_WRITE_PB_ENABLES		(HCCR_COMMAND_FIELD&(8 << 12))
#define HCCR_WRITE_BIOS_ENABLE		(HCCR_COMMAND_FIELD&(9 << 12))
#define HCCR_SET_TEST_MODE		(HCCR_COMMAND_FIELD&(F << 12))
#define HCCR_RESERVED1			(BIT11|BIT10|BIT9|BIT8)
#define HCCR_HOST_INTERRUPT		BIT7
#define HCCR_RESET			BIT6
#define HCCR_PAUSE_MODE			BIT5
#define HCCR_EXTERNAL_BREAKPOINT_ENABLE	BIT4
#define HCCR_BREAKPOINT1_ENABLE		BIT3
#define HCCR_BREAKPOINT0_ENABLE		BIT2
#define HCCR_ENABLE_INTERRUPT_ON_BREAKPOINT BIT1
#define HCCR_BIOS_ENABLE		BIT0

/*
 * PCI Registers
 *
 */

/*
 * PCI Bus Interface Registers 
 *
 * see io/dec/pci/pci.h for Bus Configuration Registers
 *
 * Note: This address space is not the same as the configuration space.
 *	(It better not be anyway...)
 */
#define PCI_ID_LOW			0x000
#define PCI_ID_HIGH			0x002
#define ISP_CONFIGURATION_0		0x004
#define ISP_CONFIGURATION_1		0x006
#define PCI_INTERFACE_CONTROL		0x008
#define PCI_INTERFACE_STATUS		0x00A
#define PCI_SEMAPHORE			0x00C
#define PCI_NONVOLATILE_RAM		0x00E

/* Register Bit Fields */
/* ISP Configuration 1 Register */
#define ISP1_RESERVED			(BYTE1)
#define ISP1_XTENDED_FIFO_THRESHOLD_CONTROL	(BIT7|BIT6|BIT5|BIT4)
#define ISP1_FIFO_THRESHOLD_128		BIT6
#define ISP1_SXP_REGISTER_SELECT	BIT3
#define ISP1_BURST_ENABLE		BIT2
#define ISP1_FIFO_THRESHOLD_CONTROL	(BIT1|BIT0)

/* PCI Interface Control Register */
#define PICR_RESERVED			(BYTE1|BIT7|BIT6)
#define PICR_ENABLE_DATA_DMA_CHANNEL_INTERRUPT 		BIT5
#define PICR_ENABLE_COMMAND_DMA_CHANNEL_INTERRUPT 	BIT4
#define PICR_ENABLE_SXP_INTERRUPT	BIT3
#define PICR_ENABLE_RISC_INTERRUPT	BIT2
#define PICR_ENABLE_ALL_PCI_INTERRUPTS	BIT1
#define PICR_ISP1020_SOFT_RESET		BIT0

/* PCI Interface Status Register */
#define PISR_RESERVED1			(BYTE1|BIT7|BIT6)
#define PISR_DATA_DMA_CHANNEL_INTERRUPT		BIT5
#define PISR_COMMAND_DMA_CHANNEL_INTERRUPT 	BIT4
#define PISR_SXP_INTERRUPT		BIT3
#define PISR_RISC_INTERRUPT		BIT2
#define PISR_PCI_INTERRUPT		BIT1
#define PISR_RESERVED2			BIT0

/* PCI Semaphore Register */
#define SEMAPHORE_RESERVED		(BYTE1|BIT7|BIT6|BIT5|BIT4|BIT3)
#define SEMAPHORE_STATUS_BIT		BIT1
#define SEMAPHORE_LOCK_BIT		BIT0

/* PCI Nonvolatile RAM Interface Register */
#define NVRAM_RESERVED			(BYTE1|BIT7|BIT6|BIT5|BIT4)
#define NVRAM_DATA_IN			BIT3
#define NVRAM_DATA_OUT			BIT2
#define NVRAM_CHIP_SELECT		BIT1
#define NVRAM_CLOCK			BIT0


/*
 * PCI DMA Controller Registers - Command DMA Channel
 *
 */
#define CDC_CONFIGURATION		0x020
#define CDC_CONTROL			0x022
#define CDC_STATUS			0x024
#define CDC_FIFO_STATUS			0x026
#define CDC_TRANSFER_COUNTER_LOW 	0x028
#define CDC_RESERVED			0x02A
#define CDC_ADDRESS_COUNTER_LOW		0x02C
#define CDC_ADDRESS_COUNTER_HIGH	0x02E

/*
 * PCI DMA Controller Registers - Data DMA Channel
 *
 */
#define DDC_CONFIGURATION		0x040
#define DDC_CONTROL			0x042
#define DDC_STATUS			0x044
#define DDC_FIFO_STATUS			0x046
#define DDC_TRANSFER_COUNTER_LOW  	0x048
#define DDC_TRANSFER_COUNTER_HIGH 	0x04a
#define DDC_ADDRESS_COUNTER_LOW		0x04c
#define DDC_ADDRESS_COUNTER_HIGH  	0x04e

/*
 * PCI DMA Controller Registers - DMA FIFO Access Ports
 *
 */
#define DFAP_COMMAND_FIFO_ACCESS_PORT  	0x060
#define DFAP_DATA_FIFO_ACCESS_PORT	0x062

/*
 * PCI Mailbox Registers V3
 *
 */
#define PCI_ISP_INCOMING_MAILBOX_0	0x070
#define PCI_ISP_INCOMING_MAILBOX_1	0x072
#define PCI_ISP_INCOMING_MAILBOX_2	0x074
#define PCI_ISP_INCOMING_MAILBOX_3	0x076
#define PCI_ISP_INCOMING_MAILBOX_4	0x078
#define PCI_ISP_INCOMING_MAILBOX_5	0x07a
#define PCI_ISP_OUTGOING_MAILBOX_0	0x070
#define PCI_ISP_OUTGOING_MAILBOX_1	0x072
#define PCI_ISP_OUTGOING_MAILBOX_2	0x074
#define PCI_ISP_OUTGOING_MAILBOX_3	0x076
#define PCI_ISP_OUTGOING_MAILBOX_4	0x078
#define PCI_ISP_OUTGOING_MAILBOX_5	0x07a


/*
 * SCSI Executive Processor SXP Registers - PCI Base Address Offsets
 *
 */
#define SXP_PART_ID_CODE		0x080
#define SXP_CONFIGURATION_1		0x082
#define SXP_CONFIGURATION_2		0x084
#define SXP_CONFIGURATION_3		0x086
#define SXP_INSTRUCTION_POINTER		0x08c
#define SXP_RETURN_ADDRESS		0x090
#define SXP_COMMAND			0x094
#define SXP_INTERRUPT			0x098
#define SXP_SEQUENCE			0x09c
#define SXP_GROSS_ERROR			0x09e
#define SXP_EXCEPTION_ENABLE		0x0a0
#define SXP_OVERRIDE			0x0a4
#define SXP_LITERAL_BASE		0x0a8
#define SXP_USER_FLAGS			0x0ac
#define SXP_USER_EXCEPTION		0x0b0
#define SXP_BREAKPOINT			0x0b4
#define SXP_SCSI_ID			0x0c0
#define SXP_SCSI_DEVICE_CONFIGURATION_1	0x0c2
#define SXP_SCSI_DEVICE_CONFIGURATION_2	0x0c4
#define SXP_SCSI_PHASE_POINTER		0x0c8
#define SXP_SCSI_BUFFER_POINTER	 	0x0cc
#define SXP_SCSI_BUFFER_COUNTER		0x0d0
#define SXP_SCSI_BUFFER			0x0d2
#define SXP_SCSI_BUFFER_BYTE		0x0d4
#define SXP_SCSI_BUFFER_WORD		0x0d6
#define SXP_SCSI_BUFFER_WORD_TRANSLATE	0x0d8
#define SXP_SCSI_FIFO			0x0da
#define SXP_SCSI_FIFO_STATUS		0x0dc
#define SXP_SCSI_FIFO_TOP_RESIDUE	0x0de
#define SXP_SCSI_FIFO_BOTTOM_RESIDUE	0x0e0
#define SXP_SCSI_TRANSFER_REGISTER	0x0e4
#define SXP_XREG SXP_SCSI_TRANSFER_REGISTER
#define SXP_SCSI_TRANSFER_COUNT_LOW	0x0e8
#define SXP_SCSI_TRANSFER_COUNT_HIGH	0x0ea
#define SXP_SCSI_TRANSFER_COUNTER_LOW	0x0ec
#define SXP_SCSI_TRANSFER_COUNTER_HIGH	0x0ee
#define SXP_SCSI_ARBITRATION_DATA	0x0f0
#define SXP_SCSI_CONTROL_PINS		0x0f2
#define SXP_SCSI_DATA_PINS		0x0f4
#define SXP_SCSI_DIFFERENTIAL_PINS	0x0f6


/* SXP Bit fields */
/* Configuration 1-3 Registers */
#define CMD1_ASYNC_SETUP		(BIT15|BIT14|BIT13|BIT12)
#define CMD1_SELECTION_TIME_LIMIT	BIT11
#define CMD1_SELECTION_TIMOUT		(BIT10|BIT9)
#define CMD1_RESERVED1			BIT8
#define CMD1_CLOCK_FACTOR		(BIT7|BIT6|BIT5)
#define CMD1_RESERVED2			BIT4
#define CMD1_SCSI_ID			(BIT3|BIT2|BIT1|BIT0)

#define CMD2_RESERVED1					(BYTE1|BIT7)
#define CMD2_DISABLE_FILTER				BIT6
#define CMD2_ENABLE_SCSI_REQ_ACK_ACTIVE_PULLUPS		BIT5
#define CMD2_ENABLE_SCSI_DATA_ACTIVE_PULLUPS		BIT4
#define CMD2_ENABLE_DEVICE_CONFIGURATION_AUTOLOAD	BIT3
#define CMD2_RESERVED2					BIT2
#define CMD2_ENABLE_RESELECTION				BIT1
#define CMD2_ENABLE_SELECTION				BIT0

#define CMD3_ENABLE_FUNCTION_ABORT_ON_SCSI_PARTIY_ERROR	BIT15
#define CMD3_RESERVED1					BIT14
#define CMD3_ENABLE_FUNCTION_ABORT_ON_ATN_CHANGE	BIT13
#define CMD3_ENABLE_FUNCTION_ABORT_ON_NONDATA		BIT12
#define CMD3_ENABLE_FUNCTION_ABORT_ON_DATA_PHASE	BIT11
#define CMD3_ENABLE_FUNCTION_ABORT_ON_FIFO_NOT_EMPTY	BIT10
#define CMD3_ENABLE_FUNCTION_ABORT_ON_GROSS_ERROR	BIT9
#define CMD3_RESERVED2			(BIT8|BIT7|BIT6|BIT5|BIT4)
#define CMD3_ENABLE_HALT_ON_GROSS_ERROR			BIT3
#define CMD3_ENABLE_HALT_ON_ATN_CHANGE			BIT2
#define CMD3_RESERVED3					BIT1
#define CMD3_ENABLE_HALT_ON_SCSI_PARITY_ERROR		BIT0

/* Instruction Pointer Register */
#define IPR_RESERVED1			BYTE1
#define IPR_INSTRUCTION_POINTER		BYTE0

/* Return Address Register */
#define RAR_RESERVED			BYTE1
#define RAR_INSTRUCTION_POINTER		BYTE0

/* Interrupt Register */
#define IR_PARTY_ERROR			BIT15
#define IR_GROSS_ERROR			BIT14
#define IR_FUNCTION_ABORT		BIT13
#define IR_CONDITION_FAILED		BIT12
#define IR_FIFO_EMPTY			BIT11
#define IR_BUFFER_COUNTER_ZERO		BIT10
#define IR_TRANSFER_COUNTER_ZERO	BIT9
#define IR_RESERVED1			BIT8
#define IR_INTERRUPT_PENDING		BIT7
#define IR_COMMAND_EXECUTING		BIT6
#define IR_RESERVED2			(BIT5|BIT4)
#define IR_INTERRUPT_RETURN_CODE	(BIT3|BIT2|BIT1|BIT0)

/* Sequence Register */
#define SR_SEQUENCE_BITS		(BYTE1|BIT7|BIT6|BIT5)
#define SR_SEQUENCE_COUNTER		(BIT4|BIT3|BIT2|BIT1|BIT0)

/* Gross Error Register */
#define GER_RESERVED			(BYTE1|BIT7)
#define GER_OFFSET_RESIDUE		BIT6
#define GER_OFFSET_UNDERFLOW		BIT5
#define GER_OFFSET_OVERFLOW		BIT4
#define GER_FIFO_UNDERFLOW		BIT3
#define GER_FIFO_OVERFLOW		BIT2
#define GER_REGISTER_WRITE_ERROR	BIT1
#define GER_ILLEGAL_INSTRUCTION		BIT0

/* Exception Enable Register */
#define GER_USER_EXCEPTION_0_ENALBE	BIT15
#define GER_USER_EXCEPTION_1_ENABLE	BIT14
#define GER_RESERVED1			(BIT13|BIT12|BIT11|BIT10)
#define GER_INITIATOR_MODE_BUS_FREE	BIT9
#define GER_TARGET_MODE_ATTENTION	BIT8
#define GER_RESELECTED			BIT7
#define GER_SELECTED			BIT6
#define GER_ARBITRATION			BIT5
#define GER_GROSS_ERROR_VECTOR_ENABLE	BIT4
#define GER_SCSI_BUS_RESET		BIT3
#define GER_RESERVED2			(BIT2|BIT1|BIT0)

/* Override Register */
#define OR_EXTERNAL_TRIGGER_ENALBE	BIT15
#define OR_PAUSE_SINGLE_STEP		BIT14
#define OR_BREAKPOINT_ENABLE		BIT13
#define OR_SCSI_PIN_WRITE_ENABLE	BIT12
#define OR_FORCE_SCSI_OUTPUT		BIT11
#define OR_SCSI_HANDSHAKE_LOOPBACK	BIT10
#define OR_PARITY_TEST_MODE		BIT9
#define OR_TRISTATE_SCSI_ENABLE_PINS	BIT8
#define OR_TRISTATE_SCSI_PINS		BIT7
#define OR_RESERVED1			(BIT6|BIT5|BIT4)
#define OR_SCSI_FIFO_RESET		BIT3
#define OR_SXP_COMMAND_TERMINATE	BIT2
#define OR_SXP_REGISTER_RESET		BIT1
#define OR_SXP_MODULE_RESET		BIT0

/* Literal Base Register */
#define LBR_RESERVED1			(BIT15|BIT14|BIT13|BIT12|BIT11|BIT10|BIT9)
#define LBR_LITERAL_BASE		(BIT8|BIT7|BIT6|BIT5|BIT4)
#define LBR_RESERVED			(BIT3|BIT2|BIT1|BIT0)

/* User Exception Register */
#define UER_RESERVED1			(BYTE1|BIT7|BIT6|BIT5|BIT4|BIT3|BIT2)
#define UER_USER_EXCEPTION_1		BIT1
#define UER_USER_EXCEPTION_0		BIT0

/* Breakpoint Register */
#define BP_RESERVED			BYTE1
#define BP_BREAKPOINT_ADDRESS		BYTE0

/* SCSI ID Register */
#define SIDR_RESERVED1			(BIT15|BIT14|BIT13|BIT12)
#define SIDR_SELECTING_IO		(BIT11|BIT10|BIT9|BIT8)
#define SIDR_RESERVED2			(BIT7|BIT6|BIT5|BIT4)
#define SIDR_SELECT_ID			(BIT3|BIT2|BIT1|BIT0)

/* SCSI Device Configuration 1 Register */
#define SDC1_RESERVED1			BIT15
#define SDC1_SYNC_DATA_HOLD		(BIT14|BIT13|BIT12)
#define SDC1_SYNC_DATA_SETUP		(BIT11|BIT10|BIT9|BIT8)
#define SDC1_RESERVED2			(BIT7|BIT6|BIT5|BIT4)
#define SDC1_SYNC_OFFSET		(BIT3|BIT2|BIT1|BIT0)

/* SCSI Device Configuration 2 Register */
#define SDC2_DEVICE_FLAG		(BIT15|BIT14|BIT13|BIT12)
#define SDC2_RESERVED1			(BIT11|BIT10|BIT9|BIT8|BIT7)
#define SDC2_WIDE_SCSI			BIT6
#define SDC2_ENABLE_SCSI_PARITY_CHECK	BIT5
#define SDC2_BLOCK_MODE_TRANSFER_COUNTER BIT4
#define SDC2_RESERVED2			BIT3
#define SDC2_ASSERTION_PERIOD		(BIT2|BIT1|BIT0)

/* SCSI Phase Pointer Register */
#define SPPR_RESERVED1			(BIT15|BIT14|BIT13)
#define SPPR_STATUS_BUFFER_POINTER	BIT12
#define SPPR_RESERVED2			BIT11
#define SPPR_MESSAGE_IN_POINTER		(BIT10|BIT9|BIT8)
#define SPPR_COMMAND_BUFFER_POINTER	(BIT7|BIT6|BIT5|BIT4)
#define SPPR_RESERVED3			BIT3
#define SPPR_MESSAGE_OUT_BUFFER_POINTER (BIT2|BIT1|BIT0)

/* SCSI Buffer Pointer Register */
#define SBPR_RESERVED			(BIT15|BIT14|BIT13|BIT12|BIT11|BIT9)
#define SBPR_BUFFER_POINTER		(BIT9|BIT8|BYTE0)

/* SCSI Buffer Counter Register */
#define SBCR_RESERVED			(BYTE1|BIT7|BIT6|BIT5|BIT4)
#define SBCR_BUFFER_COUNTER		(BIT3|BIT2|BIT1|BIT0)

/* SCSI FIFO Status Register */
#define SFSR_TOP_RESIDUE_FULL		BIT15
#define SFSR_ACK_RESIDUE		BIT14
#define SFSR_RESERVED \
	(BIT13|BIT12|BIT11|BIT10|BIT9|BIT8|BIT7|BIT6|BIT5)
#define SFSR_WORD_COUNT			(BIT4|BIT3|BIT2|BIT1)
#define SFSR_BOTTOM_RESIDUE_FULL	BIT0

/* SCSI Control Pins Register */
#define SCPR_SCSI_PHASE_VALID		BIT15
#define SCPR_RESERVED			(BIT14|BIT13|BIT12|BIT11)
#define SCPR_SCSI_DATA_PARITY_MS	BIT10
#define SCPR_SCSI_DATA_PARTIY_LS	BIT9
#define SCPR_SCSI_CONTROLL		(BIT8|BYTE0)

/* SCSI Differential Control Pins Register */
#define SDCPR_RESERVED			(BIT15|BIT14|BIT13|BIT12|BIT11|BIT10)
#define SDCPR_DIFFERENTIAL_SENSE	BIT9
#define SDCPR_DIFFERENTIAL_MODE		BIT8
#define SDCPR_INTERNAL_SCSI_DATA_OUTPUT_ENABLE BIT7
#define SDCPR_DIFFERENTIAL_CONTROL	(BIT6|BIT5|BIT4|BIT3|BIT2)
#define SDCPR_ENABLE_TARGET_GROUP	BIT1
#define SDCPR_ENABLE_INITIATOR_GROUP	BIT0



/************************************************************************/
/* PART 2
/************************************************************************/

/*
 * Mailbox Commands Directory
 *
 */
#define MB_NO_OPERATION			0x0000
#define MB_LOAD_RAM			0x0001
#define MB_EXECUTE_FIRMWARE		0x0002
#define MB_DUMP_RAM			0x0003
#define MB_WRITE_RAM_WORD		0x0004
#define MB_READ_RAM_WORD		0x0005
#define MB_MAILBOX_REGISTER_TEST	0x0006
#define MB_VERIFY_CHECKSUM		0x0007
#define MB_ABOUT_FIRMWARE		0x0008
#define MB_CHECKSUM_FIRMWARE		0x000E
#define MB_INITIALIZE_REQUEST_QUEUE	0x0010
#define MB_INITIALIZE_RESPONSE_QUEUE	0x0011
#define MB_EXECUTE_IOCB			0x0012
#define MB_WAKEUP			0X0013
#define MB_STOP_FIRMWARE		0x0014
#define MB_ABORT			0x0015
#define MB_ABORT_DEVICE			0x0016
#define MB_ABORT_TARGET			0x0017
#define MB_BUS_RESET			0x0018
#define MB_STOP_QUEUE			0x0019
#define MB_START_QUEUE			0x001A
#define MB_SINGLESTEP_QUEUE		0x001B
#define MB_ABORT_QUEUE			0x001C
#define MB_GET_DEVICE_QUEUE_STATUS	0x001D
#define MB_GET_FIRMWARE_STATUS		0x001F
#define MB_GET_INITIATOR_SCSI_ID	0x0020
#define MB_GET_SELECTION_TIMEOUT	0x0021
#define MB_GET_RETRY_COUNT		0x0022
#define MB_GET_TAG_AGE_LIMIT		0x0023
#define MB_GET_CLOCK_RATE		0x0024
#define MB_GET_ACTIVE_NEGATION_STATE	0x0025
#define MB_GET_ASYNC_DATA_SETUP_TIME	0x0026
#define MB_GET_PCI_CONTROL_PARAMETERS	0x0027
#define MB_GET_TARGET_PARAMETERS	0x0028
#define MB_GET_DEVICE_QUEUE_PARAMETERS	0x0029
#define MB_SET_INITIATOR_SCSI_ID	0x0030
#define MB_SET_SELECTION_TIMEOUT	0x0031
#define MB_SET_RETRY_COUNT		0x0032
#define MB_SET_TAG_AGE_LIMIT		0x0033
#define MB_SET_CLOCK_RATE		0x0034
#define MB_SET_ACTIVE_NEGATION_STATE	0x0035
#define MB_SET_ASYNC_DATA_SETUP_TIME	0x0036
#define MB_SET_PCI_CONTROL_PARAMETERS	0x0037
#define MB_SET_TARGET_PARAMETERS	0x0038
#define MB_SET_DEVICE_QUEUE_PARAMETERS	0x0039
#define MB_SET_RESET_DELAY_PARAMETERS	0x003A
#define MB_RETURN_BIOS_BLOCK_ADDRESS	0x0040
#define MB_WRITE_FOUR_RAM_WORDS		0x0041
#define MB_EXECUTE_BIOS_IOCB		0x0042
#define MB_ENABLE_SUBSYS_FEATURES       0x0044
#define MB_SET_SYSTEM_PARAMETER         0x0045
#define MB_GET_SYSTEM_PARAMETER         0x0046
#define MB_LOAD_RAM_A64			0x0050
#define MB_DUMP_RAM_A64			0x0051
#define MB_INITIALIZE_REQUEST_QUEUE_A64 0x0052
#define MB_INITIALIZE_RESPONSE_QUEUE_A64 0x0053
#define MB_EXECUTE_IOCB_A64		0x0054
#define MB_ENABLE_TARGET		0x0055
#define MB_GET_TARGET_STATUS		0x0056
#define MB_SET_OVR_RECOVERY_MODE        0x005A
#define MB_GET_OVR_RECOVERY_MODE        0x005B

/*
 *    Mailbox Flags 
 */

/*
 * Enable Target Flags
 */
#define ETF_ENABLE_SELECTIONS		BIT15

/*
 *    Target Control Flags
 */
#define TCF_DISCONNECT_PRIVILEGE	BIT15
#define TCF_PARITY_CHECKING		BIT14
#define TCF_WIDE_DATA_TRANSFERS		BIT13
#define TCF_SYNCHRONOUS_DATA_TRANSFERS	BIT12
#define TCF_TAGGED_QUEUING		BIT11
#define TCF_AUTOMATIC_REQEUST_SENSE	BIT10
#define TCF_STOP_QUEUE_ON_CHECK_COND	BIT9
#define TCF_RENEGOTIATE_ON_ERROR	BIT8

/*
 *    Async Event Status Codes
 */
#define AEN_SCSI_BUS_RESET 			0x8001
#define AEN_SYSTEM_ERROR   			0x8002
#define AEN_REQUEST_TRANSFER_ERROR		0x8003
#define AEN_RESPONSE_TRANSFER_ERROR		0x8004
#define AEN_REQUEST_QUEUE_WAKEUP		0x8005
#define AEN_EXECUTION_TIMEOUT_RESET		0x8006
#define AEN_BUS_DEVICE_RESET			0x8007
#define AEN_STORAGEWORKS_SWAP_SIGNAL		0x8008
#define AEN_STORAGEWORKS_SHELF_OK_SIGNAL	0x8009
#define AEN_FIRMWARE_GENERATED_BDR		0x800a
#define AEN_WRITE_DATA_OVERRUN                  0x800c
#define AEN_BUS_MODE_TRANSITION			0x800e

/*
 *    Queue Definitions
 */

/* Need these for all command entries! */
#define QE_ENABLE_LUN		0x0B
#define QE_MODIFY_LUN		0x0C
#define QE_IMMED_NOTIFY		0x0D
#define QE_NOTIFY_ACK		0x0E
#define QE_ACCEPT_TARG		0x06
#define QE_CONT_TARG		0x07

typedef struct queue_entry_header {
    U8		entry_type;
    U8		entry_count;
    U8  	system_defined_1;
    U8		flags;
} QUEUE_ENTRY_HEADER;

typedef struct dataseg {
    U32		address; 	/* RUTRO, only 32 bits */
    U32		length;
} DATASEG;

typedef struct command_entry {
    QUEUE_ENTRY_HEADER	header;
    U32		handle;
    U8 		lun;
    U8 		target;
    U16 	cdb_length;
    U16		control_flags;
    U16		reserved;
    U16		timeout;
    U16		data_segment_count;
    U8		cdb[12];
    DATASEG	data_segment[4];
} COMMAND_ENTRY;

typedef struct extended_command_entry {
    QUEUE_ENTRY_HEADER	header;
    U32		handle;
    U8 		lun;
    U8 		target;
    U16 	cdb_length;
    U16		control_flags;
    U16		reserved;
    U16		timeout;
    U16		data_segment_count;
    U8		cdb[44];
} EXTENDED_COMMAND_ENTRY;

typedef struct continuation_entry {
    QUEUE_ENTRY_HEADER header;
    U32		reserved;
    DATASEG	data_segment[7];
} CONTINUATION_ENTRY;

typedef struct marker_entry {
    QUEUE_ENTRY_HEADER header;
    U32		reserved1;
    U8 		lun;
    U8 		target;
    U8		modifier;
    U8		reserved2[53];
} MARKER_ENTRY;

typedef struct status_entry {
    QUEUE_ENTRY_HEADER header;
    U32		handle;
    U16		scsi_status;
    U16		completion_status;
    U16		state_flags;
    U16		status_flags;
    U16		time;
    U16		request_sense_data_length;
    U32		residual_transfer_length;
    U8		reserved[8];    
    U8		request_sense_data[32];
} STATUS_ENTRY;
#define SE_SENSE_DATA_LENGTH   32
#define XSE_SENSE_DATA_LENGTH  60

typedef struct enable_lun_entry {
    QUEUE_ENTRY_HEADER header;
    U32		handle;
    U8		lun;
    U8		reserved3;
    U16		reserved4;
    U32		flags;
    U8		status;
    U8		reserved5;
    U8		command_count;
    U8		immed_notify_count;
    U8		group6_length;
    U8		group7_length;
    U16		timeout;
    U16		reserved6[20];
} ENABLE_LUN_ENTRY;

typedef struct modify_lun_entry {
    QUEUE_ENTRY_HEADER header;
    U32		handle;
    U8		lun;
    U8		reserved3;
    U8		operators;
#define ACCEPT_NO_CHANGE		0
#define ACCEPT_INCREMENT		1
#define ACCEPT_DECREMENT		2
#define IMMED_NOTIFY_NO_CHANGE		0
#define IMMED_NOTIFY_INCREMENT		4
#define IMMED_NOTIFY_DECREMENT		8
    U8		reserved4;
    U32		flags;
    U8		status;
    U8		reserved5;
    U8		command_count;
    U8		immed_notify_count;
    U16		reserved6;
    U16		timeout;
    U16		reserved7[20];
} MODIFY_LUN_ENTRY;

typedef struct immediate_notify_entry {
    QUEUE_ENTRY_HEADER header;
    U32		handle;
    U8		lun;
    U8		iid;
    U8		reserved1;
    U8		tid;
    U32		flags;
    U8		status;
    U8		reserved2;
    U8		tag_value;
    U8		tag_type;
    U16		seq_id;
    U8		scsi_msg[8];
    U8		reserved3[16];
    U8		sense_data[18];
} IMMEDIATE_NOTIFY_ENTRY;

typedef struct notify_acknowledge_entry {
    QUEUE_ENTRY_HEADER header;
    U32		handle;
    U8		lun;
    U8		iid;
    U8		reserved1;
    U8		tid;
    U32		flags;
    U8		status;
    U8		event;
#define NOTIFY_ACK_RESET_CLEARED BIT7
    U16		seq_id;
    U8		reserved2[12];
    U8		reserved3[32];
} NOTIFY_ACKNOWLEDGE_ENTRY;

typedef struct accept_target_io_entry {
    QUEUE_ENTRY_HEADER header;
    U32		handle;
    U8		lun;
    U8		iid;
    U8		cdb_length;
    U8		tid;
    U32		flags;
    U8		status;
    U8		scsi_status;
    U8		tag_value;
    U8		tag_type;
    U8		cdb[26];
    U8		request_sense_data[18];
} ACCEPT_TARGET_IO_ENTRY;

typedef struct ctio_entry_to_isp {
    QUEUE_ENTRY_HEADER header;
    U32		handle;
    U8		lun;
    U8		iid;
    U8		reserved1;
    U8		tid;
    U32		flags;
#define CTIO_SEND_STATUS	BIT31
#define CTIO_DISABLE_SDP	BIT24
#define CTIO_DATA_IN		BIT6
#define CTIO_DATA_OUT		BIT7
#define CTIO_NO_DATA		(BIT6|BIT7)
#define CTIO_TAGGED_IO		BIT1
    U8		status;
    U8		scsi_status;
    U8		tag_value;
    U8		tag_type;
    U32		xfer_length;
    U32		resid_xfer_length;
    U16		timeout_value;
    U16		segment_count;
    DATASEG	data_segment[4];
} CTIO_ENTRY_TO_ISP;

typedef struct ctio_entry_from_isp {
    QUEUE_ENTRY_HEADER header;
    U32		handle;
    U8		lun;
    U8		iid;
    U8		reserved1;
    U8		tid;
    U32		flags;
    U8		status;
    U8		scsi_status;
    U8		tag_value;
    U8		tag_type;
    U32		xfer_length;
    U32		resid_xfer_length;
    U16		timeout_value;
    U16		segement_count;
    U8		data_segments[14];
    U8		sense_data[18];
} CTIO_ENTRY_FROM_ISP;

typedef struct isp_iocb_iosb {
    COMMAND_ENTRY command_entry;
    STATUS_ENTRY status_entry;
} ISP_IOCB_IOSB;

typedef struct bios_iocb {
    U32		dma_address;
    U32		dma_count;
    U8		id_lun;
    U8		flags;
    U8		cdb[12];
} BIOS_IOCB;

/* max # of entries for 1 contig page is 128 */
#define MAX_QUEUE_ENTRIES 128

typedef struct isp_queue {
    COMMAND_ENTRY	entry[MAX_QUEUE_ENTRIES];
} ISP_QUEUE;

typedef struct isp_squeue {
    STATUS_ENTRY	entry[MAX_QUEUE_ENTRIES];
} ISP_SQUEUE;

/*
 * Queue Related Bit Fields 
 *
 */

/* Control Flags */
#define CF_RESERVED_0			BIT15
#define CF_XTENDED_SENSE		BIT14
#define CF_RESERVED_1			BIT13
#define CF_DISABLE_PARITY_CHK		BIT12
#define CF_INIT_WDTR			BIT11
#define CF_FORCE_SYNC			BIT10
#define CF_FORCE_ASYNC			BIT9
#define CF_ARS_DISABLE			BIT8

#define CF_RESERVED_2			BIT7
#define CF_DATA_DIRECTION		(BIT6|BIT5)
#define CF_NO_DATA_PHASE		(CF_DATA_DIRECTION&(0 << 5))
#define CF_DATA_IN_PHASE		(CF_DATA_DIRECTION&(1 << 5))
#define CF_DATA_OUT_PHASE		(CF_DATA_DIRECTION&(2 << 5))
#define CF_TARGET			(CF_DATA_DIRECTION&(3 << 5))
#define CF_READ_DATA			BIT5
#define CF_TARGET_ROUTINE		BIT4
#define CF_SIMPLE_TAG			BIT3
#define CF_ORDERED_TAG			BIT2
#define CF_HEAD_TAG			BIT1
#define CF_NO_DISCONNECT		BIT0

/* Completion Status Error Codes */
#define CSEC_COMPLETE			0x0000
#define CSEC_INCOMPLETE			0x0001
#define CSEC_DMA			0x0002
#define CSEC_TRANSPORT			0x0003
#define CSEC_RESET			0x0004
#define CSEC_ABORTED			0x0005
#define CSEC_TIMEOUT			0x0006
#define CSEC_DATA_OVERRUN		0x0007
#define CSEC_COMMAND_OVERRUN		0x0008
#define CSEC_STATUS_OVERRUN		0x0009
#define CSEC_BAD_MESSAGE		0x000A
#define CSEC_NO_MESSAGE_OUT		0x000B
#define CSEC_EXTENDED_ID_FAILED		0x000C
#define CSEC_IDE_MESSAGE_FAILED		0x000D
#define CSEC_ABORT_MESSAGE_FAILED 	0x000E
#define CSEC_REJECT_MESSAGE_FAILED	0x000F
#define CSEC_NOP_MESSAGE_FAILED		0x0010
#define CSEC_PARTY_ERROR_MESSAGE_FAILED	0x0011
#define CSEC_DEVICE_RESET_MESSAGE_FAILED 0x0012
#define CSEC_ID_MESSAGE_FAILED		0x0013
#define CSEC_UNEXPECTED_BUS_FREE	0x0014
#define CSEC_DATA_UNDERRUN		0x0015
#define CSEC_COMMAND_UNDERRUN		0x0016
#define CSEC_MESSAGE_UNDERRUN		0x0017
#define CSEC_TRANSACTION_ERROR_1	0x0018
#define CSEC_TRANSACTION_ERROR_2	0x0019
#define CSEC_TRANSACTION_ERROR_3	0X001A
#define CSEC_IOCB_BAD_TYPE              0X001B
#define CSEC_IOCB_REJECT_QFULL          0X001C
#define CSEC_PHASE_ERR                  0X001D
#define CSEC_ARS_FAILED			0X001E


/* State Flags */
#define SE_RESERVED1			BIT15
#define SE_TRANSFER_COMPLETE		BIT14
#define SE_GOT_SENSE			BIT13
#define SE_GOT_STATUS			BIT12
#define SE_TRANSFERRED_DATA		BIT11
#define SE_SENT_COMMAND			BIT10
#define SE_GOT_TARGET			BIT9
#define SE_GOT_BUS			BIT8
#define SE_RESERVED2			BYTE0

/* Status Flags */
#define SS_RESERVED			BYTE1
#define SS_NEGOTIATION			BIT7
#define SS_TIMEOUT			BIT6
#define SS_ABORTED			BIT5
#define SS_DEVICE_RESET			BIT4
#define SS_BUS_RESET			BIT3
#define SS_PARITY_ERROR			BIT2
#define SS_SYNC				BIT1
#define SS_DISCONNECT			BIT0

