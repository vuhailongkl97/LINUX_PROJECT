#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include "lib_mouse.h"
#include "progess_data.h"

#include "lib_game_obj.h"
#include "milis.h"
#include "mqtt_lib.h"

void test_mouse(void *_self,int x_des, int y_des, int speed)
{
	mouse *self = _self;
	self->move(self,x_des,y_des,1,speed);	
}
void mtest(mouse *x)
{
	test_mouse(x, 150, 220, 1);
	
}

void ktest(game_obj *x , int key)
{
	x->change_dev(x, key); 
}
void gtest(game_obj *x)
{
	ktest(x, g_DEV_NEXT);
	sleep(1);
	ktest(x, g_DEV_BACK);
	sleep(1);
	ktest(x, g_DEV_NEXT);
	sleep(1);
	ktest(x, g_DEV_BACK);
	
}
#ifdef SERIAL
void control(FILE *fp, mouse *x,game_obj *go)
#elif defined(MQTT)
void control(MQTTClient_message *mess, mouse *x,game_obj *go)
#endif
{
	int opt = 0;
	static int timeout = 0;
	static int change_dev = 0 ;
	/*variable check support mouse button*/
	static int is_sp_mouse = 0;
	static int x_old_pos , y_old_pos;
	static int old_movement_state = 0;
	pdata p;
#ifdef SERIAL
	get_data(fp,&p);
#elif defined(MQTT)
	get_data(mess,&p);
#endif

	/*variable switch enable shot*/
	static int ready_change_dev = 1;
	//printf("pitch %f yaw %f roll %f\n",p.pitch, p.yaw, p.roll);

	if (mIDLE  != p.mouse_state)
	{
		if (LEFT_CLICK & p.mouse_state )
		{
			x->click(x);			
		}
		if (RIGHT_CLICK & p.mouse_state)
		{

		}

	 	if (STOP_MOVE & p.mouse_state)
		{
			// button is pressed	
			if ( 0 == is_sp_mouse )
			{
				is_sp_mouse = 5;
				x_old_pos = x->x_current;
				y_old_pos = x->y_current;
			}
			if (5 == is_sp_mouse)
			{
			     int tmp_x = RATIO*p.pitch;
			     int tmp_y = RATIO*p.yaw;
			     int step = abs(tmp_x-x_old_pos);
			     int step_y= abs(tmp_y -y_old_pos);

			     if ( tmp_x > ( x_old_pos +10 ))
			     	move_mouse_n_pixel(x, M_RIGHT, step);
			     else if(  tmp_x < (x_old_pos - 10))
			     	move_mouse_n_pixel(x, M_LEFT, step);

			     if ( tmp_y > ( y_old_pos  + 10 ))
			     	move_mouse_n_pixel(x, M_UP, step_y);
			     else if( tmp_y  < (y_old_pos - 10 ) )
			     	move_mouse_n_pixel(x, M_DOWN, step_y);


			     printf("chenh lech %d %d\n", x_old_pos ,tmp_x);
			     printf("22chenh lech %d %d\n", x_old_pos ,tmp_y);

			     //printf("button support is pressed x_old_pos %d x current %f\n", x_old_pos, p.pitch);
			}

		}
	}
	if (p.mouse_state != STOP_MOVE)
	{
		int retx, rety;

		is_sp_mouse = 0;
#ifdef SERIAL
		caculator_velocity(fp, x);
#elif defined(MQTT)
		caculator_velocity(mess, x);
#endif
		get_target(x->x_current,x->y_current,x->current_vx, x-> current_vy, &retx, &rety);
		
#ifdef DEBUG
	        printf("xret = %d , yret = %d vx %f vy %f\n", retx, rety,x->current_vx, x->current_vy);
	        printf("currentx = %d , currenty = %d \n",x->x_current, x->y_current);
#endif

#if 0
		retx = retx > 400 ? 400 : retx;
		retx = retx < -400 ? -400 : retx;
		rety = rety > 400 ? 400 : rety;
		rety = rety < -400 ? -400: rety;
#endif
		

		/*check change but*/
		
		if ( abs(p.roll) < 3)
		{
			ready_change_dev = 1;
		}

		if ( (1 == ready_change_dev ) && (mili_second() > timeout))
		{
		    if (p.roll > 20)
		    {
		       go->change_dev(go, g_DEV_BACK);
		       usleep(1000);
		       timeout = mili_second() + 500; //ms
		       ready_change_dev = 0;
		       goto dont_move;
		    }
		    else if(p.roll < -20)
		    {
		       go->change_dev(go, g_DEV_NEXT);
		       usleep(1000);
		       timeout = mili_second() + 500; //ms
		       ready_change_dev = 0;
		       goto dont_move;
		    }
		}

		x->move(x, retx, rety, 1, 1);	
	        	
	}

	dont_move:
	{
#if 1
		// should release or  keep state button

		// hien tai co truoc day ko co 
		if ((LEFT & p.movement_state) &&  !(LEFT & old_movement_state)) 
			press_key(go, KEY_A,1); 
		else if (!(LEFT & p.movement_state) && (LEFT & old_movement_state))
			press_key(go, KEY_A,0); 

		if ( (RIGHT & p.movement_state) &&  !(RIGHT & old_movement_state))
			press_key(go, KEY_D,1); 
		else if( !(RIGHT & p.movement_state) &&  (RIGHT & old_movement_state))
			press_key(go, KEY_D,0); 

		if ((GO_AHEAD & p.movement_state) &&  !(GO_AHEAD & old_movement_state))
			press_key(go, KEY_W,1); 
		else if( !(GO_AHEAD & p.movement_state) &&  (GO_AHEAD & old_movement_state))
			press_key(go, KEY_W,0); 

		if ((BACK & p.movement_state) &&  !(BACK & old_movement_state))
			press_key(go, KEY_S,1); 
		else if ( !(BACK & p.movement_state) &&  (BACK & old_movement_state))
			press_key(go, KEY_S,0); 

		old_movement_state = p.movement_state;
#endif
	}
}
int main(int argc, char *argv[])
{
	int choice = 1;
	char ch = 0;
	int x1 , y1;
	float vx, vy, vz = 0;
	x1 = 10;
	y1 = 10;
	int i = 0;
    	float pitch , yaw;
	FILE *fp  = NULL;
        int fd_mouse = 0;
        int fd_keyboard = 0;
	int event_mouse = 0;
	int event_keyboard = 0;
	char path_mouse_device[30] = {0};
	char path_keyboard_device[30] = {0};

        if ( argc > 2)
        {
            event_mouse = atoi(argv[1]);
            event_keyboard = atoi(argv[2]);
        }
	else
	{
            event_mouse = 17;
            event_keyboard = 3;
	}

        snprintf(path_mouse_device, sizeof(path_mouse_device), "/dev/input/event%d",event_mouse);
        snprintf(path_keyboard_device, sizeof(path_keyboard_device), "/dev/input/event%d",event_keyboard);
        printf("path to mouse event %s\n", path_mouse_device);
        printf("path to keyboard event %s\n", path_keyboard_device);

        fd_mouse = open(path_mouse_device, O_RDWR);
        fd_keyboard = open(path_keyboard_device, O_RDWR);

        if (fd_mouse < 0 || fd_keyboard < 0 ) {
            printf("Errro open mouse:%s\n", strerror(errno));
            return -1;
        }

	mouse *x = New(0, 0, constructor, destructor,fd_mouse,  mouse_click, move_xy );
	assert(x);

	game_obj *go = NULL;
       	go = gameobj_init( g_change_dev, g_movement, g_attach, event_keyboard);

	assert(go);
#ifdef SERIAL
	fp = device_init(dev_file);
	assert(fp);
	sleep(6);
	char tmp[200];
	fgets(tmp, sizeof(tmp), fp);
	puts(tmp);
#elif defined(MQTT)
	mqtt_init(x, go);
	sleep(1);
	mqtt_cmd(PAYLOAD_MQTT_START);
#endif
	do {
#ifdef SERIAL
		control(fp,x,go);
#elif defined(MQTT)
		ch = getchar();
#endif
	}
	while('q' != ch);
#ifdef SERIAL
       device_release(fp);
#elif defined(MQTT)
	mqtt_cmd(PAYLOAD_MQTT_STOP);
	mqtt_free();
#endif
    x->dstor(x);
    gameobj_des(go);
	
    return 0;
}
