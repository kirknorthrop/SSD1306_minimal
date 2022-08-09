/*
  SSD1306_minimal.h - SSD1306 OLED Driver Library
  
  Copyright (c) 2012, Adafruit Industries. All rights reserved.
  Copyright (c) 2012 GOF Electronics Co. Ltd ( http://www.geekonfire.com )
  Copyright (c) 2015 CoPiino Electronics All right reserved.
  Copyright (c) 2016 Kirk Northrop (github.com/kirknorthrop)
  
  Original Author: Limor Fried/Ladyada Adafruit Industries
  Modified by: Jimbo.we (www.geekonfire.com)
  Modified by: CoPiino Electronics (http://copiino.cc)

      CoPiino Electronics invests time and resources providing this open source code,
      please support CoPiino Electronics and open-source hardware by purchasing
      products from CoPiino Electronics!

      What is it?
        This library is derived from GOFi2cOLED library, only for SSD1306 in I2C Mode.
        As the original library only supports Frame Buffered mode which requires to have
        at least 1024bytes of free RAM for a 128x64px display it is too big for smaller devices.

        So this a SSD1306 library that works great with ATTiny85 devices :)

  Modified by: Kirk Northrop (github.com/kirknorthrop)

  It is a free software; you can redistribute it and/or modify it 
  under the terms of BSD license, check LICENSE for more information.
  All text above must be included in any redistribution.
*/


#ifndef __SSD1306_MINIMAL_H__
#define __SSD1306_MINIMAL_H__

#include <Arduino.h>
#include <TinyWireM.h>
#include <USI_TWI_Master.h>

// config
#define SlaveAddress 0x3c




// defines taken from GOFi2cOLED
#define GOFi2cOLED_Command_Mode		      0x80
#define GOFi2cOLED_Data_Mode		      0x40

//Fundamental Command (more than one bytes command pleaserefer to SSD1306 datasheet for details)
#define Set_Contrast_Cmd                      0x81     //Double byte command to select 1 out of 256 contrast steps.Default(RESET = 0x7F)
#define Entire_Display_On_Resume_Cmd          0xA4     //Resume to RAM content display(RESET), Output follows RAM content
#define Entire_Display_On_Cmd                 0xA5     //Entire display ON, Output ignores RAM content
#define GOFi2cOLED_Normal_Display_Cmd	        0xA6     //Normal display (RESET)
#define GOFi2cOLED_Inverse_Display_Cmd	      0xA7     //Inverse display
#define GOFi2cOLED_Display_Off_Cmd	          0xAE     //sleep mode(RESET)
#define GOFi2cOLED_Display_On_Cmd	            0xAF     //normal mode

//Scrolling Command (more than one bytes command pleaserefer to SSD1306 datasheet for details)
#define Right_Horizontal_Scroll_Cmd           0x26
#define Left_Horizontal_Scroll_Cmd            0x27
#define Vertical_Right_Horizontal_Scroll_Cmd  0x29
#define Vertical_Left_Horizontal_Scroll_Cmd   0x2A
#define Activate_Scroll_Cmd                   0x2F
#define Deactivate_Scroll_Cmd                 0x2E
#define Set_Vertical_Scroll_Area_Cmd          0xA3

//Addressing Setting Command (more than one bytes command pleaserefer to SSD1306 datasheet for details)
#define Set_Memory_Addressing_Mode_Cmd        0x20
#define HORIZONTAL_MODE			                  0x00
#define VERTICAL_MODE			                    0x01
#define PAGE_MODE			                        0x02       //Default(reset)
#define Set_Column_Address_Cmd                0x21       //Setup column start and end address. This command is only for horizontal or vertical addressing mode.
#define Set_Page_Address_Cmd                  0x22       //Setup page start and end address. This command is only for horizontal or vertical addressing mode.

//Hardware Configuration (Panel resolution & layout related) Command (more than one bytes command please refer to SSD1306 datasheet for details)
#define Segment_Remap_Cmd                     0xA1       //column address 127 is mapped to SEG0
#define Segment_Normal_map_Cmd                0xA0       //Default. column address 0 is mapped to SEG0(RESET)
#define Set_Multiplex_Ratio_Cmd               0xA8       //Set MUX ratio to N+1 MUX
#define COM_Output_Normal_Scan_Cmd            0xC0       //Normal mode (RESET). Scan from COM0 to COM[N �C1]
#define COM_Output_Remap_Scan_Cmd             0xC8       //Remapped mode. Scan from COM[N-1] to COM0
#define Set_Display_Offset_Cmd                0xD3       //Set vertical shift by COM from 0d~63d. The value is reset to 00h after RESET.
#define Set_COM_Pins_Hardware_Config_Cmd      0xDA   

//Timing & Driving Scheme Setting Command (more than one bytes command pleaserefer to SSD1some more than one bytes command please 306 datasheet for details)
#define Set_Display_Clock_Divide_Ratio_Cmd    0xD5
#define Set_Precharge_Period_Cmd              0xD9
#define Set_VCOMH_Deselect_Level_Cmd          0xDB
#define No_Operation_Cmd                      0xE3

#define Charge_Pump_Setting_Cmd      	        0x8D
#define Charge_Pump_Enable_Cmd	              0x14
#define Charge_Pump_Disable_Cmd               0x10     //default

#define Scroll_Left			         0x00
#define Scroll_Right			       0x01

#define Scroll_2Frames			      0x7
#define Scroll_3Frames			      0x4
#define Scroll_4Frames			      0x5
#define Scroll_5Frames			      0x0
#define Scroll_25Frames			      0x6
#define Scroll_64Frames			      0x1
#define Scroll_128Frames		      0x2
#define Scroll_256Frames		      0x3

#define Dummy_Byte_0x00                       0x00
#define Dummy_Byte_0xFF                       0xFF



// 
class SSD1306_Mini {
  
  public:
    
    // call this function once in "void setup()" to initiallize the display
    void init(uint8_t address);
  
    // reset clipArea to maximum and clear the display
    void clear();
    
    // move cursor to upper left corner in current clipArea
    void startScreen();
    
    // set the clipArea, by default (0,0,128,8)
    void clipArea(unsigned char col, unsigned char row, unsigned char w, unsigned char h);
    
    // move the cursor to a location (similar to clipArea)
    void cursorTo( unsigned char row, unsigned char col );
    
    // print a single character
    void printChar( char ch );

    // print a string to the screen
    void printString( char * pText );
    
    // draw an image with defined x,y position and width,height definition
    void drawImage( const unsigned char * img, unsigned char col, unsigned char row, unsigned char w, unsigned char h );
      
    //  
    void displayX(int off);

    void setPixel(int x, int y, bool set);
  
//  private:
    void sendCommand(unsigned char command);
    void sendData(unsigned char Data);
  
    unsigned char getFlash( const unsigned char * mem, unsigned int idx  );

};


#endif
