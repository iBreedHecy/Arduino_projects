#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN,! digitalRead(LED_BUILTIN));
  //delay(500);
  // put your main code here, to run repeatedly:
}