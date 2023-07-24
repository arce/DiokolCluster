#include "p5d.h"
#include <iostream>
using namespace std;

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 4-5: Using system variables

p5d::PGraphics pg("localhost","8888");

void setup() {
  pg.size(480, 270);
}

void draw() {
  pg.background(50);
  pg.stroke(255);
  // frameCount is used to color a rectangle.
  pg.fill(pg.frameCount / 2);
  pg.rectMode(pg.CENTER);
  // The rectangle will always be in the middle of the window 
  // if it is located at (width/2, height/2).
  pg.rect(pg.width/2, pg.height/2, pg.mouseX+10, pg.mouseY+10);
}

void keyPressed() {
  cout<<pg.key<<endl;
}

int main(int argc, char** argv) {
	pg.setupFunc(draw);
	pg.drawFunc(draw);
	pg.keyPressedFunc(keyPressed);
	
	pg.listen();
}