void updateSensors() {

  int h = 0;//(int)dht.readHumidity();
  int t = 0;//ooo(int)dht.readTemperature();

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

