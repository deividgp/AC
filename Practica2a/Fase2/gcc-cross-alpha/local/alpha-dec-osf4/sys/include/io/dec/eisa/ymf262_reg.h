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
 *	Yamaha MIDI Chip register definitions
 */
#ifndef YMF262_REG_H
#define YMF262_REG_H

#define YMF_LsiTest		0x01

#define YMF_Timer1		0x02
#define YMF_Timer2		0x03
#define YMF_TimerControl	0x04

#define YMF_NTS			0x08

#define YMF_KeyScaleRate00	0x20
#define YMF_KeyScaleRate01	0x21
#define YMF_KeyScaleRate02	0x22
#define YMF_KeyScaleRate03	0x23
#define YMF_KeyScaleRate04	0x24
#define YMF_KeyScaleRate05	0x25
#define YMF_KeyScaleRate06	0x26
#define YMF_KeyScaleRate07	0x27
#define YMF_KeyScaleRate08	0x28
#define YMF_KeyScaleRate09	0x29
#define YMF_KeyScaleRate0a	0x2a
#define YMF_KeyScaleRate0b	0x2b
#define YMF_KeyScaleRate0c	0x2c
#define YMF_KeyScaleRate0d	0x2d
#define YMF_KeyScaleRate0e	0x2e
#define YMF_KeyScaleRate0f	0x2f
#define YMF_KeyScaleRate10	0x30
#define YMF_KeyScaleRate11	0x31
#define YMF_KeyScaleRate12	0x32
#define YMF_KeyScaleRate13	0x33
#define YMF_KeyScaleRate14	0x34
#define YMF_KeyScaleRate15	0x35

#define YMF_KSL_TL00		0x40
#define YMF_KSL_TL01		0x41
#define YMF_KSL_TL02		0x42
#define YMF_KSL_TL03		0x43
#define YMF_KSL_TL04		0x44
#define YMF_KSL_TL05		0x45
#define YMF_KSL_TL06		0x46
#define YMF_KSL_TL07		0x47
#define YMF_KSL_TL08		0x48
#define YMF_KSL_TL09		0x49
#define YMF_KSL_TL0a		0x4a
#define YMF_KSL_TL0b		0x4b
#define YMF_KSL_TL0c		0x4c
#define YMF_KSL_TL0d		0x4d
#define YMF_KSL_TL0e		0x4e
#define YMF_KSL_TL0f		0x4f
#define YMF_KSL_TL10		0x50
#define YMF_KSL_TL11		0x51
#define YMF_KSL_TL12		0x52
#define YMF_KSL_TL13		0x53
#define YMF_KSL_TL14		0x54
#define YMF_KSL_TL15		0x55

#define YMF_AR_DR00		0x60
#define YMF_AR_DR01		0x61
#define YMF_AR_DR02		0x62
#define YMF_AR_DR03		0x63
#define YMF_AR_DR04		0x64
#define YMF_AR_DR05		0x65
#define YMF_AR_DR06		0x66
#define YMF_AR_DR07		0x67
#define YMF_AR_DR08		0x68
#define YMF_AR_DR09		0x69
#define YMF_AR_DR0a		0x6a
#define YMF_AR_DR0b		0x6b
#define YMF_AR_DR0c		0x6c
#define YMF_AR_DR0d		0x6d
#define YMF_AR_DR0e		0x6e
#define YMF_AR_DR0f		0x6f
#define YMF_AR_DR10		0x70
#define YMF_AR_DR11		0x71
#define YMF_AR_DR12		0x72
#define YMF_AR_DR13		0x73
#define YMF_AR_DR14		0x74
#define YMF_AR_DR15		0x75

#define YMF_SL_RR00		0x80
#define YMF_SL_RR01		0x81
#define YMF_SL_RR02		0x82
#define YMF_SL_RR03		0x83
#define YMF_SL_RR04		0x84
#define YMF_SL_RR05		0x85
#define YMF_SL_RR06		0x86
#define YMF_SL_RR07		0x87
#define YMF_SL_RR08		0x88
#define YMF_SL_RR09		0x89
#define YMF_SL_RR0a		0x8a
#define YMF_SL_RR0b		0x8b
#define YMF_SL_RR0c		0x8c
#define YMF_SL_RR0d		0x8d
#define YMF_SL_RR0e		0x8e
#define YMF_SL_RR0f		0x8f
#define YMF_SL_RR10		0x90
#define YMF_SL_RR11		0x91
#define YMF_SL_RR12		0x92
#define YMF_SL_RR13		0x93
#define YMF_SL_RR14		0x94
#define YMF_SL_RR15		0x95

#define YMF_AttackRate00	0x0
#endif /* YMF262_REG_H */
