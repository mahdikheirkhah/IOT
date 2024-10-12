#include <ESP8266WiFi.h>       //ESP8266 WiFi connection library
#include <ThingerESP8266.h>    //THINGER.IO library

#define user ""
#define device_Id ""
#define device_credentials ""
ThingerESP8266 thing(user, device_Id, device_credentials);

// WiFi connection parameters
const char WiFi_ssid[]="";      //WiFi SSID
const char WiFi_password[]="";  //WiFi password
// Global variable
int led = 2;       // GPIO02 - D4 

void setup() {

 // Initialization of the WiFi connection with THINGER.IO
   thing.add_wifi(WiFi_ssid, WiFi_password);
   randomSeed(analogRead(0));
  }

int flag = 1;
void loop() {
  thing.handle();
  pson data;
  data["name"] ="test";
  data["humadity"]= random(0,100);
  if (data["humadity"] >= 50) {
    thing.call_endpoint("E1403",data);
  }
}
