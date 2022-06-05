#ifndef GasLeakageControl_h
#define GasLeakageControl_h

#include <Arduino.h>
#include "MQ2.h"
#include "Servo.h"


#define MQ2_pin A5
#define Servo_pin 6


class GasLeakageControl
{
    private:

    public:
        GasLeakageControl();
        void init();
        bool checkCO();
        bool checkLPG();
        bool checkSmoke();
};

#endif