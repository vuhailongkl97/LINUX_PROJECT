#ifndef _MY_LIB_MOUSE_H_
#define _MY_LIB_MOUSE_H_

#include <stdio.h>
#include <unistd.h>                                                               
#include <stdlib.h>                                                               
#include <math.h>

#include "lib_types.h"
#include "device_info.h"
#include <linux/input.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <string.h>


enum DIRECTION {
        M_LEFT,
        M_RIGHT,
        M_UP,
        M_DOWN,
        NONE
};
enum MOUSE_CLICK {
        M_RELEASE,
	M_PRESS
};

void mouse_click(mouse *self);
static void mouse_press(mouse *self);
static void mouse_release(mouse *self);
void move_mouse_n_pixel(mouse *self, enum DIRECTION  d, int times);


void move_xy(void *self, int x_des, int y_des, int jump_size, int speed);

void *New(int x_c, int y_c, void (*cstor), void (*dstor), int fd_mouse, \
	     void (*click),void (*move) );

void constructor(void *_self, int x_c , int y_c );

void destructor(void *_self);

#endif
