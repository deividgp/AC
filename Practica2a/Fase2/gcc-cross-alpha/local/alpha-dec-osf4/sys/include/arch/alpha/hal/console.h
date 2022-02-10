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
 * @(#)$RCSfile: console.h,v $ $Revision: 1.1.4.4 $ (DEC) $Date: 1997/07/21 21:06:50 $
 */

#ifndef _ARCH_ALPHA_HAL_CONSOLE_H_
#define _ARCH_ALPHA_HAL_CONSOLE_H_


/*
 * CTB type 4 data structure and macros.
 */

/* CTB Type 4 format structure */
struct ctb_type_4 
{
	unsigned long ctb4_type;
	unsigned long ctb4_unit;
	unsigned long ctb4_rsv1;
	unsigned long ctb4_ddilen;
	unsigned long ctb4_ipl;
	unsigned long ctb4_txiv;
	unsigned long ctb4_rxiv;
	unsigned long ctb4_termtype;
	unsigned long ctb4_kbtype;
	unsigned long ctb4_kbtt;
	unsigned long ctb4_kbmt;
	unsigned long ctb4_kbstate;
	unsigned long ctb4_lastkey;
	unsigned long ctb4_usfont;
	unsigned long ctb4_mcsfont;
	unsigned long ctb4_fwidth;
	unsigned long ctb4_fheight;
	unsigned long ctb4_monwidth;
	unsigned long ctb4_monheight;
	unsigned long ctb4_mondensity;
	unsigned long ctb4_nplanes;
	unsigned long ctb4_curswidth;
	unsigned long ctb4_cursheight;
	unsigned long ctb4_nheads;
	unsigned long ctb4_opwin;
	unsigned long ctb4_hdoffset;
	unsigned long ctb4_putchar;
	unsigned long ctb4_iostate;
	unsigned long ctb4_lstate;
	unsigned long ctb4_xinfo;
	unsigned long ctb4_outslotinfo;
	unsigned long ctb4_srvroff;
	unsigned long ctb4_linepar;
	unsigned long ctb4_inslotinfo;
};

/**************************************************************************
 *
 *   Alpha SRM  RPB -- CTB Type 4 slotinfo format being used
 *
 *
 *   63                   40 39       32 31     24 23      16 15   8 7    0
 *   +----------------------+-----------+---------+----------+------+-----+
 *   |        Rsvd          | Channel # | Hose #  | Bus Type | Bus# |Slot#|
 *   +----------------------+-----------+---------+----------+------+-----+
 *
 *               Bus Type Field:
 *                               0 = TURBOchannel
 *                               1 = ISA
 *                               2 = EISA
 *                               3 = PCI
 *
 **************************************************************************/

/* macros for extracting subfields from the slotinfo fields */
#define SLOTINFO_TO_CHANNELNO(i)	(((i) >> 32) & 0xff)
#define SLOTINFO_TO_HOSENO(i)	        (((i) >> 24) & 0xff)
#define SLOTINFO_TO_BUSTYPE(i)	        (((i) >> 16) & 0xff)
#define SLOTINFO_TO_BUSNO(i)	        (((i) >>  8) & 0xff)
#define SLOTINFO_TO_SLOTNO(i)	        (((i)      ) & 0xff)

/* constants for slotinfo bus_type subfield */
#define SLOTINFO_TC	0
#define SLOTINFO_ISA	1
#define SLOTINFO_EISA	2
#define SLOTINFO_PCI	3


/*
 *  ctrl structure private field used
 *  for console_attach routine in device
 *  drivers that can be the system console
 *  (graphics and serial drivers).
 *
 */
#define console_attach  private[3]

/*
 *  consDev values
 *
 *  consDev indicates whether system is using 
 *  a graphics or serial console.
 */
extern int consDev;

/*
 *  structure to support acquistion of firmware 
 *  revision information by getsysinfo().
 */

struct firmware_rev {
	long firmware_major;
	long firmware_minor;
	long firmware_variation;
};

/*
 *  structure to support acquistion of palcode 
 *  revision information by getsysinfo().
 */

struct palcode_rev {
	long palcode_os_type;
	long palcode_major;
	long palcode_minor;
	long palcode_variation;
};

#define CONS_DEV      0x01
#define GRAPHIC_DEV   0x02

/*
 *  printstate values
 *  are defined in cpu.h
 */ 

/*
 * definitions needed for translation to and from console network
 * bootstrings.
 */

struct net_console2unix{
   char *driver;
   int bus_type;
};

/* table for the translation is in console.c */
extern struct net_console2unix net_console2unix_table[];

/* Get the Unix driver name for a console network device type */
#define NET_CONSOLE2UNIX(bustype, devtype, unixname) {        \
         int i=0;                                             \
         struct net_console2unix *ptr=net_console2unix_table; \
         while(i<devtype && ptr[i].driver[0] != 0) i++;         \
         strcpy(unixname, ptr[i].driver);                     \
        }

/* Get the Console network device type for a unix driver
 * devtype contains the return value, -1 on failure */
#define NET_UNIX2CONSOLE(ctlrptr, devtype) {                     \
         int i=0;                                                \
         struct net_console2unix *ptr=net_console2unix_table;    \
         devtype=-1;                                             \
         while(ptr[i].driver[0] != 0 ) {                           \
            if (strcmp(ptr[i].driver, ctlrptr->ctlr_name)==0) {  \
               if (ptr[i].bus_type == DRIVER_WILDNUM ||          \
                   ptr[i].bus_type == ctlrptr->bus_hd->bus_type) \
                  devtype=i;                                     \
	    }                                                    \
            i++;                                                 \
         }                                                       \
        }

/*
 * function prototypes 
 */
void hal_pci_cons_ctlrstr( int bus_probe_alg_type, char *device_string,
				 struct controller *ctlr, char *protocol,
				 u_int remoteid, u_int unit);


#endif /*_ARCH_ALPHA_HAL_CONSOLE_H_ */
