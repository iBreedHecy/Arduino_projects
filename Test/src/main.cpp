#include <Arduino.h>

volatile bool enc_state = false;
volatile int napr = 4;
int test;
volatile unsigned long last_enc_rot;

void encoderFunc() {
  napr = digitalRead(4);
  if(millis() - last_enc_rot > 50 && napr != 3){
    enc_state = true;

    
    last_enc_rot = millis();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  attachInterrupt(1, encoderFunc,FALLING);

}

void loop() {
  if(enc_state == true){

    Serial.print("значение : ");
    if(napr == 0)test--;else test++;
    Serial.println(test);
    napr = 3;
    enc_state = false;

  }
}

