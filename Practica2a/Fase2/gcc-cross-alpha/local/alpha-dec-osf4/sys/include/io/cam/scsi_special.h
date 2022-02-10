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
 * @(#)$RCSfile: scsi_special.h,v $ $Revision: 1.1.6.2 $ (DEC) $Date: 1995/12/20 19:08:18 $
 */
#if !defined(SCSI_SPECIAL_INCLUDE)
#define SCSI_SPECIAL_INCLUDE 1

/************************************************************************
 *									*
 * File:	scsi_special.h						*
 * Date:	May 7, 1991						*
 * Author:	Robin T. Miller						*
 *									*
 * Description:								*
 *	Definitions for CAM/SCSI special I/O control interface.		*
 *									*
 * Modification History:						*
 *									*
 * August 3, 1991 by Robin Miller.					*
 *	Added field sp_sense_resid for sense data resdiual count and	*
 *	changed field sp_sense_length from int to u_char.		*
 *									*
 * July 20, 1991 by Robin Miller.					*
 *	Added fields to scsi_special structure to allow device major/	*
 * minor number, logical unit number, and bus/target/lun information	*
 * to be specified.  This would permit this I/O control command to be	*
 * used with the User Agent interface if desired.			*
 *									*
 ************************************************************************/

/*
 * Define Special Argument Control Flags (Also See 'h/cam_special.h'):
 */
#define SA_NO_ERROR_RECOVERY	0x01	/* Don't perform error recovery	*/
#define SA_NO_ERROR_LOGGING	0x02	/* Don't log error messages.	*/
#define SA_NO_SLEEP_INTR	0x04	/* Don't allow sleep interrupts	*/

/*
 * Structure for Processing Special I/O Control Commands.
 */
typedef struct scsi_special {
	u_int	sp_flags;		/* The special command flags.	*/
	dev_t	sp_dev;			/* Device major/minor number.	*/
	u_char	sp_unit;		/* Device logical unit number.	*/
	u_char	sp_bus;			/* SCSI host adapter bus number	*/
	u_char	sp_target;		/* SCSI device target number.	*/
	u_char	sp_lun;			/* SCSI logical unit number.	*/
	u_int	sp_sub_command;		/* The sub-command (see below).	*/
	u_int	sp_cmd_parameter;	/* Command parameter (if any).	*/
	int	sp_iop_length;		/* Parameters buffer length.	*/
	caddr_t	sp_iop_buffer;		/* Parameters buffer address.	*/
	u_char	sp_sense_length;	/* Sense data buffer length.	*/
	u_char	sp_sense_resid;		/* Sense data residual count.	*/
	caddr_t	sp_sense_buffer;	/* Sense data buffer address.	*/
	int	sp_user_length;		/* User data buffer length.	*/
	caddr_t	sp_user_buffer;		/* User data buffer address.	*/
	int	sp_timeout;		/* Timeout for this command.	*/
	u_char	sp_retry_count;		/* Retrys performed on command.	*/
	u_char	sp_retry_limit;		/* Times to retry this command.	*/
	int	sp_xfer_resid;		/* Transfer residual count.	*/
} SCSI_SPECIAL_T;

typedef struct scsi_special scsi_special_t;

#define SCSI_SPECIAL		_IOWR('p', 100, struct scsi_special)

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Structure for data transfer commands (I/O parameters):
 *
 * NOTE:  The command specific flags are expected to be defined with
 *	  the actual SCSI structure in the appropriate include file.
 */
typedef struct data_transfer_params {
	u_char	dt_cmd_flags;		/* The command specific flags.	*/
	/*
	 * Inquiry Data (may be necessary to implement commands):
	 */
	u_char	dt_inq_dtype	: 5,	/* The peripheral device type.	*/
		dt_inq_pqual	: 3;	/* The peripheral qualifier.	*/
	u_char	dt_inq_ansi	: 4,	/* The ANSI version supported.	*/
				: 4;	/* Reserved.			*/
	u_char	dt_cdb_flags;		/* The CDB specific flags.	*/
	/*
	 * Common Device Fields:
	 */
	u_int	dt_block_size;		/* The device block size.	*/
	/*
	 * Direct-Access Devices:
	 */
	u_int	dt_lba;			/* The logical block address.	*/
	/*
	 * Sequential-Access Devices:
	 */
	u_char	dt_density_code;	/* The density code.		*/
	u_char	dt_compress_code;	/* The data compression code.	*/
	u_char	dt_speed_setting;	/* The tape speed setting.	*/
	u_char	dt_buffered_setting;	/* The buffer control setting.	*/
	/*
	 * Additional Parameters (if any):
	 */
	u_int	dt_device_depend[10];	/* Device dependent parameters.	*/
} DATA_TRANSFER_PARAMS;

typedef struct data_transfer_params data_transfer_params_t;
/*
 * Defines to Clarify Field Usage:
 */
#define dt_record_size	dt_block_size	/* For sequential-access device	*/
/*
 * Request length for non-data movement commands (i.e. Verify):
 */
#define dt_length	dt_device_depend[0]

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Diagnostic Test Flags.
 */
#define DP_UNIT_OFL	0x01		/* Permit unit access oper.	*/
#define DP_DEV_OFL	0x02		/* Permit device access oper.	*/
#define DP_SELF_TEST	0x04		/* Do self-test diagnostics.	*/
#define DP_PF_VALID	0x10		/* Page format valid bit.	*/

/*
 * Diagnostic Parameters Structure.
 */
typedef struct diagnostic_params_s {
	u_char	dp_control	: 5,	/* Diagnostic control flags.	*/
				: 3;	/* Reserved.			*/
	u_char	dp_test;		/* Diagnostic test flags.	*/
	u_char	dp_mode;		/* Diagnostic mode value.	*/
	u_char	dp_id;			/* Diagnostic buffer ID.	*/
	u_int	dp_lba;			/* Logical block address.	*/
	u_int	dp_offset;		/* The buffer offset (if any).	*/
	u_int	dp_diag_params[10];	/* Diagnostic specific params.	*/
} diagnostic_params_t;

/*
 * Diagnostic Page Codes:
 */
#define DIAG_SUPPORTED_PAGES	0x00	/* Supported diagnostic pages.	*/
#define DIAG_TRANS_ADDR_PAGE	0x40	/* Translate address page.	*/

#define DIAG_RESERVED_START	0x01	/* Reserved starting page value	*/
#define DIAG_RESERVED_END	0x3F	/* Reserved ending page value.	*/
#define DIAG_DEVICE_START	0x40	/* Device specific start value.	*/
#define DIAG_DEVICE_END		0x7F	/* Device specific ending value	*/
					/* 0x40-0x7F is reserved by	*/
					/* 	     most device types.	*/
#define DIAG_VENDOR_START	0x80	/* Vendor specific start value.	*/
#define DIAG_VENDOR_END		0xFF	/* Vendor specific ending value	*/

/*
 * Send Diagnostic Parameters Structure:
 */
typedef struct send_diagnostic_params {
	u_char	sdp_page_code;		/* The diagnostic page code.	*/
	u_char	sdp_reserved;		/* Reserved.			*/
	u_char	sdp_page_length[2];	/* Diagnostic page length.	*/
} send_diagnostic_params_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Structures for Inquiry/Log/Mode Select/Sense page, etc commands:
 *
 * FYI: These structures are used to pass command specific parameters
 *	to the lower level routines which actually generate the CDB.
 *	The sp_iop_buffer & sp_iop_length fields reflect this struct.
 *	The sp_user_buffer & sp_user_length fields reflect parameters
 *	which will be sent to or received from the command executed.
 *
 * BTW: While the structure definitions do _not_ have to match the
 *	actual CDB fields, I've done this for consistency and sanity.
 *
 */

typedef struct inquiry_params {
	u_char	iqp_evpd	: 1,	/* Enable vital product data.	*/
		iqp_cmddt	: 1,	/* Command support data.	*/
				: 6;	/* Reserved.			*/
	u_char	iqp_page;		/* Inquiry Page code to return.	*/
} inquiry_params_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

typedef struct logselect_params {
	u_char	lsp_sp		: 1,	/* Save log parameters.		*/
		lsp_pcr		: 1,	/* Parameter code reset.	*/
				: 6;	/* Reserved.			*/
	u_char			: 6,	/* Reserved.			*/
		lsp_pc		: 2;	/* The page control field.	*/
} logselect_params_t;

typedef struct logsense_params {
	u_char	lsp_sp		: 1,	/* Save log parameters.		*/
		lsp_ppc		: 1,	/* Parameter pointer control.	*/
				: 6;	/* Reserved.			*/
	u_char	lsp_page	: 6,	/* The page code.		*/
		lsp_pc		: 2;	/* The page control field.	*/
	u_short lsp_param_ptr;		/* Parameter data pointer.      */
} logsense_params_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

typedef struct modeselect_params {
	u_char	msp_sp		: 1,	/* Save page parameters.	*/
				: 3,	/* Reserved.			*/
		msp_pf		: 1,	/* Page format.			*/
				: 3;	/* Reserved.			*/
} modeselect_params_t;

typedef struct modesense_params {
	u_char			: 3,	/* Reserved.			*/
		msp_dbd		: 1,	/* Disable block descriptiors.	*/
				: 4;	/* Reserved.			*/
	u_char	msp_page	: 6,	/* The page code.		*/
		msp_pc		: 2;	/* The page control field.	*/
} modesense_params_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Declarations for Format Command.
 */
typedef struct format_option_bits {
	u_char				/* Format option flags:		  [1] */
		vs		: 1,	/* Vendor specific.		(0:1) */
		immed		: 1,	/* Immediate.			(1:1) */
		dsp		: 1,	/* Disable saving parameters.	(2:1) */
		ip		: 1,	/* Initialization pattern.	(3:1) */
		stpf		: 1,	/* Stop format.			(4:1) */
		dcrt		: 1,	/* Disable certification.	(5:1) */
		dpry		: 1,	/* Disable primary.		(6:1) */
		fov		: 1;	/* Format options valid.	(7:1) */
} format_option_bits_t;

#define FO_VS		0x01
#define FO_IMMED	0x02
#define FO_DSP		0x04
#define FO_IP		0x08
#define FO_STPF		0x10
#define FO_DCRT		0x20
#define FO_DPRY		0x40
#define FO_FOV		0x80

/*
 * Format Unit Defect List Header:
 */
typedef struct format_defect_header {
	u_char	fdh_reserved;		/* Reserved.			  [0] */
	union {				/* Format options.		  [1] */
		u_char format_options;
		format_option_bits_t fb;
	} fo;
	u_char	fdh_defect_length[2];	/* Defect list length.		      */
} format_defect_header;

#define fdh_vs		fo.fb.vs
#define fdh_immed	fo.fb.immed
#define fdh_dsp		fo.fb.dsp
#define fdh_ip		fo.fb.ip
#define fdh_stpf	fo.fb.stpf
#define fdh_dcrt	fo.fb.dcrt
#define fdh_dpry	fo.fb.dpry
#define fdh_fov		fo.fb.fov
#define fdh_options	fo.format_options

typedef struct format_ip_desc {
	u_char			: 6,	/* Reserved.			*/
		fip_modifier	: 2;	/* Initialization pat modifier.	*/
	u_char	fip_type;		/* Initialization pattern type.	*/
	u_char	fip_length[2];		/* The pattern length (2 or 4).	*/
	u_char	fip_pattern[4];		/* The initialization pattern.	*/
} format_ip_desc_t;

/*
 * Format Unit Parameters:
 */
typedef struct format_params_s {
	u_char	fp_defect_format : 3,	/* The defect list format.	*/
		fp_cmplst	 : 1,	/* Complete defect list.	*/
		fp_fmtdata	 : 1,	/* Format data parameters.	*/
				 : 3;	/* Not used.			*/
	u_char	fp_vendor_specific;	/* Vendor specific parameter.	*/
	u_short	fp_interleave;		/* Interleave factor.		*/
} format_params_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Read Capacity Data Structure:
 */
typedef struct read_capacity_data {
	u_char	logical_blocks[4];	/* Maximum logical blocks.	[0-3] */
	u_char	block_length[4];	/* The device block Length.	[4-7] */
} read_capacity_data_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Defect List Format Types:
 */
#define DEFECT_BLOCK_FORMAT	0x00	/* Logical block format.	*/
#define DEFECT_BFI_FORMAT	0x04	/* Bytes from index format.	*/
#define DEFECT_SECTOR_FORMAT	0x05	/* Physical sector format.	*/
#define DEFECT_VENDOR_FORMAT	0x06	/* Vendor sepcific format.	*/
					/* All others are reserved.	*/
#define DEFECTIVE_TRACK   0xFFFFFFFF	/* Entire track is defective.	*/

/*
 * Defect Data Formats:
 */
typedef struct defect_block_format {
	u_char	dbf_lba[4];		/* Defect logical block address. */
} defect_block_format_t;

typedef struct defect_bfi_format {
	u_char	dif_cylinder[3];	/* Defect cylinder number.	*/
	u_char	dif_head;		/* Defect head number.		*/
	u_char	dif_bfi[4];		/* Defect bytes from index.	*/
} defect_bfi_format_t;

typedef struct defect_sector_format {
	u_char	dsf_cylinder[3];	/* Defect cylinder number.	*/
	u_char	dsf_head;		/* Defect head number.		*/
	u_char	dsf_sector[4];		/* Defect sector number.	*/
} defect_sector_format_t;

/*
 * Read Defect Data defect list header:
 */
typedef struct read_defect_header {
	u_char	rdh_reserved;		/* Reserved.			  [0] */
	u_char				/* 				  [1] */
		rdh_format	: 3,	/* Defect list format.		(0:3) */
		rdh_glist	: 1,	/* Grown defect list.		(3:1) */
		rdh_plist	: 1,	/* Primary defect list.		(4:1) */
				: 3;	/* Reserved.			(5:3) */
	u_char	rdh_defect_length[2];	/* Defect list length.		[2-3] */
} read_defect_header_t;

/*
 * Read Defect Data Parameters:
 */
typedef struct read_defect_params_s {
	u_char	rdp_defect_format : 3,	/* The defect list format.	*/
		rdp_glist	  : 1,	/* The grown defect list.	*/
		rdp_plist	  : 1,	/* Manufacturers defect list.	*/
				  : 3;	/* Reserved field.		*/
} read_defect_params_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Reassign Block defect list header:
 */
typedef struct reassign_defect_header {
	u_char	rbh_reserved[2];	/* Reserved.			[0-1] */
	u_char	rbh_defect_length[2];	/* Defect list length.		[2-3] */
} reassign_defect_header_t;

/*
 * Reassign Block defect descriptor:
 */
typedef struct reassign_defect_desc {
	u_char	rbd_lba[4];		/* Logical block address.	[0-3] */
} reassign_defect_desc_t;

/*
 * Reassign Block defect list parameters:
 */
typedef struct reassign_params_s {
	struct reassign_defect_header	rp_header;
	struct reassign_defect_desc	rp_defects[1];
} reassign_params_t;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Various SCSI Command Flags:
 */
#define CDB_RELADR	0x01		/* Relative address.		*/
#define CDB_BYTCHK	0x02		/* Byte check data sent.	*/
#define CDB_IMMED	0x02		/* Complete immediately.	*/

#define DIR_DPO		0x10		/* Disable page-out.		*/
#define DIR_FUA		0x08		/* Force unit access.		*/

#define DIR_LBDATA	0x02		/* Logical block data.		*/
#define DIR_PBDATA	0x04		/* Physical block data.		*/

#define OP_EBP		0x04		/* Erase by-pass (don't erase).	*/
#define OP_ERA		0x04		/* Erase all (to end of media).	*/
#define OP_BLKVFY	0x04		/* Blank verify (erased media).	*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Special I/O Control Sub-Commands.
 */
#define SCMD_CHANGE_DEFINITION			1
#define SCMD_COMPARE				2
#define SCMD_COPY				3
#define SCMD_COPY_VERIFY			4
#define SCMD_ERASE				5
#define SCMD_ERASE_10				6
#define SCMD_ERASE_12				7
#define SCMD_EXCHANGE_MEDIUM			8
#define SCMD_FORMAT				9
#define SCMD_FORMAT_UNIT			10
#define SCMD_GET_DATA_BUFFER_STATUS		11
#define SCMD_GET_MESSAGE_10			12
#define SCMD_GET_MESSAGE_12			13
#define SCMD_GET_MESSAGE_6			14
#define SCMD_GET_WINDOW				15
#define SCMD_INITIALIZE_ELEMENT_STATUS		16
#define SCMD_INQUIRY				17
#define SCMD_LOAD_UNLOAD			18
#define SCMD_LOCATE				19
#define SCMD_LOCK_UNLOCK_CACHE			20
#define SCMD_LOG_SELECT				21
#define SCMD_LOG_SENSE				22
#define SCMD_MEDIUM_SCAN			23
#define SCMD_MODE_SELECT_10			24
#define SCMD_MODE_SELECT_6			25
#define SCMD_MODE_SENSE_10			26
#define SCMD_MODE_SENSE_6			27
#define SCMD_MOVE_MEDIUM			28
#define SCMD_OBJECT_POSITION			29
#define SCMD_PAUSE_RESUME			30
#define SCMD_PLAY_AUDIO_10			31
#define SCMD_PLAY_AUDIO_12			32
#define SCMD_PLAY_AUDIO_MSF			33
#define SCMD_PLAY_AUDIO_TRACK_INDEX		34
#define SCMD_PLAY_TRACK_RELATIVE_10		35
#define SCMD_PLAY_TRACK_RELATIVE_12		36
#define SCMD_POSITION_TO_ELEMENT		37
#define SCMD_PREFETCH				38
#define SCMD_PREVENT_ALLOW_REMOVAL		39
#define SCMD_PRINT				40
#define SCMD_READ				41
#define SCMD_READ_SCANNER			42
#define SCMD_READ_10				43
#define SCMD_READ_12				44
#define SCMD_READ_6				45
#define SCMD_READ_BLOCK_LIMITS			46
#define SCMD_READ_BUFFER			47
#define SCMD_READ_CAPACITY			48
#define SCMD_READ_DEFECT_DATA			49
#define SCMD_READ_DEFECT_DATA_10		50
#define SCMD_READ_DEFECT_DATA_12		51
#define SCMD_READ_ELEMENT_STATUS		52
#define SCMD_READ_GENERATION			53
#define SCMD_READ_HEADER			54
#define SCMD_READ_LONG				55
#define SCMD_READ_POSITION			56
#define SCMD_READ_REVERSE			57
#define SCMD_READ_SUBCHANNEL			58
#define SCMD_READ_TOC				59
#define SCMD_READ_UPDATED_BLOCK			60
#define SCMD_REASSIGN_BLOCKS			61
#define SCMD_RECEIVE				62
#define SCMD_RECEIVE_DIAGNOSTIC			63
#define SCMD_RECOVER_BUFFERED_DATA		64
#define SCMD_RELEASE				65
#define SCMD_RELEASE_UNIT			66
#define SCMD_REQUEST_SENSE			67
#define SCMD_REQUEST_VOLUME_ELEMENT_ADDRESS	68
#define SCMD_RESERVE				69
#define SCMD_RESERVE_UNIT			70
#define SCMD_REWIND				71
#define SCMD_REZERO_UNIT			72
#define SCMD_SCAN				73
#define SCMD_SEARCH_DATA_EQUAL			74
#define SCMD_SEARCH_DATA_EQUAL_10		75
#define SCMD_SEARCH_DATA_EQUAL_12		76
#define SCMD_SEARCH_DATA_HIGH			77
#define SCMD_SEARCH_DATA_HIGH_10		78
#define SCMD_SEARCH_DATA_HIGH_12		79
#define SCMD_SEARCH_DATA_LOW			80
#define SCMD_SEARCH_DATA_LOW_10			81
#define SCMD_SEARCH_DATA_LOW_12			82
#define SCMD_SEEK_10				83
#define SCMD_SEEK_6				84
#define SCMD_SEND				85
#define SCMD_SEND_SCANNER			86
#define SCMD_SEND_DIAGNOSTIC			87
#define SCMD_SEND_MESSAGE_10			88
#define SCMD_SEND_MESSAGE_12			89
#define SCMD_SEND_MESSAGE_6			90
#define SCMD_SEND_VOLUME_TAG			91
#define SCMD_SET_LIMITS				92
#define SCMD_SET_LIMITS_10			93
#define SCMD_SET_LIMITS_12			94
#define SCMD_SET_WINDOW				95
#define SCMD_SLEW_PRINT				96
#define SCMD_SPACE				97
#define SCMD_START_STOP_UNIT			98
#define SCMD_STOP_PRINT				99
#define SCMD_SYNCHRONIZE_BUFFER			100
#define SCMD_SYNCHRONIZE_CACHE			101
#define SCMD_TEST_UNIT_READY			102
#define SCMD_UPDATE_BLOCK			103
#define SCMD_VERIFY				104
#define SCMD_VERIFY_TAPE			105
#define SCMD_VERIFY_10				106
#define SCMD_VERIFY_12				107
#define SCMD_WRITE				108
#define SCMD_WRITE_10				109
#define SCMD_WRITE_12				110
#define SCMD_WRITE_6				111
#define SCMD_WRITE_BUFFER			112
#define SCMD_WRITE_FILEMARKS			113
#define SCMD_WRITE_LONG				114
#define SCMD_WRITE_SAME				115
#define SCMD_WRITE_VERIFY			116
#define SCMD_WRITE_VERIFY_10			117
#define SCMD_WRITE_VERIFY_12			118

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/*
 * Start of pseudo-commands (allows easy parse dispatching).
 */
enum scsi_pseudo {
	SCMD_ALLOW_REMOVAL = 1000,	/* Allow media removal.		*/
	SCMD_PREVENT_REMOVAL,		/* Prevent media removal.	*/

	SCMD_LOAD_UNIT,			/* Load unit command.		*/
	SCMD_UNLOAD_UNIT,		/* Unload unit command.		*/

	SCMD_START_UNIT,		/* Start unit command.		*/
	SCMD_STOP_UNIT,			/* Stop unit command.		*/
	SCMD_EJECT_MEDIA		/* Eject media command.		*/
};

#endif /* !defined(SCSI_SPECIAL_INCLUDE) */
