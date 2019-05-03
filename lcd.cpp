#include <Arduino.h>

#include "lcd.hpp"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//TODO mozno pridaj nech vypisuje priamo hodnotu v int alebo float
void lcdInit(){
    lcd.begin(16,2);
    lcd.display();
}

void lcdClear(){
    lcd.home();
    lcd.clear();
}


void lcdSetCursor(int y, int x){
    lcd.setCursor(y,x);
}

void lcdPrint(char* text){
//    Serial.println(text);
    lcd.print(text);
}

void lcdPrintValue(float value){
//    Serial.println(value);
    lcd.print(value);
}

void lcdPrintAt(int y, int x, char* text){
    lcdSetCursor(y, x);
    lcdPrint(text);
}

void lcdPrintValueAt(int y, int x, float value){
    lcdSetCursor(y, x);
    lcdPrintValue(value);
}

