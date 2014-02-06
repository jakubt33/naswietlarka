#include <avr/io.h>
#define F_CPU 1000000UL
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
    int8_t licznik;
    while(work)
    {
       //zrobic funkcje ktora zamienia int na *char

        wyswietl_LCD("witam kliknij ok");
        wait = TAK;
        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;

        wyswietl_LCD("ile petli?");
        _delay_ms(1000);

        wait = TAK;
        while(wait)
        {
            wyswietl_LCD("zliczam"); //powinna byc liczba
            wait2 = TAK;
            while(wait2)
            {
                _delay_ms(50);
                if(bit_is_clear(PIN_SWITCH, SWITCH_UP))
                {
                    ile_petli = 2;
                    //wait2 = NIE;
                }
                else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN))
                {
                    ile_petli = 5;
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
        wyswietl_LCD("ok?");
        _delay_ms(100);
        wait = TAK;
        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;

        for (licznik=0; licznik<3; licznik++)
        {
            wyswietl_LCD("przyspieszam...");
            rozjasnij();
            _delay_ms(100);
            wyswietl_LCD("spowalniam...");
            pociemnij();
            _delay_ms(100);
        }
    }
}


