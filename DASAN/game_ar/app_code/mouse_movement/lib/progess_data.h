#ifndef _PROGESS_DATA_H_
#define _PROGESS_DATA_H_
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "lib_types.h"


enum command {
    COMMAND_REQUEST_PITCH_YAW = 0
};


/* get target (dx, dy) from (x1,y1) and velocity vx, vy  */
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy);

int get_data(char *dev_path, float *pitch, float *yaw);

void caculator_velocity(const char *dev_path, float *vx , float *vy);

#endif
