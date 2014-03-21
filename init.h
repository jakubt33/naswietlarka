#ifndef INIT_H_INCLUDED
#define INTI_H_INCLUDED

void init_LCD()
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

void init_PWM()
{
    DDRB |= _BV(PWM); //tu jest PWM na timerze 2
    DDRB |= _BV(EN_PWM); // odcinasz napiecia na serwie

    TCCR1A |= (0<<WGM11)|(1<<WGM10)|(1<<COM1A1)|(0<<COM1A0);
    TCCR1B |= (0<<WGM13)|(1<<WGM12)|(1<<CS12)|(0<<CS11)|(0<<CS10);
    // WGM1x - fast PWM, 8 bit, TOP-0x00FF,
    // Update of OCR1A-Bottom, TOV1 flag set on TOP (tabble 39)
    // CS1x - 256 preskaler (TABLE 40)
}

void init_Switch()
{
    DDR_SWITCH &= ~(_BV(SWITCH_UP));
    DDR_SWITCH &= ~(_BV(SWITCH_DOWN));
    DDR_SWITCH &= ~(_BV(SWITCH_OK));
    DDR_SWITCH &= ~(_BV(KRANC));

    PORT_SWITCH |= _BV(SWITCH_UP);
    PORT_SWITCH |= _BV(SWITCH_DOWN);
    PORT_SWITCH |= _BV(SWITCH_OK);
    PORT_SWITCH |= _BV(KRANC);

    //krancowka bezpeiczenstwa
    MCUCR |= (1<<ISC11)|(1<<ISC10); // low level genereates interrupt
    GICR |= (1<<INT1);
}

void init_Buzzer()
{
    DDR_BUZZER |= _BV(BUZZER);
    buzzer_off();
}

void init_Timer()
{
    TCCR0 |= (1<<CS02)|(0<<CS01)|(1<<CS00); //preskaler 1024
    TIMSK |= (1<<TOIE0); //ovf int enable
}

void buzzer_off()
{
    PORT_BUZZER &= ~_BV(BUZZER);
}

void buzzer_on()
{
    PORT_BUZZER |= _BV(BUZZER);
}

void init_Relay()
{
    DDR_RELAY |= _BV(RELAY);
    relay_off();
}

void relay_off()
{
    PORT_RELAY &= ~_BV(RELAY);
}

void relay_on()
{
    PORT_RELAY |= _BV(RELAY);
}


#endif // INIT_H_INCLUDED

