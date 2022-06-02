#include "GasLeakageControl.h"

MQ2 mq2(MQ2_pin);
Servo servo;

GasLeakageControl::GasLeakageControl(){}

void GasLeakageControl::begin()
{
    servo.attach(Servo_pin);
    mq2.begin();
}

bool GasLeakageControl::checkCO()
{
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