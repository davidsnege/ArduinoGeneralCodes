//Programa SERVO1
//Programar posiciones en un Micro Servo Tower Pro SG90 9G.Z
// Incluir la librería Servo
#include <Servo.h>
Servo servo1; // Declaramos la variable para controlar el servo
int pinServo = 11; // Pin digital con PWM para el Servo
int pulsoMin = 650; // Pulso en us para girar un ángulo de 0º
int pulsoMax = 2550; // Pulso en us para girar un ángulo de 180º
int angulo = 0; // Variable para guardar el ángulo del servo
void setup()
{
// Señal del Servo1 conectado al pin digital 9 (PWM)--> pinServo
// Calibración del servo para suavizar movimientos -->(pulsoMin, pulsoMax)
// servo1.attach(pinServo, pulsoMin, pulsoMax);
}
void loop()
{
// El Servo avanza de 0º a 180º
for(angulo = 0; angulo <= 180; angulo++)
{
// Avanza 1 grado cada 10 ms
servo1.write(angulo);
delay(10);
}
// El Servo retrocede de 180º a 0º
for(angulo = 180; angulo >= 0; angulo--)
{
// Retrocede 1 grado cada 10 ms
servo1.write(angulo);
delay(10);
}
}
