// Watch video here: https://www.youtube.com/watch?v=U0hJBc1Ppv4

/*
Accelerometer connection pins (I2C) to Arduino are shown below:

Arduino     Accelerometer ADXL345
  A5            SCL
  A4            SDA
  3.3V          CS
  3.3V          VCC
  GND           GND
  
Arduino     Servo No. 1
  5V          5V  (Red Wire)
  GND         GND (Black Wire)
  D5          (last wire for control - might be white color)
  
Arduino     Servo No. 2
  5V          5V  (Red Wire)
  GND         GND (Black Wire)
  D6          (last wire for control - might be white color)
*/

#include <Wire.h>
#include <ADXL345.h>

#include <Servo.h>

Servo servo1;  // create servo object to control a servo
Servo servo2;
Servo servo3;

ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

int x, y, z;
int rawX, rawY, rawZ;
int mappedRawX, mappedRawY, mappedRawZ;

void setup() {
  Serial.begin(9600);
  adxl.powerOn();
  servo1.attach(11);
  servo2.attach(10);
  servo3.attach(9);
  servo3.write(0);
}

void loop() {
  adxl.readAccel(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z

  rawX = x ;
  rawY = y ;
  rawZ = z ;
 
  if (rawX < -255) rawX = -255; else if (rawX > 255) rawX = 255;
  if (rawY < -255) rawY = -255; else if (rawY > 255) rawY = 255;
  if (rawZ < -255) rawZ = -255; else if (rawZ > 255) rawZ = 255;

//  Serial.print(" rawX = "); Serial.print(rawX); // raw data with offset
//  Serial.print(" rawY = "); Serial.print(rawY); // raw data with offset
//  Serial.print(" rawZ = "); Serial.println(rawZ); // raw data with offset
   
  mappedRawX = map(rawX, -255, 255, 0, 90) + 54;
  mappedRawY = map(rawY, -255, 255, 0, 180) + 22;
  mappedRawZ = map(rawZ, -255, 255, -100, 100) -94;

//    Serial.print(" mappedRawX = "); Serial.println(mappedRawX); // trate data with offset
//    Serial.print(" mappedRawY = "); Serial.println(mappedRawY); // trate data with offset
//    Serial.print(" mappedRawZ = "); Serial.println(mappedRawZ); // trate data with offset

//    Serial.print(" ServoX = ");Serial.println(servo1.read());
//    Serial.print(" ServoY = ");Serial.println(servo2.read());
  

  servo1.write(180 - mappedRawX);
  servo2.write(180 - mappedRawY);
  delay(300);

// SECURE PARACHUTE SYSTEM (remove else for prod)
  if(servo2.read() > 120 | servo2.read() < 25){
    servo3.write(180);
  }else{
    servo3.write(0);
  }
  
  Serial.print(" mappedRawX = "); Serial.print(mappedRawX); // raw data with offset
  Serial.print(" mappedRawY = "); Serial.println(mappedRawY); // raw data with offset
}
