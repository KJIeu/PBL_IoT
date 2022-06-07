#include <Arduino.h>

#include "TemperatureControl.h"
#include "GasLeakageControl.h"
#include "WaterLeakageControl.h"
#include "PlantAutowater.h"
#include "RFIDLock.h"

#define timing 60000 //one minute timing

//RFID Lock
RFIDLock lock;
//Climat control
TemperatureControl temperatureControl;
//Gasleakage control
GasLeakageControl gasLeakageControl;
//water leakage control
WaterLeakageControl waterLeakageControl;
//Plant autowater
PlantAutowater plantAutowater;

//gas states
bool LPGState = true;
bool COState = true;
bool smokeState = true;

//water state
bool waterState = true;

bool doorState = false; //false - closed, true - open

unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;
unsigned long previousTime3 = 0;
unsigned long lockTime = 0;

void autonomousOperationMode();

void setup() { 
    temperatureControl.init();
    gasLeakageControl.init();
    waterLeakageControl.init();
    plantAutowater.init();
    lock.init();
}

void loop() {
    autonomousOperationMode();
}


void autonomousOperationMode()
{
    if(lock.checkCard())
    {
        doorState = true;
        lockTime = millis() + timing;
    }

    if(doorState && lockTime <= millis())
    {
        lock.setClosed();
    }

    if (plantAutowater.getRelayState())
    {
        plantAutowater.control();
    }

    if (millis() - previousTime1 >= timing)
    {
        previousTime1 = millis();
        LPGState = gasLeakageControl.checkLPG();
        COState = gasLeakageControl.checkCO();
        smokeState = gasLeakageControl.checkSmoke();
        waterState = waterLeakageControl.checkWater();
    }

    if (millis() - previousTime2 >= timing * 5)
    {
        previousTime1 = millis();
        temperatureControl.control();
    }

    if (millis() - previousTime1 >= timing * 30)
    {
        previousTime3 = millis();
        plantAutowater.control();
    }
}



//TO DO:
/*
    1)  wifi shield esp8266 connection  (hard)

    2)  Climate control                 DONE
        a)  DHT11 sensor                +
        b)  fan control                 +
        c)  heater element control      +
        d)  PID temperature control     +

    3)  RFID lock                       DONE
        a)  RFID panel                  +
        b)  electromagnetic lock        +

    4)  Water leakage                   DONE
        a)  water detector              +
        b)  servo                       +

    5)  Gas leakage                     DONE
        a)  gas detector                +
        b)  servo                       +

    6)  Plant autowater                 DONE
        a)  soil water detector         +
        b)  water pump                  +

    7)  realize EEPROM                  (hard++)
        (energoindependent memory)

*/