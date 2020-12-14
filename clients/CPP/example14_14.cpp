#include "p5lib.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-14: Rotating both squares

float theta1 = 0;
float theta2 = 0;

void setup() {
  p5_size(200, 200);
  p5_frameRate(10);
}

void draw() {
   p5_background(255);
   p5_stroke(0);
   p5_fill(175);
   p5_rectMode(P5_CENTER);

   // Save the current transformation matrix. 
   // This is where we started, with (0,0) in the top left corner of the window and no rotation.
   p5_pushMatrix(); 

   // Translate and rotate the first rectangle.
   p5_translate(50, 50); 
   //p5_rotateZ(theta1);
   // Display the first rectangle.
   p5_rect(0, 0, 60, 60); 
   // Restore matrix from Step 1 so that it isn't affected by Steps 2 and 3!
   p5_popMatrix(); 

   p5_pushMatrix();
   // Translate and rotate the second rectangle.
   p5_translate(150, 150); 
   //p5_rotateY(theta2);
   // Display the second rectangle.
   p5_rect(0, 0, 60, 60); 
   p5_popMatrix();

   theta1 += 0.02;
   theta2 += 0.02;
}

int main(int argc, char** argv) {
  p5_setupFunc(setup);
  p5_drawFunc(draw);
  p5_init(argc,argv);
}
