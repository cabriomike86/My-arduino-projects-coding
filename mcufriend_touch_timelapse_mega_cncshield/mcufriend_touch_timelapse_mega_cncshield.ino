#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <AccelStepper.h>
#define MINPRESSURE 100
#define MAXPRESSURE 1000
const int XP = 6, XM = A2, YP = A1, YM = 7; //320x480 ID=0x9486
const int TS_LEFT = 907, TS_RT = 136, TS_TOP = 942, TS_BOT = 139;
#define TS_MINX 139
#define TS_MINY 136
#define TS_MAXX 907
#define TS_MAXY 942
#define BLACK           0x0000
#define GREY            0x5555
#define BLUE            0x001F
#define RED             0xF800
#define NAVY            0x000F
#define DARKCYAN        0x03EF
#define MAROON          0x7800
#define PURPLE          0x780F
#define OLIVE           0x7BE0
#define LIGHTGREY       0xC618
#define DARKGREY        0x7BEF
#define DARKGREEN       0x05C0
#define DARKGREEN1      0x03E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define GOLD            0xDDC0
#define WHITE           0xFFFF
#define ORANGE          0xFD20
#define GREENYELLOW     0xAFE5
#define PINK            0xF81F
#define GREEN           0x07E0
#include "bitmap_Set.h"

// Button calibration
int margin = 5;
int btnWidth = 90;
int btnHeight = 40;
int btnY = 200;

// Buttons
Adafruit_GFX_Button on_btn, off_btn, page1_btn, page2_btn, page3_btn, page4_btn;
Adafruit_GFX_Button ok_btn, cncl_btn, plus_btn, minus_btn;
Adafruit_GFX_Button menu_btn, info_btn, back_btn, save_btn, speed_btn;
Adafruit_GFX_Button home_btn, homex_btn, homey_btn, homez_btn, homeall_btn;
Adafruit_GFX_Button up_btn, down_btn, ljog_btn, rjog_btn, upjog_btn, downjog_btn, sld1_btn, sld2_btn;
Adafruit_GFX_Button on1_btn, off1_btn, aan1_btn, uit1_btn, aan_btn, uit_btn;
Adafruit_GFX_Button rev1_btn, rev2_btn, rev3_btn, rev1uit_btn, rev2uit_btn, rev3uit_btn;
Adafruit_GFX_Button spdslider_btn, spdpan_btn, spdtilt_btn;


// Pin definitions for the CNC Shield V3
#define X_STEP_PIN 23
#define X_DIR_PIN 22
#define Y_STEP_PIN 25
#define Y_DIR_PIN 24
#define Z_STEP_PIN 27
#define Z_DIR_PIN 26
#define EN 28 // stepper motor enable


// Pin definitions for the end stops
#define X_ENDSTOP_PIN 51
#define Y_ENDSTOP_PIN 52
#define Z_ENDSTOP_PIN 53

// Define the motor steps per revolution
#define STEPS_PER_REV 200

// Create an instance of the MCUFRIEND touchscreen
MCUFRIEND_kbv tft;

// Create an instance of the TouchScreen
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int pixel_x, pixel_y;     //Touch_getXY() updates global vars
int touch_x, touch_y;     //Touch_getXY() updates global vars


// Create instances of the AccelStepper for each axis
AccelStepper stepperX(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperY(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperZ(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

// Variables for storing the touchscreen coordinates
int16_t x, y;
TSPoint p;

// Variables for end stops
bool xEndStopPressed = false;
bool yEndStopPressed = false;
bool zEndStopPressed = false;

// Variables for stepper settings
int xSpeed = 4000;
int xAcceleration = 1000;
int ySpeed = 4000;
int yAcceleration = 1000;
int zSpeed = 4000;
int zAcceleration = 1000;



bool down ;


// Enumeration for menu options
enum MenuOption {
  MENU,
  JOG_CONTROL,
  SPEED,
  LOOP_CONTROL,
  SETTINGS,
  END_STOP_STATUS,
  SAVE,
  INFO,
};

MenuOption currentMenu = JOG_CONTROL;
unsigned int currentPage = MENU, oldPage = -1;





void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);                         //AANPASBARE WAARDE
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(800);                         //AANPASBARE WAARDE
  }
}  


// Function to update the end stop status
void updateEndStopStatus() {
  xEndStopPressed = digitalRead(X_ENDSTOP_PIN) == LOW;
  yEndStopPressed = digitalRead(Y_ENDSTOP_PIN) == LOW;
  zEndStopPressed = digitalRead(Z_ENDSTOP_PIN) == LOW;
}

