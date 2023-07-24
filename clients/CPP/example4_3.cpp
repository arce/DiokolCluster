#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 4-3: Varying variables

p5d::PGraphics pg("localhost","8888");

// Declare and initialize two integer variables at the top of the code.
int circleX = 0;
int circleY = 100;

void setup() {
  pg.size(480, 270);
  pg.frameRate(10);
  pg.loop();
}

void draw() {
  pg.background(255);
  pg.stroke(0);
  pg.fill(175);
  // Use the variables to specify the location of an ellipse.
  pg.ellipse(circleX, circleY, 50, 50);

  // An assignment operation that increments the value of circleX by 1.
  circleX = circleX + 1;
}

int main(int argc, char** argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);
	pg.listen();
}