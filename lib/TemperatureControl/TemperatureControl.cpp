#include "TemperatureControl.h"

DHT dht(DHT_pin, DHT_type);
Relay relay(relayPin);
MotorDriver298 MotorDriver(motorPin1, motorPin2, motorPin3);


TemperatureControl::TemperatureControl(){}

void TemperatureControl::init()
{
    dht.begin();
    relay.init();
}

void TemperatureControl::setTemperature(int temperature)
{
    targetTemperature = temperature;
    
}

void TemperatureControl::setWorkState(bool state)
{
    workState = state;
    if(workState)
    {
        control();
    }
    else
    {
        MotorDriver.drive(true, 0);
        relay.relayOff();
    }
}

bool TemperatureControl::getWorkState()
{
  return workState;
}

void TemperatureControl::control()
{
    if(workState)
    {
        currentTemperature =  dht.readTemperature();
        if ((currentTemperature > targetTemperature + bounds) && heaterState)
        {
            relay.relayOff();
            heaterState = false;
        }

        if ((currentTemperature < targetTemperature - bounds) && !heaterState)
        {
            relay.relayOn();
            heaterState = true;
        }

        timeCounterMs = millis() - timeCounterMs;

        float timeCounterSec = (float)timeCounterMs / 1000;
        currentError = currentTemperature - targetTemperature;

        if (((((Ki * integralError) <= PID_DUTY_CYCLE_MAX) && currentError >= 0)) || 
            (((Ki * integralError) >= PID_DUTY_CYCLE_MIN) && currentError < 0))
        {
          integralError += currentError * timeCounterSec;
        }

        differentialError = (currentError - previousError) / timeCounterSec;
        pwmDutyCycle = Kp * currentError + Ki * integralError + Kd * differentialError;

        if (pwmDutyCycle < PID_DUTY_CYCLE_MIN)
        {
          pwmDutyCycle = PID_DUTY_CYCLE_MIN;
        }

        if (pwmDutyCycle > PID_DUTY_CYCLE_MAX)
        {
          pwmDutyCycle = PID_DUTY_CYCLE_MAX;
        }
        MotorDriver.drive(true, pwmDutyCycle);

        previousError = currentError;
    }
}

int TemperatureControl::getHumidity()
{
    return dht.readHumidity();
}

int TemperatureControl::getTemperature()
{
    return dht.readTemperature();
}
