/*
 * Leap Motion -> Processing -> Arduino -> NeoPixel
 *
 * Michelle Leonhart 2014-01-30
 * @at0mbmxb www.tinwhiskers.net
 *
 */

#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, 3, NEO_RGB + NEO_KHZ800);

int previousPosition;
int currentPosition;
int serialInput;

void setup() {
  strip.begin();
  strip.setBrightness(50); 
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(9600); // Listen for input
}

void loop() {
  if (Serial.available()) {
    serialInput = Serial.read();   
    // if our position has changed
    if(serialInput != currentPosition) {  
      // take note of where we were    
      previousPosition = currentPosition;  
      // take note of where we are now 
      currentPosition = serialInput;  
      
      // make the current LED a pretty rainbow colour
      strip.setPixelColor(currentPosition, Wheel(currentPosition * 10)); 
      strip.show();
      
      // make the previous LED turn off
      strip.setPixelColor(previousPosition, strip.Color(0, 0, 0));
      strip.show();
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
     return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
     WheelPos -= 85;
     return strip.Color(255 - WheelPos, 0, WheelPos);
  } else {
     WheelPos -= 170;
     return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

