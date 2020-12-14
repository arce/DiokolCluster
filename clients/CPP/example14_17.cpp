#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-17: Nested push and pop

// Global angle for rotation
float theta = 0;

void setup() {
  p5_size(480, 270);
  p5_frameRate(10);
}

void draw() {
  p5_background(255);
  p5_stroke(0);

  // Translate to center of window
  p5_translate(p5_width/2, p5_height/2);

  // Loop from 0 to 360 degrees (2*PI radians)
  for (float i = 0; i < P5_TWO_PI; i += 0.2) {

    // Push, rotate and draw a line!
    // The transformation state is saved at the beginning of each cycle through the for loop and restored at the enpg. 
    // Try commenting out these lines to see the difference!
    p5_pushMatrix(); 
    p5_rotate(theta + i);
    p5_line(0, 0, 100, 0);

    // Loop from 0 to 360 degrees (2*PI radians)
    for (float j = 0; j < P5_TWO_PI; j += 0.5) {
      // Push, translate, rotate and draw a line!
      p5_pushMatrix();
      p5_translate(100, 0);
      p5_rotate(-theta-j);
      p5_line(0, 0, 50, 0);
      // We're done with the inside loop, pop!
      p5_popMatrix();
    }

    // We're done with the outside loop, pop!
    p5_popMatrix();
  }
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
