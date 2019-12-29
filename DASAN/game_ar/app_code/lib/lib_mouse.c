#include "lib_mouse.h"


void move_mouse_n_pixel(mouse *self, enum DIRECTION  d, int times)
{
  struct input_event event, event_end;
  int fd = self->fd_mouse;

  memset(&event, 0, sizeof(event));
  memset(&event_end, 0, sizeof(event_end));

  gettimeofday(&event.time, NULL);
  /*when vy > vx*5 then value x dimention is 3 else is 1   */
  event.type = EV_REL;
  switch(d)
  {
	case M_LEFT:
  		event.code = REL_X;
  		event.value = -2;
		//times = (int)(times*1.5);
		break;
	case M_RIGHT:
  		event.code = REL_X;
  		event.value = 2;
		//times = (int)(times*1.5);
		break;
	case M_UP:
  		event.code = REL_Y;
  		event.value = -2;
		//times = (int)(times*2);
		break;
	case M_DOWN:
  		event.code = REL_Y;
  		event.value = 2;
		//times = (int)(times*2);
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
  for (int i=0; i<abs(times)*1; i++) {
    write(fd, &event, sizeof(event));// Move the mouse
    write(fd, &event_end, sizeof(event_end));// Show move
    if (d == M_LEFT || d == M_RIGHT)
    {
        usleep(200);
    }
    else if (d == M_UP || d == M_DOWN)
    {
	    usleep(170);
    }
  }

}
void press_mouse(mouse *self, enum MOUSE_CLICK code) 
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

  write(self->fd_mouse, &event, sizeof(event));// Move the mouse
  write(self->fd_mouse, &event_end, sizeof(event_end));// Show move

}
//left mouse
static void mouse_press(mouse *self)
{
    press_mouse(self, M_PRESS);

}
static void mouse_release(mouse *self)
{
    press_mouse(self, M_RELEASE);
}

void mouse_click(mouse *self)
{
   mouse_press(self);
   mouse_release(self);
   usleep(10000);
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
    
    number_step_move_x = abs(self->x_current -x_des)/speed ;	
    number_step_move_y = abs(self->y_current -y_des)/speed ;	
    
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
			//printf("x_src_tmp y_src_tmp = %f %f  \n",x_src_tmp ,y_src_tmp );
		#endif 
		
    	if( !over_x )
    	{
		//move -----------------------------------------------
		if ( speed* heso_x > 0)
		{
			move_mouse_n_pixel(self, M_RIGHT, round(speed*heso_x));
		}
		else 
		{
			move_mouse_n_pixel(self, M_LEFT, round(speed*heso_x));
		}
        	x_src_tmp += speed*heso_x;
	
    		self->x_current = (int)x_src_tmp;

    		int x_dis2 = abs(self->x_current -x_des);
	
		if (  x_dis  <= speed)
		{
			over_x = 1;	
		}
		
    	}
    
    	if( !over_y )
    	{
		//move -------------------------------------------
		if ( speed* heso_y > 0)
		{
			move_mouse_n_pixel(self, M_UP, round(speed*heso_y));
		}
		else 
		{
			move_mouse_n_pixel(self, M_DOWN, round(speed*heso_y));
		}
        	y_src_tmp += speed*heso_y;
    		self->y_current = (int)y_src_tmp;
    		int y_dis2 = abs(self->y_current -y_des);
		//printf("y_src_tmp = %f, y_dis2 %d\n", y_src_tmp, y_dis2);
		//sleep(1);

		if (  y_dis <= speed )
		{
			over_y = 1;
		}
    	}
    
    }   	
    while( !over_x || !over_y);
}
                                                                                

void *New(int x_c, int y_c, void (*cstor),void (*dstor),int fd_mouse,
	void (*click),  void (*move) )
{
	mouse *self = calloc(1, sizeof(mouse));

	self->cstor = cstor;	
	self->dstor  = dstor;
	self->move = move;
	self->click = click;
	self->fd_mouse = fd_mouse;
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
	close(self->fd_mouse);
	free(self);
}
