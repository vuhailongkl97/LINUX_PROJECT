#include "my_lib_mouse.h"


void mouseClick(Display *dpy, int button)
{

    // press
    XTestFakeButtonEvent(dpy, button, True, 1);
    XFlush(dpy);

    usleep(10000);

    // release 
    XTestFakeButtonEvent(dpy, button, False, 1);
    XFlush(dpy);

    usleep(10000);
    XTestFakeButtonEvent(dpy, button, True, 1);
    XFlush(dpy);

    //XCloseDisplay(dpy);

}
void move_xy(Display *dpy, Window root_w,int x_src, int y_src,
		 int x_des, int y_des, int jump_size, int speed)
{
	if ( speed < 0)		
	{
		speed = 0;
	}
	else if(speed >5) 
	{
		speed = 5;
	}

	do	

        {                                                                          
                XWarpPointer(dpy, None, root_w, 0, 0, 0, 0, x_src ,y_src );           
                x_src += jump_size;                                             
                y_src += jump_size;                                             

                usleep((int)(5000/speed));                                             

                XFlush(dpy);                                                    
        }   	
	while(x_src < x_des || y_src < y_des);
}
                                                                                
void show_attribute(Display *dpy, Window root_window)
{
        XWindowAttributes window_attr;                                          
                                                                                
        XGetWindowAttributes(dpy, root_window, &window_attr);                   
                                                                                
        printf("windows information\n");                                        
        printf("width = %d, height = %d\n", window_attr.width,                  
                 window_attr.height);    	
}
void move_with_oriened(Display *dpy, Window root_w,int x_src, int y_src,                      
                    int x_des, int y_des, int jump_size, int speed) 
{
	
}
