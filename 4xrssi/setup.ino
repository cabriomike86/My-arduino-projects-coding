

void setup(void) {
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(0);
  tft.fillScreen(BLACK);

  tft.fillRect(0, 0,320 , 240, BLACK);

  tft.drawRect(1, 0, 239, 318, WHITE);
  tft.drawRect(9, 9, 181, 71, WHITE);
  tft.drawRect(9, 81, 181, 20, WHITE);

  tft.drawLine(10,170, 10, 310, BLUE);
  tft.drawLine(1, 310, 239, 310, RED);

  tft.setTextColor(GREEN);
  tft.setTextSize(1);
  tft.setCursor(210, 10); tft.println("Vrx1");
  tft.setCursor(210, 20); tft.println("RSSI ");

  tft.setCursor(210, 36); tft.println("Vrx2");
  tft.setCursor(210, 46); tft.println("RSSI ");

  tft.setCursor(210, 60); tft.println("Vrx3");
  tft.setCursor(210, 70); tft.println("RSSI ");  

  tft.setCursor(191, 82); tft.println("RemoteTX");
  tft.setCursor(210, 92); tft.println("RSSI ");

}
