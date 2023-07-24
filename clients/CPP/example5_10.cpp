#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 5-10: Zoog and conditionals

p5d::PGraphics pg("localhost", "8888");

float x = 100;
float y = 100;
float w = 60;
float h = 60;
float eyeSize = 16;

// Zoog has variables for speed in the horizontal and vertical direction.
float xspeed = 3;
float yspeed = 1;

void setup() {
  pg.size(480, 270);  
}

void draw() {
    // Change the location of Zoog by speed
    x = x + xspeed;
    y = y + yspeed;

    // An IF statement with a logical OR determines if Zoog has reached either the right or left edge of the screen.  
    // When this is true, we multiply speed by -1, reversing Zoog's direction!
    // Identical logic is applied to the y direction as well.
    if ((x > pg.width) || (x < 0)) {
      xspeed = xspeed * -1;
    }

    if ((y > pg.height) || (y < 0)) {
      yspeed = yspeed * -1;
    }

    pg.background(255);  
    pg.ellipseMode(pg.CENTER);
    pg.rectMode(pg.CENTER); 

    // Draw Zoog's body
    pg.stroke(0);
    pg.fill(150);
    pg.rect(x,y,w/6,h*2);

    // Draw Zoog's head
    pg.fill(255);
    pg.ellipse(x,y-h/2,w,h); 

    // Draw Zoog's eyes
    pg.fill(0); 
    pg.ellipse(x-w/3+1,y-h/2,eyeSize,eyeSize*2); 
    pg.ellipse(x+w/3-1,y-h/2,eyeSize,eyeSize*2);

    // Draw Zoog's legs
    pg.stroke(0);
    pg.line(x-w/12,y+h,x-w/4,y+h+10);
    pg.line(x+w/12,y+h,x+w/4,y+h+10);
}

int main(int argc, char** argv) {
	
		pg.setupFunc(setup);
  pg.drawFunc(draw);
  setup();
  
  pg.listen();
}