// Function to draw the main menu
void drawMainMenu() {
 tft.fillScreen(BLACK);
 tft.setTextSize(2);
  tft.setTextColor(WHITE, BLACK);
 tft.setCursor(70, 10);
 tft.print("Main Menu"); // Prints the string on the screen
 tft.drawLine(0, 32, tft.width() * 1.0, 32, DARKGREEN); // Draws the green line
 tft.setTextColor(WHITE, BLACK);//((255, 255, 255), (0,0,0));
 tft.setCursor(0, 80);
 tft.setTextColor(GREEN, BLACK);//((255, 255, 255), (0,0,0));
 tft.drawBitmap(40, 40, jogicon_40x40, 40, 40, WHITE);
 tft.drawBitmap(40, 100, loopicon_40x40, 40, 40, WHITE);
 tft.drawBitmap(40, 160, freeicon_40x40, 40, 40, WHITE);
 tft.drawBitmap(40, 220, settingicon_40x40, 40, 40, WHITE);
// Buttons
 page1_btn.initButton(&tft,  148, 60, 120, 40, WHITE, CYAN, BLACK, "Jog Mode", 2);
 page2_btn.initButton(&tft, 148, 120, 120, 40, WHITE, CYAN, BLACK, "Loop Mode", 2);
 page3_btn.initButton(&tft,  148, 180, 120, 40, WHITE, CYAN, BLACK, "Free Mode", 2);
 page4_btn.initButton(&tft, 148, 240, 120, 40, WHITE, CYAN, BLACK, "Options", 2);
 page1_btn.drawButton(false);
 page2_btn.drawButton(false);
 page3_btn.drawButton(false);
 page4_btn.drawButton(false);
 info_btn.initButton(&tft,  40 ,295, btnWidth, btnHeight, BLACK, BLACK, WHITE, "->Info<-", 1);
 info_btn.drawButton(false);
 oldPage = currentPage;
}


// Function to handle jog control menu
void jogControlMenu() {
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    tft.setRotation(0);            //PORTRAIT
    tft.fillScreen(BLACK);
    tft.drawBitmap(2, 0, HomeButton_35x35, 35, 35, WHITE);
    tft.drawBitmap(202, 0, HomeButton_35x35, 35, 35, WHITE);    
    tft.drawBitmap(89, 130, DirectionalArrow_64x66, 64, 66, WHITE);
    buttonjog();
    oldPage = currentPage;
}


void buttonjog()
{    
    //menu_btn.initButton(&tft,  tft.width() / 2. - btnWidth - margin , tft.height() - btnHeight / 2., btnWidth, btnHeight, WHITE, GREY, BLACK, "MENU", 1);
    home_btn.initButton(&tft,  122, 15, 160, 30, WHITE, RED, BLACK, "Home All", 2);
    homex_btn.initButton(&tft, 40, 50, 40, 30, WHITE, RED, BLACK, "Pan", 1.5);
    homey_btn.initButton(&tft, 121, 50, 40, 30, WHITE, RED, BLACK, "Tilt", 1.5);
    homez_btn.initButton(&tft, 200, 50, 40, 30, WHITE, RED, BLACK, "Slide", 1.5);
    upjog_btn.initButton(&tft,  120, 110, 45, 40, WHITE, CYAN, BLACK, "Up", 1.5);
    downjog_btn.initButton(&tft, 120, 216, 45, 40, WHITE, CYAN, BLACK, "Down", 1.5);
    ljog_btn.initButton(&tft,  66, 160, 45, 40, WHITE, CYAN, BLACK, "L", 1.5);
    rjog_btn.initButton(&tft, 175, 160, 45, 40, WHITE, CYAN, BLACK, "R", 1.5);
    sld1_btn.initButton(&tft,  40, 210, 55, 30, WHITE, CYAN, BLACK, "<--", 2);
    sld2_btn.initButton(&tft, 200, 210, 55, 30, WHITE, CYAN, BLACK, "-->", 2);
    home_btn.drawButton(false);
    homex_btn.drawButton(false);
    homey_btn.drawButton(false);
    homez_btn.drawButton(false);   
    upjog_btn.drawButton(false);
    downjog_btn.drawButton(false);
    ljog_btn.drawButton(false);
    rjog_btn.drawButton(false);
    sld1_btn.drawButton(false);
    sld2_btn.drawButton(false); 
    back_btn.initButton(&tft,  50 , 310, btnWidth, btnHeight, BLACK, BLACK, WHITE, "<- Back", 2);
    back_btn.drawButton(false);
    speed_btn.initButton(&tft,  180 ,310, btnWidth, btnHeight, BLACK, BLACK, WHITE, "Speed", 2);
    speed_btn.drawButton(false);
}




// Function to handle loop control menu
void loopControlMenu() {
  tft.fillScreen(BLACK);
 tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 20);
  tft.println("Loop Control Menu");
  // Add loop control buttons and functionality here
}




// Function to handle settings menu
void settingsMenu() {
  tft.fillScreen(BLACK);
 tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 20);
  tft.println("Settings Menu");
  // Add settings buttons and functionality here
}




