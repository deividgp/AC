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
/* @(#)prom.h	9.2  (ULTRIX)        10/28/91    */

/************************************************************************
 *									*
 *			Copyright (c) 1990 by				*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any  other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or  reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

/*
 * Modification History: /sys/sas/alpha/prom.h
 *
 * 21-Oct-91 -- Andrew L. Duane
 *	Major fixes to upgrade to the Console rev. 3.2 specification
 *	New calling sequences, arguments, function codes, and register usage.
 *	NOTE: some of these are not yet implemented: see prom.c
 *
 * 13-Nov-90 -- Tim Burke
 *	Created this file for Alpha console support.
 */

#ifndef __PROM_INCLUDE__
#define __PROM_INCLUDE__

/*
 * The console routines are dispatched through the DISPATCH routine by
 * passing function codes and an argument list.  The various routines and
 * their function code assignments are defined in this module.
 */

#define DISPATCH prom_dispatcher	/* tim fix - no doubt will change   */

/*
 * UPDATE_FLASH_TIME is the number of seconds that we will
 * wait (overall) before we decide whether one of the callbacks
 * that writes nonvolatile storage (PROM_SAVEENV, PROM_WRITE_EEROM)
 * has failed due to timeout expiration.
 */
#define UPDATE_FLASH_TIME 30

/*
 * Console routine function codes.
 */
#define CONS_GETC		1	/* Get char from console terminal   */
#define CONS_PUTS		2	/* Put string to console terminal   */
#define CONS_RESET_TERM		3	/* Reset console term to defaults   */
#define CONS_SET_TERM_INTR	4	/* Set console terminal interrupts  */
#define CONS_SET_TERM_CTRL	5	/* Set console terminal controls    */
#define CONS_PROCESS_KEYCODE	6	/* Process/translate keycode	    */
#define CONS_RESERVED_7		7	/* reserved */
#define CONS_RESERVED_8		8	/* reserved */
#define CONS_RESERVED_9		9	/* reserved */
#define CONS_RESERVED_10	10	/* reserved */
#define CONS_RESERVED_11	11	/* reserved */
#define CONS_RESERVED_12	12	/* reserved */
#define CONS_RESERVED_13	13	/* reserved */
#define CONS_RESERVED_14	14	/* reserved */
#define CONS_RESERVED_15	15	/* reserved */
#define CONS_OPEN		16	/* Open IO device for access        */
#define CONS_CLOSE		17	/* Close IO device for access       */
#define CONS_IOCTL		18	/* Device specific IO operations    */
#define CONS_READ		19	/* Read IO device		    */
#define CONS_WRITE		20	/* Write IO device		    */
#define CONS_RESERVED_21	21	/* reserved */
#define CONS_RESERVED_22	22	/* reserved */
#define CONS_RESERVED_23	23	/* reserved */
#define CONS_RESERVED_24	24	/* reserved */
#define CONS_RESERVED_25	25	/* reserved */
#define CONS_RESERVED_26	26	/* reserved */
#define CONS_RESERVED_27	27	/* reserved */
#define CONS_RESERVED_28	28	/* reserved */
#define CONS_RESERVED_29	29	/* reserved */
#define CONS_RESERVED_30	30	/* reserved */
#define CONS_RESERVED_31	31	/* reserved */
#define CONS_SETENV		32	/* Set an environment variable	    */
#define CONS_CLEARENV		33	/* Delete an evnoronment variable   */
#define CONS_GETENV		34	/* Get an environment variable	    */
#define CONS_SAVEENV		35	/* Save environment variables	    */
#define	CONS_PSWITCH		48	/* Switch primary processor (MP)    */
#define CONS_SAVE_ERROR_LOG     49      /* Write errorlog data to non-volatile
                                            storage                         */
#define CONS_WRITE_EEROM        51      /* 0x33 - write FRU data to eerom   */
#define CONS_READ_EEROM         52      /* 0x34 - read FRU data from eerom  */

