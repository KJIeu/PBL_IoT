#include <Arduino.h>

#include "TemperatureControl.h"
#include "GasLeakageControl.h"
#include "WaterLeakageControl.h"

//Climat control
TemperatureControl temperatureControl;
//Gasleakage control
GasLeakageControl gasLeakageControl;
//water leakage control
WaterLeakageControl waterLeakageControl;


void setup() { 
    temperatureControl.init();
    gasLeakageControl.init();
    waterLeakageControl.init();
}

void loop() {
  // put your main code here, to run repeatedly:
}




//TO DO:
/*
    1)  wifi shield esp8266 connection  (hard)

    2)  Climate control                 DONE
        a)  DHT11 sensor                +
        b)  fan control                 +
        c)  heater element control      +
        d)  PID temperature control     +

    3)  RFID lock                       (middle)
        a)  RFID panel
        b)  electromagnetic lock

    4)  Water leakage                   DONE
        a)  water detector              +
        b)  servo                       +

    5)  Gas leakage                     DONE
        a)  gas detector                +
        b)  servo                       +

    6)  Plant autowater                 DONE
        a)  soil water detector         +
        b)  water pump                  +
        c)  PID water control           +

    7)  realize EEPROM                  (hard++)
        (energoindependent memory)

*/

//TO BUY LIST:
/*

    3)  electromagnetic lock(solenoid)

*/