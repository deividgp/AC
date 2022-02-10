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
 * @(#)$RCSfile: i2o_logger.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1998/10/30 17:33:22 $
 */

#ifndef _I2O_LOGGER_H_
#define _I2O_LOGGER_H_


/* Structure definitions	*/

/*
 * The error entry struct describes a data type (string, com, 
 * controller working set etc.). There can be multiple error entries 
 * per packet.
 */
typedef struct i2o_err_entry {
    U32		ent_type;	/* String, CONTRL_WS etc        */
    U32		ent_size; 	/* Size of the data 		*/
    U32		ent_total_size; /* To preserve alignment (uerf) */
    U32		ent_vers;	/* Version number of type.	*/
    u_char	*ent_data;	/* Pointer to whatever string etc */
    U32		ent_pri;	/* FULL or Brief uerf output	*/
}I2O_ERR_ENTRY;


/*
 * The i2o error header contains all the data need by uerf to determine
 * that this is a i2o error log packet.
 */

typedef struct i2o_err_hdr {
    u_short	hdr_type;	/* Packet type - I2O_ERR_PKT	*/
    U32		hdr_size;	/* Filled in by i2o_logger 	*/
    u_char	hdr_class;	/* Sub system class Tape, disk,
				 * etc..
				 */
    U32		hdr_subsystem;	/* 
				 * Mostly for controller type
				 * But the current errloger uses
				 * disk tape etc if no controller
				 * is known.. So what we will do
				 * is dup the disk and tape types
				 * in the lower number 0 - 1f and
				 * the controllers EISA SWXCR
				 * etc can use the uppers.
				 */
    U32		hdr_entries;	/* Number of error entries in list*/
    I2O_ERR_ENTRY *hdr_list;	/* Pointer to list of error entries*/
    U32		hdr_pri;	/* Error logger priority.	*/
}I2O_ERR_HDR;


/* ---------------------------------------------------------------------- */

/*
 * General purpose define for no Error logger value.
 */

#define NO_ERRVAL	-1


/* Defines for I2O_ERR_HDR	*/

/* 
 * I2O_ERR_HDR.hdr_type defines	
 * There is only 1 type I2O_ERR_PKT. This tells uerf that a I2O 
 * error or informational packet is in the log.
 *
 * ELCT_I2O_ERRPKT defined in /kernel/dec/binlog/binlog.h
 */
#define I2O_ERR_PKT	ELCT_I2O_ERRPKT	/* Error record type */

/*
 * I2O_ERR_HDR.hdr_class defines.
 * This field id's which part of I2O detected the error...
 * Tape, disk, dme, sim_sii etc. Please note that 0 - 1F  are
 * reserved for devices..........
 */

#define CLASS_RDISK  	0x00			/* 0x00 Raid Disk	*/
/* 1 - 1e reserved 							*/
#define CLASS_NOT_KNOWN 0x1f	   		/* 0x1f			*/
/* Port classes								*/
#define CLASS_I2O_BS	0x20			/* I2O BS Class		*/
/* ADD your classes here	*/


/*
 * XCR_ERR_HDR.hdr_subsystem
 */
#define SUBS_DISK CLASS_RDISK			/* 0x00			*/
/* 1 - 1e reserved                                                      */
#define SUBS_NOT_KNOWN CLASS_NOT_KNOWN 	  	/* 0x1f			*/
#define SUBS_I2O_BS	CLASS_I2O_BS		/* I2O BS 		*/


/* 
 * I2O_ERR_HDR.hdr_pri defines....
 * The Priority define is how we allocate and report the error event.
 * I2O_ERR_SEVERE - nasty panics, controller parity errors, no recovery.
 * I2O_ERR_HIGH - Hard errors, but recovery
 * I2O_ERR_LOW - Informational messages.
 */

#define I2O_ERR_SEVERE	EL_PRISEVERE
#define I2O_ERR_HIGH	EL_PRIHIGH
#define I2O_ERR_LOW	EL_PRILOW

/*
 * I2O_ERR_ENTRY defines
 */

/*
 * I2O_ERR_ENTRY.ent_type defines
 */

/* 
 * There can be multiple types of strings.... This will allow the error
 * log formatter to make the output look nice.
 */
#define STR_START		0x00000100	/* Start string range	*/
#define ENT_STRING		0x00000100	/* Generic string	*/
#define ENT_STR_DEV		0x00000101	/* Device name string	*/
#define ENT_STR_MODULE		0x00000102	/* Module name string	*/
/*
 * ERROR type string hard soft software etc.
 */
#define ENT_STR_SOFTWARE_ERROR	0x00000103	/* Software error	*/
#define ENT_STR_HARD_ERROR	0x00000104	/* Hardware error	*/
#define ENT_STR_SOFT_ERROR	0x00000105	/* Soft error (recovered)*/
#define ENT_STR_INFOR_ERROR	0x00000106	/* Informational error	*/
#define ENT_STR_UNKNOWN_ERROR	0x00000107	/* Unknown error type	*/

#define STR_END			0x000001ff	/* END string range	*/
/* 108 - 1ff reserved for further expansion.	*/

#define ENT_I2O_BS_SOFTC	0x00000200	/* I2O_BS_SOFTC		*/
#define ENT_I2O_BS_RQST		0x00000201	/* i2o_bs_rqst_t	*/
#define	ENT_I2O_REQUEST		0x00000202	/* I2O request message */
#define	ENT_I2O_REPLY		0x00000203



#define ENT_STRUCT_UNKNOWN	0xffffffff	/* Unknown structure 	*/



/*
 * I2O_ERR_ENTRY.ent_pri
 * Defines whether you always want to see when you run uerf or
 * only when you do a full error report
 */

#define PRI_BRIEF_REPORT	0x00000001
#define PRI_FULL_REPORT		0x00000002


/*
 * The peripherial drivers error types...
 */
#define I2O_INFORMATIONAL	0x00000001	/* Informational message */
#define I2O_SOFTERR		0x00000002	/* Soft error		 */
#define I2O_HARDERR		0x00000004	/* Hard error		 */
#define I2O_SOFTWARE		0x00000008	/* Software detected 	 */
#define I2O_DUMP_ALL		0x00000010	/* Dump all structures	 */



/* ---------------------------------------------------------------------- */

/*
This Macro is an attempt to present a consistant error logging
interface to the various modules within the I2O subsystem.  Using this
macro will allow all the places within the modules that need to report
and log error information to use the same macro call and arguments.  It
was decided to allow the individual modules to contain their own error
logging routine specific to that module.  This local error logging
routine is called via the macro through the static, per source file,
"(*local_errorlog)()" pointer.  The reason for this indirection is to
allow the same macro to be used within the modules.  The macro will
always call the local error logging routine though the local pointer.

All the source files will need to have the following declaration of the 
error log routine pointer:

static void (*local_errorlog)();

Within the initiailization code for that module or as part of the
initialized data the pointer is loaded with the local handler address:

extern void sx_errorlog();
static void (*local_errlog)() = sx_errorlog; 

Within common modules it is possible to have the local pointer contain the
error logger handler from the another module. 

Currently the arguments to the macro contain different types of
information.  By convention the first three arguments in the macro are
pre-defined.  The first argument, FUNC, is the function name string.
The second argument, MSGSTR, is the message string from the fuction
that will be sent to the error logger.   This second argument also
unique in that if the macro is "undefined" the message string is
reported to the console.  The third argument, EFLAGS, contains error
flags for the local handler.  The remaining arguments, ARG4 - ARG7, are
i2o_bs_rqst_t *, I2O_BS_SOFTC *, (optional null), and controller number
and device/tid associated with this controller.

Note: there is a 1:1 relationship between the controller/device

A primary reason for the use of this macro is to keep the reported
message string with the module code that reported it to begin with.
*/

#if defined(I2OERRLOG) && !defined(lint)
#   define I2O_ERROR( FUNC, MSGSTR, EFLAGS, ARG4, ARG5, ARG6, ARG7) 	 \
    {                                                                    \
	/* VARARGS */                                                    \
	(void)(*local_errlog)( FUNC, MSGSTR, EFLAGS, ARG4, ARG5, ARG6,	 \
	ARG7); 								 \
    }
#else /*  I2OERRLOG and not lint */ 
#   define I2O_ERROR( FUNC, MSGSTR, EFLAGS, ARG4, ARG5, ARG6, ARG7 ) 	 \
    {                                                                    \
	/* VARARGS */                                                    \
	printf( "%s: %s\n",                                              \
	    (((FUNC)   != (char *)NULL) ? (FUNC)   : "I2O Subsystem" ),  \
	    (((MSGSTR) != (char *)NULL) ? (MSGSTR) : "Unknown Error" ) );\
    }
#endif /* I2OERRLOG and not lint */

#endif /* _I2O_LOGGER_H_ */
