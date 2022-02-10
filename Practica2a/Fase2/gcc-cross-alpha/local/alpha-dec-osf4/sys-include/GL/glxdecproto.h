/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: glxdecproto.h,v $
 * Revision 1.1.2.17  1998/01/07  15:28:08  Charlotte_Richardson
 * 	Inform compiler that xGLXpacketAddrDECCmd is not necessarily aligned and make addrPacket field a void*
 * 	[1998/01/07  15:27:23  Charlotte_Richardson]
 *
 * Revision 1.1.2.16  1995/06/30  15:26:54  Andy_Vesper
 * 	Add BitmapDEC as a bitmap that is known to be in the
 * 	proper format for DEC
 * 	[1995/06/30  13:59:10  Andy_Vesper]
 * 
 * Revision 1.1.2.15  1995/05/12  20:43:13  Andy_Vesper
 * 	Add stream requests, reply and command.
 * 	[1995/05/12  19:31:06  Andy_Vesper]
 * 
 * Revision 1.1.2.14  1994/10/14  21:03:34  Andy_Vesper
 * 	Change GLX_COMMAND_MAX to reflect the vertex array extension
 * 	[1994/10/14  20:55:32  Andy_Vesper]
 * 
 * Revision 1.1.2.13  1993/11/11  21:28:12  Andy_Vesper
 * 	Change include to <> to work on VMS
 * 	[1993/11/11  21:23:09  Andy_Vesper]
 * 
 * Revision 1.1.2.12  1993/10/04  21:12:59  Andy_Vesper
 * 	Fix name-too-long bug: glSwapCreatePrimSMSegmentDECReply
 * 	[1993/10/04  21:09:46  Andy_Vesper]
 * 
 * Revision 1.1.2.11  1993/10/01  19:36:22  Andy_Vesper
 * 	Add primitive request and command.
 * 	[1993/10/01  19:31:06  Andy_Vesper]
 * 
 * Revision 1.1.2.10  1993/09/15  14:32:54  John_Dennis
 * 	move DEC private rending opcode to new assigned range 1024-1039
 * 	[1993/09/15  14:24:59  John_Dennis]
 * 
 * 	convert all DEC identifiers to use convention that DEC is appended to end
 * 	of identifier rather than prepended, converted to new extension dispatch
 * 	scheme voted in by the ARB.
 * 	[1993/09/10  14:11:43  John_Dennis]
 * 
 * 	initial changes in support of vendor private requests
 * 	[1993/08/20  19:59:31  John_Dennis]
 * 
 * Revision 1.1.2.9  1993/08/10  18:41:53  John_Dennis
 * 	remove include of glxint.h
 * 	[1993/08/10  18:41:17  John_Dennis]
 * 
 * Revision 1.1.2.8  1993/06/22  21:27:16  John_Dennis
 * 	remove GLX_VISUALS_PROPERTY_NAME, __glXConfigList
 * 	[1993/06/22  21:19:46  John_Dennis]
 * 
 * Revision 1.1.2.7  1993/02/18  20:44:45  John_Dennis
 * 	move X_decGLrop_PacketAddr from gllist.h to here
 * 	remove define of sz_xGLXgenericCmd, use standard __GLX_RENDER_HDR_SIZE
 * 	remove define of sz_xGLXlargeCmd, use standard __GLX_RENDER_LARGE_HDR_SIZE
 * 	[1993/02/18  20:33:44  John_Dennis]
 * 
 * Revision 1.1.2.6  1993/02/09  15:57:34  John_Dennis
 * 	change X_sgiGL_RequestLast to match 1.0.5 protocol - again since the
 * 	glxproto.h header file burried the last request in the middle of an
 * 	otherwise ordered list of requests.
 * 	[1993/02/09  15:56:55  John_Dennis]
 * 
 * Revision 1.1.2.5  1993/02/04  15:24:39  John_Dennis
 * 	change X_sgiGL_RequestLast to match 1.0.5 protocol
 * 	[1993/02/04  14:47:03  John_Dennis]
 * 
 * Revision 1.1.2.4  1992/11/13  13:46:24  Mahesh_Dandapani
 * 	"changed the xdecGLDispatchPacketCmd to use a long to hold the dispatch id
 * 	and ptrs"
 * 	[92/11/13  00:06:48  Mahesh_Dandapani]
 * 
 * Revision 1.1.2.3  92/11/06  21:46:14  Peter_Valtin
 * 	ignore this log message
 * 	[92/11/06  21:33:50  Peter_Valtin]
 * 
 * Revision 1.1.2.2  92/09/07  22:07:13  Pete_Nishimoto
 * 	New version from west coast
 * 	[92/09/07  22:06:34  Pete_Nishimoto]
 * 
 * Revision 1.1.2.2  92/08/03  08:49:10  Pete_Nishimoto
 * 	Initial version from west coast pool
 * 	[92/08/03  08:48:46  Pete_Nishimoto]
 * 
 * Revision 1.1.4.2  92/10/30  20:32:31  Terry_Crane
 * 	pad dispatchId for 64-bit case.
 * 	[92/10/30  20:17:59  Terry_Crane]
 * 
 * Revision 1.1.2.2  92/09/07  22:07:13  Pete_Nishimoto
 * 	New version from west coast
 * 	[92/09/07  22:06:34  Pete_Nishimoto]
 * 
 * Revision 1.1.2.2  92/08/03  08:49:10  Pete_Nishimoto
 * 	Initial version from west coast pool
 * 	[92/08/03  08:48:46  Pete_Nishimoto]
 * 
 * $EndLog$
 */
