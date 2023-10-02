#include <Servo.h>

Servo servo1;
int pinServo = 10;
int angulo = 0;
int inString = 0;
int call = 0;

void setup() {
  Serial.begin(9600);
  
//Pino do Servo
  servo1.attach(pinServo);
}

void loop() {
  if(Serial.available() > 0){
      inString = Serial.read();

        float angulo =inString;
        Serial.print("angulo: ");
        Serial.println(angulo);
        
        servo1.write(angulo);
        inString = "";
      
    }
}
