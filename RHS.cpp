#include <RHS.h>

RHS::RHS(uint16_t speed = 2000, uint8_t rxPin = 2, uint8_t txPin = 12)
: driver(speed, rxPin, txPin){
}

bool RHS::init(){
    return driver.init();
}

void RHS::sendTemperature(float tmp){
    char msg[16];
    char floatStr[8];

    strcpy(msg, "TEMP");
    dtostrf(tmp, 5, 2, floatStr);
    strcat(msg, floatStr);

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
}

bool RHS::received(){
    char buffer[16];
    uint8_t buflen = sizeof(buffer);

    if(driver.recv((uint8_t*)buffer, &buflen)){
        strncpy(payload.type, buffer, 4);
        payload.type[4] = '\0';

        strncpy(payload.temp, buffer+4, 5);
        payload.temp[5] = '\0';
        
        return true;
    }
    return false;
}
