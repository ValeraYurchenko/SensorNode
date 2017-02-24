
String rootContent = "<html><h2>Loading...</h2></html>";

String setup_html = "";
String dashboard_html = "";

void initWebServer() {
  loadFiles();
  
  // Start the server
  
  server.on( "/", http_root );
  server.on( "/setup", http_setup );
  server.on( "/dashboard", http_dashboard );
  
  server.onNotFound ( []() {
    server.send(404, "text/plain", "Not Found" );
  });
  
  server.begin();
  Serial.println ( "HTTP server started" );
}

void http_root() {
  server.send( 200, "text/html", rootContent);
}

void http_dashboard() {
  server.send( 200, "text/html", dashboard_html);
}


void http_setup() {
  if (!settingsMode) {
    server.send( 403, "text/plain", "The page is available in settings mode only.");
    return;
  }
  
  server.send ( 200, "text/html", setup_html);
}

void updateHTMLRootContent() {
  rootContent = String("<html><h2>Humidity: ") + String(humidity) + "%</h2><br/>"
    + "<h2>Temperature: " + String(temperature) + "&deg;C</h2>";
    + "</html>";
}

// ---------------------------- Utils -------------------------

void loadFiles() {
  statusLine = "Load files...";
  printStatusLine();

  SPIFFS.begin();
  
  Serial.println("Load: setup.html");
  setup_html = readFile("/setup.html");
  Serial.println("Load: dashboard.html");
  dashboard_html = readFile("/dashboard.html");
}

String readFile(char* fileName) {
  File file = SPIFFS.open(fileName, "r");
  String fileContent = "";
  if (!file) {
    Serial.println("file open failed");
  } else{
    Serial.println("file open success");

    while (file.available()) {
      String line = file.readStringUntil('\n');
      fileContent += line + "\n";
      Serial.println(line);
    }
    file.close();
  }
  return fileContent;
}
