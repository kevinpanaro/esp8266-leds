#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>


const char* SSID = "SFR-b118";
const char* PASSWORD = "V6AW5I2E1S2M";
const int PORT = 80;
const int NETWORK_LED_PIN = D2;
const int LED_STRIP_NB_LEDS = 300;
const int LED_STRIP_DATA_PIN = D1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_STRIP_NB_LEDS, LED_STRIP_DATA_PIN, NEO_GRB + NEO_KHZ800);

ESP8266WebServer server(PORT);

void blinkNetworkLed() {
  int ledDuration = 100;
  digitalWrite(NETWORK_LED_PIN, 1);
  delay(ledDuration);
  digitalWrite(NETWORK_LED_PIN, 0);
}

void handleRoot() {
    blinkNetworkLed();
  server.send(200, "text/plain", "hello from esp8266!");
}

int getArgValue(String name){
  for (uint8_t i = 0; i < server.args(); i++)
    if(server.argName(i) == name)
      return server.arg(i).toInt();
  return -1;
}

const char *rgbNames[] = {"r", "g", "b"};

  bool loadRGBValues(ESP8266WebServer &server, uint8_t *rgb){
    for(int i = 0; i < 3; i++)
      if(server.hasArg(rgbNames[i])){
        int value = server.arg(rgbNames[i]).toInt();
        if(value < 0 || value > 255){
          String message = "Illegal value:\n\n";
          message += rgbNames[i];
          message += "=";
          message += server.arg(rgbNames[i]);
          message += "\nOnly values 0 to 255 are allowed. 0 is off and 255 is 100% lit.";
          server.send(200, "text/plain", message);
          return false;
        }
        rgb[i] = value;
      }
    return true;
  }

void setColor(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
    strip.show();
}

void handleOneColor() {
  blinkNetworkLed();
    uint8_t rgb[3] = {0, 0, 0};
bool validInput = loadRGBValues(server, rgb);
if(validInput){
    String message = "Color:\n\n";
    for(int i = 0; i < 3; i++){
          message += rgbNames[i];
          message += "=";
          message += rgb[i];
          message += "\n";
      }
      server.send(200, "text/plain", message);
      setColor(strip.Color(rgb[0], rgb[1], rgb[2]));
    }
  else
      server.send(200, "text/plain", "error");
}

void handleNotFound() {
  blinkNetworkLed();
  String message = "Color\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


void defineRoutes(){
  server.on("/", handleRoot);
  server.on("/color", handleOneColor);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
}

void startServer(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");

  server.begin();

  Serial.println("HTTP server started");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup(void) {
  pinMode(NETWORK_LED_PIN, OUTPUT);
  pinMode(LED_STRIP_DATA_PIN, OUTPUT);
  digitalWrite(NETWORK_LED_PIN, 0);
  Serial.begin(115200);

  strip.begin();
  strip.show();

  startServer();
  defineRoutes();
}

void loop(void) {
  server.handleClient();
}