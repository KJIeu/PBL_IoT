#ifndef PlantAutowater_h
#define PlantAutowater_h

#include <Arduino.h>
#include "Relay.h"

//DHT sensor
#define SoilHumiditySensor_pin A2      
#define relayPin 9

class PlantAutowater
{
    private:
        
        bool workState = false; 
        //false => control doesn't works
        //true => works
        int targetHumidity = 20;
        int humidityBounds = 10;
        float currentHumidity = 0.0;
        bool relayState = false;


    public:
        PlantAutowater();
        void init();
        void setHumidity(int temperature);
        int getHumidity();
        void setBounds(int bound);
        int getBounds();
        void setWorkState(bool state);
        bool getWorkState();
        bool getRelayState();
        void control();
};

#endif