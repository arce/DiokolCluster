#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-9: Rotate around more than one axis
float theta = 0.0;

void setup() {
  p5_size(480, 240);
  p5_frameRate(10);
}

void draw() {
    p5_background(255);
    p5_stroke(0);
    p5_fill(175);
	p5_translate(p5_width/2, p5_height/2);
	//p5_rotateX(p5_map(p5_mouseY, 0, p5_height, 0, P5_TWO_PI));
	//p5_rotateY(p5_map(p5_mouseX, 0, p5_width, 0, P5_TWO_PI));
	p5_rectMode(P5_CENTER);
	p5_rect(0, 0, 200, 150);
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
