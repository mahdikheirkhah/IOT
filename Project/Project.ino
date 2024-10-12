#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SimpleKalmanFilter.h>
#define trigPin  D8
#define echoPin  D2
const char* ssid = "";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient esp8266device;
PubSubClient client(esp8266device);
Servo myServo;
SimpleKalmanFilter kalmanFilter(2, 2, 0.01);

struct point{
  int distance = 0;
  int angle = 0;
}point1,point2;

long duration;
int distance;
char dis[20];
char angle[20];
char len[20];
//char shapenum[20];
char mqtt_send[80];
int index_counter = 0;
static bool firstPoint = true;
static int shapeNumber = 1;
int length = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(D13);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
   Serial.print(".");
  }
  client.setServer(mqtt_server, 1883);
}
void loop() {
    if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("device1");
  for(int i=0;i<=180;i++){  
  myServo.write(i);
  delay(30);
  distance = int(kalmanFilter.updateEstimate(calculateDistance()));
  calculateLength(distance,i);
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  dis[0] = '\0';
  angle[0] = '\0';
  itoa(distance,dis,10);
  itoa(i,angle,10);
  mqtt_send[0] = '\0';
  index_counter = 0;
  for (int j = 0; angle[j] != '\0'; j++) {
    mqtt_send[index_counter] = angle[j];
    index_counter++ ;
  }
  mqtt_send[index_counter] = ',';
  index_counter++ ;
  for (int j = 0; dis[j] != '\0'; j++) {
    mqtt_send[index_counter] = dis[j];
    index_counter++;  
  }
  mqtt_send[index_counter] = '.';
  index_counter++;
  client.publish("radar",mqtt_send);
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=180;i>0;i--){  
  myServo.write(i);
  delay(30);
  distance = int(kalmanFilter.updateEstimate(calculateDistance()));
  calculateLength(distance,i);
  Serial.print(myServo.read());
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  dis[0] = '\0';
  angle[0] = '\0';
  itoa(distance,dis,10);
  itoa(i,angle,10);
    mqtt_send[0] = '\0';
  index_counter = 0;
  for (int j = 0; angle[j] != '\0'; j++) {
    mqtt_send[index_counter] = angle[j];
    index_counter++ ;
  }
  mqtt_send[index_counter] = ',';
  index_counter++ ;
  for (int j = 0; dis[j] != '\0'; j++) {
    mqtt_send[index_counter] = dis[j];
    index_counter++;  
  }
  mqtt_send[index_counter] = '.';
  index_counter++;
  client.publish("radar",mqtt_send);
  }

}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  int distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("device1")) {
    }
  }
}
void calculateLength(int distance, int i) {
 if ((distance < 41) && firstPoint) {
    point1.distance = distance;
    point1.angle = i;
    //initialDistance = distance; // Store the initial distance
    firstPoint = false;
  } else {
    // Calculate the percentage change from the initial distance
    //double percentChange = (distance - initialDistance) / static_cast<double>(initialDistance) * 100;
    if (distance - point1.distance >= 5) { // Adjust the threshold percentage as needed
      length = int(sqrt((point1.distance * point1.distance) + (point2.distance * point2.distance) - (2 * point2.distance * point1.distance * abs(cos(abs(point2.angle - point1.angle))))));

      itoa(length,len,10);
      //itoa(shapeNumber,shapenum,10);
      client.publish("radar/SahpeLength",len);
      //client.publish("radar/ShapeNumber",shapenum);
      shapeNumber++;
      firstPoint = true;
    }
    point2.distance = distance;
    point2.angle = i;
  }  
 }