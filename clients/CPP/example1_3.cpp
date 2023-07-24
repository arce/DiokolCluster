#include "p5d.h"
// using namespace p5d;

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 1-3: RGB Color

p5d::PGraphics pg("localhost","8888");

void setup() {
}

void draw() {
  pg.background(255,255,255,255);

	pg.noStroke();

  // Bright red
  pg.fill(255, 0, 0, 255);
  pg.ellipse(20, 20, 16, 16);

  // Dark red
  pg.fill(0, 255, 0 , 255);
  pg.ellipse(40, 20, 16, 16);

  // Pink (pale red)
  pg.fill(0, 0, 255, 255);
  pg.ellipse(60, 20, 16, 16);	
}

int main(int argc, char **argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);
	pg.listen();
}