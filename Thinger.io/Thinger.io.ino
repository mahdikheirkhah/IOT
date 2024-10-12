/*
 Hello World Thinger.io -Blink-

 This code is under public domain.
 Dani No www.esploradores.com
 */

#include <ESP8266WiFi.h>       //ESP8266 WiFi connection library
#include <ThingerESP8266.h>    //THINGER.IO library

// Thinger.io connection parameters
#define user "use your own"
#define device_Id "use your own"
#define device_credentials "use your own"
ThingerESP8266 thing(user, device_Id, device_credentials);

// WiFi connection parameters
const char WiFi_ssid[]= "SSID";      //WiFi SSID
const char WiFi_password[]= "password";  //WiFi password
// Global variable
int led = LED_BUILTIN;       // GPIO02 - D4 

void setup() {

 // Initialization of the WiFi connection with THINGER.IO
   thing.add_wifi(WiFi_ssid, WiFi_password);

 // Initialization of the LED
   pinMode(led, OUTPUT);

 // Resource for changing LED status from THINGER.IO
  thing["MahdiKheirkhah-9821160014"] << [](pson & in){
    if(in.is_empty()){
      in = (bool) digitalRead(LED_BUILTIN);
      }
    else{
      digitalWrite(LED_BUILTIN, in ? HIGH : LOW);
      }
    };
  }

void loop() {
  thing.handle();
  }