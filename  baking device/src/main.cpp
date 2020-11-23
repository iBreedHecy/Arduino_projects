#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  
#include <ACS712.h>

#define DEBUG 1

#define pinRELE 1
#define pinBtnStart 9
#define pinBtnStop 2
#define pinCurrent A7
#define pinSensorCurrent 1

LiquidCrystal_I2C lcd(0x27,16,2); 

ACS712 sensor(ACS712_30A, A0);





int varCurrent = 20;
int varExposition = 10;
int _current,_exposition;
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
  work = false;
  Serial.println("interrapt");
}

void disUpdate(){
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EXP:");
  lcd.print(varExposition);
  lcd.print("sec "); 
  lcd.setCursor(12, 0); 
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
    Serial.println("check A");
    Serial.println("rele ON");
  }
work = true;
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
    lcd.print("sec  "); 
    lcd.setCursor(14, 0);
    lcd.print(_current);
  }



}
if(DEBUG){
  Serial.println("becking DONE!");
  Serial.println("rele OFF");
}

delay(1000);
lcd.setCursor(0, 1);
lcd.clear();
}

void setup() {
  
  Serial.begin(9600);
  int zero = sensor.calibrate();
  Serial.println("Zero point for this sensor = " + zero);
  lcd.init();                     
  lcd.backlight();
  lcd.createChar(0, pBar);
  pinMode(pinCurrent,INPUT);
  pinMode(pinBtnStart,INPUT_PULLUP);
  pinMode(pinBtnStop,INPUT_PULLUP);
  attachInterrupt(0,Stop_Becking,FALLING);
  startScreen();
  
}

void loop() {
varExposition = map(analogRead(pinCurrent),0,1023,0,60);
if(!digitalRead(pinBtnStart) && varExposition!=0)Beking();
disUpdate();


}

