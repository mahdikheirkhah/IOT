Sonar-Based Object Detection and Distance Measurement with MQTT and Node-RED Visualization
Project Overview
This project utilizes an ultrasonic sensor (HY-SRF05), a servo motor (SG90), and an ESP8266 microcontroller to detect and measure the length of objects in front of the sensor. It uses a Kalman filter to process the distance data and sends the measurements via MQTT protocol to Node-RED, where the data is visualized on a dashboard. The system performs a continuous scan of the area by rotating the servo motor and updates the object information in real-time.

Components Used
ESP8266: Handles Wi-Fi connectivity and MQTT communication.
HY-SRF05 Ultrasonic Sensor: Measures the distance to objects.
SG90 Servo Motor: Rotates the sensor for a sweeping scan.
Kalman Filter: Filters the raw distance data to improve accuracy.
Node-RED: Visualizes the data on a custom dashboard.
MQTT Protocol: Sends the data to Node-RED for processing.
How It Works
Distance Measurement:

The ultrasonic sensor (HY-SRF05) measures the distance to an object.
The servo motor rotates from 0 to 180 degrees and back, scanning the area.
The distance data is filtered using a Kalman filter for smoother results.
Object Length Calculation:

The code calculates the length of objects based on the distance measurements taken at different angles.
If a significant change in distance is detected, the length of the shape in front of the sensor is calculated using trigonometric formulas.
Data Transmission:

The processed data is sent via MQTT to the topic "radar" for angle and distance data, and "radar/ShapeLength" for object lengths.
Node-RED receives and visualizes the data on its dashboard.
Visualization:

Node-RED is used to create a real-time visualization of the sonar readings.
The Node-RED flow has been exported to the project.js file for easy import into your Node-RED environment.
Setup Instructions
Hardware Setup
Connect the Components:
Connect the HY-SRF05 sensor's trig and echo pins to the ESP8266.
Connect the SG90 servo motor to the ESP8266.
Ensure the power supply is sufficient to drive both the ESP8266 and the servo motor.
Software Setup
Libraries Required: Ensure you have the following libraries installed in the Arduino IDE:

Servo.h
ESP8266WiFi.h
PubSubClient.h
SimpleKalmanFilter.h
Wi-Fi and MQTT Configuration: Update the following details in the code with your Wi-Fi and MQTT server credentials:

    const char* ssid = "Your_SSID";
    const char* password = "Your_PASSWORD";
    const char* mqtt_server = "Your_MQTT_Broker_Address";


Connect your ESP8266 to your computer via USB.
Upload the code using the Arduino IDE.
Node-RED Setup:

Import the Node-RED flow from the project.js file into your Node-RED instance.
Configure the MQTT nodes in Node-RED to match your MQTT server settings.
Node-RED Flow Import
To import the Node-RED flow:

Open the Node-RED editor in your browser.
Click on the menu in the top right corner and select "Import."
Paste the contents of the project.js file into the import dialog and click "Import."
Source of Code and Visualization
Part of the code and the visualization logic for this project were sourced and adapted from the following link: https://drive.google.com/drive/folders/0BwsV1jJYW9dnenRYYXRneUtLcnM?resourcekey=0-axsBFCosolW_5i1X1cXRVw.
If you use or modify this code, please consider checking the original content for any licensing or attribution requirements.
Future Enhancements
Improve Object Detection: Implement more advanced algorithms for better shape detection.
Enhanced Visualization: Add more graphical elements to the Node-RED dashboard for improved data presentation.
Dynamic Calibration: Include calibration routines to adjust the sensor and servo positions automatically.
License
This project is open-source. Feel free to use and modify the code for your own applications. Contributions are welcome!