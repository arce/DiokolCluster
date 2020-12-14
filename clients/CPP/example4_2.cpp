#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 4-2: Using variables

p5d::p5DGraphics pg;

// Declare and initialize two integer variables at the top of the code.
int circleX = 100;
int circleY = 100;

void setup() {
  pg.size(480, 270);
}

void draw() {
  pg.background(255);
  pg.stroke(0);
  pg.fill(175);
  // Use the variables to specify the location of an ellipse.
  pg.ellipse(circleX,circleY,50,50);
}

int main(int argc, char** argv) {
  pg.drawFunc(draw);
  setup();

  pg.listen();
}