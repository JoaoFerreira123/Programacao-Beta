#include <Arduino.h>
#include <Servo.h>

static const int s = 7;

Servo servo;

void setup() {
  Serial.begin(115200);
  servo.attach(s);
}

void loop() {
  while (Serial.available() > 0)
  {
    String valor = Serial.readStringUntil('/');
    Serial.flush();
    uint8_t pos = valor.toInt();
    servo.write(pos);
  }
  
}