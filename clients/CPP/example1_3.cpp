#include "p5d.h"
//using namespace p5d;

  // Learning Processing
  // Daniel Shiffman
  // http://www.learningprocessing.com

  // Example 1-3: RGB Color

int main(int argc, char** argv) {

	p5d::p5DGraphics pg;
	
	pg.background(255);    
	pg.noStroke();

    // Bright red
    pg.fill(255,0,0);
    pg.ellipse(20,20,16,16);

    // Dark red
    pg.fill(127,0,0);
    pg.ellipse(40,20,16,16);

    // Pink (pale red)
    pg.fill(255,200,200);
    pg.ellipse(60,20,16,16);
	
	pg.listen();
}