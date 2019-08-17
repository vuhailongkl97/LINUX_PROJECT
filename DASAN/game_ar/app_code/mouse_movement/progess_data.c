#include "progess_data.h"

/*
    (x3,y3)             (dx,dy)
	-------------------
	|		  |
	^		  |
	|		  |
	vy		  |
	|		  |
	-------vx ->-------
    (x1,y1)        (x2,y2)

	(dx,dy) = (x2,y3);
*/
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy)
{
	int x2,y3;
	
	x2 = x1 + VELOCITY_TO_PIXEL(vx);		
	y3 = y1 + VELOCITY_TO_PIXEL(vy);

	*dx =  x2;
	*dy =  y3;

	return 0;	
}
