
#include "LiquidCrystal_I2C.h"
#include "SPI.h" 
#include "RF24.h" 
#include "nRF24L01.h" 
#define CE_PIN 9 
#define CSN_PIN 10 
#define INTERVAL_MS_SIGNAL_LOST 1000 
#define INTERVAL_MS_SIGNAL_RETRY 250 
#define INTERVAL_MS_TRANSMISSION 250 

RF24 radio(CE_PIN, CSN_PIN); 
const byte address[6] = "00001"; 
////NRF24L01 buffer limit is 32 bytes (max struct size) 
struct payload { 
   byte data1; 
   char data2; 
}; 
payload payload; 
unsigned long lastSignalMillis = 0; 

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{ 
    // Testando I2C LCD
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                // initialize the lcd
  lcd.backlight();           // Turn on backlight
  lcd.print("Radio Defined");// Print a message to the LCD

  delay(1000);
  
   Serial.begin(115200); 
   radio.begin(); 
//   //Append ACK packet from the receiving radio back to the transmitting radio 
   radio.setAutoAck(true); //(true|false) 
//   //Set the transmission datarate 
   radio.setDataRate(RF24_2MBPS); //(RF24_250KBPS|RF24_1MBPS|RF24_2MBPS) 
//   //Greater level = more consumption = longer distance 
   radio.setPALevel(RF24_PA_MAX); //(RF24_PA_MIN|RF24_PA_LOW|RF24_PA_HIGH|RF24_PA_MAX) 
//   //Default value is the maximum 32 bytes1 
   radio.setPayloadSize(sizeof(payload)); 
//   //Act as receiver 
   radio.openReadingPipe(0, address); 
   radio.startListening(); 
   delay(1000);
} 



void loop() 
{ 
   unsigned long currentMillis = millis(); 
   if (radio.available() > 0) { 
     radio.read(&payload, sizeof(payload)); 
     Serial.println("Received"); 
     Serial.print("Data1:"); 
     Serial.println(payload.data1); 
     Serial.print("Data2:"); 
     Serial.println(payload.data2); 
     lastSignalMillis = currentMillis; 
   } 
   
   if (currentMillis - lastSignalMillis > INTERVAL_MS_SIGNAL_LOST) { 
     lostConnection(); 
     lcd.setCursor(0, 1);
     lcd.print("No Signal Radio");
   }else{ 

    lcd.setCursor(0, 1);
    lcd.print("received: ");
    lcd.setCursor(10, 1);
    lcd.print(payload.data2);
    delay(1000);
    lcd.setCursor(10, 1);
    lcd.print(payload.data1);
    delay(1000);
    lcd.setCursor(10, 1);
    lcd.print("      ");
   }
} 



void lostConnection() 
{ 
   Serial.println("We have lost connection, preventing unwanted behavior"); 
   delay(INTERVAL_MS_SIGNAL_RETRY); 
} 
// I2C Address TEST 
bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}
