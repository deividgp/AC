#ifndef SKZ_TARGET_H
#define SKZ_TARGET_H
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

/************************************************************************
 *									*
 * File:	skz_target.h					        *
 * Date:	October 7, 1993					        *
 * Author:	John Meneghini						*
 *									*
 * Description:								*
 *	This file contains skz driver structures and definitions        *
 *	used for target mode operations with the the XZA.		*
 *									*
 ************************************************************************/

#include <io/cam/xza/skz_xza.h>

/* Misc DEBUG defines */

/* #define SKZ_TGT_PRINT_ERRORS */

#define SKZ_TGT_CHECK_STATE

/* Functional defines */

/*
** SKZ_TGT_ENABLE_THREAD will inusre that "stacked register emaulations"
** will not occure by completing any target mode operation needing to do
** a register emulation (ie. TARGET_MODE_GO) in a thread.
*/

#define SKZ_TGT_ENABLE_THREAD

/* 
** XZA SCSI Target Mode Data types and Structures
*/

typedef enum xza_lun_state {

  /* Interrupts received on Misc Interrupt channel */

  NONE = 0,                /* Uninitailized LUN - Illegal state */
  SCSI_RESET_RCVD = 3,     /* ACC code SCSI Bus Reset recieved */

  /* Target Mode Status Codes 33 - 43 */

  LUN_ENABLED = 33,       /* Lun Enabled interrupt */
  LUN_DISABLED = 34,      /* Lun Disabled interrupt - not used */
  LUN_DEFAULTED = 35,     /* Lun Defaulted (ie. CAM lun disabled) */
  INVLD_SELECTION = 36,   /* Selected by unsupported initiator type */
  INVLD_IDENT = 37,       /* Invalid Identify (disconnects not allowed rcvd */
  UNSPRTD_CDB_RCVD = 38,  /* Group 6/7 or Reserved CBD received */
  SCSI_CDB_RCVD = 39,     /* Successfully recieved a CDB in TGT_COM_BUFF */
  SCSI_CMD_CMPLT = 40,    /* Successful completion of a command, Bus is Free */
  BUS_SENSE_BFREE = 41,   /* Low level SCSI error, the HBA went Bus Free. */
  SCSI_BDR_RCVD = 42,     /* A Bus Device Reset message was recieved */
  CMD_ABRTD = 43,         /* An abort message was recieved from IID */
  INVLD_RESELECTION = 44, /* Invalid reselection / reslect timeout */
  BUS_SENSE_BDISC = 45,   /* Disc msg sent, IID waiting for reselection */ 
  BUS_SENSE_BHELD = 46,   /* Bus is being held in information xfer phase */
  BUS_RELEASE = 47,       /* Premature bus release */
  RESELECT_TO = 48,       /* Reselection timeout */

  /* Software states only (not provided by Hardaware interrupt) */

  CHAN_STATE_CHANGE = 50  

} XZA_LUN_STATE;

/* XZA LUN state flags */

#define SKZ_LUN_INITIALIZED  0x00000001   /* Lun has been initialized */
#define SKZ_LUN_RESET        0x00000002   /* The Lun has been reset */
#define SKZ_CHAN_RESET       0x00000004   /* The Lun Channel has been reset */
#define SKZ_LUN_ENABLED      0x00000008   /* The Lun is presently enabled */
#define SKZ_DISABLING_LUN    0x80000000   /* Trying to disable this LUN */
#define SKZ_ENABLING_LUN     0x40000000   /* Trying to enable this LUN */

/* LUN operation flags */

#define SKZ_TGT_DIS_ALL      0x00001000   /* Disable all LUNS */
#define SKZ_TGT_DISCON       0x00002000   /* Enable Disconnects */
#define SKZ_TGT_DIS_ACC      0x00004000   /* Disable Auto CHCKCND */

typedef struct xza_lun_state_queue {
  XZA_LUN_STATE               state;   /* present state */
  struct xza_lun_state_queue *flink;   /* front link to next state */
  struct xza_lun_state_queue *blink;   /* back link to previous state */
} XZA_LUN_STATE_QUEUE;

#define SKZ_LUN_STATE_QUEUE_SIZE 5       /* Keep 5 former states around */

#define SKZ_PUT_LUN_STATE(newstate,ptr) { \
      (ptr) = (ptr)->flink;               \
      (ptr)->state = (newstate);          \
      }

#ifdef SKZ_TGT_PRINT_ERRORS
#define TOASC(i) ((i)+48)
#define SKZ_TGT_PRINTERR(B, T, L, X)                                 \
  {                                                                  \
   printf ("[%c/%c/%c] (%s): ",                                      \
	   B == NOBTL ? 'b' : TOASC(B),		                     \
	   T == NOBTL ? 't' : TOASC(T),		                     \
	   L == NOBTL ? 'l' : TOASC(L),		                     \
	   module);					             \
   printf X ;                                                        \
  }
#else
#define SKZ_TGT_PRINTERR(B, T, L, X)  SIM_PRINTD((B),(T),(L), CAMD_ERRORS, X) 
#endif

