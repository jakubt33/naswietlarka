#ifndef HD44780_H_INCLUDED
#define HD44780_H_INCLUDED

#define DDR_LCD DDRB
#define PORT_LCD PORTB
#define RS_LCD 2
#define EN_LCD 3
#define DB4_LCD 4
#define DB5_LCD 5
#define DB6_LCD 6
#define DB7_LCD 7

void wlacz_LCD();
void wyswietl_LCD( char *napis);
void czysc_LCD();
void push_LCD( int8_t bajt ) ;

void wlacz_LCD()
{
    //ustawienie kierunku wyjssciowego linii podłączonych do LCD
    DDR_LCD = (0xF0)|(1<<RS_LCD)|(1<<EN_LCD);

    //stan niski na liniach
    PORT_LCD = 0;

    //zaczekaj 45ms na ustabilizowanie napiecia
    _delay_ms(45);

    //1
    //ustaw linie EN
    PORT_LCD |= (1<<EN_LCD);
    //zaladuj sekwencje 0011
    PORT_LCD |= (1<<DB4_LCD)|(1<<DB5_LCD);
    //potwierdzneie opadającym zboczem EN
    PORT_LCD &= ~(_BV(EN_LCD));
    //zaczekaj 4.1ms
    _delay_ms(4.1);

    //2
    //ustaw linie EN
    PORT_LCD |= (1<<EN_LCD);
    //potwierdzneie opadającym zboczem EN
    PORT_LCD &= ~(_BV(EN_LCD));
    //zaczekaj 100us
    _delay_us(100);

    //3
    //ustaw linie EN
    PORT_LCD |= (1<<EN_LCD);
    //potwierdzneie opadającym zboczem EN
    PORT_LCD &= ~(_BV(EN_LCD));
    //zaczekaj 100us
    _delay_us(100);

    //4
    //ustaw linie EN
    PORT_LCD |= (1<<EN_LCD);
    //ustawienie interfejsu 4-bitowego
    PORT_LCD &= ~(_BV(DB4_LCD));
    //potwierdz opadajacym zboczem EN
    PORT_LCD &= ~(_BV(EN_LCD));

    //ustaw parametry wyswietlacza
    //bit 4 = 0 (slowo danych ma 4 bity)
    //bit 3 = 1 (2 wiersze znaków )
    //bit 2 = 0 (matryca 5x8 pikseli)
    PORT_LCD &= ~(_BV(RS_LCD));
    push_LCD(0b00101000);
    PORT_LCD |= _BV(RS_LCD);

    //ustaw tryb pracy wyswietlacza
    //bit 2 = 1 (inkrementowanie adresy zapisu danych)
    //bit 1 = 1 (wyłącznie przesuwania w prawo)
    PORT_LCD &= ~(_BV(RS_LCD));
    push_LCD(0b00000110);
    PORT_LCD |= _BV(RS_LCD);

    //włacz wyswietlacz
    //bit 2 = 1 (właczenie wyswietlania)
    //bit 1 = 1 (kursor aktywny)
    //bit 0 = 0 )kursor nie miga);
    PORT_LCD &= ~(_BV(RS_LCD));
    push_LCD(0b00001110);
    PORT_LCD |= _BV(RS_LCD);

    czysc_LCD();

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

void czysc_LCD()
{
    PORT_LCD &= ~(_BV(RS_LCD));
    push_LCD(1);
    PORT_LCD |= (_BV(RS_LCD));
    //czekaj 1.64ms
    _delay_ms(1.64);

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
#endif // INIT_H_INCLUDED

