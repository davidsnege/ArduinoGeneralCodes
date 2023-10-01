// Importanto Bibliotecas
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
// Declarando Variaveis
int moisture = 0;
int menu = 0;
// inicializando o LCD
Adafruit_LiquidCrystal lcd_1(0);
// Inicializando o Servo
Servo servo_9;
// Iniciando indicadores LED
const int LED4=11;
const int LED3=10;
const int LED2=9;
const int LED1=8;


void setup()
{
  // Iniciando BUZ
  pinMode(7, OUTPUT);
  //LEDS Indicadores
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  // Buttons de Menu
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  // Servo de abertura de agua  
  servo_9.attach(9, 500, 2500);
  // Iniciando o LCD I2C
  lcd_1.begin(16, 2);
  // Sensor de humidade do solo
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  // Iniciamos o Monitor Serial
  Serial.begin(9600);
}

void loop()
{
  // Lemos o valor dos botoes
  int sensorValBt1 = digitalRead(2);
  int sensorValBt2 = digitalRead(3);
  int menuStatus;
  int callFunction;
  // Controlamos a posicao do menu
  if(sensorValBt1 == HIGH){
    menuStatus += 1;
  }
  if(sensorValBt2 == HIGH){
    menuStatus -= 1;
  }
  if(menuStatus > 4 || menuStatus < 0){
    menuStatus = 0;
  }
   
  switch (menuStatus) {
  case 0:
    // statements
    callFunction = terra();
    break;
  case 1:
    // statements
    callFunction = temperatura();
    break;
  case 2:
    // statements
    callFunction = humidade();
    break;
  case 3:
    // statements
    callFunction = pressao();
    break;
  case 4:
    // statements
    callFunction = lux();
    break;
  default:
    // statements
    break;
  }
   delay(50); 
}

//----FUNCOES------------------------------------------
//-----------------------------------------------------
//----Condicoes da terra----
int terra(){
  // Setamos o cursor na primeira linha para o titulo
  lcd_1.setCursor(0, 0);
  lcd_1.print("Estado Tierra");
  // Lemos o sensor
  digitalWrite(A0, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  moisture = analogRead(A1) / 100 * 1024 / 100;
  // Desligamos o sensor para diminuir a corrosao
  digitalWrite(A0, LOW);
  // condicoes da terra segundo o sensor
    if (moisture < 20) {
      //----LCD-----  
      lcd_1.setCursor(0, 1);
      lcd_1.print("Insuficiente    ");
      digitalWrite(LED1,HIGH);
      delay(100);
      digitalWrite(LED1,LOW);
	  buzzerRegar();
      //servo_9.write(90);
      //----LCD-----
    }else{ 
    if (moisture < 40) {
        //----LCD-----  
        lcd_1.setCursor(0, 1);
        lcd_1.print("Baixo           ");
        digitalWrite(LED2,HIGH);
      	delay(100);
      	digitalWrite(LED2,LOW);
        //servo_9.write(90);
        //----LCD-----
    }else{
    if (moisture < 60) {
          //----LCD-----  
          lcd_1.setCursor(0, 1);
          lcd_1.print("Bom             ");
          digitalWrite(LED3,HIGH);
      	  delay(100);
      	  digitalWrite(LED3,LOW);
          //servo_9.write(0);
          //----LCD-----
    }else{ 
    if (moisture < 80) {
              //----LCD-----  
              lcd_1.setCursor(0, 1);
              lcd_1.print("Excelente       ");
              digitalWrite(LED4,HIGH);
      	      delay(100);
      	      digitalWrite(LED4,LOW);
              //servo_9.write(0);
              //----LCD-----
    }else{ 
    if (moisture > 80) {
                //----LCD-----  
                lcd_1.setCursor(0, 1);
                lcd_1.print("Encharcado      ");
      			buzzerExcesso();
                //servo_9.write(0);
                //----LCD-----
    }}}}}
    //----LCD-----
    lcd_1.setCursor(13, 1);
    lcd_1.print(moisture);
  	lcd_1.setCursor(15, 1);
    lcd_1.print("%");
    lcd_1.setBacklight(1);
  	//----LCD-----  
  //int result;
  //return result;
}
//-----------------------------------------------------
//----Temperatura----
int temperatura(){
  //lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Temperatura     ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("----------------");
  lcd_1.setBacklight(1);
  //int result;
  //return result;
}
//-----------------------------------------------------
//----Humidade do Ar----
int humidade(){
  //lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Humidade        "); 
  lcd_1.setCursor(0, 1);
  lcd_1.print("----------------");
  lcd_1.setBacklight(1);
  //int result;
  //return result;
}
//-----------------------------------------------------
//----Pressao Barometrica----
int pressao(){
  //lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Pressao Bar     ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("----------------");
  lcd_1.setBacklight(1);
  //int result;
  //return result;
}
//-----------------------------------------------------
//----Iluminacao ambiente----
int lux(){
  //lcd_1.clear();
  int lux = analogRead(A2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Luz Ambiente    ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Actual:     ");
  lcd_1.print(lux);
  lcd_1.setBacklight(1);
  //int result;
  //return result;
}
//-----------------------------------------------------
//----Buzzer de aviso----
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
    //int result;
   //return result;
}
int buzzerExcesso(){
      noTone(7);
      tone(7, 880, 200); 
      delay(300);
      delay(100);
    //int result;
   //return result;
}