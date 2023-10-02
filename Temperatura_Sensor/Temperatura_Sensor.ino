const int Pin_del_Sensor=A0;
const float Temperatura_de_Referencia=20.0;

void setup() {
  //LEDS
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
    
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int NumeroPin=2; NumeroPin<5; NumeroPin++){
    pinMode(NumeroPin,OUTPUT);
    digitalWrite(NumeroPin,LOW);
  }
}

void loop() {
  
  int Valor_del_Sensor=analogRead(Pin_del_Sensor);
  
  //Printa valor de sensor
  Serial.print("Valor del Sensor: ");
  Serial.println(Valor_del_Sensor);
  
  //Printa Tensão 
  float Tension=(Valor_del_Sensor/1024.0)*5.0;
  Serial.print("Voltios: ");
  Serial.println(Tension);
  
  //Printa Temperatura 
  float Temperatura=(Tension - 0.5)*100;
  Serial.print("Grados: ");
  Serial.println(Temperatura);
  Serial.println();
  
  //Verifica temperatura e acende a luz correspondente.
  delay(400);  
  if (Temperatura>17.50){
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }else{
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  delay(400);  
  if (Temperatura>19.00){
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }else{
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  delay(400);   
  if (Temperatura>22.00){
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
  }else{
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  delay(400);
  
}
