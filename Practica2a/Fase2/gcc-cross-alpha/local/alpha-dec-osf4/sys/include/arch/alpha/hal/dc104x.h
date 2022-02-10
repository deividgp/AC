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
#pragma ident "@(#)$RCSfile: dc104x.h,v $ $Revision: 1.1.8.6 $ (DEC) $Date: 1999/01/13 21:49:15 $"



#ifndef __ARCH_ALPHA_HAL_DC104X_H__
#define __ARCH_ALPHA_HAL_DC104X_H__


/*
 * -------------------------
 * DC104X-PCIA Address Map:
 * -------------------------
 *
 * 44-bit Physical I/O Space Per PCI Node (8GBytes per) -- 48-bit VA mode
 * ----------------------------------------------------
 * 800 0000 0000 - 801 FFFF FFFF	- I/O Space for PCI0
 * 802 0000 0000 - 803 FFFF FFFF	- I/O Space for PCI1
 * 804 0000 0000 - 805 FFFF FFFF	- I/O Space for PCI2
 * 806 0000 0000 - 806 FFFF FFFF	- I/O Space for PCI3
 *
 * 41-bit Physical I/O Space Per PCI Node (8GBytes per) -- 43-bit VA mode
 * ----------------------------------------------------
 * 100 0000 0000 - 101 FFFF FFFF	- I/O Space for PCI0
 * 102 0000 0000 - 103 FFFF FFFF	- I/O Space for PCI1
 * 104 0000 0000 - 105 FFFF FFFF	- I/O Space for PCI2
 * 106 0000 0000 - 106 FFFF FFFF	- I/O Space for PCI3
 *
 *
 * CPU to Physical PCI Address Mapping:
 * ------------------------------------
 * 
 * +---+-------+-----+--+--+--+--+--+--+---------------+----------+-----+
 * | 1 |  MBZ  | PCI |  |  |  |  |  |  | Byte Aligned  | Byte Len | Zero|
 * |   |       | SEL |  |  |  |  |  |  | I/O Address   |   Field  |     |
 * +---+-------+-----+--+--+--+--+--+--+---------------+----------+-----+
 *  XX  39   35 34 33 32 31 30 29 28 27 26            5 4        3  2  0
 *   
 * <XX> - I/O Select (Always 1 for direct I/O access)
 *	- bit 43 in 48-bit VA mode;
 *	- bit 40 in 43-bit VA mode.
 *
 * <39-35> - Must be Zeroes.
 *
 * <34:33> - PCI Bus Select
 *	
 * <32-24> - PCI Address Space
 *	0.xxxx.xxxx = PCI Memory Space		  4GB
 *	1.00xx.xxxx = TIG Bus			  1GB
 *	1.1xxx.xxxx = Pchip CSR Space		256MB
 *	1.1010.xxxx = Cchip CSR Space		256MB
 *	1.1011.xxxx = Dchip CSR Space		256MB
 *	1.1111.1xxx = IACK/Special Cycle	 64MB
 *	1.1111.110x = PCI IO Space		 32MB
 *	1.1111.1110 = PCI Configuration Space	 16MB
 */

/*
 * -------------------------
 * DC104X-PCIA Address Map: (continued)
 * -------------------------
 *
 * ---------------------------------------------------
 * CPU to PCI Physical Address Mapping for PCIy Bridge 
 * ---------------------------------------------------
 *
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * x0(y*2).0000.0000		0000.0000 - FFFF.FFFF	PCIx Memory Space 
 * - x0(y*2).FFFF.FFFF					(4GB; linear)
 *
 * x0[(y*2)+1].FC00.0000	0000.0000 - 01FF.FFFF	PCIx IO Space 
 * - x0[(y*2)+1].FDFF.FFFF				(32MB; linear)
 *
 * x0[(y*2)+1].FE00.0000	0000.0000 - 00FF.FFFF	PCIx Configuration Space 
 * - x0[(y*2)+1].FEFF.FFFF				(16MB; linear)
 *
 * x0[(y*2)+1].F800.0000	0000.0000 - 03FF.FFFF	PCIx IACK/Special Space 
 * - x0[(y*2)+1].FBFF.FFFF				(64MB; linear)
 *
 * x0[(y*2)+1].8000.0000		N/A		PCIx Pchip CSRs 
 * - x0[(y*2)+1].8FFF.FFFF				(256MB; linear)
 *
 * x0[(y*2)+1].A000.0000		N/A		Cchip CSRs 
 * - x0[(y*2)+1].AFFF.FFFF				(256MB; linear)
 *
 * x0[(y*2)+1].B000.0000		N/A		Dchip CSRs 
 * - x0[(y*2)+1].BFFF.FFFF				(256MB; linear)
 *
 * x0[(y*2)+1].FF00.0000		N/A		Unused/Reserved.
 * - x0[(y*2)+1].FFFF.FFFF
 *
 */

 /* where x = 8 when OS in 48-bit VA mode;
  *         = 1 when OS in 43-bit VA mode.
  * where y = PCI bus-hose number, which can be 0,1,2,3.
  */

/*
 * The following defines are for use in pointer arithmetic.
 */
