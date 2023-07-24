#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 5-1: Conditionals

p5d::PGraphics pg("localhost","8888");

// Variables
float r = 150;
float g = 0;
float b = 0;

void setup() {
  pg.size(480, 270);
}

void draw() {
  // Draw stuff
  pg.background(r,g,b);  
  pg.stroke(255);
  pg.line(pg.width/2,0,pg.width/2,pg.height);

  // If the mouse is on the right side of the screen is equivalent to 
  // "if mouseX is greater than width divided by 2."
  if(pg.mouseX > pg.width/2) {
    r = r + 1; 
  } else {
    r = r - 1;
  }

  // If r is greater than 255, set it back to 255.  
  // If r is less than 0, set it back to 0.
  if (r > 255) {
    r = 255; 
  } else if (r < 0) {
    r = 0; 
  }
}

int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);
  
  pg.listen();
}