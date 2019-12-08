#ifndef _PROGESS_DATA_H_
#define _PROGESS_DATA_H_
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "lib_types.h"
#include <MQTTClient.h>
#define DATA_FORMAT "%f %f %f %d %d"

enum command {
    COMMAND_REQUEST_PITCH_YAW = 0
};
typedef struct {
   float pitch, yaw, roll;
   int mouse_state;
   int movement_state;

}pdata;


/* get target (dx, dy) from (x1,y1) and velocity vx, vy  */
FILE* device_init(const char *file);
int device_release(FILE *fp);
int get_target(int x1, int y1, float vx, float vy, int *dx, int *dy);

#ifdef SERIAL
int get_data(FILE *fp, pdata *p);
void caculator_velocity(FILE *fp, mouse *self);
#elif defined(MQTT)
int get_data(MQTTClient_message *, pdata *p);
void caculator_velocity(MQTTClient_message *, mouse *self);

#endif

#endif
