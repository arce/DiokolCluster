#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 6-1: Many lines 

void setup() {
  pg.size(480,270);
  pg.background(255);
}

void draw() {
	// Legs
	pg.stroke(0);
	int y = 80;       // Vertical location of each line
	int x = 50;       // Initial horizontal location for first line
	int spacing = 10; // How far apart is each line
	int len = 20;     // Length of each line

	// Draw the first leg.
	pg.line(x,y,x,y + len); 
	// Add spacing so the next leg appears 10 pixels to the right.
	x = x + spacing; 

	// Continue this process for each leg, repeating it over and over.
	pg.line(x,y,x,y + len); 
	x = x + spacing;
	pg.line(x,y,x,y + len);
	x = x + spacing;
	pg.line(x,y,x,y + len);
	x = x + spacing;
	pg.line(x,y,x,y + len);
	x = x + spacing;
	pg.line(x,y,x,y + len);
	x = x + spacing;
	pg.line(x,y,x,y + len);
	x = x + spacing;
	pg.line(x,y,x,y + len);
	x = x + spacing;
	pg.line(x,y,x,y + len);
	x = x + spacing;
	pg.line(x,y,x,y + len);
	x = x + spacing;
	pg.line(x,y,x,y + len);
}

int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);
  pg.listen();
}

