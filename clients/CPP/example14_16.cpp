#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-16: Simple solar system

// Angle of rotation around sun and planets
float theta = 0;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(480, 270);
  //p5_set3DMode();
  pg.frameRate(10);
}

void draw() {
   pg.background(255);
   pg.stroke(0);

   // Translate to center of window to draw the sun.
   pg.translate(pg.width/2, pg.height/2);
   pg.fillRGB(255, 200, 50);
   pg.ellipse(0, 0, 64, 64);

    // The earth rotates around the sun
   pg.pushMatrix();
   pg.rotate(theta);
   pg.translate(100, 0);
   pg.fillRGB(50, 200, 255);
   pg.ellipse(0, 0, 32, 32);

   // Moon #1 rotates around the earth
   // pushMatrix() is called to save the transformation state before drawing moon #1. 
   // This way we can pop and return to earth before drawing moon #2. 
   // Both moons rotate around the earth (which itself is rotating around the sun).
   pg.pushMatrix(); 
   pg.rotate(-theta*4);
   pg.translate(36, 0);
   pg.fillRGB(50, 255, 200);
   pg.ellipse(0, 0, 12, 12);
   pg.popMatrix();

    // Moon #2 also rotates around the earth
   pg.pushMatrix();
   pg.rotate(theta*2);
   pg.translate(24, 0);
   pg.fillRGB(50, 255, 200);
   pg.ellipse(0, 0, 6, 6);
   pg.popMatrix();

   pg.popMatrix();

   theta += 0.01;
}

int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
