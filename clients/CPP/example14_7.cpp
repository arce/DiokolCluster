#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-7: rotateX
float theta = 0.0;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(200, 200);
  pg.frameRate(10);
}

void draw() {
    pg.background(255);
    pg.stroke(0);
    pg.fill(175);
    pg.translate(p5_width/2, p5_height/2);
    //p5_rotateX(theta);
    pg.rectMode(P5_CENTER);
    pg.rect(0, 0, 100, 100);
    theta += 0.02;
}

int main(int argc, char **argv) {

  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
