#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 5-6: Bouncing Ball

p5d::p5DGraphics pg;

int x = 0;
int speed = 2;

void setup() {
  pg.size(480, 270);
}

void draw() {
    pg.background(255);

    // Add the current speed to the x location.
    x = x + speed;

    // Remember, || means "or."
    if ((x > pg.width) || (x < 0)) {
      // If the object reaches either edge, multiply speed by -1 to turn it arounpg.
      speed = speed * -1;
    }

    // Display circle at x location
    pg.stroke(0);
    pg.fill(175);
    pg.ellipse(x,100,32,32);
}

int main(int argc, char** argv) {
  pg.drawFunc(draw);
  setup();
  
  pg.listen();
}