/** glxdecproto.h *************************************************************/

#ifndef _GLX_glxdecproto_h
#define _GLX_glxdecproto_h

#include <GL/glxproto.h>

/** Errors ********************************************************************/

#define GLX_BAD_SHM_SEGMENT_DEC         __GLX_NUMBER_ERRORS+0

#define GLX_NUMBER_ERRORS_DEC		__GLX_NUMBER_ERRORS+1
#define GLX_NUMBER_EVENTS_DEC		__GLX_NUMBER_EVENTS

/** Request and Command opcodes **********************************************/

/*
 * Vendor Private Request opcodes
 *
 * We are currently allocated vendor private requests opcodes 256-271
 */

#define X_GLXCreateSMSegmentDEC      	256
#define X_GLXFreeSMSegmentDEC        	257
#define X_GLXWrapSMReadPointerDEC    	258
#define X_GLXProcessSMRequestsDEC    	259
#define X_GLXQFlushDEC			260
#define X_GLXCreatePrimSegmentDEC	261
#define X_GLXFreePrimSegmentDEC		262
#define X_GLXCreateStreamBufferDEC	263
#define X_GLXFreeStreamBufferDEC	264

/*
 * Size of the protocol request tables.
 */
#define GLX_REQUEST_MAX 271
#define GLX_REQUEST_TABLE_SIZE (GLX_REQUEST_MAX+1)

/*
 * Vendor Private Rendering Command opcodes
 *
 * We are currently allocated vendor private rendering command opcodes 1024-1039
 */

/* DEC Command opcodes */
#define X_GLrop_PacketAddrDEC 	        1024
#define X_GLrop_PrimitiveDEC		1025
#define X_GLrop_StreamDEC		1026
#define X_GLrop_BitmapDEC	        1027
#define X_GLrop_DispatchPacketsDEC      1039

/*
 * Size of the rendering command tables.
 */
#define GLX_COMMAND_MAX 	0x1014		/* vertex array ext */

#define GLX_COMMAND_TABLE_SIZE (GLX_COMMAND_MAX+1)

/** Request & Command structure definitions *********************************/
/** Requests *****************************************************************/

typedef struct GLGenericReq {
    CARD8       reqType;
    CARD8       glxCode;
    CARD16      length B16;
} xGLXGenericReq;
#define sz_xGLXGenericReq		4

