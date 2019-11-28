#ifndef _PROGESS_DATA_H_
#define _PROGESS_DATA_H_
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "lib_types.h"


enum command {
    COMMAND_REQUEST_PITCH_YAW = 0
};


/* get target (dx, dy) from (x1,y1) and velocity vx, vy  */
FILE* device_init(const char *file);
int device_release(FILE *fp);
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy);

int get_data(FILE *fp, float *pitch, float *yaw, float *roll);

void caculator_velocity(FILE *fp, mouse *self);

#endif
