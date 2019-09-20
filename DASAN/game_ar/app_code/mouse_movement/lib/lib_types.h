#ifndef _LIB_TYPES_H
#define _LIB_TYPES_H

#include <X11/Xutil.h>

#define RATIO  (35)

typedef struct {
	int x_current, y_current;	
	
	int width_max, height_max;	

	Display *dpy;
	Window root;

	void (*cstor)(void *self, int x_c, int y_c, Display *dpy
				, Window root);
	void (*dstor)(void *self);

	void (*move)(void *self,int x_des, int y_des,int jump_size, int speed);
	void (*click)(void *self, int btn);
	void (*dclick)(void *self);
	void (*btn_release)(void *self, int btn);
	void (*btn_press)(void *self, int btn);
	int  (*get_attr)(void *self, int *width, int *height);

}mouse;

#endif
