#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define BLUE    0x001F
#define RED     0xF800
#define YELLOW  0xFFE0
#define CYAN    0x07FF

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

void loop(void) {
  int values[3];
  for (int i = 0; i < 3; i++) {
    values[i] = analogRead(A0 + i); // Read analog inputs A0, A1, and A2
  }

  tft.fillRect(10, 10, map(values[0], 0, 1023, 1, 180), 19, YELLOW);
  tft.fillRect(10, 20, map(values[1], 0, 1023, 1, 180), 29, YELLOW);
  tft.fillRect(10, 40, map(values[2], 0, 1023, 1, 180), 39, YELLOW);
  // Clear the rest of the bars
  tft.fillRect(map(values[0], 0, 1023, 1, 180) + 9, 10, 180 - map(values[0], 0, 1023, 1, 180), 19, BLACK);
  tft.fillRect(map(values[1], 0, 1023, 1, 180) + 9, 20, 180 - map(values[1], 0, 1023, 1, 180), 29, BLACK);
  tft.fillRect(map(values[2], 0, 1023, 1, 180) + 9, 40, 180 - map(values[2], 0, 1023, 1, 180), 39, BLACK);
  tft.setTextColor(BLUE);

  tft.setCursor(30, 16); tft.println(values[0]);
  tft.setCursor(30, 40); tft.println(values[1]);
  tft.setCursor(30, 65); tft.println(values[2]);

  delay(10);
}
