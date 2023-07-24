#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 5-3: Rollovers

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(480, 270);
}

void draw() {
	pg.background(255);
	pg.stroke(0);
	pg.line(320,0,320,360);
	pg.line(0,180,640,180);

	// Fill a black color
	pg.noStroke();
	pg.fill(0);

	// Depending on the mouse location, a different rectangle is displayed.    
	if (pg.mouseX < 320 && pg.mouseY < 180) {
	  pg.rect(0,0,320,180);
	} else if (pg.mouseX > 320 && pg.mouseY < 180) {
	  pg.rect(320,0,320,180);
	} else if (pg.mouseX < 320 && pg.mouseY > 180) {
	  pg.rect(0,180,320,180);
	} else if (pg.mouseX > 320 && pg.mouseY > 180) {
	  pg.rect(320,180,320,180);
	}
}

int main(int argc, char** argv) {
	pg.setupFunc(setup);
	pg.drawFunc(draw);

	pg.listen();
}
