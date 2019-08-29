#include <stdio.h>
#include <time.h>
#include <X11/Xutil.h>
#include <assert.h>
#include "progess_data.h"
#include "lib_mouse.h"

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

	dpy = XOpenDisplay(0);
	root_window = XRootWindow(dpy, 0);
	XSelectInput(dpy, root_window, KeyReleaseMask);
	mouse *x = New(100, 100, dpy, root_window, constructor, destructor,
	mouse_click, mouse_double_click, mouse_release, move_xy
	, get_attribute, mouse_press);

	assert(x);
	show_attribute(x);
	do {
		printf("enter vx, vy ");
		scanf("%f%f", &vx, &vy);
		get_target(x->x_current,x->y_current,vx,vy,&retx, &rety);
		x->move(x, retx, rety, 1, 1);
		printf("retx, rety %d %d\n", retx, rety);
		printf("enter choice > 0 to continue ");
		scanf("%d", &choice);
	}
	while(0 != choice);

		x->dstor(x);
    return 0;
}