#define DC104X_CSR_BYTE_STRIDE  0x40    /* byte stride between registers in CSR space */
#define DC104X_CSR_LONG_STRIDE  0x08    /* long stride between registers in CSR space */



    struct tig_regs { /* Offset 3000.0000 from IO base */
	unsigned char	trr;		/* offset 000 */
	char		pad1[0x3f];
	unsigned char	smir;		/* offset 040 */
	char		pad2[0x3f];
	unsigned char	cpuir;    	/* offset 080 */
	char		pad3[0x3f];
	unsigned char	psir;		/* offset 0C0 */
	char		pad4[0x3f];
	unsigned char	mod_info;    	/* offset 100 */
	char		pad5[0x3f];
	unsigned char	clk_info;    	/* offset 140 */
	char		pad6[0x3f];
	unsigned char	chip_info;	/* offset 180 */
	char		pad7[0x7f];

	unsigned char	tpcr;   	/* offset 200 */
	char		pad9[0x7f];

	unsigned char	pll_data;   	/* offset 280 */
	char		pad11[0x3f];
	unsigned char	pll_clk;   	/* offset 2C0 */
	char		pad12[0x3f];
	unsigned char	ev6_init;   	/* offset 300 */
	char		pad13[0x3f];
	unsigned char	csleep;		/* offset 340 */
	char		pad14[0x3f];
	unsigned char	smcr;		/* offset 380 */
	char		pad15[0x3f];
	unsigned char	ttcr;		/* offset 3c0 */
	char		pad16[0x3f];
	unsigned char	clr_irq5;  	/* offset 400 */
	char		pad17[0x3f];
	unsigned char	clr_irq4;	/* offset 440 */
	char		pad18[0x3f];
	unsigned char	clr_pwr_flt_det; /* offset 480 */
	char		pad19[0x3f];
	unsigned char	clr_temp_warn;	/* offset 4C0 */
	char		pad20[0x3f];
	unsigned char	clr_temp_fail;	/* offset 500 */
	char		pad21[0xbf];

	unsigned char	ev6_halt;	/* offset 5c0 */
	char		pad22[0x3f];
	unsigned char	srcr0;  	/* offset 600 */
	char		pad23[0x3f];
	unsigned char	srcr1;  	/* offset 640 */
	char		pad24[0xbf];

        unsigned char   frar0;          /* offset 700 */
        char            pad25[0x3f];
        unsigned char   frar1;          /* offset 740 */
        char            pad26[0xbf];

        unsigned char   fwmr0;          /* offset 800 */
        char            pad27[0x3f];
        unsigned char   fwmr1;          /* offset 840 */
        char            pad28[0x3f];
        unsigned char   fwmr2;          /* offset 880 */
        char            pad29[0x3f];
        unsigned char   fwmr3;          /* offset 8C0 */
        char            pad30[0x13f];

        unsigned char   ipcr0;          /* offset A00 */
        char            pad31[0x3f];
        unsigned char   ipcr1;          /* offset A40 */
        char            pad32[0x3f];
        unsigned char   ipcr2;          /* offset A80 */
        char            pad33[0x3f];
        unsigned char   ipcr3;          /* offset AC0 */
        char            pad34[0x3f];
        unsigned char   ipcr4;          /* offset B00 */

    };

/*
 * ------------------------
 * DC104X-PCI Address Map: (continued)
 * ------------------------
 *
 * List of PCI address spaces for the 2 possible PCI busses:
 *
 * +------+
 * | PCI0 |
 * +------+
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * x00.0000.0000		0000.0000 - FFFF.FFFF	PCIx Memory Space 
 * - x00.FFFF.FFFF					(4GB; linear)
 *
 * x01.FC00.0000		0000.0000 - 01FF.FFFF	PCIx IO Space 
 * - x01.FDFF.FFFF					(32MB; linear)
 *
 * x01.FE00.0000		0000.0000 - 00FF.FFFF	PCIx Configuration Space 
 * - x01.FEFF.FFFF					(16MB; linear)
 *
 * x01.F800.0000		0000.0000 - 03FF.FFFF	PCIx IACK/Special Space 
 * - x01.FBFF.FFFF					(64MB; linear)
 *
 * x01.8000.0000			N/A		PCIx Pchip CSRs 
 * - x01.8FFF.FFFF					(256MB; linear)
 *
 * x01.A000.0000			N/A		Cchip CSRs 
 * - x01.AFFF.FFFF					(256MB; linear)
 *
 * x01.B000.0000			N/A		Dchip CSRs 
 * - x01.BFFF.FFFF					(256MB; linear)
 *
 * x01.FF00.0000			N/A		Unused/Reserved.
 * - x01.FFFF.FFFF
 *
 * +------+
 * | PCI1 |
 * +------+
 * CPU Address Range		PCI Address Range	PCI Address Space
 * ------------------------	---------------------	------------------------
 * x02.0000.0000		0000.0000 - FFFF.FFFF	PCIx Memory Space 
 * - x02.FFFF.FFFF					(4GB; linear)
 *
 * x03.FC00.0000		0000.0000 - 01FF.FFFF	PCIx IO Space 
 * - x03.FDFF.FFFF					(32MB; linear)
 *
 * x03.FE00.0000		0000.0000 - 00FF.FFFF	PCIx Configuration Space 
 * - x03.FEFF.FFFF					(16MB; linear)
 *
 * x03.F800.0000		0000.0000 - 03FF.FFFF	PCIx IACK/Special Space 
 * - x03.FBFF.FFFF					(64MB; linear)
 *
 * x03.8000.0000			N/A		PCIx Pchip CSRs 
 * - x03.8FFF.FFFF					(256MB; linear)
 *
 * x03.A000.0000			N/A		Cchip CSRs 
 * - x03.AFFF.FFFF					(256MB; linear)
 *
 * x03.B000.0000			N/A		Dchip CSRs 
 * - x03.BFFF.FFFF					(256MB; linear)
 *
 * x03.FF00.0000			N/A		Unused/Reserved.
 * - x03.FFFF.FFFF
 */

 /* where x = 8 when OS in 48-bit VA mode;
  *         = 1 when OS in 43-bit VA mode.
  */


/*
 * DC104X PCI Bus Bridge CSRs
 *
 * Address Map Overview:
 *
 * Offset		Selected Space
 * ----------------	-------------------------------------------------
 * 0x0			DMA window base 0
 * 0x40			DMA window base 1
 * 0x80			DMA window base 2
 * 0xc0			DMA window base 3
 * 0x100		DMA window mask 0
 * 0x140		DMA window mask 1
 * 0x180		DMA window mask 2
 * 0x1c0		DMA window mask 3
 * 0x200		DMA Translated base 0
 * 0x240		DMA Translated base 1
 * 0x280		DMA Translated base 2
 * 0x2c0		DMA Translated base 3
 * 0x300		Pchip control register	 	(console only)
 * 0x340		PCI Master Latency Timer 	(console only)
 * 0x380		Reserved
 * 0x3c0		Pchip Error Register
 * 0x400		Pchip Error Mask Register
 * 0x440		Pchip Error Set Register
 * 0x480		Translation Buffer Invalidate Virtual register
 * 0x4c0		Translation Buffer Invalidate All register
 * 0x500		Pchip Monitor Control 
 * 0x540		Pchip Monitor Count
 *
 * Registers that are marked "console only" should not be accessed
 * by the operating system
 */
