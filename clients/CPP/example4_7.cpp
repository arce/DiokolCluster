#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 4-7: Filling variables with random values

float r;
float g;
float b;
float a;

float diam;
float x;
float y;

p5d::p5DGraphics pg;

void setup() {
  pg.size(480, 270);
  pg.background(255);
}

void draw() {
  // Each time through draw(), new random numbers are picked for a new ellipse.
  r = pg.random(255);
  g = pg.random(255);
  b = pg.random(255);
  a = pg.random(255);
  diam = pg.random(20);
  x = pg.random(pg.width);
  y = pg.random(pg.height);
  
  // Use values to draw an ellipse
  pg.noStroke();
  pg.fill(r,g,b,a);
  pg.ellipse(x,y,diam,diam);
}

int main(int argc, char** argv) {
	pg.drawFunc(draw);
	setup();
	
	pg.listen();
}