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
/* @(#)$RCSfile: cdaptp.h,v $ $Revision: 4.2.3.3 $ (DEC) $Date: 1992/08/21 14:19:42 $     */
#ifndef _cda_ptp_
#define _cda_ptp_
/*
**++
**
**  COPYRIGHT (c) 1989, 1992 BY
**  DIGITAL EQUIPMENT CORPORATION, MAYNARD, MASS.
**  ALL RIGHTS RESERVED.
**
**  THIS SOFTWARE IS FURNISHED UNDER A LICENSE AND MAY BE USED AND  COPIED
**  ONLY  IN  ACCORDANCE  WITH  THE  TERMS  OF  SUCH  LICENSE AND WITH THE
**  INCLUSION OF THE ABOVE COPYRIGHT NOTICE.  THIS SOFTWARE OR  ANY  OTHER
**  COPIES  THEREOF MAY NOT BE PROVIDED OR OTHERWISE MADE AVAILABLE TO ANY
**  OTHER PERSON.  NO TITLE TO AND OWNERSHIP OF  THE  SOFTWARE  IS  HEREBY
**  TRANSFERRED.
**
**  THE INFORMATION IN THIS SOFTWARE IS SUBJECT TO CHANGE  WITHOUT  NOTICE
**  AND  SHOULD  NOT  BE  CONSTRUED  AS  A COMMITMENT BY DIGITAL EQUIPMENT
**  CORPORATION.
**
**  DIGITAL ASSUMES NO RESPONSIBILITY FOR THE USE OR  RELIABILITY  OF  ITS
**  SOFTWARE ON EQUIPMENT WHICH IS NOT SUPPLIED BY DIGITAL.
**
**  ABSTRACT:
**	This file contains function prototype definitions for the CDA
**      toolkit routines.
**
**--
**/

/*
 * Include CDA defined types.
 */
#ifndef _cdatyp_
#include <cdatyp.h>
#endif

/*
 * Start of the function prototypes for CDA toolkit routines.
 */
PROTO(CDAstatus CDA_CALLBACK cda_malloc,
	(CDAsize CDA_FAR *,
	 CDAaddress CDA_FAR *,
	 CDAuserparam));

PROTO(CDAaddress CDA_APIENTRY CdaMalloc,
	 (CDAsize));

PROTO(CDAstatus CDA_CALLBACK cda_free,
	(CDAsize CDA_FAR *,
	 CDAaddress CDA_FAR *,
	 CDAuserparam));

PROTO(CDAstatus CDA_APIENTRY CdaFree,
	 (CDAaddress));

PROTO(CDAstatus CDA_APIENTRY cda_calloc,
	(CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAaddress CDA_FAR *,
	 CDAuserparam));

PROTO(CDAaddress CDA_APIENTRY CdaCalloc,
	(CDAsize,
	 CDAsize));

