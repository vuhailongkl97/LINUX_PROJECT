#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include "lib_mouse.h"
#include "progess_data.h"

#include "lib_game_obj.h"
#include "milis.h"


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
void control(FILE *fp, mouse *x,game_obj *go)
{
	int opt = 0;
	static int timeout = 0;
	static int change_dev = 0 ;
	pdata p;
	get_data(fp,&p);
	static int ready_change_dev = 1;
	//printf("pitch %f yaw %f roll %f\n",p.pitch, p.yaw, p.roll);

	switch (p.mouse_state)
	{
		case LEFT_CLICK:
			x->click(x);			
			break;
		case RIGHT_CLICK:
		case STOP_MOVE:
		default:
			break;
	}
	
	if (p.mouse_state != STOP_MOVE)
	{
		int retx, rety;
		caculator_velocity(fp, x);
		get_target(x->x_current,x->y_current,x->current_vx, x-> current_vy, &retx, &rety);
		
	        //printf("xret = %d , yret = %d vx %f vy %f\n", retx, rety,x->current_vx, x->current_vy);
		//retx = retx > 400 ? 400 : retx;
		//retx = retx < -400 ? -400 : retx;
		//rety = rety > 400 ? 400 : rety;
		//rety = rety < -400 ? -400: rety;
		
		printf("p.roll %f\n" , p.roll);
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
	        	
		dont_move:
		switch (p.movement_state)
		{
			case  LEFT :
				press_key(go, KEY_A,1); 
				press_key(go, KEY_A,0); 
				break;
			case  RIGHT :
				press_key(go, KEY_D,1); 
				press_key(go, KEY_D,0); 
				break;
			case  GO_AHEAD :
				press_key(go, KEY_W,1); 
				press_key(go, KEY_W,0); 
				break;
			case  BACK :
				press_key(go, KEY_S,1); 
				press_key(go, KEY_S,0); 
				break;
			default:
				//fprintf(stderr, "movement incorrect %s %d ", __FUNCTION__, __LINE__);
				break;
		}
	}

}
int main(int argc, char *argv[])
{

	int choice = 1;
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

	fp = device_init(dev_file);

	assert(fp);
	sleep(6);
	char tmp[200];
	fgets(tmp, sizeof(tmp), fp);
	puts(tmp);

	do {
		control(fp,x,go);
	}
	while(0 != choice);
       device_release(fp);
    x->dstor(x);
    gameobj_des(go);
	
    return 0;
}
