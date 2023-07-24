#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-9: Rotate around more than one axis
float theta = 0.0;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(480, 240);
  pg.frameRate(10);
}

void draw() {
    pg.background(255);
    pg.stroke(0);
    pg.fill(175);
	pg.translate(pg.width/2, pg.height/2);
	//p5_rotateX(p5_map(p5_mouseY, 0, p5_height, 0, P5_TWO_PI));
	//p5_rotateY(p5_map(p5_mouseX, 0, p5_width, 0, P5_TWO_PI));
	pg.rectMode(pg.CENTER);
	pg.rect(0, 0, 200, 150);
}

int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
