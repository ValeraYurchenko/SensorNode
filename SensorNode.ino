#include <Timer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define DHTTYPE DHT11
DHT dht(2, DHTTYPE);
Timer t;
WiFiServer server(80);

//Sensors values
int humidity = 0;
int temperature = 0;

String statusLine = "";

void setup() {
  Serial.begin(9600);
  initDisplay();
  updateSesors();
  checkWifiConnection();
  
  // Start the server
  server.begin();
  Serial.println("Server started");
   t.every(5000, updateSesors);
   t.every(5000, checkWifiConnection);
}

String OK_RESPONSE_HEADER = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";

String htmlContent = OK_RESPONSE_HEADER + "<html>Loading...</html>";

void loop() {
  t.update();
  
   // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    delay(20);
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  int timeout = 0;
  while(!client.available() && timeout < 5000){
    delay(1);
    timeout++;
  }
  if(!client.available()) {
    return;
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  //if (req.indexOf("/weather") == -1) {
  //  client.print("HTTP/1.1 404");
  //  return;
  //}

  client.print(htmlContent);
  delay(1);
  Serial.println("Client disonnected");
}

void onDataChanged() {
  updateHTMLContent();
  printSensorDataToDisplay();
}

void updateHTMLContent() {
  htmlContent = OK_RESPONSE_HEADER + "<html>"
    + "Humidity: " + String(humidity) + "%<br/>"
    + "Temperature: " + String(temperature) + "&deg;C";
    + "</html>";
}

