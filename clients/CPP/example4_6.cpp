#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 4-6: Ellipse with variables

p5d::PGraphics pg("localhost","8888");

// Declare and initialize your variables!
float r = 100;
float g = 150;
float b = 200;
float a = 200;
  
float diam = 20;
float x = 100;
float y = 100;

void setup() {
  pg.size(480, 270);
  pg.background(255);
}

void draw() {
  // Use those variables to draw an ellipse
  pg.stroke(0);
  pg.fill(r,g,b,a);  // (Remember, the fourth argument for a color is transparency.
  pg.ellipse(x,y,diam,diam);  
}

int main(int argc, char** argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);

	pg.listen();
}