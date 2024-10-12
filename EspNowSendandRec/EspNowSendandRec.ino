/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x4C, 0x75, 0x25, 0x37, 0x7E, 0xD4};
uint8_t recAddress[] = {0xC8, 0xC9, 0xA3, 0x5D, 0x6B, 0xC9};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char ID[200];
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    strcat(myData.ID,"29/");

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    lastTime = millis();
  }
}

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) { 
 if (mac[0] == recAddress[0] && mac[1] == recAddress[1] && mac[2] == recAddress[2] && mac[3] == recAddress[3] && mac[4] == recAddress[4] && mac[5] == recAddress[5]) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Char: ");
    Serial.println(myData.ID);
 }
}
 