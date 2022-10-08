// Código V1 do Braço Robótico Beta
// Código para a VERSÃO MÍNIMA FUNCIONAL - Potenciômetros controlando os motores
// Início: 26/07/2022
// Final: XX/07/2022

#include <Arduino.h>
#include <ESP32Servo.h>

// Os arquivos headers estão na pasta INCLUDE
//#include <constantes.h>
//#include <funcoes.h>

//DEU BUG COM AS CTES SEPARADAS
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
static const int canalLed = 0;
static const int freqPWMLed = 12000;
static const int resoluc = 8;


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

  ledcSetup(canalLed, freqPWMLed, resoluc);
  ledcAttachPin(leds, canalLed);

}

void loop() {
  //Posições dos servos a partir da leitura dos potenciômetros
  int pos_BasGir = map(analogRead(pot_servoBaseGir), 0, 4096, 0, 180);
  int pos_BracoA = map(analogRead(pot_servosBracoA), 0, 4096, 0, 180);
  int pos_BracoB = map(analogRead(pot_servoBracoB), 0, 4096, 0, 180);
  int pos_BracoC = map(analogRead(pot_servoBracoC), 0, 4096, 0, 180);
  int pos_ConectorGarra = map(analogRead(pot_servoConectorGarra), 0, 4096, 0, 180);
  int pos_Garra = map(analogRead(pot_servoGarra), 0, 4096, 0, 180);

  //Posição do potenciômetro de controle do sistema (display)
  //int pos_Controle = map(analogRead(pot_controle), 0, 4096, 0, 180);
  

  //Atuação dos servos
  //Futuramente, para a movimentação, ver como faz para ela ser mais suave!
  baseGir.write(pos_BasGir);
  bracoA.write(pos_BracoA);
  bracoB.write(pos_BracoB);
  bracoC.write(pos_BracoC);
  conectorGarra.write(pos_ConectorGarra);
  garra.write(pos_Garra);
  delay(20);

  //Deixa os leds no modo padrão
  int intensidade = 5;

  for(int i = 0; i < 255; i+= intensidade){
    ledcWrite(canalLed, i);
    delay(20);
  }

  for(int j = 0; j > 0; j-= intensidade){
    ledcWrite(canalLed, j);
    delay(20);
  }



}