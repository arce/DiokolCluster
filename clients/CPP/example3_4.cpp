#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 3-4: Drawing a continuous line

p5d::p5DGraphics pg;

void setup() {
  pg.size(480, 270);
  pg.background(255);
}

void draw() {
  pg.stroke(0);

  // Draw a line from previous mouse location to current mouse location.
  pg.line(pg.pmouseX, pg.pmouseY, pg.mouseX, pg.mouseY);
}

int main(int argc, char **argv) {
  
  pg.drawFunc(draw);
  
  setup();
  
  pg.listen();
}