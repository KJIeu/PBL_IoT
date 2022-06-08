#include <Arduino.h>

#include "TemperatureControl.h"
#include "GasLeakageControl.h"
#include "WaterLeakageControl.h"
#include "PlantAutowater.h"
#include "RFIDLock.h"
#include "SoftwareSerial.h"
#include "Util.h"

#define TIMING 60000 // one minute TIMING

// RFID Lock
RFIDLock lock;
// Climat control
TemperatureControl temperatureControl;
// Gasleakage control
GasLeakageControl gasLeakageControl;
// water leakage control
WaterLeakageControl waterLeakageControl;
// Plant autowater
PlantAutowater plantAutowater;
// Esp for communication
#define RX_PIN 17
#define TX_PIN 16
#define BAUD_RATE 9600
SoftwareSerial esp(RX_PIN, TX_PIN);

// gas states
bool LPGState = true;
bool COState = true;
bool smokeState = true;

// water state
bool waterState = true;

bool doorState = false; // false - closed, true - open

unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;
unsigned long previousTime3 = 0;
unsigned long lockTime = 0;
unsigned long timeSent = 0;

int sensorValues[4];

// function definitions
void autonomousOperationMode();
void onlineOperationMode();
void updateSensorValues();
void parseData(String s);

void setup()
{
    Serial.begin(BAUD_RATE);
    esp.begin(BAUD_RATE);
    temperatureControl.init();
    gasLeakageControl.init();
    waterLeakageControl.init();
    plantAutowater.init();
    lock.init();
}

void loop()
{
    onlineOperationMode();
    autonomousOperationMode();
}

void updateSensorValues()
{
    sensorValues[0] = temperatureControl.getTemperature();
    sensorValues[1] = temperatureControl.getHumidity();
    sensorValues[2] = gasLeakageControl.checkCO() || gasLeakageControl.checkLPG() || gasLeakageControl.checkSmoke();
    sensorValues[3] = waterLeakageControl.checkWater();
}

void parseDataAndUpdateActuatorValues(String s)
{
    String delimiter = "-";
    size_t buffer_size = s.length();
    char buffer[buffer_size];
    s.toCharArray(buffer, buffer_size);

    temperatureControl.setWorkState(String(strtok(buffer, "-")).toInt());
    doorState = String(strtok(NULL, "-")).toInt();
    bool gasStatus = String(strtok(NULL, "-")).toInt();   // to change
    bool waterStatus = String(strtok(NULL, "-")).toInt(); // to change
    temperatureControl.setTemperature(String(strtok(NULL, "-")).toInt()); 
    plantAutowater.setHumidity(String(strtok(NULL, "-")).toInt());
}

void onlineOperationMode()
{
    String payload = "";

    if (millis() - timeSent > TIMING)
    {
        timeSent = millis();
        updateSensorValues();
        sendDataToEsp(sensorValues, esp);
    }

    while (esp.available())
    {
        payload += esp.readString();
    }

    if (payload.length() > 0)
    {
        if (payload.indexOf("CONNECTION") > 0)
        {
            payload = "";
            return;
        }
        else
        {
            Serial.println(payload);
            parseDataAndUpdateActuatorValues(payload);
            payload = "";
        }
    }
}

void autonomousOperationMode()
{
    delay(1000);
    LPGState = gasLeakageControl.checkLPG();
    COState = gasLeakageControl.checkCO();
    smokeState = gasLeakageControl.checkSmoke();
    waterState = waterLeakageControl.checkWater();

    if (lock.checkCard())
    {
        doorState = true;
        lockTime = millis() + TIMING;
    }

    if (doorState && lockTime <= millis())
    {
        lock.setClosed();
    }

    /*if (plantAutowater.getRelayState())
    {
        plantAutowater.control();
    }

    if (millis() - previousTime1 >= TIMING)
    {
        previousTime1 = millis();
        LPGState = gasLeakageControl.checkLPG();
        COState = gasLeakageControl.checkCO();
        smokeState = gasLeakageControl.checkSmoke();
        waterState = waterLeakageControl.checkWater();
    }

    /*if (millis() - previousTime2 >= TIMING * 5)
    {
        previousTime1 = millis();
        temperatureControl.control();
    }

    if (millis() - previousTime1 >= TIMING * 30)
    {
        previousTime3 = millis();
        plantAutowater.control();
    }*/
}

// TO DO:
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