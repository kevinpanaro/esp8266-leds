#include <ESP8266WebServer.h>
#include "SingleColor.h"
#include "Error.h"

SingleColor::SingleColor(){
  red = 0;
  green = 0;
  blue = 0;
}

SingleColor::SingleColor(ESP8266WebServer &server){
  const char *rgbNames[] = {"r", "g", "b"};
  for(int i = 0; i < 3; i++)
  if(server.hasArg(rgbNames[i])){
    int value = server.arg(rgbNames[i]).toInt();
    setColor(rgbNames[i], value); // TODO: uint8_t overflow handling. ATM it implicitly overflows
  }
}

uint8_t SingleColor::getRed() const{
  return red;
}
uint8_t SingleColor::getGreen() const{
  return green;
}
uint8_t SingleColor::getBlue() const{
  return blue;
}


void SingleColor::setColor(String colorCode, uint8_t value){
  if(colorCode == "r") red = value;
  else if(colorCode == "g") green = value;
  else if(colorCode == "b") blue = value;
}

Error SingleColor::checkColorsValuesInRange() const{
  if(red < 0 || red > 255) return Error(true, buildValueOutOfRangeErrorMsg("r", red));
  if(green < 0 || green > 255) return  Error(true, buildValueOutOfRangeErrorMsg("g", green));
  if(blue < 0 || blue > 255) return  Error(true, buildValueOutOfRangeErrorMsg("b", blue));
  return Error(false, "");
}

String SingleColor::buildValueOutOfRangeErrorMsg(String colorCode, uint8_t value) const{
  String error = "Illegal value:\n\n";
  error += colorCode;
  error += "=";
  error += value;
  error += "\nOnly values 0 to 255 are allowed. 0 is off and 255 is 100% lit";
  return error;
}



void SingleColor::send(ESP8266WebServer &server){
}

String SingleColor::toString() const{
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
