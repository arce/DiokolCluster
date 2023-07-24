#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-3: A rectangle moving along the z-axis

// A variable for the Z (depth) coordinate

float z = 0;
p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(200, 200);
  pg.frameRate(10);
}

void draw() {
  pg.background(255);
  pg.stroke(0);
  pg.fill(175);

  // Translate to a point before displaying a shape there
  // p5_translate3d(p5_width/2, p5_height/2, z);
  pg.rectMode(pg.CENTER);
  pg.rect(0, 0, 8, 8);

  // Increment z (i.e. move the shape toward the viewer)
  z += 2;

  // Restart rectangle
  if (z > 200) {
    z = 0;
  }
}

int main(int argc, char **argv) {

  pg.setupFunc(setup);
  pg.drawFunc(draw);
  pg.listen();
}