/* #define CONS_FIXUP		16	/* Does virtual address fixup       */

/*
 * The DISPATCH routine is used to call the console routine.  
 *
 * Notes: The dispatch routine is a generic interface to the console
 * routines.  The first argument is always one of the function codes.
 * Following the function code is 0 to 5 parameters.
 *
 * tim fix -
 * I'm not sure if it is necessary to pass null parameters in the case
 * where all 5 parameters are needed.  I suppose this will  depend on how
 * the dispatch routine is implemented and register conventions/usage.
 * For now I'll assume that a full list of 5 parameters must always be
 * provided.
 *
 * ald -
 * The last two arguments are reserved for IOCTL only. Propagate them
 * for all routines, even if unused. Comment above is right: pass them all.
 *
 * Dispatch() calling sequence:
 *	arg0 is function code: e.g. CONS_GETC; goes into r16 (s0)
 *	arg1->5 are arg0->4 of caller; go into r17-r21 (s1-s5)
 *	r26 (k0) is used for the return address back to DISPATCH.
 *	r25 (t9) isn't used, even though the spec says it is.
 */

/* char = getc(unit) */
#define PROM_GETC(P_UNIT) \
	DISPATCH(CONS_GETC, P_UNIT, 0, 0, 0, 0)

/* wcount = puts(unit, string, length) */
#define PROM_PUTS(P_UNIT, P_ADDRESS, P_LENGTH) \
	DISPATCH(CONS_PUTS, P_UNIT, P_ADDRESS, P_LENGTH, 0, 0)

/* status = reset_term(unit) */
#define PROM_RESET_TERM(P_UNIT)	\
	DISPATCH(CONS_RESET_TERM, P_UNIT, 0, 0, 0, 0)

/* status = set_term_intr(unit, mask) */
#define PROM_SET_TERM_INTR(P_UNIT, P_MASK) \
	DISPATCH(CONS_SET_TERM_INTR, P_UNIT, P_MASK, 0, 0, 0)

/* status = set_term_ctrl(unit, crb) */
#define PROM_SET_TERM_CTRL(P_CRB) \
	DISPATCH(CONS_SET_TERM_CTRL, P_UNIT, P_CRB, 0, 0, 0)

/* char = process_keycode(unit, keycode, again) */
#define PROM_PROCESS_KEYCODE(P_UNIT, P_KEYCODE, P_AGAIN) \
	DISPATCH(CONS_PROCESS_KEYCODE, P_UNIT, P_KEYCODE, P_AGAIN, 0, 0)

/* channel = open(devstr, length) */
#define PROM_OPEN(P_DEVSTR, P_LENGTH) \
	DISPATCH(CONS_OPEN, P_DEVSTR, P_LENGTH, 0, 0, 0)

/* status = close(channel) */
#define PROM_CLOSE(P_CHANNEL) \
	DISPATCH(CONS_CLOSE, P_CHANNEL, 0, 0, 0, 0)

/* count = ioctl(channel, param2, param3, param4, param5) */
#define PROM_IOCTL(P_CHANNEL, P_PARAM2, P_PARAM3, P_PARAM4, P_PARAM5) \
	DISPATCH(CONS_IOCTL, P_CHANNEL, P_PARAM2, P_PARAM3, P_PARAM4, P_PARAM5)

/* rcount = read(channel, count, address, block) */
#define PROM_READ(P_CHANNEL, P_COUNT, P_ADDRESS, P_BLOCK) \
	DISPATCH(CONS_READ, P_CHANNEL, P_COUNT, P_ADDRESS, P_BLOCK, 0)

/* wcount = write(channel, count, address, block) */
#define PROM_WRITE(P_CHANNEL, P_COUNT, P_ADDRESS, P_BLOCK) \
	DISPATCH(CONS_WRITE, P_CHANNEL, P_COUNT, P_ADDRESS, P_BLOCK, 0)

