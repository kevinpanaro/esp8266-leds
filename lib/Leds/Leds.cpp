#include <ESP8266WebServer.h>
#include <stdexcept>
#include "Leds.h"
Leds::Leds(){
    red = 0;
    green = 0;
    blue = 0;
}

uint8_t Leds::getRed() const{
    return red;
}
uint8_t Leds::getGreen() const{
    return green;
}
uint8_t Leds::getBlue() const{
    return blue;
}


void Leds::setColor(String colorCode, uint8_t value){
    if(colorCode == "r") red = value;
    else if(colorCode == "g") green = value;
    else if(colorCode == "b") blue = value;
}

void Leds::singleColor(ESP8266WebServer &server){
    const char *rgbNames[] = {"r", "g", "b"};
    for(int i = 0; i < 3; i++)
        if(server.hasArg(rgbNames[i])){
            int value = server.arg(rgbNames[i]).toInt();
            if(value < 0 || value > 255){
                String error = "Illegal value:\n\n";
                error += rgbNames[i];
                error += "=";
                error += server.arg(rgbNames[i]);
                error += "\nOnly values 0 to 255 are allowed. 0 is off and 255 is 100% lit";
//                throw std::invalid_argument("ee");
            }
            else
                setColor(rgbNames[i], value);
        }
}


void Leds::send(ESP8266WebServer &server){
}


String Leds::toString() const{
    String retVal = "Color:\n\n";
    retVal += "r=";
    retVal += red;
    retVal += "\ng=";
    retVal += green;
    retVal += "\nb=";
    retVal += blue;
    retVal += "\n";
    return retVal;
}
