#include <Arduino.h>
#include <Wire.h>
#include "FastIMU.h"
#define BV(bit)                 (1 << (bit))
#define SetBit(byte, bit)       (byte |= BV(bit))
#define ClearBit(byte, bit)     (byte &= ~BV(bit))
#define ToggleBit(byte, bit)    (byte ^= BV(bit))


#define PWM_PIN     PD6         //D6
#define PWM_PORT    PORTD
#define PWM_DDR     DDRD

#define AIN2        PB1        //D9
#define AIN1        PB0        //D8
#define AIN_DDR     DDRB
#define AIN_PORT    PORTB

#define ServoPos    A0

//.5 - 10,5K rechts is naar boven

#define Links   false
#define Rechts  true

void init_PWM()
{
    //set fast PWM mode aan van timer0
    TCCR0A |= BV(WGM01) | BV(WGM00);
    TCCR0B &= ~BV(WGM02);

    //set Compare Output Mode van COM A
    TCCR0A |= BV(COM0A1)& ~BV(COM0A0);  //set OC0A pin laag op COM match en set OC0A pin hoog bij BOTTOM



    //set clock snelheid op clk/no prescale
   TCCR0B |= BV(CS00) & ~BV(CS01) & ~BV(CS02);


    //set standaard COM waarde AKA pulse breedte
    OCR0A = 127; //50% duty cycle



}

void SetMotor(char Speed, bool Dir)
{
    if(Speed)
    {
        OCR0A = Speed;
        SetBit(PWM_DDR, PWM_PIN);

        if(Dir == Rechts)
        {
            SetBit(AIN_PORT, AIN1);
            ClearBit(AIN_PORT, AIN2);


        }
        else
        {

            SetBit(AIN_PORT, AIN2);
            ClearBit(AIN_PORT, AIN1);

        }
    }
    else
    {
        ClearBit(PWM_DDR, PWM_PIN);
    }



}

void SetServoPosition(int Position, char speed) {
    int CurrentPos = analogRead(ServoPos);

    if(CurrentPos > Position) {
        SetMotor(speed, Links);
        do{CurrentPos = analogRead(ServoPos);}while(CurrentPos < Position);
        ClearBit(PWM_DDR, PWM_PIN);
        return;
    }
    else if(CurrentPos < Position) {
        SetMotor(speed, Rechts);
        do{CurrentPos = analogRead(ServoPos);}while(CurrentPos > Position);
        ClearBit(PWM_DDR, PWM_PIN);
        return;
    }
    else {
        return;
    }
}

void setup() {

    init_PWM();
    ClearBit(PWM_DDR, PWM_PIN);
    SetBit(AIN_DDR, AIN1);
    SetBit(AIN_DDR, AIN2);



}

void loop() {

    SetMotor(80, Links);
    //SetServoPosition(100, 80);

    delay(200);
    //SetMotor(80, Links);
    SetServoPosition(50, 80);

    delay(200);

}
