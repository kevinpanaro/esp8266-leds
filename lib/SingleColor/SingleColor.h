#ifndef SingleColor_H
#define SingleColor_H

#include <ESP8266WebServer.h>
#include "Error.h"

class SingleColor
{

private:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    void setColor(String colorCode, uint8_t value);
    String buildValueOutOfRangeErrorMsg(String colorCode, uint8_t value) const;

public:
    SingleColor();
    SingleColor(ESP8266WebServer &server);
    uint8_t getRed() const;
    uint8_t getGreen() const;
    uint8_t getBlue() const;
    Error checkColorsValuesInRange() const;
    void send(ESP8266WebServer &server);
    String toString() const;
};

#endif
