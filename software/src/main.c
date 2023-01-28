#include <Arduino.h>
#include "timer_relay.h"


void escribe( byte led2, byte led1)
{

digitalWrite(pin_A1, bitRead(led1,0));
digitalWrite(pin_B1, bitRead(led1,1));
digitalWrite(pin_C1, bitRead(led1,2));
digitalWrite(pin_D1, bitRead(led1,3));
digitalWrite(pin_A2, bitRead(led2,0));
digitalWrite(pin_B2, bitRead(led2,1));
digitalWrite(pin_C2, bitRead(led2,2));
digitalWrite(pin_D2, bitRead(led2,3));

}


void setup()
{
    pinMode(pin_negativo, INPUT_PULLUP);
    pinMode(pin_onoff, INPUT_PULLUP);
    pinMode(pin_positivo, INPUT_PULLUP);

    PRESCALER = 0x06;
    CCR2L = 0b11111010;
    CCR2H = 0b00000000;

    pinMode(pin_buzzer, OUTPUT);
    pinMode(pin_ledmarcha, OUTPUT);
    pinMode(pin_rele, OUTPUT);
    digitalWrite(pin_rele, LOW);

    pinMode(pin_A1, OUTPUT);
    pinMode(pin_B1, OUTPUT);
    pinMode(pin_C1, OUTPUT);
    pinMode(pin_D1, OUTPUT);

    pinMode(pin_A2, OUTPUT);
    pinMode(pin_B2, OUTPUT);
    pinMode(pin_C2, OUTPUT);
    pinMode(pin_D2, OUTPUT); 
    
    //Serial.begin(9600);
}
void loop()
{  
    while(digitalRead(pin_positivo)== false)
    {
        fl_positivo = true;
        delay(50);
    }

    //Serial.println("fl_positivo");  
    while(digitalRead(pin_negativo)== false)
    {
        fl_negativo= true;
        delay(50);
    } 

    //Serial.println("fl_negativo");
    while(digitalRead(pin_onoff)== false)
    {
    fl_onoff = true;
    delay(50);
    }

    if(fl_positivo)
    {
        if(valor_led2==9)
        {
            if(valor_led1==9)
            {
                valor_led1=valor_led2=0;
            }
            else
            {
                valor_led1++;
            }
        }
        else
        {
            if(valor_led1==9)
            {
                valor_led2++;
                valor_led1=0;
            }
            else
            {
            valor_led1++;
            }
        }
        contador ++;

        if(contador ==100)
            contador = 0;
        

        fl_positivo=false;
        //Serial.print(" Contador: ");
        //Serial.print(valor_led2);
        //Serial.println(valor_led1);
    }

    if(fl_negativo)
    {
        if(valor_led2==0)
        {
            if(valor_led1!=0)
                valor_led1--;        
        }
        else
        {
            if(valor_led1==0)
            {
                valor_led2--;
                valor_led1=9;
            }
            else
            {
                valor_led1--;
            }
        }
        contador --;
        if(contador ==255)
            contador = 0;
        
        
        fl_negativo=false;

        //Serial.print(" Contador: ");
        //Serial.print(valor_led2);
        //Serial.println(valor_led1);
    }
   
    if(fl_onoff)
    {
        if(marcha || contador == 0)
        {
            marcha=false;             
        }
        else
        {
            marcha=true;              
        }        
            
        fl_onoff=false;
        analogWrite(pin_buzzer, 127);
        delay(500);
        analogWrite(pin_buzzer, 0);        
    }

    if(marcha==true)
    {
        if(contador ==0)
        {
            marcha =false;
            analogWrite(pin_buzzer, 125);
            delay(500);
            analogWrite(pin_buzzer, 0);            
        }
        else
        {
            digitalWrite(pin_rele, HIGH);
            //Serial.println("Temporizando");
        }
        
        if(millis()-tiempoant > 60000)
        {
            fl_negativo = true;
            tiempoant=millis();
        }
        //Serial.print("Contador = ");
        //Serial.println(contador);
        digitalWrite(pin_ledmarcha, LOW);


    }
    else
    {
        //Serial.println(" Paré ");
        digitalWrite(pin_rele, LOW);
        digitalWrite(pin_ledmarcha, HIGH);
        tiempoant = millis();
    }

    escribe(valor_led2 , valor_led1);

}