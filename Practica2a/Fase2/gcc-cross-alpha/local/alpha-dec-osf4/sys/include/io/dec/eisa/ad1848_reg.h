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

#ifndef AD1848_REG_H
#define AD1848_REG_H


/*	ad1848_reg.h - Internal register definitions for the 	*/
/*		Analog Devices AD1848 codec			*/

#define MSB_CODEC_LeftInputControl 	0x00
typedef struct {
  unsigned char leftInputGainSelect	: 4;
  unsigned char resvd			: 1;
  unsigned char leftInputMicGainEnable	: 1;
  unsigned char leftInputSourceSelect	: 2;
} msb_leftInputControl_reg_t;

#define MSB_CODEC_RightInputControl 	0x01
typedef struct {
  unsigned char rightInputGainSelect	: 4;
  unsigned char resvd			: 1;
  unsigned char rightInputMicGainEnable	: 1;
  unsigned char rightInputSourceSelect	: 2;
} msb_rightInputControl_reg_t;

#define MSB_CODEC_LeftAux1InputControl 	0x02
typedef struct {
  unsigned char leftAux1Input		: 5;
  unsigned char resvd			: 2;
  unsigned char leftAux1Mute		: 1;
} msb_leftAux1_reg_t;

#define MSB_CODEC_RightAux1InputControl 0x03
typedef struct {
  unsigned char rightAux1Input		: 5;
  unsigned char resvd			: 2;
  unsigned char rightAux1Mute		: 1;
} msb_rightAux1_reg_t;

#define MSB_CODEC_LeftAux2InputControl 	0x04
typedef struct {
  unsigned char leftAux2Input		: 5;
  unsigned char resvd			: 2;
  unsigned char leftAux2Mute		: 1;
} msb_leftAux2_reg_t;

#define MSB_CODEC_RightAux2InputControl 0x05
typedef struct {
  unsigned char rightAux2Input		: 5;
  unsigned char resvd			: 2;
  unsigned char rightAux2Mute		: 1;
} msb_rightAux2_reg_t;

#define MSB_CODEC_LeftOutputControl 	0x06
typedef struct {
  unsigned char leftOutAttenuateSelect	: 6;
  unsigned char resvd			: 1;
  unsigned char leftOutputMute		: 1;
} msb_leftOutputControl_reg_t;

#define MSB_CODEC_RightOutputControl 	0x07
typedef struct {
  unsigned char rightOutAttenuateSelect	: 6;
  unsigned char resvd			: 1;
  unsigned char rightOutputMute		: 1;
} msb_rightOutputControl_reg_t;

typedef struct {
  unsigned char clockSourceSelect;
  unsigned char clockFreqDivideSelect;
} msb_clockData_t;

msb_clockData_t msbClockData[] = {
	{1,0},	/* MSB_RATE_5512_5 */ 
	{1,7},  /* MSB_RATE_6615 */
	{0,0},	/* MSB_RATE_8000 */
	{0,7},	/* MSB_RATE_9600 */
	{1,1},	/* MSB_RATE_11025 */
	{0,1},	/* MSB_RATE_16000 */
	{1,2},	/* MSB_RATE_18900 */
	{1,3},	/* MSB_RATE_22050 */
	{0,2},	/* MSB_RATE_27428_57 */
	{0,3},	/* MSB_RATE_32000 */
	{1,6},	/* MSB_RATE_33075 */
	{1,4},	/* MSB_RATE_37800 */
	{1,5},	/* MSB_RATE_44100 */
	{0,6}	/* MSB_RATE_48000 */
};

typedef struct {
  unsigned char linearCompandedSelect;
  unsigned char formatSelect;
} msb_format_data_t;

msb_format_data_t msbFormatData[] = {
	{1,1},	/* A-law */
	{1,0},	/* mu-law */
	{0,0},	/* 8 bit PCM */
	{0,1}	/* 16 bit twos complement PCM */
} ;

#define MSB_CODEC_ClockAndDataFormat	0x08
typedef struct {
  unsigned char clockSourceSelect	: 1;
  unsigned char clockFreqDivideSelect	: 3;
  unsigned char stereoMonoSelect	: 1;
  unsigned char linearCompandedSelect	: 1;
  unsigned char formatSelect		: 1;
  unsigned char resvd			: 1;
} msb_clockAndDataFormat_reg_t;

#define MSB_CODEC_InterfaceConfig	0x09
typedef struct {
  unsigned char playbackEnable		: 1;
  unsigned char captureEnable		: 1;
  unsigned char singleDmaChannel	: 1;
  unsigned char autocalibrateEnable	: 1;
  unsigned char resvd			: 2;
  unsigned char playbackPIOEnable	: 1;
  unsigned char capturePIOEnable	: 1;
} msb_interfaceConfig_reg_t;

#define MSB_CODEC_PinControl		0x0a
typedef struct {
  unsigned char resvd			: 1;
  unsigned char charerruptEnable	: 1;
  unsigned char resvd1			: 4;
  unsigned char externalControl		: 2;
} msb_pinControl_reg_t;

#define MSB_CODEC_TestAndInit		0x0b
typedef struct {
  unsigned char overrangeLeftDetect	: 2;
  unsigned char overrangeRightDetect	: 2;
  unsigned char dataRequestStatus	: 1;
  unsigned char autoCalInProgress	: 1;
  unsigned char playbackUnderrun	: 1;
  unsigned char captureOverrun		: 1;
} msb_testAndInit_reg_t;

#define MSB_CODEC_MiscInfo		0x0c
typedef struct {
  unsigned char ad1848RevId		: 4;
  unsigned char resvd			: 4;
} msb_miscInfo_reg_t;

#define MSB_CODEC_DigitalMix		0x0d
typedef struct {
  unsigned char digitalMixEnable	: 1;
  unsigned char resvd			: 1;
  unsigned char digitalMixAtten		: 6;
} msb_digitalMix_reg_t;

#define MSB_CODEC_UpperBaseCount	0x0e
typedef struct {
  unsigned char upperBaseCount		: 8;
} msb_upperBaseCount_reg_t;

#define MSB_CODEC_LowerBaseCount	0x0f
typedef struct {
  unsigned char lowerBaseCount		: 8;
} msb_lowerBaseCount_reg_t;

#endif /* AD1848_REG_H */
