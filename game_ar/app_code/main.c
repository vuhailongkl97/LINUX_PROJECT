#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "lib_mouse.h"


#include "lib_game_obj.h"

void test_mouse(void *_self,int x_des, int y_des, int speed)
{
	mouse *self = _self;
	self->move(self,x_des,y_des,1,speed);	
}
void mtest(mouse *x)
{
	test_mouse(x, -10, 220, 1);
	
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
int main(int argc, char *argv[])
{
        int fd_mouse = 0;
        int fd_keyboard = 0;
	int i = 0;
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

	gtest(go);

	x->dstor(x);
	gameobj_des(go);
	
        return 0;
}

