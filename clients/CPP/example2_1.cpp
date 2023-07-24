#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 2-1: Zoog again

p5d::PGraphics pg("localhost","8888");

void setup() {
	pg.size(480, 270);	
}

void draw() {

	pg.background(255);
	pg.ellipseMode(pg.CENTER);
	pg.rectMode(pg.CENTER); 

	// Body
	pg.stroke(0);
	pg.fill(150);
	pg.rect(240, 145, 20, 100);

	// Head
	pg.fill(255);
	pg.ellipse(240, 115, 60, 60); 

	// Eyes
	pg.fill(0); 
	pg.ellipse(221, 115, 16, 32); 
	pg.ellipse(259, 115, 16, 32);

	// Legs
	pg.stroke(0);
	pg.line(230, 195, 220, 205);
	pg.line(250, 195, 260, 205);
	
}

int main(int argc, char **argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);
	pg.listen();
}