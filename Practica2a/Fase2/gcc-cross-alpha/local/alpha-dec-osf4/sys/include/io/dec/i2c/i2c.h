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
 * @(#)$RCSfile: i2c.h,v $ $Revision: 1.1.4.2 $ (DEC) $Date: 1999/02/12 21:01:25 $
 */

#ifndef __I2C_H__
#define __I2C_H__


/* Mode Definition flags */
#define I2C_DALLAS                              0
#define I2C_LM75                                1

/* Philips I2C Bus Operation Declarations In Support of Environmental Monitoring */

#define I2C_ERROR 			       -1
#define I2C_DEVICE_PRESENT 		        1
#define I2C_DEVICE_NOT_PRESENT 		        0

/* number of bytes to transfer to read the temp sensor */
#define DALLAS_TEMP_SEQUENCE_SIZE               4
#define LM75_TEMP_SEQUENCE_SIZE                 1
#define MAX_TEMP_SEQUENCE_SIZE                  DALLAS_TEMP_SEQUENCE_SIZE

#define TEMPSENSOR_ADDR 			0x9E
#define ENV_FAIL_REG_ADDR     			0x70
#define ENV_FUNC_REG_ADDR     			0x72

/* argument passed into i2c_get_temp */
#define I2C_READ_TEMP                           0
#define I2C_READ_TEMP_THRESHOLD                 1

/* status defines */
#define I2C_FAN_OK 				1
#define I2C_POWER_OK 				1
#define I2C_ERROR_LIMIT 			35

/* i2c kernel measurement thread state support */
#define TEMP_DONE				0x2
#define FAN_DONE				0x4
#define POWER_DONE				0x8

#define wait_for_iicfree() \
	if(wait_for_i2cfree()) {\
		lock_done(&i2c_lock);\
		return I2C_ERROR;\
	}

#define wait_for_nointr() \
	if(wait_for_i2c_nointr()){\
		lock_done(&i2c_lock);\
		return I2C_ERROR;\
	}


#endif /* __I2C_H__ */
