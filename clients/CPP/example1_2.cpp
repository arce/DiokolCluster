#include "p5d.h"

	// Learning Processing
	// Daniel Shiffman
	// http://www.learningprocessing.com

	// Example 1-2: noFill

int main(int argc, char** argv) {

	p5d::p5DGraphics pg;
  
    pg.size(480,270);
	pg.background(255);

	// noFill() leaves the shape with only an outline.
	pg.noFill();
	pg.stroke(0);
	pg.ellipse(60,60,100,100);
    
    pg.listen();
}