/* status = setenv(id, value, length) */
#define PROM_SETENV(P_ID, P_VALUE, P_LENGTH) \
	DISPATCH(CONS_SETENV, P_ID, P_VALUE, P_LENGTH, 0, 0)

/* status = clearenv(id, value, length) */
#define PROM_CLEARENV(P_ID, P_BUFFER, P_BUFLEN) \
	DISPATCH(CONS_CLEARENV, P_ID, P_BUFFER, P_BUFLEN, 0, 0)

/* status = getenv(id, buffer, length) */
#define PROM_GETENV(P_ID, P_BUFFER, P_BUFLEN) \
	DISPATCH(CONS_GETENV, P_ID, P_BUFFER, P_BUFLEN, 0, 0)

/* status = save_env() */
#define PROM_SAVEENV() \
	DISPATCH(CONS_SAVEENV, 0, 0, 0, 0, 0)

/* status = prom_pswtch(action) */
#define PROM_PSWTCH(P_ACTION, P_CPUID) \
	DISPATCH(CONS_PSWTCH, P_ACTION, P_CPUID, 0, 0, 0)

/* status = save_error_log(device, size, buffer, classtype, flag) */
#define SAVE_ERROR_LOG(P_ID, P_BUFLEN, P_BUFFER, CLASSTYPE, FLAG) \
        DISPATCH(CONS_SAVE_ERROR_LOG, P_ID, P_BUFLEN, P_BUFFER, CLASSTYPE, FLAG)

/* status = prom_write_eerom(buffer, length, dpr_offset, eerom_offset) */
#define PROM_WRITE_EEROM(P_BUFFER, P_LENGTH, P_FRU_ID, P_OPCODE) \
        DISPATCH(CONS_WRITE_EEROM, P_BUFFER, P_LENGTH, P_FRU_ID, P_OPCODE)

/* status = prom_read_eerom(buffer, length, dpr_offset, eerom_offset) */
#define PROM_READ_EEROM(P_BUFFER, P_LENGTH, P_FRU_ID, P_OPCODE) \
        DISPATCH(CONS_READ_EEROM, P_BUFFER, P_LENGTH, P_FRU_ID, P_OPCODE)

/* This is BROKEN! FIXUP uses a separate entry point from DISPATCH !!! */
#define PROM_FIXUP() \
 	DISPATCH(CONS_FIXUP, 0, 0, 0, 0, 0)

/*
 * The following constants are used to examine the status of prom calls.
 */
#define CONS_WRITE_ERROR	0x8000000000000000
#define CONS_WRITE_EOT		0x4000000000000000
#define CONS_WRITE_ILI		0x2000000000000000
#define CONS_WRITE_EOM		0x1000000000000000
#define CONS_READ_ERROR		0x8000000000000000
#define CONS_READ_EOF		0x4000000000000000
#define CONS_READ_ILI		0x2000000000000000
#define CONS_READ_EOM		0x1000000000000000
#define GETC_RCV_OK	0	/* Success, character received 		*/
#define GETC_NOT_READY	2	/* Not ready for reception		*/
#define GETC_RCV_ERR	3	/* Character received with error	*/

/* defines for return status of PROM_SAVEENV */
#define CONS_SAVEENV_SUCCESS	0x0000000000000000
#define CONS_SAVEENV_PARTIAL	0x2000000000000000	/* some vars stored in nvr, 
							 * additional vars to be
							 * stored in nvr
							 */
#define	CONS_SAVEENV_UNSUP	0xc000000000000000	/* saveenv unsupported */
#define CONS_SAVEENV_FAIL	0xe000000000000000	/* saveenv failed */

