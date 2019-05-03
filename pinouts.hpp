#ifndef _PINS_HPP
#define _PINS_HPP

#define VOLT_CHANNEL_RIGHT  0                 //Pravy kanal voltmetra
#define VOLT_CHANNEL_LEFT   0                 //Lavy kanal voltmetra

#define BTN_CHANNEL_TOGGLE  10                //Volba kanalov bude implementovana pomocou tlacidla pripojeneho na pin c 10
#define BTN_BOTH_CHANNELS   9                 //Na pin c.9 bude pripojene druhe tlacidlo ktorym sa spusti mod, pre obe kanaly sucasne 
#define BTN_LOOP            8                 //Na pin c.8 bude pripojene tlacidlo ktore bude simulovat zacyklenie programu
#define LED_LEFT            4                 //Lavy kanal prave aktivny
#define LED_RIGHT           3                 //Pravy kanal prave aktivny
#define PIEZO_BEEP          0                 //Reproduktor ktory vyda zvuk (1kHz) pri kazdom stlaceni kanalu

#define RESET_ARDUINO       0                 //RESETUJE arduino po 8

#endif
