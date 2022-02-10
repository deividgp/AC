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
/* @(#)$RCSfile: cdamsg.h,v $ $Revision: 4.3.3.4 $ (DEC) $Date: 1992/07/20 10:59:02 $     */
/**/
/******************************************************************************/
/**                                                                          **/
/**  Copyright (c) 1992                                                      **/
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
/* Created 11-JUL-1992 18:09:50 by VAX SDL V3.2-12     Source: 11-JUL-1992 18:09:30 CDA$DEVELOP_ROOT:[CDABUILD.LIB.SRC]CDAMSG.SDL */
/********************************************************************************************************************************/

/*** MODULE $CDADEF ***/
#define CDA_FACILITY 436
#define CDA_NORMAL 28606465
#define CDA_DEFAULT 28606473
#define CDA_SUSPEND 28606481
#define CDA_INHERIT 28606489
#define CDA_UNRECENC 28606497
#define CDA_INFINPLOG 28607267
#define CDA_INFOUTLOG 28607275
#define CDA_FILESPEC 28607283
#define CDA_ITMAGGCNT 28607291
#define CDA_AGGCNT 28607299
#define CDA_RETROOT 28607307
#define CDA_RETDESCR 28607315
#define CDA_RETHDR 28607323
#define CDA_RETSEG 28607331
#define CDA_RETEOS 28607339
#define CDA_RETCONT 28607347
#define CDA_RETSCOPE 28607355
#define CDA_RETEOD 28607363
#define CDA_TYPEREF 28607371
#define CDA_RETDTSRTE 28607379
#define CDA_RETDTSEXT 28607387
#define CDA_RETDTFTBL 28607395
#define CDA_RETDTFROW 28607403
#define CDA_RETDTFCELL 28607411
#define CDA_STYGDEFBK 28607419
#define CDA_OUTFILE 28607427
#define CDA_UNRECOPT 28607435
#define CDA_INVOPTVAL 28607443
#define CDA_MISEXTREF 28608064
#define CDA_MISSTYGDE 28608072
#define CDA_NUMADDINFO 28608080
#define CDA_PARENMISS 28608088
#define CDA_NOOUTFIL 28608096
#define CDA_ENDOFDOC 28608866
#define CDA_ENDOFSEQ 28608874
#define CDA_EMPTY 28608882
#define CDA_INDEX 28608890
#define CDA_INVINSERT 28608898
#define CDA_INVAGGTYP 28608906
#define CDA_INVITMCOD 28608914
#define CDA_INVDOC 28608922
#define CDA_INVITMLST 28608930
#define CDA_VAREMPTY 28608938
#define CDA_VARINDEX 28608946
#define CDA_VARVALUE 28608954
#define CDA_INVTAGCOD 28608962
#define CDA_INVBUFLEN 28608970
#define CDA_ALLOCFAIL 28608978
#define CDA_INVFUNCOD 28608986
#define CDA_UNSUPFMT 28608994
#define CDA_READONLY 28609002
#define CDA_DEFNOTFOU 28609010
#define CDA_READFAIL 28609018
#define CDA_WRITFAIL 28609026
#define CDA_OPENFAIL 28609034
#define CDA_CLOSEFAIL 28609042
#define CDA_INVSCOCOD 28609050
#define CDA_INVSCOTRAN 28609058
#define CDA_ERRINPLOG 28609066
#define CDA_ERROUTLOG 28609074
#define CDA_INVDATLEN 28609082
#define CDA_UNSUPCNV 28609090
#define CDA_INVOPTION 28609098
#define CDA_VERSKEW 28609106
#define CDA_INVADDINF 28609114
#define CDA_INVFLTVAL 28609122
#define CDA_FLTTRN 28609130
#define CDA_INVINPDMN 28609138
#define CDA_INVOUTDMN 28609146
#define CDA_DCVNOTFND 28609154
#define CDA_ICVNOTFND 28609162
#define CDA_OCVNOTFND 28609170
#define CDA_INVSTSCOD 28609178
#define CDA_INVAGGCTX 28609186
#define CDA_REQITMMIS 28609194
#define CDA_INVTOKEN 28609202
#define CDA_KEYWDNF 28609210
#define CDA_LOGENDDOC 28609218
#define CDA_ENDOFFILE 28609226
#define CDA_INVAGGRITEM 28609234
#define CDA_INTNOTALLOW 28609242
#define CDA_STRNOTALLOW 28609250
#define CDA_ENUMNOTALLOW 28609258
#define CDA_BOOLREQ 28609266
#define CDA_INVENUM 28609274
#define CDA_INVADDINFO 28609282
#define CDA_INVFLAGS 28609290
#define CDA_INVHEX 28609298
#define CDA_INVFLOAT 28609306
#define CDA_INVBINARY 28609314
#define CDA_VARINTTRN 28609322
#define CDA_AGGNOTALLOW 28609330
#define CDA_WRTONLY 28609338
#define CDA_DCVBADEXIT 28609346
#define CDA_ICVBADEXIT 28609354
#define CDA_OCVBADEXIT 28609362
#define CDA_CVTSIGSIG 28609370
#define CDA_CVTSTOPSIG 28609378
#define CDA_INTERR 28609668
