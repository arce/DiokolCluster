#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-1: A growing rectangle, or a rectangle moving toward you?

float r = 8;

p5d::p5DGraphics pg;

void draw() {
  pg.background(255);

  // Display a rectangle in the middle of the screen
  pg.stroke(0);
  pg.fill(175);
  pg.rectMode(pg.CENTER);
  pg.rect(p5_width/2, pg.height/2, r, r);

  // Increase the rectangle size
  r++ ;

  // Start rectangle over
  if (r > pg.width) {
	r = 0;
  }
}

int main(int argc, char** argv) {
  pg.drawFunc(draw);
  pg.size(200, 200);
  pg.frameRate(10);
  pg.listen();
}
