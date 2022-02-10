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
#ifndef _CAM_RCI_H_
#define _CAM_RCI_H_
/*
 * HISTORY
 */
#pragma ident "@(#)$RCSfile: cam_rci.h,v $ $Revision: 1.1.15.2 $ (DEC) $Date: 1998/08/26 20:57:57 $"

/*             
 * The CAM Reservation Control Interface
 *
 * This file contains the common data structures and definitions used
 * by CAM device drivers to implement support for DEVRCI.
 *
 * DEVRCI is an abstract interface designed to support a hardware or
 * architecture specific device `Reservation' mechanism in the ASE and
 * TruClusters environments.
 *
 * For more information about DEVRCI refer to the file:
 *
 *                 <io/common/devrci.h>
 *
 */

#include <io/common/devrci.h>
#include <io/common/iotypes.h>
#include <io/common/kds.h>
#include <io/cam/camdb.h>
#include <io/cam/cam.h>
#include <io/cam/dec_cam.h>
#include <io/cam/pdrv.h>
#include <kern/queue.h>

/*********************** NEW PDRV.H MACROS **************************/

/*
 * CAMRCI_RELEASE_SIMQ - is used to release the SIMQ, if it is frozen.
 */

#define CAMRCI_RELEASE_SIMQ(trans, ccb)                    \
  if( (ccb)->cam_ch.cam_status & CAM_SIM_QFRZN )  {        \
      (ccb)->cam_ch.cam_status &= ~CAM_SIM_QFRZN;          \
      (void) cam_rci_release_simq(trans, ccb);             \
  }                                                       

/*
 * CAMRCI_CHK_SIMQ_RULE - is used to help enforce the CAM SIM queue
 * freeze rules needed to properly manage the SIM queue.
 *
 * Upon CCB completion, the actions needed to properly manage the sim
 * queue can be determined by examining the cam_status and the
 * cam_flags fields of the CCB.  IF the CCB was a tagged CCB AND the
 * queue is frozen, release the queue now, ELSE leave the queue frozen
 * and assert the simq head flag, ELSE clear the simq head flag.
 */

#define CAMRCI_CHK_SIMQ_RULE(trans, ccb)                  \
  if ((ccb)->cam_ch.cam_status & CAM_SIM_QFRZN)  {        \
    if ((ccb)->cam_ch.cam_flags & CAM_QUEUE_ENABLE)  {    \
      CAMRCI_RELEASE_SIMQ(trans, ccb);                    \
    }                                                     \
    else {  /* frozen, non-tagged */                      \
      (ccb)->cam_ch.cam_flags |= CAM_SIM_QHEAD;           \
    }                                                     \
  }                                                       \
  else {   /* not frozen, must go on tail. */             \
    (ccb)->cam_ch.cam_flags &= ~CAM_SIM_QHEAD;            \
  }                                                       

/* 
 * CAMRCI_CLEAR_CCB - Clear the fields in the CCB which will be filled
 * in on a retry of the CCB.
 */
#define CAMRCI_CLEAR_CCB(ccb) {                                 \
  (ccb)->cam_ch.cam_status &= CAM_SIM_QFRZN;                    \
  (ccb)->cam_scsi_status = 0;		                        \
  (ccb)->cam_resid = 0;			                        \
  (ccb)->cam_sense_resid = 0;		                        \
  ((PDRV_WS *)ccb->cam_pdrv_ptr)->pws_flags &= ~PWS_CALLBACK;   \
}

/* CAM RCI specific Typedefs */

typedef struct cam_rci_info {
  u_int opcode;       /* IOCTL Function (sub-command) */  
  u_int flags;	      /* Functional flags (modifier)  */
  u_int timeo;        /* Timeout value in seconds     */
  u_int retry;        /* Number of retrys allowed     */
  dev_t dev;          /* The device dev_t             */
  SCSI_TRANS *trans;  /* The device SCSI_TRANS pointer */
  u_int action;       /* Preserve Action              */
  u_char *pdata;      /* Kernel interface data descriptor */
  u_int reserved[2];  /* Reserved for Steel HW-ID */
} CAM_RCI_INFO;

typedef struct cam_rci_event_registry {
        int count;                 /* Number of elements in Queue/List */
	struct queue_entry entry;  /* CAM_RCI_EVENT_ENTRY list head */
	simple_lock_data_t lock;
} CAM_RCI_EVENT_REGISTRY;

/* Event Header Flags */

#define CAM_RCI_EVENT_INITIALIZED 0x1    

typedef struct cam_rci_event_port {
  struct queue_entry entry;
  int reference;      /* Reference count             */
  u_int flags;        /* Registration flags          */
  dev_t dev;          /* Unaldulterated dev_t        */
  RCI_REG reg;        /* Copy of the callers RCI_REG */
} CAM_RCI_EVENT_PORT;

typedef struct cam_rci_event_entry {
  struct queue_entry entry; 
  SCSI_TRANS trans;   /* Copy of the device SCSI_TRANS     */
  u_int flags;        /* Registration flags                */
  dev_t dev;          /* The major_number/unit_number pair */
  struct queue_entry port_list;  /* CAM_RCI_EVENT_PORT list head  */
  struct queue_entry ccb_list;   /* CCB list head (XPT_WS used)   */
  simple_lock_data_t lock;
} CAM_RCI_EVENT_ENTRY;

/* Event Enty flags */

#define CAM_RCI_EVENT_SEEN        0x1    /* Waiting for a Register request */
#define CAM_RCI_ASYNC_REGISTERED  0x2    /* Registered For Async Callbacks */
#define CAM_RCI_EVENT_REGISTERED  0x4    /* Registered For Error Events */
#define CAM_RCI_DESTROY_PORT      0x8    /* Destroy the event port */

/* external declarations */

extern int cam_process_rci(SCSI_TRANS *,
			   DEV_RCI_INFO *,
			   int (*)(),     /* Callback */
			   void (*)(),    /* State machine */
			   int);


/*
 * Endian byteswapping functions
 */
#define USE_SWAP 1  /* Want to byte swap all SCSI/fCP payload data */

#if !USE_SWAP
#define RCISWAP64(value) 
#define RCISWAP32(value) 
#define RCISWAP16(value) 
#else
#define RCISWAP64(value)                                   \
        ((value) = ((((ulong)(value) & 0x00000000000000FF) << 56) |   \
         (((ulong)(value) & 0x000000000000FF00) << 40) |   \
         (((ulong)(value) & 0x0000000000FF0000) << 24) |   \
         (((ulong)(value) & 0x00000000FF000000) << 8)  |   \
         (((ulong)(value) & 0x000000FF00000000) >> 8 ) |   \
         (((ulong)(value) & 0x0000FF0000000000) >> 24) |   \
         (((ulong)(value) & 0x00FF000000000000) >> 40) |   \
         (((ulong)(value) & 0xFF00000000000000) >> 56)))

#define RCISWAP32(value)                          \
        ((value) = ((((uint)(value) & 0xFF000000) >> 24) |   \
         (((uint)(value) & 0x00FF0000) >> 8)  |   \
         (((uint)(value) & 0x0000FF00) << 8)  |   \
         (((uint)(value) & 0x000000FF) << 24)))

#define RCISWAP16(value)                         \
        ((value) = ((((uint)(value) & 0x0000FF00) >> 8)  |  \
         (((uint)(value) & 0x000000FF) << 8)))
#endif

#endif /* _CAM_RCI_H_ */








