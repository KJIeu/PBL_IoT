#include <Arduino.h>

//Climat control
#include "TemperatureControl.h"


//Gas leakage
#include "MQ2.h"

TemperatureControl temperatureControl();



void setup() { 
    //temperatureControl.init();
    
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

    3)  RFID lock                       (middle)
        a)  RFID panel
        b)  electromagnetic lock

    4)  Water leakage                   (easy)
        a)  water detector
        b)  servo

    5)  Gas leakage                     (easy)
        a)  gas detector
        b)  servo
*/

//TO BUY LIST:
/*
    1)  sourse of power
    2)  L298 (or other) motor driver
    3)  electromagnetic lock(solenoid)

*/