#include <stdio.h>
#include <time.h>
#include <X11/Xutil.h>
#include "my_lib_mouse.h"
Display *dpy;
Window root_window;

void test_mouse(int x_src, int y_src,int x_des, int y_des, int speed)
{
	move_xy(dpy, root_window, x_src,y_src,x_des,y_des,1,speed);	
}

int main(int argc, char *argv[])
{
         //Get system window

         dpy = XOpenDisplay(0);
         root_window = XRootWindow(dpy, 0);
         XSelectInput(dpy, root_window, KeyReleaseMask);
	
	
	 show_attribute(dpy, root_window);
	 test_mouse(10,10,100, 70, 4);
	 
	 mouseClick(dpy, 1);
	

         return 0;
}

