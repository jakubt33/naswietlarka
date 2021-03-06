#ifndef HD44780_H_INCLUDED
#define HD44780_H_INCLUDED


void czysc_LCD_linia1()
{
    linia1();
    wyswietl_LCD("                    ");
    _delay_ms(2);
    linia1();
}
void czysc_LCD_linia2()
{
    linia2();
    wyswietl_LCD("                    ");
    _delay_ms(2);
    linia2();
}

void linia2()
{
    PORT_LCD &= ~(_BV(RS_LCD));
    push_LCD(0b10000000 | LINE2);
    PORT_LCD |= (_BV(RS_LCD));
    _delay_ms(2);
    //czekaj 1.64ms
}
void linia1()
{
    PORT_LCD &= ~(_BV(RS_LCD));
    push_LCD(0b10000000 | LINE1);
    PORT_LCD |= (_BV(RS_LCD));
    _delay_ms(2);
    //czekaj 1.64ms
}
void gen_char(char *ch, int *i)
{
    if(*i>999)
    {
        *i = 0;
    }
    else if(*i<0)
    {
        *i = 999;
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
    else if(*i<1000)
    {
        ch[0] = (*i/100 + '0');
        ch[1] = ((*i%100)/10 + '0');
        ch[2] = (*i%10 + '0');
        ch[3] = '\0';
    }
}

void gen_char_time(char *ch, volatile int *i)
{
    if(*i>999)
    {
        *i = 0;
    }
    else if(*i<0)
    {
        *i = 999;
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
    else if(*i<1000)
    {
        ch[0] = (*i/100 + '0');
        ch[1] = ((*i%100)/10 + '0');
        ch[2] = (*i%10 + '0');
        ch[3] = '\0';
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
    int8_t k=0;
    int8_t ile = strlen(napis);
    while(k<ile)
    {
        push_LCD(napis[k]);
        k++;
    }
}


#endif // INIT_H_INCLUDED

