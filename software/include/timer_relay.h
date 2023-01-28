#include <Arduino.h>
#define pin_buzzer 2
#define pin_positivo 5
#define pin_onoff 1
#define pin_negativo 0
#define pin_rele 14
#define pin_ledmarcha 15

#define pin_A1 9
#define pin_B1 11
#define pin_C1 12
#define pin_D1 13

#define pin_A2 3
#define pin_B2 7
#define pin_C2 8
#define pin_D2 6

#define PRESCALER *((volatile uint8_t*) 0x00530E)
#define CCR2L *((volatile uint8_t*) 0x005316)
#define CCR2H *((volatile uint8_t*) 0x005315)

bool fl_positivo = false;
bool fl_negativo = false;
bool fl_onoff=false;
bool marcha= false;
byte valor_led1 =0;
byte valor_led2 =0;
byte contador = 0;
double tiempoant = 0;

void escribe( byte led2, byte led1);