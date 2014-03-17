#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED


#define F_CPU 4000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

int flag_kierunek = 0;

//MAIN
#define NIE 0
#define TAK 1

#define PRZOD 1
#define TYL -1
#define STOP 0

int ilosc_petli();
void wykonaj (int ile_petli);
void beep();
void pozycjonowanie();
//

//INIT
#define DDR_BUZZER DDRD
#define PORT_BUZZER PORTD
#define BUZZER PD6

#define RELAY PD7
#define PORT_RELAY PORTD
#define DDR_RELAY DDRD

void init_LCD();
void init_PWM();
void init_Switch();

void init_Buzzer();
void buzzer_off();
void buzzer_on();

void init_ralay();
void relay_on();
void relay_off();
//

//PWM
#define PWM 1
#define EN_PWM 0
#define MIN_PWM 20
#define MAX_PWM 255

void kierunek(int gdzie);
void go();
void stop();
//

//SWITCHES
#define PIN_SWITCH PINC
#define KRANC PC0
#define SWITCH_UP PC1
#define SWITCH_DOWN PC2
#define SWITCH_OK PC3
#define DDR_SWITCH DDRC
#define PORT_SWITCH PORTC
//

//LCD
#define DDR_LCD DDRB
#define PORT_LCD PORTB
#define RS_LCD 2
#define EN_LCD 3
#define DB4_LCD 4
#define DB5_LCD 5
#define DB6_LCD 6
#define DB7_LCD 7

void czysc_LCD();
void gen_char(char *ch, int *i);
void push_LCD( int8_t bajt ) ;
void wyswietl_LCD( char *napis);
//


#endif // DEFINES_H_INCLUDED

