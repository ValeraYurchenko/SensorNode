
char* wifi_ids[2] = {  "k73",       "MikroTik"};
char* wifi_pass[2] = { "123454321", "abrakadabra"};

void checkWifiConnection(){
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnect();
  }
}

void wifiConnect(){
  WiFi.disconnect();
  delay(100);
  
  statusLine = "Scan for WiFi..";
  printStatusLine();
  
  int n = WiFi.scanNetworks();
  if (n == 0) {
    statusLine = "WiFi not found";
    printStatusLine();
  } else {
    //statusLine = "Connecting..";
    //printStatusLine();

    /*for (int i = 0; i < n; ++i) {
      int index = findInArray(wifi_ids, WiFi.SSID(i));
      if(index > -1)  {
        wifiConnect(wifi_ids[i], wifi_pass[i]);
        if(WiFi.status() == WL_CONNECTED) {
          break;
        }
      }
    }
    
    if(WiFi.status() != WL_CONNECTED) {
      // try open wifi
      for (int i = 0; i < n; ++i) {
        if(WiFi.encryptionType(i) == ENC_TYPE_NONE) {
          char* id;
          WiFi.SSID(i).toCharArray(id, sizeof(WiFi.SSID(i)));
          
          wifiConnect(id, "");
          if(WiFi.status() == WL_CONNECTED) {
            break;
          }
        }
        
      }
    }*/

    wifiConnect(wifi_ids[0], wifi_pass[0]);
    if(WiFi.status() != WL_CONNECTED) {
      wifiConnect(wifi_ids[1], wifi_pass[1]);
    }
    
    if(WiFi.status() == WL_CONNECTED) {
       statusLine = String("IP: ") + IpAddress2String(WiFi.localIP());
    } else {
      statusLine = "Can't connect :(";
    }
    printStatusLine();
  } 
}

void wifiConnect(char* ssid, char* pass) {
  statusLine = String("Connecting: ") + ssid;
  printStatusLine();
    
  Serial.print("Connect to ");
  Serial.print(ssid);
  Serial.println(pass);
  if(pass == "") {
    WiFi.begin(ssid);
  } else {
    WiFi.begin(ssid, pass);
  }

  int timer = 0;
  while (WiFi.status() != WL_CONNECTED && timer < 5000) {
    delay(500);
    timer += 500;

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

String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}
