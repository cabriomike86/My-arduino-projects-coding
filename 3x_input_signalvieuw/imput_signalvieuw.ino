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
  tft.setRotation(3);
  tft.fillScreen(BLACK);


  tft.fillRect(0, 0, 320, 240, BLACK);
  tft.drawRect(1, 0, 319, 240, WHITE);
  tft.drawRect(9, 9, 202, 21, WHITE);
  tft.drawRect(9, 49, 202, 21, WHITE);
  tft.drawRect(9, 89, 202, 21, WHITE);
  tft.drawLine(10, 90, 10, 240, BLUE);
  tft.drawLine(0, 230, 320, 230, RED);

  tft.setTextColor(GREEN);
  tft.setTextSize(1.5);
  tft.setCursor(215, 10); tft.println("%100");
  tft.setCursor(215, 20); tft.println("RSSI 1");

  tft.setCursor(215, 50); tft.println("%100");
  tft.setCursor(215, 60); tft.println("RSSI 2");

  tft.setCursor(215, 90); tft.println("%100");
  tft.setCursor(215, 100); tft.println("RSSI 3");
}

void loop(void) {
  int values[3];
  for (int i = 0; i < 3; i++) {
    values[i] = analogRead(A0 + i); // Read analog inputs A0, A1, and A2
  }

  tft.fillRect(10, 10, map(values[0], 0, 1023, 1, 200), 19, YELLOW);
  tft.fillRect(10, 50, map(values[1], 0, 1023, 1, 200), 19, YELLOW);
  tft.fillRect(10, 90, map(values[2], 0, 1023, 1, 200), 19, YELLOW);

  // Clear the rest of the bars
  tft.fillRect(map(values[0], 0, 1023, 1, 200) + 9, 10, 200 - map(values[0], 0, 1023, 1, 200), 19, BLACK);
  tft.fillRect(map(values[1], 0, 1023, 1, 200) + 9, 50, 200 - map(values[1], 0, 1023, 1, 200), 19, BLACK);
  tft.fillRect(map(values[2], 0, 1023, 1, 200) + 9, 90, 200 - map(values[2], 0, 1023, 1, 200), 19, BLACK);

  tft.setCursor(10, 15); tft.println(values[0]);
  tft.setCursor(10, 55); tft.println(values[1]);
  tft.setCursor(10, 95); tft.println(values[2]);

  delay(10);
}
