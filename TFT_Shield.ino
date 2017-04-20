/*
	Simple sketch to demonstrate the use of the 2.4" TFT LCD touch shield
 */

// Adafruit GFX Libraries
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>

// You can include several fonts but WARNING! They take up a lot of space.
#include <Fonts/FreeSansBold24pt7b.h>

// Adafruit Touch screen library (if required)
#include <TouchScreen.h>

#define LCD_CS A3     // Chip Select goes to Analog 3
#define LCD_CD A2     // Command/Data goes to Analog 2
#define LCD_WR A1     // LCD Write goes to Analog 1
#define LCD_RD A0     // LCD Read goes to Analog 0
#define LCD_RESET A4  // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

// Create the TFT object with all pin assignments
// This leaves pins 2, 3, 4, 5 free. Also pin 12 if you don't use SD card.
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Set up the touch screen element of the TFT screen
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin
#define SENSITIVITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000
TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSITIVITY);

// Define the coordinates for our buttons here
#define btnCONTINUE ((p.y < 300 || p.y > 845) || (p.x < 220 || p.x > 300))

//----------------------------------------------------------------------------
// SETUP      SETUP      SETUP      SETUP      SETUP      SETUP      SETUP
//----------------------------------------------------------------------------
void setup() {
	Serial.begin(9600);
	tft.reset();
	tft.begin(0x9341);  // SDFP5408
	tft.setRotation(3);
	tft.fillScreen(BLACK);
	tft.setCursor(0, 0);
	tft.setTextColor(YELLOW);
	tft.setTextSize(3);
	tft.println("Setup completed.");
	waitOneTouch(true);
}

//----------------------------------------------------------------------------
// LOOP      LOOP      LOOP      LOOP      LOOP      LOOP      LOOP      LOOP
//----------------------------------------------------------------------------
void loop() {
	printTitle();
	tft.setFont(&FreeSansBold24pt7b);
	tft.setCursor(100, 170);
	tft.setTextColor(GREEN);
	tft.println("IN");
	printDuration("0hrs  23mins");
	waitOneTouch(false);

	printTitle();
	tft.setFont(&FreeSansBold24pt7b);
	tft.setCursor(8, 170);
	tft.setTextColor(RED);
	tft.println("OUT");
	printDuration("14hrs  5mins");
	waitOneTouch(false);
}

//----------------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------------
void printTitle() {
	tft.setFont();
	tft.fillScreen(BLACK);
	tft.setCursor(55, 10);
	tft.setTextColor(YELLOW);
	tft.setTextSize(5);
	tft.print("Benny is");
	tft.setTextSize(3);
}

void printDuration(String msg) {
	tft.fillRect(60, 194, 230, 32, WHITE);
	tft.setFont();
	tft.setTextSize(3);
	tft.setTextColor(BLACK);
	tft.setCursor(70, 200);
	tft.print(msg);
}

//----------------------------------------------------------------------------
// Has user touched the button?
//----------------------------------------------------------------------------
TSPoint waitOneTouch(boolean showMessage) {

	bool touchAnyWhere = false;

	// show the message (if any)
	if (showMessage) {
		tft.setTextSize(2);
		tft.setTextColor(WHITE);
		tft.println("\n\nTouch to proceed...");
		touchAnyWhere = true;
	}

	// Get a touch in the required button area (or anywhere if flag set)
	TSPoint p;
	do {
		p = ts.getPoint();
		pinMode(XM, OUTPUT);  // Pins configures again for TFT control
		pinMode(YP, OUTPUT);

	} while (p.z < MINPRESSURE || p.z > MAXPRESSURE || (btnCONTINUE && (touchAnyWhere == false)));

#ifdef _DEBUG_
	Serial.print("X:");
	Serial.println(p.x);
	Serial.print("Y:");
	Serial.println(p.y);
	Serial.println("");
#endif

	// All done, return the touch coordinates object
	return p;
}
