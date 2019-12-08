#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
/* change it with your ssid-password */
const char* ssid = "WIfi Nha Minh";
const char* password = "12345678";
/* this is the IP of PC/raspberry where you installed MQTT Server 
on Wins use "ipconfig" 
on Linux use "ifconfig" to get its IP address */
const char* mqtt_server = "192.168.0.106";

float temperature = 0;

/* create an instance of PubSubClient client */
WiFiClient espClient;
PubSubClient client(espClient);
/* topics */
#define DATA_TRANSFER    "outTopic"
#define TRIGGER_EVENT     "trigger_event" /* 1=on, 0=off */

long lastMsg = 0;
char msg[20], msg2[50];
int data;

#define RXD2 16
#define TXD2 17
#define WAIT_TIME_SEND_MQTT 50
#define WAIT_TIME_GET_DATA 10
int synced;
char ch ;
int serialCount;
char buffer[30],buffer4send[30];
int ok = 1;
int stop_send_data = 1;
void receivedCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received: ");
  Serial.println(topic);

  Serial.print("payload: ");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
  if (length > 0)
  {
  if(payload[0] == '1')
  {
    stop_send_data = 0;
  }
  else 
  {
    stop_send_data = 1;  
  }
  }

}

void mqttconnect() {
  /* Loop until reconnected */
  while (!client.connected()) {
    Serial.print("MQTT connecting ...");
    /* client ID */
    String clientId = "ESP32Client";
    /* connect now */
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      /* subscribe topic with default QoS 0*/
      client.subscribe(TRIGGER_EVENT);
    } else {
      Serial.print("failed, status code =");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      /* Wait 5 seconds before retrying */
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TX));
  Serial.println("Serial Rxd is on pin: "+String(RX));
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /* configure the MQTT server with IPaddress and port */
  client.setServer(mqtt_server, 1883);
  /* this receivedCallback function will be invoked 
  when client received subscribed topic */
  client.setCallback(receivedCallback);
  /*start DHT sensor */
 
}
long long last_time4sendMQTT = 0, last_time4getData = 0;
char ready4send = 0;
void loop() {
  /* if client was disconnected then try to reconnect again */
  head1:
  if (!client.connected()) {
    mqttconnect();
  }
  /* this function will listen for incomming 
  subscribed topic-process-invoke receivedCallback */
  client.loop();
  /* we measure temperature every 3 secs
  we count until 3 secs reached to avoid blocking program if using delay()*/
  if ( ok == 1 && (millis() - last_time4getData >  WAIT_TIME_GET_DATA))
  {
    Serial2.println("a");
    last_time4getData = millis();
    //Serial2.print((char)Serial.read());  
  }
  
  if(Serial2.available()) {
    ok =0;
    ch = (char)Serial2.read();
    if(synced  == 0 && ch != '^')
      goto head1;
    synced = 1;
    if (serialCount > sizeof(buffer))
    {
      synced = 0;
      goto head1;
    }
    if(serialCount > 0 || ch == '^')
    {
      if( ch == '\n')
      {
        serialCount = 0;
        ok = 1;
        //Serial.println(buffer);  
        strncpy(buffer4send, buffer, sizeof(buffer));
        memset(buffer, 0, sizeof(buffer));
        ready4send = 1;
        delay(5);
        goto head1;
      }
      buffer[serialCount++] = ch;
    }
  }
  if ( (ready4send) && (millis() - last_time4sendMQTT > WAIT_TIME_SEND_MQTT )&& (!stop_send_data))
  {
    client.publish(DATA_TRANSFER, buffer4send);
    last_time4sendMQTT = millis();
  }

}
