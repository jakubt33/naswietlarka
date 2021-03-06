#include "defines.h"
#include "init.h"
#include "pwm.h"
#include "hd44780.h"

ISR(INT1_vect)
{
    pozycjonowanie();
}

ISR(TIMER0_OVF_vect)
{
    if(naswietlanie)
    {
        overflow += 1;
        if( (overflow%15) == 0)
        {
            time--;
            overflow = 0;
            gen_char_time(ch_liczba, &time);
            czysc_LCD_linia2();
            wyswietl_LCD(ch_liczba);
            wyswietl_LCD("s");
            if(time <=0)
            {
                naswietlanie = NIE;
                time = STOP;
            }
        }
    }
}

int main()
{
    init_LCD();
    init_Relay();
    init_Switch();
    init_Buzzer();
    init_LCD();
    init_PWM();
    init_Timer();

    sei();

    while(1)
    {
        stop();

        int dlugosc = 0;
        int wait = TAK;

        czysc_LCD_linia2();
        czysc_LCD_linia1();
        wyswietl_LCD("Start -> OK");
        _delay_ms(200);

        wait = TAK;
        while(wait)
            if(bit_is_clear(PIN_SWITCH, SWITCH_OK)) wait = NIE;

        dlugosc = get_distance();

        get_time();

        wykonaj(dlugosc);
        _delay_ms(200);

    }

}

int get_distance()
{
    int dlugosc = 0;
    char ch_liczba[3]; //przechowywana jest liczba int w formie stringu

    czysc_LCD_linia2();
    czysc_LCD_linia1();
    wyswietl_LCD("dlugosc PBC:");
    _delay_ms(200);

    int wait = TAK;
    do
    {
        if(bit_is_clear(PIN_SWITCH, SWITCH_UP))
        {
            dlugosc += 1;
            if(dlugosc>16) dlugosc = 0;
            gen_char(ch_liczba, &dlugosc);
            czysc_LCD_linia2(); //czysci i ustawai kursor na początku 2. lini
            wyswietl_LCD(ch_liczba);
            wyswietl_LCD("cm");
        }
        else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN))
        {
            dlugosc -= 1;
            if(dlugosc<0)   dlugosc = 16;
            gen_char(ch_liczba, &dlugosc);
            czysc_LCD_linia2();
            wyswietl_LCD(ch_liczba);
            wyswietl_LCD("cm");
        }
        else if(bit_is_clear(PIN_SWITCH, SWITCH_OK))
        {
            wait = NIE;
        }
        _delay_ms(200);
    }
    while(wait == TAK);

    return dlugosc;

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

void wykonaj (int dlugosc)
{
    int licznik=0;

    int delay = 370;
    if(dlugosc>MIN_DLUGOSC)
        delay = delay + (dlugosc-MIN_DLUGOSC)*190; //dobrane tak aby jeździło na odp. odleglosc;

    pozycjonowanie();
    _delay_ms(500);

    relay_on();
    _delay_ms(200);
    czysc_LCD_linia1();
    wyswietl_LCD("pozostało:");

    if(time==0) //funkcja nadajaca wartosci domyslne
    {
        if(dlugosc<=MIN_DLUGOSC) time = 100; //sekund
        else if(dlugosc<=10) time = 110;
        else if(dlugosc<=13) time = 120;
        else time = 100;
    }

    naswietlanie = TAK;
    init_LCD(); //dla pewnosci, labowy LCD...
    init_PWM();
    TCNT0 = 0; //zerownaie timera0
    overflow = 0;

    while(time > 0)
    {
        kierunek(PRZOD);
        _delay_ms(delay); //odleglosc dokad dojadą lampy

        stop();

        if(dlugosc<8) _delay_ms(2000);
        else _delay_ms(500); //tyle lampy czekaja w nowej pozycji

        pozycjonowanie(); //jezdie do tylu az napotka krancowe
        if(dlugosc<8) _delay_ms(2000);
        else _delay_ms(500);
    }
    _delay_ms(500);
    relay_off();
    _delay_ms(500);
    czysc_LCD_linia2();
    czysc_LCD_linia1();
    wyswietl_LCD("KONIEC PRACY");
    beep();
}

void beep()
{
    buzzer_on();
    _delay_ms(500);
    buzzer_off();
    _delay_ms(500);
    buzzer_on();
    _delay_ms(700);
    buzzer_off();
}

void get_time()
{
    int wait = TAK;
    czysc_LCD_linia2();
    czysc_LCD_linia1();
    wyswietl_LCD("czas: 0-default");
    _delay_ms(200);


    wait = TAK;
    czysc_LCD_linia2();
    wyswietl_LCD("0");
    do
    {
        if(bit_is_clear(PIN_SWITCH, SWITCH_UP))
        {
            if(time<5) time += 1;
            else time += 5;
            gen_char_time(ch_liczba, &time);
            czysc_LCD_linia2();
            wyswietl_LCD(ch_liczba);
            wyswietl_LCD("s");
        }
        else if(bit_is_clear(PIN_SWITCH, SWITCH_DOWN))
        {
            if(time < 10) time -= 1;
            else time -= 5;
            gen_char_time(ch_liczba, &time);
            czysc_LCD_linia2();
            wyswietl_LCD(ch_liczba);
            wyswietl_LCD("s");
        }
        else if(bit_is_clear(PIN_SWITCH, SWITCH_OK))
        {
            wait = NIE;
        }
        _delay_ms(200);
    }
    while(wait == TAK);
}
