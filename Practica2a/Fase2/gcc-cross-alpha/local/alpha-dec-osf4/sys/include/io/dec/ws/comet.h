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
 * @(#)$RCSfile: comet.h,v $ $Revision: 1.1.2.2 $ (DEC) $Date: 1998/06/26 19:09:36 $
 */

/* /usr/sys/include/io/hw/dec/ws/comet.h */

#ifndef _COMET_H_
#define _COMET_H_

/* graphics header files */
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devdriver.h>

#define COMET_IOC_GET_VIDEO_MODES 1
#define COMET_IOC_SET_VIDEO_MODE  2

typedef struct
  {
    unsigned char  pixel_depth; /* 8, 15, 32 */
    unsigned char  visual;      /* TRUECOLOR or PSEUDO COLOR */
    unsigned char  freq;        /* hz */
    unsigned short x_res;
    unsigned short y_res;
  } comet_video_mode_t;

typedef struct
  {
    int			req_mode_count;
    comet_video_mode_t	*vid_modes;
    int 		ret_mode_count;
  } comet_ioc_get_modes_t;

typedef struct
  {
    comet_video_mode_t	*vid_mode;
  } comet_ioc_set_mode_t;

typedef struct 
  {
    short         screen;
    short         cmd;
    union 
      {
	comet_ioc_get_modes_t  get_mode;
        comet_ioc_set_mode_t  set_mode;
      } info;
  } comet_ioc_t;

/* Server/driver shared data */

typedef struct 
  {
    unsigned int          text_mem_size;
    bus_addr_t            module_dma_addr;
    unsigned short        dma_limited;
  } comet_server_info_t;


#define COMET_IOC_PRIVATE	_IOWR('w', (0|IOC_S), comet_ioc_t)

#define COMET_IOC_FLASH         0
#define COMET_IOC_DMA_REQ       1
#define COMET_IOC_LOCK_BUFFER   2
#define COMET_IOC_UNLOCK_BUFFER 3
#define COMET_IOC_LOAD_WAT      4
#define COMET_IOC_SET_OVL_CMAP  5
#define COMET_IOC_OVL_ONOFF     6

#define COMET_OVL_OFF 0
#define COMET_OVL_ON 1

#define TRUECOLOR 1
#define PSEUDO_COLOR 0 


/* screen functions */
extern caddr_t comet_init_screen_handle(caddr_t screen_handle,
                                       caddr_t address,
                                       int unit,int type);
extern int comet_init_screen(caddr_t screen_handle,
                            ws_screen_descriptor *screen);
extern int comet_clear_screen(caddr_t screen_handle,
                             ws_screen_descriptor *screen);
extern int comet_scroll_screen(caddr_t screen_handle,
                              ws_screen_descriptor *screen);
extern int comet_blitc(caddr_t screen_handle,
                      register ws_screen_descriptor *sp,
                      register int row,
                      register int col,
                      register int ch);
extern int comet_map_unmap_screen(caddr_t screen_handle,
                                 ws_depth_descriptor *depths,
                                 ws_screen_descriptor *screen,
                                 ws_map_control *mp);
extern int comet_ioctl(caddr_t screen_handle, int request, caddr_t data);

extern void comet_close(caddr_t screen_handle);


extern caddr_t comet_init_ramdac_handle( caddr_t ramdac_handle,
				        caddr_t address,
                                        int unit, int type);
/* cursor functions */

extern int comet_load_cursor(caddr_t cursor_handle,
                            ws_screen_descriptor *screen,
                            ws_cursor_data *cursor);
extern int comet_recolor_cursor(caddr_t cursor_handle,
                               ws_screen_descriptor *screen,
                               ws_color_cell *fg,
                               ws_color_cell *bg);
extern int comet_set_cursor_position(caddr_t cursor_handle,
                                    ws_screen_descriptor *sp,
                                    register int x, register int y);

extern int comet_cursor_on_off(caddr_t cursor_handle,int on_off);

/* color map functions */
extern int comet_init_color_map(caddr_t colormap_handle);
extern int comet_load_color_map_entry(caddr_t colormap_handle,
                                          int map,
                                          register ws_color_cell *entry);
extern int comet_video_on(caddr_t colormap_handle);
extern int comet_video_off(caddr_t colormap_handle);

#endif /* _COMET_H_ */

/*
 * HISTORY
 */
