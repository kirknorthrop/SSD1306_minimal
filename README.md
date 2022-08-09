# SSD1306 Minimal  

## Description
This is a modification of the GOFi2cOLED which is based on the Adafruit SSD1306 library.

I have added in a reference to the codepage that the font uses (Code Page 437 minus one glyph), to make it easier to decide which rows of the font are necessary to keep, as this uses up a lot of RAM, especially on an Adafruit Trinket.

There's a lot of other commented out code which was in the version I found. I have not yet worked out why this is the case.

I've also altered it to work with the standard TinyWireM, hopefully.

## Usage / Basic Setup  
Include the library in your Arduino file  
```c
#include "SSD1306_minimal.h
```  

Setup the display  
```c
SSD1306_Mini ssd1306;

void setup() {
    ssd1306.init(SlaveAddress);
}
```

Printing strings and chars  
```c
ssd1306.printString("string");
ssd1306.printChar('a');
```  

Check the `example.ino` for a basic starting point

## Notes  
`cursorTo(x,y);` uses pages so `x` has a range of `0-127` whereas `y` has a range from `0-7`. Due to paging, using the function `setPixel()` will draw a vertical line with a width of 1px but a height of `128 / pages` (usually 8px).  

Tested on an Attiny85.
