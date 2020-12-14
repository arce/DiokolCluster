#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 4-4: Many variables

p5d::p5DGraphics pg;

// We've got 8 variables now!  All  of type float.
float circleX = 0;
float circleY = 0;
float circleW = 50;
float circleH = 100;
float circleStroke = 255;
float circleFill = 0;
float backgroundColor = 255;
float change = 0.5;

// Your basic setup
void setup() {
  pg.size(480, 270);
}

void draw() {
  // Draw the background and the ellipse
  // Variables are used for everything: background, stroke, fill, location, and size.
  pg.background(backgroundColor);
  pg.stroke(circleStroke);
  pg.fill(circleFill);
  pg.ellipse(circleX,circleY,circleW,circleH);

  // Change the values of all variables
  // The variable change is used to increment and decrement the other variables.
  circleX = circleX + change;
  circleY = circleY + change;
  circleW = circleW + change;
  circleH = circleH - change;
  circleStroke = circleStroke - change;
  circleFill = circleFill + change;
}

int main(int argc, char** argv) {
	pg.drawFunc(draw);
	setup();
	
	pg.listen();
}