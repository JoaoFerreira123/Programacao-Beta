#include <Arduino.h>
#include <constantes.h>



void ledsPadrao(){
  
  int intensidade = 10;

  for(int i = 0; i < 255; i+= intensidade){
    ledcWrite(canalLed, i);
    delay(20);
  }

  for(int j = 0; j > 0; j-= intensidade){
    ledcWrite(canalLed, j);
    delay(20);
  }

}