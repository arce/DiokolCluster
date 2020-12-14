#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-5: Rectangle rotating around center

p5d::p5DGraphics pg;

void draw() {
	pg.background(255);  
	pg.stroke(0);
	pg.fill(175);

	// Translate origin to center
	pg.translate(p5_width/2, p5_height/2);

	// The greek letter, theta, is often used as the name of a variable to store an angle
	// The angle ranges from 0 to TWO_PI using the map() function
	float theta = pg.map(pg.mouseX, 0, pg.width, 0, pg.TWO_PI); 

	// Rotate by the angle theta
	pg.rotate(theta);

	// Display rectangle with CENTER mode
	pg.rectMode(pg.CENTER);
	pg.rect(0, 0, 100, 100);
}

int main(int argc, char** argv) {

  pg.drawFunc(draw);
  
  pg.size(200, 200);
  pg.frameRate(10);
  
  pg.listen();
}
