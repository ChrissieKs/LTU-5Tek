#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 0          // PIN have to be 0.

int brightness = 20;   // Max is 255!
int waitTime = 100;    // The waiting time, after each method

/*
 * Creating an Adafruit neopixel object with the following parameters:
 *   Parameter 1 = number of pixels in strip
 *   Parameter 2 = Arduino pin number
 *   Parameter 3 = pixel type flags, DO NOT CHANGE THIS.
 */
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// This loop repeat the process forever.
void loop() {
// Test Pixels with a single color on all the LEDS:
  colorWipe(strip.Color(brightness, 0, 0), waitTime); // Red
  colorWipe(strip.Color(0, brightness, 0), waitTime); // Green
  colorWipe(strip.Color(0, 0, brightness), waitTime); // Blue
  
  theaterChase(strip.Color(brightness, brightness, brightness), waitTime); // theaterchase White
  theaterChase(strip.Color(brightness, 0, 0), waitTime);  // theatherchase Red
  theaterChase(strip.Color(0, 0, brightness), waitTime);  // theaterchase Blue

// Call the methods below
  rainbow(waitTime);
  rainbowCycle(waitTime);
  theaterChaseRainbow(waitTime);
}

/*
 * Fill the strip one LED after the other with a color
 * Parameter 1 = Color
 * Parameter 2 = Global variable waitTime
 */
void colorWipe(uint32_t color, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

/*
 * The method for the first rainbow 
 * Parameter 1 = Global variable waitTime
 */
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<(brightness+1); j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & brightness));
    }
    strip.show();
    delay(wait);
  }
}

/*
 * The method for the second rainbow
 * Parameter 1 = Global variable waitTime
 */
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & brightness));
    }
    strip.show();
    delay(wait);
  }
}

/*
 * The lights before the different rainbows
 * Parameter 1 = Color
 * Parameter 2 = Global variable waitTime
 */
void theaterChase(uint32_t color, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, color);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

/*
 * The method for the third rainbow. Theatre-style crawling lights with rainbow effect
 * Parameter 1 = Global variable waitTime
 */
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % brightness));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

/*
 * The colours are a transition r - g - b - back to r.
 */
uint32_t Wheel(byte WheelPos) {
  WheelPos = brightness - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(brightness - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, brightness - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, brightness - WheelPos * 3, 0);
}
