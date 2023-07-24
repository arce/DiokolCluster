#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 1-2: noFill

p5d::PGraphics pg("localhost","8888");

void setup() {
	pg.size(480, 270);
}

void draw() {

  pg.background(255);

  // noFill() leaves the shape with only an outline.
  pg.noFill();
  pg.stroke(0);
  pg.ellipse(60, 60, 100, 100);
}

int main(int argc, char **argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);
	pg.listen();
}