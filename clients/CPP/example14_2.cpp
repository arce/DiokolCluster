#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-2: Multiple translations

p5d::p5DGraphics pg;

void draw() {
  pg.background(255);
  pg.stroke(0);
  pg.fill(175);

  // Grab mouse coordinates, constrained to window
  int mx = pg.constrain(pg.mouseX, 0, pg.width);
  int my = pg.constrain(pg.mouseY, 0, pg.height);

  // Translate to the mouse location
  pg.translate(mx, my);
  pg.ellipse(0, 0, 8, 8);

  // Translate 100 pixels to the right
  pg.translate(100, 0);
  pg.ellipse(0, 0, 8, 8);

  // Translate 100 pixels down
  pg.translate(0, 100);
  pg.ellipse(0, 0, 8, 8);

  // Translate 100 pixels left
  pg.translate(-100, 0);
  pg.ellipse(0, 0, 8, 8);
}

int main(int argc, char** argv) {

  pg.drawFunc(draw);
  pg.size(200, 200);
  pg.frameRate(10);
  
  pg.listen();
}