typedef struct GLXCreateSMSegmentDECReq {
    CARD8	reqType;	       /* major opcode for GLX extension */
    CARD8	glxCode;	       /* X_GLXVendorPrivateWithReply */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* vendor opcode */
    /* no additional data beyond VendorPrivate Header */
} xGLXCreateSMSegmentDECReq;
#define sz_xGLXCreateSMSegmentDECReq 	(sz_xGLXVendorPrivateWithReplyReq + 0)

typedef struct GLXCreateSMSegmentReplyDEC {
    BYTE	type;			/* X_Reply */
    CARD8	unused;			/* not used */
    CARD16	sequenceNumber B16;
    CARD32	length B32;	       /* length beyond initial 32 bytes */
    INT32       success;
    INT32       seg_ID;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xGLXCreateSMSegmentReplyDEC;
#define sz_xGLXCreateSMSegmentReplyDEC  	32

/* for bundling commands in the shared memory */
/* equivalent to the Render request in Xbuf   */
typedef struct GLXFreeSMSegmentDECReq {
    CARD8	reqType;	       /* major opcode for GLX extension */
    CARD8	glxCode;	       /* minor opcode, X_GLXVendorPrivate */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* vendor opcode */
    /* no additional data beyond VendorPrivate Header */
} xGLXFreeSMSegmentDECReq;
#define sz_xGLXFreeSMSegmentDECReq (sz_xGLXVendorPrivateReq + 0)

typedef struct GLXWrapSMReadPointerDECReq {
    CARD8	reqType;	       /* major opcode for GLX extension */
    CARD8	glxCode;	       /* minor opcode, X_GLXVendorPrivate */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* vendor opcode */
    /* no additional data beyond VendorPrivate Header */
} xGLXWrapSMReadPointerDECReq;
#define sz_xGLXWrapSMReadPointerDECReq (sz_xGLXVendorPrivateReq + 0)

typedef struct GLXProcessSMRequestsDECReq {
    CARD8	reqType;	       /* major opcode for GLX extension */
    CARD8	glxCode;	       /* minor opcode, X_GLXVendorPrivate */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* vendor opcode */
    /* additional data beyond VendorPrivate Header follows */
    CARD32      num_cmds;              /* number of GL commands in shm buffer */
} xGLXProcessSMRequestsDECReq;
#define sz_xGLXProcessSMRequestsDECReq (sz_xGLXVendorPrivateReq + 4)

typedef struct GLXQFlushDECReq {
    CARD8	reqType;	       /* major opcode for GLX extension */
    CARD8	glxCode;	       /* minor opcode, X_GLXVendorPrivate */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* vendor opcode */
    /* no additional data beyond VendorPrivate Header */
} xGLXQFlushDECReq;
#define sz_xGLXQFlushDECReq (sz_xGLXVendorPrivateReq + 0)

/* this request asks the server to create a shared memory segment	     */
/* for private communication of complete primitives.			     */

typedef struct {
    CARD8	reqType;
    CARD8	glxCode;	       /* X_GLXVendorPrivateWithReply */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* X_GLXCreatePrimSMSegmentDEC */
} xGLXCreatePrimSegmentDECReq;

#define sz_xGLXCreatePrimSegmentDECReq	8

typedef struct {
    CARD8	reply;
    CARD8	bpad0;
    CARD16	seq_num B16;
    CARD32	length B32;
    CARD32	status B32;
    CARD32	sharedMemoryId B32;
    CARD32	pad[4];
} xGLXCreatePrimSegmentDECReply;

#define sz_xGLXCreatePrimSegmentDECReply	32

/* this request frees the above */

typedef struct {
    CARD8	reqType;	       /* major opcode for GLX extension */
    CARD8	glxCode;	       /* minor opcode, X_GLXVendorPrivate */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* X_GLXFreePrimSegmentDEC */
    CARD32	sharedMemoryId B32;
} xGLXFreePrimSegmentDECReq;

#define sz_xGLXFreePrimSegmentDECReq	12

/* this request asks the server to create a shared memory segment	     */
/* for private communication of streams.				     */

typedef struct {
    CARD8	reqType;
    CARD8	glxCode;	       /* X_GLXVendorPrivateWithReply */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* X_GLXCreateStreamBufferDEC */
    CARD32	sizeRequested B32;	/* desired size in 4 byte units */
} xGLXCreateStreamBufferDECReq;

#define sz_xGLXCreateStreamBufferDECReq	12

typedef struct {
    CARD8	reply;
    CARD8	bpad0;
    CARD16	seq_num B16;
    CARD32	length B32;
    CARD32	status B32;
    CARD32	sharedMemoryId B32;
    CARD32	sizeAllocated B32;
    CARD32	pad[3];
} xGLXCreateStreamBufferDECReply;

#define sz_xGLXCreateStreamBufferDECReply	32

/* this request frees the above */

typedef struct {
    CARD8	reqType;	       /* major opcode for GLX extension */
    CARD8	glxCode;	       /* minor opcode, X_GLXVendorPrivate */
    CARD16	length B16;	       /* X protocol length in 4 byte units */
    CARD32	vendorCode B32;	       /* X_GLXFreeStreamBufferDEC */
    CARD32	sharedMemoryId B32;
} xGLXFreeStreamBufferDECReq;

#define sz_xGLXFreeStreamBufferDECReq	12

/** Commands *****************************************************************/

typedef __glXRenderHeader  		xGLXgenericCmd, *xGLXgenericCmdPtr;	

typedef __glXRenderLargeHeader 		xGLXlargeCmd, *xGLXlargeCmdPtr;

#pragma nomember_alignment
typedef struct {		    /* Not 64-bit aligned */
    __GLX_RENDER_HDR;
    /*unsigned long*/ void *	addrPacket; /* Not 64-bit aligned */
} xGLXpacketAddrDECCmd;
#pragma member_alignment

#define sz_xGLXpacketAddrDECCmd 	(sizeof(xGLXpacketAddrDECCmd))	


/* Dispatch Packets Command */
typedef struct {
    CARD16      	opcode;
    CARD16      	length;
    CARD32      	realLen;
    CARD32		packetType;
    unsigned long	dispatchId;
    unsigned long	nextPacket;
} xGLXdispatchPacketsDECCmd;
#define sz_xGLXdispatchPacketsDECCmd sizeof( xGLXdispatchPacketsDECCmd )  

/* this is a rendering command to execute a complete primitive */

typedef struct {
    CARD16       length B16;
    CARD16       opCode B16;		/* X_GLrop_PrimitiveDEC */
    CARD32	sharedMemoryId B32;
    CARD16	startIndex B16;
    CARD16	numCoords B16;
    CARD16	primType B16;
    CARD16	ORAttributes B16;
    CARD16	ANDAttributes B16;
    CARD16	unused B16;
} xGLXprimitiveDECCmd;

#define sz_xGLXprimitiveDECCmd	sizeof(xGLXprimitiveDECCmd)

/* this is a rendering command to execute a stream of commands */

typedef struct {
    CARD16       length B16;
    CARD16       opCode B16;		/* X_GLrop_StreamDEC */
    CARD32	sharedMemoryId B32;
    CARD32	startOffset B32;
    CARD32	lengthInWords B32;
    CARD32	numPrimitives B32;
} xGLXstreamDECCmd;

#define sz_xGLXstreamDECCmd	sizeof(xGLXstreamDECCmd)

/* This command is a bitmap known to be in canonical form for DEC */
typedef struct {
    __GLX_RENDER_HDR;		    /* X_GLrop_BitmapDEC */
    __GLX_BITMAP_HDR;
} xGLXbitmapDECCmd;

#define sz_xGLXbitmapDECCmd	sizeof(xGLXbitmapDECCmd)

/*****************************************************************************/

#endif /* !_GLX_glxdecproto_h */
