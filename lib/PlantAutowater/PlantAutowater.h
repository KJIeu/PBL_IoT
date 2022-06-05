#ifndef PlantAutowater_h
#define PlantAutowater_h

#include <Arduino.h>
#include "MotorDriver298.h"
#include "Relay.h"

//DHT sensor
#define SoilHumiditySensor_pin A3      
#define PID_DUTY_CYCLE_MIN 0
#define PID_DUTY_CYCLE_MAX 100
#define bounds 3
#define pumpPin1 5
#define pumpPin2 4

class PlantAutowater
{
    private:
        
        bool workState = false; 
        //false => control doesn't works
        //true => works
        bool heaterState = false;
        int targetHumidity = 20;

        float pwmDutyCycle = 500;
        float currentHumidity = 0.0;
        //PID coefs
        float Kp = 300;
        float Ki = 10;
        float Kd = 900;

        float previousError = 0;
        float currentError = 0;
        float integralError = 0;
        float differentialError = 0;
        //--------------------------

        uint32_t timeCounterMs = 0;


    public:
        PlantAutowater();
        void init();
        void setHumidity(int temperature);
        void setWorkState(bool state);
        bool getWorkState();
        void control();
        int getHumidity();
};

#endif