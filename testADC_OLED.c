/******************************************************************
* testADC_OLED.c Firmware to test ATmega328P ADC & SSD1306 OLED display
*
* Version 1.0 D. McLaughlin for ECE-304 2/22/24
**************************************************************/

#include "megaTemp.h"
#define NUMSAMPLES 25  // #ADC Samples to average
#define VREF 1.1        // ADC reference voltage
#define MAXTEMP 70      // Too-Hot LED turns on at this temp (Deg F)
#define TOO_HOT_LED PD2 // LED indicator pin
#define F_C_SELECT PD3  // F vs C temp switch. C when pressed.

int main(void)
{
    float analogVoltage;
    unsigned int digitalValue, tempx10;
    unsigned long int totalValue;
    DDRD = 1 << TOO_HOT_LED;    // Set as output
    PORTD |= (1 << F_C_SELECT); // Set input pullup
    adc_init();
    OLED_Init();

    while (1)
    {
        // Acquire & average NUMSAMPLES measurements
        totalValue = 0;
        for (int i = 0; i < NUMSAMPLES; i++)
            totalValue += get_adc(); // Get a sample from temp sensor
        digitalValue = totalValue / NUMSAMPLES;

        // Convert to mV
        analogVoltage = digitalValue * 1.0 * VREF / 1024; // Convert digital value to degrees C
        analogVoltage = analogVoltage * 1000;   // Convert to mV

        OLED_GoToLine(1);
        OLED_DisplayString("Dig:");
        OLED_DisplayNumber(10, digitalValue, 4);
        OLED_GoToLine(3);
        OLED_DisplayString("mV:");
        OLED_DisplayNumber(10, analogVoltage, 4);

        _delay_ms(500);
    }
    return 0;
}

// Initialize ADC peripheral
// Enable ADC; set speed to 125 KHz
void adc_init(void)
{
    ADMUX = 0xC2; // Select ADC2; Vref=1.1
    if (F_CPU > 1000000)
        ADCSRA = 0x87; // Enable ADC; divide by 128 for 16 MHz clock
    else
        ADCSRA = 0x83; // Enable ADC; divide by 8 for 1 MHZ clock
}

// Read ADC value
unsigned int get_adc()
{
    ADCSRA |= (1 << ADSC); // start ADC conversion
    while ((ADCSRA & (1 << ADIF)) == 0)
        ;                      // wait till ADC finishes
    ADCSRA |= 1<<ADIF;         //  Clear flag 
    return ADCL | (ADCH << 8); // read ADCL first !
}
