#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  
#include <ACS712.h>

#define DEBUG 0

#define pinRELE 8
#define pinBtnStart 9
#define pinBtnStop 2
#define pinSensorCurrent A7
#define pinPosCurrent A1

LiquidCrystal_I2C lcd(0x27,16,2); 

ACS712 sensor(ACS712_30A, A0);





float varCurrent = 20.0f;
int varExposition = 10;
int _exposition;
float _current;
unsigned long _exposition_last_time;
volatile boolean work = false;
byte pBar[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void Stop_Becking(){
  digitalWrite(pinRELE,false);
  work = false;
  if(DEBUG){
  Serial.println("interrapt");
  }
}

void disUpdate(){
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EXP:");
  lcd.print(varExposition);
  lcd.print("s "); 
  lcd.setCursor(10, 0); 
  lcd.print("A:");   
  lcd.print(varCurrent);
 // delay(500);
}
void startScreen(){
  lcd.setCursor(0, 0);
  lcd.print(" Backing device ");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  by MACKELLY");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("   22/11/2020");
  delay(2000);
  lcd.clear();
  //disUpdate();
}
void Beking() {
  if(DEBUG){
    Serial.println("Start becking..");
    Serial.println("rele ON");
  }

work = true;
digitalWrite(pinRELE,true);
_exposition_last_time = millis();
_exposition = varExposition;

while(_exposition != 0 && work == true){
  
  if((millis() - _exposition_last_time) >= 1000) {
    _current = sensor.getCurrentDC();
    _exposition--;
    _exposition_last_time = millis();
    int _temp= map(_exposition,0,varExposition,17,0);
    
    for (int i = 0; i < _temp; i++)
    {
      
      lcd.setCursor(i, 1);
      lcd.write(byte(0));

    }
    lcd.setCursor(4, 0);
    lcd.print(_exposition);
    lcd.print("s"); 
    lcd.setCursor(12, 0);
    lcd.print(_current);
    if(varCurrent <= _current){
      digitalWrite(pinRELE,false);
      work = false;
      lcd.setCursor(0, 1);
      lcd.print("Cut-off current ");
      if(DEBUG){
      Serial.print("Cut-off current:");
      Serial.println(_current);
      }
      delay(500);
      break;      
    }
  }
}
if(DEBUG){
  Serial.println("becking DONE!");
  Serial.println("rele OFF");
}
digitalWrite(pinRELE,false);
delay(1000);
lcd.setCursor(0, 1);
lcd.clear();
}

void setup() {
  
  Serial.begin(9600);
  lcd.init();                     
  lcd.backlight();
  lcd.createChar(0, pBar);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(11,true);
  digitalWrite(12,false);
  pinMode(pinSensorCurrent,INPUT);
  pinMode(pinBtnStart,INPUT_PULLUP);
  pinMode(pinBtnStop,INPUT_PULLUP);
  pinMode(pinPosCurrent,INPUT);
  pinMode(pinRELE,OUTPUT);
  digitalWrite(pinRELE,false);
  attachInterrupt(0,Stop_Becking,FALLING);
  startScreen();
  
}

void loop() {

varExposition = map(analogRead(pinSensorCurrent),0,1023,0,60);
varCurrent = map(analogRead(pinPosCurrent),0,1000,0,20);
if(!digitalRead(pinBtnStart) && varExposition!=0)Beking();

disUpdate();


}

