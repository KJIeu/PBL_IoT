#include "util.h"

void sendDataToEsp(int *sensorValues, SoftwareSerial &esp)
{
    // Construct json
    StaticJsonDocument<64> doc;

    doc["field1"] = String(sensorValues[0]);
    doc["field2"] = String(sensorValues[1]);
    doc["field3"] = String(sensorValues[2]);
    doc["field4"] = String(sensorValues[3]);
    char buffer[64];
    serializeJson(doc, buffer);
    // Print it to the esp serial monitor
    Serial.println("Sending to esp: ");
    Serial.println(buffer);
    esp.print(buffer);
}
