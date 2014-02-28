#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED

void kierunek(int gdzie)
{
    if(gdzie == PRZOD)
    {
        go();
        OCR1A = 25;
    }
    else if(gdzie == TYL)
    {
        go();
        OCR1A = 10;
    }
    else
    {
        stop();
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

