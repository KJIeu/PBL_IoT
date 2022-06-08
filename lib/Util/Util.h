#ifndef Util_h
#define Util_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include "SoftwareSerial.h"

void sendDataToEsp(int *sensorValues, SoftwareSerial &esp);

#endif