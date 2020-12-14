#include "p5d.h"
#include <iostream>
using namespace std;

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 3-6: Interactive Zoog?

p5d::p5DGraphics pg;

void setup() {
  // Set the size of the window
  pg.size(480, 270);  
  // The frame rate is set to 30 frames per second.
  pg.frameRate(30);
}

void draw() {
  // Draw a white background
  pg.background(255);  

  // Set ellipses and rects to CENTER mode
  pg.ellipseMode(pg.CENTER);
  pg.rectMode(pg.CENTER); 

  // Draw Zoog's body
  pg.stroke(0);
  pg.fill(175);
  pg.rect(pg.mouseX, pg.mouseY, 20, 100);

  // Draw Zoog's head
  pg.stroke(0);
  pg.fill(255);
  pg.ellipse(pg.mouseX, pg.mouseY-30, 60, 60); 

  // Draw Zoog's eyes
  // The eye color is determined by the mouse location.
  pg.fill(pg.mouseX/2, 0, pg.mouseY/2); 
  pg.ellipse(pg.mouseX-19, pg.mouseY-30, 16, 32); 
  pg.ellipse(pg.mouseX+19, pg.mouseY-30, 16, 32); 

  // Draw Zoog's legs
  pg.stroke(0);
  // The legs are drawn according to the mouse location and the previous mouse location.
  pg.line(pg.mouseX-10, pg.mouseY+50, pg.pmouseX-10, pg.pmouseY+60);
  pg.line(pg.mouseX+10, pg.mouseY+50, pg.pmouseX+10, pg.pmouseY+60);
}

void mousePressed() {
  cout<<"Take me to your leader!"<<endl; 
}

int main(int argc, char** argv) {
	
    pg.mousePressedFunc(mousePressed);
    pg.drawFunc(draw);
	
    setup();
	
	pg.listen();
}