// Function to handle end stop status menu
void endStopStatusMenu() {
  tft.fillScreen(BLACK);
  tft.drawLine(0, 130, tft.width() * 1.0, 130, YELLOW); // Draws the YELLOW line
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(2);
  tft.setCursor(25, 140);
  tft.println("End Stop Status");
  tft.drawLine(0, 160, tft.width() * 1.0, 160, YELLOW); // Draws the YELLOW line
  // Add end stop status information here
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
//    tft.setRotation(0);            //PORTRAIT
//    tft.fillScreen(BLACK);
    oldPage = currentPage;

    tft.setTextSize(2);
    tft.setCursor(120, 170);
    tft.setTextColor(GREEN);
    tft.print("Triggered");

 //   tft.setTextSize(2);
//    tft.setCursor(110, 180);
//    tft.setTextColor(GREEN);
 //   tft.print("+Stop");

  //  tft.setTextSize(2);
  //  tft.setCursor(180, 180);
  //  tft.setTextColor(GREEN);
  //  tft.print("-Stop");

    tft.drawLine(0, 195, tft.width() * 1.0, 195, YELLOW); // Draws the YELLOW line
 
    tft.setTextSize(2);
    tft.setCursor(5, 200);
    tft.setTextColor(RED);
    tft.print("Slider");
    
    tft.setTextSize(2);
    tft.setCursor(5, 220);
    tft.setTextColor(RED);
    tft.print("Pan");

    tft.setTextSize(2);
    tft.setCursor(5, 240);
    tft.setTextColor(RED);
    tft.print("Tilt");

    back_btn.initButton(&tft,  50 , 310, btnWidth, btnHeight, BLACK, BLACK, WHITE, "<- Back", 2);
    back_btn.drawButton(false);
}


void drawInfoScreen() {
 tft.setRotation(0); 
 tft.fillScreen(BLACK);//(100, 155, 203)
 tft.drawRoundRect(10, 50, tft.width() - 20, tft.height() - 60, 5, GREEN); //tft.fillRect (10, 10, 60, 36);
 tft.setTextSize(1);
 tft.setTextColor(WHITE, BLACK);
 tft.setCursor(55, 18);
 tft.print("sex met dooie dieruh!");
 tft.setTextSize(1);
 tft.setTextColor(WHITE, BLACK);
 tft.setCursor(30, 80);
 tft.print("Je moeder op een driewieler");
 tft.setCursor(20, 290);
 tft.print("ShitShoWMike" );
 oldPage = currentPage;
}

void splash() {
  tft.fillScreen(WHITE);
  tft.setTextSize(2);
  tft.setCursor(55, 40);
  tft.setTextColor(BLUE);
  tft.print("Touchscreen");
  tft.setTextSize(2);
  tft.setCursor(85, 60);
  tft.setTextColor(BLUE);
  tft.print("Motion");
  tft.setTextSize(2);
  tft.setCursor(65, 80);
  tft.setTextColor(BLUE);
  tft.print("Controller");
  tft.setTextSize(2);
  tft.setCursor(70, 280);
  tft.setTextColor(BLACK);
  tft.print("Copyright");
  tft.setTextSize(2);
  tft.setCursor(85, 300);
  tft.setTextColor(BLACK);
  tft.print("MvB2023");
  tft.drawBitmap(95, 170, zandloper_60x60, 60, 60, BLACK);
  tft.setTextSize(2);
  tft.setCursor(35, 140);
  tft.setTextColor(RED);
  tft.print("Initializing");
    for (int i = 1; i <= 4; i++) {
    delay(350);
    tft.print(".");
  }
  delay(3500);                      // duration for the splash screen to remain displayed
  tft.fillScreen(BLACK);
}

void Save(){
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    tft.setRotation(0);            //PORTRAIT
    tft.fillScreen(BLACK);
    tft.drawRoundRect(10, 50, tft.width() - 20, tft.height() - 180, 5, GREEN); //tft.fillRect (10, 10, 60, 36);
    tft.setTextSize(3);
    tft.setCursor(75, 110);
    tft.setTextColor(GREEN);
    tft.print("Saved");
    delay(1000);
    oldPage = currentPage;
}

void speedmenu()
{
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    tft.setRotation(0);            //PORTRAIT
    tft.fillScreen(BLACK);

    tft.setTextSize(2);
    tft.setCursor(90, 40);
    tft.setTextColor(GREEN);
    tft.print("Speed");

    tft.setTextSize(2);
    tft.setCursor(180, 40);
    tft.setTextColor(GREEN);
    tft.print("Accel");
    
    tft.drawLine(0, 60, tft.width() * 1.0, 60, YELLOW); // Draws the green line

    tft.setTextSize(2);
    tft.setCursor(5, 80);
    tft.setTextColor(RED);
    tft.print("Slider");
    
    tft.setTextSize(2);
    tft.setCursor(5, 140);
    tft.setTextColor(RED);
    tft.print("Pan");

    tft.setTextSize(2);
    tft.setCursor(5, 200);
    tft.setTextColor(RED);
    tft.print("Tilt");
    
    back_btn.initButton(&tft,  50 , 310, btnWidth, btnHeight, BLACK, BLACK, WHITE, "<-Back", 2);
    back_btn.drawButton(false);
    save_btn.initButton(&tft,  190 , 310, btnWidth, btnHeight, BLACK, BLACK, WHITE, "Save->", 2);
    save_btn.drawButton(false);
    
    oldPage = currentPage;
}
