#include "lcd.hpp"
#include "pinouts.hpp"
#include "program.hpp"

void setup() {
  lcdInit();
  pinsInit();
}

void loop() {
  mainLoop();
}
