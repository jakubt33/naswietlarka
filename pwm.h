#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED

void przyspiesz()
{
    uint16_t licznik=0;
    for(licznik=MIN_PWM; licznik<=MAX_PWM; licznik++)
    {
        OCR1A = licznik;
        _delay_ms(8);
    }
}

void spowolnij()
{
    uint16_t licznik=0;
    for(licznik=MAX_PWM; licznik>=MIN_PWM; licznik--)
    {
        OCR1A = licznik;
        _delay_ms(4);
    }

}

#endif // INIT_H_INCLUDED

