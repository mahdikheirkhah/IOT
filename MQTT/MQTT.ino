#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";

//const char* mqtt_server = "192.168.1.2";
const char* mqtt_server = "broker.hivemq.com";


WiFiClient esp8266device;
PubSubClient client(esp8266device);


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
 // Serial.println();
 // Serial.print("Connecting to ");
 // Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   // Serial.print(".");
  }
 // Serial.println("");
 // Serial.print("WiFi connected - ESP IP address: ");
 // Serial.println(WiFi.localIP());
}


void callback(String topic, byte* message, unsigned int length) {
 // Serial.print("Message arrived on topic: ");
 // Serial.print(topic);
 // Serial.print(". Message: ");
  String messagein;
  
  for (int i = 0; i < length; i++) {
   // Serial.print((char)message[i]);
    messagein += (char)message[i];
  }  
}


void reconnect() {
  while (!client.connected()) {
  //  Serial.print("Attempting MQTT connection...");
 
    

    if (client.connect("device1")) {

      //Serial.println("connected");  
      client.subscribe("room1/heater");
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(client.state());
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
   randomSeed(analogRead(0));

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("device1");
    // int temp=random(0, 100);
    //    char t [8];
    //    dtostrf(temp,6,2,t);         
   client.publish("radar/distance","mohammad mahdi kheirkhah 9821160014");
  delay(2000);
  
} 
