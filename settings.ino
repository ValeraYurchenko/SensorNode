
char setupWifiId [10] = "SN-123";
char setupWifiPass [20] = "12341234";

void startSettingsMode() {
  settingsMode = true;
  
  long wifiID_rnd = random(100, 999);
  sprintf(setupWifiId, "SN-%lu", wifiID_rnd);
  
  long passLong = random(100000, 999999);
  sprintf(setupWifiPass, "00%lu", passLong); 
  
  Serial.print("setup mode: ");
  Serial.print(setupWifiId);
  Serial.print(" pass: ");
  Serial.println(setupWifiPass);

  statusLine = "Setup mode is ON";
  printStatusLine();
  while(LOW == digitalRead(modeBtnPin));
  delay(100);
  printSetupScreen();
  
  startAP(setupWifiId, setupWifiPass);
}

void startAP(char* ssid, char* pass) {
  statusLine = "Starting AP...";
  printStatusLine();
  //WiFi.setAutoConnect(false);
  WiFi.disconnect();
  delay(100);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass, 1, 0);
  delay(1000);
  WiFi.printDiag(Serial);
  statusLine = String("IP: ") + IpAddress2String(WiFi.softAPIP());
  printStatusLine();
  WiFi.printDiag(Serial);
}

void printSetupScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 20);
  display.println("Settings Mode: ON");
  display.println("");
  display.print("WiFi: ");
  display.println(setupWifiId);
  display.print("Password: ");
  display.println(setupWifiPass);
  display.display();
}

void exitFromSettingsMode(){
  settingsMode = false;

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  display.clearDisplay();
  drawStatic();
  printStatusLine();
  updateSensors();
}

