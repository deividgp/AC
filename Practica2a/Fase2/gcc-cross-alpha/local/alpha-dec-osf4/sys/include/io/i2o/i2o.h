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
 * @(#)$RCSfile: i2o.h,v $ $Revision: 1.1.8.2 $ (DEC) $Date: 1998/12/03 14:26:03 $
 */

/****************************************************************/
/*								*/
/* MODULE NAME: i2o.h						*/
/*								*/
/* LOCATION:	.../src/kernel/io/i2o/i2o.h			*/
/*								*/
/* DESCRIPTION:							*/
/*		Contains definitions for I2O bus support.       */
/*								*/
/* STRUCTURES:							*/
/*	i2o_option	Defines I2O option data table entry.	*/
/*	i2o_tid		Defines I2O tid structure.		*/
/*	i2o_sw		I2O switch table for platform indep.    */
/*			info.					*/
/*								*/
/* REVISION HISTORY:						*/
/*	8/97		Based on I2O Spec. V1.5			*/
/*								*/
/****************************************************************/

#ifndef	__I2O_H__
#define	__I2O_H__

#include <sys/types.h>
#include <io/common/handler.h>	/* for handler_* decl's */
#include <arch/alpha/hal/shared_intr.h>
#include <io/i2o/i2omsg.h>
#include <io/i2o/i2oexec.h>
#include <kern/lock.h>

/*
 * Generic defines for PCI-I2O devices
 */
#define I2O_PCI_INTR_STATUS_OFFSET	0x30
#define I2O_PCI_INTR_MASK_OFFSET	0x34
#define I2O_PCI_INBOUND_QUEUE_OFFSET	0x40
#define I2O_PCI_OUTBOUND_QUEUE_OFFSET	0x44

/* Bit 3 is enable/disable */
#define I2O_PCI_INTR_MASK_ENABLE	0x08


#ifdef _KERNEL
/*
 * I2O Bus-switch table
 */
struct i2o_sw {
    u_int       iop_num;         /* Assigned IOP num by exec. layer     */
    struct bus *busp;   	 /* Ptr. to bus struct for this I2O i/f */
    ihandler_id_t   handler_key;	/* parent rtn'd hid		*/
volatile io_handle_t in_fifo_handle;	/* iohandle for inbound FIFO	*/
volatile io_handle_t out_fifo_handle;	/* iohandle for outbound FIFO	*/
volatile io_handle_t intr_stat_handle;	/* iohandle for inbound FIFO	*/
volatile io_handle_t intr_mask_handle;	/* iohandle for outbound FIFO	*/
    io_handle_t in_msg_frame_base; 	/* kseg base address of inbound
					 * msg frame;
					 * assumption: dense mapped 
					 */
    u_long      out_msg_frame_base; /* kseg of outbound Free_list frames  */
    dma_handle_t out_mf_dma_handle; /* dma mapping of outbound msg frames */
    u_long      msg_reply_data; /* Place to put reply data from IOP
                                 * when data not returned via outbound 
				 * message; e.g., IopReset, OutboundInit
                                 */
    int (*request_resource)();	/* Function for requesting I/O resource	*/
    int (*release_resource)();	/* Function for releaseing I/O resource */
    decl_simple_lock_data( ,i2olock)
				/* Lock to critical data in this structure
                                 * -- ic_, tc_mapp elements
                                 * -- latest ExecStatusGet (ptr)
                                 */
    u_long      *ic_mapp;       /* Ptr. to array of 64-bit args, mapped
                                 * into 32-bit args for 32-bit context use
				 * -- for all OSMs, Exec & Util to IOP
                                 */
    u_long      *tc_mapp;       /* Ptr. to array of 64-bit args, mapped
                                 * into 32-bit args for 32-bit context use
				 * -- for exec, util to IOP
                                 */
    PI2O_EXEC_STATUS_GET_REPLY esgp;
    				/* Ptr. to most recent ExecStatusGet Reply */
    u_int       flags;          /* various flags (defined below)        */
};

/*
 *  i2o_sw flags definitions
 */
#define I2O_RESET_SEQUENCE_IN_PROGRESS  0x00008000

/****************************************************************/
/* I2O-specific bus info structure passed to config routine     */
/* for a bus/bus-adapter connected to a I2O bus		        */
/****************************************************************/
struct	i2o_bus_info {
   struct	common_bus_info	*common_bus_info; 
				 /* Ptr. to common bus base addrs	*/
   struct bus	*bus_hd;	 /* Ptr. to bus head structure	      	*/
   struct i2o_sw *i2o_sw;	 /* Bus-level function switch table 	*/
};


/************************************************************************/
/*									*/
/* OSF Specific data structs, defines, etc. for I2O Bus Support		*/
/*                                                                      */
/************************************************************************/

#define I2O_NAMELEN	15	/* Length of driver, ctlr, etc. names.	*/
#define QUIET		 0	/* to print or not to print....		*/
#define VERBOSE		 1

/****************************************************************/
/* I2O option data structure, used by 				*/
/* .../src/kernel/data/i2o_option_data.c which contains info    */
/* on options that may be installed on a system.		*/
/****************************************************************/

/* 
 * HW-SW rev. V1.5.0
 *	-- supports V1.5 of I2O spec.
 */
struct	i2o_option {
   u_int i2osw_version;	/* Data struct, sw-config version i.d.  */
			/* bits 8-11 is major rev. of I2O spec.
			 * this structure & sw supports;
			 * bits 4-7 are minor rev. of I2O spec.
			 * bits 0-3 are sw-support of bits 11:4
			 */
   u_int   class;	/* Class code Per Table 6-1 of spec	*/
   u_int   subclass;	/* Sub-Class code;defined by each class	*/
   u_int   class_mo_flag;	/* Match-on flag for class field	*/
   u_int   subclass_mo_flag;	/* Match-on flag for subclass field	*/
   char	   driver_name[I2O_NAMELEN+1]; /* config file name of interface	*/
   char	   type;		/* C = ctlr, A = Adapt., D = Device	*/
   int	   (*adpt_config)();	/* adapter config routine to call	*/
};



/* Used for kernel device<->driver matching code */
#define I2O_MO_SHIFT		0
#define I2O_SUBCLASS_MO_SHIFT	I2O_MO_SHIFT
#define I2O_CLASS_MO_SHIFT	(I2O_SUBCLASS_MO_SHIFT + 1)

#define I2O_CLASS_MO_INT_FLAG	 (1 << I2O_CLASS_MO_SHIFT)
#define I2O_SUBCLASS_MO_INT_FLAG (1 << I2O_SUBCLASS_MO_SHIFT)

#define I2O_MO_BASE_PRIO	1
#define I2O_MO_CASE2_PRIO	I2O_MO_BASE_PRIO
#define I2O_MO_CASE1_PRIO	(I2O_MO_CASE2_PRIO + 1)

/* X is a pointer to a i2o_option structure */
#define I2O_MOFLAG_2_INT(X, I2O_MO_INT)\
        if (X->class_mo_flag) 	 I2O_MO_INT += I2O_CLASS_MO_INT_FLAG;\
        if (X->subclass_mo_flag) I2O_MO_INT += I2O_SUBCLASS_MO_INT_FLAG;


/*
 * The following are used to describe the class attribute of the
 * module.  These will be filled in during auto-configuration.
 */
#define I2O_CTLR         1
#define I2O_DEV          2
#define I2O_ADPT         3
#define _I2O_DDM_	 4    /* DDM class device -- manages HDMs in IOP */
#define I2O_UNKNOWN      0xF  /* Module exists but we don't know 
			       * what kind it is.  Provided for 
			       * loadable support.    
			       */
/* for i2o_tid flags element */
#define I2O_ACTIVE	2

#define I2O_CLASS_INVALID 0xFFF
#define I2O_TID_INVALID   0xFFF

/********************************/
/* Per-logical I2O device data	*/
/********************************/
struct	i2o_tid {
   char		      driver_name[I2O_NAMELEN +1]; 
				/* Driver name				*/
   u_int	      tid;	/* shortcut to tid			*/
   PI2O_LCT_ENTRY     lct_entp;	/* Ptr. to tid's lct entry		*/
   i2o_handle_t	      i2o_handlep; /* i2o_handle for driver		*/
   int		      flags;	/* various flags			*/
   int		      mo_case;	/* Int value of driver match-on case	*/
   struct controller  *ctlr_p;	/* Ptr to controller structure		*/
                                /* if option in this lct is a ctlr.	*/
   struct bus         *bus_p;	/* Pointer to bus structure if		*/
				/* option in slot is a bus adapter.	*/
   int	(*adpt_config)();	/* adpt_cnfg fcn ptr			*/
   struct i2o_tid     *next;	/* next one in I2O subsystem		*/
   int		      slot;	/* index in LCT table this tid found at */
   int		      unit;	/* ctlr->ctlr_num; or bus->bus_num	*/
   int		      hw_class;	/* adapter/ctlr-class driver		*/
};

typedef struct i2o_tid	*i2o_tid_t;

/* Attach i2o_tid struct to this field of controller or bus struct */
#define _i2otid_	conn_priv[0]

/* Attach i2o_handle, lct array to bus's private[1] element	*/
#define _i2oh_		private[1]
#define _i2olct_	private[2]

/*
 * Macros used for debugging.  Placed here so driver (OSM) developers
 * can turn appropriate bits by setting I2O_Developer_Debug to these
 * values (OR'd, if need be) in /etc/sysconfigtab.
 */

extern	u_int	_i2o_developer_debug;

/* 
 * The setting of "flags" in a debug variable will turn on specific 
 * printf() calls within the kernel.  This sysconfigtab variable is called 
 * I2O_developer_debug.
 */


/* The following defines are used for the flag bits in the printf macro. */

#define	I2OD_INOUT	0x00000001	/* routine entry and exit 	*/

/* Configuration Header info 						*/
#define I2OD_EXEC	0x00000010	/* Exec. msg's			*/
#define I2OD_MSG	0x00000020	/* Message layer		*/
#define I2OD_OPTION	0x00000100	/* Sysconfigtab, Option table	*/
#define I2OD_MO_1	0x00000200	/* Match-on code info, lvl-1	*/
#define I2OD_MO_2	0x00000400	/* Match-on code info, lvl-2	*/
#define I2OD_LCT	0x00000800	/* LCT - config 		*/

/* Driver entry, configuration info					*/
#define I2OD_PROBE	0x00001000	/* Driver-probe info		*/
#define I2OD_ATTACH	0x00002000	/* Driver-attach config info	*/
#define I2OD_SLAVE	0x00004000	/* Driver-slave config. info	*/

/* Resource managment info						*/
#define I2OD_RSRC_MGMT	0x00100000	/* Resource mgmt info		*/

/* I2O bus-level info							*/
#define I2OD_IO_HANDLES 0x01000000	/* I2O IO,Mem,Config iohandles	*/

/* New, testing I2O bus-support debug printfs				*/
#define I2OD_NOT_YET	0x10000000	/* Notyet prints		*/

/*
 * string defines used to reduce number and size of strings
 * used in the kernel (data space) to print debug messages;
 * underscores used to prevent name collision w/existing drivers
 */
extern char * _Iinout;
extern char * _Iexec;
extern char * _Imsg;
extern char * _Ioption;
extern char * _Imo_1;
extern char * _Imo_2;
extern char * _Ilct;
extern char * _Iprobe;
extern char * _Iattach;
extern char * _Islave;
extern char * _Irsrc_mgmt;
extern char * _Iio_handles;
extern char * _Inot_yet	;


/*
 * printf expansion that I2OPRINTF (below) eventually expands to
 *
 * Using the following format, data-space for the _Ixxx strings
 * is significantly reduced, and is made common for all the supported
 * flag/types listed above.
 */

/* To remove/add all debug printfs */
#define _I2O_DEBUG_

#ifdef _I2O_DEBUG_
#   define _I2OD_INOUT(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_INOUT )  {	\
	    /* VARARGS */			\
            printf (_Iinout); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_EXEC(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_EXEC )  {	\
	    /* VARARGS */			\
            printf (_Iexec); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_MSG(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_MSG )  {	\
	    /* VARARGS */			\
            printf (_Imsg); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_OPTION(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_OPTION )  {	\
	    /* VARARGS */			\
            printf (_Ioption); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_MO_1(X)				\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_MO_1 )  {	\
	    /* VARARGS */			\
            printf (_Imo_1); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_MO_2(X)				\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_MO_2 )  {	\
	    /* VARARGS */			\
            printf (_Imo_2); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_LCT(X)			\
    {						\
	/* NOSTRICT */				\
         if( _i2o_developer_debug & I2OD_LCT ) {	\
	    /* VARARGS */			\
            printf (_Ilct); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_PROBE(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_PROBE )  {	\
	    /* VARARGS */			\
            printf (_Iprobe); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_ATTACH(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_ATTACH )  {	\
	    /* VARARGS */			\
            printf (_Iattach); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_SLAVE(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_SLAVE )  {	\
	    /* VARARGS */			\
            printf (_Islave); 			\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_RSRC_MGMT(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_RSRC_MGMT )  {	\
	    /* VARARGS */			\
            printf (_Irsrc_mgmt); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_IO_HANDLES(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_IO_HANDLES )  {	\
	    /* VARARGS */			\
            printf (_Iio_handles); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }
#   define _I2OD_NOT_YET(X)			\
    {						\
	/* NOSTRICT */				\
        if( _i2o_developer_debug & I2OD_NOT_YET )  {	\
	    /* VARARGS */			\
            printf (_Inot_yet); 		\
	    /* VARARGS */			\
	    printf X ;				\
        }					\
    }

/* This Macro is an attempt to be able to allow for specific subsets of the 
 * DEBUG statements be printed. The first argument is for tracking particular
 * subsets of the statements.  This first, flag argument is compared with the 
 * _i2o_developer_debug variable to determine if the develper wants to see the 
 * message. It is not checking for exact matching, ie, "== F.  This allows
 * he same Macro to be used for different settings of the flags, i.e.,
 * I2OD_LCT_ENT_S | I2OD_LCT_ENT_A
 *
 * The X argument is "ugly" it must be a complete printf argument set 
 * enclosed within "()", this will allow the pre-processor to include
 * it in the final printf statement. 
 */
#define I2OPRINTF(F, X)	_##F(X)

#else  /* !_I2O_DEBUG_ */
#   define I2OPRINTF(F, X)
#endif /* _I2O_DEBUG_ */

#endif /* _KERNEL */

#endif	/* __I2O_H__ */
