#include "defines.h"
#include "init.h"
#include "pwm.h"
#include "hd44780.h"

int ilosc_petli();
void wykonaj (int ile_petli);

ISR(INT1_vect)
{
    if(flag_kierunek == PRZOD)
    {
        kierunek(TYL); //koniec jazdy przod, trzeba wracac
        wyswietl_LCD("COFAM");
    }
    else
        wyswietl_LCD("unexpected int");

}
void pozycjonowanie()
{
    _delay_ms(100);
    wyswietl_LCD("pozycjonowanie");

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
    wyswietl_LCD("ready to go");
    _delay_ms(100);
    _delay_ms(100);
}

int main()
{

    init_LCD();
    init_Switch();
    init_PWM();
    init_Buzzer();
    init_Relay();
    sei();

    while(1)
    {
        stop();
        int ile_petli = 0; //wartosc zadana przez uzytkownika
        int wait = TAK;

        wyswietl_LCD("witam kliknij OK");
        _delay_ms(200);

        wait = TAK;
        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;


        ile_petli = ilosc_petli();

        wykonaj(ile_petli);

        wyswietl_LCD("zakonczono - OK");
        _delay_ms(200);
        wait = TAK;

        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;
    }

}


void wykonaj (int ile_petli)
{
    int licznik=0;
    //włączenie przekaźnika

    pozycjonowanie();
    for (licznik=0; licznik<ile_petli; licznik++)
    {
        wyswietl_LCD("PRZOD");
        kierunek(PRZOD);
        _delay_ms(1500); //odleglosc dokad dojadą lampy

        wyswietl_LCD("TYL");
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
    //wyłączenie przekaznika
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
            gen_char(ch_liczba, ile_petli);
            wyswietl_LCD(ch_liczba);
        }
        else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN))
        {
            ile_petli -= 1;
            gen_char(ch_liczba, ile_petli);
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
