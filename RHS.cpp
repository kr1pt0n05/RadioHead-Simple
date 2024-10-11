#include <RHC.h>

RHC::RHC(uint16_t speed = 2000, uint8_t rxPin = 2, uint8_t txPin = 12)
: driver(speed, rxPin, txPin){
}

bool RHC::init(){
    return driver.init();
}

void RHC::sendTemperature(float tmp){
    char msg[16];
    char floatStr[8];

    strcpy(msg, "TEMP");
    dtostrf(tmp, 5, 2, floatStr);
    strcat(msg, floatStr);

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
}

bool RHC::received(){
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
