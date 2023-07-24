#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-17: Nested push and pop

// Global angle for rotation
float theta = 0;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(480, 270);
  pg.frameRate(10);
}

void draw() {
  pg.background(255);
  pg.stroke(0);

  // Translate to center of window
  pg.translate(pg.width / 2, pg.height / 2);

  // Loop from 0 to 360 degrees (2*PI radians)
  for (float i = 0; i < pg.TWO_PI; i += 0.2) {

    // Push, rotate and draw a line!
    // The transformation state is saved at the beginning of each cycle through
    // the for loop and restored at the enpg. Try commenting out these lines to
    // see the difference!
    pg.pushMatrix();
    pg.rotate(theta + i);
    pg.line(0, 0, 100, 0);

    // Loop from 0 to 360 degrees (2*PI radians)
    for (float j = 0; j < pg.TWO_PI; j += 0.5) {
      // Push, translate, rotate and draw a line!
      pg.pushMatrix();
      pg.translate(100, 0);
      pg.rotate(-theta - j);
      pg.line(0, 0, 50, 0);
      // We're done with the inside loop, pop!
      pg.popMatrix();
    }

    // We're done with the outside loop, pop!
    pg.popMatrix();
  }
}

int main(int argc, char **argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
