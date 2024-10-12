/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This sketch shows how to read values from Virtual Pins

  App dashboard setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/

// Comment this out to disable prints and save space /
#define BLYNK_PRINT Serial

// Fill in information from Blynk Device Info here /
#define BLYNK_TEMPLATE_ID           "TMPLxtV4hPSz"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "--3GaQg8CpSSqPrVs4B_TucLmcLFYdLT"



#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



// Your WiFi credentials.
char ssid[] = "Mi Phone";
char pass[] = "mahdi1379";

int LED = LED_BUILTIN; // Define LED as an Integer (whole numbers) and pin D8 on Wemos D1 

//WidgetLCD vlcd(V7);

float CurTemp=37.2;
float CurHum=50.5;
int Par=1;

BlynkTimer timer;

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1


void setup()
{
  // Debug console
  Serial.begin(9600);
    pinMode(LED, OUTPUT); //Set the LED (D2) as an output
       Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
        randomSeed(analogRead(0));
//timer.setInterval(2000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  // timer.run(); // Initiates BlynkTimer

 
  //lcd.clear();
 // vlcd.clear();
  //*******************************************
  // lcd.setCursor(0, 0);
 // lcd.print("p:");
 // lcd.print(Par);
 //  vlcd.print(0,0,"P:");
 //   vlcd.print(2,0,Par);
  //***********************************************
//  lcd.setCursor(0, 1);
//  lcd.print("T:");
//  lcd.print(CurTemp);
//  vlcd.print(0,1,"T:");
//  vlcd.print(2,1,CurTemp);
 // lcd.setCursor(0, 1);
//  lcd.print(" H:");
 // lcd.print(CurHum);
 // vlcd.print(6,1," H:");
 // vlcd.print(8,1,CurHum);
 //delay(1000);
  
  
 //  
 //  delay(1000);
  // vlcd.clear();
  // 
   // delay(1000);
}



BLYNK_WRITE(V3) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
 if (pinValue == 1) {
    digitalWrite(LED, HIGH); // Turn LED on.
  } else {
    digitalWrite(LED, LOW); // Turn LED off.
 }
}



BLYNK_READ(V6) // Widget in the app READs Virtal Pin V5 with the certain frequency
{
  // This command writes Arduino's uptime in seconds to Virtual Pin V5
  String S=(String)random(0, 100);
  Blynk.virtualWrite(7, S);
 
}
