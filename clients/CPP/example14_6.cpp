#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-6: rotateZ
float theta = 0.0;

void setup() {
  p5_size(200, 200);
  p5_frameRate(10);
}

void draw() {
    p5_background(255);
    p5_stroke(0);
    p5_fill(175);
    p5_translate(p5_width/2, p5_height/2);
    p5_rotate(theta);
    p5_rectMode(P5_CENTER);
    p5_rect(0, 0, 100, 100);
    theta += 0.02;
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