PROTO(CDAstatus CDA_APIENTRY cda_realloc,
	(CDAaddress CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAaddress CDA_APIENTRY CdaRealloc,
	(CDAaddress,
	 CDAsize));

PROTO(CDAstatus CDA_APIENTRY cda_aggregate_type_to_object_id,
	(CDAaggtype CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAbufaddr,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_close_file,
	(DDISstreamhandle CDA_FAR *,
	 CDAfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_close_message_log,
	(CDAmessagehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_close_stream,
	(DDISstreamhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_close_text_file,
	(CDAtextfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_convert,
	(CDAconstant CDA_FAR *,
	 CDAitemlist CDA_FAR *,
         CDAaddress,
	 CDAconverterhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_convert_aggregate,
	(CDArootagghandle CDA_FAR *,
         CDAfrontendhandle CDA_FAR *,
	 CDAagghandle CDA_FAR *,
	 CDAaggtype CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_convert_document,
	(CDArootagghandle CDA_FAR *,
         CDAfrontendhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_convert_position,
	(CDAfrontendhandle CDA_FAR *,
         CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_copy_aggregate,
	(CDArootagghandle CDA_FAR *,
         CDAagghandle CDA_FAR *,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_create_aggregate,
	(CDArootagghandle CDA_FAR *,
         CDAaggtype CDA_FAR *,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_create_file,
	(CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDArootagghandle CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 DDISstreamhandle CDA_FAR *,
	 CDAfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_create_file_cda,
	 (CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDArootagghandle CDA_FAR *,
	 CDAitemlist CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 DDISstreamhandle CDA_FAR *,
	 CDAfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_create_message_log,
	(CDAitemlist CDA_FAR *,
	 CDAmessagehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_create_root_aggregate,
	(CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDAitemlist CDA_FAR *,
	 CDAaggtype CDA_FAR *,
	 CDArootagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_create_stream,
	(CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDAstatus (CDA_CALLBACK *) (CDAuserparam,
	 				     CDAsize CDA_FAR *,
	 				     CDAbufaddr,
			  		     CDAsize CDA_FAR *,
	 				     CDAbufaddr CDA_FAR *),
	 CDAuserparam,
	 CDAsize CDA_FAR *,
	 CDAbufaddr,
	 DDISstreamhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_create_text_file,
	(CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAtextfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_delete_aggregate,
	(CDArootagghandle CDA_FAR *,
         CDAagghandle CDA_FAR *));

PROTO(void CDA_APIENTRY cda_delete_format_list,
	(CDAformatlist *));

PROTO(CDAstatus CDA_APIENTRY cda_delete_root_aggregate,
	 (CDArootagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_enter_scope,
	(CDArootagghandle CDA_FAR *,
	 DDISstreamhandle CDA_FAR *,
	 CDAconstant CDA_FAR *,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_erase_item,
	(CDArootagghandle CDA_FAR *,
	 CDAagghandle CDA_FAR *,
	 CDAconstant CDA_FAR *,
	 CDAindex CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_find_definition,
	(CDArootagghandle CDA_FAR *,
         CDAaggtype CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAbufaddr,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_find_transformation,
	(CDArootagghandle CDA_FAR *,
         float CDA_FAR *(CDA_FAR *)));

PROTO(CDAstatus CDA_APIENTRY cda_flush_message_log,
	 (CDAmessagehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_flush_stream,
	(DDISstreamhandle CDA_FAR *,
	 CDAstatus (CDA_CALLBACK *) (CDAuserparam),
	 CDAuserparam));

PROTO(CDAstatus CDA_APIENTRY cda_get_aggregate,
	(CDArootagghandle CDA_FAR *,
         DDISstreamhandle CDA_FAR *,
	 CDAagghandle CDA_FAR *,
	 CDAaggtype CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_get_array_size,
	(CDAagghandle CDA_FAR *,
         CDAconstant CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_get_data_type,
	(CDAitemlist CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_get_document,
	(CDArootagghandle CDA_FAR *,
         DDISstreamhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_get_external_encoding,
	(CDArootagghandle CDA_FAR *,
         DDISstreamhandle CDA_FAR *,
	 CDAagghandle CDA_FAR *));

PROTO (CDAstatus CDA_APIENTRY cda_get_format_list,
	(CDAitemlist *, CDAformatlist **));

PROTO(CDAstatus CDA_APIENTRY cda_get_stream_position,
	(DDISstreamhandle CDA_FAR *,
	 CDAstatus (CDA_CALLBACK *) (CDAuserparam,
	 				     CDAsize CDA_FAR *),
	 CDAuserparam,
	 CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_get_text_position,
	(CDAtextfilehandle CDA_FAR *,
         CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_insert_aggregate,
	(CDAagghandle CDA_FAR *,
         CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_leave_scope,
	(CDArootagghandle CDA_FAR *,
	 DDISstreamhandle CDA_FAR *,
	 CDAconstant CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_locate_item,
	(CDArootagghandle CDA_FAR *,
	 CDAagghandle CDA_FAR *,
	 CDAconstant CDA_FAR *,
	 CDAaddress CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAindex CDA_FAR *,
	 CDAconstant CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_next_aggregate,
	(CDAagghandle CDA_FAR *,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_object_id_to_aggregate_type,
	(CDAsize CDA_FAR *,
	 CDAbufaddr,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAaggtype CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_open_converter,
	(CDAitemlist CDA_FAR *,
	 CDAconverterhandle CDA_FAR *,
	 CDAfrontendhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_open_erf_file,
	(CDArootagghandle *, CDAagghandle *, DDISstreamhandle *,
	 CDAfilehandle *, CDArootagghandle *, CDAsize *, CDAenvirontext *,
         CDAsize *, CDAenvirontext *, CDAsize *, CDAitemlist *));

PROTO(CDAstatus CDA_APIENTRY cda_open_file,
	(CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDAaggtype CDA_FAR *,
	 CDAitemlist CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 DDISstreamhandle CDA_FAR *,
	 CDAfilehandle CDA_FAR *,
	 CDArootagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_open_stream,
	(
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDAstatus (CDA_CALLBACK *) (CDAuserparam,
	 				     CDAsize CDA_FAR *,
	 				     CDAbufaddr CDA_FAR *),
	 CDAuserparam,
	 DDISstreamhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_open_text_file,
	(CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAtextfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_prune_aggregate,
	(CDArootagghandle CDA_FAR *,
         CDAagghandle CDA_FAR *,
	 CDAaggtype CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_prune_position,
	(CDArootagghandle CDA_FAR *,
         CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_put_aggregate,
	(CDArootagghandle CDA_FAR *,
         DDISstreamhandle CDA_FAR *,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_put_document,
	(CDArootagghandle CDA_FAR *,
         DDISstreamhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_read_text_file,
	(CDAtextfilehandle CDA_FAR *,
         CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *(CDA_FAR *)));

PROTO(CDAstatus CDA_APIENTRY cda_remove_aggregate,
	 (CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_status_to_message,
	(CDAstatus CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAitemlist CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_store_item,
	(CDArootagghandle CDA_FAR *,
	 CDAagghandle CDA_FAR *,
	 CDAconstant CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAaddress,
	 CDAindex CDA_FAR *,
	 CDAconstant CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_write_full_message,
	(CDAmessagehandle CDA_FAR *,
	 CDArootagghandle CDA_FAR *,
	 CDAstatus CDA_FAR *,
	 CDAitemlist CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_write_message,
	(CDAmessagehandle CDA_FAR *,
	 CDAstatus CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_write_status_message,
	(CDAmessagehandle CDA_FAR *,
	 CDAstatus CDA_FAR *,
	 CDAitemlist CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY cda_write_text_file,
	(CDAtextfilehandle CDA_FAR *,
         CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY dots_pack,
	(CDAitemlist CDA_FAR *,
	 CDAitemlist CDA_FAR *(CDA_FAR *)));

PROTO(CDAstatus CDA_APIENTRY dots_unpack,
	(CDAitemlist CDA_FAR *,
	 CDAitemlist CDA_FAR *(CDA_FAR *)));

PROTO(CDAstatus CDA_APIENTRY dots_free_output_list,
	(CDAitemlist CDA_FAR *));


/*** Prototypes for "C" bindings ***/

PROTO(CDAstatus CDA_APIENTRY CdaAggregateTypeToObjectId,
	(CDAaggtype,
         CDAsize,
	 CDAbufaddr,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCloseFile,
	(DDISstreamhandle,
	 CDAfilehandle));

PROTO(CDAstatus CDA_APIENTRY CdaCloseMessageLog,
	(CDAmessagehandle));

PROTO(CDAstatus CDA_APIENTRY CdaCloseStream,
	(DDISstreamhandle));

PROTO(CDAstatus CDA_APIENTRY CdaCloseTextFile,
	(CDAtextfilehandle));

PROTO(CDAstatus CDA_APIENTRY CdaConvert,
	(CDAconstant ,
	 CDAitemlist CDA_FAR *,
         CDAaddress,
	 CDAconverterhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaConvertAggregate,
	(CDArootagghandle,
         CDAfrontendhandle,
	 CDAagghandle CDA_FAR *,
	 CDAaggtype CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaConvertDocument,
	(CDArootagghandle,
         CDAfrontendhandle));

PROTO(CDAstatus CDA_APIENTRY CdaConvertPosition,
	(CDAfrontendhandle,
         CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCopyAggregate,
	(CDArootagghandle,
	 CDAagghandle,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCreateAggregate,
	(CDArootagghandle,
         CDAaggtype,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCreateFile,
	(CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDArootagghandle,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 DDISstreamhandle CDA_FAR *,
	 CDAfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCreateFileCda,
	(CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDArootagghandle,
	 CDAitemlist CDA_FAR *,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 DDISstreamhandle CDA_FAR *,
	 CDAfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCreateMessageLog,
	(CDAitemlist CDA_FAR *,
	 CDAmessagehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCreateRootAggregate,
	(CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDAitemlist CDA_FAR *,
	 CDAaggtype,
	 CDArootagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCreateStream,
	(CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDAstatus (CDA_CALLBACK *) (CDAuserparam,
	 				     CDAsize CDA_FAR *,
	 				     CDAbufaddr,
					     CDAsize CDA_FAR *,
	 				     CDAbufaddr CDA_FAR *),
	 CDAuserparam,
	 CDAsize,
	 CDAbufaddr,
	 DDISstreamhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaCreateTextFile,
	(CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAtextfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaDeleteAggregate,
	(CDArootagghandle,
	 CDAagghandle));

PROTO(void CDA_APIENTRY CdaDeleteFormatList,
	(CDAformatlist *));

PROTO(CDAstatus CDA_APIENTRY CdaDeleteRootAggregate,
	(CDArootagghandle));

PROTO(CDAstatus CDA_APIENTRY CdaEnterScope,
	(CDArootagghandle,
	 DDISstreamhandle,
	 CDAconstant,
	 CDAagghandle));

PROTO(CDAstatus CDA_APIENTRY CdaEraseItem,
	(CDArootagghandle,
	 CDAagghandle,
	 CDAconstant,
	 CDAindex));

PROTO(CDAstatus CDA_APIENTRY CdaFindDefinition,
	(CDArootagghandle,
         CDAaggtype,
	 CDAsize,
	 CDAbufaddr,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaFindTransformation,
	(CDArootagghandle,
         float CDA_FAR *(CDA_FAR *)));

PROTO(CDAstatus CDA_APIENTRY CdaFlushMessageLog,
	(CDAmessagehandle));

PROTO(CDAstatus CDA_APIENTRY CdaFlushStream,
	(DDISstreamhandle,
	 CDAstatus (CDA_CALLBACK *) (CDAuserparam),
	 				     CDAuserparam));

PROTO(CDAstatus CDA_APIENTRY CdaGetAggregate,
	(CDArootagghandle,
	 DDISstreamhandle,
	 CDAagghandle CDA_FAR *,
	 CDAaggtype CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaGetArraySize,
	(CDAagghandle,
	 CDAconstant,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaGetDataType,
	(CDAitemlist CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaGetDocument,
	(CDArootagghandle,
	 DDISstreamhandle));

PROTO(CDAstatus CDA_APIENTRY CdaGetExternalEncoding,
	(CDArootagghandle,
	 DDISstreamhandle,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaGetFormatList,
	(CDAitemlist *, CDAformatlist **));

PROTO(CDAstatus CDA_APIENTRY CdaGetStreamPosition,
	(DDISstreamhandle,
	 CDAstatus (CDA_CALLBACK *) (CDAuserparam,
	 				     CDAsize CDA_FAR *),
	 CDAuserparam,
	 CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaGetTextPosition,
	(CDAtextfilehandle,
         CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaInsertAggregate,
	(CDAagghandle,
	 CDAagghandle));

PROTO(CDAstatus CDA_APIENTRY CdaLeaveScope,
	(CDArootagghandle,
	 DDISstreamhandle,
	 CDAconstant));

PROTO(CDAstatus CDA_APIENTRY CdaLocateItem,
	(CDArootagghandle,
	 CDAagghandle,
	 CDAconstant,
	 CDAaddress CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAindex,
	 CDAconstant CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaNextAggregate,
	(CDAagghandle,
	 CDAagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaObjectIdToAggregateType,
	(CDAsize,
         CDAbufaddr,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAaggtype CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaOpenConverter,
	(CDAitemlist CDA_FAR *,
	 CDAconverterhandle,
	 CDAfrontendhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaOpenErfFile,
	(CDArootagghandle, CDAagghandle, DDISstreamhandle *,
	 CDAfilehandle *, CDArootagghandle *, CDAsize, CDAenvirontext *,
         CDAsize, CDAenvirontext *, CDAsize *, CDAitemlist *));

PROTO(CDAstatus CDA_APIENTRY CdaOpenFile,
	(CDAsize,
	 CDAenvirontext CDA_FAR *,
         CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDAaggtype,
	 CDAitemlist CDA_FAR *,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 DDISstreamhandle CDA_FAR *,
	 CDAfilehandle CDA_FAR *,
	 CDArootagghandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaOpenStream,
	(CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAstatus (CDA_CALLBACK *) (CDAsize CDA_FAR *,
	 				     CDAaddress CDA_FAR *,
	 				     CDAuserparam),
	 CDAuserparam,
	 CDAstatus (CDA_CALLBACK *) (CDAuserparam,
	 				     CDAsize CDA_FAR *,
	 				     CDAbufaddr CDA_FAR *),
	 CDAuserparam,
	 DDISstreamhandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaOpenTextFile,
	(CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAtextfilehandle CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaPruneAggregate,
	(CDArootagghandle,
	 CDAagghandle CDA_FAR *,
	 CDAaggtype CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaPrunePosition,
	(CDArootagghandle,
	 CDAsize CDA_FAR *,
	 CDAsize CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaPutAggregate,
	(CDArootagghandle,
	 DDISstreamhandle,
	 CDAagghandle));

PROTO(CDAstatus CDA_APIENTRY CdaPutDocument,
	(CDArootagghandle,
	 DDISstreamhandle));

PROTO(CDAstatus CDA_APIENTRY CdaReadTextFile,
	(CDAtextfilehandle,
         CDAsize CDA_FAR *,
	 CDAenvirontext CDA_FAR *(CDA_FAR *)));

PROTO(CDAstatus CDA_APIENTRY CdaRemoveAggregate,
	(CDAagghandle));

PROTO(CDAstatus CDA_APIENTRY CdaStatusToMessage,
	(CDAstatus,
	 CDAsize,
	 CDAenvirontext CDA_FAR *,
	 CDAsize CDA_FAR *,
	 CDAitemlist CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaStoreItem,
	(CDArootagghandle,
	 CDAagghandle,
	 CDAconstant,
	 CDAsize,
	 CDAaddress,
	 CDAindex,
	 CDAconstant));

PROTO(CDAstatus CDA_APIENTRY CdaWriteFullMessage,
	(CDAmessagehandle,
	 CDArootagghandle,
	 CDAstatus,
	 CDAitemlist CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaWriteMessage,
	(CDAmessagehandle,
	 CDAstatus,
	 CDAsize,
	 CDAenvirontext CDA_FAR *));


PROTO(CDAstatus CDA_APIENTRY CdaWriteStatusMessage,
	(CDAmessagehandle,
	 CDAstatus,
	 CDAitemlist CDA_FAR *));

PROTO(CDAstatus CDA_APIENTRY CdaWriteTextFile,
	(CDAtextfilehandle,
         CDAsize,
	 CDAenvirontext CDA_FAR *));

/*
 * The following prototypes indicate the format and argument types for
 * user supplied routines as well as converter entry points.
 *
 * prototype of user defined "stream get" routine.
 *      CDAstatus (CDA_CALLBACK *get_rtn)(CDAuserparam,
 *	 				          CDAsize CDA_FAR *,
 *	 				          CDAbufaddr CDA_FAR *);
 *
 * prototype of user defined "stream put" routine.
 *      CDAstatus (CDA_CALLBACK *put_rtn)(CDAuserparam,
 *	 					  CDAsize CDA_FAR *,
 *	 					  CDAbufaddr,
 *			    			  CDAsize CDA_FAR *,
 *						  CDAbufaddr CDA_FAR *);
 *
 * prototype of user defined "stream flush" routine.
 *	CDAstatus (CDA_CALLBACK *flush_rtn)(CDAuserparam);
 *
 * prototype of user defined  "put-message" routine.
 *      CDAstatus (CDA_CALLBACK *put_message_rtn)(CDAuserparam,
 *			    				  CDAstatus CDA_FAR *,
 *	 						  CDAsize CDA_FAR *,
 *							  CDAenvirontext CDA_FAR *,
 *                          				  CDAsize CDA_FAR *,
 *	 						  CDAenvirontext CDA_FAR *(CDA_FAR *)));
 *
 * prototype of user defined "flush-message" routine.
 *      CDAstatus (CDA_CALLBACK *flush_message_rtn) (CDAuserparam));
 *
 * prototype of user defined "memory allocation" routine.
 *      CDAstatus (CDA_CALLBACK *alloc_rtn)(CDAsize CDA_FAR *,
 *	 					    CDAaddress CDA_FAR *,
 *			    			    CDAuserparam);
 *
 * prototype of user defined "memory deallocation" routine.
 *      CDAstatus (CDA_CALLBACK *dealloc_rtn)(CDAsize CDA_FAR *,
 *	 					      CDAaddress CDA_FAR *,
 *			    			      CDAuserparam);
 *
 * prototype of front_end "get aggregate" routine.
 *      CDAstatus (CDA_CALLBACK *get_agg_rtn)(CDAuserparam CDA_FAR *,
 *			    			      CDAagghandle CDA_FAR *,
 *	 					      CDAaggtype CDA_FAR *);
 *
 * prototype of front_end "get position" routine.
 *      CDAstatus (CDA_CALLBACK *get_pos_rtn)(CDAuserparam CDA_FAR *,
 *			    			      CDAsize CDA_FAR *,
 *						      CDAsize CDA_FAR *);
 *
 * prototype of front-end "close" routine.
 *      CDAstatus (CDA_CALLBACK *cfe_a_close_rtn)(CDAuserparam CDA_FAR *);
 *
 * prototype of front-end "open" routine.
 *      CDAstatus (CDA_APIENTRY *open_rtn)(CDAitemlist CDA_FAR *,
 *	     		CDAconverterhandle CDA_FAR *,
 *	     		CDAuserparam CDA_FAR *,
 *	     		CDAstatus (CDA_CALLBACK **)(CDAuserparam CDA_FAR *,
 *	 					    CDAagghandle CDA_FAR *,
 *			    		 	    CDAaggtype CDA_FAR *),
 *			CDAstatus (CDA_CALLBACK **)(CDAuserparam CDA_FAR *,
 *	 					    CDAsize CDA_FAR *,
 *			    			    CDAsize CDA_FAR *),
 *	     		CDAstatus (CDA_CALLBACK **)(CDAuserparam CDA_FAR *)
 *	);
 *
 * prototype of "back_end" routine.
 *      CDAstatus (CDA_APIENTRY *cnv_a_back_end_rtn)
 *						(CDAconstant CDA_FAR *,
 *			    			 CDAitemlist CDA_FAR *,
 *						 CDAuserparam,
 *	 					 CDAfrontendhandle CDA_FAR *,
 *			    			 CDAuserparam CDA_FAR *);
 *
 */
#endif