struct pchip_regs { /* offset 0x8000.000 from IO base */
	unsigned long	wsba0;	/* offset 000 */
	char		pad1[0x38];
	unsigned long	wsba1;	/* offset 040 */
	char		pad2[0x38];
	unsigned long	wsba2;	/* offset 080 */
	char		pad3[0x38];
	unsigned long	wsba3;	/* offset 0C0 */
	char		pad4[0x38];
	unsigned long	wsm0;	/* offset 100 */
	char		pad5[0x38];
	unsigned long	wsm1;	/* offset 140 */
	char		pad6[0x38];
	unsigned long	wsm2;	/* offset 180 */
	char		pad7[0x38];
	unsigned long	wsm3;	/* offset 1C0 */
	char		pad8[0x38];
	unsigned long	tba0;	/* offset 200 */
	char		pad9[0x38];
	unsigned long	tba1;	/* offset 240 */
	char		pad10[0x38];
	unsigned long	tba2;	/* offset 280 */
	char		pad11[0x38];
	unsigned long	tba3;	/* offset 2C0 */
	char		pad12[0x38];
	unsigned long	pctl;	/* offset 300 */
	char		pad13[0x38];
	unsigned long	plat;	/* offset 340 */
	char		pad14[0x38];
	unsigned long	rsvd;	/* offset 380 */
	char		pad15[0x38];
	unsigned long	perror;	/* offset 3C0 */
	char		pad16[0x38];
	unsigned long	perrmask; /* offset 400 */
	char		pad17[0x38];
	unsigned long	perrset;  /* offset 440 */
	char		pad18[0x38];
	unsigned long	tlbiv; /* offset 480 */
	char		pad19[0x38];
	unsigned long	tlbia; /* offset 4C0 */
	char		pad20[0x38];
	unsigned long	pmonctl; /* offset 500 */
	char		pad21[0x38];
	unsigned long	pmoncnt; /* offset 540 */
};
/*
 * DC104X Cchip CSRs
 *
 * Address Map Overview:
 *
 * Offset		Selected Space
 * ----------------	-------------------------------------------------
 * 0x0			Cchip Configuration Register	(console only)
 * 0x40			Memory Timing Register		(console only)
 * 0x80			Cchip Miscellaneous register	
 * 0xc0			Memory Presence Detect Register (console only)
 * 0x100		Array Address 0 register	(console only)
 * 0x140		Array Address 1 register	(console only)
 * 0x180		Array Address 2 register	(console only)
 * 0x1c0		Array Address 3 register	(console only)
 * 0x200		Device Interrupt Mask 0 register	
 * 0x240		Device Interrupt Mask 1 register
 * 0x280		Device Intr request 0 register	(console only)
 * 0x2c0		Device Intr request 1 register	(console only)
 * 0x300		Device Raw Intr request register(console only)
 * 0x340		Probe Enable register		(console only)
 * 0x380		Interval Ignore Count 0 register    
 * 0x3c0		Interval Ignore Count 1 register
 * 0x400		Memory Programming 0 register	(console only)    
 * 0x440		Memory Programming 1 register	(console only)    
 * 0x480		Memory Programming 2 register	(console only)    
 * 0x4c0		Memory Programming 3 register	(console only)
 * 0x500		Debug MUX control register	(console only)
 * 0x540		Reserved
 * 0x580		TIGBus Timing Register		(console only)
 * 0x5c0		TIGBus Device Timing register	(console only)
 * 
 *     		Registers only available on Typhoon (C4chip)
 * 0x600		Device Interrupt Mask 2 register	
 * 0x640		Device Interrupt Mask 3 register
 * 0x680		Device Intr request 2 register	(console only)
 * 0x6c0		Device Intr request 3 register	(console only)
 * 0x700		Interval Ignore Count 2 register    
 * 0x740		Interval Ignore Count 3 register
 *
 * Registers that are marked "console only" should not be accessed
 * by the operating system
 */
struct cchip_regs { /* offset 0xA000.0000 from IO base */
	unsigned long	csc;	/* offset 000 */
	char		pad1[0x38];
	unsigned long	mtr;	/* offset 040 */
	char		pad2[0x38];
	unsigned long	misc;	/* offset 080 */
	char		pad3[0x38];
	unsigned long	mpd;	/* offset 0C0 */
	char		pad4[0x38];
	unsigned long	aar0;	/* offset 100 */
	char		pad5[0x38];
	unsigned long	aar1;	/* offset 140 */
	char		pad6[0x38];
	unsigned long	aar2;	/* offset 180 */
	char		pad7[0x38];
	unsigned long	aar3;	/* offset 1C0 */
	char		pad8[0x38];
	unsigned long	dim0;	/* offset 200 */
	char		pad9[0x38];
	unsigned long	dim1;	/* offset 240 */
	char		pad10[0x38];
	unsigned long	dir0;	/* offset 280 */
	char		pad11[0x38];
	unsigned long	dir1;	/* offset 2C0 */
	char		pad12[0x38];
	unsigned long	drir;	/* offset 300 */
	char		pad13[0x38];
	unsigned long	prben;	/* offset 340 */
	char		pad14[0x38];
	unsigned long	iic0;	/* offset 380 */
	char		pad15[0x38];
	unsigned long	iic1;	/* offset 3C0 */
	char		pad16[0x38];
	unsigned long	mpr0;	/* offset 400 */
	char		pad17[0x38];
	unsigned long	mpr1;	/* offset 440 */
	char		pad18[0x38];
	unsigned long	mpr2;	/* offset 480 */
	char		pad19[0x38];
	unsigned long	mpr3;	/* offset 4C0 */
	char		pad20[0x38];
	unsigned long	mctl;	/* offset 500 */
	char		pad21[0x38];
	unsigned long	rsvd;	/* offset 540 */
	char		pad22[0x38];
	unsigned long	ttr;	/* offset 580 */
	char		pad23[0x38];
	unsigned long	tdr;	/* offset 5C0 */
	char		pad24[0x38];
	unsigned long	dim2;	/* offset 600 */
	char		pad25[0x38];
	unsigned long	dim3;	/* offset 640 */
	char		pad26[0x38];
	unsigned long	dir2;	/* offset 680 */
	char		pad27[0x38];
	unsigned long	dir3;	/* offset 6c0 */
	char		pad28[0x38];
	unsigned long	iic2;	/* offset 700 */
	char		pad29[0x38];
	unsigned long	iic3;	/* offset 740 */

};
/*
 * DC104X Dchip CSRs
 *
 * Address Map Overview:
 *
 * Offset		Selected Space
 * ----------------	-------------------------------------------------
 * 0x800		Dchip Configuration register	(console only) 
 * 0x840		System Timing Register		(console only)
 * 0x880		Dchip revision register
 *
 * Registers that are marked "console only" should not be accessed
 * by the operating system
 */
