#include "lib_mouse.h"

extern int fd_mouse ;

void move_mouse_n_pixel(enum DIRECTION  d, int times)
{
  struct input_event event, event_end;

  memset(&event, 0, sizeof(event));
  memset(&event_end, 0, sizeof(event_end));

  gettimeofday(&event.time, NULL);
  switch(d)
  {
	case M_LEFT:
		event.type = EV_REL;
  		event.code = REL_X;
  		event.value = -1;
		break;
	case M_RIGHT:
		event.type = EV_REL;
  		event.code = REL_X;
  		event.value = 1;
		break;
	case M_UP:
		event.type = EV_REL;
  		event.code = REL_Y;
  		event.value = -1;
		break;
	case M_DOWN:
		event.type = EV_REL;
  		event.code = REL_Y;
  		event.value = 1;
		break;
	default:
		puts("incorrect direction");
  }

  /*stop move signal*/
  gettimeofday(&event_end.time, NULL);
  event_end.type = EV_SYN;
  event_end.code = SYN_REPORT;
  event_end.value = 0;

  /*move mouse*/
  for (int i=0; i<abs(times); i++) {
    write(fd_mouse, &event, sizeof(event));// Move the mouse
    write(fd_mouse, &event_end, sizeof(event_end));// Show move
    usleep(500);
  }

}
void press_mouse(enum MOUSE_CLICK code) 
{
  struct input_event event, event_end;

  memset(&event, 0, sizeof(event));
  memset(&event_end, 0, sizeof(event_end));

  gettimeofday(&event.time, NULL);
  event.type = EV_KEY;
  event.code = BTN_LEFT;
  event.value = code;

  /*stop move signal*/
  gettimeofday(&event_end.time, NULL);
  event_end.type = EV_SYN;
  event_end.code = SYN_REPORT;
  event_end.value = 0;

  write(fd_mouse, &event, sizeof(event));// Move the mouse
  write(fd_mouse, &event_end, sizeof(event_end));// Show move

}
void press_key(int key, int cmd)
{
  struct input_event event, event_end;

  memset(&event, 0, sizeof(event));
  memset(&event_end, 0, sizeof(event_end));

  gettimeofday(&event.time, NULL);
  event.type = EV_KEY;
  event.code = key;
  event.value = cmd;

  /*stop move signal*/
  gettimeofday(&event_end.time, NULL);
  event_end.type = EV_SYN;
  event_end.code = SYN_REPORT;
  event_end.value = 0;

  write(fd_mouse, &event, sizeof(event));// Move the mouse
  write(fd_mouse, &event_end, sizeof(event_end));// Show move

}
//left mouse
static void mouse_press()
{
    press_mouse(M_PRESS);

}
static void mouse_release()
{
    press_mouse(M_RELEASE);
}

void mouse_click(void *_self, int button)
{
   mouse_press();
   mouse_release();
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
    
    number_step_move_x = abs(self->x_current -x_des) ;	
    number_step_move_y = abs(self->y_current -y_des) ;	
    
    bigger = number_step_move_x > number_step_move_y ? 
    		number_step_move_x : number_step_move_y;
    
	if (0 == bigger)
	{
		//printf("bigger");
		return ;
	}
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
    
    	x_dis = abs(self->x_current -x_des);
    	y_dis = abs(self->y_current -y_des);	

		#if 0
			printf("x_dis ydis = %d %d  \n", x_dis, y_dis);
		#endif 
		
    	if( !over_x )
    	{
		//move -----------------------------------------------
		if ( speed* heso_x > 0)
		{
			move_mouse_n_pixel(M_RIGHT, round(speed*heso_x));
		}
		else 
		{
			move_mouse_n_pixel(M_LEFT, round(speed*heso_x));
		}
        	x_src_tmp += speed*heso_x;
	
    		self->x_current = (int)x_src_tmp;

    		int x_dis2 = abs(self->x_current -x_des);
	
		if ( x_dis2 > x_dis )
		{
			over_x = 1;	
		}
		
    	}
    
    	if( !over_y )
    	{
		//move -------------------------------------------
		if ( speed* heso_y > 0)
		{
			move_mouse_n_pixel(M_UP, round(speed*heso_y));
		}
		else 
		{
			move_mouse_n_pixel(M_DOWN, round(speed*heso_y));
		}
        	y_src_tmp += speed*heso_y;
    		self->y_current = (int)y_src_tmp;
    		int y_dis2 = abs(self->y_current -y_des);

		if ( y_dis2 >= y_dis)
		{
			over_y = 1;
		}
    	}
    
            usleep(500);                                             
    }   	
    while( !over_x || !over_y);
    }
                                                                                

void *New(int x_c, int y_c, void (*cstor), 
	void (*dstor), void (*click),  void (*move), void (*press) )
{
	mouse *self = calloc(1, sizeof(mouse));

	self->cstor = cstor;	
	self->dstor  = dstor;
	self->move = move;
	self->click = click;
	self->btn_press = press;
	self->cstor(self, x_c, y_c);

	return  self;
}
void constructor(void *_self, int x_c , int y_c)
{
	mouse *self = _self;	
	self->x_current = x_c;		
	self->y_current = y_c;		
}
void destructor(void *_self)
{
	mouse *self = _self;
	free(self);
}
