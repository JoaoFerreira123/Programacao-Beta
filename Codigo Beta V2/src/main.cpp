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
static const int servoBaseGir = 18;
static const int servosBracoA = 22;
static const int servoBracoB = 23;
static const int servoBracoC = 21;
static const int servoConectorGarra = 5;
static const int servoGarra = 15;

#define canalLED 10
#define freq 5000
#define resoluc 8


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


  //Leds
  ledcSetup(canalLED, freq, resoluc);
  ledcAttachPin(32, canalLED); //pin4


}

void loop() {
  

  while (Serial.available() > 0){
    //só vai ler se tiver /, ou seja, só quando tiver um numero -> não lê o tempo todo
    String leitura = Serial.readStringUntil('/');
    Serial.flush();
    
    
    // a variavel pos (leitura serial) vai ter um codigo identificando o motor e a posição do motor
    //ex: a45 -> motor A na posição 45º



   char motor = leitura[0];

   switch (motor){
    case 'R':{ //Base giratória
      leitura.remove(0,1); //a partir do indice 0, remove 1 caractere
      uint8_t pos_BasGir = leitura.toInt();
      baseGir.write(pos_BasGir);
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

  //Comportamento dos LEDS
  for(int i=0; i<255; i+=5){
    ledcWrite(canalLED, i);
    delay(20);
  }
  
  for(int j=255; j>0; j-=5){
    ledcWrite(canalLED, j);
    delay(20);
  }


}