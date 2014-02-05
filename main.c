#include <avr/io.h>
#define F_CPU 1000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#include "pwm.h"
#include "hd44780.h"

int main()
{

    wlacz_LCD();

    PWM_Init();
    sei();

    _delay_ms(1000);
    wyswietl_LCD("kutas");
    _delay_ms(1000);


    while(1)
        {
            czysc_LCD();
            wyswietl_LCD("przyspieszam...");
            rozjasnij();
            _delay_ms(100);
            czysc_LCD();
            wyswietl_LCD("spowalniam...");
            pociemnij();
            _delay_ms(100);
        }
}


