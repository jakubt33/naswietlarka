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

    int work = TAK;
    int wait = TAK;
    int wait2 = TAK;
    int licznik;
    while(work)
    {
       //zrobic funkcje ktora zamienia int na *char
        int ile_petli = 0;

        wyswietl_LCD("witam kliknij OK");
        _delay_ms(200);
        wait = TAK;
        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;

        _delay_ms(200);
        wyswietl_LCD("ile petli?");
        wait = TAK;
        do
        {
            wait2 = TAK;
            do
            {
                if(bit_is_clear(PIN_SWITCH, SWITCH_UP))
                {
                    ile_petli += 1;
                    wyswietl_LCD("dodano");
                    //wait2 = NIE;
                }
                else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN))
                {
                    ile_petli -= 1;
                    wyswietl_LCD("odejeto");
                    //wait2 = NIE;
                }
                else if(bit_is_clear(PIN_SWITCH, SWITCH_OK))
                {
                    wait = NIE;
                    wait2 = NIE;
                }
                _delay_ms(200);
            } while(wait2 == TAK);
                //char *ile = ile_petli;
                //wyswietl_LCD(ile);
        } while (wait == TAK);

        for (licznik=0; licznik<ile_petli; licznik++)
        {
            wyswietl_LCD("przyspieszam...");
            przyspiesz();
            _delay_ms(100);
            wyswietl_LCD("spowalniam...");
            spowolnij();
            _delay_ms(100);
        }
        wyswietl_LCD("zakonczono prace");
        _delay_ms(200);
        wait = TAK;
        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;
    }
}
