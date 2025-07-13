#include "HUSKYLENS.h"         // Include Huskylens library 
#include <smorphi.h>           // Include Smorphi Square Library
#include "SoftwareSerial.h"    // Include Software Serial for Communication

Smorphi my_robot;   // Declare smorphi as an object.
HUSKYLENS huskylens; // Declare huskylens as an object
SoftwareSerial myHuskySerial(19, 18); // TX , RX (Adjust the ports according to your requirement)

int bottom_left_sensor_status; // Define the bottom left sensor
int bottom_right_sensor_status; // Define the bottom right sensor

void setup() {
  Serial.begin(115200);   // Beginning the Serial Monitor; adjust your baud rate.
  myHuskySerial.begin(9600); // Beginning the huskylens serial monitor, adjust the baud rate according to your requirement.
  my_robot.BeginSmorphi();  // Main line to begin the robot.

  while (!huskylens.begin(myHuskySerial)) {
    Serial.println(F("HuskyLens not connected!"));  // Checking if the huskylens started or not
    delay(1000);  // Delay for stability
  }


}

void loop() {
  bottom_left_sensor_status = my_robot.module1_sensor_status(0);  // Defining the sensor port for bottom left sensor, adjust if needed.
  bottom_right_sensor_status = my_robot.module1_sensor_status(4); // Defining the sensor port for bottom right sensor, adjust if needed.

  if (huskylens.request() && huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();
    int qrID = result.ID;                                 //QR ID changes according to the tag scanned.
    Serial.print("QR Detected: "); Serial.println(qrID);
    handleQR(qrID);
    return; // Skip IR movement this loop
  }

  // Maze solving using bottom IR sensors
  if (bottom_left_sensor_status == 1 && bottom_right_sensor_status == 1) {
    my_robot.MoveForward(30);
  } 
  else if (bottom_left_sensor_status == 1 && bottom_right_sensor_status == 0) {
    my_robot.MoveTurnUpLeft(30, 100);
  } 
  else if (bottom_left_sensor_status == 0 && bottom_right_sensor_status == 1) {
    my_robot.MoveTurnUpRight(30, 100);
  } 
  else {
    my_robot.stopSmorphi();
    delay(200);
    my_robot.MoveTurnUpLeft(30, 80);
    delay(300);
    my_robot.MoveTurnUpRight(30, 80);
    delay(300);
    my_robot.stopSmorphi();
  }

  delay(30);
}

void handleQR(int id) {
  switch (id) {                              // Switch case allows you to mention what exactly must the robot do once it scans a particular tag. Adjust the robot function according to your task.
    case 1:
      my_robot.CenterPivotRight(270);
      delay(1500);
      break;
    case 2:
      my_robot.CenterPivotLeft(270);
      delay(1500);
      break;
    case 3:
      my_robot.MoveForward(40);
      delay(1000);
      break;
    case 4:
      my_robot.CenterPivotLeft(270);
      delay(1500);
      my_robot.MoveForward(40);
      delay(800);
      break;
    case 5:
      my_robot.MoveForward(40);
      delay(1500);
      my_robot.CenterPivotLeft(270);
      delay(1500);
      break;
    case 6:
      my_robot.CenterPivotRight(270);
      delay(1500);
      my_robot.MoveForward(40);
      delay(1000);
      break;
    case 7:
      my_robot.CenterPivotRight(270);
      delay(2000);
      break;
    case 8:
      my_robot.sm_reset_M1();
      my_robot.sm_reset_M2();     // Resetting the modules
      my_robot.sm_reset_M3();
      my_robot.sm_reset_M4();
      my_robot.O();
      break;
    default:
      my_robot.stopSmorphi();
      break;
  }
  delay(500);
}
