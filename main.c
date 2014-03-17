#include "defines.h"
#include "init.h"
#include "pwm.h"
#include "hd44780.h"

ISR(INT1_vect)
{
    pozycjonowanie();
}
int main()
{
    init_LCD();
    init_Relay();
    init_Switch();
    init_Buzzer();
    init_LCD();
    init_PWM();

    sei();

    while(1)
    {

        stop();
        int ile_petli = 0; //wartosc zadana przez uzytkownika
        int wait = TAK;

        wyswietl_LCD("Start -> OK");
        _delay_ms(200);

        wait = TAK;
        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;


        ile_petli = ilosc_petli();

        wykonaj(ile_petli);
        _delay_ms(200);
    }

}

void pozycjonowanie()
{
    if(bit_is_clear(PIN_SWITCH, KRANC));
    else
    {
        kierunek(TYL);
        int x=1;
        while(x)
        {
            if(bit_is_clear(PIN_SWITCH, KRANC))
            {
                x=0;
            }
        }
        stop();
    }
    stop();
}


void wykonaj (int ile_petli)
{
    int licznik=0;
    char ch_liczba[3];

    pozycjonowanie();
    _delay_ms(500);

    relay_on();
    _delay_ms(50);
    init_LCD();
    init_PWM();
    _delay_ms(200);


    for (licznik=0; licznik<ile_petli; licznik++)
    {
        int do_konca = ile_petli-licznik;
        gen_char(ch_liczba, &do_konca); //wyswietla ile cykli pozostało do konca naswietlania
        wyswietl_LCD(ch_liczba);

        kierunek(PRZOD);
        _delay_ms(1500); //odleglosc dokad dojadą lampy

        pozycjonowanie(); //jezdie do tylu az napotka krancowe
    }
    _delay_ms(1000);
    wyswietl_LCD("KUNIEC PRACY");
    _delay_ms(1000);
    relay_off();
    wyswietl_LCD("UV OFF");
    _delay_ms(1000);
    beep();
}

void beep()
{
    wyswietl_LCD("BEEP..BEEP");
    buzzer_on();
    _delay_ms(500);
    buzzer_off();
    _delay_ms(500);
    buzzer_on();
    _delay_ms(700);
    buzzer_off();
}
int ilosc_petli()
{
    int wait = TAK;
    int ile_petli = 0;
    char ch_liczba[3]; //przechowywana jest liczba int w formie stringu

    wyswietl_LCD("ilosc petli:");
    _delay_ms(200);


    wait = TAK;
    do
    {
        if(bit_is_clear(PIN_SWITCH, SWITCH_UP))
        {
            ile_petli += 1;
            gen_char(ch_liczba, &ile_petli);
            wyswietl_LCD(ch_liczba);
        }
        else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN))
        {
            ile_petli -= 1;
            gen_char(ch_liczba, &ile_petli);
            wyswietl_LCD(ch_liczba);
        }
        else if(bit_is_clear(PIN_SWITCH, SWITCH_OK))
        {
            wait = NIE;
        }
        _delay_ms(200);
    }
    while(wait == TAK);


    return ile_petli;
}
