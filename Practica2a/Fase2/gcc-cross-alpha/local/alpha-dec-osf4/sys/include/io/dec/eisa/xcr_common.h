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
 * @(#)$RCSfile: xcr_common.h,v $ $Revision: 1.1.10.2 $ (DEC) $Date: 1996/04/11 20:06:16 $
 */

#ifndef _XCR_COMMON_H_
#define _XCR_COMMON_H_

/* Hack */
#define LK_RETRY 0

#define CMD_DATA 128
/*
 * The scatter/gather element
 */
typedef struct xcr_sg_elem {
	u_char *xcr_sg_addr;
	U32    xcr_sg_count;
}XCR_SG_ELEM;

/*
 * The communication block 
 */

typedef struct xcr_com {
    struct xcr_com *my_addr;    /* Adress of this xcr_com       */ 
    U32 xcr_cntrl;              /* Controller number            */ 
    U32 xcr_unit;               /* Unit number on controller    */ 
    U32 xcr_status;             /* Function status              */ 
    U32 xcr_adap_status;	/* Adaptor Status code..	*/
    U32 xcr_flags;              /* xcr_flags                    */ 
    U32 xcr_complete;           /* Indicates that it was rec by
				   callback routine             */
    struct pd_ws *xcr_pdrv_ws; /* Ptr used by the Peripheral driver */
    struct cntrl_ws *xcr_cntrl_ws; /* Ptr used by the HBA driver   */
    struct trns_ws *xcr_trns_ws; /* Ptr used by the Transport    */
    struct buf *xcr_bp;	        /* Bp pointer used for map info */ 
    void (*xcr_cbfcnp)();       /* Callback on completion function */ 
    u_char *xcr_data_ptr;       /* Pointer to the data buf/SG list */ 
    U32 xcr_dxfer_len;          /* Data xfer length             */ 
    U32 xcr_sg_num;		/* Number of scatter entries in the list */
    U32 xcr_cmd_data_len;       /* Lenght of valid data in the xcr_cmd_data
				   area. */
    U32 xcr_blk_nu;		/* Our disk block number...	*/
    U32 xcr_resid;              /* Transfer residual length     */ 
    U32 xcr_timeout;            /* Timeout value in seconds     */ 
    U32 xcr_command;            /* Command                      */ 
    u_char xcr_cmd_data[CMD_DATA]; /* Storage for some incoming cmd
				   data or outgoing passthru scsi
				   cmds. */
}XCR_COM;

#define XCR_COM_VERSION 1	/* Struct version number. 	*/

/*
 * XCR_COM flags
 */
#define XCR_SPEC_CMD	0x00000001	/* Special passthru 	*/
#define XCR_SCSI_CMD	0x00000002	/* Passthru and scsi	*/
#define XCR_SCATTER_BUF 0x00000004	/* The databuf * is a scatter elem */
#define XCR_LOC_DATA_BUF 0x00000008	/* Local Data buffer in com */
#define XCR_BUF 	0x00000010	/* BP points to buffer	*/




/*
 * RE driver working set 
 */
typedef struct pd_ws {
    struct pd_ws	*pws_flink;     /* Linkage of working set CCBs */
    struct pd_ws	*pws_blink;     /* that we have queued */
    XCR_COM		*pws_com;       /* Pointer to the XCR_COM. */
    U32			pws_flags;      /* Generic to driver */
    U32			pws_retry_cnt;  /* Retry count for this request */
    u_char		*rws_device;    /* Pointer to RE device struct */
}PD_WS;

#define XCR_PD_WS_VERSION 1		/* Struct version number. */

/*
 * Transport working set.
 */

typedef struct trns_ws {
    struct trns_ws *trns_flink;	/* forward pointer in the chain	*/
    struct trns_ws *trns_blink; /* backward pointer in the chain */
    U32 trns_flags;             /* flags for the status of this XCR_COM */
    XCR_COM *trns_com;		/* pointer to the XCR_COM	*/
    U32 trns_nfree;             /* # of times on the free side. */
    U32 trns_nbusy;             /* # of times on the busy side. */
}TRNS_WS;

#define TRNS_WS_VERSION 1		/* Struct version number. */

/*
 * DMA list pointer 
 */
typedef struct dma_sg_list {
    U32	dma_baddr;		/* Bus address			*/
    U32 dma_count;		/* Number of bytes for this BA  */
} DMA_SG_LIST;

#define NUM_SG_LISTS	20

/*
 * Controller/HBA working set.
 */

typedef struct cntrl_ws {
    struct cntrl_ws *cntrl_flink; /* forward pointer in the chain */
    struct cntrl_ws *cntrl_blink; /* backward pointer in the chain */
    XCR_SOFTC *cntrl_softc;	  /* Pointer to the Controllers softc */
    XCR_COM *cntrl_com;		  /* Point to the communication block */
    CMD_QUE *cntrl_cmd_slot;	  /* The address of our slot slot if any */
    U32 cntrl_flags;		  /* General flags		      */
    U32 cntrl_retry_cnt;	  /* Number of times we retried cmd.  */
    caddr_t scsi_addr;		  /* Where we save away the old scsi addr */
    dma_handle_t dma_mapping0;	  /* DMA handle for dma mapping resources */
    dma_handle_t dma_mapping1;
    dma_handle_t dma_mapping_sg;
    DMA_SG_LIST cntrl_dma[NUM_SG_LISTS]; /* Scatter list		*/
    U32 xcr_val_regs;		  /* Bit mask of registers which need 
				    to be hit for this command		*/
    u_char reg_0;		  /* Register 0				*/
    u_char reg_1;		  /* Register 1				*/
    u_char reg_2;		  /* Register 2				*/
    u_char reg_3;		  /* Register 3				*/
    u_char reg_4;		  /* Register 4				*/
    u_char reg_5;		  /* Register 5				*/
    u_char reg_6;		  /* Register 6				*/
    u_char reg_7;		  /* Register 7				*/
    u_char reg_8;		  /* Register 8				*/
    u_char reg_9;		  /* Register 9				*/
    u_char reg_a;		  /* Register a				*/
    u_char reg_b;		  /* Register b				*/
    u_char reg_c;		  /* Register c				*/
    u_char reg_d;		  /* Register d				*/
    u_char reg_e;		  /* Register e				*/
    u_char reg_f;		  /* Register f				*/
}CNTRL_WS;

#define CNTRL_WS_VERSION 1	/* Struct Version Number		*/


/* 
 * CNTRL_WS flags
 */

#define CNTWS_CMD_READY 0x00000001	/* The cmd is ready all parts done */


/* 
 * The whole pkt.
 */

typedef struct xcr_pkt {
    TRNS_WS  xcr_trns_ws;
    PD_WS  xcr_pdrv_ws;
    CNTRL_WS xcr_cntrl_ws;
    XCR_COM  xcr_com;
}XCR_PKT;

#define XCR_PKT_VERSION 1	/* Struct version number 	*/

/*
 * XCR_COM status codes.
 */

#define XCR_INPROG	0x00		/* Command in progress	*/
#define XCR_CMPLT_CMD	0x01		/* Command completed No errors */  
#define XCR_FAILED_CMD  0x02		/* CMD FAILED */
#define XCR_TIMEOUT	0x03		/* Command has timed out */
#define XCR_INVAL_PATH  0x04		/* No controller */
#define XCR_INVAL_CMD   0x05		/* This command is invalid for this
					 * inplementation */
#define XCR_INVAL_PARM	0x06		/* Invaild Parameter */
#define XCR_RESOURCE_FAIL 0x07		/* Failed to get a resource */

/* 
 * THE commands themselves
 */

/* Type 0 Commands */
#define	XCR_SETDIAG		0x31	/* Set Diagnostic Mode */

/* Type 1 Commands */
#define	XCR_READA		0x01	/* Read Ahead */
#define	XCR_READ		0x02	/* Read */
#define	XCR_SGREAD		0x82	/* Scatter/Gather Read */
#define	XCR_WRITE		0x03	/* Write */
#define	XCR_SGWRITE		0x83	/* Write with Scatter/Gather */
#define	XCR_DCDB		0x04	/* Direct CDB Command */
#define	XCR_FLUSH		0x0A	/* Flush */
#define	XCR_ENQUIRY		0x05	/* Enquire about system config */
#define	XCR_SIZE		0x08	/* Size of system drive */
#define	XCR_CHK_CONSIS_ASYNC	0x1E	/* Check consistnecy async */
#define XCR_REBUILD_CTL		0x1F	/* Rebuild control */
#define XCR_INIT		0x28	/* Initialize a system drive */
#define XCR_INIT_STAT		0x29	/* Get Init status */


/* Type 2 Commands */
#define	XCR_RBLD		0x09	/* Rebuild SCSI Disk */
#define	XCR_CKCONSIS		0x0F	/* Check Consistency */
#define	XCR_START		0x10	/* Start Device */
#define	XCR_STOPC		0x13	/* Stop Channel */
#define	XCR_STARTC		0x12	/* Start Channel */
#define	XCR_GSTAT		0x14	/* Get Device State */
#define	XCR_RBLDA		0x16	/* Async Rebuild SCSI Disk */
#define	XCR_RESETC		0x1A	/* Reset Channel */

/*  Type 4 Commands */
#define	XCR_RUNDIAG		0x32	/* Run Diagnostic */

/* Type 5 Commands */
#define	XCR_WRCONFIG		0x06	/* Write XCR960 Config */
#define	XCR_RDCONFIG		0x07	/* Read ROM Config */
#define	XCR_RBADBLK		0x0B	/* Read Bad Block Table */
#define	XCR_RBLDSTAT		0x0C	/* Rebuild Status */
#define	XCR_RBLDSTAT2	        0x27	/* Rebuild Status 2 - better status detection */
#define	XCR_GREPTAB		0x0E	/* Get Replacement Table */
#define	XCR_GET_SD_ELEM		0x15	/* Get SysDrv Element */
#define	XCR_GEROR		0x17	/* Get history of errors */
#define	XCR_ADCONFIG		0x18	/* Add Configuration */
#define	XCR_SINFO		0x19	/* Info about all system drives */
#define	XCR_CLRREPTAB		0x30	/* Clear Replacement Table */
#define	XCR_RDNVRAM		0x38	/* Read NVRAM Config */
#define	XCR_IOPORT_RD		0x39	/* Read I/O Port */
#define	XCR_IOPORT_WR		0x3A	/* Write I/O Port */
#define XCR_WR_CONF2		0x3C	/* Write Config2 table */
#define XCR_RD_CONF2		0x3D	/* Read Config2 table */
#define	XCR_GET_SD_STAT		0x3E	/* Get SysDrv Stats */
#define	XCR_GET_PD_STAT		0x3f	/* Get PhyDev Stats */

/* Type 6 Commands */
#define	XCR_LOADIMG		0x20	/* Get firmware Image */
#define	XCR_STOREIMG		0x21	/* Store firmware Image */
#define	XCR_PROGIMG		0x22	/* Program  Image */




/* 
 * The passtru scsicmd struct 
 */
typedef struct xcr_scsicmd {
    u_char cdb_unit;		/*  Chan(upper 4 bits),target(lower 4) */
    u_char cdb_cmdctl;		/* Command control */
    u_short cdb_xfersz;		/* Transfer length */
    u_int cdb_databuf;		/* Not used by users Data buffer in system 
				   Memory */
    u_char cdb_cdblen;		/* Size of CDB in bytes */
    u_char cdb_senselen;	/* Size of sense length in bytes */
    u_char cdb_data[12];	/* CDB Data upto 12 bytes */
    u_char cdb_sensebuf[64];	/* Sense Data upto 64 bytes */
    u_char cdb_status;		/* SCSI Status */
    u_char cdb_reserved;	
    caddr_t cdb_64_addr;	/* Pointer to the real data buffer */
} XCR_SCSICMD;

/*
 * Pass thru cmd struct NOT for scsi cmds... 
 */
typedef struct xcr_directcmd {
    u_char ioc_mbx0;	/* REG 0			*/
    u_char ioc_mbx1;	/* REG 1 Don't care cmd id 	*/
    u_char ioc_mbx2;	/* REG 2			*/
    u_char ioc_mbx3;	/* REG 3			*/
    u_char ioc_mbx4;	/* REG 4			*/
    u_char ioc_mbx5;	/* REG 5			*/
    u_char ioc_mbx6;	/* REG 6			*/
    u_char ioc_mbx7;	/* REG 7			*/
    u_char stat1;	/* REG 0xE			*/
    u_char stat2;	/* REG 0xF			*/
    caddr_t ioc_buf;	/* User data buf		*/
    u_long ioc_bufsz;	/* User data buf size		*/
} XCR_DIRECTCMD;


/**********************************************************************/

 /* Status/Error Codes */
#define		NO_ERROR	0x00	/* Normal Completion */
#define		E_UNREC		0x01	/* Unrecoverable data error */
#define		E_NODRV		0x02	/* System Driver does not exist */
#define		E_LIMIT		0x105	/* Attempt to read beyond limit */
#define		E_INVALCHAN	0x105	/* Invalid Address (Channel) */
#define		E_CHN_BUSY	0x106 	/* Channel Busy */
#define		E_NEDRV		0x105	/* Non Existent System Drive */
#define		E_NDEVATAD	0x102	/* No Device At Address Specified */
#define		E_BADBLK	0x03	/* Some Bad Blks Found */
#define		E_RBLDFAIL	0x04	/* New Disk Failed During Rebuild */
#define		E_INPROGRES	0x106	/* Rebuild/Check is in progress */
#define		E_RBLDONLINE	0x02	/* Attempt to rebuild online drive */
#define		E_DISKDEAD	0x02	/* SCSI Disk on Sys Drive is dead */
#define		E_INVALSDRV	0x105	/* A RAID 0 Drive */
#define		E_NORBLDCHK	0x106	/* No REBUILD/CHECK in progress */


#endif /* _XCR_COMMON_H_ */
