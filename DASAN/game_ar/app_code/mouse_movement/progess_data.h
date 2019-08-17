#ifndef _PROGESS_DATA_H_
#define _PROGESS_DATA_H_
#include <stdio.h>
#include <math.h>
#include "lib_types.h"

/* get target (dx, dy) from (x1,y1) and velocity vx, vy  */
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy);

#endif
