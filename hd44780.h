#ifndef HD44780_H_INCLUDED
#define HD44780_H_INCLUDED


void czysc_LCD()
{
    PORT_LCD &= ~(_BV(RS_LCD));
    push_LCD(1);
    PORT_LCD |= (_BV(RS_LCD));
    //czekaj 1.64ms
    _delay_ms(2);

}

void gen_char(char *ch, int *i)
{
    if(*i>99)
    {
        *i = 0;
    }
    else if(*i<0)
    {
        *i = 99;
    }
    if (*i<10)
    {
        ch[0] = (*i + '0');
        ch[1] = '\0';
    }
    else if(*i<100)
    {
        ch[0] = (*i/10 + '0');
        ch[1] = (*i%10 + '0');
        ch[2] = '\0';
    }
}

void push_LCD( int8_t bajt ) //jako argument podajemy kod litery w ascii np: 'B'(lub własne dane )
{
    //ustawienie EN
    PORT_LCD |= _BV(EN_LCD);

    //wysłanie 4 najstarszych bitów danych
    //czlon bajt & 0xF0 sprawi ze w rejestrze
    //umieszczona zostanie wartosc tymczasowa
    //w ktorej będą 4 najmłodsze bity
    PORT_LCD = (bajt & 0xF0)|(PORT_LCD & 0x0F);

    //potwiwerdznie wysłania danych(opadającym zboczem EN)
    PORT_LCD &= ~(_BV(EN_LCD));

    //zaczekaj cykl
    asm volatile ("nop");

    //ustawienie EN
    PORT_LCD |= _BV(EN_LCD);

    //wysłanie 4 młodszych bitów
    PORT_LCD = ((bajt & 0x0F)<<4)|(PORT_LCD & 0x0F);

    //potwierdzneie wysłania danych (opadającym zboczem EN)
    PORT_LCD &= ~(_BV(EN_LCD));

    //obowiązkowy czas
    _delay_us(40);
}

void wyswietl_LCD( char *napis)
{
    czysc_LCD();
    int8_t k=0;
    int8_t ile = strlen(napis);
    while(k<ile)
    {
        push_LCD(napis[k]);
        k++;
    }
}


#endif // INIT_H_INCLUDED

