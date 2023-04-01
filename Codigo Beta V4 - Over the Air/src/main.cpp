// Código V4 do Braço Robótico Beta
// Código para CONTROLE via WIFI, tanto upload de Código quanto Web server para controle
// Início: 01/04/2023
// Final: XX/XX/2023

#include <Arduino.h>
#include <ESP32Servo.h>

//Pinos dos servos motores
static const int servoBaseGir = 18;
static const int servosBracoA = 22;
static const int servoBracoB = 23;
static const int servoBracoC = 15;
static const int servoConectorGarra = 21;
static const int servoGarra = 5;

//Criação dos servos 
Servo baseGir, bracoA, bracoB, bracoC, conectorGarra, garra;

//Variaveis com as posiçoes ATUAL dos servos
uint8_t pos_BasGir, pos_BracoA, pos_BracoB, pos_BracoC, pos_ConectorGarra, pos_Garra;


//Variaveis com as posicoes ANTERIORES dos servos - já definindo a POS inicial de cada servo
uint8_t Ppos_BasGir = 90;
uint8_t Ppos_BracoA = 90;
uint8_t Ppos_BracoB = 90;
uint8_t Ppos_BracoC = 90;
uint8_t Ppos_ConectorGarra = 90; 
uint8_t Ppos_Garra = 0;

//Vetores para gravar as POSICOES de CADA SERVO
int posR[10];
int posA[10];
int posB[10];
int posC[10];
int posT[10];
int posG[10];

int nPos = 0;
int reset = 0;


