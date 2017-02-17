void updateSesors() {
  Serial.println("updateSesors run");
  
  int h = (int)dht.readHumidity();
  int t = (int)dht.readTemperature();

  Serial.println("updateSesors run: t=" + String(t) + ", h=" + String(h));

  boolean changedData = h != humidity || t != temperature;

  if (!isnan(h) && h <=100) {
    humidity = h;
  }
  if (!isnan(t) && t < 100) {
    temperature = t;
  }

  if (changedData) {
    onDataChanged();
  }
}