/* defines for return status of PROM_GETENV */
#define CONS_GETENV_SUCCESS	0x0000000000000000
#define CONS_GETENV_FAILURE	0xc000000000000000	/* variable not recognized */
#define CONS_GETENV_TRUNC	0x2000000000000000	/* value truncated */
#define CONS_GETENV_STATUS_MASK 0xffffffff00000000	/* lower 32 bits are num chars copied */

/* defines for return status of WRITE/READ_EEROM */
#define CONS_EEROM_STATUS_MASK  0xf000000000000000      /* for masking off byte count    */
#define CONS_EEROM_SUCCESS      0x0000000000000000
#define CONS_EEROM_ILL_BUFSIZE  0x1000000000000000      /* buffer size exceeds 256 bytes */
#define CONS_EEROM_FRU_ID_INVAL 0x2000000000000000      /* invalid fru_id specified      */
#define CONS_EEROM_ACCESS_FAIL  0x3000000000000000      /* FRU EEROM cannot be accessed  */
#define CONS_EEROM_MEM_FAIL     0x4000000000000000      /* cannot access virtual address */
#define CONS_EEROM_SDD_BUFSIZE  0x5000000000000000      /* buffer size != 88 bytes for SDD logs */
#define CONS_EEROM_IN_PROG      0x6000000000000000      /* Command in progress           */
#define CONS_EEROM_ILL_OPCODE   0x8000000000000000      /* unsupported operation code    */
#define CONS_EEROM_BUSY         0x9000000000000000      /* busy, retry later             */
 
/*
 * Assume that there is a maximum sized output string to protect from the
 * case where cprintf is called with an improperly terminated string.
 */
#define MAX_CONSOLE_STRING	1023	/* Maximum size of output string */

/*
 * This is an internal buffer used to pass back null terminated environment
 * variable values with getenv.
 */
#define MAX_ENVIRON_LENGTH	255

/* Status returned from prom_saveenv */
#define SAVE_ENV_PARTIAL	(int)1
#define SAVE_ENV_SUCCESS	(int)0
#define SAVE_ENV_FAIL		(int)-1
#define SAVE_ENV_DISABLED       (int)-2

/* Status returned from prom_setenv */
#define SET_ENV_SUCCESS		(int)0
#define SET_ENV_FAILURE		(int)-1
#define SET_ENV_DISABLED        (int)-2

/* Status returned from prom_getenv */
#define GET_ENV_SUCCESS         (int)0
#define GET_ENV_TRUNC   	(int)1
#define GET_ENV_FAILURE 	(int)-1
#define GET_ENV_DISABLED        (int)-2

/* Status returned from prom_write_eerom/prom_read_eerom */
#define EEROM_IN_PROG   	(int)1
#define EEROM_SUCCESS   	(int)0
#define EEROM_FAIL      	(int)-1

/*
 * Three functions which set, save, and get console environment
 * variables.
 */