struct dchip_regs { /* offset 0xB000.0000 from IO base */
	unsigned long	pad1[256];
	unsigned long	dsc;	/* offset 0800*/
	char		pad2[0x38];
	unsigned long	str;	/* offset 0840*/
	char		pad3[0x38];
	unsigned long	drev;	/* offset 0880*/
};

/*
 * Structures for chip-csr error logs
 */
struct elr_dc104x_regs
{
	struct elr_pchip_regs { 
		unsigned long	wsba0;	
		unsigned long	wsba1;	
		unsigned long	wsba2;	
		unsigned long	wsba3;	
		unsigned long	wsm0;	
		unsigned long	wsm1;	
		unsigned long	wsm2;	
		unsigned long	wsm3;	
		unsigned long	tba0;	
		unsigned long	tba1;	
		unsigned long	tba2;	
		unsigned long	tba3;	
		unsigned long	pctl;	
		unsigned long	plat;	
		unsigned long	rsvd;	
		unsigned long	perror;	
		unsigned long	perrmask;
		unsigned long	perrset;
		unsigned long	tlbiv;
		unsigned long	tlbia;
		unsigned long	pmonctl;
		unsigned long	pmoncnt;
	} elr_pchip;

	struct elr_cchip_regs {
		unsigned long	csc;	
		unsigned long	mtr;	
		unsigned long	misc;	
		unsigned long	mpd;	
		unsigned long	aar0;	
		unsigned long	aar1;	
		unsigned long	aar2;	
		unsigned long	aar3;	
		unsigned long	dim0;	
		unsigned long	dim1;	
		unsigned long	dir0;	
		unsigned long	dir1;	
		unsigned long	drir;	
		unsigned long	prben;	
		unsigned long	iic0;	
		unsigned long	iic1;	
		unsigned long	mpr0;	
		unsigned long	mpr1;	
		unsigned long	mpr2;	
		unsigned long	mpr3;	
		unsigned long	mctl;	
		unsigned long	rsvd;	
		unsigned long	ttr;	
		unsigned long	tdr;
		unsigned long   dim2;
		unsigned long   dim3;
		unsigned long	dir2;
		unsigned long	dir3;
		unsigned long	iic2;
		unsigned long	iic3;
	} elr_cchip;

	struct elr_dchip_regs {
		unsigned long	dsc;	
		unsigned long	str;	
		unsigned long	drev;	
	} elr_dchip;
};





/*
 * Register bit fields in DC104X-PCI Bridge 
 */

/*
 * Dchip register bit fields
 */
/* DSC reg. */
#define DCHIP_P1P	0x00000040L /* Pchip 1 Present	*/
#define DCHIP_BC	0x00000003L /* Base Config:	*/
			/*    0 = 2 chips, 1 mem bus	*/
			/*    1 = 4 chips, 1 mem bus	*/
			/*    2 = 4 chips, 2 mem bus	*/
			/*    4 = 8 chips, 2 mem bus	*/
/* DREV reg. */
#define DCHIP_REV0	0x000000000000000fL
#define DCHIP_REV1	DCHIP_REV0<<8
#define DCHIP_REV2	DCHIP_REV1<<8
#define DCHIP_REV3	DCHIP_REV2<<8
#define DCHIP_REV4	DCHIP_REV3<<8
#define DCHIP_REV5	DCHIP_REV4<<8
#define DCHIP_REV6	DCHIP_REV5<<8
#define DCHIP_REV7	DCHIP_REV6<<8


/*
 * Cchip register bit fields
 */

/* CSC reg. */

#define CCHIP_P1P	       0x00004000L	   /* Pchip 1 Preset; <14> */
#define CCHIP_BC	       DCHIP_BC 	   /* Dchip config	   */

/* MISC reg. */

#define CCHIP_DEVSUP	       0x00000f0000000000L /* bits 43:40	   */
#define CCHIP_REV	       0x000000ff00000000L /* bits 39:32	   */
#define CCHIP_NXS              0x00000000e0000000L /* bits 31:29           */
#define CCHIP_NXM              0x0000000010000000L /* bit  28              */
#define CCHIP_CPUID            0x0000000000000003L /* bits  1:0            */
#define CCHIP_MASK             0x00000fffffffffffL /* bits 43:0            */

#define CCHIP_NXS_CPU_0        0                   /* NXM Source - CPU 0   */
#define CCHIP_NXS_CPU_1        1                   /* NXM Source - CPU 1   */
#define CCHIP_NXS_CPU_2        2                   /* NXM Source - CPU 2   */
#define CCHIP_NXS_CPU_3        3                   /* NXM Source - CPU 3   */
#define CCHIP_NXS_PCHIP_0      4                   /* NXM Source - Pchip 0 */
#define CCHIP_NXS_PCHIP_1      5                   /* NXM Source - Pchip 1 */

/*
 * Array Address Register
 *
 *      Tsunami supports 4 AAR registers (AAR0...AAR3),
 *      each describing a bank of memory. The AAR register
 *      contains the encoded memory bank size in bits <15:12>
 *      and bits <31:24> of the the starting physical address
 *      of the array in bits <31:24> of the register. The AAR
 *      registers are quadword-sized, addressed at system
 *      addresses:
 *
 *              AAR0 - 0x801a0000100
 *              AAR1 - 0x801a0000140
 *              AAR2 - 0x801a0000180
 *              AAR3 - 0x801a00001c0
 *      
 */
#define AAR_BANK_PA_MASK       0x000000007f000000L /* bits 31:24           */
#define AAR_BANK_SIZE_MASK     0x000000000000f000L /* bits 15:12           */

#define AAR_BANK_PA_SHIFT      24                  /* shift to bank PA     */
#define AAR_BANK_SIZE_SHIFT    12                  /* shift to bank size   */

#define AAR_MAX_BANK            3                  /* max AAR bank index   */

/*
 * Pchip register bit fields
 */

