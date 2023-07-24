#include "p5d.h"

// Learning Processing
// Daniel Shiffman
// http://www.learningprocessing.com

// Example 14-14: Rotating both squares

float theta1 = 0;
float theta2 = 0;

p5d::PGraphics pg("localhost", "8888");

void setup() {
  pg.size(200, 200);
  pg.frameRate(10);
}

void draw() {
   pg.background(255);
   pg.stroke(0);
   pg.fill(175);
   pg.rectMode(pg.CENTER);

   // Save the current transformation matrix. 
   // This is where we started, with (0,0) in the top left corner of the window and no rotation.
   pg.pushMatrix(); 

   // Translate and rotate the first rectangle.
   pg.translate(50, 50); 
   //p5_rotateZ(theta1);
   // Display the first rectangle.
   pg.rect(0, 0, 60, 60); 
   // Restore matrix from Step 1 so that it isn't affected by Steps 2 and 3!
   pg.popMatrix(); 

   pg.pushMatrix();
   // Translate and rotate the second rectangle.
   pg.translate(150, 150); 
   //p5_rotateY(theta2);
   // Display the second rectangle.
   pg.rect(0, 0, 60, 60); 
   pg.popMatrix();

   theta1 += 0.02;
   theta2 += 0.02;
}

int main(int argc, char** argv) {
  pg.setupFunc(setup);
  pg.drawFunc(draw);

  pg.listen();
}
