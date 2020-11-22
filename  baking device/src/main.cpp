#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей

int8_t varCurrent = 20;
int8_t varExposition;

void setup() {
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print(" Backing device");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("  by MACKELLY");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EXP:        A:");

}

void loop() {
  // Устанавливаем курсор на вторую строку и нулевой символ.
  
  lcd.setCursor(4, 0);  
  // Выводим на экран количество секунд с момента запуска ардуины
  lcd.print(millis()/1000); 
  lcd.print("sec"); 
  lcd.setCursor(14, 0);  
  // Выводим на экран количество секунд с момента запуска ардуины
  lcd.print(varCurrent); 
}

void StartBeking() {

}