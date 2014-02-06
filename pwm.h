#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED

#define PWM 1
#define MIN_PWM 20
#define MAX_PWM 255

void PWM_Init()
{
    DDRB |= _BV(PWM); //tu jest PWM na timerze 2

    TCCR1A |= (0<<WGM11)|(1<<WGM10)|(1<<COM1A1)|(0<<COM1A0);
    TCCR1B |= (0<<WGM13)|(1<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10);
    // WGM1x - fast PWM, 8 bit, TOP-0x00FF,
    // Update of OCR1A-Bottom, TOV1 flag set on TOP (tabble 39)
    // CS1x - no prescaling (TABLE 40)
}

void przyspiesz()
{
    uint16_t licznik=0;
    for(licznik=MIN_PWM; licznik<=MAX_PWM; licznik++)
    {
        OCR1A = licznik;
        _delay_ms(16);
    }
}
void spowolnij()
{
    uint16_t licznik=0;
    for(licznik=MAX_PWM; licznik>=MIN_PWM; licznik--)
    {
        OCR1A = licznik;
        _delay_ms(16);
    }

}
#endif // INIT_H_INCLUDED

