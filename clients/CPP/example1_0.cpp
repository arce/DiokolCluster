#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 1-1: stroke and fill

p5d::PGraphics pg(100);

void setup() { pg.size(640, 480); }

void draw() {
  pg.background(255);
  pg.stroke(0);
  pg.fill(150);
  pg.beginShape();
  pg.vertex(80, 0);
  pg.vertex(70, 100);
  pg.vertex(60, 0);
  pg.vertex(50, 100);
  pg.vertex(40, 0);
  pg.vertex(30, 100);
  pg.vertex(20, 0);
  pg.vertex(10, 100);
  pg.vertex(0, 0);
  pg.vertex(40, -20);
  pg.endShape(pg.CLOSE);
}

int main(int argc, char **argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);
  pg.listen();
}