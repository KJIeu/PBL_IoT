#include "GasLeakageControl.h"

MQ2 mq2(MQ2_pin);
Servo servo;

GasLeakageControl::GasLeakageControl(){}

void GasLeakageControl::init()
{
    servo.attach(Servo_pin);
    mq2.begin();
}

bool GasLeakageControl::checkCO()
{
    Serial.print("CO state: ");
    Serial.println(analogRead(mq2.readCO()));
    if( mq2.readCO() > 30.0 ) 
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool GasLeakageControl::checkSmoke()
{
    Serial.print("Smoke state: ");
    Serial.println(analogRead(mq2.readSmoke()));
    if( mq2.readSmoke() > 101.0 ) 
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool GasLeakageControl::checkLPG()
{
    Serial.print("LPG state: ");
    Serial.println(analogRead(mq2.readLPG()));
    if( mq2.readLPG() > 5622.5 ) 
    {
        servo.write(90);
        return false;
    }
    else
    {
        return true;
    }
}