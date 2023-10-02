#include <SPI.h>
#include <LoRa.h> 

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  
  while (!Serial);  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }else{
    digitalWrite(4, HIGH);
  }
}
 
void loop() {
  String val = "Holora";
  LoRa.beginPacket();  
  LoRa.print(val);
  LoRa.endPacket();
  Serial.println(val + " Estoy en Loop");

  digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  delay(50);                       // wait for a second

}
