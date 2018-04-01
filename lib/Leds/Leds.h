#ifndef LEDS_H
#define LEDS_H

class Leds
{

private:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    void setColor(String colorCode, uint8_t value);

public:
    Leds();
    uint8_t getRed() const;
    uint8_t getGreen() const;
    uint8_t getBlue() const;
    void send(ESP8266WebServer &server);
    String toString() const;
    void singleColor(ESP8266WebServer &server);
};

#endif