#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 3-5: mousePressed and keyPressed

p5d::p5DGraphics pg;

void setup() {
  pg.size(480, 270);
  pg.background(255);
}

void draw() {
  // Nothing happens in draw() in this example!
}

// Whenever a user clicks the mouse the code written inside mousePressed() is executepg.
void mousePressed() {
  pg.stroke(0);
  pg.fill(175);
  pg.rectMode(pg.CENTER);
  pg.rect(pg.mouseX, pg.mouseY, 16, 16);
}

// Whenever a user presses a key the code written inside keyPressed() is executepg.
void keyPressed() {
  pg.background(255);
}

int main(int argc, char** argv) {
	
  pg.drawFunc(draw);
  pg.mousePressedFunc(mousePressed);
  pg.keyPressedFunc(keyPressed);
    
  setup();

  pg.listen();
}