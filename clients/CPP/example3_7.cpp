#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 3-7: Translated zoog

p5d::PGraphics pg("localhost","8888");

void setup() {
  pg.size(480, 270);
}

void draw() {
  pg.background(255);
  pg.rectMode(pg.CENTER);
  pg.ellipseMode(pg.CENTER);

  // Draw everything relative to (mouseX, mouseY)
  pg.translate(pg.mouseX, pg.mouseY);

  // Draw Zoog's body
  pg.stroke(0);
  pg.fill(175);
  pg.rect(0, 0, 20, 100);

  // Draw Zoog's head
  pg.stroke(0);
  pg.fill(255);
  pg.ellipse(0, -30, 60, 60);
  // Draw Zoog's eyes
  pg.stroke(0);
  pg.fill(0);
  pg.ellipse(-19, -30, 16, 32);
  pg.ellipse( 19, -30, 16, 32);

  // Draw Zoog's legs
  pg.stroke(0);
  pg.line(-10, 50, -20, 60);
  pg.line( 10, 50, 20, 60);
}

int main(int argc, char** argv) {
	
  pg.setupFunc(setup);
  pg.drawFunc(draw);
  
  pg.listen();
}