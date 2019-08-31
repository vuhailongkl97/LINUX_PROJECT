#ifndef _MY_LIB_MOUSE_H_
#define _MY_LIB_MOUSE_H_

#include <stdio.h>
#include <unistd.h>                                                               
#include <stdlib.h>                                                               
#include <X11/Xutil.h>  
#include <math.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include "lib_types.h"
#include "device_info.h"


void mouse_click(void *self, int button);
void mouse_press(void *self, int button);
void mouse_release(void *self, int button);

void mouse_double_click(void *self);

void move_xy(void *self, int x_des, int y_des, int jump_size, int speed);

void show_attribute(void *self);
int get_attribute(void *self, int *w, int *h);

void *New(int x_c, int y_c, Display *dpy, Window root, void (*cstor), 
	void (*dstor), void (*click), void (*dclick), void (*btn_release), 
		void (*move), void (*get_attr), void (*press) );

void constructor(void *_self, int x_c , int y_c , Display *dpy, Window root);

void destructor(void *_self);

#endif
