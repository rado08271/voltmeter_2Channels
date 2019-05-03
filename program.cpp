#include <Arduino.h>
#include <Wire.h>

#include "pinouts.hpp"
#include "lcd.hpp"

typedef unsigned long int lui;            //pre skratenie zapisu vlastna premenna pri millis();

void pinsInit(){
  pinMode(VOLT_CHANNEL_RIGHT, INPUT);
  pinMode(VOLT_CHANNEL_LEFT, INPUT);

  pinMode(BTN_CHANNEL_TOGGLE, INPUT);
  pinMode(BTN_BOTH_CHANNELS, INPUT);
  pinMode(BTN_LOOP, INPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(PIEZO_BEEP, OUTPUT);
  
  pinMode(RESET_ARDUINO, OUTPUT);
}

void beepSound(){
  tone(PIEZO_BEEP, 1000, 500);            //zvuk 1000kHz na 500ms
}

void printToSerial(float value, char channel){
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(" value: ");
  Serial.println(value);
}

void printToLCD(float valueL, float valueR){
  lcdPrintAt(0,0,"Channel L ");
  lcdPrintValueAt(12,0, valueL);
  
  lcdPrintAt(0,0,"Channel R ");
  lcdPrintValueAt(12,0, valueR);
}

/**
 * Vypni kanaly
 */
void noChannel(){
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);
  lcdClear();
}


/**
 * Lavy kanal najprv vypni kanal 
 */
int leftChannel(){
  noChannel();
  digitalWrite(LED_LEFT, HIGH);

  int value = analogRead(VOLT_CHANNEL_LEFT);

  //analog cita 1024 hodnot na 5V
  float voltage = value * (5.0 / 1023.0);

  printToSerial(voltage, 'L');
  printToLCD(voltage, 0);

  return voltage;
  
}

/**
 * Pravy kanal najprv vypni kanal 
 */
int rightChannel(){
  noChannel();
  digitalWrite(LED_RIGHT, HIGH);

  //FIXME tu daj loop ale aby sa vedelo aj odtial dostat po kliknuti na ine tlacidlo ako toto mozes spravit aj cez bitovy OR | a kluce ale zmen strukturu!
  
  int value = analogRead(VOLT_CHANNEL_RIGHT);

  //analog cita 1024 hodnot na 5V
  float voltage = value * (5.0 / 1023.0);

  printToSerial(voltage, 'R');
  printToLCD(0,voltage);

  return voltage;
}

/**
 * Vypni vsetky kanaly a zapni obe
 */
void bothChannels(){
  noChannel();
  rightChannel();
  leftChannel();
}

/**
 * Zacyklenie programu pouzitim funkcie milis()
 * po 8 sekundach sa arduino resetuje!
 */
void loopThrough(){
  lcdClear();
  lcdPrintAt(3,0,"Loop: ");

  lui startTime = millis();                 //cas na vstupe
  lui actualTime = 0;                       //aktualny cas
  lui timePassed = 0;                       //inicializacia premennej pre kontrolu casu

  while(timePassed <= 8000){                //rob kym hodnota casov nieje menej ako 8k
    actualTime = millis();                  //precitaj aktualny cas
    timePassed = actualTime - startTime;    //cas od zaciatku po tento okamih...ocakavana hodnota pre ukoncenie je 8000
                 
    lcdPrintValueAt(10,0, (float) timePassed/1000);
    //TODO implementuj zacyklenie a ten watchdog pridaj dlhsie intervaly 50ms napriklad cez while alebo if...
    if(timePassed%50 == 0){                 //teoreticky preslo 50ms
      //pridaj co sa ma vykonat...
    }
    
  }

  //FIXME skontroluj ci toto resetuje arduino...100ms je len tak mozno to nieje ani potrebne!
  digitalWrite(RESET_ARDUINO, HIGH);
//  delay(100);                     //zakazane pouzitie delay!
  digitalWrite(RESET_ARDUINO, LOW);
}

void mainLoop(){
  bool left = false;
  //Toto je hlavny cyklus programu
  while(1){
    //Zmena kanalu
    while(digitalRead(BTN_CHANNEL_TOGGLE)==HIGH){
      if(digitalRead(BTN_CHANNEL_TOGGLE)==LOW){
        if(left){
          leftChannel();
          left = false;
        }else{
          rightChannel();
          left = true;
        }
        break;
      }
    }

    //Obidva kanaly
    while(digitalRead(BTN_BOTH_CHANNELS)==HIGH){
      if(digitalRead(BTN_BOTH_CHANNELS)==LOW){
        bothChannels();
        break;
      }
    }

    //Zacyklenie programu
    while(digitalRead(BTN_LOOP)==HIGH){
      if(digitalRead(BTN_LOOP)==LOW){
        loopThrough();
        break;
      }
    }

     
  }
}

