#ifndef WaterLeakageControl_h
#define WaterLeakageControl_h

#include <Arduino.h>
#include "Servo.h"

#define Water_sensor_pin A1
#define Servo_pin 8


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