# megaTemp
Code for embedded ATmega328p, TMP36, SSD OLED digital thermometer project for ECE-304 Spring 2024 @UMass


To build this code, create a project folder that contains the following files:

i2c.c, ic2,h, SSD1306.c, and SSD106.h (these 4 files comprise the library we're using for the OLED and the I2C interface)

megaTemp.c this is my example source code for the digital thermometer. Nothing fancy: take ADC measurements, average them, convert digital values to temperatire; display to the OLED, repeat. The circuit should have a push-button switch to select F vs C and an LED to indicate temp is too hot.

testADC_OLED.c this is a piece of test code I wrote for reading an ADC input and writing to the OLED

makefile (be sure that the makefile has no extension. And also insure that variables in the makefile are set correctly for the processor, port, clock frequency, and programmer) 

To compile, type "make" from the Command Prompt (Windows) or from Terminal (macOS).

To flash the compiled code to your AVR microcontroller, type "make flash"

Note that sometimes, it is necessary to re-compile even when you haven't made changes to the 
source code. For this situation, type "make -B"

My source code is based on the example found here:
https://audiodiwhy.blogspot.com/2021/06/embedded-c-avr-getting-oled-display.html
The SSD1306 libraries i2c.c, i2c.h, SSD1306.c, and SSD1306.h were downloaded from Preston Sundar's github here: 
https://github.com/Preston-Sundar/AVR-OLED-SSD1306-IIC-DRIVER


