#include <stdio.h>
#include <time.h>
#include <X11/Xutil.h>
#include <assert.h>
#include "lib_mouse.h"
#include "progess_data.h"


void test_get_target(int x1, int y1, float vx, float vy)
{
	int retx, rety;

	get_target(x1,y1,vx, vy, &retx, &rety);
	printf("ok move from (%d,%d) -> (%d, %d) vx = %f, \
			vy = %f\n", x1, y1, retx, rety, vx , vy);
}
int main(int argc, char *argv[])
{

	int choice = 1;
	int x1 , y1, retx, rety;
	float vx, vy;
	x1 = 10;
	y1 = 10;
	int i = 0;
	Display *dpy;
	Window root_window;
    	float pitch , yaw;
	int fd  = 0;

	fd = device_init(dev_file);

	assert(fd > 0);

printf("kkk\n");
	dpy = XOpenDisplay(0);
	root_window = XRootWindow(dpy, 0);
	XSelectInput(dpy, root_window, KeyReleaseMask);
	mouse *x = New(100, 100, dpy, root_window, constructor, destructor,
	mouse_click, mouse_double_click, mouse_release, move_xy
	, get_attribute, mouse_press);

	assert(x);
	show_attribute(x);
	x->move(x, 609, 336, 1, 10);
	x->click(x,1);
	sleep(1);
	x->dclick(x);

	do {
		//printf("enter vx, vy ");
		//scanf("%f%f", &vx, &vy);
		caculator_velocity(fd, &vy, &vx);
		get_target(x->x_current,x->y_current,vx,vy,&retx, &rety);
		//retx = retx > x->width_max ? x->width_max : retx;
		//retx = retx < 0 ? 0 : retx;
		//rety = rety > x->height_max ? x->height_max : retx;
		//rety = rety < 0 ? 0: rety;
	
		x->move(x, retx, rety, 1, 10);
		//printf("retx, rety %d %d\n", retx, rety);
		//printf("enter choice > 0 to continue ");

//		scanf("%d", &choice);
	}
	while(0 != choice);

   		device_release(fd);
		x->click(x,1);
		x->dstor(x);

        //get_data(fd, &pitch, &yaw);
	
    return 0;
}

