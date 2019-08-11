#include "my_lib_mouse.h"


void mousePress(Display *dpy, int button)
{

    XTestFakeButtonEvent(dpy, button, True, 1);
    XFlush(dpy);

    usleep(10000);

    XTestFakeButtonEvent(dpy, button, False, 1);
    XFlush(dpy);

}

void mouseRelease(Display *dpy, int button)
{

    XTestFakeButtonEvent(dpy, button, True, 1);
    XFlush(dpy);
}

void mouseClick(Display *dpy, int button)
{
    mousePress(dpy, button);	
    usleep(200000);
    mouseRelease(dpy, button);	
}

void move_xy(Display *dpy, Window root_w,int x_src, int y_src,
		 int x_des, int y_des, int jump_size, int speed)
{
	//printf("move from (%d,%d) -> (%d,%d)\n", x_src, y_src, x_des, y_des);
	int x_dis, y_dis;
	if(speed >5) 
	{
		speed = 5;
	}

	do	

        {                                                                          
        	XWarpPointer(dpy, None, root_w, 0, 0, 0, 0, x_src ,y_src );           

		x_dis = abs(x_src -x_des) ;	
		y_dis = abs(y_src -y_des) ;	
		if( x_dis >= jump_size)
                	x_src += speed*jump_size;                                             
	
		if( y_dis >= jump_size)
       	        	y_src += speed*jump_size;                                             

                usleep((int)(5000/abs(speed)));                                             

                XFlush(dpy);                                                    
        }   	
	while((x_dis  > jump_size) || (y_dis > jump_size));
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
