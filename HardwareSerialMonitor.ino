#include <Wire.h>
#include <Adafruit_GFX.h>
#include "images.h"

/* SSD1106 OLED setup */
#include <Adafruit_SH110X.h>
 // Hypothetical SSD1106 library
#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
#define OLED_RESET 16         // Reset pin - changed to 16 for TTGO board
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's
TwoWire twoWire = TwoWire(1);
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &twoWire, OLED_RESET);

/* vars for serial input */
String inputString = "";
boolean stringComplete = false;
int Serial_eventDelay = 15;

// Joystick pins
const int X_PIN = 32;
const int Y_PIN = 33;

String menuItems[] = {"CPU", "GPU", "RAM"};
int selectedMenuItem = 0;
bool inMenu = true;


void setup() {
 // For SDA and SCL
 twoWire.begin(21, 22);                       // Needs to come before display.begin() is used
 delay(250); // wait for the OLED to power up
 if(!display.begin(i2c_Address, true)){
       Serial.println(F("SH1106 allocation failed"));
       for(;;);                                 //Don't proceed, loop forever
 }

 display.display();
 delay(2000);
 display.clearDisplay();
 display.setTextColor(SH110X_WHITE);
 display.setRotation(0);                     // Rotate the display at the start: 0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
 display.clearDisplay();

 /* Text wrapping */
 display.setTextWrap(false);                 // Stop "Loads/Temps" wrapping and corrupting static characters

 /* Show logo boot */
 display.drawBitmap(0, 0, Loading_bits, Loading_width, Loading_height, 1);
 display.display();

 /* Serial setup, start serial port at 921600 bps and wait for port to open: */
 Serial.begin(115200);
 inputString.reserve(200);
 /* Waiting Serial connected */
 while (!Serial.available()) {
   display.fillRect(90, 24, 38, 16, SH110X_BLACK);
   display.fillRect(64, 31, 32, 2, SH110X_WHITE);
   display.drawBitmap(96, 16, USB_bits, USB_width, USB_height, 1);
   display.display();
   delay(500);
   display.fillRect(90, 24, 38, 16, SH110X_BLACK);
   display.drawBitmap(90, 16, USB_bits, USB_width, USB_height, 1);
   display.display();
   delay(300);
 }
 display.clearDisplay();

 pinMode(X_PIN, INPUT);
 pinMode(Y_PIN, INPUT);
}

void loop() {
 /* Serial stuff */
 /* Read system hardware monitor */
 serialEvent();

 /* OLED DRAW STATS */
 if (stringComplete) {
   if (inMenu) {
     DisplayMenu();
   } else {
     DisplayInfo();
   }
   inputString = "";
   stringComplete = false;
 }

 if (inMenu) {
   DisplayMenu();
 } else {
   DisplayInfo();
 }
}

void serialEvent() {
 while (Serial.available()) {             // USB Serial Available?
   char inChar = (char)Serial.read();     // Read USB Serial
   inputString += inChar;
   if (inChar == '|') {
     stringComplete = true;
     delay(Serial_eventDelay);  // Delay screen event to stop screen data corruption
   }
 }
}

