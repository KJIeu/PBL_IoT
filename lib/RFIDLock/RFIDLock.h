#ifndef RFIDLock_h
#define RFIDLock_h

#include <Arduino.h>
#include "Relay.h"
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 9      //SDA
#define RST_PIN 8     //RST
#define LED_R 13 //define green LED pin
#define LED_G 12 //define red LED
#define LED_B 11 //define red LED
#define Relay_Lock_pin 40 //relay pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

class RFIDLock
{
    private:
        String content = "";
        String cards[20] = {"00 8E DF 87"};
        int numberOfCards = 1;
        bool isCardPresent();
        void readCard();
        void arraySwap(int i);
        void setColor(int green, int red, int blue);

    public:
        RFIDLock(/* args */);
        void init();
        void setOpen();
        bool checkCard();
        void addCard();
        void deleteCard();
        void setClosed();
        void setError();
};

#endif