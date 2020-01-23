#ifndef __MQTT_LIB_H
#define __MQTT_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
#include "progess_data.h"
#include "lib_types.h"
#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "ExampleClientSub"
#define TOPIC       "outTopic"
#define TOPIC_TRIGGER_EVENT       "trigger_event"
#define PAYLOAD_MQTT_START    "1"
#define PAYLOAD_MQTT_STOP    "0"
#define PAYLOAD_MQTT_OFF    "2"
#define QOS         1
#define TIMEOUT     10000L

static MQTTClient client;
volatile MQTTClient_deliveryToken deliveredtoken;
void delivered(void *context, MQTTClient_deliveryToken dt);

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
void connlost(void *context, char *cause);
#ifdef MQTT
extern void control(MQTTClient_message *, mouse *, game_obj *);
#endif
void mqtt_init(mouse *x , game_obj *go);
void mqtt_free();
void mqtt_cmd(char *cmd);

#endif
