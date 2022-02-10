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

#ifndef _CVT_H_
#define _CVT_H_

#include <standards.h>


_BEGIN_CPLUSPLUS
extern int cvt_ftof __(( void *, int, void *, int, int));
_END_CPLUSPLUS

/*
 * FUNCTIONAL DESCRIPTION:
 * ----------------------
 *
 *    int cvt_ftof( void *input_value,  int input_type,
 *                  void *output_value, int output_type,
 *                  int options);
 *
 *    cvt_ftof is a general purpose routine for converting between any pair of
 *    the following data types:
 *
 *        VAX F_Floating
 *        VAX D_Floating
 *        VAX G_Floating
 *        VAX H_Floating
 *        IEEE Single
 *        IEEE Double
 *        IEEE Quad
 *        IEEE Single (Big Endian)
 *        IEEE Double (Big Endian)
 *        IEEE Quad (Big Endian)
 *        IBM Short Floating (base 16)
 *        IBM Long Floating (base 16)
 *        Cray Single Floating
 *
 *      The value pointed to by input_value is interpreted as being of  type
 *      input_type.   The  routine  converts  *input_value  to  output_type,
 *      applying any options specified by the options field, and stores  the
 *      result  at  output_value.  The function's return value indicates the
 *      status of the conversion.
 *
 *      Both the options parameter and the return  status  are  bit  fields.
 *      This  allows  multiple  options  to  be  applied to a conversion and
 *      multiple pieces  of  status  information  to  be  returned.
 *
 *
 * INPUT PARAMETERS:
 *
 *    input_value   - address of the value to be converted.
 *    input_type    - data type of *input_value.
 *    output_type   - data type of *output_value.
 *    options       - a bit vector used to specify various conversion options.
 *
 *
 * OUTPUT PARAMETERS:
 *
 *    output_value - address of the converted value.
 */

#define   CVT_VAX_F              1
#define   CVT_VAX_D              2
#define   CVT_VAX_G              3
#define   CVT_VAX_H              4
#define   CVT_IEEE_S             5
#define   CVT_IEEE_T             6
#define   CVT_IEEE_X             7
#define   CVT_BIG_ENDIAN_IEEE_S  8
#define   CVT_BIG_ENDIAN_IEEE_T  9
#define   CVT_BIG_ENDIAN_IEEE_X  10
#define   CVT_IBM_SHORT          11
#define   CVT_IBM_LONG           12
#define   CVT_CRAY_SINGLE        13


/*
 * FUNCTION RETURN STATUS VALUES:
 * -----------------------------
 *
 *    The following status codes are reported as return status from  cvt_ftof.
 *    Status  codes  marked  with  (o) are optional and are reported only upon
 *    request (See the section labeled OPTION FLAGS for details).
 *
 *    Note:
 *          Since more than one status value can be in effect for a given
 *          conversion (e.g. both CVT_RESULT_DENORMALIZED & CVT_RESULT_INEXACT)
 *          the return status value is a bit vector.  Each status value occupies
 *          a separate position.
 *
 *
 *    Non-Optional Status Values: (applicable to any conversion)
 *
 *     CVT_NORMAL                - Normal successful conversion
 *     CVT_INVALID_INPUT_TYPE    - Invalid input_type code
 *     CVT_INVALID_OUTPUT_TYPE   - Invalid output_type code
 *     CVT_INVALID_OPTION        - Invalid option argument
 *
 *
 *    Optional Status Values:
 *
 *           Applicable only for conversions to IEEE format 
 *  
 *   o CVT_RESULT_INFINITE          - Conversion produced an infinite result
 *   o CVT_RESULT_DENORMALIZED      - Conversion produced a denormalized result
 *
 *           Applicable only for conversions to CRAY format
 *
 *   o CVT_RESULT_OVERFLOW_RANGE    - Conversion yielded an exponent > 60000 (8)
 *   o CVT_RESULT_UNDERFLOW_RANGE   - Conversion yielded an exponent < 20000 (8)
 *
 *          Applicable only for conversions to IBM formats
 *  
 *   o CVT_RESULT_UNNORMALIZED      - Conversion produced an unnormalized result
 *
 *
 *          Applicable to any conversion
 *
 *   o CVT_RESULT_INVALID           - Conversion result is ROP, NaN or closest
 *                                    equivalent (Cray & IBM types return 0)
 *   o CVT_RESULT_OVERFLOW          - Conversion resulted in overflow
 *   o CVT_RESULT_UNDERFLOW         - Conversion resulted in underflow
 *   o CVT_RESULT_INEXACT           - Conversion resulted in a loss of precision
 *
 */

