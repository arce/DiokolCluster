#include "p5d.h"

  // Learning Processing
  // Daniel Shiffman
  // http://www.learningprocessing.com

  // Example 1-1: stroke and fill

p5d::PGraphics pg;

void setup() {
	pg.size(480, 270);
}

void draw() {
	pg.background(255);
	pg.stroke(0);
	pg.fill(150);
	pg.rect(50,50,75,100);
}

int main(int argc, char **argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);
	pg.listen();
}