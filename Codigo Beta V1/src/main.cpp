// Código V1 do Braço Robótico Beta
// Código para a VERSÃO MÍNIMA FUNCIONAL
// Início: 26/07/2022
// Final: XX/07/2022

#include <Arduino.h>
#include <ESP32Servo.h>

// Os arquivos headers estão na pasta INCLUDE
#include <constantes.h>
#include <funcoes.h>


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
  int pos_Controle = map(analogRead(pot_controle), 0, 4096, 0, 180);
  

  //Atuação dos servos
  //Futuramente, para a movimentação, ver como faz para ela ser mais suave!
  baseGir.write(pos_BasGir);
  delay(20);
  bracoA.write(pos_BracoA);
  delay(20);
  bracoB.write(pos_BracoB);
  delay(20);
  bracoC.write(pos_BracoC);
  delay(20);
  conectorGarra.write(pos_ConectorGarra);
  delay(20);
  garra.write(pos_Garra);
  delay(20);

  //Deixa os leds no modo padrão
  ledsPadrao();


}