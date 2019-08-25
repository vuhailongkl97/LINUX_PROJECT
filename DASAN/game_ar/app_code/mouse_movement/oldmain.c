#include <stdio.h>
#include <time.h>
#include <X11/Xutil.h>
#include "lib_mouse.h"

void test_mouse(Display *dpy, Window root_window,int x_src, int y_src,int x_des, int y_des, int speed)
{
	move_xy(dpy, root_window, x_src,y_src,x_des,y_des,1,speed);	
}

int main(int argc, char *argv[])
{
         //Get system window
	 int i = 0;
Display *dpy;
Window root_window;

    dpy = XOpenDisplay(0);
    root_window = XRootWindow(dpy, 0);
    XSelectInput(dpy, root_window, KeyReleaseMask);
	
	
	show_attribute(dpy, root_window);

	test_mouse(dpy,root_window, 100,200,50, 30, 3);
	
	mouse_click(dpy,1);
	sleep(1);
	mouse_double_click(dpy);
	 for ( i = 0; i< 3; i++) 
	 {
		test_mouse(dpy,root_window, 200,200,1000, 600, 4);
		usleep(100000);
	 	test_mouse(dpy,root_window, 1000,600,200, 300, 4);
		sleep(1);
	 }
	 mouse_click(dpy,1);
	 //mouse_release(dpy, 1);
	
    return 0;
}

