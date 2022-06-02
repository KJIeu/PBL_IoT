#ifndef GasLeaKageControl_h
#define GasLeaKageControl_h

#include <Arduino.h>
#include "MQ2.h"
#include "Servo.h"


#define MQ2_pin A5
#define Servo_pin 6


class GasLeaKageControl
{
    private:

    public:
        GasLeaKageControl();
        void begin();
        bool checkCO();
        bool checkLPG();
        bool checkSmoke();
};

#endif