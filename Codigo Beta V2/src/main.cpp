// Código V2 do Braço Robótico Beta
// Código para CONTROLE BÁSICO USANDO GUI PYTHON
// Início: 08/10/2022
// Final: XX/XX/2022

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
  Serial.begin(115200);
  baseGir.attach(servoBaseGir);
  bracoA.attach(servosBracoA);
  bracoB.attach(servoBracoB);
  bracoC.attach(servoBracoC);
  conectorGarra.attach(servoConectorGarra);
  garra.attach(servoGarra);

  pinMode(2, OUTPUT);
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);

  ledcSetup(canalLed, freqPWMLed, resoluc);
  ledcAttachPin(leds, canalLed);

}

void loop() {

  if (Serial.available() > 0){
    //só vai ler se tiver /, ou seja, só quando tiver um numero -> não lê o tempo todo
    String leitura = Serial.readStringUntil('/');
    Serial.flush();
    
    
    // a variavel pos (leitura serial) vai ter um codigo identificando o motor e a posição do motor
    //ex: a45 -> motor A na posição 45º



   char motor = leitura[0];

//NÃO SEI -> NÃO FUNCIONA. ELE ENTRA NO CASE, O LED ACENDE, O MOTOR MEXE PARA 100º
//MAS DEPOIS NÃO MEXE MAIS. O SERVO FICA COM AQUELE BIPE, PARECE QUE TENTANDO MEXER MAS NÃO CONSEGUE
//USEI 1 SERVO E A FONTE DE 10A, COM REGULADOR DE 3A. NÃO DEVE SER PROBLEMA ELETRONICO
   switch (motor){
    case 'R':{ //Base giratória
      leitura.remove(0,1); //a partir do indice 0, remove 1 caractere
      int pos_BasGir = leitura.toInt();
      baseGir.write(100);
      baseGir.write(pos_BasGir);
      delay(20); 
      digitalWrite(2, 1);
      Serial.flush();
      break;
    }
    case 'A':{ //Braço A
      leitura.remove(0,1);
      uint8_t pos_BracoA = leitura.toInt();
      bracoA.write(pos_BracoA);
      break;
    }
    case 'B':{ //Braço B
      leitura.remove(0,1);
      uint8_t pos_BracoB = leitura.toInt();
      bracoB.write(pos_BracoB);
      break;
    }
    case 'C':{ //Braço C
      leitura.remove(0,1);
      uint8_t pos_BracoC = leitura.toInt();
      bracoC.write(pos_BracoC);
      break;
    }
    case 'T':{ //Conector Garra
      leitura.remove(0,1);
      uint8_t pos_ConectorGarra = leitura.toInt();
      conectorGarra.write(pos_ConectorGarra);
      break;
    }
    case 'G':{ //Garra
      leitura.remove(0,1);
      uint8_t pos_Garra = leitura.toInt();
      garra.write(pos_Garra);
      break;
    }
   }

 }



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