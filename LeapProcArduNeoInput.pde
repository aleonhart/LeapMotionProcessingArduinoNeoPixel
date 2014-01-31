/*
 * Leap Motion -> Processing -> Arduino -> NeoPixel
 *
 * Michelle Leonhart 2014-01-30
 * @at0mbmxb www.tinwhiskers.net
 *
 */
 
import de.voidplus.leapmotion.*;
import processing.serial.*; 

Serial port;
LeapMotion leap;
int previousPosition = 0;
int currentPosition = 0;

void setup() {
  size(800, 800, P3D);
  background(255);

  leap = new LeapMotion(this);
  port = new Serial(this, "/dev/tty.usbmodem1411", 9600);
  /* If you want to change from port /dev/tty.usbmodem1411,
   * Use this to list out all available serial ports:
   * println(Serial.list());
   *
   * And pick the number of the one you want.
   * Like this: 
   * port = new Serial(this, Serial.list()[0], 9600);   <-- This would pick the first port from the list
   */  
}

void draw() {
  background(255);
  
  for (Hand hand : leap.getHands()) {
    hand.draw();
    
    // 0 - 24: 25 LEDs on my NeoPixel Strip
    currentPosition = (int) map(hand.getPosition().x, 0, 1000, 0, 24);

    if (previousPosition != currentPosition) {
      previousPosition = currentPosition;
      port.write(previousPosition);
    }
  }
}