#ifdef SKZ_TGT_CHECK_STATE
#define SKZ_TGT_CHECK_EXPECTED_STATE(C,N,S)                                 \
 {                                                                          \
      if (((N)->next_state)!=(S)) {                                         \
      SKZ_TGT_PRINTERR((C)->bus_num,                                        \
		    (C)->scsi_id.targid,                                    \
		    (C)->scsi_id.lun,                                       \
      ("Unexpected State ERROR, STATE=%s, EXPECT=%s, lst cmd:%s\n",skz_cvt_state_str(S),skz_cvt_state_str((N)->next_state),skz_cvt_tgt_cmd_str((C)->last_reg_cmd->cmd))); \
	skz_error (module,                                                  \
		   SKZ_TMS_ERROR,                                           \
		   (S),                                                     \
		   NULL,                                                    \
		   reg);                                                    \
       }                                                                    \
    }

#else
#define SKZ_TGT_CHECK_EXPECTED_STATE(C,N,S)
#endif

#ifdef SKZ_TGT_ENABLE_THREAD
#define SKZ_CHECK_VALID_TGT_INTR_FLAG(CH, R, S)                        \
  {                                                                    \
    if (!((R)->flags&SKZ_TGT_REG_VALID)) {                             \
	SKZ_UNLOCK((CH)->lock,(S));                                    \
      	return;                                                        \
      }                                                                \
  }
#else
#define SKZ_CHECK_VALID_TGT_INTR_FLAG(CH, R, S)                        
#endif

/* The XZA_TGT_COMM_PAGE data structure defines a 24 byte page of the 
   TGT_COMM_BUFF.  Each 8k byte aligned TGT_COMM_BUFFer has 8 of these
   24 byte pages - one for each SCSI ID on the bus. 

   o The page associated with _my_ SCSI ID is - RESERVED -
     (Group 6 & 7 SCSI commands are not supported) 

   o The other 7 pages are used to pass CDB and Data Descriptor
     information back and forth on a per nexus basis (with the IID
     being used as the index into the 8k TGT_COMM_BUFFer).

*/
  
typedef struct xza_tgt_com_page {

  u_long        array_ptr; /* 64 bit Type3 array pointer - data descriptor */
  u_char    cdb_bytes[12]; /* 12 bytes of CDB data */
  u_char         rsvrd[4]; /* 4 bytes of Reserved - filling a 24 byte page */

} XZA_TGT_COM_PAGE; 

/* The XZA_TGT_NEXUS structure is used to keep track of ative Initiator
   nexuses. */

typedef struct xza_tgt_nexus {
  u_char                 iid;      /* This nexus' Initiator ID */
  u_char        ca_condition;      /* CA condition for this nexus */
  u_char         scsi_status;      /* The last SCSI Status */
  SIM_WS         *active_sws;      /* Pointer to my active WS or NULL */
  SIM_TARG_WS            cdb;      /* Copy of this LUN's CDB bytes, etc. */
  vm_offset_t     typ3_array;      /* Address of typ3 array data descriptor */

  XZA_TGT_COM_PAGE     *page;      /* Pointer to this nexus' com. page */

  XZA_LUN_STATE   next_state;      /* The next expected nexus state */
  XZA_LUN_STATE_QUEUE *state;      /* This nexus's present state */

  /* Nexus State Histogram data */
  XZA_LUN_STATE_QUEUE state_queue[SKZ_LUN_STATE_QUEUE_SIZE];

} XZA_TGT_NEXUS;

/* The XZA_TGT_LUN structure is used to keep track of LUN states on the
   KZMSA.  This structure includes an array of XZA_TGT_NEXUS data structures
   (one for each possible IID) facilitating the support of multiple concurrent
   Initiator nexuses (not supported in CAM Processor Mode V1), as well as a
   clean implementation of the Target Mode State Machine.
*/
   
typedef struct xza_tgt_lun {
  u_long                flags;    /* Flags to keep things neat and tidy */
  SCSI_ID               my_id;    /* My SCSI ID and LUN */
  struct xza_softc *xza_softc;    /* Pointer to my HBA SOFTC */  
  NEXUS            *cam_nexus;    /* Pointer to my associated CAM NEXUS */
  
  vm_offset_t	*tgt_com_buff;    /* Address of this LUN's 8K buffer */
  vm_offset_t    typ3_array;      /* Address of typ3 array data space */
 
  XZA_LUN_STATE    next_state;    /* The next expected LUN state */
  XZA_LUN_STATE_QUEUE  *state;    /* This LUNs present state */

  /* LUN State Histogram data */
  XZA_LUN_STATE_QUEUE state_queue[SKZ_LUN_STATE_QUEUE_SIZE];

  XZA_TGT_NEXUS     iid[NDPS_8];    /* Nexus data for each possible IID.
				    (Number Devices Per SCSI bus nexuses). */
} XZA_TGT_LUN;

/* TYP3 arrays must not cross port page boundries, must be contiguious,
   and cannot be greater than 1K * 8 quadwords long.  */

#define SKZ_TGT_TYP3_ARRAY_SIZE 1024       /* 1K page per LUN */
#define SKZ_TGT_MAX_TYP3_ELEMENTS SKZ_TGT_TYP3_ARRAY_SIZE/8   /* 128 */

#endif /* SKZ_TARGET_H */





