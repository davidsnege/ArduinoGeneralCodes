#include <SPI.h>
#include <LoRa.h> 

String inString = "";    // string to hold input
String val = "";
 
void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
 
void loop() {
  
int packetSize = LoRa.parsePacket();

  
 
    
      while (LoRa.available())
      {
        int packetSize = LoRa.parsePacket();    
        int inChar = LoRa.read();
        inString += (char)inChar;
        val = inString.toInt();   
      } 
      LoRa.packetRssi();    
  
    Serial.println(inString);
    inString = "";

    digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
    delay(500); 
    digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);   


}
