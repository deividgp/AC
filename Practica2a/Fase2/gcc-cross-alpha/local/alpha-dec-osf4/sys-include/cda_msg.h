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
/* @(#)$RCSfile: cda_msg.h,v $ $Revision: 4.2 $ (DEC) $Date: 1991/09/20 04:27:57 $     */
/**/
/******************************************************************************/
/**                                                                          **/
/**  Copyright (c) 1991                                                      **/
/**  by DIGITAL Equipment Corporation, Maynard, Mass.                        **/
/**                                                                          **/
/**  This software is furnished under a license and may be used and  copied  **/
/**  only  in  accordance  with  the  terms  of  such  license and with the  **/
/**  inclusion of the above copyright notice.  This software or  any  other  **/
/**  copies  thereof may not be provided or otherwise made available to any  **/
/**  other person.  No title to and ownership of  the  software  is  hereby  **/
/**  transferred.                                                            **/
/**                                                                          **/
/**  The information in this software is subject to change  without  notice  **/
/**  and  should  not  be  construed  as  a commitment by DIGITAL Equipment  **/
/**  Corporation.                                                            **/
/**                                                                          **/
/**  DIGITAL assumes no responsibility for the use or  reliability  of  its  **/
/**  software on equipment which is not supplied by DIGITAL.                 **/
/**                                                                          **/
/******************************************************************************/
/********************************************************************************************************************************/
/* Created  3-AUG-1991 17:36:57 by VAX SDL V3.2-12     Source:  3-AUG-1991 17:36:42 DDIF$DEVELOP_ROOT:[DDIFBUILD.LIB.SRC]CDA$MSG. */
/********************************************************************************************************************************/
 
/*** MODULE $CDADEF ***/
#define CDA$_FACILITY 436
#define CDA$_NORMAL 28606465
#define CDA$_DEFAULT 28606473
#define CDA$_SUSPEND 28606481
#define CDA$_INHERIT 28606489
#define CDA$_UNRECENC 28606497
#define CDA$_INFINPLOG 28607267
#define CDA$_INFOUTLOG 28607275
#define CDA$_FILESPEC 28607283
#define CDA$_ITMAGGCNT 28607291
#define CDA$_AGGCNT 28607299
#define CDA$_RETROOT 28607307
#define CDA$_RETDESCR 28607315
#define CDA$_RETHDR 28607323
#define CDA$_RETSEG 28607331
#define CDA$_RETEOS 28607339
#define CDA$_RETCONT 28607347
#define CDA$_RETSCOPE 28607355
#define CDA$_RETEOD 28607363
#define CDA$_TYPEREF 28607371
#define CDA$_RETDTSRTE 28607379
#define CDA$_RETDTSEXT 28607387
#define CDA$_RETDTFTBL 28607395
#define CDA$_RETDTFROW 28607403
#define CDA$_RETDTFCELL 28607411
#define CDA$_STYGDEFBK 28607419
#define CDA$_MISEXTREF 28608064
#define CDA$_MISSTYGDE 28608072
#define CDA$_NUMADDINFO 28608080
#define CDA$_PARENMISS 28608088
#define CDA$_ENDOFDOC 28608866
#define CDA$_ENDOFSEQ 28608874
#define CDA$_EMPTY 28608882
#define CDA$_INDEX 28608890
#define CDA$_INVINSERT 28608898
#define CDA$_INVAGGTYP 28608906
#define CDA$_INVITMCOD 28608914
#define CDA$_INVDOC 28608922
#define CDA$_INVITMLST 28608930
#define CDA$_VAREMPTY 28608938
#define CDA$_VARINDEX 28608946
#define CDA$_VARVALUE 28608954
#define CDA$_INVTAGCOD 28608962
#define CDA$_INVBUFLEN 28608970
#define CDA$_ALLOCFAIL 28608978
#define CDA$_INVFUNCOD 28608986
#define CDA$_UNSUPFMT 28608994
#define CDA$_READONLY 28609002
#define CDA$_DEFNOTFOU 28609010
#define CDA$_READFAIL 28609018
#define CDA$_WRITFAIL 28609026
#define CDA$_OPENFAIL 28609034
#define CDA$_CLOSEFAIL 28609042
#define CDA$_INVSCOCOD 28609050
#define CDA$_INVSCOTRAN 28609058
#define CDA$_ERRINPLOG 28609066
#define CDA$_ERROUTLOG 28609074
#define CDA$_INVDATLEN 28609082
#define CDA$_UNSUPCNV 28609090
#define CDA$_INVOPTION 28609098
#define CDA$_VERSKEW 28609106
#define CDA$_INVADDINF 28609114
#define CDA$_INVFLTVAL 28609122
#define CDA$_FLTTRN 28609130
#define CDA$_INVINPDMN 28609138
#define CDA$_INVOUTDMN 28609146
#define CDA$_DCVNOTFND 28609154
#define CDA$_ICVNOTFND 28609162
#define CDA$_OCVNOTFND 28609170
#define CDA$_INVSTSCOD 28609178
#define CDA$_INVAGGCTX 28609186
#define CDA$_REQITMMIS 28609194
#define CDA$_INVTOKEN 28609202
#define CDA$_KEYWDNF 28609210
#define CDA$_LOGENDDOC 28609218
#define CDA$_ENDOFFILE 28609226
#define CDA$_INVAGGRITEM 28609234
#define CDA$_INTNOTALLOW 28609242
#define CDA$_STRNOTALLOW 28609250
#define CDA$_ENUMNOTALLOW 28609258
#define CDA$_BOOLREQ 28609266
#define CDA$_INVENUM 28609274
#define CDA$_INVADDINFO 28609282
#define CDA$_INVFLAGS 28609290
#define CDA$_INVHEX 28609298
#define CDA$_INVFLOAT 28609306
#define CDA$_INVBINARY 28609314
#define CDA$_VARINTTRN 28609322
#define CDA$_AGGNOTALLOW 28609330
#define CDA$_WRTONLY 28609338
#define CDA$_INTERR 28609668
