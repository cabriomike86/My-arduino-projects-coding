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