
/* importando as bibliotecas que precisamos ----- */

#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

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
  lcd.print("Planta Feliz 1.0");// Print a message to the LCD
  delay(1000);
/*-----------------------*/

/*Iniciamos o monitor serial*/
Serial.begin(9600);  

}

void loop() {
/* -------------------------------------------- */

  lcd.setCursor(0, 0);
  lcd.print("Estado Tierra   ");
  digitalWrite(A0, HIGH);  
  moisture = analogRead(A1);
  lcd.setCursor(0, 1);
  lcd.print("Humidade   ");
  Serial.println(moisture);

  if(moisture<5){
      lcd.setCursor(0, 1);
      lcd.print("Humidade    ");
      delay(2500);
      lcd.setCursor(0, 1);
      lcd.print("Perigo =(   ");
      lcd.setCursor(13, 1);
      lcd.print(moisture);
      lcd.setCursor(15, 1);
      lcd.print("%");
      buzzerRegar(); 
      delay(1000);
  }else if(moisture<15){
      lcd.setCursor(0, 1);
      lcd.print("Humidade   ");
      delay(2500);
      lcd.setCursor(0, 1);
      lcd.print("Baixo :(   ");
      lcd.setCursor(13, 1);
      lcd.print(moisture);
      lcd.setCursor(15, 1);
      lcd.print("%");
      buzzerRegar();
      delay(1000);
  }else if(moisture>20){
      lcd.setCursor(0, 1);
      lcd.print("Humidade   ");
      delay(2500);
      lcd.setCursor(0, 1);
      lcd.print("Boa =)     ");
      lcd.setCursor(13, 1);
      lcd.print(moisture);
      lcd.setCursor(15, 1);
      lcd.print("%");
  }else if(moisture>25){
      lcd.setCursor(0, 1);
      lcd.print("Humidade   ");
      delay(2500);
      lcd.setCursor(0, 1);
      lcd.print("Excelente ;)");
      lcd.setCursor(13, 1);
      lcd.print(moisture);
      lcd.setCursor(15, 1);
      lcd.print("%");
  }else if(moisture>40){
      lcd.setCursor(0, 1);
      lcd.print("Humidade   ");
      delay(2500);
      lcd.setCursor(0, 1);
      lcd.print("Muita XP   ");
      lcd.setCursor(13, 1);
      lcd.print(moisture);
      lcd.setCursor(15, 1);
      lcd.print("%");
  }

  digitalWrite(A0, LOW);  

  /*40 >= Muita agua */
  /*25 >= Excelente  */
  /*20 >= Bom        */
  /*15 <= Baixo      */
  /* 4 <= Perigo     */

/* -------------------------------------------- */
delay(460);
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
