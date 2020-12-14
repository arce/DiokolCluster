#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 3-1: Zoog as dynamic sketch

p5d::p5DGraphics pg;

// setup() runs first one time.  
// size() should always be first line of setup

void setup() {
	// Set the size of the window
	pg.size(480, 270);
}

// draw() loops continuously until you close the sketch window.
void draw() {
    // Draw a white background
    pg.background(255);   

    // Set CENTER mode
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

	pg.drawFunc(draw);
	setup();
	
	pg.listen();
}