#define CVT_NORMAL                      0
#define CVT_INVALID_INPUT_TYPE          (1<<0)
#define CVT_INVALID_OUTPUT_TYPE         (1<<1)
#define CVT_INVALID_OPTION              (1<<2)
#define CVT_RESULT_INFINITE             (1<<3)
#define CVT_RESULT_DENORMALIZED         (1<<4)
#define CVT_RESULT_OVERFLOW_RANGE       (1<<5)
#define CVT_RESULT_UNDERFLOW_RANGE      (1<<6)
#define CVT_RESULT_UNNORMALIZED         (1<<7)
#define CVT_RESULT_INVALID              (1<<8)
#define CVT_RESULT_OVERFLOW             (1<<9)
#define CVT_RESULT_UNDERFLOW            (1<<10)
#define CVT_RESULT_INEXACT              (1<<11)


/*
 * OPTION FLAGS:
 * ------------
 *
 *  The options below are  provided  for  reporting  on,  and  manipulating,
 *  conversion  results.   Each option applies to one or more floating point
 *  data formats.  For conversions, select  only  options  applying  to  the
 *  conversion  data  types.   Options  selected  which do not apply will be
 *  reported as errors (CVT_INVALID_OPTION).
 */

/*
 *    Rounding - By default, conversions perform rounding in a traditional
 *               manner with half way cases rounding to the infinities.
 *               The exception is that conversions to IEEE data formats default
 *               to "round to nearest" style rounding (as described in the IEEE
 *               Std. 754).  The following options may be applied to any
 *               conversion.
 *
 *    CVT_ROUND_TO_NEAREST            - Round to nearest (IEEE Std. 754)
 *    CVT_ROUND_TO_ZERO               - Round toward zero (i.e. chop/truncate)
 *    CVT_ROUND_TO_POS                - Round toward Positive Infinity
 *    CVT_ROUND_TO_NEG                - Round toward Negative Infinity
 *    CVT_BIASED_ROUNDING             - Perform "traditional" style rounding
 */

#define    CVT_ROUND_TO_NEAREST     (1<<0)
#define    CVT_ROUND_TO_ZERO        (1<<1)
#define    CVT_ROUND_TO_POS         (1<<2)
#define    CVT_ROUND_TO_NEG         (1<<3)
#define    CVT_BIASED_ROUNDING      (1<<4)


/*
 *    Forcing results - Conversions resulting in the following special cases may
 *                      be forced to the indicated value.
 *
 *           Applicable only for conversions to IEEE or VAX formats
 *
 *    CVT_FORCE_INVALID_TO_ZERO       - Force invalid results to zero
 *
 *           Applicable only for conversions to IEEE format 
 *  
 *    CVT_FORCE_DENORM_TO_ZERO        - Force denormalized results to zero
 *    CVT_FORCE_INF_TO_MAX_FLOAT      - Force infinite output values to max
 *                                      float (-inf is forced to -max float)
 *
 *           Applicable to any conversion
 *
 *    CVT_FORCE_ALL_SPECIAL_VALUES    - Apply all FORCE options which are valid
 *                                      for the current conversion.
 *
 */

#define    CVT_FORCE_INVALID_TO_ZERO         (1<<5)
#define    CVT_FORCE_DENORM_TO_ZERO          (1<<6)
#define    CVT_FORCE_INF_TO_MAX_FLOAT        (1<<7)
#define    CVT_FORCE_ALL_SPECIAL_VALUES      (1<<8)


/*
 *    Allowing special results & input/output args - The following options allow
 *    for the generation of special result formats, and allow special
 *    input and output argument formats.
 *
 *           Applicable only for conversions involving CRAY format
 *
 *    CVT_ALLOW_OVRFLW_RANGE_VALUES   - Allow input/output exponent > 60000 (8)
 *    CVT_ALLOW_UDRFLW_RANGE_VALUES   - Allow input/output exponent < 20000 (8)
 *                                        
 *
 *          Applicable only for conversions involving IBM formats
 *  
 *    CVT_ALLOW_UNNORMALIZED_VALUES   - Allow unnormalized input args.
 *                                      Allow unnormalized output for small
 *                                      values which would normalize to zero. 
 */

#define    CVT_ALLOW_OVRFLW_RANGE_VALUES     (1<<9)
#define    CVT_ALLOW_UDRFLW_RANGE_VALUES     (1<<10)
#define    CVT_ALLOW_UNNORMALIZED_VALUES     (1<<11)


/*
 *    Status - The  following  option  forces  all  status  conditions  to   be
 *             reported.   By  default  the  reporting  of  many  conditions is
 *             disabled with only severe conditions being  reported.   See  the
 *             section on return status for details.
 *
 *
 *          Applicable to any conversion
 *
 *    CVT_REPORT_ALL             - report all applicable status conditions 
 *
 */

#define    CVT_REPORT_ALL               (1<<12) 



#endif  /* _CVT_H_ */
