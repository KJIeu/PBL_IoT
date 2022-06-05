#ifndef WaterLeakageControl_h
#define WaterLeakageControl_h

#include <Arduino.h>
//#include ""
#include "Servo.h"

#define Water_sensor_pin A4
#define Servo_pin 10


class WaterLeakageControl
{
    private:

    public:
        WaterLeakageControl();
        void init();
        bool checkWater();
        void setWaterTapPosition();
        bool getWaterTapPosition();
};

#endif