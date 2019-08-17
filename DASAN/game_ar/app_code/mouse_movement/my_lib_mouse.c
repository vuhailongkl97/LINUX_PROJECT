#include "my_lib_mouse.h"

void mouse_press(Display *dpy, int button)
{

    XTestFakeButtonEvent(dpy, button, True, 1);
    XFlush(dpy);

    usleep(10000);

    XTestFakeButtonEvent(dpy, button, False, 1);
    XFlush(dpy);

}
void mouse_release(Display *dpy, int button)
{

    XTestFakeButtonEvent(dpy, button, True, 1);
    XFlush(dpy);
}

void mouse_click(Display *dpy, int button)
{
    mouse_press(dpy, button);	
    usleep(200000);
    mouse_release(dpy, button);	
}

void mouse_double_click(Display *dpy)
{
    mouse_click(dpy,1);
    sleep(1);
    mouse_click(dpy,1);
}

/*
	movement really
*/
void move_xy(Display *dpy, Window root_w,int x_src, int y_src,
		 int x_des, int y_des, int jump_size, int speed)
{
    int x_dis, y_dis;
    int number_step_move_x, number_step_move_y;
    int bigger;
    float heso_x, heso_y;
    float x_src_tmp, y_src_tmp;
    
    number_step_move_x = abs(x_src -x_des) ;	
    number_step_move_y = abs(y_src -y_des) ;	
    
    bigger = number_step_move_x > number_step_move_y ? 
    		number_step_move_x : number_step_move_y;
    
    heso_x = 1.0*number_step_move_x/bigger;
    heso_y = 1.0*number_step_move_y/bigger;
    
    
    if (x_des < x_src)
    	heso_x = -heso_x;
    if (y_des < y_src)
    	heso_y = -heso_y;
    
    x_src_tmp = x_src;
    y_src_tmp = y_src;
    
    do	
    {                                                                          
    	XWarpPointer(dpy, None, root_w, 0, 0, 0, 0, x_src ,y_src );           
    
    	x_dis = abs(x_src -x_des) ;	
    	y_dis = abs(y_src -y_des) ;	
    	if( x_dis >= jump_size)
    	{
            	x_src_tmp += speed*heso_x;
    		x_src = (int)x_src_tmp;
    	}
    
    	if( y_dis >= jump_size)
    	{
            	y_src_tmp += speed*heso_y;
    		y_src = (int)y_src_tmp;
    	}
    
            usleep((int)(10000/abs(speed)));                                             
    
            XFlush(dpy);                                                    
    }   	
    while((x_dis  > abs(heso_x)) || (y_dis > abs(heso_y)));
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
