#include "RFIDLock.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Relay relay_Lock(Relay_Lock_pin);

RFIDLock::RFIDLock()
{}

void RFIDLock::init()
{
    Serial.begin(9600);   // Initiate a serial communication
    SPI.begin();          // Initiate  SPI bus
    mfrc522.PCD_Init(); 
    relay_Lock.init();
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    setClosed();
}

void RFIDLock::readCard()
{
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
        //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        //Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    //Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    Serial.println(content);
}

bool RFIDLock::isCardPresent()
{
    return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}

bool RFIDLock::checkCard()
{
    if(isCardPresent())
    {
        readCard();

        for(int i = 0; i < numberOfCards; i++)
                if (content.substring(1) == cards[i]) 
                {
                    //Serial.println("Authorized access");
                    setOpen();
                    content = "";
                    return true;
                }
        
        content = "";
        setError();
    }

    return false;
}

void RFIDLock::addCard()
{
    readCard();
    cards[numberOfCards] = content;
    numberOfCards++;
    setOpen();
}

void RFIDLock::deleteCard()
{
    readCard();
    for(int i = 0; i < numberOfCards; i++)
        if (content.substring(1) == cards[i]) 
        {
            //Serial.println("Authorized access");
            numberOfCards--;
            arraySwap(i);
            content = "";
            break;
        }
    
    content = "";
}

void RFIDLock::arraySwap(int i)
{
    for(i; i < numberOfCards; i++)
        cards[i] = cards[i++];
}

void RFIDLock::setOpen()
{
    relay_Lock.relayOn();
    setColor(0, 255, 0);
}

void RFIDLock::setClosed()
{
    relay_Lock.relayOff();
    setColor(0, 0, 255);
}

void RFIDLock::setError()
{
    setColor(255, 0, 0);
}

void RFIDLock::setColor( int red, int green, int blue)
{
    analogWrite(LED_R, red);
    analogWrite(LED_G, green);
    analogWrite(LED_B, blue);
}