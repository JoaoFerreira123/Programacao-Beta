//Versão de teste do código braço robótico BETA
//Código para ser aplicado no teste em protoboard - Com menos motores
//17/07/2022

#include <Arduino.h>
#include <ESP32Servo.h>

static const int Pservo1 = 18;
static const int Pservo2 = 19;

static const int pot1 = 25;
static const int pot2 = 26;

Servo servo1, servo2;

void setup() {
  Serial.begin(9600);
  servo1.attach(Pservo1);
  servo2.attach(Pservo2);

  pinMode(34, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int posServo1 = map(analogRead(pot1), 0, 4096, 0, 180);
  int posServo2 = map(analogRead(pot2), 0, 4096, 0, 180);

  servo1.write(posServo1);
  delay(20);
  servo2.write(posServo2);
  delay(20);

  int buttom = 0;
  buttom = digitalRead(34);

  if (buttom == 1){
    digitalWrite(13, 1);
  }else{
    digitalWrite(13, 0);
  }
}