/*void loop() {
  // Read touchscreen input
 //touch = ts.getPoint();

  // Scale touchscreen coordinates
  x = map(pixel_x, TS_MINX, TS_MAXX, 0, tft.width());
  y = map(pixel_y, TS_MINY, TS_MAXY, 0, tft.height());

  // Update the end stop status
  updateEndStopStatus();

  // Check if any of the menu options are pressed
  if (currentMenu == JOG_CONTROL) {
    if (isButtonPressed(20, 20, tft.width(), tft.height())) {
      jogControlMenu();
      currentMenu = JOG_CONTROL;
    }
  } else if (currentMenu == LOOP_CONTROL) {
    if (isButtonPressed(20, 40, tft.width(), tft.height())) {
      loopControlMenu();
      currentMenu = LOOP_CONTROL;
    }
  } else if (currentMenu == SETTINGS) {
    if (isButtonPressed(20, 60, tft.width(), tft.height())) {
      settingsMenu();
      currentMenu = SETTINGS;
    }
  } else if (currentMenu == END_STOP_STATUS) {
    if (isButtonPressed(20, 80, tft.width(), tft.height())) {
      endStopStatusMenu();
      currentMenu = END_STOP_STATUS;
    }
  }

  // Check if the main menu button is pressed
  if (currentMenu != JOG_CONTROL && isButtonPressed(0, 0, tft.width(), tft.height())) {
    drawMainMenu();
    currentMenu = JOG_CONTROL;
  }
}
*/

