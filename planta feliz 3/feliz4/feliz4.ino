/* PLANTA FELIZ 3.0 CON ALARMA DE BUZZER PARA REGAR */



/* importando as bibliotecas que precisamos ----- */

#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>

/* Defininindo valores de pinos para sensor DHT11 */
#define DHTPIN 3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* Iniciando o LCD 16x2 com a quantidade de pinos */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Declarando variaveis ------------------------- */
const int button = 4; /*Pino Button de menu*/
      int menu=0;     /*Valor inicial do menu*/
      int moisture=0; /*Valor inicial do menu*/
      int regarSi=0;

const int pos;
const int lin;


byte leftHeart[] = {
  0x04,
  0x0E,
  0x1F,
  0x1F,
  0x0F,
  0x07,
  0x03,
  0x01
};

byte rightHearth[] = {
  0x04,
  0x0E,
  0x1F,
  0x1F,
  0x1E,
  0x1C,
  0x18,
  0x10
};




/*
 * Inicializamos tudo que vamos usar
 */
void setup() {


buzzerPerigo(); delay(600);

/* Inciando Pinos IN OUT ------------------------ */

pinMode(7, OUTPUT); /*buzzer de som*/
pinMode(A0, OUTPUT); /*Entrada de energia do sensor de solo VCC*/
pinMode(A1, INPUT);  /*Saida de dados do sensor de solo*/

/* Inciando hardwares -------------------------- */


/* Iniciando teste do LCD */
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                // initialize the lcd
  lcd.backlight();           // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("PLANTA FELIZ 3.0");// Print a message to the LCD
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("MEDINDO HUMIDADE");// Print a message to the LCD
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("INICIANDO...    ");// Print a message to the LCD
  delay(1000);
/*-----------------------*/

/*Iniciamos o monitor serial*/
Serial.begin(9600);  

}

void loop() {
/* -------------------------------------------- */

  lcd.setCursor(0, 0);
  lcd.print("   PLANTA 3.0   ");
  digitalWrite(A0, HIGH);  
  moisture = analogRead(A1);

  if(moisture<10){
      // 10
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      regarSi++;
      Serial.println("10");
  }else if(moisture<15){
      // 15
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      Serial.println("15");
  }else if(moisture<20){
      // 20
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      Serial.println("20");
  }else if(moisture<25){
      // 25
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      Serial.println("25");
  }else if(moisture>30){
      // 30
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      Serial.println("30");
  }else if(moisture>35){
      // 35
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      hearthL(7,1);
      Serial.println("35");
  }else if(moisture>40){
      // 40
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      hearthL(7,1);
      hearthR(8,1);
      Serial.println("40");
  }else if(moisture>45){
      // 45
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      hearthL(7,1);
      hearthR(8,1);
      hearthL(9,1);
      Serial.println("45");
  }else if(moisture>50){
      // 50
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      hearthL(7,1);
      hearthR(8,1);
      hearthL(9,1);
      hearthR(10,1);
      Serial.println("50");
  }else if(moisture>55){
      // 55
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      hearthL(7,1);
      hearthR(8,1);
      hearthL(9,1);
      hearthR(10,1);
      hearthL(11,1);
      Serial.println("55");
  }else if(moisture>60){
      // 60
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      hearthL(7,1);
      hearthR(8,1);
      hearthL(9,1);
      hearthR(10,1);
      hearthL(11,1);
      hearthR(12,1);
      Serial.println("60");
  }else if(moisture>65){
      // 65
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      hearthL(7,1);
      hearthR(8,1);
      hearthL(9,1);
      hearthR(10,1);
      hearthL(11,1);
      hearthR(12,1);
      hearthL(13,1);
      Serial.println("65");
  }else if(moisture>70){
      // 70
      lcd.print("                ");// Clean LCD
      hearthL(1,1);
      hearthR(2,1);
      hearthL(3,1);
      hearthR(4,1);
      hearthL(5,1);
      hearthR(6,1);
      hearthL(7,1);
      hearthR(8,1);
      hearthL(9,1);
      hearthR(10,1);
      hearthL(11,1);
      hearthR(12,1);
      hearthL(13,1);
      hearthR(14,1);
      Serial.println("70");
  }

  Serial.println(regarSi);

  // Alarme para regar de los cojones
  if(regarSi>=100){
    buzzerRegar();
    Serial.println("ATIVANDO BUZZER REGAR");
    delay(4500);
    if(regarSi>101){
      regarSi=0;
    }
  }
  digitalWrite(A0, LOW);  
  delay(45000);
/* -------------------------------------------- */
}


/* Funções para ser chamadas ------------------ */
/* Função de teste do LCD */
bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}
/* -------------------------------------------- */



/* -------------------------------------------- */
int hearthL(int pos,int lin){
  lcd.setCursor(0, lin);
  lcd.createChar(0, leftHeart);
  lcd.setCursor(pos, lin);
  lcd.write(byte(0));
  delay(10);
}
int hearthR(int pos,int lin){
  lcd.setCursor(0, lin);
  lcd.createChar(1, rightHearth);
  lcd.setCursor(pos, lin);
  lcd.write(byte(1));
  delay(10);
}
/* -------------------------------------------- */



/* Avisos sonoros ----------------------------- */
int buzzerRegar(){
      noTone(7);
      tone(7, 523, 600); 
      delay(600);
      noTone(7);
      tone(7, 587, 600); 
      delay(600);
      noTone(7);  
      tone(7, 659, 600); 
      delay(600);
      delay(100);
}
int buzzerPerigo(){
      noTone(7);
      tone(7, 880, 200); 
      delay(300);
      delay(100);
}
/* -------------------------------------------- */
