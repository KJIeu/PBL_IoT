#include "PlantAutowater.h"

MotorDriver298 MotorDriver(pumpPin1, pumpPin2);


PlantAutowater::PlantAutowater(){}

void PlantAutowater::init()
{
    
}

void PlantAutowater::setHumidity(int humidity)
{
    targetHumidity = humidity;
    
}

void PlantAutowater::setWorkState(bool state)
{
    workState = state;
    if(workState)
    {
        control();
    }
    else
    {
        MotorDriver.drive(true, 0);
    }
}

bool PlantAutowater::getWorkState()
{
  return workState;
}

void PlantAutowater::control()
{
    if(workState)
    {
        currentHumidity =  dht.readHumidity();
        if ((currentHumidity > targetHumidity + bounds) && heaterState)
        {
            relay.rela
            heaterState = false;
        }

        if ((currentHumidity < targetHumidity - bounds) && !heaterState)
        {
            relay.relayOn();
            heaterState = true;
        }

        timeCounterMs = millis() - timeCounterMs;

        float timeCounterSec = (float)timeCounterMs / 1000;
        currentError = currentHumidity - targetHumidity;

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

int PlantAutowater::getHumidity()
{
    return analogRead(SoilHumiditySensor_pin);
}



