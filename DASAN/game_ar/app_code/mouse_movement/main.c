#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "lib_mouse.h"
int fd_mouse = 0;

void test_mouse(void *_self,int x_des, int y_des, int speed)
{
	mouse *self = _self;
	self->move(self,x_des,y_des,1,speed);	
}

int main(int argc, char *argv[])
{
	int i = 0;
	int event_n = 0;
	char path_device[30] = {0};


	mouse *x = New(0, 0, constructor, destructor, mouse_click, move_xy, NULL);

	assert(x);

        if ( argc > 1)
        {
            event_n = atoi(argv[1]);
        }

        snprintf(path_device, sizeof(path_device), "/dev/input/event%d",event_n);
        puts(path_device);

        fd_mouse = open(path_device, O_RDWR);
        if (fd_mouse < 0) {
            printf("Errro open mouse:%s\n", strerror(errno));
            return -1;
        }
	x->btn_press(x,1);
	test_mouse(x, 150, 220, 1);
	printf("self .x.y = %d %d", x->x_current, x->y_current);
	sleep(4);
	test_mouse(x, 0, 0, 1);
	printf("self .x.y = %d %d", x->x_current, x->y_current);
	sleep(3);
	test_mouse(x, -40, -70, 1);
	x->btn_release(x,1);
	x->dstor(x);
	close(fd_mouse);
	
        return 0;
}

