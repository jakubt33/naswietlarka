#include <avr/io.h>
#define F_CPU 4000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#include "pwm.h"
#include "hd44780.h"

#define PIN_SWITCH PINC
#define SWITCH_UP PC1
#define SWITCH_DOWN PC2
#define SWITCH_OK PC3
#define DDR_SWITCH DDRC
#define PORT_SWITCH PORTC


#define NIE 0
#define TAK 1

void Switch_Init()
{
    DDR_SWITCH &= ~(_BV(SWITCH_UP));
    DDR_SWITCH &= ~(_BV(SWITCH_DOWN));
    DDR_SWITCH &= ~(_BV(SWITCH_OK));

    PORT_SWITCH |= _BV(SWITCH_UP);
    PORT_SWITCH |= _BV(SWITCH_DOWN);
    PORT_SWITCH |= _BV(SWITCH_OK);
}

/*
int main()
{

    wlacz_LCD();
    Switch_Init();
    PWM_Init();
    sei();

    _delay_ms(1000);
    wyswietl_LCD("kutas");
    _delay_ms(1000);


    while(1)
        {
           if(bit_is_clear(PIN_SWITCH, SWITCH_UP)) wyswietl_LCD("UP");
           else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN)) wyswietl_LCD("DOWN");
           else if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wyswietl_LCD("OK");
           _delay_ms(100);
        }
}
*/

int main()
{

    wlacz_LCD();
    Switch_Init();
    PWM_Init();
    sei();

    int8_t work = TAK;
    int8_t wait = TAK;
    int8_t wait2 = TAK;
    int8_t ile_petli = 0;
    uint16_t licznik;
    while(work)
    {
       //zrobic funkcje ktora zamienia int na *char

        wyswietl_LCD("witam kliknij OK");
        wait = TAK;
        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;


        wyswietl_LCD("ile petli?");
        wait = TAK;
        while(wait)
        {
            wait2 = TAK;
            while(wait2)
            {
                _delay_ms(50);
                if(bit_is_clear(PIN_SWITCH, SWITCH_UP))
                {
                    ile_petli = 2;
                    wyswietl_LCD("ilos to 2");
                    //wait2 = NIE;
                }
                else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN))
                {
                    ile_petli = 5;
                    wyswietl_LCD("ilos to 5");
                    //wait2 = NIE;
                }
                else if(bit_is_clear(PIN_SWITCH, SWITCH_OK))
                {
                    wait = NIE;
                    wait2 = NIE;
                }
            }
                //char *ile = ile_petli;
                //wyswietl_LCD(ile);
        }

        for (licznik=0; licznik<ile_petli; licznik++)
        {
            wyswietl_LCD("przyspieszam...");
            przyspiesz();
            _delay_ms(100);
            wyswietl_LCD("spowalniam...");
            spowolnij();
            _delay_ms(100);
        }
    }
}
