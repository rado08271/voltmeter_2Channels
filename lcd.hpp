#ifndef _LCD_HPP
#define _LCD_HPP

void lcdInit();
void lcdClear();
void lcdSetCursor(int y, int x);
void lcdPrint(char* text);
void lcdPrintValue(float value);
void lcdPrintAt(int y, int x, char* text);
void lcdPrintValueAt(int y, int x, float value);

#endif
