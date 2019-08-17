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


void mouse_click(Display *dpy, int button);
void mouse_press(Display *dpy, int button);
void mouse_release(Display *dpy, int button);

void mouse_double_click(Display *dpy);

void move_xy(Display *dpy, Window root_w,int x_src, int y_src,                  
                    int x_des, int y_des, int jump_size, int speed);

void move_with_oriened(Display *dpy, Window root_w,int x_src, int y_src,                  
                    int x_des, int y_des, int jump_size, int speed);

void show_attribute(Display *dpy, Window root_window);

#endif

