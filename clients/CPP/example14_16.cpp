#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-16: Simple solar system

// Angle of rotation around sun and planets
float theta = 0;

void setup() {
  p5_size(480, 270);
  //p5_set3DMode();
  p5_frameRate(10);
}

void draw() {
   p5_background(255);
   p5_stroke(0);

   // Translate to center of window to draw the sun.
   p5_translate(p5_width/2, p5_height/2);
   p5_fillRGB(255, 200, 50);
   p5_ellipse(0, 0, 64, 64);

    // The earth rotates around the sun
   p5_pushMatrix();
   p5_rotate(theta);
   p5_translate(100, 0);
   p5_fillRGB(50, 200, 255);
   p5_ellipse(0, 0, 32, 32);

   // Moon #1 rotates around the earth
   // pushMatrix() is called to save the transformation state before drawing moon #1. 
   // This way we can pop and return to earth before drawing moon #2. 
   // Both moons rotate around the earth (which itself is rotating around the sun).
   p5_pushMatrix(); 
   p5_rotate(-theta*4);
   p5_translate(36, 0);
   p5_fillRGB(50, 255, 200);
   p5_ellipse(0, 0, 12, 12);
   p5_popMatrix();

    // Moon #2 also rotates around the earth
   p5_pushMatrix();
   p5_rotate(theta*2);
   p5_translate(24, 0);
   p5_fillRGB(50, 255, 200);
   p5_ellipse(0, 0, 6, 6);
   p5_popMatrix();

   p5_popMatrix();

   theta += 0.01;
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
