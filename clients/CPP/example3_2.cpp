#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 3-2: mouseX and mouseY

p5d::PGraphics pg("localhost","8888");

void setup() {
	pg.size(480, 270);
}

void draw() {
  pg.background(255);

  // Body
  pg.stroke(0);
  pg.fill(175);
  pg.rectMode(pg.CENTER);

  // mouseX is a keyword that the sketch replaces with the horizontal position
  // of the mouse. mouseY is a keyword that the sketch replaces with the
  // vertical position of the mouse.
  pg.rect(pg.mouseX, pg.mouseY, 50, 50);
}

int main(int argc, char **argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);
	pg.listen();
}