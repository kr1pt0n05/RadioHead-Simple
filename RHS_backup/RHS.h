#ifndef RHC_H
#define RHC_H

#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h> // needed for RH_ASK

#define PAYLOAD_COMMAND_LENGTH 4
#define PAYLOAD_TEMPERATURE_LENGTH 5
#define PAYLOAD_LENGTH 9

struct Payload{
    char type[8];
    char temp[8];
};

class RHS{
public:
    Payload payload;
    RHS(uint16_t speed = 2000, uint8_t rxPin = 2, uint8_t txPin = 12);
    bool init();
    void sendTemperature(float tmp); // used for sending Temperature to Master Arduino
    void sendInstruction(float tmp); // used for instructing Slave Arduino to regulate temperature
    bool received();

private:
    RH_ASK driver;
};

#endif