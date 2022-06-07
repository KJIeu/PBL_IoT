#ifndef RFIDLock_h
#define RFIDLock_h

#include <Arduino.h>
#include "Relay.h"
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_R 13 //define green LED pin
#define LED_G 12 //define red LED
#define LED_B 11 //define red LED
#define Relay_Lock_pin 0 //relay pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

class RFIDLock
{
    private:
        String content = "";
        String cards[20] = {"XX XX XX XX"};
        int numberOfCards = 1;
        bool isCardPresent();
        void readCard();
        void arraySwap(int i);
        void setOpen();
        void setColor(int green, int red, int blue);

    public:
        RFIDLock(/* args */);
        void init();
        bool checkCard();
        void addCard();
        void deleteCard();
        void setClosed();
        void setError();
};

#endif