/*
 * int prom_setenv(char *varname, char *value, int flags)
 *
 * synopsis: sets the in memory environment variable specified by 
 *	varname to the value specified by the value parameter.
 *	The environment	variable type is validated as one 
 *	that Digital UNIX recognizes. Then an attempt is made 
 *	to set the in memory copy of the console environment 
 *	variable via SRM console callback.  According to the
 *	SRM, the environment variable is not saved in NVR after 
 *	this call.
 *
 *	The flags field will be used to determine if this
 *	functionality should be verified by the hal.  This
 *	is needed because new UNIX 4.0b EV functionality
 *	is not backward compatable with existing firmware,
 *	which doesn't compley with the SRM.
 *
 * parameters:
 *
 *	char *varname 
 *		is the type of environment variable that is 
 *		being set.
 *
 *		Alpha SRM defined varnames are:
 *		===============================
 * 		auto_action,	boot_dev,	bootdef_dev,
 *		booted_dev, 	boot_file, 	booted_file,
 *		boot_osflags, 	booted_osflags,	boot_reset,
 *		dump_dev, 	enable_audit, 	license,
 *		char_set, 	language, 	tty_dev,
 *
 *		Serial Modem Console Support varnames
 *		which are system specific:
 *		==========================
 *	 	com1_baud,	com1_modem, 	com1_flow,
 *	 	com1_misc,	com2_baud, 	com2_modem,
 *	 	com2_flow,	com2_misc
 *
 *		Bird only? system specific scsi varnames
 *		========================================
 *		scsiid, 	scsifast
 *
 *	char *value
 *		the value that the console environment variable
 *		is being set to.
 *
 *	int flags 
 *		This interface should be called with the PROM_VERIFY
 *		flag when:
 *
 *			an environment variable is defined as 
 *			being stored in NVR or flash ROM and
 *			it is expected to be saved there with
 *			a subsequent call to prom_saveenv
 *
 *			an environment variable is being used
 *			for the first time.
 *
 *			an environment variable is already being
 *			used with the PROM_VERIFY flag set.
 *
 *		Otherwise, this interface should be called with
 *		flags set to PROM_NOVERIFY
 *
 *		All com variables and any new vriables which 
 *		are not explicitly defined in the SRM must be
 *		called with the flag field set to PROM_VERIFY.
 *
 * return value: 
 *
 * 	SET_ENV_SUCCESS	(int)0 
 *		Console callback indicated that the environment
 *		variable was successfully saved in system memory.
 *	SET_ENV_FAILURE	(int)-1
 *		Invalid environment variable was passed or 
 *		console callback indicated it could not
 *		successfully save the environment variable.
 *
 * restrictions:
 *	
 *	This function cannot be called from ISR context.
 */
extern int	prom_setenv(char *varname, char *value, int flags);

/*
 * extern int	prom_saveenv();
 *
 * synopsis:
 *	Attempt to save, in NVR, all environment variables 
 *	which have been	set by prom_setenv(), and are supported
 *	was being stored in NVR.  This function will repeatedly
 *	attempt to save until successful or until 30 seconds
 *	expires.  This is not an unreasonable amount of	time 
 *	for a multiple copy flash rom update.  Be aware that
 *	this function could take several seconds to complete. 
 *
 *	Environment variables which are capable of being saved 
 *	in NVR are:
 *
 *		SRM defined variables:
 *
 *		auto_action,    bootdef_dev,    boot_file,
 *		boot_osflags,   boot_reset,     dump_dev,
 *		enable_audit,   char_set,       language,
 *
 *		Addtional System specific variables:
 *
 *		com1_baud,	com1_modem, 	com1_flow,
 *		com1_misc,	com2_baud,	com2_modem,
 *		com2_flow,	com2_misc
 *
 *		NOT SURE IF THESE TWO VARIABLES ARE SAVED ON THE
 *		SYSTEMS THEY ARE SUPPORTED ON.
 *
 *		scsiid,		scsifast
 *
 *
 * parameters:
 *		none
 * return value: 
 *
 * 	SAVE_ENV_PARTIAL (int)1 
 *		Indicates that the save wasn't completed after
 *		attempting to save for 30 seconds.
 * 	SAVE_ENV_SUCCESS (int)0
 *		Indicates that modified environment variable 
 *		have been successfully saved in NVR.
 * 	SAVE_ENV_FAIL (int)-1
 *		Indicidates that the console failed to save 
 *		the updated environment variables or that the 
 *		console	doesn't support	saving environment 
 *		variables.
 *		
 * restrictions:
 *		This function can block and should never be 
 *		called from ISR context.
 */
extern int	prom_saveenv();

