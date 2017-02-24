#include <Timer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include "FS.h"

#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);

#define DHTTYPE DHT11
//DHT dht(2, DHTTYPE);
Timer t;

//WiFiServer server(80);
ESP8266WebServer server(80);

int modeBtnPin = 2;

//Sensors values
int humidity = 0;
int temperature = 0;

String statusLine = "Loading...";

boolean settingsMode = false;

void setup() {
  Serial.begin(115200);
  //pinMode(12, INPUT);
  pinMode(modeBtnPin, INPUT);
  //pinMode(14, INPUT);
  
  initDisplay();
  updateSensors();
  initWebServer();
  checkWifiConnection();
  
  t.every(5000, updateSensors);
  t.every(5000, checkWifiConnection);
}

void loop() {
  checkModeButton();
  server.handleClient();
  
  if(settingsMode) {
    return;
  }
  
  t.update();
}

void checkModeButton() {
  if(LOW == digitalRead(modeBtnPin)) {
    Serial.println(WiFi.softAPIP());
    delay(2000);
    if(LOW == digitalRead(modeBtnPin)) {
      
      settingsMode = !settingsMode;
      Serial.print("!!!!!! Settings Mode: ");
      Serial.println(settingsMode ? "ON" : "OFF");
      if(settingsMode) {
        startSettingsMode();
      } else {
        exitFromSettingsMode();
      }
    }
  }
}

void onDataChanged() {
  updateHTMLRootContent();
  printSensorDataToDisplay();
}

