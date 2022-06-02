#ifndef TemperatureControl_h
#define TemperatureControl_h

#include <Arduino.h>
#include "DHT.h"
#include "MotorDriver298.h"
#include "Relay.h"

//DHT sensor
#define DHT_pin 2       //Pin for DHT sensor
#define DHT_type DHT11  //type of dht sensor
#define PID_DUTY_CYCLE_MIN 0
#define PID_DUTY_CYCLE_MAX 100
#define bounds 3
#define relayPin 7     //Pin for Relay-heater
#define motorPin1 5
#define motorPin2 4
#define motorPin3 3

class TemperatureControl
{
    private:
        
        bool workState = false; 
        //false => control doesn't works
        //true => works
        bool heaterState = false;
        int targetTemperature = 20;

        float pwmDutyCycle = 500;
        float currentTemperature = 0.0;
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
        TemperatureControl();
        void init();
        void setTemperature(int temperature);
        void setWorkState(bool state);
        bool getWorkState();
        void control();
        int getTemperature();
        int gettHumidity();
};

#endif