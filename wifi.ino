
char* wifi_ids[3] = {  "k73",       "MikroTik",    "Unify"};
char* wifi_pass[3] = { "123454321", "abrakadabra", "abrakadabra"};

void checkWifiConnection(){
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnect();
  }
}

void wifiConnect(){
  WiFi.setAutoConnect(false);
  WiFi.disconnect();
  delay(100);
  WiFi.softAPdisconnect(true);
  delay(100);
  WiFi.mode(WIFI_STA);
  WiFi.setPhyMode(WIFI_PHY_MODE_11G);
  
  statusLine = "Scan for WiFi..";
  printStatusLine();
  
  int n = WiFi.scanNetworks();
  if (n == 0) {
    statusLine = "WiFi not found";
    printStatusLine();
  } else {
    for (int i = 0; i < n; i++) {
      int index = findInArray(wifi_ids, WiFi.SSID(i));
      if(index > -1)  {
        wifiConnect(wifi_ids[index], wifi_pass[index]);
        if(WiFi.status() == WL_CONNECTED) {
          break;
        }
      }
    }
    
    if(WiFi.status() == WL_CONNECTED) {
       statusLine = String("IP: ") + IpAddress2String(WiFi.localIP());
    } else {
      statusLine = "Can't connect :(";
      WiFi.printDiag(Serial);
    }
    printStatusLine();
  } 
}

void wifiConnect(char* ssid, char* pass) {
  statusLine = String("Connecting: ") + ssid;
  printStatusLine();
    
  Serial.print("Connect to ");
  Serial.print(ssid);
  Serial.print(" pass: ");
  Serial.println(pass);
  if(pass == "") {
    WiFi.begin(ssid);
  } else {
    WiFi.begin(ssid, pass);
  }

  int timer = 0;
  while (WiFi.status() != WL_CONNECTED && timer < 10000) {
    delay(1000);
    timer += 1000;
    Serial.print(ssid);
    Serial.print(" status: ");
    Serial.println(WiFi.status());
    if (WiFi.status() == WL_NO_SSID_AVAIL) {
      break;
    }
  }
}

int findInArray(char* wifi_ids[], String val) {
  for (int i = 0; i < sizeof(wifi_ids); i++){
    if(String(wifi_ids[i]) == val) {
      return i;
    }
  }
  return -1;
}

String IpAddress2String(const IPAddress& ipAddress) {
  return String(ipAddress[0]) + String(".") +
  String(ipAddress[1]) + String(".") +
  String(ipAddress[2]) + String(".") +
  String(ipAddress[3])  ; 
}
