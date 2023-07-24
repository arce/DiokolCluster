#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 5-8: Square following edge, uses a "state" variable

p5d::PGraphics pg("localhost", "8888");

int x = 0;  // x location of square
int y = 0;  // y location of square

int speed = 5;  // speed of square

// A variable to keep track of the square's "state".  
// Depending on the value of its state, it will either move right, down, left, or up.
int state = 0;

void setup() {
  pg.size(480, 270);
}

void draw() {
  pg.background(255);

  // Display the square
  pg.stroke(0);
  pg.fill(175);
  pg.rect(x,y,9,9);

  // If the state is 0, move to the right.
  if (state == 0) {
    x = x + speed;
    // If, while the state is 0, it reaches the right side of the window, change the state to 1
    // Repeat this same logic for all states!?
    if (x > pg.width-10) {
      x = pg.width-10;
      state = 1;
    }
  } else if (state == 1) {
    y = y + speed;
    if (y > pg.height-10) {
      y = pg.height-10;
      state = 2;
    }
  } else if (state == 2) {
    x = x - speed;
    if (x < 0) {
      x = 0;
      state = 3;
    }
  } else if (state == 3) {
    y = y - speed;
    if (y < 0) {
      y = 0;
      state=0;
    }
  }
}

int main(int argc, char** argv) {

	pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