/* PCTL reg */
#define	PCHIP_PCTL_PID	0xc00000000000L		/* bits 47:46 */
#define PCHIP_PCTL_PID_SHIFT 46
#define PCHIP_PCTL_MWIN 0x40                    /* bit 6 -- monster window enable */

/* PERROR reg */
#define PCHIP_PERR_LOST		0x1		/* bit 0 */
#define PCHIP_PERR_SERR		0x2		/* bit 1 */
#define PCHIP_PERR_PERR		0x4		/* bit 2 */
#define PCHIP_PERR_DCRTO	0x8		/* bit 3 */
#define PCHIP_PERR_SGE		0x10		/* bit 4 */
#define PCHIP_PERR_APE		0x20		/* bit 5 */
#define PCHIP_PERR_TA		0x40		/* bit 6 */
#define PCHIP_PERR_RDPE		0x80		/* bit 7 */
#define PCHIP_PERR_NDS		0x100		/* bit 8 */
#define PCHIP_PERR_RTO		0x200		/* bit 9 */
#define PCHIP_PERR_UECC		0x400		/* bit 10 */
#define PCHIP_PERR_CRE		0x800		/* bit 11 */
#define PCHIP_PERR_DAC          0x10000         /* bit 16 */

#define PCHIP_PERR_ADDR		0x0007ffffffff0000L
#define PCHIP_PERR_SYSADDR_MASK 0x00000007ffffffffL
#define PCHIP_PERR_PCIADDR_MASK 0x00000000fffffffcL
#define PCHIP_PERR_ADDR_SHIFT   16

#define PCHIP_PERR_CMD		0x00f0000000000000L
#define PCHIP_PERR_CMD_SHIFT    52

#define PCHIP_PERR_SYN		0xff00000000000000L
#define PCHIP_PERR_SYN_MASK     0x00000000000000ffL
#define PCHIP_PERR_SYN_SHIFT    56

#define PCHIP_PERR_DMA_READ     0
#define PCHIP_PERR_DMA_RMW      1
#define PCHIP_PERR_SGTE_READ    3

/*
 * INT_MASK register
 */
#define DC104X_C_ERR		0x8000000000000000L	/* bit 63 */
#define DC104X_P0_ERR		0x4000000000000000L	/* bit 62 */
#define DC104X_P1_ERR		0x2000000000000000L	/* bit 61 */
#define DC104X_P2_ERR		0x1000000000000000L	/* bit 60 */
#define DC104X_P3_ERR		0x0800000000000000L	/* bit 59 */
#define DC104X_HALT		0x0400000000000000L	/* bit 58 */
/* bits 57:56 are reserved */
#define DC104X_ISA_INTR_ENABLE	0x0080000000000000L	/* BIT 55 */
#define DC104X_SMI_ENABLE	0x0040000000000000L	/* BIT 54 */
#define DC104X_NMI_ENABLE	0x0020000000000000L	/* BIT 53 */
/* bit 52 is reserved */
#define DC104X_POWER_WARN       0x0008000000000000L	/* bit 51 */
/* Clipper has OR'd all environmental errors into bit 50 */
#define DC104X_TEMP_WARN	0x0004000000000000L	/* bit 50 */
#define DC104X_CLIPPER_SME      0x0004000000000000L     /* bit 50 */
#define DC104X_SLEEP_INT	0x0002000000000000L	/* bit 49 */
#define DC104X_FAN_FAULT	0x0001000000000000L	/* bit 48 */

#define DC104X_INTR_MASK        0xffff000000000000L

/* bits 47:0 are used for PCI interrupts */ 

#define DC104X_C_ERR_BIT	63	/* bit 63 */
#define DC104X_P0_ERR_BIT	62	/* bit 62 */
#define DC104X_P1_ERR_BIT	61	/* bit 61 */
#define DC104X_P2_ERR_BIT	60	/* bit 60 */
#define DC104X_P3_ERR_BIT	59	/* bit 59 */
#define DC104X_HALT_BIT		58	/* bit 58 */
#define DC104X_ISA_INTR_BIT	55	/* BIT 55 */
#define DC104X_SMIE_BIT		54	/* BIT 54 */
#define DC104X_NMI_BIT		53	/* BIT 53 */
#define DC104X_PWR_WARN_BIT	51	/* bit 51 */
#define DC104X_TEMP_WARN_BIT	50	/* bit 50 */
#define DC104X_SMI_BIT		49	/* bit 49 */
#define DC104X_I2C_BUS_ERR_BIT	48	/* bit 48 */


/*
 * IIC Interval Ignore Count Register
 */
#define CCHIP_IIC_OF	0x1000000			/* bit 24 */
#define CCHIP_IIC_ICNT	0x0ffffff			/* bit 23:0 */

/*
 * PCI Window BASE register defines
 */
#define WINDOW_ENABLE		0x1
#define WINDOW_DISABLE		0x0
#define WINDOW_SCATTER_GATHER	0x2
#define WINDOW_DIRECT_MAPPED 	0x0
#define WINDOW_DAC_ENABLE	0x8000000000L	/* bit 39 */
#define WINDOW_BASE_MASK	0xfff00000L
#define WINDOW_BASE(Size_index)	 ((1UL << (Size_index - 1)) << 20)

/*
 * PCI WINDOW mask register defines
 */

/* index'es into the base and mask arrays */
#define WIN_NONE        0
#define WIN_1MEG        1
#define WIN_2MEG        2
#define WIN_4MEG        3
#define WIN_8MEG        4
#define WIN_16MEG       5
#define WIN_32MEG       6
#define WIN_64MEG       7
#define WIN_128MEG      8
#define WIN_256MEG      9
#define WIN_512MEG      10
#define WIN_1GIG        11
#define WIN_2GIG        12
#define WIN_4GIG        13
#define WIN_8GIG        14

#define WINDOW_SIZE(Wndw_index)  ((1UL << (Wndw_index - 1)) << 20)
#define WINDOW_MASK(Wndw_index) (((1UL << (Wndw_index - 1)) - 1) << 20)
#define SG_TABLE_SIZE(Wndw_index) (1UL << (Wndw_index + 9))
/* 
 * these defines don't work for window size of WIN_NONE 
 */

