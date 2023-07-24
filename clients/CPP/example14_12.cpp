#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-12: Rotating one square

float theta1 = 0;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(200, 200);
  pg.frameRate(10);
}

void draw() {
  pg.background(255);
  pg.stroke(0);
  pg.fill(175);
  pg.rectMode(P5_CENTER);

  pg.translate(50, 50);
  //p5_rotateZ(theta1);
  pg.rect(0, 0, 60, 60);

  theta1 += 0.02;
}


int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}