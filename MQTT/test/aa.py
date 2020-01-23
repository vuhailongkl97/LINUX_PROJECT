

import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    client.publish("test_mqtt", "test")
    client.subscribe("test")

def on_disconnect(client, userdata, rc):
    print("Disconnect, reason: " + str(rc))
    print("Disconnect, reason: " + str(client))

client = mqtt.Client("testclient", protocol=mqtt.MQTTv31)
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.connect("127.0.0.1", 1883, 60)
client.loop_forever()


