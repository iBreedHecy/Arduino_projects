#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define DEBUG 0
LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей

int varCurrent = 20;
int varExposition = 250;
int _current,_exposition;
unsigned long _exposition_last_time;
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


void disUpdate(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EXP:");
  lcd.print(varExposition);
  lcd.print("sec "); 
  lcd.setCursor(12, 0); 
  lcd.print("A:");   
  lcd.print(varCurrent);

}
void startScreen(){
  lcd.setCursor(0, 0);
  lcd.print(" Backing device");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  by MACKELLY");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("   22/11/2020");
  delay(2000);
  disUpdate();
}
void Beking() {
Serial.println("Start becking..");
Serial.println("check A");
Serial.println("rele ON");
_exposition_last_time = millis();
_exposition = varExposition;
while(_exposition != 0){
  if((millis() - _exposition_last_time) >= 1000) {
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
Serial.println("becking DONE!");
Serial.println("rele OFF");

delay(1000);
lcd.setCursor(0, 1);

lcd.print("      DONE      ");
delay(1000);
lcd.setCursor(0, 1);
lcd.print("                ");








}
void setup() {
  
  Serial.begin(9600);
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.createChar(0, pBar);
  startScreen();
  #ifndef DEGUG
      Serial.println("#DEGUG");
  #endif
  
}

void loop() {
Beking();
disUpdate();

}

