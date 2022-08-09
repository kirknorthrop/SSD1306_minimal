#include "SSD1306_minimal.h"

SSD1306_Mini ssd1306;

int y = 0;
bool down = true;

void setup() {
  // put your setup code here, to run once:
  ssd1306.init(SlaveAddress);
  ssd1306.clear();
  ssd1306.cursorTo(0, 0);
  ssd1306.printString("SSD1306 Mini");
}


void loop() {
  // put your main code here, to run repeatedly:
  ssd1306.setPixel(120, y + 1, false);
  ssd1306.setPixel(120, y - 1, false);

  ssd1306.setPixel(120, y, true);
  y += down ? 1 : -1;
  down = y >= 7 ? false : y <= 0 ? true : down;

  ssd1306.cursorTo(0, 7);
  ssd1306.printChar(y + 48);

  delay(100);
}