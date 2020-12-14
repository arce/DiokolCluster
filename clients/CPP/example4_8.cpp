#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 4-8: Variable Zoog

// NEW FEATURE #1: Zoog will rise from below the screen 
// and fly off into space (above the screen.)

// NEW FEATURE #2: Zoog's eyes will be colored randomly as Zoog moves.

// Declaring Variables.  
// zoogX and zoogY are for feature #1.  
// eyeR, eyeG, eyeB are for feature #2.
float zoogX;
float zoogY;

float eyeR;
float eyeG;
float eyeB;

p5d::p5DGraphics pg;

void setup() {
  // Set the size of the window
  pg.size(480, 270);        
  // Feature #1.  zoogX and zoogY are initialized 
  // based on the size of the window.  Note we cannot 
  // initialize these variables before the size() 
  // function is called since we are using the built-in 
  // variables width and height.
  zoogX = pg.width/2;      // Zoog always starts in the middle
  zoogY = pg.height + 100; // Zoog starts below the screen
}

void draw() {

	pg.background(255);  // Draw a white background 

	// Set ellipses and rects to CENTER mode
	pg.ellipseMode(pg.CENTER);
	pg.rectMode(pg.CENTER); 

	// Draw Zoog's body
	pg.stroke(0);
	pg.fill(150);
	// Feature #1.  zoogX and zoogY are used for the shape locations.
	pg.rect(zoogX, zoogY, 20, 100);

	// Draw Zoog's head
	pg.stroke(0);
	pg.fill(255);
	pg.ellipse(zoogX, zoogY-30, 60, 60); 

	// Draw Zoog's eyes
	// Feature #2.  eyeR, eyeG, and eyeB are given 
	// random values and used in the fill() function.
	eyeR = pg.random(255);
	eyeG = pg.random(255);
	eyeB = pg.random(255);
	pg.fill(eyeR, eyeG, eyeB);

	pg.ellipse(zoogX-19, zoogY-30, 16, 32); 
	pg.ellipse(zoogX+19, zoogY-30, 16, 32); 

	// Draw Zoog's legs
	pg.stroke(150);
	pg.line(zoogX-10, zoogY+50, zoogX-10, pg.height);
	pg.line(zoogX+10, zoogY+50, zoogX+10, pg.height);

	// Zoog moves up
	zoogY = zoogY - 1;
}

int main(int argc, char** argv) {
	pg.drawFunc(draw);
	setup();
	
	pg.listen();
}