//int posicoes[10][6]; //matriz para guardar 10 posições
void setup() {
  Serial.begin(115200);
  baseGir.attach(servoBaseGir);
  bracoA.attach(servosBracoA);
  bracoB.attach(servoBracoB);
  bracoC.attach(servoBracoC);
  conectorGarra.attach(servoConectorGarra);
  garra.attach(servoGarra);


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
      pos_BasGir = leitura.toInt();

      if(Ppos_BasGir > pos_BasGir){
        for(int i=Ppos_BasGir; i>= pos_BasGir; i--){
          baseGir.write(i);
          delay(10);
        }
      }
      if(Ppos_BasGir < pos_BasGir){
        for(int i=Ppos_BasGir; i<=pos_BasGir; i++){
          baseGir.write(i);
          delay(10);
        }
      }
      Ppos_BasGir = pos_BasGir;
      
      break;
    }
    case 'A':{ //Braço A
      leitura.remove(0,1);
      pos_BracoA = leitura.toInt();
      if(Ppos_BracoA > pos_BracoA){
        for(int i=Ppos_BracoA; i>= pos_BracoA; i--){
          bracoA.write(i);
          delay(10);
        }
      }
      if(Ppos_BracoA < pos_BracoA){
        for(int i=Ppos_BracoA; i<=pos_BracoA; i++){
          bracoA.write(i);
          delay(10);
        }
      }
      Ppos_BracoA = pos_BracoA;
      
      break;
    }
    case 'B':{ //Braço B
      leitura.remove(0,1);
      pos_BracoB = leitura.toInt();
      if(Ppos_BracoB > pos_BracoB){
        for(int i=Ppos_BracoB; i>= pos_BracoB; i--){
          bracoB.write(i);
          delay(10);
        }
      }
      if(Ppos_BracoB < pos_BracoB){
        for(int i=Ppos_BracoB; i<=pos_BracoB; i++){
          bracoB.write(i);
          delay(10);
        }
      }
      Ppos_BracoB = pos_BracoB;

      break;
    }
    case 'C':{ //Braço C
      leitura.remove(0,1);
      pos_BracoC = leitura.toInt();
      if(Ppos_BracoC > pos_BracoC){
        for(int i=Ppos_BracoC; i>= pos_BracoC; i--){
          bracoC.write(i);
          delay(10);
        }
      }
      if(Ppos_BracoC < pos_BracoC){
        for(int i=Ppos_BracoC; i<=pos_BracoC; i++){
          bracoC.write(i);
          delay(10);
        }
      }
      Ppos_BracoC = pos_BracoC;
      break;
    }
    case 'T':{ //Conector Garra
      leitura.remove(0,1);
      pos_ConectorGarra = leitura.toInt();
      if(Ppos_ConectorGarra > pos_ConectorGarra){
        for(int i=Ppos_ConectorGarra; i>= pos_ConectorGarra; i--){
          conectorGarra.write(i);
          delay(10);
        }
      }
      if(Ppos_ConectorGarra < pos_ConectorGarra){
        for(int i=Ppos_ConectorGarra; i<=pos_ConectorGarra; i++){
          conectorGarra.write(i);
          delay(10);
        }
      }
      Ppos_ConectorGarra = pos_ConectorGarra;
      break;
    }
    case 'G':{ //Garra
      leitura.remove(0,1);
      pos_Garra = leitura.toInt();
       if(Ppos_Garra > pos_Garra){
        for(int i=Ppos_Garra; i>= pos_Garra; i--){
          garra.write(i);
          delay(10);
        }
      }
      if(Ppos_Garra < pos_Garra){
        for(int i=Ppos_Garra; i<=pos_Garra; i++){
          garra.write(i);
          delay(10);
        }
      }
      Ppos_Garra = pos_Garra;
      
      break;
    }

    case 'S':{ //Flag salvar nova posição
      //leitura.remove(0,1); //remove o S, deixando somente o numero
      //nPos = leitura.toInt(); 
      posR[nPos] = Ppos_BasGir;
      posA[nPos] = Ppos_BracoA;
      posB[nPos] = Ppos_BracoB;
      posC[nPos] = Ppos_BracoC;
      posT[nPos] = Ppos_ConectorGarra;
      posG[nPos] = Ppos_Garra;

      nPos++;
      break;
    }
    case 'E':{ //Flag pra apagar as posicoes salvas
      memset(posR, 0, sizeof(posR));
      memset(posA, 0, sizeof(posA));
      memset(posB, 0, sizeof(posB));
      memset(posC, 0, sizeof(posC));
      memset(posT, 0, sizeof(posT));
      memset(posG, 0, sizeof(posG));
      nPos = 0;
      reset = 1;


    }

    case 'P':{ //Flag pra executar as posições
      while(reset != 1){
        for(int i=0; i<=nPos - 2; i++){
          //Base Giratoria
          if(posR[i] == posR[i+1]){
          }

          if(posR[i] > posR[i+1]){
            for(int j=posR[i]; j>=posR[i+1]; j--){
              baseGir.write(j);
              delay(20);
            }
          }
          if(posR[i] < posR[i+1]){
            for(int j=posR[i]; j<=posR[i+1]; j++){
              baseGir.write(j);
              delay(20);
            }
          }
        
          //Braco A
          if(posA[i] == posA[i+1]){
          }

          if(posA[i] > posA[i+1]){
            for(int j=posA[i]; j>=posA[i+1]; j--){
              bracoA.write(j);
              delay(20);
            }
          }
          if(posA[i] < posA[i+1]){
            for(int j=posA[i]; j<=posA[i+1]; j++){
              bracoA.write(j);
              delay(20);
            }
          }
          //Braco B
           if(posB[i] == posB[i+1]){
          }

          if(posB[i] > posB[i+1]){
            for(int j=posB[i]; j>=posB[i+1]; j--){
              bracoB.write(j);
              delay(20);
            }
          }
          if(posB[i] < posB[i+1]){
            for(int j=posB[i]; j<=posB[i+1]; j++){
              bracoB.write(j);
              delay(20);
            }
          }

          //Braco C
           if(posC[i] == posC[i+1]){
          }

          if(posC[i] > posC[i+1]){
            for(int j=posC[i]; j>=posC[i+1]; j--){
              bracoC.write(j);
              delay(20);
            }
          }
          if(posC[i] < posC[i+1]){
            for(int j=posC[i]; j<=posC[i+1]; j++){
              bracoC.write(j);
              delay(20);
            }
          }

          //Conector Garra
           if(posT[i] == posT[i+1]){
          }

          if(posT[i] > posT[i+1]){
            for(int j=posT[i]; j>=posT[i+1]; j--){
              conectorGarra.write(j);
              delay(20);
            }
          }
          if(posT[i] < posT[i+1]){
            for(int j=posT[i]; j<=posT[i+1]; j++){
              conectorGarra.write(j);
              delay(20);
            }
          }

          //GARRA
           if(posG[i] == posG[i+1]){
          }

          if(posG[i] > posG[i+1]){
            for(int j=posG[i]; j>=posG[i+1]; j--){
              garra.write(j);
              delay(20);
            }
          }
          if(posG[i] < posG[i+1]){
            for(int j=posG[i]; j<=posG[i+1]; j++){
              garra.write(j);
              delay(20);
            }
          }

        }

        break;
      }
        
      }
    }
   }
}
  