void loop(void) {
 switch (currentPage) {
  
   case MENU: //Menu page
     if (currentPage != oldPage)   drawMainMenu();
     page1_btn.press(down && page1_btn.contains(pixel_x, pixel_y));
     page2_btn.press(down && page2_btn.contains(pixel_x, pixel_y));
     page3_btn.press(down && page3_btn.contains(pixel_x, pixel_y));
     page4_btn.press(down && page4_btn.contains(pixel_x, pixel_y));
     info_btn.press(down && info_btn.contains(pixel_x, pixel_y));

     if (page1_btn.justReleased())
       page1_btn.drawButton();
     if (page2_btn.justReleased())
       page2_btn.drawButton();
     if (page3_btn.justReleased())
       page3_btn.drawButton();
     if (page4_btn.justReleased())
       page4_btn.drawButton();
     if (info_btn.justReleased())
       info_btn.drawButton();
     if (page1_btn.justPressed()) {
       page1_btn.drawButton(true);
       currentPage = JOG_CONTROL;
     }
     if (page2_btn.justPressed()) {
       page2_btn.drawButton(true);
       currentPage = LOOP_CONTROL;
     }
     if (page3_btn.justPressed()) {
       page3_btn.drawButton(true);
       currentPage = SETTINGS;
     }
     if (page4_btn.justPressed()) {
       page4_btn.drawButton(true);
       currentPage = END_STOP_STATUS;
     }
     if (info_btn.justPressed()) {
       info_btn.drawButton(true);
       currentPage = INFO;
     }
     break;
     
  case JOG_CONTROL:
     if (currentPage != oldPage)   jogControlMenu();
     back_btn.press(down && back_btn.contains(pixel_x, pixel_y));
     info_btn.press(down && info_btn.contains(pixel_x, pixel_y));
     speed_btn.press(down && speed_btn.contains(pixel_x, pixel_y));
     home_btn.press(down && home_btn.contains(pixel_x, pixel_y));
     ljog_btn.press(down && ljog_btn.contains(pixel_x,pixel_y));
     rjog_btn.press(down && rjog_btn.contains(pixel_x,pixel_y));
     upjog_btn.press(down && upjog_btn.contains(pixel_x,pixel_y));
     downjog_btn.press(down && downjog_btn.contains(pixel_x,pixel_y));
     sld1_btn.press(down && sld1_btn.contains(pixel_x,pixel_y));
     sld2_btn.press(down && sld2_btn.contains(pixel_x,pixel_y));

     if (back_btn.justReleased())
       back_btn.drawButton();
     if (info_btn.justReleased())
       info_btn.drawButton();
     if (speed_btn.justReleased())
       speed_btn.drawButton();
     if (back_btn.justPressed()) {
       back_btn.drawButton(true);
       currentPage = MENU;
     }
     if (speed_btn.justPressed()) {
       speed_btn.drawButton(true);
       currentPage = SPEED;
     }
     if (home_btn.justReleased())
       home_btn.drawButton();
     if (home_btn.justPressed()) {
       home_btn.drawButton(true);
//       if (digitalRead(SLD1_PIN1) || (SLD2_PIN1) != LOW)
//       homing();
     }
     if (ljog_btn.justReleased())
       ljog_btn.drawButton();
     if (ljog_btn.justPressed()) {
       ljog_btn.drawButton(true);
       ljog();
     }
     if (rjog_btn.justReleased())
       rjog_btn.drawButton();
     if (rjog_btn.justPressed()) {
       rjog_btn.drawButton(true);
       rjog();
     }
     if (upjog_btn.justReleased())
       upjog_btn.drawButton();
     if (upjog_btn.justPressed()) {
       upjog_btn.drawButton(true);
       upjog();
     }
     if (downjog_btn.justReleased())
       downjog_btn.drawButton();
     if (downjog_btn.justPressed()) {
       downjog_btn.drawButton(true);
       downjog();
     }
     if (sld1_btn.justReleased())
       sld1_btn.drawButton();
     if (sld1_btn.justPressed()) {
       sld1_btn.drawButton(true);
       sldLjog();
     }
     if (sld2_btn.justReleased())
       sld2_btn.drawButton();
     if (sld2_btn.justPressed()) {
       sld2_btn.drawButton(true);
       sldRjog();
     }  
     break;
     
  case SPEED: //consigne
     if (currentPage != oldPage)   speedmenu();     
      spdslider_btn.press(down && spdslider_btn.contains(pixel_x, pixel_y));
      spdpan_btn.press(down && spdpan_btn.contains(pixel_x, pixel_y));
      spdtilt_btn.press(down && spdtilt_btn.contains(pixel_x, pixel_y));
      back_btn.press(down && back_btn.contains(pixel_x, pixel_y));
      save_btn.press(down && save_btn.contains(pixel_x, pixel_y));


     if (back_btn.justReleased())
       back_btn.drawButton();
      if (back_btn.justPressed()) {
       back_btn.drawButton(true);
       currentPage = JOG_CONTROL;
        }
     if (save_btn.justReleased())
       save_btn.drawButton();
      if (save_btn.justPressed()) {
       save_btn.drawButton(true);
       Save();
       tft.fillScreen(BLACK);
       speedmenu();
       currentPage = SPEED;
        }
     break;

  case END_STOP_STATUS:
     if (currentPage != oldPage)   endStopStatusMenu();
     back_btn.press(down && back_btn.contains(pixel_x, pixel_y));
     if (digitalRead(X_ENDSTOP_PIN) != LOW) {
    tft.setTextSize(2);
    tft.setCursor(180, 200);
    tft.setTextColor(BLACK);
    tft.print("act.");
    tft.setTextSize(2);
    tft.setCursor(85, 200);
    tft.setTextColor(BLUE);
    tft.print("ok");
     }
     
    if (digitalRead(X_ENDSTOP_PIN) != HIGH) {
    tft.setTextSize(2);
    tft.setCursor(180, 200);
    tft.setTextColor(GREEN);
    tft.print("act.");
    tft.setTextSize(2);
    tft.setCursor(85, 200);
    tft.setTextColor(BLACK);
    tft.print("ok");
     }

     if (digitalRead(Y_ENDSTOP_PIN) != LOW) {
    tft.setTextSize(2);
    tft.setCursor(180, 220);
    tft.setTextColor(BLACK);
    tft.print("act.");
    tft.setTextSize(2);
    tft.setCursor(85, 220);
    tft.setTextColor(BLUE);
    tft.print("ok");
     }
     
    if (digitalRead(Y_ENDSTOP_PIN) != HIGH) {
    tft.setTextSize(2);
    tft.setCursor(180, 220);
    tft.setTextColor(GREEN);
    tft.print("act.");
    tft.setTextSize(2);
    tft.setCursor(85, 220);
    tft.setTextColor(BLACK);
    tft.print("ok");
     }

    if (digitalRead(Z_ENDSTOP_PIN) != LOW) {
    tft.setTextSize(2);
    tft.setCursor(180, 240);
    tft.setTextColor(BLACK);
    tft.print("act.");
    tft.setTextSize(2);
    tft.setCursor(85, 240);
    tft.setTextColor(BLUE);
    tft.print("ok");
     }
     
    if (digitalRead(Z_ENDSTOP_PIN) != HIGH) {
    tft.setTextSize(2);
    tft.setCursor(180, 240);
    tft.setTextColor(GREEN);
    tft.print("act.");
    tft.setTextSize(2);
    tft.setCursor(85, 240);
    tft.setTextColor(BLACK);
    tft.print("ok");
     }
     if (back_btn.justReleased())
     back_btn.drawButton();
     if (back_btn.justPressed()) {
     back_btn.drawButton(true);
     currentPage = MENU;
     }
    break;

case INFO:
     if (currentPage != oldPage) drawInfoScreen();
     if (Touch_getXY()) {
       currentPage = MENU;
     }
     break;

     
 }
 if (oldPage == currentPage){
   down = Touch_getXY();
 }else{
   down=false;
 }
}
