#include "WaterLeakageControl.h"

Servo servo2;
bool waterTapPosition = true;

WaterLeakageControl::WaterLeakageControl(){}

void WaterLeakageControl::init()
{
    servo2.attach(Servo_pin);
}

bool WaterLeakageControl::checkWater()
{
    if( analogRead(Water_sensor_pin) > 300 && waterTapPosition) 
    {
        servo2.write(90);
        waterTapPosition = false;
        return false;
        
    }
    else
    {
        return true;
    }
}

void WaterLeakageControl::setWaterTapPosition()
{
    waterTapPosition = !waterTapPosition;
    if(waterTapPosition)
    {
        servo2.write(0);
    }
    else
    {
        servo2.write(90);
    }
}

bool WaterLeakageControl::getWaterTapPosition()
{
    return waterTapPosition;
}

