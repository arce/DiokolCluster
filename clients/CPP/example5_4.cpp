#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 5-4: Hold down the button

p5d::p5DGraphics pg;

bool button = false;

int x = 50;
int y = 50;
int w = 100;
int h = 75;

void setup() {
  pg.size(480, 270); 
}

void draw() {
	// The button is pressed if (mouseX,mouseY) is inside the rectangle and mousePressed is true.
	if (pg.mouseX > x && pg.mouseX < x+w && pg.mouseY > y && pg.mouseY < y+h && pg.mousePressed) {
	  button = true; 
	} else {
	  button = false;
	}

	if (button) {
	  pg.background(255);
	  pg.stroke(0);
	} else {
	  pg.background(0);
	  pg.stroke(255);
	}

	pg.fill(175);
	pg.rect(x,y,w,h);
}

int main(int argc, char** argv) {
	pg.drawFunc(draw);
	setup();

	pg.listen();
}
