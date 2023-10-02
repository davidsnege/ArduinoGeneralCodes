#include <SPI.h>
#include <SX127x.h>
SX127x LoRa;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Begin LoRa radio");
  int8_t txenPin = 8, rxenPin = 7;
  if (LoRa.begin(txenPin, rxenPin)){
    Serial.println("Something wrong, can't begin LoRa radio");
    while(9);
  }
}

void loop() {

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.endPacket();
  delay(1000);
}
