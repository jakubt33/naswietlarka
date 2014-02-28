#include "defines.h"
#include "init.h"
#include "pwm.h"
#include "hd44780.h"

int ilosc_petli(int*);
void wykonaj (int ile_petli);

ISR(INT1_vect)
{
    kierunek(TYL); //koniec jazdy przod, trzeba wracac
    wyswietl_LCD("COFAM");
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
}
int main()
{

    init_LCD();
    init_Switch();
    init_PWM();
    sei();

    stop();

    int wait = TAK;
    int wait2 = TAK;
    int licznik = 0;

    pozycjonowanie();
    _delay_ms(2000);
    kierunek(PRZOD);
    wyswietl_LCD("PRZOD");

    while(1)
    {
        if( bit_is_clear(PIN_SWITCH, KRANC) )
        {
            kierunek(PRZOD);
            wyswietl_LCD("PRZOD");
        }
    }
    stop();
    /*
    while(1)
    {
    int ile_petli = 0; //wartosc zadana przez uzytkownika


    wyswietl_LCD("witam kliknij OK");
    _delay_ms(200);

    wait = TAK;
    while(wait)
        if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;


    ile_petli = ilosc_petli(&ile_petli);

    wykonaj(ile_petli);

    wyswietl_LCD("rozpocznij - OK");
    _delay_ms(200);
    wait = TAK;

    while(wait)
        if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;
    }
        */

}

/*
void wykonaj (int ile_petli)
{
    int licznik;
    for (licznik=0; licznik<ile_petli; licznik++)
    {
        wyswietl_LCD("inkrementacja...");
        przod();
        _delay_ms(1000);
        wyswietl_LCD("dekrementacja...");
        tyl();
        _delay_ms(1000);
    }
}

int ilosc_petli(int *ile_petli)
{
    int wait = TAK;
    int wait2 = TAK;
    char ch_liczba[3]; //przechowywana jest liczba int w formie stringu

    wyswietl_LCD("ilosc petli:");
    _delay_ms(200);


    {
        wait2 = TAK;
        do
        {
            if(bit_is_clear(PIN_SWITCH, SWITCH_UP))
            {
                *ile_petli += 1;
                gen_char(ch_liczba, ile_petli);
                wyswietl_LCD(ch_liczba);
            }
            else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN))
            {
                *ile_petli -= 1;
                gen_char(ch_liczba, ile_petli);
                wyswietl_LCD(ch_liczba);
            }
            else if(bit_is_clear(PIN_SWITCH, SWITCH_OK))
            {
                wait = NIE;
                wait2 = NIE;
            }
            _delay_ms(200);
        }
        while(wait2 == TAK);
    }
    while (wait == TAK);

    return *ile_petli;
}
*/
