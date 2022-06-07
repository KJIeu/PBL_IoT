#include "PlantAutowater.h"

Relay relayPump(relayPin);


PlantAutowater::PlantAutowater(){}

void PlantAutowater::init()
{
    relayPump.init();
}

void PlantAutowater::setHumidity(int humidity)
{
    targetHumidity = humidity;
    
}

int PlantAutowater::getHumidity()
{
    return analogRead(SoilHumiditySensor_pin);
}

void PlantAutowater::setBounds(int bound)
{
    humidityBounds = bound;
    
}

int PlantAutowater::getBounds()
{
    return humidityBounds;
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
        relayPump.relayOff();
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
        currentHumidity =  getHumidity();

        if ((currentHumidity < targetHumidity - (targetHumidity*humidityBounds/100)))
        {
            if(!relayState)
            {
            relayPump.relayOn();
            relayState = true;
            }
        }

        if ((currentHumidity >= targetHumidity + (targetHumidity*humidityBounds/100)))
        {
            relayPump.relayOff();
            relayState = false;
        }

    
    }
}




