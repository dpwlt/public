// Includes

#include <SPI.h>
#include <TFT_eSPI.h> // Call up TFT screen library
#include <TFT_Touch.h> // Call up touch screen library


// These are the pins used to interface between the 2046 touch controller and ESP32
#define DOUT 39  /* Data out pin (T_DO) of touch screen */
#define DIN  32  /* Data in pin (T_DIN) of touch screen */
#define DCS  33  /* Chip select pin (T_CS) of touch screen */
#define DCLK 25  /* Clock pin (T_CLK) of touch screen */


/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;

/*collect touch data*/
int X_RawData;
int Y_RawData;
int X_Coord;
int Y_Coord;

// Create tft and touch instances
TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT); /* Create an instance of the touch screen library */

void getTouchData()
{
    if (touch.Pressed())
  {
    X_Coord = touch.X();
    Y_Coord = touch.Y();
    Serial.print(X_Coord); Serial.print(","); Serial.println(Y_Coord);
    delay(50);
  }
}

uint32_t rd = 0xFFFFFFFF;

void setup()
{
  Serial.begin(115200); // Start Serial monitor

  tft.init(); // Initialise TFT display

  touch.setCal(490, 3470, 711, 3499, 320, 240, 1); //This is the calibration line produced by the TFT_Touch_Calibrate_v2 sketch
  
  // Set the TFT and touch screen to landscape orientation
  tft.setRotation(1);
  tft.invertDisplay(1);
  touch.setRotation(1);

  tft.setTextSize(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);

  tft.fillRect(40, 40, 20, 20, TFT_WHITE);
  tft.fillRect(80, 80, 20, 20, TFT_WHITE);
  

}

void loop()
{
  

  rd = tft.readPixel(42,42);
  Serial.print(" Pixel value read    = ");Serial.println(rd,HEX);
  
  getTouchData();
  if ((X_Coord > 40 && X_Coord < 60)&&(Y_Coord > 40 && Y_Coord < 60))
  {
    tft.fillRect(40, 40, 20, 20, TFT_RED);
  }
  if ((X_Coord > 80 && X_Coord < 100)&&(Y_Coord > 80 && Y_Coord < 100))
  {
    tft.fillRect(80, 80, 20, 20, TFT_BLUE);
  }
  
}
