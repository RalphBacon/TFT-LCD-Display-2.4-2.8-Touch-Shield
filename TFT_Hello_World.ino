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

// Assign human-readable names to some common 16-bit colour values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

// Make an array of those values too
int tftColours[] = {BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE};

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

//----------------------------------------------------------------------------
// SETUP      SETUP      SETUP      SETUP      SETUP      SETUP      SETUP
//----------------------------------------------------------------------------
void setup() {
	Serial.begin(9600);
	tft.reset();
	tft.begin(0x9341);  // SDFP5408
	tft.setRotation(3);
	randomSeed(analogRead(A1));
}

//----------------------------------------------------------------------------
// LOOP      LOOP      LOOP      LOOP      LOOP      LOOP      LOOP      LOOP
//----------------------------------------------------------------------------
void loop() {

	tft.fillScreen(BLACK);

	tft.setCursor(0, 100);
	tft.setTextColor(YELLOW);
	tft.setFont(&FreeSansBold24pt7b);
	tft.setTextSize(2);
	tft.println("HELLO");

	tft.setCursor(10, 200);
	tft.setTextSize(1);
	tft.setTextColor(RED);
	tft.println("ARDUINITES");

	delay(2000);
	tft.fillScreen(BLACK);
	tft.setCursor(0, 50);
	tft.setTextColor(YELLOW);
	tft.println("Want to know");
	tft.setTextColor(BLUE);
	tft.println("how to do this");
	tft.setTextColor(GREEN);
	tft.print("on your TFT?");
	delay(1500);

	tft.setTextColor(RED);
	tft.setTextSize(1);
	tft.setCursor(150, 220);
	tft.print("Well...");
	delay(2000);
	tft.fillScreen(BLACK);

	for (int cnt=0; cnt< 20; cnt++) {
		tft.setCursor(0, 100);
		tft.setTextColor(getRandomColour());
		tft.setFont(&FreeSansBold24pt7b);
		tft.setTextSize(2);
		tft.println("Watch");

		tft.setTextSize(1);
		tft.setCursor(150, 150);
		tft.setTextColor(getRandomColour());
		tft.println("this");

		tft.setCursor(50, 220);
		tft.setTextColor(getRandomColour());
		tft.println("video!");
	}

	// Simple button
	// x, y, w, h, colour
	tft.fillRoundRect(220, 180, 75, 40, 3, WHITE);
	tft.setFont();
	tft.setTextSize(3);
	tft.setTextColor(BLACK);
	tft.setCursor(240, 190);
	tft.print("OK");

	// User touches screen
	waitOneTouch();
}

unsigned int getRandomColour() {
	static unsigned int prevColour = 99;
	int colour;
	do {
		colour = random(0, sizeof tftColours / 2);
		} while (colour == prevColour);

	prevColour = colour;
	return tftColours[colour];
}

//----------------------------------------------------------------------------
// Has user touched the button?
//----------------------------------------------------------------------------
TSPoint waitOneTouch() {

	// Get a touch in the required button area (or anywhere if flag set)
	TSPoint p;
	do {
		p = ts.getPoint();
		pinMode(XM, OUTPUT);  // Pins configures again for TFT control
		pinMode(YP, OUTPUT);

	} while (p.z < MINPRESSURE || p.z > MAXPRESSURE );

	// All done, return the touch coordinates object
	return p;
}