#define M_1_MEG                 WINDOW_SIZE(WIN_1MEG)
#define M_2_MEG                 WINDOW_SIZE(WIN_2MEG)
#define M_4_MEG                 WINDOW_SIZE(WIN_4MEG)
#define M_8_MEG                 WINDOW_SIZE(WIN_8MEG)
#define M_16_MEG                WINDOW_SIZE(WIN_16MEG)
#define M_32_MEG                WINDOW_SIZE(WIN_32MEG)
#define M_64_MEG                WINDOW_SIZE(WIN_64MEG)
#define M_128_MEG               WINDOW_SIZE(WIN_128MEG)
#define M_256_MEG               WINDOW_SIZE(WIN_256MEG)
#define M_512_MEG               WINDOW_SIZE(WIN_512MEG)
#define M_1_GIG                 WINDOW_SIZE(WIN_1GIG)
#define M_2_GIG                 WINDOW_SIZE(WIN_2GIG)
#define M_4_GIG                 WINDOW_SIZE(WIN_4GIG)
#define M_8_GIG                 WINDOW_SIZE(WIN_8GIG)



/*
 * DC104X-PCI Address Space defines & declarations 
 */

/*
 * IOHANDLE-related definitions
 */
#define LOW_23			0x00000000007FFFFFL	/* Low 22 bits   */
#define LOW_24			0x0000000000FFFFFFL	/* Low 24 bits   */
#define LOW_25			0x0000000001FFFFFFL	/* Low 25 bits   */
#define LOW_26			0x0000000003FFFFFFL	/* Low 25 bits   */
#define LOW_27			0x0000000007FFFFFFL	/* Low 27 bits   */
#define LOW_28			0x000000000FFFFFFFL	/* Low 28 bits   */
#define LOW_29			0x000000001FFFFFFFL	/* Low 29 bits   */
#define LOW_30			0x000000003FFFFFFFL	/* Low 30 bits   */
#define LOW_31			0x000000007FFFFFFFL	/* Low 31 bits   */
#define LOW_32			0x00000000FFFFFFFFL	/* Low 32 bits   */
#define HIGH_32			0xFFFFFFFF00000000L	/* Upper 32-bits */
#define DC104X_BUSMEM_MASK	LOW_32
#define DC104X_BUSIO_MASK	LOW_24
#define DC104X_SYSMAP_MASK	0x00000001FF000000L	/* bits 32-24 */
#define DC104X_HOSE_NUM_SHIFT	33

#define DC104X_IOBUS_MASK 	0x0000080000000000L
#define DC104X_MEM_SPACE_MASK	0x0000000100000000L
#define DC104X_MEM_SPACE	0x0

#define DC104X_MID_MASK        0x0000000300000000L
#define DC104X_MID_SHIFT	32

#define CONFIG_HANDLE_TO_MID_NUM(Handle) \
    ((((Handle) & DC104X_MID_MASK)) >> DC104X_MID_SHIFT)


#define BIT31		0x80000000
#define BIT24		0x01000000


/*
 * The following are offsets from the PCI adapter base address.
 * The adapter base address is a function of the PCI hose number.
 */
#define DC104X_MEM_BASE  	0x000000000L
#define	DC104X_TIG_BASE		0x100000000L
#define DC104X_TIG_CSRS		0x030000000L
#define DC104X_DPR_BASE         0x010000000L
#define DC104X_IO_BASE		0x1FC000000L
#define DC104X_CONFIG_BASE	0x1FE000000L	/* PCI Config Sparse Space */

#define DC104X_SPARSE_MEM_BASE	DC104X_MEM_BASE
#define DC104X_DENSE_MEM_BASE	DC104X_MEM_BASE
#define DC104X_SPARSE_IO_BASE	DC104X_IO_BASE

#define PCHIP_BRIDGE_CSR_BASE	0x180000000L
#define CCHIP_BRIDGE_CSR_BASE	0x1A0000000L
#define DCHIP_BRIDGE_CSR_BASE	0x1B0000000L
#define DC104X_BRIDGE_CSR_BASE 0x080000000L
#define DC104X_INTR_ACK_BASE	0x1F0000000L

/* 
 * PCI-centric defines for DC104X-PCI Adapter
 */
#define	DC104X_PCI_MAX_SLOT		12	
#define DC104X_PCI_INTR_INFO_SIZE	DC104X_PCI_MAX_SLOT*4 /* 4 INTx's/slot */

/* address generation/translation macros	*/
#define DC104X_PA_IO_BASE(X) (dc104x_io_space_pa_base | (u_long)(X))

#define HOSE_NUM_TO_PA_ADPT_BASE(Hose_num) 				\
	(  dc104x_io_space_pa_base +  ((u_long)(Hose_num) << DC104X_HOSE_NUM_SHIFT) )
#define ADPT_BASE_TO_HOSE_NUM(Adpt_base) 				\
	( (Adpt_base >> DC104X_HOSE_NUM_SHIFT) & 0x03L)

#define DC104X_8259_INTR_INFO_SIZE	16
#define DC104X_ISA_IO_ADDR_BASE	\
				(HOSE_NUM_TO_PA_ADPT_BASE(0) | DC104X_IO_BASE)
#define DC104X_ISA_ADDR_TO_HANDL(x) \
PHYS_TO_KSEG(DC104X_ISA_IO_ADDR_BASE |(u_long)(x))
#define DC104X_ISA_BRIDGE_SLOT		1

/* at some point this may need to change to 4 */
#define DC104X_MAX_PCI_PER_SYS		2

/* maximum number of cpu's (required C4 chip) */
#define DC104X_MAX_CPU                  4

#define DC104X_KEYB_IRQ		        1
#define DC104X_MOUSE_IRQ		12
#define DC104X_GPC_CONFIG_HANDLE \
				(HOSE_NUM_TO_PA_ADPT_BASE(0) | DC104X_CONFIG_BASE))
#define DC104X_GPC_IO_HANDLE	(HOSE_NUM_TO_PA_ADPT_BASE(0) | DC104X_IO_BASE))
#define DC104X_GPC_MEM_HANDLE	(HOSE_NUM_TO_PA_ADPT_BASE(0) | DC104X_MEM_BASE))
#define DC104X_GPC_DENSE_HANDLE	\
				(HOSE_NUM_TO_PA_ADPT_BASE(0) | DC104X_MEM_BASE))

