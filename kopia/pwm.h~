#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED

void kierunek(int gdzie)
{
    if(gdzie == PRZOD)
    {
        go();
        OCR1A = 25;
        flag_kierunek = PRZOD;
    }
    else if(gdzie == TYL)
    {
        go();
        OCR1A = 10;
        flag_kierunek = TYL;
    }
    else
    {
        stop();
        flag_kierunek = STOP;
    }
}

void go()
{
    PORTB |= _BV(EN_PWM);
}

void stop()
{
    PORTB &= ~_BV(EN_PWM);
}
#endif // INIT_H_INCLUDED