/*
 * extern int prom_getenv(char *varname, char *value, int flags);
 *
 * Synopsis:
 *	read the in memory copy of the console environment
 *	variable specified by varname.  The in-memory copy
 *	will be copied into the char array pointed to by
 *	value.
 *
 *	The flags field will be used to determine if this
 *	functionality should be verified by the hal.  This
 *	is needed because new EV firmware functionality broke
 *	existing firmware in the field in several ways.
 *
 *	All SRM define variables should be readable.
 *	The system specific environment variables
 *	defined for serial modem console support can also be
 *	read on systems for which they are defined.  The
 *	flag field must be set to PROM_VERIFY when reading
 *	non-SRM defined EVs.
 *
 * Parameters:
 *	char *varname
 *		the console environment variable which is being
 *		read.
 *
 *		Alpha SRM defined varnames are:
 *		===============================
 * 		auto_action,	boot_dev,	bootdef_dev,
 *		booted_dev, 	boot_file, 	booted_file,
 *		boot_osflags, 	booted_osflags,	boot_reset,
 *		dump_dev, 	enable_audit, 	license,
 *		char_set, 	language, 	tty_dev,
 *
 *		Serial Modem Console Support varnames
 *		which are system specific:
 *		==========================
 *	 	com1_baud,	com1_modem, 	com1_flow,
 *	 	com1_misc,	com2_baud, 	com2_modem,
 *	 	com2_flow,	com2_misc
 *
 *		Bird only? system specific scsi varnames
 *		========================================
 *		scsiid, 	scsifast
 *
 *
 *	char *value
 *		the value of the environment variable specified
 *		by varname.  This is the output.
 *
 *	int flags 
 *		This interface should be called with the PROM_VERIFY
 *		flag when:
 *
 *			an environment variable is being used
 *			for the first time.
 *
 *			an environment variable is already being
 *			used with the PROM_VERIFY flag set.
 *
 *		Otherwise, this interface should be called with
 *		flags set to PROM_NOVERIFY
 *
 *		All com variables and any new vriables which 
 *		are not explicitly defined in the SRM must be
 *		called with the flag field set to PROM_VERIFY.
 *
 *
 * Return status:
 *	
 * 	GET_ENV_SUCCESS 
 *
 *		indicates the value of the variable returned 
 *		is accurate.
 *
 * 	GET_ENV_TRUNC 
 *
 *		indicates the variable returned is truncated.
 *
 *	GET_ENV_FAILURE
 *
 *		indicates the variable being requested is not 
 *		recognized by the console.
 */
extern int prom_getenv(char *varname, char *value, int flags);

extern void prom_get_fwevdb_entry();

#define PROM_SUCCESS (int)1
#define PROM_FAILURE (int)0

/* Validation bits dedicated to ev functions */
#define CON_EV_SAVEENV 0xFF
#define CON_EV_CLRENV  0xFE

/* flags used by prom_getenv, setenv, and saveenv */
#define PROM_CONVERT_TYPE  (long)(1<<2)

/* console environment variables should be one of the following types */
#define EV_STRING_T  (long)(1 << 0)
#define EV_BOOT_T    (long)(1 << 1)
#define EV_INT_T     (long)(1 << 2)
#define EV_TYPE_MASK (long)0x7

#define FWDBFNAME "/etc/fwevdb"

/* Record type for the table describing the console EVs */
typedef struct {
   char name[32];    /* name of the console variable */
   int  num;         /* number used to access variable */
   int  flags;       /* content info, etc. */
}evinfo_t;

/* Get the family, processor type and smm value for this system */
extern void get_fam_cpu_smm(long *fam, long *proc, long *smm, long flags);
#define CPU_BY_FAMILY 1 << 0  /* flag used to get proc base type (EV56=EV5) */

typedef struct{
   ushort_t from;
   ushort_t to;
}smmrange_t;

/* record type for firmware ev database */
typedef struct{
   uchar_t   fam;            /* platform */
   uchar_t   proc;
   smmrange_t smm[5];
   uchar_t   maj;            /* firmware rev */
   uchar_t   min;
   ushort_t  var;
   ulong_t   bits[4];        /* 256 bits for fw ev bugs */
}fwentry_t;


#endif /* __PROM_INCLUDE__ */


