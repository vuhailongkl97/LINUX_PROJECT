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
int device_init(const char *file);
int device_release(int fd);
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy);

int get_data(const int fd, float *pitch, float *yaw);

void caculator_velocity(const int fd, float *vx , float *vy);

#endif