/* DC104X INTERRUPT TO SCB INDEX-ing MACROS */
#define DC104X_SCB_ISA_BASE		0x800
#define DC104X_SCB_PCI_BASE		0x900
#define DC104X_SCB_BUS_INDEX		0x200
#define DC104X_SCB_PCI_SLOT_INDEX	0x40
#define DC104X_SCB_PER_INTR_INDEX	0x10

#define SET_INTMASK	1
#define CLEAR_INTMASK	2

#define DC104X_ISA_INTR_LOW		0xE0
#define DC104X_ISA_INTR_HIGH		0xEF

#define DC104X_PCI_INTR_LOW             0
#define DC104X_PCI_INTR_HIGH            63


#ifdef KERNEL

/*
 * DMA Support
 */

/*
 * DMA Window defines for MC-PCI Bridge
 */

struct win_sel {
	u_long	type;		/* Direct, SG; En/disable; DAC	*/
	u_long	size;		/* based on WIN_xxxx index 	*/
	u_long	pci_base;	/* PCI base addr. of window 	*/
	u_long	tbase;		/* TBASE for s/g or direct 	*/
};

/*
 *      Definition of bus info structures.
 */
/*----------------------------------------------------------------*/
/* The agreed upon format for bus info structures is              */
/*                                                                */
/*      +----------------------------------------+                */
/*      |  Pointer to common info block          |                */
/*      |  (this is a struct common_bus_info *)  |                */
/*      +----------------------------------------|                */
/*      |  Bus specific data block               |                */
/*      +----------------------------------------+                */
/*                                                                */
/* NOTE: common_bus_info is defined in io/common/devdriver.h      */
/*                                                                */
/*----------------------------------------------------------------*/

struct dc104x_bus_info {
        struct common_bus_info *common_bus_info;
        ulong		adpt_base;
	io_handle_t	io_base;
	io_handle_t	mem_base;
        /*
         * Platform interrupt callback functions
         *
         *  - This is really the arg list for
         *    register_plat_intr_callbacks.
         */
        int (*modify_intmask)();          /* modify interrupt mask func */
        struct shared_intr_info *(*get_shared_struct)();
        int (*irq_to_scbvec)();           /* convert bus ptr/IRQ to SCB vector */
        struct eisa_sw *eisasw;           /* pointer to eisa switch table */
        int (*eoi)();                     /* end of interrupt for (e)isa */
        int (*enable_irq)();              /* enable (e)isa interrupts */
        int (*disable_irq)();             /* disable (e)isa interrupts */
        /*
         * Device Interrupt Control
         */
        int (*range_check)();             /* IRQ range check for platform */
        int low_irq;                      /* Platform's low IRQ level  */
        int high_irq;                     /* Platform's high IRQ level */
	int (*total_pci_intrs)();	  /* Platform's max PCI interrupts */
	int (*irq_to_index)();		  /* Platform's irq to shintr index */

        unsigned long   dim_data[DC104X_MAX_CPU];
        unsigned long  *dim_ptr[DC104X_MAX_CPU];
        /*
         * PCI Configuration control
         */
        int sys_hose;                   /* PCI bus used as system bus */
};


/*
 * DC104X DMA Window defines
 */

/*
 * Each MCBUS<->PCI adapter had 4 DMA windows.
 * The windows are used as defined below
 *      (console expectations as well).
 *  +--------+--------+--------+--------+-----------------------+
 *  |   PCI  | Window | Offset |  Size  |  Usage                |
 *  | Window |  Type  |        |        |                       |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    0   |  S/G   |   8 MB |   8 MB | ADDR-LIMITED devices  |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    1   | Direct |   3 GB |   1 GB | Map 0-1GB main mem    |
 *  +--------+--------+--------+--------+-----------------------+
 *  |    2   |  S/G   |   2 GB | 128MB  | General Purpose	| 
 *  |        |        |        | - 2GB  | 32-bit SG		|
 *  +--------+--------+--------+--------+-----------------------+
 *  |    3   |  S/G   |   4 GB |  ??    | 64-bit, DAC S/G	|
 *  +--------+--------+--------+--------+-----------------------+
 */

/* win_sel indices */
#define DC104X_ADDRLIM_WIN      0       /* Index to Addr. Lim. DMA Window  */
#define DC104X_DIRECT_WIN       1       /* Index to Direct-map DMA Window  */
#define DC104X_32BIT_SG_WIN     2       /* Index to 32-bit, SAC S/G DMA Window */
#define DC104X_64BIT_SG_WIN     3       /* Index to 64-bit, DAC S/G DMA Window */
#define DC104X_DIRECT64         4       /* 64-bit direct DMA is just a 
                                         * register, not a window as such,
                                         * but it needs a dma_map_info_t
                                         * structure allocated...
                                         */

/* Per-DC104X info struct used for dma, intrs, etc.	*/
/* Note: order of elements correlates to frequency of use/access in cache */
struct dc104x_info {
	u_long			sg_32b_ctl;
	u_long			sg_64b_ctl;
	u_long			addrlim_sg_ctl;
	shared_intr_info_t	*intr;
        u_long                  addrlim_sg_base;
	u_long			gp_sg_base;
	u_long			sg_64bit_base;
	u_long			direct_base;
	dma_map_info_t		dma_maps;
	u_long			present;
	u_long			busp;	/* ptr to bus struct for this bus */
	u_long			rsvd3;
};
/* 
 * Macro to extract primary PCI bus number from 
 * (potentially a compound) PCI bus number.
 * Used as index into array of DC104X_info structs
 */
#define DC104X_BUS_NUM(Busp)	(((Busp)->bus_num) & 0x00000003)

#define IS_AN_ISA_DEVICE(a)	(a->bus_hd->bus_type == BUS_ISA)
#define IS_A_CONTIG_DEVICE(f)	(f & DMA_CONTIG)
#define IS_A_SG_DEVICE(a,f)	(IS_A_CONTIG_DEVICE(f) || dc104x_always_sg)
#define ADDRESS_LIMITED(Flags)	((Flags) & DMA_ADDR_LIMIT)
#define CONTIG_DESIRED(Flags)	((Flags) & DMA_CONTIG)
#define SG_ALLOCED(f)		((f) & DMA_HW_SG)
#define HAS_SG_ALLOCED(f)	((f) & DMA_HW_SG)

#define SG_NOTNEEDED	0
#define SG_REQUIRED	1
#define SG_DESIRED	2

