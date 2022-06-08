#ifndef GasLeakageControl_h
#define GasLeakageControl_h

#include <Arduino.h>
#include "MQ2.h"
#include "Servo.h"


#define MQ2_pin A0
#define Servo_pin 7


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