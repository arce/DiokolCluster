#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 5-2: More conditionals

p5d::p5DGraphics pg;

// Three variables for the background color.
float r = 0;
float b = 0;
float g = 0;

void setup() {
  pg.size(480, 270);
}

void draw() {
    // Color the background and draw lines to divide the window in quadrants.
    pg.background(r,g,b);  
    pg.stroke(255);
    pg.line(pg.width/2,0,pg.width/2,pg.height);
    pg.line(0,pg.height/2,pg.width,pg.height/2);
  
    // If the mouse is on the right hand side of the window, increase red.  
    // Otherwise, it is on the left hand side and decrease red.
    if (pg.mouseX > pg.width/2) {
      r = r + 1; 
    } else {
      r = r - 1;
    }
  
    // If the mouse is on the bottom of the window, increase blue.  
    // Otherwise, it is on the top and decrease blue.
    if (pg.mouseY > pg.height/2) {
      b = b + 1; 
    } else {
      b = b - 1; 
    }
  
    // If the mouse is pressed (using the system variable mousePressed)
    if (pg.mousePressed) {
      g = g + 1; 
    } else {
      g = g - 1; 
    }  
  
    // Constrain all color values to between 0 and 255.
    r = pg.constrain(r,0,255);
    g = pg.constrain(g,0,255);
    b = pg.constrain(b,0,255);
}

int main(int argc, char** argv) {
    pg.drawFunc(draw);
    setup();
	
	pg.listen();
}
