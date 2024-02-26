#include <avr/io.h>
#include <util/delay.h>
void adc_init(void);
unsigned int get_adc(void);
#include "i2c.h"
#include "SSD1306.h"