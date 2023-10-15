////////////////////////////////////////////////////////
// ARDUINO INTERVALOMETRO //////////////////////////////
////////////////////////////////////////////////////////
/*
Estamos usando arduino para disparar uma Canon 250D con
un cable tipo P2 de audio con adaptador para Mini P2 que
es la entrada de disparadores de Canon.

Estamos usando un LCD tipo I2C para exhibir las informaciones.

Tenemos un menu inicial para iniciar las tomas de fotos, pero
donde no se puede iniciar nada si no configuramos los otros menus.

Tenemos un menu para configurar los segundos de exposición de cada
foto, con un intervalo automatico de 4 segundos para que la 
cámara pueda guardar el archivo antes de que se tome la próxima foto.

Tenemos un menu para configurar la cantidad de fotos que queremos tomar
en cada start, y un contador que suma la cantidad y para cuando se llega
al maximo.

Cuando se acaba vuelve al menu inicial, y podemos ir hasta el menu de cantidad
de fotos, incrementar más fotos, y volver a iniciar en el menu home para
que se llegue a su nuevo numero.

Ej: 

1 config : 10 tomas (cuando llega a 10 para y volve al home)
2 volvemos al menu de tomas, donde tenemos ya el valor 10, agregamos mas 5 y ahora tenemos 15
3 volvemos al menu de home, y hacemos start.
4 volve a tomar las fotos hasta que llegue ahora en 15 o sea saca más 5 fotos.
5 para el contador y vuelve al home.

La idea es mejorar esto y hacer una integración con una montaje Barn Door que tenemos, movimentando un
motor de paso para acompañar el movimiento del cielo y hacer astrofotografias.
*/


////////////////////////////////////////////////////////



//////////////////////////////////////////////////////// INCLUDE LIBS

#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

//////////////////////////////////////////////////////// DECALRE VARS
int posMenu = 0;

float obturador = 0;
int delayObturador = 5;
int fotosTotal = 0;
int obturadorDelay = 0;
int fotosTomadas = 0;

int startStop = 0; // activa desactiva en el menu 1 todo


//////////////////////////////////////////////////////// START SETUP
void setup() {
Serial.begin(9600);
if (!i2CAddrTest(0x27)) {
lcd = LiquidCrystal_I2C(0x3F, 16, 2);
}

pinMode(A0, INPUT_PULLUP);
pinMode(A1, INPUT_PULLUP);
pinMode(A2, INPUT_PULLUP);
pinMode(7, OUTPUT);
pinMode(6, OUTPUT);

pinMode(A3, INPUT);

lcd.init();  
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("Intervalometer  ");
delay(500); // La camara va sacar una foto inicial, borrar después
lcd.clear();

digitalWrite(7, LOW);
digitalWrite(6, HIGH);

}
//////////////////////////////////////////////////////// END SETUP


//////////////////////////////////////////////////////// START LOOP 
void loop() {
 
  switch (posMenu) {
  case 0:
      StartStop();
    break;
  case 1:
      ConfigObturador();
    break;
  case 2:
      ConfigFotos();
    break;
  case 3:
      lcd.setCursor(0, 0); 
      lcd.print("Fotos QTD"); 
    break;    
  default:
    // statements
    break;
  }
  
  delay(1000);
    
  if (digitalRead(A0) == LOW) {
    posMenu += 1;
  }
  if (posMenu == 3) {
    posMenu = 0;
  }

}
//////////////////////////////////////////////////////// END LOOP


////////////////////////////////////////////////////////
void StartStop(){
////////////////////////
  lcd.setCursor(0, 0); 
  lcd.print("Arduinter Home      "); 

////////////////////////  
  if (digitalRead(A2) == LOW) {
    startStop = 1;
    TakeFotos();
    lcd.setCursor(6, 0); 
    lcd.print("Arduinter   Take");  
  }
////////////////////////  
  if (digitalRead(A1) == LOW) {
    startStop = 0;
    lcd.setCursor(6, 0); 
    lcd.print("Arduinter   Stop");    
  }
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
void ConfigObturador(){
////////////////////////
  lcd.setCursor(0, 0); 
  lcd.print("Obturador Timer "); 
////////////////////////  
  if (digitalRead(A2) == LOW) {
    obturador += 0.5;
  }
////////////////////////  
  if (digitalRead(A1) == LOW) {
    obturador -= 0.5;
  }

  obturadorDelay = obturador * 1000 + 1000;

  lcd.setCursor(0, 1); 
  lcd.print(obturador);  
//////////////////////// 
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
void ConfigFotos(){
////////////////////////
  lcd.setCursor(0, 0); 
  lcd.print("Fotos Cuantidad "); 
////////////////////////  
  if (digitalRead(A2) == LOW) {
    fotosTotal += 1;
  }
////////////////////////  
  if (digitalRead(A1) == LOW) {
    fotosTotal -= 1;
  }

  lcd.setCursor(6, 1); 
  lcd.print(fotosTotal);   
//////////////////////// 
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
void TakeFotos(){
////////////////////////
  //Tomamos fotos con los parametros 
  //Hasta que se cumpla
  if (fotosTomadas != fotosTotal){
    while(fotosTomadas < fotosTotal){
      digitalWrite(6, LOW); // Abre BULB foto
      lcd.setCursor(0, 0);
      lcd.print("Sacando Fotos   "); 
      delay(obturadorDelay);
      digitalWrite(6, HIGH); // Cierra BULB foto

      lcd.setCursor(0, 0);
      lcd.print("Guardando Fotos "); 
      digitalWrite(7, HIGH);        
      delay(4000);
      digitalWrite(7, LOW);
      
      fotosTomadas++;
    
      lcd.setCursor(13, 1); 
      lcd.print(fotosTomadas);
    }
      if(fotosTomadas == fotosTotal){ // Paramos todo y volvemos valores a cero
        startStop = 0;
        //fotosTomadas = 0;
        //fotosTotal = 0;
        //obturador = 0;
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Arduinter   Stop"); 
        lcd.setCursor(0, 1); 
        lcd.print(obturador);         
        lcd.setCursor(6, 1); 
        lcd.print(fotosTotal);
        lcd.setCursor(13, 1); 
        lcd.print(fotosTomadas);                        
      }
  }
     
//////////////////////// 
}
////////////////////////////////////////////////////////



////////////////////////////////////////////////////////
// I2C Address TEST 
bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}
////////////////////////////////////////////////////////
