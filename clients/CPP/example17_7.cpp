#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 17-7: Boxes along a curve 

// The radius of a circle
float r = 100;

// The width and height of the boxes
float w = 40;
float h = 40;

void setup() {
  p5_size(480, 270);
}

void draw() {
    p5_background(255);

     // Start in the center and draw the circle
     p5_translate(p5_width/2, p5_height/2);
     p5_noFill();
     p5_stroke(0);
     // Our curve is a circle with radius r in the center of the window.
     p5_ellipse(0, 0, r*2, r*2); 
     // 10 boxes along the curve
     int totalBoxes = 10;
     // We must keep track of our position along the curve
     float arclength = 0;
     // For every box
     for (int i = 0; i < totalBoxes; i ++ ) {
       // Each box is centered so we move half the width
       arclength += w/2; 

       // Angle in radians is the arclength divided by the radius
       float theta = arclength / r;

       p5_pushMatrix();
       // Polar to cartesian coordinate conversion
       p5_translate(r*cos(theta), r*sin(theta));
       // Rotate the box
       p5_rotate(theta);

       // Display the box
       p5_fillA(0, 100);
       p5_rectMode(P5_CENTER);
       p5_rect(0, 0, w, h);
       p5_popMatrix();

       // Move halfway again
       arclength += w/2;
     }
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
