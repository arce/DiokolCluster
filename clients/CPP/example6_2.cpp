#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 6-1: Many lines 

void setup() {
  p5_size(480,270);
  p5_background(255);
}

void draw() {
	// Legs
	p5_stroke(0);
	int y = 80;       // Vertical location of each line
	int x = 50;       // Initial horizontal location for first line
	int spacing = 10; // How far apart is each line
	int len = 20;     // Length of each line

	// Draw the first leg.
	p5_line(x,y,x,y + len); 
	// Add spacing so the next leg appears 10 pixels to the right.
	x = x + spacing; 

	// Continue this process for each leg, repeating it over and over.
	p5_line(x,y,x,y + len); 
	x = x + spacing;
	p5_line(x,y,x,y + len);
	x = x + spacing;
	p5_line(x,y,x,y + len);
	x = x + spacing;
	p5_line(x,y,x,y + len);
	x = x + spacing;
	p5_line(x,y,x,y + len);
	x = x + spacing;
	p5_line(x,y,x,y + len);
	x = x + spacing;
	p5_line(x,y,x,y + len);
	x = x + spacing;
	p5_line(x,y,x,y + len);
	x = x + spacing;
	p5_line(x,y,x,y + len);
	x = x + spacing;
	p5_line(x,y,x,y + len);
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
