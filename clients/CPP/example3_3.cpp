#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 3-3: Zoog as dynamic sketch with variation

p5d::PGraphics pg("localhost","8888");

void setup() {
	pg.size(480, 270);
}

void draw() {

  pg.background(255);  // Draw a white background 

  // Set ellipses and rects to CENTER mode
  pg.ellipseMode(pg.CENTER);
  pg.rectMode(pg.CENTER); 

  // Draw Zoog's body
  pg.stroke(0);
  pg.fill(175);
  // Zoog's body is drawn at the location (mouseX, mouseY).
  pg.rect(pg.mouseX, pg.mouseY, 20, 100);

  // Draw Zoog's head
  pg.stroke(0);
  pg.fill(255);
  // Zoog's head is drawn above the body at the location (mouseX, mouseY - 30).
  pg.ellipse(pg.mouseX, pg.mouseY-30, 60, 60);

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