#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-11: A growing rectangle, using scale()

float r = 0.0;

void setup() {
  p5_size(200, 200);
  p5_frameRate(10);
}

void draw() {
  p5_background(255);
  // Translate to center of window
  p5_translate(p5_width/2, p5_height/2);

  // scale() increases the dimensions of an object relative to the origin by a percentage (1.0 = 100%). 
  // Notice how in this example the scaling effect causes the outline of the shape to become thicker.
  p5_scale(r); 

  // Display a rectangle in the middle of the screen
  p5_stroke(0);
  p5_fill(175);
  p5_rectMode(P5_CENTER);
  p5_rect(0, 0, 10, 10);

  // Increase the scale variable
  r += 0.2;

  // Retstart r
  if (r > 20) {
    r = 0;
  }
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
