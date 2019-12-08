#include "mqtt_lib.h"

mouse  *x;
game_obj *go;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char* payloadptr;
    payloadptr = message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');

    control(message, x, go);

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}
void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}
void mqtt_init(mouse *_x, game_obj *_go)
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    x = _x;
    go = _go;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);

}
void mqtt_free()
{
	MQTTClient_disconnect(client, 10000);
	MQTTClient_destroy(&client);
}
void mqtt_kick_start_get_data()
{
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_deliveryToken token;
	pubmsg.payload = PAYLOAD_START;
	pubmsg.payloadlen = strlen(PAYLOAD_START);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	deliveredtoken = 0;
	MQTTClient_publishMessage(client, TOPIC_TRIGGER_EVENT, &pubmsg, &token);
	printf("Waiting for publication of %s\n"
           "on topic %s for client with ClientID: %s\n",
            PAYLOAD_START, TOPIC, CLIENTID);
	while(deliveredtoken != token);
	usleep(5000);
}
void mqtt_kick_stop_get_data()
{
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_deliveryToken token;
	pubmsg.payload = PAYLOAD_STOP;
	pubmsg.payloadlen = strlen(PAYLOAD_STOP);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	deliveredtoken = 0;
	MQTTClient_publishMessage(client, TOPIC_TRIGGER_EVENT, &pubmsg, &token);
	printf("Waiting for publication of %s\n"
           "on topic %s for client with ClientID: %s\n",
            PAYLOAD_STOP, TOPIC, CLIENTID);
	while(deliveredtoken != token);
	usleep(5000);
}
