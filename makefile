# makefile for AVR projects
# ECE-231 and ECE-304 Spring 2024
# revision history
#	Version	Date		Author			Revision
#	1.0		2/21/24		D. McLaughlin	initial release 

#______________ MODIFY SERIALPORT________________________________________
# Specify the com port (windows) or USB port (macOS)
# Use Device Manager to identify COM port number in Windows
# In Terminal, type ls /dev/tty.usb* to determine USB port in macOS
# use usb for pocket programmer on macOS
SERIALPORT = /dev/tty.usbmodem1101

#______________ MODIFY SOURCEFILE NAME(S)_________________________________
# Specify the name of your source code here:
SOURCEFILE =megaTemp.c i2c.c ssd1306.c

#______________ MODIFY CPU CLOCK, PROGRAMMER MODEL, AND MCU_______________
CLOCKSPEED = 16000000UL	#Use 16000000 for Arduino Uno; 1000000 for new ATmega328P chip
PROGRAMMER = Arduino 	#Use Arduino for Arduino Uno; usbtiny for pocket programmer 
MCU = ATmega328p 	#Use ATmega328p, ATtiny85, or other MCU name as appropriate

#______________DON'T CHANGE ANYTHING BELOW UNLESS YOU KNOW WHAT YOU'RE DOING_________
begin:	main.hex

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(MCU) main.elf

main.elf: $(SOURCEFILE)
	avr-gcc -Wall -Os -DF_CPU=$(CLOCKSPEED) -mmcu=$(MCU) -o main.elf $(SOURCEFILE)
	
flash:	begin
	avrdude -c $(PROGRAMMER) -b 115200 -P $(SERIALPORT) -p $(MCU) -U flash:w:main.hex:i