#define DC104X_WIN_MAX		0x5		/* 5 DMA mapping windows per PCI */
#define DC104X_DMA_PREFETCH	0xff 		/* 255 bytes */
#define DC104X_ISA_DMA_PREFETCH	0x0ffL

/* the value used for no PCI IRQ */
#define DC104X_NO_IRQ -1


/* Various translation macros 	*/
#define CONFIG_BASE_TO_BRIDGE_CSR_BASE	0x02000000L

#define HOSE_TO_BRIDGE_CSR_PHYS(Hose_num) 				\
	( dc104x_io_space_pa_base + \
	 ( ( (u_long)Hose_num << 1) << 32) + DC104X_BRIDGE_CSR_BASE )

#define _IS_64BIT_CAPABLE_(f) ((f) & DMA_64BIT)

/* Determination of SG DMA Window base address on PCI
 * Now includes 64-bit DMA selection...
 */

#define SG_MAP_SELECT(Flags,Busp) \
    ( !(_IS_64BIT_CAPABLE_(Flags)) && !(ADDRESS_LIMITED(Flags))) ? \
                dc104x_info[DC104X_BUS_NUM(Busp)].sg_32b_ctl : \
                    (_IS_64BIT_CAPABLE_(Flags) ? \
                            dc104x_info[DC104X_BUS_NUM(Busp)].sg_64b_ctl : \
                            dc104x_info[DC104X_BUS_NUM(Busp)].addrlim_sg_ctl )

#define SG_MAP_BASE_DEVICE(Flags,Busp) \
	(ADDRESS_LIMITED(Flags) ? \
		dc104x_info[DC104X_BUS_NUM(Busp)].addrlim_sg_ctl : \
		dc104x_info[DC104X_BUS_NUM(Busp)].sg_32b_ctl )

/* PCI base address values of direct-map DMA windows	*/
#define DC104X_32B_DIRECT_MAP_BASE	(u_long)(1UL << 31)	/* 2GB */
#define DC104X_64B_DIRECT_MAP_BASE	(u_long)(1UL << 40)  	/* 1TB */

#define DC104X_64B_SG_MAP_BASE          (u_long)(1UL << 36)     /* 64GB */

/* Determination of direct-map DMA Window base on PCI	*/
#define DIRECT_MAP_SELECT(Flags) \
	(((Flags) & DMA_64BIT) ? \
		DC104X_64B_DIRECT_MAP_BASE : DC104X_32B_DIRECT_MAP_BASE)


/* p2p region includes sparse & dense memory region	*/
#define LOCAL_PEER_TO_PEER_DMA_BASE	(0x0000000000000000L)	/* 0GB->2GB */

#define IS_IN_PCI_SPACE(Pa)		((Pa) & DC104X_IOBUS_MASK)
#define IS_IN_PCI_MEM(Pa)		(((Pa) & DC104X_MEM_SPACE_MASK) \
						== DC104X_MEM_SPACE)
/* 
 * Note:
 *	The and-or check below is designed to:
 *	-- fail if the physical address is not in PCI space 
 *	-- then check for the next most freq. case: dense-mapped mem. region
 *	-- then check for sparse-space mapped mem. region.
 *
 *	The checking is done in this order to minimize the code sequence
 *	executed for the most frequent dma-mapping check (non-peer-to-peer)
 *	and to allow the p-2-p check to be longer if it is p-2-p, since
 *	the performance of p-2-p can afford the slightly greater overhead.
 */
#define IS_PEER_TO_PEER(Pa) (IS_IN_PCI_SPACE(Pa) && IS_IN_PCI_MEM(Pa)) 

#define IS_LOCAL_PEER_TO_PEER(Addr, Busp) \
    ( (((Addr) &  DC104X_MID_MASK) >> DC104X_MID_SHIFT) == \
      CONFIG_HANDLE_TO_MID_NUM(((struct pci_sw *)((Busp)->bus_sw))->config_base))

#endif 

/* size of the I/O resource map for TSUNAMI */
#define DC104X_RESOURCE_MAP_SIZE 200


#ifdef KERNEL
/* for pa-addr. gen/trans. macros below */
extern	u_long dc104x_io_space_pa_base;

/*
 * Function prototypes for dc104x.c;
 * Externs for kn600.c
 */
/*
 * Init, IO-adapt-config
 */
extern void	dc104x_init(u_long io_space_base);
extern int	dc104x_adpt_cnfg(caddr_t binfo, struct bus *busp);
/*
 * IO-Access routine externs
 */
extern	long dc104x_read_io_port(io_handle_t iohandle, int width, int type);
extern	void dc104x_write_io_port(io_handle_t iohandle, int width, int type, 
								long data);
extern	int dc104x_io_copyin(io_handle_t src, vm_offset_t dest, u_long count);
extern	int dc104x_io_copyout(vm_offset_t src, io_handle_t dest, u_long count);
extern	int dc104x_io_zero(io_handle_t dest, u_long count);
extern	int dc104x_io_copyio(io_handle_t src, io_handle_t dest, u_long count);
extern	io_handle_t dc104x_busphys_to_iohandle(u_long bus_addr, 
					int flags, struct controller *ctlrp);
extern	u_long dc104x_iohandle_to_phys(io_handle_t iohandle, long flags);

/*
 * DMA window sizing alg.
 */
extern	void dc104x_choose_dma_windows();

/*
 * DMA mapping externs
 */
extern	int dc104x_dma_map_dealloc(dma_handle_t dma_handle);
extern	u_long dc104x_dma_map_alloc(u_long bc, struct  controller *cntrlrp, 
					dma_handle_t *dma_handlep, int flags);
extern	u_long dc104x_dma_map_load(u_long bc, vm_offset_t va, 
		struct proc *procp, struct controller *cntrlrp, 
		dma_handle_t *dma_handlep, u_long max_bc, int flags);
extern	int dc104x_dma_map_unload(int flags, dma_handle_t dma_handle);
extern	int dc104x_dma_min_boundary(struct controller *cntrlrp);
extern  void    dc104x_sg_tbia(struct sglist *);
/*
 * interrupt related functions
 */
extern u_long dc104x_set_dim_reg(struct bus *busp,
				 int bit_to_change,
				 int operation);
#endif	/* KERNEL */


#endif	/* __ARCH_ALPHA_HAL_DC104X_H__ */










