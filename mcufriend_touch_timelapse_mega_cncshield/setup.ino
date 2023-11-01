void setup() {
                                                                // Initialize the touchscreen and CNC Shield V3
   Serial.begin(9600);
 uint16_t ID = tft.readID();                                   //init TFTTouch
 Serial.print("TFT ID = 0x");
 Serial.println(ID, HEX);
 Serial.println(F("Calibrate for your Touch Panel"));
 if (ID == 0xD3D3) ID = 0x9486;                                 //for 3.5" TFT LCD Shield , 0x9341 for 2.8" TFT LCD Shield

 tft.begin(ID);
 tft.setRotation(0);                                            //0-PORTRAIT 1-PAYSAGE 2-REVERSE PORTRAIT 3-REVERSE PAYSAGE
  pinMode(X_ENDSTOP_PIN, INPUT_PULLUP);
  pinMode(Y_ENDSTOP_PIN, INPUT_PULLUP);
  pinMode(Z_ENDSTOP_PIN, INPUT_PULLUP);
  pinMode(X_DIR_PIN, OUTPUT); pinMode(X_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT); pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT); pinMode(Z_STEP_PIN, OUTPUT);
  stepperX.setMaxSpeed(xSpeed);
  stepperX.setAcceleration(xAcceleration);
  stepperY.setMaxSpeed(ySpeed);
  stepperY.setAcceleration(yAcceleration);
  stepperZ.setMaxSpeed(zSpeed);
  stepperZ.setAcceleration(zAcceleration);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  splash();
  currentPage = MENU; // Indicates that we are at Home Screen
}


// Function to check if a touchscreen coordinate is inside a button
// bool isButtonPressed(int16_t x, int16_t y, int16_t width, int16_t height) {
// return (touch_x >= x && touch_x <= (x + width) && touch_y >= y && touch_y <= (y + height));
// }



bool Touch_getXY(void)
{
 p = ts.getPoint();
 pinMode(YP, OUTPUT);      //restore shared pins
 pinMode(XM, OUTPUT);
 digitalWrite(YP, HIGH);
 digitalWrite(XM, HIGH);
 bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
 if (pressed) {
   if (tft.width() <= tft.height()) { //Portrait
     pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
     pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
   } else {
     pixel_x = map(p.y, TS_TOP, TS_BOT, 0, tft.width());
     pixel_y = map(p.x, TS_RT, TS_LEFT, 0, tft.height());
   }
 }
 return pressed;
}
