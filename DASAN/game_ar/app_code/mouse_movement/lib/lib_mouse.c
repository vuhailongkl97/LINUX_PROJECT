#include "lib_mouse.h"

void mouse_press(void *_self, int button)
{
    mouse *self = _self;

    XTestFakeButtonEvent(self->dpy, button, True, 1);
    XFlush(self->dpy);

    usleep(10000);

    XTestFakeButtonEvent(self->dpy, button, False, 1);
    XFlush(self->dpy);

}
void mouse_release(void *_self, int button)
{
    mouse *self = _self;

    XTestFakeButtonEvent(self->dpy, button, True, 1);
    XFlush(self->dpy);
}

void mouse_click(void *_self, int button)
{
    mouse *self = _self;

    self->btn_press(self, button);	
    usleep(200000);
    self->btn_release(self, button);	
}

void mouse_double_click(void *_self)
{
    mouse *self = _self;
    self->click(self,1);
    sleep(1);
    self->click(self,1);
}

/*
	movement really
*/
void move_xy(void *_self, int x_des, int y_des, int jump_size, int speed)
{

    int x_dis, y_dis;
    int number_step_move_x, number_step_move_y;
    int bigger;
    float heso_x, heso_y;
    float x_src_tmp, y_src_tmp;
    int over_x = 0, over_y = 0;
    mouse *self = _self;
    
    x_des = x_des > self->width_max ? self->width_max : abs(x_des);
    y_des = y_des > self->height_max ? self->height_max : abs(y_des);

    number_step_move_x = abs(self->x_current -x_des) ;	
    number_step_move_y = abs(self->y_current -y_des) ;	
    
    bigger = number_step_move_x > number_step_move_y ? 
    		number_step_move_x : number_step_move_y;
    
    heso_x = 1.0*number_step_move_x/bigger;
    heso_y = 1.0*number_step_move_y/bigger;
    
    
    if (x_des < self->x_current)
    	heso_x = -heso_x;
    if (y_des < self->y_current)
    	heso_y = -heso_y;
    
    x_src_tmp = self->x_current;
    y_src_tmp = self->y_current;
    
    do	
    {                                                                          
    	XWarpPointer(self->dpy, None, self->root, 0, 0, 0, 0, self->x_current
			 ,self->y_current );           
    
    	x_dis = abs(self->x_current -x_des);
    	y_dis = abs(self->y_current -y_des);	

		#ifdef DEBUG
			printf("x_dis ydis = %d %d  \n", x_dis, y_dis);
		#endif 
		
    	if( !over_x )
    	{
        	x_src_tmp += speed*heso_x;
    		self->x_current = (int)x_src_tmp;

    		int x_dis2 = abs(self->x_current -x_des);
	
		if ( x_dis2 >= x_dis )
		{
			over_x = 1;	
		}
		
    	}
    
    	if( !over_y )
    	{
        	y_src_tmp += speed*heso_y;
    		self->y_current = (int)y_src_tmp;
    		int y_dis2 = abs(self->y_current -y_des);

		if ( y_dis2 >= y_dis)
		{
			over_y = 1;
		}
    	}
    
            usleep((int)(10000/abs(speed)));                                             
    
            XFlush(self->dpy);                                                    
    }   	
    while( !over_x || !over_y);
    }
                                                                                
void show_attribute(void *_self)
{
	mouse *self = _self;
        printf("windows information\n");                                        
        printf("width = %d, height = %d\n", self->width_max, self->height_max);

}

int get_attribute(void *_self, int *width, int *height)
{
        XWindowAttributes window_attr;                                          
	mouse *self = _self;
                                                                                
        if ( 0 <  XGetWindowAttributes(self->dpy, self->root, &window_attr) )
	{
        	*width = window_attr.width;
        	*height = window_attr.height;    	
		return 0;
	}
	else 
	{
		*width = *height= 0;
		return -1;
	}
}

void *New(int x_c, int y_c, Display *dpy, Window root, void (*cstor), 
	void (*dstor), void (*click), void (*dclick), void (*btn_release), 
		void (*move), void (*get_attr), void (*press) )
{
	mouse *self = calloc(1, sizeof(mouse));

	self->cstor = cstor;	
	self->dstor  = dstor;
	self->move = move;
	self->click = click;
	self->dclick = dclick;
	self->btn_release = btn_release;
	self->get_attr = get_attr;
	self->btn_press = press;
	self->cstor(self, x_c, y_c, dpy, root);

	return  self;
}
void constructor(void *_self, int x_c , int y_c , Display *dpy, Window root)
{
	mouse *self = _self;	
	self->x_current = x_c;		
	self->y_current = y_c;		
	self->dpy = dpy;
	self->root = root;
	self->get_attr(self, &(self->width_max), &(self->height_max));
}
void destructor(void *_self)
{
	mouse *self = _self;
	free(self);
}
