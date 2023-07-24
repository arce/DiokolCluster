#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-11: A growing rectangle, using scale()

float r = 0.0;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(200, 200);
  pg.frameRate(10);
}

void draw() {
  pg.background(255);
  // Translate to center of window
  pg.translate(pg.width/2, pg.height/2);

  // scale() increases the dimensions of an object relative to the origin by a percentage (1.0 = 100%). 
  // Notice how in this example the scaling effect causes the outline of the shape to become thicker.
  pg.scale(r); 

  // Display a rectangle in the middle of the screen
  pg.stroke(0);
  pg.fill(175);
  pg.rectMode(pg.CENTER);
  pg.rect(0, 0, 10, 10);

  // Increase the scale variable
  r += 0.2;

  // Retstart r
  if (r > 20) {
    r = 0;
  }
}

int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
