// Código V1 do Braço Robótico Beta
// Código para a VERSÃO MÍNIMA FUNCIONAL
// Início: 26/07/2022
// Final: XX/07/2022

#include <Arduino.h>
#include <ESP32Servo.h>

//Pinos dos servos motores
static const int servoBaseGir = 33;
static const int servosBracoA = 32;
static const int servoBracoB = 23;
static const int servoBracoC = 19;
static const int servoConectorGarra = 18;
static const int servoGarra = 5;

//Potenciômetros de cada servo motor e de controle
static const int pot_servoBaseGir = 26;
static const int pot_servosBracoA = 27;
static const int pot_servoBracoB = 14;
static const int pot_servoBracoC = 2;
static const int pot_servoConectorGarra = 4;
static const int pot_servoGarra = 15;
static const int pot_controle = 25;

//Botões
static const int bot1 = 34;
static const int bot2 = 35;

//Leds
static const int leds = 13;

//Criação dos servos 
Servo baseGir, bracoA, bracoB, bracoC, conectorGarra, garra;


void setup() {
  Serial.begin(9600);
  baseGir.attach(servoBaseGir);
  bracoA.attach(servosBracoA);
  bracoB.attach(servoBracoB);
  bracoC.attach(servoBracoC);
  conectorGarra.attach(servoConectorGarra);
  garra.attach(servoGarra);

  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);
  pinMode(leds, OUTPUT);
}

void loop() {
  


}