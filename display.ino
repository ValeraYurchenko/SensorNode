char degree_symbol = char(503);
void initDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  drawStatic();
  printStatusLine();
}

void printSensorDataToDisplay() {
  display.setTextSize(2);
  display.setCursor(5,15);
  display.setTextColor(WHITE, BLACK);
  display.print(temperature);
  display.print(degree_symbol);
  display.print("C");
  display.setCursor(74,15);
  display.print(humidity);
  display.print("%");
  display.display();
}

void drawStatic() {
  display.fillRect(0, 0, 128, 10, WHITE);     //       ||||||||||||||||||||
  display.drawLine(0, 43, 128, 43, WHITE);   //       |        |         |
  display.drawLine(66, 10, 66, 43, WHITE);  //       |  25 C  |   40%   |
                                             //       |tempera_|_Humid___|
  display.setTextSize(1);                    //       |-------------     |
  display.setCursor(0,33);                   //       |___Ligting 80%____|
  display.setTextColor(WHITE, BLACK);
  display.print("Temperature");
  display.setCursor(70,33);
  display.print("Humidity");

  display.display();
}

void printStatusLine() {
  display.fillRect(0, 0, 128, 10, WHITE);
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(1);
  display.setCursor(1,1);
  display.println(statusLine);
  display.display();
}

